#pragma once

#include <revolution/types.h>

struct Unk800097D8 {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 _01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 _03;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 unk05[8];
    /* 0x0D */ u8 _0D;
    /* 0x0E */ u8 unk0E[0xC2];
    /* 0xD0 */ u32 _D0;
    // size: unknown
};

extern "C" {
void fn_80009808(u8 v);

// TODO Replace with proper imports
void fn_8000A0F0(Unk800097D8 *obj);
void fn_8000A54C(Unk800097D8 *obj);
}
