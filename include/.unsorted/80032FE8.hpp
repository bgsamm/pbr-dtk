#pragma once

#include ".unsorted/800400E8.hpp"
#include "gs/GScolor.hpp"
#include "gs/render/GSrenderTarget.hpp"

class GScamera;
class GSobject;

// size: 0x10
struct Unk800354D8 {
    /* 0x0 */ f32 _0[4];
};

// size: 0xB4
struct Unk80035380 {
    /* 0x00 */ u8 _00;
    /* 0x01 */ bool _01;
    /* 0x02 */ u8 _02;
    /* 0x04 */ GScamera *_04;
    /* 0x08 */ u32 _08;
    /* 0x0C */ Unk800354D8 _0c;
    /* 0x1C */ eftseq::AnimNode<f32> _1c[4];
    /* 0xAC */ void *_ac;
    /* 0xB0 */ GSobject *_b0;
};

namespace eftseq {

// Name known from RTTI.
// size: 0xC0
class AnimNodeSpring : public AnimNode<f32> {
public:
    /* 0x24 */ u8 unk24[0x9C];
};

} // namespace eftseq

// size: 0x6B4
struct Unk80033090 {
    /* 0x000 */ Unk80035380 _000[2];
    /* 0x168 */ u8 _168;
    /* 0x16C */ f32 _16c;
    /* 0x170 */ u8 _170;
    /* 0x171 */ u8 _171;
    /* 0x174 */ f32 _174;
    /* 0x178 */ s32 _178;
    /* 0x17C */ u8 _17c;
    /* 0x180 */ f32 _180;
    /* 0x184 */ f32 _184;
    /* 0x188 */ u8 _188;
    /* 0x18C */ f32 _18c;
    /* 0x190 */ s32 _190;
    /* 0x194 */ u8 _194;
    /* 0x198 */ f32 _198;
    /* 0x19C */ f32 _19c;
    /* 0x1A0 */ s32 _1a0;
    /* 0x1A4 */ u8 _1a4;
    /* 0x1A5 */ u8 _1a5;
    /* 0x1A8 */ f32 _1a8;
    /* 0x1AC */ f32 _1ac;
    /* 0x1B0 */ f32 _1b0;
    /* 0x1B4 */ f32 _1b4;
    /* 0x1B8 */ f32 _1b8;
    /* 0x1BC */ f32 _1bc;
    /* 0x1C0 */ f32 _1c0;
    /* 0x1C4 */ f32 _1c4;
    /* 0x1C8 */ f32 _1c8;
    /* 0x1CC */ f32 _1cc;
    /* 0x1D0 */ f32 _1d0;
    /* 0x1D4 */ f32 _1d4;
    /* 0x1D8 */ f32 _1d8;
    /* 0x1DC */ GXColor _1dc;
    /* 0x1E0 */ s32 _1e0;
    /* 0x1E4 */ s32 _1e4;
    /* 0x1E8 */ f32 _1e8;
    /* 0x1EC */ f32 _1ec;
    /* 0x1F0 */ f32 _1f0;
    /* 0x1F4 */ f32 _1f4;
    /* 0x1F8 */ f32 _1f8;
    /* 0x1FC */ f32 _1fc;
    /* 0x200 */ s32 _200;
    /* 0x204 */ eftseq::AnimNodeShake _204;
    /* 0x264 */ eftseq::AnimNodeShake _264;
    /* 0x2C4 */ eftseq::AnimNode<f32> _2c4[6];
    /* 0x39C */ eftseq::AnimNodeSpring _39c[3];
    /* 0x5DC */ eftseq::AnimNode<f32> _5dc;
    /* 0x600 */ eftseq::AnimNode<f32> _600;
    /* 0x624 */ eftseq::AnimNode<f32> _624;
    /* 0x648 */ eftseq::AnimNode<f32> _648;
    /* 0x66C */ eftseq::AnimNode<f32> _66c;
    // AnimNode<GScolor<unsigned char>> in the RTTI of the original.
    /* 0x690 */ eftseq::AnimNode<GScolor> _690;
};

// The render target with id 2.
class Unk80242A00 : public GSrenderTarget {
public:
    using GSrenderTarget::_c;

    /* 0x20 */ s32 _20;
    /* 0x24 */ GScamera *_24;
    /* 0x28 */ u8 unk28[0x11];
    /* 0x39 */ u8 _39;
    /* 0x3A */ u8 unk3a[0x2A];
    /* 0x64 */ GScamera *_64;
    /* 0x68 */ u8 unk68[0x11];
    /* 0x79 */ u8 _79;
    /* 0x7A */ u8 unk7a[0x2E];
    /* 0xA8 */ s32 _a8;
    /* 0xAC */ f32 _ac;
    /* 0xB0 */ f32 _b0;
    /* 0xB4 */ f32 _b4;
    /* 0xB8 */ f32 _b8;
    /* 0xBC */ f32 _bc;
    /* 0xC0 */ f32 _c0;
    /* 0xC4 */ GXColor _c4;
    /* 0xC8 */ u32 _c8;
};

