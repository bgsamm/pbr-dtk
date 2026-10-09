#include "gs/scene/GSmaterial.hpp"

#include "gs/GShierarchyModule.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSrender.hpp"
#include "gs/render/80236704.hpp"
#include "gs/scene/GSlight.hpp"

#include <cmath>
#include <cstring>

#include "common.hpp"

// TODO(samm) Proper imports
extern GSmeshRenderSettings *sLastMeshRenderSettings;
extern GSmaterialData *lbl_8063F3AC;
extern u8 lbl_8063F3B0;

GSmatrix lbl_80491970;
_UnkMaterialStruct_2 lbl_8063D768 = {1};

GSmaterial::GSmaterial(GSmaterialData *matData, GSmeshRenderSettings *renderSettings)
    : GSanimationObject(matData->mKeyframes),
      mOrigMatData(matData),
      mMatData(matData),
      mRenderSettings(renderSettings),
      _14(),
      _18(),
      _1c(),
      mTexGenCount(),
      mChannelCount(),
      mCurrTevStage(),
      _20(255),
      _21(255),
      _22(255),
      _23(255),
      _24(255),
      _25(255),
      _26(),
      _27(1),
      _28(),
      _2c(0, 0, 0, 0),
      mBaseColor(128, 128, 128, 255) {
    if (matData->_5b) {
        _18 = new _UnkMaterialStruct_1[matData->_5b];
    }

    if (matData->mKeyframes) {
        GSkeyframeData *group = matData->mKeyframes;
        while (group) {
            GSchannelData *channelData = group->mChannels;
            u16 channelCount = group->mChannelCount;
            for (u16 i = 0; i < channelCount; i++, channelData++) {
                switch (channelData->mChannel) {
                    case 0x14:
                    case 0x15:
                    case 0x16:
                        if (mMatData == matData) {
                            GSmaterialData *_unk1 = new GSmaterialData();
                            if (_unk1) {
                                memcpy(_unk1, matData, sizeof(*matData));
                                mMatData = _unk1;
                            }
                        }
                        if (mMatData != matData) {
                            _UnkMaterialData_2 *_unk2 = matData->_2c[channelData->_3];
                            if (_unk2 == mMatData->_2c[channelData->_3]) {
                                _UnkMaterialData_2 *_unk3 = new _UnkMaterialData_2();
                                if (_unk3) {
                                    memcpy(_unk3, _unk2, sizeof(*_unk2));
                                    mMatData->_2c[channelData->_3] = _unk3;
                                }
                            }
                        }
                        break;
                    case 0x17:
                    case 0x18:
                    case 0x19:
                    case 0x1a:
                    case 0x1b:
                    case 0x1c:
                        if (mMatData == matData) {
                            GSmaterialData *_unk1 = new GSmaterialData();
                            if (_unk1) {
                                memcpy(_unk1, matData, sizeof(*matData));
                                mMatData = _unk1;
                            }
                        }
                        break;
                }
            }
            group = group->mNext;
        }
    }
}

GSmaterial::~GSmaterial() {
    if (mOrigMatData->_50) {
        if (_14 && (_28 & (1 << 0))) {
            _14->fn_8023E2D0();
            _28 &= ~(1 << 0);
        }
        _14 = NULL;
    }

    if (mMatData != mOrigMatData) {
        u16 i, _unk1;

        _unk1 = mMatData->_5b;
        for (i = 0; i < _unk1; i++) {
            _UnkMaterialData_2 *_unk2 = mMatData->_2c[i];
            if (mOrigMatData->_2c[i] != _unk2) {
                delete _unk2;
            }
        }
        delete mMatData;
    }

    if (_18) {
        delete[] _18;
    }
}

