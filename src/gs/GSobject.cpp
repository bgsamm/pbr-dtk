#include "gs/GSobject.hpp"

#include ".unsorted/80205954.hpp"
#include "gs/GShierarchyModule.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSmenuModule.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSscene.hpp"
#include "gs/scene/GSanimationPlayer.hpp"
#include "gs/scene/GScamera.hpp"
#include "gs/scene/GSjointNode.hpp"
#include "gs/scene/GSlight.hpp"
#include "gs/scene/GSmesh.hpp"
#include "gs/scene/GSmodel.hpp"
#include "gs/scene/GSnull.hpp"
#include "gs/scene/GSparticle.hpp"
#include "gs/scene/GSvolumeNode.hpp"

#include <cstring>

#include "common.hpp"

#define _UNK_MAX 1e38f
#define _UNK_MIN -1e38f

// TODO(samm) Proper includes
extern GSmatrix lbl_804932B0;
extern GSvec3 lbl_8049362C;

bool GSobject::fn_801F40E0(GSnull *rootNode) {
    GSnull *node = rootNode;
    while (node) {
        mNodes[node->getIndex()] = node;

        switch (node->getNodeType()) {
            case GS_NODE_CAMERA: mCameraCount++; break;
            case GS_NODE_JOINT:  mJointCount++; break;
            case GS_NODE_LIGHT:  mLightCount++; break;
            case GS_NODE_MODEL:  {
                GSmodel *model = static_cast<GSmodel *>(node);
                u16 meshCount = model->countMeshes();
                for (u16 i = 0; i < meshCount; i++) {
                    if (model->getMesh(i)) {
                        mMeshCount++;
                    }
                }
                if (model->checkDataFlag((1 << 9))) {
                    mFlags |= (1 << 1);
                }
                if (model->checkDataFlag((1 << 10))) {
                    mFlags |= (1 << 2);
                }
                if (model->checkDataFlag((1 << 11))) {
                    mFlags |= (1 << 3);
                }
                mModelCount++;
            } break;
            case GS_NODE_PARTICLE: mParticleCount++; break;
            case GS_NODE_VOLUME:   mVolumeCount++; break;
        }

        node = node->nextInObject();
    }

    u32 lookupSize = mMeshCount * sizeof(*mMeshLookup);
    lookupSize += mCameraCount * sizeof(*mCameraLookup);
    lookupSize += mJointCount * sizeof(*mJointLookup);
    lookupSize += mLightCount * sizeof(*mLightLookup);
    lookupSize += mModelCount * sizeof(*mModelLookup);
    lookupSize += mParticleCount * sizeof(*mParticleLookup);
    lookupSize += mVolumeCount * sizeof(*mVolumeLookup);
    lookupSize = ROUNDUP(lookupSize, 16);
    if ((mFlags & (1 << 3))) {
        lookupSize += sizeof(*_2c);
    }

    void *lookupBuf = GSmem::allocFromHeapAligned(gGameHeap, lookupSize, 0x20);
    if (!lookupBuf) {
        return false;
    }

    mLookupBuffer = lookupBuf;
    if (mMeshCount) {
        mMeshLookup = (GSmesh **)lookupBuf;
        lookupBuf = mMeshLookup + mMeshCount;
    }
    if (mCameraCount) {
        mCameraLookup = (u16 *)lookupBuf;
        lookupBuf = mCameraLookup + mCameraCount;
    }
    if (mJointCount) {
        mJointLookup = (u16 *)lookupBuf;
        lookupBuf = mJointLookup + mJointCount;
    }
    if (mLightCount) {
        mLightLookup = (u16 *)lookupBuf;
        lookupBuf = mLightLookup + mLightCount;
    }
    if (mModelCount) {
        mModelLookup = (u16 *)lookupBuf;
        lookupBuf = mModelLookup + mModelCount;
    }
    if (mParticleCount) {
        mParticleLookup = (u16 *)lookupBuf;
        lookupBuf = mParticleLookup + mParticleCount;
    }
    if (mVolumeCount) {
        mVolumeLookup = (u16 *)lookupBuf;
        lookupBuf = mVolumeLookup + mVolumeCount;
    }

    if ((mFlags & (1 << 3))) {
        // TODO(samm) #define the 8
        _2c = (_UnkObjectStruct_2(*)[8])PTR_ROUNDUP(lookupBuf, 16);
        for (u8 i = 0; i < 8; i++) {
            (*_2c)[i]._0 = 0;
            (*_2c)[i]._3f = i;
        }
    }

    u16 cameraIdx = 0;
    u16 jointIdx = 0;
    u16 lightIdx = 0;
    u16 modelIdx = 0;
    u16 particleIdx = 0;
    u16 volumeIdx = 0;
    u16 meshIdx = 0;
    for (u16 i = 0; i < mNodeCount; i++) {
        GSnull *node = mNodes[i];
        if (!node) {
            continue;
        }

        switch (node->getNodeType()) {
            case GS_NODE_CAMERA: mCameraLookup[cameraIdx++] = i; break;
            case GS_NODE_JOINT:  mJointLookup[jointIdx++] = i; break;
            case GS_NODE_LIGHT:  mLightLookup[lightIdx++] = i; break;
            case GS_NODE_MODEL:  {
                GSmodel *model = static_cast<GSmodel *>(node);
                u16 meshCount = model->countMeshes();
                for (u16 j = 0; j < meshCount; j++) {
                    GSmesh *mesh = model->getMesh(j);
                    if (mesh) {
                        mMeshLookup[meshIdx++] = mesh;
                    }
                }
                mModelLookup[modelIdx++] = i;
                registerModel(model);
            } break;
            case GS_NODE_PARTICLE: mParticleLookup[particleIdx++] = i; break;
            case GS_NODE_VOLUME:   mVolumeLookup[volumeIdx++] = i; break;
        }
    }

    return true;
}

