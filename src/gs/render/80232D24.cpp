#include "gs/GSrender.hpp"

#include <cstring>

#include "common.hpp"

void GSrender::configureColorChannel(
    u32 channel, u32 chanFlags, GXColorSrc ambSrc, GXColorSrc matSrc, u32 lightCount, GSrenderLight **lights,
    GXAttnFn attnFn, GXDiffuseFn diffFn
) {
    u32 colorChan = channel;
    u32 alphaChan = channel + 2;
    bool enable = lights && lightCount;

    if (!enable) {
        attnFn = GX_AF_NONE;
        diffFn = GX_DF_NONE;
    } else if (attnFn == GX_AF_SPEC) {
        diffFn = GX_DF_NONE;
    } else if (attnFn == GX_AF_NONE) {
        for (u32 i = 0; i < lightCount; i++) {
            if (lights[i] && lights[i]->mType == GS_LIGHT_SPOT) {
                attnFn = GX_AF_SPOT;
                break;
            }
        }
    }

    if ((chanFlags & (1 << 0))) {
        // TODO(samm) Certainly not, right?
        mState->mCurr.mChannels[colorChan].mEnable = enable;
        mState->mCurr.mChannels[colorChan].mAmbSrc = ambSrc;
        mState->mCurr.mChannels[colorChan].mMatSrc = matSrc;
        mState->mCurr.mChannels[colorChan].mLightMask = GX_LIGHT_NULL;
        mState->mCurr.mChannels[colorChan].mDiffFn = diffFn;
        mState->mCurr.mChannels[colorChan].mAttnFn = attnFn;

        if (enable) {
            // TODO(samm) #define max lights
            for (u32 i = 0; i < 8; i++) {
                if (i < lightCount) {
                    mState->mCurr.mChannels[colorChan].mLights[i] = lights[i];
                } else {
                    mState->mCurr.mChannels[colorChan].mLights[i] = NULL;
                }
            }
        } else {
            memset(mState->mCurr.mChannels[colorChan].mLights, 0, sizeof(mState->mCurr.mChannels[colorChan].mLights));
        }

        mState->mChanCtrlFlags |= (1 << colorChan);
    }

    if ((chanFlags & (1 << 1))) {
        // TODO(samm) Certainly not, right?
        mState->mCurr.mChannels[alphaChan].mEnable = enable;
        mState->mCurr.mChannels[alphaChan].mAmbSrc = ambSrc;
        mState->mCurr.mChannels[alphaChan].mMatSrc = matSrc;
        mState->mCurr.mChannels[alphaChan].mLightMask = GX_LIGHT_NULL;
        mState->mCurr.mChannels[alphaChan].mDiffFn = diffFn;
        mState->mCurr.mChannels[alphaChan].mAttnFn = attnFn;

        if (enable) {
            // TODO(samm) #define max lights
            for (u32 i = 0; i < 8; i++) {
                if (i < lightCount) {
                    mState->mCurr.mChannels[alphaChan].mLights[i] = lights[i];
                } else {
                    mState->mCurr.mChannels[alphaChan].mLights[i] = NULL;
                }
            }
        } else {
            memset(mState->mCurr.mChannels[alphaChan].mLights, 0, sizeof(mState->mCurr.mChannels[colorChan].mLights));
        }

        mState->mChanCtrlFlags |= (1 << alphaChan);
    }

    mState->_0 |= (1 << 2);
}

void GSrender::configureTevStage(u8 stage, GStevMode mode) {
    switch (mode) {
        case GS_TEV_MODE_MODULATE:
            // Color = RASC * TEXC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
            // Alpha = RASA * TEXA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
            break;
        case GS_TEV_MODE_DECAL:
            // Color = (1 - TEXA) * RASC + TEXA * TEXC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_RASC, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
            // Alpha = RASA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            break;
        case GS_TEV_MODE_BLEND:
            // Color = (1 - TEXC) * RASC + TEXC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_RASC, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
            // Color = TEXA * RASA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
            break;
        case GS_TEV_MODE_REPLACE:
            // Color = TEXC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            // Alpha = TEXA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            break;
        case GS_TEV_MODE_PASSCLR:
            // Color = RASC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
            // Alpha = RASA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            break;
        case GS_TEV_MODE_ADD_TEX:
            // Color = CPREV + TEXC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            // Alpha = APREV + TEXA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            break;
        case GS_TEV_MODE_ADD_RAS:
            // Color = CPREV + RASC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            // Alpha = APREV + RASA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            break;
        case GS_TEV_MODE_ADD_MODULATE:
            // Color = CPREV + TEXC * RASC
            setTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevColorIn(stage, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_CPREV);
            // Alpha = APREV + TEXA * RASA
            setTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            setTevAlphaIn(stage, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_APREV);
            break;
    }
}

void GSrender::configureTexCoordGen(
    u8 texCoord, GXTexGenType type, GXTexGenSrc src, Mtx texMtx, GXBool normalize, Mtx postMtx
) {
    bool hasMtx = false;

    mState->mCurr.mTexCoordGens[texCoord].mType = type;
    mState->mCurr.mTexCoordGens[texCoord].mSrc = src;
    mState->mCurr.mTexCoordGens[texCoord].mNormalize = normalize;
    mState->mCurr.mTexCoordGens[texCoord].mLight = NULL;

    if (!texMtx) {
        mState->mCurr.mTexCoordGens[texCoord].mTexMtx = GX_IDENTITY;
    } else {
        mState->mCurr.mTexCoordGens[texCoord].mTexMtx = GX_TEXMTX0 + texCoord * 3;
        hasMtx = true;
    }

    if (!postMtx) {
        mState->mCurr.mTexCoordGens[texCoord].mPostMtx = GX_PTIDENTITY;
    } else {
        mState->mCurr.mTexCoordGens[texCoord].mPostMtx = GX_PTTEXMTX0 + texCoord * 3;
        hasMtx = true;
    }

    if (hasMtx) {
        if (texMtx) {
            if (type == GX_TG_MTX2x4) {
                GXLoadTexMtxImm(texMtx, mState->mCurr.mTexCoordGens[texCoord].mTexMtx, GX_MTX2x4);
            } else {
                GXLoadTexMtxImm(texMtx, mState->mCurr.mTexCoordGens[texCoord].mTexMtx, GX_MTX3x4);
            }
        }

        if (postMtx) {
            GXLoadTexMtxImm(postMtx, mState->mCurr.mTexCoordGens[texCoord].mPostMtx, GX_MTX3x4);
        }
    }

    mState->mTexGenFlags |= (1 << texCoord);
    mState->_0 |= (1 << 0);
}
