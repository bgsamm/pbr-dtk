#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x138
class GSlight : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x8];
    /* 0x10C */ u32 _10c;
    /* 0x110 */ u8 _pad_110[0x28];

public:
    GSlight(GSobject *parentObject, GSnodeData *data);

    u32 get_10c() const {
        return _10c;
    }

    static void fn_801E6BB0(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
