#pragma once

#include <revolution/types.h>

#include "gs/GSfile.hpp"

#define TOC_ENTRY_FLAG_LOADED (1 << 0)

#define FSYS_FLAG_PERSISTENT (1 << 30)
#define FSYS_FLAG_DEBUG      (1 <<  0)

#define FSYS_ENTRY_FLAG_COMPRESSED       (1 << 31)
#define FSYS_ENTRY_FLAG_27               (1 << 27)
#define FSYS_ENTRY_FLAG_23               (1 << 23)
#define FSYS_ENTRY_FLAG_19               (1 << 19)
#define FSYS_ENTRY_FLAG_18               (1 << 18)
#define FSYS_ENTRY_FLAG_CACHED           (1 << 17)
#define FSYS_ENTRY_FLAG_BUFFER_ALLOCATED (1 << 16)
#define FSYS_ENTRY_FLAG_11               (1 << 11)
#define FSYS_ENTRY_FLAG_FINISHED         (1 <<  3)

struct GSfsysCacheRequest;
struct GSfsysChunk;

typedef void *(*GSfsysFunc1)(u32, u32, u32);
typedef u32 (*GSfsysFunc2)(u32, u32, u32);
typedef void (*GSfsysCallback)(u32, u32, u32);
typedef void (*GSfsysCacheCallback)(GSfsysCacheRequest *);

enum GSfsysRequestType {
    FSYS_REQUEST_NULL       = 0,
    FSYS_REQUEST_LOAD       = 1,
    FSYS_REQUEST_CACHE      = 2, // Appears unused
    FSYS_REQUEST_SEEK_START = 3, // Appears unused
    FSYS_REQUEST_STREAM     = 4,
    FSYS_REQUEST_CANCEL     = 5
};

enum GSfsysLoadStatus {
    FSYS_LOAD_CRITICAL_ERROR = -2,
    FSYS_LOAD_INVALID        = -1,
    FSYS_LOAD_COMPLETE       =  0,
    FSYS_LOAD_IN_PROGRESS    =  1
};

// TODO give these proper names
enum GSfsysState {
    FSYS_STATE_ERROR_INVALIDSTATE = -1000,
    FSYS_STATE_CRITICAL_ERROR = -999,
    FSYS_STATE_ERROR_FILEOPEN = -998,
    FSYS_STATE_ERROR_FILECLOSE = -997,
    FSYS_STATE_ERROR_FILEREAD = -996,
    FSYS_STATE_NEG_995 = -995,
    FSYS_STATE_ERROR_FILESEEK = -994,
    FSYS_STATE_FREE = 0,
    FSYS_STATE_INVALID = 1,
    FSYS_STATE_OPENING = 2,
    FSYS_STATE_READ_SIZE = 3,
    FSYS_STATE_READING = 4,
    FSYS_STATE_BEGIN_REQUEST = 5,
    FSYS_STATE_6 = 6,
    FSYS_STATE_7 = 7,
    FSYS_STATE_SEEK_TO_START = 8,
    FSYS_STATE_9 = 9,
    FSYS_STATE_READ_COMPLETE = 10,
    FSYS_STATE_REQUEST_COMPLETE = 11,
    FSYS_STATE_FINISHED = 12,
    FSYS_STATE_NULL = 0xffff
};

enum GSfsysEntryState {
    FSYS_ENTRY_STATE_BEGIN       = 0,
    FSYS_ENTRY_STATE_READY       = 1,
    FSYS_ENTRY_STATE_STANDBY     = 2,
    FSYS_ENTRY_STATE_READ_ERROR  = 3,
    FSYS_ENTRY_STATE_QUEUE_ERROR = 4,
    FSYS_ENTRY_STATE_YIELD       = 5,
    FSYS_ENTRY_STATE_NULL        = 0xffff
};

struct GStocHeader {
    /* 0x0 */ char mMagic[4]; // GLLA
    u8 unk1[0x4];
    /* 0x8 */ u32 mCount;
    u8 unk2[0x4];
    /* 0x10 */ u32 mTableOffset;
};

