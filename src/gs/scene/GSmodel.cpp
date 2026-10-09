#include "gs/scene/GSmodel.hpp"

#include "gs/GShierarchyModule.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/render/80236704.hpp"
#include "gs/render/GSrenderPass.hpp"
#include "gs/scene/GSmesh.hpp"

#include "common.hpp"

// _UnkModelStruct_2 lbl_804919B0;

GSmaterialData lbl_804919B0;
GSmeshRenderSettings lbl_804919B0_8c(false);
GSmaterial lbl_804919B0_b8(&lbl_804919B0, &lbl_804919B0_8c);

GSmodel::GSmodel(GSobject *parentObject, GSmodelNodeData *data)
    : GSnull(parentObject, data),
      _104((1 << 0)),
      mCenter(0.f, 0.f, 0.f),
      _130(0.f),
      _134(0, 0, 0, 0),
      _138(0.f),
      _13c(0.f),
      _140(0.f),
      _144(0.f),
      _148(1.f),
      _14c(0.f),
      _150(1.f),
      _154(GSmath::sYAxis),
      _160(PI),
      mModelData(data->mModelData),
      _168(data->_34),
      _16c(data->mModelData),
      mFirstMesh() {
    mBoundingBox.mTransform = &mTransform;

    GSmeshData *meshData = mModelData->mFirstMesh;
    GSmesh *prev = NULL;
    while (meshData) {
        GSmesh *mesh = new GSmesh(this, meshData);
        if (!mesh) {
            break;
        }

        if (prev) {
            prev->mNext = mesh;
        } else {
            mFirstMesh = mesh;
        }

        prev = mesh;
        meshData = meshData->mNext;
    }

    PPCSync();
}

GSmodel::~GSmodel() {
    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        GSmesh *nextMesh = mesh->mNext;
        delete mesh;
        mesh = nextMesh;
    }
}

GSmesh *GSmodel::getMesh(u16 index) const {
    GSmesh *mesh = mFirstMesh;
    u16 i = 0;

    while (mesh) {
        if (i == index) {
            return mesh;
        }
        mesh = mesh->mNext;
        i++;
    }

    return NULL;
}

u16 GSmodel::countMeshes() const {
    GSmesh *mesh = mFirstMesh;
    u16 count = 0;
    while (mesh) {
        mesh = mesh->mNext;
        count++;
    }
    return count;
}

void GSmodel::update(f32 deltaTime) {
    if (fn_801F3C7C()) {
        deltaTime = 0.f;
    }

    bool _unk1 = (mFlags & (1 << 0));

    GSnull::update(deltaTime);

    if (_unk1) {
        if (_168) {
            GSmatrix _unk2;
            MTXConcat(mTransform, *_168, _unk2);
            MTXCopy(_unk2, mTransform);
        }

        GSnull *parent;
        bool _unk4 = false;
        GSnull *node = this;

        while (node) {
            if (node->mLocalScale.x < 0.f) {
                _unk4 ^= true;
            }
            if (node->mLocalScale.y < 0.f) {
                _unk4 ^= true;
            }
            if (node->mLocalScale.z < 0.f) {
                _unk4 ^= true;
            }

            parent = node->mParent;
            if (!node->mParent) {
                parent = NULL;
            } else if (!node->unkBool()) {
                parent = NULL;
            } else if ((node->mInheritFlags & (1 << 2))) {
                parent = node->mParent;
            } else {
                parent = parent->mRoot;
            }

            node = parent;
        }

        if (_unk4) {
            _104 |= (1 << 1);
        } else {
            _104 &= ~(1 << 1);
        }
    }

    if (mParentObject) {
        s32 baseAnimId = getAnimId();
        f32 baseAnimProg;
        if (baseAnimId != GS_ANIM_NULL) {
            baseAnimProg = getAnimProgress();
        } else {
            baseAnimId = mParentObject->getBaseAnimId();
            baseAnimProg = mParentObject->fn_801F5B44();
        }
        fn_801F15EC(baseAnimId, 0, baseAnimProg);

        bool _unk5;
        if (mBlendPlayer) {
            _unk5 = mBlendPlayer->isPlaying();
        } else {
            _unk5 = false;
        }

        if (_unk5 || mParentObject->fn_801F5EBC()) {
            s32 blendAnimId = getBlendAnimId();
            f32 blendAnimProg;
            if (blendAnimId != GS_ANIM_NULL) {
                blendAnimProg = getBlendAnimProgress();
            } else {
                blendAnimId = mParentObject->getBlendAnimId();
                blendAnimProg = mParentObject->fn_801F5C60();
            }

            if (blendAnimId != GS_ANIM_NULL) {
                fn_801F15EC(blendAnimId, 1, blendAnimProg);
            }
        }
    } else {
        fn_801F15EC(0, 0, 0.f);
    }

    GSvec3 center;
    GSmath::calcBoundingBoxCenter(&center, &mBoundingBox);
    mCenter = center;

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        mesh->update(deltaTime);
        mesh = mesh->mNext;
    }

    _104 |= (1 << 0);
}

