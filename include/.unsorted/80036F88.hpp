#pragma once

#include <revolution/types.h>

struct Unk80036F88 {
    /* 0x000 */ u32 _00;
    /* 0x004 */ u8 unk004[0xBF2];
    /* 0xBF6 */ u8 _BF6;
    /* 0xBF7 */ u8 unkBF7;
    /* 0xBF8 */ u16 _BF8;
    /* 0xBFA */ u8 unkBFA[0x56];
    /* 0xC50 */ u32 _C50;
    /* 0xC54 */ u32 _C54;
    /* 0xC58 */ u8 unkC58[0xAC];
    /* 0xD04 */ u8 _D04;
    // size: unknown
};

extern "C" {
void fn_8003D82C(Unk80036F88 *obj, u32 kind);

// TODO Replace with proper imports
void fn_8003D4D4(Unk80036F88 *obj, u32 kind);
}
