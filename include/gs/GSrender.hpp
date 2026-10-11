#pragma once

#include "decomp.h"
#include "gs/GScolor.hpp"
#include "gs/GSfile.hpp"
#include "gs/GSvideo.hpp"
#include "gs/render/GSrenderLight.hpp"
#include "gs/render/GStexture.hpp"

#include <revolution.h>

#define GS_RENDER_INVALIDATE_CACHE (1 << 0)
#define GS_RENDER_INVALIDATE_TEXTURE_CACHE (1 << 1)

#define GS_VERTEX_UPDATE_FORMAT (1 << 1)
#define GS_VERTEX_UPDATE_ARRAYS (1 << 2)
#define GS_VERTEX_INVALIDATE_CACHE (1 << 3)

struct GSrenderStruct8;
class _UnkClass80236704;
class GSdisplayList;
class GSmatrix;
class GSmesh;

typedef void (*_UnkRenderFunc_1)(void *);
typedef void (*GSrenderFunc2)();
typedef void (*GSrenderFunc3)(f32);

enum GStevMode {
    GS_TEV_MODE_MODULATE,
    GS_TEV_MODE_DECAL,
    GS_TEV_MODE_BLEND,
    GS_TEV_MODE_REPLACE,
    GS_TEV_MODE_PASSCLR,
    GS_TEV_MODE_ADD_TEX,
    GS_TEV_MODE_ADD_RAS,
    GS_TEV_MODE_ADD_MODULATE
};

enum GStevColorType {
    GS_TEV_COLOR_U8,
    GS_TEV_COLOR_S10
};

enum GStevIndType {
    GS_TEV_DIRECT,
    GS_TEV_INDIRECT,
    GS_TEV_IND_WARP,
    GS_TEV_IND_TILE,
    GS_TEV_IND_BUMP_ST,
    GS_TEV_IND_BUMP_XYZ,
    GS_TEV_IND_REPEAT,
    GS_TEV_NULL
};

struct GSrenderStruct1 {
    u8 mNumBuffers;
    u16 mEfbHeight;
    VideoFormat mVidFmt;
    u32 _8;
    u32 _C;
    u32 _10;
    u16 _14; // some sort of count
    u8 _16;
    u8 _17;
};

struct GSrenderStruct2 {
    _UnkRenderFunc_1 _0;
    void *_4;
    u32 _8;
    GSrenderStruct2 *_c;
};

struct GSrenderStruct3 {
    u32 _0;
    u32 _4;
    u32 _8;
};

// Size: 0xac
struct GSgraphicsFifo {
    u8 unk1[0x80];
    /* 0x80 */ GXFifoObj *mFifoObj;
    /* 0x84 */ u32 _84;
    /* 0x88 */ void *_88;
    /* 0x8c */ void *mReadPtr;
    /* 0x90 */ void *mWritePtr;
    /* 0x94 */ GXBool mOverhi;
    /* 0x95 */ GXBool mUnderlow;
    /* 0x96 */ GXBool mReadIdle;
    /* 0x97 */ GXBool mCmdIdle;
    /* 0x98 */ GXBool mBrkpt;
    /* 0x9c */ u8 _pad_9c[4];
    /* 0xa0 */ GSrenderStruct2 *_a0;
    /* 0xa4 */ GSrenderStruct2 *_a4;
    /* 0xa8 */ GSrenderStruct2 *_a8;
};

// Size: 0xc
struct GSvtxAttrArray {
    /* 0x0 */ bool mDirty;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 mStride;
    /* 0x3 */ u8 mAttr;
    /* 0x4 */ void *mBasePtr;
    /* 0x8 */ u32 mSize;
};

// Size: 0x3d4
struct GSvertexFormat {
    /* 0x0 */ u8 mFlags;
    /* 0x4 */ GXVtxFmt mVtxFmt;
    /* 0x8 */ GXVtxAttrFmtList mVtxAttrFmtList[GX_VA_MAX_ATTR + 1];
    /* 0x1b8 */ GXVtxDescList mVtxDescList[GX_VA_MAX_ATTR + 1];
    /* 0x290 */ GSvtxAttrArray mAttrArrayList[GX_VA_MAX_ATTR + 1];
};

// Size: 0x18
struct GStexGen {
    /* 0x0 */ GXTexGenType mType;
    /* 0x4 */ GXTexGenSrc mSrc;
    /* 0x8 */ u32 mTexMtx;
    /* 0xc */ GXBool mNormalize;
    /* 0x10 */ u32 mPostMtx;
    /* 0x14 */ GSrenderLight *mLight;
};

