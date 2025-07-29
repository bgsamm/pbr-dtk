#include "global.hpp"

#include <cstring>

#include "gs/GScache.hpp"
#include "gs/GSmem.hpp"

/* lbl_8063F2E8 */ static GScacheEntry *sFileCacheList;
/* lbl_8063F2EC */ static GScacheObjPool *sFilePool;

GScacheEntry *GScache::findCacheEntry(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = sFileCacheList;

    while (cacheEntry != NULL) {
        if (cacheEntry->mFsysId == fsysId && cacheEntry->mFileId == fileId) {
            return cacheEntry;
        }
        cacheEntry = cacheEntry->mNext;
    }

    return NULL;
}

GScacheEntry *GScache::releaseCacheEntry(
    GScacheEntry *cacheEntry,
    bool removeFromList
) {
    if (cacheEntry->_18 != NULL
        && !cacheEntry->_18(cacheEntry->mBuffer, cacheEntry->mFsysId, cacheEntry->mFileId)
    ) {
        return cacheEntry->mNext;
    }

    if (cacheEntry->mOwnsBuffer) {
        if (cacheEntry->mBuffer != NULL) {
            GSmem::freeToHeap(cacheEntry->mHeap, cacheEntry->mBuffer);
            cacheEntry->mBuffer = NULL;
        }
        cacheEntry->mOwnsBuffer = false;
    }

    cacheEntry->mBuffer = NULL;

    GScacheEntry *next = cacheEntry->mNext;

    if (removeFromList) {
        if (cacheEntry->mPrev != NULL) {
            cacheEntry->mPrev->mNext = next;
        }
        else {
            sFileCacheList = next;
        }

        if (next != NULL) {
            next->mPrev = cacheEntry->mPrev;
        }

        freeToPool(sFilePool, cacheEntry);
    }

    return next;
}

void GScache::initFileCache(u32 nEntries) {
    sFilePool = createObjectPool(nEntries, sizeof(GScacheEntry));
}

void *GScache::createCacheEntryOnHeap(
    MEMHeapHandle heap,
    u32 size,
    u32 fsysId,
    u32 fileId,
    UnkFunc1 param5
) {
    if (findCacheEntry(fsysId, fileId) != NULL) {
        return NULL;
    }

    GScacheEntry *cacheEntry = (GScacheEntry *)allocFromPool(sFilePool);
    if (cacheEntry == NULL) {
        return NULL;
    }

    cacheEntry->mBuffer = GSmem::allocFromHeap(heap, size);
    if (cacheEntry->mBuffer == NULL) {
        freeToPool(sFilePool, cacheEntry);
        return NULL;
    }

    if (sFileCacheList != NULL) {
        sFileCacheList->mPrev = cacheEntry;
    }

    cacheEntry->mNext = sFileCacheList;
    cacheEntry->mPrev = NULL;
    sFileCacheList = cacheEntry;

    cacheEntry->mOwnsBuffer = true;
    cacheEntry->mHeap = heap;
    cacheEntry->mLocked = false;
    cacheEntry->mFsysId = fsysId;
    cacheEntry->mFileId = fileId;
    cacheEntry->_18 = param5;
    cacheEntry->mRefCount = 0;

    return cacheEntry->mBuffer;
}

void *GScache::createCacheEntryOnHeapAligned(
    MEMHeapHandle heap,
    u32 size,
    u32 align,
    u32 fsysId,
    u32 fileId,
    UnkFunc1 param6
) {
    if (findCacheEntry(fsysId, fileId) != NULL) {
        return NULL;
    }

    GScacheEntry *cacheEntry = (GScacheEntry *)allocFromPool(sFilePool);
    if (cacheEntry == NULL) {
        return NULL;
    }

    cacheEntry->mBuffer = GSmem::allocFromHeapAligned(heap, size, align);
    if (cacheEntry->mBuffer == NULL) {
        freeToPool(sFilePool, cacheEntry);
        return NULL;
    }

    if (sFileCacheList != NULL) {
        sFileCacheList->mPrev = cacheEntry;
    }

    cacheEntry->mNext = sFileCacheList;
    cacheEntry->mPrev = NULL;
    sFileCacheList = cacheEntry;

    cacheEntry->mOwnsBuffer = true;
    cacheEntry->mHeap = heap;
    cacheEntry->mLocked = false;
    cacheEntry->mFsysId = fsysId;
    cacheEntry->mFileId = fileId;
    cacheEntry->_18 = param6;

    return cacheEntry->mBuffer;
}

void *GScache::createCacheEntryAligned(
    u32 size,
    u32 align,
    u32 fsysId,
    u32 fileId,
    UnkFunc1 param5
) {
    return createCacheEntryOnHeapAligned(
        GSmem::getDefaultHeap(),
        size,
        align,
        fsysId,
        fileId,
        param5
    );
}

