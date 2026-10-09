#pragma once

#include "gs/GSmath.hpp"
#include "gs/scene/GSmaterial.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution.h>

struct GSmodelData;
struct GSmodelNodeData;
class GSmesh;
class _UnkClass8023C09C;

// TODO(samm) Move?
void fn_801EE044();

// TODO(samm) Convert to class?
struct _UnkModelStruct_1 {
    /* 0x00 */ u32 _0;
    /* 0x04 */ u8 _pad_4[0x8];
    // TODO(samm) Confirm type
    /* 0x0C */ GScolor *mVertexColors;
    /* 0x10 */ _UnkModelData_2 *_10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u8 _pad_18[0x2];
    /* 0x1a */ u8 _1a;
    /* 0x1b */ u8 _1b;

    _UnkModelStruct_1(GSmodelData *arg0);
    ~_UnkModelStruct_1();

    void fn_801EFA6C();
    void fn_801EFBE4(_UnkClass8023C09C *arg0, bool arg1);
};

// Size: 0x18c
class GSmodel : public GSnull {
private:
    /* 0x104 */ u32 _104;
    /* 0x108 */ GSboundingBox mBoundingBox;
    /* 0x124 */ GSvec3 mCenter;
    /* 0x130 */ f32 _130;
    /* 0x134 */ GScolor _134;
    /* 0x138 */ f32 _138;
    /* 0x13C */ f32 _13c;
    /* 0x140 */ f32 _140;
    /* 0x144 */ f32 _144;
    /* 0x148 */ f32 _148;
    /* 0x14C */ f32 _14c;
    /* 0x150 */ f32 _150;
    /* 0x154 */ GSvec3 _154;
    /* 0x160 */ f32 _160;
    /* 0x164 */ GSmodelData *mModelData;
    /* 0x168 */ GSmatrix *_168;
    /* 0x16C */ _UnkModelStruct_1 _16c;
    /* 0x188 */ GSmesh *mFirstMesh;

public:
    GSmodel(GSobject *parentObject, GSmodelNodeData *data);

    /* 0x08 */ virtual ~GSmodel();
    /* 0x0C */ virtual void update(f32 deltaTime);
    /* 0x10 */ virtual void initTransform(bool recursive);
    /* 0x14 */ virtual void updateTransform();

    bool fn_801F06E4(_UnkMaterialStruct_3 *arg0);
    bool fn_801F0B50(_UnkMaterialStruct_3 *arg0);
    bool fn_801F0B7C(_UnkMaterialStruct_3 *arg0, bool arg1);
    bool fn_801F0FD8(_UnkMaterialStruct_3 *arg0, bool arg1);
    bool fn_801F113C(_UnkMaterialStruct_3 *arg0);
    bool fn_801F134C(_UnkMaterialStruct_3 *arg0);
    void fn_801F15EC(u16 animId, u32 arg1, f32 arg2);

    // TODO(samm) Name
    bool checkUnkFlag(u16 flag) const {
        return (_104 & flag) == flag;
    }

    // TODO(samm) Name
    bool checkDataFlag(u16 flag) const {
        return (mModelData->mFlags & flag) == flag;
    }

    GSboundingBox *getBoundingBox() {
        return &mBoundingBox;
    }

    GSmesh *getMesh(u16 index) const;
    u16 countMeshes() const;

    static void fn_801F1554(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend);
};
