#pragma once

#include <revolution/types.h>
#include <revolution/dvd.h>

#include "gs/GSmem.hpp"

enum GSdvdError {
    DVD_ERROR_OK            = 0,
    DVD_ERROR_COVER_OPEN    = 1,
    DVD_ERROR_NO_DISK       = 2,
    DVD_ERROR_WRONG_DISK    = 3,
    DVD_ERROR_RETRY         = 4,
    DVD_ERROR_FATAL         = 5
};

enum GSdvdErrorState {
    DVD_ERROR_STATE_OK                  = 0,
    DVD_ERROR_STATE_COVER_OPEN          = 1,
    DVD_ERROR_STATE_WAIT_COVER_CLOSE    = 2,
    DVD_ERROR_STATE_NO_DISK             = 3,
    DVD_ERROR_STATE_WAIT_DISK_INSERT    = 4,
    DVD_ERROR_STATE_WRONG_DISK          = 5,
    DVD_ERROR_STATE_WAIT_CORRECT_DISK   = 6,
    DVD_ERROR_STATE_RETRY               = 7,
    DVD_ERROR_STATE_WAIT_RETRY          = 8,
    DVD_ERROR_STATE_FATAL_ERROR         = 9,
    DVD_ERROR_STATE_FATAL_ERROR_DONE    = 10
};

struct GSfileHandle;
struct GSnandFileHandle;

typedef void (*GSdvdCallback)(s32, GSfileHandle *);
typedef void (*GSdvdErrorCallback)(GSdvdError);
typedef void (*GSdvdErrorHandledCallback)();

// size: 0x50
struct GSfileHandle {
    /* 0x0 */ bool mInUse;
    /* 0x1 */ bool mIsNandFile;
    /* 0x4 */ DVDFileInfo mFileInfo;
    /* 0x40 */ GSnandFileHandle *mNandFileHandle;
    /* 0x44 */ GSdvdCallback mCallback;
    /* 0x48 */ void *mBuffer;
    /* 0x4c */ u32 mBufSize;
};

namespace GSfile {
    void *allocAligned32(u32 size) NO_INLINE;
    void initFileHandles() NO_INLINE;
    GSfileHandle *getFreeFileHandle() NO_INLINE;
    void releaseFileHandle(GSfileHandle *fileHandle) NO_INLINE;
    GSfileHandle *getHandleFromFileInfo(DVDFileInfo *fileInfo) NO_INLINE;
    void readAsyncCallback(s32 result, DVDFileInfo *fileInfo);
    void seekAsyncCallback(s32 result, DVDFileInfo *fileInfo);
    bool init(u32 nFileHandles, bool patchDiskID);
    void waitForDvdErrorClear() NO_INLINE;
    GSfileHandle *openFile(char *fileName) NO_INLINE;
    bool fileExists(char *fileName) NO_INLINE;
    s32 readFile(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset);
    bool readFileAsync(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset, GSdvdCallback callback);
    s32 readFilePrio(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset, s32 priority);
    u32 closeFile(GSfileHandle *fileHandle) NO_INLINE;
    u32 getFileLength(GSfileHandle *fileHandle) NO_INLINE;
    s32 getDriveStatus() NO_INLINE;
    bool seekAsync(GSfileHandle *fileHandle, s32 offset, GSdvdCallback callback);
    void updateErrorState(s32 dvdState) NO_INLINE;
    void notifyError(GSdvdError error) NO_INLINE;
    void notifyErrorHandled() NO_INLINE;
    void checkDiskCallback(s32 result, DVDCommandBlock *block);
    bool checkDisk() NO_INLINE;
    void errorTaskCallback(u32 taskID, u32 userParam);
    void *loadFile(char *fileName, u32 *outLength);
    void *loadFileOnHeap(char *fileName, MEMHeapHandle heap, u32 *outLength);
    bool copyFileToNand(char *fileName);
    void setErrorCallbacks(GSdvdErrorCallback errorCallback, GSdvdErrorHandledCallback errorHandledCallback);
    GSdvdError getCurrentError();
    void disableAsyncCallbacks();
    bool getAsyncCallbacksDisabled();
};
