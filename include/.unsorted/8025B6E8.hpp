#pragma once

#include <revolution/types.h>

struct Unk80424F60 {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ u32 _20;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 _28;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ u8 unk30[8];
    /* 0x38 */ u32 _38;
    /* 0x3C */ u8 unk3C[0x104];
    // size: 0x140
};

struct Unk80425110 {
    /* 0x00 */ u8 unk00[8];
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ u8 unk10[0x24];
    // size: 0x34
};

struct Unk8025CEF8 {
    /* 0x0000 */ u8 unk0000[0x6050];
    /* 0x6050 */ u32 _6050;
    /* 0x6054 */ u32 _6054;
    /* 0x6058 */ u32 _6058;
    // size: unknown
};
