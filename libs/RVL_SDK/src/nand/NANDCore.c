// Imported from doldecomp/ogws (CC0), src/revolution/NAND/NANDCore.c
#include <private/es.h>
#include <private/fs.h>
#include <private/ios.h>
#include <private/ipc.h>
#include <private/nand.h>
#include <revolution/esp.h>
#include <revolution/nand.h>
#include <revolution/os.h>

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

// __memclr is a compiler intrinsic
#define MEMCLR(x) __memclr((x), sizeof(*(x)))

#include <stdio.h>
#include <string.h>
#include <wchar.h>

// From doldecomp/ogws (CC0), include/revolution/ESP/esp.h
enum {
    ES_IOCTLV_GET_DATA_DIR = 29,
    ES_IOCTLV_GET_TITLE_ID = 32,
};

#define NAND_BANNER_MAGIC 'WIBN'

typedef enum {
    NAND_LIB_UNINITIALIZED,
    NAND_LIB_INITIALIZING,
    NAND_LIB_INITIALIZED
} NANDLibState;

static void nandShutdownCallback(s32 result, void *arg);
static void nandGetTypeCallback(s32 result, void *arg);
static BOOL nandOnShutdown(BOOL final, u32 event);
static s32 _ES_InitLib(s32 *fd);
static s32 _ES_GetDataDir(s32 *fd, u64 tid, char *dirOut) NO_INLINE;
static s32 _ES_GetTitleId(s32 *fd, u64 *tidOut);
static s32 _ES_CloseLib(s32 *fd);

const char *__NANDVersion = "<< RVL_SDK - NAND \trelease build: Nov 30 2006 03:32:57 (0x4199_60831) >>";

static NANDLibState s_libState = NAND_LIB_UNINITIALIZED;
static char s_currentDir[64] ALIGN32 = "/";
static OSShutdownFunctionInfo s_shutdownFuncInfo = {nandOnShutdown, 255};

static char s_homeDir[64] ALIGN32;

void nandRemoveTailToken(char *newp, const char *oldp) {
    int i;

    if (oldp[0] == '/' && oldp[1] == '\0') {
        newp[0] = '/';
        newp[1] = '\0';
    } else {
        for (i = strlen(oldp) - 1; i >= 0; i--) {
            if (oldp[i] == '/') {
                if (i != 0) {
                    strncpy(newp, oldp, i);
                    newp[i] = '\0';
                    break;
                } else {
                    newp[0] = '/';
                    newp[1] = '\0';
                    break;
                }
            }
        }
    }
}

void nandGetHeadToken(char *head, char *rest, const char *path) {
    int i;

    for (i = 0; i <= strlen(path); i++) {
        if (path[i] == '/') {
            strncpy(head, path, i);
            head[i] = '\0';

            if (path[i + 1] == '\0') {
                *rest = '\0';
            } else {
                strcpy(rest, path + i + 1);
            }
            break;
        } else if (path[i] == '\0') {
            strncpy(head, path, i);
            head[i] = '\0';
            *rest = '\0';
            break;
        }
    }
}

void nandGetRelativeName(char *name, const char *path) {
    int i;

    if (strcmp("/", path) == 0) {
        strcpy(name, "");
    } else {
        for (i = strlen(path) - 1; i >= 0; i--) {
            if (path[i] == '/') {
                break;
            }
        }

        strcpy(name, path + i + 1);
    }
}

void nandConvertPath(char *abs, const char *dir, const char *rel) {
    char head[128];
    char rest[128];
    char notail[128];
    char newdir[128];

    if (strlen(rel) == 0) {
        strcpy(abs, dir);
        return;
    }

    nandGetHeadToken(head, rest, rel);

    if (strcmp(head, ".") == 0) {
        nandConvertPath(abs, dir, rest);
    } else if (strcmp(head, "..") == 0) {
        nandRemoveTailToken(notail, dir);
        nandConvertPath(abs, notail, rest);
    } else if (head[0] != '\0') {
        if (strcmp(dir, "/") == 0) {
            sprintf(newdir, "/%s", head);
        } else {
            sprintf(newdir, "%s/%s", dir, head);
        }
        nandConvertPath(abs, newdir, rest);
    } else {
        strcpy(abs, dir);
    }
}

