#include "version.hpp"

#include <cstring>
#include <revolution/nand.h>

#include "gs/GSfile.hpp"
#include "gs/GSnand.hpp"
#include "gs/GSthread.hpp"

extern MEMHeapHandle lbl_8063E8EC;

char *GSnand::getFileName(GSnandFileHandle *nandHandle) {
    return nandHandle->mName;
}

char *GSnand::getFilePath(GSnandFileHandle *nandHandle) {
    return nandHandle->mPath;
}

GSnandManager::GSnandManager() {
    memset(mFileHandles, 0, sizeof(mFileHandles));
}

GSnandFileHandle *GSnandManager::getFileHandle(char *fileName) {
    char fname[13];
    memcpy(fname, fileName, 12);
    fname[12] = '\0';

    for (int i = 0; i < 8; i++) {
        GSnandFileHandle *nandHandle = &mFileHandles[i];
        if (nandHandle->mInUse && !nandHandle->mCopyInProgress) {
            if (strcmp(GSnand::getFileName(nandHandle), fname) == 0) {
                return nandHandle;
            }
        }
    }
    return NULL;
}

bool GSnandManager::fileExists(char *fileName) {
    return getFileHandle(fileName) != NULL;
}

bool GSnandManager::openFile(char *fileName, GSfileHandle *fileHandle) {
    GSnandFileHandle *nandHandle = getFileHandle(fileName);
    if (nandHandle != NULL) {
        s32 result = NANDOpen(GSnand::getFilePath(nandHandle), &nandHandle->mFileInfo, NAND_ACCESS_READ);
        if (result == NAND_RESULT_OK) {
            fileHandle->mNandFileHandle = nandHandle;
            fileHandle->mIsNandFile = true;
            return true;
        }
    }
    return false;
}

bool GSnandManager::closeFile(GSfileHandle *fileHandle) {
    if (!fileHandle->mIsNandFile) {
        return false;
    }

    NANDClose(&fileHandle->mNandFileHandle->mFileInfo);
    fileHandle->mIsNandFile = false;
    fileHandle->mNandFileHandle = NULL;

    return true;
}

bool GSnandManager::getFileLength(GSfileHandle *fileHandle, u32 *outLength) {
    if (!fileHandle->mIsNandFile) {
        return false;
    }

    s32 result = NANDGetLength(&fileHandle->mNandFileHandle->mFileInfo, outLength);
    return result == NAND_RESULT_OK;
}

s32 GSnandManager::readFile(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset) {
    if (!fileHandle->mIsNandFile) {
        return -1;
    }

    s32 position = NANDSeek(&fileHandle->mNandFileHandle->mFileInfo, offset, NAND_SEEK_SET);
    // This appears to be a bug (and a pretty major one at that)
    if (position >= 0) {
        return -1;
    }

    return NANDRead(&fileHandle->mNandFileHandle->mFileInfo, buffer, length);
}

void GSnand::readAsyncCallback(s32 result, NANDCommandBlock *block) {
    GSfileHandle *fileHandle = (GSfileHandle *)NANDGetUserData(block);

    if (!GSfile::getAsyncCallbacksDisabled()) {
        if (fileHandle->mCallback != NULL) {
            fileHandle->mCallback(result, fileHandle);
        }
    }
}

void GSnand::seekAsyncCallback(s32 result, NANDCommandBlock *block) {
    GSfileHandle *fileHandle = (GSfileHandle *)NANDGetUserData(block);
    GSnandFileHandle *nandHandle = fileHandle->mNandFileHandle;

    if (GSfile::getAsyncCallbacksDisabled()) {
        return;
    }

    if (result < 0) {
        fileHandle->mCallback(-1, fileHandle);
        return;
    }
    
    s32 readResult = NANDReadAsync(
        &nandHandle->mFileInfo,
        fileHandle->mBuffer,
        fileHandle->mBufSize,
        readAsyncCallback,
        &nandHandle->mCommandBlock
    );

    if (readResult != NAND_RESULT_OK) {
        fileHandle->mCallback(-1, fileHandle);
    }
}

bool GSnandManager::readFileAsync(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset) {
    if (!fileHandle->mIsNandFile) {
        return false;
    }
    
    GSnandFileHandle *nandHandle = fileHandle->mNandFileHandle;
    NANDSetUserData(&nandHandle->mCommandBlock, fileHandle);

    s32 result = NANDSeekAsync(
        &nandHandle->mFileInfo,
        offset, NAND_SEEK_SET,
        GSnand::seekAsyncCallback,
        &nandHandle->mCommandBlock
    );

    return result == NAND_RESULT_OK;
}

bool GSnandManager::copyFile(char *fileName, bool unusedParam) {
    if (getFileHandle(fileName) != NULL) {
        return true;
    }

    // TODO get this loop to unroll
    GSnandFileHandle *nandHandle;
    for (int i = 0; i < 8; i++) {
        if (!mFileHandles[i].mInUse) {
            nandHandle = &mFileHandles[i];
            break;
        }
    }

    if (nandHandle == NULL) {
        return false;
    }

    if (!GSfile::fileExists(fileName)) {
        return false;
    }

    GSfileHandle *fileHandle = GSfile::openFile(fileName);
    if (fileHandle == NULL) {
        return false;
    }

    u32 length = (GSfile::getFileLength(fileHandle) + 0x1f) / 0x20 * 0x20;
    if (length == 0) {
        return false;
    }

    void *buffer = GSmem::allocFromHeap(lbl_8063E8EC, 0x200000);
    if (buffer == NULL) {
        return false;
    }

    nandHandle->mInUse = true;
    nandHandle->mCopyInProgress = true;

    strcpy(nandHandle->mPath, "/tmp/");
    strncat(nandHandle->mPath, fileName, 12);

    bool success = false;

    s32 result = NANDCreate(
        nandHandle->mPath,
        NAND_PERM_OWNER_READ | NAND_PERM_OWNER_WRITE,
        0
    );

    if (result == NAND_RESULT_OK || result == NAND_RESULT_EXISTS) {
        NANDFileInfo info;
        result = NANDOpen(nandHandle->mPath, &info, NAND_ACCESS_RW);

        if (result == NAND_RESULT_OK) {
            u32 offset = 0;
            do {
                s32 readLen = (length < 0x200000) ? length : 0x200000;
                s32 nRead = GSfile::readFilePrio(fileHandle, buffer, readLen, offset, 2);

                if (nRead < 0) {
                    if (nRead == -1) {
                        while (true) {
                            GSthreadManager::sInstance->sleepCurrentThread();
                        }
                    }
                    GSmem::freeToHeap(lbl_8063E8EC, buffer);
                    GSfile::closeFile(fileHandle);
                    return false;
                }

                s32 nWritten = NANDWrite(&info, buffer, readLen);
                if (nWritten != readLen) {
                    NANDClose(&info);
                    break;
                }

                length -= readLen;
                offset += readLen;
            } while (length > 0);

            result = NANDClose(&info);
            if (result == NAND_RESULT_OK) {
                success = true;
                nandHandle->mCopyInProgress = false;
            }
        }
    }

    if (buffer != NULL) {
        GSmem::freeToHeap(lbl_8063E8EC, buffer);
    }
    GSfile::closeFile(fileHandle);

    if (success) {
        nandHandle->mCopyInProgress = false;
        return true;
    }

    nandHandle->mInUse = false;
    return true;
}
