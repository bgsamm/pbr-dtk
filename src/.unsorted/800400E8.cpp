#include ".unsorted/800400E8.hpp"

#include "gs/GSmath.hpp"
#include "gs/GSrender.hpp"
#include "gs/render/GSrenderTarget.hpp"
#include "gs/scene/GScamera.hpp"

#include <cmath>

#include "common.hpp"

class Unk80242B88;

void *operator new(unsigned long);

// TODO Replace with proper imports
extern "C" {
f32 PSVECMag(const Vec *v);
f32 PSVECDistance(const Vec *a, const Vec *b);
f32 PSVECDotProduct(const Vec *a, const Vec *b);
void GXProject(f32 x, f32 y, f32 z, const f32 *mtx, const f32 *pm, const f32 *vp, f32 *sx, f32 *sy, f32 *sz);
GSvec3 fn_8003B674(u32 obj, u32 kind);
f32 fn_8000739C();
f32 fn_8003A5EC(u32 obj, int i);
int fn_800396D4(u32 obj);
u32 fn_80033088();
u32 fn_80033B98(u32 a, u32 id);
void fn_800387E0(Vec *out, u32 obj);
void fn_80038A94(Vec *out, u32 a);
void fn_8003989C(Vec *out, u32 a, u32 b);
void fn_80050324(eftseq::AnimNode<f32> *s);
void fn_8005033C(eftseq::AnimNode<f32> *s, f32 *a, f32 *b, f32 *c, u32 x, f32 f);
void fn_80050388(eftseq::AnimNode<f32> *s);
void fn_80050E38(eftseq::AnimNodeShake *s);
void fn_80050E7C(eftseq::AnimNodeShake *s, u32 a, f32 *b, u32 c, u32 d, u32 e);
void fn_80242B88(Unk80242B88 *target, u16 idx, f32 *x, f32 *y, f32 *w, f32 *h);
void fn_8023EB58(u32, void (*)(), void (*)(), u32, u32);
}

extern const f32 lbl_806408B0;
extern const f32 lbl_806408B4;
extern const f32 lbl_806408B8;
extern const f32 lbl_806408BC;
extern const f32 lbl_806408C8;
extern const f32 lbl_806408CC;
extern const f32 lbl_806408D0;
extern const f32 lbl_806408D4;
extern const f32 lbl_806408D8;
extern const f32 lbl_806408DC;
extern const f32 lbl_806408E0;
extern const f32 lbl_806408E4;
extern const f32 lbl_806408E8;
extern const f32 lbl_806408EC;
extern const f32 lbl_806408F0;
extern const f32 lbl_806408F4;
extern const f32 lbl_806408F8;
extern const f32 lbl_806408FC;
extern const f32 lbl_80640900;
extern const f64 lbl_80640908;
extern const f32 lbl_80640910;
extern const f32 lbl_80640914;
extern const f32 lbl_80640918;
extern const f64 lbl_80640920;
extern const f32 lbl_80640928;
extern const f32 lbl_8064092C;
extern const f64 lbl_80640930;
extern const f64 lbl_80640938;
extern const f32 lbl_80640940;
extern const f32 lbl_80640944;
extern const f32 lbl_80640950;
extern const f32 lbl_80640954;
extern const f32 lbl_80640958;
extern const f32 lbl_8064095C;
extern const f32 lbl_80640960;
extern const f32 lbl_80640964;
extern const f32 lbl_80640968;
extern const f32 lbl_8064096C;
extern const f32 lbl_80640970;
extern u32 lbl_8063F778;

/* lbl_8063EA98 */ Unk80040274 *lbl_8063EA98;

// size: 0x10
struct Unk80040960 {
    /* 0x0 */ f32 _0;
    /* 0x4 */ f32 _4;
    /* 0x8 */ f32 _8;
    /* 0xC */ f32 _c;
};

// size: 0x18
struct Unk80044554 {
    /* 0x00 */ f32 _00;
    /* 0x04 */ f32 _04;
    /* 0x08 */ f32 _08;
    /* 0x0C */ f32 _0c;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
};

class Unk80242B88 : public GSrenderTarget {
public:
    /* 0x20 */ s32 _20;
};

static inline void vcopy(Vec *d, const Vec *s) {
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
}

// TODO Value of object obj read by fn_8003A5EC; which one depends on kind.
static inline f32 fn_8003A5ECByKind(u32 obj, u32 kind) {
    if (kind - 0x15 <= 1) {
        return fn_8003A5EC(obj, 0);
    }
    return fn_8003A5EC(obj, 1);
}

static inline f32 clampAsin(f32 r) {
    if (fabsf(r) >= lbl_806408D4) {
        if (r > lbl_806408B0) {
            return lbl_806408D4;
        }
        return lbl_806408D8;
    }
    if (r >= lbl_806408BC) {
        return lbl_806408DC;
    }
    if (r <= lbl_806408E0) {
        return lbl_806408E4;
    }
    return asinf(r);
}

static inline f32 safeSqrt(f32 x) {
    return (x <= lbl_806408B0) ? lbl_806408B0 : sqrtf(x);
}

static inline int isZeroVec(const Vec *v) {
    if (!(v->x < lbl_80640950 && v->x > lbl_8064096C && v->y < lbl_80640950 && v->y > lbl_8064096C &&
          v->z < lbl_80640950 && v->z > lbl_8064096C)) {
        return 0;
    }
    return 1;
}

// TODO Same as fn_80041204.
static inline Vec *fn_80041204Inline(Unk80040EA4 *e) {
    return &e->_4e8[0]._14;
}

// Nothing in this unit is inlined automatically in the original.
#pragma auto_inline off

// TODO Linear interpolation from a to b.
void fn_800400E8(Vec *out, Vec *a, Vec *b, f32 t) {
    f32 x = a->x + t * (b->x - a->x);
    f32 y = a->y + t * (b->y - a->y);
    f32 z = a->z + t * (b->z - a->z);
    out->x = x;
    out->y = y;
    out->z = z;
}

// TODO Per-frame callback registered by fn_800401A0; updates the cameras.
void fn_80040134() {
    Unk80040274 *p = fn_800401F4();
    if (p) {
        fn_800403B0(p, fn_8000739C());
    }
}

// TODO Second callback registered by fn_800401A0.
void fn_80040174() {
    Unk80040274 *p = fn_800401F4();
    if (p) {
        fn_80040434(p);
    }
}

// TODO Creates the camera manager and registers its callbacks.
void fn_800401A0() {
    Unk80040274 *p = (Unk80040274 *)operator new(sizeof(Unk80040274));
    if (p) {
        p = fn_80040274(p);
    }
    lbl_8063EA98 = p;
    fn_8023EB58(lbl_8063F778, fn_80040134, fn_80040174, 3, 0xc);
}

// TODO Camera manager created by fn_800401A0.
Unk80040274 *fn_800401F4() {
    return lbl_8063EA98;
}

// TODO Detaches object a from every active camera.
void fn_800401FC(Unk80040274 *p, u32 a) {
    u32 i;
    for (i = 0; i < 8; i++) {
        if (p->_4[i]._000) {
            fn_80044770(&p->_4[i], a);
        }
    }
}

// TODO Initializes the camera manager and its 8 cameras.
Unk80040274 *fn_80040274(Unk80040274 *p) {
    Unk80040EA4 *e;
    e = p->_4;
    do {
        fn_80040EA4(e);
        e++;
    } while (e < p->_4 + 8);
    p->_0 = 0;
    return p;
}

// TODO Activates the first free camera; returns its id, 0 when none is free.
u32 fn_800402D4(Unk80040274 *p) {
    int i;
    for (i = 0; i < 8; i++) {
        if (!p->_4[i]._000) {
            fn_80040FA0(&p->_4[i]);
            p->_4[i]._4b4 = i + 1;
            return i + 1;
        }
    }
    return 0;
}

