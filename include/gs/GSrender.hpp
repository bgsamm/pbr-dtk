#pragma once

#include <revolution/types.h>
#include <revolution/gx.h>
#include <revolution/mtx.h>

#include "gs/GSfile.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSvideo.hpp"
#include "gs/render/GSrenderLight.hpp"

#define GS_RENDER_INVALIDATE_CACHE (1 << 0)

#define GS_VERTEX_UPDATE_FORMAT    (1 << 1)
#define GS_VERTEX_UPDATE_ARRAYS    (1 << 2)
#define GS_VERTEX_INVALIDATE_CACHE (1 << 3)

typedef void (*UnkFunc1)(void *);
typedef void (*GSrenderFunc2)();
typedef void (*GSrenderFunc3)(f32);

struct GSColor {
    union {
        struct {
            /* 0x0 */ u8 r;
            /* 0x1 */ u8 g;
            /* 0x2 */ u8 b;
            /* 0x3 */ u8 a;
        };
        /* 0x0 */ u32 rgba;
    };

    GSColor() {}

    GSColor(u8 r, u8 g, u8 b, u8 a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
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
    UnkFunc1 _0;
    void *_4;
    u32 _8;
    GSrenderStruct2 *_c;
};

struct GSrenderStruct3 {
    u32 _0;
    u32 _4;
    u32 _8;
};

// size: 0xac
struct GSrenderStruct4 {
    u8 unk1[0x84];
    /* 0x84 */ u32 _84;
    /* 0x88 */ void *_88;
    u8 unk2[0x14];
    /* 0xa0 */ GSrenderStruct2 *_a0;
    /* 0xa4 */ GSrenderStruct2 *_a4;
    /* 0xa8 */ GSrenderStruct2 *_a8;
};

struct GSrenderStruct7;

// size: 0xc
struct GSVtxAttrArray {
    /* 0x0 */ bool mDirty;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 mStride;
    /* 0x3 */ u8 mAttr;
    /* 0x4 */ void *mBasePtr;
    /* 0x8 */ u32 mSize;
};

// size: 0x3d4
struct GSvertexFormat {
    /* 0x0 */ u8 mFlags;
    /* 0x4 */ GXVtxFmt mVtxFmt;
    /* 0x8 */ GXVtxAttrFmtList mVtxAttrFmtList[GX_VA_MAX_ATTR + 1];
    /* 0x1b8 */ GXVtxDescList mVtxDescList[GX_VA_MAX_ATTR + 1];
    /* 0x290 */ GSVtxAttrArray mAttrArrayList[GX_VA_MAX_ATTR + 1];
};

// size: 0x18
struct GStexGen {
    /* 0x0 */ GXTexGenType mTexGenFunc;
    /* 0x4 */ GXTexGenSrc mTexGenSrc;
    /* 0x8 */ u32 mTexMtx;
    /* 0xc */ GXBool mNormalize;
    /* 0x10 */ u32 mPostMtx;
    /* 0x14 */ GSlight *mLight;
};

// size: 0x2
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

// size: 0x38
struct GScolorChannel {
    /* 0x0 */ GXBool mEnable;
    /* 0x4 */ GXColorSrc mAmbSrc;
    /* 0x8 */ GXColorSrc mMatSrc;
    /* 0xc */ GXLightID mLightMask;
    /* 0x10 */ GXDiffuseFn mDiffFn;
    /* 0x14 */ GXAttnFn mAttnFn;
    /* 0x18 */ GSlight *mLights[8];
};

// size: 0xc
struct GStevStage {
    /* 0x0 */ GXTexCoordID mTexCoord;
    /* 0x4 */ GXTexMapID mTexMap;
    /* 0x8 */ GXChannelID mChannel;
};

// size: 0x10
struct GStevColorIn {
    /* 0x0 */ GXTevColorArg mArgA;
    /* 0x4 */ GXTevColorArg mArgB;
    /* 0x8 */ GXTevColorArg mArgC;
    /* 0xc */ GXTevColorArg mArgD;
};

// size: 0x10
struct GStevAlphaIn {
    /* 0x0 */ GXTevAlphaArg mArgA;
    /* 0x4 */ GXTevAlphaArg mArgB;
    /* 0x8 */ GXTevAlphaArg mArgC;
    /* 0xc */ GXTevAlphaArg mArgD;
};

// size: 0x14
struct GStevOp {
    /* 0x0 */ GXTevOp mOp;
    /* 0x4 */ GXTevBias mBias;
    /* 0x8 */ GXTevScale mScale;
    /* 0xc */ GXBool mClamp;
    /* 0x10 */ GXTevRegID mReg;
};

enum GStevColorType {
    TEV_COLOR_U8,
    TEV_COLOR_S10
};

// size: 0xc
struct GStevColor {
    /* 0x0 */ GStevColorType mType;
    union {
        /* 0x4 */ GXColor mColor;
        /* 0x4 */ GXColorS10 mColorS10;
    };
};

enum GStevIndType {
    TEV_DIRECT,
    TEV_INDIRECT,
    TEV_IND_WARP,
    TEV_IND_TILE,
    TEV_IND_BUMP_ST,
    TEV_IND_BUMP_XYZ,
    TEV_IND_REPEAT,
    TEV_NULL
};

// size: 0x24
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

// size: 0x8
struct GSindTexOrder {
    /* 0x0 */ GXTexCoordID mTexCoord;
    /* 0x4 */ GXTexMapID mTexMap;
};

// size: 0x8
struct GSindTexScale {
    /* 0x0 */ GXIndTexScale mScaleS;
    /* 0x4 */ GXIndTexScale mScaleT;
};

// size: 0x8
struct GStevSwapMode {
    /* 0x0 */ GXTevSwapSel mRasSel;
    /* 0x4 */ GXTevSwapSel mTexSel;
};

// size: 0x10
struct GStevSwapModeTable {
    /* 0x0 */ GXTevColorChan mRed;
    /* 0x4 */ GXTevColorChan mGreen;
    /* 0x8 */ GXTevColorChan mBlue;
    /* 0xc */ GXTevColorChan mAlpha;
};

// size: 0xa20
struct GSrenderSettings {
    /* 0x0 */ u8 mNumTexGens;
    /* 0x4 */ GStexGen mTexGens[8];
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
    // TODO use GSColor instead?
    /* 0x208 */ GXColor mChanAmbColors[2];
    /* 0x210 */ GXColor mChanMatColors[2];
    /* 0x218 */ u8 mNumTevStages;
    /* 0x21c */ GStevStage mTevStages[GX_MAX_TEVSTAGE];
    /* 0x2dc */ GStevColorIn mTevColorIns[GX_MAX_TEVSTAGE];
    /* 0x3dc */ GStevAlphaIn mTevAlphaIns[GX_MAX_TEVSTAGE];
    /* 0x3dc */ GStevOp mTevColorOps[GX_MAX_TEVSTAGE];
    /* 0x61c */ GStevOp mTevAlphaOps[GX_MAX_TEVSTAGE];
    /* 0x75c */ GStevColor mTevColors[GX_MAX_TEVREG];
    // I feel as though this should have used GX_MAX_TEVSTAGE
    /* 0x78c */ GSindTexStage mIndTexStages[GX_MAX_INDTEXSTAGE];
    /* 0x81c */ GXZTexOp mZTexOp;
    /* 0x820 */ GXTexFmt mZTexFmt;
    /* 0x824 */ u32 mZTexBias;
    /* 0x828 */ u8 mNumIndStages;
    /* 0x82c */ GSindTexOrder mIndTexOrders[GX_MAX_INDTEXSTAGE];
    /* 0x84c */ GSindTexScale mIndTexScales[GX_MAX_INDTEXSTAGE];
    // TODO use GSColor instead?
    /* 0x86c */ GXColor mTevKColors[GX_MAX_KCOLOR];
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
    u8 _9eb[0x1];
    /* 0x9ec */ GXBool mDitherEnable;
    /* 0x9f0 */ GXFogType mFogType;
    /* 0x9f4 */ f32 mFogStartZ;
    /* 0x9f8 */ f32 mFogEndZ;
    /* 0x9fc */ f32 mFogNearZ;
    /* 0xa00 */ f32 mFogFarZ;
    /* 0xa04 */ GXColor mFogColor;
    /* 0xa08 */ GXFogAdjTable mFogAdjTable;
    /* 0xa1c */ u16 mFogRangeAdjCenter;
    // TODO avoid this use of volatile?
    /* 0xa1e */ volatile GXBool mFogRangeAdjEnable;
    /* 0xa1f */ bool mFogEnable;
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
    // TODO confirm array length
    /* 0x14cc */ GSscissor _14cc[3];
    /* 0x14e4 */ GSvertexFormat *mVertexFormats[GX_MAX_VTXFMT];
    /* 0x1504 */ GSvertexFormat *mActiveFormat;
    u8 _1508[0xc];
    /* 0x1514 */ u8 mNumLights;
    /* 0x1518 */ GSlight *mLights[8];
    /* 0x1538 */ u32 _1538;
    /* 0x153c */ GSrenderStruct7 *_153c;
};

struct GSrenderStruct7 {
    u8 _0[0x7];
    /* 0x7 */ u8 _7;
};

// size: 0xc
class GSrenderClass1 {
public:
    u8 unk1[0xc];