void GSmaterial::fn_801E74B0(_UnkMaterialData_1 *arg0) {
    GXTevColorArg colorIn1;
    GXTevColorArg colorIn2;
    GXTevAlphaArg alphaIn;
    u8 texCoordId;
    u8 texMapId;

    switch (arg0->_0) {
        case 1:
            GSrender::sInstance->setTevKColorSel(mCurrTevStage, (GXTevKColorSel)arg0->_4);
            GSrender::sInstance->setTevKAlphaSel(mCurrTevStage, (GXTevKAlphaSel)arg0->_5);
            colorIn1 = GX_CC_KONST;
            colorIn2 = GX_CC_KONST;
            alphaIn = GX_CA_KONST;
            texCoordId = GX_TEXCOORD_NULL;
            texMapId = GX_TEXMAP_NULL;
            break;
        case 0:
            colorIn1 = GX_CC_TEXC;
            colorIn2 = GX_CC_TEXA;
            alphaIn = GX_CA_TEXA;
            texCoordId = arg0->_5;
            texMapId = arg0->_4;
            break;
        case 2:
            GSrender::sInstance->setTevKColorSel(mCurrTevStage, (GXTevKColorSel)arg0->_6);
            colorIn1 = GX_CC_TEXC;
            colorIn2 = GX_CC_KONST;
            alphaIn = GX_CA_TEXA;
            texCoordId = arg0->_5;
            texMapId = arg0->_4;
            break;
        default: return;
    }

    lbl_8063D768._0 = 0;
    lbl_8063D768._1 = false;
    lbl_8063D768.mTexMapId = texMapId;
    lbl_8063D768.mTexCoordId = texCoordId;
    lbl_8063D768._4 = GX_CC_ZERO;
    lbl_8063D768._5 = GX_CA_ZERO;

    // TODO(samm) Revisit these casts
    bool _unk6 = !((s8)arg0->_2 + 1) && !((s8)arg0->_3 + 1);

    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevStage(mCurrTevStage, (GXTexCoordID)texCoordId, (GXTexMapID)texMapId, GX_COLOR_NULL);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, (GXTevSwapSel)(arg0->_2 + 1), (GXTevSwapSel)(arg0->_3 + 1));

    GXTevColorArg colorPrev = (mCurrTevStage != GX_TEVSTAGE0) ? GX_CC_CPREV : GX_CC_ZERO;
    GXTevAlphaArg alphaPrev = (mCurrTevStage != GX_TEVSTAGE0) ? GX_CA_APREV : GX_CA_ZERO;

    switch (arg0->_1) {
        case 0:
            // Color = colorIn1
            // Alpha = alphaIn
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, colorIn1);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);

            lbl_8063D768._1 = _unk6;
            lbl_8063D768._4 = colorIn1;
            lbl_8063D768._5 = alphaIn;
            break;
        case 1:
            // Color = ((1.0 - colorIn2) * colorPrev + colorIn2 * colorIn1)
            // Alpha = clamp(alphaIn + ((1.0 - alphaIn) * alphaPrev))
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_TRUE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, colorPrev, colorIn1, colorIn2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, alphaPrev, GX_CA_ZERO, alphaIn, alphaIn);
            break;
        case 2:
            // Color = colorIn2 * colorPrev
            // Alpha = alphaIn * alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorPrev, colorIn2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, alphaPrev, alphaIn, GX_CA_ZERO);

            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO) && (alphaPrev == GX_CA_ZERO);
            lbl_8063D768._4 = colorIn2;
            lbl_8063D768._5 = alphaIn;
            break;
        case 3:
            // Color = (1.0 - colorIn2) * colorPrev
            // Alpha = (1.0 - alphaIn) * alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, colorPrev, GX_CC_ZERO, colorIn2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, alphaPrev, GX_CA_ZERO, alphaIn, GX_CA_ZERO);

            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO) && (alphaPrev == GX_CA_ZERO);
            lbl_8063D768._4 = GX_CC_ZERO;
            lbl_8063D768._5 = GX_CA_ZERO;
            break;
        case 4:
            // Color = clamp(colorPrev + colorIn2 * colorIn1)
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               (mCurrTevStage != GX_TEVSTAGE0),
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorIn1, colorIn2, colorPrev);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaPrev);
            break;
        case 5:
            // Color = clamp(colorPrev - colorIn2 * colorIn1)
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_SUB,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               (mCurrTevStage != GX_TEVSTAGE0),
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorIn1, colorIn2, colorPrev);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaPrev);
            break;
        case 6:
            // Color = colorIn1 * colorPrev
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorPrev, colorIn1, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaPrev);

            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO);
            lbl_8063D768._4 = GX_CC_ZERO;
            lbl_8063D768._5 = alphaPrev;
            break;
        case 7:
            // Color = ((1.0 - colorIn2) + colorIn2 * colorIn1) * colorPrev
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVREG2);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ONE, colorIn1, colorIn2, GX_CC_ZERO);
            // TODO(samm) Why does it put alphaPrev in `a` instead of `d`?
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, alphaPrev, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);

            mCurrTevStage++;
            GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
            GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GSrender::sInstance->setTevSwapMode(mCurrTevStage, arg0->_2 + 1, arg0->_3 + 1);

            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorPrev, GX_CC_C2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);

            lbl_8063D768.mTexMapId = GX_TEXMAP_NULL;
            lbl_8063D768.mTexCoordId = GX_TEXCOORD_NULL;
            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO);
            lbl_8063D768._4 = GX_CC_ZERO;
            lbl_8063D768._5 = GX_CA_APREV;
            break;
        case 8:
            // Color = clamp(1.0 + colorIn2 * colorIn1) * colorPrev
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_TRUE,
                                               GX_TEVREG2);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorIn1, colorIn2, GX_CC_ONE);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, alphaPrev, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);

            mCurrTevStage++;
            GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
            GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GSrender::sInstance->setTevSwapMode(mCurrTevStage, arg0->_2 + 1, arg0->_3 + 1);

            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorPrev, GX_CC_C2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);

            lbl_8063D768.mTexMapId = GX_TEXMAP_NULL;
            lbl_8063D768.mTexCoordId = GX_TEXCOORD_NULL;
            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO);
            lbl_8063D768._4 = GX_CC_ZERO;
            lbl_8063D768._5 = GX_CA_APREV;
            break;
        case 9:
            // Color = clamp(1.0 - colorIn2 * colorIn1) * colorPrev
            // Alpha = alphaPrev
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_SUB,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_TRUE,
                                               GX_TEVREG2);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorIn1, colorIn2, GX_CC_ONE);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, alphaPrev, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);

            mCurrTevStage++;
            GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
            GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GSrender::sInstance->setTevSwapMode(mCurrTevStage, arg0->_2 + 1, arg0->_3 + 1);

            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, colorPrev, GX_CC_C2, GX_CC_ZERO);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);

            lbl_8063D768.mTexMapId = GX_TEXMAP_NULL;
            lbl_8063D768.mTexCoordId = GX_TEXCOORD_NULL;
            lbl_8063D768._1 = _unk6 && (colorPrev == GX_CC_ZERO);
            lbl_8063D768._4 = GX_CC_ZERO;
            lbl_8063D768._5 = GX_CA_APREV;
            break;
        case 10:
            // Color = (stage != 0) ? colorPrev : 1.0
            // Alpha = alphaIn
            GSrender::sInstance->setTevColorOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevAlphaOp(mCurrTevStage,
                                               GX_TEV_ADD,
                                               GX_TB_ZERO,
                                               GX_CS_SCALE_1,
                                               GX_FALSE,
                                               GX_TEVPREV);
            GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                               GX_CC_ZERO,
                                               GX_CC_ZERO,
                                               GX_CC_ZERO,
                                               (mCurrTevStage != GX_TEVSTAGE0) ? colorPrev : GX_CC_ONE);
            GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, alphaIn);

            lbl_8063D768._1 = _unk6;
            lbl_8063D768._4 = (mCurrTevStage != GX_TEVSTAGE0) ? colorPrev : GX_CC_ONE;
            lbl_8063D768._5 = alphaIn;
            break;
    }

    mCurrTevStage++;
}

