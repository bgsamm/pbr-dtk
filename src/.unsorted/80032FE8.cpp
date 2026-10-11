#include ".unsorted/80032FE8.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EA58;

void fn_8003301C(void) {}
u32 fn_80033088(void) { return lbl_8063EA58; }
u32 fn_800353F4(u8 *p) { return *(u32 *)(p + 0x8); }
void fn_80035A40(u8 *p, u32 v) { *(u32 *)(p + 0xac) = v; }
void fn_80035A48(u8 *p, u32 v) { *(u32 *)(p + 0xb0) = v; }

}

#include "common.hpp"

extern "C" {



void fn_80033488(u8 *p) { *(u8 *)(p + 0x1a5) = 0x1; }
void fn_80033494(u8 *p) { *(u8 *)(p + 0x1a5) = 0x0; }

}

// Fade, color and tone controls
struct MEMiHeapHead;
extern MEMiHeapHead *gGameHeap;
class GSmem {
public:
    static bool isInitialized();
    static void *allocFromHeap(MEMiHeapHead *heap, u32 size);
};
struct Vec3 { f32 x, y, z; };
class GSmath {
public:
    static Vec3 sYAxis;
};

class GSrenderTarget {
public:
    static GSrenderTarget *findTarget(long id);
};
f32 fn_8000739C();
void *operator new(unsigned long size);
void operator delete(void *p);
class Interp {
public:
    u32 m0;
    f32 m4;
    f32 m8;
    u32 mC;
    f32 m10;
    f32 m14;
    u32 m18;
    u32 m1C;
    virtual int update(f32 t);
};

struct Rect4 {
    f32 v[4];
};

class Screen {
public:
    u8 m0;
    bool m1;
    u8 m2;
    u32 m4;
    u32 m8;
    Rect4 mRect;
    Interp mInterp[4];
    u32 mAC;
    u32 mB0;
};

