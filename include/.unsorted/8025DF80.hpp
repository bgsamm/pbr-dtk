#pragma once

#include <revolution/types.h>

struct Unk8025DF80 {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ u32 _04;
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ u8 *_10;
    /* 0x14 */ u32 _14;
    // size: unknown
};

/* lbl_8063F998 */ extern Unk8025DF80 *lbl_8063F998;

extern "C" {
Unk8025DF80 *fn_8025DFD0(void);
u8 *fn_8025E31C(Unk8025DF80 *obj);
}
