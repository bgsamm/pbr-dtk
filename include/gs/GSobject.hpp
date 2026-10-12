#pragma once

#include "gs/GSlinkedList.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/scene/GScamera.hpp"
#include "gs/scene/GShierMemObject.hpp"
#include "gs/scene/GSlight.hpp"
#include "gs/scene/GSmodel.hpp"
#include "gs/scene/GSnull.hpp"
#include "gs/scene/GSparticle.hpp"

#include <revolution.h>

class GSscene;
class GSmesh;

struct _UnkObjectStruct_3 {
    /* 0x00 */ u8 _pad_0[0xd8];
    /* 0xD8 */ f32 _d8;
    /* 0xDC */ f32 _dc;
    /* 0xE0 */ u8 _pad_e0[0x8];
    /* 0xE8 */ f32 _e8;
    /* 0xEC */ f32 _ec;
    /* 0xF0 */ u8 _pad_f0[0x8];
    /* 0xF8 */ f32 _f8;
    /* 0xFC */ f32 _fc;

    GSvec3 _unkVec3_1() const {
        GSvec3 _unk1;
        _unk1.x = _d8;
        _unk1.y = _e8;
        _unk1.z = _f8;
        return _unk1;
    }

    GSvec3 _unkVec3_2() const {
        GSvec3 _unk1;
        _unk1.x = _dc;
        _unk1.y = _ec;
        _unk1.z = _fc;
        return _unk1;
    }
};

// Size: 0x70
struct _UnkObjectStruct_2 {
    /* 0x000 */ u32 _0;
    /* 0x004 */ _UnkObjectStruct_3 *_4;
    /* 0x008 */ GSvec3 _8;
    /* 0x014 */ GSvec3 _14;
    /* 0x020 */ f32 _20;
    /* 0x024 */ f32 _24;
    /* 0x028 */ f32 _28;
    /* 0x02C */ Vec2 _2c;
    /* 0x034 */ f32 _34;
    /* 0x038 */ u8 _pad_38[0x6];
    /* 0x03E */ u8 _3e;
    /* 0x03F */ u8 _3f;
    /* 0x040 */ Mtx _40;

    // TODO(samm) Move?
    bool fn_801F8368(const GSmatrix *arg0, f32 deltaTime);
};

// Size: 0x154
class GSobject : public GShierMemObject {
private:
    /* 0x000 */ GSscene *mParentScene;
    /* 0x004 */ GSobjectData *mData;
    /* 0x008 */ GSnull **mNodes;
    /* 0x00C */ void *mLookupBuffer;
    /* 0x010 */ u16 *mCameraLookup;
    /* 0x014 */ u16 *mJointLookup;
    /* 0x018 */ u16 *mLightLookup;
    /* 0x01C */ GSmesh **mMeshLookup;
    /* 0x020 */ u16 *mModelLookup;
    /* 0x024 */ u16 *mParticleLookup;
    /* 0x028 */ u16 *mVolumeLookup;
    // TODO(samm) #define the 8
    /* 0x02C */ _UnkObjectStruct_2 (*_2c)[8];
    /* 0x030 */ GSdoublyLinkedList mModelList;
    /* 0x038 */ GSsinglyLinkedList _38;
    /* 0x03C */ u32 _3c;
    /* 0x040 */ u32 _40;
    /* 0x044 */ GStexture *_44;
    /* 0x048 */ GStexture *_48;
    /* 0x04C */ Mtx mPositionMtx;
    /* 0x07C */ Mtx mRotationMtx;
    /* 0x0AC */ Mtx mScaleMtx;
    /* 0x0DC */ u16 mFlags;
    /* 0x0DE */ u16 mNodeCount;
    /* 0x0E0 */ u16 mCameraCount;
    /* 0x0E2 */ u16 mJointCount;
    /* 0x0E4 */ u16 mLightCount;
    /* 0x0E6 */ u16 mMeshCount;
    /* 0x0E8 */ u16 mModelCount;
    /* 0x0EA */ u16 mParticleCount;
    /* 0x0EC */ u16 mVolumeCount;
    /* 0x0EE */ u16 _ee;
    /* 0x0F0 */ u16 mBaseAnimId;
    /* 0x0F4 */ u32 mBaseAnimType;
    /* 0x0F8 */ f32 mBaseAnimTime;
    /* 0x0FC */ f32 mBaseAnimLength;
    /* 0x100 */ f32 mBaseAnimSpeed;
    /* 0x104 */ u16 mBlendAnimId;
    /* 0x108 */ u32 mBlendAnimType;
    /* 0x10C */ f32 mBlendAnimTime;
    /* 0x110 */ f32 mBlendAnimLength;
    /* 0x114 */ f32 mBlendAnimSpeed;
    /* 0x118 */ f32 mAnimBlendFactor;
    /* 0x11C */ f32 mTransitionLength;
    /* 0x120 */ GSboundingBox mBoundingBox;
    /* 0x13C */ GSvec3 mCenter;
    // TODO(samm) GScolor?
    /* 0x148 */ u8 _148;
    /* 0x149 */ u8 _149;
    /* 0x14A */ u8 _14a;
    /* 0x14B */ u8 _14b;
    // TODO(samm) Figure out what's going on here
    /* 0x14C */ union {
        u32 _14c;
        struct {
            u16 _14c_0;
            u16 _14c_1;
        };
    };
    /* 0x150 */ union {
        u32 _150;
        struct {
            u16 _150_0;
            u16 _150_1;
        };
    };

