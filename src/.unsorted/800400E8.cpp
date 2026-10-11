#include ".unsorted/800400E8.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EA98;

u32 fn_800401F4(void) { return lbl_8063EA98; }
u8 *fn_80041204(u8 *p) { return p + 0x4fc; }
f32 fn_80042708(u8 *p) { return *(f32 *)(p + 0x6dc); }
void fn_80043B60(u8 *p, f32 v) { *(f32 *)(p + 0x4e4) = v; }
void fn_8004449C(void) {}

}

#include "common.hpp"

extern "C" {

struct CamCtl;
void fn_80040588(CamCtl *c, int force);
f32 fn_800407B0(CamCtl *c);

void fn_80040580(CamCtl *c) { fn_80040588(c, 0); }
void fn_80041064(u8 *p) { *(u8 *)(p + 0x0) = 0x0; }
void fn_8004121C(u8 *p) { *(u8 *)(p + 0x6f8) = 0x0; }
f32 fn_80042794(u8 *p) { return fn_800407B0((CamCtl *)(p + 0x560)); }

}

// ---------------------------------------------------------------------------
// Battle camera manager (8 slots of 0x6FC bytes)

#include "gs/GSmath.hpp"

typedef Vec V3;

struct CamPair {
    u32 a;
    u32 b;
};

