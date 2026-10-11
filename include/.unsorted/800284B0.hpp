#pragma once

#include <revolution/gx/GXStruct.h>
#include <revolution/mtx.h>
#include <revolution/types.h>

#include ".unsorted/80024914.hpp"

// Tagged value: the tag at 0x00 says whether the value at 0x04 is an integer or a float.
struct Unk800284B0Value {
    /* 0x00 */ s16 _00;
    /* 0x02 */ u8 unk02[2];
    /* 0x04 */ union {
        u32 u;
        f32 f;
    } _04;
    // size: unknown
};

struct Unk800284B0 {
    /* 0x000 */ u32 mFlags;
    /* 0x004 */ u8 unk004[0x508];
    /* 0x50C */ u16 _50C;
    /* 0x50E */ u16 _50E;
    /* 0x510 */ u16 _510;
    /* 0x512 */ u16 _512;
    /* 0x514 */ u16 _514;
    /* 0x516 */ u8 _516;
    /* 0x517 */ u8 unk517;
    /* 0x518 */ u32 _518;
    /* 0x51C */ u16 _51C;
    /* 0x51E */ u8 unk51E[2];
    /* 0x520 */ u8 _520;
    /* 0x521 */ u8 unk521[0x85F];
    /* 0xD80 */ f32 _D80;
    /* 0xD84 */ f32 _D84;
    /* 0xD88 */ u8 _D88;
    /* 0xD89 */ u8 unkD89[0x2B];
    /* 0xDB4 */ Vec _DB4;
    // size: unknown
};

extern "C" {
// TODO Replace with proper imports
u32 fn_800282E0(Unk800284B0Value *value);
u32 fn_800283B0(Unk800284B0Value *value);
}
