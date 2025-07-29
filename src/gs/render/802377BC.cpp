#include "global.hpp"

#include <revolution/base/PPCArch.h>

#include "gs/GSrender.hpp"

/* lbl_80496760 */ static f32 sProjectionMatrix[4][4];

void GSrenderManager::loadLights() {
    GSlight **light;
    u32 i;
    u8 nLights;

    if ((mState->_0 & (1 << 2)) == 0) {
        return;
    }

    if ((mState->_14 & (1 << 4)) == 0) {
        return;
    }

    nLights = mState->mNumLights;
    light = mState->mLights;
    for (i = 0; (u8)i < nLights; i++, light++) {
        (*light)->load(i, _16ec);
    }

    mState->_14 &= ~(1 << 4);
}

void GSrenderManager::setVertexFormat(GSvertexFormat *format) {
    GSVtxAttrArray *array;

    GXClearVtxDesc();
    GXSetVtxDescv(format->mVtxDescList);

    if (mState->mActiveFormat != format
        || (format->mFlags & GS_VERTEX_UPDATE_ARRAYS) == GS_VERTEX_UPDATE_ARRAYS
    ) {
        array = format->mAttrArrayList;
        while (array->mAttr != GX_VA_NULL) {
            GXSetArray((GXAttr)array->mAttr, array->mBasePtr, array->mStride);
            mFlags |= GS_RENDER_INVALIDATE_CACHE;
            array++;
        }
        mState->mActiveFormat = format;
    }

    GXVtxFmt vtxFmt = format->mVtxFmt;
    if (mState->mVertexFormats[vtxFmt] != format
        || (format->mFlags & GS_VERTEX_UPDATE_FORMAT) == GS_VERTEX_UPDATE_FORMAT
    ) {
        GXSetVtxAttrFmtv(vtxFmt, format->mVtxAttrFmtList);
        mState->mVertexFormats[vtxFmt] = format;
    }

    bool pendingStore = false;

    array = format->mAttrArrayList;
    while (array->mAttr != GX_VA_NULL) {
        if (array->mDirty) {
            DCStoreRangeNoSync(array->mBasePtr, array->mSize);
            array->mDirty = false;
            pendingStore = true;
        }
        array++;
    }

    if (pendingStore) {
        PPCSync();
    }

    if ((mFlags & GS_RENDER_INVALIDATE_CACHE) != 0
        || (format->mFlags & GS_VERTEX_INVALIDATE_CACHE) == GS_VERTEX_INVALIDATE_CACHE
    ) {
        GXInvalidateVtxCache();
        mFlags &= ~GS_RENDER_INVALIDATE_CACHE;
    }

    format->mFlags &= ~(GS_VERTEX_UPDATE_ARRAYS | GS_VERTEX_UPDATE_FORMAT);
}

