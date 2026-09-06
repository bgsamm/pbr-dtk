#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

// Size: 0x188
class GSjointNode : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x84];

public:
    GSjointNode(GSobject *parentObject, GSnodeData *data);
};
