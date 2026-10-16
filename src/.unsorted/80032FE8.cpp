#include ".unsorted/80032FE8.hpp"

#include "gs/GSmath.hpp"
#include "gs/GSmem.hpp"
#include "gs/GSobject.hpp"
#include "gs/GSrender.hpp"
#include "gs/scene/GScamera.hpp"

#include <revolution/gx/GXTransform.h>

#include "common.hpp"

void *operator new(unsigned long size);
void operator delete(void *ptr);

// TODO Replace with proper imports
extern "C" {
f32 fn_8000739C();
void fn_8023EB58(void *, void (*)(), void (*)(), s32, s32);
GScamera *fn_8003CE88(void *, s32);
void fn_80039090(void *, f32);
GScamera *fn_801DDF78(GScamera *camera);
void fn_80050808(eftseq::AnimNode<GScolor> *, GXColor *, GXColor *, GXColor *, s32);
void fn_80050E7C(eftseq::AnimNodeShake *, void *, f32 *, s32, s32, s32, f32, f32);
void fn_800510E8(eftseq::AnimNodeSpring *);
void fn_80051134(eftseq::AnimNodeSpring *, void *, f32 *, s32, s32, f32, f32, f32, f32, f32);
void fn_800507F0(eftseq::AnimNode<GScolor> *);
void fn_80050324(eftseq::AnimNode<f32> *);
void fn_8005033C(eftseq::AnimNode<f32> *, f32 *, f32 *, f32 *, u32, f32);
void fn_80050388(eftseq::AnimNode<f32> *);
void fn_80050E38(eftseq::AnimNodeShake *);
void *fn_802352BC(GSrender *render);
s32 fn_80242A00(Unk80242A00 *target, s32 mode);
void fn_80242A3C(Unk80242A00 *target, s32, s32, s32, f32 x, f32 y, f32 w, f32 h);
void fn_80242CD0(Unk80242A00 *target, f32 *, f32 *);
void fn_80243538(Unk80242A00 *target, s32, f32, f32, f32, f32, f32);
f32 PSVECMag(const Vec *v);
}

extern void *lbl_8063F778;
extern const f32 lbl_806407C8;
extern const f32 lbl_806407CC;
extern const f32 lbl_806407D0;
extern const f32 lbl_806407D4;
extern const f32 lbl_806407D8;
extern const f32 lbl_806407DC;
extern const f32 lbl_806407E0;
extern const f32 lbl_806407E4;
extern const f32 lbl_806407E8;
extern const f32 lbl_806407EC;
extern const f32 lbl_806407F0;
extern const f32 lbl_806407F4;
extern const f32 lbl_806407F8;
extern const f32 lbl_80640808;
extern const f32 lbl_8064080C;
extern const f32 lbl_80640810;

/* lbl_8063EA58 */ Unk80033090 *lbl_8063EA58;

// size: 0xC
struct Unk80496754 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ GScamera *_4;
    /* 0x8 */ u32 _8;
};

extern Unk80496754 lbl_80496754;

static inline void SetColor(Unk80033090 *p, u8 r, u8 g, u8 b, u8 a) {
    p->_1dc.r = r;
    p->_1dc.g = g;
    p->_1dc.b = b;
    p->_1dc.a = a;
}

static inline void SetF410_40e(u8 value) {
    if (lbl_8063F410->_418 != 0) {
        lbl_8063F410->_40e = value;
    } else {
        lbl_8063F410->_40e = 0;
    }
}

static inline void SetF410_450(f32 value) {
    lbl_8063F410->_450 = value;
}

static inline f32 Clamp01(f32 value) {
    if (value < lbl_806407E4) {
        value = lbl_806407E4;
    }
    if (value >= lbl_806407E8) {
        value = lbl_806407E8;
    }
    return value;
}

static inline GSvec3 MulVec(const Vec &a, const GSvec3 &b) {
    f32 z = a.z * b.z;
    f32 y = a.y * b.y;
    f32 x = a.x * b.x;
    return GSvec3(x, y, z);
}

static inline void SetCameraView(GScamera *camera, const Vec &dir) {
    GSvec3 target(lbl_806407E4, lbl_806407CC, lbl_806407E4);
    GSvec3 scale(lbl_806407E8, lbl_806407E8, lbl_806407EC);
    GSvec3 pos = MulVec(dir, scale);
    camera->_1ac.x = pos.x;
    camera->_1ac.y = pos.y;
    camera->_1ac.z = pos.z;
    camera->_1b8.x = GSmath::sYAxis.x;
    camera->_1b8.y = GSmath::sYAxis.y;
    camera->_1b8.z = GSmath::sYAxis.z;
    camera->_1c4.x = target.x;
    camera->_1c4.y = target.y;
    camera->_1c4.z = target.z;
    camera->_104 |= 0x30;
}

// TODO Sets the low bits of _104 to 1 and sets bit 3; inlined in fn_80033090.
static inline void fn_80033090Inline(GScamera *camera) {
    camera->_104 = (camera->_104 & ~3) | 1;
    camera->_104 |= 8;
}

// The original does not inline the functions between the dont_inline pragmas.
#pragma dont_inline on

// TODO Per-frame callback registered by fn_80033020; updates the viewport manager.
void fn_80032FE8() {
    if (lbl_8063EA58 != NULL) {
        f32 t = fn_8000739C();
        fn_800334A0(lbl_8063EA58, t);
    }
}

#pragma dont_inline reset

// TODO Empty; second callback registered by fn_80033020.
void fn_8003301C() {}

#pragma dont_inline on

