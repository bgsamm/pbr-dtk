#pragma once

#include "gs/GSlinkedList.hpp"
#include "gs/scene/GShierMemObject.hpp"
#include "gs/scene/GSlightNode.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution.h>

class GSscene;

// TODO(samm) Move elsewhere?
struct GSobjectData {
    /* 0x00 */ char *mName;
    /* 0x04 */ u16 mId;
    /* 0x06 */ u16 mNodeCount;
    /* 0x08 */ u16 mAnimCount;
    /* 0x0C */ void *mAnimList;
    /* 0x10 */ GSnodeData *mRootNode;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
};

// TODO(samm) Is this really what's going?
struct _UnkObjectStruct_1 {
    /* 0x0 */ GSlistNode *mHead;
    /* 0x4 */ GSlistNode *_4;

    _UnkObjectStruct_1() : mHead(NULL), _4(NULL) {}
};

// Size: 0x154
class GSobject : public GShierMemObject {
private:
    /* 0x000 */ GSscene *mParentScene;
    /* 0x004 */ GSobjectData *mData;
    /* 0x008 */ GSnull **mNodes;
    /* 0x00C */ u16 *mNodeLookup;
    /* 0x010 */ u16 *mCameraLookup;
    /* 0x014 */ u16 *mJointLookup;
    /* 0x018 */ u16 *mLightLookup;
    /* 0x01C */ u16 *mSubmeshLookup;
    /* 0x020 */ u16 *mMeshLookup;
    /* 0x024 */ u16 *mParticleLookup;
    /* 0x028 */ u16 *mVolumeLookup;
    /* 0x02C */ u32 _2c;
    /* 0x030 */ _UnkObjectStruct_1 _30;
    /* 0x038 */ _UnkObjectStruct_1 _38;
    /* 0x040 */ u32 _40;
    /* 0x044 */ void *_44;
    /* 0x048 */ void *_48;
    /* 0x04C */ Mtx mPositionMtx;
    /* 0x07C */ Mtx mRotationMtx;
    /* 0x0AC */ Mtx mScaleMtx;
    /* 0x0DC */ u16 mFlags;
    /* 0x0DE */ u16 mNodeCount;
    /* 0x0E0 */ u16 mCameraCount;
    /* 0x0E2 */ u16 mJointCount;
    /* 0x0E4 */ u16 mLightCount;
    /* 0x0E6 */ u16 mSubmeshCount;
    /* 0x0E8 */ u16 mMeshCount;
    /* 0x0EA */ u16 mParticleCount;
    /* 0x0EC */ u16 mVolumeCount;
    /* 0x0EE */ u16 _ee;
    /* 0x0F0 */ u16 _f0;
    /* 0x0F4 */ u32 _f4;
    /* 0x0F8 */ f32 _f8;
    /* 0x0FC */ f32 _fc;
    /* 0x100 */ f32 _100;
    /* 0x104 */ u16 _104;
    /* 0x108 */ u32 _108;
    /* 0x10C */ f32 _10c;
    /* 0x110 */ f32 _110;
    /* 0x114 */ f32 _114;
    /* 0x118 */ f32 _118;
    /* 0x11C */ f32 _11c;
    /* 0x120 */ f32 _120;
    /* 0x124 */ f32 _124;
    /* 0x128 */ f32 _128;
    /* 0x12C */ f32 _12c;
    /* 0x130 */ f32 _130;
    /* 0x134 */ f32 _134;
    /* 0x138 */ Mtx *_138;
    /* 0x13C */ f32 _13c;
    /* 0x140 */ f32 _140;
    /* 0x144 */ f32 _144;
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

public:
    GSobject(GSscene *parentScene, GSobjectData *data);
    ~GSobject();

    void fn_801F40E0(GSnull *arg0);
    void fn_801F4C98(bool arg0);
    void fn_801F4DF4(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, f32 arg5, f32 arg6);
    void fn_801F6618();

    GSscene *getParentScene() const {
        return mParentScene;
    }

    // TODO(samm) Name
    void *get_44() const {
        return _44;
    }

    // TODO(samm) Name?
    bool checkFlag(u16 flag) {
        return (mFlags & flag) == flag;
    }

    GSnull *getRootNode() const {
        if (!mNodes) {
            return NULL;
        }
        if (mNodeCount == 0) {
            return NULL;
        }
        return mNodes[0];
    }

    u16 getLightCount() const {
        return mLightCount;
    }

    GSlightNode *getLightNode(u16 index) const {
        u16 *lightIndices = mLightLookup;
        if (!lightIndices) {
            return NULL;
        }
        if (index >= mLightCount) {
            return NULL;
        }

        u16 nodeIndex = lightIndices[index];
        if (!mNodes) {
            return NULL;
        }
        if (nodeIndex >= mNodeCount) {
            return NULL;
        }

        return static_cast<GSlightNode *>(mNodes[nodeIndex]);
    }

    // TODO(samm) Name?
    void addChild(GSobject *child) {
        if (!child) {
            return;
        }

        GSlistNode *tail = _38.mHead;
        if (tail) {
            if (tail->mData == child) {
                return;
            }

            GSlistNode *node;
            while ((node = tail->mNext)) {
                if (node->mData == child) {
                    return;
                }
                tail = node;
            }
        }

        GSlistNode *newNode = GSlinkedList::allocNode();
        if (newNode) {
            newNode->mData = child;
            newNode->mNext = NULL;
        }

        if (tail) {
            tail->mNext = newNode;
        } else {
            _38.mHead = newNode;
        }
    }

    void removeChild(GSobject *child) {
        if (!child) {
            return;
        }

        GSlistNode *node = _38.mHead;
        GSlistNode *prev = NULL;

        if (!node) {
            return;
        }

        while (node) {
            if (node->mData == child) {
                break;
            }
            prev = node;
            node = node->mNext;
        }

        if (!node) {
            return;
        }

        GSlistNode *next = node->mNext;
        if (prev) {
            prev->mNext = next;
        } else {
            _38.mHead = next;
        }

        GSlinkedList::freeNode(node);
    }

    // TODO(samm) Name
    static void freeList1(_UnkObjectStruct_1 *list) {
        if (!list) {
            return;
        }

        GSlistNode *curr = list->mHead;
        while (curr) {
            GSlistNode *next = curr->mNext;
            GSlinkedList::freeNode(curr);
            curr = next;
        }

        list->mHead = NULL;
    }

    // TODO(samm) Name
    static void freeList2(_UnkObjectStruct_1 *list) {
        if (!list) {
            return;
        }

        GSlistNode *curr = list->mHead;
        while (curr) {
            GSlistNode *next = curr->_8;
            GSlinkedList::freeNode(curr);
            curr = next;
        }
    }
};
