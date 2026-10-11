// Imported from koopthekoopa/wii-ipl (CC0), libs/RVL_SDK/src/dvd/dvdfs.c
#include <private/dvd.h>
#include <revolution/dvd.h>

#include <revolution/os.h>
#include <revolution/os/OSBootInfo.h>

#include <ctype.h>
#include <stddef.h>

// Few functions are unused. Make sure that they link.
#pragma force_active on

extern u32 __DVDLayoutFormat;

typedef struct FSTEntry {
    u32 isDirAndStringOff;  // 0x00
    union {
        struct {
            u32 parent;  // 0x04
            u32 next;    // 0x08
        } dir;
        struct {
            u32 position;  // 0x04
            u32 length;    // 0x08
        } file;
    };
} FSTEntry;

static OSBootInfo* BootInfo;

static FSTEntry* FstStart;
static char* FstStringStart;

static u32 MaxEntryNum;

static u32 currentDirectory = 0;

OSThreadQueue __DVDThreadQueue;

u32 __DVDLongFileNameFlag = TRUE;

void cbForReadAsync(s32 result, DVDCommandBlock* block);
void cbForReadSync(s32 result, DVDCommandBlock* block);

#define IS_ENTRY_DIR(fstStart, i) ((((fstStart)[i].isDirAndStringOff & 0xFF000000) == 0) ? FALSE : TRUE)
#define FILE_STRING_OFF(fstStart, i) ((fstStart)[i].isDirAndStringOff & 0x00FFFFFF)

static BOOL DVDGetCurrentDir(char* path, u32 maxlen);

void __DVDFSInit() {
    BootInfo = (OSBootInfo*)OSPhysicalToCached(OS_ADDR_BOOT_INFO);
    FstStart = (FSTEntry*)BootInfo->FSTLocation;

    if (FstStart != NULL) {
        MaxEntryNum = FstStart[0].dir.next;
        FstStringStart = (char*)&FstStart[MaxEntryNum];
    }
}

static BOOL isSame(const char* path, const char* str) {
    while (*str != '\0') {
        if (tolower(*path++) != tolower(*str++)) {
            return FALSE;
        }
    }

    if (*path == '/' || *path == '\0') {
        return TRUE;
    }

    return FALSE;
}

s32 DVDConvertPathToEntrynum(const char* path) {
    const char* ptrPath;
    char* name;

    BOOL isDir;
    s32 pathLen, dirLookAt, i;

    const char* origPathPtr = path;
    const char* hasExtensionStart;

    BOOL isInvalid, hasExtension;

    dirLookAt = currentDirectory;

    while (TRUE) {
        // End of path? Done!
        if (*path == 0) {
            return dirLookAt;
        }
        // Ignore initial slash.
        else if (*path == '/') {
            dirLookAt = 0;
            path++;
            continue;
        }
        // Special cases
        else if (*path == '.') {
            if (*(path + 1) == '.') {
                // Found `../`? Seek to parent.
                if (*(path + 2) == '/') {
                    dirLookAt = FstStart[dirLookAt].dir.parent;
                    path += 3;
                    continue;
                }
                // If the input path was literally just `../`, then return the parent.
                else if (*(path + 2) == 0) {
                    return FstStart[dirLookAt].dir.parent;
                }
            }
            // "." directory does nothing
            else if (*(path + 1) == '/') {
                path += 2;
                continue;
            }
            // Ignore trailing dot
            else if (*(path + 1) == 0) {
                return dirLookAt;
            }
        }

        if (__DVDLongFileNameFlag == FALSE) {
            hasExtension = FALSE;
            isInvalid = FALSE;

            for (ptrPath = path; *ptrPath != '\0' && *ptrPath != '/'; ptrPath++) {
                if (*ptrPath == '.') {
                    if (ptrPath - path > 8 || hasExtension == TRUE) {
                        isInvalid = TRUE;
                        break;
                    }

                    hasExtension = TRUE;
                    hasExtensionStart = ptrPath + 1;

                } else if (*ptrPath == ' ') {
                    isInvalid = TRUE;
                }
            }

            if (hasExtension == TRUE && ptrPath - hasExtensionStart > 3) {
                isInvalid = TRUE;
            }

            // Yeah I wonder how soon the restriction was finally patched out (or was it even patched out at ALL)
            if (!(!isInvalid)) OSPanic(__FILE__, 443, "DVDConvertEntrynumToPath(possibly DVDOpen or DVDChangeDir or DVDOpenDir): specified directory or file (%s) doesn't match "
                         "standard 8.3 format. This is a temporary restriction and will be removed soon\n", origPathPtr);
        } else {
            for (ptrPath = path; (*ptrPath != '\0') && (*ptrPath != '/'); ptrPath++) {
            }
        }

        isDir = (*ptrPath == '\0') ? FALSE : TRUE;
        pathLen = (u32)(ptrPath - path);

        ptrPath = path;

        for (i = dirLookAt + 1; i < FstStart[dirLookAt].dir.next; i = IS_ENTRY_DIR(FstStart, i) ? FstStart[i].dir.next : (i + 1)) {
            // Skip directories
            if (IS_ENTRY_DIR(FstStart, i) == FALSE && isDir == TRUE) {
                continue;
            }

            name = FstStringStart + FILE_STRING_OFF(FstStart, i);

            // Advance to next file in hierarchy
            if (isSame(ptrPath, name) == TRUE) {
                goto next_in_hier;
            }
        }

        return -1;

    next_in_hier:
        if (!isDir) {
            return i;
        }

        dirLookAt = i;
        path += pathLen + 1;
    }
}

