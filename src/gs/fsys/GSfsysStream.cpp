#include "version.hpp"

#include <revolution/os.h>

#include "gs/GSfsys.hpp"

u32 GSfsys::getStreamBufferSize() {
    return gFsysChunkSize * 8;
}

u32 GSfsys::getHalfStreamBufferSize() {
    return gFsysChunkSize * 4;
}

u32 GSfsys::getStreamChunkSize() {
    return gFsysChunkSize;
}

void GSfsys::freeStreamedFsysBuffers(GSfsysHandle *fsysHandle) {
    if (fsysHandle == NULL) {
        return;
    }

    if (fsysHandle->mRequestType != FSYS_REQUEST_STREAM) {
        return;
    }
    
    BOOL intEnabled = OSDisableInterrupts();

    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if (fsys != NULL) {
        GSfsysEntry *fsysEntry;
        for (u32 i = 0; i < fsys->mFileCount; i++) {
            fsysEntry = getFsysEntry(fsysHandle, i);
            if (fsysEntry != NULL && fsysEntry->mCachedBuffer != NULL) {
                freeCachedBuffer(fsysEntry->mCachedBuffer);
                fsysEntry->mCachedBuffer = NULL;
            }
        }
    }

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::streamedFsysReadCallback(GSfsysCacheRequest *cacheRequest) {
    if (cacheRequest == NULL) {
        // Debug stuff? Inlining?
        if (cacheRequest == NULL) {
            return;
        }
        return;
    }

    GSfsysHandle *fsysHandle = cacheRequest->mFsysHandle;

    cacheRequest->mFsysEntry->mFlags |= FSYS_ENTRY_FLAG_27;

    if (cacheRequest->mUserCallback != NULL) {
        cacheRequest->mUserCallback(
            fsysHandle->mRequestType,
            cacheRequest->mUserParam1,
            cacheRequest->mUserParam2
        );
    }

    cacheRequest->mUserCallback = NULL;
}

bool GSfsys::readFsysEntryStream(
    GSfsysHandle *fsysHandle,
    u32 fileId,
    void *buffer,
    u32 length,
    u32 offset,
    GSfsysCallback userCallback,
    u32 userParam1,
    u32 userParam2
) {
    u32 readLen;

    BOOL intEnabled = OSDisableInterrupts();

    GSfsysEntry *fsysEntry;
    if (fileId == 0) {
        fsysEntry = getFsysEntry(fsysHandle, 1);
    }
    else {
        u32 index = getFsysEntryIndex(fsysHandle, fileId);
        fsysEntry = getFsysEntry(fsysHandle, index);
    }

    if (fsysEntry != NULL) {
        u32 toRead = length;
        u32 readChunks = 0;

        offset = offset % getStreamBufferSize();
        
        u8 *writeHead = (u8 *)buffer;
        while (toRead != 0) {
            readLen = toRead;
            if (readLen >= gFsysChunkSize) {
                readLen = gFsysChunkSize;
            }
            toRead -= readLen;

            u32 chunkFlag = getStreamChunkFlag(offset);

            if (!(fsysEntry->mValidChunks & chunkFlag)) {
                // This leaves interrupts disabled!
                return false;
            }

            fsysEntry->mFlags &= ~FSYS_ENTRY_FLAG_27;

            if (toRead != 0) {
                bool success = fsysCacheReadEx(
                    fsysHandle,
                    fsysEntry,
                    writeHead,
                    readLen,
                    offset,
                    NULL,
                    0,
                    0,
                    0
                );
                if (!success) {
                    // This leaves interrupts disabled!
                    return false;
                }
            }
            else {
                bool success = fsysCacheReadEx(
                    fsysHandle,
                    fsysEntry,
                    writeHead,
                    readLen,
                    offset,
                    streamedFsysReadCallback,
                    userCallback,
                    userParam1,
                    userParam2
                );
                if (!success) {
                    // This leaves interrupts disabled!
                    return false;
                }
            }

            writeHead += readLen;
            readChunks |= chunkFlag;
            offset += readLen;

            offset = offset % getStreamBufferSize();
        }

        if ((fsysEntry->mFlags & FSYS_ENTRY_FLAG_23)) {
            fsysEntry->mRingBufFill = fsysEntry->mPackedSize;
        }
        else {
            fsysEntry->mRingBufFill -= length;
            fsysEntry->mValidChunks &= ~readChunks;
        }

        OSRestoreInterrupts(intEnabled);
        return true;
    }

    OSRestoreInterrupts(intEnabled);

    fillAndFlushBuffer(buffer, 0, length);

    return false;
}

u32 GSfsys::getStreamChunkFlag(u32 offset) {
    return 1 << (offset / gFsysChunkSize);
}
