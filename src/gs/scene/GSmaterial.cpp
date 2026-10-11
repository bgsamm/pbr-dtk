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
extern GSmatrix lbl_804932B0;

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
        _18 = new GSmatrix[matData->_5b];
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

void GSmaterial::fn_801E8858(bool useTexture) {
    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    if (useTexture) {
        GSrender::sInstance->setTevStage(mCurrTevStage,
                                         (GXTexCoordID)mMatData->_75,
                                         (GXTexMapID)mMatData->_74,
                                         _21);
        GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                           GX_CC_ZERO,
                                           GX_CC_RASC,
                                           GX_CC_TEXC,
                                           (mCurrTevStage != GX_TEVSTAGE0) ? GX_CC_CPREV : GX_CC_ZERO);
    } else {
        GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, _21);
        GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                           GX_CC_ZERO,
                                           GX_CC_RASC,
                                           GX_CC_ONE,
                                           (mCurrTevStage != GX_TEVSTAGE0) ? GX_CC_CPREV : GX_CC_ZERO);
    }

    GSrender::sInstance->setTevAlphaIn(mCurrTevStage,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       (mCurrTevStage != GX_TEVSTAGE0) ? GX_CA_APREV : GX_CA_RASA);

    mCurrTevStage++;
}

void GSmaterial::fn_801E8BA4(bool useTexture) {
    GXTevColorArg colorIn = GX_CC_RASC;
    u8 channel = _21;

    if (useTexture) {
        GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
        GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
        GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
        GSrender::sInstance->setTevStage(mCurrTevStage,
                                         (GXTexCoordID)mMatData->_75,
                                         (GXTexMapID)mMatData->_74,
                                         _21);
        GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        mCurrTevStage++;

        colorIn = GX_CC_C2;
        channel = 0xFF;
    }

    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevStage(mCurrTevStage,
                                     (GXTexCoordID)mMatData->_77,
                                     (GXTexMapID)mMatData->_76,
                                     channel);

    bool hasPrevStage = (!useTexture && mCurrTevStage != 0) || (useTexture == true && mCurrTevStage > 1);
    GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                       GX_CC_ZERO,
                                       GX_CC_TEXC,
                                       colorIn,
                                       hasPrevStage ? GX_CC_CPREV : GX_CC_ZERO);

    if (mCurrTevStage > 1 || (!useTexture && mCurrTevStage == 1)) {
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    } else {
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    }

    mCurrTevStage++;
}

