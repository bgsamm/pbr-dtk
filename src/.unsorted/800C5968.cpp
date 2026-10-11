#include ".unsorted/800C5968.hpp"
#include ".unsorted/800B9E10.hpp"
#include "ds/pokemon.hpp"

#include "common.hpp"

#pragma optimize_for_size on

extern "C" {

extern u8 lbl_8063EEF0;

void fn_800D149C(u8 v) { lbl_8063EEF0 = v; }
void fn_800D2A1C(void) {}

}

#include <revolution/os/OSFastCast.h>

extern "C" {

f32 fn_800D64BC(s16 v) { return __OSs16tof32(&v); }
f32 fn_800D64D0(u16 v) { return __OSu16tof32(&v); }
u16 fn_800D64E4(f32 v) { return __OSf32tou16(v); }

void fn_800D64F8(u8* p, u8 a, u8 b, u8 c, u8 d) {
    p[0] = a;
    p[1] = b;
    p[2] = c;
    p[3] = d;
}

struct Float8 { f32 a, b, c, d, e, f, g, h; };
void fn_800D650C(Float8* d, const Float8* s) {
    d->a = s->a; d->b = s->b; d->c = s->c; d->d = s->d;
    d->e = s->e; d->f = s->f; d->g = s->g; d->h = s->h;
}


struct Byte88 { u8 b[0x88]; };
struct Byte8C { Byte88 a; u8 b, c, d, e; };
void fn_800D13B4(Byte8C* d, const Byte8C* s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
}

void fn_8015C4F4(int, int);
void fn_800D13FC(void) {
    switch (lbl_8063EEF0) {
    case 1: fn_8015C4F4(3, 0x30b7); break;
    case 2: fn_8015C4F4(4, 0x30bf); break;
    case 3: fn_8015C4F4(4, 0x30c0); break;
    case 4: fn_8015C4F4(4, 0x30c1); break;
    case 5: fn_8015C4F4(4, 0x30c2); break;
    case 6: fn_8015C4F4(4, 0x30c3); break;
    case 7: fn_8015C4F4(3, 0x30c4); break;
    case 8: fn_8015C4F4(4, 0x30c5); break;
    case 9: fn_8015C4F4(4, 0x30c6); break;
    case 10: fn_8015C4F4(4, 0x30c7); break;
    }
}

}

extern "C" {

struct Flags7 { u32 pad : 7; u32 flag : 1; };
Flags7* fn_8011C974(void);
u32 fn_80162A90(int);
void fn_80059A6C(void*, void*, int, int);

#pragma optimize_for_size on
void fn_800D7BF8(void* a, void* b) {
    Flags7* f = fn_8011C974();
    int r = 0;
    if (fn_80162A90(0x261) == 2 && f->flag && fn_80162A90(0x265) != 0) {
        r = 1;
    }
    fn_80059A6C(a, b, r, 1);
}
#pragma optimize_for_size reset

struct Sub1638 {
    u32 x0;
    u8 pad4[0x60];
    u32 x64;
    u8 pad68[0xa36 - 0x68];
    u8 xa36;
    u8 xa37;
    u8 xa38;
};
struct Obj1638 {
    u8 pad[0x1638];
    Sub1638* p;
};

void fn_800D642C(Obj1638* o, int a, int b, int c) {
    if (a) {
        o->p->xa36 = 1;
    } else {
        o->p->xa36 = 0;
    }
    if (b) {
        o->p->xa37 = 1;
    } else {
        o->p->xa37 = 0;
    }
    if (c) {
        o->p->xa38 = 1;
    } else {
        o->p->xa38 = 0;
    }
    o->p->x64 |= 4;
    o->p->x0 |= 0x40;
}

void fn_80253EDC(void*, void*, int, void*);
void fn_80059A3C(int, void*);

struct Rect6 { f32 v[11]; };

void fn_800D755C(void* a, void* b) {
    int type;
    Rect6 buf;
    fn_80253EDC(a, b, 3, &type);
    switch (type) {
    case 1:
        fn_80253EDC(a, b, 6, &buf);
        fn_80059A3C(1, &buf);
        break;
    case 2:
        fn_80253EDC(a, b, 6, &buf);
        fn_80059A3C(2, &buf);
        break;
    }
}

struct CopyPair { u32 a, b; };
struct Copy80 {
    u16 a, b;
    u8 c, d, e, f;
    u32 g0, g1, g2, g3, g4, g5, g6, g7;
    CopyPair h[4];
    u32 i, j, k;
    CopyPair l[4];
    CopyPair m;
    u32 o;
};
void fn_800CAC0C(Copy80* d, const Copy80* s) { *d = *s; }

}

extern "C" {

struct HiBits { u8 hi : 7; u8 lo : 1; };
extern HiBits lbl_8047CE18[];
int fn_800BA7EC(int);
void* fn_800E5DEC(u8, u8);
int fn_80056BD4(void*);
int fn_80056E2C(void*);

void* fn_800D75FC(void* self, u32* idx, int dir) {
    u32 i = *idx;
    void* r;
    u8 k = fn_800BA7EC(0) * 4 + (3 - (0x12 - fn_800BA7EC(9)));
    if (dir) {
        do {
            if (i == 0) {
                i = 6;
            }
            i--;
            r = fn_800E5DEC(i, lbl_8047CE18[k].hi);
        } while (!fn_80056BD4(r) || fn_80056E2C(r));
        *idx = i;
        return r;
    } else {
        do {
            i++;
            if (i == 6) {
                i = 0;
            }
            r = fn_800E5DEC(i, lbl_8047CE18[k].hi);
        } while (!fn_80056BD4(r) || fn_80056E2C(r));
        *idx = i;
        return r;
    }
}

extern Float8 lbl_80416B58;
extern f32 lbl_806410C4;
void fn_80253F04(void*, void*, int, void*);
void* fn_8005CB24(void*, int, void*);
struct Buf28 { u8 b[0x24]; };
struct Rect8 { f32 v[8]; };

#pragma dont_inline on
void fn_800D740C(void* a, void* b) {
    Buf28 buf;
    struct {
        int type;
        Rect8 rect;
    } t;
    fn_80253EDC(a, b, 3, &t.type);
    fn_80253EDC(a, b, 6, &t.rect);
    switch (t.type) {
    case 0:
        fn_800D650C(&lbl_80416B58, (Float8*)&t.rect);
        if (lbl_806410C4 == t.rect.v[0] && lbl_806410C4 == t.rect.v[4]) {
            fn_80253F04(a, b, 2, 0);
        } else {
            u8 x = lbl_8047CE18[fn_800BA7EC(0xb)].hi;
            void* r = fn_800E5DEC(fn_800BA7EC(0xc), x);
            fn_80253F04(a, b, 2, fn_8005CB24(r, 0, &buf));
            fn_80253F04(a, b, 1, &buf);
        }
        break;
    case 1:
        if (t.rect.v[0] <= lbl_806410C4 && t.rect.v[4] <= lbl_806410C4) {
            fn_80253F04(a, b, 2, 0);
        }
        break;
    }
}
#pragma dont_inline reset

}

