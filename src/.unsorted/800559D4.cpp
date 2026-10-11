#include "ds/pokemon.hpp"
#include "common.hpp"

void fn_8005C9C8();

void fn_80055D94() {
    fn_8005C9C8();
}

#include "common.hpp"

extern "C" {

void fn_800E43D0();

void fn_80056978(void) {}
void fn_80057558(void) {}
void fn_800576AC(void) { fn_800E43D0(); }

}

#include "common.hpp"

extern "C" {

extern u8 *lbl_8063D4A0;

u32 fn_8005755C(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 3) & 0x1; }
u32 fn_8005756C(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 23) & 0x1; }
u32 fn_8005769C(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 26) & 0x1; }
u32 fn_80058480(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 10) & 0x1; }
u32 fn_80058490(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 9) & 0x1; }
u32 fn_800584A0(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 8) & 0x1; }
u32 fn_800584B0(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 7) & 0x1; }
u32 fn_8005923C(void) { return (*(u32 *)(lbl_8063D4A0 + 0x8) >> 2) & 0x1; }

}

#include "gs/GSmem.hpp"
#include "gs/GSthread.hpp"

struct Bits32 {
    u32 b31 : 1;
    u32 b30 : 1;
    u32 b29 : 1;
    u32 b28 : 1;
    u32 b27 : 1;
    u32 b26 : 1;
    u32 b25 : 1;
    u32 b24 : 1;
    u32 b23 : 1;
    u32 b22 : 1;
    u32 b21 : 1;
    u32 b20 : 1;
    u32 b19 : 1;
    u32 b18 : 1;
    u32 b17 : 1;
    u32 b16 : 1;
    u32 b15 : 1;
    u32 b14 : 1;
    u32 b13 : 1;
    u32 b12 : 1;
    u32 b11 : 1;
    u32 b10 : 1;
    u32 b9 : 1;
    u32 b8 : 1;
    u32 b7 : 1;
    u32 b6 : 1;
    u32 b5 : 1;
    u32 b4 : 1;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
};

struct ArenaCtx {
    /* 0x0000 */ u8 _0[0x8];
    /* 0x0008 */ Bits32 flags;
    /* 0x000C */ Bits32 flags2;
    /* 0x0010 */ u8 _10[0x3C - 0x10];
    /* 0x003C */ u16 names[64][32];
    /* 0x103C */ u16 _103C;
    /* 0x103E */ u8 _103E[6];
    /* 0x1044 */ s16 _1044;
    /* 0x1046 */ u8 _1046[0x1058 - 0x1046];
    /* 0x1058 */ u32 _1058;
    /* 0x105C */ u8 _105C[0x107C - 0x105C];
    /* 0x107C */ u32 _107C;
    /* 0x1080 */ u8 _1080;
    /* 0x1081 */ u8 _1081;
    /* 0x1082 */ u8 _1082[2];
    /* 0x1084 */ u32 _1084;
};

#define ACTX ((ArenaCtx *)lbl_8063D4A0)

extern "C" {

void fn_80253DB0(s16, int, int);
u16 fn_80253DD0(s16);
u16 fn_80253DE0(s16);
int fn_80253E8C(s16, int, int, void *);
void fn_8015C4F4(u8, u32);
u8 *fn_8015F690(void);
double fn_8015F7A0(void);
void fn_8015F758(double);
f32 fn_80055E3C(void);
int fn_80056F68(void *, int);
void *fn_80059288(void *);
extern u16 lbl_8040B088[];

void *fn_80055E1C(u32 size) { return GSmem::allocFromHeap(gUnkHeap2, (size + 0x1f) & ~0x1f); }
void fn_80055E30(void *p) { GSmem::freeToHeap(gUnkHeap2, p); }
void fn_80055EB4(int x) __attribute__((never_inline));
void fn_80055EB4(int x) { ACTX->flags.b31 = x; }
void fn_80055EC8(void) { ACTX->flags.b28 = 1; }
void fn_800562BC(void) { fn_80253DB0(ACTX->_1044, 0, 0); }
void fn_800562D0(void) { fn_80253DB0(ACTX->_1044, 5, 0); }
void fn_800562E4(void) { fn_80253DB0(ACTX->_1044, 4, 0); }
void fn_80056330(void) { fn_80253DB0(ACTX->_1044, 1, 0); }
void fn_80056344(void) { fn_80253DB0(ACTX->_1044, 3, 0); }
void fn_800563CC(int x) { ACTX->flags.b6 = x; }
void fn_800563E0(u8 x) { ACTX->_1081 = x; }
void fn_800564AC(u32 x) { ACTX->_1084 = x; }
void fn_800564B8(u8 a, u32 b) { ACTX->_1080 = a; ACTX->_107C = b; }
void fn_80057688(void) { ACTX->flags.b26 = 1; }
void fn_800583A4(void) { ACTX->flags.b9 = 1; }
void fn_800583B8(void) { ACTX->flags.b9 = 0; }
void fn_800583CC(void) { ACTX->flags.b10 = 0; }
void fn_800583E0(void) { ACTX->flags.b7 = 1; }
void fn_800583F4(void) { ACTX->flags.b7 = 0; }
void fn_80058408(void) { ACTX->flags.b8 = 0; }
void fn_800584C0(void) { ACTX->flags.b4 = 1; }
void fn_800584D4(void) { ACTX->flags.b4 = 0; }
u32 fn_8005924C(void) { return ACTX->flags.b0; }
void fn_8005650C(void) __attribute__((never_inline));
void fn_8005650C(void) { u32 v = ACTX->_1084; if (v) fn_8015C4F4(9, v); }
void fn_80056528(void) { u32 w = *(u32 *)&ACTX->flags2; w |= 0x40000000; *(u32 *)&ACTX->flags2 = w; ACTX->flags2.b31 = w >> 30; }
u8 fn_80058BA4(void) { return *(u32 *)(fn_8015F690() + 0x48); }
int fn_8005694C(int a, int b) { u32 tmp; return fn_80253E8C(a, b, 3, &tmp); }
void fn_8005925C(int x) { ACTX->flags.b1 = x; if (!x) ACTX->flags.b0 = 0; }
u16 fn_80058BCC(u32 x) { if (x >= 1 && x <= 12) { u32 i = x - 1; return lbl_8040B088[i]; } return 0; }
void fn_80056F34(int a, int b) { fn_80056F68(Pokemon_GetBoxPokemon((Pokemon *)a), b); }
GSthreadHandle *fn_80059208(void) { ACTX->flags.b2 = 0; return GSthreadManager::sInstance->createThread(200, fn_80059288, 0, 0x2000, 8, 1); }
void fn_800561B0(void) { double a = fn_8015F7A0(); fn_8015F758(a + fn_80055E3C()); }
BOOL fn_800562F8(void) { return fn_80253DD0(ACTX->_1044) == 3; }
void fn_800564CC(void) { if (ACTX->_107C) { fn_8015C4F4(ACTX->_1080, ACTX->_107C); ACTX->_107C = 0; } }
void fn_80056230(void) { if (fn_80253DE0(ACTX->_1044)) fn_80253DB0(ACTX->_1044, 0, 0); }

}

// Batch 2
#include "gs/GSfsys.hpp"
#include "gs/GScache.hpp"

struct ArenaCtxF {
    u8 _0[0x1088];
    /* 0x1088 */ f32 _1088;
    /* 0x108C */ f32 _108C;
    /* 0x1090 */ f32 _1090;
    /* 0x1094 */ f32 _1094;
};
#define ACTXF ((ArenaCtxF *)lbl_8063D4A0)

