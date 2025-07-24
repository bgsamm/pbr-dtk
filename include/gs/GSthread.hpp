#pragma once

#include <revolution/types.h>
#include <revolution/os.h>

// size: 0x370
struct GSthreadHandle {
    // TODO fill out remaining fields (if possible)
    /* 0x0 */ OSThread mThread;
    /* 0x318 */ void *mStack;
    /* 0x31c */ vu32 mFlags;
    /* 0x320 */ u32 mID;
    u8 unk1[0x24];
    /* 0x348 */ bool _348;
    u8 unk2[0x1f];
    /* 0x368 */ GSthreadHandle *mNext;
    u8 unk3[0x4];

    void clearFlags();
    void sleepThread();
    void resetHandle();
    void resumeThread();
    void stopThread(bool wait);
    void suspendThread();
    bool isThreadStopped();
};

// size: 0x1c
class GSthreadManager {
public:
    /* 0x0 */ u32 mThreadHandleCount;
    /* 0x4 */ GSthreadHandle *mThreadHandlePool;
    /* 0x8 */ OSPriority mParentThreadPriority;
    /* 0xc */ OSThreadQueue mThreadQueue;
    /* 0x14 */ GSthreadHandle *mThreadStartQueue;
    /* 0x18 */ OSThread *mParentThread;

    GSthreadManager(u32 poolCount);

    GSthreadHandle *getFreeThreadHandle();
    GSthreadHandle *createThread(u32 threadID, void *(*func)(void *), void *userParam, u32 stackSize, OSPriority priority, u16 attributes);
    void update();
    void suspendThread(u32 threadID);
    void resumeThread(u32 threadID);
    void stopThread(u32 threadID);
    void fn_80224584(bool param1);
    void sleepCurrentThread();
    bool isCurrentThreadManaged();

    static GSthreadManager *sInstance;
};

namespace GSthread {
    void threadTaskCallback(u32 taskID, void *userParam);
    void init(u32 poolCount);
};