GSobject::GSobject(GSscene *parentScene, GSobjectData *data)
    : mParentScene(parentScene),
      mData(data),
      mNodes(NULL),
      mLookupBuffer(NULL),
      mCameraLookup(NULL),
      mJointLookup(NULL),
      mLightLookup(NULL),
      mMeshLookup(NULL),
      mModelLookup(NULL),
      mParticleLookup(NULL),
      mVolumeLookup(NULL),
      _2c(NULL),
      _30(),
      _38(),
      _40(0),
      // TODO(samm) Identify this default flag
      mFlags((1 << 0)),
      mNodeCount(0),
      mCameraCount(0),
      mJointCount(0),
      mLightCount(0),
      mMeshCount(0),
      mModelCount(0),
      mParticleCount(0),
      mVolumeCount(0),
      _ee(0),
      mAnimBlendFactor(0.f),
      mTransitionLength(1.f),
      // TODO(samm) Possibly defaults rather than args
      mBoundingBox(_UNK_MAX, _UNK_MAX, _UNK_MAX, _UNK_MIN, _UNK_MIN, _UNK_MIN),
      mCenter(0.f, 0.f, 0.f),
      _148(0x80),
      _149(0x80),
      _14a(0x80),
      _14b(0xff),
      _14c(0),
      _150(0) {
    _44 = NULL;
    _48 = NULL;

    MTXIdentity(mPositionMtx);
    MTXIdentity(mRotationMtx);
    MTXScale(mScaleMtx, lbl_8049362C.x, lbl_8049362C.y, lbl_8049362C.z);

    mBaseAnimId = GS_ANIM_NULL;
    mBaseAnimType = GS_ANIM_TYPE_ONESHOT;
    mBaseAnimTime = 0.f;
    mBaseAnimLength = 0.f;
    mBaseAnimSpeed = 1.f;
    mBlendAnimId = GS_ANIM_NULL;
    mBlendAnimType = GS_ANIM_TYPE_ONESHOT;
    mBlendAnimTime = 0.f;
    mBlendAnimLength = 0.f;
    mBlendAnimSpeed = 1.f;
    _14c_0 = 0;
    _14c_1 = 0;

    GSrender::getInstance()->getRenderDimensions(&_150_0, &_150_1);

    if (mParentScene && mParentScene->getUnkSceneData()) {
        // TODO(samm) #define flag
        mFlags |= (1 << 7);
    }

    mNodeCount = data->mNodeCount;
    if (!mNodeCount) {
        return;
    }
    if (!data->mRootNode) {
        return;
    }

    /* NOTE(samm)
     * It appears the sizeof usage here is a bug. It allocates space for entire nodes (size 0x104)
     * instead of just pointers, leading to an allocation 65 times larger than is actually needed.
     * From testing, the game runs without issue if the multiplier is changed from 0x104 to 0x4.
     */
    mNodes = (GSnull **)GSmem::allocFromHeap(gGameHeap, mNodeCount * sizeof(**mNodes));
    if (!mNodes) {
        return;
    }

    memset(mNodes, 0, mNodeCount * sizeof(*mNodes));

    GSnull *rootNode;
    switch (data->mRootNode->mNodeType) {
        case GS_NODE_MODEL:    rootNode = new GSmodel(this, data->mRootNode); break;
        case GS_NODE_CAMERA:   rootNode = new GScamera(this, data->mRootNode); break;
        case GS_NODE_JOINT:    rootNode = new GSjointNode(this, data->mRootNode); break;
        case GS_NODE_LIGHT:    rootNode = new GSlight(this, data->mRootNode); break;
        case GS_NODE_VOLUME:   rootNode = new GSvolumeNode(this, data->mRootNode); break;
        case GS_NODE_PARTICLE: rootNode = new GSparticle(this, data->mRootNode); break;
        case GS_NODE_NULL:
        default:               rootNode = new GSnull(this, data->mRootNode); break;
    }

    if (!rootNode) {
        return;
    }

    mBoundingBox.mTransform = rootNode->getTransform();
    fn_801F40E0(rootNode);
    init();

    // TODO(samm) #define flags/pull out to inline
    if (mFlags & (1 << 1)) {
        fn_801F4C98((mFlags >> 2) & 0x1);
    }

    GShierarchyModule::fn_80200594(this);
    GShierarchyModule::getInstance()->registerObject(this);

    startAnimation(0, GS_ANIM_TYPE_CYCLE, 0.f, 1.f, false, false, false);
}