void GSmaterial::fn_801E9DCC(const _UnkMaterialStruct_3 *arg0, GSmatrix *arg1) {
    GSmatrix _unk1;

    mTexGenCount = mMatData->_5b;

    for (u8 i = 0; i < mTexGenCount; i++) {
        _UnkMaterialData_2 *_unk2 = mMatData->_2c[i];
        GSmatrix *_unk3 = fn_801E9C74(i, _unk2);

        GSrender::sInstance->setTexOffsetEnabled(i, false, false);

        if (_unk2->_2 == 1) {
            _unk1(0, 0) = 0.5f * (*_unk3)(0, 0);
            _unk1(0, 1) = -0.5f * (*_unk3)(0, 1);
            _unk1(0, 2) = 0.f;
            _unk1(0, 3) = 0.5f * ((*_unk3)(0, 0) + (*_unk3)(0, 1)) + (*_unk3)(0, 2) + (*_unk3)(0, 3);

            _unk1(1, 0) = 0.5f * (*_unk3)(1, 0);
            _unk1(1, 1) = -0.5f * (*_unk3)(1, 1);
            _unk1(1, 2) = 0.f;
            _unk1(1, 3) = 0.5f * ((*_unk3)(1, 0) + (*_unk3)(1, 1)) + (*_unk3)(1, 2) + (*_unk3)(1, 3);

            _unk1(2, 0) = 0.5f * (*_unk3)(2, 0);
            _unk1(2, 1) = -0.5f * (*_unk3)(2, 1);
            _unk1(2, 2) = 0.f;
            _unk1(2, 3) = 0.5f * ((*_unk3)(2, 0) + (*_unk3)(2, 1)) + (*_unk3)(2, 2) + (*_unk3)(2, 3);

            u32 _unk4 = i + 13;
            GSrender::sInstance->fn_802345F8(_unk4, &_unk1, true);
            GSrender::sInstance->fn_802346FC(i, 0, 1, 10, 1, _unk4);
        } else {
            GSrender::sInstance->configureTexCoordGen(i, _unk2->_0, _unk2->_1, *_unk3, false, NULL);
        }
    }

    if (_22 != 0xFF) {
        u32 _unk3 = mTexGenCount + 13;
        GSrender::sInstance->fn_802345F8(_unk3, &lbl_80491970, true);
        GSrender::sInstance->setTexOffsetEnabled(mTexGenCount, false, false);
        GSrender::sInstance->fn_802346FC(mTexGenCount, 0, 1, 10, 1, _unk3);
        _23 = mTexGenCount++;
    } else {
        _23 = 0xFF;
    }

    if (_24 != 0xFF) {
        _UnkClass80236704 *_unk4 = GSrender::sInstance->get_16e8();
        if ((_unk4->_4->mFlags & (1 << 1))) {
            _unk4->_4->mNrmMtx = _unk4->_4->mPosMtx.invXpose();
            _unk4->_4->mFlags &= ~(1 << 1);
        }

        GSmatrix _unk6 = _unk4->_4->mNrmMtx;

        if (_27) {
            _unk6.scale(GSvec3(1.f, 1.f, 0.75f));

            GSvec3 _unk5 = arg0->_1ac - arg0->_1c4;

            f32 _unk7 = _unk5.x * _unk5.x + _unk5.z * _unk5.z;
            _unk7 = (_unk7 <= 0.f) ? 0.f : sqrtf(_unk7);

            f32 _unk8 = (2.f * atan2f(_unk5.x, _unk5.z)) / PI;
            f32 _unk9 = (2.f * atan2f(_unk5.y, _unk7)) / PI;

            _unk5.normalize();

            _unk1(0, 0) = 1.f + 0.25f * abs(_unk5.x);
            _unk1(0, 1) = 0.f;
            _unk1(0, 2) = 0.f;
            _unk1(0, 3) = 1.f + _unk8;

            _unk1(1, 0) = 0.f;
            _unk1(1, 1) = -1.f - 0.25f * abs(_unk5.y);
            _unk1(1, 2) = 0.f;
            _unk1(1, 3) = 1.f - _unk9;

            _unk1(2, 0) = 0.f;
            _unk1(2, 1) = 0.f;
            _unk1(2, 2) = 0.f;
            _unk1(2, 3) = 4.f;
        } else {
            _unk1(0, 0) = 0.5f;
            _unk1(0, 1) = 0.f;
            _unk1(0, 2) = 0.f;
            _unk1(0, 3) = 0.5f;

            _unk1(1, 0) = 0.f;
            _unk1(1, 1) = -0.5f;
            _unk1(1, 2) = 0.f;
            _unk1(1, 3) = 0.5f;

            _unk1(2, 0) = 0.f;
            _unk1(2, 1) = 0.f;
            _unk1(2, 2) = 0.f;
            _unk1(2, 3) = 1.f;

            GSmatrix _unk2;
            u8 _unk9 = (arg0->_104 & 0x3);
            switch (_unk9) {
                case 1: {
                    f32 fovy = (_unk9 == 1) ? arg0->_168 : 1.f;
                    f32 aspect =
                        (_unk9 == 1) ? arg0->_16c : fabsf(arg0->_174 - arg0->_170) / fabsf(arg0->_16c - arg0->_168);
                    MTXLightPerspective(_unk2, fovy, aspect, 0.5f, 0.5f, 0.5f, 0.5f);
                } break;
                case 3:
                    MTXLightFrustum(_unk2,
                                    arg0->_168,
                                    arg0->_16c,
                                    arg0->_170,
                                    arg0->_174,
                                    arg0->_17c,
                                    0.5f,
                                    0.5f,
                                    0.5f,
                                    0.5f);
                    break;
                case 2:
                    MTXLightOrtho(_unk2, arg0->_168, arg0->_16c, arg0->_170, arg0->_174, 0.5f, 0.5f, 0.5f, 0.5f);
                    break;
                default: MTXIdentity(_unk2); break;
            }

            GSmatrix _unk3;
            MTXConcat(_unk1, _unk2, _unk3);
            MTXCopy(_unk3, _unk1);
        }

        GSrender::sInstance->fn_802345F8(11, &_unk6, true);

        u32 _unk3 = mTexGenCount + 13;
        GSrender::sInstance->fn_802345F8(_unk3, &_unk1, true);
        GSrender::sInstance->setTexOffsetEnabled(mTexGenCount, false, false);
        GSrender::sInstance->fn_802346FC(mTexGenCount, 0, 1, 11, 1, _unk3);

        _25 = mTexGenCount++;
    } else {
        _25 = 0xFF;
    }
}

