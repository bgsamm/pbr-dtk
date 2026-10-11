#pragma once

#include <revolution/types.h>

struct Unk8000748C {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u8 unk02[4];
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 unk07[9];
    /* 0x10 */ u32 _10;
    // size: unknown
};

extern "C" {
// TODO Replace with proper imports
void fn_8000764C(Unk8000748C *obj);
void fn_800077C0(Unk8000748C *obj);
}