// size: 0x10
struct GStocEntry {
    /* 0x0 */ u32 mFsysId;
    /* 0x4 */ char *mName;
    /* 0x8 */ u32 mSize; // size of fsys excluding fsysEntry files
    /* 0xc */ u32 mFlags;
};

// size: 0x20
struct GSfsysHeader {
    /* 0x0 */ char mMagic[4]; // FSYS
    u8 unk1[0x8];
    /* 0xc */ u32 mFileCount;
    /* 0x10 */ u32 mFlags;
    /* 0x14 */ u32 _14;
    u8 unk2[0x4];
    /* 0x1c */ u32 mSize; // size of fsys excluding fsysEntry files
};

// size: 0x60
struct GSfsysHeaderEx : public GSfsysHeader {
    /* 0x20 */ u32 mFullSize; // total size of fsys, including fsysEntry files
    u8 unk3[0x1c];
    /* 0x40 */ u32 mFsysEntryTableOffset;
    /* 0x44 */ u32 mFileNamesOffset;
    /* 0x48 */ u32 mFsysEntryDataOffset;
    u8 unk4[0x14];
};

// size: 0x10
struct GSlzssHeader {
    /* 0x0 */ char mMagic[4]; // LZSS
    /* 0x4 */ u32 mUnpackedSize;
    /* 0x8 */ u32 mPackedSize; // includes header
    /* 0xc */ union {
        /*
         * This field initially contains a CRC-32 checksum,
         * but gets written to with the length of the data
         * (i.e. excluding the header) when decompressing
         */
        u32 mCheckSum;
        u32 mDataSize;
    };
};

struct GSfsysEntry {
    /* 0x0 */ u32 mFileId;
    /* 0x4 */ u32 mDataOffset;
    /* 0x8 */ u32 mUnpackedSize;
    /* 0xc */ u32 mFlags;
    u8 unk1[0x4];
    /* 0x14 */ u32 mPackedSize;
    /* 0x18 */ void *mOutputBuffer;
    /* 0x1c */ u32 mDebugNameOffset;
    /* 0x20 */ int mFileType;
    /* 0x24 */ u32 mNameOffset;
    /* 0x28 */ u32 mReadPosition;
    /* 0x2c */ void *mCachedBuffer;
    /* 0x30 */ GSfsysChunk *mPendingChunks;
    /* 0x34 */ GSfsysChunk *mCompletedChunks;
    /* 0x38 */ GSfileHandle *mFileHandle;
    /* 0x3c */ GSfsysEntryState mState;
    /* 0x40 */ GSfsysEntryState mNextState;
    /* 0x44 */ u32 mRingBufFill;
    /* 0x48 */ u32 mRingBufPos;
    /* 0x4c */ u32 mValidChunks;
    /* 0x50 */ u32 mLoopStart;
    /* 0x54 */ u32 mLoopEnd;
};

// size: 0x48
struct GSfsysHandle {
    /* 0x0 */ u32 mFsysId;
    /* 0x4 */ u32 mCacheEntryIndex;
    /* 0x8 */ u32 mNextFileId;
    /* 0xc */ GSfileHandle *mFileHandle;
    /* 0x10 */ GSfsysRequestType mRequestType;
    /* 0x14 */ GSfsysState mState;
    /* 0x18 */ GSfsysState mNextState;
    /* 0x1c */ GStocEntry *mTocEntry;
    /* 0x20 */ GSfsysHeaderEx *mData;
    /* 0x24 */ u32 mReadingEntryIndex;
    /* 0x28 */ u32 mCopyingEntryIndex;
    /* 0x2c */ bool mCancelRequested;
    /* 0x2d */ bool mPersistent;
    /* 0x2e */ bool mDataLoaded;
    /* 0x30 */ GSfsysCallback mUserCallback;
    /* 0x34 */ u32 _34; // a file ID
    /* 0x38 */ u32 _38;
    /* 0x3c */ u32 mCacheIndex;
    /* 0x40 */ u32 *_40;
    /* 0x44 */ u32 *mFileIdQueue;
    
