#include "gs/GShierarchyModule.hpp"

#include ".unsorted/801FA38C.hpp"
#include ".unsorted/80204058.hpp"
#include ".unsorted/8021D0E0.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSrender.hpp"
#include "gs/GSscene.hpp"
#include "gs/render/80235A74.hpp"
#include "gs/render/GSrenderTarget.hpp"
#include "gs/render/GStexture.hpp"
#include "gs/scene/GSmodel.hpp"

#include <cstring>

#include "common.hpp"

GSrenderLight *GShierarchyModule::sLights[8];
GSrenderLight *GShierarchyModule::lbl_804920B0[8];
GSrenderLight *GShierarchyModule::lbl_804920D0[8];
u8 GShierarchyModule::sLightCount;
u8 GShierarchyModule::lbl_8063F46D;
u8 GShierarchyModule::lbl_8063F46E;

GShierarchyModule::GShierarchyModule()
    : GSrenderModule("hierarchy"),
      mObjectList(),
      _14(),
      _1c(),
      _20(),
      _24(),
      _28(),
      _48(),
      _108(),
      _10a(),
      mLights(),
      _110(),
      _114(),
      _118(),
      _11c(),
      _120(),
      mCurrentScene(),
      _12c(),
      _130(),
      _134(),
      _138(),
      _13c(),
      _140(),
      _144(),
      _148(),
      _14c(),
      _150() {
    sInstance = this;
    fn_80204058();

    memset(&_48, 0, sizeof(_48));
    memset(&_28, 0, sizeof(_28));

    _12c = fn_8023D974(16, 16, 0xa4, 0, 0, 1);
    if (_12c) {
        fn_8023E3C8(_12c, GX_NEAR_MIP_NEAR, GX_NEAR_MIP_NEAR, (1 << 1));

        u8 *imgData = fn_8023E434(_12c, 0);
        for (s32 i = 0; i < 256; i++) {
            // Appears to map an 8-bit texel index to a linear, column-major pixel index
            // (A 16x16 8-bit texture would be made up of a 2x4 arrangement of 8x4 tiles)
            s32 tileX = ((i & 0x80) >> 2); // Which tile horizontally
            s32 tileY = ((i & 0xc) << 4);  // Which tile vertically
            s32 xOff = ((i & 0x70) >> 4);  // Horizontal position within tile
            s32 yOff = ((i & 0x3) << 3);   // Vertical position within tile
            imgData[tileX + xOff + tileY + yOff] = i;
            /*                      Result:                                            As image:
                00 10 20 30 40 50 60 70 01 11 21 31 41 51 61 71     00 10 20 30 40 50 60 70 80 90 a0 b0 c0 d0 e0 f0
                02 12 22 32 42 52 62 72 03 13 23 33 43 53 63 73     01 11 21 31 41 51 61 71 81 91 a1 b1 c1 d1 e1 f1
                80 90 a0 b0 c0 d0 e0 f0 81 91 a1 b1 c1 d1 e1 f1     02 12 22 32 42 52 62 72 82 92 a2 b2 c2 d2 e2 f2
                82 92 a2 b2 c2 d2 e2 f2 83 93 a3 b3 c3 d3 e3 f3     03 13 23 33 43 53 63 73 83 93 a3 b3 c3 d3 e3 f3
                04 14 24 34 44 54 64 74 05 15 25 35 45 55 65 75     04 14 24 34 44 54 64 74 84 94 a4 b4 c4 d4 e4 f4
                06 16 26 36 46 56 66 76 07 17 27 37 47 57 67 77     05 15 25 35 45 55 65 75 85 95 a5 b5 c5 d5 e5 f5
                84 94 a4 b4 c4 d4 e4 f4 85 95 a5 b5 c5 d5 e5 f5     06 16 26 36 46 56 66 76 86 96 a6 b6 c6 d6 e6 f6
                86 96 a6 b6 c6 d6 e6 f6 87 97 a7 b7 c7 d7 e7 f7 --> 07 17 27 37 47 57 67 77 87 97 a7 b7 c7 d7 e7 f7
                08 18 28 38 48 58 68 78 09 19 29 39 49 59 69 79     08 18 28 38 48 58 68 78 88 98 a8 b8 c8 d8 e8 f8
                0a 1a 2a 3a 4a 5a 6a 7a 0b 1b 2b 3b 4b 5b 6b 7b     09 19 29 39 49 59 69 79 89 99 a9 b9 c9 d9 e9 f9
                88 98 a8 b8 c8 d8 e8 f8 89 99 a9 b9 c9 d9 e9 f9     0a 1a 2a 3a 4a 5a 6a 7a 8a 9a aa ba ca da ea fa
                8a 9a aa ba ca da ea fa 8b 9b ab bb cb db eb fb     0b 1b 2b 3b 4b 5b 6b 7b 8b 9b ab bb cb db eb fb
                0c 1c 2c 3c 4c 5c 6c 7c 0d 1d 2d 3d 4d 5d 6d 7d     0c 1c 2c 3c 4c 5c 6c 7c 8c 9c ac bc cc dc ec fc
                0e 1e 2e 3e 4e 5e 6e 7e 0f 1f 2f 3f 4f 5f 6f 7f     0d 1d 2d 3d 4d 5d 6d 7d 8d 9d ad bd cd dd ed fd
                8c 9c ac bc cc dc ec fc 8d 9d ad bd cd dd ed fd     0e 1e 2e 3e 4e 5e 6e 7e 8e 9e ae be ce de ee fe
                8e 9e ae be ce de ee fe 8f 9f af bf cf df ef ff     0f 1f 2f 3f 4f 5f 6f 7f 8f 9f af bf cf df ef ff
            */
        }

        _12c->flush();
    }

    _128 = fn_8023623C(0x44, 0, 0, 1, 0, 1);
    fn_801EE044();
}