extern "C" {

struct Blk1FC { u32 w[0x7f]; };
struct Blk348 { u8 b[0x348]; };
struct BlkB8 { u32 w[0x2e]; };
struct BlkC0 { u16 h[0x60]; };
struct Blk8W { u32 w[2]; };
struct Blk8B { u8 b[8]; };
struct Copy6EC {
    Blk1FC a;
    Blk348 b;
    u8 c, d;
    BlkB8 e;
    u32 f;
    BlkC0 g;
    Blk8W h;
    u32 i;
    Blk8B j;
    u8 k, l;
    u32 m, n;
    u8 o, p, q, r, s, t, u, v;
};
void fn_800CAAA0(Copy6EC* d, const Copy6EC* s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
    d->f = s->f;
    d->g = s->g;
    d->h = s->h;
    d->i = s->i;
    d->j = s->j;
    d->k = s->k;
    d->l = s->l;
    d->m = s->m;
    d->n = s->n;
    d->o = s->o;
    d->p = s->p;
    d->q = s->q;
    d->r = s->r;
    d->s = s->s;
    d->t = s->t;
    d->u = s->u;
    d->v = s->v;
}

struct MsgObj {
    u8* p;
    u8 x4, x5, x6, x7;
    u8 x8, x9;
};
struct Arg5 { u8 pad[5]; u8 x5; };
extern u8 lbl_8047D1D8[];
void fn_80253E8C(void*, void*, int, void*);
void fn_80253EB4(void*, void*, int, int);
void fn_802503D8(int, u8*);

void fn_800D2A20(void* a, Arg5* b) {
    u32 type;
    MsgObj* tmp;
    MsgObj* o;
    fn_80253E8C(a, b, 3, &type);
    switch (type) {
    case 8:
        fn_80253E8C(a, b, 5, &tmp);
        o = tmp;
        o->p = lbl_8047D1D8;
        if (fn_800BA578() == 3) {
            fn_802503D8(0x2d38, o->p);
        } else {
            fn_802503D8(0x2d36, o->p);
        }
        o->x6 = 0xff;
        o->x5 = 0xff;
        o->x4 = 0xff;
        o->x7 = b->x5;
        o->x9 = 0x84;
        fn_80253EB4(a, b, 2, -2);
        break;
    case 10:
        fn_80253E8C(a, b, 5, &tmp);
        o = tmp;
        o->p = lbl_8047D1D8 + 0x40;
        if (fn_800BA578() == 3) {
            fn_802503D8(0x2d39, o->p);
        } else {
            fn_802503D8(0x2d37, o->p);
        }
        o->x6 = 0xff;
        o->x5 = 0xff;
        o->x4 = 0xff;
        o->x7 = b->x5;
        o->x9 = 0x84;
        fn_80253EB4(a, b, 2, -2);
        break;
    case 3:
        if (fn_800BA578() == 3) {
            fn_80253EB4(a, b, 2, 0x2d30);
        } else {
            fn_80253EB4(a, b, 2, 0x2d31);
        }
        break;
    case 5:
        fn_800BA578();
        fn_80253EB4(a, b, 2, 0x2d2f);
        break;
    }
}

}

extern "C" {

extern Rect8 lbl_80416AB8[];

void fn_800D6DA8(void* a, void* b) {
    int type;
    s8 x, y, z;
    fn_80253EDC(a, b, 3, &type);
    if (fn_800BA578() == 13) {
        x = fn_800BA7EC(0x12) + 1;
        y = ((u32)fn_800BA7EC(0x13) + 3) / 4;
        z = fn_800BA7EC(0x13);
    } else {
        x = fn_800BA7EC(0) + 1;
        y = ((u32)fn_800BA7EC(1) + 3) / 4;
        z = fn_800BA7EC(1);
    }
    if (x == y) {
        x = z % 4;
    } else {
        x = 0;
    }
    switch (type) {
    case 9:
        fn_80253EDC(a, b, 6, &lbl_80416AB8[1]);
        fn_80059A3C(0x14, &lbl_80416AB8[1]);
        break;
    case 10:
        fn_80253EDC(a, b, 6, &lbl_80416AB8[2]);
        if (x > 1 || x == 0) {
            fn_80059A3C(0x15, &lbl_80416AB8[2]);
        }
        break;
    case 11:
        fn_80253EDC(a, b, 6, &lbl_80416AB8[3]);
        if (x > 2 || x == 0) {
            fn_80059A3C(0x16, &lbl_80416AB8[3]);
        }
        break;
    case 12:
        fn_80253EDC(a, b, 6, &lbl_80416AB8[4]);
        if (x == 0) {
            fn_80059A3C(0x17, &lbl_80416AB8[4]);
        }
        break;
    }
}

}

class GSrender {
public:
    static GSrender* sInstance;
    u8 pad0[0x59];
    u8 m59;
    u8 pad5A[0xa0 - 0x5a];
    f64 mA0;
};

extern "C" {

extern f32 lbl_80641078;
extern f32 lbl_80641058;
extern f32 lbl_80641064;
extern f32 lbl_80641070;
extern f32 lbl_80641038;
extern f32 lbl_8064107C;
extern Rect8 lbl_8047D5D8;
void fn_80253E4C(void*, int, void*);
s16 fn_800BA98C(int);
u16 fn_80253DE0(s16);
void fn_80059A54(int, Rect8*);
void fn_80253E10(void*, int, f32);
double cos(double);

void fn_800D1BB4(void* a) {
    f32 y, x;
    GSrender* r = GSrender::sInstance;
    f32 t = (f32)(r->mA0 / r->m59 - lbl_8063EED8->_00) / 0.25f;
    int flag;
    fn_80253E4C(a, 8, &flag);
    if (flag == 0) {
        return;
    }
    if (fn_80253DE0(fn_800BA98C(0)) == 0) {
        fn_80059A54(1, &lbl_8047D5D8);
    }
    switch (fn_80253DE0(fn_800BA98C(0xc))) {
    case 1:
        fn_80059A54(2, &lbl_8047D5D8);
        break;
    case 0:
        fn_80059A54(3, &lbl_8047D5D8);
        break;
    case 5:
        fn_80059A54(7, &lbl_8047D5D8);
        break;
    case 6:
        fn_80059A54(8, &lbl_8047D5D8);
        break;
    case 7:
        fn_80059A54(9, &lbl_8047D5D8);
        break;
    }
    int n = 0x15;
    switch (fn_80253DE0(fn_800BA98C(0xf))) {
    case 6:
        n = 0x16;
    case 5:
        n++;
    case 4:
        n++;
    case 3:
        n++;
    case 2:
        n++;
    case 1:
        fn_80059A54(n, &lbl_8047D5D8);
        break;
    }
    x = (lbl_8047D5D8.v[1] + lbl_8047D5D8.v[0]) / 2;
    y = -(lbl_8047D5D8.v[6] + lbl_8047D5D8.v[4]) / 2 + (lbl_80416B58.g - lbl_80416B58.e);
    if (fn_800BA5CC() == 0x13) {
        x += 480.0f * (1.0f - (f32)cos(0.017453292f * (90.0f * t)));
    }
    fn_80253E10(a, 3, x);
    fn_80253E10(a, 4, y);
}

}

