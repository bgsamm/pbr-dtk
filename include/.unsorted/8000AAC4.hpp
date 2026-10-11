#pragma once

#include <revolution/types.h>

struct Unk8000AAC4Sub {
    /* 0x00 */ u16 _00;
    /* 0x02 */ u8 _02;
    /* 0x03 */ u8 _03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u16 _06;
    /* 0x08 */ u32 _08;
    /* 0x0C */ u32 _0C;
    /* 0x10 */ s32 _10;
    // size: unknown
};

struct Unk8000AAC4 {
    /* 0x00 */ const void *_00;
    /* 0x04 */ Unk8000AAC4Sub *_04;
    // size: unknown
};