// Size: 0x2
struct GStexOffsetEnable {
    /* 0x0 */ GXBool mLineEnable;
    /* 0x1 */ GXBool mPointEnable;
};

struct GSscissor {
    /* 0x0 */ u16 mOrigX;
    /* 0x2 */ u16 mOrigY;
    /* 0x4 */ u16 mWidth;
    /* 0x6 */ u16 mHeight;
};

struct GSviewport {
    /* 0x0 */ f32 mOrigX;
    /* 0x4 */ f32 mOrigY;
    /* 0x8 */ f32 mWidth;
    /* 0xc */ f32 mHeight;
};

// Size: 0x38
struct GScolorChannel {
    /* 0x0 */ GXBool mEnable;
    /* 0x4 */ GXColorSrc mAmbSrc;
    /* 0x8 */ GXColorSrc mMatSrc;
    /* 0xc */ GXLightID mLightMask;
    /* 0x10 */ GXDiffuseFn mDiffFn;
    /* 0x14 */ GXAttnFn mAttnFn;
    /* 0x18 */ GSrenderLight *mLights[8];
};

// Size: 0xc
struct GStevStage {
    /* 0x0 */ GXTexCoordID mTexCoord;
    /* 0x4 */ GXTexMapID mTexMap;
    /* 0x8 */ GXChannelID mChannel;
};

// Size: 0x10
struct GStevColorIn {
    /* 0x0 */ GXTevColorArg mArgA;
    /* 0x4 */ GXTevColorArg mArgB;
    /* 0x8 */ GXTevColorArg mArgC;
    /* 0xc */ GXTevColorArg mArgD;
};

// Size: 0x10
struct GStevAlphaIn {
    /* 0x0 */ GXTevAlphaArg mArgA;
    /* 0x4 */ GXTevAlphaArg mArgB;
    /* 0x8 */ GXTevAlphaArg mArgC;
    /* 0xc */ GXTevAlphaArg mArgD;
};

// Size: 0x14
struct GStevOp {
    /* 0x0 */ GXTevOp mOp;
    /* 0x4 */ GXTevBias mBias;
    /* 0x8 */ GXTevScale mScale;
    /* 0xc */ GXBool mClamp;
    /* 0x10 */ GXTevRegID mReg;
};

// Size: 0xc
struct GStevColor {
    /* 0x0 */ GStevColorType mType;
    union {
        /* 0x4 */ GXColor mColor;
        /* 0x4 */ GXColorS10 mColorS10;
    };
};

// Size: 0x24
struct GSindTexStage {
    /* 0x0 */ GStevIndType mType;
    /* 0x4 */ GXIndTexStageID mIndStage;
    union {
        struct {
            /* 0x8 */ GXIndTexFormat mFormat;
            /* 0xc */ GXIndTexBiasSel mBiasSel;
            /* 0x10 */ GXIndTexMtxID mMatrixSel;
            /* 0x14 */ GXIndTexWrap mWrapS;
            /* 0x18 */ GXIndTexWrap mWrapT;
            /* 0x1c */ GXIndTexAlphaSel mAlphaSel;
            /* 0x20 */ GXBool mAddPrev;
            /* 0x21 */ GXBool mUtcLod;
        } indirect;

        struct {
            /* 0x8 */ GXBool mSignedOffsets;
            /* 0x9 */ GXBool mReplaceMode;
            /* 0xc */ GXIndTexMtxID mMatrixSel;
        } warp;

        struct {
            /* 0x8 */ u16 mTileSizeS;
            /* 0xa */ u16 mTileSizeT;
            /* 0xc */ u16 mTileSpacingS;
            /* 0xe */ u16 mTileSpacingT;
            /* 0x10 */ GXIndTexFormat mFormat;
            /* 0x14 */ GXIndTexMtxID mMatrixSel;
            /* 0x18 */ GXIndTexBiasSel mBiasSel;
            /* 0x1c */ GXIndTexAlphaSel mAlphaSel;
        } tile;

        struct {
            /* 0x8 */ GXIndTexMtxID mMatrixSel;
        } bump;
    };
};

// Size: 0x8
struct GSindTexOrder {
    /* 0x0 */ GXTexCoordID mTexCoord;
    /* 0x4 */ GXTexMapID mTexMap;
};

// Size: 0x8
struct GSindTexScale {
    /* 0x0 */ GXIndTexScale mScaleS;
    /* 0x4 */ GXIndTexScale mScaleT;
};

