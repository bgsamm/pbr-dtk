#pragma once

#include "gs/GSmath.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution.h>

class GSmesh;

struct _UnkModelStruct_1 {
    /* 0x0 */ u16 _0;
};

// TODO(samm) Move?
void fn_801EE044();

// Size: 0x18c
class GSmodel : public GSnull {
private:
    /* 0x104 */ u8 _pad_104[0x4];
    /* 0x108 */ GSboundingBox mBoundingBox;
    /* 0x124 */ u8 _pad_124[0x40];
    /* 0x164 */ _UnkModelStruct_1 *_164;
    /* 0x168 */ u8 _pad_168[0x24];

public:
    GSmodel(GSobject *parentObject, GSnodeData *data);

    // TODO(samm) Name
    bool checkDataFlag(u16 flag) const {
        return (_164->_0 & flag) == flag;
    }

    GSboundingBox *getBoundingBox() {
        return &mBoundingBox;
    }

    GSmesh *getMesh(u16 index) const;
    u16 countMeshes() const;
};