GSobject::~GSobject() {
    // TODO(samm) Registers allocate incorrectly w/ getInstance()
    GShierarchyModule::sInstance->unregisterObject(this);
    GShierarchyModule::fn_80200858(this);
    GSmenuModule::fn_80203950(this);

    if (_44) {
        fn_8023E2D0(_44);
    }
    if (_48) {
        fn_8023E2D0(_48);
    }

    if (mLookupBuffer) {
        GSmem::freeToHeap(gGameHeap, mLookupBuffer);
        mLookupBuffer = NULL;
    }

    if (mNodes[0]) {
        delete mNodes[0];
        mNodes[0] = NULL;
    }

    if (mNodes) {
        GSmem::freeToHeap(gGameHeap, mNodes);
        mNodes = NULL;
    }

    freeList1(&_38);
    freeList2(&_30);
}

void GSobject::startAnimation(u16 animId, u32 animType, f32 startTime, f32 speed, bool arg2, bool arg3, bool arg4) {
    GSanimationData *animData;
    if (!mData) {
        animData = NULL;
    } else if (animId >= mData->mAnimCount) {
        animData = NULL;
    } else {
        animData = &mData->mAnimList[animId];
    }

    if (!animData) {
        return;
    }

    if (animData->_29) {
        u16 _unk1 = animData->_18;
        u16 *_unk2 = animData->_10;

        if (!_unk1 || !_unk2) {
            for (u16 i = 0; i < mNodeCount; i++) {
                GSnull *node = mNodes[i];
                if (!node) {
                    continue;
                }

                node->startAnimation(animId, animType, startTime, speed);
                if (arg2) {
                    node->lockAnimation();
                }
            }

            mBaseAnimId = animId;
            mBaseAnimType = animType;
            mBaseAnimTime = startTime;
            mBaseAnimLength = animData->mLength;
            mBaseAnimSpeed = speed;
            mBlendAnimId = GS_ANIM_NULL;
            mAnimBlendFactor = 0.f;
            mTransitionLength = 1.f;
        } else {
            bool _unk3 = animData->_2b;

            for (u16 i = 0; i < _unk1; i++) {
                GSnull *node = mNodes[_unk2[i]];
                if (!node) {
                    continue;
                }

                node->startAnimation(animId, animType, startTime, speed);
                if (arg2) {
                    node->lockAnimation();
                }

                if (_unk3) {
                    GSmodel *model = (node->getNodeType() == GS_NODE_MODEL) ? static_cast<GSmodel *>(node) : NULL;
                    if (model) {
                        u16 meshCount = model->countMeshes();
                        for (u16 meshIdx = 0; meshIdx < meshCount; meshIdx++) {
                            GSmesh *mesh = model->getMesh(meshIdx);
                            if (!mesh) {
                                continue;
                            }

                            // TODO(samm) Revisit this
                            GSmaterial *material = mesh->_14;
                            if (!material) {
                                continue;
                            }

                            material->startAnimation(animId, animType, startTime, speed);
                            if (arg3) {
                                material->lockAnimation();
                            }
                        }
                    }
                }
            }
        }
    }

    if (animData->_2a) {
        u16 _unk1 = animData->_1a;
        u16 *_unk2 = animData->_14;

        if (!_unk1 || !_unk2) {
            for (u16 i = 0; i < mMeshCount; i++) {
                GSmesh *mesh = mMeshLookup[i];

                // TODO(samm) Revisit this
                GSmaterial *material = mesh->_14;
                if (!material) {
                    continue;
                }

                material->startAnimation(animId, animType, startTime, speed);
                if (arg3) {
                    material->lockAnimation();
                }
            }
        } else {
            for (u16 i = 0; i < _unk1; i++) {
                GSmesh *mesh = mMeshLookup[_unk2[i]];

                // TODO(samm) Revisit this
                GSmaterial *material = mesh->_14;
                if (!material) {
                    continue;
                }

                material->startAnimation(animId, animType, startTime, speed);
                if (arg3) {
                    material->lockAnimation();
                }
            }
        }
    }

    if (!arg4) {
        _UnkAnimData_1 *_unk4 = animData->_1c;
        if (_unk4) {
            u16 _unk5 = animData->_24;
            for (u16 i = 0; i < _unk5; i++, _unk4++) {
                GSnull *node = mNodes[_unk4->_4];
                if (!node) {
                    continue;
                }

                GSparticle *particle =
                    (node->getNodeType() == GS_NODE_PARTICLE) ? static_cast<GSparticle *>(node) : NULL;
                if (!particle) {
                    continue;
                }

                if (fn_80207864(particle->_138) && particle->_unkCondition1()) {
                    particle->_104 &= ~((1 << 1) | (1 << 2));
                } else {
                    f32 _unk6 = _unk4->_0;
                    particle->_104 |= (1 << 0);
                    particle->_104 &= ~((1 << 1) | (1 << 2));
                    particle->_108 = _unk6;
                }
            }
        }

        _UnkAnimData_1 *_unk7 = animData->_20;
        if (_unk7) {
            u16 _unk5 = animData->_26;
            for (u16 i = 0; i < _unk5; i++, _unk7++) {
                GSnull *node = mNodes[_unk7->_4];
                if (!node) {
                    continue;
                }

                // TODO(samm) Revisit the s8 cast
                GSparticle *particle =
                    ((s8)node->getNodeType() == GS_NODE_PARTICLE) ? reinterpret_cast<GSparticle *>(node) : NULL;
                if (!particle) {
                    continue;
                }

                if (particle->_unkCondition1() && fn_80207864(particle->_138)) {
                    f32 _unk8 = _unk7->_0;
                    particle->_104 |= (1 << 1);
                    particle->_104 &= ~(1 << 2);
                    particle->_10c = _unk8;
                } else {
                    f32 _unk9 = _unk7->_0;
                    particle->_104 |= (1 << 2);
                    particle->_110 = _unk9;
                }
            }
        }
    }
}

