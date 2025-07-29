#include "global.hpp"

#include <cstdio>
#include <cstring>
#include <revolution/os.h>

#include "gs/GSfile.hpp"
#include "gs/GSfsys.hpp"
#include "gs/GStask.hpp"
#include "gs/GSthread.hpp"

extern void *fn_8025999C(u32, u32);
extern void fn_802599D0(u32, u32);

#define LZSS_RING_BUF_LEN 4096
#define FSYS_REQUEST_PRIORITY_LEVELS 3

/* lbl_80497FA0 */ static GSfsysRequest *sFsysRequestQueues[8]; // length seems to be 8, even though only 3 used
/* lbl_80497FC0 */ static GSfsysHeader sFsysHeaderBuffer;

/* lbl_8063F856 */ static bool sInitialized;
/* lbl_8063F858 */ static u32 sFsysHandlePoolCount;
/* lbl_8063F85C */ static u32 sFsysHandlePoolLastIndex;
/* lbl_8063F860 */ static u32 sFsysEntryHandlePoolCount;
/* lbl_8063F864 */ static u32 sFsysEntryHandlePoolLastIndex;
/* lbl_8063F868 */ static u32 sLoadRequestPoolCount;
/* lbl_8063F86C */ static GStocHeader *sToc; // toc = table of contents
/* lbl_8063F870 */ static GSfsysHandle *sFsysHandlePool;
/* lbl_8063F874 */ static GSfsysEntryHandle *sFsysEntryHandlePool;
/* lbl_8063F878 */ static GSfsysEntryHandle *sFsysEntryList;
/* lbl_8063F87C */ static GSfsysRequest *sFsysRequestPool;
/* lbl_8063F880 */ static GSfsysRequest *sActiveFsysRequest;
/* lbl_8063F884 */ static u32 sForegroundTaskID;
/* lbl_8063F888 */ static u32 sBackgroundTaskID;
/* lbl_8063F88C */ static GSfsysHeader *sCurrentFsysHeader;
/* lbl_8063F890 */ GSfsysFileTypeHandler *GSfsys::gFileTypeHandlerList;
/* lbl_8063F894 */ u32 GSfsys::gFileTypeHandlerCount;

static inline GStocEntry *getTocTableStart() {
    return (GStocEntry *)((u8 *)sToc + sToc->mTableOffset);
}

void *GSfsys::allocAligned32(u32 size) {
    return GSmem::allocAligned(size, 0x20);
}

bool GSfsys::loadToc() {
    u32 length;

    GSfileHandle *tocHandle = GSfile::openFile("gsfsys.toc");
    if (tocHandle == NULL) {
        return false;
    }

    length = (GSfile::getFileLength(tocHandle) + 0x1f) / 0x20 * 0x20;
    sToc = (GStocHeader *)allocAligned32(length);
    if (sToc == NULL) {
        return false;
    }

    s32 nRead = GSfile::readFile(tocHandle, sToc, length, 0);
    if (nRead < 0) {
        GSfile::closeFile(tocHandle);
        return false;
    }

    GSfile::closeFile(tocHandle);

    GStocEntry *tocEntry = getTocTableStart();
    for (u32 i = 0; i < sToc->mCount; i++, tocEntry++) {
        tocEntry->mName = (char *)((u8 *)sToc + (u32)tocEntry->mName);
        tocEntry->mFlags = 0;
    }

    return true;
}

GSfsysHandle *GSfsys::getAssociatedFsysHandle(GSfileHandle *fileHandle) {
    GSfsysHandle *fsysHandle;
    for (u32 i = 0; i < sFsysHandlePoolCount; i++) {
        fsysHandle = &sFsysHandlePool[i];

        switch (fsysHandle->mState) {
            case FSYS_STATE_CRITICAL_ERROR:
            case FSYS_STATE_FREE:
            case FSYS_STATE_INVALID:
            case FSYS_STATE_FINISHED:
                continue;
        }

        if (fsysHandle->mFileHandle == fileHandle) {
            return fsysHandle;
        }

        GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
        // TODO #define this flag
        if (fsys == NULL || !(fsys->mFlags & 1)) {
            continue;
        }

        GSfsysEntry *fsysEntry;
        for (u32 j = 0; j < fsys->mFileCount; j++) {
            fsysEntry = getFsysEntry(fsysHandle, j);
            if (fsysEntry != NULL && fsysEntry->mFileHandle == fileHandle) {
                return fsysHandle;
            }
        }
    }

    return NULL;
}

GSfsysHandle *GSfsys::getFsysHandleById(u32 fsysId, bool activeOnly) {
    for (u32 i = 0; i < sFsysHandlePoolCount; i++) {
        if (activeOnly == true) {
            switch (sFsysHandlePool[i].mState) {
                case FSYS_STATE_CRITICAL_ERROR:
                case FSYS_STATE_FREE:
                case FSYS_STATE_FINISHED:
                    continue;
            }
        }
        else if (sFsysHandlePool[i].mState == FSYS_STATE_FREE) {
            continue;
        }

        if (sFsysHandlePool[i].mFsysId == fsysId) {
            return &sFsysHandlePool[i];
        }
    }
    return NULL;
}

GSfsysHandle *GSfsys::getAvailableFsysHandle(bool ignoreLoaded) {
    GSfsysHandle *fsysHandle = NULL;

    u32 i = sFsysHandlePoolLastIndex;
    while (fsysHandle == NULL) {
        switch (sFsysHandlePool[i].mState) {
            case FSYS_STATE_FINISHED:
                // NOTE must be signed comparison to match
                if ((int)ignoreLoaded == true) {
                    break;
                }
                // fallthrough
            case FSYS_STATE_CRITICAL_ERROR:
            case FSYS_STATE_FREE:
            case FSYS_STATE_INVALID:
                fsysHandle = &sFsysHandlePool[i];
                if (fsysHandle->mData != NULL) {
                    freeFsysDataBuffer(fsysHandle);
                }
                break;
        }

        i++;
        if (i >= sFsysHandlePoolCount) {
            i = 0;
        }

        if (i == sFsysHandlePoolLastIndex) {
            break;
        }
    }
    sFsysHandlePoolLastIndex = i;

    return fsysHandle;
}

GSfsysHandle *GSfsys::getOrStealFsysHandle() {
    GSfsysHandle *fsysHandle;

    fsysHandle = getAvailableFsysHandle(true);
    if (fsysHandle != NULL) {
        return fsysHandle;
    }

    fsysHandle = getAvailableFsysHandle(false);
    if (fsysHandle != NULL) {
        return fsysHandle;
    }

    return NULL;
}

