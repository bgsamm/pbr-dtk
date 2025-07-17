#include "version.hpp"

#include <cstdio>
#include <revolution/os.h>

#include "gs/GSfile.hpp"
#include "gs/GSfsys.hpp"

/* lbl_8063F838 */ static u32 sUnknownFlag; // Never gets written to

void GSfsys::seekFsysCallback(s32 result, GSfileHandle *fileHandle) {
    GSfsysHandle *fsysHandle = getAssociatedFsysHandle(fileHandle);
    if (fsysHandle == NULL) {
        return;
    }

    if (result < 0) {
        setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILESEEK);
    }
    else {
        setFsysNextState(fsysHandle, FSYS_STATE_REQUEST_COMPLETE);
    }
}

GSfsysFileTypeHandler *GSfsys::getHandlerForFileType(u32 fileType) {
    for (u32 i = 0; i < gFileTypeHandlerCount; i++) {
        GSfsysFileTypeHandler *handler = &gFileTypeHandlerList[i];
        if (handler->mFileType == fileType) {
            return handler;
        }
    }

    return NULL;
}

bool GSfsys::queueFsysEntryForCopying(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry) {
    BOOL intEnabled = OSDisableInterrupts();
    
    GSfsysEntryHandle *fsysEntryHandle = getFreeFsysEntryHandle();
    if (fsysEntryHandle == NULL) {
        setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_QUEUE_ERROR);
        OSRestoreInterrupts(intEnabled);
        return false;
    }

    setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READY);

    fsysEntryHandle->mInfo = fsysEntry;
    fsysEntryHandle->mFsysHandle = fsysHandle;

    if ((fsysEntry->mFlags & FSYS_ENTRY_FLAG_COMPRESSED)) {
        fsysEntryHandle->mCompressed = true;
    }
    else {
        fsysEntryHandle->mCompressed = false;
    }

    enqueueFsysEntry(fsysEntryHandle);

    OSRestoreInterrupts(intEnabled);

    return true;
}

bool GSfsys::queueNextFsysEntryForCopying(GSfsysHandle *fsysHandle) {
    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if (fsysHandle->mCopyingEntryIndex >= fsys->mFileCount) {
        return false;
    }

    GSfsysEntry *fsysEntry = getFsysEntry(fsysHandle, fsysHandle->mCopyingEntryIndex);
    if (fsysEntry == NULL) {
        return false;
    }

    fsysHandle->mCopyingEntryIndex++;

    return queueFsysEntryForCopying(fsysHandle, fsysEntry);
}

bool GSfsys::findFirstUnchachedFsysEntry(GSfsysHandle *fsysHandle) {
    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);

    u16 i;
    for (i = 0; i < fsys->mFileCount; i++) {
        if (!isFsysEntryCached(fsysHandle->mFsysId, i)) {
            break;
        }
    }

    if (i >= fsys->mFileCount) {
        return false;
    }

    fsysHandle->mReadingEntryIndex = i;

    return true;
}

GSfsysHeaderEx *GSfsys::getFsysData(GSfsysHandle *fsysHandle) {
    if (fsysHandle->mData == NULL) {
        return NULL;
    }

    // Does not match with !
    if (fsysHandle->mDataLoaded == false) {
        return NULL;
    }

    return fsysHandle->mData;
}

GSfsysEntry *GSfsys::getFsysEntry(GSfsysHandle *fsysHandle, u32 index) {
    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if (fsys == NULL) {
        return NULL;
    }

    if (index >= fsys->mFileCount) {
        return NULL;
    }

    u32 *fileOffsets = (u32 *)((u8 *)fsys + fsys->mFsysEntryTableOffset);
    return (GSfsysEntry *)((u8 *)fsys + fileOffsets[index]);
}

