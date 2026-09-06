#include "gs/scene/GSnull.hpp"

#include "common.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/scene/GScameraNode.hpp"
#include "gs/scene/GSjointNode.hpp"
#include "gs/scene/GSlightNode.hpp"
#include "gs/scene/GSmeshNode.hpp"
#include "gs/scene/GSparticleNode.hpp"
#include "gs/scene/GSvolumeNode.hpp"

#include "version.hpp"

// TODO(samm) Convert to enum?
#define START 0
#define BEFORE 1
#define AFTER 2
#define END 3

// TODO(samm) Convert to enum?
#define CHANNEL_TRANSLATION 0
#define CHANNEL_ROTATION 1
#define CHANNEL_SCALE 2

#define FLAG_UPDATE_TRANSFORM (1 << 0)
// TODO(samm) #define flag (1 << 1)
#define FLAG_UPDATE_LOCAL_ROTATION_QUAT (1 << 2)
#define FLAG_UPDATE_BLEND_TRANSLATION (1 << 3)
#define FLAG_UPDATE_BLEND_ROTATION (1 << 4)
#define FLAG_UPDATE_BLEND_ROTATION_QUAT (1 << 5)
#define FLAG_UPDATE_BLEND_SCALE (1 << 6)
#define FLAG_BLEND_ROTATION_MODEL_SPACE (1 << 7)
#define FLAG_BLEND_SCALE_LINEAR (1 << 8)
// TODO(samm) #define flag (1 << 9)

#define FLAG_INHERIT_TRANSLATION (1 << 0)
#define FLAG_INHERIT_ROTATION (1 << 1)
#define FLAG_INHERIT_SCALE (1 << 2)
#define FLAG_INHERIT_ROOT_TRANSLATION (1 << 3)
#define FLAG_INHERIT_ROOT_ROTATION (1 << 4)
#define FLAG_INHERIT_ROOT_SCALE (1 << 5)
#define FLAG_CACHE_INHERITED_TRANSLATION (1 << 6)
#define FLAG_CACHE_INHERITED_ROTATION (1 << 7)
#define FLAG_CACHE_INHERITED_SCALE (1 << 8)
// TODO(samm) #define flag (1 << 9)
// TODO(samm) #define flag (1 << 10)

#define STATE_TRANSLATION_CACHED (1 << 0)
#define STATE_ROTATION_CACHED (1 << 1)
#define STATE_SCALE_CACHED (1 << 2)

GSnull *GSnull::sRootNodeList;
GSnull *GSnull::sRootNode;
u8 GSnull::sDepth;

// TODO(samm) Move to GSmath.hpp once fully matching

inline GSvec3 getMtxScale(const Mtx mtx) {
    GSvec3 scale;
    scale.x = safe_sqrt(mtx[0][0] * mtx[0][0] + mtx[1][0] * mtx[1][0] + mtx[2][0] * mtx[2][0]);
    scale.y = safe_sqrt(mtx[0][1] * mtx[0][1] + mtx[1][1] * mtx[1][1] + mtx[2][1] * mtx[2][1]);
    scale.z = safe_sqrt(mtx[0][2] * mtx[0][2] + mtx[1][2] * mtx[1][2] + mtx[2][2] * mtx[2][2]);
    return scale;
}

inline GSquat getMtxRot(const Mtx mtx) {
    Mtx copy;
    MTXCopy(mtx, copy);

    GSvec3 scale = getMtxScale(copy);

    // TODO(samm) Inlining/macro?
    f32 x;
    if (scale.x > -EPSILON && scale.x < EPSILON) {
        x = (scale.x < 0.f) ? -EPSILON : EPSILON;
    } else {
        x = scale.x;
    }

    f32 y;
    if (scale.y > -EPSILON && scale.y < EPSILON) {
        y = (scale.y < 0.f) ? -EPSILON : EPSILON;
    } else {
        y = scale.y;
    }

    f32 z;
    if (scale.z > -EPSILON && scale.z < EPSILON) {
        z = (scale.z < 0.f) ? -EPSILON : EPSILON;
    } else {
        z = scale.z;
    }

    MTXScaleApply(copy, copy, 1.f / x, 1.f / y, 1.f / z);

    GSquat rotation;
    QUATMtx(&rotation, copy);

    return rotation;
}