void GSfsys::appendNodeToList(GSfsysNode *node, GSfsysNode **list) {
    BOOL intEnabled = OSDisableInterrupts();

    if (*list == NULL) {
        *list = node;
    }
    else {
        GSfsysNode *end = *list;
        while (end->mNext != NULL) {
            end = end->mNext;
        }
        end->mNext = node;
        node->mPrev = end;
    }

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::removeNodeFromList(GSfsysNode *node, GSfsysNode **list) {
    BOOL intEnabled = OSDisableInterrupts();

    if (node->mPrev != NULL) {
        node->mPrev->mNext = node->mNext;
    }

    if (node->mNext != NULL) {
        node->mNext->mPrev = node->mPrev;
    }

    if (node == *list) {
        *list = node->mNext;
    }

    node->mInUse = false;
    node->mPrev = NULL;
    node->mNext = NULL;

    OSRestoreInterrupts(intEnabled);
}

GSfsysEntryHandle *GSfsys::getFreeFsysEntryHandle() {
    GSfsysEntryHandle *fsysEntryHandle = NULL;

    BOOL intEnabled = OSDisableInterrupts();

    u32 i = sFsysEntryHandlePoolLastIndex;
    while (fsysEntryHandle == NULL) {
        if (!sFsysEntryHandlePool[i].mInUse) {
            fsysEntryHandle = &sFsysEntryHandlePool[i];
            fsysEntryHandle->mPrev = NULL;
            fsysEntryHandle->mNext = NULL;
            fsysEntryHandle->mInUse = true;
            fsysEntryHandle->mReadComplete = false;
            fsysEntryHandle->mCompressed = false;
            fsysEntryHandle->mProcessed = false;
            fsysEntryHandle->mFsysHandle = NULL;
            fsysEntryHandle->mInfo = NULL;
            fsysEntryHandle->mFsysEntry.mMagic[0] = '\0';
            fsysEntryHandle->mFsysEntry.mMagic[1] = '\0';
            fsysEntryHandle->mFsysEntry.mMagic[2] = '\0';
            fsysEntryHandle->mFsysEntry.mMagic[3] = '\0';
            fsysEntryHandle->mFsysEntry.mUnpackedSize = 0;
            fsysEntryHandle->mFsysEntry.mPackedSize = 0;
            fsysEntryHandle->mFsysEntry.mDataSize = 0;
            fsysEntryHandle->mRingBuffer = NULL;
            fsysEntryHandle->mCopyPosition = 0;
            fsysEntryHandle->mRingBufferIndex = 0;
            fsysEntryHandle->mDataFlags = 0;
            fsysEntryHandle->mIterationCount = 0;
            fsysEntryHandle->mSourcePosition = 0;
            fsysEntryHandle->mWriteIndex = 0;
            fsysEntryHandle->mResumeFrom = 0;
        }

        i++;
        if (i >= sFsysEntryHandlePoolCount) {
            i = 0;
        }
        if (i == sFsysEntryHandlePoolLastIndex) {
            break;
        }
    }
    sFsysEntryHandlePoolLastIndex = i;

    OSRestoreInterrupts(intEnabled);

    return fsysEntryHandle;
}

void GSfsys::enqueueFsysEntry(GSfsysEntryHandle *fsysEntryHandle) {
    appendNodeToList((GSfsysNode *)fsysEntryHandle, (GSfsysNode **)&sFsysEntryList);
}

void GSfsys::dequeueFsysEntry(GSfsysEntryHandle *fsysEntryHandle) {
    removeNodeFromList((GSfsysNode *)fsysEntryHandle, (GSfsysNode **)&sFsysEntryList);
}

GStocEntry *GSfsys::getTocEntry(u32 fsysId) {
    u32 count = sToc->mCount;
    GStocEntry *tocEntry = getTocTableStart();
    for (u32 i = 0; i < count; i++, tocEntry++) {
        if (tocEntry->mFsysId == fsysId) {
            return tocEntry;
        }
    }
    return NULL;
}

void GSfsys::setFsysNextState(GSfsysHandle *fsysHandle, GSfsysState state) {
    BOOL intEnabled = OSDisableInterrupts();
    fsysHandle->mNextState = state;
    OSRestoreInterrupts(intEnabled);
}

void GSfsys::setFsysEntryNextState(GSfsysEntry *fsysEntry, GSfsysEntryState state) {
    BOOL intEnabled = OSDisableInterrupts();
    fsysEntry->mNextState = state;
    OSRestoreInterrupts(intEnabled);
}

bool GSfsys::getFsysPath(GSfsysHandle *fsysHandle, char *outPath) {
    GStocEntry *tocEntry = getTocEntry(fsysHandle->mFsysId);
    if (tocEntry == NULL) {
        return false;
    }

    sprintf(outPath, "%s.fsys", tocEntry->mName);
    return true;
}

bool GSfsys::openFsys(GSfsysHandle *fsysHandle) {
    char path[0x80];
    getFsysPath(fsysHandle, path);

    fsysHandle->mFileHandle = GSfile::openFile(path);
    if (fsysHandle->mFileHandle == NULL) {
        fsysHandle->setNextState(FSYS_STATE_ERROR_FILEOPEN);
        return false;
    }

    if (fsysHandle->mTocEntry->mSize == 0) {
        fsysHandle->setNextState(FSYS_STATE_READ_SIZE);
    }
    else {
        fsysHandle->setNextState(FSYS_STATE_BEGIN_REQUEST);
    }
    return true;
}

bool GSfsys::closeFsys(GSfsysHandle *fsysHandle, bool skipCallback) {
    if (!skipCallback
        && fsysHandle->mUserCallback != NULL
        && fsysHandle->mRequestType != FSYS_REQUEST_STREAM
    ) {
        fsysHandle->mUserCallback(
            fsysHandle->mRequestType,
            fsysHandle->_34,
            fsysHandle->_38
        );
    }
    
    BOOL intEnabled = OSDisableInterrupts();
    setFsysCacheEntriesPinned(fsysHandle->mFsysId, false);
    freeStreamedFsysBuffers(fsysHandle);
    OSRestoreInterrupts(intEnabled);

    GSfileHandle *fileHandle = fsysHandle->mFileHandle;
    fsysHandle->mFileHandle = NULL;
    return GSfile::closeFile(fileHandle) != 0;
}

u32 GSfsys::countActiveRequestsOfType(GSfsysRequestType requestType) {
    u32 count = 0;
    for (u32 i = 0; i < sFsysHandlePoolCount; i++) {
        switch (sFsysHandlePool[i].mState) {
            case FSYS_STATE_CRITICAL_ERROR:
            case FSYS_STATE_FREE:
            case FSYS_STATE_INVALID:
            case FSYS_STATE_FINISHED:
                continue;
        }

        if (requestType == sFsysHandlePool[i].mRequestType) {
            count++;
        }
    }
    return count;
}

bool GSfsys::doFsysEntryState(GSfsysHandle *fsysHandle, u32 entryIndex) {
    GSfsysEntry *fsysEntry = getFsysEntry(fsysHandle, entryIndex);
    if (fsysEntry == NULL) {
        return false;
    }
    
    BOOL intEnabled = OSDisableInterrupts();
    if (fsysEntry->mNextState != FSYS_ENTRY_STATE_NULL) {
        fsysEntry->mState = fsysEntry->mNextState;
        fsysEntry->mNextState = FSYS_ENTRY_STATE_NULL;
    }
    OSRestoreInterrupts(intEnabled);

    bool finished;
    if (!(fsysEntry->mFlags & FSYS_ENTRY_FLAG_FINISHED)) {
        switch (fsysEntry->mState) {
            case FSYS_ENTRY_STATE_READ_ERROR:
                readNextFsysEntryChunk(fsysHandle, fsysEntry);
                break;
            
            case FSYS_ENTRY_STATE_QUEUE_ERROR:
                if (queueFsysEntryForCopying(fsysHandle, fsysEntry) == true) {
                    readNextFsysEntryChunk(fsysHandle, fsysEntry);
                }
                break;
            
            case FSYS_ENTRY_STATE_YIELD:
                if (fsysHandle->mCancelRequested == true) {
                    setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
                    setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READY);
                }
                else if (countActiveRequestsOfType(FSYS_REQUEST_LOAD) + countActiveRequestsOfType(FSYS_REQUEST_CACHE) == 0) {
                    if (fsysEntry->mRingBufFill <= getHalfStreamBufferSize()) {
                        readNextFsysEntryChunk(fsysHandle, fsysEntry);
                    }
                }
                else {
                    if (fsysEntry->mRingBufFill <= getStreamChunkSize()) {
                        readNextFsysEntryChunk(fsysHandle, fsysEntry);
                    }
                }
                break;
            
            case FSYS_ENTRY_STATE_STANDBY:
                if (fsysHandle->mCancelRequested == true) {
                    setFsysNextState(fsysHandle, FSYS_STATE_READ_COMPLETE);
                    setFsysEntryNextState(fsysEntry, FSYS_ENTRY_STATE_READY);
                }
                break;
            
            // NOTE these cases required explicitly to match
            case FSYS_ENTRY_STATE_BEGIN:
            case FSYS_ENTRY_STATE_READY:
                break;
        }
        finished = false;
    }
    else {
        finished = true;
    }
    
    intEnabled = OSDisableInterrupts();
    if (fsysEntry->mNextState != FSYS_ENTRY_STATE_NULL) {
        fsysEntry->mState = fsysEntry->mNextState;
        fsysEntry->mNextState = FSYS_ENTRY_STATE_NULL;
    }
    OSRestoreInterrupts(intEnabled);

    return finished;
}