static inline u8 blend1(u8 c1, u8 c2) {
    f32 f1 = u8tof32(c1);
    f32 f2 = u8tof32(c2);
    return f32tou8((f1 * f2) / 255.f + 0.5f);
}

static inline u8 blend2(u8 c1, u8 c2, f32 f3) {
    f32 f1 = u8tof32(c1);
    f32 f2 = u8tof32(c2);

    return f32tou8(0.5f + f1 + f3 * (f2 - f1));
}

void GSmaterial::fn_801EA44C() {
    u8 _unk1 = 0;
    GSrenderLight **_unk2 = NULL;

    mChannelCount = 0;

    if ((mMatData->_5d & (1 << 0))) {
        _unk1 = GShierarchyModule::lbl_8063F46D;
        _unk2 = GShierarchyModule::lbl_804920B0;
    }

    GScolor matColor;
    GScolor ambColor;

    GSlight *_unk3 = GShierarchyModule::sInstance->get_118();
    if (_unk3 && (_unk3->checkLightFlag((1 << 0)))) {
        matColor.r = blend1(_unk3->_110.r, mMatData->_60.r);
        matColor.g = blend1(_unk3->_110.g, mMatData->_60.g);
        matColor.b = blend1(_unk3->_110.b, mMatData->_60.b);
        matColor.a = blend1(_unk3->_110.a, mMatData->_60.a);
    } else {
        matColor.r = 0;
        matColor.g = 0;
        matColor.b = 0;
        matColor.a = 255;
    }

    ambColor.r = mMatData->_64.r;
    ambColor.g = mMatData->_64.g;
    ambColor.b = mMatData->_64.b;
    ambColor.a = mMatData->_64.a;

    if (_2c.a != 0) {
        f32 _unk3 = u8tof32(_2c.a) / 255.f;
        ambColor.r = blend2(ambColor.r, _2c.r, _unk3);
        ambColor.g = blend2(ambColor.g, _2c.g, _unk3);
        ambColor.b = blend2(ambColor.b, _2c.b, _unk3);
        ambColor.a = blend2(ambColor.a, _2c.a, _unk3);
        GSrender::sInstance->setTevColor(2, GS_TEV_COLOR_U8, &_2c);
    }
}