// TODO Deactivates camera id.
void fn_80040358(Unk80040274 *p, u32 id) {
    Unk80040EA4 *e = fn_80040384(p, id);
    if (e) {
        fn_80041064(e);
    }
}

// TODO Camera of an id; NULL for 0 and out-of-range ids.
Unk80040EA4 *fn_80040384(Unk80040274 *p, u32 id) {
    if (id == 0 || id >= 8) {
        return 0;
    }
    return &p->_4[id - 1];
}

// TODO Updates the active cameras by t when the manager is enabled.
void fn_800403B0(Unk80040274 *p, f32 t) {
    u32 i;
    if (p->_0) {
        for (i = 0; i < 8; i++) {
            if (p->_4[i]._000) {
                fn_80043B68(&p->_4[i], t);
            }
        }
    }
}

// TODO Calls fn_8004449C on the active cameras when the manager is enabled.
void fn_80040434(Unk80040274 *p) {
    u32 i;
    if (p->_0) {
        for (i = 0; i < 8; i++) {
            if (p->_4[i]._000) {
                fn_8004449C(&p->_4[i]);
            }
        }
    }
}

// TODO Resets a camera point controller of the owner camera.
void fn_800404A8(Unk800404A8 *c, Unk80040EA4 *owner) {
    f32 z = lbl_806408B0;
    c->_10 = 0;
    c->_14.x = z;
    c->_14.y = z;
    c->_14.z = z;
    c->_50 = z;
    c->_54 = owner;
    c->_00 = 0;
    c->_04 = 0;
    c->_08 = z;
    c->_58[0]._0 = 0;
    c->_58[0]._4 = 0;
    c->_58[1]._0 = 0;
    c->_58[1]._4 = 0;
    c->_58[2]._0 = 0;
    c->_58[2]._4 = 0;
    c->_58[3]._0 = 0;
    c->_58[3]._4 = 0;
}

// TODO Position of the object followed in slot i; FALSE when the slot is empty.
int fn_800404F8(Unk800404A8 *c, int i, Vec *out) {
    Vec tmp;
    u32 a;
    u32 b;
    if (i >= 0 && i < 4) {
        Unk800404F8 *pr = &c->_58[i];
        a = pr->_0;
        if (a != 0) {
            b = pr->_4;
            if (b == 0) {
                b = 0x13;
            }
            fn_8003989C(&tmp, a, b);
            out->x = tmp.x;
            out->y = tmp.y;
            out->z = tmp.z;
            return 1;
        }
    }
    return 0;
}

// TODO Updates the controller without forcing its position.
void fn_80040580(Unk800404A8 *c) {
    fn_80040588(c, 0);
}

// TODO Recomputes the controller position from its mode and followed objects.
void fn_80040588(Unk800404A8 *c, int force) {
    Vec b;
    Vec a;
    Vec p;
    Vec r;
    Vec out1;
    Vec out4;
    Unk80040EA4 *owner = c->_54;
    switch (c->_10) {
        case 1:
            fn_800404F8(c, 0, &p);
            PSVECAdd(&p, &c->_44, &out1);
            {
                f32 z;
                f32 y;
                f32 x;
                c->_14.x = x = out1.x;
                c->_14.y = y = out1.y;
                c->_14.z = z = out1.z;
                c->_38.x = x;
                c->_38.y = y;
                c->_38.z = z;
            }
            fn_800400E8(&c->_2c, &c->_14, &p, lbl_806408B4);
            break;
        case 2: {
            int res;
            if (!fn_800404F8(c, 0, &a)) {
                break;
            }
            if (fn_800404F8(c, 1, &b)) {
                fn_800400E8(&p, &a, &b, lbl_806408B8);
            } else {
                vcopy(&p, &a);
            }
            PSVECAdd(&p, &c->_44, &p);
            res = fn_80040960(c, &r, &p);
            c->_38.x = p.x;
            c->_38.y = p.y;
            c->_38.z = p.z;
            fn_800400E8(&c->_2c, &c->_14, &p, lbl_806408B4);
            if (force || res == 1) {
                c->_14.x = p.x;
                c->_14.y = p.y;
                c->_14.z = p.z;
            } else if (res == 2) {
                c->_14.x = r.x;
                c->_14.y = r.y;
                c->_14.z = r.z;
            }
            break;
        }
        case 4: {
            Vec *t = fn_80042590(owner);
            p.x = t->x;
            p.y = t->y;
            p.z = t->z;
            PSVECAdd(&p, &c->_44, &out4);
            {
                f32 z;
                f32 y;
                f32 x;
                c->_14.x = x = out4.x;
                c->_14.y = y = out4.y;
                c->_14.z = z = out4.z;
                c->_38.x = x;
                c->_38.y = y;
                c->_38.z = z;
            }
            fn_800400E8(&c->_2c, &c->_14, &p, lbl_806408B4);
            break;
        }
    }
}

// TODO Height of the followed objects.
f32 fn_800407B0(Unk800404A8 *c) {
    f32 r = lbl_806408B0;
    if (c->_00) {
        return c->_0c;
    } else {
        switch (c->_10) {
            case 1:
                if (c->_58[0]._0) {
                    r = fn_8003A5ECByKind(c->_58[0]._0, c->_58[0]._4);
                }
                break;
            case 2: {
                u32 a = c->_58[0]._0;
                if (a) {
                    u32 a2 = c->_58[1]._0;
                    if (a2 == 0) {
                        r = fn_8003A5ECByKind(a, c->_58[0]._4);
                    } else if (a == a2) {
                        r = fn_8003A5ECByKind(a, c->_58[0]._4);
                    } else {
                        GSvec3 p1;
                        GSvec3 p0;
                        p0 = fn_8003B674(a, c->_58[0]._4);
                        p1 = fn_8003B674(c->_58[1]._0, c->_58[1]._4);
                        r = lbl_806408B8 * PSVECDistance(&p0, &p1);
                    }
                }
                break;
            }
        }
    }
    return r;
}

// TODO Sets _20 and marks it valid.
void fn_80040928(Unk800404A8 *c, Vec *v) {
    vcopy(&c->_20, v);
    c->_04 |= 1;
}

// TODO Sets flag 2.
void fn_80040950(Unk800404A8 *c) {
    c->_04 |= 2;
}

// TODO Keeps the point inside the screen area; returns 1, or 2 when out holds a moved point.
int fn_80040960(Unk800404A8 *c, Vec *out, Vec *in) {
    Vec scr;
    Unk80040960 rect;
    Unk80040960 center;
    f32 dist;
    GScamera *camera = c->_54->_6cc;
    if (c->_50 <= lbl_806408B0 || camera == NULL) {
        return 1;
    }
    if (!fn_80044554(c->_54, in, &scr)) {
        return 1;
    }
    rect._0 = lbl_806408B0;
    rect._4 = lbl_806408B0;
    rect._8 = GSrender::sInstance->getRenderMode()->fbWidth;
    rect._c = GSrender::sInstance->getRenderMode()->efbHeight;
    center._0 = rect._8 * lbl_806408B8;
    center._4 = rect._c * lbl_806408B8;
    dist = safeSqrt((scr.x - center._0) * (scr.x - center._0) + (scr.y - center._4) * (scr.y - center._4));
    if (c->_50 > dist) {
        return 0;
    } else {
        f32 m = center._4 - c->_50;
        f32 k;
        if (m <= lbl_806408B0) {
            return 0;
        }
        k = (dist - c->_50) / m;
        if (k > lbl_806408BC) {
            k = lbl_806408BC;
        }
        fn_800400E8(out, &c->_14, in, k * lbl_806408B4);
        return 2;
    }
}