GShierarchyModule::~GShierarchyModule() {
    for (s32 i = 0; i < _10a; i++) {
        GSrenderTarget::_unkFunc_2(_130);
    }

    if (_128) {
        fn_8023645C(_128);
    }

    if (_12c) {
        _12c->fn_8023E2D0();
    }

    fn_80204270();

    sInstance = NULL;
}

void GShierarchyModule::fn_80200594(GSobject *arg0) {
    GShierarchyModule::sInstance->_14.append(arg0);
    if (arg0->get_44()) {
        GShierarchyModule::sInstance->_1c.append(arg0);
        if (arg0->get_48()) {
            GShierarchyModule::sInstance->_24.append(arg0);
        }
    } else if (arg0->checkFlag((1 << 2))) {
        GShierarchyModule::sInstance->_20.append(arg0);
    }

    u16 particleCount = arg0->getParticleCount();
    for (u16 i = 0; i < particleCount; i++) {
        GSparticle *particle = arg0->getParticle(i);
        if (particle && particle->get_138()) {
            particle->get_138()->_148 |= (1 << 3);
        }
    }
}

void GShierarchyModule::fn_80200858(GSobject *arg0) {
    u16 particleCount = arg0->getParticleCount();
    for (u16 i = 0; i < particleCount; i++) {
        GSparticle *particle = arg0->getParticle(i);
        if (particle && particle->get_138()) {
            particle->get_138()->_148 &= ~(1 << 3);
        }
    }

    u16 i;
    u16 _unk1 = GShierarchyModule::sInstance->_108;
    bool _unk2 = true;
    // TODO(samm) Revisit this cast
    for (i = 0; i < (s32)_unk1; i++) {
        if (_unk2) {
            GSobject *_unk3 = GShierarchyModule::sInstance->_28[i];
            if (_unk3 == arg0) {
                GShierarchyModule::sInstance->_28[i] = NULL;
                GShierarchyModule::sInstance->_108--;
                _unk2 = false;
            }
        } else {
            GSobject *_unk3 = GShierarchyModule::sInstance->_28[i];
            GShierarchyModule::sInstance->_28[i - 1] = _unk3;
        }
    }

    GShierarchyModule::sInstance->_1c.remove(arg0);
    GShierarchyModule::sInstance->_24.remove(arg0);
    GShierarchyModule::sInstance->_20.remove(arg0);
    GShierarchyModule::sInstance->_14.remove(arg0);
}

