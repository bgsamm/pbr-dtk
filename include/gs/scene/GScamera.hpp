#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x264
class GScamera : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x160];

public:
    GScamera(GSobject *parentObject, GSnodeData *data);

    static void fn_801DEEF8(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
