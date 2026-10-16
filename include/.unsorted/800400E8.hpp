#pragma once

#include "gs/GSmath.hpp"

class GScamera;

// A vector copied member by member.
struct Unk80040CAC : public Vec {
    Unk80040CAC &operator=(const Unk80040CAC &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

// size: 0x8
struct Unk800404F8 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
};

struct Unk80040EA4;

// size: 0x78
struct Unk800404A8 {
    /* 0x00 */ u8 _00;
    /* 0x04 */ u32 _04;
    /* 0x08 */ f32 _08;
    /* 0x0C */ f32 _0c;
    /* 0x10 */ s32 _10;
    /* 0x14 */ Unk80040CAC _14;
    /* 0x20 */ Unk80040CAC _20;
    /* 0x2C */ Unk80040CAC _2c;
    /* 0x38 */ Unk80040CAC _38;
    /* 0x44 */ Unk80040CAC _44;
    /* 0x50 */ f32 _50;
    /* 0x54 */ Unk80040EA4 *_54;
    /* 0x58 */ Unk800404F8 _58[4];
};

namespace eftseq {

// Name known from RTTI (instances for float, GSvec and GScolor<unsigned char>).
// size: 0x24
template <typename T>
class AnimNode {
public:
    /* 0x00 */ u32 _00;
    /* 0x04 */ T _04;
    /* 0x08 */ T _08;
    /* 0x0C */ u32 _0c;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1c;