// size: unknown
struct Unk8063F410 {
    /* 0x000 */ u8 unk000[0x40D];
    /* 0x40D */ u8 _40d;
    /* 0x40E */ u8 _40e;
    /* 0x40F */ u8 _40f;
    /* 0x410 */ u8 unk410[0x8];
    /* 0x418 */ s32 _418;
    /* 0x41C */ u8 unk41c[0x8];
    /* 0x424 */ Vec2 _424;
    /* 0x42C */ f32 _42c;
    /* 0x430 */ u8 _430;
    /* 0x431 */ u8 _431;
    /* 0x434 */ s32 _434;
    /* 0x438 */ f32 _438;
    /* 0x43C */ f32 _43c;
    /* 0x440 */ f32 _440;
    /* 0x444 */ f32 _444;
    /* 0x448 */ u8 _448;
    /* 0x44C */ s32 _44c;
    /* 0x450 */ f32 _450;
};

extern Unk8063F410 *lbl_8063F410;

void fn_80032FE8();
void fn_8003301C();
void fn_80033020();
Unk80033090 *fn_80033088();
Unk80033090 *fn_80033090(Unk80033090 *p);
void fn_80033488(Unk80033090 *p);
void fn_80033494(Unk80033090 *p);
void fn_800334A0(Unk80033090 *p, f32 t);
Unk80035380 *fn_80033B7C(Unk80033090 *p, u32 i);
s32 fn_80033B98(Unk80033090 *p, u32 id);
void fn_80033C0C(Unk80033090 *p);
void fn_80033C6C(Unk80033090 *p);
void fn_800340D0(Unk80033090 *p, f32 x0, f32 y0, f32 x1, f32 y1);
void fn_80034170(Unk80033090 *p, f32 v);
void fn_80034280(Unk80033090 *p, f32 v);
void fn_80034390(Unk80033090 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, s32 x);
void fn_80034494(Unk80033090 *p, f32 v, f32 t, s32 x);
void fn_8003452C(Unk80033090 *p, f32 v, f32 t, s32 x);
void fn_800345C4(Unk80033090 *p, void *a, s32 b, f32 x, f32 y);
void fn_80034630(Unk80033090 *p, void *a, s32 b, f32 x, f32 y);
void fn_8003469C(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
void fn_800347BC(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
void fn_800348BC(Unk80033090 *p, s32 mode);
void fn_80034918();
s32 fn_80034930(Unk80033090 *p);
void fn_800349B4(Unk80033090 *p);
void fn_80034A00(Unk80033090 *p);
void fn_80034A38(Unk80033090 *p, s32 v);
void fn_80034AB8(Unk80033090 *p, f32 v);
void fn_80034B10(Unk80033090 *p, GXColor *color);
void fn_80034B34(Unk80033090 *p, f32 a, f32 b);
void fn_80034B40(Unk80033090 *p, f32 a);
void fn_80034B48(Unk80033090 *p, f32 a, f32 b);
void fn_80034B54(Unk80033090 *p, s32 mode, GXColor *target, s32 x);
void fn_80034BA0(Unk80033090 *p, f32 a, f32 b, s32 mode, s32 x, f32 t);
void fn_80034C30(Unk80033090 *p, f32 a, s32 mode, s32 x, f32 t);
void fn_80034C88(Unk80033090 *p, f32 a, f32 b, s32 mode, s32 x, f32 t);
void fn_80034D18(Unk80033090 *p, f32 a, s32 x, f32 t);
void fn_80034D68(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
void fn_80034E68(Unk80033090 *p, u8 v);
void fn_80034EA0(Unk80033090 *p, f32 v);
void fn_80034EDC(Unk80033090 *p, f32 v, s32 x, f32 t);
void fn_80034F48(Unk80033090 *p);
void fn_80034FA4(Unk80033090 *p, u8 v);
void fn_80034FAC(Unk80033090 *p, f32 v);
void fn_8003500C(Unk80033090 *p, f32 v, s32 x, f32 t);
void fn_80035078(Unk80033090 *p, u8 v);
void fn_80035080(Unk80033090 *p, s32 v);
void fn_800350A0(Unk80033090 *p, u32 v);
void fn_800350B4(Unk80033090 *p, f32 x, f32 y);
void fn_80035148(Unk80033090 *p, f32 v0, f32 v1, s32 x, f32 t);
void fn_80035228(Unk80033090 *p);
void fn_80035278(Unk80033090 *p, u8 v);
void fn_80035280(Unk80033090 *p, f32 v);
void fn_800352AC(Unk80033090 *p, s32 v);
void fn_800352CC(Unk80033090 *p, u32 v);
void fn_800352E0(Unk80033090 *p, u32 v, s32 x, f32 t);
void fn_80035354(f32 *v);
Unk80035380 *fn_80035380(Unk80035380 *p);
u32 fn_800353F4(Unk80035380 *p);
void fn_800353FC(Unk80035380 *p, u32 id);
void fn_800354D8(Unk80035380 *p, Unk800354D8 *rect);
void fn_800354FC(Unk80035380 *p, f32 x0, f32 y0, f32 x1, f32 y1);
void fn_80035628(Unk80035380 *p);
void fn_80035690(Unk80035380 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, s32 x);
void fn_80035828(Unk80035380 *p, f32 t);
void fn_800358C8(Unk80035380 *p);
s32 fn_80035914(Unk80035380 *p);
GScamera *fn_80035970(Unk80035380 *p);
void fn_80035A40(Unk80035380 *p, void *v);
void fn_80035A48(Unk80035380 *p, GSobject *v);
void fn_80035A50(Unk80035380 *p);
void fn_80035AB8(Unk80035380 *p);
