#pragma once

#include "gs/GSsceneData.hpp"
#include "gs/scene/GShierMemObject.hpp"

#include <revolution.h>

class GSobject;
class GSlight;

// Size: 0x14
class GSscene : public GShierMemObject {
private:
    /* 0x00 */ GSsceneData *mData;
    /* 0x04 */ GSobject **mObjects;
    /* 0x08 */ GSlight *_8;
    /* 0x0C */ GSlight *_c;
    /* 0x10 */ GSlight *_10;

public:
    GSscene(GSsceneData *sceneData);
    ~GSscene();

    u32 getObjectCount() const {
        return mData->mObjectCount;
    }

    GSobject *getObject(u16 index) const {
        if (!mObjects) {
            return NULL;
        }
        if (index >= getObjectCount()) {
            return NULL;
        }
        return mObjects[index];
    }

    const GSenvData *getEnvData() const {
        return mData->mEnvData;
    }

    GStexture *getUnkTexture_1() const {
        return mData->mEnvData ? mData->mEnvData->_10 : NULL;
    }

    GStexture *getUnkTexture_2() const {
        return mData->mEnvData ? mData->mEnvData->_14 : NULL;
    }

    GSlight *getUnkLight_1() const {
        return _8;
    }

    GSlight *getUnkLight_2() const {
        return _c;
    }

    GSlight *getUnkLight_3() const {
        return _10;
    }
};
