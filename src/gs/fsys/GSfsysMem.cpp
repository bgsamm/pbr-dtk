#include "version.hpp"

#include <cstring>
#include <revolution/os.h>

#include "gs/GSfsys.hpp"
#include "gs/GSmem.hpp"

extern void *fn_801DB360(u32, u32, u32, u32, u32);

#define DATA_HEAP_SIZE 0x50000

/* lbl_8063F7C8 */ static MEMHeapHandle sFsysDataHeap;

void *GSfsys::allocFromFsysDataHeap(u32 size) {
    return GSmem::allocFromHeap(sFsysDataHeap, size);
}

bool GSfsys::freeToFsysDataHeap(void *ptr) {
    GSmem::freeHeapBlock(sFsysDataHeap, ptr);
    return true;
}

bool GSfsys::initFsysDataHeap() {
    void *start = OSGetMEM2ArenaLo();
    void *end = (u8 *)start + DATA_HEAP_SIZE;

    sFsysDataHeap = GSmem::createHeap(start, DATA_HEAP_SIZE, MEM_HEAP_OPT_THREAD_SAFE);
    if (sFsysDataHeap == NULL) {
        return false;
    }

    GSmem::setHeapGroupID(sFsysDataHeap, 1);

    OSSetMEM2ArenaLo(end);

    return true;
}

bool GSfsys::initFsysDataBuffer(GSfsysHandle *fsysHandle) {
    if (fsysHandle->mData != NULL) {
        return false;
    }

    fsysHandle->mDataLoaded = false;

    u32 size = (fsysHandle->mTocEntry->mSize + 0x1f) / 0x20 * 0x20;
    fsysHandle->mData = (GSfsysHeaderEx *)GSfsys::allocFromFsysDataHeap(size);
    if (fsysHandle->mData == NULL) {
        return false;
    }

    memset(fsysHandle->mData, 0, sizeof(GSfsysHeaderEx));
    memcpy(fsysHandle->mData->mMagic, "INVA", 4);

    DCFlushRange(fsysHandle->mData, sizeof(GSfsysHeaderEx));

    return true;
}

bool GSfsys::freeFsysDataBuffer(GSfsysHandle *fsysHandle) {
    BOOL intEnabled = OSDisableInterrupts();
    void *buffer = fsysHandle->mData;
    fsysHandle->mDataLoaded = false;
    fsysHandle->mData = NULL;
    OSRestoreInterrupts(intEnabled);

    return GSfsys::freeToFsysDataHeap(buffer);
}

void *GSfsys::getOrCreateCachedBuffer(
    GSfsysHandle *fsysHandle,
    u32 entryIndex,
    u32 size,
    u32 fsysCacheIndex
) {
    GSfsysCacheEntry *cacheEntry = findFsysCacheEntry(fsysHandle->mFsysId, entryIndex);
    if (cacheEntry == NULL) {
        bool persistent = fsysHandle->mPersistent;
        
        GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
        if (fsys != NULL && (fsys->mFlags & FSYS_FLAG_PERSISTENT)) {
            persistent = true;
        }

        cacheEntry = createFsysCacheEntry(
            fsysHandle->mFsysId,
            entryIndex,
            persistent,
            true,
            fsysCacheIndex
        );
        if (cacheEntry == NULL) {
            return NULL;
        }

        cacheEntry->mBufSize = size;
        cacheEntry->mBuffer = allocFromFsysCacheHeap(size);
        if (cacheEntry->mBuffer == NULL) {
            removeFromCacheEntryList(cacheEntry);
            return NULL;
        }
    }
    return cacheEntry->mBuffer;
}

bool GSfsys::releaseFsysCacheEntry(GSfsysCacheEntry *cacheEntry) {
    void *buffer = cacheEntry->mBuffer;
    u32 size = cacheEntry->mBufSize;
    removeFromCacheEntryList(cacheEntry);
    freeToFsysCacheHeap(buffer, size);
    return true;
}

bool GSfsys::releaseFsysCacheEntryByBuffer(void *buffer) {
    GSfsysCacheEntry *cacheEntry = findFsysCacheEntryByBuffer(buffer);
    if (cacheEntry == NULL) {
        return false;
    }

    return releaseFsysCacheEntry(cacheEntry);
}

bool GSfsys::makeSpaceForCachedBuffer(u32 fsysId, u32 size) {
    while(true) {
        // TODO #define the 0x80000
        if (size < getFsysCacheHeapFreeSize() - 0x80000) {
            break;
        }

        GSfsysCacheEntry *victim = selectCacheEvictionVictim(fsysId, false);
        if (victim == NULL) {
            return false;
        }

        if (!releaseFsysCacheEntry(victim)) {
            return false;
        }
    }
    
    return true;
}

bool GSfsys::batchEvictFsysCacheEntries(u32 fsysId) {
    u32 currentFsysCacheIndex;
    bool anyEvicted = false;

    while(true) {
        GSfsysCacheEntry *victim = selectCacheEvictionVictim(fsysId, true);
        if (victim == NULL) {
            return anyEvicted;
        }

        if (anyEvicted != true || currentFsysCacheIndex == victim->mFsysCacheIndex) {
            currentFsysCacheIndex = victim->mFsysCacheIndex;
            anyEvicted = true;
            
            if (!releaseFsysCacheEntry(victim)) {
                return false;
            }
        }
        else {
            return anyEvicted;
        }
    }
}

void *GSfsys::allocCachedBuffer(
    GSfsysHandle *fsysHandle,
    u32 entryIndex,
    u32 length,
    u32 fsysCacheIndex
) {
    u32 size = (length + 0x1f) / 0x20 * 0x20;
    makeSpaceForCachedBuffer(fsysHandle->mFsysId, size);

    void *buffer;
    while (true) {
        buffer = getOrCreateCachedBuffer(fsysHandle, entryIndex, size, fsysCacheIndex);
        if (buffer != NULL) {
            break;
        }

        if (!batchEvictFsysCacheEntries(fsysHandle->mFsysId)) {
            return NULL;
        }
    }

    return buffer;
}

bool GSfsys::freeCachedBuffer(void *buffer) {
    return releaseFsysCacheEntryByBuffer(buffer);
}

bool GSfsys::releaseFirstCacheEntryForFsys(u32 fsysId) {
    GSfsysCacheEntry *cacheEntry = findFirstCacheEntryForFsys(fsysId);
    if (cacheEntry == NULL) {
        return false;
    }

    return releaseFsysCacheEntry(cacheEntry);
}

// TODO name this function once fn_801DB360 understood
void *GSfsys::fn_80244EA8(u32 size, u32 fsysId, u32 fileId) {
    return fn_801DB360(size, 0x20, fsysId, fileId, 0);
}
