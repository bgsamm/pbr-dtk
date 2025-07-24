#pragma once

#include <revolution/types.h>

#include "gs/GSvideo.hpp"

typedef void (*UnkFunc1)(u32);

struct UnkStruct1 {
    u8 mNumBuffers;
    u16 mEfbHeight;
    VideoFormat mVidFmt;
    u32 _8;
    u32 _C;
    u32 _10;
    u16 _14; // some sort of count
    u8 _16;
    u8 _17;
};

struct UnkStruct2 {
    UnkFunc1 _0;
    u32 _4;
    u32 _8;
    UnkStruct2 *_c;
};

class UnkClass5 {
    u8 unk1[0xc];
public:
    UnkClass5(u32 param1);
    ~UnkClass5();
};

struct UnkStruct8 {
    void *_0;
    u32 _4;
    u32 _8;
};

class GSrender : public GSvideoManager {
public:
    u32 _dc;
    u8 unk5[0x1558];
    void *_1638;
    struct {
        u8 unk1[0x88];
        void *_16c4;
        u8 unk2[0x14];
        UnkStruct2 *_16dc;
        UnkStruct2 *_16e0;
        UnkStruct2 *_16e4;
    } _163c;
    UnkClass5 *_16e8;
    u32 _16ec;
    u32 _16f0;
    u32 _16f4;
    u8 _16f8;
    u8 _16f9;
    u8 _16fa;
    u8 _16fb;
    u8 _16fc;
    u8 _16fd;
    u16 _16fe;
    u32 _1700;
    u32 _1704;
    u8 _1708;
    u8 _1709;
    u8 _170a;
    u8 _170b;
    u32 _170c;
    u32 _1710;
    u32 _1714;
    u8 _1718;
    u8 _1719;
    u8 _171a;
    u8 _171b;
    u32 _171c;
    u32 _1720;
    u32 _1724;
    u32 _1728;
    void *_172c;
    void *_1730;
    void *_1734;
    u32 _1738;
    u32 _173c;
    
    GSrender(UnkStruct1 *param1);
    ~GSrender();

    void fn_802311AC(UnkStruct8 *);
    void fn_802311BC(UnkStruct8 *);
    void fn_8023125C(UnkStruct8 *);
    void fn_80231374();
    
    void fn_802327E8();

    u32 fn_80232404(UnkFunc1, u32);
    UnkStruct2 *fn_802324F0();
    UnkStruct2 *fn_8023246C();
    void fn_8023255C(u32, u32);
    void fn_80232770();
    
    void fn_80235178(u32, u32, u32, u32, u32);
    void fn_80235204(u32, f32, f32, f32, f32);
    void fn_80237798(u32);

    void fn_80239E58();
    void fn_8023B6BC();
    void fn_8023B704();
    u32 fn_8023B864(u32);
    u32 fn_8023B948(u32);
    void fn_8023AE54();
    
    void fn_8024041C();
};
