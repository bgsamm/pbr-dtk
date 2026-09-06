#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x148
class GSvolumeNode : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x44];

public:
    GSvolumeNode(GSobject *parentObject, GSnodeData *data);
};