extern "C" {

struct DrawObj {
    u8 pad[0xe];
    u8 xe, xf, x10, x11;
};
u8 fn_800E644C(void);
void fn_80250134(int, int, int, s16, s16, u32);

void fn_800D6F90(void* a, DrawObj* b) {
    struct {
        int type;
        Rect8 r;
    } t;
    u32 col;
    fn_80253EDC(a, b, 3, &t.type);
    switch (t.type) {
    case 4:
        if ((fn_800BA7EC(4) & 1) && fn_80162A90(0x18) != 1) {
            b->x10 = 0x80;
            b->xf = 0x80;
            b->xe = 0x80;
        }
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xd, &t.r);
        break;
    case 6:
        if ((fn_800BA7EC(4) & 2) && fn_80162A90(0x18) != 2) {
            b->x10 = 0x80;
            b->xf = 0x80;
            b->xe = 0x80;
        }
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xe, &t.r);
        break;
    case 8:
        switch (fn_800E644C()) {
        case 0:
        case 2:
            if (fn_80162A90(0x261) != 2) {
                fn_80253F04(a, b, 2, 0);
                return;
            }
        }
        if ((fn_800BA7EC(4) & 4) && fn_80162A90(0x18) != 3) {
            b->x10 = 0x80;
            b->xf = 0x80;
            b->xe = 0x80;
        }
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xf, &t.r);
        break;
    case 5:
        fn_80253EDC(a, b, 6, &t.r);
        if ((fn_800BA7EC(4) & 1) && fn_80162A90(0x18) != 1) {
            col = 0x40404000 | b->x11;
        } else {
            col = 0xFFFFFF00 | b->x11;
        }
        fn_80250134(0x2cf6, t.r.v[0], t.r.v[4], t.r.v[1] - t.r.v[0], t.r.v[6] - t.r.v[4], col);
        break;
    case 7:
        fn_80253EDC(a, b, 6, &t.r);
        if ((fn_800BA7EC(4) & 2) && fn_80162A90(0x18) != 2) {
            col = 0x40404000 | b->x11;
        } else {
            col = 0xFFFFFF00 | b->x11;
        }
        fn_80250134(0x2cf7, t.r.v[0], t.r.v[4], t.r.v[1] - t.r.v[0], t.r.v[6] - t.r.v[4], col);
        break;
    case 9:
        switch (fn_800E644C()) {
        case 0:
        case 2:
            if (fn_80162A90(0x261) != 2) {
                fn_80253F04(a, b, 2, 0);
                return;
            }
        }
        fn_80253EDC(a, b, 6, &t.r);
        if ((fn_800BA7EC(4) & 4) && fn_80162A90(0x18) != 3) {
            col = 0x40404000 | b->x11;
        } else {
            col = 0xFFFFFF00 | b->x11;
        }
        fn_80250134(0x2cf8, t.r.v[0], t.r.v[4], t.r.v[1] - t.r.v[0], t.r.v[6] - t.r.v[4], col);
        break;
    case 10:
        if (fn_80162A90(0x18) != 1) {
            fn_80253F04(a, b, 2, 0);
        }
        break;
    case 11:
        if (fn_80162A90(0x18) != 2) {
            fn_80253F04(a, b, 2, 0);
        }
        break;
    case 12:
        if (fn_80162A90(0x18) != 3) {
            fn_80253F04(a, b, 2, 0);
        }
        break;
    }
}

}

