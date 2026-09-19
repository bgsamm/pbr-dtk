#pragma once

#include <revolution.h>

struct _UnkRenderTargetStruct_2 {
    /* 0x0 */ s32 _0;
};

struct _UnkRenderTargetStruct_3 {
    /* 0x0 */ u8 _pad_0[0x4];
    /* 0x4 */ u8 _4;
};

struct _UnkRenderTargetStruct_1 {
    /* 0x00 */ _UnkRenderTargetStruct_2 *_0;
    /* 0x04 */ _UnkRenderTargetStruct_3 *_4;
    /* 0x08 */ u16 _8;
    /* 0x0A */ u8 _pad_a[0x6];
    /* 0x10 */ _UnkRenderTargetStruct_1 *mNext;
};

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
    /* 0x10 */ _UnkRenderTargetStruct_1 *_10;
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
    void fn_8023B3B8(u32 arg0);

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