void GSfsys::handleFsysChunkReady(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry) {
    fsysEntry->mReadPosition += gFsysChunkSize;

    if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM
        && !(fsysEntry->mFlags & FSYS_ENTRY_FLAG_18)
    ) {
        u32 bufSize = getStreamBufferSize();

        fsysEntry->mRingBufFill += gFsysChunkSize;
        fsysEntry->mValidChunks |= getStreamChunkFlag(fsysEntry->mRingBufPos);
        fsysEntry->mRingBufPos += gFsysChunkSize;
        if (fsysEntry->mRingBufPos >= bufSize) {
            fsysEntry->mRingBufPos = 0;
        }

        if (fsysHandle->mCancelRequested) {
            fsysHandle->setNextState(FSYS_STATE_READ_COMPLETE);
            return;
        }

        if (fsysEntry->mReadPosition >= fsysEntry->mLoopEnd) {
            if ((fsysEntry->mFlags & FSYS_ENTRY_FLAG_11)) {
                setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_STANDBY);
                return;
            }

            if (fsysEntry->mReadPosition < bufSize) {
                fsysEntry->mFlags |= FSYS_ENTRY_FLAG_23;
                setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_STANDBY);
                fsysEntry->mValidChunks = 0xffffffff;
                return;
            }

            fsysEntry->mReadPosition = fsysEntry->mLoopStart;
        }

        if (fsysEntry->mRingBufFill >= bufSize) {
            setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_YIELD);
            return;
        }

        if (countActiveRequestsOfType(FSYS_REQUEST_LOAD) + countActiveRequestsOfType(FSYS_REQUEST_CACHE) != 0) {
            setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_YIELD);
            return;
        }
    }
    else if (fsysEntry->mReadPosition >= fsysEntry->mPackedSize) {
        GSfileHandle *fileHandle = fsysEntry->mFileHandle;
        if (fileHandle != NULL) {
            fsysEntry->mFileHandle = NULL;
            GSfile::closeFile(fileHandle);
        }

        if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM && fsysHandle->_34 != 0) {
            fsysHandle->mReadingEntryIndex = getFsysEntryIndex(fsysHandle, fsysHandle->_34);
        }
        else {
            if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff) {
                if (fsysHandle->mFileIdQueue != NULL && *fsysHandle->mFileIdQueue != 0) {
                    fsysHandle->mNextFileId = *fsysHandle->mFileIdQueue;
                    fsysHandle->mFileIdQueue++;

                    u32 nextIndex = fsysHandle->getEntryIndex(fsysHandle->mNextFileId);
                    fsysHandle->mReadingEntryIndex = nextIndex;
                    fsysHandle->mCopyingEntryIndex = nextIndex;

                    beginReadNextFsysEntry(fsysHandle);
                    return;
                }

                fsysHandle->mFileIdQueue = NULL;
                fsysHandle->setNextState(FSYS_STATE_READ_COMPLETE);
                return;
            }
            
            fsysHandle->mReadingEntryIndex++;
        }

        GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
        if (fsysHandle->mReadingEntryIndex >= fsys->mFileCount) {
            fsysHandle->setNextState(FSYS_STATE_READ_COMPLETE);
            return;
        }

        beginReadNextFsysEntry(fsysHandle);
        return;
    }
    
    readNextFsysEntryChunk(fsysHandle, fsysEntry);
}

void GSfsys::finalizeFsysChunk(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry) {
    if (!fsysHandle->mCancelRequested
        && (fsysHandle->mRequestType == FSYS_REQUEST_LOAD
            || (fsysHandle->mRequestType == FSYS_REQUEST_STREAM
                && (fsysEntry->mFlags & FSYS_ENTRY_FLAG_18)))
    ) {
        transferChunkListTail(&fsysEntry->mPendingChunks, &fsysEntry->mCompletedChunks);
    }
    else {
        popChunkFromList(&fsysEntry->mPendingChunks, false);
    }
}

void GSfsys::fsysChunkCopyCallback(GSfsysCacheRequest *cacheRequest) {
    if (cacheRequest == NULL) {
        return;
    }

    finalizeFsysChunk(cacheRequest->mFsysHandle, cacheRequest->mFsysEntry);
}

u32 GSfsys::getChunkSize(u32 totalSize, u32 currentPos) {
    u32 chunkSize = totalSize - currentPos;

    if (chunkSize > gFsysChunkSize) {
        chunkSize = gFsysChunkSize;
    }

    return (chunkSize + 0x1f) / 0x20 * 0x20;
}

