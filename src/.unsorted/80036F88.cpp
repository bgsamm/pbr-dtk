#include ".unsorted/80036F88.hpp"

#include ".unsorted/800400E8.hpp"

#include "common.hpp"

extern "C" {

void fn_800375A4(void *p);

void fn_80037D28(void *p) {
    fn_800375A4(p);
}
// TODO role: accessors of the object at 0xBF6, 0xBF8, 0xC50, 0xC54 and 0xD04
u16 fn_80039460(Unk80036F88 *obj) {
    return obj->_BF8;
}
int fn_800394F0(Unk80036F88 *obj) {
    return obj->_BF6;
}

void fn_80039634(Unk80036F88 *obj, u32 x, u32 y) {
    obj->_C50 = x;
    obj->_C54 = y;
}

// TODO role: wrappers calling fn_8003D4D4 and fn_8003D82C with a fixed kind from 0 to 3
void fn_8003D4B4(Unk80036F88 *obj) {
    fn_8003D4D4(obj, 0);
}
void fn_8003D4BC(Unk80036F88 *obj) {
    fn_8003D4D4(obj, 1);
}
void fn_8003D4C4(Unk80036F88 *obj) {
    fn_8003D4D4(obj, 2);
}
void fn_8003D4CC(Unk80036F88 *obj) {
    fn_8003D4D4(obj, 3);
}
void fn_8003D80C(Unk80036F88 *obj) {
    fn_8003D82C(obj, 0);
}
void fn_8003D814(Unk80036F88 *obj) {
    fn_8003D82C(obj, 1);
}
void fn_8003D81C(Unk80036F88 *obj) {
    fn_8003D82C(obj, 2);
}
void fn_8003D824(Unk80036F88 *obj) {
    fn_8003D82C(obj, 3);
}
u8 fn_8003DE50(Unk80036F88 *obj) {
    return obj->_D04;
}
}

#include "gs/GScache.hpp"
#include "gs/GSmath.hpp"
#include "gs/GSobject.hpp"

#include <string.h>

#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define OBJ(p) (*(GSobject **)((u8 *)(p) + 0xc04))

struct Vec3f {
    f32 x, y, z;
};

extern "C" {

extern const f32 lbl_80640820;

void *fn_8004D80C(void);
void fn_8004DCAC(void *h, void *e);
void *fn_8004DC50(void *h);
void fn_8004E234(void *e, u32 a, u32 b, u32 c);
void fn_801F6158(GSobject *o, int a);
void fn_801F9744(GSobject *o);
void fn_801F9808(GSobject *o);
u32 fn_8003D0C0(void *p, u16 a, u32 b, s8 c, u16 *d);
void *fn_8003E15C(void);
void *fn_8003E42C(void *a);
u32 fn_8003E610(void *a, u16 b);
void fn_8003DDA4(void *p, int a);
void fn_800371D4(void *p);
GSvec3 fn_80039F60(void *p, u32 a, u32 b, u32 c);
f32 fn_8003B7FC(void *p);

void fn_8003DB34(void *p, f32 a, f32 b) {
    F32(p, 0xd08) = a;
    F32(p, 0xd0c) = b;
}

void fn_8003CB90(void *p, f32 *v) {
    F32(p, 0xd50) = v[0];
    F32(p, 0xd54) = v[1];
}

void fn_8003CBA4(void *p, f32 *v) {
    F32(p, 0xd48) = v[0];
    F32(p, 0xd4c) = v[1];
}

void fn_8003DD90(void *p) {
    U8(p, 0xd04) = 1;
    F32(p, 0xd10) = lbl_80640820;
}

void fn_80038518(void *p, const char *s) {
    if (s) {
        strncpy((char *)p + 0xd94, s, 0x1f);
    }
}

f32 fn_80039F44(void *p) {
    GSobject *o = OBJ(p);
    if (o == NULL) {
        return lbl_80640820;
    } else {
        return o->fn_801F5B44();
    }
}

void fn_8003C83C(void *p, int a) {
    GSobject *o = OBJ(p);
    if (o) {
        fn_801F6158(o, a == 0);
    }
}

void fn_8003DF1C(void *p, int a) {
    GSobject *o = OBJ(p);
    if (o) {
        if (a) {
            fn_801F9744(o);
        } else {
            fn_801F9808(o);
        }
    }
}

u32 fn_8003D304(void *p, u16 *q, u32 b, s8 c) {
    if (q == NULL) {
        return 0;
    } else {
        return fn_8003D0C0(p, *q, b, c, q + 1);
    }
}

void fn_8003D48C(u32 *p, int a) {
    if (a) {
        *p |= 0x800;
    } else {
        *p &= ~0x800;
    }
}

void fn_800370F4(void *p) {
    f32 z = lbl_80640820;
    U8(p, 0) = 0;
    F32(p, 4) = z;
    F32(p, 8) = z;
    F32(p, 0xc) = z;
    U32(p, 0x10) = 0;
    U32(p, 0x14) = 0;
    U32(p, 0x18) = 0;
    U32(p, 0x1c) = 0;
    U32(p, 0x20) = 0;
    U32(p, 0x24) = 0;
    U32(p, 0x28) = 0;
}

int fn_8003712C(void *p, u32 key) {
    void **arr;
    void *h = fn_8004D80C();
    if (!h) {
        return 0;
    }
    arr = (void **)p;
    for (int i = 0; i < 6; i++) {
        if (arr[5]) {
            fn_8004DCAC(h, arr[5]);
            arr[5] = 0;
        }
        arr[5] = fn_8004DC50(h);
        fn_8004E234(arr[5], 0xc, key, 0);
        arr++;
    }
    U8(p, 0) = 0;
    return 1;
}

void fn_8003DB24(void *p) {
    fn_8003712C((u8 *)p + 0xd04, 0x199C0A00);
}

void fn_8003C224(void *p, u32 a, u32 b, u32 c, u32 d) {
    if (b >= 3) {
        U32(p, 0) &= ~0x40000;
    } else {
        U8(p, 0xca0) = b;
        U32(p, 0xca4) = c;
        U32(p, 0xca8) = d;
        U32(p, 0xcac) = a;
        U32(p, 0) |= 0x40000;
    }
}

void fn_8003DE58(void *p) {
    fn_8003DDA4(p, 1);
    fn_800371D4((u8 *)p + 0xd04);
}

GSvec3 fn_800387E0(void *p) {
    if (OBJ(p)) {
        return GSvec3(F32(p, 0xcb4), F32(p, 0xcb8), F32(p, 0xcbc));
    }
    return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
}

GSvec3 fn_80038914(void *p) {
    if (OBJ(p)) {
        return GSvec3(F32(p, 0xccc), F32(p, 0xcd0), F32(p, 0xcd4));
    }
    return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
}

GSvec3 fn_80038A94(void *p) {
    if (OBJ(p)) {
        return GSvec3(F32(p, 0xcc0), F32(p, 0xcc4), F32(p, 0xcc8));
    }
    return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
}

void *fn_80039640(void *p) {
    void *r = GScache::getCachedFile(U32(p, 0xc50), U32(p, 0xc54));
    if (r == NULL) {
        r = fn_8003E42C(fn_8003E15C());
    }
    return r;
}

f32 fn_8003A230(void *p, u32 a, u32 b, u32 c) {
    return fn_80039F60(p, a, b, c).y;
}

u32 fn_800396D4(void *p) {
    void *r = fn_8003E15C();
    if (r) {
        return fn_8003E610(r, U16(p, 0x510));
    }
    return 0;
}

#pragma dont_inline on
GSvec3 fn_8003B890(void *p) {
    GSvec3 v = fn_800387E0(p);
    v.y = fn_8003B7FC(p);
    return v;
}
#pragma dont_inline reset

void fn_8003CB4C(void *p, f32 a, f32 b, f32 c) {
    if (a <= lbl_80640820) {
        U8(p, 0xd44) = 0;
        return;
    }
    F32(p, 0xd34) = a;
    if (a < b) {
        b = a;
    }
    if (a < c) {
        c = a;
    }
    F32(p, 0xd3c) = b;
    F32(p, 0xd38) = c;
}
}

