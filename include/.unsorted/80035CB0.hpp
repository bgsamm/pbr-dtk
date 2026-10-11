#pragma once

#include <revolution/types.h>

// Only the fields used by the decompiled functions are named; the roles are not established yet.

struct Unk80035CB0Sub {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 unk07;
    /* 0x08 */ u16 _08;
    /* 0x0A */ u16 _0A;
    /* 0x0C */ u16 _0C;
    /* 0x0E */ u8 unk0E[0x0A];
    /* 0x18 */ u16 _18;
    /* 0x1A */ u8 unk1A[0x0A];
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 _25;
    /* 0x26 */ u8 _26;
    /* 0x27 */ u8 _27;
    // size: unknown
};

struct Unk80035CB0 {
    /* 0x000 */ u32 _00;
    /* 0x004 */ u32 _04;
    /* 0x008 */ u32 _08;
    /* 0x00C */ u32 _0C;
    /* 0x010 */ u32 _10;
    /* 0x014 */ u32 _14;
    /* 0x018 */ u8 unk18[0x14];
    /* 0x02C */ u32 _2C;
    /* 0x030 */ u8 unk30[0x300];
    /* 0x330 */ u8 _330;
    /* 0x331 */ u8 unk331[3];
    /* 0x334 */ u32 mFlags;
    /* 0x338 */ u8 unk338[0x638];
    /* 0x970 */ Unk80035CB0Sub *_970;
    // size: 0x974 (allocation size in fn_80035D58)
};
