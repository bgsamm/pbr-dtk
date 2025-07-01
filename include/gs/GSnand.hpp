#pragma once

#include <revolution/types.h>

// TODO introduce #define's for various array sizes

struct GSfileHandle;

// size: 0x190
struct GSnandFileHandle {
    /* 0x0 */ bool mInUse;
    /* 0x1 */ bool mCopyInProgress;
    /* 0x2 */ char mPath[5];
    // This length is an educated guess
    /* 0x7 */ char mName[64];
    /* 0x48 */ NANDFileInfo mFileInfo;
    /* 0xd4 */ NANDCommandBlock mCommandBlock;
};

// size: 0xc80
class GSnandManager {
public:
    GSnandFileHandle mFileHandles[8];

    GSnandManager();

    GSnandFileHandle *getFileHandle(char *fileName);
    bool fileExists(char *fileName);
    bool openFile(char *fileName, GSfileHandle *fileHandle);
    bool closeFile(GSfileHandle *fileHandle);
    bool getFileLength(GSfileHandle *fileHandle, u32 *outLength);
    s32 readFile(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset);
    bool readFileAsync(GSfileHandle *fileHandle, void *buffer, u32 length, u32 offset);
    bool copyFile(char *fileName, bool unusedParam);
};

namespace GSnand {
    static char *getFileName(GSnandFileHandle *nandHandle);
    static char *getFilePath(GSnandFileHandle *nandHandle);
    static void readAsyncCallback(s32 result, NANDCommandBlock *block);
    static void seekAsyncCallback(s32 result, NANDCommandBlock *block);
};