// Size: 0x8
struct GStevSwapMode {
    /* 0x0 */ GXTevSwapSel mRasSel;
    /* 0x4 */ GXTevSwapSel mTexSel;
};

// Size: 0x10
struct GStevSwapModeTable {
    /* 0x0 */ GXTevColorChan mRed;
    /* 0x4 */ GXTevColorChan mGreen;
    /* 0x8 */ GXTevColorChan mBlue;
    /* 0xc */ GXTevColorChan mAlpha;
};

// Size: 0xa20
struct GSrenderSettings {
    /* 0x0 */ u8 mNumTexGens;
    /* 0x4 */ GStexGen mTexCoordGens[8];
    /* 0xc4 */ u8 mLineWidth;
    /* 0xc8 */ GXTexOffset mLineTexOffsets;
    /* 0xcc */ u8 mPointSize;
    /* 0xd0 */ GXTexOffset mPointTexOffsets;
    /* 0xd4 */ GStexOffsetEnable mTexOffsetsEnabled[8];
    union {
        /* 0xe4 */ GXProjectionType mProjectionType;
        /* 0xe4 */ f32 mProjectionParams[7];
    };
    /* 0x100 */ GSscissor mScissor;
    /* 0x108 */ GSviewport mViewport;
    /* 0x118 */ GXBool mCoPlanar;
    /* 0x11c */ GXCullMode mCullMode;
    /* 0x120 */ GXClipMode mClipMode;
    /* 0x124 */ u8 mNumChans;
    /* 0x128 */ GScolorChannel mChannels[4];
    /* 0x208 */ GScolor mChanAmbColors[2];
    /* 0x210 */ GScolor mChanMatColors[2];
    /* 0x218 */ u8 mNumTevStages;
    /* 0x21c */ GStevStage mTevStages[GX_MAX_TEVSTAGE];
    /* 0x2dc */ GStevColorIn mTevColorIns[GX_MAX_TEVSTAGE];
    /* 0x3dc */ GStevAlphaIn mTevAlphaIns[GX_MAX_TEVSTAGE];
    /* 0x4dc */ GStevOp mTevColorOps[GX_MAX_TEVSTAGE];
    /* 0x61c */ GStevOp mTevAlphaOps[GX_MAX_TEVSTAGE];
    /* 0x75c */ GStevColor mTevColors[GX_MAX_TEVREG];
    // NOTE(samm) I feel as though this should have used GX_MAX_TEVSTAGE
    /* 0x78c */ GSindTexStage mIndTexStages[GX_MAX_INDTEXSTAGE];
    /* 0x81c */ GXZTexOp mZTexOp;
    /* 0x820 */ GXTexFmt mZTexFmt;
    /* 0x824 */ u32 mZTexBias;
    /* 0x828 */ u8 mNumIndStages;
    /* 0x82c */ GSindTexOrder mIndTexOrders[GX_MAX_INDTEXSTAGE];
    /* 0x84c */ GSindTexScale mIndTexScales[GX_MAX_INDTEXSTAGE];
    /* 0x86c */ GScolor mTevKColors[GX_MAX_KCOLOR];
    /* 0x87c */ GXTevKColorSel mTevKColorSels[GX_MAX_TEVSTAGE];
    /* 0x8bc */ GXTevKAlphaSel mTevKAlphaSels[GX_MAX_TEVSTAGE];
    /* 0x8fc */ GStevSwapMode mTevSwapModes[GX_MAX_TEVSTAGE];
    /* 0x97c */ GStevSwapModeTable mTevSwapModeTables[GX_MAX_TEVSWAP];
    /* 0x9bc */ GXBlendMode mBlendMode;
    /* 0x9c0 */ GXBlendFactor mBlendSrcFactor;
    /* 0x9c4 */ GXBlendFactor mBlendDstFactor;
    /* 0x9c8 */ GXLogicOp mBlendOp;
    /* 0x9cc */ GXBool mDstAlphaEnable;
    /* 0x9cd */ u8 mDstAlpha;
    /* 0x9ce */ GXBool mColorUpdateEnable;
    /* 0x9cf */ GXBool mAlphaUpdateEnable;
    /* 0x9d0 */ GXBool mZUpdateEnable;
    u8 _9d1[0x3];
    /* 0x9d4 */ GXBool mZCompareEnable;
    /* 0x9d8 */ GXCompare mZCompareFunc;
    /* 0x9dc */ GXCompare mAlphaComp0;
    /* 0x9e0 */ GXAlphaOp mAlphaOp;
    /* 0x9e4 */ GXCompare mAlphaComp1;
    /* 0x9e8 */ u8 mAlphaRef0;
    /* 0x9e9 */ u8 mAlphaRef1;
    /* 0x9ea */ GXBool mZCompBeforeTex;
    /* 0x9eb */ u8 _9eb;
    /* 0x9ec */ GXBool mDitherEnable;
    /* 0x9f0 */ GXFogType mFogType;
    /* 0x9f4 */ f32 mFogStartZ;
    /* 0x9f8 */ f32 mFogEndZ;
    /* 0x9fc */ f32 mFogNearZ;
    /* 0xa00 */ f32 mFogFarZ;
    /* 0xa04 */ GScolor mFogColor;
    /* 0xa08 */ GXFogAdjTable mFogAdjTable;
    /* 0xa1c */ u16 mFogRangeAdjCenter;
    // TODO(samm) Avoid this use of volatile?
    /* 0xa1e */ volatile GXBool mFogRangeAdjEnable;
    /* 0xa1f */ u8 mFogEnable;
};