inline GSvec3 getMtxTrans(const Mtx mtx) {
    GSvec3 trans;
    trans.x = mtx[0][3];
    trans.y = mtx[1][3];
    trans.z = mtx[2][3];
    return trans;
}

inline void blendTranslation(const GSvec3 *a, const GSvec3 *b, GSvec3 *out, f32 blendFactor) {
    GSvec3 _unk1, _unk2;
    VECSubtract(b, a, &_unk1);
    VECScale(&_unk1, &_unk2, blendFactor);
    VECAdd(a, &_unk2, out);
}

inline void blendRotationLocal(const GSquat *a, const GSquat *b, GSquat *out, f32 blendFactor) {
    GSquat blended;
    QUATSlerp(a, b, &blended, blendFactor);
    *out = blended;
}

inline void blendScaleLinear(const GSvec3 *a, const GSvec3 *b, GSvec3 *out, f32 blendFactor) {
    GSvec3 temp;
    VECScale(a, out, 1.f - blendFactor);
    VECScale(b, &temp, blendFactor);
    VECAdd(out, &temp, out);
}

inline void blendScaleGeometric(const GSvec3 *a, const GSvec3 *b, GSvec3 *out, f32 blendFactor) {
    out->x = SAFE_POW(a->x, 1.f - blendFactor);
    out->y = SAFE_POW(a->y, 1.f - blendFactor);
    out->z = SAFE_POW(a->z, 1.f - blendFactor);

    out->x = out->x * SAFE_POW(b->x, blendFactor);
    out->y = out->y * SAFE_POW(b->y, blendFactor);
    out->z = out->z * SAFE_POW(b->z, blendFactor);

    ensure_nonzero_inplace(&out->x);
    ensure_nonzero_inplace(&out->y);
    ensure_nonzero_inplace(&out->z);
}

GSnull::GSnull(GSnodeType type)
    : GSblendObject(NULL),
      mFlags((1 << 1) | FLAG_UPDATE_TRANSFORM),
      mNodeType(type),
      mInheritState(0),
      mInheritFlags(FLAG_INHERIT_SCALE | FLAG_INHERIT_ROTATION | FLAG_INHERIT_TRANSLATION),
      mChildCount(0),
      mDepth(0),
      mNodeData(NULL),
      mLocalTranslation(0.f, 0.f, 0.f),
      mLocalRotationQuat(0.f, 0.f, 0.f, 1.f),
      mLocalRotationEuler(0.f, 0.f, 0.f),
      mLocalScale(1.f, 1.f, 1.f),
      mTransformPivots(NULL),
      mRotationCache(NULL),
      mParentObject(NULL),
      mRoot(this),
      mParent(NULL),
      mNext(NULL),
      mPrev(NULL),
      mFirstChild(NULL) {
    registerAsRoot();
    MTXIdentity(mTransform);
}

