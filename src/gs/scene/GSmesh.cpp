#include "gs/scene/GSmesh.hpp"

#include "gs/GSrender.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/render/8023283C.hpp"
#include "gs/render/8023B9F4.hpp"

#include "common.hpp"

GSmesh::GSmesh(GSmodel *parentModel, GSmeshData *data)
    : mFlags((1 << 0)),
      _4(),
      mParentModel(parentModel),
      _c(),
      mData(data),
      mMaterial(),
      _18(),
      mDisplayList(),
      mNext() {
    switch (data->_0) {
        case 0:
            if (data->mRenderSettings->mAlphaUpdateEnable || data->mRenderSettings->mDstAlphaEnable ||
                !data->mRenderSettings->mBlend || data->mRenderSettings->mBlendMode != GX_BM_NONE) {
                mFlags |= (1 << 1);
            }
            break;

        case 2: mFlags |= (1 << 1); break;
    }

    if (!data->_10) {
        return;
    }

    GSdisplayList *displayList = data->_10->mDisplayList;
    if (!displayList) {
        return;
    }
    mDisplayList = displayList;

    _18 = new _UnkClass8023C09C(displayList->get_10());
    if (!_18) {
        return;
    }

    _c = mMaterial = new GSmaterial(data->mMaterial, data->mRenderSettings);
}

GSmesh::~GSmesh() {
    if (_4) {
        GSrender::sInstance->fn_8023B88C(_4);
        _4 = 0;
    }

    if (mMaterial) {
        delete mMaterial;
    }

    if (_18) {
        delete _18;
    }
}

bool GSmesh::fn_801ED62C(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool inverted, u32 arg3) {
    if (!mMaterial || !_18 || !mDisplayList || mMaterial->getAlpha() == 0) {
        return false;
    }

    _18->fn_8023C2E8();
    mMaterial->fn_801EABE8(inverted);

    GSmeshRenderSettings *renderSettings = mMaterial->getRenderSettings();
    bool isFogEnabled = GSrender::sInstance->isFogEnabled();

    if (!mMaterial->fn_801EC050(arg0, arg1, isFogEnabled)) {
        return false;
    }

    // TODO(samm) Inline
    if ((mFlags & (1 << 1)) != (1 << 1)) {
        bool translucent = (mMaterial->getAlpha() != 255);

        if (translucent) {
            GSrender::sInstance->setBlend(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
        }

        if (mMaterial->fn_801EC538(arg0, arg1, true, true, arg3)) {
            GSrender::sInstance->callDisplayList(mDisplayList);
        }

        if (translucent) {
            if (renderSettings->mBlend) {
                GSrender::sInstance->setBlend((GXBlendMode)renderSettings->mBlendMode,
                                              (GXBlendFactor)renderSettings->mBlendSrcFactor,
                                              (GXBlendFactor)renderSettings->mBlendDstFactor);
            } else {
                GSrender::sInstance->setBlend((GXLogicOp)renderSettings->mBlendOp);
            }
        }
    } else {
        bool zUpdateEnable = false;
        if (mMaterial->fn_801EC538(arg0, arg1, true, false, arg3)) {
            GSrender::sInstance->callDisplayList(mDisplayList);
            zUpdateEnable = renderSettings->mZUpdateEnable;
        }

        if (mMaterial->fn_801EC538(arg0, arg1, false, true, false)) {
            if (zUpdateEnable) {
                GSrender::sInstance->setZCompare(true, GX_EQUAL);
            }

            // TODO(samm) Revisit this
            if (renderSettings->mAlphaCompEnable == 1) {
                GSrender::sInstance->setAlphaCompare(false, GX_ALWAYS, 0);
            }

            GSrender::sInstance->setEfbUpdate(renderSettings->mColorUpdateEnable,
                                              false,
                                              renderSettings->mZUpdateEnable);
            GSrender::sInstance->setBlend(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE);
            GSrender::sInstance->callDisplayList(mDisplayList);

            GSrender::sInstance->setEfbUpdate(renderSettings->mColorUpdateEnable,
                                              renderSettings->mAlphaUpdateEnable,
                                              renderSettings->mZUpdateEnable);

            if (renderSettings->mBlend) {
                GSrender::sInstance->setBlend((GXBlendMode)renderSettings->mBlendMode,
                                              (GXBlendFactor)renderSettings->mBlendSrcFactor,
                                              (GXBlendFactor)renderSettings->mBlendDstFactor);
            } else {
                GSrender::sInstance->setBlend((GXLogicOp)renderSettings->mBlendOp);
            }

            if (zUpdateEnable) {
                GSrender::sInstance->setZCompare(renderSettings->mZCompareFunc != GX_ALWAYS,
                                                 (GXCompare)renderSettings->mZCompareFunc);
            }

            // TODO(samm) Revisit this
            if (renderSettings->mAlphaCompEnable == 1) {
                GSrender::sInstance->setAlphaCompare(renderSettings->mAlphaCompEnable,
                                                     renderSettings->mAlphaComp,
                                                     renderSettings->mAlphaRef);
            }
        }
    }

    _4 = GSrender::sInstance->fn_8023B948(this);

    GSrender::sInstance->setFogEnabled(isFogEnabled);

    return true;
}

bool GSmesh::fn_801EDDFC(_UnkMaterialStruct_3 *arg0, GSmatrix *arg1, bool inverted) {
    if (!mMaterial || !_18 || !mDisplayList || mMaterial->getAlpha() == 0) {
        return false;
    }

    _18->fn_8023C2E8();

    bool zComp = (mFlags & (1 << 1)) == (1 << 1);
    mMaterial->fn_801EB044(inverted, true, zComp);

    if (zComp) {
        mMaterial->fn_801EB87C(arg0, arg1);
    }

    GSrender::sInstance->callDisplayList(mDisplayList);

    _4 = GSrender::sInstance->fn_8023B948(this);

    return true;
}

bool GSmesh::fn_801EDEDC(bool inverted) {
    if (!mMaterial || !_18 || !mDisplayList || mMaterial->getAlpha() == 0) {
        return false;
    }

    _18->fn_8023C2E8();

    mMaterial->fn_801EB044(inverted, false, true);

    GSrender::sInstance->callDisplayList(mDisplayList);

    _4 = GSrender::sInstance->fn_8023B948(this);

    return true;
}

bool GSmesh::fn_801EDF84(bool inverted) {
    if (!mMaterial || !_18 || !mDisplayList || mMaterial->getAlpha() == 0) {
        return false;
    }

    _18->fn_8023C2E8();

    mMaterial->fn_801EB668(inverted);

    GSrender::sInstance->callDisplayList(mDisplayList);

    _4 = GSrender::sInstance->fn_8023B948(this);

    return true;
}
