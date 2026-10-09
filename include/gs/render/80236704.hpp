#pragma once

#include "gs/GSmath.hpp"
#include "gs/GSrender.hpp"

#include <revolution.h>

struct GSrenderStruct8;

struct GSrenderStruct8 {
    /* 0x0 */ u32 mFlags;
    /* 0x4 */ GSmatrix mPosMtx;
    /* 0x34 */ u8 _pad_34[48];
    /* 0x64 */ GSmatrix mNrmMtx;
};

// Size: 0xc
class _UnkClass80236704 {
    // TODO(samm) Make private
public:
    /* 0x0 */ u8 _pad_0[4];
    /* 0x4 */ GSrenderStruct8 *_4;
    /* 0x8 */ u8 _pad_8[4];

public:
    _UnkClass80236704(u32 param1);
    ~_UnkClass80236704();

    void fn_80236878(GSmatrix *arg0);

    GSrenderStruct8 *get_4() const {
        return _4;
    }

    void _unkFunc_1() {
        if ((_4->mFlags & (1 << 1))) {
            Mtx _unk1;
            MTXInvXpose(_4->mPosMtx, _unk1);
            MTXCopy(_unk1, _4->mNrmMtx);
            _4->mFlags &= ~(1 << 1);
        }
        GSrender::sInstance->fn_802345F8(10, &_4->mNrmMtx, true);
    }
};