GSnull::GSnull(GSobject *parentObject, GSnodeData *data)
    : GSblendObject(data->mAnimData),
      mFlags((1 << 1) | FLAG_UPDATE_TRANSFORM),
      mNodeType(GS_NODE_NULL),
      mInheritState(0),
      mInheritFlags(FLAG_INHERIT_SCALE | FLAG_INHERIT_ROTATION | FLAG_INHERIT_TRANSLATION),
      mChildCount(0),
      mDepth(0),
      mNodeData(data),
      mLocalTranslation(0.f, 0.f, 0.f),
      mLocalRotationQuat(0.f, 0.f, 0.f, 1.f),
      mLocalRotationEuler(0.f, 0.f, 0.f),
      mLocalScale(1.f, 1.f, 1.f),
      mTransformPivots(NULL),
      mRotationCache(NULL),
      mParentObject(parentObject),
      mRoot(NULL),
      mParent(NULL),
      mNext(NULL),
      mPrev(NULL),
      mFirstChild(NULL) {
    if (mBlendPlayer) {
        mRotationCache = (_BlendRotationCache *)GSmem::allocFromHeap(gUnkHeap2, sizeof(*mRotationCache));
    }

    mNodeType = data->mNodeType;

    mTransformPivots = data->mTransformPivots;
    MTXIdentity(mTransform);

    if (!sRootNode) {
        sRootNode = this;
    }
    mRoot = sRootNode;

    // TODO(samm) There's an extraneous move instruction here I can't get
    mDepth = sDepth++;

    GSnull *childNode;
    GSnodeData *childData = data->mFirstChild;
    while (childData) {
        switch (childData->mNodeType) {
            case GS_NODE_MESH:     childNode = new GSmeshNode(parentObject, childData); break;
            case GS_NODE_CAMERA:   childNode = new GScameraNode(parentObject, childData); break;
            case GS_NODE_JOINT:    childNode = new GSjointNode(parentObject, childData); break;
            case GS_NODE_LIGHT:    childNode = new GSlightNode(parentObject, childData); break;
            case GS_NODE_PARTICLE: childNode = new GSparticleNode(parentObject, childData); break;
            case GS_NODE_VOLUME:   childNode = new GSvolumeNode(parentObject, childData); break;
            case GS_NODE_NULL:
            default:               childNode = new GSnull(parentObject, childData); break;
        }
        if (childNode) {
            insertChild(childNode, NULL, END);
        }
        childData = childData->mNextSibling;
    }

    sDepth--;

    if (sRootNode == this) {
        registerAsRoot();
        sRootNode = NULL;
    }
}

GSnull::~GSnull() {
    GSnull *child = mFirstChild;
    while (child) {
        GSnull *nextChild = child->mNext;

        if (child->mRoot == mRoot) {
            delete child;
        } else {
            child->mPrev = NULL;
            child->mNext = NULL;
            child->mParent = NULL;

            if (mFirstChild == child) {
                mFirstChild = nextChild;
            }

            child->registerAsRoot();
        }

        child = nextChild;
    }

    if (mParent) {
        mParent->removeChild(this);
    }

    unregisterAsRoot();

    if (mRotationCache) {
        GSmem::freeToHeap(gUnkHeap2, mRotationCache);
    }
}

GSnull *GSnull::nextInObject() const {
    if (!mParentObject) {
        return NULL;
    }

    GSnull *next = nextPreorder();
    while (next) {
        if (next->mParentObject == mParentObject) {
            return next;
        }
        next = next->nextPreorder();
    }

    return NULL;
}

GSnull *GSnull::nextPreorder() const {
    if (mFirstChild) {
        return mFirstChild;
    }

    if (mNext) {
        return mNext;
    }

    GSnull *parent = mParent;
    while (parent) {
        if (parent->mNext) {
            return parent->mNext;
        }
        parent = parent->mParent;
    }

    return NULL;
}

void GSnull::registerAsRoot() {
    GSnull *tail = sRootNodeList;
    if (tail) {
        GSnull *curr;
        while ((curr = tail->mNext)) {
            if (this == curr) {
                return;
            }
            tail = curr;
        }
    }

    if (tail) {
        tail->mNext = this;
    } else {
        sRootNodeList = this;
    }

    mPrev = tail;
    mNext = NULL;
}

void GSnull::unregisterAsRoot() {
    GSnull *prev = mPrev;
    GSnull *next = mNext;

    if (prev) {
        prev->mNext = next;
    } else if (sRootNodeList == this) {
        sRootNodeList = next;
    }

    if (next) {
        next->mPrev = prev;
    }

    mPrev = NULL;
    mNext = NULL;
}

