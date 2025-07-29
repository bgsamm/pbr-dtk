#include "global.hpp"

#include <revolution/mem.h>
#include <revolution/os.h>

#include "gs/GSfsys.hpp"
#include "gs/GSmem.hpp"

#define CACHE_HEAP_SIZE 0x800000

/* lbl_8063F7F8 */ static u32 sCacheHeapSize; // Unused outside of initialization
/* lbl_8063F7FC */ static u32 sCacheEntryPoolCount;
/* lbl_8063F800 */ static u32 sCacheEntryPoolLastIndex;
/* lbl_8063F804 */ static u32 sCacheFsysCounter;
/* lbl_8063F808 */ static u32 sCacheEntryCounter;
/* lbl_8063F80C */ static u32 sFsysCacheHeapUsedSize;
/* lbl_8063F810 */ static u32 sCacheRequestPoolCount;
/* lbl_8063F814 */ static u32 sCacheRequestPoolLastIndex;
/* lbl_8063F818 */ static GSfsysCacheEntry *sCacheEntryPool;
/* lbl_8063F81C */ static GSfsysCacheEntry *sCacheEntryList;
/* lbl_8063F820 */ static GSfsysCacheRequest *sCacheRequestPool;
/* lbl_8063F824 */ static GSfsysCacheRequest *sCacheRequestList;
/* lbl_8063F828 */ static MEMHeapHandle sFsysCacheHeap;

void GSfsys::addToCacheRequestList(GSfsysCacheRequest *cacheRequest) {
    appendNodeToList((GSfsysNode *)cacheRequest, (GSfsysNode **)&sCacheRequestList);
}

GSfsysCacheRequest *GSfsys::getFreeCacheRequest() {
    BOOL intEnabled;

    GSfsysCacheRequest *cacheRequest = NULL;

    intEnabled = OSDisableInterrupts();

    u32 i = sCacheRequestPoolLastIndex;
    while (cacheRequest == NULL) {
        if (!sCacheRequestPool[i].mInUse) {
            cacheRequest = &sCacheRequestPool[i];
            cacheRequest->mPrev = NULL;
            cacheRequest->mNext = NULL;
            cacheRequest->mInUse = true;
            cacheRequest->mCallback = NULL;
            cacheRequest->mFsysHandle = NULL;
            cacheRequest->mFsysEntry = NULL;
            cacheRequest->mUserCallback = NULL;
            cacheRequest->mUserParam1 = 0;
            cacheRequest->mUserParam2 = 0;
            cacheRequest->mBuffer = NULL;
            cacheRequest->mLength = 0;
        }

        i++;
        if (i >= sCacheRequestPoolCount) {
            i = 0;
        }
        if (i == sCacheRequestPoolLastIndex) {
            break;
        }
    }
    sCacheRequestPoolLastIndex = i;

    addToCacheRequestList(cacheRequest);

    OSRestoreInterrupts(intEnabled);

    return cacheRequest;
}

void GSfsys::removeFromCacheRequestList(GSfsysCacheRequest *cacheRequest) {
    removeNodeFromList((GSfsysNode *)cacheRequest, (GSfsysNode **)&sCacheRequestList);
}

void GSfsys::addToCacheEntryList(GSfsysCacheEntry *cacheEntry) {
    appendNodeToList((GSfsysNode *)cacheEntry, (GSfsysNode **)&sCacheEntryList);
}

GSfsysCacheEntry *GSfsys::createFsysCacheEntry(
    u32 fsysId,
    u32 entryIndex,
    bool persistent,
    bool pinned,
    u32 fsysCacheIndex
) {
    BOOL intEnabled;

    GSfsysCacheEntry *cacheEntry = NULL;

    intEnabled = OSDisableInterrupts();

    u32 i = sCacheEntryPoolLastIndex;
    while (cacheEntry == NULL) {
        if (!sCacheEntryPool[i].mInUse) {
            cacheEntry = &sCacheEntryPool[i];
            cacheEntry->mPrev = NULL;
            cacheEntry->mNext = NULL;
            cacheEntry->mInUse = true;
            cacheEntry->mPersistent = persistent;
            cacheEntry->mPinned = pinned;
            cacheEntry->mFsysId = fsysId;
            cacheEntry->mEntryIndex = entryIndex;
            cacheEntry->mBuffer = NULL;
            cacheEntry->mBufSize = 0;
            cacheEntry->mFsysCacheIndex = fsysCacheIndex;
            cacheEntry->mEntryCacheIndex = sCacheEntryCounter;
            sCacheEntryCounter++;
        }

        i++;
        if (i >= sCacheEntryPoolCount) {
            i = 0;
        }
        
        // NOTE this matches a repeated bne instruction
        if (i != sCacheEntryPoolLastIndex) {
            continue;
        }

        if (i == sCacheEntryPoolLastIndex) {
            return NULL;
        }
    }
    sCacheEntryPoolLastIndex = i;

    addToCacheEntryList(cacheEntry);

    OSRestoreInterrupts(intEnabled);

    return cacheEntry;
}