// TODO Creates the viewport manager (replacing the previous one) and registers its callbacks.
void fn_80033020() {
    if (lbl_8063EA58 != NULL) {
        operator delete(lbl_8063EA58);
    }
    Unk80033090 *manager = (Unk80033090 *)operator new(sizeof(Unk80033090));
    if (manager != NULL) {
        manager = fn_80033090(manager);
    }
    lbl_8063EA58 = manager;
    fn_8023EB58(lbl_8063F778, fn_80032FE8, fn_8003301C, 3, 0xc);
    fn_80034918();
}

#pragma dont_inline reset

// TODO Viewport manager created by fn_80033020.
Unk80033090 *fn_80033088() {
    return lbl_8063EA58;
}

// TODO Initializes the viewport manager: two viewports, each with its scene camera.
Unk80033090 *fn_80033090(Unk80033090 *p) {
    Unk80035380 *view = p->_000;
    do {
        fn_80035380(view);
        view++;
    } while (view < p->_000 + 2);
    fn_80050E38(&p->_204);
    fn_80050E38(&p->_264);
    eftseq::AnimNode<f32> *tween = p->_2c4;
    do {
        fn_80050324(tween);
        tween++;
    } while (tween < p->_2c4 + 6);
    fn_800510E8(&p->_39c[0]);
    fn_800510E8(&p->_39c[1]);
    fn_800510E8(&p->_39c[2]);
    fn_80050324(&p->_5dc);
    fn_80050324(&p->_600);
    fn_80050324(&p->_624);
    fn_80050324(&p->_648);
    fn_80050324(&p->_66c);
    fn_800507F0(&p->_690);
    Vec dir;
    dir.x = lbl_806407C8;
    dir.y = lbl_806407CC;
    dir.z = lbl_806407D0;
    p->_1a5 = 0;
    Unk80040274 *cameras = fn_800401F4();
    if (cameras == NULL) {
        return p;
    }
    f32 aspect = lbl_806407D8;
    GScamera *camera = lbl_80496754._4;
    if ((camera->_104 & 3) == 1) {
        aspect = camera->_16c;
        camera->_168 = lbl_806407D4;
        camera->_17c = lbl_806407DC;
        camera->_180 = lbl_806407E0;
        fn_80033090Inline(camera);
    }
    SetCameraView(camera, dir);
    p->_000[0]._04 = camera;
    fn_80034918();
    fn_800353FC(&p->_000[0], fn_800402D4(cameras));
    p->_000[0]._01 = true;
    fn_80034918();
    GScamera *second;
    if (GSmem::isInitialized()) {
        second = (GScamera *)GSmem::allocFromHeap(gGameHeap, sizeof(GScamera));
    } else {
        second = NULL;
    }
    if (second != NULL) {
        second = fn_801DDF78(second);
    }
    second->_168 = lbl_806407D4;
    second->_16c = aspect;
    second->_17c = lbl_806407DC;
    second->_180 = lbl_806407E0;
    fn_80033090Inline(second);
    SetCameraView(second, dir);
    p->_000[1]._04 = second;
    fn_80034918();
    fn_800353FC(&p->_000[1], fn_800402D4(cameras));
    p->_000[1]._01 = false;
    fn_80034918();
    Unk80035380 *v = p->_000;
    for (s32 i = 0; i < 2; i++, v++) {
        fn_800354FC(v, lbl_806407E4, lbl_806407E4, lbl_806407E8, lbl_806407E8);
    }
    fn_800348BC(p, 0);
    p->_168 = 0;
    p->_16c = lbl_806407DC;
    p->_170 = 0;
    p->_174 = lbl_806407DC;
    p->_171 = 0;
    p->_178 = 0;
    p->_17c = 25;
    p->_180 = lbl_806407E4;
    p->_184 = lbl_806407E4;
    p->_188 = 0;
    p->_18c = lbl_806407E8;
    p->_190 = 0;
    p->_194 = 30;
    p->_198 = lbl_806407E4;
    p->_19c = lbl_806407E4;
    p->_1d0 = lbl_806407E4;
    p->_1d4 = lbl_806407E4;
    p->_1dc.r = 0xFF;
    p->_1dc.g = 0xFF;
    p->_1dc.b = 0xFF;
    p->_1dc.a = 0xFF;
    p->_1e4 = 1;
    p->_1e0 = 0;
    p->_1e8 = lbl_806407E4;
    p->_1ec = lbl_806407E4;
    p->_1f0 = lbl_806407E4;
    p->_1f4 = lbl_806407E8;
    p->_1f8 = lbl_806407E8;
    p->_1fc = lbl_806407E8;
    return p;
}

// TODO Enables the per-frame update.
void fn_80033488(Unk80033090 *p) {
    p->_1a5 = 1;
}

// TODO Disables the per-frame update.
void fn_80033494(Unk80033090 *p) {
    p->_1a5 = 0;
}

#pragma dont_inline on