void GSfsys::directFsysEntryReadCallback(s32 result, GSfileHandle *fileHandle) {
    u32 offset;

    GSfsysHandle *fsysHandle = getAssociatedFsysHandle(fileHandle);
    if (fsysHandle == NULL) {
        return;
    }

    if (result < 0) {
        setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
        return;
    }

    GSfsysEntry *fsysEntry = getFsysEntry(fsysHandle, fsysHandle->mReadingEntryIndex);
    if (fsysEntry == NULL) {
        return;
    }

    if (!(fsysEntry->mFlags & FSYS_ENTRY_FLAG_BUFFER_ALLOCATED)) {
        if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM) {
            if ((fsysEntry->mFlags & FSYS_ENTRY_FLAG_18)) {
                fsysEntry->mCachedBuffer = NULL;
            }
            else {
                fsysEntry->mCachedBuffer = allocCachedBuffer(
                    fsysHandle,
                    fsysHandle->mReadingEntryIndex,
                    getStreamBufferSize(),
                    fsysHandle->mCacheIndex
                );
            }
        }
        else {
            fsysEntry->mCachedBuffer = allocCachedBuffer(
                fsysHandle,
                fsysHandle->mReadingEntryIndex,
                fsysEntry->mPackedSize,
                fsysHandle->mCacheIndex
            );
        }
        fsysEntry->mFlags |= FSYS_ENTRY_FLAG_BUFFER_ALLOCATED;
    }

    if (fsysEntry->mCachedBuffer != NULL) {
        if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM) {
            offset = fsysEntry->mRingBufPos;
        }
        else {
            offset = fsysEntry->mReadPosition;
        }

        copyToCachedBuffer(
            fsysHandle,
            fsysEntry,
            fsysEntry->mPendingChunks->mBuffer,
            fsysEntry->mCachedBuffer,
            getChunkSize(fsysEntry->mPackedSize, fsysEntry->mReadPosition),
            offset,
            fsysChunkCopyCallback
        );
    }
    else {
        finalizeFsysChunk(fsysHandle, fsysEntry);
    }

    handleFsysChunkReady(fsysHandle, fsysEntry);
}

void GSfsys::cachedFsysEntryReadCallback(GSfsysCacheRequest *cacheRequest) {
    if (cacheRequest == NULL) {
        return;
    }
    
    GSfsysHandle *fsysHandle = cacheRequest->mFsysHandle;
    GSfsysEntry *fsysEntry = cacheRequest->mFsysEntry;

    finalizeFsysChunk(fsysHandle, fsysEntry);
    handleFsysChunkReady(fsysHandle, fsysEntry);
}

bool GSfsys::readNextFsysEntryChunk(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry) {
    BOOL intEnabled = OSDisableInterrupts();

    if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM
        && !(fsysEntry->mFlags & FSYS_ENTRY_FLAG_19)
    ) {
        GSfsysFileTypeHandler *handler = getHandlerForFileType(fsysEntry->mFileType);
        if (!(handler->mFlags & (1 << 0)) || (handler->mFlags & (1 << 1))) {
            GSfsysEntry *thpEntry;
            if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff) {
                u32 index = getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId);
                thpEntry = getFsysEntry(fsysHandle, index);
            }
            else {
                thpEntry = getFsysEntry(fsysHandle, 0);
            }

            if (thpEntry == NULL) {
                setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READ_ERROR);
                OSRestoreInterrupts(intEnabled);
                return false;
            }

            if (!(thpEntry->mFlags & FSYS_ENTRY_FLAG_FINISHED)) {
                setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READ_ERROR);
                OSRestoreInterrupts(intEnabled);
                return false;
            }

            if (handler->_8 != NULL) {
                handler->_8(fsysHandle->mFsysId, fsysEntry->mFileId, fsysEntry->mPackedSize);
            }

            fsysEntry->mFlags |= FSYS_ENTRY_FLAG_19;
        }
    }

    GSfsysChunk *chunk = getFreeFsysChunk();
    if (chunk == NULL) {
        setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READ_ERROR);
        OSRestoreInterrupts(intEnabled);
        return false;
    }

    setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READY);

    chunk->mOffset = fsysEntry->mReadPosition;
    prependToChunkList(&fsysEntry->mPendingChunks, chunk);

    bool cached = (fsysEntry->mFlags & FSYS_ENTRY_FLAG_CACHED);

    bool success = readFsys(
        fsysHandle,
        fsysEntry,
        cached,
        fsysHandle->mReadingEntryIndex,
        fsysEntry->mPendingChunks->mBuffer,
        getChunkSize(fsysEntry->mPackedSize, fsysEntry->mReadPosition),
        fsysEntry->mReadPosition,
        directFsysEntryReadCallback,
        cachedFsysEntryReadCallback
    );

    OSRestoreInterrupts(intEnabled);

    return success;
}

