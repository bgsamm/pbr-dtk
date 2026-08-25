#pragma once

#include <revolution/types.h>

namespace gs {

struct GSmodelData;
struct GStextureData;
struct _UnkSceneData_2;

struct _UnkSceneData_1 {
    /* 0x00 */ u8 _pad_00[24];
    /* 0x18 */ void *_18;
};

#define MATERIAL_MAX_TEXTURE_SLOTS 5

struct _UnkMaterialData_1 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _pad_1[3];
    /* 0x4 */ u8 _4;
};

struct _UnkMaterialData_2 {};

struct GSmaterialData {
    /* 0x00 */ char *mName;
    /* 0x04 */ u8 _pad_04[20];
    /* 0x18 */ GStextureData *mTextureSlots[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x2c */ void *_2c[MATERIAL_MAX_TEXTURE_SLOTS];
    /* 0x40 */ _UnkMaterialData_1 *_40[2][2];
    /* 0x50 */ GStextureData *_50;
    /* 0x54 */ u8 _54;
    /* 0x55 */ u8 _pad_55[0x2f];
    /* 0x84 */ _UnkMaterialData_2 *_84;
};

// .sdr files
struct GSsceneData {
    /* 0x00 */ u8 _00;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 _04;
    /* 0x08 */ GSmodelData **mModelList;
    /* 0x0c */ GStextureData **mTextureList;
    /* 0x10 */ _UnkSceneData_1 **_10;
    /* 0x14 */ GSmaterialData **mMaterialList;
    /* 0x18 */ u16 mModelCount;
    /* 0x1a */ u16 mTextureCount;
    /* 0x1c */ u16 _1c;
    /* 0x1e */ u16 mMaterialCount;
    /* 0x20 */ u8 _pad_20[4];
    /* 0x24 */ _UnkSceneData_2 *_24;
    /* 0x28 */ void *_28;
};

void fn_801E1540(_UnkMaterialData_2 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E1714(_UnkSceneData_1 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E18F8(GSmaterialData *materialData, GSsceneData *sceneData, u32 baseAddr);
void fn_801E2F60(GSmodelData *modelData, GSsceneData *sceneData, u32 baseAddr, bool arg3);
void fn_801E3380(_UnkSceneData_2 *arg0, GSsceneData *sceneData, u32 baseAddr);
void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr);

} // namespace gs
