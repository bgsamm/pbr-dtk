#pragma once

#include "gs/GSthread.hpp"

#include <revolution/types.h>

struct Unk80226364_00 {
    /* 0x000 */ u32 _00;
    /* 0x004 */ u32 _04;
    /* 0x008 */ u32 _08;
    /* 0x00C */ u32 _0C;
    /* 0x010 */ u8 _10;
    /* 0x011 */ u8 _11;
    /* 0x012 */ u8 unk012[2];
    /* 0x014 */ u32 _14;
    /* 0x018 */ u8 unk018[4];
    /* 0x01C */ GSthreadHandle *_1C;
    /* 0x020 */ u8 unk020[0x200];
    /* 0x220 */ u32 _220;
    // size: 0x224
};

struct Unk80226364_04 {
    /* 0x00 */ Unk80226364_00 *_00;
    /* 0x04 */ u32 _04;
    // size: unknown
};

struct Unk80226364 {
    /* 0x00 */ u8 unk00[4];
    /* 0x04 */ Unk80226364_04 *_04;
    /* 0x08 */ u8 unk08[0x18];
    /* 0x20 */ u32 _20;
    // size: unknown
};

struct Unk80227558 {
    /* 0x00 */ u8 unk00[0x30];
    /* 0x30 */ u32 _30;
    /* 0x34 */ u32 _34;
    // size: unknown
};

/* lbl_8063F640 */ extern Unk80226364 *lbl_8063F640;

extern "C" {
// TODO Replace with proper imports
u32 fn_80226910(Unk80226364 *obj);
u32 fn_80228B84(Unk80226364_00 *obj);
void fn_80228CF8(Unk80226364_00 *obj);
void fn_80227574();
}