// TODO Per-frame update: runs the animations, then sends the screen layout to render target 2.
void fn_800334A0(Unk80033090 *p, f32 t) {
    if (p->_1a5 == 0) {
        return;
    }
    if (p->_188 != 0) {
        GScamera *camera = fn_80035970(&p->_000[0]);
        Vec v;
        v.x = camera->_1c4.x;
        v.y = camera->_1c4.y;
        v.z = camera->_1c4.z;
        if (camera->_104 & 0x40) {
            PSVECSubtract(&v, &camera->_1ac, &v);
            PSVECScale(&v, &v, camera->_184 / PSVECMag(&v));
            PSVECAdd(&v, &camera->_1ac, &v);
        }
        f32 sx;
        f32 sy;
        f32 sz;
        f32 *viewport = (f32 *)fn_802352BC(GSrender::sInstance);
        GXProject(v.x, v.y, v.z, camera->_1d4, camera->_14c, viewport, &sx, &sy, &sz);
        lbl_8063F410->_444 = sz > lbl_806407E4 ? sz : -sz;
    }
    s32 changed = 0;
    for (s32 i = 0; i < 6; i++) {
        if (p->_2c4[i].fn_80050394(t)) {
            changed = 1;
        }
    }
    if (p->_204.fn_80050394(t)) {
        changed = 1;
    }
    if (p->_264.fn_80050394(t)) {
        changed = 1;
    }
    if (p->_39c[0].fn_80050394(t)) {
        changed = 1;
    }
    if (p->_39c[1].fn_80050394(t)) {
        changed = 1;
    }
    if (p->_39c[2].fn_80050394(t)) {
        changed = 1;
    }
    if (p->_690.fn_80050394(t)) {
        changed = 1;
    }
    if (changed) {
        switch ((u32)p->_200) {
            case 4: fn_800340D0(p, p->_1b8, p->_1bc, p->_1c0, p->_1c4); break;
            case 2: fn_80034170(p, p->_1cc); break;
            case 3: fn_80034280(p, p->_1c8); break;
            case 5: fn_80034918(); break;
            case 6: fn_80034918(); break;
            case 7: fn_80034918(); break;
            case 0:
            case 1: break;
        }
    }
    fn_80035828(&p->_000[0], t);
    fn_80035828(&p->_000[1], t);
    if (p->_5dc.fn_80050394(t)) {
        lbl_8063F410->_450 = p->_16c;
    }
    if (p->_600.fn_80050394(t)) {
        p->_194 = (s32)p->_1d8;
        fn_80035228(p);
    }
    s32 changed2 = 0;
    if (p->_648.fn_80050394(t)) {
        changed2 = 1;
    }
    if (p->_66c.fn_80050394(t)) {
        changed2 = 1;
    }
    if (p->_624.fn_80050394(t)) {
        changed2 = 1;
    }
    if (changed2) {
        fn_80034F48(p);
    }
    if (p->_1a4 == 0) {
        return;
    }
    if (((p->_000[0]._01 ? 1 : 0) | (p->_000[1]._01 ? 2 : 0)) == 0) {
        return;
    }
    Unk80242A00 *target = (Unk80242A00 *)GSrenderTarget::findTarget(2);
    if (target == NULL) {
        return;
    }
    switch (p->_1a0) {
        case 0: {
            GScamera *camera = fn_80035970(&p->_000[0]);
            target->_20 = 0;
            target->_c = (u32)camera;
            break;
        }
        case 1:
        case 2:
        case 3:
            fn_80242A00(target, 1);
            target->_24 = fn_80035970(&p->_000[0]);
            target->_39 = 1;
            target->_64 = fn_80035970(&p->_000[1]);
            target->_79 = 0;
            {
                f32 h = p->_000[0]._0c._0[3] - p->_000[0]._0c._0[1];
                f32 w = p->_000[0]._0c._0[2] - p->_000[0]._0c._0[0];
                fn_80242A3C(target, 0, 1, 1, p->_000[0]._0c._0[0], p->_000[0]._0c._0[1], w, h);
            }
            {
                f32 h = p->_000[1]._0c._0[3] - p->_000[1]._0c._0[1];
                f32 w = p->_000[1]._0c._0[2] - p->_000[1]._0c._0[0];
                fn_80242A3C(target, 1, 0, 1, p->_000[1]._0c._0[0], p->_000[1]._0c._0[1], w, h);
            }
            break;
        case 4:
            if (fn_80242A00(target, 2) == 0) {
                break;
            }
            target->_24 = fn_80035970(&p->_000[0]);
            target->_39 = 0;
            target->_64 = fn_80035970(&p->_000[1]);
            target->_79 = 0;
            fn_80242CD0(target, &p->_1a8, &p->_1b0);
            break;
        case 5:
            if (p->_1e0 == 0) {
                break;
            }
            fn_80242A00(target, 3);
            target->_24 = fn_80035970(&p->_000[0]);
            target->_39 = 0;
            target->_64 = fn_80035970(&p->_000[1]);
            target->_79 = 0;
            target->_a8 = p->_1e0;
            target->_c4.r = p->_1dc.r;
            target->_c4.g = p->_1dc.g;
            target->_c4.b = p->_1dc.b;
            target->_c4.a = p->_1dc.a;
            target->_ac = p->_1e8;
            target->_b0 = p->_1ec;
            target->_b4 = p->_1f0;
            target->_b8 = p->_1f4;
            target->_bc = p->_1f8;
            break;
        case 6:
            fn_80242A00(target, 4);
            switch (p->_1e4) {
                case 0: target->_c8 = 0; break;
                case 1:
                    fn_80243538(target, 0xc, lbl_806407F0, lbl_806407F4, lbl_806407DC, lbl_806407F8, lbl_806407DC);
                    break;
            }
            target->_24 = fn_80035970(&p->_000[0]);
            target->_39 = 0;
            target->_64 = fn_80035970(&p->_000[1]);
            target->_79 = 0;
            target->_c4.r = p->_1dc.r;
            target->_c4.g = p->_1dc.g;
            target->_c4.b = p->_1dc.b;
            target->_c4.a = p->_1dc.a;
            target->_ac = p->_1e8;
            target->_b0 = p->_1ec;
            target->_b4 = p->_1f0;
            target->_b8 = p->_1f4;
            target->_bc = p->_1f8;
            break;
        case 7:
            fn_80242A00(target, 5);
            target->_24 = fn_80035970(&p->_000[0]);
            target->_39 = 0;
            target->_64 = fn_80035970(&p->_000[1]);
            target->_79 = 0;
            target->_c4.r = p->_1dc.r;
            target->_c4.g = p->_1dc.g;
            target->_c4.b = p->_1dc.b;
            target->_c4.a = p->_1dc.a;
            target->_ac = p->_1e8;
            target->_b0 = p->_1ec;
            target->_b4 = p->_1f0;
            target->_c0 = p->_1fc;
            break;
    }
    p->_1a4 = 0;
}

