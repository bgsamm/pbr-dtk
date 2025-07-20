#include "version.hpp"

#include <revolution/os.h>

#include "gs/GScache.hpp"

// TODO clean up this module

#define BUFFER_SIZE (512)
#define NUM_BUFFERS (32)

struct GSscratchpadBuffer {
    /* 0x0 */ u8 mBufIdx;
    /* 0x1 */ u8 mChunkLen;
    /* 0x4 */ UnkFunc2 mCallback;
};

/* lbl_80491370 */ static GSscratchpadBuffer sBufferPool[NUM_BUFFERS];

static u32 lbl_8063F2F8;
/* lbl_8063F2FC */ static void *sScratchpadBase;
static void *lbl_8063F300;
static bool lbl_8063F304;
/* lbl_8063F308 */ static u32 sActiveBuffers;

void GScache::fn_801DB81C(u8 param1) {
    sActiveBuffers = 0;

    for (u32 i = 0; i < NUM_BUFFERS; i++) {
        sBufferPool[i].mBufIdx = 0xff;
    }

    LCEnable();

    sScratchpadBase = LCGetBase();
    lbl_8063F2F8 = param1 * BUFFER_SIZE;

    if (param1 != 0) {
        fn_801DB92C(0, param1, true);

        sBufferPool[0].mBufIdx = 0;
        sBufferPool[0].mChunkLen = param1;
    }

    lbl_8063F304 = false;
}

void GScache::fn_801DB92C(u8 start, u8 count, bool param3) {
    u32 bufFlag = 0x80000000;
    while (start-- > 0) {
        bufFlag >>= 1;
    }

    while (count-- > 0) {
        if (param3 == true) {
            sActiveBuffers |= bufFlag;
        }
        else {
            sActiveBuffers &= ~bufFlag;
        }
        bufFlag >>= 1;
    }
}

bool GScache::fn_801DB978(u8 param1) {
    asm {
        mflr    r3
        stw     r3, lbl_8063F300
    }

    fn_801DB81C(param1);

    if (param1 == 0) {
        return true;
    }
    else {
        asm {
            lwz     r3, sScratchpadBase
            lwz     r5, lbl_8063F2F8
            add     r3, r3, r5
            subi    r1, r3, 8
            li      r3, -1
            stw     r3, 0x0(r1)
            lwz     r3, lbl_8063F300
            mtlr    r3
            blr
        }
    }

    return true;
}

void GScache::fn_801DB9FC() {
    if (lbl_8063F304 == true) {
        return;
    }

    u32 i;
    GSscratchpadBuffer *buf = sBufferPool;
    // This is funky but it matches
    for (i = NUM_BUFFERS; i-- > 0; buf++) {
        if (buf->mBufIdx == 0xff) {
            continue;
        }

        if (buf->mCallback != NULL) {
            buf->mCallback(0, (u8 *)sScratchpadBase + buf->mBufIdx * BUFFER_SIZE, buf->mChunkLen);
        }
    }

    lbl_8063F304 = true;
}

void GScache::fn_801DBA8C() {
    if (lbl_8063F304 == false) {
        return;
    }

    u32 i;
    GSscratchpadBuffer *buf = sBufferPool;
    // This is funky but it matches
    for (i = NUM_BUFFERS; i-- > 0; buf++) {
        if (buf->mBufIdx == 0xff) {
            continue;
        }

        if (buf->mCallback != NULL) {
            buf->mCallback(1, (u8 *)sScratchpadBase + buf->mBufIdx * BUFFER_SIZE, buf->mChunkLen);
        }
    }

    lbl_8063F304 = false;
}