// TODO Follows object a (slot b) with an offset.
void fn_80040AE0(Unk800404A8 *c, u32 a, u32 b, Vec *v) {
    vcopy(&c->_44, v);
    c->_58[0]._0 = a;
    c->_58[0]._4 = b;
    c->_10 = 1;
    fn_80040588(c, 1);
}

// TODO Follows the camera target with an offset.
void fn_80040B10(Unk800404A8 *c, Vec *v) {
    vcopy(&c->_44, v);
    c->_10 = 4;
    fn_80040588(c, 1);
}

// TODO Follows the point between objects a and a2 with an offset.
void fn_80040B38(Unk800404A8 *c, u32 a, u32 b, u32 a2, u32 b2, f32 f, Vec *v) {
    if (a != 0) {
        c->_10 = 2;
    }
    c->_58[0]._0 = a;
    c->_58[0]._4 = b;
    c->_58[1]._0 = a2;
    c->_58[1]._4 = b2;
    c->_50 = f;
    c->_44.x = v->x;
    c->_44.y = v->y;
    c->_44.z = v->z;
    fn_80040588(c, 1);
}

// TODO Object followed in slot i.
u32 fn_80040B7C(Unk800404A8 *c, int i) {
    if (i >= 0 && i < 4) {
        return c->_58[i]._0;
    }
    return 0;
}

// TODO Updates the position, then switches to another mode.
void fn_80040BA4(Unk800404A8 *c, int mode) {
    fn_80040588(c, 1);
    c->_10 = mode;
}

// TODO Places the controller at a fixed position.
void fn_80040BE4(Unk800404A8 *c, Vec *v) {
    fn_80040BA4(c, 0);
    vcopy(&c->_14, v);
}

// TODO Angle used as the yaw reference; the followed object's when there is one.
f32 fn_80040C38(Unk800404A8 *c) {
    u32 a;
    if (c->_00) {
        return c->_08;
    }
    a = 0;
    if (c->_58[0]._0) {
        a = c->_58[0]._0;
    } else if (c->_58[1]._0) {
        a = c->_58[1]._0;
    }
    if (a) {
        Vec tmp;
        fn_80038A94(&tmp, a);
        return tmp.y;
    }
    return lbl_806408B0;
}

// TODO Interpolates two controllers into d.
void fn_80040CAC(Unk800404A8 *d, Unk800404A8 *a, Unk800404A8 *b, f32 t) {
    d->_10 = a->_10;
    d->_00 = 1;
    if (b->_04 & 1) {
        fn_800400E8(&d->_14, &b->_20, &b->_14, t);
    } else {
        fn_800400E8(&d->_14, &a->_14, &b->_14, t);
    }
    fn_800400E8(&d->_2c, &a->_2c, &b->_2c, t);
    fn_800400E8(&d->_38, &a->_38, &b->_38, t);
    fn_800400E8(&d->_44, &a->_44, &b->_44, t);
    d->_50 = a->_50 + t * (b->_50 - a->_50);
    d->_58[0]._0 = a->_58[0]._0;
    d->_58[0]._4 = a->_58[0]._4;
    d->_58[1]._0 = a->_58[1]._0;
    d->_58[1]._4 = a->_58[1]._4;
    d->_58[2]._0 = a->_58[2]._0;
    d->_58[2]._4 = a->_58[2]._4;
    d->_58[3]._0 = a->_58[3]._0;
    d->_58[3]._4 = a->_58[3]._4;
    if (b->_04 & 2) {
        d->_08 = fn_80040C38(b);
    } else {
        f32 x = fn_80040C38(a);
        d->_08 = x + t * (fn_80040C38(b) - x);
    }
    {
        f32 y = fn_800407B0(a);
        d->_0c = y + t * (fn_800407B0(b) - y);
    }
}

// TODO Removes object id from the followed slots.
void fn_80040E48(Unk800404A8 *c, u32 id) {
    int i;
    for (i = 0; i < 4; i++) {
        u32 a = c->_58[i]._0;
        if (a == id) {
            c->_58[i]._0 = 0;
            c->_58[i]._4 = 0;
        }
    }
}

// TODO Initializes a camera.
Unk80040EA4 *fn_80040EA4(Unk80040EA4 *e) {
    eftseq::AnimNode<f32> *p;
    eftseq::AnimNodeShake *q;
    p = e->_004;
    do {
        fn_80050324(p);
        p++;
    } while (p < e->_004 + 12);
    q = e->_1b4;
    do {
        fn_80050E38(q);
        q++;
    } while (q < e->_1b4 + 5);
    fn_80050E38(&e->_394);
    fn_80050E38(&e->_3f4);
    fn_80050E38(&e->_454);
    fn_800404A8(&e->_4e8[0], e);
    fn_800404A8(&e->_4e8[1], e);
    fn_800404A8(&e->_4e8[2], e);
    fn_800404A8(&e->_4e8[3], e);
    e->_000 = 0;
    e->_6cc = 0;
    e->_002 = 0;
    e->_4bc = 0;
    e->_4d0 = lbl_806408BC;
    e->_4cc = lbl_806408B4;
    e->_4c8 = lbl_806408B0;
    e->_6dc = lbl_806408B0;
    e->_6f0 = lbl_806408B0;
    e->_6ec = lbl_806408B0;
    e->_6e8 = lbl_806408B0;
    e->_6e4 = lbl_806408B0;
    e->_6e0 = lbl_806408B0;
    return e;
}

// TODO Activates a camera with its default eye and target.
void fn_80040FA0(Unk80040EA4 *e) {
    Vec a;
    Vec b;
    Vec c;
    e->_000 = 1;
    e->_4e0 = lbl_806408C8;
    fn_80050388(&e->_004[0]);
    e->_001 = 1;
    a.x = lbl_806408B0;
    a.y = lbl_806408CC;
    a.z = lbl_806408D0;
    fn_800410AC(e, &a);
    b.x = lbl_806408B0;
    b.y = lbl_806408B0;
    b.z = lbl_806408B0;
    fn_80042534(e, &b);
    c.x = lbl_806408B0;
    c.y = lbl_806408CC;
    c.z = lbl_806408D0;
    e->_6c8 = PSVECMag(&c);
    e->_6f4 = lbl_806408B0;
    e->_6f8 = 0;
    e->_001 = 1;
}

// TODO Deactivates the camera.
void fn_80041064(Unk80040EA4 *e) {
    e->_000 = 0;
}

// TODO Starts a tween of _4e0 towards a over b, with curve x.
void fn_80041070(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->_004[0], &e->_4e0, &t, &e->_4e0, x, b);
}

// TODO Sets the eye position and cancels the automatic eye placement.
void fn_800410AC(Unk80040EA4 *e, Vec *v) {
    e->_4bc = 0;
    e->_002 = 0;
    fn_800410BC(e, v);
}

// TODO Sets the eye position and stops its tweens.
void fn_800410BC(Unk80040EA4 *e, Vec *v) {
    fn_80040BE4(&e->_4e8[0], v);
    fn_80050388(&e->_004[2]);
    fn_80050388(&e->_004[3]);
    fn_80050388(&e->_004[4]);
    fn_80050388(&e->_004[8]);
    fn_80050388(&e->_004[9]);
    e->_001 = 1;
}

// TODO Places the eye around the target from yaw x, pitch y and distance d.
void fn_8004111C(Unk80040EA4 *e, f32 x, f32 y, f32 d) {
    GSvec3 tmp;
    GSquat q;
    GSvec3 temp;
    GSvec3 out;
    GSvec3 v;
    GSvec3 ang;
    ang.set(-y, x, lbl_806408B0);
    GSmath::eulerToQuat(&q, &ang);
    temp.set(lbl_806408B0, lbl_806408B0, d);
    v = temp;
    GSmath::rotateVec3ByQuat(&v, &q);
    PSVECAdd(&e->_4e8[1]._14, &v, &out);
    tmp = out;
    fn_80040BE4(&e->_4e8[0], &tmp);
    e->_4bc = 0;
    e->_002 = 0;
    fn_80050388(&e->_004[2]);
    fn_80050388(&e->_004[3]);
    fn_80050388(&e->_004[4]);
    e->_001 = 1;
}