bool GSnull::attachChild(u32 inheritFlags, GSnull *child, GSnull *refNode, u32 where) {
    if (!child->isRoot() || mParentObject == child->mParentObject) {
        return false;
    }

    GSnull *parent = this;
    while (parent) {
        if (parent == child) {
            return false;
        }
        parent = parent->mParent;
    }

    insertChild(child, refNode, where);
    child->mInheritFlags = inheritFlags;
    child->mInheritState = 0;

    return true;
}

void GSnull::unattachChild(GSnull *child) {
    if (!child->isRoot() || mParentObject == child->mParentObject) {
        return;
    }
    removeChild(child);
}

bool GSnull::attachChild(u32 inheritFlags, GSobject *child, GSnull *refNode, u32 where) {
    if (mParentObject == child) {
        return false;
    }

    GSnull *childNode = child->getRootNode();
    if (!childNode || !childNode->isRoot()) {
        return false;
    }

    GSnull *parent = this;
    while (parent) {
        if (parent == childNode) {
            return false;
        }
        parent = parent->mParent;
    }

    insertChild(childNode, refNode, where);
    childNode->mInheritFlags = inheritFlags;
    childNode->mInheritState = 0;

    return true;
}

void GSnull::unattachChild(GSobject *child) {
    if (mParentObject == child) {
        return;
    }

    GSnull *childNode = child->getRootNode();
    if (!childNode || !childNode->isRoot()) {
        return;
    }

    removeChild(childNode);
}

void GSnull::insertChild(GSnull *child, GSnull *refNode, u32 where) {
    if (!child) {
        return;
    }

    if (child->mParent) {
        child->mParent->removeChild(child);
    }

    child->unregisterAsRoot();

    switch (where) {
        case START: refNode = NULL; break;
        case BEFORE:
            if (refNode) {
                refNode = refNode->mPrev;
            }
            break;
        case AFTER: break;
        case END:
            if (!refNode) {
                refNode = mFirstChild;
            }
            if (refNode) {
                GSnull *curr;
                while ((curr = refNode->mNext)) {
                    refNode = curr;
                }
            }
            break;
        default: return;
    }

    if (!refNode) {
        child->mNext = mFirstChild;

        if (mFirstChild) {
            mFirstChild->mPrev = child;
        }

        child->mPrev = NULL;
        mFirstChild = child;
    } else {
        child->mNext = refNode->mNext;

        if (refNode->mNext) {
            refNode->mNext->mPrev = child;
        }

        child->mPrev = refNode;
        refNode->mNext = child;
    }

    child->mParent = this;
    child->mInheritFlags = FLAG_INHERIT_SCALE | FLAG_INHERIT_ROTATION | FLAG_INHERIT_TRANSLATION;
    child->mInheritState = 0;

    GSobject *childObject, *thisObject;

    thisObject = mParentObject;
    if (thisObject && thisObject->get_44()) {
        childObject = child->mParentObject;

        // TODO(samm) #define flag & clean up this condition
        if (childObject && childObject != thisObject && !childObject->get_44() && !childObject->checkFlag((1 << 2)) &&
            !childObject->getParentScene()) {
            thisObject->addChild(childObject);
        }
    }

    markNeedsUpdate(true);
    mChildCount++;
}

void GSnull::removeChild(GSnull *child) {
    if (!child) {
        return;
    }

    if (child->mParent != this) {
        return;
    }

    GSnull *prevChild, *nextChild;

    nextChild = child->mNext;
    prevChild = child->mPrev;

    GSobject *childObject = child->mParentObject;
    if (childObject) {
        GSobject *thisObject = mParentObject;

        if (childObject != thisObject) {
            thisObject->removeChild(childObject);
        }
    }

    child->mParent = NULL;
    child->mPrev = NULL;
    child->mNext = NULL;

    if (nextChild) {
        nextChild->mPrev = prevChild;
    }

    if (prevChild) {
        prevChild->mNext = nextChild;
    } else {
        mFirstChild = nextChild;
    }

    child->mInheritFlags = 0;
    child->mInheritState = 0;

    mChildCount--;
    child->registerAsRoot();
    markNeedsUpdate(true);
}