void GSmaterial::fn_801EAA94() {
    _22 = 0xFF;
    _24 = 0xFF;

    u8 _unk1 = mMatData->mTextureCount;

    if ((mMatData->_5d & (1 << 5))) {
        GStexture *_unk2 = GShierarchyModule::sInstance->get_110();
        if (_unk2) {
            GSrender::sInstance->setTexture(_unk1, _unk2);
            _22 = _unk1++;
        }
    }

    if (!_26 && !mMatData->_54) {
        return;
    }

    if ((mMatData->_5d & (1 << 6))) {
        GStexture *_unk3 = _27 ? GShierarchyModule::sInstance->get_114() : GShierarchyModule::sInstance->get_128();
        if (_unk3) {
            GSrender::sInstance->setTexture(_unk1, _unk3);

            _24 = _unk1;

            if (_27) {
                GSrender::sInstance->setFlag((1 << 2) | (1 << 1));
            }
        }
    }
}

void GSmaterial::fn_801EABE8(bool inverted) {
    GXCullMode cullMode = (GXCullMode)mRenderSettings->mCullMode;
    if (inverted) {
        if (cullMode == GX_CULL_FRONT) {
            cullMode = GX_CULL_BACK;
        } else if (cullMode == GX_CULL_BACK) {
            cullMode = GX_CULL_FRONT;
        }
    }
    GSrender::sInstance->setCullMode(cullMode);

    if (sLastMeshRenderSettings == mRenderSettings) {
        return;
    }

    if (mRenderSettings->mBlend) {
        GSrender::sInstance->setBlend((GXBlendMode)mRenderSettings->mBlendMode,
                                      (GXBlendFactor)mRenderSettings->mBlendSrcFactor,
                                      (GXBlendFactor)mRenderSettings->mBlendDstFactor);
    } else {
        GSrender::sInstance->setBlend((GXLogicOp)mRenderSettings->mBlendOp);
    }

    GSrender::sInstance->setEfbUpdate(mRenderSettings->mColorUpdateEnable,
                                      mRenderSettings->mAlphaUpdateEnable,
                                      mRenderSettings->mZUpdateEnable);

    GSrender::sInstance->setDstAlpha(mRenderSettings->mDstAlphaEnable, mRenderSettings->mDstAlpha);

    GSrender::sInstance->setAlphaCompare(mRenderSettings->mAlphaCompEnable,
                                         mRenderSettings->mAlphaComp,
                                         mRenderSettings->mAlphaRef);

    GSrender::sInstance->setZCompare(mRenderSettings->mZCompareFunc != GX_ALWAYS, mRenderSettings->mZCompareFunc);

    GSrender::sInstance->setZTexture(mRenderSettings->mZTexture, mRenderSettings->mZTexOp, mRenderSettings->mZTexBias);

    sLastMeshRenderSettings = mRenderSettings;
}

