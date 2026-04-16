#include <private/os.h>
#include <revolution/os.h>

#include <revolution/base/PPCArch.h>

/* Macros for dequeueing and enqueueing thread */

#define ENQUEUE_THREAD(thread, queue, link)                                                                                                          \
    {                                                                                                                                                \
        OSThread* __prev = (queue)->tail;                                                                                                            \
        if (__prev == NULL) {                                                                                                                        \
            (queue)->head = (thread);                                                                                                                \
        } else {                                                                                                                                     \
            __prev->link.next = (thread);                                                                                                            \
        }                                                                                                                                            \
        (thread)->link.prev = __prev;                                                                                                                \
        (thread)->link.next = NULL;                                                                                                                  \
        (queue)->tail = (thread);                                                                                                                    \
    }

#define DEQUEUE_THREAD(thread, queue, link)                                                                                                          \
    {                                                                                                                                                \
        OSThread* __next = (thread)->link.next;                                                                                                      \
        OSThread* __prev = (thread)->link.prev;                                                                                                      \
        if (__next == NULL) {                                                                                                                        \
            (queue)->tail = __prev;                                                                                                                  \
        } else {                                                                                                                                     \
            __next->link.prev = __prev;                                                                                                              \
        }                                                                                                                                            \
        if (__prev == NULL) {                                                                                                                        \
            (queue)->head = __next;                                                                                                                  \
        } else {                                                                                                                                     \
            __prev->link.next = __next;                                                                                                              \
        }                                                                                                                                            \
    }

#define ENQUEUE_THREAD_PRIO(thread, queue, link)                                                                                                     \
    {                                                                                                                                                \
        OSThread* __prev;                                                                                                                            \
        OSThread* __next;                                                                                                                            \
        for (__next = (queue)->head; __next && (__next->priority <= (thread)->priority); __next = __next->link.next)                                 \
            ;                                                                                                                                        \
                                                                                                                                                     \
        if (__next == NULL) {                                                                                                                        \
            ENQUEUE_THREAD(thread, queue, link);                                                                                                     \
        } else {                                                                                                                                     \
            (thread)->link.next = __next;                                                                                                            \
            __prev = __next->link.prev;                                                                                                              \
            __next->link.prev = (thread);                                                                                                            \
            (thread)->link.prev = __prev;                                                                                                            \
            if (__prev == NULL) {                                                                                                                    \
                (queue)->head = (thread);                                                                                                            \
            } else {                                                                                                                                 \
                __prev->link.next = (thread);                                                                                                        \
            }                                                                                                                                        \
        }                                                                                                                                            \
    }

#define DEQUEUE_HEAD(thread, queue, link)                                                                                                            \
    {                                                                                                                                                \
        OSThread* __next = thread->link.next;                                                                                                        \
        if (__next == NULL) {                                                                                                                        \
            (queue)->tail = NULL;                                                                                                                    \
        } else {                                                                                                                                     \
            __next->link.prev = NULL;                                                                                                                \
        }                                                                                                                                            \
        (queue)->head = __next;                                                                                                                      \
    }

/* Exactly named `IsSuspended` for assert */
#define IsSuspended(suspend) (suspend > 0)

#define OS_THREAD_STACK_MAGIC 0xDEADBABE

/* Run queue */
static vu32 RunQueueBits;
static OSThreadQueue RunQueue[OS_PRIORITY_MAX + 1];
static vBOOL RunQueueHint;
static vs32 Reschedule;

/* Idle and default stuff */
static OSThread IdleThread;
static OSThread DefaultThread;
static OSContext IdleContext;

/* Auto generated by linker. */
extern u8 _stack_addr[];
extern u8 _stack_end[];

/* Queue initialization */

void OSInitThreadQueue(OSThreadQueue* queue);
static void OSInitMutexQueue(OSMutexQueue* queue);

/* Other small utilities */

static void OSClearStack(u8 value) {
    u32 *sp, *p;
    u32 pattern;

    u32 val32 = (u32)value;
    pattern = (val32 << 24) | (val32 << 16) | (val32 << 8) | val32;

    sp = (u32*)OSGetStackPointer();
    for (p = __OSCurrentThread->stackEnd + 1; p < sp; ++p) {
        *p = pattern;
    }
}

static void OSSetCurrentThread(OSThread* thread);

/* Switch thread callback */