extern "C" {

extern u32 lbl_803FB880[][5];
extern const f32 lbl_80640B70;
extern f32 lbl_8063D988;
extern const f32 lbl_80640B6C;
u8 *fn_8011C974(void);
void fn_8000B570(int);
int fn_80056BD4(void *);
int fn_80056C4C(void *);
int GetMonDataInternal(void *, int, int);

void fn_800561E8(void) { if (fn_80253DE0(ACTX->_1044) != 2) fn_80253DB0(ACTX->_1044, 2, 0); }
void fn_80056274(void) { if (fn_80253DE0(ACTX->_1044) != 2) fn_80253DB0(ACTX->_1044, 2, 0); }
bool fn_8005983C(int i) { return GSfsys::loadFsys(lbl_803FB880[i][fn_80058BA4()]); }
BOOL fn_80058610(void) { if (*(u16 *)(fn_8011C974() + 0x94) == 0) return 0; return ACTXF->_1088 >= ACTXF->_108C; }
BOOL fn_80058660(void) { if (*(u16 *)(fn_8011C974() + 0x92) == 0) return 0; return ACTXF->_1090 >= ACTXF->_1094; }
void fn_80056458(int x) { if (x) fn_8000B570(lbl_80640B6C + lbl_80640B70 * lbl_8063D988); else fn_8000B570(0); }
void fn_80059884(int i) { u32 *row = lbl_803FB880[i]; GScache::freeFsysCacheEntries(row[fn_80058BA4()]); GSfsys::fn_80249890(row[fn_80058BA4()]); }
BOOL fn_80056E2C(void *p) { if (!fn_80056BD4(p)) return 0; if (BoxPokemon_GetValue((BoxPokemon *)p, 0xac, NULL)) return 1; return 0; }
BOOL fn_80056E84(void *p) { if (fn_80056C4C(p) == 0) return 0; return (u32)GetMonDataInternal(p, 0xac, 0) != 0; }
BOOL fn_80056EDC(void *p) { if (!fn_80056BD4(p)) return 0; if (BoxPokemon_GetValue((BoxPokemon *)p, 3, NULL)) return 1; return 0; }

}

// Batch 3
extern "C" {

extern const f32 lbl_80640B68;
void fn_8000B170(void *, f32, int);
int fn_8000708C(void);
int fn_8000B4C0(void *);
u32 fn_80164BA8(void);
int fn_80164D78(void);
int fn_80164DA8(void);

void fn_8005841C(void) {
    ACTX->flags.b10 = 0;
    ACTX->flags.b9 = 0;
    ACTX->flags.b8 = 0;
    ACTX->flags.b7 = 0;
    ACTX->flags.b5 = 0;
    ACTX->flags.b4 = 0;
}
int fn_800586B0(void) {
    if (*(u16 *)(fn_8011C974() + 0x94) == 0) return 0;
    if (ACTXF->_1088 >= ACTXF->_108C) return 0;
    return ACTXF->_108C - ACTXF->_1088;
}
int fn_80058714(void) {
    if (*(u16 *)(fn_8011C974() + 0x92) == 0) return 0;
    if (ACTXF->_1090 >= ACTXF->_1094) return 0;
    return ACTXF->_1094 - ACTXF->_1090;
}
void fn_800563EC(void *p, int x) {
    if (x) {
        fn_8000B170(p, lbl_80640B68, 0);
    } else if (fn_8000708C() && !fn_8000B4C0(p)) {
        fn_8000B170(p, lbl_80640B68, 0);
    }
}
void fn_80058E34(u16 *p) {
    int i;
    if (p[2] == 0xffff && p[3] == 0x13) {
        for (i = 0; i < 10; i++) {
            p[2 + i] = p[4 + i];
        }
    }
}
void fn_8005654C(void) {
    if (ACTX->flags.b22) {
        ACTX->_1058 = fn_80164BA8();
    }
    if (ACTX->flags.b19) {
        if (!fn_80164D78() && fn_80164DA8() == 1) {
            ACTX->flags.b19 = 0;
        }
    }
}

}

// Batch 4
#include "gs/GSrender.hpp"

struct Bits32Q {
    u32 _hi : 13;
    u32 q15 : 4;
    u32 _lo : 15;
};

extern "C" {

void fn_80177080(u16 *, u16 *, int);
void fn_80253EB4(s16, int, int, int);
int fn_801E07E8(void);
int fn_80007084(void);
extern const f32 lbl_80640B60;
extern const f32 lbl_80640B64;

u16 *fn_8005697C(void *p) {
    u16 buf[32];
    BoxPokemon_GetValue((BoxPokemon *)p, 0x74, buf);
    fn_80177080(ACTX->names[ACTX->_103C & 0x3f], buf, 0x20);
    ACTX->_103C++;
    return ACTX->names[(ACTX->_103C - 1) & 0x3f];
}
u16 *fn_800569EC(void *p) {
    u16 buf[32];
    GetMonDataInternal(p, 0x74, (int)buf);
    fn_80177080(ACTX->names[ACTX->_103C & 0x3f], buf, 0x20);
    ACTX->_103C++;
    return ACTX->names[(ACTX->_103C - 1) & 0x3f];
}
void fn_80056358(int a, int b, int c, int d, int e) {
    u32 w;
    ACTX->flags.b22 = a;
    ACTX->flags.b21 = b;
    ACTX->flags.b20 = c;
    ((Bits32Q *)&ACTX->flags)->q15 = d;
    ACTX->flags.b19 = e;
    w = *(u32 *)&ACTX->flags2;
    w &= ~0x40000000;
    *(u32 *)&ACTX->flags2 = w;
    ACTX->flags2.b31 = w >> 30;
}
void fn_800565BC(s16 a, int b) {
    int tmp;
    fn_80253E8C(a, b, 3, &tmp);
    switch (tmp) {
    case 2:
        if (!ACTX->flags.b20) {
            fn_80253EB4(a, b, 1, 0);
        }
        break;
    }
}
f32 fn_80055E3C(void) {
    if (fn_801E07E8()) return lbl_80640B60;
    if (fn_80007084()) return lbl_80640B60;
    if (*((u8 *)GSrender::sInstance + 0x82)) return lbl_80640B60;
    return *(u64 *)ACTX / lbl_80640B64 / lbl_80640B64;
}
int fn_80056BD4(void *p) {
    u16 v;
    if (p == 0) return 0;
    v = BoxPokemon_GetValue((BoxPokemon *)p, 5, NULL);
    if (v == 0 || v > 0x1ef) return 0;
    if (BoxPokemon_GetValue((BoxPokemon *)p, 0xab, NULL)) return 1;
    return 0;
}
int fn_80056C4C(void *p) {
    u16 v;
    if (p == 0) return 0;
    v = GetMonDataInternal(p, 5, 0);
    if (v == 0 || v > 0x1ef) return 0;
    if (GetMonDataInternal(p, 0xab, 0)) return 1;
    return 0;
}

}

// Batch 5
#include <cstring>

