#include "version.hpp"

#include <cstring>

#include <revolution/dvd.h>
#include <revolution/nand.h>
#include <revolution/os.h>

#include "gs/GSdebug.hpp"
#include "gs/GSfile.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSnand.hpp"
#include "gs/GStask.hpp"
#include "gs/GSthread.hpp"

extern MEMHeapHandle lbl_8063E8EC;

/* lbl_804917F0 */ static u8 sUnused[0x40];
/* lbl_80491830 */ static OSSemaphore sDvdSemaphore;
/* lbl_80491840 */ static DVDCommandBlock sDiskCheckBlock;

/* lbl_8063D6D0 */ static char gameid[] = "RPBE";
/* lbl_8063D6D8 */ static char *sGameID = gameid;
/* lbl_8063D6DC */ static char company[] = "01";
/* lbl_8063D6E0 */ static char *sCompanyID = company;

/* lbl_8063F31E */ static bool sInitialized;
/* lbl_8063F31F */ static bool sAsyncCallbacksDisabled;
/* lbl_8063F320 */ static u32 sFileHandleCount;
/* lbl_8063F324 */ static GSfileHandle *sFileHandlePool;
/* lbl_8063F328 */ static GSdvdErrorState sDvdErrorState;
/* lbl_8063F32C */ static u32 sDvdErrorTaskID;
/* lbl_8063F330 */ static GSdvdErrorCallback sDvdErrorCallback;
/* lbl_8063F334 */ static GSdvdErrorHandledCallback sDvdErrorHandledCallback;
/* lbl_8063F338 */ static GSnandManager *sNandManager;

void *GSfile::allocAligned32(u32 size) {
    return GSmem::allocFromHeapAligned(lbl_8063E8EC, size, 0x20);
}

void GSfile::initFileHandles() {
    for (u32 i = 0; i < sFileHandleCount; i++) {
        sFileHandlePool[i].mInUse = false;
    }
}

GSfileHandle *GSfile::getFreeFileHandle() {
    BOOL intEnabled = OSDisableInterrupts();

    GSfileHandle *fileHandle = NULL;

    for (u32 i = 0; i < sFileHandleCount; i++) {
        if (sFileHandlePool[i].mInUse != true) {
            sFileHandlePool[i].mInUse = true;
            sFileHandlePool[i].mIsNandFile = false;
            fileHandle = &sFileHandlePool[i];
            break;
        }
    }

    OSRestoreInterrupts(intEnabled);

    return fileHandle;
}

void GSfile::releaseFileHandle(GSfileHandle *fileHandle) {
    BOOL intEnabled = OSDisableInterrupts();
    fileHandle->mInUse = false;
    OSRestoreInterrupts(intEnabled);
}

GSfileHandle *GSfile::getHandleFromFileInfo(DVDFileInfo *fileInfo) {
    for (u32 i = 0; i < sFileHandleCount; i++) {
        if (sFileHandlePool[i].mInUse && &sFileHandlePool[i].mFileInfo == fileInfo) {
            return &sFileHandlePool[i];
        }
    }
    return NULL;
}

void GSfile::readAsyncCallback(s32 result, DVDFileInfo *fileInfo) {
    if (sAsyncCallbacksDisabled) {
        return;
    }

    GSfileHandle *fileHandle = getHandleFromFileInfo(fileInfo);
    if (fileHandle == NULL) {
        return;
    }

    if (fileHandle->mCallback == NULL) {
        return;
    }

    DCInvalidateRange(fileHandle->mBuffer, fileHandle->mBufSize);

    fileHandle->mCallback(result, fileHandle);
}

void GSfile::seekAsyncCallback(s32 result, DVDFileInfo *fileInfo) {
    if (sAsyncCallbacksDisabled) {
        return;
    }

    GSfileHandle *fileHandle = getHandleFromFileInfo(fileInfo);
    if (fileHandle == NULL) {
        return;
    }

    if (fileHandle->mCallback == NULL) {
        return;
    }

    fileHandle->mCallback(result, fileHandle);
}