u32 GSfsys::getFsysEntryIndex(GSfsysHandle *fsysHandle, u32 fileId) {
    if (fileId == 0xffff) {
        return 0xffff;
    }

    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if (fsys != NULL) {
        for (u32 i = 0; i < fsys->mFileCount; i++) {
            GSfsysEntry *fsysEntry = getFsysEntry(fsysHandle, i);
            if (fsysEntry != NULL && fsysEntry->mFileId == fileId) {
                return i;
            }
        }
    }

    return 0xffff;
}

bool GSfsys::checkAllFsysEntriesReady(GSfsysHandle *fsysHandle) {
    GSfsysHeaderEx *fsys = getFsysData(fsysHandle);
    if (fsys == NULL) {
        return false;
    }

    bool finished = true;
    if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff) {
        u32 index;
        if (fsysHandle->mRequestType == FSYS_REQUEST_STREAM) {
            index = getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId);
            if (!doFsysEntryState(fsysHandle, index)) {
                finished = false;
            }

            index = getFsysEntryIndex(fsysHandle, fsysHandle->_34);
            if (!doFsysEntryState(fsysHandle, index)) {
                finished = false;
            }
        }
        // TODO fix regswap here
        else if (fsysHandle->_40 != NULL) {
            u32 *nextId = fsysHandle->_40;
            while (*nextId != 0) {
                index = getFsysEntryIndex(fsysHandle, *nextId);
                if (!doFsysEntryState(fsysHandle, index)) {
                    finished = false;
                }
                nextId++;
            }
        }
        else {
            index = getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId);
            return doFsysEntryState(fsysHandle, index);
        }
    }
    else {
        for (u32 i = 0; i < fsys->mFileCount; i++) {
            if (!doFsysEntryState(fsysHandle, i)) {
                finished = false;
            }
        }
    }

    return finished;
}

void GSfsys::setTocEntryFlags(u32 fsysId, u32 flags) {
    GStocEntry *tocEntry = getTocEntry(fsysId);
    if (tocEntry != NULL) {
        tocEntry->mFlags |= flags;
    }
}

void GSfsys::clearTocEntryFlags(u32 fsysId, u32 flags) {
    GStocEntry *tocEntry = getTocEntry(fsysId);
    if (tocEntry != NULL) {
        tocEntry->mFlags &= ~flags;
    }
}

void GSfsys::readFsysSizeCallback(s32 result, GSfileHandle *fileHandle) {
    GSfsysHandle *fsysHandle = getAssociatedFsysHandle(fileHandle);
    if (fsysHandle == NULL) {
        sCurrentFsysHeader = NULL;
        if (fsysHandle == NULL) {
            // Perhaps there was debug stuff here?
            return;
        }
        return;
    }

    if (result < 0) {
        sCurrentFsysHeader = NULL;
        setFsysNextState(fsysHandle, FSYS_STATE_READ_SIZE);
        if (fsysHandle == NULL) {
            // Again, debug?
            return;
        }
        return;
    }
    
    fsysHandle->mTocEntry->mSize = sCurrentFsysHeader->mSize;
    sCurrentFsysHeader = NULL;
    setFsysNextState(fsysHandle, FSYS_STATE_BEGIN_REQUEST);
}

