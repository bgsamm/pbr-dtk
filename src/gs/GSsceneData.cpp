#include "gs/GSsceneData.hpp"

#include "gs/GSrender.hpp"
#include "gs/render/GStexture.hpp"

#include <revolution/gx/GXEnum.h>

#include "version.hpp"

// TODO(samm) #define the start of logical memory somewhere
#define FIX_POINTER(pointer, baseAddr)                                                                                 \
    do {                                                                                                               \
        if ((baseAddr) && (pointer) && (pointer) < (void *)0x80000000) {                                               \
            *(u32 *)&(pointer) += (u32)(baseAddr);                                                                     \
        }                                                                                                              \
    } while (0)

void fn_801E1714(_UnkSceneData_1 *arg0, GSsceneData *sceneData, u32 baseAddr) {
    FIX_POINTER(arg0->_18, baseAddr);
}

void fn_801E18F8(GSmaterialData *materialData, GSsceneData *sceneData, u32 baseAddr) {
    // TODO(samm) Figure out wth is going on here
    if (((sceneData->_00 << 24) | (sceneData->_02 << 8) | (sceneData->_04)) < 0x1000300) {
        materialData->_54 = 0;
    }
    if (((sceneData->_00 << 24) | (sceneData->_02 << 8) | (sceneData->_04)) < 0x1000400) {
        materialData->_50 = NULL;
    }

    FIX_POINTER(materialData->mName, baseAddr);
    FIX_POINTER(materialData->_50, baseAddr);

    GStexture **texSlots = materialData->mTextureSlots;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, texSlots++) {
        FIX_POINTER(*texSlots, baseAddr);
    }

    void **_unkVar1 = materialData->_2c;
    for (u32 i = 0; i < MATERIAL_MAX_TEXTURE_SLOTS; i++, _unkVar1++) {
        FIX_POINTER(*_unkVar1, baseAddr);
    }

    // TODO(samm) Is it possible to clean up these types?
    u32 _unkVar3 = 0;
    _UnkMaterialData_1 *(*_unkVar2)[2] = materialData->_40;
    for (u32 i = 0; i < 2; i++, _unkVar2++) {
        for (u32 j = 0; j < 2; j++) {
            FIX_POINTER((*_unkVar2)[j], baseAddr);

            if (_unkVar3 == 0 && (*_unkVar2)[j] && !materialData->_50) {
                switch ((*_unkVar2)[j]->_0) {
                    case 0:
                    case 2: materialData->_50 = materialData->mTextureSlots[(*_unkVar2)[j]->_4]; break;
                }
            }
            _unkVar3++;
        }
    }

    FIX_POINTER(materialData->_84, baseAddr);

    if (materialData->_84) {
        fn_801E1540(materialData->_84, sceneData, baseAddr);
    }
}

inline void initSceneTextures(GSsceneData *sceneData, u32 baseAddr) {
    GStexture **texList;
    u16 texCount;
    u16 texIndex;

    texCount = sceneData->mTextureCount;
    texList = sceneData->mTextureList;

    for (texIndex = 0; texIndex < texCount; texIndex++, texList++) {
        if (!*texList) {
            continue;
        }

        FIX_POINTER(*texList, baseAddr);
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

inline void initSceneUnknown(GSsceneData *sceneData, u32 baseAddr) {
    u16 _unkCount;
    u16 _unkIndex;
    _UnkSceneData_1 **_unkList;

    _unkCount = sceneData->_1c;
    _unkList = sceneData->_10;

    for (_unkIndex = 0; _unkIndex < _unkCount; _unkIndex++, _unkList++) {
        if (!*_unkList) {
            continue;
        }

        FIX_POINTER(*_unkList, baseAddr);
        fn_801E1714(*_unkList, sceneData, baseAddr);
    }
}

inline void initSceneMaterials(GSsceneData *sceneData, u32 baseAddr) {
    u16 matCount;
    u16 matIndex;
    GSmaterialData **matList;

    matCount = sceneData->mMaterialCount;
    matList = sceneData->mMaterialList;

    for (matIndex = 0; matIndex < matCount; matIndex++, matList++) {
        if (!*matList) {
            continue;
        }

        FIX_POINTER(*matList, baseAddr);
        fn_801E18F8(*matList, sceneData, baseAddr);
    }
}

inline void initSceneObjects(GSsceneData *sceneData, u32 baseAddr) {
    u16 objCount;
    u16 objIndex;
    GSobjectData **objList;

    objCount = sceneData->mObjectCount;
    objList = sceneData->mObjectList;

    for (objIndex = 0; objIndex < objCount; objIndex++, objList++) {
        if (!*objList) {
            continue;
        }

        FIX_POINTER(*objList, baseAddr);
        fn_801E2F60(*objList, sceneData, baseAddr, (bool)sceneData->_24);
    }
}

void fn_801E34DC(GSsceneData *sceneData, u32 baseAddr) {
    FIX_POINTER(sceneData->mObjectList, baseAddr);
    FIX_POINTER(sceneData->mTextureList, baseAddr);
    FIX_POINTER(sceneData->_10, baseAddr);
    FIX_POINTER(sceneData->mMaterialList, baseAddr);
    FIX_POINTER(sceneData->_24, baseAddr);
    FIX_POINTER(sceneData->_28, baseAddr);

    initSceneTextures(sceneData, baseAddr);

    // TODO(samm) Move to its own inline function?
    if (sceneData->_24) {
        fn_801E3380(sceneData->_24, sceneData, baseAddr);
    }

    initSceneUnknown(sceneData, baseAddr);
    initSceneMaterials(sceneData, baseAddr);
    initSceneObjects(sceneData, baseAddr);
}