extern "C" {

u8 fn_80056A5C(void *);
void fn_80253DF0(s16, int, int);
void fn_80253E10(s16, int, f32);
extern const f32 lbl_80640B78;
extern u8 lbl_8063CE34[];
u32 fn_80391F94(void *, int);
void fn_802503D8(u16, u16 *);
void fn_80176EB4(u16 *, u16 *, int);

f32 fn_800597C4(void) {
    if (fn_801E07E8()) return lbl_80640B60;
    if (fn_80007084()) return lbl_80640B60;
    if (*((u8 *)GSrender::sInstance + 0x82)) return lbl_80640B60;
    return *(u64 *)((u8 *)lbl_8063D4A0 + 0x10A0) / lbl_80640B64 / lbl_80640B64;
}
void fn_800574DC(s16 a, int b, void *c) {
    int id;
    switch (fn_80056A5C(c)) {
    case 0:
        id = 0xe8d;
        break;
    case 1:
        id = 0xe90;
        break;
    default:
        return;
    }
    fn_80253EB4(a, b, 2, id);
}
void *fn_80055D98(u32 a, u32 b) __attribute__((never_inline));
void *fn_80055D98(u32 a, u32 b) {
    u32 size = GScache::getCachedFileSize(a, b);
    void *p = GSmem::allocFromHeapAlignedTop(gUnkHeap2, (size + 0x1f) & ~0x1f, 0x20);
    memcpy(p, GScache::getCachedFile(a, b), size);
    return p;
}
void fn_800568C0(s16 a) {
    fn_80253DF0(a, 8, ACTX->flags.b6);
    if (ACTX->flags.b6) {
        switch (ACTX->_1081) {
        case 0:
            fn_80253E10(a, 4, lbl_80640B60);
            break;
        case 1:
            fn_80253E10(a, 4, lbl_80640B78);
            break;
        }
    }
}
void fn_80057450(void *p) {
    u32 z;
    u16 buf2[32];
    u16 buf1[32];
    fn_802503D8(fn_80391F94(lbl_8063CE34 + 0x10, BoxPokemon_GetValue((BoxPokemon *)p, 5, NULL)), buf2);
    fn_80176EB4(buf1, buf2, 0x20);
    BoxPokemon_SetValue((BoxPokemon *)p, 0x74, buf1);
    z = 0;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x4d, &z);
}

}

// Batch 6
extern "C" {

extern u32 lbl_8063F640;
void fn_80101C18(void);
void fn_80226700(u32, u32);
void fn_80226A68(u32);
void fn_8022673C(u32);
u8 SCGetLanguage(void);
extern const f32 lbl_80640B84;

#define INIT_FAST_CAST() \
    asm { \
        li r3, 4; \
        oris r3, r3, 4; \
        mtspr 914, r3; \
        li r3, 5; \
        oris r3, r3, 5; \
        mtspr 915, r3; \
        li r3, 6; \
        oris r3, r3, 6; \
        mtspr 916, r3; \
        li r3, 7; \
        oris r3, r3, 7; \
        mtspr 917, r3 \
    }

struct ArenaCtxT {
    u8 _0[0x10];
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 *_14;
    /* 0x18 */ u32 _18;
};

void *fn_8005606C(void *arg) {
    INIT_FAST_CAST();
    while (TRUE) {
        if (ACTX->flags.b30) {
            fn_80226700(lbl_8063F640, ((ArenaCtxT *)lbl_8063D4A0)->_10);
            fn_80226A68(lbl_8063F640);
            *((ArenaCtxT *)lbl_8063D4A0)->_14 = ((ArenaCtxT *)lbl_8063D4A0)->_18;
            ACTX->flags.b30 = 0;
        }
        if (ACTX->flags.b29) {
            fn_8022673C(lbl_8063F640);
            ACTX->flags.b29 = 0;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

#pragma dont_inline on
void *fn_80056120(void *arg) {
    INIT_FAST_CAST();
    while (TRUE) {
        if (ACTX->flags.b28) {
            fn_80101C18();
            ACTX->flags.b28 = 0;
        }
        if (ACTX->flags.b26) {
            fn_800576AC();
            ACTX->flags.b26 = 0;
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}
#pragma dont_inline reset

void fn_80058580(void) {
    u8 *p = fn_8011C974();
    if (*(u16 *)(p + 0x92) == 0) {
        ACTX->flags.b8 = 0;
    } else {
        ACTX->flags.b8 = 1;
        ACTXF->_1094 = *(u16 *)(p + 0x92);
        ACTXF->_1090 = lbl_80640B60;
        ACTX->flags.b4 = 0;
    }
}
void fn_800584E8(void) {
    u8 *p = fn_8011C974();
    if (*(u16 *)(p + 0x94) == 0) {
        ACTX->flags.b10 = 0;
    } else {
        ACTX->flags.b10 = 1;
        ACTXF->_108C = lbl_80640B84 * *(u16 *)(p + 0x94);
        ACTXF->_1088 = lbl_80640B60;
        ACTX->flags.b5 = 0;
    }
}
int fn_80058B10(int x) {
    switch (SCGetLanguage()) {
    case 2:
        return 1;
    case 3:
        return 3;
    case 4:
        return 2;
    case 5:
        return 4;
    case 6:
        return x ? 5 : 0;
    default:
        return 0;
    }
}

}

// Batch 7
extern "C" {

void *fn_802502F4(u16);
void fn_8015C308(int, u16 *);
void fn_80250134(int, int, int, int, int, int);
int fn_80250398(int, int, int);

void *fn_80056CC4(void *p) {
    if (!fn_80056BD4(p)) {
        return fn_802502F4(10);
    } else if (BoxPokemon_GetValue((BoxPokemon *)p, 0xac, NULL)) {
        if (BoxPokemon_GetValue((BoxPokemon *)p, 3, NULL)) {
            return fn_802502F4(0x1f9);
        } else {
            return fn_802502F4(0x1f8);
        }
    } else {
        return fn_802502F4(fn_80391F94(lbl_8063CE34 + 0x10, BoxPokemon_GetValue((BoxPokemon *)p, 5, NULL)));
    }
}
void *fn_80056D78(void *p) {
    if (!fn_80056C4C(p)) {
        return fn_802502F4(10);
    } else if (GetMonDataInternal(p, 0xac, 0)) {
        if (GetMonDataInternal(p, 3, 0)) {
            return fn_802502F4(0x1f9);
        } else {
            return fn_802502F4(0x1f8);
        }
    } else {
        return fn_802502F4(fn_80391F94(lbl_8063CE34 + 0x10, GetMonDataInternal(p, 5, 0)));
    }
}
u8 fn_80056A5C(void *p) {
    if (!fn_80056BD4(p)) return 2;
    if (BoxPokemon_GetValue((BoxPokemon *)p, 0xac, NULL)) return 2;
    if (!BoxPokemon_GetValue((BoxPokemon *)p, 0xaf, NULL)) return 2;
    switch ((u16)BoxPokemon_GetValue((BoxPokemon *)p, 0x6f, NULL)) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return 2;
    }
}
u8 fn_80056B18(void *p) {
    if (!fn_80056C4C(p)) return 2;
    if (GetMonDataInternal(p, 0xac, 0)) return 2;
    if (!GetMonDataInternal(p, 0xaf, 0)) return 2;
    switch ((u16)GetMonDataInternal(p, 0x6f, 0)) {
    case 0:
        return 0;
    case 1:
        return 1;
    default:
        return 2;
    }
}
u16 fn_80058BFC(int a, int b, int c) {
    u16 buf[3] = {0, 0, 0};
    if (fn_80058BA4() == 1) {
        buf[0] = 0x2e;
        buf[1] = 0x20;
    } else {
        buf[0] = 0x20;
        buf[1] = 0;
    }
    fn_8015C308(0xf, buf);
    fn_80250134(0x3f9, a, b, 0, 0, c);
    return fn_80250398(0x3f9, 1, 0);
}

}

// Batch 8
extern "C" {

int fn_803919C4(void *, int);
int fn_803919F8(void *, int);

int fn_80056F68(void *p, int b) {
    int v = BoxPokemon_GetValue((BoxPokemon *)p, 5, NULL);
    if (v == 0x1ed) {
        switch (BoxPokemon_GetValue((BoxPokemon *)p, 0x70, NULL)) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
        case 5: return 5;
        case 6: return 6;
        case 7: return 7;
        case 8: return 8;
        case 10: return 10;
        case 11: return 11;
        case 12: return 12;
        case 13: return 13;
        case 14: return 14;
        case 15: return 15;
        case 16: return 16;
        case 17: return 17;
        default: return 0;
        }
    } else if (b == 0) {
        return fn_803919C4(lbl_8063CE34 + 0x10, v);
    } else if (v == 0x19d) {
        switch (BoxPokemon_GetValue((BoxPokemon *)p, 0x70, NULL)) {
        case 0:
        default: return 12;
        case 1: return 4;
        case 2: return 8;
        }
    } else {
        return fn_803919F8(lbl_8063CE34 + 0x10, v);
    }
}

}

// Batch 9
#include "gs/GSfile.hpp"

extern "C" {

extern u8 lbl_8063EB6E;

void *fn_8005757C(void *arg) {
    while (!ACTX->flags.b27) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    lbl_8063EB6E = 0;
    GSfile::copyFileToNand("mn_tr_10.fsys");
    GSfile::copyFileToNand("mc_tr_10.fsys");
    GSfile::copyFileToNand("mt_tr_10.fsys");
    GSfile::copyFileToNand("fn_tr_10.fsys");
    GSfile::copyFileToNand("fc_tr_10.fsys");
    GSfile::copyFileToNand("fm_tr_10.fsys");
    GSfile::copyFileToNand("mn_tr_00.fsys");
    GSfile::copyFileToNand("mc_tr_00.fsys");
    GSfile::copyFileToNand("mt_tr_00.fsys");
    GSfile::copyFileToNand("fn_tr_00.fsys");
    GSfile::copyFileToNand("fc_tr_00.fsys");
    GSfile::copyFileToNand("fm_tr_00.fsys");
    ACTX->flags.b3 = 0;
    while (!lbl_8063EB6E) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    GSfile::copyFileToNand("menu_face.fsys");
    GSfile::copyFileToNand("menu_pokemon.fsys");
    ACTX->flags.b23 = 0;
    GSthreadManager::sInstance->stopThread(0x9fc78);
    return 0;
}

}

// Batch 10
extern "C" {


struct MonSetup {
    /* 0x0 */ u16 _0;
    /* 0x2 */ u16 _2;
    /* 0x4 */ u16 _4;
    /* 0x6 */ u16 _6;
    /* 0x8 */ u32 _8;
    /* 0xC */ u16 name[1];
};

void fn_80057208(void *p) {
    u32 tmp;
    if (fn_80056C4C(p)) {
        if (GetMonDataInternal(p, 0x36, 0)) {
            tmp = GetMonDataInternal(p, 0x42, 0);
            Pokemon_SetValue((Pokemon *)p, 0x3a, &tmp);
        }
        if (GetMonDataInternal(p, 0x37, 0)) {
            tmp = GetMonDataInternal(p, 0x43, 0);
            Pokemon_SetValue((Pokemon *)p, 0x3b, &tmp);
        }
        if (GetMonDataInternal(p, 0x38, 0)) {
            tmp = GetMonDataInternal(p, 0x44, 0);
            Pokemon_SetValue((Pokemon *)p, 0x3c, &tmp);
        }
        if (GetMonDataInternal(p, 0x39, 0)) {
            tmp = GetMonDataInternal(p, 0x45, 0);
            Pokemon_SetValue((Pokemon *)p, 0x3d, &tmp);
        }
    }
}
void fn_8005732C(void *p) {
    u32 tmp;
    if (fn_80056BD4(p)) {
        if (BoxPokemon_GetValue((BoxPokemon *)p, 0x36, NULL)) {
            tmp = BoxPokemon_GetValue((BoxPokemon *)p, 0x42, NULL);
            BoxPokemon_SetValue((BoxPokemon *)p, 0x3a, &tmp);
        }
        if (BoxPokemon_GetValue((BoxPokemon *)p, 0x37, NULL)) {
            tmp = BoxPokemon_GetValue((BoxPokemon *)p, 0x43, NULL);
            BoxPokemon_SetValue((BoxPokemon *)p, 0x3b, &tmp);
        }
        if (BoxPokemon_GetValue((BoxPokemon *)p, 0x38, NULL)) {
            tmp = BoxPokemon_GetValue((BoxPokemon *)p, 0x44, NULL);
            BoxPokemon_SetValue((BoxPokemon *)p, 0x3c, &tmp);
        }
        if (BoxPokemon_GetValue((BoxPokemon *)p, 0x39, NULL)) {
            tmp = BoxPokemon_GetValue((BoxPokemon *)p, 0x45, NULL);
            BoxPokemon_SetValue((BoxPokemon *)p, 0x3d, &tmp);
        }
    }
}
void fn_800570E8(void *p, MonSetup *q) {
    u32 tmp;
    u16 buf[20];
    tmp = 0;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x97, &tmp);
    BoxPokemon_SetValue((BoxPokemon *)p, 0x6e, &tmp);
    tmp = 0x37;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x98, &tmp);
    tmp = 0x10;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x79, &tmp);
    tmp = q->_0;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x94, &tmp);
    tmp = q->_2;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x95, &tmp);
    tmp = q->_4;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x96, &tmp);
    tmp = q->_6;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x9b, &tmp);
    tmp = q->_8;
    BoxPokemon_SetValue((BoxPokemon *)p, 0x7, &tmp);
    fn_80176EB4(buf, q->name, 0x10);
    BoxPokemon_SetValue((BoxPokemon *)p, 0x8f, buf);
}

}

