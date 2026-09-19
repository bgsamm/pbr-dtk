#include "gs/GSsceneData.hpp"

#include ".unsorted/80220DC4.hpp"
#include "gs/GShierarchyModule.hpp"
#include "gs/GSmenuModule.hpp"
#include "gs/GSrender.hpp"
#include "gs/render/GStexture.hpp"
#include "gs/scene/GScamera.hpp"
#include "gs/scene/GSlight.hpp"
#include "gs/scene/GSmaterial.hpp"
#include "gs/scene/GSmodel.hpp"
#include "gs/scene/GSnull.hpp"

#include <revolution/gx/GXEnum.h>

#include "common.hpp"

static _UnkObjectData_1 lbl_804918B4;

// TODO(samm) #define the start of logical memory somewhere
template <typename T>
static inline void fixPointer(T **pointer, u32 baseAddr) {
    if (baseAddr && *pointer && (u32)*pointer < 0x80000000) {
        *pointer = (T *)((u32)*pointer + baseAddr);
    }
}

void fn_801E0A60(GSchannelData *channelData, GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&channelData->mKeyframes, baseAddr);

    if (!channelData->mKeyframes) {
        return;
    }

    GSkeyframe *keyframes = NULL;
    u16 keyframeCount = 0;
    f32 *pDuration = NULL;

    switch (channelData->mChannel) {
        case 0:
        case 1:
        case 2:
        case 3:
            channelData->_0 = false;
            channelData->mStepCallback = GSnull::fn_801F3D44;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            channelData->_0 = false;
            channelData->mStepCallback = GScamera::fn_801DEEF8;
            break;
        case 17:
        case 18:
            channelData->_0 = false;
            channelData->mStepCallback = GSmodel::fn_801F1554;
            break;
        case 19:
            channelData->_0 = false;
            channelData->mStepCallback = GSlight::fn_801E6BB0;
            break;
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
            channelData->_0 = true;
            channelData->mStepCallback = GSmaterial::fn_801EC9AC;
            break;
    }

    GSanimTrackData *trackData;
    switch (channelData->mDataType) {
        // NOTE(samm) There is no difference between any of the cases
        case 0:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 1:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 2:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 3:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 4:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 5:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 6:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 7:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
        case 8:
            trackData = channelData->mKeyframes;
            fixPointer(&trackData->mValues, baseAddr);
            fixPointer(&trackData->mControls, baseAddr);
            fixPointer(&trackData->mKeyframes, baseAddr);
            keyframeCount = trackData->mKeyframCount;
            pDuration = &trackData->mDuration;
            keyframes = trackData->mKeyframes;
            break;
    }

    if (pDuration && keyframes && keyframeCount) {
        *pDuration = 0.f;
        for (u16 i = 0; i < keyframeCount; i++, keyframes++) {
            if (*pDuration < keyframes->mTime) {
                *pDuration = keyframes->mTime;
            }
        }
    }
}