void GSfsys::removeFromCacheEntryList(GSfsysCacheEntry *cacheEntry) {
    removeNodeFromList((GSfsysNode *)cacheEntry, (GSfsysNode **)&sCacheEntryList);
}

GSfsysCacheEntry *GSfsys::findFsysCacheEntry(u32 fsysId, u32 entryIndex) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysCacheEntry *cacheEntry = sCacheEntryList;
    while (cacheEntry != NULL) {
        if (cacheEntry->mFsysId == fsysId && cacheEntry->mEntryIndex == entryIndex) {
            break;
        }
        cacheEntry = cacheEntry->mNext;
    }

    OSRestoreInterrupts(intEnabled);
    
    return cacheEntry;
}

GSfsysCacheEntry *GSfsys::findFirstCacheEntryForFsys(u32 fsysId) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysCacheEntry *cacheEntry = sCacheEntryList;
    while (cacheEntry != NULL) {
        if (cacheEntry->mFsysId == fsysId) {
            break;
        }
        cacheEntry = cacheEntry->mNext;
    }

    OSRestoreInterrupts(intEnabled);
    
    return cacheEntry;
}

GSfsysCacheEntry *GSfsys::findFsysCacheEntryByBuffer(void *buffer) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysCacheEntry *cacheEntry = sCacheEntryList;
    while (cacheEntry != NULL) {
        if (cacheEntry->mBuffer == buffer) {
            break;
        }
        cacheEntry = cacheEntry->mNext;
    }

    OSRestoreInterrupts(intEnabled);
    
    return cacheEntry;
}

GSfsysCacheEntry *GSfsys::selectCacheEvictionVictim(u32 fsysId, bool ignoreCacheOrder) {
    GSfsysCacheEntry *cacheEntry = sCacheEntryList;
    GSfsysCacheEntry *victim = NULL;

    while (cacheEntry != NULL) {
        if (cacheEntry->mPersistent != true
            && cacheEntry->mPinned != true
            && cacheEntry->mFsysId != fsysId
        ) {
            if (victim == NULL) {
                victim = cacheEntry;
            }
            else if (victim->mFsysCacheIndex >= cacheEntry->mFsysCacheIndex) {
                if (!ignoreCacheOrder) {
                    if (victim->mEntryCacheIndex < cacheEntry->mEntryCacheIndex) {
                        victim = cacheEntry;
                    }
                }
                else {
                    victim = cacheEntry;
                }
            }
        }

        cacheEntry = cacheEntry->mNext;
    }

    return victim;
}

void GSfsys::setFsysCacheEntryPinned(u32 fsysId, u32 entryIndex, bool pinned) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysCacheEntry *cacheEntry = findFsysCacheEntry(fsysId, entryIndex);
    if (cacheEntry != NULL) {
        cacheEntry->mPinned = pinned;
    }

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::setFsysCacheEntriesPinned(u32 fsysId, bool pinned) {
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysCacheEntry *cacheEntry = sCacheEntryList;
    while (cacheEntry != NULL) {
        if (cacheEntry->mFsysId == fsysId) {
            cacheEntry->mPinned = pinned;
        }
        cacheEntry = cacheEntry->mNext;
    }

    OSRestoreInterrupts(intEnabled);
}

bool GSfsys::initFsysCacheHeap() {
    void *start = OSGetMEM2ArenaLo();
    void *end = (u8 *)start + CACHE_HEAP_SIZE;

    sFsysCacheHeap = GSmem::createHeap(start, CACHE_HEAP_SIZE, MEM_HEAP_OPT_THREAD_SAFE);
    if (sFsysCacheHeap == NULL) {
        return false;
    }

    GSmem::setHeapGroupID(sFsysCacheHeap, 2);

    OSSetMEM2ArenaLo(end);

    return true;
}

bool GSfsys::isLessThanEqualToCacheHeapSize(u32 size) {
    return size <= CACHE_HEAP_SIZE;
}

void *GSfsys::allocFromFsysCacheHeap(u32 size) {
    void *ptr;

    BOOL intEnabled = OSDisableInterrupts();

    ptr = GSmem::allocFromHeap(sFsysCacheHeap, size);

    OSRestoreInterrupts(intEnabled);

    if (ptr != NULL) {
        sFsysCacheHeapUsedSize += size;
    }

    return ptr;
}

void GSfsys::freeToFsysCacheHeap(void *ptr, u32 size) {
    BOOL intEnabled = OSDisableInterrupts();

    GSmem::freeToHeap(sFsysCacheHeap, ptr);

    OSRestoreInterrupts(intEnabled);

    sFsysCacheHeapUsedSize -= size;
}

u32 GSfsys::getFsysCacheHeapFreeSize() {
    return CACHE_HEAP_SIZE - sFsysCacheHeapUsedSize;
}

