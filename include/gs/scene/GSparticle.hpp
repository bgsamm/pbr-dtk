#pragma once

#include "gs/scene/GSnull.hpp"

#include <revolution.h>

struct _UnkParticleStruct_1 {
    /* 0x000 */ u8 _pad_0[0x148];
    /* 0x148 */ u16 _148;
};

// NOTE(samm) Name known from RTTI
// Size: 0x140
class GSparticle : public GSnull {
    // TODO(samm) Make private
public:
    /* 0x104 */ u32 _104;
    /* 0x108 */ f32 _108;
    /* 0x10C */ f32 _10c;
    /* 0x110 */ f32 _110;
    /* 0x114 */ u8 _pad_114[0x24];
    /* 0x138 */ _UnkParticleStruct_1 *_138;
    /* 0x13c */ u8 _pad_13c[0x4];

public:
    GSparticle(GSobject *parentObject, GSnodeData *data);

    /* 0x08 */ virtual ~GSparticle();
    /* 0x0C */ virtual void update(f32 deltaTime);
    /* 0x10 */ virtual void initTransform(bool recursive);
    /* 0x14 */ virtual void updateTransform();

    _UnkParticleStruct_1 *get_138() const {
        return _138;
    }

    // TODO(samm) Name
    bool _unkCondition1() const {
        // TODO(samm) Really??
        if ((_104 & (1 << 0))) {
            return true;
        }
        if (_138 && (_138->_148 & (1 << 0))) {
            return true;
        }
        return false;
    }
};
