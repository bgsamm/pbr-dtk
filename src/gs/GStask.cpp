#include "version.hpp"
#include <cstring>

#include <revolution/os.h>
#include <revolution/vi.h>

#include "gs/GSmem.hpp"
#include "gs/GStask.hpp"
#include "gs/GSvideo.hpp"

#define STACK_SIZE 0x2000

/* lbl_8063F5D0 */ static GStaskHandle *sTaskPool;
/* lbl_8063F5D4 */ static u32 sActiveTaskHandleCount;
/* lbl_8063F5D8 */ static u32 sIdleTaskHandleCount;
/* lbl_8063F5DC */ static u32 sTotalTaskHandleCount;
// TODO name this variable
static bool lbl_8063F5E0;
/* lbl_8063F5E4 */ static u8 *sIdleStack;
/* lbl_8063F5E8 */ static GStaskHandle *sCurrentTask;
/* lbl_8063F5EC */ static GStaskHandle *sTaskListHead;
/* lbl_8063F5F0 */ static GStaskHandle *sIdleTaskListHead;
/* lbl_8063F5F4 */ static VIRetraceCallback sRetraceCallback;

static inline u32 getTaskID(GStaskHandle *task) {
    return ((u32)task - (u32)sTaskPool) / sizeof(GStaskHandle) + 1;
}

void GStask::runTasksOfType(GStaskType type) {
    GStaskHandle *task = sTaskListHead;
    while (task) {
        GStaskHandle *next = task->mNext;
        if (task->mType == type && !task->mDisabled && (!lbl_8063F5E0 || !task->_C)) {
            sCurrentTask = task;
            task->mCallback(getTaskID(task), task->mUserParam);
        }
        task = next;
    }
    sCurrentTask = NULL;
}

void GStask::retraceCallback(u32 retraceCount) {
    runTasksOfType(TASK_TYPE_RETRACE);

    if (sRetraceCallback != NULL) {
        sRetraceCallback(retraceCount);
    }
}

void GStask::idleCallback(void *param) {
    GStaskHandle *node, *next;

    while (true) {
        runTasksOfType(TASK_TYPE_IDLE);
    
        BOOL intEnabled = OSDisableInterrupts();

        node = sIdleTaskListHead;
        while (node) {
            next = node->mNext;
            insertTaskByPriority(node);
            node = next;
        }
        sIdleTaskListHead = NULL;
    
        OSRestoreInterrupts(intEnabled);
    }
}

GStaskHandle *GStask::getFreeTaskHandle(GStaskType taskType) {
    GStaskHandle *node;
    int count;
    
    if (taskType == TASK_TYPE_IDLE) {
        node = sTaskPool + sActiveTaskHandleCount;
        count = sIdleTaskHandleCount;
    }
    else {
        node = sTaskPool;
        count = sActiveTaskHandleCount;
    }

    for (int i = 0; i != count; i++, node++) {
        if (node->mType == TASK_TYPE_NULL) {
            return node;
        }
    }

    return NULL;
}

void GStask::insertTaskByPriority(GStaskHandle *taskHandle) {
    GStaskHandle *node = sTaskListHead;
    while (node->mNext && node->mPriority < taskHandle->mPriority) {
        node = node->mNext;
    }

    if (!node->mNext && node->mPriority < taskHandle->mPriority) {
        taskHandle->mPrev = node;
        taskHandle->mNext = NULL;
        node->mNext = taskHandle;
        return;
    }

    if (node->mPrev != NULL) {
        node->mPrev->mNext = taskHandle;
    }

    taskHandle->mPrev = node->mPrev;
    taskHandle->mNext = node;
    node->mPrev = taskHandle;

    if (sTaskListHead == node) {
        sTaskListHead = taskHandle;
    }
}

void GStask::pushIdleTask(GStaskHandle *taskHandle) {
    taskHandle->mNext = sIdleTaskListHead;
    sIdleTaskListHead = taskHandle;
}

void GStask::enqueueTask(GStaskHandle *taskHandle) {
    if (sTaskListHead == NULL) {
        sTaskListHead = taskHandle;
        return;
    }

    BOOL intEnabled = OSDisableInterrupts();
    if (taskHandle->mType == TASK_TYPE_IDLE) {
        pushIdleTask(taskHandle);
    }
    else {
        insertTaskByPriority(taskHandle);
    }
    OSRestoreInterrupts(intEnabled);
}

void GStask::init(u32 activeCount, u32 idleCount) {
    sActiveTaskHandleCount = activeCount;
    sIdleTaskHandleCount = idleCount;
    sTotalTaskHandleCount = activeCount + idleCount;

    sCurrentTask = NULL;

    sTaskPool = (GStaskHandle *)GSmem::allocFromDefaultHeap(sTotalTaskHandleCount * sizeof(GStaskHandle));
    if (sTaskPool == NULL) {
        return;
    }
    
    for (u32 i = 0; i < sTotalTaskHandleCount; i++) {
        sTaskPool[i].mType = TASK_TYPE_NULL;
    }

    sIdleStack = (u8 *)GSmem::allocFromDefaultHeap(STACK_SIZE);
    OSSetIdleFunction(idleCallback, NULL, sIdleStack + STACK_SIZE - 4, STACK_SIZE - 4);

    if (GSvideo::sInstance) {
        VIRetraceCallback temp = GSvideo::sInstance->mRetraceCallback;
        GSvideo::sInstance->mRetraceCallback = retraceCallback;
        sRetraceCallback = temp;
    }
}

u32 GStask::createTask(GStaskType taskType, u8 priority, u32 userParam, GStaskCallback callback) {
    GStaskHandle *node = getFreeTaskHandle(taskType);

    if (node == NULL) {
        return 0;
    }

    node->mPrev = NULL;
    node->mNext = NULL;
    node->mType = taskType;
    node->mPriority = priority;
    node->mDisabled = false;
    node->mUserParam = userParam;
    node->mCallback = callback;
    node->_C = 0;
    node->mName[0] = '\0';

    enqueueTask(node);

    return getTaskID(node);
}

void GStask::runMainTasks() {
    runTasksOfType(TASK_TYPE_MAIN);
}

// TODO name this function
GStaskHandle *GStask::fn_80224074(u32 param1) {
    GStaskHandle *node = sTaskListHead;
    while (node) {
        node = node->mNext;
    }
    return node;
}

void GStask::setTaskName(u32 taskID, char *name) {
    GStaskHandle *node;
    
    if (name != NULL && taskID != 0) {
        node = &sTaskPool[taskID - 1];
        memcpy(node->mName, name, sizeof(node->mName) - 1);
        node->mName[sizeof(node->mName) - 1] = '\0';
    }
}