void GSmaterial::fn_801EB044(bool inverted, bool blend, bool zComp) {
    GXCullMode cullMode = (GXCullMode)mRenderSettings->mCullMode;
    if (inverted) {
        if (cullMode == GX_CULL_FRONT) {
            cullMode = GX_CULL_BACK;
        } else if (cullMode == GX_CULL_BACK) {
            cullMode = GX_CULL_FRONT;
        }
    }
    GSrender::sInstance->setCullMode(cullMode);

    f32 _unk1 = u8tof32(mMatData->_64.a) / 255.f;
    f32 _unk2 = u8tof32(mBaseColor.a);
    u8 value = f32tou8(_unk2 * _unk1 + 0.5f);

    GScolor color(value, value, value, value);
    GSrender::sInstance->setChannelColors(0, color, color);

    if (sLastMeshRenderSettings != mRenderSettings) {
        if (blend) {
            if (mRenderSettings->mBlend) {
                GSrender::sInstance->setBlend((GXBlendMode)mRenderSettings->mBlendMode,
                                              (GXBlendFactor)mRenderSettings->mBlendSrcFactor,
                                              (GXBlendFactor)mRenderSettings->mBlendDstFactor);
            } else {
                GSrender::sInstance->setBlend((GXLogicOp)mRenderSettings->mBlendOp);
            }

            GSrender::sInstance->setEfbUpdate(mRenderSettings->mColorUpdateEnable,
                                              mRenderSettings->mAlphaUpdateEnable,
                                              mRenderSettings->mZUpdateEnable);

            GSrender::sInstance->setDstAlpha(mRenderSettings->mDstAlphaEnable, mRenderSettings->mDstAlpha);

            GSrender::sInstance->setAlphaCompare(mRenderSettings->mAlphaCompEnable,
                                                 mRenderSettings->mAlphaComp,
                                                 mRenderSettings->mAlphaRef);
        } else {
            GSrender::sInstance->setBlend(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCLR);
            GSrender::sInstance->setEfbUpdate(true, false, false);
            GSrender::sInstance->setDstAlpha(false, 255);
            GSrender::sInstance->setAlphaCompare(false, GX_ALWAYS, 0);
        }

        GSrender::sInstance->setZTexture(mRenderSettings->mZTexture,
                                         mRenderSettings->mZTexOp,
                                         mRenderSettings->mZTexBias);

        GSrender::sInstance->setZCompare(zComp && mRenderSettings->mZCompareFunc != GX_ALWAYS,
                                         mRenderSettings->mZCompareFunc);

        sLastMeshRenderSettings = mRenderSettings;
    }
}