// Batch 11
#include "gs/GSscene.hpp"
#include "gs/GShierarchyModule.hpp"

struct ArenaCtxS {
    u8 _0[0x1C];
    /* 0x1C */ void *_1C;
    /* 0x20 */ void *_20;
    /* 0x24 */ void *_24;
    /* 0x28 */ GSscene *_28;
    /* 0x2C */ GSscene *_2C;
    /* 0x30 */ GSscene *_30;
    /* 0x34 */ u16 _34;
    /* 0x36 */ u16 _36;
    /* 0x38 */ u32 _38;
};
struct Bits32P {
    u32 _hi : 6;
    u32 p24 : 2;
    u32 _lo : 24;
};
#define ACTXS ((ArenaCtxS *)lbl_8063D4A0)

extern "C" {

void fn_80057FB4(int);
void fn_80253CCC(u16);
void fn_801E37F0(void *);
extern u8 *lbl_8063F410;

#pragma dont_inline on
void fn_800578BC(void) {
    switch (((Bits32P *)&ACTX->flags)->p24) {
    case 2:
        fn_80057FB4(2);
        break;
    case 3:
        fn_80057FB4(3);
        break;
    }
    if (ACTXS->_28) {
        delete ACTXS->_28;
        ACTXS->_28 = 0;
        lbl_8063F410[0x40d] = 0;
    }
    if (ACTXS->_2C) {
        delete ACTXS->_2C;
        ACTXS->_2C = 0;
    }
    if (!ACTXS->_30) {
        GShierarchyModule::setCurrentScene(ACTXS->_30);
    }
    ACTXS->_30 = 0;
    fn_80253CCC(ACTXS->_34);
    if (ACTXS->_1C) {
        fn_801E37F0(ACTXS->_1C);
        fn_80055E30(ACTXS->_1C);
    }
    if (ACTXS->_20) {
        fn_80055E30(ACTXS->_20);
    }
    if (ACTXS->_24) {
        fn_801E37F0(ACTXS->_24);
        fn_80055E30(ACTXS->_24);
    }
    ACTXS->_1C = 0;
    ACTXS->_20 = 0;
    ACTXS->_24 = 0;
}
#pragma dont_inline reset

}