struct GSrenderState {
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
    /* 0x8 */ u32 mTexGenFlags;
    /* 0xc */ u32 mTexOffsetFlags;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 mChanCtrlFlags;
    /* 0x1c */ u32 mChanAmbColorFlags;
    /* 0x20 */ u32 mChanMatColorFlags;
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 mTevStageFlags;
    /* 0x2c */ u32 mTevColorInFlags;
    /* 0x30 */ u32 mTevAlphaInFlags;
    /* 0x34 */ u32 mTevColorOpFlags;
    /* 0x38 */ u32 mTevAlphaOpFlags;
    /* 0x3c */ u32 mTevColorFlags;
    /* 0x40 */ u32 mIndTexStageFlags;
    /* 0x44 */ u32 _44;
    /* 0x48 */ u32 mIndTexOrderFlags;
    /* 0x4c */ u32 mIndTexScaleFlags;
    /* 0x50 */ u32 mTevKColorFlags;
    /* 0x54 */ u32 mTevKColorSelFlags;
    /* 0x58 */ u32 mTevKAlphaSelFlags;
    /* 0x5c */ u32 mTevSwapModeFlags;
    /* 0x60 */ u32 mTevSwapModeTableFlags;
    /* 0x64 */ u32 _64;
    /* 0x68 */ GSrenderSettings mCurr;
    /* 0xa88 */ GSrenderSettings mPrev;
    /* 0x14a8 */ u16 _14a8;
    /* 0x14aa */ u16 _14aa;
    /* 0x14ac */ GSviewport _14ac[2];
    // TODO(samm) Confirm array length
    /* 0x14cc */ GSscissor _14cc[3];
    /* 0x14e4 */ GSvertexFormat *mVertexFormats[GX_MAX_VTXFMT];
    /* 0x1504 */ GSvertexFormat *mActiveFormat;
    /* 0x1508 */ GSrenderStruct8 *_1508;
    /* 0x150c */ bool _150c;
    /* 0x150d */ u8 _pad_150d[7];
    /* 0x1514 */ u8 mLightCount;
    /* 0x1518 */ GSrenderLight *mLights[8];
    /* 0x1538 */ u32 mTextureFlags;
    /* 0x153c */ GStexture *mTextures[8];
};

// NOTE(samm) Name known from RTTI
class GSrender : public GSvideo {
private:
    /* 0xdc */ GSrenderState _dc;
    /* 0x1638 */ GSrenderState *mState;
    /* 0x163c */ GSgraphicsFifo mGraphicsFifo;
    /* 0x16e8 */ _UnkClass80236704 *_16e8;
    /* 0x16ec */ GSlightStruct1 *_16ec;
    /* 0x16f0 */ u32 _16f0;
    /* 0x16f4 */ u32 _16f4;
    /* 0x16f8 */ bool _16f8;
    // NOT a boolean
    /* 0x16f9 */ u8 _16f9;
    /* 0x16fa */ u8 _16fa;
    /* 0x16fb */ u8 _16fb;
    /* 0x16fc */ bool _16fc;
    /* 0x16fd */ u8 _16fd;
    /* 0x16fe */ u16 mFlags;
    /* 0x1700 */ GSdvdError mDvdError;
    /* 0x1704 */ u32 _1704;
    /* 0x1708 */ GScolor mFillColor;
    /* 0x170c */ MEMHeapHandle _170c;
    /* 0x1710 */ void *_1710;
    /* 0x1714 */ GStexture *_1714;
    /* 0x1718 */ bool _1718;
    /* 0x1719 */ bool _1719;
    u8 _171a;
    u8 _171b;
    u32 _171c;
    u32 _1720;
    u32 _1724;
    /* 0x1728 */ GSrenderFunc2 _1728;
    /* 0x172c */ GSrenderFunc2 _172c;
    /* 0x1730 */ GSrenderFunc3 _1730;
    /* 0x1734 */ GSrenderFunc2 _1734;
    /* 0x1738 */ u32 mPrimitiveType;
    /* 0x173c */ GSvertexFormat *mVertexFormat;

