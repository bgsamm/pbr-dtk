#pragma once

#include "gs/GSsceneData.hpp"
#include "gs/scene/GShierMemObject.hpp"
#include "gs/scene/GSlightNode.hpp"

#include <revolution.h>

struct GSobject;

// Size: 0x14
class GSscene : public GShierMemObject {
private:
    /* 0x00 */ GSsceneData *mData;
    /* 0x04 */ GSobject **mObjects;
    /* 0x08 */ GSlightNode *_8;
    /* 0x0C */ GSlightNode *_c;
    /* 0x10 */ GSlightNode *_10;

public:
    GSscene(GSsceneData *sceneData);
    ~GSscene();

    inline u32 getObjectCount() const {
        return mData->mObjectCount;
    }

    // TODO(samm) Return bool?
    inline _UnkSceneData_2 *getUnkSceneData() const {
        return mData->_24;
    }
};