void GSnull::markNeedsUpdate(bool recursive) {
    mFlags |= FLAG_UPDATE_TRANSFORM;

    if (recursive) {
        GSnull *child = mFirstChild;
        while (child) {
            child->markNeedsUpdate(true);
            child = child->mNext;
        }
    }
}

void GSnull::applyParentTransform() {
    if (!mParent) {
        return;
    }

    if (!unkBool() || !(mInheritFlags & (FLAG_INHERIT_SCALE | FLAG_INHERIT_ROTATION | FLAG_INHERIT_TRANSLATION))) {
        return;
    }

    if (mParent->checkFlag(FLAG_UPDATE_TRANSFORM)) {
        mParent->updateTransform();
    }

    if ((mInheritFlags & 0x1FF) == (FLAG_INHERIT_SCALE | FLAG_INHERIT_ROTATION | FLAG_INHERIT_TRANSLATION)) {
        MTXConcat(mParent->mTransform, mTransform, mTransform);
    } else {
        GSnull *root = mParent->mRoot;

        if ((mInheritFlags & FLAG_INHERIT_SCALE)) {
            if (!(mInheritState & STATE_SCALE_CACHED)) {
                if ((mInheritFlags & FLAG_INHERIT_ROOT_SCALE)) {
                    mParentScale = getMtxScale(root->mTransform);
                } else {
                    mParentScale = getMtxScale(mParent->mTransform);
                }

                if ((mInheritFlags & FLAG_CACHE_INHERITED_SCALE)) {
                    mInheritState |= STATE_SCALE_CACHED;
                }
            }
            applyParentScale();
        }

        if ((mInheritFlags & FLAG_INHERIT_ROTATION)) {
            if (!(mInheritState & STATE_ROTATION_CACHED)) {
                if ((mInheritFlags & FLAG_INHERIT_ROOT_ROTATION)) {
                    mParentRotation = getMtxRot(root->mTransform);
                } else {
                    mParentRotation = getMtxRot(mParent->mTransform);
                }

                if ((mInheritFlags & FLAG_CACHE_INHERITED_ROTATION)) {
                    mInheritState |= STATE_ROTATION_CACHED;
                }
            }
            applyParentRotation();
        }

        if ((mInheritFlags & FLAG_INHERIT_TRANSLATION)) {
            if (!(mInheritState & STATE_TRANSLATION_CACHED)) {
                if ((mInheritFlags & FLAG_INHERIT_ROOT_TRANSLATION)) {
                    mParentTranslation = getMtxTrans(root->mTransform);
                } else {
                    mParentTranslation = getMtxTrans(mParent->mTransform);
                }

                if ((mInheritFlags & FLAG_CACHE_INHERITED_TRANSLATION)) {
                    mInheritState |= STATE_TRANSLATION_CACHED;
                }
            }
            applyParentTranslation();
        }
    }

    if ((mInheritFlags &
         (FLAG_CACHE_INHERITED_ROTATION | FLAG_CACHE_INHERITED_SCALE | FLAG_CACHE_INHERITED_TRANSLATION))) {
        mParent->unattachChild(this);
    }
}