    bool fn_801F40E0(GSnull *rootNode);
    void calcBoundingBox();
    void init();

    void registerModel(GSmodel *model) {
        mModelList.append(model);
    }

    GSnull *getNode(u16 index) const {
        if (!mNodes) {
            return NULL;
        }
        if (index >= mNodeCount) {
            return NULL;
        }
        return mNodes[index];
    }

public:
    GSobject(GSscene *parentScene, GSobjectData *data);
    ~GSobject();

    void fn_801F4C98(bool arg0);
    void startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed, bool arg2, bool arg3, bool arg4);
    void clearAnimation();
    f32 fn_801F5B44();
    f32 fn_801F5C60();
    void stepAnimTransition(f32 arg0);
    bool fn_801F5EBC();
    void fn_801F6390();
    void update(f32 deltaTime, bool updateNodes);

    GSscene *getParentScene() const {
        return mParentScene;
    }

    // TODO(samm) Name
    void *get_44() const {
        return _44;
    }

    // TODO(samm) Name
    void *get_48() const {
        return _48;
    }

    // TODO(samm) Name?
    bool checkFlag(u16 flag) {
        return (mFlags & flag) == flag;
    }

    u16 getBaseAnimId() const {
        return mBaseAnimId;
    }

    u16 getBlendAnimId() const {
        return mBlendAnimId;
    }

    GSnull *getRootNode() const {
        return getNode(0);
    }

    u16 getLightCount() const {
        return mLightCount;
    }

    GScamera *getCamera(u16 index) const {
        u16 *lookup = mCameraLookup;
        if (!lookup) {
            return NULL;
        }
        if (index >= mCameraCount) {
            return NULL;
        }
        return static_cast<GScamera *>(getNode(lookup[index]));
    }

    GSlight *getLight(u16 index) const {
        u16 *lookup = mLightLookup;
        if (!lookup) {
            return NULL;
        }
        if (index >= mLightCount) {
            return NULL;
        }
        return static_cast<GSlight *>(getNode(lookup[index]));
    }

    GSmodel *getModel(u16 index) const {
        u16 *lookup = mModelLookup;
        if (!lookup) {
            return NULL;
        }
        if (index >= mModelCount) {
            return NULL;
        }
        return static_cast<GSmodel *>(getNode(lookup[index]));
    }

    u16 getParticleCount() const {
        return mParticleCount;
    }

    GSparticle *getParticle(u16 index) const {
        u16 *lookup = mParticleLookup;
        if (!lookup) {
            return NULL;
        }
        if (index >= mParticleCount) {
            return NULL;
        }
        return static_cast<GSparticle *>(getNode(lookup[index]));
    }

    // TODO(samm) Name?
    void addChild(GSobject *child) {
        _38.append(child);
    }

    void removeChild(GSobject *child) {
        _38.remove(child);
    }
};