bool GSfsys::beginReadNextFsysEntry(GSfsysHandle *fsysHandle) {
    if (fsysHandle->mCancelRequested == true) {
        setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
        return false;
    }

    GSfsysEntry *fsysEntry = getFsysEntry(fsysHandle, fsysHandle->mReadingEntryIndex);
    if (fsysEntry == NULL) {
        return false;
    }

    char *fname = (char *)((u8 *)fsysHandle->mData + fsysEntry->mDebugNameOffset);

    fsysEntry->mReadPosition = 0;
    fsysEntry->mCachedBuffer = NULL;
    fsysEntry->mPendingChunks = NULL;
    fsysEntry->mCompletedChunks = NULL;
    fsysEntry->mFileHandle = NULL;
    fsysEntry->mState = FSYS_ENTRY_STATE_BEGIN;
    fsysEntry->mNextState = FSYS_ENTRY_STATE_NULL;
    fsysEntry->mFlags = (fsysEntry->mFlags & 0xff70fff7) | FSYS_ENTRY_FLAG_11;
    fsysEntry->mRingBufFill = 0;
    fsysEntry->mValidChunks = 0;
    fsysEntry->mRingBufPos = 0;
    fsysEntry->mLoopStart = 0;
    fsysEntry->mLoopEnd = fsysEntry->mPackedSize;

    if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM) {
        GSfsysFileTypeHandler *handler = getHandlerForFileType(fsysEntry->mFileType);
        if ((handler->mFlags & (1 << 0)) && !(handler->mFlags & (1 << 1))) {
            fsysEntry->mFlags |= FSYS_ENTRY_FLAG_18;
        }
    }

    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if ((fsys->mFlags & FSYS_FLAG_DEBUG)) {
        char buf[128];
        sprintf(buf, "debug/%s", fname);

        if (GSfile::fileExists(buf) == true) {
            fsysEntry->mFileHandle = GSfile::openFile(buf);
            fsysEntry->mFlags &= ~FSYS_ENTRY_FLAG_COMPRESSED;

            u32 length = GSfile::getFileLength(fsysEntry->mFileHandle);
            fsysEntry->mPackedSize = length;
            fsysEntry->mUnpackedSize = length;
        }
    }

    if (fsysHandle->mRequestType != FSYS_REQUEST_STREAM) {
        if (isFsysEntryCached(fsysHandle->mFsysId, fsysHandle->mReadingEntryIndex) == true) {
            fsysEntry->mFlags |= FSYS_ENTRY_FLAG_CACHED;
            setFsysCacheEntryPinned(
                fsysHandle->mFsysId,
                fsysHandle->mReadingEntryIndex,
                true
            );
        }
    }

    if (fsysHandle->mRequestType == FSYS_REQUEST_LOAD
        || (fsysHandle->mRequestType == FSYS_REQUEST_STREAM
            && (fsysEntry->mFlags & FSYS_ENTRY_FLAG_18))
    ) {
        if (!queueNextFsysEntryForCopying(fsysHandle)) {
            return false;
        }
    }

    return readNextFsysEntryChunk(fsysHandle, fsysEntry);
}

void GSfsys::handleFsysDataReady(GSfsysHandle *fsysHandle) {
    BOOL intEnabled = OSDisableInterrupts();

    fsysHandle->mDataLoaded = true;

    switch (fsysHandle->mRequestType) {
        case FSYS_REQUEST_LOAD:
        case FSYS_REQUEST_STREAM:
            if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff) {
                u32 *nextId = fsysHandle->mFileIdQueue;
                if (nextId != NULL) {
                    if (*nextId != 0) {
                        fsysHandle->mNextFileId = *nextId;
                        fsysHandle->mFileIdQueue++;
                    }
                    else {
                        fsysHandle->mFileIdQueue = NULL;
                        setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
                        break;
                    }
                }

                u32 index = fsysHandle->getEntryIndex(fsysHandle->mNextFileId);
                fsysHandle->mReadingEntryIndex = index;
                fsysHandle->mCopyingEntryIndex = index;
            }
            beginReadNextFsysEntry(fsysHandle);
            break;

        case FSYS_REQUEST_CACHE:
            if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff) {
                u32 index;
                
                index = getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId);
                if (isFsysEntryCached(fsysHandle->mFsysId, index) == true) {
                    setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
                    break;
                }

                index = getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId);
                fsysHandle->mReadingEntryIndex = index;
                fsysHandle->mCopyingEntryIndex = index;

                beginReadNextFsysEntry(fsysHandle);
                break;
            }
            
            if (findFirstUnchachedFsysEntry(fsysHandle) == true) {
                beginReadNextFsysEntry(fsysHandle);
                break;
            }

            setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
            break;
    }

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::directFsysReadCallback(s32 result, GSfileHandle *fileHandle) {
    GSfsysHandle *fsysHandle = getAssociatedFsysHandle(fileHandle);
    if (fsysHandle == NULL) {
        return;
    }

    if (result < 0) {
        setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
        return;
    }

    void *cachedBuffer = allocCachedBuffer(
        fsysHandle,
        0xffff,
        fsysHandle->mTocEntry->mSize,
        fsysHandle->mCacheIndex
    );

    if (cachedBuffer != NULL) {
        copyToCachedBuffer(
            fsysHandle,
            NULL,
            fsysHandle->mData,
            cachedBuffer,
            fsysHandle->mTocEntry->mSize,
            0,
            NULL
        );
    }

    handleFsysDataReady(fsysHandle);
}