void GSnull::applyBlending(f32 blendFactor) {
    if (mRotationCache) {
        mRotationCache->mBase = mRotationCache->mBlend = getMtxRot(mTransform);
    }

    if (!(mFlags & (FLAG_UPDATE_BLEND_TRANSLATION | FLAG_UPDATE_BLEND_ROTATION | FLAG_UPDATE_BLEND_SCALE)) ||
        !mBlendPlayer) {
        return;
    }

    if ((mFlags & FLAG_UPDATE_BLEND_TRANSLATION)) {
        blendTranslation(&mLocalTranslation, &mBlendTranslation, &mLocalTranslation, blendFactor);
        mFlags &= ~FLAG_UPDATE_BLEND_TRANSLATION;
    }

    if ((mFlags & FLAG_UPDATE_BLEND_ROTATION)) {
        if ((mFlags & FLAG_UPDATE_BLEND_ROTATION_QUAT)) {
            GSmath::eulerToQuat(&mBlendRotationQuat, &mBlendRotationEuler);
            mFlags &= ~FLAG_UPDATE_BLEND_ROTATION_QUAT;
        }

        if (mRotationCache && (mFlags & FLAG_BLEND_ROTATION_MODEL_SPACE)) {
            if ((mFlags & FLAG_UPDATE_LOCAL_ROTATION_QUAT)) {
                GSmath::eulerToQuat(&mLocalRotationQuat, &mLocalRotationEuler);
                mFlags &= ~FLAG_UPDATE_LOCAL_ROTATION_QUAT;
            }

            mRotationCache->mBase = mLocalRotationQuat;
            mRotationCache->mBlend = mBlendRotationQuat;

            if (mParent && unkBool() && mParent->mRoot == mRoot && mParent->mRotationCache) {
                GSquat _unk1 = getMtxRot(mParent->mTransform);
                QUATInverse(&_unk1, &_unk1);

                // Project rotations into model space
                QUATMultiply(&mRotationCache->mBase, &mParent->mRotationCache->mBase, &mRotationCache->mBase);
                QUATMultiply(&mRotationCache->mBlend, &mParent->mRotationCache->mBlend, &mRotationCache->mBlend);

                blendRotationLocal(&mRotationCache->mBase, &mRotationCache->mBlend, &mLocalRotationQuat, blendFactor);

                // Project back into local space
                QUATMultiply(&mLocalRotationQuat, &_unk1, &mLocalRotationQuat);
            } else {
                blendRotationLocal(&mRotationCache->mBase, &mRotationCache->mBlend, &mLocalRotationQuat, blendFactor);
            }
        } else { // Local space
            if ((mFlags & FLAG_UPDATE_LOCAL_ROTATION_QUAT)) {
                GSmath::eulerToQuat(&mLocalRotationQuat, &mLocalRotationEuler);
                mFlags &= ~FLAG_UPDATE_LOCAL_ROTATION_QUAT;
            }
            blendRotationLocal(&mLocalRotationQuat, &mBlendRotationQuat, &mLocalRotationQuat, blendFactor);
        }
        mFlags &= ~FLAG_UPDATE_BLEND_ROTATION;
    }

    if ((mFlags & FLAG_UPDATE_BLEND_SCALE)) {
        if ((mFlags & FLAG_BLEND_SCALE_LINEAR)) {
            blendScaleLinear(&mLocalScale, &mBlendScale, &mLocalScale, blendFactor);
        } else {
            blendScaleGeometric(&mLocalScale, &mBlendScale, &mLocalScale, blendFactor);
        }
        mFlags &= ~FLAG_UPDATE_BLEND_SCALE;
    }
}