extern "C" {

extern f32 lbl_8064105C;
u8 fn_800E5224(int, u8);
void* fn_8005AC60(int, u32);
int fn_802502F4(int);
void fn_802501AC(int, int, int, int, s16, s16, u32);
int fn_800E5630(int, int, u8);
void fn_8015C308(int, void*);
u16 fn_80250398(int, int, int);
u16 fn_80058BFC(int, int, u32);
u16 fn_80058BCC(u16);
struct Obj5E8 { u8 pad[0x5e8]; void* x5e8; };
Obj5E8* fn_800E5AD0(u8);

void fn_800D6550(void* a, DrawObj* b) {
    int k = 0;
    int type;
    u16 str[4];
    Rect8 c;
    Rect8 r;
    void* res;
    u8 id;
    switch (fn_800BA7EC(9)) {
    case 0xf:
        break;
    case 0x10:
        k = 1;
        break;
    case 0x11:
        k = 2;
        break;
    case 0x12:
        k = 3;
        break;
    }
    id = lbl_8047CE18[k + fn_800BA7EC(0) * 4].hi;
    fn_80253EDC(a, b, 3, &type);
    switch (type) {
    case 1:
        c.v[6] = lbl_80641038;
        c.v[0] = lbl_80641038;
        c.v[4] = lbl_8064105C;
        c.v[2] = lbl_8064105C;
        c.v[3] = lbl_8064105C;
        c.v[1] = lbl_8064105C;
        c.v[7] = lbl_80641038;
        c.v[5] = lbl_80641038;
        switch (fn_800E5224(2, id)) {
        case 0:
        case 1:
            res = fn_8005AC60(0x3f4, 0x27BE0C00);
            break;
        case 2:
        case 3:
            res = fn_8005AC60(0x3f4, 0x27BD0C00);
            break;
        }
        fn_80253F04(a, b, 2, res);
        fn_80253F04(a, b, 1, &c);
        break;
    case 2:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_802502F4(0x2d3a), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 4:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_802502F4(0x2d3b), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 9:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_802502F4(0x2d3d), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 7:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_802502F4(0x2d3c), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 12:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_802502F4(0x2d3e), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 3:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_800E5630(9, 0, id), 1, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 5: {
        u16* p = (u16*)fn_800E5630(0xa, 0, id);
        u16* q = (u16*)fn_800E5630(0xb, 0, id);
        u16 n;
        int x, y;
        fn_80253EDC(a, b, 6, &r);
        x = r.v[0];
        y = r.v[4];
        if (p[0] == 0x3f || p[0] == 0xff1f) {
            fn_80250134(0x552c, x, y, 0, 0, b->x11);
            break;
        }
        if (p[0] < 0xff10) {
            if (p[1] != 0) {
                n = (p[0] - 0x30) * 10 + p[1] - 0x30;
            } else {
                n = p[0] - 0x30;
            }
        } else {
            if (p[1] != 0) {
                n = (p[0] - 0xff10) * 10 + (p[1] - 0xff10);
            } else {
                n = p[0] - 0xff10;
            }
        }
        str[3] = 0;
        str[2] = 0;
        str[1] = 0;
        if (q[0] < 0xff10) {
            str[0] = q[0];
            str[1] = q[1];
        } else {
            str[0] = q[0] - 0xfee0;
            if (q[1] != 0) {
                str[1] = q[1] - 0xfee0;
            }
        }
        fn_8015C308(0xf, str);
        fn_80250134(0x3f9, x, y, 0, 0, b->x11);
        x += fn_80250398(0x3f9, 1, 0);
        x += fn_80058BFC(x, y, b->x11);
        fn_80250134(fn_80058BCC(n), x, y, 0, 0, b->x11);
        break;
    }
    case 8:
        fn_80253EDC(a, b, 6, &r);
        fn_8015C308(0x17, fn_800E5AD0(id)->x5e8);
        fn_80250134(0x2d42, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 10:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_800E5630(0xc, 0, id), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 11:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_800E5630(0xd, 0, id), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    case 13:
        fn_80253EDC(a, b, 6, &r);
        fn_802501AC(fn_800E5630(0xe, 0, id), 2, r.v[0], r.v[4], r.v[1] - r.v[0], r.v[6] - r.v[4], b->x11);
        break;
    }
}

}

extern "C" {

struct FObj24 { f32 x0, x4, x8, xc; };
struct Arg2508 {
    u8 pad[5];
    u8 x5;
    u8 pad6[0x24 - 6];
    FObj24* x24;
};
struct Obj1D0 {
    u8 pad[0x1c];
    u16 x1c;
    u8 pad1e[0x1d0 - 0x1e];
    u8 name[1];
};
extern u8 lbl_8063CE34[];
extern f32 lbl_8064106C;
extern f32 lbl_80641080;
u16 fn_80391F94(void*, u32);

static inline void SetX4XC(Arg2508* b, f32 x, f32 y) {
    b->x24->x4 = x;
    b->x24->xc = y;
}

void fn_800D2508(int a, Arg2508* b) {
    u8 slot;
    u8 base;
    base = fn_800BA7EC(0) * 4;
    slot = fn_800BA7EC(2);
    s8 idx;
    int type;
    MsgObj* tmp;
    MsgObj* o;
    u8* buf;
    if (fn_800BA578() == 0xd && fn_800BA5CC() != 0x14) {
        return;
    }
    fn_80253E8C((void*)a, b, 3, &type);
    if ((fn_800BA578() == 2 && fn_800BA5CC() != 8) || (fn_800BA578() == 0xd && fn_800BA5CC() == 0x14) ||
        fn_800BA578() == 9 || fn_800BA578() == 3) {
        if (a == fn_800BA98C(0xf)) {
            slot = 0;
            idx = 3 - (0x12 - fn_800BA7EC(9));
        } else if (a == fn_800BA98C(0x10)) {
            slot = 1;
            idx = 4 - (0x12 - fn_800BA7EC(9));
        } else if (a == fn_800BA98C(0x11)) {
            slot = 2;
            idx = 2 - (0x12 - fn_800BA7EC(9));
            if (idx + base < 0) {
                idx = 0;
            }
        }
    } else {
        if (a == fn_800BA98C(0xf)) {
            idx = 0;
            slot = 0;
        } else if (a == fn_800BA98C(0x10)) {
            idx = 1;
            slot = 1;
        } else if (a == fn_800BA98C(0x11)) {
            idx = 2;
            slot = 2;
        } else if (a == fn_800BA98C(0x12)) {
            idx = 3;
            slot = 3;
        } else if (a == fn_800BA98C(0x13)) {
            int hi = slot & 0x80;
            slot = 4;
            if (hi) {
                idx = 4;
            } else if (base != 0) {
                idx = -4;
            }
        } else if (a == fn_800BA98C(0x14)) {
            int hi = slot & 0x80;
            slot = 5;
            if (hi) {
                idx = 5;
            } else if (base != 0) {
                idx = -3;
            }
        } else if (a == fn_800BA98C(0x15)) {
            int hi = slot & 0x80;
            slot = 6;
            if (hi) {
                idx = 6;
            } else if (base != 0) {
                idx = -2;
            }
        } else if (a == fn_800BA98C(0x16)) {
            int hi = slot & 0x80;
            slot = 7;
            if (hi) {
                idx = 7;
            } else if (base != 0) {
                idx = -1;
            }
        }
    }
    buf = lbl_8047D1D8 + slot * 0x40;
    idx = idx + base;
    switch (type) {
    case 2:
        fn_80253E8C((void*)a, b, 5, &tmp);
        o = tmp;
        o->p = buf;
        fn_8015C308(0x57, (void*)fn_800E5630(0, 0, lbl_8047CE18[idx].hi));
        fn_802503D8(0x2db5, o->p);
        if (lbl_8047CE18[idx].lo) {
            o->x6 = 0x80;
            o->x5 = 0x80;
            o->x4 = 0x80;
        } else {
            o->x6 = 0xff;
            o->x5 = 0xff;
            o->x4 = 0xff;
        }
        o->x7 = b->x5;
        o->x9 = 5;
        fn_80253EB4((void*)a, b, 2, -2);
        break;
    case 1: {
        b->x24->x4 = 10.0f;
        b->x24->xc = 21.0f;
        fn_80253E8C((void*)a, b, 5, &tmp);
        o = tmp;
        o->p = lbl_8047D1D8 + (slot + 8) * 0x40;
        Obj1D0* q = (Obj1D0*)fn_800E5AD0(lbl_8047CE18[idx].hi);
        void* pk = fn_800E5DEC(0, lbl_8047CE18[idx].hi);
        switch (q->x1c) {
        case 0x2b42:
        case 0x2b7e:
        case 0x2bba:
        case 0x2bf6:
        case 0x2c32:
        case 0x2c6e:
            fn_8015C308(0x15, (void*)fn_802502F4(fn_80391F94(lbl_8063CE34 + 0x10, BoxPokemon_GetValue((BoxPokemon *)pk, MON_DATA_SPECIES, NULL))));
            break;
        }
        if (q->x1c != 0xffff) {
            fn_802503D8(q->x1c, o->p);
        } else {
            fn_802503D8((int)q->name, o->p);
        }
        if (lbl_8047CE18[idx].lo) {
            o->x6 = 0x80;
            o->x5 = 0x80;
            o->x4 = 0x80;
        } else {
            o->x6 = 0xff;
            o->x5 = 0xff;
            o->x4 = 0xff;
        }
        o->x7 = b->x5;
        o->x9 = 5;
        fn_80253EB4((void*)a, b, 2, -2);
        break;
    }
    }
}

}

extern "C" {

struct PkmFlag {
    u8 pad[0x8a];
    u8 flag : 1;
    u8 rest : 7;
};
extern u16 lbl_8063EEEE;
extern u32 lbl_8041BFE0[];
u8 fn_80056F68(void*, int);
u32 fn_8005A9F8(u32);
u8 fn_80056A5C(void*);

static inline void fn_800D1E50_sub(void* a, void* b, int type, PkmFlag* p) {
    switch (type) {
    case 0x13:
        fn_80253EB4(a, b, 1, BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_CHECKSUM_FAILED, NULL) ? 0 : fn_8005A9F8(lbl_8041BFE0[fn_80056F68(p, 0)]));
        break;
    case 0x14: {
        if (fn_80056F68(p, 0) != fn_80056F68(p, 1)) {
            fn_80253EB4(a, b, 1, BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_CHECKSUM_FAILED, NULL) ? 0 : fn_8005A9F8(lbl_8041BFE0[fn_80056F68(p, 1)]));
        }
        break;
    }
    case 0x15:
        break;
    case 0x16:
        switch (fn_80056A5C(p)) {
        case 0:
            fn_80253EB4(a, b, 2, 0xe8d);
            break;
        case 1:
            fn_80253EB4(a, b, 2, 0xe90);
            break;
        }
        break;
    }
}