void GSmaterial::fn_801E9114(_UnkMaterialStruct_3 *arg0, bool useTexture) {
    GSrenderLight *renderLight = NULL;

    GSlight *light = GShierarchyModule::get_11c();
    if (light && light->checkLightFlag((1 << 0))) {
        renderLight = light->get_134();
    }

    if (!renderLight) {
        return;
    }

    GSvec3 dir(renderLight->mDirection.x, renderLight->mDirection.y, renderLight->mDirection.z);
    MTXMultVecSR(arg0->_1d4, &dir, &dir);

    f32 cosAngle = -dir.z;
    if (FLOAT_EQUAL(1.f + cosAngle, 0.f)) {
        return;
    }

    GSmatrix mtx;
    if (FLOAT_EQUAL(cosAngle, 1.f)) {
        MTXIdentity(mtx);
    } else {
        GSvec3 viewDir = -GSmath::sZAxis;
        GSvec3 half;
        VECHalfAngle(&dir, &viewDir, &half);
        half = -half;

        GSvec3 axis;
        VECCrossProduct(&half, &viewDir, &axis);
        f32 dot = VECDotProduct(&half, &viewDir);

        f32 angle;
        if (dot >= 1.f) {
            angle = 0.f;
        } else if (dot <= -1.f) {
            angle = PI;
        } else {
            angle = acosf(dot);
        }

        MTXRotAxisRad(mtx, &axis, angle);
    }

    mtx(0, 0) *= 0.5f;
    mtx(0, 1) *= 0.5f;
    mtx(0, 2) *= 0.5f;
    mtx(0, 3) = 0.5f;

    mtx(1, 0) *= 0.5f;
    mtx(1, 1) *= 0.5f;
    mtx(1, 2) *= 0.5f;
    mtx(1, 3) = 0.5f;

    mtx(2, 0) = 0.f;
    mtx(2, 1) = 0.f;
    mtx(2, 2) = 0.f;
    mtx(2, 3) = 0.f;

    u32 texMtx = mTexGenCount + 13;
    GSrender::sInstance->fn_802345F8(texMtx, &mtx, true);
    GSrender::sInstance->setTexOffsetEnabled(mTexGenCount, false, false);
    GSrender::sInstance->fn_802346FC(mTexGenCount, 0, 1, 10, 1, texMtx);

    GXTevColorArg colorIn = GX_CC_RASC;
    u8 channel = _21;

    if (useTexture) {
        GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
        GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
        GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG2);
        GSrender::sInstance->setTevStage(mCurrTevStage,
                                         (GXTexCoordID)mMatData->_75,
                                         (GXTexMapID)mMatData->_74,
                                         _21);
        GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        mCurrTevStage++;

        colorIn = GX_CC_C2;
        channel = 0xFF;
    }

    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevStage(mCurrTevStage,
                                     (GXTexCoordID)mTexGenCount,
                                     (GXTexMapID)mMatData->_76,
                                     channel);
    GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                       GX_CC_ZERO,
                                       GX_CC_TEXC,
                                       colorIn,
                                       (mCurrTevStage != GX_TEVSTAGE0) ? GX_CC_CPREV : GX_CC_ZERO);

    if (mCurrTevStage > 1 || (!useTexture && mCurrTevStage == 1)) {
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    } else {
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    }

    mTexGenCount++;
    mCurrTevStage++;
}

void GSmaterial::fn_801E98E0() {
    if (_24 == 0xFF) {
        return;
    }

    s32 sum = _26 + mMatData->_54;
    u8 alpha = (sum < 0xFF) ? sum : 0xFF;

    GScolor kColor(alpha, alpha, alpha, alpha);
    GSrender::sInstance->setTevKColor(2, &kColor);

    GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
    GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GSrender::sInstance->setTevKColorSel(mCurrTevStage, GX_TEV_KCSEL_K2);
    GSrender::sInstance->setTevKAlphaSel(mCurrTevStage, GX_TEV_KASEL_K2_A);
    GSrender::sInstance->setTevStage(mCurrTevStage, (GXTexCoordID)_25, (GXTexMapID)_24, 0xFF);
    GSrender::sInstance->setTevColorIn(mCurrTevStage,
                                       (mCurrTevStage != GX_TEVSTAGE0) ? GX_CC_CPREV : GX_CC_ZERO,
                                       GX_CC_TEXC,
                                       GX_CC_KONST,
                                       GX_CC_ZERO);
    GSrender::sInstance->setTevAlphaIn(mCurrTevStage,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       GX_CA_ZERO,
                                       (mCurrTevStage != GX_TEVSTAGE0) ? GX_CA_APREV : GX_CA_ZERO);

    mCurrTevStage++;
}

void GSmaterial::fn_801E9C18(_UnkMaterialStruct_3 *arg0) {
    if (!(mMatData->_5d & (1 << 2))) {
        return;
    }

    if (_21 == 0xFF) {
        return;
    }

    bool useTexture = (s8)mMatData->_74 >= 0;
    if (mMatData->_76 < 0) {
        fn_801E8858(useTexture);
    } else if (mMatData->_77 < 0) {
        fn_801E9114(arg0, useTexture);
    } else {
        fn_801E8BA4(useTexture);
    }
}

