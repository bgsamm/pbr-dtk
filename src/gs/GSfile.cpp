#include <version.hpp>

#include <cstring>

#include <revolution/dvd.h>
#include <revolution/nand.h>
#include <revolution/os.h>

#include "gs/GSfile.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSnand.hpp"
#include "gs/GStask.hpp"

extern GSheapHandle lbl_8063E8EC;
extern u32 lbl_8063F600; // static instance?

extern void fn_80224588(u32);
extern u32 fn_802245C4(u32);
extern int fn_80249BC8(); // gets region (e.g. PAL)?

/* lbl_804917F0 */ static u8 gUnused[0x40];
/* lbl_80491830 */ static OSSemaphore gDvdSemaphore;
/* lbl_80491840 */ static DVDCommandBlock gDiskCheckBlock;

/* lbl_8063D6D0 */ static char gameid[] = "RPBE";
/* lbl_8063D6D8 */ static char *gGameID = gameid;
/* lbl_8063D6DC */ static char company[] = "01";
/* lbl_8063D6E0 */ static char *gCompanyID = company;

/* lbl_8063F31E */ static bool gInitialized;
/* lbl_8063F31F */ static bool gAsyncCallbacksDisabled;
/* lbl_8063F320 */ static u32 gFileHandleCount;
/* lbl_8063F324 */ static GSfileHandle *gFileHandlePool;
/* lbl_8063F328 */ static GSdvdErrorState gDvdErrorState;
/* lbl_8063F32C */ static u32 gDvdErrorTaskID;
/* lbl_8063F330 */ static GSdvdErrorCallback gDvdErrorCallback;
/* lbl_8063F334 */ static GSdvdErrorHandledCallback gDvdErrorHandledCallback;
/* lbl_8063F338 */ static GSnandManager *gNandManager;

void *GSfile::allocAligned32(u32 size) {
    return GSmem::allocFromHeapAligned(lbl_8063E8EC, size, 0x20);
}

void GSfile::initFileHandles() {
    for (u32 i = 0; i < gFileHandleCount; i++) {
        gFileHandlePool[i].mInUse = false;
    }
}