    GScolorChannel *getColorChannel(u32 channel) const {
        return &mState->mCurr.mChannels[channel];
    }

public:
    GSrender(GSrenderStruct1 *param1);
    virtual ~GSrender();

    void invalidateTextureCache() {
        mFlags |= GS_RENDER_INVALIDATE_TEXTURE_CACHE;
    }

    bool isFogEnabled() const {
        return mState->mCurr.mFogEnable;
    }

    // TODO(samm) Name these

    _UnkClass80236704 *get_16e8() const {
        return _16e8;
    }

    void set_16f4(u32 value) {
        _16f4 = value;
    }

    void set_16f8(bool value) {
        _16f8 = value;
    }

    u8 get_16f9() const {
        return _16f9;
    }

    void set_16f9(u8 value) {
        _16f9 = value;
    }

    bool get_1718() const {
        return _1718;
    }

    bool get_1719() const {
        return _1719;
    }

    void setTexOffsetEnabled(u8 gen, bool lineEnable, bool pointEnable) {
        GStexOffsetEnable *texOffset = &mState->mCurr.mTexOffsetsEnabled[gen];
        texOffset->mLineEnable = lineEnable;
        texOffset->mPointEnable = pointEnable;
        mState->mTexOffsetFlags |= (1 << gen);
        mState->_0 |= (1 << 0);
    }

    void setCullMode(GXCullMode mode) {
        mState->mCurr.mCullMode = mode;
        mState->_10 |= (1 << 1);
        mState->_0 |= (1 << 1);
    }

    void setClipMode(GXClipMode mode) {
        mState->mCurr.mClipMode = mode;
        mState->_10 |= (1 << 2);
        mState->_0 |= (1 << 1);
    }

    void setNumChannels(u8 nChans) {
        mState->mCurr.mNumChans = nChans;
        mState->_14 |= (1 << 0);
        mState->_0 |= (1 << 2);
    }

    void setNumTexGens(u8 nTexGens) {
        mState->mCurr.mNumTexGens = nTexGens;
        mState->_4 |= (1 << 0);
        mState->_0 |= (1 << 0);
    }

    void setNumTevStages(u8 nTevStages) {
        mState->mCurr.mNumTevStages = nTevStages;
        mState->_24 |= (1 << 0);
        mState->_0 |= (1 << 3);
    }

    void setNumIndStages(u8 nIndStages) {
        mState->mCurr.mNumIndStages = nIndStages;
        mState->_44 |= (1 << 0);
        mState->_0 |= (1 << 7);
    }

    void setChannelColors(u8 channel, const GScolor &ambColor, const GScolor &matColor) {
        mState->mCurr.mChanAmbColors[channel] = ambColor;
        mState->mCurr.mChanMatColors[channel] = matColor;
        mState->mChanAmbColorFlags |= (1 << channel);
        mState->mChanMatColorFlags |= (1 << channel);
        mState->_0 |= (1 << 2);
    }

    void setTevColor(u8 reg, GStevColorType type, GScolor *color) {
        GStevColor *tevColor = &mState->mCurr.mTevColors[reg];
        tevColor->mType = type;
        static_cast<GScolor &>(tevColor->mColor) = *color;
        mState->mTevColorFlags |= (1 << reg);
        mState->_0 |= (1 << 3);
    }

    void setTevKColor(u8 index, GScolor *color) {
        mState->mCurr.mTevKColors[index] = *color;
        mState->mTevKColorFlags |= (1 << index);
        mState->_0 |= (1 << 4);
    }

    void setTevSwapModTable(u8 index, u8 r, u8 g, u8 b, u8 a) {
        GStevSwapModeTable *table = &mState->mCurr.mTevSwapModeTables[index];
        table->mRed = (GXTevColorChan)r;
        table->mGreen = (GXTevColorChan)g;
        table->mBlue = (GXTevColorChan)b;
        table->mAlpha = (GXTevColorChan)a;
        mState->mTevSwapModeTableFlags |= (1 << index);
        mState->_0 |= (1 << 5);
    }