void GSrenderManager::fn_802384BC() {
    s32 i;

    GSrenderState *state = mState;

    if (mState->_0 == 0) {
        return;
    }

    if ((mState->_0 & (1 << 0)) != 0) {
        u32 texGenFlags;
        u32 texOffsetFlags;
        u8 nTexGens;
        
        nTexGens = state->mCurr.mNumTexGens;
        if ((mState->_4 & (1 << 0)) != 0) {
            if (state->mPrev.mNumTexGens != nTexGens) {
                GXSetNumTexGens(nTexGens);
                state->mPrev.mNumTexGens = nTexGens;
            }
        }

        texGenFlags = mState->mTexGenFlags;
        if (texGenFlags != 0) {
            GStexGen *curr = state->mCurr.mTexGens;
            GStexGen *prev = state->mPrev.mTexGens;
            for (i = 0; i < nTexGens; i++, curr++, prev++) {
                if ((texGenFlags & (1 << i)) == 0) {
                    continue;
                }

                if (curr->mLight != NULL) {
                    curr->mTexGenFunc = (GXTexGenType)(GX_TG_BUMP0 + curr->mLight->mIndex);
                }

                if (prev->mTexGenFunc != curr->mTexGenFunc
                    || prev->mTexGenSrc != curr->mTexGenSrc
                    || prev->mTexMtx != curr->mTexMtx
                    || prev->mNormalize != curr->mNormalize
                    || prev->mPostMtx != curr->mPostMtx
                ) {
                    GXSetTexCoordGen2(
                        (GXTexCoordID)i,
                        curr->mTexGenFunc,
                        curr->mTexGenSrc,
                        curr->mTexMtx,
                        curr->mNormalize,
                        curr->mPostMtx
                    );

                    prev->mTexGenFunc = curr->mTexGenFunc;
                    prev->mTexGenSrc = curr->mTexGenSrc;
                    prev->mTexMtx = curr->mTexMtx;
                    prev->mNormalize = curr->mNormalize;
                    prev->mPostMtx = curr->mPostMtx;
                }
            }

            mState->mTexGenFlags = 0;
        }

        if ((mState->_4 & (1 << 2)) != 0) {
            if (state->mPrev.mLineWidth != state->mCurr.mLineWidth
                || state->mPrev.mLineTexOffsets != state->mCurr.mLineTexOffsets
            ) {
                GXSetLineWidth(state->mCurr.mLineWidth, state->mCurr.mLineTexOffsets);
                state->mPrev.mLineWidth = state->mCurr.mLineWidth;
                state->mPrev.mLineTexOffsets = state->mCurr.mLineTexOffsets;
            }
        }

        if ((mState->_4 & (1 << 3)) != 0) {
            if (state->mPrev.mPointSize != state->mCurr.mPointSize
                || state->mPrev.mPointTexOffsets != state->mCurr.mPointTexOffsets
            ) {
                GXSetPointSize(state->mCurr.mPointSize, state->mCurr.mPointTexOffsets);
                state->mPrev.mPointSize = state->mCurr.mPointSize;
                state->mPrev.mPointTexOffsets = state->mCurr.mPointTexOffsets;
            }
        }

        texOffsetFlags = mState->mTexOffsetFlags;
        if (texOffsetFlags != 0) {
            GStexOffsetEnable *curr = state->mCurr.mTexOffsetsEnabled;
            GStexOffsetEnable *prev = state->mPrev.mTexOffsetsEnabled;
            for (i = 0; i < nTexGens; i++, curr++, prev++) {
                if ((texOffsetFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mLineEnable != curr->mLineEnable
                    || prev->mPointEnable != curr->mPointEnable
                ) {
                    GXEnableTexOffsets(
                        (GXTexCoordID)i,
                        curr->mLineEnable,
                        curr->mPointEnable
                    );
                    prev->mLineEnable = curr->mLineEnable;
                    prev->mPointEnable = curr->mPointEnable;
                }
            }
            mState->mTexOffsetFlags = 0;
        }

        if ((mState->_4 & (1 << 5)) != 0) {
            GXSetProjectionv(state->mCurr.mProjectionParams);
            for (u32 i = 0; i < 7; i++) {
                state->mPrev.mProjectionParams[i] = state->mCurr.mProjectionParams[i];
            }
        }

        mState->_4 = 0;
    }

    if ((mState->_0 & (1 << 1)) != 0) {
        if ((mState->_10 & (1 << 3)) != 0) {
            if (state->mPrev.mCoPlanar != state->mCurr.mCoPlanar) {
                GXSetCoPlanar(state->mCurr.mCoPlanar);
                state->mPrev.mCoPlanar = state->mCurr.mCoPlanar;
            }
        }

        if ((mState->_10 & (1 << 1)) != 0) {
            if (state->mPrev.mCullMode != state->mCurr.mCullMode) {
                GXSetCullMode(state->mCurr.mCullMode);
                state->mPrev.mCullMode = state->mCurr.mCullMode;
            }
        }

        if ((mState->_10 & (1 << 2)) != 0) {
            if (state->mPrev.mClipMode != state->mCurr.mClipMode) {
                GXSetClipMode(state->mCurr.mClipMode);
                state->mPrev.mClipMode = state->mCurr.mClipMode;
            }
        }
        
        if ((mState->_10 & (1 << 0)) != 0) {
            if (state->mPrev.mScissor.mOrigX != state->mCurr.mScissor.mOrigX
                || state->mPrev.mScissor.mOrigY != state->mCurr.mScissor.mOrigY
                || state->mPrev.mScissor.mWidth != state->mCurr.mScissor.mWidth
                || state->mPrev.mScissor.mHeight != state->mCurr.mScissor.mHeight
            ) {
                setScissor(
                    state->mCurr.mScissor.mOrigX,
                    state->mCurr.mScissor.mOrigY,
                    state->mCurr.mScissor.mWidth,
                    state->mCurr.mScissor.mHeight
                );
                state->mPrev.mScissor.mOrigX = state->mCurr.mScissor.mOrigX;
                state->mPrev.mScissor.mOrigY = state->mCurr.mScissor.mOrigY;
                state->mPrev.mScissor.mWidth = state->mCurr.mScissor.mWidth;
                state->mPrev.mScissor.mHeight = state->mCurr.mScissor.mHeight;

                GSscissor *scissor = &mState->_14cc[mState->_14aa];
                scissor->mOrigX = state->mCurr.mScissor.mOrigX;
                scissor->mOrigY = state->mCurr.mScissor.mOrigY;
                scissor->mWidth = state->mCurr.mScissor.mWidth;
                scissor->mHeight = state->mCurr.mScissor.mHeight;
            }
        }
        
        if ((mState->_10 & (1 << 4)) != 0) {
            if (state->mPrev.mViewport.mOrigX != state->mCurr.mViewport.mOrigX
                || state->mPrev.mViewport.mOrigY != state->mCurr.mViewport.mOrigY
                || state->mPrev.mViewport.mWidth != state->mCurr.mViewport.mWidth
                || state->mPrev.mViewport.mHeight != state->mCurr.mViewport.mHeight
            ) {
                setViewport(
                    state->mCurr.mViewport.mOrigX,
                    state->mCurr.mViewport.mOrigY,
                    state->mCurr.mViewport.mWidth,
                    state->mCurr.mViewport.mHeight,
                    0f,
                    1f
                );
                state->mPrev.mViewport.mOrigX = state->mCurr.mViewport.mOrigX;
                state->mPrev.mViewport.mOrigY = state->mCurr.mViewport.mOrigY;
                state->mPrev.mViewport.mWidth = state->mCurr.mViewport.mWidth;
                state->mPrev.mViewport.mHeight = state->mCurr.mViewport.mHeight;

                GSviewport *viewport = &mState->_14ac[mState->_14a8];
                viewport->mOrigX = state->mCurr.mViewport.mOrigX;
                viewport->mOrigY = state->mCurr.mViewport.mOrigY;
                viewport->mWidth = state->mCurr.mViewport.mWidth;
                viewport->mHeight = state->mCurr.mViewport.mHeight;
            }
        }

        mState->_10 = 0;
    }

    if ((mState->_0 & (1 << 2)) != 0) {
        u8 nChans = state->mCurr.mNumChans;
        if ((mState->_14 & (1 << 0)) != 0) {
            if (state->mPrev.mNumChans != nChans) {
                GXSetNumChans(nChans);
                state->mPrev.mNumChans = nChans;
            }
        }

        u32 chanCtrlFlags = mState->mChanCtrlFlags;
        if (chanCtrlFlags != 0) {
            GScolorChannel *curr = state->mCurr.mChannels;
            GScolorChannel *prev = state->mPrev.mChannels;

            for (i = 0; i < 4; i++, curr++, prev++) {
                if ((chanCtrlFlags & (1 << i)) == 0) {
                    continue;
                }

                bool enable = (curr->mEnable != GX_FALSE);
                if (i % 2 >= nChans) {
                    enable = false;
                }

                if (enable) {
                    GSlight **lights;
                    u32 lightMask = 0;
                    GXAttnFn attnFn = curr->mAttnFn;
                    for (lights = curr->mLights; *lights != NULL; lights++) {
                        if (attnFn != GX_AF_SPEC || (*lights)->mType == GS_LIGHT_SPEC) {
                            lightMask |= (1 << (*lights)->mIndex);
                        }
                    }
                    curr->mLightMask = (GXLightID)lightMask;
                }
                else {
                    curr->mLightMask = GX_LIGHT_NULL;
                }

                if (prev->mEnable != enable
                    || prev->mAmbSrc != curr->mAmbSrc
                    || prev->mMatSrc != curr->mMatSrc
                    || prev->mLightMask != curr->mLightMask
                    || prev->mDiffFn != curr->mDiffFn
                    || prev->mAttnFn != curr->mAttnFn
                ) {
                    GXSetChanCtrl(
                        (GXChannelID)i,
                        enable,
                        curr->mAmbSrc,
                        curr->mMatSrc,
                        curr->mLightMask,
                        curr->mDiffFn,
                        curr->mAttnFn
                    );
                    prev->mEnable = enable;
                    prev->mAmbSrc = curr->mAmbSrc;
                    prev->mMatSrc = curr->mMatSrc;
                    prev->mLightMask = curr->mLightMask;
                    prev->mDiffFn = curr->mDiffFn;
                    prev->mAttnFn = curr->mAttnFn;
                }
            }

            mState->mChanCtrlFlags = 0;
        }

        u32 chanAmbColorFlags = mState->mChanAmbColorFlags;
        if (chanAmbColorFlags != 0) {
            GXColor *curr = state->mCurr.mChanAmbColors;
            GXColor *prev = state->mPrev.mChanAmbColors;

            for (i = 0; i < nChans; i++, curr++, prev++) {
                if ((chanAmbColorFlags & (1 << i)) == 0) {
                    continue;
                }

                if (*(s32 *)prev != *(s32 *)curr) {
                    GXSetChanAmbColor((GXChannelID)(GX_COLOR0A0 + i), *curr);
                    prev->r = curr->r;
                    prev->g = curr->g;
                    prev->b = curr->b;
                    prev->a = curr->a;
                }
            }

            mState->mChanAmbColorFlags = 0;
        }

        u32 chanMatColorFlags = mState->mChanMatColorFlags;
        if (chanMatColorFlags != 0) {
            GXColor *curr = state->mCurr.mChanMatColors;
            GXColor *prev = state->mPrev.mChanMatColors;

            for (i = 0; i < nChans; i++, curr++, prev++) {
                if ((chanMatColorFlags & (1 << i)) == 0) {
                    continue;
                }

                // TODO revisit this casting (GSColor?)
                if (*(s32 *)prev != *(s32 *)curr) {
                    GXSetChanMatColor((GXChannelID)(GX_COLOR0A0 + i), *curr);
                    prev->r = curr->r;
                    prev->g = curr->g;
                    prev->b = curr->b;
                    prev->a = curr->a;
                }
            }

            mState->mChanMatColorFlags = 0;
        }

        mState->_14 = 0;
    }

    u8 nTevStages = state->mCurr.mNumTevStages;
    if ((mState->_0 & (1 << 3)) != 0) {
        if ((mState->_24 & (1 << 0)) != 0) {
            if (state->mPrev.mNumTevStages != nTevStages) {
                GXSetNumTevStages(nTevStages);
                state->mPrev.mNumTevStages = nTevStages;
            }
        }

        u32 tevStageFlags = mState->mTevStageFlags;
        if (tevStageFlags != 0) {
            GStevStage *curr = state->mCurr.mTevStages;
            GStevStage *prev = state->mPrev.mTevStages;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevStageFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mTexCoord != curr->mTexCoord
                    || prev->mTexMap != curr->mTexMap
                    || prev->mChannel != curr->mChannel
                ) {
                    GXSetTevOrder(
                        (GXTevStageID)i,
                        curr->mTexCoord,
                        curr->mTexMap,
                        curr->mChannel
                    );
                    prev->mTexCoord = curr->mTexCoord;
                    prev->mTexMap = curr->mTexMap;
                    prev->mChannel = curr->mChannel;
                }
            }

            mState->mTevStageFlags = 0;
        }
        
        u32 tevColorInFlags = mState->mTevColorInFlags;
        if (tevColorInFlags != 0) {
            GStevColorIn *curr = state->mCurr.mTevColorIns;
            GStevColorIn *prev = state->mPrev.mTevColorIns;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevColorInFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mArgA != curr->mArgA
                    || prev->mArgB != curr->mArgB
                    || prev->mArgC != curr->mArgC
                    || prev->mArgD != curr->mArgD
                ) {
                    GXSetTevColorIn(
                        (GXTevStageID)i,
                        curr->mArgA,
                        curr->mArgB,
                        curr->mArgC,
                        curr->mArgD
                    );
                    prev->mArgA = curr->mArgA;
                    prev->mArgB = curr->mArgB;
                    prev->mArgC = curr->mArgC;
                    prev->mArgD = curr->mArgD;
                }
            }

            mState->mTevColorInFlags = 0;
        }
        
        u32 tevAlphaInFlags = mState->mTevAlphaInFlags;
        if (tevAlphaInFlags != 0) {
            GStevAlphaIn *curr = state->mCurr.mTevAlphaIns;
            GStevAlphaIn *prev = state->mPrev.mTevAlphaIns;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevAlphaInFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mArgA != curr->mArgA
                    || prev->mArgB != curr->mArgB
                    || prev->mArgC != curr->mArgC
                    || prev->mArgD != curr->mArgD
                ) {
                    GXSetTevAlphaIn(
                        (GXTevStageID)i,
                        curr->mArgA,
                        curr->mArgB,
                        curr->mArgC,
                        curr->mArgD
                    );
                    prev->mArgA = curr->mArgA;
                    prev->mArgB = curr->mArgB;
                    prev->mArgC = curr->mArgC;
                    prev->mArgD = curr->mArgD;
                }
            }

            mState->mTevAlphaInFlags = 0;
        }
        
        u32 tevColorOpFlags = mState->mTevColorOpFlags;
        if (tevColorOpFlags != 0) {
            GStevOp *curr = state->mCurr.mTevColorOps;
            GStevOp *prev = state->mPrev.mTevColorOps;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevColorOpFlags & (1 << i)) == 0) {
                    continue;
                }

                if (i == nTevStages - 1) {
                    curr->mClamp = GX_TRUE;
                }

                if (prev->mOp != curr->mOp
                    || prev->mBias != curr->mBias
                    || prev->mScale != curr->mScale
                    || prev->mClamp != curr->mClamp
                    || prev->mReg != curr->mReg
                ) {
                    GXSetTevColorOp(
                        (GXTevStageID)i,
                        curr->mOp,
                        curr->mBias,
                        curr->mScale,
                        curr->mClamp,
                        curr->mReg
                    );
                    prev->mOp = curr->mOp;
                    prev->mBias = curr->mBias;
                    prev->mScale = curr->mScale;
                    prev->mClamp = curr->mClamp;
                    prev->mReg = curr->mReg;
                }
            }

            mState->mTevColorOpFlags = 0;
        }
        
        u32 tevAlphaOpFlags = mState->mTevAlphaOpFlags;
        if (tevAlphaOpFlags != 0) {
            GStevOp *curr = state->mCurr.mTevAlphaOps;
            GStevOp *prev = state->mPrev.mTevAlphaOps;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevAlphaOpFlags & (1 << i)) == 0) {
                    continue;
                }

                if (i == nTevStages - 1) {
                    curr->mClamp = GX_TRUE;
                }

                if (prev->mOp != curr->mOp
                    || prev->mBias != curr->mBias
                    || prev->mScale != curr->mScale
                    || prev->mClamp != curr->mClamp
                    || prev->mReg != curr->mReg
                ) {
                    GXSetTevAlphaOp(
                        (GXTevStageID)i,
                        curr->mOp,
                        curr->mBias,
                        curr->mScale,
                        curr->mClamp,
                        curr->mReg
                    );
                    prev->mOp = curr->mOp;
                    prev->mBias = curr->mBias;
                    prev->mScale = curr->mScale;
                    prev->mClamp = curr->mClamp;
                    prev->mReg = curr->mReg;
                }
            }

            mState->mTevAlphaOpFlags = 0;
        }

        u32 tevColorFlags = mState->mTevColorFlags;
        if (tevColorFlags != 0) {
            GStevColor *curr = state->mCurr.mTevColors;

            for (i = 0; i < GX_MAX_TEVREG; i++, curr++) {
                if ((tevColorFlags & (1 << i)) == 0) {
                    continue;
                }

                if (curr->mType == TEV_COLOR_U8) {
                    GXSetTevColor((GXTevRegID)i, curr->mColor);
                }
                else {
                    GXSetTevColorS10((GXTevRegID)i, curr->mColorS10);
                }
            }

            mState->mTevColorFlags = 0;
        }

        u32 indTexStageFlags = mState->mIndTexStageFlags;
        if (indTexStageFlags != 0) {
            GSindTexStage *curr = state->mCurr.mIndTexStages;
            GSindTexStage *prev = state->mPrev.mIndTexStages;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((indTexStageFlags & (1 << i)) == 0) {
                    continue;
                }

                switch (curr->mType) {
                case TEV_DIRECT:
                    if (prev->mType != curr->mType) {
                        GXSetTevDirect((GXTevStageID)i);
                    }
                    break;
                
                case TEV_INDIRECT:
                    GXSetTevIndirect(
                        (GXTevStageID)i,
                        curr->mIndStage,
                        curr->indirect.mFormat,
                        curr->indirect.mBiasSel,
                        curr->indirect.mMatrixSel,
                        curr->indirect.mWrapS,
                        curr->indirect.mWrapT,
                        curr->indirect.mAddPrev,
                        curr->indirect.mUtcLod,
                        curr->indirect.mAlphaSel
                    );
                    break;
                
                case TEV_IND_WARP:
                    GXSetTevIndWarp(
                        (GXTevStageID)i,
                        curr->mIndStage,
                        curr->warp.mSignedOffsets,
                        curr->warp.mReplaceMode,
                        curr->warp.mMatrixSel
                    );
                    break;
                
                case TEV_IND_TILE:
                    GXSetTevIndTile(
                        (GXTevStageID)i,
                        curr->mIndStage,
                        curr->tile.mTileSizeS,
                        curr->tile.mTileSizeT,
                        curr->tile.mTileSpacingS,
                        curr->tile.mTileSpacingT,
                        curr->tile.mFormat,
                        curr->tile.mMatrixSel,
                        curr->tile.mBiasSel,
                        curr->tile.mAlphaSel
                    );
                    break;
                
                case TEV_IND_BUMP_ST:
                    GXSetTevIndBumpST(
                        (GXTevStageID)i,
                        curr->mIndStage,
                        curr->bump.mMatrixSel
                    );
                    break;
                
                case TEV_IND_BUMP_XYZ:
                    GXSetTevIndBumpXYZ(
                        (GXTevStageID)i,
                        curr->mIndStage,
                        curr->bump.mMatrixSel
                    );
                    break;
                
                case TEV_IND_REPEAT:
                    if (prev->mType != curr->mType) {
                        GXSetTevIndRepeat((GXTevStageID)i);
                    }
                    break;
                
                case TEV_NULL:
                default:
                    break;
                }
                
                prev->mType = curr->mType;
            }

            mState->mIndTexStageFlags = 0;
        }

        if ((mState->_24 & (1 << 8)) != 0) {
            if (state->mPrev.mZTexOp != state->mCurr.mZTexOp
                || state->mPrev.mZTexFmt != state->mCurr.mZTexFmt
                || state->mPrev.mZTexBias != state->mCurr.mZTexBias
            ) {
                GXSetZTexture(
                    state->mCurr.mZTexOp,
                    state->mCurr.mZTexFmt,
                    state->mCurr.mZTexBias
                );
                state->mPrev.mZTexOp = state->mCurr.mZTexOp;
                state->mPrev.mZTexFmt = state->mCurr.mZTexFmt;
                state->mPrev.mZTexBias = state->mCurr.mZTexBias;
            }
        }

        mState->_24 = 0;
    }

    if ((mState->_0 & (1 << 7)) != 0) {
        u8 nIndStages = state->mCurr.mNumIndStages;
        if ((mState->_44 & (1 << 0)) != 0) {
            if (state->mPrev.mNumIndStages != nIndStages) {
                GXSetNumIndStages(nIndStages);
                state->mPrev.mNumIndStages = nIndStages;
            }
        }

        u32 indTexOrderFlags = mState->mIndTexOrderFlags;
        if (indTexOrderFlags != 0) {
            GSindTexOrder *curr = state->mCurr.mIndTexOrders;
            GSindTexOrder *prev = state->mPrev.mIndTexOrders;

            for (i = 0; i < nIndStages; i++, curr++, prev++) {
                if ((indTexOrderFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mTexCoord != curr->mTexCoord
                    || prev->mTexMap != curr->mTexMap
                ) {
                    GXSetIndTexOrder(
                        (GXIndTexStageID)i,
                        curr->mTexCoord,
                        curr->mTexMap
                    );
                    prev->mTexCoord = curr->mTexCoord;
                    prev->mTexMap = curr->mTexMap;
                }
            }

            mState->mIndTexOrderFlags = 0;
        }

        u32 indTexScaleFlags = mState->mIndTexScaleFlags;
        if (indTexScaleFlags != 0) {
            GSindTexScale *curr = state->mCurr.mIndTexScales;
            GSindTexScale *prev = state->mPrev.mIndTexScales;

            for (i = 0; i < nIndStages; i++, curr++, prev++) {
                if ((indTexScaleFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mScaleS != curr->mScaleS
                    || prev->mScaleT != curr->mScaleT
                ) {
                    GXSetIndTexCoordScale(
                        (GXIndTexStageID)i,
                        curr->mScaleS,
                        curr->mScaleT
                    );
                    prev->mScaleS = curr->mScaleS;
                    prev->mScaleT = curr->mScaleT;
                }
            }

            mState->mIndTexScaleFlags = 0;
        }

        mState->_44 = 0;
    }

    if ((mState->_0 & (1 << 4)) != 0) {
        u32 tevKColorFlags = mState->mTevKColorFlags;
        if (tevKColorFlags != 0) {
            GXColor *curr = state->mCurr.mTevKColors;
            GXColor *prev = state->mPrev.mTevKColors;

            for (i = 0; i < GX_MAX_KCOLOR; i++, curr++, prev++) {
                if ((tevKColorFlags & (1 << i)) == 0) {
                    continue;
                }

                // TODO revisit this casting (GSColor?)
                if (*(s32 *)prev != *(s32 *)curr) {
                    GXSetTevKColor((GXTevKColorID)i, *curr);
                    (*prev).r = (*curr).r;
                    (*prev).g = (*curr).g;
                    (*prev).b = (*curr).b;
                    (*prev).a = (*curr).a;
                }
            }

            mState->mTevKColorFlags = 0;
        }

        u32 tevKColorSelFlags = mState->mTevKColorSelFlags;
        if (tevKColorSelFlags != 0) {
            GXTevKColorSel *curr = state->mCurr.mTevKColorSels;
            GXTevKColorSel *prev = state->mPrev.mTevKColorSels;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevKColorSelFlags & (1 << i)) == 0) {
                    continue;
                }

                if (*prev != *curr) {
                    GXSetTevKColorSel((GXTevStageID)i, *curr);
                    *prev = *curr;
                }
            }

            mState->mTevKColorSelFlags = 0;
        }

        u32 tevKAlphaSelFlags = mState->mTevKAlphaSelFlags;
        if (tevKAlphaSelFlags != 0) {
            GXTevKAlphaSel *curr = state->mCurr.mTevKAlphaSels;
            GXTevKAlphaSel *prev = state->mPrev.mTevKAlphaSels;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevKAlphaSelFlags & (1 << i)) == 0) {
                    continue;
                }

                if (*prev != *curr) {
                    GXSetTevKAlphaSel((GXTevStageID)i, *curr);
                    *prev = *curr;
                }
            }

            mState->mTevKAlphaSelFlags = 0;
        }
    }

    if ((mState->_0 & (1 << 5)) != 0) {
        u32 tevSwapModeFlags = mState->mTevSwapModeFlags;
        if (tevSwapModeFlags != 0) {
            GStevSwapMode *curr = state->mCurr.mTevSwapModes;
            GStevSwapMode *prev = state->mPrev.mTevSwapModes;

            for (i = 0; i < nTevStages; i++, curr++, prev++) {
                if ((tevSwapModeFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mRasSel != curr->mRasSel
                    || prev->mTexSel != curr->mTexSel
                ) {
                    GXSetTevSwapMode(
                        (GXTevStageID)i,
                        curr->mRasSel,
                        curr->mTexSel
                    );
                    prev->mRasSel = curr->mRasSel;
                    prev->mTexSel = curr->mTexSel;
                }
            }

            mState->mTevSwapModeFlags = 0;
        }
        
        u32 tevSwapModeTableFlags = mState->mTevSwapModeTableFlags;
        if (tevSwapModeTableFlags != 0) {
            GStevSwapModeTable *curr = state->mCurr.mTevSwapModeTables;
            GStevSwapModeTable *prev = state->mPrev.mTevSwapModeTables;

            for (i = 0; i < GX_MAX_TEVSWAP; i++, curr++, prev++) {
                if ((tevSwapModeTableFlags & (1 << i)) == 0) {
                    continue;
                }

                if (prev->mRed != curr->mRed
                    || prev->mGreen != curr->mGreen
                    || prev->mBlue != curr->mBlue
                    || prev->mAlpha != curr->mAlpha
                ) {
                    GXSetTevSwapModeTable(
                        (GXTevSwapSel)i,
                        curr->mRed,
                        curr->mGreen,
                        curr->mBlue,
                        curr->mAlpha
                    );
                    prev->mRed = curr->mRed;
                    prev->mGreen = curr->mGreen;
                    prev->mBlue = curr->mBlue;
                    prev->mAlpha = curr->mAlpha;
                }
            }

            mState->mTevSwapModeTableFlags = 0;
        }
    }

    if ((mState->_0 & (1 << 6)) != 0) {
        bool zCompEnable = (state->mCurr.mZCompareEnable != GX_FALSE);
        GXCompare zCompFunc = state->mCurr.mZCompareFunc;
        if (state->mCurr.mZUpdateEnable == GX_TRUE && !zCompEnable) {
            zCompEnable = true;
            zCompFunc = GX_ALWAYS;
        }

        if ((mState->_64 & (1 << 0)) != 0) {
            if (state->mPrev.mBlendMode != state->mCurr.mBlendMode
                || state->mPrev.mBlendSrcFactor != state->mCurr.mBlendSrcFactor
                || state->mPrev.mBlendDstFactor != state->mCurr.mBlendDstFactor
                || state->mPrev.mBlendOp != state->mCurr.mBlendOp
            ) {
                GXSetBlendMode(
                    state->mCurr.mBlendMode,
                    state->mCurr.mBlendSrcFactor,
                    state->mCurr.mBlendDstFactor,
                    state->mCurr.mBlendOp
                );
                state->mPrev.mBlendMode = state->mCurr.mBlendMode;
                state->mPrev.mBlendSrcFactor = state->mCurr.mBlendSrcFactor;
                state->mPrev.mBlendDstFactor = state->mCurr.mBlendDstFactor;
                state->mPrev.mBlendOp = state->mCurr.mBlendOp;
            }
        }

        if ((mState->_64 & (1 << 1)) != 0) {
            if (state->mPrev.mDstAlphaEnable != state->mCurr.mDstAlphaEnable
                || state->mPrev.mDstAlpha != state->mCurr.mDstAlpha
            ) {
                GXSetDstAlpha(state->mCurr.mDstAlphaEnable, state->mCurr.mDstAlpha);
                state->mPrev.mDstAlphaEnable = state->mCurr.mDstAlphaEnable;
                state->mPrev.mDstAlpha = state->mCurr.mDstAlpha;
            }
        }

        if ((mState->_64 & (1 << 2)) != 0) {
            if (state->mPrev.mColorUpdateEnable != state->mCurr.mColorUpdateEnable) {
                GXSetColorUpdate(state->mCurr.mColorUpdateEnable);
                state->mPrev.mColorUpdateEnable = state->mCurr.mColorUpdateEnable;
            }

            if (state->mPrev.mAlphaUpdateEnable != state->mCurr.mAlphaUpdateEnable) {
                GXSetAlphaUpdate(state->mCurr.mAlphaUpdateEnable);
                state->mPrev.mAlphaUpdateEnable = state->mCurr.mAlphaUpdateEnable;
            }
        }

        if ((mState->_64 & ((1 << 2) | (1 << 3))) != 0) {
            if (state->mPrev.mZCompareEnable != zCompEnable
                || state->mPrev.mZCompareFunc != zCompFunc
                || state->mPrev.mZUpdateEnable != state->mCurr.mZUpdateEnable
            ) {
                GXSetZMode(zCompEnable, zCompFunc, state->mCurr.mZUpdateEnable);
                state->mPrev.mZCompareEnable = zCompEnable;
                state->mPrev.mZCompareFunc = zCompFunc;
                state->mPrev.mZUpdateEnable = state->mCurr.mZUpdateEnable;
            }
        }

        if ((mState->_64 & (1 << 4)) != 0) {
            if (state->mPrev.mAlphaComp0 != state->mCurr.mAlphaComp0
                || state->mPrev.mAlphaRef0 != state->mCurr.mAlphaRef0
                || state->mPrev.mAlphaOp != state->mCurr.mAlphaOp
                || state->mPrev.mAlphaComp1 != state->mCurr.mAlphaComp1
                || state->mPrev.mAlphaRef1 != state->mCurr.mAlphaRef1
            ) {
                GXSetAlphaCompare(
                    state->mCurr.mAlphaComp0,
                    state->mCurr.mAlphaRef0,
                    state->mCurr.mAlphaOp,
                    state->mCurr.mAlphaComp1,
                    state->mCurr.mAlphaRef1
                );
                state->mPrev.mAlphaComp0 = state->mCurr.mAlphaComp0;
                state->mPrev.mAlphaRef0 = state->mCurr.mAlphaRef0;
                state->mPrev.mAlphaOp = state->mCurr.mAlphaOp;
                state->mPrev.mAlphaComp1 = state->mCurr.mAlphaComp1;
                state->mPrev.mAlphaRef1 = state->mCurr.mAlphaRef1;
            }

            if (state->mPrev.mZCompBeforeTex != state->mCurr.mZCompBeforeTex) {
                GXSetZCompLoc(state->mCurr.mZCompBeforeTex);
                state->mPrev.mZCompBeforeTex = state->mCurr.mZCompBeforeTex;
            }
        }

        if ((mState->_64 & (1 << 5)) != 0) {
            if (state->mPrev.mDitherEnable != state->mCurr.mDitherEnable) {
                GXSetDither(state->mCurr.mDitherEnable);
                state->mPrev.mDitherEnable = state->mCurr.mDitherEnable;
            }
        }

        if ((mState->_64 & (1 << 6)) != 0) {
            GXFogType fogType;
            
            if (state->mCurr.mFogEnable) {
                fogType = state->mCurr.mFogType;

                if (fogType == GX_FOG_NONE) {
                    state->mCurr.mFogEnable = false;
                }
                else if (state->mCurr.mProjectionType == GX_ORTHOGRAPHIC) {
                    fogType = (GXFogType)(fogType + (GX_FOG_ORTHO_LIN - GX_FOG_PERSP_LIN));
                }
            }
            else {
                fogType = GX_FOG_NONE;
            }
            
            if (state->mPrev.mFogType != fogType
                || fogType != GX_FOG_NONE
                && (state->mPrev.mFogStartZ != state->mCurr.mFogStartZ
                    || state->mPrev.mFogEndZ != state->mCurr.mFogEndZ
                    || state->mPrev.mFogNearZ != state->mCurr.mFogNearZ
                    || state->mPrev.mFogFarZ != state->mCurr.mFogFarZ
                    // TODO revisit this casting (GSColor?)
                    || *(s32 *)(&state->mPrev.mFogColor) != *(s32 *)(&state->mCurr.mFogColor))
            ) {
                GXSetFog(
                    fogType,
                    state->mCurr.mFogStartZ,
                    state->mCurr.mFogEndZ,
                    state->mCurr.mFogNearZ,
                    state->mCurr.mFogFarZ,
                    state->mCurr.mFogColor
                );
                state->mPrev.mFogType = fogType;
                state->mPrev.mFogStartZ = state->mCurr.mFogStartZ;
                state->mPrev.mFogEndZ = state->mCurr.mFogEndZ;
                state->mPrev.mFogNearZ = state->mCurr.mFogNearZ;
                state->mPrev.mFogFarZ = state->mCurr.mFogFarZ;
                state->mPrev.mFogColor.r = state->mCurr.mFogColor.r;
                state->mPrev.mFogColor.g = state->mCurr.mFogColor.g;
                state->mPrev.mFogColor.b = state->mCurr.mFogColor.b;
                state->mPrev.mFogColor.a = state->mCurr.mFogColor.a;
            }
        }
        else if ((mState->_64 & (1 << 7)) != 0) {
            // TODO revisit this casting (GSColor?)
            if (*(s32 *)(&state->mPrev.mFogColor) != *(s32 *)(&state->mCurr.mFogColor)) {
                GXSetFogColor(state->mCurr.mFogColor);
                state->mPrev.mFogColor.r = state->mCurr.mFogColor.r;
                state->mPrev.mFogColor.g = state->mCurr.mFogColor.g;
                state->mPrev.mFogColor.b = state->mCurr.mFogColor.b;
                state->mPrev.mFogColor.a = state->mCurr.mFogColor.a;
            }
        }

        bool doFogRangeAdj = false;
        if ((mState->_64 & (1 << 8)) != 0) {
            sProjectionMatrix[0][0] = state->mCurr.mProjectionParams[1];
            sProjectionMatrix[1][1] = state->mCurr.mProjectionParams[3];
            sProjectionMatrix[2][2] = state->mCurr.mProjectionParams[5];
            sProjectionMatrix[2][3] = state->mCurr.mProjectionParams[6];

            if (state->mCurr.mProjectionType == GX_PERSPECTIVE) {
                sProjectionMatrix[0][2] = state->mCurr.mProjectionParams[2];
                sProjectionMatrix[0][3] = 0f;
                sProjectionMatrix[1][2] = state->mCurr.mProjectionParams[4];
                sProjectionMatrix[1][3] = 0f;
                sProjectionMatrix[3][2] = -1f;
                sProjectionMatrix[3][3] = 0f;
            }
            else {
                sProjectionMatrix[0][2] = 0f;
                sProjectionMatrix[0][3] = state->mCurr.mProjectionParams[2];
                sProjectionMatrix[1][2] = 0f;
                sProjectionMatrix[1][3] = state->mCurr.mProjectionParams[4];
                sProjectionMatrix[3][2] = 0f;
                sProjectionMatrix[3][3] = 1f;
            }

            u16 width;
            OSf32tou16(&mViewportWidth.fval, &width);
            GXInitFogAdjTable(&state->mCurr.mFogAdjTable, width, sProjectionMatrix);

            doFogRangeAdj = (state->mCurr.mFogRangeAdjEnable != GX_FALSE);
        }

        if (doFogRangeAdj || (mState->_64 & (1 << 9)) != 0) {
            if (state->mPrev.mFogRangeAdjEnable != state->mCurr.mFogRangeAdjEnable
                || state->mPrev.mFogRangeAdjCenter != state->mCurr.mFogRangeAdjCenter
            ) {
                u16 center;
                if (mState->mCurr.mFogRangeAdjCenter == 0xffff) {
                    f32 w = 0.5f * mViewportWidth.fval + 0.5f;
                    OSf32tou16(&w, &center);
                }
                else {
                    center = state->mCurr.mFogRangeAdjCenter;
                }

                GXSetFogRangeAdj(
                    state->mCurr.mFogRangeAdjEnable,
                    center,
                    &state->mCurr.mFogAdjTable
                );
                state->mPrev.mFogRangeAdjCenter = center;
                state->mPrev.mFogRangeAdjEnable = state->mCurr.mFogRangeAdjEnable;
            }
        }

        mState->_64 = 0;
    }

    mState->_0 = 0;
}