// Batch 12
extern "C" {

struct U16List {
    u8 _0[4];
    u16 arr[12];
};

void fn_80058EA0(U16List *p) {
    s16 i;
    int j;
    for (i = 0; i < 10; i++) {
        if (p->arr[i] == 0xffff && p->arr[i + 1] == 0xffff) {
            p->arr[i] = 0xffff;
            p->arr[i + 1] = 0x13;
            p->arr[i + 2] = 0;
            break;
        }
        if (p->arr[i] == 0) {
            p->arr[i] = 0xffff;
            p->arr[i + 1] = 0x13;
            p->arr[i + 2] = 0;
            break;
        }
    }
    for (j = 9; j >= 0; j--) {
        p->arr[j + 2] = p->arr[j];
    }
    p->arr[0] = 0xffff;
    p->arr[1] = 0x14;
}

}

// Batch 13
struct ArenaCtxR {
    u8 _0[0x1098];
    /* 0x1098 */ f32 _1098;
    /* 0x109C */ f32 _109C;
    /* 0x10A0 */ s64 _10A0;
    /* 0x10A8 */ u8 _10A8;
};
#define ACTXR ((ArenaCtxR *)lbl_8063D4A0)

extern "C" {

extern u32 lbl_803FB820[];
int fn_80253F6C(int, void (*)(void), int);
void fn_80253F8C(int);
void fn_8005A994(void);
void fn_80059414(void);

void fn_80058CBC(U16List *p) {
    s16 i;
    int j;
    for (i = 0; i < 12; i++) {
        if (p->arr[i] == 0xffff && p->arr[i + 1] == 0xffff) {
            p->arr[i] = 0;
            break;
        }
        if (p->arr[i] == 0) {
            break;
        }
    }
    for (j = 9; j >= 0; j--) {
        p->arr[j + 2] = p->arr[j];
    }
    p->arr[0] = 0xffff;
    p->arr[1] = 0x13;
}

void *fn_80059288(void *arg) {
    OSTime t;
    int h;
    ACTXR->_10A8 = 0;
    ACTXR->_1098 = lbl_80640B60;
    h = fn_80253F6C(0, fn_80059414, -1);
    fn_8005A994();
    while (!ACTX->flags.b1) {
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    GSfsys::loadFsys(lbl_803FB820[(u8)fn_80058B10(1)]);
    ACTXR->_10A8 = 1;
    ACTX->flags.b0 = 1;
    t = OSGetTime();
    do {
        ACTXR->_10A0 = OSTicksToMicroseconds((u64)(OSGetTime() - t));
        t = OSGetTime();
        ACTXR->_1098 += fn_800597C4();
        GSthreadManager::sInstance->sleepCurrentThread();
    } while (ACTXR->_10A8 != 15);
    GSfsys::fn_80249890(lbl_803FB820[(u8)fn_80058B10(1)]);
    GScache::freeFsysCacheEntries(lbl_803FB820[(u8)fn_80058B10(1)]);
    fn_80253F8C(h);
    ACTX->flags.b2 = 1;
    return 0;
}

}

// Batch 14
extern "C" {

#pragma dont_inline on
void *fn_80055EDC(void *arg) {
    OSTime t;
    int last;
    t = OSGetTime();
    last = 0;
    INIT_FAST_CAST();
    while (TRUE) {
        *(u64 *)lbl_8063D4A0 = OSTicksToMicroseconds((u64)(OSGetTime() - t));
        t = OSGetTime();
        if (ACTX->flags.b31) {
            fn_800561B0();
        }
        if (!ACTX->flags.b5 && ACTX->flags.b10 && ACTXF->_1088 < ACTXF->_108C) {
            ACTXF->_1088 += fn_80055E3C();
        }
        if (!ACTX->flags.b4 && ACTX->flags.b8 && ACTXF->_1090 < ACTXF->_1094) {
            int rem;
            ACTXF->_1090 += fn_80055E3C();
            rem = ACTXF->_1094 - ACTXF->_1090;
            if ((u16)rem <= 5 && (u16)last != (u16)rem && (u16)rem != 0) {
                last = rem;
                fn_8000B170((void *)0x234, lbl_80640B68, 0);
            }
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}
#pragma dont_inline reset

}

// Batch 15
#include "gs/render/GSrenderTarget.hpp"

extern "C" {

void fn_80057FB4(int mode) {
    GSrenderTarget *rt = GSrenderTarget::findTarget(2);
    switch (mode) {
    case 1:
        if (ACTXS->_20) {
            fn_80253DF0((s16)ACTXS->_34, 8, 0);
            ((Bits32P *)&ACTX->flags)->p24 = 0;
        }
        break;
    case 2:
        if (ACTXS->_1C) {
            GSobject *o;
            u32 v;
            if (rt && (v = ACTXS->_38) != 0) {
                *(u32 *)((u8 *)rt + 0x20) = 0;
                *(u32 *)((u8 *)rt + 0xC) = v;
            }
            o = ACTXS->_28->getObject(0);
            if (o) {
                GShierarchyModule::fn_80200858(o);
            }
            GShierarchyModule::setCurrentScene(ACTXS->_30);
            lbl_8063F410[0x40d] = 0;
            ((Bits32P *)&ACTX->flags)->p24 = 0;
        }
        break;
    case 3:
        if (ACTXS->_24) {
            GSobject *o;
            u32 v;
            if (rt && (v = ACTXS->_38) != 0) {
                *(u32 *)((u8 *)rt + 0x20) = 0;
                *(u32 *)((u8 *)rt + 0xC) = v;
            }
            o = ACTXS->_2C->getObject(0);
            if (o) {
                GShierarchyModule::fn_80200858(o);
            }
            GShierarchyModule::setCurrentScene(ACTXS->_30);
            lbl_8063F410[0x40d] = 0;
            ((Bits32P *)&ACTX->flags)->p24 = 0;
        }
        break;
    }
}

}

// Batch 16
extern "C" {

u16 fn_80253C38(void *, void *, void *, void *, int, int, int, int);

void fn_800576B0(void) {
    GSsceneData *d;
    GSobject *o;
    ((Bits32P *)&ACTX->flags)->p24 = 0;
    if (!ACTXS->_1C) {
        GSfsys::loadFsys(0x401);
        ACTXS->_1C = fn_80055D98(0x401, 0x44a0000);
        d = (GSsceneData *)ACTXS->_1C;
        fn_801E34DC(d, (u32)d);
        ACTXS->_28 = new GSscene(d);
        ACTXS->_30 = 0;
        o = ACTXS->_28->getObject(0);
        if (o) {
            GShierarchyModule::fn_80200858(o);
        }
        ACTXS->_20 = fn_80055D98(0x401, 0x1b9b1a00);
        ACTXS->_34 = fn_80253C38(ACTXS->_20, 0, 0, 0, -1, 0, 1, 0);
        fn_80253DF0((s16)ACTXS->_34, 10, 1);
        ACTXS->_24 = fn_80055D98(0x401, 0x23800000);
        d = (GSsceneData *)ACTXS->_24;
        fn_801E34DC(d, (u32)d);
        ACTXS->_2C = new GSscene(d);
        o = ACTXS->_2C->getObject(0);
        if (o) {
            GShierarchyModule::fn_80200858(o);
        }
        GSfsys::fn_80249890(0x401);
        GScache::freeFsysCacheEntries(0x401);
    }
}

}

// Batch 17
struct Bits32T {
    u32 _hi : 17;
    u32 t12 : 3;
    u32 _lo : 12;
};

struct DrawObj {
    u8 _0[0x11];
    /* 0x11 */ u8 _11;
    u8 _12[0x48 - 0x12];
    /* 0x48 */ f32 _48;
    /* 0x4C */ f32 _4C;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
};

extern "C" {

void fn_80253EDC(s16, void *, int, void *);
extern const f32 lbl_80640B74;

void fn_80056630(s16 a, DrawObj *o) {
    int st;
    f32 buf[8];
    fn_80253EDC(a, o, 3, &st);
    switch (st) {
    case 3:
        if (ACTX->flags2.b31) {
            o->_48 += lbl_80640B74;
            o->_4C += lbl_80640B74;
            o->_50 += lbl_80640B74;
            o->_54 += lbl_80640B74;
            ACTX->flags2.b31 = 0;
        }
        if (ACTX->flags.b20) {
            u32 color;
            int x;
            int y, w, h;
            fn_80253EDC(a, o, 6, buf);
            x = buf[0];
            y = buf[4];
            w = buf[1] - buf[0];
            h = buf[6] - buf[4];
            color = o->_11 | 0xffffff00;
            fn_8015C308(8, (u16 *)((Bits32Q *)&ACTX->flags)->q15);
            fn_80250134(0x3ed, x, y, (s16)w, (s16)h, color);
        }
        break;
    case 2:
        if (ACTX->flags2.b30) {
            o->_48 += lbl_80640B74;
            o->_4C += lbl_80640B74;
            o->_50 += lbl_80640B74;
            o->_54 += lbl_80640B74;
            ACTX->flags2.b30 = 0;
        }
        break;
    case 0:
    case 1:
        if (((u32)st == 1 && ACTX->flags.b21) || (st == 0 && !ACTX->flags.b21)) {
            switch (ACTX->_1058) {
            case 0:
                ((Bits32T *)&ACTX->flags)->t12 = 0;
                break;
            case 1:
                ((Bits32T *)&ACTX->flags)->t12 = 1;
                break;
            case 2:
                ((Bits32T *)&ACTX->flags)->t12 = 2;
                break;
            case 3:
                ((Bits32T *)&ACTX->flags)->t12 = 3;
                break;
            default:
                ((Bits32T *)&ACTX->flags)->t12 = 7;
                break;
            }
            fn_80253EDC(a, o, 6, (u8 *)lbl_8063D4A0 + 0x105c);
        }
        break;
    }
}

}

// Batch 18
#include "gs/render/GStexture.hpp"

struct Quad {
    f32 x[4];
    f32 y[4];
};

struct LangFsys {
    u32 a;
    u32 b;
};

extern "C" {

extern const f32 lbl_80640BA0;
extern const f32 lbl_80640BA4;
extern const f32 lbl_80640B88;
extern const f32 lbl_80640B8C;
GStexture *fn_8005AC60(u32, u32);
void fn_8005AF78(GStexture *, Quad *, u32, int);

struct LangTable {
    u32 fsys[6];
    LangFsys tex[6];
    u32 tex2[6];
};

void fn_80058FD4(u8 c, int mode) {
    Quad q;
    u32 color = c | 0xffffff00;
    LangTable *t = (LangTable *)lbl_803FB820;
    if (mode) {
        if (*((u8 *)GSrender::sInstance + 0x7a)) {
            LangFsys *e;
            q.x[0] = q.x[3] = lbl_80640BA0;
            q.x[1] = q.x[2] = lbl_80640BA4;
            q.y[0] = q.y[1] = lbl_80640B60;
            q.y[2] = q.y[3] = lbl_80640B8C;
            e = &t->tex[(u8)fn_80058B10(1)];
            fn_8005AF78(fn_8005AC60(t->fsys[(u8)fn_80058B10(1)], e->b), &q, color, 0);
        } else {
            q.x[0] = q.x[3] = lbl_80640B60;
            q.x[1] = q.x[2] = lbl_80640B88;
            q.y[0] = q.y[1] = lbl_80640B60;
            q.y[2] = q.y[3] = lbl_80640B8C;
            fn_8005AF78(fn_8005AC60(t->fsys[(u8)fn_80058B10(1)], t->tex[(u8)fn_80058B10(1)].a), &q, color, 0);
        }
    } else {
        GStexture *tex;
        u16 w, h;
        f32 left, top;
        tex = fn_8005AC60(t->fsys[(u8)fn_80058B10(1)], t->tex2[(u8)fn_80058B10(1)]);
        w = tex->getWidth();
        h = tex->getHeight();
        left = (640 - w) / 2;
        top = (480 - h) / 2;
        q.x[0] = q.x[3] = left;
        q.x[1] = q.x[2] = left + w;
        q.y[0] = q.y[1] = top;
        q.y[2] = q.y[3] = top + h;
        fn_8005AF78(tex, &q, color, 0);
    }
}

}

// Batch 19
extern "C" {

extern const f32 lbl_80640B90;
void fn_80234FE0(GSrender *, f32, f32, f32, f32, f32, f32);

void fn_80058178(void) {
    GSrender *r = GSrender::sInstance;
#define RSTATE(r) (*(GSrenderState **)((u8 *)(r) + 0x1638))
    RSTATE(r)->mCurr.mLineWidth = 6;
    RSTATE(r)->mCurr.mLineTexOffsets = GX_TO_ZERO;
    RSTATE(r)->_4 |= (1 << 2);
    RSTATE(r)->_0 |= (1 << 0);
    GSrender::sInstance->setBlend(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
    fn_80234FE0(GSrender::sInstance, lbl_80640B60, lbl_80640B60, lbl_80640B88, lbl_80640B8C, lbl_80640B60, lbl_80640B90);
    GSrender::sInstance->setEfbUpdate(true, false, false);
    GSrender::sInstance->setZCompare(false, 3);
    GSrender::sInstance->setAlphaCompare(false, 0, 0);
    GSrender::sInstance->setCullMode(GX_CULL_NONE);
    GSrender::sInstance->setClipMode(GX_CLIP_DISABLE);
    GSrender::sInstance->setFogEnabled(false);
    fn_8005650C();
}

}

// Batch 20
extern "C" {

extern void *lbl_8063E908;
extern void *lbl_8063E90C;
void fn_8025005C(void *);
void fn_8025006C(void *);

static inline void LoadMsgPair(u32 fsys, u32 f1, u32 f2) {
    u32 size;
    GSfsys::loadFsys(fsys);
    size = GScache::getCachedFileSize(fsys, f1);
    memcpy(lbl_8063E908, GScache::getCachedFile(fsys, f1), size);
    size = GScache::getCachedFileSize(fsys, f2);
    memcpy(lbl_8063E90C, GScache::getCachedFile(fsys, f2), size);
    GSfsys::fn_80249890(fsys);
    GScache::freeFsysCacheEntries(fsys);
    fn_8025005C(lbl_8063E908);
    fn_8025006C(lbl_8063E90C);
}

void fn_80058778(int x) {
    if (x) {
        switch ((u8)fn_80058B10(0)) {
        case 0:
            LoadMsgPair(0x5dc, 0x27c00000, 0x27c10000);
            break;
        case 1:
            LoadMsgPair(0x5de, 0x2b820000, 0x2b830000);
            break;
        case 2:
            LoadMsgPair(0x5e0, 0x2b860000, 0x2b870000);
            break;
        case 3:
            LoadMsgPair(0x5dd, 0x2b800000, 0x2b810000);
            break;
        case 4:
            LoadMsgPair(0x5df, 0x2b840000, 0x2b850000);
            break;
        }
    } else {
        switch (*(int *)(fn_8015F690() + 0x48)) {
        case 1:
        case 2:
        case 3:
        case 4:
            break;
        case 0:
        default:
            LoadMsgPair(0x5dc, 0x27c00000, 0x27c10000);
            break;
        }
    }
}

}

// Batch 21
#include "gs/GSinput.hpp"

extern "C" {

extern const f32 lbl_80640BB0;
extern const f32 lbl_80640BB4;
extern const f32 lbl_80640BB8;
extern const f32 lbl_80640BBC;

void fn_80059414(void) {
    GSinputDevice *dev = GSinput::getDevice(0);
    f32 f;
    switch (ACTXR->_10A8) {
    case 0:
        break;
    case 1:
        ACTXR->_109C = ACTXR->_1098;
        fn_80058FD4(0, 1);
        ACTXR->_10A8 = 2;
        break;
    case 2:
        f = lbl_80640BB0 * (ACTXR->_1098 - ACTXR->_109C);
        if (f >= lbl_80640B68) {
            f = lbl_80640B68;
            ACTXR->_10A8 = 3;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(lbl_80640BB4 * f, 1);
        break;
    case 3:
        if (ACTXR->_1098 - ACTXR->_109C >= lbl_80640BB0) {
            ACTXR->_10A8 = 4;
        }
        fn_80058FD4(0xff, 1);
        break;
    case 4:
        if (ACTXR->_1098 - ACTXR->_109C >= lbl_80640BB8) {
            ACTXR->_10A8 = 5;
            ACTXR->_109C = ACTXR->_1098;
        } else if (dev && (*(u32 *)((u8 *)dev + 0x1c) & 0x1f1f)) {
            ACTXR->_10A8 = 5;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(0xff, 1);
        break;
    case 5:
        f = lbl_80640BB0 * (ACTXR->_1098 - ACTXR->_109C);
        if (f >= lbl_80640B68) {
            f = lbl_80640B68;
            ACTXR->_10A8 = 6;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(lbl_80640BB4 * (lbl_80640B68 - f), 1);
        break;
    case 6:
        fn_80058FD4(0, 1);
        ACTXR->_10A8 = 13;
        break;
    case 7:
        ACTXR->_109C = ACTXR->_1098;
        fn_80058FD4(0, 0);
        ACTXR->_10A8 = 8;
        break;
    case 8:
        f = lbl_80640BB0 * (ACTXR->_1098 - ACTXR->_109C);
        if (f >= lbl_80640B68) {
            f = lbl_80640B68;
            ACTXR->_10A8 = 9;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(lbl_80640BB4 * f, 0);
        break;
    case 9:
        if (ACTXR->_1098 - ACTXR->_109C >= lbl_80640BB0) {
            ACTXR->_10A8 = 10;
        }
        fn_80058FD4(0xff, 0);
        break;
    case 10:
        if (ACTXR->_1098 - ACTXR->_109C >= lbl_80640BBC) {
            ACTXR->_10A8 = 11;
            ACTXR->_109C = ACTXR->_1098;
        } else if (dev && (*(u32 *)((u8 *)dev + 0x1c) & 0x1f1f)) {
            ACTXR->_10A8 = 11;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(0xff, 0);
        break;
    case 11:
        f = lbl_80640BB0 * (ACTXR->_1098 - ACTXR->_109C);
        if (f >= lbl_80640B68) {
            f = lbl_80640B68;
            ACTXR->_10A8 = 12;
            ACTXR->_109C = ACTXR->_1098;
        }
        fn_80058FD4(lbl_80640BB4 * (lbl_80640B68 - f), 0);
        break;
    case 12:
        fn_80058FD4(0, 0);
        ACTXR->_10A8 = 13;
        break;
    case 13:
        ACTXR->_10A8 = 14;
        break;
    case 14:
        ACTXR->_10A8 = 15;
        break;
    }
}

}

// Batch 22
struct ArenaCtxI {
    u8 _0[0x1040];
    /* 0x1040 */ void *_1040;
    /* 0x1044 */ s16 _1044;
    /* 0x1048 */ void *_1048;
    /* 0x104C */ s16 _104C;
    /* 0x1050 */ void *_1050;
    /* 0x1054 */ s16 _1054;
};
#define ACTXI ((ArenaCtxI *)lbl_8063D4A0)

extern "C" {

void fn_8005C9A8(int);
void fn_8005C9B8(int);
void fn_8005A588(void);
void fn_80055504(void);
void fn_8005A450(void);
void fn_800AA470(void);
void fn_800F8B04(void);
void fn_80104354(void);
void fn_800E9740(void);
void fn_800E4320(void);
void fn_8011E1FC(void);
void fn_8013A930(void);
void fn_80131CF0(void);
void fn_801581B8(void);
void fn_80162790(void);
void fn_8016281C(int);
void fn_80161164(void);

void fn_800559D4(void) {
    *(u64 *)lbl_8063D4A0 = 0;
    ACTX->flags.b31 = 0;
    ACTX->flags.b30 = 0;
    ACTX->flags.b29 = 0;
    ACTX->flags.b28 = 0;
    ACTX->flags.b27 = 1;
    ACTX->flags.b26 = 0;
    ACTXS->_20 = 0;
    ACTXS->_1C = 0;
    ACTX->flags.b3 = 0;
    ACTX->flags.b23 = 0;
    ACTX->flags.b22 = 0;
    ACTX->flags.b20 = 0;
    ACTX->flags.b19 = 0;
    ACTX->flags.b11 = 0;
    ACTX->flags.b6 = 0;
    ACTX->_1081 = 0;
    ACTX->_107C = 0;
    ACTX->_1080 = 0;
    ACTX->flags.b3 = 1;
    ACTX->flags.b23 = 1;
    GSthreadManager::sInstance->createThread(0x9fc78, fn_8005757C, 0, 0x2000, 8, 1);
    fn_8005C9A8(0x80);
    fn_8005C9B8(0x60);
    fn_8005A588();
    GSfsys::loadFsys(0xe);
    fn_80055504();
    GSthreadManager::sInstance->createThread(0x9fbf1, fn_80055EDC, 0, 0x2000, 8, 1);
    GSthreadManager::sInstance->createThread(0xa2c2a, fn_8005606C, 0, 0x2000, 8, 1);
    GSthreadManager::sInstance->createThread(0x9fbfd, fn_80056120, 0, 0x2000, 8, 1);
    fn_8005A450();
    fn_80055EB4(0);
    fn_800AA470();
    fn_800F8B04();
    fn_80104354();
    fn_800E9740();
    fn_800E4320();
    fn_8011E1FC();
    fn_8013A930();
    fn_80131CF0();
    fn_801581B8();
    fn_80162790();
    fn_8016281C(0);
    fn_8016281C(1);
    fn_8016281C(2);
    fn_8016281C(3);
    ACTXI->_1040 = fn_80055D98(0xe, 0x1d571a00);
    ACTXI->_1044 = fn_80253C38(ACTXI->_1040, 0, 0, (void *)fn_800564CC, -1, 1, 1, 0);
    fn_80253DB0(ACTXI->_1044, 1, 0);
    fn_80253DF0(ACTXI->_1044, 9, 3);
    ACTXI->_1048 = fn_80055D98(0xe, 0x21881a00);
    ACTXI->_104C = fn_80253C38(ACTXI->_1048, (void *)fn_8005654C, (void *)fn_800565BC, (void *)fn_80056630, -1, 1, 1, 0);
    fn_80253DB0(ACTXI->_104C, 0, 0);
    fn_80253DF0(ACTXI->_104C, 9, 2);
    ACTXI->_1050 = fn_80055D98(0xe, 0x23881a00);
    ACTXI->_1054 = fn_80253C38(ACTXI->_1050, (void *)fn_800568C0, (void *)fn_8005694C, (void *)fn_80056978, -1, 1, 1, 0);
    fn_80253DB0(ACTXI->_1054, 0, 0);
    fn_80253DF0(ACTXI->_1054, 9, 2);
    fn_80161164();
}

}

// Batch 23
#include "gs/scene/GSnull.hpp"

struct Vec2f {
    f32 x;
    f32 y;
};

struct UnkF410 {
    u8 _0[0x40d];
    /* 0x40D */ u8 _40d;
    /* 0x40E */ u8 _40e;
    u8 _40f[0x418 - 0x40f];
    /* 0x418 */ u32 _418;
    u8 _41c[0x424 - 0x41c];
    /* 0x424 */ Vec2f _424;
    /* 0x42C */ f32 _42c;
    /* 0x430 */ u8 _430;
    /* 0x431 */ u8 _431;
    u8 _432[2];
    /* 0x434 */ u32 _434;
    u8 _438[0x450 - 0x438];
    /* 0x450 */ f32 _450;
};
#define F410 ((UnkF410 *)lbl_8063F410)
#define RT_FIELD(rt, off) (*(u32 *)((u8 *)(rt) + (off)))

struct ObjRaw {
    u8 _0[0x8];
    /* 0x08 */ GSnull **nodes;
    u8 _c[4];
    /* 0x10 */ u16 *camLookup;
    u8 _14[0xde - 0x14];
    /* 0xDE */ u16 nodeCount;
    /* 0xE0 */ u16 camCount;
};

static inline GSnull *ObjGetNode(ObjRaw *o, u16 index) {
    if (!o->nodes) {
        return NULL;
    }
    if (index >= o->nodeCount) {
        return NULL;
    }
    return o->nodes[index];
}

static inline GSnull *ObjGetCamera(ObjRaw *o, u16 index) {
    u16 *lookup = o->camLookup;
    if (!lookup) {
        return NULL;
    }
    if (index >= o->camCount) {
        return NULL;
    }
    return ObjGetNode(o, lookup[index]);
}

extern "C" {

extern const f32 lbl_80640B7C;
extern const f32 lbl_80640B80;
u32 fn_8023B330(GSrenderTarget *, u32);

static inline void RtUpdate(u32 v) {
    GSrenderTarget *t = GSrenderTarget::findTarget((v >> 16) & 0xff);
    u32 r;
    if (t) {
        r = fn_8023B330(t, v);
    } else {
        r = 0;
    }
    if (!r) {
        GSrenderTarget::_unkFunc_1(v);
    }
}

void fn_800579FC(int mode) {
    GSrenderTarget *rt = GSrenderTarget::findTarget(2);
    switch (mode) {
    case 1:
        if (((Bits32P *)&ACTX->flags)->p24 == 1) {
            break;
        }
        if (((Bits32P *)&ACTX->flags)->p24 == 2) {
            GSrenderTarget *rt2 = GSrenderTarget::findTarget(2);
            GSobject *o;
            u32 v;
            if (rt2 && (v = ACTXS->_38) != 0) {
                RT_FIELD(rt2, 0x20) = 0;
                RT_FIELD(rt2, 0xC) = v;
            }
            o = ACTXS->_28->getObject(0);
            if (o) {
                GShierarchyModule::fn_80200858(o);
            }
            GShierarchyModule::setCurrentScene(ACTXS->_30);
            F410->_40d = 0;
        }
        ((Bits32P *)&ACTX->flags)->p24 = 1;
        fn_80253DF0((s16)ACTXS->_34, 8, 1);
        break;
    case 2:
        if (((Bits32P *)&ACTX->flags)->p24 == 2) {
            break;
        }
        if (((Bits32P *)&ACTX->flags)->p24 == 1) {
            fn_80253DF0((s16)ACTXS->_34, 8, 0);
        }
        if (((Bits32P *)&ACTX->flags)->p24 == 3) {
            fn_80057FB4(3);
        }
        ((Bits32P *)&ACTX->flags)->p24 = 2;
        if (rt) {
            ACTXS->_38 = RT_FIELD(rt, 0x20) == 0 ? RT_FIELD(rt, 0xC) : RT_FIELD(rt, 0x24);
        }
        if (ACTXS->_28) {
            Vec2f tmp;
            GSobject *o;
            GSnull *cam;
            ACTXS->_30 = *(GSscene **)((u8 *)GShierarchyModule::sInstance + 0x124);
            GShierarchyModule::setCurrentScene(ACTXS->_28);
            F410->_40d = 1;
            F410->_42c = lbl_80640B7C;
            F410->_430 = 0;
            F410->_434 = 0;
            F410->_431 = 50;
            tmp.x = lbl_80640B60;
            tmp.y = lbl_80640B60;
            F410->_424 = tmp;
            o = ACTXS->_28->getObject(0);
            if (o) {
                GShierarchyModule::fn_80200594(o);
                cam = ObjGetCamera((ObjRaw *)o, 0);
                if (rt && cam) {
                    RT_FIELD(rt, 0x20) = 0;
                    RT_FIELD(rt, 0xC) = (u32)cam;
                }
            }
        }
        break;
    case 3:
        if (((Bits32P *)&ACTX->flags)->p24 == 3) {
            break;
        }
        if (((Bits32P *)&ACTX->flags)->p24 == 1) {
            fn_80253DF0((s16)ACTXS->_34, 8, 0);
        }
        if (((Bits32P *)&ACTX->flags)->p24 == 2) {
            fn_80057FB4(2);
        }
        ((Bits32P *)&ACTX->flags)->p24 = 3;
        if (rt) {
            ACTXS->_38 = RT_FIELD(rt, 0x20) == 0 ? RT_FIELD(rt, 0xC) : RT_FIELD(rt, 0x24);
        }
        if (ACTXS->_2C) {
            Vec2f tmp;
            GSobject *o;
            u32 v;
            s32 id;
            GSrenderTarget *t;
            u32 r;
            ACTXS->_30 = *(GSscene **)((u8 *)GShierarchyModule::sInstance + 0x124);
            GShierarchyModule::setCurrentScene(ACTXS->_2C);
            F410->_40d = 1;
            F410->_42c = lbl_80640B80;
            F410->_431 = 40;
            F410->_430 = 0;
            if (F410->_418) {
                F410->_40e = 1;
            } else {
                F410->_40e = 0;
            }
            F410->_434 = 0;
            F410->_450 = lbl_80640B6C;
            tmp.x = lbl_80640B60;
            tmp.y = lbl_80640B60;
            F410->_424 = tmp;
            o = ACTXS->_2C->getObject(0);
            {
                u32 v = *(u32 *)((u8 *)GShierarchyModule::sInstance + 0x138);
                s32 id = (v >> 16) & 0xff;
                GSrenderTarget *t = GSrenderTarget::findTarget(id);
                u32 r;
                if (t) {
                    r = fn_8023B330(t, v);
                } else {
                    r = 0;
                }
                if (!r) {
                    t = GSrenderTarget::findTarget(id);
                    if (t) {
                        t->fn_8023B3B8(v);
                    }
                }
            }
            {
                v = *(u32 *)((u8 *)GShierarchyModule::sInstance + 0x144);
                id = (v >> 16) & 0xff;
                t = GSrenderTarget::findTarget(id);
                if (t) {
                    r = fn_8023B330(t, v);
                } else {
                    r = 0;
                }
                if (!r) {
                    t = GSrenderTarget::findTarget(id);
                    if (t) {
                        t->fn_8023B3B8(v);
                    }
                }
            }
            if (o) {
                GShierarchyModule::fn_80200594(o);
                o = (GSobject *)ObjGetCamera((ObjRaw *)o, 0);
                if (rt && o) {
                    RT_FIELD(rt, 0x20) = 0;
                    RT_FIELD(rt, 0xC) = (u32)o;
                    ((GSnull *)o)->initTransform(false);
                    if ((*(u32 *)((u8 *)o + 0x104) & 3) == 1) {
                        *(f32 *)((u8 *)o + 0x168) = lbl_80640B84;
                        *(u32 *)((u8 *)o + 0x104) |= 8;
                    }
                }
            }
        }
        break;
    }
}

}