// TODO Eye position.
Vec *fn_80041204(Unk80040EA4 *e) {
    return &e->_4e8[0]._14;
}

// TODO Sets the lowest eye height.
void fn_8004120C(Unk80040EA4 *e, f32 f) {
    e->_6f4 = f;
    e->_6f8 = 1;
}

// TODO Removes the lowest eye height.
void fn_8004121C(Unk80040EA4 *e) {
    e->_6f8 = 0;
}

// TODO Computes the eye position from the angles and distance around controller c.
void fn_80041228(Unk80040EA4 *e, Unk800404A8 *c) {
    Vec d;
    GSvec3 tmp;
    GSquat q;
    GSvec3 off;
    GSvec3 out;
    GSvec3 v;
    GSvec3 ang;
    Vec *tgt = &c->_14;
    f32 yaw0;
    f32 dist;
    f32 yaw;
    f32 pitch;
    PSVECSubtract(&e->_4e8[0]._14, tgt, &d);
    yaw0 = fn_80040C38(c);
    if (e->_4bc & 0x20) {
        f32 h = fn_800407B0(c);
        e->_6c8 = fn_80041524(e, c) - h;
        dist = e->_6e8 + (e->_6c8 + fn_800407B0(c));
    } else {
        dist = e->_6e8 + (e->_6c8 + fn_800407B0(c));
    }
    off.set(lbl_806408B0, lbl_806408B0, dist);
    if (e->_004[8]._00) {
        yaw = e->_4d8 + yaw0;
    } else if (e->_4bc & 0x10) {
        yaw = e->_4c0 + yaw0;
    } else {
        yaw = atan2f(d.x, d.z);
    }
    if (e->_004[9]._00) {
        pitch = e->_4dc;
    } else if (e->_4bc & 0x40) {
        pitch = clampAsin((e->_4c8 - tgt->y) / dist);
    } else if (e->_4bc & 0x8) {
        pitch = fn_80043B10(e, e->_4c4);
    } else {
        pitch = clampAsin(d.y / PSVECMag(&d));
    }
    ang.set(-pitch - e->_6f0, yaw + e->_6ec, lbl_806408B0);
    GSmath::eulerToQuat(&q, &ang);
    v = off;
    GSmath::rotateVec3ByQuat(&v, &q);
    PSVECAdd(tgt, &v, &out);
    tmp = out;
    fn_80040BE4(&e->_4e8[0], &tmp);
    e->_001 = 1;
}

// TODO Distance that frames the objects followed by controller c.
f32 fn_80041524(Unk80040EA4 *e, Unk800404A8 *c) {
    f32 r;
    switch (c->_10) {
        case 1:
            if (fn_80040B7C(c, 0)) {
                r = fn_800439EC(e, fn_80040B7C(c, 0), e->_4d4);
            } else {
                r = e->_6c8;
            }
            break;
        case 2:
            if (fn_80040B7C(c, 0)) {
                if (fn_80040B7C(c, 1) == 0) {
                    r = fn_800439EC(e, fn_80040B7C(c, 0), e->_4d4);
                } else if (fn_80040B7C(c, 0) == fn_80040B7C(c, 1)) {
                    r = fn_800439EC(e, fn_80040B7C(c, 0), e->_4d4);
                } else {
                    r = fn_800439EC(e, fn_80040B7C(c, 0), e->_4d4) + fn_800407B0(c);
                }
            } else {
                r = e->_6c8;
            }
            break;
        default: r = e->_6c8; break;
    }
    return r;
}

// TODO Starts the automatic eye placement with all its parameters.
void fn_80041690(Unk80040EA4 *e, f32 a, f32 b, f32 c, u32 x, u32 y) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4c0 = a;
    e->_4c4 = x;
    e->_4cc = c;
    e->_4d0 = b;
    e->_4d4 = y;
    e->_4bc = 0x3f;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->_4e8[1]);
    }
}

// TODO Starts the automatic eye placement for yaw a.
void fn_800416E8(Unk80040EA4 *e, f32 a, f32 b, f32 c) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4c0 = a;
    e->_4bc |= 0x17;
    e->_4cc = c;
    e->_4d0 = b;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->_4e8[1]);
    }
}

// TODO Starts the automatic eye placement with framing mode x.
void fn_8004173C(Unk80040EA4 *e, f32 b, f32 c, u32 x) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4bc |= 0xf;
    e->_4c4 = x;
    e->_4bc &= ~0x40;
    e->_4cc = c;
    e->_4d0 = b;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->_4e8[1]);
    }
}

// TODO Starts the automatic eye placement with distance mode y.
void fn_80041794(Unk80040EA4 *e, f32 b, f32 c, u32 y) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4d4 = y;
    e->_4bc |= 0x27;
    e->_4cc = c;
    e->_4d0 = b;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->_4e8[1]);
    }
}

// TODO Starts the automatic eye placement for pitch a.
void fn_800417E8(Unk80040EA4 *e, f32 a, f32 b, f32 c) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4bc |= 0x47;
    e->_4bc &= ~0x8;
    fn_80050388(&e->_004[9]);
    e->_4c8 = a;
    e->_4cc = c;
    e->_4d0 = b;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->_4e8[1]);
    }
}

// TODO Stops parts of the automatic eye placement.
void fn_800418AC(Unk80040EA4 *e, u32 flags) {
    if (flags & 1) {
        e->_4bc = 0;
        fn_80040BA4(&e->_4e8[0], 0);
        e->_002 = 0;
    } else {
        if (flags & 4) {
            e->_4bc &= ~0x8;
        }
        if (flags & 2) {
            e->_4bc &= ~0x10;
        }
        if (flags & 8) {
            e->_4bc &= ~0x20;
        }
        if (flags & 0x10) {
            e->_4bc &= ~0x40;
        }
    }
}

// TODO Starts a tween of _4c8 towards a over b, with curve x.
void fn_80041950(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->_004[11], &e->_4c8, &t, &e->_4c8, x, b);
}

// TODO Makes the eye follow object a.
void fn_8004198C(Unk80040EA4 *e, u32 a, u32 b, Vec *v) {
    fn_80040AE0(&e->_4e8[0], a, b, v);
    e->_4bc = 0;
    fn_80050388(&e->_004[2]);
    fn_80050388(&e->_004[3]);
    fn_80050388(&e->_004[4]);
    e->_001 = 1;
}

// TODO Makes the eye follow the target, at offset v or at the current offset.
void fn_800419E4(Unk80040EA4 *e, Vec *v) {
    Vec l;
    Vec tmp;
    if (v == 0) {
        Vec *p = fn_80042590(e);
        PSVECSubtract(fn_80041204(e), p, &tmp);
        vcopy(&l, &tmp);
    } else {
        l.x = v->x;
        l.y = v->y;
        l.z = v->z;
    }
    fn_80040B10(&e->_4e8[0], &l);
    e->_4bc = 0;
    e->_001 = 1;
}

// TODO Makes the eye follow the target at the offset given by angles and distance.
void fn_80041A88(Unk80040EA4 *e, f32 f1, f32 f2, f32 f3) {
    Vec l;
    Vec tmp;
    fn_80041B58(&tmp, e, f1, f2, f3);
    vcopy(&l, &tmp);
    fn_800419E4(e, &l);
}