void GSmodel::initTransform(bool recursive) {
    GSnull::initTransform(recursive);

    if ((mModelData->mFlags & (1 << 6))) {
        _104 |= (1 << 2);
    }

    if ((mModelData->mFlags & (1 << 7))) {
        _104 |= (1 << 3) | (1 << 2);
    }

    _16c.fn_801EFA6C();

    _UnkModelData_1 *_unk1 = mModelData->_1c;
    mBoundingBox.mMin = _unk1->mBoundingBoxMin;
    mBoundingBox.mMax = _unk1->mBoundingBoxMax;

    GSvec3 center;
    GSmath::calcBoundingBoxCenter(&center, &mBoundingBox);
    mCenter = center;

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        mesh->initTransform();
        mesh = mesh->mNext;
    }
}

bool GSmodel::fn_801F0B50(_UnkMaterialStruct_3 *arg0) {
    u32 _unk1;
    if (GSrenderPass::getActiveRenderPass()) {
        _unk1 = GSrenderPass::getActiveRenderPass()->get_0();
    } else {
        _unk1 = 0;
    }
    return fn_801F0B7C(arg0, _unk1 != 8);
}

bool GSmodel::fn_801F0B7C(_UnkMaterialStruct_3 *arg0, bool arg1) {
    if (!fn_801F3CE0()) {
        return false;
    }

    switch (GSmath::fn_80220B18(&mBoundingBox)) {
        case 2:  GSrender::sInstance->setClipMode(GX_CLIP_DISABLE); break;
        case 0:  return false;
        default: GSrender::sInstance->setClipMode(GX_CLIP_ENABLE); break;
    }

    if (!fn_801F06E4(arg0)) {
        return false;
    }

    bool inverted = (_104 & (1 << 1));

    GSrender::sInstance->get_16e8()->fn_80236878(&mTransform);

    GShierarchyModule::fn_802027FC(&mCenter);
    GShierarchyModule::applyLights();

    GSrender::sInstance->get_16e8()->_unkFunc_1();

    bool _unk4 = false;
    bool _unk5 = checkDataFlag((1 << 5));
    bool _unk6 = (checkUnkFlag((1 << 4)) && !arg1);

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        if ((mesh->mFlags & (1 << 0)) == (1 << 0)) {
            if (_unk6) {
                _UnkClass8023C09C *_unk7 = mesh->_18;
                if (_unk7) {
                    GSmaterial *_unk8 = mesh->mMaterial;
                    _16c.fn_801EFBE4(_unk7, true);

                    mesh->mMaterial = &lbl_804919B0_b8;
                    lbl_804919B0._60 = _134;
                    lbl_804919B0._64 = _134;

                    u8 alpha = _134.a;
                    lbl_804919B0_8c.mZUpdateEnable = (alpha == 255);

                    if (mesh->fn_801ED62C(arg0, &mTransform, inverted, 0)) {
                        _unk4 = true;
                    }

                    mesh->mMaterial = _unk8;

                    _16c.fn_801EFBE4(_unk7, false);
                }
            }

            bool _unk9 = false;
            if ((mesh->mFlags & (1 << 1)) == (1 << 1) || mesh->mMaterial->getAlpha() != 255) {
                _unk9 = true;
            }

            if (arg1 != _unk9) {
                if (mesh->fn_801ED62C(arg0, &mTransform, inverted, _unk5)) {
                    _unk4 = true;
                }
            }
        }
        mesh = mesh->mNext;
    }

    GSrender::sInstance->get_16e8()->_4--;

    if (_unk4) {
        if (_16c._1b) {
            _16c._14 = GSrender::sInstance->fn_8023B948(&_16c);
        }
        return true;
    }

    return false;
}

bool GSmodel::fn_801F0FD8(_UnkMaterialStruct_3 *arg0, bool arg1) {
    if (!fn_801F3CE0() || !checkDataFlag((1 << 9))) {
        return false;
    }

    if (!fn_801F06E4(arg0)) {
        return false;
    }

    bool _unk1 = !checkUnkFlag((1 << 1));

    GSrender::sInstance->setClipMode(GX_CLIP_DISABLE);

    GSrender::sInstance->get_16e8()->fn_80236878(&mTransform);

    bool _unk4 = false;

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        // TODO(samm) Inlining
        if ((mesh->mFlags & (1 << 0)) == (1 << 0)) {
            if (arg1 == !((mesh->mFlags & (1 << 1)) == (1 << 1))) {
                if (mesh->fn_801EDDFC(arg0, &mTransform, _unk1)) {
                    _unk4 = true;
                }
            }
        }
        mesh = mesh->mNext;
    }

    GSrender::sInstance->get_16e8()->_4--;

    if (_unk4) {
        if (_16c._1b) {
            _16c._14 = GSrender::sInstance->fn_8023B948(&_16c);
        }
        return true;
    }

    return false;
}