bool GSfile::init(u32 nFileHandles, bool patchDiskID) {
    if (sInitialized == true) {
        return false;
    }

    sAsyncCallbacksDisabled = false;
    sNandManager = NULL;

    NANDInit();

    if (sNandManager == NULL) {
        sNandManager = new GSnandManager();
    }

    sFileHandleCount = nFileHandles;
    sFileHandlePool = (GSfileHandle *)allocAligned32(nFileHandles * sizeof(GSfileHandle));
    if (sFileHandlePool == NULL) {
        return false;
    }
    initFileHandles();

    // This is the only reference to this variable
    memset(sUnused, 0, sizeof(sUnused));

    DVDInit();

    if (patchDiskID) {
        switch (GSdebug::getRegionOverride()) {
            case REGION_OVERRIDE_DEFAULT:
                sGameID = "RPBE";
                break;
            
            case REGION_OVERRIDE_USA:
                sGameID = "RPBE";
                break;
            
            case REGION_OVERRIDE_PAL:
                sGameID = "RPBP";
                break;
        }

        DVDDiskID *diskID = DVDGetCurrentDiskID();
        diskID->gameName[0] = sGameID[0];
        diskID->gameName[1] = sGameID[1];
        diskID->gameName[2] = sGameID[2];
        diskID->gameName[3] = sGameID[3];
        diskID->company[0] = sCompanyID[0];
        diskID->company[1] = sCompanyID[1];
        diskID->diskNumber = 0;
        diskID->gameVersion = 0;
    }

    DVDSetAutoFatalMessaging(FALSE);

    sDvdErrorTaskID = GStask::createTask(TASK_TYPE_MAIN, 19, 0, errorTaskCallback);
    GStask::setTaskName(sDvdErrorTaskID, "GSdvdErrorTask");

    sInitialized = 1;

    return true;
}

