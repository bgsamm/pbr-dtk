#include "version.hpp"

#include <revolution/os.h>

#include "gs/GSmem.hpp"
#include "gs/GStask.hpp"
#include "gs/GSthread.hpp"

/* lbl_8063F600 */ GSthreadManager *GSthreadManager::sInstance;

void GSthread::threadTaskCallback(u32 taskID, u32 userParam) {
    GSthreadManager::sInstance->update();
}

void GSthread::init(u32 poolCount) {
    GSthreadManager::sInstance = new GSthreadManager(poolCount);

    u32 taskID = GStask::createTask(TASK_TYPE_MAIN, 0, 0, threadTaskCallback);
    GStask::setTaskName(taskID, "GSthreadManager");
}

GSthreadManager::GSthreadManager(u32 poolCount) {
    mThreadHandleCount = poolCount;
    mThreadStartQueue = NULL;
    mParentThreadPriority = OSGetThreadPriority(OSGetCurrentThread());
    mThreadHandlePool = (GSthreadHandle *)GSmem::allocFromDefaultHeapAndClear(poolCount * sizeof(GSthreadHandle));
    mParentThread = OSGetCurrentThread();
    OSInitThreadQueue(&mThreadQueue);
}

GSthreadHandle *GSthreadManager::getFreeThreadHandle() {
    GSthreadHandle *end = mThreadHandlePool + mThreadHandleCount;
    GSthreadHandle *threadHandle = mThreadHandlePool;

    while (threadHandle != end) {
        if (!(threadHandle->mFlags & 1)) {
            return threadHandle;
        }
        threadHandle++;
    }

    return NULL;
}

GSthreadHandle *GSthreadManager::createThread(
    u32 threadID,
    void *(*func)(void *),
    void *param,
    u32 stackSize,
    OSPriority priority,
    u16 attributes
) {
    GSthreadHandle *threadHandle = getFreeThreadHandle();
    if (threadHandle == NULL) {
        return NULL;
    }

    priority = mParentThreadPriority + priority + 1;
    if (priority >= 30) {
        priority = 29;
    }

    void *stack = GSmem::allocFromDefaultHeap(stackSize);
    if (stack == NULL) {
        return NULL;
    }

    if (threadHandle != NULL) {
        threadHandle->clearFlags();
    }

    if (param == NULL) {
        param = threadHandle;
    }

    void *stackBase = (u8 *)stack + stackSize;
    BOOL success = OSCreateThread(
        &threadHandle->mThread,
        func,
        param,
        stackBase,
        stackSize,
        priority,
        attributes
    );
    if (!success) {
        return NULL;
    }

    threadHandle->mFlags = 1;
    threadHandle->mStack = stack;
    threadHandle->mID = threadID;
    threadHandle->mNext = NULL;

    if (mThreadStartQueue == NULL) {
        mThreadStartQueue = threadHandle;
    }
    else {
        GSthreadHandle *ptr = mThreadStartQueue;
        while (ptr->mNext != NULL) {
            ptr = ptr->mNext;
        }
        ptr->mNext = threadHandle;
    }

    return threadHandle;
}

void GSthreadManager::update() {
    GSthreadHandle *threadHandle;
    
    threadHandle = mThreadHandlePool;
    while (threadHandle != (mThreadHandlePool + mThreadHandleCount)) {
        // Was this supposed to be a &&?
        if (threadHandle->mFlags & threadHandle->isThreadStopped()) {
            threadHandle->resetHandle();
        }
        threadHandle++;
    }

    OSWakeupThread(&mThreadQueue);
    OSSetThreadPriority(OSGetCurrentThread(), 30);

    threadHandle = mThreadStartQueue;
    while (threadHandle != NULL) {
        if (OSIsThreadSuspended(&threadHandle->mThread)) {
            OSResumeThread(&threadHandle->mThread);
        }
        threadHandle = threadHandle->mNext;
    }
    mThreadStartQueue = NULL;

    OSSetThreadPriority(OSGetCurrentThread(), mParentThreadPriority);
}

void GSthreadManager::suspendThread(u32 threadID) {
    GSthreadHandle *threadHandle = mThreadHandlePool;
    while (threadHandle != (mThreadHandlePool + mThreadHandleCount)) {
        if ((threadHandle->mFlags & 1) && threadID == threadHandle->mID) {
            threadHandle->suspendThread();
        }
        threadHandle++;
    }
}

void GSthreadManager::resumeThread(u32 threadID) {
    GSthreadHandle *threadHandle = mThreadHandlePool;
    while (threadHandle != (mThreadHandlePool + mThreadHandleCount)) {
        if ((threadHandle->mFlags & 1) && threadID == threadHandle->mID) {
            threadHandle->resumeThread();
        }
        threadHandle++;
    }
}

void GSthreadManager::stopThread(u32 threadID) {
    GSthreadHandle *threadHandle = mThreadHandlePool;
    while (threadHandle != (mThreadHandlePool + mThreadHandleCount)) {
        if ((threadHandle->mFlags & 1) && threadID == threadHandle->mID) {
            threadHandle->stopThread(false);
        }
        threadHandle++;
    }
}

// TODO name this function
void GSthreadManager::fn_80224584(bool param1) {

}

void GSthreadManager::sleepCurrentThread() {
    if (isCurrentThreadManaged()) {
        OSSleepThread(&mThreadQueue);
    }
}

bool GSthreadManager::isCurrentThreadManaged() {
    OSThread *currentThread = OSGetCurrentThread();

    GSthreadHandle *end = mThreadHandlePool + mThreadHandleCount;
    GSthreadHandle *threadHandle = mThreadHandlePool;

    while (threadHandle != end) {
        if ((threadHandle->mFlags & 1) && currentThread == &threadHandle->mThread) {
            return true;
        }
        threadHandle++;
    }

    return false;
}

void GSthreadHandle::clearFlags() {
    mFlags = 0;
}

void GSthreadHandle::sleepThread() {
    GSthreadManager::sInstance->sleepCurrentThread();
}

void GSthreadHandle::resetHandle() {
    if (mStack != NULL) {
        GSmem::freeDefaultHeapBlock(mStack);
        mStack = NULL;
    }
    mFlags = 0;
    mID = 0;
    _348 = false;
}

void GSthreadHandle::resumeThread() {
    if (mFlags & 1) {
        OSResumeThread(&mThread);
    }
}

void GSthreadHandle::stopThread(bool wait) {
    if ((mFlags & 1) == 0) {
        return;
    }

    // TODO get this to load new copy of mFlags
    mFlags |= 2;

    if (OSGetCurrentThread() == &mThread) {
        OSExitThread(NULL);
        return;
    }

    OSCancelThread(&mThread);
    if (wait) {
        void *exitVal;
        OSJoinThread(&mThread, &exitVal);
    }
}

void GSthreadHandle::suspendThread() {
    if (mFlags & 1) {
        OSSuspendThread(&mThread);
    }
}

bool GSthreadHandle::isThreadStopped() {
    // Does not match using !(mFlags & 1)
    if ((mFlags & 1) == 0) {
        return true;
    }
     
    return OSIsThreadTerminated(&mThread) == TRUE;
}