bool GSfsys::initFsysCacheSystem(u32 heapSize, u32 nCacheEntries) {
    sCacheEntryList = NULL;
    sCacheEntryPoolLastIndex = 0;
    sCacheFsysCounter = 0;
    sCacheEntryCounter = 0;
    sFsysCacheHeapUsedSize = 0;
    sCacheRequestList = NULL;
    sCacheRequestPoolLastIndex = 0;

    if (heapSize == 0) {
        heapSize = CACHE_HEAP_SIZE;
    }

    sCacheEntryPoolCount = nCacheEntries;
    sCacheHeapSize = (heapSize + 0x1f) / 0x20 * 0x20;

    if (sCacheEntryPoolCount == 0) {
        sCacheEntryPoolCount = 512;
    }

    sCacheRequestPoolCount = 128;

    if (!isLessThanEqualToCacheHeapSize(sCacheHeapSize)) {
        return false;
    }

    sCacheEntryPool = (GSfsysCacheEntry *)allocAligned32(sCacheEntryPoolCount * sizeof(GSfsysCacheEntry));
    if (sCacheEntryPool == NULL) {
        return false;
    }

    sCacheRequestPool = (GSfsysCacheRequest *)allocAligned32(sCacheRequestPoolCount * sizeof(GSfsysCacheRequest));
    if (sCacheRequestPool == NULL) {
        return false;
    }

    for (u32 i = 0; i < sCacheEntryPoolCount; i++) {
        sCacheEntryPool[i].mInUse = false;
        sCacheEntryPool[i].mPersistent = false;
        sCacheEntryPool[i].mPinned = false;
    }

    for (u32 i = 0; i < sCacheRequestPoolCount; i++) {
        sCacheRequestPool[i].mInUse = false;
    }

    return true;
}

u32 GSfsys::getNextCacheFsysIndex() {
    u32 index = sCacheFsysCounter;
    sCacheFsysCounter++;
    return index;
}

bool GSfsys::isFsysEntryCached(u32 fsysId, u32 entryIndex) {
    return findFsysCacheEntry(fsysId, entryIndex) != NULL;
}

bool GSfsys::doFsysCacheRead(
    GSfsysHandle *fsysHandle,
    GSfsysEntry *fsysEntry,
    void *buffer,
    u32 length,
    u32 offset,
    GSfsysCacheCallback callback,
    GSfsysCallback userCallback,
    u32 userParam1,
    u32 userParam2
) {
    GSfsysCacheEntry *cacheEntry = findFsysCacheEntry(
        fsysHandle->mFsysId,
        fsysHandle->mCacheEntryIndex
    );
    if (cacheEntry == NULL) {
        return false;
    }

    GSfsysCacheRequest *cacheRequest = getFreeCacheRequest();
    if (cacheRequest == NULL) {
        return false;
    }

    cacheRequest->mFsysHandle = fsysHandle;
    cacheRequest->mFsysEntry = fsysEntry;
    cacheRequest->mCallback = callback;
    cacheRequest->mUserCallback = userCallback;
    cacheRequest->mUserParam1 = userParam1;
    cacheRequest->mUserParam2 = userParam2;

    if (offset + length > cacheEntry->mBufSize) {
        length = cacheEntry->mBufSize - offset;
    }

    if ((u32)buffer % 0x20 != 0) {
        return false;
    }

    if (length % 0x20 != 0) {
        return false;
    }

    cacheRequest->mBuffer = buffer;
    cacheRequest->mLength = length;

    GSmem::copyMem(buffer, (u8 *)cacheEntry->mBuffer + offset, length);

    if (cacheRequest->mCallback != NULL) {
        cacheRequest->mCallback(cacheRequest);
    }

    removeFromCacheRequestList(cacheRequest);

    return true;
}

bool GSfsys::fsysCacheRead(
    GSfsysHandle *fsysHandle,
    GSfsysEntry *fsysEntry,
    void *buffer,
    u32 length,
    u32 offset,
    GSfsysCacheCallback callback
) {
    return doFsysCacheRead(
        fsysHandle,
        fsysEntry,
        buffer,
        length,
        offset,
        callback,
        NULL,
        0,
        0
    );
}

bool GSfsys::fsysCacheReadEx(
    GSfsysHandle *fsysHandle,
    GSfsysEntry *fsysEntry,
    void *buffer,
    u32 length,
    u32 offset,
    GSfsysCacheCallback callback,
    GSfsysCallback userCallback,
    u32 userParam1,
    u32 userParam2
) {
    return doFsysCacheRead(
        fsysHandle,
        fsysEntry,
        buffer,
        length,
        offset,
        callback,
        userCallback,
        userParam1,
        userParam2
    );
}

void GSfsys::copyToCachedBuffer(
    GSfsysHandle *fsysHandle,
    GSfsysEntry *fsysEntry,
    void *src,
    void *dst,
    u32 length,
    u32 offset,
    GSfsysCacheCallback callback
) {
    GSfsysCacheRequest *cacheRequest = getFreeCacheRequest();
    if (cacheRequest == NULL) {
        // Debug leftovers?
        if (cacheRequest == NULL) {
            return;
        }
        return;
    }

    cacheRequest->mFsysHandle = fsysHandle;
    cacheRequest->mFsysEntry = fsysEntry;
    cacheRequest->mCallback = callback;

    GSmem::copyMem((u8 *)dst + offset, src, length);

    if (callback != NULL) {
        callback(cacheRequest);
    }

    removeFromCacheRequestList(cacheRequest);
}