void fn_801E10C0(GSchannelData *channelData, f32 cursor, f32 *dst) {
    switch (channelData->mDataType) {
        case 0: *dst = GSmath::fn_80221B2C(cursor, channelData->mKeyframes, 0); break;
        case 5: {
            u8 result = GSmath::animSampleU8(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 6: {
            s8 result = GSmath::animSampleS8(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 7: {
            u16 result = GSmath::animSampleU16(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
        case 8: {
            s16 result = GSmath::animSampleS16(cursor, channelData->mKeyframes, channelData->mScaleExp);
            *dst = (f32)result / (1 << channelData->mScaleExp);
        } break;
    }
}

void fn_801E1278(GSchannelData *channelData, f32 cursor, GSvec3 *dst) {
    switch (channelData->mComponent) {
        case 0: {
            GSvec3 result;
            GSmath::animSampleVec3(&result, cursor, channelData->mKeyframes, 0);
            *dst = result;
        } break;
        case 1: {
            fn_801E10C0(channelData, cursor, &dst->x);
        } break;
        case 2: {
            fn_801E10C0(channelData, cursor, &dst->y);
        } break;
        case 3: {
            fn_801E10C0(channelData, cursor, &dst->z);
        } break;
        // NOTE(samm) These appear bugged, since the function they call also switches on mComponent, but uses 0-2
        case 4: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->x = result.x;
            dst->y = result.y;
        } break;
        case 5: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->x = result.x;
            dst->z = result.y;
        } break;
        case 6: {
            GSvec2 result;
            fn_801E13B8(channelData, cursor, &result);
            dst->y = result.x;
            dst->z = result.y;
        } break;
    }
}

void fn_801E1360(GSchannelData *channelData, f32 cursor, GSquat *dst) {
    GSquat result;
    GSmath::animSampleQuat(&result, cursor, channelData->mKeyframes, 0);
    *dst = result;
}

void fn_801E13B8(GSchannelData *channelData, f32 cursor, GSvec2 *dst) {
    switch (channelData->mComponent) {
        case 0: *dst = GSmath::fn_80221F8C(cursor, channelData->mKeyframes, 0); break;
        case 1: fn_801E10C0(channelData, cursor, &dst->x); break;
        case 2: fn_801E10C0(channelData, cursor, &dst->y); break;
    }
}

void fn_801E1504(GSchannelData *channelData, f32 cursor, u8 *dst) {
    *dst = GSmath::animSampleU8(cursor, channelData->mKeyframes, channelData->mScaleExp);
}

void fn_801E1540(GSkeyframeData *arg0, GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&arg0->mChannels, baseAddr);

    GSchannelData *channelData = arg0->mChannels;
    for (u16 i = 0; i < arg0->mChannelCount; i++, channelData++) {
        fn_801E0A60(channelData, sceneData, baseAddr);
    }

    fixPointer(&arg0->mNext, baseAddr);

    if (arg0->mNext) {
        fn_801E1540(arg0->mNext, sceneData, baseAddr);
    }
}

void fn_801E1714(_UnkSceneData_1 *arg0, GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&arg0->_18, baseAddr);
}

void fn_801E18F8(GSmaterialData *materialData, GSsceneData *sceneData, u32 baseAddr) {
    if (sceneData->mVersion < VERSION(1, 3, 0)) {
        materialData->_54 = 0;
    }
    if (sceneData->mVersion < VERSION(1, 4, 0)) {
        materialData->_50 = NULL;
    }

    fixPointer(&materialData->mName, baseAddr);
    fixPointer(&materialData->_50, baseAddr);

    GStexture **texSlots = materialData->mTextureSlots;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, texSlots++) {
        fixPointer(texSlots, baseAddr);
    }

    void **_unkVar1 = materialData->_2c;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, _unkVar1++) {
        fixPointer(_unkVar1, baseAddr);
    }

    // TODO(samm) Is it possible to clean up these types?
    u32 _unkVar3 = 0;
    _UnkMaterialData_1 *(*_unkVar2)[2] = materialData->_40;
    for (u32 i = 0; i < 2; i++, _unkVar2++) {
        for (u32 j = 0; j < 2; j++) {
            fixPointer(&(*_unkVar2)[j], baseAddr);

            if (_unkVar3 == 0 && (*_unkVar2)[j] && !materialData->_50) {
                switch ((*_unkVar2)[j]->_0) {
                    case 0:
                    case 2: materialData->_50 = materialData->mTextureSlots[(*_unkVar2)[j]->_4]; break;
                }
            }
            _unkVar3++;
        }
    }

    fixPointer(&materialData->_84, baseAddr);

    if (materialData->_84) {
        fn_801E1540(materialData->_84, sceneData, baseAddr);
    }
}

