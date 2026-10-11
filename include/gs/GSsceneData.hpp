#pragma once

#include "gs/GScolor.hpp"
#include "gs/GSmath.hpp"
#include "version.hpp"

#include <revolution.h>

// TODO(samm) Keeping all the data structs here for ease of reference

struct GSanimationObject;
struct GSchannelData;
struct GStexture;
struct GSmaterialData;
struct GSvertexFormat;
class GSdisplayList;

#define MATERIAL_MAX_TEXTURE_SLOTS 5

typedef void (*GSanimationCallback)(GSanimationObject *node, GSchannelData *channel, f32 cursor, bool blend);

// TODO(samm) Name? Move? Vec vs. GSvec3?
struct _TransformPivots {
    /* 0x00 */ GSvec3 mScalePivot;
    /* 0x0C */ GSvec3 mScaleToRot;
    /* 0x18 */ GSvec3 mRotToTrans;
    /* 0x24 */ union {
        Vec _24;
        struct {
            u32 _24_0;
            u32 _24_1;
            u32 _24_2;
        };
    };
};

enum GSnodeType {
    GS_NODE_NULL     = 0,
    GS_NODE_JOINT    = 2,
    GS_NODE_MODEL    = 3,
    GS_NODE_CAMERA   = 4,
    GS_NODE_LIGHT    = 5,
    GS_NODE_VOLUME   = 6,
    GS_NODE_PARTICLE = 7
};

// Size: 0xC
struct GSkeyframe {
    /* 0x0 */ u16 mInterpType;
    /* 0x2 */ u16 mValueIdx;
    /* 0x4 */ u16 mControlIdxL;
    /* 0x6 */ u16 mControlIdxR;
    /* 0x8 */ f32 mTime;
};

// TODO(samm) Name
struct GSanimTrackData {
    /* 0x00 */ void *mValues;
    /* 0x04 */ void *mControls;
    /* 0x08 */ u16 mValueCount;
    /* 0x0C */ f32 mDuration;
    /* 0x10 */ GSkeyframe *mKeyframes;
    /* 0x14 */ u16 mKeyframCount;
    /* 0x16 */ u16 mCachedIndex;
    /* 0x18 */ f32 mCachedTime;
    /* 0x1c */ union {
        s8 mCachedByte;
        s16 mCachedShort;
        u16 mCachedUShort;
        Vec mCachedVec3;
        Quaternion mCachedQuat;
    };
};

// TODO(samm) Name
// Size: 0x10
struct GSchannelData {
    /* 0x0 */ bool _0;
    /* 0x1 */ u8 mChannel;
    /* 0x2 */ u8 mComponent;
    /* 0x3 */ u8 _3;
    /* 0x4 */ u16 mIndex;
    /* 0x6 */ u8 mDataType;
    /* 0x7 */ u8 mScaleExp;
    /* 0x8 */ GSanimTrackData *mKeyframes;
    /* 0xC */ GSanimationCallback mStepCallback;
};

// TODO(samm) Name
struct GSkeyframeData {
    /* 0x0 */ u16 mAnimId;
    /* 0x2 */ u16 mChannelCount;
    /* 0x4 */ GSchannelData *mChannels;
    /* 0x8 */ f32 mAnimLength;
    /* 0xc */ GSkeyframeData *mNext;
};

struct GSnodeData {
    /* 0x00 */ GSnodeType mNodeType;
    /* 0x04 */ char *mName;
    /* 0x08 */ u16 mIndex;
    /* 0x0A */ u16 mFlags;
    /* 0x0C */ Vec *mTranslation;
    /* 0x10 */ Vec *mRotation;
    /* 0x14 */ Vec *mScale;
    /* 0x18 */ _TransformPivots *mTransformPivots;
    /* 0x1C */ f32 _1c;
    /* 0x20 */ GSkeyframeData *mAnimData;
    /* 0x24 */ GSnodeData *mFirstChild;
    /* 0x28 */ GSnodeData *mNextSibling;
    /* 0x2C */ void *_2c;
};