    GSrenderClass1(u32 param1);
    ~GSrenderClass1();
};

class GSrenderClass2 {
public:
    u8 unk1[0x8];
    /* 0x8 */ GSrenderClass2 *_8;
};

// "GSrenderModule"
class GSrenderClass3 : public GSrenderClass2 {
public:
    virtual void func1(f32 param1);
    virtual void func2();
};

class GSrenderClass4 {
public:
    u8 unk1[0x18];
    /* 0x18 */ GSrenderClass4 *_18;
};

// "GSrenderTarget"
class GSrenderClass5 : public GSrenderClass4 {
public:
    virtual void func1();
    virtual void func2();
};

class GSrenderManager : public GSvideoManager {
public:
    /* 0xdc */ GSrenderState _dc;
    u8 unk5[0x1c];
    /* 0x1638 */ GSrenderState *mState;
    /* 0x163c */ GSrenderStruct4 _163c;
    /* 0x16e8 */ GSrenderClass1 *_16e8;
    /* 0x16ec */ GSlightStruct1 *_16ec;
    /* 0x16f0 */ u32 _16f0;
    /* 0x16f4 */ u32 _16f4;
    /* 0x16f8 */ bool _16f8;
    /* 0x16f9 */ bool _16f9;
    /* 0x16fa */ u8 _16fa;
    /* 0x16fb */ u8 _16fb;
    /* 0x16fc */ bool _16fc;
    /* 0x16fd */ u8 _16fd;
    /* 0x16fe */ u16 mFlags;
    /* 0x1700 */ GSdvdError mDvdError;
    /* 0x1704 */ u32 _1704;
    /* 0x1708 */ GSColor mFillColor;
    /* 0x170c */ MEMHeapHandle _170c;
    /* 0x1710 */ void *_1710;
    /* 0x1714 */ GSrenderStruct7 *_1714;
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
    