// TODO Starts tween _1b4[0] on _6e0.
void fn_80041AE0(Unk80040EA4 *e, u32 a, u32 b) {
    fn_80050E7C(&e->_1b4[0], a, &e->_6e0, b, 0, 0);
}

// TODO Starts tween _1b4[1] on _6e4.
void fn_80041AF8(Unk80040EA4 *e, u32 a, u32 b) {
    fn_80050E7C(&e->_1b4[1], a, &e->_6e4, b, 0, 0);
}

// TODO Starts tween _1b4[3] on _6ec.
void fn_80041B10(Unk80040EA4 *e, u32 a, u32 b) {
    fn_80050E7C(&e->_1b4[3], a, &e->_6ec, b, 0, 0);
}

// TODO Starts tween _1b4[4] on _6f0.
void fn_80041B28(Unk80040EA4 *e, u32 a, u32 b) {
    fn_80050E7C(&e->_1b4[4], a, &e->_6f0, b, 0, 0);
}

// TODO Starts tween _1b4[2] on _6e8.
void fn_80041B40(Unk80040EA4 *e, u32 a, u32 b) {
    fn_80050E7C(&e->_1b4[2], a, &e->_6e8, b, 0, 0);
}

// TODO Offset from the target for the given angles and distance.
void fn_80041B58(Vec *out, Unk80040EA4 *e, f32 a, f32 b, f32 c) {
    GSvec3 dir;
    GSquat q;
    Vec tv;
    Vec p1;
    Vec p2;
    Vec p4;
    Vec p3;
    GSvec3 eul;
    u32 obj;
    Unk800404A8 *ctl;
    f32 yaw;
    f32 h;
    f32 t;
    dir.set(lbl_806408B0, lbl_806408B0, lbl_806408BC);
    if (e->_6d0) {
        ctl = &e->_4e8[3];
    } else {
        ctl = &e->_4e8[1];
    }
    obj = fn_80040B7C(ctl, 0);
    if (obj) {
        fn_80038A94(&tv, obj);
        yaw = tv.y;
    } else {
        yaw = lbl_806408B0;
    }
    if (isinf(yaw)) {
        yaw = lbl_806408B0;
    }
    if (isnan(yaw)) {
        yaw = lbl_806408B0;
    }
    while (yaw < lbl_806408B0) {
        yaw += lbl_806408EC;
    }
    while (yaw > lbl_806408EC) {
        yaw -= lbl_806408EC;
    }
    if (yaw <= lbl_806408F0 || yaw >= lbl_806408F4) {
        a = yaw - a;
    } else if (lbl_806408F8 <= yaw && yaw <= lbl_806408FC) {
        a = yaw + a;
    } else if (lbl_806408F0 < yaw && yaw < lbl_806408F8) {
        if (fn_80042590(e)->z < lbl_806408B0) {
            a = yaw - a;
        } else {
            a = yaw + a;
        }
    } else {
        if (fn_80042590(e)->z < lbl_806408B0) {
            a = yaw + a;
        } else {
            a = yaw - a;
        }
    }
    if (obj) {
        u32 obj2 = fn_80040B7C(ctl, 1);
        if (obj2 == 0 || obj2 == obj) {
            h = fn_8003A5EC(obj, 1);
            if (h < lbl_80640900) {
                h = lbl_80640900;
            }
            h = h / (f32)tan(lbl_80640908);
            if (fn_800396D4(obj) <= 1) {
                c *= lbl_80640910 * h;
            } else {
                c *= lbl_80640914 + lbl_80640918 * h;
            }
        } else {
            fn_800387E0(&p2, obj2);
            t = p2.x;
            fn_800387E0(&p1, obj);
            if (p1.x < t) {
                t = fn_8003A5EC(obj, 1);
            } else {
                t = fn_8003A5EC(obj2, 1);
            }
            h = t / (f32)tan(lbl_80640920);
            fn_800387E0(&p3, obj2);
            t = p3.x;
            fn_800387E0(&p4, obj);
            c *= lbl_80640918 * h + lbl_806408B8 * fabsf(p4.x - t);
        }
    } else {
        c = lbl_80640928 * c;
    }
    eul.set(-b, a, lbl_806408B0);
    GSmath::eulerToQuat(&q, &eul);
    GSmath::rotateVec3ByQuat(&dir, &q);
    PSVECScale(&dir, out, c);
}

// TODO Keeps pos outside the area around center.
void fn_80041ED4(Vec *pos, Vec *center) {
    Vec p;
    Vec n;
    Vec d;
    Vec d2;
    Vec o;
    Vec sc;
    Vec d3;
    Vec o2;
    Vec sc2;
    f32 a;
    f32 s;
    f32 b;
    p.x = pos->x;
    p.y = pos->y;
    p.z = pos->z;
    p.y = lbl_806408B0;
    if (PSVECMag(&p) > lbl_8064092C) {
        f32 r;
        PSVECSubtract(center, &p, &d);
        vcopy(&n, &d);
        PSVECNormalize(&n, &n);
        a = pow(PSVECDotProduct(&n, &p), lbl_80640930);
        b = PSVECDotProduct(&p, &p);
        r = pow(lbl_80640938, lbl_80640930);
        r = r + (a - b);
        s = -PSVECDotProduct(&n, &p) - safeSqrt(r);
        p.x = pos->x;
        p.y = pos->y;
        p.z = pos->z;
        PSVECSubtract(center, &p, &d2);
        vcopy(&n, &d2);
        PSVECNormalize(&n, &n);
        PSVECScale(&n, &sc, s);
        PSVECAdd(&p, &sc, &o);
        vcopy(&p, &o);
        pos->x = p.x;
        pos->y = p.y;
        pos->z = p.z;
    }
    p.x = pos->x;
    p.y = pos->y;
    p.z = pos->z;
    if (p.y > lbl_80640940) {
        s = lbl_80640940 / p.y;
        PSVECSubtract(&p, center, &d3);
        vcopy(&n, &d3);
        b = PSVECMag(&n);
        PSVECNormalize(&n, &n);
        PSVECScale(&n, &sc2, b * s);
        PSVECAdd(center, &sc2, &o2);
        vcopy(&p, &o2);
        pos->x = p.x;
        pos->y = p.y;
        pos->z = p.z;
    }
}

// TODO Places the eye at the given angles and distance from the target.
void fn_8004215C(Unk80040EA4 *e, f32 f1, f32 f2, f32 f3) {
    Vec a;
    Vec b;
    Vec tmp;
    Vec *p;
    fn_80041B58(&tmp, e, f1, f2, f3);
    vcopy(&a, &tmp);
    p = fn_80042590(e);
    b.x = p->x;
    b.y = p->y;
    b.z = p->z;
    PSVECAdd(&a, &b, &a);
    fn_80041ED4(&a, &b);
    fn_800410AC(e, &a);
}

// TODO Places the eye at the given yaw, height and distance from the target.
void fn_800421F0(Unk80040EA4 *e, f32 a, f32 b, f32 c) {
    Unk800404A8 *ctl;
    u32 *obj;
    if (e->_6d0) {
        ctl = &e->_4e8[3];
    } else {
        ctl = &e->_4e8[1];
    }
    obj = (u32 *)fn_80040B7C(ctl, 0);
    if (obj && (*obj & 0x1000)) {
        fn_8004215C(e, a, lbl_80640944, c);
    } else {
        Vec A;
        Vec B;
        Vec tmp;
        Vec *p;
        fn_80041B58(&tmp, e, a, lbl_806408B0, c);
        vcopy(&A, &tmp);
        p = fn_80042590(e);
        B.x = p->x;
        B.y = p->y;
        B.z = p->z;
        PSVECAdd(&A, &B, &A);
        A.y = b;
        fn_80041ED4(&A, &B);
        fn_800410AC(e, &A);
    }
}

