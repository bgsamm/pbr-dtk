#pragma once

#include <revolution/types.h>

// Second argument of fn_8015AAF0 and fn_8015ABD8; the same layout is used for the eight slots at 0x68.
// Only the members read by the decompiled functions are named.
struct Unk8015AAF0 {
    /* 0x00 */ void *_00;
    /* 0x04 */ u32 _04;
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ s16 _10;
    /* 0x12 */ s16 _12;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u8 _18;
    /* 0x19 */ u8 _19;
    /* 0x1A */ u8 _1A;
    /* 0x1B */ u8 _1B;
    /* 0x1C */ s16 _1C;
    /* 0x1E */ s16 _1E;
    /* 0x20 */ s16 _20;
    /* 0x22 */ s16 _22;
    /* 0x24 */ s16 _24;
    /* 0x26 */ s16 _26;
    /* 0x28 */ u8 _28;
    /* 0x29 */ u8 unk29[3];
    /* 0x2C */ u32 _2C;
    /* 0x30 */ u32 _30;
    /* 0x34 */ u32 _34;
    /* 0x38 */ u32 _38;
    /* 0x3C */ u32 _3C;
    /* 0x40 */ u32 _40;
    /* 0x44 */ u8 _44;
    /* 0x45 */ u8 unk45[0x14];
    /* 0x59 */ u8 _59;
    /* 0x5A */ u8 _5A;
    /* 0x5B */ u8 unk5B[1];
    /* 0x5C */ u32 _5C;
    /* 0x60 */ u32 _60;
    /* 0x64 */ u8 _64;
    /* 0x65 */ u8 unk65[3];
    /* 0x68 */ Unk8015AAF0 *_68[8];
    /* 0x88 */ u8 _88;
    /* 0x89 */ u8 unk89[0x1B];
    // size: 0xA4 (allocation size in fn_8015AAF0)
};