void fn_800D1E50(void* a, void* b) {
    int type;
    int sel;
    int idx;
    PkmFlag* p;
    PkmFlag* q;
    fn_80253E8C(a, b, 3, &type);
    switch (type) {
    case 0x18:
    case 0x1a:
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x1e:
        if (lbl_8063EEEE & 0x8) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x1f:
        if (lbl_8063EEEE & 0x10) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x21:
        if (lbl_8063EEEE & 0x20) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x22:
        if (lbl_8063EEEE & 0x40) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x24:
        if (lbl_8063EEEE & 0x80) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x26:
        if (lbl_8063EEEE & 0x100) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x28:
        if (lbl_8063EEEE & 0x200) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x2a:
        if (lbl_8063EEEE & 0x400) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x2d:
        if (lbl_8063EEEE & 0x800) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x11:
        if (lbl_8063EEEE & 0x1000) return;
        fn_80253EB4(a, b, 1, 0);
        break;
    case 0x12:
        if (!(lbl_8063EEEE & 0x1000)) return;
        sel = fn_800BA7EC(9);
        idx = fn_800BA7EC(0);
        if (fn_800BA578() == 2 || fn_800BA578() == 9) {
            switch (sel) {
            case 0xf:
                idx = idx * 4 + 1;
                break;
            case 0x10:
                idx = idx * 4 + 2;
                break;
            case 0x11:
                idx = idx * 4 + 3;
                break;
            case 0x12:
                idx = idx * 4 + 4;
                break;
            }
            sel = 0;
            switch (fn_80253DE0(fn_800BA98C(0xf))) {
            case 6:
                sel = 1;
            case 5:
                sel++;
            case 4:
                sel++;
            case 3:
                sel++;
            case 2:
                sel++;
            case 1:
                if (((PkmFlag*)fn_800E5DEC(sel, lbl_8047CE18[idx - 1].hi))->flag) return;
            }
            fn_8015C308(0x17, (void*)idx);
            fn_8015C308(0x18, (void*)fn_800BA7EC(1));
            fn_80253EB4(a, b, 2, 0x2dd0);
        } else if (fn_800BA578() == 0xd) {
            if (fn_800BA5CC() < 0xa || fn_800BA5CC() == 0x16 || fn_800BA5CC() >= 0x18) {
                fn_8015C308(0x17, (void*)(fn_800BA7EC(0x12) + 1));
                fn_8015C308(0x18, (void*)(((u32)fn_800BA7EC(0x13) + 3) / 4));
                fn_80253EB4(a, b, 2, 0x2ce8);
            } else {
                sel = fn_800BA7EC(0xe);
                idx = fn_800BA7EC(0x12) * 4;
                fn_8015C308(0x17, (void*)(idx + sel + 1));
                fn_8015C308(0x18, (void*)fn_800BA7EC(0x13));
                fn_80253EB4(a, b, 2, 0x2dd0);
            }
        } else {
            fn_8015C308(0x17, (void*)(idx + 1));
            fn_8015C308(0x18, (void*)(((u32)fn_800BA7EC(1) + 3) / 4));
            fn_80253EB4(a, b, 2, 0x2ce8);
        }
        break;
    }
    if (fn_800BA578() != 2) return;
    if (!(lbl_8063EEEE & 0x1000)) return;
    sel = fn_800BA7EC(9);
    idx = fn_800BA7EC(0);
    switch (sel) {
    case 0xf:
        idx = idx * 4 + 1;
        break;
    case 0x10:
        idx = idx * 4 + 2;
        break;
    case 0x11:
        idx = idx * 4 + 3;
        break;
    case 0x12:
        idx = idx * 4 + 4;
        break;
    }
    sel = 0;
    switch (fn_80253DE0(fn_800BA98C(0xf))) {
    case 6:
        sel = 1;
    case 5:
        sel++;
    case 4:
        sel++;
    case 3:
        sel++;
    case 2:
        sel++;
    case 1:
        q = (PkmFlag*)fn_800E5DEC(sel, lbl_8047CE18[idx - 1].hi);
        if (!q->flag) return;
        break;
    default:
        return;
    }
    p = q;
    fn_800D1E50_sub(a, b, type, p);
}

}

