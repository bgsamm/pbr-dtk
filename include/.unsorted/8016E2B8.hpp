#pragma once

#include <revolution/types.h>

struct Unk8016E2B8 {
    /* 0x00 */ u32 _00[4];
    /* 0x10 */ s32 _10[26];
    /* 0x78 */ u8 _78[4];
    /* 0x7C */ u8 _7C[4];
    /* 0x80 */ u8 _80[4];
    // size: unknown (array lengths inferred from the neighbouring offsets)
};

/* lbl_8063F1C8 */ extern Unk8016E2B8 *lbl_8063F1C8;

extern "C" {
void fn_8016E2E4(u32 value);
s32 fn_8016E430(u8 i);
}