void GSfsys::doFsysState(GSfsysHandle *fsysHandle) {
    BOOL intEnabled = OSDisableInterrupts();
    if (fsysHandle->mNextState != FSYS_STATE_NULL) {
        fsysHandle->mState = fsysHandle->mNextState;
        fsysHandle->mNextState = FSYS_STATE_NULL;
    }
    OSRestoreInterrupts(intEnabled);

    switch (fsysHandle->mState) {
        case FSYS_STATE_READ_SIZE:
            if (sCurrentFsysHeader == NULL) {
                sCurrentFsysHeader = &sFsysHeaderBuffer;

                setFsysNextState(fsysHandle, FSYS_STATE_READING);

                bool success = GSfile::readFileAsync(
                    fsysHandle->mFileHandle,
                    sCurrentFsysHeader,
                    sizeof(GSfsysHeader),
                    0,
                    readFsysSizeCallback
                );
                if (!success) {
                    sCurrentFsysHeader = NULL;
                    setFsysNextState(fsysHandle, FSYS_STATE_READ_SIZE);
                }
            }
            break;
        
        case FSYS_STATE_BEGIN_REQUEST:
            switch (fsysHandle->mRequestType) {
                case FSYS_REQUEST_LOAD:
                    setFsysNextState(fsysHandle, FSYS_STATE_6);
                    readFsysData(fsysHandle);
                    break;
                
                case FSYS_REQUEST_STREAM:
                    setFsysNextState(fsysHandle, FSYS_STATE_9);
                    readFsysData(fsysHandle);
                    break;
                
                case FSYS_REQUEST_CACHE:
                    setFsysNextState(fsysHandle, FSYS_STATE_7);
                    readFsysData(fsysHandle);
                    break;
                
                case FSYS_REQUEST_SEEK_START:
                    setFsysNextState(fsysHandle, FSYS_STATE_SEEK_TO_START);
                    seekFsysToStart(fsysHandle);
                    break;
                
                default:
                    setFsysNextState(fsysHandle, FSYS_STATE_ERROR_INVALIDSTATE);
                    break;
            }
            break;
        
        case FSYS_STATE_6:
        case FSYS_STATE_7:
        case FSYS_STATE_9:
            checkAllFsysEntriesReady(fsysHandle);
            break;
        
        case FSYS_STATE_READ_COMPLETE:
            switch (fsysHandle->mRequestType) {
                case FSYS_REQUEST_LOAD:
                    if (!checkAllFsysEntriesReady(fsysHandle)) {
                        break;
                    }
                    // fallthrough
                case FSYS_REQUEST_CACHE:
                case FSYS_REQUEST_STREAM:
                    setFsysNextState(fsysHandle, FSYS_STATE_REQUEST_COMPLETE);
                    break;
                
                case FSYS_REQUEST_SEEK_START:
                default:
                    setFsysNextState(fsysHandle, FSYS_STATE_ERROR_INVALIDSTATE);
                    break;
            }
            break;
        
        case FSYS_STATE_ERROR_INVALIDSTATE:
        case FSYS_STATE_ERROR_FILEREAD:
        case FSYS_STATE_NEG_995:
        case FSYS_STATE_ERROR_FILESEEK:
            OSReport("_fsysForegroundTask:ERROR...:%d\n", fsysHandle->mFsysId);
            if (!closeFsys(fsysHandle, true)) {
                setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILECLOSE);
                break;
            }
            // fallthrough
        case FSYS_STATE_ERROR_FILEOPEN:
            OSReport("_fsysForegroundTask:ERROR_FILEOPEN:%d\n", fsysHandle->mFsysId);
            openFsys(fsysHandle);
            break;
        
        case FSYS_STATE_ERROR_FILECLOSE:
            OSReport("_fsysForegroundTask:ERROR_FILECLOSE:%d\n", fsysHandle->mFsysId);
            setFsysNextState(fsysHandle, FSYS_STATE_CRITICAL_ERROR);
            break;
        
        case FSYS_STATE_REQUEST_COMPLETE:
            if (!closeFsys(fsysHandle, false)) {
                setFsysNextState(fsysHandle, FSYS_STATE_ERROR_FILECLOSE);
                break;
            }

            // Equivalent to != 3 && != 4 (though does not match that way)
            if (fsysHandle->mRequestType >= 5 || fsysHandle->mRequestType < 3) {
                setTocEntryFlags(fsysHandle->mFsysId, TOC_ENTRY_FLAG_LOADED);
            }

            setFsysNextState(fsysHandle, FSYS_STATE_FINISHED);
            break;
        
        // NOTE these cases required explicitly to match
        case FSYS_STATE_FREE:
        case FSYS_STATE_INVALID:
        case FSYS_STATE_FINISHED:
            break;
    }

    intEnabled = OSDisableInterrupts();
    if (fsysHandle->mNextState != FSYS_STATE_NULL) {
        fsysHandle->mState = fsysHandle->mNextState;
        fsysHandle->mNextState = FSYS_STATE_NULL;
    }
    OSRestoreInterrupts(intEnabled);
}

void GSfsys::foregroundTaskCallback(u32 taskId, void *userParam) {
    GSfsysEntryHandle *fsysEntryHandle, *next;

    fsysEntryHandle = sFsysEntryList;
    while (fsysEntryHandle != NULL) {
        next = fsysEntryHandle->mNext;
        if (fsysEntryHandle->mReadComplete == true) {
            GSfsysHandle *fsysHandle = fsysEntryHandle->mFsysHandle;
            GSfsysEntry *fsysEntry = fsysEntryHandle->mInfo;
            u32 index = getFsysEntryIndex(fsysHandle, fsysEntry->mFileId);

            GSfsysEntry *prevEntry;
            if (index != 0) {
                prevEntry = getFsysEntry(fsysHandle, index - 1);
            }
            else {
                prevEntry = NULL;
            }

            if (getFsysEntryIndex(fsysHandle, fsysHandle->mNextFileId) != 0xffff
                || prevEntry == NULL
                || (prevEntry->mFlags & FSYS_ENTRY_FLAG_FINISHED)
            ) {
                GSfsysFileTypeHandler *handler = getHandlerForFileType(fsysEntry->mFileType);
                if (!fsysHandle->mCancelRequested && handler->_C != NULL) {
                    if ((fsysEntry->mFlags & FSYS_ENTRY_FLAG_COMPRESSED)) {
                        handler->_C(fsysHandle->mFsysId, fsysEntry->mFileId, fsysEntry->mUnpackedSize);
                    }
                    else {
                        handler->_C(fsysHandle->mFsysId, fsysEntry->mFileId, fsysEntry->mPackedSize);
                    }
                }
                if (fsysEntryHandle->mRingBuffer != NULL) {
                    GSmem::free(fsysEntryHandle->mRingBuffer);
                    fsysEntryHandle->mRingBuffer = NULL;
                }
                dequeueFsysEntry(fsysEntryHandle);
                fsysEntry->mFlags |= FSYS_ENTRY_FLAG_FINISHED;
                index = getFsysEntryIndex(fsysHandle, fsysEntry->mFileId);
                setFsysCacheEntryPinned(fsysHandle->mFsysId, index, false);
            }
            else if (prevEntry != NULL && !(prevEntry->mFlags & FSYS_ENTRY_FLAG_FINISHED)) {
                index = getFsysEntryIndex(fsysHandle, fsysEntry->mFileId);
                OSReport("<1>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", fsysHandle->mFsysId, index);
            }
            else {
                index = getFsysEntryIndex(fsysHandle, fsysEntry->mFileId);
                OSReport("<2>-----fsysBGwork:Wait Prev ResFinish Index=%d:%d\n", fsysHandle->mFsysId, index);
            }
        }
        fsysEntryHandle = next;
    }

    for (u32 i = 0; i < sFsysHandlePoolCount; i++) {
        doFsysState(&sFsysHandlePool[i]);
    }

    processNextFsysRequest();
};

bool GSfsys::processMidCopyCancel(GSfsysEntryHandle *fsysEntryHandle) {
    if (fsysEntryHandle->mFsysHandle->mCancelRequested == true) {
        clearChunkList(&fsysEntryHandle->mInfo->mPendingChunks);
        clearChunkList(&fsysEntryHandle->mInfo->mCompletedChunks);
        fsysEntryHandle->mReadComplete = true;
        return true;
    }
    return false;
}

