#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x264
class GScameraNode : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x160];

public:
    GScameraNode(GSobject *parentObject, GSnodeData *data);
};
