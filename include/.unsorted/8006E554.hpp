#pragma once

#include <revolution/types.h>

struct Unk8006E554 {
    /* 0x000 */ u32 _00;
    /* 0x004 */ u32 _04;
    /* 0x008 */ u32 _08;
    /* 0x00C */ u8 unk00C[8];
    /* 0x014 */ u32 _14;
    /* 0x018 */ u8 unk018[0x408];
    /* 0x420 */ s32 _420[];
    // size: unknown
};

/* lbl_8063D4D0 */ extern Unk8006E554 *lbl_8063D4D0;