// TODO Viewport i, NULL when out of range.
Unk80035380 *fn_80033B7C(Unk80033090 *p, u32 i) {
    if (i >= 2) {
        return NULL;
    }
    return &p->_000[i];
}

// TODO Index of the viewport using camera id, 0xFFFF when none does.
s32 fn_80033B98(Unk80033090 *p, u32 id) {
    for (u32 i = 0; i < 2; i++) {
        if (id == fn_800353F4(&p->_000[(u16)i])) {
            return i;
        }
    }
    return 0xFFFF;
}

// TODO Swaps the screen rectangles of the two viewports.
void fn_80033C0C(Unk80033090 *p) {
    Unk800354D8 rect = p->_000[0]._0c;
    fn_800354D8(&p->_000[0], &p->_000[1]._0c);
    fn_800354D8(&p->_000[1], &rect);
    fn_80034918();
}

#pragma dont_inline reset

// TODO Swaps the two viewports.
void fn_80033C6C(Unk80033090 *p) {
    // Storage for a viewport built by fn_80035380, which acts as its constructor.
    u32 buf[sizeof(Unk80035380) / sizeof(u32)];
    fn_80035380((Unk80035380 *)buf);
    *(Unk80035380 *)buf = p->_000[0];
    p->_000[0] = p->_000[1];
    p->_000[1] = *(Unk80035380 *)buf;
    fn_80034918();
}

#pragma dont_inline on

// TODO Window layout from a rectangle in pixels (layout 4).
void fn_800340D0(Unk80033090 *p, f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 w = GSrender::sInstance->mRenderMode.fbWidth;
    f32 h = GSrender::sInstance->mRenderMode.efbHeight;
    f32 a = x0 / w;
    p->_1a8 = a;
    f32 c = x1 / w;
    p->_1b0 = c;
    f32 b = y0 / h;
    p->_1ac = b;
    f32 d = y1 / h;
    p->_1b4 = d;
    if (a == c || b == d) {
        return;
    }
    p->_1b8 = x0;
    p->_1bc = y0;
    p->_1c0 = x1;
    p->_1c4 = y1;
    fn_800348BC(p, 4);
    fn_80034918();
}

// TODO Horizontal split at height v in pixels (layout 2).
void fn_80034170(Unk80033090 *p, f32 v) {
    f32 w = GSrender::sInstance->mRenderMode.fbWidth;
    f32 h = GSrender::sInstance->mRenderMode.efbHeight;
    if (v <= lbl_806407E4) {
        fn_800348BC(p, 0);
        fn_80033C6C(p);
    } else if (v >= h) {
        fn_800348BC(p, 0);
    } else {
        fn_800354FC(&p->_000[0], lbl_806407E4, lbl_806407E4, w, v + p->_1d4);
        fn_800354FC(&p->_000[1], lbl_806407E4, v + p->_1d4, w, h);
        p->_1cc = v;
        fn_800348BC(p, 2);
        fn_80034918();
    }
}

// TODO Vertical split at width v in pixels (layout 3).
void fn_80034280(Unk80033090 *p, f32 v) {
    f32 w = GSrender::sInstance->mRenderMode.fbWidth;
    f32 h = GSrender::sInstance->mRenderMode.efbHeight;
    if (v <= lbl_806407E4) {
        fn_800348BC(p, 0);
        fn_80033C6C(p);
    } else if (v >= w) {
        fn_800348BC(p, 0);
    } else {
        fn_800354FC(&p->_000[0], lbl_806407E4, lbl_806407E4, v + p->_1d0, h);
        fn_800354FC(&p->_000[1], v + p->_1d0, lbl_806407E4, w, h);
        p->_1c8 = v;
        fn_800348BC(p, 3);
        fn_80034918();
    }
}

// TODO Animates the window rectangle of layout 4 over x.
void fn_80034390(Unk80033090 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, s32 x) {
    f32 v[4];
    v[0] = x0;
    v[1] = y0;
    v[2] = x1;
    v[3] = y1;
    if (lbl_806407E4 == t) {
        fn_800340D0(p, v[0], v[1], v[2], v[3]);
    } else if (p->_1a0 == 4) {
        fn_800349B4(p);
        fn_8005033C(&p->_2c4[0], &p->_1b8, &v[0], &p->_1b8, x, t);
        fn_8005033C(&p->_2c4[1], &p->_1bc, &v[1], &p->_1bc, x, t);
        fn_8005033C(&p->_2c4[2], &p->_1c0, &v[2], &p->_1c0, x, t);
        fn_8005033C(&p->_2c4[3], &p->_1c4, &v[3], &p->_1c4, x, t);
        p->_200 = 4;
    }
}

// TODO Animates the horizontal split position over x.
void fn_80034494(Unk80033090 *p, f32 v, f32 t, s32 x) {
    f32 tmp = v;
    if (lbl_806407E4 == t) {
        fn_80034170(p, tmp);
    } else if (p->_1a0 == 2) {
        fn_800349B4(p);
        fn_8005033C(&p->_2c4[0], &p->_1cc, &tmp, &p->_1cc, x, t);
        p->_200 = 2;
    }
}

