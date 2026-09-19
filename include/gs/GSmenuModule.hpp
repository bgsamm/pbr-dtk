#pragma once

#include "gs/render/GSrenderModule.hpp"

class GSobject;

// NOTE(samm) Name known from RTTI
// Size: 0x120
class GSmenuModule : public GSrenderModule {
protected:
    /* 0x010 */ u8 _pad_10[0xfc];
    /* 0x10C */ u32 _10c;
    /* 0x110 */ u32 _110;
    /* 0x114 */ u8 _pad_114[0x4];

    static GSmenuModule *sInstance;

public:
    // TODO(samm) Names
    /* 0x08 */ virtual void update(f32 deltaTime);
    /* 0x0C */ virtual void fn_80236AE0();
    /* 0x10 */ virtual void fn_80236AE4();
    /* 0x14 */ virtual ~GSmenuModule();

    // TODO(samm) Names

    u32 get_10c() const {
        return _10c;
    }

    u32 get_110() const {
        return _110;
    }

    static GSmenuModule *getInstance() {
        return sInstance;
    }

    static void fn_80203950(GSobject *arg0);
};