    u32 getEntryIndex(u32 fileId);
    void setNextState(GSfsysState state);
};

// TODO revisit this "common initial sequence" stuff
struct GSfsysNode {
    /* 0x0 */ GSfsysNode *mPrev;
    /* 0x4 */ GSfsysNode *mNext;
    /* 0x8 */ bool mInUse;
};

// size: 0x44
struct GSfsysEntryHandle {
    /* 0x0 */ GSfsysEntryHandle *mPrev;
    /* 0x4 */ GSfsysEntryHandle *mNext;
    /* 0x8 */ bool mInUse;
    /* 0x9 */ bool mReadComplete;
    /* 0xa */ bool mCompressed;
    /* 0xb */ bool mProcessed;
    /* 0xc */ GSfsysHandle *mFsysHandle;
    /* 0x10 */ GSfsysEntry *mInfo;
    /* 0x14 */ GSlzssHeader mFsysEntry;
    /* 0x24 */ u8 *mRingBuffer;
    /* 0x28 */ u32 mCopyPosition;
    /* 0x2c */ u32 mRingBufferIndex;
    /* 0x30 */ u32 mDataFlags;
    /* 0x34 */ u32 mIterationCount;
    /* 0x38 */ u32 mSourcePosition;
    /* 0x3c */ u32 mWriteIndex;
    /* 0x40 */ u32 mResumeFrom;
};

// size: 0x24
struct GSfsysCacheEntry {
    /* 0x0 */ GSfsysCacheEntry *mPrev;
    /* 0x4 */ GSfsysCacheEntry *mNext;
    /* 0x8 */ bool mInUse;
    /* 0x9 */ bool mPersistent;
    /* 0xa */ bool mPinned;
    /* 0xC */ void *mBuffer;
    /* 0x10 */ u32 mBufSize;
    /* 0x14 */ u32 mFsysCacheIndex;
    /* 0x18 */ u32 mEntryCacheIndex;
    /* 0x1C */ u32 mFsysId;
    /* 0x20 */ u32 mEntryIndex;
};

// size: 0x2c
struct GSfsysCacheRequest {
    /* 0x0 */ GSfsysCacheRequest *mPrev;
    /* 0x4 */ GSfsysCacheRequest *mNext;
    /* 0x8 */ bool mInUse;
    /* 0xC */ GSfsysCacheCallback mCallback;
    /* 0x10 */ GSfsysHandle *mFsysHandle;
    /* 0x14 */ GSfsysEntry *mFsysEntry;
    /* 0x18 */ GSfsysCallback mUserCallback;
    /* 0x1C */ u32 mUserParam1;
    /* 0x20 */ u32 mUserParam2;
    /* 0x24 */ void *mBuffer;
    /* 0x28 */ u32 mLength;
};

// size: 0x28
struct GSfsysRequest {
    /* 0x0 */ GSfsysRequest *mPrev;
    /* 0x4 */ GSfsysRequest *mNext;
    /* 0x8 */ GSfsysRequestType mRequestType;
    /* 0xc */ u32 mFsysId;
    /* 0x10 */ u32 mFileId;
    /* 0x14 */ GSfsysCallback mCallback;
    /* 0x18 */ u32 _18;
    /* 0x1c */ u32 _1c;
    /* 0x20 */ u32 *mFileIds;
    /* 0x24 */ bool mPersistent;
    /* 0x25 */ bool mProcessed;
};

// size: 0x10
struct GSfsysFileTypeHandler {
    /* 0x0 */ s16 _0;
    /* 0x2 */ u16 mFlags;
    /* 0x4 */ u32 mFileType;
    /* 0x8 */ GSfsysFunc1 _8; // background callback
    /* 0xc */ GSfsysFunc2 _C; // foreground callback
};

