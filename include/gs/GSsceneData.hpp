#pragma once

#include "gs/GSmath.hpp"

#include <revolution.h>

struct GSanimationObject;
struct GSnodeAnimChannel;
struct GSobjectData;
struct GStexture;

#define MATERIAL_MAX_TEXTURE_SLOTS 5

typedef void (*GSanimationCallback)(GSanimationObject *node, GSnodeAnimChannel *channel, f32 cursor, bool blend);

// TODO(samm) Name? Move?
struct _TransformPivots {
    /* 0x00 */ GSvec3 mScalePivot;
    /* 0x0C */ GSvec3 mScaleToRot;
    /* 0x18 */ GSvec3 mRotToTrans;
};

struct _UnkMaterialData_1 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _pad_1[3];
    /* 0x4 */ u8 _4;
};

struct _UnkMaterialData_2 {};

struct GSmaterialData {
    /* 0x00 */ char *mName;
    /* 0x04 */ u8 _pad_04[20];
    /* 0x18 */ GStexture *mTextureSlots[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x2c */ void *_2c[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x40 */ _UnkMaterialData_1 *_40[2][2];
    /* 0x50 */ GStexture *_50;
    /* 0x54 */ u8 _54;
    /* 0x55 */ u8 _pad_55[0x2f];
    /* 0x84 */ _UnkMaterialData_2 *_84;
};

enum GSnodeType {
    GS_NODE_NULL = 0,
    GS_NODE_JOINT = 2,
    GS_NODE_MESH = 3,
    GS_NODE_CAMERA = 4,
    GS_NODE_LIGHT = 5,
    GS_NODE_VOLUME = 6,
    GS_NODE_PARTICLE = 7
};

// TODO(samm) Move elsewhere?
struct GSnodeAnimChannel {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 mChannel;
    /* 0x2 */ u8 mComponent;
    /* 0x3 */ u8 _3;
    /* 0x4 */ u8 _4;
    /* 0x5 */ u8 _5;
    /* 0x6 */ u8 mDataType;
    /* 0x7 */ u8 mScaleExp;
    /* 0x8 */ void *mKeyframes;
    /* 0xC */ GSanimationCallback mStepCallback;
};

// TODO(samm) Move elsewhere?
struct GSnodeAnimData {
    /* 0x0 */ u16 mAnimId;
    /* 0x2 */ u16 mChannelCount;
    /* 0x4 */ GSnodeAnimChannel *mChannels;
    /* 0x8 */ f32 mAnimLength;
    /* 0xc */ GSnodeAnimData *mNext;
};

// TODO(samm) Move elsewhere?
struct GSnodeData {
    /* 0x00 */ GSnodeType mNodeType;
    /* 0x04 */ char *mName;
    /* 0x08 */ u16 mId;
    /* 0x0A */ u16 mFlags;
    /* 0x0C */ Vec *mTranslation;
    /* 0x10 */ Vec *mRotation;
    /* 0x14 */ Vec *mScale;
    /* 0x18 */ _TransformPivots *mTransformPivots;
    /* 0x1C */ u32 _1c;
    /* 0x20 */ GSnodeAnimData *mAnimData;
    /* 0x24 */ GSnodeData *mFirstChild;
    /* 0x28 */ GSnodeData *mNextSibling;
    /* 0x2C */ u32 _2c;
};

struct _UnkSceneData_1 {
    /* 0x00 */ u8 _pad_00[24];
    /* 0x18 */ void *_18;
};

struct _UnkSceneData_2 {
    /* 0x00 */ u8 _pad_0[0x18];
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1c;
    /* 0x20 */ u32 _20;
};

// .sdr files
struct GSsceneData {
    /* 0x00 */ u8 _00;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 _04;
    /* 0x08 */ GSobjectData **mObjectList;
    /* 0x0c */ GStexture **mTextureList;
    /* 0x10 */ _UnkSceneData_1 **_10;
    /* 0x14 */ GSmaterialData **mMaterialList;
    /* 0x18 */ u16 mObjectCount;
    /* 0x1a */ u16 mTextureCount;
    /* 0x1c */ u16 _1c;
    /* 0x1e */ u16 mMaterialCount;
    /* 0x20 */ u8 _pad_20[4];
    /* 0x24 */ _UnkSceneData_2 *_24;
    /* 0x28 */ void *_28;
};

void fn_801E1278(GSnodeAnimChannel *channel, GSvec3 *vec);
void fn_801E1360(GSnodeAnimChannel *channel, GSquat *quat);
void fn_801E1504(GSnodeAnimChannel *channel, u8 *arg1);
void fn_801E1540(_UnkMaterialData_2 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E1714(_UnkSceneData_1 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E18F8(GSmaterialData *materialData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2F60(GSobjectData *objectData, GSsceneData *sceneData, u32 baseAddr, bool arg3);
void fn_801E3380(_UnkSceneData_2 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr);
