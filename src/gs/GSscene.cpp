#include "gs/GSscene.hpp"

#include "gs/GShierarchyModule.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSsceneData.hpp"

#include <cstring>

#include "common.hpp"

GSscene::GSscene(GSsceneData *sceneData) : mData(sceneData), mObjects(NULL), _8(0), _c(0), _10(0) {
    u16 objectCount = mData->mObjectCount;
    if (!objectCount) {
        return;
    }

    mObjects = (GSobject **)GSmem::allocFromHeap(gGameHeap, objectCount * sizeof(*mObjects));
    if (!mObjects) {
        return;
    }

    memset(mObjects, 0, sizeof(*mObjects));

    for (s32 i = 0; i < objectCount; i++) {
        GSobjectData *objData = sceneData->mObjectList[i];
        if (objData) {
            mObjects[i] = new GSobject(this, objData);
        }
    }

    GSenvData *envData = sceneData->mEnvData;
    if (envData) {
        for (s32 i = 0; i < objectCount; i++) {
            GSobject *object = mObjects[i];
            if (!object) {
                continue;
            }

            u16 lightCount = object->getLightCount();
            for (u16 j = 0; j < lightCount; j++) {
                GSlight *light = object->getLight(j);

                if (light && light->get_10c()) {
                    u32 _unk7 = light->get_10c();
                    if (_unk7 == envData->_18) {
                        _8 = light;
                    }
                    if (_unk7 == envData->_1c) {
                        _c = light;
                    }
                    if (_unk7 == envData->_20) {
                        _10 = light;
                    }
                }
            }
        }

        if (!_10) {
            _10 = _c;
        }
    }
}

GSscene::~GSscene() {
    if (GShierarchyModule::isCurrentScene(this)) {
        GShierarchyModule::setCurrentScene(NULL);
    }

    if (!mObjects) {
        return;
    }

    for (u16 i = 0; i < getObjectCount(); i++) {
        if (mObjects[i]) {
            delete mObjects[i];
        }
    }

    if (mObjects) {
        GSmem::freeToHeap(gGameHeap, mObjects);
        mObjects = NULL;
    }
}