void GSfsys::cachedFsysReadCallback(GSfsysCacheRequest *cacheRequest) {
    if (cacheRequest == NULL) {
        return;
    }
    handleFsysDataReady(cacheRequest->mFsysHandle);
}

bool GSfsys::readFsys(
    GSfsysHandle *fsysHandle,
    GSfsysEntry *fsysEntry,
    bool cached,
    u32 entryIndex,
    void *buffer,
    u32 length,
    u32 offset,
    GSdvdCallback directReadCallback,
    GSfsysCacheCallback cachedReadCallback
) {
    BOOL intEnabled;

    fsysHandle->mCacheEntryIndex = entryIndex;

    if (cached == true) {
        if (!sUnknownFlag) {
            // Was this supposed to disable interrupts?
            intEnabled = OSEnableInterrupts();
        }

        bool success = fsysCacheRead(
            fsysHandle,
            fsysEntry,
            buffer,
            length,
            offset,
            cachedReadCallback
        );

        if (!success) {
            setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
            if (!sUnknownFlag) {
                OSRestoreInterrupts(intEnabled);
            }
            return false;
        }

        if (!sUnknownFlag) {
            OSRestoreInterrupts(intEnabled);
        }
    }
    else {
        bool success;

        if (fsysEntry != NULL && fsysEntry->mFileHandle != NULL) {
            success = GSfile::readFileAsync(
                fsysEntry->mFileHandle,
                buffer,
                length,
                offset,
                directReadCallback
            );

            if (!success) {
                setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
                return false;
            }
        }
        else {
            if (fsysEntry != NULL) {
                offset += fsysEntry->mDataOffset;
            }

            success = GSfile::readFileAsync(
                fsysHandle->mFileHandle,
                buffer,
                length,
                offset,
                directReadCallback
            );

            if (!success) {
                setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
                return false;
            }
        }
    }

    return true;
}

void GSfsys::readFsysData(GSfsysHandle *fsysHandle) {
    BOOL intEnabled;

    if (fsysHandle->mData != NULL && fsysHandle->mDataLoaded == true) {
        handleFsysDataReady(fsysHandle);
        return;
    }

    GSfsysHandle *victim;
    while (true) {
        if (initFsysDataBuffer(fsysHandle) == true) {
            break;
        }

        intEnabled = OSDisableInterrupts();

        // freeFsysDataBuffer gets called on the handle before it is returned
        victim = getOrStealFsysHandle();
        if (victim == NULL) {
            OSRestoreInterrupts(intEnabled);
            // Debug leftovers?
            if (victim == NULL) {
                return;
            }
            setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILEREAD);
            return;
        }
        victim->mState = FSYS_STATE_FREE;

        OSRestoreInterrupts(intEnabled);
    }

    intEnabled = OSDisableInterrupts();

    bool cached = false;
    if (isFsysEntryCached(fsysHandle->mFsysId, 0xffff) == true) {
        setFsysCacheEntryPinned(fsysHandle->mFsysId, 0xffff, true);
        cached = true;
    }

    OSRestoreInterrupts(intEnabled);

    readFsys(
        fsysHandle,
        NULL,
        cached,
        0xffff,
        fsysHandle->mData,
        fsysHandle->mTocEntry->mSize,
        0,
        directFsysReadCallback,
        cachedFsysReadCallback
    );
}

void GSfsys::seekFsysToStart(GSfsysHandle *fsysHandle) {
    bool success = GSfile::seekAsync(fsysHandle->mFileHandle, 0, seekFsysCallback);

    if (!success) {
        setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILESEEK);
    }
}
