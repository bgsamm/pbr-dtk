#pragma once

#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/scene/GSanimationObject.hpp"

#include <revolution.h>

struct GSnodeAnimChannel;
struct GSnodeAnimData;
class GSobject;

// TODO(samm) Name? Move?
// Size: 0x20
struct _BlendRotationCache {
    /* 0x00 */ GSquat mBase;
    /* 0x10 */ GSquat mBlend;
};

// NOTE(samm) Name known from RTTI
// Size: 0x104
class GSnull : public GSblendObject {
protected:
    /* 0x010 */ u16 mFlags;
    /* 0x012 */ u8 mNodeType;
    /* 0x013 */ u8 mInheritState;
    /* 0x014 */ u16 mInheritFlags;
    /* 0x016 */ u16 mChildCount;
    /* 0x018 */ u8 mDepth;
    /* 0x01C */ GSnodeData *mNodeData;
    /* 0x020 */ GSvec3 mLocalTranslation;
    /* 0x02C */ GSquat mLocalRotationQuat;
    /* 0x03C */ GSvec3 mLocalRotationEuler;
    /* 0x048 */ GSvec3 mLocalScale;
    /* 0x054 */ GSvec3 mParentTranslation;
    /* 0x060 */ GSquat mParentRotation;
    /* 0x070 */ GSvec3 mParentScale;
    /* 0x07C */ GSvec3 mBlendTranslation;
    /* 0x088 */ GSquat mBlendRotationQuat;
    /* 0x098 */ GSvec3 mBlendRotationEuler;
    /* 0x0A4 */ GSvec3 mBlendScale;
    // TODO(samm) Revisit this
    /* 0x0B0 */ _TransformPivots *mTransformPivots;
    /* 0x0B4 */ _BlendRotationCache *mRotationCache;
    /* 0x0B8 */ GSobject *mParentObject;
    /* 0x0BC */ GSnull *mRoot;
    /* 0x0C0 */ GSnull *mParent;
    /* 0x0C4 */ GSnull *mNext;
    /* 0x0C8 */ GSnull *mPrev;
    /* 0x0CC */ GSnull *mFirstChild;
    /* 0x0D0 */ GSmatrix mTransform;

    static GSnull *sRootNodeList;
    static GSnull *sRootNode;
    static u8 sDepth;

protected:
    // TODO(samm) Name
    bool unkBool() const {
        return mNodeData ? ((mNodeData->mFlags >> 3) & 0x1) : true;
    }

    void initTranslation(f32 x, f32 y, f32 z) {
        MTXTrans(mTransform, x, y, z);
    }

    void applyParentScale() {
        MTXScaleApply(mTransform, mTransform, mParentScale.x, mParentScale.y, mParentScale.z);
    }

    void applyParentRotation() {
        Mtx mtx;
        MTXQuat(mtx, &mParentRotation);
        MTXConcat(mtx, mTransform, mTransform);
    }

    void applyParentTranslation() {
        MTXTransApply(mTransform, mTransform, mParentTranslation.x, mParentTranslation.y, mParentTranslation.z);
    }

    GSnull *nextPreorder() const;
    void registerAsRoot();
    void unregisterAsRoot();
    void insertChild(GSnull *child, GSnull *refNode, u32 where);
    void removeChild(GSnull *child);
    void applyParentTransform();
    void applyBlending(f32 blendFactor);
    void updateChildren(f32 deltaTime);
    bool fn_801F3C7C();

public:
    GSnull(GSnodeType type);
    GSnull(GSobject *parentObject, GSnodeData *data);

    /* 0x08 */ virtual ~GSnull();
    /* 0x0C */ virtual void update(f32 deltaTime);
    /* 0x10 */ virtual void initTransform(bool recursive);
    /* 0x14 */ virtual void updateTransform();

    GSnull *nextInObject() const;
    bool attachChild(u32 inheritFlags, GSnull *child, GSnull *refNode, u32 where);
    void unattachChild(GSnull *child);
    bool attachChild(u32 inheritFlags, GSobject *child, GSnull *refNode, u32 where);
    void unattachChild(GSobject *child);
    // TODO(samm) Name
    void markNeedsUpdate(bool recursive);
    bool fn_801F3CE0();

    static void fn_801F3D44(GSnull *node, GSnodeAnimChannel *channel, f32 cursor, bool blend);

    bool checkFlag(u16 flag) const {
        return (mFlags & flag) == flag;
    }

    bool isRoot() {
        return mRoot == this;
    }

    u16 getIndex() const {
        return mNodeData ? mNodeData->mIndex : 0;
    }

    GSnodeType getNodeType() const {
        return (GSnodeType)mNodeType;
    }

    GSmatrix *getTransform() {
        return &mTransform;
    }

    static void updateAllTrees(f32 deltaTime) {
        GSnull *node = sRootNodeList;
        while (node) {
            node->update(deltaTime);
            node = node->mNext;
        }
    }
};
