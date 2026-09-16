#include "gs/scene/GSanimationObject.hpp"

#include "gs/GSsceneData.hpp"

#include "version.hpp"

GSanimationObject::GSanimationObject(GSnodeAnimData *animData) : mAnimData(animData), mPlayer(NULL) {
    if (animData) {
        mPlayer = new GSanimationPlayer();
    }
}

GSanimationObject::~GSanimationObject() {
    if (mPlayer) {
        delete mPlayer;
        mPlayer = NULL;
    }
}

void GSanimationObject::update(f32 deltaTime) {
    if (!mPlayer) {
        return;
    }

    if (mPlayer->isPlaying()) {
        mPlayer->updateCursor(deltaTime);
        mPlayer->updateChannels(this, false);

        if (mPlayer->isFinished()) {
            mPlayer->stop();
        }
    }
}

GSnodeAnimData *GSanimationObject::findAnimData(u16 animId) {
    GSnodeAnimData *anim = mAnimData;
    while (anim) {
        if (anim->mAnimId == animId) {
            return anim;
        }
        anim = anim->mNext;
    }

    return NULL;
}

void GSanimationObject::startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed) {
    if (!mPlayer) {
        return;
    }

    mPlayer->stop();

    GSnodeAnimData *animData = findAnimData(animId);
    if (animData) {
        mPlayer->startAnimation(animData, startTime, speed, animType);
    }
}

GSblendObject::GSblendObject(GSnodeAnimData *anims) : GSanimationObject(anims), mBlendPlayer(NULL), mBlendFactor(0.f) {
    if (mPlayer) {
        mBlendPlayer = new GSanimationPlayer();
    }
}

GSblendObject::~GSblendObject() {
    if (mBlendPlayer) {
        delete mBlendPlayer;
        mBlendPlayer = NULL;
    }
}

void GSblendObject::update(f32 deltaTime) {
    if (!mPlayer) {
        return;
    }

    bool baseAnimPlaying = mPlayer->isPlaying();
    bool blendAnimPlaying = mBlendPlayer && mBlendPlayer->isPlaying();

    if (baseAnimPlaying) {
        mPlayer->updateCursor(deltaTime);
    }

    if (blendAnimPlaying) {
        mBlendPlayer->updateCursor(deltaTime);
        mPlayer->setFlag(ANIM_FLAG_STEPPED);
        baseAnimPlaying = true;
    }

    if (baseAnimPlaying) {
        mPlayer->updateChannels(this, false);

        if (mPlayer->isFinished()) {
            mPlayer->stop();
        }
    }

    if (blendAnimPlaying) {
        mBlendPlayer->updateChannels(this, true);

        if (mBlendPlayer->isFinished()) {
            mBlendPlayer->stop();
        }
    }
}

void GSblendObject::startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed) {
    if (mBlendPlayer) {
        mBlendFactor = 0.f;

        if (mBlendPlayer->isPlaying()) {
            mBlendPlayer->stop();
        }
    }

    GSanimationObject::startAnimation(animId, animType, startTime, speed);
}

void GSblendObject::blendAnimation(u16 animId, u32 animType, f32 startTime, f32 speed, f32 blendFactor) {
    if (!mBlendPlayer) {
        return;
    }

    mBlendPlayer->stop();

    GSnodeAnimData *animData = findAnimData(animId);
    if (animData) {
        mBlendPlayer->startAnimation(animData, startTime, speed, animType);
    }

    mBlendFactor = blendFactor;
}
