#pragma once

#include <revolution.h>

// NOTE(samm) Name known from RTTI
// Size: 0x20
class GSrenderTarget {
protected:
    /* 0x00 */ s32 mId;
    /* 0x04 */ u8 _4;
    /* 0x05 */ u8 _5;
    /* 0x06 */ u16 _6;
    /* 0x08 */ u32 _8;
    /* 0x0C */ u32 _c;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ GSrenderTarget *mNext;

    static GSrenderTarget *sHead;
    static GSrenderTarget *sTail;

public:
    GSrenderTarget(s32 id, u8 arg1, u8 arg2, u32 arg3);

    /* 0x08 */ virtual void fn_8023B59C();
    /* 0x0C */ virtual void fn_8023B5A0();
    /* 0x10 */ virtual ~GSrenderTarget();

    void fn_8023B2F0();

    GSrenderTarget *getNext() const {
        return mNext;
    }

    static GSrenderTarget *findTarget(s32 id);
    static void registerTarget(GSrenderTarget *target);
    static void unregisterTarget(GSrenderTarget *target);

    static GSrenderTarget *getTargetList() {
        return sHead;
    }
};