extern "C" {

extern u8 *lbl_8063F410;
extern const f32 lbl_806407E4;
extern const f32 lbl_806407E8;
extern const f32 lbl_806407EC;
extern const f64 lbl_80640800;

void fn_80050808(void *obj, void *cur, void *target, void *out, int frames);
void fn_8005033C(void *obj, f32 *cur, f32 *target, f32 *out, int frames, f32 t);
void fn_80050388(void *obj);
void fn_80050324(void *obj);

struct S16 { u32 a, b, c, d; };
class GSrender {
public:
    static GSrender *sInstance;
};
#define SCREEN_W() ((f32)*(u16 *)((u8 *)GSrender::sInstance + 4))
#define SCREEN_H() ((f32)*(u16 *)((u8 *)GSrender::sInstance + 6))
struct Color4 { u8 r, g, b, a; };
struct S24 { u8 d[0x24]; };

void fn_80034918(void);

void fn_800354D8(Screen *p, Rect4 *src) {
    p->mRect = *src;
    fn_80034918();
}

static inline void SetColor(u8 *p, u8 r, u8 g, u8 b, u8 a) {
    p[0x1dc] = r;
    p[0x1dd] = g;
    p[0x1de] = b;
    p[0x1df] = a;
}

void fn_80034B10(u8 *p, Color4 *c) {
    SetColor(p, c->r, c->g, c->b, c->a);
    fn_80034918();
}

void *fn_8003CE88(void *obj, int a);
void *fn_800401F4(void);
u8 *fn_80040384(void *mgr, u32 id);
void fn_800410AC(u8 *obj, void *a);
void fn_80042534(u8 *obj, void *a);
void fn_80050388(void *obj);
extern u8 *lbl_8063F410;
extern const f32 lbl_806407E4;

static inline f32 MyFabs(f32 x) {
    return __fabs(x);
}

static inline void *GetEntry(u8 *q) {
    void **arr;
    u16 *idx = *(u16 **)(q + 0x10);
    if (idx == 0) {
        return 0;
    }
    if (*(u16 *)(q + 0xe0) == 0) {
        return 0;
    }
    arr = *(void ***)(q + 0x8);
    u16 i = *idx;
    if (arr == 0) {
        return 0;
    }
    if (i >= *(u16 *)(q + 0xde)) {
        return 0;
    }
    return arr[i];
}

void fn_80035AB8(u8 *p) {
    if (p[2] == 0) {
        return;
    }
    u8 *obj;
    if (*(void **)(p + 0xac) != 0) {
        obj = (u8 *)fn_8003CE88(*(void **)(p + 0xac), 0);
        *(void **)(p + 0xac) = 0;
    } else if (*(u8 **)(p + 0xb0) != 0) {
        obj = (u8 *)GetEntry(*(u8 **)(p + 0xb0));
        *(void **)(p + 0xb0) = 0;
    }
    if (obj != 0) {
        Vec3 pos;
        pos.x = *(f32 *)(obj + 0x20);
        pos.y = *(f32 *)(obj + 0x24);
        pos.z = *(f32 *)(obj + 0x28);
        f32 ratio;
        if ((*(u32 *)(obj + 0x104) & 3) == 1) {
            ratio = *(f32 *)(obj + 0x16c);
        } else {
            f32 w = MyFabs(*(f32 *)(obj + 0x16c) - *(f32 *)(obj + 0x168));
            f32 h = MyFabs(*(f32 *)(obj + 0x174) - *(f32 *)(obj + 0x170));
            ratio = h / w;
        }
        u8 *q = *(u8 **)(p + 0x4);
        if ((*(u32 *)(q + 0x104) & 3) == 1) {
            *(f32 *)(q + 0x16c) = ratio;
            *(u32 *)(q + 0x104) |= 8;
        }
        void *mgr = fn_800401F4();
        if (mgr != 0) {
            u8 *o = fn_80040384(mgr, *(u32 *)(p + 0x8));
            if (o != 0) {
                *(f32 *)(o + 0x4e0) = (*(u32 *)(obj + 0x104) & 3) == 1 ? *(f32 *)(obj + 0x168) : lbl_806407E4;
                fn_80050388(o + 0x4);
                o[1] = 1;
                fn_800410AC(o, obj + 0x1ac);
                fn_80042534(o, obj + 0x1c4);
            }
        }
    }
    p[2] = 0;
    fn_80034918();
}


u8 *fn_80035380(u8 *p);


void fn_80033C6C(u8 *p) {
    u32 raw[0xb4 / 4];
    fn_80035380((u8 *)raw);
    Screen *s = (Screen *)p;
    *(Screen *)raw = s[0];
    s[0] = s[1];
    s[1] = *(Screen *)raw;
    fn_80034918();
}


#pragma dont_inline on

void fn_80034918(void) {
    u8 *p = (u8 *)lbl_8063EA58;
    if (p != 0) {
        p[0x1a4] = 1;
    }
}

void fn_80034F48(u8 *p) {
    if (lbl_8063F410 == 0) {
        return;
    }
    lbl_8063F410[0x40d] = p[0x170];
    *(f32 *)(lbl_8063F410 + 0x42c) = *(f32 *)(p + 0x174);
    lbl_8063F410[0x430] = p[0x171];
    *(s32 *)(lbl_8063F410 + 0x434) = *(s32 *)(p + 0x178);
    lbl_8063F410[0x431] = p[0x17c];
    u8 *g = lbl_8063F410;
    *(f32 *)(g + 0x424) = *(f32 *)(p + 0x180);
    *(f32 *)(g + 0x428) = *(f32 *)(p + 0x184);
}

void fn_80034FA4(u8 *p, u8 v) {
    p[0x170] = v;
    fn_80034F48(p);
}

void fn_80035078(u8 *p, u8 v) {
    p[0x171] = v;
    fn_80034F48(p);
}

void fn_80035080(u8 *p, s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (v > 1) {
        v = 1;
    }
    *(s32 *)(p + 0x178) = v;
    fn_80034F48(p);
}

void fn_800350A0(u8 *p, u32 v) {
    if (v > 100) {
        v = 100;
    }
    p[0x17c] = v;
    fn_80034F48(p);
}

void fn_80035228(u8 *p) {
    if (lbl_8063F410 == 0) {
        return;
    }
    lbl_8063F410[0x40f] = p[0x188];
    *(f32 *)(lbl_8063F410 + 0x440) = *(f32 *)(p + 0x18c);
    *(s32 *)(lbl_8063F410 + 0x44c) = *(s32 *)(p + 0x190);
    lbl_8063F410[0x448] = p[0x194];
    u8 *g = lbl_8063F410;
    *(f32 *)(g + 0x438) = *(f32 *)(p + 0x198);
    *(f32 *)(g + 0x43c) = *(f32 *)(p + 0x19c);
}

void fn_80035278(u8 *p, u8 v) {
    p[0x188] = v;
    fn_80035228(p);
}

void fn_80035280(u8 *p, f32 v) {
    if (v < lbl_806407E4) {
        v = lbl_806407E4;
    }
    if (v >= lbl_806407E8) {
        v = lbl_806407E8;
    }
    *(f32 *)(p + 0x18c) = v;
    fn_80035228(p);
}

void fn_800352AC(u8 *p, s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (v > 1) {
        v = 1;
    }
    *(s32 *)(p + 0x190) = v;
    fn_80035228(p);
}

void fn_800352CC(u8 *p, u32 v) {
    if (v > 100) {
        v = 100;
    }
    p[0x194] = v;
    fn_80035228(p);
}

void fn_80035354(f32 *p) {
    if (*p < lbl_806407E4) {
        *p = lbl_806407E4;
    } else if (*p > lbl_806407E8) {
        *p = lbl_806407E8;
    }
}

void fn_80034B34(u8 *p, f32 a, f32 b) {
    *(f32 *)(p + 0x1e8) = a;
    *(f32 *)(p + 0x1ec) = b;
    fn_80034918();
}

void fn_80034B40(u8 *p, f32 a) {
    *(f32 *)(p + 0x1f0) = a;
    fn_80034918();
}

void fn_80034B48(u8 *p, f32 a, f32 b) {
    *(f32 *)(p + 0x1f4) = a;
    *(f32 *)(p + 0x1f8) = b;
    fn_80034918();
}

void fn_80034B54(u8 *p, s32 mode, void *target, int frames) {
    fn_80050808(p + 0x690, p + 0x1dc, target, p + 0x1dc, frames);
    *(s32 *)(p + 0x200) = mode;
}

void fn_80034BA0(u8 *p, f32 a, f32 b, s32 mode, int frames, f32 t) {
    f32 v[2];
    v[0] = a;
    v[1] = b;
    fn_8005033C(p + 0x2c4, (f32 *)(p + 0x1e8), &v[0], (f32 *)(p + 0x1e8), frames, t);
    fn_8005033C(p + 0x2e8, (f32 *)(p + 0x1ec), &v[1], (f32 *)(p + 0x1ec), frames, t);
    *(s32 *)(p + 0x200) = mode;
}

void fn_80034C30(u8 *p, f32 a, s32 mode, int frames, f32 t) {
    f32 v = a;
    fn_8005033C(p + 0x30c, (f32 *)(p + 0x1f0), &v, (f32 *)(p + 0x1f0), frames, t);
    *(s32 *)(p + 0x200) = mode;
}

void fn_80034C88(u8 *p, f32 a, f32 b, s32 mode, int frames, f32 t) {
    f32 v[2];
    v[0] = a;
    v[1] = b;
    fn_8005033C(p + 0x330, (f32 *)(p + 0x1f4), &v[0], (f32 *)(p + 0x1f4), frames, t);
    fn_8005033C(p + 0x354, (f32 *)(p + 0x1f8), &v[1], (f32 *)(p + 0x1f8), frames, t);
    *(s32 *)(p + 0x200) = mode;
}

void fn_80034D18(u8 *p, f32 a, int frames, f32 t) {
    f32 v = a;
    fn_8005033C(p + 0x378, (f32 *)(p + 0x1fc), &v, (f32 *)(p + 0x1fc), frames, t);
    *(s32 *)(p + 0x200) = 7;
}

void fn_800349B4(u8 *p) {
    for (int i = 0; i < 6; i++) {
        fn_80050388((S24 *)(p + 0x2c4) + i);
    }
}

void fn_80034A00(u8 *p) {
    p[0x1dc] = 0xff;
    p[0x1dd] = 0xff;
    p[0x1de] = 0xff;
    p[0x1df] = 0xff;
    *(f32 *)(p + 0x1e8) = lbl_806407E4;
    *(f32 *)(p + 0x1ec) = lbl_806407E4;
    *(f32 *)(p + 0x1f0) = lbl_806407E4;
    *(f32 *)(p + 0x1f4) = lbl_806407E8;
    *(f32 *)(p + 0x1f8) = lbl_806407E8;
    *(f32 *)(p + 0x1fc) = lbl_806407E8;
    fn_800349B4(p);
}

u8 *fn_80035380(u8 *p) {
    u8 *q = p + 0x1c;
    do {
        fn_80050324(q);
        q += 0x24;
    } while (q < p + 0xac);
    p[0] = 0;
    p[2] = 0;
    *(u32 *)(p + 0x4) = 0;
    *(u32 *)(p + 0x8) = 0;
    *(u32 *)(p + 0xac) = 0;
    *(u32 *)(p + 0xb0) = 0;
    return p;
}


#pragma dont_inline reset
static inline void SetGlobal40E(u8 v) {
    if (*(s32 *)(lbl_8063F410 + 0x418) != 0) {
        lbl_8063F410[0x40e] = v;
    } else {
        lbl_8063F410[0x40e] = 0;
    }
}

static inline void SetGlobal450(f32 v) {
    *(f32 *)(lbl_8063F410 + 0x450) = v;
}

void fn_80034E68(u8 *p, u8 v) {
    p[0x168] = v;
    SetGlobal40E(v);
    SetGlobal450(*(f32 *)(p + 0x16c));
}

static inline f32 Clamp01(f32 v) {
    if (v < lbl_806407E4) {
        v = lbl_806407E4;
    }
    if (v >= lbl_806407E8) {
        v = lbl_806407E8;
    }
    return v;
}

void fn_80034EA0(u8 *p, f32 v) {
    f32 c = Clamp01(v);
    *(f32 *)(p + 0x16c) = c;
    SetGlobal450(c);
    fn_80050388(p + 0x5dc);
}

#pragma dont_inline on

void fn_80034EDC(u8 *p, f32 v, int frames, f32 t) {
    f32 tmp = v;
    if (tmp < lbl_806407E4) {
        tmp = lbl_806407E4;
    }
    if (tmp >= lbl_806407E8) {
        tmp = lbl_806407E8;
    }
    fn_8005033C(p + 0x5dc, (f32 *)(p + 0x16c), &tmp, (f32 *)(p + 0x16c), frames, t);
}

void fn_80034FAC(u8 *p, f32 v) {
    if (v < lbl_806407E4) {
        v = lbl_806407E4;
    }
    if (v >= lbl_806407E8) {
        v = lbl_806407E8;
    }
    *(f32 *)(p + 0x174) = v;
    fn_80050388(p + 0x624);
    fn_80034F48(p);
}

void fn_8003500C(u8 *p, f32 v, int frames, f32 t) {
    f32 tmp = v;
    if (tmp < lbl_806407E4) {
        tmp = lbl_806407E4;
    }
    if (tmp >= lbl_806407E8) {
        tmp = lbl_806407E8;
    }
    fn_8005033C(p + 0x624, (f32 *)(p + 0x174), &tmp, (f32 *)(p + 0x174), frames, t);
}

void fn_800350B4(u8 *p, f32 x, f32 y) {
    if (x > lbl_806407E8) {
        x = lbl_806407E8;
    }
    if (x < lbl_806407EC) {
        x = lbl_806407EC;
    }
    if (y > lbl_806407E8) {
        y = lbl_806407E8;
    }
    if (y < lbl_806407EC) {
        y = lbl_806407EC;
    }
    *(f32 *)(p + 0x180) = x;
    *(f32 *)(p + 0x184) = y;
    fn_80050388(p + 0x648);
    fn_80050388(p + 0x66c);
    u8 *g = lbl_8063F410;
    *(f32 *)(g + 0x424) = *(f32 *)(p + 0x180);
    *(f32 *)(g + 0x428) = *(f32 *)(p + 0x184);
}

void fn_80035148(u8 *p, f32 x, f32 y, int frames, f32 t) {
    f32 b;
    f32 a;
    a = x;
    b = y;
    if (a > lbl_806407E8) {
        a = lbl_806407E8;
    }
    if (a < lbl_806407EC) {
        a = lbl_806407EC;
    }
    if (b > lbl_806407E8) {
        b = lbl_806407E8;
    }
    if (b < lbl_806407EC) {
        b = lbl_806407EC;
    }
    fn_8005033C(p + 0x648, (f32 *)(p + 0x180), &a, (f32 *)(p + 0x180), frames, t);
    fn_8005033C(p + 0x66c, (f32 *)(p + 0x184), &b, (f32 *)(p + 0x184), frames, t);
}

void fn_800352E0(u8 *p, u32 v, int frames, f32 t) {
    if (v > 100) {
        v = 100;
    }
    f32 cur;
    f32 target = v;
    cur = p[0x194];
    fn_8005033C(p + 0x600, &cur, &target, (f32 *)(p + 0x1d8), frames, t);
}

s32 fn_80034930(u8 *p) {
    for (int i = 0; i < 6; i++) {
        if (*(s32 *)(p + 0x2c4) != 0) {
            return 1;
        }
        p += 0x24;
    }
    return 0;
}

void fn_800348BC(u8 *p, s32 mode) {
    switch (mode) {
    case 0:
        fn_80034918();
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        break;
    default:
        return;
    }
    *(s32 *)(p + 0x1a0) = mode;
}

void fn_80034A38(u8 *p, s32 v) {
    if (*(s32 *)(p + 0x1a0) != 6) {
        fn_800348BC(p, 6);
        fn_80034A00(p);
    }
    switch (v) {
    case 0:
        *(s32 *)(p + 0x1e4) = 0;
        break;
    case 1:
        *(s32 *)(p + 0x1e4) = 1;
        break;
    }
    fn_80034918();
}

void fn_80034AB8(u8 *p, f32 v) {
    if (*(s32 *)(p + 0x1a0) != 7) {
        fn_800348BC(p, 7);
        fn_80034A00(p);
    }
    *(f32 *)(p + 0x1fc) = v;
    fn_80034918();
}

u8 *fn_80033B7C(u8 *p, u32 i) {
    if (i >= 2) {
        return 0;
    }
    return p + i * 0xb4;
}

u32 fn_800353F4(u8 *p);

s32 fn_80033B98(u8 *p, u32 key) {
    for (u32 i = 0; i < 2; i++) {
        if (key == fn_800353F4(p + (u16)i * 0xb4)) {
            return i;
        }
    }
    return 0xffff;
}

void fn_80033C0C(u8 *p) {
    S16 tmp = *(S16 *)(p + 0xc);
    fn_800354D8((Screen *)p, (Rect4 *)(p + 0xc0));
    fn_800354D8((Screen *)(p + 0xb4), (Rect4 *)&tmp);
    fn_80034918();
}

#pragma dont_inline reset


void fn_800348BC(u8 *p, s32 mode);
void fn_80033C6C(u8 *p);
void fn_80050E7C(void *obj, void *a, f32 *out, int b, int c, int d, f32 x, f32 y);
extern const f32 lbl_8064080C;
extern const f32 lbl_80640810;

#pragma dont_inline on

void fn_800354FC(u8 *p, f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dx = x0 - x1;
    f32 dy;
    if ((dx < lbl_8064080C && dx > lbl_80640810) ||
        ((dy = y0 - y1) < lbl_8064080C && dy > lbl_80640810)) {
        return;
    }
    f32 w = SCREEN_W();
    f32 h = SCREEN_H();
    if (x0 < x1) {
        *(f32 *)(p + 0xc) = x0 / w;
        *(f32 *)(p + 0x14) = x1 / w;
    } else {
        *(f32 *)(p + 0x14) = x0 / w;
        *(f32 *)(p + 0xc) = x1 / w;
    }
    if (y0 < y1) {
        *(f32 *)(p + 0x10) = y0 / h;
        *(f32 *)(p + 0x18) = y1 / h;
    } else {
        *(f32 *)(p + 0x18) = y0 / h;
        *(f32 *)(p + 0x10) = y1 / h;
    }
    fn_80035354((f32 *)(p + 0x14));
    fn_80035354((f32 *)(p + 0xc));
    fn_80035354((f32 *)(p + 0x10));
    fn_80035354((f32 *)(p + 0x18));
    if (fn_80033088() != 0) {
        fn_800348BC((u8 *)fn_80033088(), 1);
    }
    fn_80034918();
}

void fn_80035628(u8 *p) {
    f32 h = SCREEN_H();
    f32 w = SCREEN_W();
    fn_800354FC(p, lbl_806407E4, lbl_806407E4, w, h);
    fn_800348BC((u8 *)fn_80033088(), 0);
}

void fn_800340D0(u8 *p, f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 w = SCREEN_W();
    f32 h = SCREEN_H();
    f32 a = x0 / w;
    *(f32 *)(p + 0x1a8) = a;
    f32 c = x1 / w;
    *(f32 *)(p + 0x1b0) = c;
    f32 b = y0 / h;
    *(f32 *)(p + 0x1ac) = b;
    f32 d = y1 / h;
    *(f32 *)(p + 0x1b4) = d;
    if (a == c || b == d) {
        return;
    }
    *(f32 *)(p + 0x1b8) = x0;
    *(f32 *)(p + 0x1bc) = y0;
    *(f32 *)(p + 0x1c0) = x1;
    *(f32 *)(p + 0x1c4) = y1;
    fn_800348BC(p, 4);
    fn_80034918();
}

void fn_80034170(u8 *p, f32 v) {
    f32 w = SCREEN_W();
    f32 h = SCREEN_H();
    if (v <= lbl_806407E4) {
        fn_800348BC(p, 0);
        fn_80033C6C(p);
    } else if (v >= h) {
        fn_800348BC(p, 0);
    } else {
        fn_800354FC(p, lbl_806407E4, lbl_806407E4, w, v + *(f32 *)(p + 0x1d4));
        fn_800354FC(p + 0xb4, lbl_806407E4, v + *(f32 *)(p + 0x1d4), w, h);
        *(f32 *)(p + 0x1cc) = v;
        fn_800348BC(p, 2);
        fn_80034918();
    }
}

void fn_80034494(u8 *p, f32 v, f32 t, int frames) {
    f32 tmp = v;
    if (lbl_806407E4 == t) {
        fn_80034170(p, tmp);
    } else if (*(s32 *)(p + 0x1a0) == 2) {
        fn_800349B4(p);
        fn_8005033C(p + 0x2c4, (f32 *)(p + 0x1cc), &tmp, (f32 *)(p + 0x1cc), frames, t);
        *(s32 *)(p + 0x200) = 2;
    }
}

void fn_800345C4(u8 *p, void *a, int b, f32 x, f32 y) {
    if (y <= lbl_806407E4) {
        *(f32 *)(p + 0x1d4) = lbl_806407E4;
    } else if (*(s32 *)(p + 0x1a0) == 2) {
        fn_80050E7C(p + 0x264, a, (f32 *)(p + 0x1d4), b, 0, 0, x, y);
        *(s32 *)(p + 0x200) = 2;
    }
}

#pragma dont_inline reset


#pragma dont_inline on

void fn_80034280(u8 *p, f32 v) {
    f32 w = SCREEN_W();
    f32 h = SCREEN_H();
    if (v <= lbl_806407E4) {
        fn_800348BC(p, 0);
        fn_80033C6C(p);
    } else if (v >= w) {
        fn_800348BC(p, 0);
    } else {
        fn_800354FC(p, lbl_806407E4, lbl_806407E4, v + *(f32 *)(p + 0x1d0), h);
        fn_800354FC(p + 0xb4, v + *(f32 *)(p + 0x1d0), lbl_806407E4, w, h);
        *(f32 *)(p + 0x1c8) = v;
        fn_800348BC(p, 3);
        fn_80034918();
    }
}

void fn_80034390(u8 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, int frames) {
    f32 v[4];
    v[0] = x0;
    v[1] = y0;
    v[2] = x1;
    v[3] = y1;
    if (lbl_806407E4 == t) {
        fn_800340D0(p, v[0], v[1], v[2], v[3]);
    } else if (*(s32 *)(p + 0x1a0) == 4) {
        fn_800349B4(p);
        fn_8005033C(p + 0x2c4, (f32 *)(p + 0x1b8), &v[0], (f32 *)(p + 0x1b8), frames, t);
        fn_8005033C(p + 0x2e8, (f32 *)(p + 0x1bc), &v[1], (f32 *)(p + 0x1bc), frames, t);
        fn_8005033C(p + 0x30c, (f32 *)(p + 0x1c0), &v[2], (f32 *)(p + 0x1c0), frames, t);
        fn_8005033C(p + 0x330, (f32 *)(p + 0x1c4), &v[3], (f32 *)(p + 0x1c4), frames, t);
        *(s32 *)(p + 0x200) = 4;
    }
}

void fn_8003452C(u8 *p, f32 v, f32 t, int frames) {
    f32 tmp = v;
    if (lbl_806407E4 == t) {
        fn_80034280(p, tmp);
    } else if (*(s32 *)(p + 0x1a0) == 3) {
        fn_800349B4(p);
        fn_8005033C(p + 0x2c4, (f32 *)(p + 0x1c8), &tmp, (f32 *)(p + 0x1c8), frames, t);
        *(s32 *)(p + 0x200) = 3;
    }
}

void fn_80034630(u8 *p, void *a, int b, f32 x, f32 y) {
    if (y <= lbl_806407E4) {
        *(f32 *)(p + 0x1d0) = lbl_806407E4;
    } else if (*(s32 *)(p + 0x1a0) == 3) {
        fn_80050E7C(p + 0x204, a, (f32 *)(p + 0x1d0), b, 0, 0, x, y);
        *(s32 *)(p + 0x200) = 3;
    }
}

#pragma dont_inline reset


void fn_80051134(void *obj, void *a, f32 *out, int b, int c, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
extern const f32 lbl_80640808;
extern const f32 lbl_806407DC;
#pragma dont_inline on

void fn_8003469C(u8 *p, void *a, int b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (*(s32 *)(p + 0x1a0) != 2) {
        return;
    }
    fn_800349B4(p);
    if (*(s32 *)((u8 *)GSrender::sInstance + 0x70) == 1 && lbl_80640808 == f3) {
        f3 = lbl_806407DC;
    }
    fn_80051134(p + 0x45c, a, (f32 *)(p + 0x1cc), b, 1, f1, f4, f5, f3, f2);
    *(s32 *)(p + 0x200) = 2;
}

void fn_800347BC(u8 *p, void *a, int b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (*(s32 *)(p + 0x1a0) != 3) {
        return;
    }
    fn_800349B4(p);
    fn_80051134(p + 0x39c, a, (f32 *)(p + 0x1c8), b, 1, f1, f4, f5, f3, f2);
    *(s32 *)(p + 0x200) = 3;
}

void fn_80034D68(u8 *p, void *a, int b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (*(s32 *)(p + 0x1a0) != 7) {
        return;
    }
    fn_800349B4(p);
    fn_80051134(p + 0x51c, a, (f32 *)(p + 0x1fc), b, 1, f1, f4, f5, f3, f2);
    *(s32 *)(p + 0x200) = 7;
}

#pragma dont_inline reset


void fn_80039090(void *obj, f32 t);
void *fn_8003CE88(void *obj, int a);


void *fn_80035970(u8 *p) {
    if (p[2] != 0) {
        if (*(void **)(p + 0xac) != 0) {
            void *r = fn_8003CE88(*(void **)(p + 0xac), 0);
            if (r != 0) {
                return r;
            }
        } else {
            u8 *q = *(u8 **)(p + 0xb0);
            if (q != 0) {
                void *r = GetEntry(q);
                if (r != 0) {
                    return r;
                }
            }
        }
    }
    return *(void **)(p + 0x4);
}

#pragma dont_inline on

void fn_800358C8(u8 *p) {
    for (int i = 0; i < 4; i++) {
        fn_80050388((S24 *)(p + 0x1c) + i);
    }
}

s32 fn_80035914(u8 *p) {
    for (int i = 0; i < 4; i++) {
        if (*(s32 *)(p + 0x1c) != 0) {
            return 1;
        }
        p += 0x24;
    }
    return 0;
}

void fn_80035828(u8 *p, f32 t) {
    int changed = 0;
    for (int i = 0; i < 4; i++) {
        if (((Interp *)(p + 0x1c))[i].update(t)) {
            changed = 1;
        }
    }
    if (changed) {
        fn_800354D8((Screen *)p, (Rect4 *)(p + 0xc));
    }
}

void fn_80035A50(u8 *p) {
    if (*(void **)(p + 0xac) != 0) {
        fn_80039090(*(void **)(p + 0xac), lbl_806407E4);
        fn_80034918();
        p[2] = 1;
    } else if (*(void **)(p + 0xb0) != 0) {
        fn_80034918();
        p[2] = 1;
    }
}

void fn_80035690(u8 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, int frames) {
    f32 v[4];
    v[0] = x0;
    v[1] = y0;
    v[2] = x1;
    v[3] = y1;
    if (lbl_806407E4 == t) {
        fn_800354FC(p, v[0], v[1], v[2], v[3]);
    } else {
        f32 w = SCREEN_W();
        f32 h = SCREEN_H();
        v[0] /= w;
        fn_80035354(&v[0]);
        v[2] /= w;
        fn_80035354(&v[2]);
        v[1] /= h;
        fn_80035354(&v[1]);
        v[3] /= h;
        fn_80035354(&v[3]);
        fn_800358C8(p);
        fn_8005033C(p + 0x1c, (f32 *)(p + 0xc), &v[0], (f32 *)(p + 0xc), frames, t);
        fn_8005033C(p + 0x40, (f32 *)(p + 0x10), &v[1], (f32 *)(p + 0x10), frames, t);
        fn_8005033C(p + 0x64, (f32 *)(p + 0x14), &v[2], (f32 *)(p + 0x14), frames, t);
        fn_8005033C(p + 0x88, (f32 *)(p + 0x18), &v[3], (f32 *)(p + 0x18), frames, t);
    }
}

#pragma dont_inline reset


void *fn_800401F4(void);
u8 *fn_80040384(void *mgr, u32 id);
void fn_800410AC(u8 *obj, void *a);
void fn_80042534(u8 *obj, void *a);

#pragma dont_inline on

void fn_800353FC(u8 *p, u32 id) {
    void *mgr = fn_800401F4();
    if (mgr != 0) {
        u8 *obj = fn_80040384(mgr, *(u32 *)(p + 0x8));
        if (obj != 0) {
            *(u32 *)(obj + 0x6cc) = 0;
        }
        obj = fn_80040384(mgr, id);
        if (obj != 0) {
            *(u8 **)(obj + 0x6cc) = *(u8 **)(p + 0x4);
            u8 *src = *(u8 **)(p + 0x4);
            *(f32 *)(obj + 0x4e0) = (*(u32 *)(src + 0x104) & 3) == 1 ? *(f32 *)(src + 0x168) : lbl_806407E4;
            fn_80050388(obj + 0x4);
            obj[1] = 1;
            fn_800410AC(obj, *(u8 **)(p + 0x4) + 0x1ac);
            fn_80042534(obj, *(u8 **)(p + 0x4) + 0x1c4);
        }
    }
    *(u32 *)(p + 0x8) = id;
}

#pragma dont_inline reset


extern void *lbl_8063F778;
void fn_800334A0(u8 *p, f32 t);
u8 *fn_80033090(u8 *p);
void fn_8023EB58(void *a, void (*f1)(void), void (*f2)(void), int b, int c);
void fn_8003301C(void);

#pragma dont_inline on

void fn_80032FE8(void) {
    if (lbl_8063EA58 != 0) {
        f32 t = fn_8000739C();
        fn_800334A0((u8 *)lbl_8063EA58, t);
    }
}

void fn_80033020(void) {
    if (lbl_8063EA58 != 0) {
        operator delete((void *)lbl_8063EA58);
    }
    u8 *m = (u8 *)operator new(0x6b4);
    if (m != 0) {
        m = fn_80033090(m);
    }
    lbl_8063EA58 = (u32)m;
    fn_8023EB58(lbl_8063F778, fn_80032FE8, fn_8003301C, 3, 0xc);
    fn_80034918();
}

#pragma dont_inline reset



void PSVECSubtract(const Vec3 *a, const void *b, Vec3 *out);
f32 PSVECMag(const Vec3 *v);
void PSVECScale(const Vec3 *src, Vec3 *dst, f32 scale);
void PSVECAdd(const Vec3 *a, const void *b, Vec3 *out);
void *fn_802352BC(GSrender *r);
void GXProject(f32 x, f32 y, f32 z, const void *mtx, const void *pm, const void *vp, f32 *sx, f32 *sy, f32 *sz);
int fn_80242A00(u8 *tgt, int mode);
void fn_80242A3C(u8 *tgt, int a, int b, int c, f32 x, f32 y, f32 w, f32 h);
void fn_80242CD0(u8 *tgt, void *a, void *b);
void fn_80243538(u8 *tgt, int a, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);
void fn_80035828(u8 *p, f32 t);
extern const f32 lbl_806407F0;
extern const f32 lbl_806407F4;
extern const f32 lbl_806407F8;

#define UPDATE(off) (((Interp *)(p + (off)))->update(t))

#pragma dont_inline on

void fn_800334A0(u8 *p, f32 t) {
    if (p[0x1a5] == 0) {
        return;
    }
    if (p[0x188] != 0) {
        u8 *obj = (u8 *)fn_80035970(p);
        Vec3 v;
        v.x = *(f32 *)(obj + 0x1c4);
        v.y = *(f32 *)(obj + 0x1c8);
        v.z = *(f32 *)(obj + 0x1cc);
        if (*(u32 *)(obj + 0x104) & 0x40) {
            PSVECSubtract(&v, obj + 0x1ac, &v);
            PSVECScale(&v, &v, *(f32 *)(obj + 0x184) / PSVECMag(&v));
            PSVECAdd(&v, obj + 0x1ac, &v);
        }
        f32 sx;
        f32 sy;
        f32 sz;
        void *vp = fn_802352BC(GSrender::sInstance);
        GXProject(v.x, v.y, v.z, obj + 0x1d4, obj + 0x14c, vp, &sx, &sy, &sz);
        *(f32 *)(lbl_8063F410 + 0x444) = sz > lbl_806407E4 ? sz : -sz;
    }
    int changed = 0;
    for (int i = 0; i < 6; i++) {
        if (((Interp *)(p + 0x2c4))[i].update(t)) {
            changed = 1;
        }
    }
    if (UPDATE(0x204)) {
        changed = 1;
    }
    if (UPDATE(0x264)) {
        changed = 1;
    }
    if (UPDATE(0x39c)) {
        changed = 1;
    }
    if (UPDATE(0x45c)) {
        changed = 1;
    }
    if (UPDATE(0x51c)) {
        changed = 1;
    }
    if (UPDATE(0x690)) {
        changed = 1;
    }
    if (changed) {
        switch (*(u32 *)(p + 0x200)) {
        case 4:
            fn_800340D0(p, *(f32 *)(p + 0x1b8), *(f32 *)(p + 0x1bc), *(f32 *)(p + 0x1c0), *(f32 *)(p + 0x1c4));
            break;
        case 2:
            fn_80034170(p, *(f32 *)(p + 0x1cc));
            break;
        case 3:
            fn_80034280(p, *(f32 *)(p + 0x1c8));
            break;
        case 5:
            fn_80034918();
            break;
        case 6:
            fn_80034918();
            break;
        case 7:
            fn_80034918();
            break;
        case 0:
        case 1:
            break;
        }
    }
    fn_80035828(p, t);
    fn_80035828(p + 0xb4, t);
    if (UPDATE(0x5dc)) {
        *(f32 *)(lbl_8063F410 + 0x450) = *(f32 *)(p + 0x16c);
    }
    if (UPDATE(0x600)) {
        p[0x194] = (int)*(f32 *)(p + 0x1d8);
        fn_80035228(p);
    }
    int changed2 = 0;
    if (UPDATE(0x648)) {
        changed2 = 1;
    }
    if (UPDATE(0x66c)) {
        changed2 = 1;
    }
    if (UPDATE(0x624)) {
        changed2 = 1;
    }
    if (changed2) {
        fn_80034F48(p);
    }
    if (p[0x1a4] == 0) {
        return;
    }
    if (((*(bool *)(p + 1) ? 1 : 0) | (*(bool *)(p + 0xb5) ? 2 : 0)) == 0) {
        return;
    }
    u8 *tgt = (u8 *)GSrenderTarget::findTarget(2);
    if (tgt == 0) {
        return;
    }
    switch (*(s32 *)(p + 0x1a0)) {
    case 0: {
        void *r = fn_80035970(p);
        *(u32 *)(tgt + 0x20) = 0;
        *(void **)(tgt + 0xc) = r;
        break;
    }
    case 1:
    case 2:
    case 3:
        fn_80242A00(tgt, 1);
        *(void **)(tgt + 0x24) = fn_80035970(p);
        tgt[0x39] = 1;
        *(void **)(tgt + 0x64) = fn_80035970(p + 0xb4);
        tgt[0x79] = 0;
        {
            f32 h = *(f32 *)(p + 0x18) - *(f32 *)(p + 0x10);
            f32 w = *(f32 *)(p + 0x14) - *(f32 *)(p + 0xc);
            fn_80242A3C(tgt, 0, 1, 1, *(f32 *)(p + 0xc), *(f32 *)(p + 0x10), w, h);
        }
        {
            f32 h = *(f32 *)(p + 0xcc) - *(f32 *)(p + 0xc4);
            f32 w = *(f32 *)(p + 0xc8) - *(f32 *)(p + 0xc0);
            fn_80242A3C(tgt, 1, 0, 1, *(f32 *)(p + 0xc0), *(f32 *)(p + 0xc4), w, h);
        }
        break;
    case 4:
        if (fn_80242A00(tgt, 2) == 0) {
            break;
        }
        *(void **)(tgt + 0x24) = fn_80035970(p);
        tgt[0x39] = 0;
        *(void **)(tgt + 0x64) = fn_80035970(p + 0xb4);
        tgt[0x79] = 0;
        fn_80242CD0(tgt, p + 0x1a8, p + 0x1b0);
        break;
    case 5:
        if (*(s32 *)(p + 0x1e0) == 0) {
            break;
        }
        fn_80242A00(tgt, 3);
        *(void **)(tgt + 0x24) = fn_80035970(p);
        tgt[0x39] = 0;
        *(void **)(tgt + 0x64) = fn_80035970(p + 0xb4);
        tgt[0x79] = 0;
        *(s32 *)(tgt + 0xa8) = *(s32 *)(p + 0x1e0);
        tgt[0xc4] = p[0x1dc];
        tgt[0xc5] = p[0x1dd];
        tgt[0xc6] = p[0x1de];
        tgt[0xc7] = p[0x1df];
        *(f32 *)(tgt + 0xac) = *(f32 *)(p + 0x1e8);
        *(f32 *)(tgt + 0xb0) = *(f32 *)(p + 0x1ec);
        *(f32 *)(tgt + 0xb4) = *(f32 *)(p + 0x1f0);
        *(f32 *)(tgt + 0xb8) = *(f32 *)(p + 0x1f4);
        *(f32 *)(tgt + 0xbc) = *(f32 *)(p + 0x1f8);
        break;
    case 6:
        fn_80242A00(tgt, 4);
        switch (*(s32 *)(p + 0x1e4)) {
        case 0:
            *(u32 *)(tgt + 0xc8) = 0;
            break;
        case 1:
            fn_80243538(tgt, 0xc, lbl_806407F0, lbl_806407F4, lbl_806407DC, lbl_806407F8, lbl_806407DC);
            break;
        }
        *(void **)(tgt + 0x24) = fn_80035970(p);
        tgt[0x39] = 0;
        *(void **)(tgt + 0x64) = fn_80035970(p + 0xb4);
        tgt[0x79] = 0;
        tgt[0xc4] = p[0x1dc];
        tgt[0xc5] = p[0x1dd];
        tgt[0xc6] = p[0x1de];
        tgt[0xc7] = p[0x1df];
        *(f32 *)(tgt + 0xac) = *(f32 *)(p + 0x1e8);
        *(f32 *)(tgt + 0xb0) = *(f32 *)(p + 0x1ec);
        *(f32 *)(tgt + 0xb4) = *(f32 *)(p + 0x1f0);
        *(f32 *)(tgt + 0xb8) = *(f32 *)(p + 0x1f4);
        *(f32 *)(tgt + 0xbc) = *(f32 *)(p + 0x1f8);
        break;
    case 7:
        fn_80242A00(tgt, 5);
        *(void **)(tgt + 0x24) = fn_80035970(p);
        tgt[0x39] = 0;
        *(void **)(tgt + 0x64) = fn_80035970(p + 0xb4);
        tgt[0x79] = 0;
        tgt[0xc4] = p[0x1dc];
        tgt[0xc5] = p[0x1dd];
        tgt[0xc6] = p[0x1de];
        tgt[0xc7] = p[0x1df];
        *(f32 *)(tgt + 0xac) = *(f32 *)(p + 0x1e8);
        *(f32 *)(tgt + 0xb0) = *(f32 *)(p + 0x1ec);
        *(f32 *)(tgt + 0xb4) = *(f32 *)(p + 0x1f0);
        *(f32 *)(tgt + 0xc0) = *(f32 *)(p + 0x1fc);
        break;
    }
    p[0x1a4] = 0;
}

#pragma dont_inline reset



void fn_80050E38(void *obj);
void fn_800510E8(void *obj);
void fn_800507F0(void *obj);
u32 fn_800402D4(void *mgr);
u8 *fn_801DDF78(void *obj);
extern u8 lbl_80496754[];
extern const f32 lbl_806407C8;
extern const f32 lbl_806407CC;
extern const f32 lbl_806407D0;
extern const f32 lbl_806407D4;
extern const f32 lbl_806407D8;
extern const f32 lbl_806407E0;

}

struct V3 {
    f32 x, y, z;
    V3() {}
    V3(f32 a, f32 b, f32 c) : x(a), y(b), z(c) {}
};

static inline V3 V3Mul(const Vec3 &a, const V3 &b) {
    f32 z = a.z * b.z; f32 y = a.y * b.y; f32 x = a.x * b.x; return V3(x, y, z);
}

extern "C" {

static inline void CamSetView(u8 *cam, const Vec3 &col) {
    V3 target(lbl_806407E4, lbl_806407CC, lbl_806407E4);
    V3 scale(lbl_806407E8, lbl_806407E8, lbl_806407EC);
    V3 pos = V3Mul(col, scale);
    *(f32 *)(cam + 0x1ac) = pos.x;
    *(f32 *)(cam + 0x1b0) = pos.y;
    *(f32 *)(cam + 0x1b4) = pos.z;
    *(f32 *)(cam + 0x1b8) = GSmath::sYAxis.x;
    *(f32 *)(cam + 0x1bc) = GSmath::sYAxis.y;
    *(f32 *)(cam + 0x1c0) = GSmath::sYAxis.z;
    *(f32 *)(cam + 0x1c4) = target.x;
    *(f32 *)(cam + 0x1c8) = target.y;
    *(f32 *)(cam + 0x1cc) = target.z;
    *(u32 *)(cam + 0x104) |= 0x30;
}

#define CamSetMode(cam) (*(u32 *)((cam) + 0x104) = (*(u32 *)((cam) + 0x104) & ~3) | 1, *(u32 *)((cam) + 0x104) |= 8)

u8 *fn_80033090(u8 *p) {
    u8 *q = p;
    do {
        fn_80035380(q);
        q += 0xb4;
    } while (q < p + 0x168);
    fn_80050E38(p + 0x204);
    fn_80050E38(p + 0x264);
    q = p + 0x2c4;
    do {
        fn_80050324(q);
        q += 0x24;
    } while (q < p + 0x39c);
    fn_800510E8(p + 0x39c);
    fn_800510E8(p + 0x45c);
    fn_800510E8(p + 0x51c);
    fn_80050324(p + 0x5dc);
    fn_80050324(p + 0x600);
    fn_80050324(p + 0x624);
    fn_80050324(p + 0x648);
    fn_80050324(p + 0x66c);
    fn_800507F0(p + 0x690);
    Vec3 col;
    col.x = lbl_806407C8;
    col.y = lbl_806407CC;
    col.z = lbl_806407D0;
    p[0x1a5] = 0;
    void *mgr = fn_800401F4();
    if (mgr == 0) {
        return p;
    }
    f32 aspect = lbl_806407D8;
    u8 *cam = *(u8 **)(lbl_80496754 + 4);
    if ((*(u32 *)(cam + 0x104) & 3) == 1) {
        aspect = *(f32 *)(cam + 0x16c);
        *(f32 *)(cam + 0x168) = lbl_806407D4;
        *(f32 *)(cam + 0x17c) = lbl_806407DC;
        *(f32 *)(cam + 0x180) = lbl_806407E0;
        CamSetMode(cam);
    }
    CamSetView(cam, col);
    *(u8 **)(p + 0x4) = cam;
    fn_80034918();
    fn_800353FC(p, fn_800402D4(mgr));
    p[1] = 1;
    fn_80034918();
    u8 *m;
    if (GSmem::isInitialized()) {
        m = (u8 *)GSmem::allocFromHeap(gGameHeap, 0x264);
    } else {
        m = 0;
    }
    if (m != 0) {
        m = fn_801DDF78(m);
    }
    *(f32 *)(m + 0x168) = lbl_806407D4;
    *(f32 *)(m + 0x16c) = aspect;
    *(f32 *)(m + 0x17c) = lbl_806407DC;
    *(f32 *)(m + 0x180) = lbl_806407E0;
    CamSetMode(m);
    CamSetView(m, col);
    *(u8 **)(p + 0xb8) = m;
    fn_80034918();
    fn_800353FC(p + 0xb4, fn_800402D4(mgr));
    p[0xb5] = 0;
    fn_80034918();
    Screen *s = (Screen *)p;
    for (int i = 0; i < 2; i++, s++) {
        fn_800354FC((u8 *)s, lbl_806407E4, lbl_806407E4, lbl_806407E8, lbl_806407E8);
    }
    fn_800348BC(p, 0);
    p[0x168] = 0;
    *(f32 *)(p + 0x16c) = lbl_806407DC;
    p[0x170] = 0;
    *(f32 *)(p + 0x174) = lbl_806407DC;
    p[0x171] = 0;
    *(s32 *)(p + 0x178) = 0;
    p[0x17c] = 0x19;
    *(f32 *)(p + 0x180) = lbl_806407E4;
    *(f32 *)(p + 0x184) = lbl_806407E4;
    p[0x188] = 0;
    *(f32 *)(p + 0x18c) = lbl_806407E8;
    *(s32 *)(p + 0x190) = 0;
    p[0x194] = 0x1e;
    *(f32 *)(p + 0x198) = lbl_806407E4;
    *(f32 *)(p + 0x19c) = lbl_806407E4;
    *(f32 *)(p + 0x1d0) = lbl_806407E4;
    *(f32 *)(p + 0x1d4) = lbl_806407E4;
    p[0x1dc] = 0xff;
    p[0x1dd] = 0xff;
    p[0x1de] = 0xff;
    p[0x1df] = 0xff;
    *(s32 *)(p + 0x1e4) = 1;
    *(s32 *)(p + 0x1e0) = 0;
    *(f32 *)(p + 0x1e8) = lbl_806407E4;
    *(f32 *)(p + 0x1ec) = lbl_806407E4;
    *(f32 *)(p + 0x1f0) = lbl_806407E4;
    *(f32 *)(p + 0x1f4) = lbl_806407E8;
    *(f32 *)(p + 0x1f8) = lbl_806407E8;
    *(f32 *)(p + 0x1fc) = lbl_806407E8;
    return p;
}

}