// size: 0x10
struct GSfsysChunk {
    /* 0x0 */ GSfsysChunk *mPrev;
    /* 0x4 */ GSfsysChunk *mNext;
    /* 0x8 */ u8 *mBuffer;
    /* 0xc */ u32 mOffset;
};

namespace GSfsys {
    extern u32 gFsysChunkSize;
    extern GSfsysFileTypeHandler *gFileTypeHandlerList;
    extern u32 gFileTypeHandlerCount;

    // GSfsysMem.cpp
    void *allocFromFsysDataHeap(u32 size);
    bool freeToFsysDataHeap(void *ptr);
    bool initFsysDataHeap();
    bool initFsysDataBuffer(GSfsysHandle *fsysHandle);
    bool freeFsysDataBuffer(GSfsysHandle *fsysHandle);
    void *getOrCreateCachedBuffer(GSfsysHandle *fsysHandle, u32 entryIndex, u32 size, u32 fsysCacheIndex);
    bool releaseFsysCacheEntry(GSfsysCacheEntry *cacheEntry);
    bool releaseFsysCacheEntryByBuffer(void *buffer);
    bool makeSpaceForCachedBuffer(u32 fsysId, u32 size);
    bool batchEvictFsysCacheEntries(u32 fsysId);
    void *allocCachedBuffer(GSfsysHandle *fsysHandle, u32 entryIndex, u32 length, u32 fsysCacheIndex);
    bool freeCachedBuffer(void *buffer);
    bool releaseFirstCacheEntryForFsys(u32 fsysId);
    void *allocBufferInFileCache(u32 size, u32 fsysId, u32 fileId);

    // GSfsysChunk.cpp
    bool initFsysChunkSystem(u32 heapSize);
    GSfsysChunk *getFreeFsysChunk();
    bool popChunkFromList(GSfsysChunk **list, bool fromFront);
    void clearChunkList(GSfsysChunk **list);
    void prependToChunkList(GSfsysChunk **list, GSfsysChunk *chunk);
    void transferChunkListTail(GSfsysChunk **srcList, GSfsysChunk **dstList);

    // GSfsysCache.cpp
    void addToCacheRequestList(GSfsysCacheRequest *cacheRequest);
    GSfsysCacheRequest *getFreeCacheRequest();
    void removeFromCacheRequestList(GSfsysCacheRequest *cacheRequest);
    void addToCacheEntryList(GSfsysCacheEntry *cacheEntry);
    GSfsysCacheEntry *createFsysCacheEntry(u32 fsysId, u32 entryIndex, bool persistent, bool pinned, u32 fsysCacheIndex);
    void removeFromCacheEntryList(GSfsysCacheEntry *cacheEntry);
    GSfsysCacheEntry *findFsysCacheEntry(u32 fsysId, u32 entryIndex);
    GSfsysCacheEntry *findFirstCacheEntryForFsys(u32 fsysId);
    GSfsysCacheEntry *findFsysCacheEntryByBuffer(void *buffer);
    GSfsysCacheEntry *selectCacheEvictionVictim(u32 fsysId, bool ignoreCacheOrder);
    void setFsysCacheEntryPinned(u32 fsysId, u32 entryIndex, bool pinned);
    void setFsysCacheEntriesPinned(u32 fsysId, bool pinned);
    bool initFsysCacheHeap();
    bool isLessThanEqualToCacheHeapSize(u32 size);
    void *allocFromFsysCacheHeap(u32 size);
    void freeToFsysCacheHeap(void *ptr, u32 size);
    u32 getFsysCacheHeapFreeSize();
    bool initFsysCacheSystem(u32 heapSize, u32 nCacheEntries);
    u32 getNextCacheFsysIndex();
    bool isFsysEntryCached(u32 fsysId, u32 entryIndex);
    bool doFsysCacheRead(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry, void *buffer, u32 length, u32 offset, GSfsysCacheCallback callback, GSfsysCallback param7, u32 param8, u32 param9);
    bool fsysCacheRead(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry, void *buffer, u32 length, u32 offset, GSfsysCacheCallback callback);
    bool fsysCacheReadEx(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry, void *buffer, u32 length, u32 offset, GSfsysCacheCallback callback, GSfsysCallback userCallback, u32 userParam1, u32 userParam2);
    void copyToCachedBuffer(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry, void *src, void *dst, u32 length, u32 offset, GSfsysCacheCallback callback);