void GSnull::updateTransform() {
    if (!checkFlag(FLAG_UPDATE_TRANSFORM)) {
        return;
    }

    applyBlending(mBlendFactor);

    if (mTransformPivots) {
        // TODO(samm) Only this being inlined feels weird
        // Move to scale pivot
        initTranslation(
            mTransformPivots->mScalePivot.x, mTransformPivots->mScalePivot.y, mTransformPivots->mScalePivot.z
        );

        MTXScaleApply(mTransform, mTransform, mLocalScale.x, mLocalScale.y, mLocalScale.z);

        // Move from scale pivot to rotation pivot
        MTXTransApply(
            mTransform, mTransform, mTransformPivots->mScaleToRot.x, mTransformPivots->mScaleToRot.y,
            mTransformPivots->mScaleToRot.z
        );

        if ((mFlags & FLAG_UPDATE_LOCAL_ROTATION_QUAT)) {
            GSmath::eulerToQuat(&mLocalRotationQuat, &mLocalRotationEuler);
            mFlags &= ~FLAG_UPDATE_LOCAL_ROTATION_QUAT;
        }
        Mtx mtx;
        MTXQuat(mtx, &mLocalRotationQuat);
        MTXConcat(mtx, mTransform, mTransform);

        // Move from rotation pivot to translation pivot
        MTXTransApply(
            mTransform, mTransform, mTransformPivots->mRotToTrans.x, mTransformPivots->mRotToTrans.y,
            mTransformPivots->mRotToTrans.z
        );
    } else {
        MTXScale(mTransform, mLocalScale.x, mLocalScale.y, mLocalScale.z);

        if ((mFlags & FLAG_UPDATE_LOCAL_ROTATION_QUAT)) {
            GSmath::eulerToQuat(&mLocalRotationQuat, &mLocalRotationEuler);
            mFlags &= ~FLAG_UPDATE_LOCAL_ROTATION_QUAT;
        }
        Mtx mtx;
        MTXQuat(mtx, &mLocalRotationQuat);
        MTXConcat(mtx, mTransform, mTransform);
    }
    MTXTransApply(mTransform, mTransform, mLocalTranslation.x, mLocalTranslation.y, mLocalTranslation.z);

    applyParentTransform();

    mFlags &= ~FLAG_UPDATE_TRANSFORM;
}

void GSnull::updateChildren(f32 deltaTime) {
    GSnull *child, *next;

    child = mFirstChild;
    while (child) {
        next = child->mNext;
        child->update(deltaTime);
        child = next;
    }
}

void GSnull::update(f32 deltaTime) {
    if (fn_801F3C7C()) {
        deltaTime = 0.f;
    }

    GSblendObject::update(deltaTime);

    if (checkFlag(FLAG_UPDATE_TRANSFORM)) {
        updateTransform();
    }

    updateChildren(deltaTime);
}

void GSnull::initTransform(bool recursive) {
    if (!mNodeData) {
        return;
    }

    mFlags = FLAG_UPDATE_TRANSFORM;

    if ((mNodeData->mFlags & (1 << 4))) {
        mFlags |= (1 << 1);
    } else {
        // TODO(samm) This duplication is weird
        mFlags = FLAG_UPDATE_TRANSFORM;
    }

    if (mNodeData->mScale) {
        mLocalScale = *mNodeData->mScale;
        // TODO(samm) Revisit this
        ensure_nonzero_inplace(&mLocalScale.x);
        ensure_nonzero_inplace(&mLocalScale.y);
        ensure_nonzero_inplace(&mLocalScale.z);
        mBlendScale = mLocalScale;
    } else {
        mLocalScale.set(1.f, 1.f, 1.f);
        mBlendScale.set(1.f, 1.f, 1.f);
    }

    if (mNodeData->mRotation) {
        mLocalRotationEuler = *mNodeData->mRotation;
        GSmath::eulerToQuat(&mLocalRotationQuat, &mLocalRotationEuler);
        mBlendRotationEuler = mLocalRotationEuler;
        mBlendRotationQuat = mLocalRotationQuat;
    } else {
        mLocalRotationQuat.set(0.f, 0.f, 0.f, 1.f);
        mLocalRotationEuler.set(0.f, 0.f, 0.f);
        mBlendRotationQuat.set(0.f, 0.f, 0.f, 1.f);
        mBlendRotationEuler.set(0.f, 0.f, 0.f);
    }

    if (mNodeData->mTranslation) {
        mLocalTranslation = *mNodeData->mTranslation;
        mBlendTranslation = mLocalTranslation;
    } else {
        mLocalTranslation.set(0.f, 0.f, 0.f);
        mBlendTranslation.set(0.f, 0.f, 0.f);
    }

    if (recursive) {
        GSnull *child = mFirstChild;
        while (child) {
            child->initTransform(true);
            child = child->mNext;
        }
    }
}

