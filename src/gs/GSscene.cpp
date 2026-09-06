#include "gs/GSscene.hpp"

#include "gs/GSmem.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSsceneData.hpp"
#include "gs/GSsceneManager.hpp"

#include <cstring>

#include "version.hpp"

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

    _UnkSceneData_2 *_unk6 = sceneData->_24;
    if (_unk6) {
        for (s32 i = 0; i < objectCount; i++) {
            GSobject *object = mObjects[i];
            if (!object) {
                continue;
            }

            u16 lightCount = object->getLightCount();
            for (u16 j = 0; j < lightCount; j++) {
                GSlightNode *lightNode = object->getLightNode(j);

                if (lightNode && lightNode->get_10c()) {
                    u32 _unk7 = lightNode->get_10c();
                    if (_unk7 == _unk6->_18) {
                        _8 = lightNode;
                    }
                    if (_unk7 == _unk6->_1c) {
                        _c = lightNode;
                    }
                    if (_unk7 == _unk6->_20) {
                        _10 = lightNode;
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
    if (GSsceneManager::isCurrentScene(this)) {
        GSsceneManager::setCurrentScene(NULL);
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