void GSobject::clearAnimation() {
    for (u16 i = 0; i < mNodeCount; i++) {
        if (mNodes[i]) {
            mNodes[i]->clearAnimation();
        }
    }

    for (u16 i = 0; i < mMeshCount; i++) {
        mMeshLookup[i]->clearAnimation();
    }

    mBaseAnimId = GS_ANIM_NULL;
    mBlendAnimId = GS_ANIM_NULL;
    mAnimBlendFactor = 0.f;
    mTransitionLength = 1.f;
}

void GSobject::stepAnimTransition(f32 deltaTime) {
    if (mBaseAnimId != GS_ANIM_NULL) {
        mBaseAnimTime += deltaTime;
    }

    if (mBlendAnimId == GS_ANIM_NULL) {
        return;
    }

    mBlendAnimTime += deltaTime;

    if ((mFlags & (1 << 5))) {
        if (mBlendAnimTime < mTransitionLength - EPSILON) {
            mAnimBlendFactor = mBlendAnimTime / mTransitionLength;
        } else {
            mAnimBlendFactor = 1.f;
            if ((mFlags & (1 << 6))) {
                startAnimation(mBlendAnimId, mBlendAnimType, mBlendAnimTime, mBlendAnimSpeed, false, false, true);
            }
            return;
        }
    }

    for (u16 i = 0; i < mNodeCount; i++) {
        if (mNodes[i]) {
            mNodes[i]->setBlendFactor(mAnimBlendFactor);
        }
    }
}