extern "C" {

void fn_801F8BC4(GSobject *o, u8 a);
void fn_8003E238(void *r, void *a);
void fn_80038020(void *p);
void fn_8003881C(void *p, GSvec3 *v);
void fn_801F5A9C(GSobject *o);
u32 fn_80039838(void *p, u32 a);
GSvec3 fn_8003B674(void *p, int i);
f32 PSVECMag(const Vec *v);

void fn_8003CB04(void *p) {
    if (OBJ(p)) {
        fn_801F8BC4(OBJ(p), U8(p, 0xd30));
    }
    U8(p, 0xd44) = 0;
}

void fn_8003CF0C(void *a) {
    void *r = fn_8003E15C();
    if (a == NULL || r == NULL) {
        return;
    } else {
        fn_8003E238(r, a);
    }
}

void fn_80037FD4(u32 *p, int a, int b) {
    if (a) {
        *p |= 2;
    } else {
        *p &= ~2;
    }
    if (b) {
        *p |= 4;
    } else {
        *p &= ~4;
    }
    fn_80038020(p);
}

u32 fn_800394F8(void *p, int i) {
    GSobject *o = OBJ(p);
    if (o == NULL) {
        return 0;
    }
    if (i >= 0) {
        void *q = PTR(o, 4);
        if (i < (q ? U16(q, 8) : 0)) {
            return 1;
        }
    }
    return 0;
}

inline void *objGetNode(GSobject *o, u16 i) {
    void **arr = (void **)PTR(o, 8);
    if (arr == NULL) {
        return NULL;
    }
    if (i >= U16(o, 0xde)) {
        return NULL;
    }
    return arr[i];
}

void *fn_8003997C(void *p, int i) {
    GSobject *o = OBJ(p);
    if (o) {
        return objGetNode(o, i);
    }
    return NULL;
}

f32 fn_8003A1E4(void *p, u32 a, u32 b, u32 c) {
    GSvec3 v = fn_80039F60(p, a, b, c);
    v.y = lbl_80640820;
    return PSVECMag(&v);
}

#pragma dont_inline on
void fn_800388C4(void *p, GSvec3 *v) {
    if (OBJ(p)) {
        fn_8003881C(p, v);
        OBJ(p)->update(lbl_80640820, true);
        fn_801F5A9C(OBJ(p));
    }
}

GSvec3 fn_8003989C(void *p, u32 b) {
    return fn_8003B674(p, fn_80039838(p, b));
}
#pragma dont_inline reset

GSvec3 fn_8003B6F4(void *p) {
    GSobject *o = OBJ(p);
    GSboundingBox *bb = o ? (GSboundingBox *)((u8 *)o + 0x120) : NULL;
    if (bb == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    return bb->mMin;
}

GSvec3 fn_8003B744(void *p) {
    GSobject *o = OBJ(p);
    GSboundingBox *bb = o ? (GSboundingBox *)((u8 *)o + 0x120) : NULL;
    if (bb == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    return bb->mMax;
}
}

extern "C" {

extern const f32 lbl_80640878;
extern const f32 lbl_80640848;
extern const f32 lbl_80640838;
extern const f32 lbl_806408AC;
extern u8 lbl_8063CE34[];

s8 *fn_80032EEC(void *r, u32 a, u16 b, u16 c);
void fn_8003ADC8(void *p, u32 a, f32 x, f32 y);
void fn_8005033C(void *a, void *b, f32 *c, void *d, u32 e, f32 f);
u32 fn_80395E00(void *a, u16 b);
void fn_8003F6F4(void *a, GSobject *o, u32 b);
u32 fn_8003E7C4(void *r, u16 a, u32 b, u8 c, u8 d);
u32 fn_8003E750(void *r, u16 a, u32 b, u8 c, u8 d);

#pragma dont_inline on
s8 *fn_8003967C(void *p, u32 a) {
    void *r = fn_80039640(p);
    if (r == NULL) {
        return 0;
    }
    return fn_80032EEC(r, a, U16(p, 0x510), U16(p, 0x50e));
}

void fn_8003AE30(void *p, u32 a, f32 x, f32 y) {
    while (x - F32(p, 0xcc4) > lbl_80640848) {
        F32(p, 0xcc4) = F32(p, 0xcc4) + lbl_80640878;
    }
    while (F32(p, 0xcc4) - x > lbl_80640848) {
        F32(p, 0xcc4) = F32(p, 0xcc4) - lbl_80640878;
    }
    fn_8003ADC8(p, a, x, y);
}
#pragma dont_inline reset

struct TmpC70 {
    u8 pad[0x190];
    u8 s190[0xae0];
    f32 c70;
};
void fn_8003C8C4(TmpC70 *p, u32 a, u32 b, f32 c) {
    f32 t = (f32)a / lbl_80640838;
    fn_8005033C(p->s190, &p->c70, &t, &p->c70, b, c);
}

void fn_8003C91C(void *p) {
    U8(p, 0) = 0;
    F32(p, 4) = F32(p, 8) = F32(p, 0xc) = F32(p, 0x10) = lbl_80640820;
    U8(p, 0x14) = 0;
    *(GSvec2 *)((u8 *)p + 0x18) = GSvec2(lbl_806408AC, lbl_806408AC);
    *(GSvec2 *)((u8 *)p + 0x20) = *(GSvec2 *)((u8 *)p + 0x28) = GSvec2(lbl_80640820, lbl_80640820);
}

void fn_8003D434(void *p) {
    if (fn_80395E00(lbl_8063CE34 + 0x28, U16(p, 0x51c))) {
        fn_8003F6F4((u8 *)p + 0x524, OBJ(p), (U32(p, 0) >> 11) & 1);
    }
}

u16 fn_8003C25C(void *p, u16 a) {
    void *r = fn_8003E15C();
    if (r) {
        return fn_8003E7C4(r, U16(p, 0x510), a, U16(p, 0x514), U16(p, 0x512));
    }
    return 0;
}

u32 fn_80039838(void *p, u32 a) {
    void *r = fn_8003E15C();
    if (r) {
        return fn_8003E750(r, U16(p, 0x510), a, U16(p, 0x514), U16(p, 0x512));
    }
    return -1;
}

#pragma dont_inline on
BOOL fn_8003DFC0(void *p) {
    return fn_8003C25C(p, 10) != fn_8003C25C(p, 0);
}
#pragma dont_inline reset
}

#include "gs/GSfsys.hpp"
#include "gs/GSthread.hpp"

void operator delete(void *p);

extern "C" {

extern const f32 lbl_80640830;

u32 fn_800399C8(void *p, int a, f32 x, f32 y);
void fn_8003E94C(void *p, s32 a);
u32 fn_8003E544(void *r, u16 a, u8 b, u32 c);
f32 fn_803913B4(void *a, u32 b);
void fn_801F611C(GSobject *o, u32 a);

void fn_80036F88(u32 a, u32 b) {
    if (GScache::getCachedFile(a, b) == NULL) {
        GSfsys::loadFsysEntry(a, b);
        while (GScache::getCachedFile(a, b) == NULL) {
            GSthreadManager::sInstance->sleepCurrentThread();
        }
    }
    GScache::incrementRefCount(a, b);
}

#pragma dont_inline on
void *fn_8003753C(void *p, int del) {
    if (p) {
        fn_800375A4(p);
        if ((u8 *)p + 0x51c) {
            fn_8003E94C((u8 *)p + 0x524, -1);
        }
        if (del > 0) {
            operator delete(p);
        }
    }
    return p;
}

struct TmpCB8 {
    u8 pad[0x28];
    u8 s28[0xc90];
    f32 cb8;
};
void fn_8003AC9C(TmpCB8 *p, u32 a, f32 x, f32 y, u32 b) {
    f32 t = x;
    fn_8005033C(p->s28, &p->cb8, &t, &p->cb8, b, y);
    fn_800399C8(p, a, lbl_80640820, lbl_80640830);
}

struct TmpCC4 {
    u8 pad[0x94];
    u8 s94[0xc30];
    f32 cc4;
};
void fn_8003ADC8(void *p, u32 a, f32 x, f32 y) {
    f32 t = x;
    TmpCC4 *s = (TmpCC4 *)p;
    fn_8005033C(s->s94, &s->cc4, &t, &s->cc4, 0, y);
    fn_800399C8(p, a, lbl_80640820, lbl_80640830);
}

f32 fn_8003D2A0(void *p) {
    u32 x;
    void *r = fn_8003E15C();
    if (r) {
        x = fn_8003E544(r, U16(p, 0x510), U16(p, 0x514), 0);
    } else {
        return lbl_80640820;
    }
    return fn_803913B4(lbl_8063CE34, x);
}

f32 fn_8003B794(void *p) {
    GSvec3 v = fn_800387E0(p);
    GSobject *o = OBJ(p);
    GSboundingBox *bb = o ? (GSboundingBox *)((u8 *)o + 0x120) : NULL;
    if (bb == NULL) {
        return v.y;
    }
    return bb->mMin.y + v.y;
}
#pragma dont_inline reset

void fn_8003C858(void *p, u32 a) {
    if (OBJ(p)) {
        fn_801F611C(OBJ(p), a);
    }
    F32(p, 0xc70) = (f32)a / lbl_80640838;
}
}

extern "C" {

extern const f32 lbl_80640888;
extern const f32 lbl_8064088C;
extern const f32 lbl_80640890;
extern const f32 lbl_8064083C;
extern const f32 lbl_80640894;
extern char lbl_8063D398[4];

u32 fn_8003F604(void *a, u32 b);
u32 fn_80039090(void *p, u32 a, f32 f);
void fn_80050388(void *p);

u32 fn_8003D3B8(void *p, u32 a) {
    u32 r = 0;
    if (fn_80395E00(lbl_8063CE34 + 0x28, U16(p, 0x51c))) {
        r = fn_8003F604((u8 *)p + 0x524, a);
        U32(p, 0) |= 0x200;
    }
    return r;
}

#pragma dont_inline on
void fn_80039200(void *p, u8 a, f32 f) {
    U8(p, 0xbf6) = a;
    fn_80039090(p, fn_8003C25C(p, a), f);
    if (U8(p, 0xbf6) == 0 || U8(p, 0xbf6) == 0x10) {
        U32(p, 0) |= 0x20000;
    } else {
        U32(p, 0) &= ~0x20000;
    }
}

f32 fn_800397BC(void *p) {
    switch (fn_800396D4(p)) {
        case 0:  return lbl_80640830;
        case 1:  return lbl_80640888;
        case 2:  return lbl_8064088C;
        case 3:  return lbl_80640830;
        case 4:  return lbl_80640890;
        case 5:  return lbl_8064083C;
        case 6:  return lbl_80640894;
        default: return lbl_80640830;
    }
}
#pragma dont_inline reset

void *fn_800398EC(void *p, u32 b) {
    if (OBJ(p)) {
        int i = fn_80039838(p, b);
        if (i >= 0 && i < U16(OBJ(p), 0xde)) {
            return objGetNode(OBJ(p), i);
        }
        return NULL;
    }
    return NULL;
}

GSvec3 fn_8003B674(void *p, int i) {
    GSobject *o = OBJ(p);
    if (o && i >= 0 && i < U16(o, 0xde)) {
        _UnkObjectStruct_3 *n = (_UnkObjectStruct_3 *)objGetNode(o, i);
        return n->_unkVec3_2();
    }
    return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
}

#pragma dont_inline on
void fn_8003B14C(void *p) {
    if (PTR(p, 0xd70)) {
        GSnull *n = (GSnull *)fn_800398EC(PTR(p, 0xd70), U32(p, 0xd74));
        if (n) {
            n->unattachChild(OBJ(p));
        }
        PTR(p, 0xd70) = NULL;
    }
    fn_80050388((u8 *)p + 0x1b4);
    fn_80050388((u8 *)p + 0x1d8);
    fn_80050388((u8 *)p + 0x1fc);
    F32(p, 0xd64) = lbl_80640820;
    F32(p, 0xd68) = lbl_80640820;
    F32(p, 0xd6c) = lbl_80640820;
}

u32 fn_80037924(void *p, u32 a, u32 b) {
    void *r = GScache::getCachedFile(a, b);
    PTR(p, 0xbfc) = r;
    if (r == NULL) {
        return 0;
    }
    U32(p, 0xc48) = a;
    U32(p, 0xc4c) = b;
    U32(p, 0) |= 0x10;
    fn_80038518(p, lbl_8063D398);
    return 1;
}
#pragma dont_inline reset
}

struct VDeletable {
    u8 _0[0xc];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual ~VDeletable();
};

inline void *objGetNode2(GSobject *o, u16 i) {
    if (PTR(o, 8) == NULL) {
        return NULL;
    }
    if (i >= U16(o, 0xde)) {
        return NULL;
    }
    return ((void **)PTR(o, 8))[i];
}

inline GSobject *qGetObj(void *q, u16 a) {
    void **arr = (void **)PTR(q, 4);
    if (arr == NULL) {
        return NULL;
    }
    if (a >= U16(PTR(q, 0), 0x18)) {
        return NULL;
    }
    return (GSobject *)arr[a];
}

inline void *objGetMapped(GSobject *o, u16 i) {
    u16 *a = (u16 *)PTR(o, 0x10);
    if (a == NULL) {
        return NULL;
    }
    if (i >= U16(o, 0xe0)) {
        return NULL;
    }
    return objGetNode(o, a[i]);
}

extern "C" {

u32 fn_8003927C(void *p, s8 *r, f32 x, f32 y);
u32 fn_8003F528(void *a, u32 b, u32 c);
void fn_8004E678(void *a, u32 b, u32 c);

void fn_8003CD4C(void *p) {
    VDeletable *v = (VDeletable *)PTR(p, 0xc08);
    if (v) {
        delete v;
        PTR(p, 0xc08) = NULL;
    }
}

void *fn_8003CE88(void *p, int i) {
    GSobject *o = OBJ(p);
    if (o && i < U16(o, 0xe0)) {
        u16 *a = (u16 *)PTR(o, 0x10);
        u16 n;
        if (a == NULL) {
            return NULL;
        }
        if ((u16)i >= U16(o, 0xe0)) {
            return NULL;
        }
        n = a[(u16)i];
        return objGetNode2(o, n);
    }
    return NULL;
}

void *fn_8003DF3C(void *p, u16 a, u16 b) {
    void *q = PTR(p, 0xc00);
    if (q) {
        GSobject *o = qGetObj(q, a);
        if (o) {
            return objGetNode(o, b);
        }
    }
    return NULL;
}

#pragma dont_inline on
s32 fn_80039468(void *p, int a) {
    if (a < 0) {
        return -1;
    }
    s8 *r = fn_8003967C(p, a);
    if (r) {
        u32 x = fn_8003C25C(p, *r);
        return fn_800394F8(p, x) ? x : -1;
    }
    return -1;
}

u32 fn_800399C8(void *p, int a, f32 x, f32 y) {
    if (a < 0) {
        return 0;
    }
    s8 *r = fn_8003967C(p, a);
    if (r) {
        fn_8003927C(p, r, x, y);
        U16(p, 0xbf4) = a;
        return 1;
    }
    return 0;
}
#pragma dont_inline reset

u32 fn_8003D32C(void *p, u32 a, u32 b) {
    u32 r = 0;
    if (fn_80395E00(lbl_8063CE34 + 0x28, U16(p, 0x51c))) {
        r = fn_8003F528((u8 *)p + 0x524, a, b);
        U32(p, 0) |= 0x200;
    }
    return r;
}

void fn_8003DE90(void *p, u32 a, u32 b) {
    if (U8(p, 0xd04) || OBJ(p)) {
        void **arr = (void **)p;
        for (int i = 0; i < 6; i++) {
            if (arr[0xd18 / 4]) {
                fn_8004E678(arr[0xd18 / 4], a, b);
            }
            arr++;
        }
    }
}
}

struct BoxPair {
    GSvec3 a;
    GSvec3 b;
};

extern "C" {

extern const u16 lbl_8040A3F0[];

u32 fn_8003B388(void *p) {
    const u16 *t = lbl_8040A3F0;
    u32 r = 0;
    for (int i = 0; i < 15; i++) {
        if (PTR(p, 4)) {
            r |= *t;
        }
        p = (u8 *)p + 0x24;
        t++;
    }
    return r;
}

f32 fn_8003B7FC(void *p) {
    GSvec3 pos = fn_800387E0(p);
    BoxPair *q = (BoxPair *)((u8 *)p + 0xc0c);
    f32 h;
    if (q == NULL) {
        h = lbl_80640820;
    } else {
        GSvec3 t;
        VECSubtract(&q->b, &q->a, &t);
        GSvec3 d = t;
        h = d.y;
    }
    f32 b = fn_8003B794(p);
    return pos.y + (b + lbl_80640888 * h);
}
}

struct TmpCB4 {
    u8 pad[4];
    u8 s4[0x24];
    u8 s28[0x24];
    u8 s4c[0xc68];
    f32 cb4;
    f32 cb8;
    f32 cbc;
};

extern "C" {

u32 fn_8003E660(void *r, u16 a);

int fn_80039718(void *p) {
    int v = 0;
    void *r = fn_8003E15C();
    if (r) {
        v = fn_8003E660(r, U16(p, 0x510));
    }
    if (v < 100) {
        return 1;
    }
    if (v < 250) {
        return 2;
    }
    if (v < 500) {
        return 3;
    }
    if (v < 1000) {
        return 4;
    }
    if (v < 2000) {
        return 5;
    }
    return 6;
}

struct W3 {
    u32 a, b, c;
};
void fn_8003881C(void *p, GSvec3 *v) {
    GSobject *o = OBJ(p);
    if (o) {
        GSnull **arr = (GSnull **)PTR(o, 8);
        if (arr && arr[0]) {
            GSnull *n = arr[0];
            GSvec3 *d = (GSvec3 *)((u8 *)n + 0x20);
            f32 x = v->x;
            f32 y = v->y;
            d->x = x;
            d->y = y;
            d->z = v->z;
            n->markNeedsUpdate(true);
        }
        *(W3 *)((u8 *)p + 0xcb4) = *(W3 *)v;
        fn_80050388((u8 *)p + 0x4);
        fn_80050388((u8 *)p + 0x28);
        fn_80050388((u8 *)p + 0x4c);
    }
}

void fn_8003ABF4(void *p, u32 a, f32 x, f32 y, f32 f, u32 b) {
    TmpCB4 *s = (TmpCB4 *)p;
    f32 t[2];
    t[0] = x;
    t[1] = y;
    fn_8005033C(s->s4, &s->cb4, &t[0], &s->cb4, b, f);
    fn_8005033C(s->s4c, &s->cbc, &t[1], &s->cbc, b, f);
    fn_800399C8(p, a, lbl_80640820, lbl_80640830);
}

void fn_8003DDA4(void *p, int a) {
    void *q;
    int i;
    U8(p, 0xd04) = 0;
    F32(p, 0xd10) = lbl_80640820;
    if (a) {
        for (i = 0; i < 6; i++) {
            q = PTR(p, 0xd18);
            if (q) {
                void *n = PTR(q, 0x40);
                if (n) {
                    U32(n, 0x104) |= 4;
                    F32(n, 0x110) = lbl_80640820;
                }
            }
            p = (u8 *)p + 4;
        }
    }
}
}

struct TmpD64 {
    u8 pad[0x1b4];
    u8 s1b4[0x24];
    u8 s1d8[0x24];
    u8 s1fc[0xb68];
    f32 d64;
    f32 d68;
    f32 d6c;
};

extern "C" {

void fn_800371D4(void *p) {
    void **arr;
    void *h = fn_8004D80C();
    if (h) {
        arr = (void **)p;
        for (int i = 0; i < 6; i++) {
            if (arr[5]) {
                void *n = PTR(arr[5], 0x40);
                if (n) {
                    U32(n, 0x104) |= 4;
                    F32(n, 0x110) = lbl_80640820;
                }
                fn_8004DCAC(h, arr[5]);
                arr[5] = 0;
            }
            arr++;
        }
        U8(p, 0) = 0;
    }
}

void fn_8003B2D0(void *p, u32 b, f32 x, f32 y, f32 z, f32 f) {
    TmpD64 *s = (TmpD64 *)p;
    if (PTR(p, 0xd70)) {
        GSvec3 pos = fn_800387E0(p);
        fn_8005033C(s->s1b4, &s->d64, &z, &s->d64, b, f);
        fn_8005033C(s->s1d8, &s->d68, &x, &s->d68, b, f);
        fn_8005033C(s->s1fc, &s->d6c, &y, &s->d6c, b, f);
    }
}
}

inline u8 *animEntry(void *q, u16 idx) {
    if (q == NULL) {
        return NULL;
    }
    if (idx >= U16(q, 8)) {
        return NULL;
    }
    return (u8 *)PTR(q, 0xc) + idx * 0x30;
}

extern "C" {

f32 fn_80039DC0(void *p, u32 a, int c) {
    if (OBJ(p) == NULL) {
        return lbl_80640820;
    }
    u16 idx = fn_8003C25C(p, a);
    u8 *e = animEntry(PTR(OBJ(p), 4), idx);
    if (e) {
        if (c < 0) {
            return F32(e, 0xc);
        }
        if (c < 3) {
            return ((f32 *)(e + 4))[c];
        }
    }
    return lbl_80640820;
}

f32 fn_80039E80(void *p, u16 a, int c) {
    if (c == 0) {
        return lbl_80640820;
    }
    if (OBJ(p)) {
        u16 idx = fn_8003C25C(p, a);
        u8 *e = animEntry(PTR(OBJ(p), 4), idx);
        if (e) {
            int k = c - 1;
            if (k < 0 || k >= 3) {
                return F32(e, 0xc);
            }
            return ((f32 *)(e + 4))[k];
        }
    }
    return lbl_80640820;
}
}

struct BmSub24 {
    u8 d[0x24];
};

struct BmModel {
    u8 pad0[4];
    BmSub24 s[15];
    u8 pad220[0xcb4 - 0x220];
    f32 pos[3];
    f32 rot[3];
    f32 v3[3];
};

extern "C" {

void fn_8003AB30(void *p, f32 *v, u32 a, u32 b, f32 f) {
    BmModel *m = (BmModel *)p;
    fn_8005033C(&m->s[0], &m->pos[0], &v[0], &m->pos[0], b, f);
    fn_8005033C(&m->s[1], &m->pos[1], &v[1], &m->pos[1], b, f);
    fn_8005033C(&m->s[2], &m->pos[2], &v[2], &m->pos[2], b, f);
    fn_800399C8(p, a, lbl_80640820, lbl_80640830);
}

void fn_8003AD04(void *p, f32 *v, u32 a, u32 b, f32 f) {
    BmModel *m = (BmModel *)p;
    fn_8005033C(&m->s[3], &m->rot[0], &v[0], &m->rot[0], b, f);
    fn_8005033C(&m->s[4], &m->rot[1], &v[1], &m->rot[1], b, f);
    fn_8005033C(&m->s[5], &m->rot[2], &v[2], &m->rot[2], b, f);
    fn_800399C8(p, a, lbl_80640820, lbl_80640830);
}

void fn_8003AE84(void *p, f32 *v, int a, u32 b, f32 f) {
    BmModel *m = (BmModel *)p;
    fn_8005033C(&m->s[6], &m->v3[0], &v[0], &m->v3[0], b, f);
    fn_8005033C(&m->s[7], &m->v3[1], &v[1], &m->v3[1], b, f);
    fn_8005033C(&m->s[8], &m->v3[2], &v[2], &m->v3[2], b, f);
    if (a >= 0) {
        fn_800399C8(p, a, lbl_80640820, lbl_80640830);
    }
}
}

extern "C" {

void eulerToQuatC(void);

f32 fn_80039CF0(void *p, u32 a, int c) {
    s8 *r = fn_8003967C(p, a);
    if (r && OBJ(p)) {
        u16 idx = fn_8003C25C(p, *r);
        u8 *e = animEntry(PTR(OBJ(p), 4), idx);
        if (e) {
            if (c < 0) {
                return F32(e, 0xc);
            }
            if (c < 3) {
                return ((f32 *)(e + 4))[c];
            }
        }
    }
    return lbl_80640820;
}

#pragma dont_inline on
void fn_80039C10(void *p) {
    if (U32(p, 0) & 0x1000) {
        if (fn_8003C25C(p, 10) != fn_8003C25C(p, 0)) {
            f32 f = fn_80039DC0(p, 10, 2);
            F32(p, 0xd80) = f;
            fn_80039200(p, 10, lbl_80640820);
            fn_8003AC9C((TmpCB8 *)p, -1, lbl_80640820, f, 0);
        } else {
            fn_80039200(p, 0, lbl_80640820);
        }
    } else {
        fn_80039200(p, 0, lbl_80640820);
    }
    U32(p, 0) &= ~0x200000;
}
#pragma dont_inline reset

struct W12 {
    u32 a, b, c;
};
void fn_80038AD0(void *p, GSvec3 *v) {
    if (OBJ(p)) {
        u32 a = ((u32 *)v)[0];
        u32 b = ((u32 *)v)[1];
        u32 c = ((u32 *)v)[2];
        ((u32 *)((u8 *)p + 0xcc0))[0] = a;
        ((u32 *)((u8 *)p + 0xcc0))[1] = b;
        ((u32 *)((u8 *)p + 0xcc0))[2] = c;
        GSquat q;
        GSmath::eulerToQuat(&q, v);
        GSnull **arr = (GSnull **)PTR(OBJ(p), 8);
        if (arr && arr[0]) {
            GSnull *n = arr[0];
            *(GSquat *)((u8 *)n + 0x2c) = q;
            U16(n, 0x10) &= ~4;
            n->markNeedsUpdate(true);
        }
        fn_80050388((u8 *)p + 0x70);
        fn_80050388((u8 *)p + 0x94);
        fn_80050388((u8 *)p + 0xb8);
    }
}
}

extern "C" {

extern u8 lbl_8049362C[];

void fn_800505C0(void *p);
void fn_8003A958(void *p, void *a, u32 b);

void fn_80039544(void *p, int on) {
    if (U16(p, 0xc68) == 0x100) {
        if (PTR(p, 0xc00) == NULL) {
            return;
        }
        for (u8 i = 0; i < U16(PTR(PTR(p, 0xc00), 0), 0x18); i++) {
            GSobject *o = qGetObj(PTR(p, 0xc00), i);
            if (o) {
                if (on) {
                    U16(o, 0xdc) |= 0x10;
                } else {
                    U16(o, 0xdc) &= ~0x10;
                }
            }
        }
    } else if (on) {
        GSobject *o = OBJ(p);
        if (o) {
            U16(o, 0xdc) |= 0x10;
        }
    } else if (!(U32(p, 0) & 0x4000)) {
        GSobject *o = OBJ(p);
        if (o) {
            U16(o, 0xdc) &= ~0x10;
        }
    }
}

void fn_80038FB0(void *p) {
    if (U16(p, 0x51c) >= 9 || U8(p, 0x520) == 0) {
        fn_800505C0((u8 *)p + 0x460);
        fn_8003A958(p, lbl_8049362C, 14);
        if (OBJ(p)) {
            GSnull *n = (GSnull *)objGetNode(OBJ(p), fn_80039838(p, 14));
            if (n) {
                n->startAnimation(n->getIndex(), 1, lbl_80640820, lbl_80640830);
            }
        }
    }
}
}

extern "C" {

void fn_80051134(void *a, u32 b, f32 *c, u32 d, u32 e, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5);

struct NodeSet {
    u32 flags;
    u32 fsys;
    u32 file;
    GSnull *nodes[8];
};
inline void hideNode(void *n) {
    U32(n, 0x104) |= 4;
    F32(n, 0x110) = lbl_80640820;
}
void fn_80037000(void *p) {
    GSnull **arr;
    int i;
    NodeSet *s = (NodeSet *)p;
    s->flags = 0;
    arr = (GSnull **)s;
    for (i = 0; i < 8; i++) {
        if (arr[3]) {
            hideNode(arr[3]);
            GSnull *parent = (GSnull *)PTR(arr[3], 0xc0);
            if (parent) {
                parent->unattachChild(arr[3]);
            }
            delete arr[3];
            arr[3] = NULL;
        }
        arr++;
    }
    if (s->fsys || s->file) {
        GScache::decrementRefCount(s->fsys, s->file);
    }
    s->fsys = 0;
    s->file = 0;
}

void fn_8003AF50(void *p, f32 *v, u32 a, u32 b, f32 x, f32 y) {
    fn_80051134((u8 *)p + 0x220, a, (f32 *)((u8 *)p + 0xccc), b, 0, v[0], x, y, lbl_80640820, lbl_80640820);
    fn_80051134((u8 *)p + 0x2e0, a, (f32 *)((u8 *)p + 0xcd0), b, 0, v[1], x, y, lbl_80640820, lbl_80640820);
    fn_80051134((u8 *)p + 0x3a0, a, (f32 *)((u8 *)p + 0xcd4), b, 0, v[2], x, y, lbl_80640820, lbl_80640820);
}
}

extern "C" {

f32 fn_8003A5EC(void *p, int k) {
    f32 r = lbl_80640820;
    u16 id;
    if (OBJ(p) == NULL) {
        return r;
    }
    if (k == 0) {
        id = 0x15;
    } else if (k == 1) {
        id = 0x17;
    } else {
        return r;
    }
    GSnull *n = (GSnull *)objGetNode(OBJ(p), fn_80039838(p, id));
    if (n) {
        void *d = PTR(n, 0x1c);
        r = d ? F32(d, 0x1c) : lbl_80640820;
    }
    return r;
}

void fn_8003B044(void *p, void *a, u32 b, u32 flags) {
    if (!(flags & 0x80000000)) {
        if (flags & 8) {
            flags &= ~8;
            if (flags & 1) {
                flags |= 0x40;
            }
            if (flags & 2) {
                flags |= 0x80;
            }
            if (flags & 4) {
                flags |= 0x100;
            }
        }
        if (!(flags & 1)) {
            flags |= 9;
        }
        if (!(flags & 2)) {
            flags |= 0x12;
        }
    }
    GSnull *n = (GSnull *)fn_800398EC(a, b);
    if (n) {
        GSnull *root = (GSnull *)objGetNode(OBJ(p), 0);
        root->initTransform(true);
        n->attachChild((u16)flags, OBJ(p), NULL, 3);
        PTR(p, 0xd70) = a;
        U32(p, 0xd74) = b;
    }
}
}

inline void clearAnimFlag(void *c) {
    if (c) {
        u16 f = U16(c, 6);
        if (!(f & 0x10)) {
            U16(c, 6) = f & ~1;
        }
    }
}

extern "C" {

void fn_802233C8(Mtx m, void *a, u32 b);
void C_QUATMtx(Quaternion *q, const Mtx m);

void fn_8003A958(void *p, void *a, u32 b) {
    if (OBJ(p)) {
        GSnull *n = (GSnull *)objGetNode(OBJ(p), fn_80039838(p, b));
        if (n) {
            Mtx m;
            GSquat q;
            fn_802233C8(m, a, 0);
            C_QUATMtx(&q, m);
            *(GSquat *)((u8 *)n + 0x2c) = q;
            U16(n, 0x10) &= ~4;
            n->markNeedsUpdate(true);
            if (PTR(n, 4) && !(U16(PTR(n, 4), 6) & 0x10)) {
                U16(PTR(n, 4), 6) &= ~1;
            }
            if (PTR(n, 8) && !(U16(PTR(n, 8), 6) & 0x10)) {
                U16(PTR(n, 8), 6) &= ~1;
            }
        }
    }
}
}

extern "C" {

void *fn_80200B2C(void *a, void *b, void *c, u32 d, u32 e);
void fn_80200C54(void *h, GSobject *o);
void fn_80200D08(void *h, GSobject *o);
void fn_80200D78(void *h);
void fn_8003FD78(void *a, void *h, u32 b);

u32 fn_8003D9FC(void *p, void *a, void *b, void *c, u32 d) {
    if (a == NULL || b == NULL || c == NULL || OBJ(p) == NULL) {
        return 0;
    }
    void *h = fn_80200B2C(a, b, c, d, 1);
    if (h == NULL) {
        return 0;
    }
    fn_80200C54(h, OBJ(p));
    if (U16(p, 0x50c) == 2 && fn_80395E00(lbl_8063CE34 + 0x28, U16(p, 0x51c))) {
        fn_8003FD78((u8 *)p + 0x524, h, 1);
    }
    GSthreadManager::sInstance->sleepCurrentThread();
    GSthreadManager::sInstance->sleepCurrentThread();
    fn_80200D08(h, OBJ(p));
    if (U16(p, 0x50c) == 2 && fn_80395E00(lbl_8063CE34 + 0x28, U16(p, 0x51c))) {
        fn_8003FD78((u8 *)p + 0x524, h, 0);
    }
    fn_80200D78(h);
    return 1;
}
}

extern "C" {

extern const f32 lbl_80640884;
extern const f32 lbl_8064087C;
extern const f32 lbl_80640844;
extern const f32 lbl_80640880;

double atan2(double y, double x);
double asin(double x);
f32 fn_8003AA74(void *p, f32 a, f32 b);
void fn_8003A6C8(void *p, GSvec3 *e, u32 c, u32 b, f32 f);
}

inline f32 safeAsin(f32 x) {
    if (x >= lbl_80640830) {
        return lbl_8064087C;
    }
    if (x <= lbl_80640844) {
        return lbl_80640880;
    }
    return asin(x);
}

extern "C" {

inline f32 myAtan2(f32 y, f32 x) {
    return atan2(y, x);
}
void fn_80038D08(void *p, void *q, u32 b, f32 f) {
    if (U16(p, 0x51c) >= 9 || U8(p, 0x520) == 0) {
        GSvec3 d = fn_8003B674(q, 10) - fn_8003B674(p, 14);
        f32 yaw = myAtan2(d.x, d.z);
        yaw -= fn_8003AA74(p, fn_80038A94(p).y, yaw);
        f32 pitch = safeAsin(d.y / PSVECMag(&d));
        fn_8003A6C8(p, &GSvec3(-pitch, yaw, lbl_80640820), 14, b, f);
    }
}

void fn_80038E58(void *p, void *q) {
    if (U16(p, 0x51c) >= 9 || U8(p, 0x520) == 0) {
        f32 yaw;
        f32 lim = lbl_80640884;
        GSvec3 d = fn_8003B674(q, 10) - fn_8003B674(p, 14);
        yaw = myAtan2(d.x, d.z);
        yaw -= fn_8003AA74(p, fn_80038A94(p).y, yaw);
        if (yaw > lim) {
            yaw = lim;
        }
        if (yaw < -lim) {
            yaw = -lim;
        }
        f32 pitch = safeAsin(d.y / PSVECMag(&d));
        fn_8003A958(p, &GSvec3(-pitch, yaw, lbl_80640820), 14);
    }
}
}

extern "C" {

extern const f32 lbl_80640870;
extern const f32 lbl_80640874;

void fn_801F5364(GSobject *o, u16 a, u32 kind, f32 t, f32 speed, bool b, bool c, bool d, f32 g, bool e, bool f);

struct TmpD80 {
    u8 pad[0xd80];
    f32 d80;
    u32 d84;
    bool d88;
    bool d89;
    u8 pad2[2];
    f32 d8c;
    f32 d90;
};

u32 fn_80039090(void *p, u32 a, f32 t) {
    TmpD80 *s = (TmpD80 *)p;
    if (OBJ(p) == NULL) {
        return 0;
    }
    if (!fn_800394F8(p, a)) {
        return 0;
    }
    if (U32(p, 0) & 0x4000) {
        ((void (*)(void *))fn_8003D4B4)(p);
        return 1;
    }
    u8 *e = animEntry(PTR(OBJ(p), 4), a);
    u8 kind = e[0x28];
    F32(p, 0xd90) = lbl_80640830;
    if ((F32(p, 0xd80) < lbl_80640870 && F32(p, 0xd80) > lbl_80640874) || F32(p, 0xd8c) > lbl_80640820) {
        OBJ(p)->startAnimation(a, kind, t, lbl_80640830, false, false, false);
        F32(p, 0xd8c) = lbl_80640820;
    } else {
        fn_801F5364(OBJ(p), a, kind, t, lbl_80640830, true, true, false, s->d80, s->d88, s->d89);
        F32(p, 0xd8c) = F32(p, 0xd80);
    }
    U16(p, 0xbf8) = a;
    U32(p, 0xcb0) = 0;
    return 1;
}
}

extern "C" {

u32 fn_8003E698(void *r, u16 a, u8 c, u16 d);
u32 fn_8003E6E0(void *r, u16 a, u8 b, u8 c, u16 d);

u32 fn_8003CF54(void *p, u16 a, u8 b, u16 c, u16 d, u32 e) {
    void *r = fn_8003E15C();
    if (r == NULL) {
        return 0;
    }
    u32 fs = fn_8003E698(r, a, c, d);
    u32 fi = fn_8003E6E0(r, a, b, c, d);
    if (fs == 0 || fi == 0) {
        return 0;
    }
    u32 keep = U32(p, 0) & 0x800;
    fn_800375A4(p);
    U32(p, 0) |= keep;
    fn_80036F88(fs, fi);
    if (a == 0x147) {
        fn_80036F88(fs, 0x9310C00);
        fn_80036F88(fs, 0x9300C00);
        U32(p, 0xc58) = fs;
        U32(p, 0xc5c) = 0x9310C00;
        U32(p, 0xc60) = fs;
        U32(p, 0xc64) = 0x9300C00;
    }
    U32(p, 0xcd8) = 0;
    U32(p, 0xce0) = 0;
    GSfsys::fn_80249890(fs);
    GSfsys::releaseAllCacheEntriesForFsys(fs);
    GSthreadManager::sInstance->sleepCurrentThread();
    U16(p, 0x510) = a;
    U16(p, 0x512) = d;
    U8(p, 0x516) = b;
    U16(p, 0x514) = c;
    U32(p, 0x518) = e;
    U16(p, 0x50c) = 1;
    fn_80037924(p, fs, fi);
    U16(p, 0x50c) = 1;
    GSthreadManager::sInstance->sleepCurrentThread();
    return 1;
}
}

#include "gs/render/GSrenderTarget.hpp"

struct EffObj {
    u8 _0[0xc];
    virtual u8 start();
};

extern "C" {

extern const f32 lbl_80640898;

EffObj *fn_8021D424(void *m, GSobject *o);
EffObj *fn_8021EA48(void *m, GSobject *o, u32 a);

void fn_8003C6B4(void *p, f32 f) {
    if (OBJ(p)) {
        fn_8003CD4C(p);
        void *m = GShierMemObject::operator new(0x70);
        EffObj *x = (EffObj *)m;
        if (m) {
            x = fn_8021D424(m, OBJ(p));
        }
        if (x) {
            PTR(p, 0xc08) = x;
            U8(x, 0x1e) = U8(p, 0xdb4);
            U8(x, 0x20) = U8(p, 0xdb5);
            U8(x, 0x28) = U8(p, 0xdc0);
            U8(x, 0x29) = U8(p, 0xdc1);
            U8(x, 0x2a) = U8(p, 0xdc2);
            U8(x, 0x2b) = U8(p, 0xdc3);
            F32(x, 0x6c) = f;
            F32(x, 0x48) = F32(p, 0xdb8);
            U8(x, 0x1f) = U8(p, 0xdb6);
            F32(x, 0x5c) = F32(p, 0xdc4);
            F32(x, 0x60) = F32(p, 0xdc8);
            F32(x, 0x64) = F32(p, 0xdcc);
            F32(x, 0x44) = F32(p, 0xdbc);
            F32(x, 0x38) = F32(p, 0xdd0);
            F32(x, 0x3c) = F32(p, 0xdd4);
            F32(x, 0x40) = F32(p, 0xdd8);
            F32(x, 0x2c) = F32(p, 0xddc);
            F32(x, 0x30) = F32(p, 0xde0);
            F32(x, 0x34) = F32(p, 0xde4);
            F32(x, 0x58) = F32(p, 0xde8);
            F32(x, 0x4c) = F32(p, 0xdec);
            F32(x, 0x50) = F32(p, 0xdf0);
            F32(x, 0x54) = F32(p, 0xdf4);
            if ((U8(x, 8) = x->start()) != 0) {
                GSrenderTarget::_unkFunc_1(U32(x, 4));
            }
        }
    }
}

void fn_8003CDA4(void *p) {
    if (OBJ(p)) {
        fn_8003CD4C(p);
        void *m = GShierMemObject::operator new(0x28);
        EffObj *x = (EffObj *)m;
        if (m) {
            x = fn_8021EA48(m, OBJ(p), 0);
        }
        if (x) {
            PTR(p, 0xc08) = x;
            *(GSvec2 *)((u8 *)x + 0x1c) = GSvec2(lbl_80640898, lbl_80640888);
            U32(x, 0x24) = 1;
            if ((U8(x, 8) = x->start()) != 0) {
                GSrenderTarget::_unkFunc_1(U32(x, 4));
            }
        }
    }
}
}

inline void vec2AddTo(GSvec2 *a, GSvec2 b) {
    a->x = a->x + b.x;
    a->y = a->y + b.y;
}

inline GSvec2 vec2Scale(const GSvec2 &v, f32 s) {
    return GSvec2(v.x * s, v.y * s);
}

extern "C" {

void fn_801F8B40(GSobject *o, u8 a, GSvec2 *v);
void fn_801F8BA0(GSobject *o, u8 a, u8 b);

inline void addD58(void *p, GSvec2 b) {
    F32(p, 0xd58) = F32(p, 0xd58) + b.x;
    F32(p, 0xd5c) = F32(p, 0xd5c) + b.y;
}

struct V2 : GSvec2 {
    void add(GSvec2 b) {
        x = x + b.x;
        y = y + b.y;
    }
};

struct TmpD58 {
    u8 pad[0xd58];
    V2 d58;
};

void fn_8003CBB8(void *p, f32 dt) {
    if (U8(p, 0xd44) == 0) {
        return;
    }
    if (F32(p, 0xd34) < F32(p, 0xd40)) {
        fn_8003CB04(p);
        return;
    }
    addD58(p, vec2Scale(*(GSvec2 *)((u8 *)p + 0xd50), F32(p, 0xd60)));
    GSobject *o = OBJ(p);
    if (o) {
        fn_801F8B40(o, U8(p, 0xd30), (GSvec2 *)((u8 *)p + 0xd58));
    }
    if (F32(p, 0xd40) < F32(p, 0xd3c) && F32(p, 0xd3c) > lbl_80640820) {
        f32 r = F32(p, 0xd40) / F32(p, 0xd3c);
        if (OBJ(p)) {
            fn_801F8BA0(OBJ(p), U8(p, 0xd30), (u8)(lbl_80640838 * r));
        }
    } else if (F32(p, 0xd40) > F32(p, 0xd34) - F32(p, 0xd38) && F32(p, 0xd38) > lbl_80640820) {
        f32 r = (F32(p, 0xd40) - (F32(p, 0xd34) - F32(p, 0xd38))) / F32(p, 0xd38);
        if (OBJ(p)) {
            fn_801F8BA0(OBJ(p), U8(p, 0xd30), (u8)(lbl_80640838 - lbl_80640838 * r));
        }
    } else {
        fn_801F8BA0(OBJ(p), U8(p, 0xd30), 0xff);
    }
    F32(p, 0xd40) += dt;
}
}

extern "C" {

void fn_8003FEF0(void *a, u32 b);

struct TmpC90 {
    u8 pad[0xc90];
    void *n[4];
};

void fn_8003837C(void *p, int on) {
    GSobject *o = OBJ(p);
    if (o == NULL) {
        return;
    }
    if (!(U32(p, 0) & 0x100000) && !(U32(p, 0) & 0x80000)) {
        return;
    }
    if (on) {
        U16(o, 0xdc) |= 1;
        fn_8003FEF0((u8 *)p + 0x524, 1);
        void *n;
        for (u16 i = 0; i < 4; i++) {
            n = ((TmpC90 *)p)->n[i];
            if (n) {
                if ((u16)(i + 0xffff) <= 1) {
                    U16(n, 0x10) &= ~2;
                } else {
                    U16(n, 0x10) |= 2;
                }
            }
        }
        U32(p, 0) |= 1;
    } else {
        U16(o, 0xdc) &= ~1;
        fn_8003FEF0((u8 *)p + 0x524, 0);
        for (u16 i = 0; i < 4; i++) {
            void *n = ((TmpC90 *)p)->n[i];
            if (n) {
                U16(n, 0x10) &= ~2;
            }
        }
        U32(p, 0) &= ~1;
    }
}
}

#include "gs/GSscene.hpp"

struct RefPair {
    u32 a;
    u32 b;
};

struct TmpC58 {
    u8 pad[0xc58];
    RefPair refs[2];
};

extern "C" {

void fn_801E37F0(void *a);
void fn_8003EAB0(void *a);

void fn_800375A4(void *p) {
    GSnull **arr;
    int i;
    Unk80040274 *m = fn_800401F4();
    if (m) {
        // The camera code handles objects as u32 ids.
        fn_800401FC(m, (u32)p);
    }
    arr = (GSnull **)p;
    for (i = 0; i < 4; i++) {
        if (arr[0xc90 / 4]) {
            delete arr[0xc90 / 4];
            arr[0xc90 / 4] = NULL;
        }
        arr++;
    }
    VDeletable *v = (VDeletable *)PTR(p, 0xc08);
    if (v) {
        delete v;
        PTR(p, 0xc08) = NULL;
    }
    if (OBJ(p)) {
        OBJ(p)->fn_801F6390();
    }
    GSscene *sc = (GSscene *)PTR(p, 0xc00);
    if (sc) {
        delete sc;
        PTR(p, 0xc00) = NULL;
    }
    fn_800371D4((u8 *)p + 0xd04);
    if (PTR(p, 0xbfc)) {
        if (U32(p, 0) & 0x80) {
            fn_801E37F0(PTR(p, 0xbfc));
            GSmem::free(PTR(p, 0xbfc));
        } else {
            GScache::decrementRefCount(U32(p, 0xc48), U32(p, 0xc4c));
            for (RefPair *e = ((TmpC58 *)p)->refs; e != ((TmpC58 *)p)->refs + 2; e++) {
                if (e->a) {
                    GScache::decrementRefCount(e->a, e->b);
                }
            }
            memset((u8 *)p + 0xc58, 0, 0x10);
        }
        PTR(p, 0xbfc) = NULL;
    }
    fn_80037000((u8 *)p + 0xcd8);
    fn_8003EAB0((u8 *)p + 0x524);
    U32(p, 0xc48) = 0;
    U32(p, 0xc4c) = 0;
    PTR(p, 0xc04) = NULL;
    U32(p, 0) &= 0x20807;
    U16(p, 0x510) = 0;
    U16(p, 0x512) = 0;
    U8(p, 0x516) = 0;
    U16(p, 0x514) = 0;
    U32(p, 0x518) = 0;
}
}

extern "C" {

void fn_80039A54(void *p, int flag, f32 f) {
    F32(p, 0xd78) = f + fn_80039DC0(p, 8, 2);
    if (U16(p, 0x510) == 0x167) {
        flag = 0;
    }
    if (U32(p, 0) & 0x1000) {
        if (fn_8003C25C(p, 10) != fn_8003C25C(p, 0)) {
            if (fn_800394F0((Unk80036F88 *)p) == 10) {
                F32(p, 0xd7c) = fn_8003B794(p);
            }
            if (U16(p, 0x510) == 0xb2) {
                return;
            }
            if (flag) {
                F32(p, 0xd80) = F32(p, 0xd78);
                fn_80039200(p, 8, lbl_80640820);
                fn_8003AC9C((TmpCB8 *)p, -1, F32(p, 0xd7c), F32(p, 0xd78), 0);
            } else {
                F32(p, 0xd80) = lbl_80640820;
                fn_80039200(p, 8, lbl_80640820);
                GSvec3 v = fn_800387E0(p);
                v.y = F32(p, 0xd7c);
                fn_8003881C(p, &v);
            }
        } else {
            if (flag) {
                F32(p, 0xd80) = lbl_80640898 * F32(p, 0xd78);
            } else {
                F32(p, 0xd80) = lbl_80640820;
            }
            fn_80039200(p, 8, lbl_80640820);
        }
    } else {
        if (flag) {
            F32(p, 0xd80) = lbl_80640898 * F32(p, 0xd78);
        } else {
            F32(p, 0xd80) = lbl_80640820;
        }
        fn_80039200(p, 8, lbl_80640820);
    }
    U32(p, 0) |= 0x200000;
}
}

extern "C" {

GSvec3 fn_8003A430(void *p, u32 a, f32 t) {
    s8 *r = fn_8003967C(p, a);
    if (r == NULL || OBJ(p) == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    u16 id = fn_8003C25C(p, *r);
    GSobject *o = OBJ(p);
    if (objGetNode(o, 0) == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    if (!(U32(p, 0) & 1)) {
        U16(o, 0xdc) |= 1;
    }
    OBJ(p)->startAnimation(id, 0, t, lbl_80640830, false, false, false);
    OBJ(p)->update(lbl_80640820, true);
    GSvec3 d = fn_8003B744(p) - fn_8003B6F4(p);
    if (!(U32(p, 0) & 1)) {
        U16(OBJ(p), 0xdc) &= ~1;
    }
    OBJ(p)->startAnimation(0, 1, lbl_80640820, lbl_80640830, false, false, false);
    OBJ(p)->update(lbl_80640820, true);
    return d;
}
}

extern "C" {

GSvec3 fn_8003A270(void *p, u32 a, u32 b, f32 t) {
    s8 *r = fn_8003967C(p, a);
    if (r == NULL || OBJ(p) == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    u16 id = fn_8003C25C(p, *r);
    GSnull *root = (GSnull *)objGetNode(OBJ(p), 0);
    GSnull *n = (GSnull *)objGetNode(OBJ(p), fn_80039838(p, b));
    if (root == NULL || n == NULL) {
        return GSvec3(lbl_80640820, lbl_80640820, lbl_80640820);
    }
    OBJ(p)->startAnimation(id, 0, t, lbl_80640830, false, false, false);
    root->update(lbl_80640820);
    GSvec3 v = ((_UnkObjectStruct_3 *)n)->_unkVec3_2();
    OBJ(p)->startAnimation(0, 1, lbl_80640820, lbl_80640830, false, false, false);
    return v;
}
}

extern "C" {

u32 fn_80395DE4(void *a);
u32 fn_80395ED8(void *a, u16 id);
u32 fn_80395F0C(void *a, u16 id);
u32 fn_80395E70(void *a, u16 id);
u32 fn_80395EA4(void *a, u16 id);
u16 fn_80395E38(void *a, u16 id);
void fn_8003F29C(void *a, u16 id, u32 b, s8 c, u16 *d, u32 e);
void fn_8003E9A0(void *a);

u32 fn_8003D0C0(void *p, u16 id, u32 b, s8 c, u16 *d) {
    u32 fs;
    u32 fi;
    if (id >= fn_80395DE4(lbl_8063CE34 + 0x28)) {
        return 0;
    }
    if (b) {
        fs = fn_80395ED8(lbl_8063CE34 + 0x28, id);
        fi = fn_80395F0C(lbl_8063CE34 + 0x28, id);
    } else {
        fs = fn_80395E70(lbl_8063CE34 + 0x28, id);
        fi = fn_80395EA4(lbl_8063CE34 + 0x28, id);
    }
    if (fs == 0 || fi == 0) {
        return 0;
    }
    u32 keep = U32(p, 0) & 0x800;
    fn_800375A4(p);
    U32(p, 0) |= keep;
    U16(p, 0x510) = id + 999;
    U16(p, 0x514) = (b == 0);
    void *cached = GScache::getCachedFile(fs, fi);
    U16(p, 0x51c) = id;
    U8(p, 0x520) = b;
    if (c >= 0) {
        U8(p, 0x521) = c;
    }
    if (fn_80395E00(lbl_8063CE34 + 0x28, id)) {
        U16(p, 0x51e) = fn_80395E38(lbl_8063CE34 + 0x28, id);
        fn_8003F29C((u8 *)p + 0x524, id, b, c, d, 1);
    } else {
        U16(p, 0x51e) = -1;
        fn_8003E9A0((u8 *)p + 0x524);
        if (cached == NULL) {
            GSfsys::loadFsysEntry(fs, fi);
            while (GScache::getCachedFile(fs, fi) == NULL) {
                GSthreadManager::sInstance->sleepCurrentThread();
            }
        }
        GScache::incrementRefCount(fs, fi);
    }
    fn_80037924(p, fs, fi);
    U16(p, 0x50c) = 2;
    GSfsys::fn_80249890(fs);
    GSfsys::releaseAllCacheEntriesForFsys(fs);
    return 1;
}
}

extern "C" {

u32 fn_8003927C(void *p, s8 *r, f32 t, f32 speed) {
    TmpD80 *s = (TmpD80 *)p;
    if (OBJ(p) == NULL) {
        return 0;
    }
    if (r == NULL) {
        return 0;
    }
    u32 id = fn_8003C25C(p, *r);
    if (!fn_800394F8(p, id)) {
        return 0;
    }
    if (U32(p, 0) & 0x4000) {
        ((void (*)(void *))fn_8003D4B4)(p);
        return 1;
    }
    u8 *e = animEntry(PTR(OBJ(p), 4), id);
    u8 kind = e[0x28];
    F32(p, 0xd90) = lbl_80640830;
    if ((F32(p, 0xd80) < lbl_80640870 && F32(p, 0xd80) > lbl_80640874) || F32(p, 0xd8c) > lbl_80640820) {
        OBJ(p)->startAnimation(id, kind, t, speed, false, false, false);
        F32(p, 0xd8c) = lbl_80640820;
    } else {
        fn_801F5364(OBJ(p), id, kind, t, speed, false, true, false, lbl_80640820, s->d88, s->d89);
        F32(p, 0xd8c) = F32(p, 0xd80);
    }
    U16(p, 0xbf8) = id;
    U8(p, 0xbf6) = *(u8 *)r;
    PTR(p, 0xcb0) = r + 1;
    if (U8(p, 0xbf6) == 0 || U8(p, 0xbf6) == 0x10) {
        U32(p, 0) |= 0x20000;
    } else {
        U32(p, 0) &= ~0x20000;
    }
    return 1;
}
}

extern "C" {

void fn_801F58FC(GSobject *o);
void fn_80037D2C(void *p, int a);

void fn_8003D82C(Unk80036F88 *obj, u32 kind) {
    void *p = obj;
    int k = kind;
    switch (k) {
        case 0:
            if (!(U32(p, 0) & 0x4000)) {
                return;
            }
            if (OBJ(p)) {
                U16(OBJ(p), 0xdc) &= ~0x10;
            }
            U32(p, 0) &= ~0x4000;
            break;
        case 1:
            if (!(U32(p, 0) & 0x80000)) {
                return;
            }
            U32(p, 0) &= ~0x80000;
            break;
        case 2:
            if (!(U32(p, 0) & 0x100000)) {
                return;
            }
            U32(p, 0) &= ~0x100000;
            break;
        case 3:
            if (!(U32(p, 0) & 0x2000)) {
                return;
            }
            {
                u16 id = fn_8003C25C(p, 0x15);
                if (OBJ(p)) {
                    fn_801F58FC(OBJ(p));
                    if (id < 0xff) {
                        OBJ(p)->startAnimation(id, 0, lbl_80640820, lbl_80640830, false, false, false);
                    }
                }
            }
            U32(p, 0) &= ~0x2000;
            break;
        default: return;
    }
    TmpC90 *s = (TmpC90 *)p;
    if (s->n[k]) {
        hideNode(s->n[k]);
        delete (GSnull *)s->n[k];
        s->n[k] = NULL;
    }
    if ((u32)(k - 1) <= 1) {
        fn_80037D2C(p, !(U32(p, 0) & 1));
        fn_80037D2C(p, !(U32(p, 0) & 1));
        fn_80038020(p);
    }
}
}