void GSmaterial::fn_801EB668(bool inverted) {
    GXCullMode cullMode = (GXCullMode)mRenderSettings->mCullMode;
    if (inverted) {
        if (cullMode == GX_CULL_FRONT) {
            cullMode = GX_CULL_BACK;
        } else if (cullMode == GX_CULL_BACK) {
            cullMode = GX_CULL_FRONT;
        }
    }
    GSrender::sInstance->setCullMode(cullMode);

    f32 _unk1 = u8tof32(mMatData->_64.a) / 255.f;
    f32 _unk2 = u8tof32(mBaseColor.a);
    u8 value = f32tou8(_unk2 * _unk1 + 0.5f);

    GScolor color(value, value, value, value);
    GSrender::sInstance->setChannelColors(0, color, color);

    if (sLastMeshRenderSettings != mRenderSettings) {
        GSrender::sInstance->setZTexture(mRenderSettings->mZTexture,
                                         mRenderSettings->mZTexOp,
                                         mRenderSettings->mZTexBias);
        GSrender::sInstance->setZCompare(mRenderSettings->mZCompareFunc != GX_ALWAYS, mRenderSettings->mZCompareFunc);
        sLastMeshRenderSettings = mRenderSettings;
    }
}

void GSmaterial::fn_801EB87C(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1) {
    u8 kColorCount = mMatData->_58;
    GScolor *kColor = mMatData->_4;
    for (u8 i = 0; i < kColorCount; i++, kColor++) {
        GSrender::sInstance->setTevKColor(i, kColor);
    }

    u8(*tevSwapTable)[4] = mMatData->_c;
    u8 tevSwapCount = mMatData->_59;
    for (u8 i = 0; i < tevSwapCount; i++, tevSwapTable++) {
        GSrender::sInstance->setTevSwapModTable(i + 1,
                                                (*tevSwapTable)[0],
                                                (*tevSwapTable)[1],
                                                (*tevSwapTable)[2],
                                                (*tevSwapTable)[3]);
    }

    u8 textureCount = mMatData->mTextureCount;
    for (u8 i = 0; i < textureCount; i++) {
        GStexture *texture = mMatData->mTextureSlots[i];
        if (_14 && mOrigMatData->_50 == texture) {
            GSrender::sInstance->setTexture(i, _14);
        } else {
            GSrender::sInstance->setTexture(i, texture);
        }
    }

    _22 = 0xFF;
    _24 = 0xFF;

    fn_801E9DCC(arg0, arg1);

    mCurrTevStage = 0;

    u8 _unk1 = mMatData->_5c;
    for (u8 i = 0; i < _unk1; i++) {
        fn_801E74B0(mMatData->_40[i]);
    }

    GSrender::sInstance->configureColorChannel(0,
                                               (1 << 1) | (1 << 0),
                                               GX_SRC_REG,
                                               GX_SRC_REG,
                                               0,
                                               NULL,
                                               GX_AF_NONE,
                                               GX_DF_NONE);

    mChannelCount = 1;

    if (mCurrTevStage == 0) {
        GSrender::sInstance->setTevKAlphaSel(0, GX_TEV_KASEL_1);
    }

    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASA);
    GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevAlphaIn(mCurrTevStage,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       mCurrTevStage ? GX_CA_APREV : GX_CA_KONST);
    mCurrTevStage++;

    GSrender::sInstance->setNumTexGens(mTexGenCount);
    GSrender::sInstance->setNumChannels(mChannelCount);
    GSrender::sInstance->setNumTevStages(mCurrTevStage);
}

bool GSmaterial::fn_801EC050(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool arg2) {
    if (arg2 && !(mMatData->_5d & (1 << 3))) {
        GSrender::sInstance->setFogEnabled(false);
    }

    if (mBaseColor.a == 0) {
        return false;
    }

    u8 kColorCount = mMatData->_58;
    GScolor *kColor = mMatData->_4;
    for (u8 i = 0; i < kColorCount; i++, kColor++) {
        GSrender::sInstance->setTevKColor(i, kColor);
    }

    u8(*tevSwapTable)[4] = mMatData->_c;
    u8 tevSwapCount = mMatData->_59;
    for (u8 i = 0; i < tevSwapCount; i++, tevSwapTable++) {
        GSrender::sInstance->setTevSwapModTable(i + 1,
                                                (*tevSwapTable)[0],
                                                (*tevSwapTable)[1],
                                                (*tevSwapTable)[2],
                                                (*tevSwapTable)[3]);
    }

    u8 textureCount = mMatData->mTextureCount;
    for (u8 i = 0; i < textureCount; i++) {
        GStexture *texture = mMatData->mTextureSlots[i];
        if (_14 && mOrigMatData->_50 == texture) {
            GSrender::sInstance->setTexture(i, _14);
        } else {
            GSrender::sInstance->setTexture(i, texture);
        }
    }

    fn_801EAA94();
    fn_801E9DCC(arg0, arg1);
    fn_801EA44C();

    lbl_8063F3AC = mMatData;
    lbl_8063F3B0 = 0;

    return true;
}