GSfileHandle *GSfile::getFreeFileHandle() {
    BOOL intEnabled = OSDisableInterrupts();

    GSfileHandle *fileHandle = NULL;

    for (u32 i = 0; i < gFileHandleCount; i++) {
        if (gFileHandlePool[i].mInUse != true) {
            gFileHandlePool[i].mInUse = true;
            gFileHandlePool[i].mIsNandFile = false;
            fileHandle = &gFileHandlePool[i];
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
    for (u32 i = 0; i < gFileHandleCount; i++) {
        if (gFileHandlePool[i].mInUse && &gFileHandlePool[i].mFileInfo == fileInfo) {
            return &gFileHandlePool[i];
        }
    }
    return NULL;
}

void GSfile::readAsyncCallback(s32 result, DVDFileInfo *fileInfo) {
    if (gAsyncCallbacksDisabled) {
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
    if (gAsyncCallbacksDisabled) {
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
    if (gInitialized == true) {
        return false;
    }

    gAsyncCallbacksDisabled = false;
    gNandManager = NULL;

    NANDInit();

    if (gNandManager == NULL) {
        gNandManager = new GSnandManager();
    }

    gFileHandleCount = nFileHandles;
    gFileHandlePool = (GSfileHandle *)allocAligned32(nFileHandles * sizeof(GSfileHandle));
    if (gFileHandlePool == NULL) {
        return false;
    }
    initFileHandles();

    // This is the only reference to this variable
    memset(gUnused, 0, sizeof(gUnused));

    DVDInit();

    if (patchDiskID) {
        switch (fn_80249BC8()) {
            case 0:
                gGameID = "RPBE";
                break;
            
            case 1:
                gGameID = "RPBE";
                break;
            
            case 2:
                gGameID = "RPBP";
                break;
        }

        DVDDiskID *diskID = DVDGetCurrentDiskID();
        diskID->gameName[0] = gGameID[0];
        diskID->gameName[1] = gGameID[1];
        diskID->gameName[2] = gGameID[2];
        diskID->gameName[3] = gGameID[3];
        diskID->company[0] = gCompanyID[0];
        diskID->company[1] = gCompanyID[1];
        diskID->diskNumber = 0;
        diskID->gameVersion = 0;
    }

    DVDSetAutoFatalMessaging(FALSE);

    gDvdErrorTaskID = GStask::createTask(TASK_TYPE_1, 19, 0, errorTaskCallback);
    GStask::setTaskName(gDvdErrorTaskID, "GSdvdErrorTask");

    gInitialized = 1;

    return true;
}

// TODO name once fn_802245C4 & fn_80224588 understood
void GSfile::fn_801DC264() {
    BOOL intEnabled = OSDisableInterrupts();
    OSRestoreInterrupts(intEnabled);

    if (!intEnabled) {
        return;
    }

    while (true) {
        errorTaskCallback(gDvdErrorTaskID, 0);

        if (gDvdErrorState == DVD_ERROR_STATE_IDLE) {
            break;
        }

        if (fn_802245C4(lbl_8063F600) == 0) {
            break;
        }

        fn_80224588(lbl_8063F600);
    }
}

GSfileHandle *GSfile::openFile(char *fileName) {
    if (gInitialized == false) {
        return NULL;
    }

    fn_801DC264();

    GSfileHandle *fileHandle = getFreeFileHandle();
    if (fileHandle == NULL) {
        return NULL;
    }

    if (gNandManager != NULL) {
        if (gNandManager->openFile(fileName, fileHandle)) {
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
    if (gInitialized == false) {
        return false;
    }

    if (gNandManager != NULL) {
        if (gNandManager->fileExists(fileName)) {
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
    if (gInitialized == false) {
        return -1;
    }

    fn_801DC264();

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

    if (gNandManager != NULL && fileHandle->mIsNandFile) {
        s32 nBytesRead = gNandManager->readFile(fileHandle, buffer, length, offset);
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
    if (gInitialized == false) {
        return false;
    }

    fn_801DC264();

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

    if (gNandManager != NULL && fileHandle->mIsNandFile) {
        if (gNandManager->readFileAsync(fileHandle, buffer, length, offset)) {
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
    if (gInitialized == false) {
        return -1;
    }

    fn_801DC264();

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
    if (gInitialized == false) {
        return false;
    }

    fn_801DC264();

    if (fileHandle == NULL) {
        return false;
    }
    
    if (gNandManager != NULL) {
        if (gNandManager->closeFile(fileHandle)) {
            releaseFileHandle(fileHandle);
            return true;
        }
    }

    BOOL success = DVDClose(&fileHandle->mFileInfo);
    releaseFileHandle(fileHandle);

    return success;
}

u32 GSfile::getFileLength(GSfileHandle *fileHandle) {
    if (gInitialized == false) {
        return 0;
    }

    fn_801DC264();

    if (fileHandle == NULL) {
        return 0;
    }

    if (gNandManager != NULL) {
        u32 length;
        if (gNandManager->getFileLength(fileHandle, &length)) {
            return length;
        }
    }

    return fileHandle->mFileInfo.length;
}

s32 GSfile::getDriveStatus() {
    // Does not match with !gInitialized
    if (gInitialized == false) {
        return DVD_STATE_FATAL_ERROR;
    }

    return DVDGetDriveStatus();
}

bool GSfile::seekAsync(GSfileHandle *fileHandle, s32 offset, GSdvdCallback callback) {
    if (gInitialized == false) {
        return false;
    }

    fn_801DC264();

    if (fileHandle == NULL) {
        return false;
    }

    fileHandle->mCallback = callback;
    return DVDSeekAsyncPrio(&fileHandle->mFileInfo, offset, seekAsyncCallback, 2);
}

void GSfile::updateErrorState(s32 dvdState) {
    switch (dvdState) {
        case DVD_STATE_FATAL_ERROR:
            gDvdErrorState = DVD_ERROR_STATE_FATAL_ERROR;
            break;
        
        case DVD_STATE_COVER_OPEN:
            gDvdErrorState = DVD_ERROR_STATE_COVER_OPEN;
            break;
        
        case DVD_STATE_NO_DISK:
            gDvdErrorState = DVD_ERROR_STATE_NO_DISK;
            break;
        
        case DVD_STATE_WRONG_DISK:
            gDvdErrorState = DVD_ERROR_STATE_WRONG_DISK;
            break;
        
        case DVD_STATE_RETRY:
            gDvdErrorState = DVD_ERROR_STATE_RETRY;
            break;
        
        default:
            break;
    }
}

void GSfile::notifyError(GSdvdError error) {
    if (gDvdErrorCallback != NULL) {
        gDvdErrorCallback(error);
    }
}

void GSfile::notifyErrorHandled() {
    if (gDvdErrorHandledCallback != NULL) {
        gDvdErrorHandledCallback();
    }
}

// Comes after "RPBE"/"RPBP" strings in .sdata
/* lbl_8063D6F4 */ static s32 gDiscCheckResult = -1;

void GSfile::checkDiskCallback(s32 result, DVDCommandBlock *block) {
    gDiscCheckResult = result;
    OSSignalSemaphore(&gDvdSemaphore);
}

bool GSfile::checkDisk() {
    BOOL intEnabled = OSDisableInterrupts();
    OSRestoreInterrupts(intEnabled);

    if (!intEnabled) {
        return true;
    }

    OSInitSemaphore(&gDvdSemaphore, 0);

    gDiscCheckResult = -1;

    if (!DVDCheckDiskAsync(&gDiskCheckBlock, checkDiskCallback)) {
        gDiscCheckResult = 0;
    }

    if (gDiscCheckResult < 0) {
        OSWaitSemaphore(&gDvdSemaphore);
    }

    return gDiscCheckResult != 0;
}

void GSfile::errorTaskCallback(u32 taskID, u32 userParam) {
    s32 dvdState = getDriveStatus();

    switch (gDvdErrorState) {
        case DVD_ERROR_STATE_IDLE:
            updateErrorState(dvdState);
            break;
        
        case DVD_ERROR_STATE_COVER_OPEN:
            notifyError(DVD_ERROR_COVER_OPEN);
            gDvdErrorState = DVD_ERROR_STATE_WAIT_COVER_CLOSE;
            break;
        
        case DVD_ERROR_STATE_WAIT_COVER_CLOSE:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                gDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_COVER_OPEN && checkDisk()) {
                notifyErrorHandled();
                gDvdErrorState = DVD_ERROR_STATE_IDLE;
            }
            break;
        
        case DVD_ERROR_STATE_NO_DISK:
            notifyError(DVD_ERROR_NO_DISK);
            gDvdErrorState = DVD_ERROR_STATE_WAIT_DISK_INSERT;
            break;
        
        case DVD_ERROR_STATE_WAIT_DISK_INSERT:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                gDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_NO_DISK && checkDisk()) {
                notifyErrorHandled();
                gDvdErrorState = DVD_ERROR_STATE_IDLE;
            }
            break;
        
        case DVD_ERROR_STATE_WRONG_DISK:
            notifyError(DVD_ERROR_WRONG_DISK);
            gDvdErrorState = DVD_ERROR_STATE_WAIT_CORRECT_DISK;
            break;
        
        case DVD_ERROR_STATE_WAIT_CORRECT_DISK:
            if (dvdState == DVD_STATE_RETRY) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_RETRY);
                gDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            }
            else if (dvdState != DVD_STATE_WRONG_DISK && checkDisk()) {
                notifyErrorHandled();
                gDvdErrorState = DVD_ERROR_STATE_IDLE;
            }
            break;
        
        case DVD_ERROR_STATE_RETRY:
            notifyError(DVD_ERROR_RETRY);
            gDvdErrorState = DVD_ERROR_STATE_WAIT_RETRY;
            break;
        
        case DVD_ERROR_STATE_WAIT_RETRY:
            if (dvdState == DVD_STATE_COVER_OPEN) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_COVER_OPEN);
                gDvdErrorState = DVD_ERROR_STATE_WAIT_COVER_CLOSE;
            }
            else if (dvdState == DVD_STATE_NO_DISK) {
                notifyErrorHandled();
                notifyError(DVD_ERROR_NO_DISK);
                gDvdErrorState = DVD_ERROR_STATE_WAIT_DISK_INSERT;
            }
            // Not sure why DVD_STATE_NO_DISK and DVD_STATE_COVER_OPEN are checked here
            else if ((dvdState != DVD_STATE_RETRY && checkDisk()) || (dvdState == DVD_STATE_NO_DISK || dvdState == DVD_STATE_COVER_OPEN)) {
                notifyErrorHandled();
                gDvdErrorState = DVD_ERROR_STATE_IDLE;
            }
            break;
        
        case DVD_ERROR_STATE_FATAL_ERROR:
            notifyError(DVD_ERROR_FATAL);
            gDvdErrorState = DVD_ERROR_STATE_FATAL_ERROR_DONE;
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

void *GSfile::loadFileOnHeap(char *fileName, GSheapHandle heap, u32 *pLength) {
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
    if (gNandManager != NULL) {
        return gNandManager->copyFile(fileName, false);
    }
    return false;
}

void GSfile::setErrorCallbacks(
    GSdvdErrorCallback errorCallback,
    GSdvdErrorHandledCallback errorHandledCallback
) {
    gDvdErrorCallback = errorCallback;
    gDvdErrorHandledCallback = errorHandledCallback;
}

GSdvdError GSfile::getCurrentError() {
    switch (gDvdErrorState) {
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

        case DVD_ERROR_STATE_IDLE:
        default:
            return DVD_ERROR_OK;
    }
}

void GSfile::disableAsyncCallbacks() {
    gAsyncCallbacksDisabled = true;
}

bool GSfile::getAsyncCallbacksDisabled() {
    return gAsyncCallbacksDisabled;
}
