#pragma once

#include <revolution/types.h>

struct Unk80250F18;
typedef void (*Unk80250F18Callback)(Unk80250F18 *obj);

struct Unk80250F18_08 {
    /* 0x00 */ u8 unk00[6];
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 unk07[0xB9];
    // size: 0xC0
};

struct Unk80250F18 {
    /* 0x000 */ u16 _00;
    /* 0x002 */ u16 _02;
    /* 0x004 */ void *_04;
    /* 0x008 */ Unk80250F18_08 *_08;
    /* 0x00C */ void *_0C;
    /* 0x010 */ u8 unk010[0x14];
    /* 0x024 */ u32 _24;
    /* 0x028 */ u32 _28;
    /* 0x02C */ u32 _2C[32];
    /* 0x0AC */ u32 _AC[32];
    /* 0x12C */ u8 _12C[32];
    /* 0x14C */ u32 _14C;
    /* 0x150 */ u32 _150;
    /* 0x154 */ Unk80250F18Callback _154;
    /* 0x158 */ u8 unk158[0x18];
    // size: 0x170
};

/* lbl_804FDAB0 */ extern Unk80250F18 lbl_804FDAB0;

extern "C" {
// TODO Replace with proper imports
void fn_80250FF8(Unk80250F18 *obj, u16 count);
void fn_80251AF8(Unk80250F18 *obj, s16 a);
void fn_80253A74(Unk80250F18 *obj, u32 a, u32 b, u32 c);
void fn_80253ABC(Unk80250F18 *obj, s16 a);
void fn_80253AEC(Unk80250F18 *obj, s16 a);
void fn_80253B2C(Unk80250F18 *obj, u32 a, u32 b, u32 c);
void fn_80254260(Unk80250F18 *obj, u32 a, u32 b, u32 c);
void fn_80254334(Unk80250F18 *obj, u32 a, u32 b, u32 c);
}
