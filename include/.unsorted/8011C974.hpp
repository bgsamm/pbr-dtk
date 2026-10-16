#pragma once

#include <revolution/types.h>

// The object returned by fn_8011C974.
// size: unknown
struct Unk8011C974 {
    /* 0x0000 */ u8 unk0000[0x4];
    /* 0x0004 */ u32 _0004;
    /* 0x0008 */ s32 _0008;
    /* 0x000C */ u8 unk000c[0x4];
    /* 0x0010 */ s32 _0010;
    /* 0x0014 */ u8 _0014;
    /* 0x0015 */ u8 unk0015;
    /* 0x0016 */ u16 _0016;
    /* 0x0018 */ u8 _0018;
    /* 0x0019 */ u8 unk0019[0x2];
    /* 0x001B */ u8 _001b;
    /* 0x001C */ u8 _001c[0x64];
    /* 0x0080 */ u8 _0080[0xA];
    /* 0x008A */ u8 _008a[0x6];
    /* 0x0090 */ u16 _0090;
    /* 0x0092 */ u16 _0092;
    /* 0x0094 */ u16 _0094;
    /* 0x0096 */ u8 unk0096[0x4];
    /* 0x009A */ u16 _009a;
    /* 0x009C */ u8 unk009c[0xA9];
    /* 0x0145 */ u8 _0145;
    /* 0x0146 */ u8 unk0146[0x1EB6];
    /* 0x1FFC */ u8 _1ffc[0x1FC];
    /* 0x21F8 */ u8 _21f8[0x2CD4];
    /* 0x4ECC */ u8 _4ecc[0x4];
    /* 0x4ED0 */ u8 unk4ed0[0x7738];
    /* 0xC608 */ u8 _c608[3][0x6EC];
};

extern "C" {
// TODO Replace with proper imports
Unk8011C974 *fn_8011C974();
}