GSmatrix *GSmaterial::fn_801E9C74(u8 index, _UnkMaterialData_2 *data) {
    if (!_18) {
        return &lbl_804932B0;
    }

    static GSvec3 center(0.5f, 0.5f, 0.f);

    GSmatrix *mtx = &_18[index];
    u16 mask = (1 << index);
    if (_1c & mask) {
        mtx->setScale(GSvec3(data->_10, data->_14, 1.f));
        MTXTransApply(*mtx, *mtx, -center.x, -center.y, -center.z);

        GSmatrix rot;
        MTXRotRad(rot, 'Z', data->_c);
        MTXConcat(rot, *mtx, *mtx);

        MTXTransApply(*mtx, *mtx, center.x, center.y, center.z);
        mtx->translate(GSvec3(data->_4, data->_8, 0.f));

        _1c &= ~mask;
    }

    return mtx;
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

static inline f32 lerp(f32 a, f32 b, f32 t) {
    return a + t * (b - a);
}

void GSmaterial::fn_801EA44C() {
    u8 lightCount = 0;
    GSrenderLight **lights = NULL;

    mChannelCount = 0;

    if ((mMatData->_5d & (1 << 0))) {
        lightCount = GShierarchyModule::lbl_8063F46D;
        lights = GShierarchyModule::lbl_804920B0;
    }

    GScolor ambColor;
    GScolor matColor;

    GSlight *light = GShierarchyModule::sInstance->get_118();
    if (light && (light->checkLightFlag((1 << 0)))) {
        ambColor.r = f32tou8(0.5f + (u8tof32(light->_110.r) * u8tof32(mMatData->_60.r)) / 255.f);
        ambColor.g = f32tou8(0.5f + (u8tof32(light->_110.g) * u8tof32(mMatData->_60.g)) / 255.f);
        ambColor.b = f32tou8(0.5f + (u8tof32(light->_110.b) * u8tof32(mMatData->_60.b)) / 255.f);
        ambColor.a = f32tou8(0.5f + (u8tof32(light->_110.a) * u8tof32(mMatData->_60.a)) / 255.f);
    } else {
        ambColor.r = 0;
        ambColor.g = 0;
        ambColor.b = 0;
        ambColor.a = 255;
    }

    matColor.r = mMatData->_64.r;
    matColor.g = mMatData->_64.g;
    matColor.b = mMatData->_64.b;
    matColor.a = mMatData->_64.a;

    if (_2c.a != 0) {
        f32 t = u8tof32(_2c.a) / 255.f;
        matColor.r = f32tou8(0.5f + lerp(u8tof32(matColor.r), u8tof32(_2c.r), t));
        matColor.g = f32tou8(0.5f + lerp(u8tof32(matColor.g), u8tof32(_2c.g), t));
        matColor.b = f32tou8(0.5f + lerp(u8tof32(matColor.b), u8tof32(_2c.b), t));
        GSrender::sInstance->setTevColor(2, GS_TEV_COLOR_U8, &_2c);
    }

    bool _unk1 = (mMatData->_5e != 1 || mMatData->_5f != 1);
    if (_unk1 && lightCount) {
        GSrender::sInstance->setChannelColors(mChannelCount, ambColor, matColor);
        GSrender::sInstance->configureColorChannel(mChannelCount,
                                                   (1 << 0),
                                                   (GXColorSrc)mMatData->_5e,
                                                   (GXColorSrc)mMatData->_5f,
                                                   lightCount,
                                                   lights,
                                                   GX_AF_NONE,
                                                   GX_DF_CLAMP);
        GSrender::sInstance->configureColorChannel(mChannelCount,
                                                   (1 << 1),
                                                   (GXColorSrc)mMatData->_5e,
                                                   (GXColorSrc)mMatData->_5f,
                                                   0,
                                                   NULL,
                                                   GX_AF_NONE,
                                                   GX_DF_NONE);
    } else {
        GSrender::sInstance->setChannelColors(mChannelCount, ambColor, ambColor);
        GSrender::sInstance->configureColorChannel(mChannelCount,
                                                   (1 << 1) | (1 << 0),
                                                   (GXColorSrc)mMatData->_5e,
                                                   (GXColorSrc)mMatData->_5f,
                                                   0,
                                                   NULL,
                                                   GX_AF_NONE,
                                                   GX_DF_NONE);
    }

    _20 = mChannelCount;
    _21 = 0xFF;
    mChannelCount++;

    if ((mMatData->_5d & (1 << 2))) {
        u8 specLightCount = GShierarchyModule::lbl_8063F46E;
        GSrenderLight **specLights = GShierarchyModule::lbl_804920D0;
        if (specLightCount) {
            GSrender::sInstance->setChannelColors(mChannelCount, GScolor(0, 0, 0, 0), mMatData->_78);

            if (mMatData->_76 < 0) {
                for (u16 i = 0; i < specLightCount; i++) {
                    GSrenderLight *specLight = specLights[i];
                    if (specLight) {
                        specLight->setShininess(mMatData->_7c);
                        GSrender::sInstance->setLightsDirty();
                    }
                }

                GSrender::sInstance->configureColorChannel(mChannelCount,
                                                           (1 << 0),
                                                           GX_SRC_REG,
                                                           GX_SRC_REG,
                                                           specLightCount,
                                                           specLights,
                                                           GX_AF_SPEC,
                                                           GX_DF_NONE);
                GSrender::sInstance->configureColorChannel(mChannelCount,
                                                           (1 << 1),
                                                           GX_SRC_REG,
                                                           GX_SRC_REG,
                                                           0,
                                                           NULL,
                                                           GX_AF_NONE,
                                                           GX_DF_NONE);
            } else {
                GSrender::sInstance->configureColorChannel(mChannelCount,
                                                           (1 << 1) | (1 << 0),
                                                           GX_SRC_REG,
                                                           GX_SRC_REG,
                                                           0,
                                                           NULL,
                                                           GX_AF_NONE,
                                                           GX_DF_SIGN);
            }

            _21 = mChannelCount++;
        }
    }

    if (mBaseColor.r != 128 || mBaseColor.g != 128 || mBaseColor.b != 128 || mBaseColor.a != 255) {
        GSrender::sInstance->setTevKColor(3, &mBaseColor);
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

bool GSmaterial::fn_801EC538(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool arg2, bool arg3, u32 arg4) {
    lbl_8063D768._0 = 1;
    mCurrTevStage = 0;

    u8 prevFlags = lbl_8063F3B0;
    lbl_8063F3B0 = 0;
    if (arg2) {
        lbl_8063F3B0 |= (1 << 0);
    }
    if (arg3) {
        lbl_8063F3B0 |= (1 << 1);
    }

    if (lbl_8063F3AC == mMatData && prevFlags == lbl_8063F3B0) {
        return true;
    }

    if (arg2) {
        u8 count = mMatData->_5c;
        for (u8 i = 0; i < count; i++) {
            fn_801E74B0(mMatData->_40[i]);
        }
        fn_801E7FA4(arg0, arg1, arg4);
        fn_801E98E0();
    }

    if (arg3) {
        fn_801E9C18(arg0);
    }

    if (mCurrTevStage == 0) {
        lbl_8063F3B0 = 0;
        return false;
    }

    if (mBaseColor.r != 128 || mBaseColor.g != 128 || mBaseColor.b != 128 || mBaseColor.a != 255) {
        GSrender::sInstance->setIndTexStageDirect(mCurrTevStage);
        GSrender::sInstance->setTevSwapMode(mCurrTevStage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GSrender::sInstance->setTevKColorSel(mCurrTevStage, GX_TEV_KCSEL_K3);
        GSrender::sInstance->setTevKAlphaSel(mCurrTevStage, GX_TEV_KASEL_K3_A);
        GSrender::sInstance->setTevColorOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_2, GX_TRUE, GX_TEVPREV);
        GSrender::sInstance->setTevAlphaOp(mCurrTevStage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GSrender::sInstance->setTevStage(mCurrTevStage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GSrender::sInstance->setTevColorIn(mCurrTevStage, GX_CC_ZERO, GX_CC_KONST, GX_CC_CPREV, GX_CC_ZERO);
        GSrender::sInstance->setTevAlphaIn(mCurrTevStage, GX_CA_ZERO, GX_CA_KONST, GX_CA_APREV, GX_CA_ZERO);
        mCurrTevStage++;
    }

    GSrender::sInstance->setNumTexGens(mTexGenCount);
    GSrender::sInstance->setNumChannels(mChannelCount);
    GSrender::sInstance->setNumTevStages(mCurrTevStage);

    return true;
}