void fn_801E1CD0(GSnodeData *nodeData, GSsceneData *sceneData, u32 baseAddr) {
    switch (nodeData->mNodeType) {
        case GS_NODE_JOINT:    fn_801E2A90(nodeData, sceneData, baseAddr); break;
        case GS_NODE_MODEL:    fn_801E2878(nodeData, sceneData, baseAddr); break;
        case GS_NODE_CAMERA:   fn_801E2AE8(nodeData, sceneData, baseAddr); break;
        case GS_NODE_LIGHT:    fn_801E2A60(nodeData, sceneData, baseAddr); break;
        case GS_NODE_PARTICLE: fn_801E2B40(nodeData, sceneData, baseAddr); break;
        case GS_NODE_VOLUME:   fn_801E2D88(nodeData, sceneData, baseAddr); break;
    }

    fixPointer(&nodeData->mName, baseAddr);
    fixPointer(&nodeData->mTranslation, baseAddr);
    fixPointer(&nodeData->mRotation, baseAddr);
    fixPointer(&nodeData->mScale, baseAddr);
    fixPointer(&nodeData->mTransformPivots, baseAddr);
    fixPointer(&nodeData->mAnimData, baseAddr);
    fixPointer(&nodeData->mNextSibling, baseAddr);
    fixPointer(&nodeData->mFirstChild, baseAddr);
    fixPointer(&nodeData->_2c, baseAddr);

    _TransformPivots *pivots = nodeData->mTransformPivots;
    if (pivots) {
        if (sceneData->mVersion < VERSION(1, 3, 0)) {
            if (pivots->_24_0 != 0xfefefefe || pivots->_24_1 != 0xfefefefe || pivots->_24_2 != 0xfefefefe) {
                GSvec3 _unk1, _unk2, _unk3;

                _unk1 = -pivots->mScalePivot;
                _unk2 = pivots->mScalePivot;

                VECAdd(&_unk2, &pivots->mScaleToRot, &_unk2);
                VECSubtract(&_unk2, &pivots->mRotToTrans, &_unk2);

                _unk3 = pivots->mRotToTrans;
                VECAdd(&_unk3, &pivots->_24, &_unk3);

                nodeData->mTransformPivots->mScalePivot = _unk1;
                nodeData->mTransformPivots->mScaleToRot = _unk2;
                nodeData->mTransformPivots->mRotToTrans = _unk3;

                pivots->_24_0 = 0xfefefefe;
                pivots->_24_1 = 0xfefefefe;
                pivots->_24_2 = 0xfefefefe;
            };
        }
    }

    if (nodeData->mAnimData) {
        fn_801E1540(nodeData->mAnimData, sceneData, baseAddr);
    }

    if (nodeData->mFirstChild) {
        fn_801E1CD0(nodeData->mFirstChild, sceneData, baseAddr);
    }

    if (nodeData->mNextSibling) {
        fn_801E1CD0(nodeData->mNextSibling, sceneData, baseAddr);
    }
}

// TODO(samm) Move?
inline void _unkRenderTarget(u32 arg0) {
    GSrenderTarget *target = GSrenderTarget::findTarget((arg0 >> 16) & 0xff);
    if (target) {
        target->fn_8023B3B8(arg0);
    }
}

void fn_801E2E34(GSanimationData *animationData, GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&animationData->mName, baseAddr);
    fixPointer(&animationData->_10, baseAddr);
    fixPointer(&animationData->_14, baseAddr);
    fixPointer(&animationData->_1c, baseAddr);
    fixPointer(&animationData->_20, baseAddr);
    fixPointer(&animationData->_2c, baseAddr);
}

void fn_801E2F60(GSobjectData *objectData, GSsceneData *sceneData, u32 baseAddr, bool arg3) {
    fixPointer(&objectData->mName, baseAddr);
    fixPointer(&objectData->mRootNode, baseAddr);
    fixPointer(&objectData->mAnimList, baseAddr);
    fixPointer(&objectData->mBoundingBox, baseAddr);
    fixPointer(&objectData->_18, baseAddr);

    GSanimationData *animData = objectData->mAnimList;
    for (u16 i = 0; i < objectData->mAnimCount; i++, animData++) {
        fn_801E2E34(animData, sceneData, baseAddr);
    }

    if (objectData->mRootNode) {
        fn_801E1CD0(objectData->mRootNode, sceneData, baseAddr);
    }

    if (objectData->_18) {
        // TODO(samm) Fix regswap here
        fixPointer(&objectData->_18->_0, baseAddr);
        fixPointer(&objectData->_18->_8, baseAddr);
    } else {
        objectData->_18 = &lbl_804918B4;
    }

    if (arg3) {
        _unkRenderTarget(GShierarchyModule::getInstance()->get_138());
        _unkRenderTarget(GShierarchyModule::getInstance()->get_144());
    } else {
        _unkRenderTarget(GShierarchyModule::getInstance()->get_140());
        _unkRenderTarget(GShierarchyModule::getInstance()->get_144());
        _unkRenderTarget(GSmenuModule::getInstance()->get_10c());
        _unkRenderTarget(GSmenuModule::getInstance()->get_110());
    }
}