// TODO Animates the vertical split position over x.
void fn_8003452C(Unk80033090 *p, f32 v, f32 t, s32 x) {
    f32 tmp = v;
    if (lbl_806407E4 == t) {
        fn_80034280(p, tmp);
    } else if (p->_1a0 == 3) {
        fn_800349B4(p);
        fn_8005033C(&p->_2c4[0], &p->_1c8, &tmp, &p->_1c8, x, t);
        p->_200 = 3;
    }
}

// TODO Starts a shake of the horizontal split position.
void fn_800345C4(Unk80033090 *p, void *a, s32 b, f32 x, f32 y) {
    if (y <= lbl_806407E4) {
        p->_1d4 = lbl_806407E4;
    } else if (p->_1a0 == 2) {
        fn_80050E7C(&p->_264, a, &p->_1d4, b, 0, 0, x, y);
        p->_200 = 2;
    }
}

// TODO Starts a shake of the vertical split position.
void fn_80034630(Unk80033090 *p, void *a, s32 b, f32 x, f32 y) {
    if (y <= lbl_806407E4) {
        p->_1d0 = lbl_806407E4;
    } else if (p->_1a0 == 3) {
        fn_80050E7C(&p->_204, a, &p->_1d0, b, 0, 0, x, y);
        p->_200 = 3;
    }
}

// TODO Starts a spring animation of the horizontal split position.
void fn_8003469C(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (p->_1a0 != 2) {
        return;
    }
    fn_800349B4(p);
    if (GSrender::sInstance->mVideoFmt == VID_FMT_PAL && lbl_80640808 == f3) {
        f3 = lbl_806407DC;
    }
    fn_80051134(&p->_39c[1], a, &p->_1cc, b, 1, f1, f4, f5, f3, f2);
    p->_200 = 2;
}

// TODO Starts a spring animation of the vertical split position.
void fn_800347BC(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (p->_1a0 != 3) {
        return;
    }
    fn_800349B4(p);
    fn_80051134(&p->_39c[0], a, &p->_1c8, b, 1, f1, f4, f5, f3, f2);
    p->_200 = 3;
}

// TODO Sets the screen layout, from 0 to 7.
void fn_800348BC(Unk80033090 *p, s32 mode) {
    switch (mode) {
        case 0:  fn_80034918(); break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:  break;
        default: return;
    }
    p->_1a0 = mode;
}

// TODO Marks the screen layout as changed.
void fn_80034918() {
    Unk80033090 *p = lbl_8063EA58;
    if (p != NULL) {
        p->_1a4 = 1;
    }
}

// TODO Whether one of the layout animations is running.
s32 fn_80034930(Unk80033090 *p) {
    for (s32 i = 0; i < 6; i++) {
        if (p->_2c4[i]._00 != 0) {
            return 1;
        }
    }
    return 0;
}

// TODO Stops the layout animations.
void fn_800349B4(Unk80033090 *p) {
    for (s32 i = 0; i < 6; i++) {
        fn_80050388(&p->_2c4[i]);
    }
}

// TODO Resets the color and the values used by layouts 5 to 7.
void fn_80034A00(Unk80033090 *p) {
    p->_1dc.r = 0xFF;
    p->_1dc.g = 0xFF;
    p->_1dc.b = 0xFF;
    p->_1dc.a = 0xFF;
    p->_1e8 = lbl_806407E4;
    p->_1ec = lbl_806407E4;
    p->_1f0 = lbl_806407E4;
    p->_1f4 = lbl_806407E8;
    p->_1f8 = lbl_806407E8;
    p->_1fc = lbl_806407E8;
    fn_800349B4(p);
}

// TODO Switches to layout 6 with variant v.
void fn_80034A38(Unk80033090 *p, s32 v) {
    if (p->_1a0 != 6) {
        fn_800348BC(p, 6);
        fn_80034A00(p);
    }
    switch (v) {
        case 0: p->_1e4 = 0; break;
        case 1: p->_1e4 = 1; break;
    }
    fn_80034918();
}

// TODO Switches to layout 7 with value v.
void fn_80034AB8(Unk80033090 *p, f32 v) {
    if (p->_1a0 != 7) {
        fn_800348BC(p, 7);
        fn_80034A00(p);
    }
    p->_1fc = v;
    fn_80034918();
}

#pragma dont_inline reset

// TODO Sets the color used by layouts 5 to 7.
void fn_80034B10(Unk80033090 *p, GXColor *color) {
    SetColor(p, color->r, color->g, color->b, color->a);
    fn_80034918();
}

#pragma dont_inline on

// TODO Sets _1e8 and _1ec.
void fn_80034B34(Unk80033090 *p, f32 a, f32 b) {
    p->_1e8 = a;
    p->_1ec = b;
    fn_80034918();
}

// TODO Sets _1f0.
void fn_80034B40(Unk80033090 *p, f32 a) {
    p->_1f0 = a;
    fn_80034918();
}

// TODO Sets _1f4 and _1f8.
void fn_80034B48(Unk80033090 *p, f32 a, f32 b) {
    p->_1f4 = a;
    p->_1f8 = b;
    fn_80034918();
}

// TODO Animates the color towards target over x and sets the update mode.
void fn_80034B54(Unk80033090 *p, s32 mode, GXColor *target, s32 x) {
    fn_80050808(&p->_690, &p->_1dc, target, &p->_1dc, x);
    p->_200 = mode;
}