// Vector with an explicit member-wise copy
struct FV : public Vec {
    FV &operator=(const FV &o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
};

// Camera target/eye controller (size 0x78)
struct CamCtl {
    /* 0x00 */ u8 b0;
    /* 0x04 */ u32 flags;
    /* 0x08 */ f32 f8;
    /* 0x0C */ f32 fc;
    /* 0x10 */ s32 mode;
    /* 0x14 */ FV pos;
    /* 0x20 */ FV v20;
    /* 0x2C */ FV v2c;
    /* 0x38 */ FV v38;
    /* 0x44 */ FV ofs;
    /* 0x50 */ f32 f50;
    /* 0x54 */ u8 *owner;
    /* 0x58 */ CamPair pair[4];
};

typedef void (*UpdateFn)(void *self, f32 dt);

struct Sub24 {
    u32 w0;
    u8 d[0x1C];
    virtual void update(f32 dt);
};

struct Sub60 {
    u8 d[0x20];
    virtual void update(f32 dt);
    u8 rest[0x3C];
};

struct CamEntry {
    /* 0x000 */ u8 active;
    /* 0x001 */ u8 dirty;
    /* 0x002 */ u8 b2;
    /* 0x003 */ u8 _3;
    /* 0x004 */ Sub24 s24[12];
    /* 0x1B4 */ Sub60 s60[5];
    /* 0x394 */ Sub60 m394;
    /* 0x3F4 */ Sub60 m3f4;
    /* 0x454 */ Sub60 m454;
    /* 0x4B4 */ u32 id;
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
    /* 0x4E8 */ CamCtl ctl[4];
    /* 0x6C8 */ f32 _6c8;
    /* 0x6CC */ u32 _6cc;
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

struct CamMgr {
    u8 flag;
    u8 pad[3];
    CamEntry e[8];
};

void *operator new(unsigned long);

static inline void vcopy(V3 *d, const V3 *s) {
    f32 x = s->x;
    f32 y = s->y;
    f32 z = s->z;
    d->x = x;
    d->y = y;
    d->z = z;
}
f32 fn_8000739C();

class GSrender {
public:
    static u8 *sInstance;
};

extern "C" {

extern u32 lbl_8063F778;
extern const f32 lbl_806408B0;
extern const f32 lbl_806408B4;
extern const f32 lbl_806408B8;
extern const f32 lbl_806408BC;

void fn_800403B0(CamMgr *p, f32 t);
void fn_80040434(CamMgr *p);
CamMgr *fn_80040274(CamMgr *p);
void fn_8023EB58(u32, void (*)(void), void (*)(void), u32, u32);
void fn_80044770(CamEntry *e, u32 a);
CamEntry *fn_80040EA4(CamEntry *e);
void fn_80040FA0(CamEntry *e);
void fn_80043B68(CamEntry *e, f32 t);
void fn_8003989C(V3 *out, u32 a, u32 b);

#pragma auto_inline off

void fn_800400E8(V3 *out, V3 *a, V3 *b, f32 t) {
    f32 x = a->x + t * (b->x - a->x);
    f32 y = a->y + t * (b->y - a->y);
    f32 z = a->z + t * (b->z - a->z);
    out->x = x;
    out->y = y;
    out->z = z;
}

void fn_80040134(void) {
    CamMgr *p = (CamMgr *)fn_800401F4();
    if (p) {
        fn_800403B0(p, fn_8000739C());
    }
}

void fn_80040174(void) {
    CamMgr *p = (CamMgr *)fn_800401F4();
    if (p) {
        fn_80040434(p);
    }
}

void fn_800401A0(void) {
    CamMgr *p = (CamMgr *)operator new(0x37e4);
    if (p) {
        p = fn_80040274(p);
    }
    lbl_8063EA98 = (u32)p;
    fn_8023EB58(lbl_8063F778, fn_80040134, fn_80040174, 3, 0xc);
}

void fn_800401FC(CamMgr *p, u32 a) {
    u32 i;
    for (i = 0; i < 8; i++) {
        if (p->e[i].active) {
            fn_80044770(&p->e[i], a);
        }
    }
}

CamMgr *fn_80040274(CamMgr *p) {
    CamEntry *e;
    e = p->e;
    do {
        fn_80040EA4(e);
        e++;
    } while (e < p->e + 8);
    p->flag = 0;
    return p;
}

u32 fn_800402D4(CamMgr *p) {
    int i;
    for (i = 0; i < 8; i++) {
        if (!p->e[i].active) {
            fn_80040FA0(&p->e[i]);
            p->e[i].id = i + 1;
            return i + 1;
        }
    }
    return 0;
}

CamEntry *fn_80040384(CamMgr *p, u32 id);

void fn_80040358(CamMgr *p, u32 id) {
    CamEntry *e = fn_80040384(p, id);
    if (e) {
        fn_80041064((u8 *)e);
    }
}

CamEntry *fn_80040384(CamMgr *p, u32 id) {
    if (id == 0 || id >= 8) {
        return 0;
    }
    return &p->e[id - 1];
}

void fn_800403B0(CamMgr *p, f32 t) {
    u32 i;
    if (p->flag) {
        for (i = 0; i < 8; i++) {
            if (p->e[i].active) {
                fn_80043B68(&p->e[i], t);
            }
        }
    }
}

void fn_80040434(CamMgr *p) {
    u32 i;
    if (p->flag) {
        for (i = 0; i < 8; i++) {
            if (p->e[i].active) {
                ((void (*)(CamEntry *))fn_8004449C)(&p->e[i]);
            }
        }
    }
}

void fn_800404A8(CamCtl *c, u8 *owner) {
    f32 z = lbl_806408B0;
    c->mode = 0;
    c->pos.x = z;
    c->pos.y = z;
    c->pos.z = z;
    c->f50 = z;
    c->owner = owner;
    c->b0 = 0;
    c->flags = 0;
    c->f8 = z;
    c->pair[0].a = 0;
    c->pair[0].b = 0;
    c->pair[1].a = 0;
    c->pair[1].b = 0;
    c->pair[2].a = 0;
    c->pair[2].b = 0;
    c->pair[3].a = 0;
    c->pair[3].b = 0;
}

int fn_800404F8(CamCtl *c, int i, V3 *out) {
    V3 tmp;
    u32 a;
    u32 b;
    if (i >= 0 && i < 4) {
        CamPair *pr = &c->pair[i];
        a = pr->a;
        if (a != 0) {
            b = pr->b;
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

void fn_80040928(CamCtl *c, V3 *v) {
    vcopy(&c->v20, v);
    c->flags |= 1;
}

void fn_80040950(CamCtl *c) {
    c->flags |= 2;
}

void fn_80040AE0(CamCtl *c, u32 a, u32 b, V3 *v) {
    vcopy(&c->ofs, v);
    c->pair[0].a = a;
    c->pair[0].b = b;
    c->mode = 1;
    fn_80040588(c, 1);
}

void fn_80040B10(CamCtl *c, V3 *v) {
    vcopy(&c->ofs, v);
    c->mode = 4;
    fn_80040588(c, 1);
}

void fn_80040B38(CamCtl *c, u32 a, u32 b, u32 a2, u32 b2, f32 f, V3 *v) {
    if (a != 0) {
        c->mode = 2;
    }
    c->pair[0].a = a;
    c->pair[0].b = b;
    c->pair[1].a = a2;
    c->pair[1].b = b2;
    c->f50 = f;
    c->ofs.x = v->x;
    c->ofs.y = v->y;
    c->ofs.z = v->z;
    fn_80040588(c, 1);
}

u32 fn_80040B7C(CamCtl *c, int i) {
    if (i >= 0 && i < 4) {
        return c->pair[i].a;
    }
    return 0;
}

void fn_80040BA4(CamCtl *c, int mode) {
    fn_80040588(c, 1);
    c->mode = mode;
}

void fn_80040BE4(CamCtl *c, V3 *v) {
    fn_80040BA4(c, 0);
    vcopy(&c->pos, v);
}

void fn_80038A94(V3 *out, u32 a);

f32 fn_80040C38(CamCtl *c) {
    u32 a;
    if (c->b0) {
        return c->f8;
    }
    a = 0;
    if (c->pair[0].a) {
        a = c->pair[0].a;
    } else if (c->pair[1].a) {
        a = c->pair[1].a;
    }
    if (a) {
        V3 tmp;
        fn_80038A94(&tmp, a);
        return tmp.y;
    }
    return lbl_806408B0;
}

void fn_80040E48(CamCtl *c, u32 id) {
    int i;
    for (i = 0; i < 4; i++) {
        u32 a = c->pair[i].a;
        if (a == id) {
            c->pair[i].a = 0;
            c->pair[i].b = 0;
        }
    }
}

void fn_80050324(Sub24 *s);
void fn_80050E38(Sub60 *s);
void fn_80050388(Sub24 *s);
void fn_8005033C(Sub24 *s, f32 *a, f32 *b, f32 *c, u32 x, f32 f);
void fn_800410AC(CamEntry *e, V3 *v);
void fn_8004215C(CamEntry *e, f32 f1, f32 f2, f32 f3);
void fn_800410BC(CamEntry *e, V3 *v);
void fn_80042534(CamEntry *e, V3 *v);
extern const f32 lbl_806408C8;
f32 PSVECMag(const Vec *v);
extern const f32 lbl_806408CC;
extern const f32 lbl_806408D0;

CamEntry *fn_80040EA4(CamEntry *e) {
    Sub24 *p;
    Sub60 *q;
    p = e->s24;
    do {
        fn_80050324(p);
        p++;
    } while (p < e->s24 + 12);
    q = e->s60;
    do {
        fn_80050E38(q);
        q++;
    } while (q < e->s60 + 5);
    fn_80050E38(&e->m394);
    fn_80050E38(&e->m3f4);
    fn_80050E38(&e->m454);
    fn_800404A8(&e->ctl[0], (u8 *)e);
    fn_800404A8(&e->ctl[1], (u8 *)e);
    fn_800404A8(&e->ctl[2], (u8 *)e);
    fn_800404A8(&e->ctl[3], (u8 *)e);
    e->active = 0;
    e->_6cc = 0;
    e->b2 = 0;
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

void fn_80040FA0(CamEntry *e) {
    V3 a;
    V3 b;
    V3 c;
    e->active = 1;
    e->_4e0 = lbl_806408C8;
    fn_80050388(&e->s24[0]);
    e->dirty = 1;
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
    e->dirty = 1;
}

void fn_80041070(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->s24[0], &e->_4e0, &t, &e->_4e0, x, b);
}

void fn_800410AC(CamEntry *e, V3 *v) {
    e->_4bc = 0;
    e->b2 = 0;
    fn_800410BC(e, v);
}

void fn_800410BC(CamEntry *e, V3 *v) {
    fn_80040BE4(&e->ctl[0], v);
    fn_80050388(&e->s24[2]);
    fn_80050388(&e->s24[3]);
    fn_80050388(&e->s24[4]);
    fn_80050388(&e->s24[8]);
    fn_80050388(&e->s24[9]);
    e->dirty = 1;
}

void fn_8004111C(CamEntry *e, f32 x, f32 y, f32 d) {
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
    PSVECAdd(&e->ctl[1].pos, &v, &out);
    tmp = out;
    fn_80040BE4(&e->ctl[0], &tmp);
    e->_4bc = 0;
    e->b2 = 0;
    fn_80050388(&e->s24[2]);
    fn_80050388(&e->s24[3]);
    fn_80050388(&e->s24[4]);
    e->dirty = 1;
}

void fn_8004120C(CamEntry *e, f32 f) {
    e->_6f4 = f;
    e->_6f8 = 1;
}

extern const f32 lbl_806408E8;
void fn_80041228(CamEntry *e, CamCtl *c);
void fn_80041B58(V3 *out, CamEntry *e, f32 a, f32 b, f32 c);
V3 *fn_80042590(CamEntry *e);
void fn_80050E7C(Sub60 *s, u32 a, f32 *b, u32 c, u32 d, u32 e);
void fn_80041ED4(V3 *a, V3 *b);
f32 PSVECDistance(const Vec *a, const Vec *b);

void fn_80041690(CamEntry *e, f32 a, f32 b, f32 c, u32 x, u32 y) {
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
        fn_80041228(e, &e->ctl[1]);
    }
}

void fn_800416E8(CamEntry *e, f32 a, f32 b, f32 c) {
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
        fn_80041228(e, &e->ctl[1]);
    }
}

void fn_8004173C(CamEntry *e, f32 b, f32 c, u32 x) {
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
        fn_80041228(e, &e->ctl[1]);
    }
}

void fn_80041794(CamEntry *e, f32 b, f32 c, u32 y) {
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
        fn_80041228(e, &e->ctl[1]);
    }
}

void fn_800417E8(CamEntry *e, f32 a, f32 b, f32 c) {
    if (c < lbl_806408B0) {
        c = lbl_806408B0;
    }
    if (c > lbl_806408BC) {
        c = lbl_806408BC;
    }
    e->_4bc |= 0x47;
    e->_4bc &= ~0x8;
    fn_80050388(&e->s24[9]);
    e->_4c8 = a;
    e->_4cc = c;
    e->_4d0 = b;
    if (c >= lbl_806408E8) {
        fn_80041228(e, &e->ctl[1]);
    }
}

void fn_800418AC(CamEntry *e, u32 flags) {
    if (flags & 1) {
        e->_4bc = 0;
        fn_80040BA4(&e->ctl[0], 0);
        e->b2 = 0;
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

void fn_80041950(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->s24[11], &e->_4c8, &t, &e->_4c8, x, b);
}

void fn_8004198C(CamEntry *e, u32 a, u32 b, V3 *v) {
    fn_80040AE0(&e->ctl[0], a, b, v);
    e->_4bc = 0;
    fn_80050388(&e->s24[2]);
    fn_80050388(&e->s24[3]);
    fn_80050388(&e->s24[4]);
    e->dirty = 1;
}

void fn_800419E4(CamEntry *e, V3 *v) {
    V3 l;
    V3 tmp;
    if (v == 0) {
        V3 *p = fn_80042590(e);
        PSVECSubtract((V3 *)fn_80041204((u8 *)e), p, &tmp);
        vcopy(&l, &tmp);
    } else {
        l.x = v->x;
        l.y = v->y;
        l.z = v->z;
    }
    fn_80040B10(&e->ctl[0], &l);
    e->_4bc = 0;
    e->dirty = 1;
}

void fn_80041A88(CamEntry *e, f32 f1, f32 f2, f32 f3) {
    V3 l;
    V3 tmp;
    fn_80041B58(&tmp, e, f1, f2, f3);
    vcopy(&l, &tmp);
    fn_800419E4(e, &l);
}

void fn_80041AE0(CamEntry *e, u32 a, u32 b) {
    fn_80050E7C(&e->s60[0], a, &e->_6e0, b, 0, 0);
}

void fn_80041AF8(CamEntry *e, u32 a, u32 b) {
    fn_80050E7C(&e->s60[1], a, &e->_6e4, b, 0, 0);
}

void fn_80041B10(CamEntry *e, u32 a, u32 b) {
    fn_80050E7C(&e->s60[3], a, &e->_6ec, b, 0, 0);
}

void fn_80041B28(CamEntry *e, u32 a, u32 b) {
    fn_80050E7C(&e->s60[4], a, &e->_6f0, b, 0, 0);
}

void fn_80041B40(CamEntry *e, u32 a, u32 b) {
    fn_80050E7C(&e->s60[2], a, &e->_6e8, b, 0, 0);
}

void fn_8004215C(CamEntry *e, f32 f1, f32 f2, f32 f3) {
    V3 a;
    V3 b;
    V3 tmp;
    V3 *p;
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

void fn_80042534(CamEntry *e, V3 *v) {
    fn_80040BE4(&e->ctl[1], v);
    fn_80050388(&e->s24[5]);
    fn_80050388(&e->s24[6]);
    fn_80050388(&e->s24[7]);
    u32 f = e->_6d0;
    e->dirty = 1;
    e->_6d0 = f & ~3;
}

V3 *fn_80042590(CamEntry *e) {
    if (e->_6d0) {
        return &e->ctl[2].pos;
    }
    return &e->ctl[1].pos;
}

void fn_800425AC(CamEntry *e, u32 a, u32 b, V3 *v) {
    fn_80040AE0(&e->ctl[1], a, b, v);
    fn_80050388(&e->s24[5]);
    fn_80050388(&e->s24[6]);
    fn_80050388(&e->s24[7]);
    e->dirty = 1;
}

void fn_800426CC(CamEntry *e, f32 f) {
    e->_6dc = f;
    fn_80050388(&e->s24[10]);
    e->dirty = 1;
}

void fn_80042710(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_8005033C(&e->s24[10], &e->_6dc, &t, &e->_6dc, x, b);
}

f32 fn_8004274C(CamEntry *e) {
    V3 *p = fn_80042590(e);
    return PSVECDistance((V3 *)fn_80041204((u8 *)e), p);
}

void fn_800425FC(CamEntry *e, f32 f);
extern const f32 lbl_806408EC;

void fn_8004279C(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    f32 base;
    e->_4bc &= ~0x20;
    base = fn_80042794((u8 *)e);
    fn_800425FC(e, fn_8004274C(e) - base);
    fn_8005033C(&e->s24[1], &e->_6c8, &t, &e->_6c8, x, b);
}

f32 fn_80042950(CamEntry *e, f32 a, f32 b) {
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

void fn_80042A0C(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_80040BA4(&e->ctl[0], 0);
    e->_4bc &= ~0x8;
    fn_8005033C(&e->s24[3], &e->ctl[0].pos.y, &t, &e->ctl[0].pos.y, x, b);
}

void fn_80042A84(CamEntry *e, f32 a, f32 b, u32 x) {
    V3 d;
    f32 ang;
    d.x = e->ctl[0].pos.x;
    d.y = e->ctl[0].pos.y;
    d.z = e->ctl[0].pos.z;
    PSVECSubtract(&d, &e->ctl[1].pos, &d);
    ang = atan2f(d.x, d.z);
    e->_4bc &= ~0x10;
    fn_8005033C(&e->s24[8], &ang, &a, &e->_4d8, x, b);
}

void fn_80042EA8(CamEntry *e, f32 f, V3 *src, u32 x) {
    V3 *p = &e->ctl[1].pos;
    fn_80040BA4(&e->ctl[1], 0);
    fn_8005033C(&e->s24[5], &p->x, &src->x, &p->x, x, f);
    fn_8005033C(&e->s24[6], &p->y, &src->y, &p->y, x, f);
    fn_8005033C(&e->s24[7], &p->z, &src->z, &p->z, x, f);
}

void fn_80042F60(CamEntry *e, f32 a, f32 b, u32 x) {
    f32 t = a;
    fn_80040BA4(&e->ctl[1], 0);
    fn_8005033C(&e->s24[6], &e->ctl[1].pos.y, &t, &e->ctl[1].pos.y, x, b);
}

void fn_80043988(CamEntry *e) {
    V3 z;
    z.x = lbl_806408B0;
    z.y = lbl_806408B0;
    z.z = lbl_806408B0;
    fn_80040BA4(&e->ctl[1], 0);
    fn_80040B38(&e->ctl[1], 0, 0, 0, 0, lbl_806408B0, &z);
}

extern const f32 lbl_80640960;
extern const f32 lbl_80640964;
extern const f32 lbl_80640968;

f32 fn_80043B10(CamEntry *e, int i) {
    switch (i) {
    case 0:
        return lbl_80640960;
    case 1:
        return lbl_806408B0;
    case 2:
        return lbl_80640964;
    case 3:
        return lbl_80640968;
    }
    return lbl_806408B0;
}

u32 fn_800444A0(CamEntry *e) {
    u32 m = 0;
    int i;
    for (i = 0; i < 12; i++) {
        if (e->s24[i].w0) {
            m |= 1 << i;
        }
    }
    return m;
}

void fn_80044770(CamEntry *e, u32 id) {
    fn_80040E48(&e->ctl[0], id);
    fn_80040E48(&e->ctl[1], id);
    fn_80040E48(&e->ctl[3], id);
}

void fn_8004283C(CamEntry *e, V3 *v, u32 x, f32 f);
void fn_8004231C(CamEntry *e, u32 x, f32 f1, f32 f2, f32 f3, f32 f4);
extern const f32 lbl_806408DC;
extern const f32 lbl_806408E0;
extern const f32 lbl_806408E4;

void fn_8004231C(CamEntry *e, u32 x, f32 f1, f32 f2, f32 f3, f32 f4) {
    V3 a;
    V3 b;
    V3 tmp;
    V3 *p;
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

void fn_800425FC(CamEntry *e, f32 f) {
    V3 d;
    f32 r = fn_800407B0(&e->ctl[1]);
    e->_6c8 = f;
    fn_80040588(&e->ctl[0], 1);
    d.x = e->ctl[0].pos.x;
    d.y = e->ctl[0].pos.y;
    d.z = e->ctl[0].pos.z;
    PSVECSubtract(&d, &e->ctl[1].pos, &d);
    PSVECNormalize(&d, &d);
    PSVECScale(&d, &d, f + r);
    PSVECAdd(&d, &e->ctl[1].pos, &d);
    fn_80040BE4(&e->ctl[0], &d);
    e->dirty = 1;
}

void fn_80042DC0(CamEntry *e, f32 a, f32 b, u32 x) {
    V3 d;
    f32 ang;
    f32 r;
    d.x = e->ctl[0].pos.x;
    d.y = e->ctl[0].pos.y;
    d.z = e->ctl[0].pos.z;
    PSVECSubtract(&d, &e->ctl[1].pos, &d);
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
    fn_8005033C(&e->s24[9], &ang, &a, &e->_4dc, x, b);
}

extern const f32 lbl_80640944;

void fn_800421F0(CamEntry *e, f32 a, f32 b, f32 c) {
    CamCtl *ctl;
    u32 *obj;
    if (e->_6d0) {
        ctl = &e->ctl[3];
    } else {
        ctl = &e->ctl[1];
    }
    obj = (u32 *)fn_80040B7C(ctl, 0);
    if (obj && (*obj & 0x1000)) {
        fn_8004215C(e, a, lbl_80640944, c);
    } else {
        V3 A;
        V3 B;
        V3 tmp;
        V3 *p;
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

void fn_8004283C(CamEntry *e, V3 *v, u32 x, f32 f) {
    f32 y1;
    f32 y0;
    f32 vy;
    fn_80040BA4(&e->ctl[0], 0);
    vy = v->y;
    e->_4bc = 0;
    if (vy < e->_6f4 && e->_6f8) {
        y0 = e->_6f4;
    } else {
        y0 = v->y;
    }
    if (e->ctl[0].pos.y < e->_6f4 && e->_6f8) {
        y1 = e->_6f4;
    } else {
        y1 = e->ctl[0].pos.y;
    }
    fn_8005033C(&e->s24[2], &e->ctl[0].pos.x, &v->x, &e->ctl[0].pos.x, x, f);
    fn_8005033C(&e->s24[3], &y1, &y0, &e->ctl[0].pos.y, x, f);
    fn_8005033C(&e->s24[4], &e->ctl[0].pos.z, &v->z, &e->ctl[0].pos.z, x, f);
}

void fn_80042CB0(CamEntry *e, f32 a, f32 b, u32 x) {
    V3 d;
    f32 ang;
    d.x = e->ctl[0].pos.x;
    d.y = e->ctl[0].pos.y;
    d.z = e->ctl[0].pos.z;
    PSVECSubtract(&d, &e->ctl[1].pos, &d);
    if (e->_6d0 & 2) {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->ctl[3]);
    } else {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->ctl[1]);
    }
    ang = fn_80042950(e, ang, a);
    e->_4bc &= ~0x10;
    fn_8005033C(&e->s24[8], &ang, &a, &e->_4d8, x, b);
}

f32 fn_800439EC(CamEntry *e, u32 obj, int kind);

f32 fn_80041524(CamEntry *e, CamCtl *c) {
    f32 r;
    switch (c->mode) {
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
    default:
        r = e->_6c8;
        break;
    }
    return r;
}

f32 fn_8003A5EC(u32 obj, int i);
extern const f32 lbl_80640950;
extern const f32 lbl_80640954;
extern const f32 lbl_80640958;
extern const f32 lbl_8064095C;

f32 fn_800439EC(CamEntry *e, u32 obj, int kind) {
    f32 h;
    f32 a;
    f32 b;
    f32 sa;
    if (obj == 0) {
        return e->_6c8;
    }
    switch (kind) {
    case 0:
        h = fn_8003A5EC(obj, 0);
        break;
    case 1:
        h = fn_8003A5EC(obj, 1);
        break;
    case 2:
        h = lbl_80640954 * fn_8003A5EC(obj, 1);
        break;
    case 3:
        return e->_6c8;
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

void fn_800423D8(CamEntry *e, u32 x, f32 a, f32 b, f32 c, f32 d) {
    CamCtl *ctl;
    u32 *obj;
    if (e->_6d0) {
        ctl = &e->ctl[3];
    } else {
        ctl = &e->ctl[1];
    }
    obj = (u32 *)fn_80040B7C(ctl, 0);
    if (obj && (*obj & 0x1000)) {
        fn_8004231C(e, x, a, lbl_80640944, c, d);
    } else {
        V3 A;
        V3 B;
        V3 tmp;
        V3 *p;
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

void fn_80042B34(CamEntry *e, f32 a, f32 b, f32 c, u32 x) {
    V3 d;
    f32 ang;
    f32 elev;
    f32 r;
    d.x = e->ctl[0].pos.x;
    d.y = e->ctl[0].pos.y;
    d.z = e->ctl[0].pos.z;
    PSVECSubtract(&d, &e->ctl[1].pos, &d);
    if (e->_6d0 & 2) {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->ctl[3]);
    } else {
        ang = atan2f(d.x, d.z) - fn_80040C38(&e->ctl[1]);
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
    fn_8005033C(&e->s24[8], &ang, &a, &e->_4d8, x, c);
    fn_8005033C(&e->s24[9], &elev, &b, &e->_4dc, x, c);
}

GSvec3 fn_8003B674(u32 obj, u32 kind);

static inline f32 objHeight(u32 obj, u32 kind) {
    if (kind - 0x15 <= 1) {
        return fn_8003A5EC(obj, 0);
    }
    return fn_8003A5EC(obj, 1);
}

f32 fn_800407B0(CamCtl *c) {
    f32 r = lbl_806408B0;
    if (c->b0) {
        return c->fc;
    } else {
        switch (c->mode) {
        case 1:
            if (c->pair[0].a) {
                r = objHeight(c->pair[0].a, c->pair[0].b);
            }
            break;
        case 2: {
            u32 a = c->pair[0].a;
            if (a) {
                u32 a2 = c->pair[1].a;
                if (a2 == 0) {
                    r = objHeight(a, c->pair[0].b);
                } else if (a == a2) {
                    r = objHeight(a, c->pair[0].b);
                } else {
                    GSvec3 p1;
                    GSvec3 p0;
                    p0 = fn_8003B674(a, c->pair[0].b);
                    p1 = fn_8003B674(c->pair[1].a, c->pair[1].b);
                    r = lbl_806408B8 * PSVECDistance(&p0, &p1);
                }
            }
            break;
        }
        }
    }
    return r;
}

void fn_80040CAC(CamCtl *d, CamCtl *a, CamCtl *b, f32 t) {
    d->mode = a->mode;
    d->b0 = 1;
    if (b->flags & 1) {
        fn_800400E8(&d->pos, &b->v20, &b->pos, t);
    } else {
        fn_800400E8(&d->pos, &a->pos, &b->pos, t);
    }
    fn_800400E8(&d->v2c, &a->v2c, &b->v2c, t);
    fn_800400E8(&d->v38, &a->v38, &b->v38, t);
    fn_800400E8(&d->ofs, &a->ofs, &b->ofs, t);
    d->f50 = a->f50 + t * (b->f50 - a->f50);
    d->pair[0].a = a->pair[0].a;
    d->pair[0].b = a->pair[0].b;
    d->pair[1].a = a->pair[1].a;
    d->pair[1].b = a->pair[1].b;
    d->pair[2].a = a->pair[2].a;
    d->pair[2].b = a->pair[2].b;
    d->pair[3].a = a->pair[3].a;
    d->pair[3].b = a->pair[3].b;
    if (b->flags & 2) {
        d->f8 = fn_80040C38(b);
    } else {
        f32 x = fn_80040C38(a);
        d->f8 = x + t * (fn_80040C38(b) - x);
    }
    {
        f32 y = fn_800407B0(a);
        d->fc = y + t * (fn_800407B0(b) - y);
    }
}

int fn_80040960(CamCtl *c, V3 *out, V3 *in);

void fn_80040588(CamCtl *c, int force) {
    V3 b;
    V3 a;
    V3 p;
    V3 r;
    V3 out1;
    V3 out4;
    u8 *owner = c->owner;
    switch (c->mode) {
    case 1:
        fn_800404F8(c, 0, &p);
        PSVECAdd(&p, &c->ofs, &out1);
        {
            f32 z;
            f32 y;
            f32 x;
            c->pos.x = x = out1.x;
            c->pos.y = y = out1.y;
            c->pos.z = z = out1.z;
            c->v38.x = x;
            c->v38.y = y;
            c->v38.z = z;
        }
        fn_800400E8(&c->v2c, &c->pos, &p, lbl_806408B4);
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
        PSVECAdd(&p, &c->ofs, &p);
        res = fn_80040960(c, &r, &p);
        c->v38.x = p.x;
        c->v38.y = p.y;
        c->v38.z = p.z;
        fn_800400E8(&c->v2c, &c->pos, &p, lbl_806408B4);
        if (force || res == 1) {
            c->pos.x = p.x;
            c->pos.y = p.y;
            c->pos.z = p.z;
        } else if (res == 2) {
            c->pos.x = r.x;
            c->pos.y = r.y;
            c->pos.z = r.z;
        }
        break;
    }
    case 4: {
        V3 *t = fn_80042590((CamEntry *)owner);
        p.x = t->x;
        p.y = t->y;
        p.z = t->z;
        PSVECAdd(&p, &c->ofs, &out4);
        {
            f32 z;
            f32 y;
            f32 x;
            c->pos.x = x = out4.x;
            c->pos.y = y = out4.y;
            c->pos.z = z = out4.z;
            c->v38.x = x;
            c->v38.y = y;
            c->v38.z = z;
        }
        fn_800400E8(&c->v2c, &c->pos, &p, lbl_806408B4);
        break;
    }
    }
}

extern const f32 lbl_806408D4;
extern const f32 lbl_806408D8;
f32 fn_80041524(CamEntry *e, CamCtl *c);
f32 fn_80043B10(CamEntry *e, int i);

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

void fn_80041228(CamEntry *e, CamCtl *c) {
    V3 d;
    GSvec3 tmp;
    GSquat q;
    GSvec3 off;
    GSvec3 out;
    GSvec3 v;
    GSvec3 ang;
    V3 *tgt = &c->pos;
    f32 yaw0;
    f32 dist;
    f32 yaw;
    f32 pitch;
    PSVECSubtract(&e->ctl[0].pos, tgt, &d);
    yaw0 = fn_80040C38(c);
    if (e->_4bc & 0x20) {
        f32 h = fn_800407B0(c);
        e->_6c8 = fn_80041524(e, c) - h;
        dist = e->_6e8 + (e->_6c8 + fn_800407B0(c));
    } else {
        dist = e->_6e8 + (e->_6c8 + fn_800407B0(c));
    }
    off.set(lbl_806408B0, lbl_806408B0, dist);
    if (e->s24[8].w0) {
        yaw = e->_4d8 + yaw0;
    } else if (e->_4bc & 0x10) {
        yaw = e->_4c0 + yaw0;
    } else {
        yaw = atan2f(d.x, d.z);
    }
    if (e->s24[9].w0) {
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
    fn_80040BE4(&e->ctl[0], &tmp);
    e->dirty = 1;
}

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
int fn_800396D4(u32 obj);
void fn_800387E0(V3 *out, u32 obj);

void fn_80041B58(V3 *out, CamEntry *e, f32 a, f32 b, f32 c) {
    GSvec3 dir;
    GSquat q;
    V3 tv;
    V3 p1;
    V3 p2;
    V3 p4;
    V3 p3;
    GSvec3 eul;
    u32 obj;
    CamCtl *ctl;
    f32 yaw;
    f32 h;
    f32 t;
    dir.set(lbl_806408B0, lbl_806408B0, lbl_806408BC);
    if (e->_6d0) {
        ctl = &e->ctl[3];
    } else {
        ctl = &e->ctl[1];
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

extern const f32 lbl_8064092C;
extern const f64 lbl_80640930;
extern const f64 lbl_80640938;
extern const f32 lbl_80640940;
f32 PSVECDotProduct(const Vec *a, const Vec *b);

static inline f32 safeSqrt(f32 x) {
    return (x <= lbl_806408B0) ? lbl_806408B0 : sqrtf(x);
}

void fn_80041ED4(V3 *pos, V3 *center) {
    V3 p;
    V3 n;
    V3 d;
    V3 d2;
    V3 o;
    V3 sc;
    V3 d3;
    V3 o2;
    V3 sc2;
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


void fn_80042FCC(CamEntry *e, u32 a, u32 b, f32 f, f32 g, V3 *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->ctl[1], a, b, 0, 0, f, v);
        e->_6d0 &= ~3;
    } else {
        V3 tmp;
        if (e->_6d0) {
            e->ctl[1] = e->ctl[2];
        } else {
            e->ctl[2] = e->ctl[1];
        }
        fn_80040B38(&e->ctl[3], a, b, 0, 0, f, v);
        e->_6d0 |= 1;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->ctl[1].pos.x;
        tmp.y = e->ctl[1].pos.y;
        tmp.z = e->ctl[1].pos.z;
        fn_80040928(&e->ctl[3], &tmp);
    }
    e->b2 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->s24[5]);
    fn_80050388(&e->s24[6]);
    fn_80050388(&e->s24[7]);
    e->dirty = 1;
}

void fn_80043310(CamEntry *e, u32 a, u32 b, u32 a2, u32 b2, f32 f, f32 g, V3 *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->ctl[1], a, b, a2, b2, f, v);
        e->_6d0 &= ~3;
    } else {
        V3 tmp;
        if (e->_6d0) {
            e->ctl[1] = e->ctl[2];
        } else {
            e->ctl[2] = e->ctl[1];
        }
        fn_80040B38(&e->ctl[3], a, b, a2, b2, f, v);
        e->_6d0 |= 1;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->ctl[1].pos.x;
        tmp.y = e->ctl[1].pos.y;
        tmp.z = e->ctl[1].pos.z;
        fn_80040928(&e->ctl[3], &tmp);
    }
    e->b2 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->s24[5]);
    fn_80050388(&e->s24[6]);
    fn_80050388(&e->s24[7]);
    e->dirty = 1;
}

void fn_8004363C(CamEntry *e, u32 a, u32 b, f32 f, f32 g, V3 *v) {
    if (g <= lbl_80640950) {
        fn_80040B38(&e->ctl[1], a, b, 0, 0, f, v);
        e->_6d0 &= ~3;
    } else {
        V3 tmp;
        if (e->_6d0) {
            e->ctl[1] = e->ctl[2];
        } else {
            e->ctl[2] = e->ctl[1];
        }
        fn_80040B38(&e->ctl[3], a, b, 0, 0, f, v);
        e->_6d0 |= 2;
        e->_6d4 = g;
        e->_6d8 = lbl_806408B0;
        tmp.x = e->ctl[1].pos.x;
        tmp.y = e->ctl[1].pos.y;
        tmp.z = e->ctl[1].pos.z;
        fn_80040928(&e->ctl[3], &tmp);
        fn_80040950(&e->ctl[3]);
    }
    e->b2 = 1;
    if (e->_4bc & 1) {
        e->_4bc |= 4;
    }
    fn_80050388(&e->s24[5]);
    fn_80050388(&e->s24[6]);
    fn_80050388(&e->s24[7]);
    e->dirty = 1;
}

int fn_80044554(CamEntry *e, V3 *in, V3 *out);

struct Rect4 {
    f32 x0;
    f32 y0;
    f32 x1;
    f32 y1;
};

struct Pt2 {
    f32 x;
    f32 y;
};

int fn_80040960(CamCtl *c, V3 *out, V3 *in) {
    V3 scr;
    Rect4 rect;
    Rect4 center;
    f32 dist;
    u32 active = ((CamEntry *)c->owner)->_6cc;
    if (c->f50 <= lbl_806408B0 || active == 0) {
        return 1;
    }
    if (!fn_80044554((CamEntry *)c->owner, in, &scr)) {
        return 1;
    }
    rect.x0 = lbl_806408B0;
    rect.y0 = lbl_806408B0;
    rect.x1 = *(u16 *)(GSrender::sInstance + 4);
    rect.y1 = *(u16 *)(GSrender::sInstance + 6);
    center.x0 = rect.x1 * lbl_806408B8;
    center.y0 = rect.y1 * lbl_806408B8;
    dist = safeSqrt((scr.x - center.x0) * (scr.x - center.x0) + (scr.y - center.y0) * (scr.y - center.y0));
    if (c->f50 > dist) {
        return 0;
    } else {
        f32 m = center.y0 - c->f50;
        f32 k;
        if (m <= lbl_806408B0) {
            return 0;
        }
        k = (dist - c->f50) / m;
        if (k > lbl_806408BC) {
            k = lbl_806408BC;
        }
        fn_800400E8(out, &c->pos, in, k * lbl_806408B4);
        return 2;
    }
}

u32 fn_80033088(void);
u32 fn_80033B98(u32 a, u32 id);
void fn_80242B88(u8 *t, u16 idx, f32 *x, f32 *y, f32 *w, f32 *h);
void GXProject(f32 x, f32 y, f32 z, const f32 *mtx, const f32 *pm, const f32 *vp, f32 *sx, f32 *sy, f32 *sz);

class GSrenderTarget {
public:
    static u8 *findTarget(long id);
};

struct Rect6 {
    f32 x;
    f32 y;
    f32 w;
    f32 h;
    f32 n;
    f32 f;
};

int fn_80044554(CamEntry *e, V3 *in, V3 *out) {
    Rect6 vp;
    GSvec3 dir;
    GSvec3 rel;
    GSvec3 pos;
    GSvec3 p;
    GSvec3 q;
    GSvec3 d;
    u32 x;
    u8 *cam;
    u8 *proj;
    u8 *view;
    f32 lim;
    if (e->_6cc == 0) {
        return 0;
    }
    x = fn_80033088();
    if (x == 0) {
        return 0;
    }
    x = fn_80033B98(x, e->id);
    if ((u16)x != 0xffff) {
        u8 *t = GSrenderTarget::findTarget(2);
        if (*(s32 *)(t + 0x20) == 1) {
            fn_80242B88(t, (u16)x, &vp.x, &vp.y, &vp.w, &vp.h);
        }
    }
    vp.x = lbl_806408B0;
    vp.y = lbl_806408B0;
    vp.w = *(u16 *)(GSrender::sInstance + 4);
    vp.h = *(u16 *)(GSrender::sInstance + 6);
    vp.n = lbl_806408B0;
    vp.f = lbl_806408BC;
    cam = (u8 *)e->_6cc;
    proj = cam + 0x14c;
    view = cam + 0x1d4;
    p.x = *(f32 *)(cam + 0x210);
    p.y = *(f32 *)(cam + 0x220);
    p.z = *(f32 *)(cam + 0x230);
    pos = p;
    q.x = *(f32 *)(cam + 0x20c);
    q.y = *(f32 *)(cam + 0x21c);
    q.z = *(f32 *)(cam + 0x22c);
    dir = q;
    lim = -*(f32 *)(cam + 0x164);
    PSVECSubtract(&pos, in, &d);
    rel = d;
    if (PSVECDotProduct(&dir, &rel) <= lim) {
        out->x = lbl_806408B8 * (vp.w - vp.x);
        out->y = lbl_806408B8 * (vp.h - vp.y);
        out->z = lbl_806408E0;
        return 0;
    }
    GXProject(in->x, in->y, in->z, (f32 *)view, (f32 *)proj, &vp.x, &out->x, &out->y, &out->z);
    return 1;
}

void C_QUATRotAxisRad(Quaternion *q, const Vec *axis, f32 rad);
extern const f32 lbl_8064096C;
extern const f32 lbl_80640970;

static inline int isZeroVec(const Vec *v) {
    if (!(v->x < lbl_80640950 && v->x > lbl_8064096C && v->y < lbl_80640950 && v->y > lbl_8064096C &&
          v->z < lbl_80640950 && v->z > lbl_8064096C)) {
        return 0;
    }
    return 1;
}

static inline Vec *getPos(CamEntry *e) {
    return &e->ctl[0].pos;
}

void fn_80043B68(CamEntry *e, f32 dt) {
    CamCtl tmp;
    GSvec3 p;
    GSvec3 off;
    GSvec3 f;
    GSvec3 s2;
    GSvec3 up;
    Quaternion q;
    V3 cr;
    GSvec3 p2;
    GSvec3 E;
    GSvec3 T;
    V3 fwd;
    V3 side;
    V3 sc;
    GSvec3 r;
    V3 eye;
    CamCtl *tgt;
    int i;
    u8 *cam;
    fn_800404A8(&tmp, (u8 *)e);
    if (!e->active) {
        return;
    }
    fn_80040580(&e->ctl[1]);
    if (e->_6d0) {
        fn_80040580(&e->ctl[3]);
        e->_6d8 += dt;
        if (e->_6d8 >= e->_6d4) {
            e->_6d8 = e->_6d4;
            e->_6d0 = 0;
        }
        fn_80040CAC(&tmp, &e->ctl[1], &e->ctl[3], e->_6d8 / e->_6d4);
        if (e->_6d0 == 0) {
            e->ctl[1] = e->ctl[3];
        }
        e->ctl[2] = tmp;
        tgt = &tmp;
    } else {
        tgt = &e->ctl[1];
    }
    fn_80040580(&e->ctl[0]);
    for (i = 0; i < 12; i++) {
        e->s24[i].update(dt);
    }
    for (i = 0; i < 5; i++) {
        e->s60[i].update(dt);
    }
    if (e->s24[8].w0 || e->s24[9].w0 || e->_4bc) {
        fn_80041228(e, tgt);
        p = *getPos(e);
        if (e->_4bc) {
            if (!(e->_4bc & 4)) {
                if (PSVECDistance(&p, getPos(e)) > e->_4d0) {
                    fn_800400E8(&p, &e->ctl[0].pos, &p, e->_4cc);
                } else {
                    p = e->ctl[0].pos;
                }
            }
            fn_80040BE4(&e->ctl[0], &p);
            e->_4bc &= ~6;
        } else {
            fn_80040BE4(&e->ctl[0], &p);
        }
    } else if (e->s24[1].w0) {
        fn_800425FC(e, e->_6c8 + e->_6e8);
    }
    if (!e->_6cc) {
        return;
    }
    PSVECSubtract(&tgt->pos, &e->ctl[0].pos, &fwd);
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
        p2 = e->ctl[0].pos;
        if (p2.y < e->_6f4) {
            p2.y = e->_6f4;
            fn_80040BE4(&e->ctl[0], &p2);
        }
    }
    PSVECAdd(&e->ctl[0].pos, &off, &eye);
    E = eye;
    T = tgt->pos;
    if (isnan(E.x) || isinf(E.x) || isnan(E.y) || isinf(E.y) || isnan(E.z) || isinf(E.z) || isnan(T.x) ||
        isinf(T.x) || isnan(T.y) || isinf(T.y) || isnan(T.z) || isinf(T.z) || isnan(up.x) || isinf(up.x) ||
        isnan(up.y) || isinf(up.y) || isnan(up.z) || isinf(up.z)) {
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
    cam = (u8 *)e->_6cc;
    *(f32 *)(cam + 0x1ac) = E.x;
    *(f32 *)(cam + 0x1b0) = E.y;
    *(f32 *)(cam + 0x1b4) = E.z;
    *(f32 *)(cam + 0x1b8) = up.x;
    *(f32 *)(cam + 0x1bc) = up.y;
    *(f32 *)(cam + 0x1c0) = up.z;
    *(f32 *)(cam + 0x1c4) = T.x;
    *(f32 *)(cam + 0x1c8) = T.y;
    *(f32 *)(cam + 0x1cc) = T.z;
    *(u32 *)(cam + 0x104) |= 0x30;
    {
        f32 fov;
        cam = (u8 *)e->_6cc;
        fov = e->_4e0;
        if ((*(u32 *)(cam + 0x104) & 3) == 1) {
            *(f32 *)(cam + 0x168) = fov;
            *(u32 *)(cam + 0x104) |= 8;
        }
    }
}

#pragma auto_inline reset

}