struct GSmeshRenderSettings {
    /* 0x00 */ u8 mBlendMode;
    /* 0x01 */ u8 mBlendSrcFactor;
    /* 0x02 */ u8 mBlendDstFactor;
    /* 0x03 */ u8 mBlendOp;
    /* 0x04 */ bool mBlend;
    /* 0x05 */ bool mColorUpdateEnable;
    /* 0x06 */ bool mAlphaUpdateEnable;
    /* 0x07 */ bool mZUpdateEnable;
    /* 0x08 */ u8 mZCompareFunc;
    /* 0x09 */ bool mAlphaCompEnable;
    /* 0x0A */ u8 mAlphaComp;
    /* 0x0B */ u8 mAlphaRef;
    /* 0x0C */ u8 _pad_c[0x3];
    /* 0x0F */ u8 mCullMode;
    /* 0x10 */ u8 _10;
    /* 0x11 */ bool mDstAlphaEnable;
    /* 0x12 */ u8 mDstAlpha;
    /* 0x13 */ u8 mZTexOp;
    /* 0x14 */ u32 mZTexBias;
    /* 0x18 */ GStexture *mZTexture;

    GSmeshRenderSettings(bool arg0);
};

struct _UnkMeshData_2 {
    /* 0x00 */ u8 _pad_0[0xb8];
    /* 0xB8 */ GSdisplayList *mDisplayList;
};

struct GSmeshData {
    /* 0x00 */ u32 _0;
    /* 0x04 */ GSmeshRenderSettings *mRenderSettings;
    /* 0x08 */ GSmaterialData *mMaterial;
    /* 0x0C */ u16 _c;
    /* 0x10 */ _UnkMeshData_2 *_10;
    /* 0x14 */ void *mDisplayList;
    /* 0x18 */ u32 mDisplayListSize;
    /* 0x1C */ GSmeshData *mNext;
    /* 0x20 */ void *_20;
};

struct _UnkModelData_1 {
    /* 0x00 */ GSvec3 mBoundingBoxMin;
    /* 0x0C */ GSvec3 mBoundingBoxMax;
};

struct _UnkModelData_2 {
    /* 0x0 */ GSvec2 *mTexCoords;
    /* 0x4 */ u16 mCount;
};

struct GSmodelData {
    /* 0x00 */ u16 mFlags;
    /* 0x02 */ u16 mVertexCount;
    /* 0x04 */ u16 _4;
    /* 0x06 */ u16 _6;
    /* 0x08 */ void *mVertices;
    /* 0x0C */ void *mWeights;
    /* 0x10 */ GScolor *mVertexColors;
    /* 0x14 */ _UnkModelData_2 *_14;
    /* 0x18 */ GSmeshData *mFirstMesh;
    /* 0x1C */ _UnkModelData_1 *_1c;
    /* 0x20 */ void *_20;
};

struct GSmodelNodeData : public GSnodeData {
    /* 0x30 */ GSmodelData *mModelData;
    /* 0x34 */ GSmatrix *_34;
    /* 0x38 */ void *_38;
};

struct _UnkAnimData_1 {
    /* 0x0 */ f32 _0;
    /* 0x4 */ u16 _4;
};

// Size: 0x30
struct GSanimationData {
    /* 0x00 */ char *mName;
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8;
    /* 0x0C */ f32 mLength;
    /* 0x10 */ u16 *_10;
    /* 0x14 */ u16 *_14;
    /* 0x18 */ u16 _18;
    /* 0x1A */ u16 _1a;
    /* 0x1C */ _UnkAnimData_1 *_1c;
    /* 0x20 */ _UnkAnimData_1 *_20;
    /* 0x24 */ u16 _24;
    /* 0x26 */ u16 _26;
    /* 0x28 */ u8 _28;
    /* 0x29 */ bool _29;
    /* 0x2A */ bool _2a;
    /* 0x2B */ bool _2b;
    /* 0x2C */ void *_2c;
};

struct _UnkObjectData_1 {
    /* 0x0 */ void *_0;
    /* 0x4 */ u8 _pad_4[0x4];
    /* 0x8 */ void *_8;
};

struct GSobjectData {
    /* 0x00 */ char *mName;
    /* 0x04 */ u16 mId;
    /* 0x06 */ u16 mNodeCount;
    /* 0x08 */ u16 mAnimCount;
    /* 0x0C */ GSanimationData *mAnimList;
    /* 0x10 */ GSnodeData *mRootNode;
    // TODO(samm) Confirm type (does data incl. possible matrix ptr?)
    /* 0x14 */ GSboundingBox *mBoundingBox;
    /* 0x18 */ _UnkObjectData_1 *_18;
};

