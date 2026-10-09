#pragma once

#include "gs/GScolor.hpp"
#include "gs/GSrender.hpp"
#include "gs/scene/GSanimationObject.hpp"

struct GSmatrix;
struct GSmeshRenderSettings;
class GSchannelData;

// Size: 0x30
struct _UnkMaterialStruct_1 {
    /* 0x00 */ u8 _pad_0[0x30];

    _UnkMaterialStruct_1();
};

struct _UnkMaterialStruct_2 {
    /* 0x0 */ u8 _0;
    /* 0x1 */ bool _1;
    /* 0x2 */ u8 mTexMapId;
    /* 0x3 */ u8 mTexCoordId;
    /* 0x4 */ u8 _4;
    /* 0x5 */ u8 _5;
};

struct _UnkMaterialStruct_3 {
    /* 0x000 */ u8 _pad_0[0x104];
    /* 0x104 */ u32 _104;
    /* 0x108 */ u8 _pad_108[0x60];
    /* 0x168 */ f32 _168;
    /* 0x16C */ f32 _16c;
    /* 0x170 */ f32 _170;
    /* 0x174 */ f32 _174;
    /* 0x178 */ f32 _178;
    /* 0x17c */ f32 _17c;
    /* 0x180 */ u8 _pad_180[0x2c];
    /* 0x1AC */ GSvec3 _1ac;
    /* 0x1B8 */ GSvec3 _1b8;
    /* 0x1C4 */ GSvec3 _1c4;
};

// NOTE(samm) Name known from RTTI
// Size: 0x38
class GSmaterial : public GSanimationObject {
protected:
    /* 0x08 */ const GSmaterialData *mOrigMatData;
    /* 0x0C */ GSmaterialData *mMatData;
    /* 0x10 */ GSmeshRenderSettings *mRenderSettings;
    /* 0x14 */ GStexture *_14;
    /* 0x18 */ _UnkMaterialStruct_1 *_18;
    /* 0x1C */ u8 _1c;
    /* 0x1D */ u8 mTexGenCount;
    /* 0x1E */ u8 mChannelCount;
    /* 0x1F */ u8 mCurrTevStage;
    /* 0x20 */ u8 _20;
    /* 0x21 */ u8 _21;
    /* 0x22 */ u8 _22;
    /* 0x23 */ u8 _23;
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 _25;
    /* 0x26 */ u8 _26;
    /* 0x27 */ u8 _27;
    /* 0x28 */ u32 _28;
    /* 0x2C */ GScolor _2c;
    /* 0x30 */ GScolor mBaseColor;

public:
    GSmaterial(GSmaterialData *data, GSmeshRenderSettings *arg1);

    /* 0x8 */ virtual ~GSmaterial();

    void fn_801E74B0(_UnkMaterialData_1 *arg0);
    GSmatrix *fn_801E9C74(u8 arg0, _UnkMaterialData_2 *arg1);
    void fn_801E9DCC(const _UnkMaterialStruct_3 *arg0, GSmatrix *arg1);
    void fn_801EA44C();
    void fn_801EAA94();
    void fn_801EABE8(bool inverted);
    void fn_801EB044(bool inverted, bool blend, bool zComp);
    void fn_801EB668(bool inverted);
    void fn_801EB87C(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1);
    bool fn_801EC050(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool arg2);
    bool fn_801EC538(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool arg2, bool arg3, u32 arg4);
    void fn_801ECBA8();

    GSmeshRenderSettings *getRenderSettings() const {
        return mRenderSettings;
    }

    u8 getAlpha() const {
        return mBaseColor.a;
    }

    static void fn_801EC9AC(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