    void setZTexture(GStexture *zTexture, u8 op, u32 bias) {
        if (zTexture) {
            GXTexFmt fmt = (GXTexFmt)zTexture->getGXTextureFormat(true);
            mState->mCurr.mZTexOp = (GXZTexOp)op;
            mState->mCurr.mZTexFmt = fmt;
            mState->mCurr.mZTexBias = bias;
        } else {
            mState->mCurr.mZTexOp = GX_ZT_DISABLE;
            mState->mCurr.mZTexFmt = GX_TF_Z8;
            mState->mCurr.mZTexBias = 0;
        }
        mState->_24 |= (1 << 8);
        mState->_0 |= (1 << 3);
    }

    // TODO(samm) Better names for these blend inlines?

    void setBlend(GXBlendMode mode, GXBlendFactor srcFactor, GXBlendFactor dstFactor) {
        if (mode == GX_BM_NONE) {
            mState->mCurr.mBlendMode = GX_BM_NONE;
            mState->mCurr.mBlendSrcFactor = GX_BL_ONE;
            mState->mCurr.mBlendDstFactor = GX_BL_ONE;
            mState->mCurr.mBlendOp = GX_LO_NOOP;

        } else {
            mState->mCurr.mBlendMode = mode;
            mState->mCurr.mBlendSrcFactor = srcFactor;
            mState->mCurr.mBlendDstFactor = dstFactor;
            mState->mCurr.mBlendOp = GX_LO_NOOP;
        }
        mState->_64 |= (1 << 0);
        mState->_0 |= (1 << 6);
    }

    void setBlend(GXLogicOp op) {
        if (op == GX_LO_NOOP) {
            mState->mCurr.mBlendMode = GX_BM_NONE;
            mState->mCurr.mBlendSrcFactor = GX_BL_ONE;
            mState->mCurr.mBlendDstFactor = GX_BL_ONE;
            mState->mCurr.mBlendOp = GX_LO_NOOP;

        } else {
            mState->mCurr.mBlendMode = GX_BM_LOGIC;
            mState->mCurr.mBlendSrcFactor = GX_BL_ONE;
            mState->mCurr.mBlendDstFactor = GX_BL_ONE;
            mState->mCurr.mBlendOp = op;
        }
        mState->_64 |= (1 << 0);
        mState->_0 |= (1 << 6);
    }

    void setDstAlpha(bool enable, u8 alpha) {
        if (enable) {
            mState->mCurr.mDstAlphaEnable = GX_TRUE;
        } else {
            mState->mCurr.mDstAlphaEnable = GX_FALSE;
        }
        mState->mCurr.mDstAlpha = alpha;
        mState->_64 |= (1 << 1);
        mState->_0 |= (1 << 6);
    }

    void setEfbUpdate(bool colorEnable, bool alphaEnable, bool zEnable) const {
        if (colorEnable) {
            mState->mCurr.mColorUpdateEnable = GX_TRUE;
        } else {
            mState->mCurr.mColorUpdateEnable = GX_FALSE;
        }

        if (alphaEnable) {
            mState->mCurr.mAlphaUpdateEnable = GX_TRUE;
        } else {
            mState->mCurr.mAlphaUpdateEnable = GX_FALSE;
        }

        if (zEnable) {
            mState->mCurr.mZUpdateEnable = GX_TRUE;
        } else {
            mState->mCurr.mZUpdateEnable = GX_FALSE;
        }

        mState->_64 |= (1 << 2);
        mState->_0 |= (1 << 6);
    }

    // TODO(samm) Revisit the type of func
    void setZCompare(bool enable, u32 func) const {
        if (enable) {
            mState->mCurr.mZCompareEnable = GX_TRUE;
        } else {
            mState->mCurr.mZCompareEnable = GX_FALSE;
        }
        mState->mCurr.mZCompareFunc = (GXCompare)func;
        mState->_64 |= (1 << 3);
        mState->_0 |= (1 << 6);
    }

    void setAlphaCompare(bool enable, u8 comp, u8 ref) const {
        if (enable) {
            mState->mCurr.mAlphaComp0 = (GXCompare)comp;
            mState->mCurr.mAlphaRef0 = ref;
            mState->mCurr.mAlphaOp = GX_AOP_AND;
            mState->mCurr.mAlphaComp1 = GX_ALWAYS;
            mState->mCurr.mAlphaRef1 = 0;
            mState->mCurr.mZCompBeforeTex = GX_FALSE;
        } else {
            mState->mCurr.mAlphaComp0 = GX_ALWAYS;
            mState->mCurr.mAlphaRef0 = 0;
            mState->mCurr.mAlphaOp = GX_AOP_AND;
            mState->mCurr.mAlphaComp1 = GX_ALWAYS;
            mState->mCurr.mAlphaRef1 = 0;
            mState->mCurr.mZCompBeforeTex = GX_TRUE;
        }
        mState->_64 |= (1 << 4);
        mState->_0 |= (1 << 6);
    }