// TODO Animates _1e8 and _1ec over x.
void fn_80034BA0(Unk80033090 *p, f32 a, f32 b, s32 mode, s32 x, f32 t) {
    f32 v[2];
    v[0] = a;
    v[1] = b;
    fn_8005033C(&p->_2c4[0], &p->_1e8, &v[0], &p->_1e8, x, t);
    fn_8005033C(&p->_2c4[1], &p->_1ec, &v[1], &p->_1ec, x, t);
    p->_200 = mode;
}

// TODO Animates _1f0 over x.
void fn_80034C30(Unk80033090 *p, f32 a, s32 mode, s32 x, f32 t) {
    f32 v = a;
    fn_8005033C(&p->_2c4[2], &p->_1f0, &v, &p->_1f0, x, t);
    p->_200 = mode;
}

// TODO Animates _1f4 and _1f8 over x.
void fn_80034C88(Unk80033090 *p, f32 a, f32 b, s32 mode, s32 x, f32 t) {
    f32 v[2];
    v[0] = a;
    v[1] = b;
    fn_8005033C(&p->_2c4[3], &p->_1f4, &v[0], &p->_1f4, x, t);
    fn_8005033C(&p->_2c4[4], &p->_1f8, &v[1], &p->_1f8, x, t);
    p->_200 = mode;
}

// TODO Animates _1fc over x.
void fn_80034D18(Unk80033090 *p, f32 a, s32 x, f32 t) {
    f32 v = a;
    fn_8005033C(&p->_2c4[5], &p->_1fc, &v, &p->_1fc, x, t);
    p->_200 = 7;
}

// TODO Starts a spring animation of _1fc.
void fn_80034D68(Unk80033090 *p, void *a, s32 b, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5) {
    if (lbl_806407E4 == f4 || lbl_806407E4 == f5) {
        return;
    }
    if (p->_1a0 != 7) {
        return;
    }
    fn_800349B4(p);
    fn_80051134(&p->_39c[2], a, &p->_1fc, b, 1, f1, f4, f5, f3, f2);
    p->_200 = 7;
}

#pragma dont_inline reset

// TODO Sets _168 and forwards it to the global render settings.
void fn_80034E68(Unk80033090 *p, u8 v) {
    p->_168 = v;
    SetF410_40e(v);
    SetF410_450(p->_16c);
}

// TODO Sets _16c, clamped, and forwards it to the global render settings.
void fn_80034EA0(Unk80033090 *p, f32 v) {
    f32 c = Clamp01(v);
    p->_16c = c;
    SetF410_450(c);
    fn_80050388(&p->_5dc);
}

#pragma dont_inline on

// TODO Animates _16c over x.
void fn_80034EDC(Unk80033090 *p, f32 v, s32 x, f32 t) {
    f32 tmp = v;
    if (tmp < lbl_806407E4) {
        tmp = lbl_806407E4;
    }
    if (tmp >= lbl_806407E8) {
        tmp = lbl_806407E8;
    }
    fn_8005033C(&p->_5dc, &p->_16c, &tmp, &p->_16c, x, t);
}

// TODO Forwards _170 to _184 to the global render settings.
void fn_80034F48(Unk80033090 *p) {
    if (lbl_8063F410 == NULL) {
        return;
    }
    lbl_8063F410->_40d = p->_170;
    lbl_8063F410->_42c = p->_174;
    lbl_8063F410->_430 = p->_171;
    lbl_8063F410->_434 = p->_178;
    lbl_8063F410->_431 = p->_17c;
    Unk8063F410 *g = lbl_8063F410;
    g->_424.x = p->_180;
    g->_424.y = p->_184;
}

// TODO Sets _170.
void fn_80034FA4(Unk80033090 *p, u8 v) {
    p->_170 = v;
    fn_80034F48(p);
}

// TODO Sets _174, clamped.
void fn_80034FAC(Unk80033090 *p, f32 v) {
    if (v < lbl_806407E4) {
        v = lbl_806407E4;
    }
    if (v >= lbl_806407E8) {
        v = lbl_806407E8;
    }
    p->_174 = v;
    fn_80050388(&p->_624);
    fn_80034F48(p);
}

// TODO Animates _174 over x.
void fn_8003500C(Unk80033090 *p, f32 v, s32 x, f32 t) {
    f32 tmp = v;
    if (tmp < lbl_806407E4) {
        tmp = lbl_806407E4;
    }
    if (tmp >= lbl_806407E8) {
        tmp = lbl_806407E8;
    }
    fn_8005033C(&p->_624, &p->_174, &tmp, &p->_174, x, t);
}

// TODO Sets _171.
void fn_80035078(Unk80033090 *p, u8 v) {
    p->_171 = v;
    fn_80034F48(p);
}

// TODO Sets _178 to 0 or 1.
void fn_80035080(Unk80033090 *p, s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (v > 1) {
        v = 1;
    }
    p->_178 = v;
    fn_80034F48(p);
}

// TODO Sets _17c, at most 100.
void fn_800350A0(Unk80033090 *p, u32 v) {
    if (v > 100) {
        v = 100;
    }
    p->_17c = v;
    fn_80034F48(p);
}

// TODO Sets _180 and _184, clamped.
void fn_800350B4(Unk80033090 *p, f32 x, f32 y) {
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
    p->_180 = x;
    p->_184 = y;
    fn_80050388(&p->_648);
    fn_80050388(&p->_66c);
    Unk8063F410 *g = lbl_8063F410;
    g->_424.x = p->_180;
    g->_424.y = p->_184;
}