_UnkMaterialStruct_1::_UnkMaterialStruct_1() {}

inline void GSrender::setTevKColorSel(u8 stage, u8 sel) {
    mState->mCurr.mTevKColorSels[stage] = (GXTevKColorSel)sel;
    mState->mTevKColorSelFlags |= (1 << stage);
    mState->_0 |= (1 << 4);
}

inline void GSrender::setTevKAlphaSel(u8 stage, u8 sel) {
    mState->mCurr.mTevKAlphaSels[stage] = (GXTevKAlphaSel)sel;
    mState->mTevKAlphaSelFlags |= (1 << stage);
    mState->_0 |= (1 << 4);
}

inline void GSrender::setIndTexStageDirect(u8 stage) {
    if (mState->mCurr.mIndTexStages[stage].mType != GS_TEV_NULL) {
        mState->mCurr.mIndTexStages[stage].mType = GS_TEV_DIRECT;
    }
    mState->mIndTexStageFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}

inline void GSrender::setTevStage(u8 stage, GXTexCoordID texCoord, GXTexMapID texMap, u8 channel) {
    GStevStage *tevStage = &mState->mCurr.mTevStages[stage];
    tevStage->mTexCoord = texCoord;
    tevStage->mTexMap = texMap;
    if (channel != 0xff) {
        tevStage->mChannel = (GXChannelID)(channel + GX_COLOR0A0);
    } else {
        tevStage->mChannel = GX_COLOR_NULL;
    }
    mState->mTevStageFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}

inline void GSrender::setTevSwapMode(u8 stage, u8 rasSel, u8 texSel) {
    GStevSwapMode *tevSwapMode = &mState->mCurr.mTevSwapModes[stage];
    tevSwapMode->mRasSel = (GXTevSwapSel)rasSel;
    tevSwapMode->mTexSel = (GXTevSwapSel)texSel;
    mState->mTevSwapModeFlags |= (1 << stage);
    mState->_0 |= (1 << 5);
}

inline void
GSrender::setTevColorOp(u8 stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg) {
    GStevOp *tevColorOp = &mState->mCurr.mTevColorOps[stage];
    tevColorOp->mOp = op;
    tevColorOp->mBias = bias;
    tevColorOp->mScale = scale;
    tevColorOp->mClamp = clamp;
    tevColorOp->mReg = reg;
    mState->mTevColorOpFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}

inline void
GSrender::setTevAlphaOp(u8 stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg) {
    GStevOp *tevAlphaOp = &mState->mCurr.mTevAlphaOps[stage];
    tevAlphaOp->mOp = op;
    tevAlphaOp->mBias = bias;
    tevAlphaOp->mScale = scale;
    tevAlphaOp->mClamp = clamp;
    tevAlphaOp->mReg = reg;
    mState->mTevAlphaOpFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}

inline void
GSrender::setTevColorIn(u8 stage, GXTevColorArg argA, GXTevColorArg argB, GXTevColorArg argC, GXTevColorArg argD) {
    GStevColorIn *tevColorIn = &mState->mCurr.mTevColorIns[stage];
    tevColorIn->mArgA = argA;
    tevColorIn->mArgB = argB;
    tevColorIn->mArgC = argC;
    tevColorIn->mArgD = argD;
    mState->mTevColorInFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}

inline void
GSrender::setTevAlphaIn(u8 stage, GXTevAlphaArg argA, GXTevAlphaArg argB, GXTevAlphaArg argC, GXTevAlphaArg argD) {
    GStevAlphaIn *tevAlphaIn = &mState->mCurr.mTevAlphaIns[stage];
    tevAlphaIn->mArgA = argA;
    tevAlphaIn->mArgB = argB;
    tevAlphaIn->mArgC = argC;
    tevAlphaIn->mArgD = argD;
    mState->mTevAlphaInFlags |= (1 << stage);
    mState->_0 |= (1 << 3);
}