void GSobject::fn_801F6390() {
    for (s32 i = 0; i < mMeshCount; i++) {
        mMeshLookup[i]->_14 = mMeshLookup[i]->_c;
    }
}

inline void GSobject::calcBoundingBox() {
    // TODO(samm) This reversing of components seems wrong but inlines didn't work
    mBoundingBox.mMin.z = _UNK_MAX;
    mBoundingBox.mMin.y = _UNK_MAX;
    mBoundingBox.mMin.x = _UNK_MAX;
    mBoundingBox.mMax.z = _UNK_MIN;
    mBoundingBox.mMax.y = _UNK_MIN;
    mBoundingBox.mMax.x = _UNK_MIN;

    GSmodel *model;
    for (u16 i = 0; i < mModelCount; i++) {
        model = getModel(i);
        if (model && model->fn_801F3CE0()) {
            GSmath::expandBoundingBox(&mBoundingBox, model->getBoundingBox());
        }
    }

    if ((mBoundingBox.mMin.x > 0.f && mBoundingBox.mMax.x < 0.f) ||
        (mBoundingBox.mMin.y > 0.f && mBoundingBox.mMax.y < 0.f) ||
        (mBoundingBox.mMin.z > 0.f && mBoundingBox.mMax.z < 0.f)) {
        mBoundingBox.mMin.set(-EPSILON, -EPSILON, -EPSILON);
        mBoundingBox.mMax.set(EPSILON, EPSILON, EPSILON);
    }
}

void GSobject::init() {
    clearAnimation();
    fn_801F6390();

    GSnull *rootNode = getRootNode();
    if (rootNode) {
        rootNode->initTransform(true);
    }

    if (mData->mBoundingBox) {
        GSvec3 center;
        mBoundingBox.mMin = mData->mBoundingBox->mMin;
        mBoundingBox.mMax = mData->mBoundingBox->mMax;
        GSmath::calcBoundingBoxCenter(&center, &mBoundingBox);
        mCenter = center;
    } else {
        calcBoundingBox();
    }
}