void GSfile::waitForDvdErrorClear() {
    BOOL intEnabled = OSDisableInterrupts();
    OSRestoreInterrupts(intEnabled);

    if (!intEnabled) {
        return;
    }

    while (true) {
        errorTaskCallback(sDvdErrorTaskID, 0);

        if (sDvdErrorState == DVD_ERROR_STATE_OK) {
            break;
        }

        if (!GSthreadManager::sInstance->isCurrentThreadManaged()) {
            break;
        }

        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

GSfileHandle *GSfile::openFile(char *fileName) {
    if (sInitialized == false) {
        return NULL;
    }

    waitForDvdErrorClear();

    GSfileHandle *fileHandle = getFreeFileHandle();
    if (fileHandle == NULL) {
        return NULL;
    }

    if (sNandManager != NULL) {
        if (sNandManager->openFile(fileName, fileHandle)) {
            return fileHandle;
        }
    }

    if (!DVDOpen(fileName, &fileHandle->mFileInfo)) {
        releaseFileHandle(fileHandle);
        return NULL;
    }

    return fileHandle;
}

bool GSfile::fileExists(char *fileName) {
    if (sInitialized == false) {
        return false;
    }

    if (sNandManager != NULL) {
        if (sNandManager->fileExists(fileName)) {
            return true;
        }
    }

    if (DVDConvertPathToEntrynum(fileName) == -1) {
        return false;
    }

    return true;
}

s32 GSfile::readFile(
    GSfileHandle *fileHandle,
    void *buffer,
    u32 length,
    u32 offset
) {
    if (sInitialized == false) {
        return -1;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return -1;
    }
    if ((u32)buffer % 0x20 != 0) {
        return -1;
    }
    if (length % 0x20 != 0) {
        return -1;
    }
    if (offset % 4 != 0) {
        return -1;
    }

    if (sNandManager != NULL && fileHandle->mIsNandFile) {
        s32 nBytesRead = sNandManager->readFile(fileHandle, buffer, length, offset);
        if (nBytesRead > 0) {
            return nBytesRead;
        }
    }

    return DVDReadPrio(&fileHandle->mFileInfo, buffer, length, offset, 2);
}

// read file async
bool GSfile::readFileAsync(
    GSfileHandle *fileHandle,
    void *buffer,
    u32 length,
    u32 offset,
    GSdvdCallback callback
) {
    if (sInitialized == false) {
        return false;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return false;
    }

    fileHandle->mCallback = callback;

    if ((u32)buffer % 0x20 != 0) {
        return false;
    }
    if (length % 0x20 != 0) {
        return false;
    }
    if (offset % 4 != 0) {
        return false;
    }

    fileHandle->mBuffer = buffer;
    fileHandle->mBufSize = length;

    if (sNandManager != NULL && fileHandle->mIsNandFile) {
        if (sNandManager->readFileAsync(fileHandle, buffer, length, offset)) {
            return true;
        }
    }

    return DVDReadAsyncPrio(&fileHandle->mFileInfo, buffer, length, offset, readAsyncCallback, 2);
}

s32 GSfile::readFilePrio(
    GSfileHandle *fileHandle,
    void *buffer,
    u32 length,
    u32 offset,
    s32 priority
) {
    if (sInitialized == false) {
        return -1;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return -1;
    }
    if ((u32)buffer % 0x20 != 0) {
        return -1;
    }
    if (length % 0x20 != 0) {
        return -1;
    }
    if (offset % 4 != 0) {
        return -1;
    }
    if (priority < 0 || priority > 3) {
        return -1;
    }

    return DVDReadPrio(&fileHandle->mFileInfo, buffer, length, offset, priority);
}

u32 GSfile::closeFile(GSfileHandle *fileHandle) {
    if (sInitialized == false) {
        return false;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return false;
    }
    
    if (sNandManager != NULL) {
        if (sNandManager->closeFile(fileHandle)) {
            releaseFileHandle(fileHandle);
            return true;
        }
    }

    BOOL success = DVDClose(&fileHandle->mFileInfo);
    releaseFileHandle(fileHandle);

    return success;
}

u32 GSfile::getFileLength(GSfileHandle *fileHandle) {
    if (sInitialized == false) {
        return 0;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return 0;
    }

    if (sNandManager != NULL) {
        u32 length;
        if (sNandManager->getFileLength(fileHandle, &length)) {
            return length;
        }
    }

    return fileHandle->mFileInfo.length;
}

s32 GSfile::getDriveStatus() {
    // Does not match with !sInitialized
    if (sInitialized == false) {
        return DVD_STATE_FATAL_ERROR;
    }

    return DVDGetDriveStatus();
}

bool GSfile::seekAsync(GSfileHandle *fileHandle, s32 offset, GSdvdCallback callback) {
    if (sInitialized == false) {
        return false;
    }

    waitForDvdErrorClear();

    if (fileHandle == NULL) {
        return false;
    }

    fileHandle->mCallback = callback;
    return DVDSeekAsyncPrio(&fileHandle->mFileInfo, offset, seekAsyncCallback, 2);
}

void GSfile::updateErrorState(s32 dvdState) {
    switch (dvdState) {
        case DVD_STATE_FATAL_ERROR:
            sDvdErrorState = DVD_ERROR_STATE_FATAL_ERROR;
            break;
        
        case DVD_STATE_COVER_OPEN:
            sDvdErrorState = DVD_ERROR_STATE_COVER_OPEN;
            break;
        
        case DVD_STATE_NO_DISK:
            sDvdErrorState = DVD_ERROR_STATE_NO_DISK;
            break;
        
        case DVD_STATE_WRONG_DISK:
            sDvdErrorState = DVD_ERROR_STATE_WRONG_DISK;
            break;
        
        case DVD_STATE_RETRY:
            sDvdErrorState = DVD_ERROR_STATE_RETRY;
            break;
        
        default:
            break;
    }
}

void GSfile::notifyError(GSdvdError error) {
    if (sDvdErrorCallback != NULL) {
        sDvdErrorCallback(error);
    }
}

void GSfile::notifyErrorHandled() {
    if (sDvdErrorHandledCallback != NULL) {
        sDvdErrorHandledCallback();
    }
}

// Comes after "RPBE"/"RPBP" strings in .sdata
/* lbl_8063D6F4 */ static s32 gDiscCheckResult = -1;

void GSfile::checkDiskCallback(s32 result, DVDCommandBlock *block) {
    gDiscCheckResult = result;
    OSSignalSemaphore(&sDvdSemaphore);
}

bool GSfile::checkDisk() {
    BOOL intEnabled = OSDisableInterrupts();
    OSRestoreInterrupts(intEnabled);

    if (!intEnabled) {
        return true;
    }

    OSInitSemaphore(&sDvdSemaphore, 0);

    gDiscCheckResult = -1;

    if (!DVDCheckDiskAsync(&sDiskCheckBlock, checkDiskCallback)) {
        gDiscCheckResult = 0;
    }

    if (gDiscCheckResult < 0) {
        OSWaitSemaphore(&sDvdSemaphore);
    }

    return gDiscCheckResult != 0;
}

void GSfile::errorTaskCallback(u32 taskID, u32 userParam) {
    s32 dvdState = getDriveStatus();

    switch (sDvdErrorState) {
        case DVD_ERROR_STATE_OK:
            updateErrorState(dvdState);
            break;
        
        case DVD_ERROR_STATE_COVER_OPEN:
            notifyError(DVD_ERROR_COVER_OPEN);
            sDvdErrorState = DVD_ERROR_STATE_WAIT_COVER_CLOSE;
            break;
        
        case DVD_ERROR_STATE_WAIT_COVER_CLOSE:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                sDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_COVER_OPEN && checkDisk()) {
                notifyErrorHandled();
                sDvdErrorState = DVD_ERROR_STATE_OK;
            }
            break;
        
        case DVD_ERROR_STATE_NO_DISK:
            notifyError(DVD_ERROR_NO_DISK);
            sDvdErrorState = DVD_ERROR_STATE_WAIT_DISK_INSERT;
            break;
        
        case DVD_ERROR_STATE_WAIT_DISK_INSERT:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                sDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_NO_DISK && checkDisk()) {
                notifyErrorHandled();
                sDvdErrorState = DVD_ERROR_STATE_OK;
            }
            break;
        
        case DVD_ERROR_STATE_WRONG_DISK:
            notifyError(DVD_ERROR_WRONG_DISK);
            sDvdErrorState = DVD_ERROR_STATE_WAIT_CORRECT_DISK;
            break;
        
        case DVD_ERROR_STATE_WAIT_CORRECT_DISK:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                sDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_WRONG_DISK && checkDisk()) {
                notifyErrorHandled();
                sDvdErrorState = DVD_ERROR_STATE_OK;
            }
            break;
        
        case DVD_ERROR_STATE_RETRY:
            notifyError(DVD_ERROR_RETRY);
            sDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            break;
        
        case DVD_ERROR_STATE_WAIT_RETRY:
            if (dvdState == DVD_STATE_COVER_OPEN) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_COVER_OPEN);
                sDvdErrorState = DVD_ERROR_STATE_WAIT_COVER_CLOSE;
            }
            else if (dvdState == DVD_STATE_NO_DISK) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_NO_DISK);
                sDvdErrorState = DVD_ERROR_STATE_WAIT_DISK_INSERT;
            }
            // Not sure why DVD_STATE_NO_DISK and DVD_STATE_COVER_OPEN are checked here
            else if ((dvdState != DVD_STATE_RETRY && checkDisk()) || (dvdState == DVD_STATE_NO_DISK || dvdState == DVD_STATE_COVER_OPEN)) {
                notifyErrorHandled();
                sDvdErrorState = DVD_ERROR_STATE_OK;
            }
            break;
        
        case DVD_ERROR_STATE_FATAL_ERROR:
            notifyError(DVD_ERROR_FATAL);
            sDvdErrorState = DVD_ERROR_STATE_FATAL_ERROR_DONE;
            break;
        
        case DVD_ERROR_STATE_FATAL_ERROR_DONE:
            break;
    }
}