void GSfsys::fillAndFlushBuffer(void *buffer, u8 fillValue, u32 length) {
    if (buffer != NULL) {
        memset(buffer, fillValue, length);
        DCFlushRange(buffer, length);
    }
}

void GSfsys::decompressLzss(GSfsysEntryHandle *fsysEntryHandle) {
    // TODO fix regswaps
    u8 *writeBuf;
    u8 *ringBuf;

    u32 srcLen;
    u32 bufLen;
    u32 resumeFrom;

    GSfsysChunk *nextChunk;
    
    u32 copyPos;
    u32 ringBufIdx;
    u32 flags;
    u32 iterCount;
    
    u32 srcPos;
    u32 writeIdx;
    
    int copyLen;
    u32 readIdx;
    int i;
    u8 *readBuf;

    if (fsysEntryHandle->mReadComplete == true) {
        return;
    }

    if (processMidCopyCancel(fsysEntryHandle) == true) {
        return;
    }

    nextChunk = fsysEntryHandle->mInfo->mCompletedChunks;
    if (nextChunk == NULL) {
        return;
    }

    if (fsysEntryHandle->mRingBuffer == NULL) {
        // TODO better understand where these 17s and 18s are coming from
        u32 size = LZSS_RING_BUF_LEN + 17;
        fsysEntryHandle->mRingBuffer = (u8 *)GSmem::allocAlignedTop(size, -0x20);
        if (fsysEntryHandle->mRingBuffer == NULL) {
            return;
        }

        memset(fsysEntryHandle->mRingBuffer, 0, LZSS_RING_BUF_LEN - 18);
        memcpy(&fsysEntryHandle->mFsysEntry, nextChunk->mBuffer, sizeof(GSlzssHeader));

        fsysEntryHandle->mRingBufferIndex = LZSS_RING_BUF_LEN - 18;
        fsysEntryHandle->mDataFlags = 0;
        fsysEntryHandle->mFsysEntry.mDataSize = fsysEntryHandle->mFsysEntry.mPackedSize - sizeof(GSlzssHeader);
        fsysEntryHandle->mResumeFrom = 0;

        readIdx = sizeof(GSlzssHeader);
    }
    else {
        readIdx = 0;
    }

    iterCount = fsysEntryHandle->mIterationCount;
    flags = fsysEntryHandle->mDataFlags;
    ringBufIdx = fsysEntryHandle->mRingBufferIndex;
    copyPos = fsysEntryHandle->mCopyPosition;
    srcPos = fsysEntryHandle->mSourcePosition;
    writeIdx = fsysEntryHandle->mWriteIndex;
    writeBuf = (u8 *)fsysEntryHandle->mInfo->mOutputBuffer;
    srcLen = fsysEntryHandle->mFsysEntry.mDataSize;
    bufLen = gFsysChunkSize;
    ringBuf = fsysEntryHandle->mRingBuffer;
    resumeFrom = fsysEntryHandle->mResumeFrom;
    while (true) {
        readBuf = (u8 *)nextChunk->mBuffer;
        switch (resumeFrom) {
            case 0:
                break;
            
            case 1:
                goto fsysEntry_read_flags;
            
            case 2:
                goto fsysEntry_read_literal;
            
            case 3:
                goto fsysEntry_read_lookup_1;
            
            case 4:
                goto fsysEntry_read_lookup_2;
        }

        while (true) {
            flags >>= 1;
            if (!(flags & 0x100)) {
fsysEntry_read_flags:
                srcPos++;
                u8 c = readBuf[readIdx++];

                if (srcPos > srcLen) {
                    break;
                }

                if (readIdx > bufLen) {
                    resumeFrom = 1;
                    srcPos--;
                    break;
                }

                flags = 0xff00 | c;
            }
            
            if ((flags & 1)) {
fsysEntry_read_literal:
                srcPos++;
                u8 c = readBuf[readIdx++];

                if (srcPos > srcLen) {
                    break;
                }

                if (readIdx > bufLen) {
                    resumeFrom = 2;
                    srcPos--;
                    break;
                }

                writeBuf[writeIdx++] = c;
                ringBuf[ringBufIdx++] = c;
                ringBufIdx %= LZSS_RING_BUF_LEN;
            }
            else {
fsysEntry_read_lookup_1:
                srcPos++;
                copyPos = readBuf[readIdx++];

                if (srcPos > srcLen) {
                    break;
                }

                if (readIdx > bufLen) {
                    resumeFrom = 3;
                    srcPos--;
                    break;
                }
fsysEntry_read_lookup_2:
                srcPos++;
                u8 c = readBuf[readIdx++];

                if (srcPos > srcLen) {
                    break;
                }

                if (readIdx > bufLen) {
                    resumeFrom = 4;
                    srcPos--;
                    break;
                }

                copyPos |= (c & 0xf0) << 4;

                copyLen = (c & 0xf) + 2;
                for (i = 0; i <= copyLen; i++) {
                    c = ringBuf[(copyPos + i) % LZSS_RING_BUF_LEN];
                    writeBuf[writeIdx++] = c;
                    ringBuf[ringBufIdx++] = c;
                    ringBufIdx %= LZSS_RING_BUF_LEN;
                }
            }
            iterCount++;
        }

        popChunkFromList(&fsysEntryHandle->mInfo->mCompletedChunks, true);

        if (srcPos > srcLen) {
            fsysEntryHandle->mReadComplete = true;
            return;
        }

        if (processMidCopyCancel(fsysEntryHandle) == true) {
            return;
        }

        nextChunk = fsysEntryHandle->mInfo->mCompletedChunks;
        if (nextChunk == NULL) {
            break;
        }

        readIdx = 0;
    }

    fsysEntryHandle->mIterationCount = iterCount;
    fsysEntryHandle->mDataFlags = flags;
    fsysEntryHandle->mCopyPosition = copyPos;
    fsysEntryHandle->mRingBufferIndex = ringBufIdx;
    fsysEntryHandle->mSourcePosition = srcPos;
    fsysEntryHandle->mWriteIndex = writeIdx;
    fsysEntryHandle->mResumeFrom = resumeFrom;
}

void GSfsys::readUncompressedFile(GSfsysEntryHandle *fsysEntryHandle, bool doCopy) {
    if (fsysEntryHandle->mReadComplete == true) {
        return;
    }

    do {
        if (processMidCopyCancel(fsysEntryHandle) == true) {
            return;
        }

        GSfsysChunk *nextChunk = fsysEntryHandle->mInfo->mCompletedChunks;
        if (nextChunk == NULL) {
            return;
        }

        if (doCopy == true) {
            void *dst = (u8 *)fsysEntryHandle->mInfo->mOutputBuffer + fsysEntryHandle->mSourcePosition;
            u32 size = getChunkSize(fsysEntryHandle->mInfo->mPackedSize, fsysEntryHandle->mSourcePosition);
            memcpy(dst, nextChunk->mBuffer, size);
        }

        popChunkFromList(&fsysEntryHandle->mInfo->mCompletedChunks, true);

        fsysEntryHandle->mSourcePosition += gFsysChunkSize;
    } while (fsysEntryHandle->mSourcePosition < fsysEntryHandle->mInfo->mPackedSize);

    fsysEntryHandle->mReadComplete = true;
}