// TODO Moves the eye to the given angles and distance from the target over time.
void fn_8004231C(Unk80040EA4 *e, u32 x, f32 f1, f32 f2, f32 f3, f32 f4) {
    Vec a;
    Vec b;
    Vec tmp;
    Vec *p;
    fn_80041B58(&tmp, e, f1, f2, f3);
    vcopy(&a, &tmp);
    p = fn_80042590(e);
    b.x = p->x;
    b.y = p->y;
    b.z = p->z;
    PSVECAdd(&a, &b, &a);
    fn_80041ED4(&a, &b);
    fn_8004283C(e, &a, x, f4);
}

// TODO Moves the eye to the given yaw, height and distance from the target over time.
void fn_800423D8(Unk80040EA4 *e, u32 x, f32 a, f32 b, f32 c, f32 d) {
    Unk800404A8 *ctl;
    u32 *obj;
    if (e->_6d0) {
        ctl = &e->_4e8[3];
    } else {
        ctl = &e->_4e8[1];
    }
    obj = (u32 *)fn_80040B7C(ctl, 0);
    if (obj && (*obj & 0x1000)) {
        fn_8004231C(e, x, a, lbl_80640944, c, d);
    } else {
        Vec A;
        Vec B;
        Vec tmp;
        Vec *p;
        fn_80041B58(&tmp, e, a, lbl_806408B0, c);
        vcopy(&A, &tmp);
        p = fn_80042590(e);
        B.x = p->x;
        B.y = p->y;
        B.z = p->z;
        PSVECAdd(&A, &B, &A);
        A.y = b;
        fn_80041ED4(&A, &B);
        fn_8004283C(e, &A, x, d);
    }
}

// TODO Sets the target position and stops its tweens.
void fn_80042534(Unk80040EA4 *e, Vec *v) {
    fn_80040BE4(&e->_4e8[1], v);
    fn_80050388(&e->_004[5]);
    fn_80050388(&e->_004[6]);
    fn_80050388(&e->_004[7]);
    u32 f = e->_6d0;
    e->_001 = 1;
    e->_6d0 = f & ~3;
}

// TODO Target position, or the blended one during a transition.
Vec *fn_80042590(Unk80040EA4 *e) {
    if (e->_6d0) {
        return &e->_4e8[2]._14;
    }
    return &e->_4e8[1]._14;
}

// TODO Makes the target follow object a.
void fn_800425AC(Unk80040EA4 *e, u32 a, u32 b, Vec *v) {
    fn_80040AE0(&e->_4e8[1], a, b, v);
    fn_80050388(&e->_004[5]);
    fn_80050388(&e->_004[6]);
    fn_80050388(&e->_004[7]);
    e->_001 = 1;
}

// TODO Sets the eye distance from the target.
void fn_800425FC(Unk80040EA4 *e, f32 f) {
    Vec d;
    f32 r = fn_800407B0(&e->_4e8[1]);
    e->_6c8 = f;
    fn_80040588(&e->_4e8[0], 1);
    d.x = e->_4e8[0]._14.x;
    d.y = e->_4e8[0]._14.y;
    d.z = e->_4e8[0]._14.z;
    PSVECSubtract(&d, &e->_4e8[1]._14, &d);
    PSVECNormalize(&d, &d);
    PSVECScale(&d, &d, f + r);
    PSVECAdd(&d, &e->_4e8[1]._14, &d);
    fn_80040BE4(&e->_4e8[0], &d);
    e->_001 = 1;
}

// TODO Sets the roll.
void fn_800426CC(Unk80040EA4 *e, f32 f) {
    e->_6dc = f;
    fn_80050388(&e->_004[10]);
    e->_001 = 1;
}

// TODO Roll.
f32 fn_80042708(Unk80040EA4 *e) {
    return e->_6dc;
}

// TODO Starts a tween of the roll towards a over b, with curve x.
void fn_80042710(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->_004[10], &e->_6dc, &t, &e->_6dc, x, b);
}

// TODO Distance between the eye and the target.
f32 fn_8004274C(Unk80040EA4 *e) {
    Vec *p = fn_80042590(e);
    return PSVECDistance(fn_80041204(e), p);
}

// TODO Height of the objects followed by the target.
f32 fn_80042794(Unk80040EA4 *e) {
    return fn_800407B0(&e->_4e8[1]);
}

// TODO Starts a tween of the eye distance towards a over b, with curve x.
void fn_8004279C(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    f32 base;
    e->_4bc &= ~0x20;
    base = fn_80042794(e);
    fn_800425FC(e, fn_8004274C(e) - base);
    fn_8005033C(&e->_004[1], &e->_6c8, &t, &e->_6c8, x, b);
}

// TODO Moves the eye to v over time, above the lowest height.
void fn_8004283C(Unk80040EA4 *e, Vec *v, u32 x, f32 f) {
    f32 y1;
    f32 y0;
    f32 vy;
    fn_80040BA4(&e->_4e8[0], 0);
    vy = v->y;
    e->_4bc = 0;
    if (vy < e->_6f4 && e->_6f8) {
        y0 = e->_6f4;
    } else {
        y0 = v->y;
    }
    if (e->_4e8[0]._14.y < e->_6f4 && e->_6f8) {
        y1 = e->_6f4;
    } else {
        y1 = e->_4e8[0]._14.y;
    }
    fn_8005033C(&e->_004[2], &e->_4e8[0]._14.x, &v->x, &e->_4e8[0]._14.x, x, f);
    fn_8005033C(&e->_004[3], &y1, &y0, &e->_4e8[0]._14.y, x, f);
    fn_8005033C(&e->_004[4], &e->_4e8[0]._14.z, &v->z, &e->_4e8[0]._14.z, x, f);
}

// TODO Brings angle a within one turn of b.
f32 fn_80042950(Unk80040EA4 *e, f32 a, f32 b) {
    f32 p = lbl_806408EC;
    int n = (int)(b / p);
    f32 hi;
    f32 lo;
    if (b < lbl_806408B0) {
        hi = (f32)n * p;
        lo = (f32)(n - 1) * p;
    } else {
        lo = (f32)n * p;
        hi = (f32)(n + 1) * p;
    }
    while (a < lo) {
        a += p;
    }
    while (a > hi) {
        a -= p;
    }
    return a;
}

// TODO Starts a tween of the eye height towards a over b.
void fn_80042A0C(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_80040BA4(&e->_4e8[0], 0);
    e->_4bc &= ~0x8;
    fn_8005033C(&e->_004[3], &e->_4e8[0]._14.y, &t, &e->_4e8[0]._14.y, x, b);
}

// TODO Starts a tween of the yaw towards a over b.
void fn_80042A84(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    Vec d;
    f32 ang;
    d.x = e->_4e8[0]._14.x;
    d.y = e->_4e8[0]._14.y;
    d.z = e->_4e8[0]._14.z;
    PSVECSubtract(&d, &e->_4e8[1]._14, &d);
    ang = atan2f(d.x, d.z);
    e->_4bc &= ~0x10;
    fn_8005033C(&e->_004[8], &ang, &a, &e->_4d8, x, b);
}

// TODO Starts tweens of the yaw and pitch relative to the target reference.
void fn_80042B34(Unk80040EA4 *e, f32 a, f32 b, f32 c, u32 x) {
    Vec d;
    f32 ang;
    f32 elev;
    f32 r;
    d.x = e->_4e8[0]._14.x;
    d.y = e->_4e8[0]._14.y;
    d.z = e->_4e8[0]._14.z;
    PSVECSubtract(&d, &e->_4e8[1]._14, &d);
    if (e->_6d0 & 2) {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->_4e8[3]);
    } else {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->_4e8[1]);
    }
    ang = fn_80042950(e, ang, a);
    r = d.y / PSVECMag(&d);
    if (r >= lbl_806408BC) {
        r = lbl_806408DC;
    } else if (r <= lbl_806408E0) {
        r = lbl_806408E4;
    } else {
        r = asinf(r);
    }
    elev = r;
    e->_4bc &= ~0x18;
    fn_8005033C(&e->_004[8], &ang, &a, &e->_4d8, x, c);
    fn_8005033C(&e->_004[9], &elev, &b, &e->_4dc, x, c);
}