// TODO Animates _180 and _184 over x.
void fn_80035148(Unk80033090 *p, f32 v0, f32 v1, s32 x, f32 t) {
    f32 b;
    f32 a;
    a = v0;
    b = v1;
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
    fn_8005033C(&p->_648, &p->_180, &a, &p->_180, x, t);
    fn_8005033C(&p->_66c, &p->_184, &b, &p->_184, x, t);
}

// TODO Forwards _188 to _19c to the global render settings.
void fn_80035228(Unk80033090 *p) {
    if (lbl_8063F410 == NULL) {
        return;
    }
    lbl_8063F410->_40f = p->_188;
    lbl_8063F410->_440 = p->_18c;
    lbl_8063F410->_44c = p->_190;
    lbl_8063F410->_448 = p->_194;
    Unk8063F410 *g = lbl_8063F410;
    g->_438 = p->_198;
    g->_43c = p->_19c;
}

// TODO Sets _188.
void fn_80035278(Unk80033090 *p, u8 v) {
    p->_188 = v;
    fn_80035228(p);
}

// TODO Sets _18c, clamped.
void fn_80035280(Unk80033090 *p, f32 v) {
    if (v < lbl_806407E4) {
        v = lbl_806407E4;
    }
    if (v >= lbl_806407E8) {
        v = lbl_806407E8;
    }
    p->_18c = v;
    fn_80035228(p);
}

// TODO Sets _190 to 0 or 1.
void fn_800352AC(Unk80033090 *p, s32 v) {
    if (v < 0) {
        v = 0;
    }
    if (v > 1) {
        v = 1;
    }
    p->_190 = v;
    fn_80035228(p);
}

// TODO Sets _194, at most 100.
void fn_800352CC(Unk80033090 *p, u32 v) {
    if (v > 100) {
        v = 100;
    }
    p->_194 = v;
    fn_80035228(p);
}

// TODO Animates _194 over x.
void fn_800352E0(Unk80033090 *p, u32 v, s32 x, f32 t) {
    if (v > 100) {
        v = 100;
    }
    f32 cur;
    f32 target = v;
    cur = p->_194;
    fn_8005033C(&p->_600, &cur, &target, &p->_1d8, x, t);
}

// TODO Clamps a coordinate to the screen.
void fn_80035354(f32 *v) {
    if (*v < lbl_806407E4) {
        *v = lbl_806407E4;
    } else if (*v > lbl_806407E8) {
        *v = lbl_806407E8;
    }
}

// TODO Initializes a viewport.
Unk80035380 *fn_80035380(Unk80035380 *p) {
    eftseq::AnimNode<f32> *tween = p->_1c;
    do {
        fn_80050324(tween);
        tween++;
    } while (tween < p->_1c + 4);
    p->_00 = 0;
    p->_02 = 0;
    p->_04 = NULL;
    p->_08 = 0;
    p->_ac = NULL;
    p->_b0 = NULL;
    return p;
}

#pragma dont_inline reset

// TODO Camera id of the viewport.
u32 fn_800353F4(Unk80035380 *p) {
    return p->_08;
}

#pragma dont_inline on

// TODO Binds the viewport camera to battle camera id.
void fn_800353FC(Unk80035380 *p, u32 id) {
    Unk80040274 *cameras = fn_800401F4();
    if (cameras != NULL) {
        Unk80040EA4 *camera = fn_80040384(cameras, p->_08);
        if (camera != NULL) {
            camera->_6cc = NULL;
        }
        camera = fn_80040384(cameras, id);
        if (camera != NULL) {
            camera->_6cc = p->_04;
            GScamera *scene = p->_04;
            camera->_4e0 = (scene->_104 & 3) == 1 ? scene->_168 : lbl_806407E4;
            fn_80050388(&camera->_004[0]);
            camera->_001 = 1;
            fn_800410AC(camera, &p->_04->_1ac);
            fn_80042534(camera, &p->_04->_1c4);
        }
    }
    p->_08 = id;
}

#pragma dont_inline reset

// TODO Sets the screen rectangle of the viewport.
void fn_800354D8(Unk80035380 *p, Unk800354D8 *rect) {
    p->_0c = *rect;
    fn_80034918();
}

#pragma dont_inline on

// TODO Sets the screen rectangle of the viewport from pixels.
void fn_800354FC(Unk80035380 *p, f32 x0, f32 y0, f32 x1, f32 y1) {
    f32 dx = x0 - x1;
    f32 dy;
    if ((dx < lbl_8064080C && dx > lbl_80640810) || ((dy = y0 - y1) < lbl_8064080C && dy > lbl_80640810)) {
        return;
    }
    f32 w = GSrender::sInstance->mRenderMode.fbWidth;
    f32 h = GSrender::sInstance->mRenderMode.efbHeight;
    if (x0 < x1) {
        p->_0c._0[0] = x0 / w;
        p->_0c._0[2] = x1 / w;
    } else {
        p->_0c._0[2] = x0 / w;
        p->_0c._0[0] = x1 / w;
    }
    if (y0 < y1) {
        p->_0c._0[1] = y0 / h;
        p->_0c._0[3] = y1 / h;
    } else {
        p->_0c._0[3] = y0 / h;
        p->_0c._0[1] = y1 / h;
    }
    fn_80035354(&p->_0c._0[2]);
    fn_80035354(&p->_0c._0[0]);
    fn_80035354(&p->_0c._0[1]);
    fn_80035354(&p->_0c._0[3]);
    if (fn_80033088() != NULL) {
        fn_800348BC(fn_80033088(), 1);
    }
    fn_80034918();
}

