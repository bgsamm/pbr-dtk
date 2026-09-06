#pragma once

#include "gs/scene/GShierMemObject.hpp"

#define ANIM_TYPE_ONESHOT 0
#define ANIM_TYPE_CYCLE 1
#define ANIM_TYPE_OSCILLATE 2

#define ANIM_FLAG_PLAYING (1 << 0)
#define ANIM_FLAG_STEPPED (1 << 1)
#define ANIM_FLAG_LOOPED (1 << 2)
#define ANIM_FLAG_FINISHED (1 << 3)
#define ANIM_FLAG_LOCKED (1 << 4)

struct GSnodeAnimData;
class GSanimationObject;

// Size: 0x10
class GSanimationPlayer : public GShierMemObject {
private:
    /* 0x0 */ GSnodeAnimData *mAnimData;
    /* 0x4 */ u16 mAnimType;
    /* 0x6 */ u16 mFlags;
    /* 0x8 */ f32 mSpeed;
    /* 0xc */ f32 mCursor;

public:
    GSanimationPlayer()
        : mAnimData(NULL), mAnimType(0), mFlags(ANIM_FLAG_FINISHED | ANIM_FLAG_LOOPED), mSpeed(1.f), mCursor(0.f) {}

    bool isPlaying() const {
        return mAnimData && (mFlags & ANIM_FLAG_PLAYING);
    }

    bool isFinished() const {
        return (mFlags & ANIM_FLAG_FINISHED) || !isPlaying();
    }

    void setFlag(u16 flag) {
        mFlags |= flag;
    }

    void startAnimation(GSnodeAnimData *animData, f32 startTime, f32 speed, u16 animType) {
        if (!(mFlags & ANIM_FLAG_LOCKED)) {
            mAnimData = animData;
            mCursor = startTime;
            mSpeed = speed;
            // TODO(samm) Revisit this
            mAnimType = animType & 0xff;
            mFlags = ANIM_FLAG_STEPPED | ANIM_FLAG_PLAYING;
        }
    }

    void stop() {
        if (!(mFlags & ANIM_FLAG_LOCKED)) {
            mFlags &= ~ANIM_FLAG_PLAYING;
        }
    }

    void updateCursor(f32 deltaTime);
    void updateChannels(GSanimationObject *object, bool blend);
};
