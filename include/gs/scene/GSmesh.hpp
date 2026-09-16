#pragma once

#include "gs/scene/GSanimationObject.hpp"
#include "gs/scene/GShierMemObject.hpp"

class GSnull;
class GSmaterial : public GSanimationObject {};

// NOTE(samm) Name known from RTTI
class GSmesh : public GShierMemObject {
    // TODO(samm) Make private
public:
    /* 0x00 */ u8 _pad_0[0xc];
    // TODO(samm) Type?
    /* 0x0C */ GSmaterial *_c;
    /* 0x10 */ u8 _pad_10[0x4];
    // TODO(samm) Type?
    /* 0x14 */ GSmaterial *_14;

    void lockAnimation() {
        if (_14) {
            _14->lockAnimation();
        }
    }

    void clearAnimation() {
        if (_14) {
            _14->clearAnimation();
        }
    }
};
