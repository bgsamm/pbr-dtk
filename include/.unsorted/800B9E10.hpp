#pragma once

#include <revolution/types.h>

struct Unk800B9E10 {
    /* 0x000 */ f64 _00;
    /* 0x008 */ u16 _08;
    /* 0x00A */ u16 _0A;
    /* 0x00C */ u16 _0C;
    /* 0x00E */ u8 unk00E[2];
    /* 0x010 */ s32 _10;
    /* 0x014 */ u16 _14[32];
    /* 0x054 */ u32 _54[142];
    /* 0x28C */ u32 _28C[]; // array lengths inferred from the neighbouring offsets
    // size: unknown
};

/* lbl_8063EED8 */ extern Unk800B9E10 *lbl_8063EED8;

extern "C" {
u16 fn_800BA578(void);
u16 fn_800BA5CC(void);
}
