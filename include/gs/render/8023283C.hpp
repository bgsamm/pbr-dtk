#pragma once

#include <revolution.h>

struct GSvertexFormat;

class GSdisplayList {
private:
    /* 0x00 */ u16 mFlags;
    /* 0x02 */ u16 _2;
    /* 0x04 */ void *mDisplayList;
    /* 0x08 */ u32 mDisplayListSize;
    /* 0x0C */ GSvertexFormat *mVertexFormat;
    /* 0x10 */ u32 _10;

public:
    GSdisplayList();
    ~GSdisplayList();

    void fn_802328AC();
    void call();
    void flush();

    u32 *get_10() {
        return &_10;
    }

    GSvertexFormat *getVertexFormat() const {
        if ((mFlags & (1 << 0))) {
            return mVertexFormat;
        }
        return NULL;
    }
};