// TODO Starts a tween of the yaw relative to the target reference.
void fn_80042CB0(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    Vec d;
    f32 ang;
    d.x = e->_4e8[0]._14.x;
    d.y = e->_4e8[0]._14.y;
    d.z = e->_4e8[0]._14.z;
    PSVECSubtract(&d, &e->_4e8[1]._14, &d);
    if (e->_6d0 & 2) {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->_4e8[3]);
    } else {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->_4e8[1]);
    }
    ang = fn_80042950(e, ang, a);
    e->_4bc &= ~0x10;
    fn_8005033C(&e->_004[8], &ang, &a, &e->_4d8, x, b);
}

// TODO Starts a tween of the pitch towards a over b.
void fn_80042DC0(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    Vec d;
    f32 ang;
    f32 r;
    d.x = e->_4e8[0]._14.x;
    d.y = e->_4e8[0]._14.y;
    d.z = e->_4e8[0]._14.z;
    PSVECSubtract(&d, &e->_4e8[1]._14, &d);
    r = d.y / PSVECMag(&d);
    if (r >= lbl_806408BC) {
        r = lbl_806408DC;
    } else if (r <= lbl_806408E0) {
        r = lbl_806408E4;
    } else {
        r = asinf(r);
    }
    ang = r;
    e->_4bc &= ~0x8;
    fn_8005033C(&e->_004[9], &ang, &a, &e->_4dc, x, b);
}

// TODO Moves the target to src over time.
void fn_80042EA8(Unk80040EA4 *e, f32 f, Vec *src, u32 x) {
    Vec *p = &e->_4e8[1]._14;
    fn_80040BA4(&e->_4e8[1], 0);
    fn_8005033C(&e->_004[5], &p->x, &src->x, &p->x, x, f);
    fn_8005033C(&e->_004[6], &p->y, &src->y, &p->y, x, f);
    fn_8005033C(&e->_004[7], &p->z, &src->z, &p->z, x, f);
}

// TODO Starts a tween of the target height towards a over b.
void fn_80042F60(Unk80040EA4 *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_80040BA4(&e->_4e8[1], 0);
    fn_8005033C(&e->_004[6], &e->_4e8[1]._14.y, &t, &e->_4e8[1]._14.y, x, b);
}

// TODO Starts a transition of the target to object a.
void fn_80042FCC(Unk80040EA4 *e, u32 a, u32 b, f32 f, f32 g, Vec *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->_4e8[1], a, b, 0, 0, f, v);
        e->_6d0 &= ~3;
    } else {
        Vec tmp;
        if (e->_6d0) {
            e->_4e8[1] = e->_4e8[2];
        } else {
            e->_4e8[2] = e->_4e8[1];
        }
        fn_80040B38(&e->_4e8[3], a, b, 0, 0, f, v);
        e->_6d0 |= 1;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->_4e8[1]._14.x;
        tmp.y = e->_4e8[1]._14.y;
        tmp.z = e->_4e8[1]._14.z;
        fn_80040928(&e->_4e8[3], &tmp);
    }
    e->_002 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->_004[5]);
    fn_80050388(&e->_004[6]);
    fn_80050388(&e->_004[7]);
    e->_001 = 1;
}

// TODO Starts a transition of the target to the point between objects a and a2.
void fn_80043310(Unk80040EA4 *e, u32 a, u32 b, u32 a2, u32 b2, f32 f, f32 g, Vec *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->_4e8[1], a, b, a2, b2, f, v);
        e->_6d0 &= ~3;
    } else {
        Vec tmp;
        if (e->_6d0) {
            e->_4e8[1] = e->_4e8[2];
        } else {
            e->_4e8[2] = e->_4e8[1];
        }
        fn_80040B38(&e->_4e8[3], a, b, a2, b2, f, v);
        e->_6d0 |= 1;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->_4e8[1]._14.x;
        tmp.y = e->_4e8[1]._14.y;
        tmp.z = e->_4e8[1]._14.z;
        fn_80040928(&e->_4e8[3], &tmp);
    }
    e->_002 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->_004[5]);
    fn_80050388(&e->_004[6]);
    fn_80050388(&e->_004[7]);
    e->_001 = 1;
}

// TODO Starts a transition of the target to an offset from the target.
void fn_8004363C(Unk80040EA4 *e, u32 a, u32 b, f32 f, f32 g, Vec *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->_4e8[1], a, b, 0, 0, f, v);
        e->_6d0 &= ~3;
    } else {
        Vec tmp;
        if (e->_6d0) {
            e->_4e8[1] = e->_4e8[2];
        } else {
            e->_4e8[2] = e->_4e8[1];
        }
        fn_80040B38(&e->_4e8[3], a, b, 0, 0, f, v);
        e->_6d0 |= 2;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->_4e8[1]._14.x;
        tmp.y = e->_4e8[1]._14.y;
        tmp.z = e->_4e8[1]._14.z;
        fn_80040928(&e->_4e8[3], &tmp);
        fn_80040950(&e->_4e8[3]);
    }
    e->_002 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->_004[5]);
    fn_80050388(&e->_004[6]);
    fn_80050388(&e->_004[7]);
    e->_001 = 1;
}

// TODO Clears the target followed objects.
void fn_80043988(Unk80040EA4 *e) {
    Vec z;
    z.x = lbl_806408B0;
    z.y = lbl_806408B0;
    z.z = lbl_806408B0;
    fn_80040BA4(&e->_4e8[1], 0);
    fn_80040B38(&e->_4e8[1], 0, 0, 0, 0, lbl_806408B0, &z);
}

// TODO Distance that frames object obj for framing mode kind.
f32 fn_800439EC(Unk80040EA4 *e, u32 obj, int kind) {
    f32 h;
    f32 a;
    f32 b;
    f32 sa;
    if (obj == 0) {
        return e->_6c8;
    }
    switch (kind) {
        case 0: h = fn_8003A5EC(obj, 0); break;
        case 1: h = fn_8003A5EC(obj, 1); break;
        case 2: h = lbl_80640954 * fn_8003A5EC(obj, 1); break;
        case 3: return e->_6c8;
    }
    if (h <= lbl_80640950) {
        h = lbl_80640958;
    }
    a = e->_4e0;
    a = lbl_8064095C * (lbl_806408B8 * a);
    b = lbl_806408DC - a;
    sa = sinf(a);
    return h * sinf(b) / sa;
}

// TODO Fixed value of index i.
f32 fn_80043B10(Unk80040EA4 *e, int i) {
    switch (i) {
        case 0: return lbl_80640960;
        case 1: return lbl_806408B0;
        case 2: return lbl_80640964;
        case 3: return lbl_80640968;
    }
    return lbl_806408B0;
}

// TODO Sets _4e4.
void fn_80043B60(Unk80040EA4 *e, f32 v) {
    e->_4e4 = v;
}

