#include "gs/scene/GSanimationPlayer.hpp"

#include "gs/GSsceneData.hpp"

#include "version.hpp"

void GSanimationPlayer::updateCursor(f32 deltaTime) {
    if (!mAnimData || !(mFlags & ANIM_FLAG_PLAYING) || (mFlags & ANIM_FLAG_FINISHED)) {
        return;
    }

    mCursor += deltaTime * mSpeed;
    if (mCursor < 0.f) {
        mFlags |= ANIM_FLAG_LOOPED;

        switch (mAnimType) {
            case ANIM_TYPE_CYCLE:
                while (mCursor < 0.f) {
                    mCursor += mAnimData->mAnimLength;
                }
                break;
            case ANIM_TYPE_OSCILLATE:
                mCursor = -mCursor;
                if (mCursor > mAnimData->mAnimLength) {
                    f32 pos = mCursor / mAnimData->mAnimLength;
                    s32 nLoops = pos;
                    pos -= nLoops;

                    if (nLoops % 2 != 0) {
                        mCursor = mAnimData->mAnimLength * (1 - pos);
                    } else {
                        mCursor = mAnimData->mAnimLength * pos;
                        mSpeed = -mSpeed;
                    }
                } else {
                    mSpeed = -mSpeed;
                }
                break;
            default:
                mFlags |= ANIM_FLAG_FINISHED;
                mCursor = 0.f;
                break;
        }
    } else if (mCursor > mAnimData->mAnimLength) {
        mFlags |= ANIM_FLAG_LOOPED;

        switch (mAnimType) {
            case ANIM_TYPE_CYCLE:
                while (mCursor > mAnimData->mAnimLength) {
                    mCursor -= mAnimData->mAnimLength;
                }
                break;
            case ANIM_TYPE_OSCILLATE: {
                f32 pos = mCursor / mAnimData->mAnimLength;
                s32 nLoops = pos;
                pos -= nLoops;

                if (nLoops % 2 != 0) {
                    mCursor = mAnimData->mAnimLength * (1 - pos);
                    mSpeed = -mSpeed;
                } else {
                    mCursor = mAnimData->mAnimLength * pos;
                }
            } break;
            default:
                mFlags |= ANIM_FLAG_FINISHED;
                mCursor = mAnimData->mAnimLength;
                break;
        }
    }

    mFlags |= ANIM_FLAG_STEPPED;
}

void GSanimationPlayer::updateChannels(GSanimationObject *object, bool blend) {
    if (!mAnimData || !(mFlags & ANIM_FLAG_STEPPED)) {
        return;
    }

    GSnodeAnimChannel *channel = mAnimData->mChannels;
    u16 channelCount = mAnimData->mChannelCount;

    for (s32 i = 0; i < channelCount; i++, channel++) {
        if (channel->mStepCallback) {
            channel->mStepCallback(object, channel, mCursor, blend);
        }
    }

    mFlags &= ~ANIM_FLAG_STEPPED;
}