    // TODO Called once per frame; returns whether the value changed.
    /* 0x20 */ virtual s32 fn_80050394(f32 arg0);
};

// Name known from RTTI.
// size: 0x60
class AnimNodeShake : public AnimNode<f32> {
public:
    /* 0x24 */ u8 unk24[0x3C];
};

} // namespace eftseq

// size: 0x6FC
struct Unk80040EA4 {
    /* 0x000 */ u8 _000;
    /* 0x001 */ u8 _001;
    /* 0x002 */ u8 _002;
    /* 0x003 */ u8 _003;
    /* 0x004 */ eftseq::AnimNode<f32> _004[12];
    /* 0x1B4 */ eftseq::AnimNodeShake _1b4[5];
    /* 0x394 */ eftseq::AnimNodeShake _394;
    /* 0x3F4 */ eftseq::AnimNodeShake _3f4;
    /* 0x454 */ eftseq::AnimNodeShake _454;
    /* 0x4B4 */ u32 _4b4;
    /* 0x4B8 */ u32 _4b8;
    /* 0x4BC */ u32 _4bc;
    /* 0x4C0 */ f32 _4c0;
    /* 0x4C4 */ u32 _4c4;
    /* 0x4C8 */ f32 _4c8;
    /* 0x4CC */ f32 _4cc;
    /* 0x4D0 */ f32 _4d0;
    /* 0x4D4 */ u32 _4d4;
    /* 0x4D8 */ f32 _4d8;
    /* 0x4DC */ f32 _4dc;
    /* 0x4E0 */ f32 _4e0;
    /* 0x4E4 */ f32 _4e4;
    /* 0x4E8 */ Unk800404A8 _4e8[4];
    /* 0x6C8 */ f32 _6c8;
    /* 0x6CC */ GScamera *_6cc;
    /* 0x6D0 */ u32 _6d0;
    /* 0x6D4 */ f32 _6d4;
    /* 0x6D8 */ f32 _6d8;
    /* 0x6DC */ f32 _6dc;
    /* 0x6E0 */ f32 _6e0;
    /* 0x6E4 */ f32 _6e4;
    /* 0x6E8 */ f32 _6e8;
    /* 0x6EC */ f32 _6ec;
    /* 0x6F0 */ f32 _6f0;
    /* 0x6F4 */ f32 _6f4;
    /* 0x6F8 */ u8 _6f8;
};

// size: 0x37E4
struct Unk80040274 {
    /* 0x0 */ u8 _0;
    /* 0x4 */ Unk80040EA4 _4[8];
};

void fn_800400E8(Vec *out, Vec *a, Vec *b, f32 t);
void fn_80040134();
void fn_80040174();
void fn_800401A0();
Unk80040274 *fn_800401F4();
void fn_800401FC(Unk80040274 *p, u32 a);
Unk80040274 *fn_80040274(Unk80040274 *p);
u32 fn_800402D4(Unk80040274 *p);
void fn_80040358(Unk80040274 *p, u32 id);
Unk80040EA4 *fn_80040384(Unk80040274 *p, u32 id);
void fn_800403B0(Unk80040274 *p, f32 t);
void fn_80040434(Unk80040274 *p);
void fn_800404A8(Unk800404A8 *c, Unk80040EA4 *owner);
int fn_800404F8(Unk800404A8 *c, int i, Vec *out);
void fn_80040580(Unk800404A8 *c);
void fn_80040588(Unk800404A8 *c, int force);
f32 fn_800407B0(Unk800404A8 *c);
void fn_80040928(Unk800404A8 *c, Vec *v);
void fn_80040950(Unk800404A8 *c);
int fn_80040960(Unk800404A8 *c, Vec *out, Vec *in);
void fn_80040AE0(Unk800404A8 *c, u32 a, u32 b, Vec *v);
void fn_80040B10(Unk800404A8 *c, Vec *v);
void fn_80040B38(Unk800404A8 *c, u32 a, u32 b, u32 a2, u32 b2, f32 f, Vec *v);
u32 fn_80040B7C(Unk800404A8 *c, int i);
void fn_80040BA4(Unk800404A8 *c, int mode);
void fn_80040BE4(Unk800404A8 *c, Vec *v);
f32 fn_80040C38(Unk800404A8 *c);
void fn_80040CAC(Unk800404A8 *d, Unk800404A8 *a, Unk800404A8 *b, f32 t);
void fn_80040E48(Unk800404A8 *c, u32 id);
Unk80040EA4 *fn_80040EA4(Unk80040EA4 *e);
void fn_80040FA0(Unk80040EA4 *e);
void fn_80041064(Unk80040EA4 *e);
void fn_80041070(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_800410AC(Unk80040EA4 *e, Vec *v);
void fn_800410BC(Unk80040EA4 *e, Vec *v);
void fn_8004111C(Unk80040EA4 *e, f32 x, f32 y, f32 d);
Vec *fn_80041204(Unk80040EA4 *e);
void fn_8004120C(Unk80040EA4 *e, f32 f);
void fn_8004121C(Unk80040EA4 *e);
void fn_80041228(Unk80040EA4 *e, Unk800404A8 *c);
f32 fn_80041524(Unk80040EA4 *e, Unk800404A8 *c);
void fn_80041690(Unk80040EA4 *e, f32 a, f32 b, f32 c, u32 x, u32 y);
void fn_800416E8(Unk80040EA4 *e, f32 a, f32 b, f32 c);
void fn_8004173C(Unk80040EA4 *e, f32 b, f32 c, u32 x);
void fn_80041794(Unk80040EA4 *e, f32 b, f32 c, u32 y);
void fn_800417E8(Unk80040EA4 *e, f32 a, f32 b, f32 c);
void fn_800418AC(Unk80040EA4 *e, u32 flags);
void fn_80041950(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_8004198C(Unk80040EA4 *e, u32 a, u32 b, Vec *v);
void fn_800419E4(Unk80040EA4 *e, Vec *v);
void fn_80041A88(Unk80040EA4 *e, f32 f1, f32 f2, f32 f3);
void fn_80041AE0(Unk80040EA4 *e, u32 a, u32 b);
void fn_80041AF8(Unk80040EA4 *e, u32 a, u32 b);
void fn_80041B10(Unk80040EA4 *e, u32 a, u32 b);
void fn_80041B28(Unk80040EA4 *e, u32 a, u32 b);
void fn_80041B40(Unk80040EA4 *e, u32 a, u32 b);
void fn_80041B58(Vec *out, Unk80040EA4 *e, f32 a, f32 b, f32 c);
void fn_80041ED4(Vec *pos, Vec *center);
void fn_8004215C(Unk80040EA4 *e, f32 f1, f32 f2, f32 f3);
void fn_800421F0(Unk80040EA4 *e, f32 a, f32 b, f32 c);
void fn_8004231C(Unk80040EA4 *e, u32 x, f32 f1, f32 f2, f32 f3, f32 f4);
void fn_800423D8(Unk80040EA4 *e, u32 x, f32 a, f32 b, f32 c, f32 d);
void fn_80042534(Unk80040EA4 *e, Vec *v);
Vec *fn_80042590(Unk80040EA4 *e);
void fn_800425AC(Unk80040EA4 *e, u32 a, u32 b, Vec *v);
void fn_800425FC(Unk80040EA4 *e, f32 f);
void fn_800426CC(Unk80040EA4 *e, f32 f);
f32 fn_80042708(Unk80040EA4 *e);
void fn_80042710(Unk80040EA4 *e, f32 a, f32 b, u32 x);
f32 fn_8004274C(Unk80040EA4 *e);
f32 fn_80042794(Unk80040EA4 *e);
void fn_8004279C(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_8004283C(Unk80040EA4 *e, Vec *v, u32 x, f32 f);
f32 fn_80042950(Unk80040EA4 *e, f32 a, f32 b);
void fn_80042A0C(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_80042A84(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_80042B34(Unk80040EA4 *e, f32 a, f32 b, f32 c, u32 x);
void fn_80042CB0(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_80042DC0(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_80042EA8(Unk80040EA4 *e, f32 f, Vec *src, u32 x);
void fn_80042F60(Unk80040EA4 *e, f32 a, f32 b, u32 x);
void fn_80042FCC(Unk80040EA4 *e, u32 a, u32 b, f32 f, f32 g, Vec *v);
void fn_80043310(Unk80040EA4 *e, u32 a, u32 b, u32 a2, u32 b2, f32 f, f32 g, Vec *v);
void fn_8004363C(Unk80040EA4 *e, u32 a, u32 b, f32 f, f32 g, Vec *v);
void fn_80043988(Unk80040EA4 *e);
f32 fn_800439EC(Unk80040EA4 *e, u32 obj, int kind);
f32 fn_80043B10(Unk80040EA4 *e, int i);
void fn_80043B60(Unk80040EA4 *e, f32 v);
void fn_80043B68(Unk80040EA4 *e, f32 t);
void fn_8004449C(Unk80040EA4 *e);
u32 fn_800444A0(Unk80040EA4 *e);
int fn_80044554(Unk80040EA4 *e, Vec *in, Vec *out);
void fn_80044770(Unk80040EA4 *e, u32 id);