void *GSfile::loadFile(char *fileName, u32 *outLength) {
    if (!fileExists(fileName)) {
        return NULL;
    }

    GSfileHandle *fileHandle = openFile(fileName);
    if (fileHandle == NULL) {
        return NULL;
    }

    u32 length = (getFileLength(fileHandle) + 0x1f) / 0x20 * 0x20;
    if (length == 0) {
        return NULL;
    }

    void *buffer = GSmem::allocFromDefaultHeap(length);
    if (buffer == NULL) {
        return NULL;
    }

    u32 read = readFile(fileHandle, buffer, length, 0);
    if (read != length) {
        GSmem::freeDefaultHeapBlock(buffer);
        return NULL;
    }

    closeFile(fileHandle);

    if (outLength != NULL) {
        *outLength = length;
    }

    return buffer;
}

void *GSfile::loadFileOnHeap(char *fileName, MEMHeapHandle heap, u32 *pLength) {
    if (!fileExists(fileName)) {
        return NULL;
    }

    GSfileHandle *fileHandle = openFile(fileName);
    if (fileHandle == NULL) {
        return NULL;
    }

    u32 length = (getFileLength(fileHandle) + 0x1f) / 0x20 * 0x20;
    if (length == 0) {
        return NULL;
    }

    void *buffer = GSmem::allocFromHeap(heap, length);
    if (buffer == NULL) {
        return NULL;
    }

    u32 read = readFile(fileHandle, buffer, length, 0);
    if (read != length) {
        GSmem::freeHeapBlock(heap, buffer);
        return NULL;
    }

    closeFile(fileHandle);

    if (pLength != NULL) {
        *pLength = length;
    }

    return buffer;
}

