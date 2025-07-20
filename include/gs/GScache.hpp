#pragma once

#include <revolution/types.h>

#include "gs/GSmem.hpp"

typedef bool (*UnkFunc1)(void *, u32, u32);
typedef void (*UnkFunc2)(u32, void *, u32);

struct GScacheObjNode {
    /* 0x0 */ GScacheObjNode *mNext;
};

// size: 0x1c
struct GScacheObjPool {
    /* 0x0 */ u32 mUsedNodes;
    /* 0x4 */ u32 mPeakUsedNodes;
    /* 0x8 */ u32 mCount;
    /* 0xc */ u32 mNodeSize;
    /* 0x10 */ GScacheObjNode *mStart;
    /* 0x14 */ GScacheObjNode *mEnd;
    /* 0x18 */ GScacheObjNode *mFreeHead;
};

// size: 0x24
struct GScacheEntry {
    /* 0x0 */ bool mOwnsBuffer;
    /* 0x1 */ bool mLocked;
    /* 0x4 */ u32 mRefCount;
    /* 0x8 */ MEMHeapHandle mHeap;
    /* 0xc */ void *mBuffer;
    /* 0x10 */ u32 mFsysId;
    /* 0x14 */ u32 mFileId;
    /* 0x18 */ UnkFunc1 _18;
    /* 0x1c */ GScacheEntry *mNext;
    /* 0x20 */ GScacheEntry *mPrev;
};

namespace GScache {
    // GScache.cpp
    GScacheEntry *findCacheEntry(u32 fsysId, u32 fileId);
    GScacheEntry *releaseCacheEntry(GScacheEntry *cacheEntry, bool param2);
    void initFileCache(u32 param1);
    void *createCacheEntryOnHeap(MEMHeapHandle heap, u32 size, u32 fsysId, u32 fileId, UnkFunc1 param5);
    void *createCacheEntryOnHeapAligned(MEMHeapHandle heap, u32 size, u32 align, u32 fsysId, u32 fileId, UnkFunc1 param6);
    void *createCacheEntryAligned(u32 size, u32 align, u32 fsysId, u32 fileId, UnkFunc1 param5);
    void setCacheEntryBuffer(void *buffer, u32 fsysId, u32 fileId, UnkFunc1 param4);
    void *getCacheEntryBuffer(u32 fsysId, u32 fileId);
    u32 incrementRefCount(u32 fsysId, u32 fileId);
    u32 decrementRefCount(u32 fsysId, u32 fileId);
    u32 getCacheEntryBufferSize(u32 fsysId, u32 fileId);
    void freeFileCacheEntry(u32 fsysId, u32 fileId);
    void freeFsysCacheEntries(u32 fsysId);
    bool copyCacheEntry(u32 srcFsysId, u32 srcFileId, MEMHeapHandle heap, u32 dstFsysId, u32 dstFileId, UnkFunc1 param6);
    void lockCacheEntry(u32 fsysId, u32 fileId);
    void unlockCacheEntry(u32 fsysId, u32 fileId);

    // GScacheScratchpad.cpp
    void fn_801DB81C(u8 param1);
    void fn_801DB92C(u8 start, u8 count, bool param3);
    bool fn_801DB978(u8 param1);
    void fn_801DB9FC();
    void fn_801DBA8C();

    // GScachePool.cpp
    bool fn_801DBB3C();
    void fn_801DBB44(bool param1);
    void initObjectPool(GScacheObjPool *pool, u32 count, u32 objSize);
    void *allocFromPool(GScacheObjPool *pool);
    void freeToPool(GScacheObjPool *pool, void *obj);
    GScacheObjPool *createObjectPool(u32 count, u32 objSize);
}
