#ifndef OSTHREAD_H
#define OSTHREAD_H

#include <revolution/types.h>

#include <revolution/os/OSContext.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_THREAD_ATTR_DETACH 0x0001u

typedef s32 OSPriority;

typedef struct OSThread OSThread;
typedef struct OSThreadQueue OSThreadQueue;
typedef struct OSThreadLink OSThreadLink;

typedef struct OSMutex OSMutex;
typedef struct OSMutexQueue OSMutexQueue;
typedef struct OSMutexLink OSMutexLink;

typedef struct OSSemaphore OSSemaphore;

// size: 0x8
struct OSThreadQueue {
    OSThread* head;
    OSThread* tail;
};

// size: 0x8
struct OSThreadLink {
    OSThread* next;
    OSThread* prev;
};

// size: 0x8
struct OSMutexQueue {
    OSMutex* head;
    OSMutex* tail;
};

// size: 0x8
struct OSMutexLink {
    OSMutex* next;
    OSMutex* prev;
};

// size: 0x318
struct OSThread {
    OSContext context;
    u16 state;
    u16 attr;
    s32 suspend;
    OSPriority priority;
    OSPriority base;
    void* value;
    OSThreadQueue* queue;
    OSThreadLink link;
    OSThreadQueue queueJoin;
    OSMutex* mutex;
    OSMutexQueue queueMutex;
    OSThreadLink linkActive;
    u8* stackBase;
    u32* stackEnd;
    s32 error;
    void* specific[2];
};

struct OSMutex {
    OSThreadQueue queue;
    OSThread* thread;
    s32 count;
    OSMutexLink link;
};

// size: 0xc
struct OSSemaphore {
    s32 count;
    OSThreadQueue queue;
};

void OSInitThreadQueue(OSThreadQueue* queue);
OSThread* OSGetCurrentThread(void);
BOOL OSIsThreadSuspended(OSThread* thread);
BOOL OSIsThreadTerminated(OSThread* thread);
void OSYieldThread(void);
BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stackBase, u32 stackSize, OSPriority priority, u16 attribute);
void OSExitThread(void* val);
void OSCancelThread(OSThread* thread);
BOOL OSJoinThread(OSThread* thread, void** val);
s32 OSResumeThread(OSThread* thread);
s32 OSSuspendThread(OSThread* thread);
void OSSleepThread(OSThreadQueue* queue);
void OSWakeupThread(OSThreadQueue* queue);
BOOL OSSetThreadPriority (OSThread* thread, OSPriority priority);
OSPriority OSGetThreadPriority(OSThread* thread);

void OSInitSemaphore(OSSemaphore* sem, s32 count);
s32 OSWaitSemaphore(OSSemaphore* sem);
s32 OSSignalSemaphore(OSSemaphore* sem);

#ifdef __cplusplus
}
#endif

#endif // OSTHREAD_H