bool GSfile::copyFileToNand(char *fileName) {
    if (sNandManager != NULL) {
        return sNandManager->copyFile(fileName, false);
    }
    return false;
}

void GSfile::setErrorCallbacks(
    GSdvdErrorCallback errorCallback,
    GSdvdErrorHandledCallback errorHandledCallback
) {
    sDvdErrorCallback = errorCallback;
    sDvdErrorHandledCallback = errorHandledCallback;
}

GSdvdError GSfile::getCurrentError() {
    switch (sDvdErrorState) {
        case DVD_ERROR_STATE_COVER_OPEN:
        case DVD_ERROR_STATE_WAIT_COVER_CLOSE:
            return DVD_ERROR_COVER_OPEN;
        
        case DVD_ERROR_STATE_NO_DISK:
        case DVD_ERROR_STATE_WAIT_DISK_INSERT:
            return DVD_ERROR_NO_DISK;
        
        case DVD_ERROR_STATE_WRONG_DISK:
        case DVD_ERROR_STATE_WAIT_CORRECT_DISK:
            return DVD_ERROR_WRONG_DISK;
        
        case DVD_ERROR_STATE_RETRY:
        case DVD_ERROR_STATE_WAIT_RETRY:
            return DVD_ERROR_RETRY;
        
        case DVD_ERROR_STATE_FATAL_ERROR:
        case DVD_ERROR_STATE_FATAL_ERROR_DONE:
            return DVD_ERROR_FATAL;

        case DVD_ERROR_STATE_OK:
        default:
            return DVD_ERROR_OK;
    }
}

void GSfile::disableAsyncCallbacks() {
    sAsyncCallbacksDisabled = true;
}

bool GSfile::getAsyncCallbacksDisabled() {
    return sAsyncCallbacksDisabled;
}