BOOL nandIsRelativePath(const char *path) {
    return *path == '/' ? FALSE : TRUE;
}

BOOL nandIsPrivatePath(const char *path) {
    size_t len = sizeof("/shared2") - 1;
    return strncmp(path, "/shared2", len) == 0;
}

BOOL nandIsUnderPrivatePath(const char *path) {
    size_t len = sizeof("/shared2/") - 1;

    if (strncmp(path, "/shared2/", len) == 0 && path[len] != '\0') {
        return TRUE;
    }

    return FALSE;
}

BOOL nandIsInitialized(void) {
    return s_libState == NAND_LIB_INITIALIZED ? TRUE : FALSE;
}

// Stubbed for release
void nandReportErrorCode(s32 result) {
#pragma unused(result)
}

s32 nandConvertErrorCode(s32 result) {
    int i;

    // clang-format off
    const s32 errorMap[] = {IPC_RESULT_OK,                    NAND_RESULT_OK,
                            ISFS_ERROR_ACCESS,                NAND_RESULT_ACCESS,
                            ISFS_ERROR_CORRUPT,               NAND_RESULT_CORRUPT,
                            ISFS_ERROR_ECC_CRIT,              NAND_RESULT_ECC_CRIT,
                            ISFS_ERROR_EXISTS,                NAND_RESULT_EXISTS,
                            -116,                             NAND_RESULT_AUTHENTICATION,
                            ISFS_ERROR_INVALID,               NAND_RESULT_INVALID,
                            ISFS_ERROR_MAXBLOCKS,             NAND_RESULT_MAXBLOCKS,
                            ISFS_ERROR_MAXFD,                 NAND_RESULT_MAXFD,
                            ISFS_ERROR_MAXFILES,              NAND_RESULT_MAXFILES,
                            ISFS_ERROR_NOEXISTS,              NAND_RESULT_NOEXISTS,
                            ISFS_ERROR_NOTEMPTY,              NAND_RESULT_NOTEMPTY,
                            -104,                             NAND_RESULT_UNKNOWN,
                            ISFS_ERROR_OPENFD,                NAND_RESULT_OPENFD,
                            -117,                             NAND_RESULT_UNKNOWN,
                            ISFS_ERROR_BUSY,                  NAND_RESULT_BUSY,
                            ISFS_ERROR_SHUTDOWN,           NAND_RESULT_FATAL_ERROR,
                            IPC_RESULT_ACCESS,       NAND_RESULT_ACCESS,
                            IPC_RESULT_EXISTS,       NAND_RESULT_EXISTS,
                            -3,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_INVALID,      NAND_RESULT_INVALID,
                            -5,                               NAND_RESULT_UNKNOWN,
                            IPC_RESULT_NOEXISTS,     NAND_RESULT_NOEXISTS,
                            -7,                               NAND_RESULT_UNKNOWN,
                            IPL_RESULT_FULLQUEUE,         NAND_RESULT_BUSY,
                            -9,                               NAND_RESULT_UNKNOWN,
                            -10,                              NAND_RESULT_UNKNOWN,
                            -11,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_ECC_CRIT,     NAND_RESULT_ECC_CRIT,
                            -13,                              NAND_RESULT_UNKNOWN,
                            -14,                              NAND_RESULT_UNKNOWN,
                            -15,                              NAND_RESULT_UNKNOWN,
                            -16,                              NAND_RESULT_UNKNOWN,
                            -17,                              NAND_RESULT_UNKNOWN,
                            -18,                              NAND_RESULT_UNKNOWN,
                            -19,                              NAND_RESULT_UNKNOWN,
                            -20,                              NAND_RESULT_UNKNOWN,
                            -21,                              NAND_RESULT_UNKNOWN,
                            IPC_RESULT_ALLOC_FAILED,          NAND_RESULT_ALLOC_FAILED,
                            -23,                              NAND_RESULT_UNKNOWN};
    // clang-format on

    i = 0;

    if (result >= 0) {
        return result;
    }

    for (; i < ARRAY_SIZE(errorMap); i += 2) {
        if (result == errorMap[i]) {
            nandReportErrorCode(result);
            return errorMap[i + 1];
        }
    }

    OSReport("CAUTION!  Unexpected error code [%d] was found.\n", result);
    nandReportErrorCode(result);
    return NAND_RESULT_UNKNOWN;
}