bool GSnull::fn_801F3C7C() {
    if (mParentObject && mParentObject->checkFlag((1 << 4))) {
        return true;
    }

    GSnull *parent = this;
    while (parent) {
        if ((parent->mFlags & (1 << 9))) {
            return true;
        }
        if ((parent->mInheritFlags & (1 << 9))) {
            return false;
        }
        parent = parent->mParent;
    }

    return false;
}

bool GSnull::fn_801F3CE0() {
    if (mParentObject && !mParentObject->checkFlag((1 << 0))) {
        return false;
    }

    GSnull *parent = this;
    while (parent) {
        if (!(parent->mFlags & (1 << 1))) {
            return false;
        }
        if ((parent->mInheritFlags & (1 << 10))) {
            return true;
        }
        parent = parent->mParent;
    }

    return true;
}

void GSnull::fn_801F3D44(GSnull *node, GSnodeAnimChannel *channel, f32 cursor, bool blend) {
    switch (channel->mChannel) {
        case CHANNEL_TRANSLATION:
            if (blend) {
                fn_801E1278(channel, &node->mBlendTranslation);
                node->mFlags |= FLAG_UPDATE_BLEND_TRANSLATION;
            } else {
                fn_801E1278(channel, &node->mLocalTranslation);
                node->mBlendTranslation = node->mLocalTranslation;
            }
            node->markNeedsUpdate(true);
            break;
        case CHANNEL_ROTATION:
            if (channel->mDataType == 2) {
                if (blend) {
                    fn_801E1360(channel, &node->mBlendRotationQuat);
                    node->mFlags |= FLAG_UPDATE_BLEND_ROTATION;
                    node->mFlags &= ~FLAG_UPDATE_BLEND_ROTATION_QUAT;
                } else {
                    fn_801E1360(channel, &node->mLocalRotationQuat);
                    node->mFlags &= ~(FLAG_UPDATE_BLEND_ROTATION_QUAT | FLAG_UPDATE_LOCAL_ROTATION_QUAT);
                    node->mBlendRotationQuat = node->mLocalRotationQuat;
                }
            } else {
                if (blend) {
                    fn_801E1278(channel, &node->mBlendRotationEuler);
                    node->mFlags |= FLAG_UPDATE_BLEND_ROTATION_QUAT | FLAG_UPDATE_BLEND_ROTATION;
                } else {
                    fn_801E1278(channel, &node->mLocalRotationEuler);
                    node->mFlags |= FLAG_UPDATE_BLEND_ROTATION_QUAT | FLAG_UPDATE_LOCAL_ROTATION_QUAT;
                    node->mBlendRotationEuler = node->mLocalRotationEuler;
                }
            }
            node->markNeedsUpdate(true);
            break;
        case CHANNEL_SCALE:
            if (blend) {
                fn_801E1278(channel, &node->mBlendScale);
                ensure_nonzero_inplace(&node->mBlendScale.x);
                ensure_nonzero_inplace(&node->mBlendScale.y);
                ensure_nonzero_inplace(&node->mBlendScale.z);
                node->mFlags |= FLAG_UPDATE_BLEND_SCALE;
            } else {
                fn_801E1278(channel, &node->mLocalScale);
                ensure_nonzero_inplace(&node->mLocalScale.x);
                ensure_nonzero_inplace(&node->mLocalScale.y);
                ensure_nonzero_inplace(&node->mLocalScale.z);
                node->mBlendScale = node->mLocalScale;
            }
            node->markNeedsUpdate(true);
            break;
        case 3: {
            // TODO(samm) ???
            u8 _unk1;
            fn_801E1504(channel, &_unk1);
            _unk1 |= blend && node->checkFlag((1 << 1));
            if (_unk1) {
                node->mFlags |= (1 << 1);
            } else {
                node->mFlags &= ~(1 << 1);
            }
        } break;
    }
}