struct _UnkMaterialData_1 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _1;
    /* 0x2 */ u8 _2;
    /* 0x3 */ u8 _3;
    /* 0x4 */ u8 _4;
    /* 0x5 */ u8 _5;
    /* 0x6 */ u8 _6;
};

// Size: 0x18
struct _UnkMaterialData_2 {
    /* 0x00 */ u8 _0;
    /* 0x01 */ u8 _1;
    /* 0x02 */ u8 _2;
    /* 0x03 */ u8 _pad_3[0x1];
    /* 0x04 */ f32 _4;
    /* 0x08 */ f32 _8;
    /* 0x0C */ f32 _c;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
};

// Size: 0x8c
struct GSmaterialData {
    /* 0x00 */ char *mName;
    /* 0x04 */ GScolor _4[2];
    /* 0x0C */ u8 _c[3][4];
    /* 0x18 */ GStexture *mTextureSlots[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x2c */ _UnkMaterialData_2 *_2c[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x40 */ _UnkMaterialData_1 *_40[4];
    /* 0x50 */ GStexture *_50;
    /* 0x54 */ u8 _54;
    /* 0x55 */ u8 _pad_55[0x3];
    /* 0x58 */ u8 _58;
    /* 0x59 */ u8 _59;
    /* 0x5A */ u8 mTextureCount;
    /* 0x5B */ u8 _5b;
    /* 0x5C */ u8 _5c;
    /* 0x5D */ u8 _5d;
    /* 0x5E */ u8 _5e;
    /* 0x5F */ u8 _5f;
    /* 0x60 */ GXColor _60;
    /* 0x64 */ GScolor _64;
    /* 0x68 */ u8 _pad_68[0xc];
    /* 0x74 */ u8 _74;
    /* 0x75 */ u8 _75;
    /* 0x76 */ s8 _76;
    /* 0x77 */ s8 _77;
    /* 0x78 */ GScolor _78;
    /* 0x7C */ f32 _7c;
    /* 0x80 */ u8 _pad_80[0x4];
    /* 0x84 */ GSkeyframeData *mKeyframes;
    /* 0x88 */ u8 _pad_88[0x4];

    GSmaterialData();
};

struct _UnkSceneData_1 {
    /* 0x00 */ u8 _pad_00[24];
    /* 0x18 */ void *_18;
};

struct GSenvData {
    /* 0x00 */ bool mFogEnable;
    /* 0x01 */ u8 mFogType;
    /* 0x02 */ bool mFogRangeAdjEnable;
    /* 0x04 */ f32 mFogStartZ;
    /* 0x08 */ f32 mFogEndZ;
    /* 0x0C */ GScolor mFogColor;
    /* 0x10 */ GStexture *_10;
    /* 0x14 */ GStexture *_14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1c;
    /* 0x20 */ u32 _20;
};

// .sdr files
struct GSsceneData {
    /* 0x00 */ Version mVersion;
    /* 0x08 */ GSobjectData **mObjectList;
    /* 0x0c */ GStexture **mTextureList;
    /* 0x10 */ _UnkSceneData_1 **_10;
    /* 0x14 */ GSmaterialData **mMaterialList;
    /* 0x18 */ u16 mObjectCount;
    /* 0x1a */ u16 mTextureCount;
    /* 0x1c */ u16 _1c;
    /* 0x1e */ u16 mMaterialCount;
    /* 0x20 */ u8 _pad_20[4];
    /* 0x24 */ GSenvData *mEnvData;
    /* 0x28 */ void *_28;
};

void fn_801E0A60(GSchannelData *channelData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E10C0(GSchannelData *channelData, f32 cursor, f32 *dst);
void fn_801E1278(GSchannelData *channelData, f32 cursor, GSvec3 *dst);
void fn_801E1360(GSchannelData *channelData, f32 cursor, GSquat *dst);
void fn_801E13B8(GSchannelData *channelData, f32 cursor, GSvec2 *dst);
void fn_801E1440(GSchannelData *channelData, f32 cursor, GScolor *dst);
void fn_801E1504(GSchannelData *channelData, f32 cursor, u8 *dst);
void fn_801E1540(GSkeyframeData *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E1714(_UnkSceneData_1 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E18F8(GSmaterialData *materialData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E1CD0(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2878(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2A60(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2A90(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2AE8(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2B40(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2D88(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2E34(GSanimationData *animationData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2F60(GSobjectData *objectData, GSsceneData *sceneData, u32 baseAddr, bool arg3);
void fn_801E3380(GSenvData *fogData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr);
