#pragma once

#include "gs/scene/GSanimationObject.hpp"

class GSchannelData;

// NOTE(samm) Name known from RTTI
// Size: 0x38
class GSmaterial : public GSanimationObject {
protected:
    /* 0x08 */ u8 _pad_8[0x30];

public:
    static void fn_801EC9AC(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