static void DefaultSwitchThreadCallback(OSThread* from, OSThread* to) {
}
static OSSwitchThreadCallback SwitchThreadCallback = DefaultSwitchThreadCallback;

void __OSThreadInit() {
    OSThread* thread = &DefaultThread;
    OSPriority prio;

    // Setup default thread
    thread->state = OS_THREAD_STATE_RUNNING;
    thread->attr = OS_THREAD_ATTR_DETACH;
    thread->base = 16;
    thread->priority = 16;
    thread->suspend = 0;
    thread->value = (void*)-1;
    thread->mutex = 0;

    // Setup queues
    OSInitThreadQueue(&thread->queueJoin);
    OSInitMutexQueue(&thread->queueMutex);

    // Setup contexts
    __OSFPUContext = &thread->context;
    OSClearContext(&thread->context);
    OSSetCurrentContext(&thread->context);

    // Setup stack
    thread->stackBase = (u8*)&_stack_addr;
    thread->stackEnd = (u32*)&_stack_end;
    *thread->stackEnd = OS_THREAD_STACK_MAGIC;
    OSSetCurrentThread(thread);
    OSClearStack(0);

    // Setup run queues
    RunQueueBits = 0;
    RunQueueHint = FALSE;
    for (prio = 0; prio < OS_PRIORITY_MAX + 1; prio++) {
        OSInitThreadQueue(&RunQueue[prio]);
    }

    // Setup active thread queue
    OSInitThreadQueue(&__OSActiveThreadQueue);
    ENQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);

    // Setup idle context
    OSClearContext(&IdleContext);

    Reschedule = 0;
}

void OSInitThreadQueue(OSThreadQueue* queue) {
    queue->head = queue->tail = NULL;
}

void OSInitMutexQueue(OSMutexQueue* queue) {
    queue->head = queue->tail = NULL;
}

void OSSetCurrentThread(OSThread* thread) {
    SwitchThreadCallback(OSGetCurrentThread(), thread);
    __OSCurrentThread = thread;
}

OSThread* OSGetCurrentThread() {
    return __OSCurrentThread;
}

static void __OSSwitchThread(OSThread* thread) {
    OSSetCurrentThread(thread);
    OSSetCurrentContext(&thread->context);
    OSLoadContext(&thread->context);
}

BOOL OSIsThreadSuspended(OSThread* thread) {
    return (IsSuspended(thread->suspend)) ? TRUE : FALSE;
}

BOOL OSIsThreadTerminated(OSThread* thread) {
    return thread->state == OS_THREAD_STATE_DEAD || thread->state == OS_THREAD_STATE_UNINITIALIZED ? TRUE : FALSE;
}

