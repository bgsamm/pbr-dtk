// Imported from doldecomp/ogws (CC0), src/revolution/DVD/dvderror.c
#include <revolution/dvd.h>
#include <revolution/nand.h>
#include <private/dvd.h>
#include <private/nand.h>

static NANDFileInfo NandInfo;
static NANDCommandBlock NandCb ALIGN32;

DVDErrorInfo __ErrorInfo ALIGN32;
static DVDErrorCallback Callback;

static void cbForNandClose(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (Callback != NULL) {
        Callback(result == NAND_RESULT_OK ? 1 : 2, 0);
    }
}

static void cbForNandWrite(s32 result, NANDCommandBlock* block) {
#pragma unused(result)
#pragma unused(block)

    if (NANDCloseAsync(&NandInfo, cbForNandClose, &NandCb) != NAND_RESULT_OK) {
        // Must call callback function manually
        cbForNandClose(-1, NULL);
    }
}

static void cbForNandOpen(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK) {
        if (NANDWriteAsync(&NandInfo, &__ErrorInfo, sizeof(DVDErrorInfo),
                           cbForNandWrite, &NandCb) != NAND_RESULT_OK) {
            // Must call callback function manually
            cbForNandWrite(-1, NULL);
        }
    } else if (Callback != NULL) {
        Callback(2, 0);
    }
}

static void cbForNandCreate(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK || result == NAND_RESULT_EXISTS) {
        if (NANDPrivateOpenAsync("/shared2/test2/dvderror.dat", &NandInfo,
                                 NAND_ACCESS_WRITE, cbForNandOpen,
                                 &NandCb) != NAND_RESULT_OK) {
            // Must call callback function manually
            cbForNandOpen(-1, NULL);
        }
    } else if (Callback != NULL) {
        Callback(2, 0);
    }
}

static void cbForNandCreateDir(s32 result, NANDCommandBlock* block) {
#pragma unused(block)

    if (result == NAND_RESULT_OK || result == NAND_RESULT_EXISTS) {
        if (NANDPrivateCreateAsync("/shared2/test2/dvderror.dat",
                                   NAND_PERM_RWALL, 0, cbForNandCreate,
                                   &NandCb) != NAND_RESULT_OK) {
            // Must call callback function manually
            cbForNandCreate(-1, NULL);
        }
    } else if (Callback != NULL) {
        Callback(2, 0);
    }
}

void __DVDStoreErrorCode(u32 error, DVDErrorCallback callback) {
    __ErrorInfo.error = error;
    __ErrorInfo.dateTime = OSTicksToSeconds(OSGetTime());
    Callback = callback;

    if (NANDPrivateCreateDirAsync("/shared2/test2", NAND_PERM_RWALL, 0,
                                  cbForNandCreateDir, &NandCb) != 0) {
        // Must call callback function manually
        cbForNandCreateDir(-1, NULL);
    }
}