extern "C" {

struct Rules {
    u8 pad0[8];
    u32 x8;
    u32 xc;
    u32 x10;
    u8 x14;
    u8 pad15[4];
    u8 x19;
    u8 pad1a[0x8a - 0x1a];
    u16 x8a;
    u16 x8c;
    u16 x8e;
    u16 x90;
    u8 pad92[4];
    u16 x96_15 : 1;
    u16 x96_14 : 1;
    u16 x96_rest : 14;
};
int fn_80390988(void*, u32);
u8 fn_800E64BC(int);

void fn_800D7704(void) {
    u8 n;
    u8 count;
    u8 t;
    u8 need;
    u16 flags;
    u16 species[6];
    u16 item[6];
    u8 lv[6];
    Rules* r;
    int ok;
    PkmFlag* p;
    u8 i;
    u8 minLv;
    u8 maxLv;
    r = (Rules*)fn_8011C974();
    if (r->xc == 0 && r->x10 == 0x3f0) {
        return;
    }
    flags = 0;
    n = fn_800BA7EC(1);
    for (t = 0; t < n; t++) {
        maxLv = 0;
        minLv = 100;
        ok = 1;
        need = 0;
        count = 0;
        for (i = 0; i < 6; i++) {
            p = (PkmFlag*)fn_800E5DEC(i, lbl_8047CE18[t].hi);
            species[i] = 0;
            item[i] = 0;
            lv[i] = 0;
            if (p->flag && fn_80056BD4(p) && !fn_80056E2C(p)) {
                u8 l = BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_LEVEL, NULL);
                lv[i] = l;
                if (l > maxLv) {
                    maxLv = l;
                }
                if (l < minLv) {
                    minLv = l;
                }
                need += l;
                count++;
                if (!fn_80390988(lbl_8063CE34 + 4, BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_SPECIES, NULL))) {
                    ok = 0;
                }
                species[i] = BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_SPECIES, NULL);
                item[i] = BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_HELD_ITEM, NULL);
            }
        }
        if (r->xc == 0) {
            u8 m = r->x14;
            need = r->x19;
            if (m == 7) {
                if (maxLv > 5 || !ok) {
                    lbl_8047CE18[t].lo = 1;
                    continue;
                }
            } else if (m == 0xb) {
                need = (r->x8 == 2) ? 1 : 2;
            }
            if (m == 0xd || m == 7) {
                flags = 0x1800;
            }
        } else {
            u8 j, k;
            u32 sum;
            u8 c;
            if (r->x8a > minLv) {
                lbl_8047CE18[t].lo = 1;
                continue;
            }
            if (r->x8c < maxLv) {
                lbl_8047CE18[t].lo = 1;
                continue;
            }
            switch (r->x90) {
            case 0:
                if (r->x8 == 2) {
                    need = 1;
                } else {
                    need = 2;
                }
                break;
            case 7:
                if (r->x8 == 2) {
                    need = 3;
                } else {
                    need = 4;
                }
                break;
            default:
                need = r->x90;
                break;
            }
            for (j = 0; j < 6; j++) {
                for (k = 5; k > j; k--) {
                    if (lv[k - 1] > lv[k]) {
                        u8 tmp = lv[k - 1];
                        lv[k - 1] = lv[k];
                        lv[k] = tmp;
                    }
                }
            }
            sum = 0;
            c = 0;
            for (k = 0; k < 6; k++) {
                sum += lv[k];
                if (lv[k] != 0) {
                    c++;
                }
                if (c == need) {
                    break;
                }
            }
            if (r->x8e < sum) {
                lbl_8047CE18[t].lo = 1;
                continue;
            }
            if (!r->x96_15) {
                flags |= 0x800;
            }
            if (!r->x96_14) {
                flags |= 0x1000;
            }
        }
        if (flags) {
            int dupSpecies = flags & 0x800;
            int dupItem = flags & 0x1000;
            for (i = 0; i < 6; i++) {
                p = (PkmFlag*)fn_800E5DEC(i, lbl_8047CE18[t].hi);
                if (p->flag && fn_80056BD4(p) && !fn_80056E2C(p)) {
                    u8 j;
                    if (dupSpecies) {
                        for (j = 0; j < 6; j++) {
                            if (j != i && species[j] == BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_SPECIES, NULL)) {
                                lbl_8047CE18[t].lo = 1;
                                break;
                            }
                        }
                    }
                    if (dupItem) {
                        for (j = 0; j < 6; j++) {
                            if (j != i) {
                                u16 it = item[j];
                                if (it != 0 && it == BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_HELD_ITEM, NULL)) {
                                    lbl_8047CE18[t].lo = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (count < need || count == 0) {
            lbl_8047CE18[t].lo = 1;
        }
        if (fn_800E644C() == 1 && lbl_8047CE18[t].hi == fn_800E64BC(0)) {
            lbl_8047CE18[t].lo = 1;
        }
    }
}

}

extern "C" {

u8 fn_800E63D0(void);
u16 fn_800F78A4(int);
u8 fn_800E63E4(int);
void* fn_8005697C(void*);

#define GET_TEAM_IDX(i)              \
    i = fn_800BA7EC(0) * 4;         \
    switch (fn_800BA7EC(9)) {       \
    case 0xf:                       \
        break;                      \
    case 0x10:                      \
        i += 1;                     \
        break;                      \
    case 0x11:                      \
        i += 2;                     \
        break;                      \
    case 0x12:                      \
        i += 3;                     \
        break;                      \
    }

#define DRAW(id, col) fn_80250134(id, t.r.v[0], t.r.v[4], t.r.v[1] - t.r.v[0], t.r.v[6] - t.r.v[4], col)
#define DRAW2(id, col) fn_802501AC(id, 1, t.r.v[0], t.r.v[4], t.r.v[1] - t.r.v[0], t.r.v[6] - t.r.v[4], col)
#define WHITE (0xFFFFFF00 | b->x11)
#define GRAY (0x40404000 | b->x11)
#define DIM() \
    b->x10 = 0x80; \
    b->xf = 0x80; \
    b->xe = 0x80
#define SETC()            \
    t.c.v[1] = 0.0f;      \
    t.c.v[0] = 0.0f;      \
    t.c.v[3] = 0.0f;      \
    t.c.v[6] = 0.0f;      \
    t.c.v[5] = 1.0f;      \
    t.c.v[2] = 1.0f;      \
    t.c.v[7] = 1.0f;      \
    t.c.v[4] = 1.0f

void fn_800D2BF4(void* a, DrawObj* b) {
    int sel;
    PkmFlag* p;
    int k;
    int hl = 0;
    int ok = 1;
    u8 idx;
    u32 col;
    int n;
    struct {
        int type;
        Rect8 c;
        Rect8 r;
    } t;
    fn_80253EDC(a, b, 3, &t.type);
    if (fn_800BA578() == 2) {
        switch (fn_800E63D0()) {
        case 0:
            GET_TEAM_IDX(idx);
            if (fn_800F78A4(0) || fn_800F78A4(1)) {
                ok = 0;
            } else {
                u8 i;
                for (i = 0; i < 6; i++) {
                    if (((PkmFlag*)fn_800E5DEC(i, lbl_8047CE18[idx].hi))->flag) {
                        ok = 0;
                        break;
                    }
                }
            }
            break;
        }
    }
    switch (t.type) {
    case 0x1c:
        if (!(lbl_8063EEEE & 1)) {
            b->x10 = 0x40;
            b->xf = 0x40;
            b->xe = 0x40;
            b->x11 = 0.76f * b->x11;
        }
        if (fn_800BA7EC(0x15) && fn_800BA578() == 0) {
            fn_80253F04(a, b, 2, 0);
            break;
        }
        fn_80253EDC(a, b, 6, &t.r);
        if (fn_800BA578() != 1) {
            fn_80059A3C(2, &t.r);
        }
        break;
    case 0x1d:
        if (!(lbl_8063EEEE & 2)) {
            b->x10 = 0x40;
            b->xf = 0x40;
            b->xe = 0x40;
            b->x11 = 0.76f * b->x11;
        }
        if (fn_800BA7EC(0x15) && fn_800BA578() == 0) {
            fn_80253F04(a, b, 2, 0);
            break;
        }
        fn_80253EDC(a, b, 6, &t.r);
        if (fn_800BA578() != 1) {
            fn_80059A3C(3, &t.r);
        }
        break;
    case 0x1e:
        if (!(lbl_8063EEEE & 8)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(4, &t.r);
        break;
    case 0x1f:
        if (!(lbl_8063EEEE & 0x10)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(5, &t.r);
        GET_TEAM_IDX(idx);
        if (fn_800BA578() != 1 && fn_800E63D0()) {
            SETC();
            fn_80253F04(a, b, 2, fn_8005AC60(0x3f4, 0x27570C00));
            fn_80253F04(a, b, 1, &t.c);
        }
        if ((!ok && !fn_800BA7EC(0x15)) || lbl_8047CE18[idx].lo) {
            DIM();
        }
        break;
    case 0x21:
        if (!(lbl_8063EEEE & 0x20)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(6, &t.r);
        break;
    case 0x22:
        if (!(lbl_8063EEEE & 0x40)) return;
        GET_TEAM_IDX(idx);
        if (fn_800E5224(2, lbl_8047CE18[idx].hi)) {
            DIM();
        }
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(7, &t.r);
        break;
    case 0x24:
        if (!(lbl_8063EEEE & 0x80)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(8, &t.r);
        break;
    case 0x26:
        if (!(lbl_8063EEEE & 0x100)) return;
        GET_TEAM_IDX(idx);
        if (fn_800E5224(2, lbl_8047CE18[idx].hi)) {
            DIM();
        }
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(9, &t.r);
        break;
    case 0x28:
        if (!(lbl_8063EEEE & 0x200)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xa, &t.r);
        SETC();
        fn_80253F04(a, b, 2, fn_8005AC60(0x3f4, 0x27560C00));
        fn_80253F04(a, b, 1, &t.c);
        if (lbl_8047CE18[fn_800BA7EC(0xe) + fn_800BA7EC(0x12) * 4].lo) {
            DIM();
        }
        break;
    case 0x29:
        if (!(lbl_8063EEEE & 0x200)) return;
        fn_80253EDC(a, b, 6, &t.r);
        col = WHITE;
        if (fn_800BA578() == 0xd) {
            if ((u32)fn_800BA7EC(0x11) == 1) {
                DRAW(0x2d06, col);
            } else {
                if (lbl_8047CE18[fn_800BA7EC(0xe) + fn_800BA7EC(0x12) * 4].lo) {
                    col = GRAY;
                }
                DRAW(0x2d52, col);
            }
        } else if (fn_800BA7EC(0x15)) {
            DRAW(0x46b4, col);
        } else {
            DRAW(0x2dd0, col);
        }
        break;
    case 0x2a:
        if (!(lbl_8063EEEE & 0x400)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xb, &t.r);
        if (fn_800BA7EC(0x11) == 0) {
            if (fn_800BA7EC(3) == 0) {
                DIM();
            }
        } else {
            if (fn_800BA7EC(1) == 0) {
                DIM();
            }
        }
        break;
    case 0x2d:
        if (!(lbl_8063EEEE & 0x800)) return;
        fn_80253EDC(a, b, 6, &t.r);
        fn_80059A3C(0xc, &t.r);
        break;
    case 0x2c:
        if (!(lbl_8063EEEE & 0x400)) break;
        SETC();
        fn_80253F04(a, b, 2, (u32)fn_800BA7EC(0x11) == 1 ? fn_8005AC60(0x3f4, 0x0BC00C00) : fn_8005AC60(0x3f4, 0x0BBF0C00));
        fn_80253F04(a, b, 1, &t.c);
        if (fn_800BA7EC(0x11) == 0) {
            if (fn_800BA7EC(3) == 0) {
                DIM();
            }
        } else {
            if (fn_800BA7EC(1) == 0) {
                DIM();
            }
        }
        break;
    case 0x20:
        if (!(lbl_8063EEEE & 0x10)) return;
        fn_80253EDC(a, b, 6, &t.r);
        if (fn_800BA578() == 1) {
            DRAW(0x2d09, WHITE);
            break;
        }
        switch (fn_800E63D0()) {
        case 0:
            if (ok) {
                DRAW(0x2d07, WHITE);
            } else {
                DRAW(0x2d07, GRAY);
            }
            break;
        default:
        if (fn_800E63E4(0)) {
            DRAW(0x5162, WHITE);
        } else if (fn_800E63E4(1)) {
            GET_TEAM_IDX(idx);
            if (lbl_8047CE18[idx].lo) {
                DRAW(0x46b6, GRAY);
            } else {
                DRAW(0x2d17, WHITE);
            }
        } else {
            GET_TEAM_IDX(idx);
            if (lbl_8047CE18[idx].lo) {
                DRAW(0x2d08, GRAY);
            } else {
                DRAW(0x2d08, WHITE);
            }
        }
            break;
        }
        break;
    case 0x2b:
        if (!(lbl_8063EEEE & 0x400)) break;
        fn_80253EDC(a, b, 6, &t.r);
        col = WHITE;
        if ((u32)fn_800BA7EC(0x11) == 1) {
            if (fn_800BA7EC(1) == 0) {
                col = GRAY;
            }
            DRAW2(fn_802502F4(0x2cea), col);
        } else {
            if (fn_800BA7EC(3) == 0) {
                col = GRAY;
            }
            DRAW2(fn_802502F4(0x2ce9), col);
        }
        break;
    case 0x2e:
        if (!(lbl_8063EEEE & 0x800)) break;
        fn_80253EDC(a, b, 6, &t.r);
        DRAW(0x2ceb, WHITE);
        break;
    case 0x23:
        if (!(lbl_8063EEEE & 0x40)) break;
        fn_80253EDC(a, b, 6, &t.r);
        GET_TEAM_IDX(idx);
        if (fn_800E5224(2, lbl_8047CE18[idx].hi)) {
            DRAW(0x2d0a, GRAY);
        } else {
            DRAW(0x2d0a, WHITE);
        }
        break;
    case 0x25:
        if (!(lbl_8063EEEE & 0x80)) break;
        fn_80253EDC(a, b, 6, &t.r);
        DRAW(0x2d0b, WHITE);
        break;
    case 0x27:
        if (!(lbl_8063EEEE & 0x100)) break;
        fn_80253EDC(a, b, 6, &t.r);
        GET_TEAM_IDX(idx);
        if (fn_800E5224(2, lbl_8047CE18[idx].hi)) {
            DRAW(0x2d0c, GRAY);
        } else {
            DRAW(0x2d0c, WHITE);
        }
        break;
    }
    if (fn_800BA578() != 2) return;
    if (!(lbl_8063EEEE & 0x1000)) return;
    {
        sel = fn_800BA7EC(9);
        k = fn_800BA7EC(0);
        switch (sel) {
        case 0xf:
            k = k * 4 + 1;
            break;
        case 0x10:
            k = k * 4 + 2;
            break;
        case 0x11:
            k = k * 4 + 3;
            break;
        case 0x12:
            k = k * 4 + 4;
            break;
        }
        n = 0;
        switch (fn_80253DE0(fn_800BA98C(0xf))) {
        case 6:
            n = 1;
        case 5:
            n++;
        case 4:
            n++;
        case 3:
            n++;
        case 2:
            n++;
        case 1:
            p = (PkmFlag*)fn_800E5DEC(n, lbl_8047CE18[k - 1].hi);
            if (!p->flag) return;
            break;
        default:
            return;
        }
        if ((u8)n == (u32)fn_800BA7EC(0xc) && k - 1 == (u32)fn_800BA7EC(0xb) && fn_800BA7EC(0xa) != 0) {
            hl = 1;
        }
    }
    switch (t.type) {
    case 0x15:
        fn_8015C308(0x54, fn_8005697C(p));
        fn_80253EDC(a, b, 6, &t.r);
        DRAW(0x2db0, hl ? (0x00EEFF00 | b->x11) : WHITE);
        break;
    case 0x16:
        break;
    case 0x17:
        fn_80253EDC(a, b, 6, &t.r);
        fn_8015C308(0x1b, (void*)BoxPokemon_GetValue((BoxPokemon *)p, MON_DATA_LEVEL, NULL));
        DRAW(0xea0, hl ? (0x00EEFF00 | b->x11) : WHITE);
        break;
    }
}

#undef DRAW
#undef GET_TEAM_IDX
#undef DRAW2
#undef WHITE
#undef GRAY
#undef DIM
#undef SETC

}

class GSmath {
public:
    static f32 sin(f32);
};

extern "C" {

double sin(double);
void fn_80253DF0(void*, int, u32);

void fn_800D14A4(int a) {
    u8 m;
    u8 sel;
    int slot;
    int hl;
    s8 idx;
    s8 base;
    f32 x;
    f32 t;
    int flag;
    GSrender* r = GSrender::sInstance;
    t = (f32)(r->mA0 / r->m59 - lbl_8063EED8->_00) / 0.5f;
    m = fn_800BA7EC(2);
    fn_80253E4C((void*)a, 8, &flag);
    if (flag == 0) {
        return;
    }
    base = fn_800BA7EC(0) * 4;
    if ((fn_800BA578() == 2 && fn_800BA5CC() != 8) || fn_800BA578() == 3 || fn_800BA578() == 9 ||
        (fn_800BA578() == 0xd && fn_800BA5CC() >= 0xa && fn_800BA5CC() < 0x15)) {
        u32 lo;
        x = 0.0f;
        lo = m & 0xf;
        if (lo <= 0xe) {
            if (m & 0x80) {
                x -= 640.0f * GSmath::sin(90.0f * lo / 14.0f);
            } else {
                x += 640.0f * GSmath::sin(90.0f * lo / 14.0f);
            }
            if (a == fn_800BA98C(0x10)) {
                x += 640.0f;
            } else if (a == fn_800BA98C(0x11)) {
                x -= 640.0f;
            }
        }
        fn_80253E10((void*)a, 5, 1.0f);
        fn_80253E10((void*)a, 6, 1.0f);
        fn_80253E10((void*)a, 3, x);
        fn_80253E10((void*)a, 4, 10.0f);
        if (fn_800BA578() == 0xd) {
            sel = fn_800BA7EC(0x14);
        } else {
            sel = fn_800BA7EC(9);
        }
        if (a == fn_800BA98C(0xf)) {
            idx = 3 - (0x12 - sel);
        } else if (a == fn_800BA98C(0x10)) {
            idx = 4 - (0x12 - sel);
        } else if (a == fn_800BA98C(0x11)) {
            idx = 2 - (0x12 - sel);
            if (idx + base < 0) {
                idx = 0;
            }
        }
    } else {
        hl = 0;
        f32 s;
        f32 w;
        f32 y;
        f32 h;
        u32 lo;
        if (a == fn_800BA98C(0xf)) {
            slot = 1;
            idx = 0;
        } else if (a == fn_800BA98C(0x10)) {
            slot = 2;
            idx = 1;
        } else if (a == fn_800BA98C(0x11)) {
            slot = 3;
            idx = 2;
        } else if (a == fn_800BA98C(0x12)) {
            slot = 4;
            idx = 3;
        } else if (a == fn_800BA98C(0x13)) {
            slot = 1;
            hl = 1;
            if (m & 0x80) {
                idx = 4;
            } else if (base > 0) {
                idx = -4;
            }
        } else if (a == fn_800BA98C(0x14)) {
            slot = 2;
            hl = 1;
            if (m & 0x80) {
                idx = 5;
            } else if (base > 0) {
                idx = -3;
            }
        } else if (a == fn_800BA98C(0x15)) {
            slot = 3;
            hl = 1;
            if (m & 0x80) {
                idx = 6;
            } else if (base > 0) {
                idx = -2;
            }
        } else if (a == fn_800BA98C(0x16)) {
            slot = 4;
            hl = 1;
            if (m & 0x80) {
                idx = 7;
            } else if (base > 0) {
                idx = -1;
            }
        } else {
            return;
        }
        x = 0.0f;
        w = lbl_80416AB8[slot].v[2] - lbl_80416AB8[slot].v[0];
        if (w <= x) {
            s = 1.0f;
        } else {
            s = w / (lbl_80416AB8[0].v[2] - lbl_80416AB8[0].v[0]);
            x = (lbl_80416AB8[slot].v[0] + w / 2) - (lbl_80416AB8[0].v[0] + (lbl_80416AB8[0].v[1] - lbl_80416AB8[0].v[0]) / 2);
        }
        fn_80253E10((void*)a, 5, s);
        if (fn_800BA578() == 0) {
            if (fn_800BA5CC() == 0xc) {
                if (slot - 1 == (u32)fn_800BA7EC(9)) {
                    if (t >= 1.0f) {
                        t = 1.0f;
                    }
                    x += 640.0f * (f32)sin(0.017453292f * (90.0f * t));
                }
            } else if (fn_800BA5CC() == 0xd) {
                if (slot - 1 == (u32)fn_800BA7EC(9)) {
                    if (t >= 1.0f) {
                        t = 1.0f;
                    }
                    x -= 640.0f * (1.0f - (f32)sin(0.017453292f * (90.0f * t)));
                }
            }
        }
        if (hl) {
            if (m & 0x80) {
                x += 640.0f;
            } else {
                x -= 640.0f;
            }
        }
        lo = m & 0xf;
        if (lo <= 0xe) {
            if (m & 0x80) {
                x -= 640.0f * GSmath::sin(90.0f * lo / 14.0f);
            } else {
                x += 640.0f * GSmath::sin(90.0f * lo / 14.0f);
            }
        }
        fn_80253E10((void*)a, 3, x);
        y = 0.0f;
        h = lbl_80416AB8[slot].v[7] - lbl_80416AB8[slot].v[4];
        if (h <= y) {
            s = 1.0f;
        } else {
            s = h / (lbl_80416AB8[0].v[6] - lbl_80416AB8[0].v[4]);
            y = (240.0f - (240.0f - lbl_80416AB8[0].v[4]) * s) - lbl_80416AB8[slot].v[4];
        }
        fn_80253E10((void*)a, 6, s);
        fn_80253E10((void*)a, 4, y);
    }
    if (fn_800BA578() == 0xd && fn_800BA5CC() != 0x14) {
        return;
    }
    idx += base;
    if (lbl_8047CE18[idx].lo) {
        fn_80253DF0((void*)a, 2, 0x808080FF);
    } else {
        fn_80253DF0((void*)a, 2, 0xFFFFFFFF);
    }
}

}