static BOOL __OSIsThreadActive(OSThread* thread) {
    OSThread* active;
    if (thread->state == OS_THREAD_STATE_UNINITIALIZED) {
        return FALSE;
    }
    for (active = __OSActiveThreadQueue.head; active; active = active->linkActive.next) {
        if (thread == active) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 OSDisableScheduler() {
    BOOL enabled;
    s32 count;
    enabled = OSDisableInterrupts();
    count = Reschedule++;
    OSRestoreInterrupts(enabled);
    return count;
}

s32 OSEnableScheduler() {
    BOOL enabled;
    s32 count;
    enabled = OSDisableInterrupts();
    count = Reschedule--;
    OSRestoreInterrupts(enabled);
    return count;
}

static void SetRun(OSThread* thread) {
    thread->queue = &RunQueue[thread->priority];
    ENQUEUE_THREAD(thread, thread->queue, link);
    RunQueueBits |= 1 << (OS_PRIORITY_MAX - thread->priority);
    RunQueueHint = TRUE;
}

static void UnsetRun(OSThread* thread) NO_INLINE {
    OSThreadQueue* queue;
    queue = thread->queue;
    DEQUEUE_THREAD(thread, queue, link);
    if (queue->head == NULL) {
        RunQueueBits &= ~(1 << (OS_PRIORITY_MAX - thread->priority));
    }
    thread->queue = NULL;
}

OSPriority __OSGetEffectivePriority(OSThread* thread) {
    OSPriority priority;
    OSMutex* mutex;
    OSThread* blocked;
    priority = thread->base;
    for (mutex = thread->queueMutex.head; mutex; mutex = mutex->link.next) {
        blocked = mutex->queue.head;
        if (blocked != NULL && blocked->priority < priority) {
            priority = blocked->priority;
        }
    }
    return priority;
}

OSThread* SetEffectivePriority(OSThread* thread, OSPriority priority) {
    switch (thread->state) {
        case OS_THREAD_STATE_READY: {
            UnsetRun(thread);
            thread->priority = priority;
            SetRun(thread);

            break;
        }
        case OS_THREAD_STATE_WAITING: {
            DEQUEUE_THREAD(thread, thread->queue, link);
            thread->priority = priority;

            ENQUEUE_THREAD_PRIO(thread, thread->queue, link);
            if (thread->mutex != NULL) {
                return thread->mutex->thread;
            }

            break;
        }
        case OS_THREAD_STATE_RUNNING: {
            RunQueueHint = TRUE;
            thread->priority = priority;

            break;
        }
    }

    return NULL;
}

static void UpdatePriority(OSThread* thread) {
    OSPriority priority;
    do {
        if (IsSuspended(thread->suspend)) {
            break;
        }
        priority = __OSGetEffectivePriority(thread);
        if (thread->priority == priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
    } while (thread);
}

void __OSPromoteThread(OSThread* thread, OSPriority priority) {
    do {
        if (IsSuspended(thread->suspend) || thread->priority <= priority) {
            break;
        }
        thread = SetEffectivePriority(thread, priority);
    } while (thread);
}

OSThread* SelectThread(BOOL yield) {
    OSContext* currentContext;

    OSThread *currentThread, *nextThread;

    OSPriority priority;
    OSThreadQueue* queue;

    if (Reschedule > 0) {
        return NULL;
    }

    currentContext = OSGetCurrentContext();
    currentThread = OSGetCurrentThread();

    if (currentContext != &currentThread->context) {
        return NULL;
    }

    if (currentThread) {
        if (currentThread->state == OS_THREAD_STATE_RUNNING) {
            if (yield == FALSE) {
                priority = __cntlzw(RunQueueBits);
                if (currentThread->priority <= priority)
                    return NULL;
            }
            currentThread->state = OS_THREAD_STATE_READY;
            SetRun(currentThread);
        }
        if (!(currentThread->context.state & OS_THREAD_STATE_RUNNING) && OSSaveContext(&currentThread->context) != 0) {
            return NULL;
        }
    }

    if (RunQueueBits == 0) {
        OSSetCurrentThread(NULL);
        OSSetCurrentContext(&IdleContext);
        do {
            OSEnableInterrupts();
            while (RunQueueBits == 0) {
            }
            OSDisableInterrupts();
        } while (RunQueueBits == 0);
        OSClearContext(&IdleContext);
    }

    RunQueueHint = 0;
    priority = __cntlzw(RunQueueBits);

    queue = &RunQueue[priority];
    nextThread = queue->head;

    DEQUEUE_HEAD(nextThread, queue, link);

    if (queue->head == NULL) {
        RunQueueBits &= ~(1 << (OS_PRIORITY_MAX - priority));
    }
    nextThread->queue = NULL;
    nextThread->state = OS_THREAD_STATE_RUNNING;
    __OSSwitchThread(nextThread);
    return nextThread;
}

void __OSReschedule() {
    if (RunQueueHint) {
        SelectThread(FALSE);
    }
}

void OSYieldThread() {
    BOOL enabled = OSDisableInterrupts();
    SelectThread(TRUE);
    OSRestoreInterrupts(enabled);
}

BOOL OSCreateThread(OSThread* thread, void* (*ThreadFunc)(void*), void* param, void* stack, u32 stackSize, OSPriority priority, u16 attr) {
    BOOL enabled;
    u32 sp;
    int i;

    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return FALSE;
    }

    thread->state = OS_THREAD_STATE_READY;
    thread->attr = attr & OS_THREAD_ATTR_DETACH;
    thread->priority = thread->base = priority;
    thread->suspend = 1;
    thread->value = (void*)-1;
    thread->mutex = NULL;
    OSInitThreadQueue(&thread->queueJoin);
    OSInitMutexQueue(&thread->queueMutex);

    sp = (u32)stack;
    sp = ROUNDDOWN(sp, 8);
    sp -= 8;

    ((u32*)sp)[0] = 0;
    ((u32*)sp)[1] = 0;

    OSInitContext(&thread->context, (u32)ThreadFunc, sp);

    thread->context.lr = (u32)OSExitThread;
    thread->context.gpr[3] = (u32)param;
    thread->stackBase = stack;
    thread->stackEnd = (u32*)((u32)stack - stackSize);
    *thread->stackEnd = OS_THREAD_STACK_MAGIC;
    thread->error = 0;
    for (i = 0; i < OS_THREAD_SPECIFIC_MAX; ++i) {
        thread->specific[i] = 0;
    }

    enabled = OSDisableInterrupts();
    if (__OSErrorTable[OS_EXCEPTION_FLOATING_POINT_EXCEPTION] != NULL) {
        thread->context.srr1 |= (MSR_FE0 | MSR_FE1);
        thread->context.state |= OS_THREAD_STATE_READY;
        thread->context.fpscr = OS_FPSCR_ENABLE | 4;

        for (i = 0; i < OS_PRIORITY_MAX + 1; ++i) {
            *(u64*)&thread->context.fpr[i] = (u64)0xFFFFFFFFFFFFFFFFLL;
            *(u64*)&thread->context.psf[i] = (u64)0xFFFFFFFFFFFFFFFFLL;
        }
    }

    ENQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
    OSRestoreInterrupts(enabled);

    return TRUE;
}

void OSExitThread(void* val) {
    BOOL enabled;
    OSThread* currentThread;

    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();
    OSClearContext(&currentThread->context);

    if (currentThread->attr & OS_THREAD_ATTR_DETACH) {
        DEQUEUE_THREAD(currentThread, &__OSActiveThreadQueue, linkActive);
        currentThread->state = OS_THREAD_STATE_UNINITIALIZED;
    } else {
        currentThread->state = OS_THREAD_STATE_DEAD;
        currentThread->value = val;
    }

    __OSUnlockAllMutex(currentThread);
    OSWakeupThread(&currentThread->queueJoin);

    RunQueueHint = TRUE;

    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSCancelThread(OSThread* thread) {
    BOOL enabled = OSDisableInterrupts();

    switch (thread->state) {
        case OS_THREAD_STATE_READY: {
            if (!IsSuspended(thread->suspend)) {
                UnsetRun(thread);
            }
            break;
        }
        case OS_THREAD_STATE_RUNNING: {
            RunQueueHint = TRUE;
            break;
        }
        case OS_THREAD_STATE_WAITING: {
            DEQUEUE_THREAD(thread, thread->queue, link);

            thread->queue = NULL;
            if (!IsSuspended(thread->suspend) && thread->mutex) {
                UpdatePriority(thread->mutex->thread);
            }
            break;
        }
        default: {
            OSRestoreInterrupts(enabled);
            return;
        }
    }

    OSClearContext(&thread->context);
    if (thread->attr & OS_THREAD_ATTR_DETACH) {
        DEQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
        thread->state = OS_THREAD_STATE_UNINITIALIZED;
    } else {
        thread->state = OS_THREAD_STATE_DEAD;
    }

    __OSUnlockAllMutex(thread);
    OSWakeupThread(&thread->queueJoin);
    __OSReschedule();

    OSRestoreInterrupts(enabled);
}

BOOL OSJoinThread(OSThread* thread, void* val) {
    BOOL enabled = OSDisableInterrupts();

    if (!(thread->attr & OS_THREAD_ATTR_DETACH) && thread->state != OS_THREAD_STATE_DEAD && thread->queueJoin.head == NULL) {
        OSSleepThread(&thread->queueJoin);
        if (!__OSIsThreadActive(thread)) {
            OSRestoreInterrupts(enabled);
            return FALSE;
        }
    }

    if (((volatile OSThread*)thread)->state == OS_THREAD_STATE_DEAD) {
        if (val != NULL) {
            *(u32*)val = (u32)thread->value;
        }
        DEQUEUE_THREAD(thread, &__OSActiveThreadQueue, linkActive);
        thread->state = OS_THREAD_STATE_UNINITIALIZED;
        OSRestoreInterrupts(enabled);
        return TRUE;
    }

    OSRestoreInterrupts(enabled);
    return FALSE;
}

s32 OSResumeThread(OSThread* thread) {
    BOOL enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();

    suspendCount = thread->suspend--;

    if (thread->suspend < 0) {
        thread->suspend = 0;
    } else if (thread->suspend == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_READY: {
                thread->priority = __OSGetEffectivePriority(thread);
                SetRun(thread);
                break;
            }

            case OS_THREAD_STATE_WAITING: {
                DEQUEUE_THREAD(thread, thread->queue, link);

                thread->priority = __OSGetEffectivePriority(thread);
                ENQUEUE_THREAD_PRIO(thread, thread->queue, link);

                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
            }
        }

        __OSReschedule();
    }

    OSRestoreInterrupts(enabled);
    return suspendCount;
}

s32 OSSuspendThread(OSThread* thread) {
    BOOL enabled;
    s32 suspendCount;

    enabled = OSDisableInterrupts();
    suspendCount = thread->suspend++;

    if (suspendCount == 0) {
        switch (thread->state) {
            case OS_THREAD_STATE_RUNNING: {
                RunQueueHint = TRUE;
                thread->state = OS_THREAD_STATE_READY;
                break;
            }

            case OS_THREAD_STATE_READY: {
                UnsetRun(thread);
                break;
            }

            case OS_THREAD_STATE_WAITING: {
                DEQUEUE_THREAD(thread, thread->queue, link);
                thread->priority = OS_PRIORITY_MAX + 1;
                ENQUEUE_THREAD(thread, thread->queue, link);

                if (thread->mutex) {
                    UpdatePriority(thread->mutex->thread);
                }
                break;
            }
        }

        __OSReschedule();
    }

    OSRestoreInterrupts(enabled);

    return suspendCount;
}

void OSSleepThread(OSThreadQueue* queue) {
    BOOL enabled;
    OSThread* currentThread;

    enabled = OSDisableInterrupts();
    currentThread = OSGetCurrentThread();

    currentThread->state = OS_THREAD_STATE_WAITING;
    currentThread->queue = queue;
    ENQUEUE_THREAD_PRIO(currentThread, queue, link);

    RunQueueHint = TRUE;

    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

void OSWakeupThread(OSThreadQueue* queue) {
    BOOL enabled = OSDisableInterrupts();

    while (queue->head) {
        OSThread* thread = queue->head;
        DEQUEUE_HEAD(thread, queue, link);

        thread->state = OS_THREAD_STATE_READY;
        if (!IsSuspended(thread->suspend)) {
            SetRun(thread);
        }
    }
    __OSReschedule();
    OSRestoreInterrupts(enabled);
}

BOOL OSSetThreadPriority(OSThread* thread, OSPriority priority) {
    BOOL enabled;

    if (priority < OS_PRIORITY_MIN || priority > OS_PRIORITY_MAX) {
        return FALSE;
    }

    enabled = OSDisableInterrupts();

    if (thread->base != priority) {
        thread->base = priority;
        UpdatePriority(thread);
        __OSReschedule();
    }

    OSRestoreInterrupts(enabled);

    return TRUE;
}

OSPriority OSGetThreadPriority(OSThread* thread) {
    return thread->base;
}

OSThread* OSSetIdleFunction(OSIdleFunction idleFunc, void* param, void* stack, u32 stackSize) {
    if (idleFunc) {
        if (IdleThread.state == OS_THREAD_STATE_UNINITIALIZED) {
            OSCreateThread(&IdleThread, (void* (*)(void*))idleFunc, param, stack, stackSize, 31, OS_THREAD_ATTR_DETACH);
            OSResumeThread(&IdleThread);
            return &IdleThread;
        }
    } else {
        if (IdleThread.state != OS_THREAD_STATE_UNINITIALIZED) {
            OSCancelThread(&IdleThread);
        }
    }
    return NULL;
}

static void SleepAlarmHandler(OSAlarm* alarm, OSContext* context) {
    OSResumeThread((OSThread*)OSGetAlarmUserData(alarm));
}

void OSSleepTicks(OSTime tick) {
    BOOL enabled;
    OSThread* current;
    OSAlarm sleepAlarm;

    enabled = OSDisableInterrupts();
    current = OSGetCurrentThread();

    if (current == NULL) {
        OSRestoreInterrupts(enabled);
        return;
    }

    OSCreateAlarm(&sleepAlarm);
    OSSetAlarmTag(&sleepAlarm, (u32)current);
    OSSetAlarmUserData(&sleepAlarm, (void*)current);
    OSSetAlarm(&sleepAlarm, tick, SleepAlarmHandler);

    OSSuspendThread(current);

    OSCancelAlarm(&sleepAlarm);

    OSRestoreInterrupts(enabled);
}