    // GSfsysRead.cpp
    void seekFsysCallback(s32 result, GSfileHandle *fileHandle);
    GSfsysFileTypeHandler *getHandlerForFileType(u32 fileType);
    bool queueFsysEntryForCopying(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry);
    bool queueNextFsysEntryForCopying(GSfsysHandle *fsysHandle);
    bool findFirstUnchachedFsysEntry(GSfsysHandle *fsysHandle);
    GSfsysHeaderEx *getFsysData(GSfsysHandle *fsysHandle);
    GSfsysEntry *getFsysEntry(GSfsysHandle *fsysHandle, u32 index);
    void handleFsysChunkReady(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry);
    void finalizeFsysChunk(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry);
    void fsysChunkCopyCallback(GSfsysCacheRequest *cacheRequest);
    u32 getChunkSize(u32 totalSize, u32 currentPos);
    void directFsysEntryReadCallback(s32 result, GSfileHandle *fileHandle);
    void cachedFsysEntryReadCallback(GSfsysCacheRequest *cacheRequest);
    bool readNextFsysEntryChunk(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry);
    bool beginReadNextFsysEntry(GSfsysHandle *fsysHandle);
    void handleFsysDataReady(GSfsysHandle *fsysHandle);
    void directFsysReadCallback(s32 result, GSfileHandle *fileHandle);
    void cachedFsysReadCallback(GSfsysCacheRequest *param1);
    bool readFsys(GSfsysHandle *fsysHandle, GSfsysEntry *fsysEntry, bool buffered, u32 param4, void *buffer, u32 length, u32 offset, GSdvdCallback callback, GSfsysCacheCallback param9);
    void readFsysData(GSfsysHandle *fsysHandle);
    void seekFsysToStart(GSfsysHandle *fsysHandle);

    // GSfsysStream.cpp
    u32 getStreamBufferSize();
    u32 getHalfStreamBufferSize();
    u32 getStreamChunkSize();
    void freeStreamedFsysBuffers(GSfsysHandle *fsysHandle);
    void streamedFsysReadCallback(GSfsysCacheRequest *cacheRequest);
    bool readFsysEntryStream(GSfsysHandle *fsysHandle, u32 fileId, void *buffer, u32 length, u32 offset, GSfsysCallback userCallback, u32 userParam1, u32 userParam2);
    u32 getStreamChunkFlag(u32 offset);

