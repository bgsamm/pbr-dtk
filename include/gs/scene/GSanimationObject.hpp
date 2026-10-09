#pragma once

#include "gs/scene/GSanimationPlayer.hpp"
#include "gs/scene/GShierMemObject.hpp"

struct GSkeyframeData;

// NOTE(samm) Name known from RTTI
class GSanimationObject : public GShierMemObject {
protected:
    /* 0x000 */ GSkeyframeData *mAnimData;
    /* 0x004 */ GSanimationPlayer *mPlayer;

protected:
    GSkeyframeData *findAnimData(u16 animId);

public:
    GSanimationObject(GSkeyframeData *animData);
    ~GSanimationObject();

    void update(f32 deltaTime);
    void startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed);

    u16 getAnimId() const {
        if (mPlayer) {
            return mPlayer->getAnimId();
        }
        return GS_ANIM_NULL;
    }

    f32 getAnimProgress() const {
        if (mPlayer) {
            return mPlayer->getAnimProgress();
        }
        return 0.f;
    }

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
    GSblendObject(GSkeyframeData *anims);
    ~GSblendObject();

    void update(f32 deltaTime);
    void startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed);
    void blendAnimation(u16 animId, u32 animType, f32 startTime, f32 speed, f32 blendFactor);

    u16 getBlendAnimId() const {
        if (mBlendPlayer) {
            return mBlendPlayer->getAnimId();
        }
        return GS_ANIM_NULL;
    }

    f32 getBlendAnimProgress() const {
        if (mBlendPlayer) {
            return mBlendPlayer->getAnimProgress();
        }
        return 0.f;
    }

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