bool GSmodel::fn_801F113C(_UnkMaterialStruct_3 *arg0) {
    if (!fn_801F3CE0() || !checkDataFlag((1 << 10))) {
        return false;
    }

    // TODO(samm) Move to inline in GSrenderPass?
    u32 _unk1;
    if (GSrenderPass::getActiveRenderPass()) {
        _unk1 = GSrenderPass::getActiveRenderPass()->get_0();
    } else {
        _unk1 = 0;
    }

    bool _unk2 = (_unk1 != 8);

    switch (GSmath::fn_80220B18(&mBoundingBox)) {
        case 2:  GSrender::sInstance->setClipMode(GX_CLIP_DISABLE); break;
        case 0:  return false;
        default: GSrender::sInstance->setClipMode(GX_CLIP_ENABLE); break;
    }

    if (!fn_801F06E4(arg0)) {
        return false;
    }

    bool inverted = (_104 & (1 << 1));

    GSrender::sInstance->get_16e8()->fn_80236878(&mTransform);
    GSrender::sInstance->fn_802345F8(0, &mTransform, 0);

    bool _unk4 = false;

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        if ((mesh->mFlags & (1 << 0)) == (1 << 0)) {
            bool _unk5 = false;
            if ((mesh->mFlags & (1 << 1)) != (1 << 1) && mesh->mMaterial->getAlpha() == 255) {
                _unk5 = true;
            }

            if (_unk2 == _unk5) {
                if (mesh->fn_801EDEDC(inverted)) {
                    _unk4 = true;
                }
            }
        }
        mesh = mesh->mNext;
    }

    GSrender::sInstance->get_16e8()->_4--;

    if (_unk4) {
        if (_16c._1b) {
            _16c._14 = GSrender::sInstance->fn_8023B948(&_16c);
        }
        return true;
    }

    return false;
}

bool GSmodel::fn_801F134C(_UnkMaterialStruct_3 *arg0) {
    if (!fn_801F3CE0() || !checkDataFlag((1 << 11))) {
        return false;
    }

    // TODO(samm) Move to inline in GSrenderPass?
    u32 _unk1;
    if (GSrenderPass::getActiveRenderPass()) {
        _unk1 = GSrenderPass::getActiveRenderPass()->get_0();
    } else {
        _unk1 = 0;
    }

    bool _unk2 = (_unk1 != 8);

    switch (GSmath::fn_80220B18(&mBoundingBox)) {
        case 2:  GSrender::sInstance->setClipMode(GX_CLIP_DISABLE); break;
        case 0:  return false;
        default: GSrender::sInstance->setClipMode(GX_CLIP_ENABLE); break;
    }

    if (!fn_801F06E4(arg0)) {
        return false;
    }

    bool inverted = (_104 & (1 << 1));

    GSrender::sInstance->get_16e8()->fn_80236878(&mTransform);
    GSrender::sInstance->fn_802345F8(0, &mTransform, 0);

    bool _unk4 = false;

    GSmesh *mesh = mFirstMesh;
    while (mesh) {
        if ((mesh->mFlags & (1 << 0)) == (1 << 0)) {
            bool _unk5 = false;
            if ((mesh->mFlags & (1 << 1)) != (1 << 1) && mesh->mMaterial->getAlpha() == 255) {
                _unk5 = true;
            }

            if (_unk2 == _unk5) {
                _unk4 = true;
                mesh->fn_801EDF84(inverted);
            }
        }
        mesh = mesh->mNext;
    }

    GSrender::sInstance->get_16e8()->_4--;

    if (_unk4) {
        if (_16c._1b) {
            _16c._14 = GSrender::sInstance->fn_8023B948(&_16c);
        }
        return true;
    }

    return false;
}

void GSmodel::fn_801F1554(GSanimationObject *animObj, GSchannelData *channel, f32 cursor, bool blend) {
    if (blend) {
        return;
    }

    GSmodel *model = static_cast<GSmodel *>(animObj);
    GSmodelData *modelData = model->mModelData;

    switch (channel->mChannel) {
        case 17: {
            GScolor *vtxColors = model->_16c.mVertexColors;

            if (vtxColors && vtxColors != modelData->mVertexColors) {
                fn_801E1440(channel, cursor, &vtxColors[channel->mIndex]);
            }
        } break;
        case 18: {
            _UnkModelData_2 *_unk1 = model->_16c._10;

            if (_unk1 && _unk1 != modelData->_14) {
                GSvec2 *texCoords = _unk1[channel->_3].mTexCoords;
                if (texCoords != modelData->_14[channel->_3].mTexCoords) {
                    fn_801E13B8(channel, cursor, &texCoords[channel->mIndex]);
                }
            }
        } break;
    }
}
