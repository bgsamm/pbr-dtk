#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x138
class GSlightNode : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x8];
    /* 0x10C */ u32 _10c;
    /* 0x110 */ u8 _pad_110[0x28];

public:
    GSlightNode(GSobject *parentObject, GSnodeData *data);

    u32 get_10c() const {
        return _10c;
    }
};
