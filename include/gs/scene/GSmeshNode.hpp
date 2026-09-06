#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x18c
class GSmeshNode : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x88];

public:
    GSmeshNode(GSobject *parentObject, GSnodeData *data);
};