// TODO Makes the viewport cover the whole screen.
void fn_80035628(Unk80035380 *p) {
    f32 h = GSrender::sInstance->mRenderMode.efbHeight;
    f32 w = GSrender::sInstance->mRenderMode.fbWidth;
    fn_800354FC(p, lbl_806407E4, lbl_806407E4, w, h);
    fn_800348BC(fn_80033088(), 0);
}

// TODO Animates the screen rectangle of the viewport over x.
void fn_80035690(Unk80035380 *p, f32 x0, f32 y0, f32 x1, f32 y1, f32 t, s32 x) {
    f32 v[4];
    v[0] = x0;
    v[1] = y0;
    v[2] = x1;
    v[3] = y1;
    if (lbl_806407E4 == t) {
        fn_800354FC(p, v[0], v[1], v[2], v[3]);
    } else {
        f32 w = GSrender::sInstance->mRenderMode.fbWidth;
        f32 h = GSrender::sInstance->mRenderMode.efbHeight;
        v[0] /= w;
        fn_80035354(&v[0]);
        v[2] /= w;
        fn_80035354(&v[2]);
        v[1] /= h;
        fn_80035354(&v[1]);
        v[3] /= h;
        fn_80035354(&v[3]);
        fn_800358C8(p);
        fn_8005033C(&p->_1c[0], &p->_0c._0[0], &v[0], &p->_0c._0[0], x, t);
        fn_8005033C(&p->_1c[1], &p->_0c._0[1], &v[1], &p->_0c._0[1], x, t);
        fn_8005033C(&p->_1c[2], &p->_0c._0[2], &v[2], &p->_0c._0[2], x, t);
        fn_8005033C(&p->_1c[3], &p->_0c._0[3], &v[3], &p->_0c._0[3], x, t);
    }
}

// TODO Runs the rectangle animations of the viewport.
void fn_80035828(Unk80035380 *p, f32 t) {
    s32 changed = 0;
    for (s32 i = 0; i < 4; i++) {
        if (p->_1c[i].fn_80050394(t)) {
            changed = 1;
        }
    }
    if (changed) {
        fn_800354D8(p, &p->_0c);
    }
}

// TODO Stops the rectangle animations of the viewport.
void fn_800358C8(Unk80035380 *p) {
    for (s32 i = 0; i < 4; i++) {
        fn_80050388(&p->_1c[i]);
    }
}

// TODO Whether one of the rectangle animations of the viewport is running.
s32 fn_80035914(Unk80035380 *p) {
    for (s32 i = 0; i < 4; i++) {
        if (p->_1c[i]._00 != 0) {
            return 1;
        }
    }
    return 0;
}

#pragma dont_inline reset

// TODO Camera the viewport renders with: the one of its attached object, else its own.
GScamera *fn_80035970(Unk80035380 *p) {
    if (p->_02 != 0) {
        if (p->_ac != NULL) {
            GScamera *camera = fn_8003CE88(p->_ac, 0);
            if (camera != NULL) {
                return camera;
            }
        } else {
            GSobject *object = p->_b0;
            if (object != NULL) {
                GScamera *camera = object->getCamera(0);
                if (camera != NULL) {
                    return camera;
                }
            }
        }
    }
    return p->_04;
}

// TODO Attaches an object handle to the viewport.
void fn_80035A40(Unk80035380 *p, void *v) {
    p->_ac = v;
}

// TODO Attaches a scene object to the viewport.
void fn_80035A48(Unk80035380 *p, GSobject *v) {
    p->_b0 = v;
}

#pragma dont_inline on

// TODO Uses the attached object's camera from now on.
void fn_80035A50(Unk80035380 *p) {
    if (p->_ac != NULL) {
        fn_80039090(p->_ac, lbl_806407E4);
        fn_80034918();
        p->_02 = 1;
    } else if (p->_b0 != NULL) {
        fn_80034918();
        p->_02 = 1;
    }
}

#pragma dont_inline reset

// TODO Copies the attached object's camera into the viewport camera and its battle camera.
void fn_80035AB8(Unk80035380 *p) {
    if (p->_02 == 0) {
        return;
    }
    GScamera *camera;
    if (p->_ac != NULL) {
        camera = fn_8003CE88(p->_ac, 0);
        p->_ac = NULL;
    } else if (p->_b0 != NULL) {
        camera = p->_b0->getCamera(0);
        p->_b0 = NULL;
    }
    if (camera != NULL) {
        Vec pos;
        pos.x = camera->getLocalTranslation().x;
        pos.y = camera->getLocalTranslation().y;
        pos.z = camera->getLocalTranslation().z;
        f32 ratio;
        if ((camera->_104 & 3) == 1) {
            ratio = camera->_16c;
        } else {
            f32 w = __fabs(camera->_16c - camera->_168);
            f32 h = __fabs(camera->_174 - camera->_170);
            ratio = h / w;
        }
        GScamera *own = p->_04;
        if ((own->_104 & 3) == 1) {
            own->_16c = ratio;
            own->_104 |= 8;
        }
        Unk80040274 *cameras = fn_800401F4();
        if (cameras != NULL) {
            Unk80040EA4 *entry = fn_80040384(cameras, p->_08);
            if (entry != NULL) {
                entry->_4e0 = (camera->_104 & 3) == 1 ? camera->_168 : lbl_806407E4;
                fn_80050388(&entry->_004[0]);
                entry->_001 = 1;
                fn_800410AC(entry, &camera->_1ac);
                fn_80042534(entry, &camera->_1c4);
            }
        }
    }
    p->_02 = 0;
    fn_80034918();
}
