#include "gs/GSobject.hpp"

#include ".unsorted/80202E54.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSscene.hpp"
#include "gs/GSsceneManager.hpp"
#include "gs/scene/GScameraNode.hpp"
#include "gs/scene/GSjointNode.hpp"
#include "gs/scene/GSlightNode.hpp"
#include "gs/scene/GSmeshNode.hpp"
#include "gs/scene/GSnull.hpp"
#include "gs/scene/GSparticleNode.hpp"
#include "gs/scene/GSvolumeNode.hpp"

#include <cstring>

#define _UNK_MAX 1e38f
#define _UNK_MIN -1e38f

// TODO(samm) Name
extern Vec lbl_8049362C;

GSobject::GSobject(GSscene *parentScene, GSobjectData *data)
    : mParentScene(parentScene),
      mData(data),
      mNodes(NULL),
      mNodeLookup(NULL),
      mCameraLookup(NULL),
      mJointLookup(NULL),
      mLightLookup(NULL),
      mSubmeshLookup(NULL),
      mMeshLookup(NULL),
      mParticleLookup(NULL),
      mVolumeLookup(NULL),
      _2c(0),
      _30(),
      _38(),
      _40(0),
      // TODO(samm) Identify this default flag
      mFlags(1),
      mNodeCount(0),
      mCameraCount(0),
      mJointCount(0),
      mLightCount(0),
      mSubmeshCount(0),
      mMeshCount(0),
      mParticleCount(0),
      mVolumeCount(0),
      _ee(0),
      _118(0.f),
      _11c(1.f),
      _120(_UNK_MAX),
      _124(_UNK_MAX),
      _128(_UNK_MAX),
      _12c(_UNK_MIN),
      _130(_UNK_MIN),
      _134(_UNK_MIN),
      _138(NULL),
      _13c(0.f),
      _140(0.f),
      _144(0.f),
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

    _f0 = 0xffff;
    _f4 = 0;
    _f8 = 0.f;
    _fc = 0.f;
    _100 = 1.f;
    _104 = 0xffff;
    _108 = 0;
    _10c = 0.f;
    _110 = 0.f;
    _114 = 1.f;
    _14c_0 = 0;
    _14c_1 = 0;

    GSrenderManager::getInstance()->getRenderDimensions(&_150_0, &_150_1);

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

    // TODO(samm) Should this specifically be using _8[0].mNode?
    memset(mNodes, 0, mNodeCount * sizeof(*mNodes));

    GSnull *rootNode;
    switch (data->mRootNode->mNodeType) {
        case GS_NODE_MESH:     rootNode = new GSmeshNode(this, data->mRootNode); break;
        case GS_NODE_CAMERA:   rootNode = new GScameraNode(this, data->mRootNode); break;
        case GS_NODE_JOINT:    rootNode = new GSjointNode(this, data->mRootNode); break;
        case GS_NODE_LIGHT:    rootNode = new GSlightNode(this, data->mRootNode); break;
        case GS_NODE_VOLUME:   rootNode = new GSvolumeNode(this, data->mRootNode); break;
        case GS_NODE_PARTICLE: rootNode = new GSparticleNode(this, data->mRootNode); break;
        case GS_NODE_NULL:
        default:               rootNode = new GSnull(this, data->mRootNode); break;
    }

    if (!rootNode) {
        return;
    }

    _138 = rootNode->getTransform();
    fn_801F40E0(rootNode);
    fn_801F6618();

    // TODO(samm) #define flags
    if (mFlags & (1 << 1)) {
        fn_801F4C98((mFlags >> 2) & 0x1);
    }

    GSsceneManager::fn_80200594(this);
    GSsceneManager::getInstance()->registerObject(this);

    fn_801F4DF4(0, 1, 0, 0, 0, 0.f, 1.f);
}

GSobject::~GSobject() {
    // TODO(samm) Registers allocate incorrectly w/ getInstance()
    GSsceneManager::sInstance->unregisterObject(this);
    GSsceneManager::fn_80200858(this);
    fn_80203950(this);

    if (_44) {
        GSrender::fn_8023E2D0(_44);
    }
    if (_48) {
        GSrender::fn_8023E2D0(_48);
    }

    if (mNodeLookup) {
        GSmem::freeToHeap(gGameHeap, mNodeLookup);
        mNodeLookup = NULL;
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
