#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x264
class GScamera : public GSnull {
public:
    /* 0x104 */ u32 _104;
    /* 0x108 */ u8 _pad_108[0x44];
    /* 0x14C */ f32 _14c[7];
    /* 0x168 */ f32 _168;
    /* 0x16C */ u8 _pad_16c[0x40];
    /* 0x1AC */ Vec _1ac;
    /* 0x1B8 */ Vec _1b8;
    /* 0x1C4 */ Vec _1c4;
    /* 0x1D0 */ u8 _pad_1d0[0x4];
    /* 0x1D4 */ Mtx _1d4;
    /* 0x204 */ Mtx _204;
    /* 0x234 */ Mtx _234;

    GScamera(GSobject *parentObject, GSnodeData *data);

    static void fn_801DEEF8(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