    // GSfsys.cpp
    void *allocAligned32(u32 size);
    bool loadToc();
    GSfsysHandle *getAssociatedFsysHandle(GSfileHandle *fileHandle);
    GSfsysHandle *getFsysHandleById(u32 fsysId, bool param2);
    GSfsysHandle *getAvailableFsysHandle(bool ignoreLoaded);
    GSfsysHandle *getOrStealFsysHandle();
    void appendNodeToList(GSfsysNode *node, GSfsysNode **list);
    void removeNodeFromList(GSfsysNode *node, GSfsysNode **list);
    GSfsysEntryHandle *getFreeFsysEntryHandle();
    void enqueueFsysEntry(GSfsysEntryHandle *fsysEntryHandle);
    void dequeueFsysEntry(GSfsysEntryHandle *fsysEntryHandle);
    GStocEntry *getTocEntry(u32 fsysId);
    void setFsysNextState(GSfsysHandle *fsysHandle, GSfsysState state);
    void setFsysEntryNextState(GSfsysEntry *fsysEntry, GSfsysEntryState state);
    bool getFsysPath(GSfsysHandle *fsysHandle, char *outPath);
    bool openFsys(GSfsysHandle *fsysHandle);
    bool closeFsys(GSfsysHandle *fsysHandle, bool skipCallback);
    u32 countActiveRequestsOfType(GSfsysRequestType requestType);
    bool doFsysEntryState(GSfsysHandle *fsysHandle, u32 entryIndex);
    u32 getFsysEntryIndex(GSfsysHandle *fsysHandle, u32 fileId);
    bool checkAllFsysEntriesReady(GSfsysHandle *fsysHandle);
    void setTocEntryFlags(u32 fsysId, u32 flags);
    void clearTocEntryFlags(u32 fsysId, u32 flags);
    void readFsysSizeCallback(s32 result, GSfileHandle *fileHandle);
    void doFsysState(GSfsysHandle *fsysHandle);
    void foregroundTaskCallback(u32 taskId, u32 userParam);
    bool processMidCopyCancel(GSfsysEntryHandle *fsysEntryHandle);
    void fillAndFlushBuffer(void *buffer, u8 value, u32 length);
    void decompressLzss(GSfsysEntryHandle *fsysEntryHandle);
    void readUncompressedFile(GSfsysEntryHandle *fsysEntryHandle, bool param2);
    void backgroundTaskCallback(u32 taskId, u32 userParam);
    bool initSubroutine(u32 chunkHeapSize, u32 cacheHeapSize, u32 nCacheEntries);
    void setFileTypeHandlers(GSfsysFileTypeHandler *param1);
    s32 getFsysLoadStatus(u32 fsysId);
    void invalidateFsysHandle(u32 fsysId);
    bool beginLoadFsys(u32 fsysId, u32 fileId, GSfsysRequestType requestType, bool param4, GSfsysCallback onCloseCallback, u32 param6, u32 param7, u32 *param8);
    GSfsysRequest *createFsysRequest(GSfsysRequestType requestType, u32 fsysId, u32 param3, bool param4, GSfsysCallback param5, u32 param6, u32 param7, u32 *param8);
    GSfsysRequest *findFsysRequest(u32 fsysId, u32 param2);
    bool enqueueFsysRequest(GSfsysRequest *request, u32 param2);
    void dequeueFsysRequest(GSfsysRequest *request);
    bool processFsysRequest(GSfsysRequest *request);
    void processNextFsysRequest();
    bool submitFsysRequest(GSfsysRequestType requestType, u32 fsysId, u32 param3, bool param4, GSfsysCallback param5, u32 param6, u32 param7, s32 param8, u32 *param9);
    bool requestLoadFsys(u32 fsysId);
    bool startOrResetFsysStream(u32 fsysId, u32 param2, u32 param3);
    bool streamFsys(u32 fsysId);
    bool waitForFsysLoad(u32 fsysId, bool param2);
    bool loadFsys(u32 fsysId);
    bool cancelFsysLoad(u32 fsysId);
    bool cancelFsysLoadBlocking(u32 fsysId);
    bool requestLoadFsysEntry(u32 fsysId, u32 param2);
    bool requestLoadFsysEntryEx(u32 fsysId, u32 param2, GSfsysCallback param3, u32 param4, u32 param5);
    bool requestLoadFsysEntries(u32 fsysId, u32 *param2, GSfsysCallback param3, u32 param4, u32 param5);
    bool loadFsysEntry(u32 fsysId, u32 param2);
    void fn_80249890(u32 fsysId);
    void releaseAllCacheEntriesForFsys(u32 fsysId);
    void init(u32 nFileHandles, u32 chunkHeapSize, u32 cacheHeapSize, u32 nCacheEntries);
    bool fn_802499E4();
    bool fn_802499EC(u32 fsysId);
    void *fn_80249A28(u32 fsysId, u32 fileId, u32 size);
    void *fn_80249A44(u32 fsysId, u32 fileId, u32 size);
    u32 fn_80249AA8();
    bool readFsysStream(u32 fsysId, u32 param2, void *param3, u32 param4, u32 param5, GSfsysCallback param6, u32 param7, u32 param8);
};