void GSobject::update(f32 deltaTime, bool updateNodes) {
    if ((mFlags & (1 << 4))) {
        deltaTime = 0.f;
    }

    stepAnimTransition(deltaTime);

    if (updateNodes) {
        GSnull *rootNode = getRootNode();
        if (rootNode) {
            rootNode->update(deltaTime);
        }
    }

    if (!mData->mBoundingBox) {
        calcBoundingBox();
    }

    GSvec3 center;
    GSmath::calcBoundingBoxCenter(&center, &mBoundingBox);
    mCenter = center;

    const GSmatrix *_unk1;
    if (mNodes && mNodes[0]) {
        _unk1 = mNodes[0]->getTransform();
    } else {
        _unk1 = &lbl_804932B0;
    }

    GSmatrix _unk2;
    MTXInverse(*_unk1, _unk2);

    if (_2c && _ee) {
        _UnkObjectStruct_2 *_unk3 = *_2c;
        for (u32 i = 0; i < 8; i++, _unk3++) {
            if (!_unk3->_0) {
                continue;
            }
            if (!_unk3->fn_801F8368(&_unk2, deltaTime)) {
                _ee--;
            }
        }
    }
}

// TODO(samm) Clean all this up

inline Vec2 scaleHalf(const Vec2 *a) {
    Vec2 result;
    result.x = a->x * 0.5f;
    result.y = a->y * 0.5f;
    return result;
}

bool _UnkObjectStruct_2::fn_801F8368(const GSmatrix *arg0, f32 deltaTime) {
    if (_3e) {
        _34 -= deltaTime;
        if (_34 < EPSILON) {
            _0 = 0;
            return false;
        }
    }

    Vec2 _unk1;
    _unk1 = scaleHalf(&_2c);

    _UnkObjectStruct_3 *_unk3 = _4;
    if (_unk3) {
        _8 = _unk3->_unkVec3_2();
        MTXMultVec(*arg0, &_8, &_8);
        _14 = _unk3->_unkVec3_1();
        MTXMultVecSR(*arg0, &_14, &_14);
    }

    GSvec3 _unk4;
    _unk4 = _14.cross(&GSmath::sYAxis);

    f32 x = _unk4.x;
    f32 y = _unk4.y;
    f32 z = _unk4.z;

    bool _unk5;
    if (!(x < EPSILON && x > -EPSILON && y < EPSILON && y > -EPSILON && z < EPSILON && z > -EPSILON)) {
        _unk5 = false;
    } else {
        _unk5 = true;
    }

    if (_unk5) {
        _unk4 = _14.cross(&GSmath::sZAxis);
    }

    VECNormalize(&_unk4, &_unk4);

    GSvec3 camUp;
    camUp = _unk4.cross(&_14);

    if (!(_28 < EPSILON && _28 > -EPSILON)) {
        GSquat _unk7;
        QUATRotAxisRad(&_unk7, &_14, _28);
        GSmath::rotateVec3ByQuat(&camUp, &_unk7);
    }

    GSvec3 _unk8;
    _unk8 = _unk4 * _20;

    GSvec3 _unk9 = camUp * _24;
    VECAdd(&_unk8, &_unk9, &_unk8);

    GSvec3 target = _8 + _14 + _unk8;
    GSvec3 camPos = _8 + _unk8;

    MTXLookAt(_40, &camPos, &camUp, &target);
    Mtx _unk13;
    MTXLightOrtho(_unk13, -_unk1.y, _unk1.y, _unk1.x, -_unk1.x, 0.5f, 0.5f, 0.5f, 0.5f);

    Mtx _unk14;
    MTXConcat(_40, *arg0, _unk14);
    MTXCopy(_unk14, _40);
    MTXConcat(_unk13, _40, _40);

    return true;
}