void nandGenerateAbsPath(char *abs, const char *rel) {
    s32 len;

    if (strlen(rel) == 0) {
        strcpy(abs, "");
    } else if (nandIsRelativePath(rel)) {
        nandConvertPath(abs, s_currentDir, rel);
    } else {
        strcpy(abs, rel);
        len = strlen(abs);
        if (len != 0 && abs[len - 1] == '/' && len - 1 != 0) {
            abs[len - 1] = '\0';
        }
    }
}

void nandGetParentDirectory(char *dir, const char *path) {
    int i;

    for (i = strlen(path); i >= 0; i--) {
        if (path[i] == '/') {
            break;
        }
    }

    if (i == 0) {
        strcpy(dir, "/");
    } else {
        strncpy(dir, path, i);
        dir[i] = '\0';
    }
}

s32 NANDInit(void) {
    s32 result;
    u64 tid;
    s32 fd;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (s_libState == NAND_LIB_INITIALIZING) {
        OSRestoreInterrupts(enabled);
        return NAND_RESULT_BUSY;
    } else if (s_libState == NAND_LIB_INITIALIZED) {
        OSRestoreInterrupts(enabled);
        return NAND_RESULT_OK;
    }

    s_libState = NAND_LIB_INITIALIZING;
    OSRestoreInterrupts(enabled);

    result = ISFS_OpenLib();
    if (result == IPC_RESULT_OK) {
        result = _ES_InitLib(&fd);

        if (result == IPC_RESULT_OK) {
            result = _ES_GetTitleId(&fd, &tid);
        }

        if (result == IPC_RESULT_OK) {
            result = _ES_GetDataDir(&fd, tid, s_homeDir);
        }

        if (result == IPC_RESULT_OK) {
            strcpy(s_currentDir, s_homeDir);
        }

        _ES_CloseLib(&fd);

        if (result != IPC_RESULT_OK) {
            OSReport("Failed to set home directory.\n");
        }

        OSRegisterShutdownFunction(&s_shutdownFuncInfo);
        enabled = OSDisableInterrupts();
        s_libState = NAND_LIB_INITIALIZED;
        OSRestoreInterrupts(enabled);
        OSRegisterVersion(__NANDVersion);
        return NAND_RESULT_OK;
    } else {
        enabled = OSDisableInterrupts();
        s_libState = NAND_LIB_UNINITIALIZED;
        OSRestoreInterrupts(enabled);
        return nandConvertErrorCode(result);
    }
}

static BOOL nandOnShutdown(BOOL final, u32 event) {
    if (!final) {
        if (event == OS_SD_EVENT_SHUTDOWN) {
            volatile BOOL shutdown = FALSE;
            s64 start = OSGetTime();
            ISFS_ShutdownAsync(nandShutdownCallback, (void *)&shutdown);

            while (OSTicksToMilliseconds(OSGetTime() - start) < 500) {
                if (shutdown) {
                    break;
                }
            }
        }

        return TRUE;
    }

    return TRUE;
}

static void nandShutdownCallback(s32 result, void *arg) {
#pragma unused(result)

    *(BOOL *)arg = TRUE;
}

// nandChangeDir and nandChangeDirCallback: from koopthekoopa/wii-ipl (CC0),
// libs/RVL_SDK/src/nand/NANDCore.c. NANDChangeDirAsync is the public wrapper
// (async, not private), as the compiled code shows.
static void nandChangeDirCallback(s32 result, void *arg);

