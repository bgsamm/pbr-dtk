#pragma once

#include "gs/scene/GSanimationPlayer.hpp"
#include "gs/scene/GShierMemObject.hpp"

struct GSnodeAnimData;

// NOTE(samm) Name known from RTTI
class GSanimationObject : public GShierMemObject {
protected:
    /* 0x000 */ GSnodeAnimData *mAnimData;
    /* 0x004 */ GSanimationPlayer *mPlayer;

protected:
    GSnodeAnimData *findAnimData(u16 animId);
    void update(f32 deltaTime);

public:
    GSanimationObject(GSnodeAnimData *animData);
    ~GSanimationObject();

    void startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed);

    void lockAnimation() {
        if (mPlayer) {
            mPlayer->lock();
        }
    }

    void clearAnimation() {
        if (mPlayer) {
            mPlayer->reset();
        }
    }
};

// NOTE(samm) Name known from RTTI
class GSblendObject : public GSanimationObject {
protected:
    /* 0x008 */ GSanimationPlayer *mBlendPlayer;
    /* 0x00C */ f32 mBlendFactor;

public:
    GSblendObject(GSnodeAnimData *anims);
    ~GSblendObject();

    void update(f32 deltaTime);
    void startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed);
    void blendAnimation(u16 animId, u32 animType, f32 startTime, f32 speed, f32 blendFactor);

    void lockAnimation() {
        GSanimationObject::lockAnimation();
        if (mBlendPlayer) {
            mBlendPlayer->lock();
        }
    }

    void clearAnimation() {
        GSanimationObject::clearAnimation();
        if (mBlendPlayer) {
            mBlendPlayer->reset();
        }
    }

    void setBlendFactor(f32 blendFactor) {
        mBlendFactor = blendFactor;
    }
};