BOOL DVDFastOpen(s32 entry, DVDFileInfo* fileInfo) {
    if (entry < 0 || entry >= MaxEntryNum || IS_ENTRY_DIR(FstStart, entry)) {
        return FALSE;
    }

    fileInfo->startAddr = FstStart[entry].file.position >> __DVDLayoutFormat;
    fileInfo->length = FstStart[entry].file.length;
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_IDLE;

    return TRUE;
}

BOOL DVDOpen(const char* fileName, DVDFileInfo* fileInfo) {
    s32 entry;
    char currentDir[128];

    entry = DVDConvertPathToEntrynum(fileName);

    if (entry < 0) {
        DVDGetCurrentDir(currentDir, sizeof(currentDir));
        OSReport("Warning: DVDOpen(): file '%s' was not found under %s.\n", fileName, currentDir);
        return FALSE;
    }

    if (IS_ENTRY_DIR(FstStart, entry)) {
        return FALSE;
    }

    fileInfo->startAddr = FstStart[entry].file.position >> __DVDLayoutFormat;
    fileInfo->length = FstStart[entry].file.length;
    fileInfo->callback = (DVDCallback)NULL;
    fileInfo->cb.state = DVD_STATE_IDLE;

    return TRUE;
}

BOOL DVDClose(DVDFileInfo* fileInfo) {
    DVDCancel(&fileInfo->cb);
    return TRUE;
}

static u32 myStrncpy(char* dest, char* src, u32 maxlen) {
    u32 i = maxlen;

    while (i > 0 && *src != 0) {
        *dest++ = *src++;
        i--;
    }

    return (maxlen - i);
}

u32 entryToPath(u32 entry, char* path, u32 maxlen) {
    char* name;
    u32 loc;

    if (entry == 0) {
        return 0;
    }

    name = FstStringStart + FILE_STRING_OFF(FstStart, entry);
    loc = entryToPath(FstStart[entry].dir.parent, path, maxlen);

    if (loc == maxlen) {
        return loc;
    }

    *(path + loc++) = '/';
    loc += myStrncpy(path + loc, name, maxlen - loc);
    return loc;
}

static BOOL DVDConvertEntrynumToPath(s32 entry, char* path, u32 maxlen) {
    u32 loc = entryToPath((u32)entry, path, maxlen);

    if (loc == maxlen) {
        path[maxlen - 1] = '\0';
        return FALSE;
    }

    if (IS_ENTRY_DIR(FstStart, entry)) {
        if (loc == maxlen - 1) {
            path[loc] = '\0';
            return FALSE;
        }

        path[loc++] = '/';
    }

    path[loc] = '\0';

    return TRUE;
}

BOOL DVDGetCurrentDir(char* path, u32 maxlen) {
    return DVDConvertEntrynumToPath((s32)currentDirectory, path, maxlen);
}

BOOL DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio) {
    if (!(offset >= 0 && offset <= fileInfo->length)) OSPanic(__FILE__, 823, "DVDReadAsync(): specified area is out of the file  ");
    if (!((offset + length) >= 0 && (offset + length) < fileInfo->length + 32)) OSPanic(__FILE__, 829, "DVDReadAsync(): specified area is out of the file  ");

    fileInfo->callback = callback;
    DVDReadAbsAsyncPrio(&fileInfo->cb, addr, length, (u32)(fileInfo->startAddr + (offset >> 2)), cbForReadAsync, prio);

    return TRUE;
}

void cbForReadAsync(s32 result, DVDCommandBlock* block) {
    DVDFileInfo* fileInfo = (DVDFileInfo*)((char*)block - offsetof(DVDFileInfo, cb));

    if (fileInfo->callback) {
        (fileInfo->callback)(result, fileInfo);
    }
}

s32 DVDReadPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, s32 prio) {
    DVDCommandBlock* block;
    BOOL result;
    BOOL enabled;
    s32 state;
    s32 retVal;

    if (!(offset >= 0 && offset <= fileInfo->length)) OSPanic(__FILE__, 893, "DVDRead(): specified area is out of the file  ");
    if (!((offset + length) >= 0 && (offset + length) < fileInfo->length + 32)) OSPanic(__FILE__, 899, "DVDRead(): specified area is out of the file  ");

    block = &fileInfo->cb;
    result = DVDReadAbsAsyncPrio(block, addr, length, (u32)(fileInfo->startAddr + (offset >> 2)), cbForReadSync, prio);

    if (result == FALSE) {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (TRUE) {
        state = ((DVDCommandBlock*)block)->state;

        if (state == DVD_STATE_IDLE) {
            retVal = block->transferredSize;
            break;
        }

        if (state == DVD_STATE_FATAL) {
            retVal = DVD_RESULT_FATAL;
            break;
        }

        if (state == DVD_STATE_CANCELED) {
            retVal = DVD_RESULT_CANCELED;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

void cbForReadSync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

