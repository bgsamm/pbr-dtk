#pragma once

#include <revolution/types.h>

struct Unk80024914 {
    /* 0x00 */ void *_00;
    /* 0x04 */ u8 unk04[4];
    /* 0x08 */ u8 _08;
    /* 0x09 */ u8 unk09[3];
    /* 0x0C */ u32 _0C;
    // size: unknown
};

/* lbl_8063E9B0 */ extern Unk80024914 *lbl_8063E9B0;

extern "C" {
// TODO Replace with proper imports
void fn_80025024(Unk80024914 *obj);
}