    GSrenderManager(GSrenderStruct1 *param1);
    ~GSrenderManager();

    void fn_802310C0();
    void fn_802311AC(GSrenderStruct3 *);
    void fn_802311BC(GSrenderStruct3 *);
    void fn_8023125C(GSrenderStruct3 *);
    void fn_80231260();
    void fn_802313B0();
    void fn_80231400();
    void fn_80231490(f32 param1);
    void fn_80231544();
    void fn_8023177C(GSdvdError error, u32 param2, GSColor fillColor);
    void fn_80231918();
    void fn_802321DC();

    u32 fn_80232404(UnkFunc1, void *);
    GSrenderStruct2 *fn_802324F0();
    GSrenderStruct2 *fn_8023246C();
    void fn_8023255C(u32, u32);
    void fn_80232770();
    void fn_802327E8();

    void fn_8023352C(u32 nVerts);
    void fn_80233580();
    void fn_8023378C(u32, u32, u32, u32, u32, u32, u32, u32);
    void fn_80233B88(u32, u32);
    void fn_80234474(u32, u32, u32, u32, u32, u32);
    void fn_80234FE0(f32, f32, f32, f32, f32, f32);
    void fn_80235178(u32, u32, u32, u32, u32);
    void fn_80235204(u32, f32, f32, f32, f32);
    void fn_80237798(u32);

    // 802377BC
    void loadLights();
    void fn_802384BC();
    void setVertexFormat(GSvertexFormat *param1);
    void fn_80239E58();
    void fn_8023A95C();
    void fn_8023AE54();

    void fn_8023B6B0();
    void fn_8023B6BC();
    void fn_8023B704();
    u32 fn_8023B864(u32);
    u32 fn_8023B948(void *);

    static GSrenderManager *sInstance;
};

namespace GSrender {
    // TODO can this work as a class method?
    void fn_80231374(void *param1);

    void fn_8023234C();
    void fn_80232394();

    GSvertexFormat *fn_8023CF1C(u32 param1);
    GSrenderStruct7 *fn_8023D6CC(void *param1);
    void fn_8023E2D0(void *param1);
    u16 fn_8023E540(void *param1);
    u16 fn_8023E548(void *param1);
};