    void setFogEnabled(bool enable) {
        mState->mCurr.mFogEnable = enable;

        mState->_64 |= (1 << 6);
        if (enable) {
            mState->_64 |= (1 << 9);
            if (mState->mCurr.mFogRangeAdjEnable) {
                mState->_64 |= (1 << 8);
            }
        }
        mState->_0 |= (1 << 6);
    }

    void setFog(GXFogType type, f32 startZ, f32 endZ, const GScolor *color) {
        mState->mCurr.mFogType = type;
        mState->mCurr.mFogStartZ = startZ;
        mState->mCurr.mFogEndZ = endZ;
        mState->mCurr.mFogColor = *color;

        if (mState->mCurr.mFogEnable) {
            mState->_64 |= (1 << 6);
            mState->_0 |= (1 << 6);
        }
    }

    void setFogRangeAdjEnabled(bool enable) {
        mState->mCurr.mFogRangeAdjEnable = enable;
        mState->mCurr.mFogRangeAdjCenter = 0;

        if (mState->mCurr.mFogEnable) {
            mState->_64 |= (1 << 9);
            if (enable) {
                mState->_64 |= (1 << 8);
            }
            mState->_0 |= (1 << 6);
        }
    }

    void setLights(u32 lightCount, GSrenderLight **lights) {
        mState->mLightCount = lightCount;

        for (u8 i = 0; i < 8; i++) {
            if (i < lightCount) {
                mState->mLights[i] = lights[i];
            } else {
                mState->mLights[i] = NULL;
            }
        }

        mState->_14 |= (1 << 4);
        mState->_0 |= (1 << 2);
    }

    void setLightsDirty() {
        mState->_0 |= (1 << 2);
        mState->_14 |= (1 << 4);
    }

    void setTexture(u8 index, GStexture *texture) {
        if (mState->mTextures[index] != texture || (texture->mFlags & (1 << 0)) == (1 << 0)) {
            mState->mTextures[index] = texture;
            mState->mTextureFlags |= (1 << index);
        }
    }

    void setFlag(u16 flag) {
        mFlags |= flag;
    }

    void setTevKColorSel(u8 stage, u8 sel) {
        mState->mCurr.mTevKColorSels[stage] = (GXTevKColorSel)sel;
        mState->mTevKColorSelFlags |= (1 << stage);
        mState->_0 |= (1 << 4);
    }

    void setTevKAlphaSel(u8 stage, u8 sel) {
        mState->mCurr.mTevKAlphaSels[stage] = (GXTevKAlphaSel)sel;
        mState->mTevKAlphaSelFlags |= (1 << stage);
        mState->_0 |= (1 << 4);
    }

    void setIndTexStageDirect(u8 stage) {
        if (mState->mCurr.mIndTexStages[stage].mType != GS_TEV_NULL) {
            mState->mCurr.mIndTexStages[stage].mType = GS_TEV_DIRECT;
        }
        mState->mIndTexStageFlags |= (1 << stage);
        mState->_0 |= (1 << 3);
    }

