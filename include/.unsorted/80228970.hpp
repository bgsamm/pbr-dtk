#pragma once

#include ".unsorted/80226364.hpp"

#include <revolution/types.h>

struct Unk8022898C {
    /* 0x0 */ u16 _00;
    /* 0x4 */ u32 _04;
    // size: 0x8
};

struct Unk80228A54 {
    /* 0x000 */ u8 unk000[0x940];
    /* 0x940 */ u32 _940;
    // size: unknown
};

s32 fn_80228970(u32 a);
u32 fn_8022898C(u32 a, u32 b, u32 c, u32 d, u32 e);
u32 fn_80228A54(u32 a, u32 b, u32 c, u32 d, u32 e);

extern "C" {
// TODO Replace with proper imports
u32 fn_8022A6A4(u32 a, u32 b, Unk8022898C *c, u32 count, u32 d);
u32 fn_8022CFB8(u32 a, u32 b);
u32 fn_8022D02C(Unk80228A54 *p, u32 a);
}