static inline void initSceneTextures(GSsceneData *sceneData, u32 baseAddr) {
    GStexture **texList;
    u16 texCount;
    u16 texIndex;

    texCount = sceneData->mTextureCount;
    texList = sceneData->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (!*texList) {
            continue;
        }

        fixPointer(texList, baseAddr);
        *texList = fn_8023D6CC(*texList);

        if (GSrender::getInstance()->get_7a()) {
            GXTexFilter magFilter = (*texList)->mMagFilter;
            if (magFilter < GX_NEAR_MIP_NEAR) {
                magFilter = GX_NEAR_MIP_NEAR;
            }

            GXTexFilter minFilter = (*texList)->mMinFilter;
            if (minFilter < GX_NEAR_MIP_NEAR) {
                minFilter = GX_NEAR_MIP_NEAR;
            }

            u32 filterFlags = (*texList)->mFilterFlags;
            fn_8023E3C8(*texList, minFilter, magFilter, filterFlags);
        }
    }

    GSrender::getInstance()->invalidateTextureCache();
}

static inline void initSceneUnknown(GSsceneData *sceneData, u32 baseAddr) {
    u16 _unkCount;
    u16 _unkIndex;
    _UnkSceneData_1 **_unkList;

    _unkCount = sceneData->_1c;
    _unkList = sceneData->_10;

    for (_unkIndex = 0; _unkIndex < _unkCount; _unkIndex++, _unkList++) {
        if (!*_unkList) {
            continue;
        }

        fixPointer(_unkList, baseAddr);
        fn_801E1714(*_unkList, sceneData, baseAddr);
    }
}

static inline void initSceneMaterials(GSsceneData *sceneData, u32 baseAddr) {
    u16 matCount;
    u16 matIndex;
    GSmaterialData **matList;

    matCount = sceneData->mMaterialCount;
    matList = sceneData->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (!*matList) {
            continue;
        }

        fixPointer(matList, baseAddr);
        fn_801E18F8(*matList, sceneData, baseAddr);
    }
}

static inline void initSceneObjects(GSsceneData *sceneData, u32 baseAddr) {
    u16 objCount;
    u16 objIndex;
    GSobjectData **objList;

    objCount = sceneData->mObjectCount;
    objList = sceneData->mObjectList;

    for (objIndex = 0; objIndex < objCount; objIndex++, objList++) {
        if (!*objList) {
            continue;
        }

        fixPointer(objList, baseAddr);
        fn_801E2F60(*objList, sceneData, baseAddr, (bool)sceneData->_24);
    }
}

void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr) {
    fixPointer(&sceneData->mObjectList, baseAddr);
    fixPointer(&sceneData->mTextureList, baseAddr);
    fixPointer(&sceneData->_10, baseAddr);
    fixPointer(&sceneData->mMaterialList, baseAddr);
    fixPointer(&sceneData->_24, baseAddr);
    fixPointer(&sceneData->_28, baseAddr);

    initSceneTextures(sceneData, baseAddr);

    // TODO(samm) Move to its own inline function?
    if (sceneData->_24) {
        fn_801E3380(sceneData->_24, sceneData, baseAddr);
    }

    initSceneUnknown(sceneData, baseAddr);
    initSceneMaterials(sceneData, baseAddr);
    initSceneObjects(sceneData, baseAddr);
}
