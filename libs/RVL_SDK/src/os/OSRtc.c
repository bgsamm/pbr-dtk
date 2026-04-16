#include <private/os.h>
#include <revolution/os.h>

#include <private/exi.h>

static SramControl Scb ALIGN32;

static BOOL ReadSram(void* buffer) {
    BOOL err;
    u32 cmd;

    DCInvalidateRange(buffer, 64);

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    cmd = 0x20000000 | 0x100;
    err = FALSE;
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDma(EXI_CHAN_0, buffer, 64, EXI_READ, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);
    return !err;
}

static u16 OSGetGbsMode();
static void OSSetGbsMode(u16 mode);

static BOOL WriteSram(void* buffer, u32 offset, u32 size);

static void WriteSramCallback(s32 chan, OSContext* context) {
    Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, 64 - Scb.offset);

    if (Scb.sync) {
        Scb.offset = 64;
    }
}

void __OSInitSram() {
    Scb.locked = Scb.enabled = FALSE;
    Scb.sync = ReadSram(Scb.sram);
    Scb.offset = 64;

    OSSetGbsMode(OSGetGbsMode());
}

static BOOL WriteSram(void* buffer, u32 offset, u32 size) {
    BOOL err;
    u32 cmd;

    if (!EXILock(EXI_CHAN_0, EXI_WRITE, WriteSramCallback)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_WRITE, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    offset <<= 6;
    cmd = 0xA0000000 | 0x000000100 + offset;
    err = FALSE;
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIImmEx(EXI_CHAN_0, buffer, size, EXI_WRITE);
    err |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);
    return !err;
}

static void* LockSram(u32 offset) {
    BOOL enabled;
    enabled = OSDisableInterrupts();

    if (Scb.locked) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }

    Scb.enabled = enabled;
    Scb.locked = TRUE;
    return Scb.sram + offset;
}

static OSSramEx* __OSLockSramEx() {
    return LockSram(sizeof(OSSram));
}

BOOL UnlockSram(BOOL commit, u32 offset) {
    u16* p;

    if (commit) {
        if (offset == 0) {
            OSSram* sram = (OSSram*)Scb.sram;

            if ((sram->flags & 3) > (u32)2) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;

            for (p = (u16*)&sram->counterBias; p < (u16*)(Scb.sram + sizeof(OSSram)); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~*p;
            }
        }

        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        if (Scb.offset <= sizeof(OSSram)) {
            OSSramEx* sram = (OSSramEx*)(Scb.sram + sizeof(OSSram));

            if ((sram->gbs & 0x7C00) == (u32)0x5000 || (sram->gbs & 0xC0) == (u32)0xC0) {
                sram->gbs = 0;
            }
        }

        Scb.sync = WriteSram(Scb.sram + Scb.offset, Scb.offset, 64 - Scb.offset);

        if (Scb.sync) {
            Scb.offset = 64;
        }
    }

    Scb.locked = FALSE;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

static BOOL __OSUnlockSramEx(BOOL commit) {
    return UnlockSram(commit, sizeof(OSSram));
}

BOOL __OSSyncSram() {
    return Scb.sync;
}

BOOL __OSReadROM(void* buffer, s32 length, s32 offset) {
    BOOL err;
    u32 cmd;

    DCInvalidateRange(buffer, (u32)length);

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    cmd = (u32)(offset << 6);
    err = FALSE;
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDma(EXI_CHAN_0, buffer, length, EXI_READ, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);
    return !err;
}

u16 OSGetGbsMode() {
    OSSramEx* sram;
    u16 mode;
    sram = __OSLockSramEx();
    mode = sram->gbs;
    __OSUnlockSramEx(FALSE);
    return mode;
}

static void OSSetGbsMode(u16 mode) {
    OSSramEx* sram;

    if ((mode & 0x7C00) == (u32)0x5000 || (mode & 0xC0) == (u32)0xC0) {
        mode = 0;
    }

    sram = __OSLockSramEx();

    if (mode == sram->gbs) {
        __OSUnlockSramEx(FALSE);
        return;
    }

    sram->gbs = mode;
    __OSUnlockSramEx(TRUE);
}

u16 OSGetWirelessID(s32 chan) {
    OSSramEx* sram;
    u16 id;
    sram = __OSLockSramEx();
    id = sram->wirelessPadID[chan];
    __OSUnlockSramEx(FALSE);
    return id;
}

void OSSetWirelessID(s32 chan, u16 id) {
    OSSramEx* sram;
    sram = __OSLockSramEx();

    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        __OSUnlockSramEx(TRUE);
    } else {
        __OSUnlockSramEx(FALSE);
    }
}

BOOL __OSGetRTCFlags(u32* flags) {
    BOOL err;
    u32 cmd;

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    cmd = 0x21000800;
    err = FALSE;
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_READ, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);
    *flags = cmd;

    return !err;
}

BOOL __OSClearRTCFlags() {
    BOOL err;
    u32 cmd;
    u32 data = 0;

    if (!EXILock(EXI_CHAN_0, EXI_DEV_INT, NULL)) {
        return FALSE;
    }

    if (!EXISelect(EXI_CHAN_0, EXI_DEV_INT, EXI_FREQ_8MHZ)) {
        EXIUnlock(EXI_CHAN_0);
        return FALSE;
    }

    cmd = 0xA1000800;
    err = FALSE;
    err |= !EXIImm(EXI_CHAN_0, &cmd, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIImm(EXI_CHAN_0, &data, sizeof(u32), EXI_WRITE, NULL);
    err |= !EXISync(EXI_CHAN_0);
    err |= !EXIDeselect(EXI_CHAN_0);
    EXIUnlock(EXI_CHAN_0);

    return !err;
}