    void setTevStage(u8 stage, GXTexCoordID texCoord, GXTexMapID texMap, u8 channel) {
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

    void setTevSwapMode(u8 stage, u8 rasSel, u8 texSel) {
        GStevSwapMode *tevSwapMode = &mState->mCurr.mTevSwapModes[stage];
        tevSwapMode->mRasSel = (GXTevSwapSel)rasSel;
        tevSwapMode->mTexSel = (GXTevSwapSel)texSel;
        mState->mTevSwapModeFlags |= (1 << stage);
        mState->_0 |= (1 << 5);
    }

    void setTevColorOp(u8 stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg) {
        GStevOp *tevColorOp = &mState->mCurr.mTevColorOps[stage];
        tevColorOp->mOp = op;
        tevColorOp->mBias = bias;
        tevColorOp->mScale = scale;
        tevColorOp->mClamp = clamp;
        tevColorOp->mReg = reg;
        mState->mTevColorOpFlags |= (1 << stage);
        mState->_0 |= (1 << 3);
    }

    void setTevAlphaOp(u8 stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID reg) {
        GStevOp *tevAlphaOp = &mState->mCurr.mTevAlphaOps[stage];
        tevAlphaOp->mOp = op;
        tevAlphaOp->mBias = bias;
        tevAlphaOp->mScale = scale;
        tevAlphaOp->mClamp = clamp;
        tevAlphaOp->mReg = reg;
        mState->mTevAlphaOpFlags |= (1 << stage);
        mState->_0 |= (1 << 3);
    }

    void setTevColorIn(u8 stage, GXTevColorArg argA, GXTevColorArg argB, GXTevColorArg argC, GXTevColorArg argD) {
        GStevColorIn *tevColorIn = &mState->mCurr.mTevColorIns[stage];
        tevColorIn->mArgA = argA;
        tevColorIn->mArgB = argB;
        tevColorIn->mArgC = argC;
        tevColorIn->mArgD = argD;
        mState->mTevColorInFlags |= (1 << stage);
        mState->_0 |= (1 << 3);
    }

    void setTevAlphaIn(u8 stage, GXTevAlphaArg argA, GXTevAlphaArg argB, GXTevAlphaArg argC, GXTevAlphaArg argD) {
        GStevAlphaIn *tevAlphaIn = &mState->mCurr.mTevAlphaIns[stage];
        tevAlphaIn->mArgA = argA;
        tevAlphaIn->mArgB = argB;
        tevAlphaIn->mArgC = argC;
        tevAlphaIn->mArgD = argD;
        mState->mTevAlphaInFlags |= (1 << stage);
        mState->_0 |= (1 << 3);
    }

    void fn_802310C0();
    void fn_802311AC(u32 *);
    void fn_802311BC(u32 *);
    void fn_8023125C(u32 *);
    void fn_80231260();
    void fn_802313B0();
    void fn_80231400();
    void update(f32 deltaTime);
    void draw();
    void fn_8023177C(GSdvdError error, u32 param2, GScolor fillColor);
    void fn_80231918();
    void fn_802321DC();

    u32 fn_80232404(_UnkRenderFunc_1 arg0, void *arg1);
    GSrenderStruct2 *fn_802324F0();
    GSrenderStruct2 *fn_8023246C();
    void fn_8023255C(u32, u32);
    void fn_80232770();
    void fn_802327E8();

    void fn_8023352C(u32 nVerts);
    void fn_80233580();
    void callDisplayList(GSdisplayList *displayList);
    void configureColorChannel(u32 channel,
                               u32 chanFlags,
                               GXColorSrc ambSrc,
                               GXColorSrc matSrc,
                               u32 lightCount,
                               GSrenderLight **lights,
                               GXAttnFn attnFn,
                               GXDiffuseFn diffFn);
    void configureTevStage(u8 stage, GStevMode mode);
    void configureTexCoordGen(u8 texCoord, u8 type, u8 src, Mtx texMtx, GXBool normalize, Mtx postMtx);
    void fn_802345F8(u32 arg0, GSmatrix *arg1, bool arg2);
    void fn_802346FC(u8 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);
    void fn_80234FE0(f32, f32, f32, f32, f32, f32);
    void fn_80235178(u32, u32, u32, u32, u32);
    void fn_80235204(u32, f32, f32, f32, f32);
    void fn_80237794(u32);
    void fn_80237798(u32);

    void setupFlatTranslucentTexture();
    void setupAdditiveMultiTexture(u8 textureCount);
    void setupVertexColoring();
    void setupMultiplicativeMultiTexture(u8 textureCount);
    // TODO(samm) Names
    void fn_80237FA4();
    void fn_80237FA8(u8 textureCount);
    void fn_80237FAC();
    void fn_80237FB0(u8 textureCount);
    void loadLights() NO_INLINE;
    void setVertexFormat(GSvertexFormat *format);
    void loadModelViewMatrix();
    void loadTextures();
    void syncRenderSettings();
    void fn_80239E58();
    void fn_8023A95C();
    void sync();

    void fn_8023B6B0();
    void fn_8023B6BC();
    void fn_8023B704();
    bool fn_8023B864(u32 arg0);
    void fn_8023B88C(u32 arg0);
    u32 fn_8023B948(void *arg0);

    /* NOTE(samm)
     * As far as I can tell, this should indeed be public; using
     * a getter introduces a whole host of regswap issues.
     */
    static GSrender *sInstance;
};

// TODO(samm) Move these somewhere appropriate
void fn_80231374(void *arg0);
void fn_8023234C();
void fn_80232394();
GSvertexFormat *fn_8023CF1C(u32 arg0);