void GSfsys::backgroundTaskCallback(u32 taskId, void *userParam) {
    GSfsysEntryHandle *fsysEntryHandle = sFsysEntryList;
    while (fsysEntryHandle != NULL) {
        if (!fsysEntryHandle->mProcessed) {
            fsysEntryHandle->mProcessed = true;

            GSfsysFileTypeHandler *handler = getHandlerForFileType(fsysEntryHandle->mInfo->mFileType);
            void *outBuf;
            if (handler->_8 != NULL) {
                outBuf = handler->_8(
                    fsysEntryHandle->mFsysHandle->mFsysId,
                    fsysEntryHandle->mInfo->mFileId,
                    fsysEntryHandle->mInfo->mUnpackedSize
                );
            }
            else {
                outBuf = allocBufferInFileCache(
                    (fsysEntryHandle->mInfo->mUnpackedSize + 0x1f) / 0x20 * 0x20,
                    fsysEntryHandle->mFsysHandle->mFsysId,
                    fsysEntryHandle->mInfo->mFileId
                );
            }
            fsysEntryHandle->mInfo->mOutputBuffer = outBuf;
        }

        if (fsysEntryHandle->mInfo->mOutputBuffer == NULL) {
            readUncompressedFile(fsysEntryHandle, false);
        }
        else if (fsysEntryHandle->mCompressed == true) {
            decompressLzss(fsysEntryHandle);
        }
        else {
            readUncompressedFile(fsysEntryHandle, true);
        }

        fsysEntryHandle = fsysEntryHandle->mNext;
    }
}

bool GSfsys::initSubroutine(u32 chunkHeapSize, u32 cacheHeapSize, u32 nCacheEntries) {
    if (sInitialized == true) {
        return false;
    }

    sFsysHandlePoolLastIndex = 0;
    sFsysEntryHandlePoolLastIndex = 0;
    sFsysRequestQueues[0] = NULL;
    sFsysRequestQueues[1] = NULL;
    sFsysRequestQueues[2] = NULL;
    sActiveFsysRequest = NULL;

    if (!initFsysChunkSystem(chunkHeapSize)) {
        return false;
    }

    // The cacheHeapSize does not actually get used
    if (!initFsysCacheSystem(cacheHeapSize, nCacheEntries)) {
        return false;
    }

    sFsysHandlePoolCount = 4;
    sFsysEntryHandlePoolCount = 32;
    sLoadRequestPoolCount = 24;
    
    sFsysHandlePool = (GSfsysHandle *)allocAligned32(sizeof(GSfsysHandle) * sFsysHandlePoolCount);
    if (sFsysHandlePool == NULL) {
        return false;
    }

    sFsysEntryHandlePool = (GSfsysEntryHandle *)allocAligned32(sizeof(GSfsysEntryHandle) * sFsysEntryHandlePoolCount);
    if (sFsysEntryHandlePool == NULL) {
        return false;
    }

    sFsysRequestPool = (GSfsysRequest *)allocAligned32(sizeof(GSfsysRequest) * sLoadRequestPoolCount);
    if (sFsysRequestPool == NULL) {
        return false;
    }

    for (u32 i = 0; i < sFsysHandlePoolCount; i++) {
        sFsysHandlePool[i].mState = FSYS_STATE_FREE;
        sFsysHandlePool[i].mNextState = FSYS_STATE_NULL;
        sFsysHandlePool[i].mData = NULL;
        sFsysHandlePool[i].mDataLoaded = false;
    }

    for (u32 i = 0; i < sFsysEntryHandlePoolCount; i++) {
        sFsysEntryHandlePool[i].mInUse = false;
    }

    for (u32 i = 0; i < sLoadRequestPoolCount; i++) {
        sFsysRequestPool[i].mFsysId = 0;
    }

    if (!loadToc()) {
        return false;
    }

    sForegroundTaskID = GStask::createTask(TASK_TYPE_MAIN, 254, NULL, foregroundTaskCallback);
    GStask::setTaskName(sForegroundTaskID, "GSfsysDaemonForeground");

    sBackgroundTaskID = GStask::createTask(TASK_TYPE_MAIN, 2, NULL, backgroundTaskCallback);
    GStask::setTaskName(sBackgroundTaskID, "GSfsysDaemonBackground");

    sInitialized = true;

    return true;
}

void GSfsys::setFileTypeHandlers(GSfsysFileTypeHandler *handlerList) {
    if (handlerList == NULL) {
        return;
    }

    gFileTypeHandlerList = handlerList;
    gFileTypeHandlerCount = 0;

    while (gFileTypeHandlerList[gFileTypeHandlerCount]._0 >= 0) {
        gFileTypeHandlerCount++;
    }
}

s32 GSfsys::getFsysLoadStatus(u32 fsysId) {
    if (!sInitialized) {
        return FSYS_LOAD_CRITICAL_ERROR;
    }

    GStocEntry *tocEntry = getTocEntry(fsysId);
    if (tocEntry == NULL) {
        return FSYS_LOAD_INVALID;
    }
    else if ((tocEntry->mFlags & TOC_ENTRY_FLAG_LOADED)) {
        return FSYS_LOAD_COMPLETE;
    }

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle == NULL) {
        return FSYS_LOAD_INVALID;
    }

    switch (fsysHandle->mState) {
        case FSYS_STATE_FINISHED:
            return FSYS_LOAD_COMPLETE;
        
        case FSYS_STATE_INVALID:
            return FSYS_LOAD_INVALID;
        
        case FSYS_STATE_CRITICAL_ERROR:
            return FSYS_LOAD_CRITICAL_ERROR;
        
        default:
            return FSYS_LOAD_IN_PROGRESS;
    }
}

void GSfsys::invalidateFsysHandle(u32 fsysId) {
    clearTocEntryFlags(fsysId, TOC_ENTRY_FLAG_LOADED);

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle != NULL) {
        fsysHandle->mState = FSYS_STATE_INVALID;
    }
}