static s32 nandChangeDir(const char *path, NANDCommandBlock *block, BOOL async, BOOL priv) {
    s32 result;
    BOOL enabled;
    char absPath[64];
    u32 numFiles;

    if (async) {
        nandGenerateAbsPath(block->absPath, path);

        if (!priv && (strncmp(block->absPath, "/shared2", 8) == 0 ? TRUE : FALSE)) {
            return ISFS_ERROR_ACCESS;
        }

        return ISFS_ReadDirAsync(block->absPath, NULL, &block->num, nandChangeDirCallback, block);
    } else {
        numFiles = 0;
        MEMCLR(&absPath);
        nandGenerateAbsPath(absPath, path);

        if (!priv && (strncmp(absPath, "/shared2", 8) == 0 ? TRUE : FALSE)) {
            return ISFS_ERROR_ACCESS;
        }

        result = ISFS_ReadDir(absPath, NULL, &numFiles);

        if (result == IPC_RESULT_OK) {
            enabled = OSDisableInterrupts();
            strcpy(s_currentDir, absPath);
            OSRestoreInterrupts(enabled);
        }

        return result;
    }
}

s32 NANDChangeDirAsync(const char *path, NANDAsyncCallback callback, NANDCommandBlock *block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    block->callback = callback;
    return nandConvertErrorCode(nandChangeDir(path, block, TRUE, FALSE));
}

static void nandChangeDirCallback(s32 result, void *arg) {
    NANDCommandBlock *block = (NANDCommandBlock *)arg;
    BOOL enabled;

    if (result == IPC_RESULT_OK) {
        enabled = OSDisableInterrupts();
        strcpy(s_currentDir, block->absPath);
        OSRestoreInterrupts(enabled);
    }

    block->callback(nandConvertErrorCode(result), block);
}

s32 NANDGetCurrentDir(char *out) {
    BOOL enabled;

    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    enabled = OSDisableInterrupts();
    strcpy(out, s_currentDir);
    OSRestoreInterrupts(enabled);
    return NAND_RESULT_OK;
}

s32 NANDGetHomeDir(char *out) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    strcpy(out, s_homeDir);
    return NAND_RESULT_OK;
}

void nandCallback(s32 result, void *arg) {
    NANDCommandBlock *block = (NANDCommandBlock *)arg;
    block->callback(nandConvertErrorCode(result), block);
}

static s32 nandGetType(const char *path, u8 *type, NANDCommandBlock *block, BOOL async, BOOL priv) {
    char absPath[64];
    u32 numFiles;
    s32 result;

    if (strlen(path) == 0) {
        return ISFS_ERROR_INVALID;
    }

    if (async) {
        nandGenerateAbsPath(block->absPath, path);

        if (!priv && nandIsUnderPrivatePath(block->absPath)) {
            return ISFS_ERROR_ACCESS;
        }

        block->type = type;
        return ISFS_ReadDirAsync(block->absPath, NULL, &block->num, nandGetTypeCallback, block);
    } else {
        MEMCLR(&absPath);
        nandGenerateAbsPath(absPath, path);

        if (!priv && nandIsUnderPrivatePath(absPath)) {
            return ISFS_ERROR_ACCESS;
        }

        numFiles = 0;
        result = ISFS_ReadDir(absPath, NULL, &numFiles);
        if (result == IPC_RESULT_OK || result == ISFS_ERROR_ACCESS) {
            *type = NAND_FILE_TYPE_DIR;
            return IPC_RESULT_OK;
        } else if (result == ISFS_ERROR_INVALID) {
            *type = NAND_FILE_TYPE_FILE;
            return IPC_RESULT_OK;
        }

        return result;
    }
}

s32 NANDGetType(const char *path, u8 *type) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    return nandConvertErrorCode(nandGetType(path, type, NULL, FALSE, FALSE));
}

s32 NANDPrivateGetTypeAsync(const char *path, u8 *type, NANDAsyncCallback callback, NANDCommandBlock *block) {
    if (!nandIsInitialized()) {
        return NAND_RESULT_FATAL_ERROR;
    }

    block->callback = callback;
    return nandConvertErrorCode(nandGetType(path, type, block, TRUE, TRUE));
}