// TODO Updates a camera and writes its eye, target and up vector to the scene camera.
void fn_80043B68(Unk80040EA4 *e, f32 t) {
    Unk800404A8 tmp;
    GSvec3 p;
    GSvec3 off;
    GSvec3 f;
    GSvec3 s2;
    GSvec3 up;
    Quaternion q;
    Vec cr;
    GSvec3 p2;
    GSvec3 E;
    GSvec3 T;
    Vec fwd;
    Vec side;
    Vec sc;
    GSvec3 r;
    Vec eye;
    Unk800404A8 *tgt;
    int i;
    GScamera *cam;
    fn_800404A8(&tmp, e);
    if (!e->_000) {
        return;
    }
    fn_80040580(&e->_4e8[1]);
    if (e->_6d0) {
        fn_80040580(&e->_4e8[3]);
        e->_6d8 += t;
        if (e->_6d8 >= e->_6d4) {
            e->_6d8 = e->_6d4;
            e->_6d0 = 0;
        }
        fn_80040CAC(&tmp, &e->_4e8[1], &e->_4e8[3], e->_6d8 / e->_6d4);
        if (e->_6d0 == 0) {
            e->_4e8[1] = e->_4e8[3];
        }
        e->_4e8[2] = tmp;
        tgt = &tmp;
    } else {
        tgt = &e->_4e8[1];
    }
    fn_80040580(&e->_4e8[0]);
    for (i = 0; i < 12; i++) {
        e->_004[i].fn_80050394(t);
    }
    for (i = 0; i < 5; i++) {
        e->_1b4[i].fn_80050394(t);
    }
    if (e->_004[8]._00 || e->_004[9]._00 || e->_4bc) {
        fn_80041228(e, tgt);
        p = *fn_80041204Inline(e);
        if (e->_4bc) {
            if (!(e->_4bc & 4)) {
                if (PSVECDistance(&p, fn_80041204Inline(e)) > e->_4d0) {
                    fn_800400E8(&p, &e->_4e8[0]._14, &p, e->_4cc);
                } else {
                    p = e->_4e8[0]._14;
                }
            }
            fn_80040BE4(&e->_4e8[0], &p);
            e->_4bc &= ~6;
        } else {
            fn_80040BE4(&e->_4e8[0], &p);
        }
    } else if (e->_004[1]._00) {
        fn_800425FC(e, e->_6c8 + e->_6e8);
    }
    if (!e->_6cc) {
        return;
    }
    PSVECSubtract(&tgt->_14, &e->_4e8[0]._14, &fwd);
    f = fwd;
    if (!isZeroVec(&f)) {
        PSVECNormalize(&f, &f);
    } else {
        f.x = lbl_806408B0;
        f.y = lbl_806408B0;
        f.z = lbl_806408BC;
    }
    PSVECCrossProduct(&f, &GSmath::sYAxis, &side);
    s2 = side;
    s2.y = lbl_806408B0;
    if (!isZeroVec(&s2)) {
        PSVECNormalize(&s2, &s2);
        PSVECScale(&s2, &sc, e->_6e4);
        off = sc;
        off.y = e->_6e0;
    } else {
        off.x = lbl_806408B0;
        off.y = lbl_806408B0;
        off.z = lbl_806408B0;
    }
    up = GSmath::sYAxis;
    PSVECCrossProduct(&up, &f, &cr);
    if (isZeroVec(&cr)) {
        up = GSmath::sXAxis;
    }
    C_QUATRotAxisRad(&q, &f, e->_6dc);
    r = up;
    GSmath::rotateVec3ByQuat(&r, (GSquat *)&q);
    up = r;
    if (e->_6f8) {
        p2 = e->_4e8[0]._14;
        if (p2.y < e->_6f4) {
            p2.y = e->_6f4;
            fn_80040BE4(&e->_4e8[0], &p2);
        }
    }
    PSVECAdd(&e->_4e8[0]._14, &off, &eye);
    E = eye;
    T = tgt->_14;
    if (isnan(E.x) || isinf(E.x) || isnan(E.y) || isinf(E.y) || isnan(E.z) || isinf(E.z) || isnan(T.x) || isinf(T.x) ||
        isnan(T.y) || isinf(T.y) || isnan(T.z) || isinf(T.z) || isnan(up.x) || isinf(up.x) || isnan(up.y) ||
        isinf(up.y) || isnan(up.z) || isinf(up.z)) {
        E.x = lbl_80640970;
        E.y = lbl_806408CC;
        E.z = lbl_806408B0;
        T.x = lbl_806408B0;
        T.y = lbl_806408CC;
        T.z = lbl_806408B0;
        up.x = lbl_806408B0;
        up.y = lbl_806408BC;
        up.z = lbl_806408B0;
    }
    if (isnan(e->_4e0) || isinf(e->_4e0)) {
        e->_4e0 = lbl_806408C8;
    }
    cam = e->_6cc;
    cam->_1ac.x = E.x;
    cam->_1ac.y = E.y;
    cam->_1ac.z = E.z;
    cam->_1b8.x = up.x;
    cam->_1b8.y = up.y;
    cam->_1b8.z = up.z;
    cam->_1c4.x = T.x;
    cam->_1c4.y = T.y;
    cam->_1c4.z = T.z;
    cam->_104 |= 0x30;
    {
        f32 fov;
        cam = e->_6cc;
        fov = e->_4e0;
        if ((cam->_104 & 3) == 1) {
            cam->_168 = fov;
            cam->_104 |= 8;
        }
    }
}

// TODO Empty.
void fn_8004449C(Unk80040EA4 *e) {}

// TODO Bit mask of the running tweens.
u32 fn_800444A0(Unk80040EA4 *e) {
    u32 m = 0;
    int i;
    for (i = 0; i < 12; i++) {
        if (e->_004[i]._00) {
            m |= 1 << i;
        }
    }
    return m;
}

// TODO Projects a point on the screen of the camera's render target; FALSE when it is behind.
int fn_80044554(Unk80040EA4 *e, Vec *in, Vec *out) {
    Unk80044554 vp;
    GSvec3 dir;
    GSvec3 rel;
    GSvec3 pos;
    GSvec3 p;
    GSvec3 q;
    GSvec3 d;
    u32 x;
    GScamera *cam;
    f32 *proj;
    f32 *view;
    f32 lim;
    if (e->_6cc == 0) {
        return 0;
    }
    x = fn_80033088();
    if (x == 0) {
        return 0;
    }
    x = fn_80033B98(x, e->_4b4);
    if ((u16)x != 0xffff) {
        Unk80242B88 *t = (Unk80242B88 *)GSrenderTarget::findTarget(2);
        if (t->_20 == 1) {
            fn_80242B88(t, (u16)x, &vp._00, &vp._04, &vp._08, &vp._0c);
        }
    }
    vp._00 = lbl_806408B0;
    vp._04 = lbl_806408B0;
    vp._08 = GSrender::sInstance->getRenderMode()->fbWidth;
    vp._0c = GSrender::sInstance->getRenderMode()->efbHeight;
    vp._10 = lbl_806408B0;
    vp._14 = lbl_806408BC;
    cam = e->_6cc;
    proj = cam->_14c;
    view = (f32 *)cam->_1d4;
    p.x = cam->_204[0][3];
    p.y = cam->_204[1][3];
    p.z = cam->_204[2][3];
    pos = p;
    q.x = cam->_204[0][2];
    q.y = cam->_204[1][2];
    q.z = cam->_204[2][2];
    dir = q;
    lim = -cam->_14c[6];
    PSVECSubtract(&pos, in, &d);
    rel = d;
    if (PSVECDotProduct(&dir, &rel) <= lim) {
        out->x = lbl_806408B8 * (vp._08 - vp._00);
        out->y = lbl_806408B8 * (vp._0c - vp._04);
        out->z = lbl_806408E0;
        return 0;
    }
    GXProject(in->x, in->y, in->z, view, proj, &vp._00, &out->x, &out->y, &out->z);
    return 1;
}

// TODO Removes object id from the eye and target controllers.
void fn_80044770(Unk80040EA4 *e, u32 id) {
    fn_80040E48(&e->_4e8[0], id);
    fn_80040E48(&e->_4e8[1], id);
    fn_80040E48(&e->_4e8[3], id);
}

#pragma auto_inline reset