void GScache::setCacheEntryBuffer(
    void *buffer,
    u32 fsysId,
    u32 fileId,
    UnkFunc1 param4
) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);

    if (buffer == NULL) {
        if (cacheEntry == NULL) {
            return;
        }
        releaseCacheEntry(cacheEntry, true);
        return;
    }

    if (cacheEntry != NULL) {
        if (cacheEntry->mOwnsBuffer) {
            return;
        }
        if (cacheEntry->mBuffer != buffer) {
            if (cacheEntry->_18 != NULL) {
                cacheEntry->_18(cacheEntry->mBuffer, fsysId, fileId);
            }
            cacheEntry->mBuffer = buffer;
        }
        cacheEntry->_18 = param4;
    }
    else {
        cacheEntry = (GScacheEntry *)allocFromPool(sFilePool);
        if (cacheEntry == NULL) {
            return;
        }

        if (sFileCacheList != NULL) {
            sFileCacheList->mPrev = cacheEntry;
        }

        cacheEntry->mNext = sFileCacheList;
        cacheEntry->mPrev = NULL;
        sFileCacheList = cacheEntry;

        cacheEntry->mOwnsBuffer = false;
        cacheEntry->mLocked = false;
        cacheEntry->mBuffer = buffer;
        cacheEntry->mFsysId = fsysId;
        cacheEntry->mFileId = fileId;
        cacheEntry->_18 = param4;
    }
}

void *GScache::getCacheEntryBuffer(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);

    if (cacheEntry == NULL || cacheEntry->mLocked) {
        return NULL;
    }

    return cacheEntry->mBuffer;
}

u32 GScache::incrementRefCount(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);

    if (cacheEntry == NULL || cacheEntry->mLocked) {
        return 0;
    }

    cacheEntry->mRefCount++;

    return cacheEntry->mRefCount;
}

u32 GScache::decrementRefCount(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);

    if (cacheEntry == NULL || cacheEntry->mLocked) {
        return 0;
    }

    if (cacheEntry->mRefCount == 0) {
        freeFileCacheEntry(fsysId, fileId);
        return 0;
    }

    cacheEntry->mRefCount--;

    if (cacheEntry->mRefCount == 0) {
        freeFileCacheEntry(fsysId, fileId);
    }

    return cacheEntry->mRefCount;
}

u32 GScache::getCacheEntryBufferSize(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);
    if (cacheEntry == NULL) {
        return 0;
    }

    if (cacheEntry->mBuffer == NULL) {
        return 0;
    }

    // NOTE does not match with !
    if (cacheEntry->mOwnsBuffer == false) {
        return 0;
    }

    return GSmem::getAllocatedSize(cacheEntry->mBuffer);
}

void GScache::freeFileCacheEntry(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);
    if (cacheEntry == NULL) {
        return;
    }

    releaseCacheEntry(cacheEntry, true);
}

void GScache::freeFsysCacheEntries(u32 fsysId) {
    GScacheEntry *cacheEntry = sFileCacheList;
    while (cacheEntry != NULL) {
        if (cacheEntry->mFsysId == fsysId) {
            cacheEntry = releaseCacheEntry(cacheEntry, true);
        }
        else {
            cacheEntry = cacheEntry->mNext;
        }
    }
}

bool GScache::copyCacheEntry(
    u32 srcFsysId,
    u32 srcFileId,
    MEMHeapHandle heap,
    u32 dstFsysId,
    u32 dstFileId,
    UnkFunc1 param6
) {
    GScacheEntry *cacheEntry = findCacheEntry(srcFsysId, srcFileId);

    if (cacheEntry == NULL
        || cacheEntry->mLocked
        || cacheEntry->mBuffer == NULL
        || !cacheEntry->mOwnsBuffer
    ) {
        return false;
    }

    u32 size = GSmem::getAllocatedSize(cacheEntry->mBuffer);
    if (size == 0) {
        return false;
    }

    void *dst = createCacheEntryOnHeap(heap, size, dstFsysId, dstFileId, param6);
    if (dst == NULL) {
        return false;
    }

    memcpy(dst, cacheEntry->mBuffer, size);

    return true;
}

void GScache::lockCacheEntry(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);
    if (cacheEntry == NULL) {
        return;
    }

    cacheEntry->mLocked = true;
}

void GScache::unlockCacheEntry(u32 fsysId, u32 fileId) {
    GScacheEntry *cacheEntry = findCacheEntry(fsysId, fileId);
    if (cacheEntry == NULL) {
        return;
    }

    cacheEntry->mLocked = false;
}