bool GSfsys::beginLoadFsys(
    u32 fsysId,
    u32 fileId,
    GSfsysRequestType requestType,
    bool persistent,
    GSfsysCallback userCallback,
    u32 userParam1,
    u32 userParam2,
    u32 *fileIds
) {
    GSfsysHandle *fsysHandle;

    BOOL intEnabled = OSDisableInterrupts();

    invalidateFsysHandle(fsysId);

    fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle == NULL) {
        fsysHandle = getOrStealFsysHandle();
        if (fsysHandle == NULL) {
            OSRestoreInterrupts(intEnabled);
            return false;
        }
        fsysHandle->mData = NULL;
        fsysHandle->mCacheIndex = getNextCacheFsysIndex();
    }

    fsysHandle->mFsysId = fsysId;
    fsysHandle->mNextFileId = fileId;
    fsysHandle->mFileHandle = NULL;
    fsysHandle->mRequestType = requestType;
    fsysHandle->mState = FSYS_STATE_OPENING;
    fsysHandle->mNextState = FSYS_STATE_NULL;
    fsysHandle->mReadingEntryIndex = 0;
    fsysHandle->mCopyingEntryIndex = 0;
    fsysHandle->mCancelRequested = false;
    fsysHandle->mPersistent = persistent;
    fsysHandle->mUserCallback = userCallback;
    fsysHandle->_34 = userParam1;
    fsysHandle->_38 = userParam2;
    fsysHandle->_40 = fileIds;
    fsysHandle->mFileIdQueue = fileIds;
    fsysHandle->mTocEntry = getTocEntry(fsysId);

    openFsys(fsysHandle);

    OSRestoreInterrupts(intEnabled);

    return true;
}

GSfsysRequest *GSfsys::createFsysRequest(
    GSfsysRequestType requestType,
    u32 fsysId,
    u32 fileId,
    bool persistent,
    GSfsysCallback callback,
    u32 param6,
    u32 param7,
    u32 *fileIds
) {
    GSfsysRequest *request = NULL;
    for (u32 i = 0; i < sLoadRequestPoolCount; i++) {
        if (sFsysRequestPool[i].mFsysId == 0) {
            request = &sFsysRequestPool[i];
            request->mPrev = NULL;
            request->mNext = NULL;
            request->mRequestType = requestType;
            request->mFsysId = fsysId;
            request->mFileId = fileId;
            request->mCallback = callback;
            request->_18 = param6;
            request->_1c = param7;
            request->mPersistent = persistent;
            request->mProcessed = false;
            request->mFileIds = fileIds;
            break;
        }
    }
    return request;
}

GSfsysRequest *GSfsys::findFsysRequest(u32 fsysId, u32 fileId) {
    GSfsysRequest *request;
    for (u32 i = 0; i < FSYS_REQUEST_PRIORITY_LEVELS; i++) {
        request = sFsysRequestQueues[i];
        while (request != NULL) {
            // Interesting it doesn't also check mFileId
            if (request->mFsysId == fsysId) {
                return request;
            }
            request = request->mNext;
        }
    }
    return NULL;
}

bool GSfsys::enqueueFsysRequest(GSfsysRequest *request, u32 priority) {
    bool result;

    if (sFsysRequestQueues[priority] == NULL) {
        sFsysRequestQueues[priority] = request;
        result = true;
    }
    else {
        GSfsysRequest *end = sFsysRequestQueues[priority];
        while (end->mNext != NULL) {
            end = end->mNext;
        }

        end->mNext = request;
        request->mPrev = end;
        result = false;
    }

    return result;
}

void GSfsys::dequeueFsysRequest(GSfsysRequest *request) {
    if (request->mPrev != NULL) {
        request->mPrev->mNext = request->mNext;
    }

    if (request->mNext != NULL) {
        request->mNext->mPrev = request->mPrev;
    }

    for (u32 i = 0; i < FSYS_REQUEST_PRIORITY_LEVELS; i++) {
        if (request == sFsysRequestQueues[i]) {
            sFsysRequestQueues[i] = request->mNext;
            break;
        }
    }

    request->mFsysId = 0;
}

bool GSfsys::processFsysRequest(GSfsysRequest *request) {
    if (!request->mProcessed) {
        request->mProcessed = true;
        switch (request->mRequestType) {
            case FSYS_REQUEST_CANCEL:
                cancelFsysLoad(request->mFsysId);
                return false;
            
            default:
                dequeueFsysRequest(request);
                return true;
            
            case FSYS_REQUEST_LOAD:
            case FSYS_REQUEST_CACHE:
            case FSYS_REQUEST_SEEK_START:
            case FSYS_REQUEST_STREAM:
                beginLoadFsys(
                    request->mFsysId,
                    request->mFileId,
                    request->mRequestType,
                    request->mPersistent,
                    request->mCallback,
                    request->_18,
                    request->_1c,
                    request->mFileIds
                );
                return false;
        }
    }
    else if (getFsysLoadStatus(request->mFsysId) <= 0) {
        dequeueFsysRequest(request);
        return true;
    }
    return false;
}

void GSfsys::processNextFsysRequest() {
    if (sActiveFsysRequest != NULL) {
        if (!processFsysRequest(sActiveFsysRequest)) {
            return;
        }
        sActiveFsysRequest = NULL;
    }

    GSfsysRequest *request, *next;
    // NOTE uses signed comparison
    for (s32 i = 0; i < FSYS_REQUEST_PRIORITY_LEVELS; i++) {
        request = sFsysRequestQueues[i];
        while (request != NULL) {
            next = request->mNext;
            if (!processFsysRequest(request)) {
                sActiveFsysRequest = request;
                return;
            }
            request = next;
        }
    }
}

bool GSfsys::submitFsysRequest(
    GSfsysRequestType requestType,
    u32 fsysId,
    u32 fileId,
    bool persistent,
    GSfsysCallback callback,
    u32 param6,
    u32 param7,
    s32 priority,
    u32 *fileIds
) {
    if (!sInitialized) {
        return false;
    }

    // Almost certainly was supposed to test requestType for both
    if (requestType < 0 || priority >= 6) {
        return false;
    }

    if (priority < 0 || priority >= FSYS_REQUEST_PRIORITY_LEVELS) {
        return false;
    }
    
    GSfsysRequest *oldRequest = findFsysRequest(fsysId, fileId);
    if (oldRequest != NULL
        && !oldRequest->mProcessed
        && (requestType == FSYS_REQUEST_CACHE || requestType == FSYS_REQUEST_SEEK_START)
    ) {
        dequeueFsysRequest(oldRequest);
    }

    GSfsysRequest *newRequest = createFsysRequest(
        requestType,
        fsysId,
        fileId,
        persistent,
        callback,
        param6,
        param7,
        fileIds
    );
    if (newRequest == NULL) {
        return false;
    }

    if (enqueueFsysRequest(newRequest, priority) == true) {
        processNextFsysRequest();
    }

    return true;
}

bool GSfsys::requestLoadFsys(u32 fsysId) {
    return submitFsysRequest(
        FSYS_REQUEST_LOAD,
        fsysId,
        0xffff,
        false,
        NULL,
        0,
        0,
        1,
        NULL
    );
}