static void nandGetTypeCallback(s32 result, void *arg) {
    NANDCommandBlock *block = (NANDCommandBlock *)arg;

    if (result == IPC_RESULT_OK || result == ISFS_ERROR_ACCESS) {
        *block->type = NAND_FILE_TYPE_DIR;
        result = IPC_RESULT_OK;
    } else if (result == ISFS_ERROR_INVALID) {
        *block->type = NAND_FILE_TYPE_FILE;
        result = IPC_RESULT_OK;
    }

    block->callback(nandConvertErrorCode(result), block);
}

const char *nandGetHomeDir(void) {
    return s_homeDir;
}

void NANDInitBanner(NANDBanner *banner, u32 flags, const wchar_t *title, const wchar_t *subtitle) {
    memset(banner, 0, sizeof(NANDBanner));
    banner->flags = flags;
    banner->magic = NAND_BANNER_MAGIC;

    if (wcscmp(title, L"") == 0) {
        wcsncpy(banner->title, L" ", NAND_BANNER_TITLE_MAX);
    } else {
        wcsncpy(banner->title, title, NAND_BANNER_TITLE_MAX);
    }

    if (wcscmp(subtitle, L"") == 0) {
        wcsncpy(banner->subtitle, L" ", NAND_BANNER_TITLE_MAX);
    } else {
        wcsncpy(banner->subtitle, subtitle, NAND_BANNER_TITLE_MAX);
    }
}

/**
 * These were actually re(?)implemented in NANDCore/OSExec according to BBA
 */

static s32 _ES_InitLib(s32 *fd) {
    s32 result;

    *fd = -1;
    result = IPC_RESULT_OK;

    *fd = IOS_Open("/dev/es", IPC_OPEN_NONE);
    if (*fd < 0) {
        result = *fd;
    }

    return result;
}

static s32 _ES_GetDataDir(s32 *fd, u64 tid, char *dirOut) {
    // TODO(kiwi) Hacky solution
    u8 tidWork[256] ALIGN32;
    u8 vectorWork[32] ALIGN32;
    IOSIoVector *pVectors = (IOSIoVector *)vectorWork;
    u64 *pTid = (u64 *)tidWork;

    // Cast is necessary
    if (*fd < 0 || dirOut == ((void *)NULL)) {
        return -0x3F9;
    }

    if ((u32)dirOut % 32 != 0) {
        return -0x3F9;
    }

    *pTid = tid;

    pVectors[0].base = (u8 *)pTid;
    pVectors[0].length = sizeof(u64);
    pVectors[1].base = (u8 *)dirOut;
    pVectors[1].length = 30;

    return IOS_Ioctlv(*fd, ES_IOCTLV_GET_DATA_DIR, 1, 1, pVectors);
}

static s32 _ES_GetTitleId(s32 *fd, u64 *tidOut) {
    s32 result;
    u64 *pTid;
    // TODO(kiwi) Hacky solution
    u8 tidWork[256] ALIGN32;
    u8 vectorWork[32] ALIGN32;
    IOSIoVector *pVectors = (IOSIoVector *)vectorWork;

    // Cast is necessary
    if (*fd < 0 || tidOut == ((void *)NULL)) {
        return -0x3F9;
    }

    pTid = (u64 *)tidWork;
    pVectors[0].base = (u8 *)pTid;
    pVectors[0].length = sizeof(u64);

    result = IOS_Ioctlv(*fd, ES_IOCTLV_GET_TITLE_ID, 0, 1, pVectors);
    if (result == IPC_RESULT_OK) {
        *tidOut = *pTid;
    }

    return result;
}

static s32 _ES_CloseLib(s32 *fd) {
    s32 result = IPC_RESULT_OK;

    if (*fd >= 0 && (result = IOS_Close(*fd)) == IPC_RESULT_OK) {
        *fd = -1;
    }

    return result;
}
