#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

class GSrenderLight;

// NOTE(samm) Name known from RTTI
// Size: 0x138
class GSlight : public GSnull {
public: // TODO(samm) Make private
    /* 0x104 */ u32 _104;
    /* 0x108 */ u8 _pad_108[0x4];
    /* 0x10C */ u32 _10c;
    /* 0x110 */ GScolor _110;
    /* 0x114 */ u8 _pad_114[0x1c];
    /* 0x130 */ GSrenderLight *_130;
    /* 0x134 */ GSrenderLight *_134;

public:
    GSlight(GSobject *parentObject, GSnodeData *data);

    // TODO(samm) Names

    u32 checkLightFlag(u32 flag) const {
        return (_104 & flag) == flag;
    }

    u32 get_10c() const {
        return _10c;
    }

    GSrenderLight *get_130() const {
        return _130;
    }

    GSrenderLight *get_134() const {
        return _134;
    }

    static void fn_801E6BB0(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