bool GSfsys::startOrResetFsysStream(u32 fsysId, u32 fileId, u32 param3) {
    if (!sInitialized) {
        return false;
    }

    if (getFsysLoadStatus(fsysId) <= 0) {
        return beginLoadFsys(
            fsysId,
            fileId,
            FSYS_REQUEST_STREAM,
            false,
            NULL,
            0,
            param3,
            NULL
        );
    }
    else {
        cancelFsysLoadBlocking(fsysId);
        return beginLoadFsys(
            fsysId,
            fileId,
            FSYS_REQUEST_STREAM,
            false,
            NULL,
            0,
            param3,
            NULL
        );
    }
}

bool GSfsys::streamFsys(u32 fsysId) {
    return startOrResetFsysStream(fsysId, 0xffff, 0);
}

bool GSfsys::waitForFsysLoad(u32 fsysId, bool allowInvalidAsSuccess) {
    if (!sInitialized) {
        return false;
    }

    while (true) {
        s32 loadStatus = getFsysLoadStatus(fsysId);
        if (loadStatus == FSYS_LOAD_COMPLETE) {
            return true;
        }
        else if (loadStatus == FSYS_LOAD_INVALID) {
            if (allowInvalidAsSuccess == true) {
                return true;
            }
        }
        else if (loadStatus <= FSYS_LOAD_CRITICAL_ERROR) {
            return false;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

bool GSfsys::loadFsys(u32 fsysId) {
    if (!sInitialized) {
        return false;
    }

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, true);
    if (fsysHandle != NULL && fsysHandle->mRequestType == FSYS_REQUEST_CACHE) {
        cancelFsysLoadBlocking(fsysId);
    }

    do {
        if (requestLoadFsys(fsysId) == true) {
            break;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    } while (true);

    return waitForFsysLoad(fsysId, false);
}

bool GSfsys::cancelFsysLoad(u32 fsysId) {
    if (!sInitialized) {
        return false;
    }

    if (getFsysLoadStatus(fsysId) <= 0) {
        return false;
    }

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, true);
    if (fsysHandle == NULL) {
        return false;
    }

    fsysHandle->mCancelRequested = true;
    return true;
}

bool GSfsys::cancelFsysLoadBlocking(u32 fsysId) {
    if (cancelFsysLoad(fsysId) == false) {
        return false;
    }

    return waitForFsysLoad(fsysId, false);
}

bool GSfsys::requestLoadFsysEntry(u32 fsysId, u32 fileId) {
    return submitFsysRequest(
        FSYS_REQUEST_LOAD,
        fsysId,
        fileId,
        false,
        NULL,
        0,
        0,
        1,
        NULL
    );
}

bool GSfsys::requestLoadFsysEntryEx(
    u32 fsysId,
    u32 fileId,
    GSfsysCallback param3,
    u32 param4,
    u32 param5
) {
    return submitFsysRequest(
        FSYS_REQUEST_LOAD,
        fsysId,
        fileId,
        false,
        param3,
        param4,
        param5,
        1,
        NULL
    );
}

bool GSfsys::requestLoadFsysEntries(
    u32 fsysId,
    u32 *fileIds,
    GSfsysCallback param3,
    u32 param4,
    u32 param5
) {
    if (fileIds == NULL || *fileIds == 0) {
        return true;
    }
    return submitFsysRequest(
        FSYS_REQUEST_LOAD,
        fsysId,
        *fileIds,
        false,
        param3,
        param4,
        param5,
        1,
        fileIds
    );
}

bool GSfsys::loadFsysEntry(u32 fsysId, u32 fileId) {
    if (!sInitialized) {
        return false;
    }

    while (true) {
        if (requestLoadFsysEntry(fsysId, fileId) == true) {
            break;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }

    return waitForFsysLoad(fsysId, false);
}

void GSfsys::fn_80249890(u32 fsysId) {
    GSfsysHandle *fsysHandle;
    GSfsysHeaderEx *fsys;
    GSfsysEntry *fsysEntry;
    u32 i;
    BOOL intEnabled;

    if (!sInitialized) {
        return;
    }

    intEnabled = OSDisableInterrupts();

    invalidateFsysHandle(fsysId);

    fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle != NULL) {
        fsys = getFsysData(fsysHandle);
        if (fsys != NULL) {
            for (i = 0; i < fsys->mFileCount; i++) {
                fsysEntry = getFsysEntry(fsysHandle, i);
                if (fsysEntry != NULL) {
                    fsysEntry->mFlags &= ~FSYS_ENTRY_FLAG_FINISHED;
                }
            }
        }

        if (fsysHandle->mFileHandle != NULL) {
            closeFsys(fsysHandle, false);
        }
    }

    OSRestoreInterrupts(intEnabled);
}

void GSfsys::releaseAllCacheEntriesForFsys(u32 fsysId) {
    if (!sInitialized) {
        return;
    }

    while (releaseFirstCacheEntryForFsys(fsysId)) {}
}

void GSfsys::init(
    u32 nFileHandles,
    u32 chunkHeapSize,
    u32 cacheHeapSize,
    u32 nCacheEntries
) {
    GSfile::init(nFileHandles, false);
    // Were params 2 - 4 supposed to be passed here?
    initSubroutine(0, 0, 0);
}

bool GSfsys::fn_802499E4() {
    return false;
}

bool GSfsys::fn_802499EC(u32 fsysId) {
    if (!sInitialized) {
        return false;
    }
    getFsysHandleById(fsysId, false);
    return false;
}

void *GSfsys::fn_80249A28(u32 fsysId, u32 fileId, u32 size) {
    // NOTE does not match with !sInitialized
    if (sInitialized == false) {
        return NULL;
    }
    return fn_8025999C(fsysId, fileId);
}

void *GSfsys::fn_80249A44(u32 fsysId, u32 fileId, u32 size) {
    if (!sInitialized) {
        return NULL;
    }

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle == NULL) {
        return NULL;
    }

    fn_802599D0(fsysId, fsysHandle->_34);
    return NULL;
}

u32 GSfsys::fn_80249AA8() {
    return gFsysChunkSize;
}

bool GSfsys::readFsysStream(
    u32 fsysId,
    u32 fileId,
    void *buffer,
    u32 length,
    u32 offset,
    GSfsysCallback userCallback,
    u32 userParam1,
    u32 userParam2
) {
    if (!sInitialized) {
        return false;
    }

    GSfsysHandle *fsysHandle = getFsysHandleById(fsysId, false);
    if (fsysHandle == NULL) {
        fillAndFlushBuffer(buffer, 0, length);
        return false;
    }
    
    return readFsysEntryStream(
        fsysHandle,
        fileId,
        buffer,
        length,
        offset,
        userCallback,
        userParam1,
        userParam2
    );
}

/*
 * Not actually sure these are class methods, just needed a
 * way to differentiate them from the functions they wrap.
 */

u32 GSfsysHandle::getEntryIndex(u32 fileId) {
    return GSfsys::getFsysEntryIndex(this, fileId);
}

void GSfsysHandle::setNextState(GSfsysState state) {
    GSfsys::setFsysNextState(this, state);
}