void GShierarchyModule::update(f32 deltaTime) {
    if (GSrender::sInstance->_unkCondition1()) {
        deltaTime = 0.f;
    }

    GSnull::updateAllTrees(deltaTime);

    GSlistNode *curr = mObjectList.mHead;
    while (curr) {
        GSobject *object = static_cast<GSobject *>(curr->mData);
        object->update(deltaTime, false);
        curr = curr->sll.mNext;
    }

    _UnkClass801FA38C::update(deltaTime);
    fn_802042E0(deltaTime);
    fn_8021D1D0(deltaTime);
}

void GShierarchyModule::fn_802010E0() {
    sLightCount = 0;
    lbl_8063F46D = 0;
    lbl_8063F46E = 0;

    GSlistNode *curr = mLights.mHead;
    while (curr) {
        GSlight *light = static_cast<GSlight *>(curr->mData);

        if (light->checkLightFlag((1 << 0))) {
            GSrenderLight *_unk1 = light->get_130();
            GSrenderLight *_unk2 = light->get_134();

            if (_unk1) {
                sLights[sLightCount++] = _unk1;
                lbl_804920B0[lbl_8063F46D++] = _unk1;
            }

            if (_unk2) {
                if (_unk1 != _unk2) {
                    sLights[sLightCount++] = _unk2;
                }
                lbl_804920D0[lbl_8063F46E++] = _unk2;
            }

            // TODO(samm) #define the 8
            if (sLightCount >= 8) {
                return;
            }
        }

        curr = curr->sll.mNext;
    }
}

void GShierarchyModule::setCurrentScene(GSscene *scene) {
    if (GShierarchyModule::sInstance->isCurrentScene(scene)) {
        return;
    }

    GShierarchyModule::sInstance->_114 = NULL;
    GShierarchyModule::sInstance->_110 = NULL;
    GShierarchyModule::sInstance->_118 = NULL;
    GShierarchyModule::sInstance->_11c = NULL;
    GShierarchyModule::sInstance->_120 = NULL;

    if (!GShierarchyModule::sInstance->mLights.isEmpty()) {
        GShierarchyModule::sInstance->mLights.clear();
    }

    GSrender::sInstance->setFogEnabled(false);

    GShierarchyModule::sInstance->mCurrentScene = NULL;

    if (scene) {
        const GSenvData *envData = scene->getEnvData();
        GSrender::sInstance->setFog((GXFogType)envData->mFogType,
                                    envData->mFogStartZ,
                                    envData->mFogEndZ,
                                    &envData->mFogColor);
        GSrender::sInstance->setFogRangeAdjEnabled(envData->mFogRangeAdjEnable);
        GSrender::sInstance->setFogEnabled(envData->mFogEnable);

        GShierarchyModule::sInstance->_114 = scene->getUnkTexture_1();
        GShierarchyModule::sInstance->_110 = scene->getUnkTexture_2();
        GShierarchyModule::sInstance->_118 = scene->getUnkLight_1();
        GShierarchyModule::sInstance->_11c = scene->getUnkLight_2();
        GShierarchyModule::sInstance->_120 = scene->getUnkLight_3();

        u16 objectCount = scene->getObjectCount();
        for (u16 objectIdx = 0; objectIdx < objectCount; objectIdx++) {
            GSobject *object = scene->getObject(objectIdx);
            if (object) {
                u16 lightCount = object->getLightCount();
                for (u16 lightIdx = 0; lightIdx < lightCount; lightIdx++) {
                    GSlight *light = object->getLight(lightIdx);
                    if (light) {
                        GShierarchyModule::sInstance->mLights.append(light);
                    }
                }
            }
        }

        GShierarchyModule::sInstance->mCurrentScene = scene;
    }

    GShierarchyModule::sInstance->fn_802010E0();
}
