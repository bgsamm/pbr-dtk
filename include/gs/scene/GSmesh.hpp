#pragma once

#include "gs/scene/GShierMemObject.hpp"
#include "gs/scene/GSmaterial.hpp"

struct GSmeshData;
struct GSmatrix;
class GSmodel;
class _UnkClass8023C09C;

// NOTE(samm) Name known from RTTI
// Size: 0x28
class GSmesh : public GShierMemObject {
    // TODO(samm) Revisit this
    friend class GSmodel;

private:
    /* 0x00 */ u32 mFlags;
    /* 0x04 */ u32 _4;
    /* 0x08 */ GSmodel *mParentModel;
    // TODO(samm) Type?
    /* 0x0C */ GSmaterial *_c;
    /* 0x10 */ GSmeshData *mData;
    // TODO(samm) Type?
    /* 0x14 */ GSmaterial *mMaterial;
    /* 0x18 */ _UnkClass8023C09C *_18;
    /* 0x1C */ GSdisplayList *mDisplayList;
    /* 0x20 */ GSmesh *mNext;

public:
    GSmesh(GSmodel *parentModel, GSmeshData *data);

    /* 0x8 */ virtual ~GSmesh();

    bool fn_801ED62C(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool inverted, u32 arg3);
    bool fn_801EDDFC(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool inverted);
    bool fn_801EDEDC(bool inverted);
    bool fn_801EDF84(bool inverted);

    void lockAnimation() {
        if (mMaterial) {
            mMaterial->lockAnimation();
        }
    }

    void clearAnimation() {
        if (mMaterial) {
            mMaterial->clearAnimation();
        }
    }

    void initTransform() {
        if (mMaterial) {
            mMaterial->fn_801ECBA8();
        }
    }

    void update(f32 deltaTime) {
        if (mMaterial) {
            mMaterial->update(deltaTime);
        }
    }

    void _unkFunc_1() {
        mMaterial = _c;
    }

    GSmaterial *getMaterial() const {
        return mMaterial;
    }
};
