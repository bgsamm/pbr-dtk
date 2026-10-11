#include ".unsorted/8013F044.hpp"

#include "common.hpp"
#include "gs/GSfsys.hpp"
#include "gs/GScache.hpp"
#include "gs/GSrender.hpp"

extern "C" {

void fn_8014C074(void) {}
void fn_8014E050(void) {}

}

extern "C" {

extern u8* lbl_8063D578;
extern const f32 lbl_8064144C;

int fn_80253E8C(s16, int, int, void*);
int fn_80253EDC(s16, int, int, void*);
void fn_80058CBC(void*);
void fn_80253E10(s16, f32, int);
void fn_80253DB0(s16, int, int);
void fn_80253DF0(s16, int, int);
void fn_80253E4C(s16, int, void*);
void fn_8017714C(void*, void*, int);
int fn_80162A90(int);
void fn_80166D6C(void*, int, int, int, int, int);

#define GW_S16(off, i) (*(s16*)(lbl_8063D578 + (i) * 2 + (off)))

void fn_8014FC00(u8* p) {
    p[0x6e5] = 0;
    fn_80058CBC(p);
}

void fn_8014BDA8(s16 a) {
    fn_80253E10(a, lbl_8064144C, 4);
}

void fn_8014E94C(u16 i, int b) {
    fn_80253DB0(GW_S16(0x80, i), b, 0);
}

void fn_8014E964(u16 i, int b) {
    fn_80253DF0(GW_S16(0x80, i), 8, b);
}

#define SETFLAG_FN(name, callee) \
    void name(s16 a, int b) { u8 buf[8]; callee(a, b, 3, buf); }

SETFLAG_FN(fn_80149348, fn_80253E8C)
SETFLAG_FN(fn_80149374, fn_80253EDC)
SETFLAG_FN(fn_801498C0, fn_80253E8C)
SETFLAG_FN(fn_801498EC, fn_80253EDC)
SETFLAG_FN(fn_80149918, fn_80253E8C)
SETFLAG_FN(fn_80149944, fn_80253EDC)
SETFLAG_FN(fn_80149970, fn_80253E8C)
SETFLAG_FN(fn_8014BCA0, fn_80253E8C)
SETFLAG_FN(fn_8014BCCC, fn_80253EDC)
SETFLAG_FN(fn_8014BCF8, fn_80253E8C)
SETFLAG_FN(fn_8014BD24, fn_80253EDC)
SETFLAG_FN(fn_8014BD50, fn_80253E8C)
SETFLAG_FN(fn_8014BD7C, fn_80253EDC)
SETFLAG_FN(fn_8014E3C4, fn_80253E8C)

void fn_8014F2CC(void* a, u8* b) {
    u8 buf[0x80];
    fn_8017714C(buf, b + 0x1c, 0x80);
}

int fn_8014E980(u16 i) {
    int v;
    fn_80253E4C(GW_S16(0x80, i), 8, &v);
    return v == 1;
}

void fn_8014F214(void) {
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(*(u8**)(lbl_8063D578 + 0xd24) + 0x10, 1, b, a, 0, 0);
}

void fn_8014F270(void) {
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(*(u8**)(lbl_8063D578 + 0xd24) + 0x10, 5, b, a, 0, 0);
}

}

extern "C" {

void fn_80253EB4(s16, int, int, int);
int fn_8005A9F8(int);
u16 fn_80253DE0(s16);
u16 fn_80253DD0(s16);
void fn_80059A3C(int, void*);

void fn_8014E730(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 1:
        fn_80253EB4(a, b, 1, fn_8005A9F8(0x1a));
        break;
    }
}

#pragma dont_inline on
void fn_8014E354(s16 a) {
    if (fn_8014E980(0x1e) && fn_80253DE0(a) == 1 && fn_80253DD0(a) == 3) {
        fn_80253DF0(a, 8, 0);
    }
}

void fn_8014E6C0(s16 a) {
    if (fn_8014E980(0x1f) && fn_80253DE0(a) == 3 && fn_80253DD0(a) == 3) {
        fn_80253DF0(a, 8, 0);
    }
}
#pragma dont_inline reset

void fn_8014E79C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 0:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(0x63, buf);
        break;
    }
}

void fn_801495A8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 5:
        fn_80253EB4(a, b, 2, 0x50c4);
        break;
    case 8:
        fn_80253EB4(a, b, 2, 0x50c5);
        break;
    }
}

}

extern "C" {

void fn_8014C50C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    fn_80253EDC(a, b, 6, buf);
    switch (v) {
    case 1:
        fn_80059A3C(0x3d, buf);
        break;
    case 2:
        fn_80059A3C(0x3e, buf);
        break;
    }
}

void fn_8014C2B8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 3:
        fn_80253EB4(a, b, 2, 0x2a40);
        break;
    case 4:
        break;
    case 5:
        fn_80253EB4(a, b, 2, 0x2a41);
        break;
    }
}

void fn_8014E054(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 3:
        fn_80253EB4(a, b, 2, 0x50a9);
        break;
    case 4:
        break;
    case 5:
        fn_80253EB4(a, b, 2, 0x50aa);
        break;
    }
}

void fn_8014C34C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 1:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(1, buf);
        break;
    case 0:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(2, buf);
        break;
    }
}

}

extern "C" {

#define MSG2_FN(name, c0, n0, c1, n1) \
    void name(s16 a, int b) { \
        int v; \
        u8 buf[0x28]; \
        fn_80253EDC(a, b, 3, &v); \
        switch (v) { \
        case c0: \
            fn_80253EDC(a, b, 6, buf); \
            fn_80059A3C(n0, buf); \
            break; \
        case c1: \
            fn_80253EDC(a, b, 6, buf); \
            fn_80059A3C(n1, buf); \
            break; \
        } \
    }

MSG2_FN(fn_8014D9E4, 0, 7, 1, 8)
MSG2_FN(fn_8014DC54, 1, 1, 2, 2)
MSG2_FN(fn_8014E2B4, 0, 7, 1, 8)

#pragma dont_inline on
void fn_8014E80C(int a) {
    if (a) {
        if (fn_8014E980(0x1e)) {
            if (fn_80253DE0(GW_S16(0x80, 0x1e)) == 1) {
                fn_8014E964(0x1e, 1);
                fn_8014E94C(0x1e, 2);
            }
        } else {
            fn_8014E964(0x1e, 1);
            fn_8014E94C(0x1e, 2);
        }
    } else {
        if (fn_8014E980(0x1e)) {
            fn_8014E94C(0x1e, 1);
        }
    }
}

void fn_8014E8AC(int a) {
    if (a) {
        if (fn_8014E980(0x1f)) {
            if (fn_80253DE0(GW_S16(0x80, 0x1f)) == 3) {
                fn_8014E964(0x1f, 1);
                fn_8014E94C(0x1f, 4);
            }
        } else {
            fn_8014E964(0x1f, 1);
            fn_8014E94C(0x1f, 4);
        }
    } else {
        if (fn_8014E980(0x1f)) {
            fn_8014E94C(0x1f, 3);
        }
    }
}
#pragma dont_inline reset

}

extern "C" {

void fn_80253CCC(u16);
void fn_80055E30(void*);
void fn_80253F8C(int);
int fn_802502F4(int);
void fn_8015C308(int, int);

void fn_80149744(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 5:
        fn_80253EB4(a, b, 2, 0x50e8);
        break;
    case 7:
        fn_80253EB4(a, b, 2, 0x50e9);
        break;
    case 9:
        fn_80253EB4(a, b, 2, 0x50ea);
        break;
    }
}

void fn_8013FFB8(void) {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        if (((void**)lbl_8063D578)[(u16)i] != 0) {
            fn_80253CCC(*(u16*)(lbl_8063D578 + (u16)i * 2 + 0x80));
            fn_80055E30(((void**)lbl_8063D578)[(u16)i]);
            GW_S16(0x80, (u16)i) = -1;
            ((void**)lbl_8063D578)[(u16)i] = 0;
        }
    }
    fn_80253F8C(*(int*)(lbl_8063D578 + 0xc0));
    *(int*)(lbl_8063D578 + 0xc0) = -1;
    GSfsys::fn_80249890(0x405);
    GScache::freeFsysCacheEntries(0x405);
}

void fn_8014F164(void) {
    int id;
    switch (*(int*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x10)) {
    case 1000: id = 0x29c6; break;
    case 1001: id = 0x29c7; break;
    case 1002: id = 0x29c8; break;
    case 1003: id = 0x29c9; break;
    case 1004: id = 0x29ca; break;
    case 1005: id = 0x29cb; break;
    case 1006: id = 0x29cc; break;
    case 1007: id = 0x29cd; break;
    case 1008: id = 0x29ce; break;
    case 1009: id = 0x29cf; break;
    default: id = 0x29d0; break;
    }
    fn_8015C308(0xe, fn_802502F4(id));
}

void fn_8014E1EC(int a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 2:
        if (*(u16*)(lbl_8063D578 + 0xf8) == 0) {
            b[2] >>= 2;
            b[3] >>= 2;
            b[4] >>= 2;
        }
        break;
    case 3:
        if (*(u16*)(lbl_8063D578 + 0xf8) + 6 >= *(u16*)(lbl_8063D578 + 0xfc)) {
            b[2] >>= 2;
            b[3] >>= 2;
            b[4] >>= 2;
        }
        break;
    }
}

}

extern "C" {

void fn_8014AAA4(s16 a, int b) {
    u32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (lbl_8063D578[0xd40]) {
    case 1:
        if (v == 7) {
            fn_80253EB4(a, b, 2, 0x510c);
            break;
        }
    case 0:
        switch (v) {
        case 3:
            fn_80253EB4(a, b, 2, 0x510a);
            break;
        case 9:
            fn_80253EB4(a, b, 2, 0x50ab);
            break;
        }
        break;
    }
}

void fn_801497F0(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 1:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(1, buf);
        break;
    case 2:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(2, buf);
        break;
    case 3:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(3, buf);
        break;
    }
}

#define GW_FLAG6() ((*(u32*)(lbl_8063D578 + 0xd30) >> 25) & 1)

void fn_8014A1E8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 10:
        if (GW_FLAG6()) {
            fn_80253EB4(a, b, 2, 0x51a2);
        } else {
            fn_80253EB4(a, b, 2, 0x51a3);
        }
        break;
    case 5:
        if (GW_FLAG6()) {
            fn_80253EB4(a, b, 2, 0x50d1);
        } else {
            fn_80253EB4(a, b, 2, 0x50d0);
        }
        break;
    }
}

}

extern "C" {

void fn_801493A0(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 1: {
        int id = 0;
        switch (*(int*)(lbl_8063D578 + 0xd4)) {
        case 1:
            id = 0x50be;
            break;
        case 2:
            id = 0x50bf;
            break;
        case 3:
            id = 0x50c1;
            break;
        }
        fn_80253EB4(a, b, 2, id);
        break;
    }
    case 9:
    case 10:
    case 13:
    case 14:
        fn_80253EB4(a, b, 2, 0);
        break;
    case 16:
        fn_80253EB4(a, b, 2, 0x50c0);
        break;
    }
}

extern const u16 lbl_80641470;
extern const u16 lbl_80641472;
extern const u16 lbl_80641474;
extern const u16 lbl_80641476;

void fn_8014D8EC(int a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 2:
        if (*(u16*)(lbl_8063D578 + 0xf8) == 0) {
            b[2] >>= 2;
            b[3] >>= 2;
            b[4] >>= 2;
        }
        break;
    case 3: {
        u16 tbl[4] = {lbl_80641470, lbl_80641472, lbl_80641474, lbl_80641476};
        if (*(u16*)(lbl_8063D578 + 0xf8) + tbl[(*(u32*)(lbl_8063D578 + 0xd30) >> 23) & 3] >= *(u16*)(lbl_8063D578 + 0xfc)) {
            b[2] >>= 2;
            b[3] >>= 2;
            b[4] >>= 2;
        }
        break;
    }
    }
}

}

extern "C" {

u16 fn_80250398(int, int, int);
void fn_80250134(int, int, int, int, int, u32);

void fn_8014FC0C(int a, u8* b, int c) {
    u32 color = b[0x11] | 0xFFFFFF00;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 6, buf);
    s16 w = fn_80250398(c, 1, 0);
    s16 width = buf[1] - buf[0];
    s16 height = buf[6] - buf[4];
    fn_80250134(c, buf[0] + (width - w) / 2, buf[4], width, height, color);
}

}

extern "C" {

void fn_8015C4F4(int, int);
void fn_8011F050(void);
void fn_800E7044(void);
void fn_8009FC9C(void);
void fn_80056330(void);
void fn_802502D4(u16);
void fn_800598F8(int, int);
void* memcpy(void*, const void*, u32);

#define GW_D30 (*(u32*)(lbl_8063D578 + 0xd30))

#pragma dont_inline on
void fn_8014E0E8(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 0:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(1, buf);
        break;
    case 1:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(2, buf);
        break;
    }
    if (*(u16*)(lbl_8063D578 + 0xc4) == 0x49 && fn_80253DD0(GW_S16(0x80, 0x1c)) == 3) {
        if (lbl_8063D578[0xefd] == 0) {
            fn_8014E80C(0);
            fn_8014E94C(0x1c, 5);
            *(u16*)(lbl_8063D578 + 0xc4) = 0x4a;
        } else {
            fn_8015C4F4(3, 0x5533);
        }
    }
}

void fn_8014C598(s16 a) {
    int v;
    fn_80253E4C(a, 8, &v);
    if (v != 0 && fn_80253DD0(a) == 3) {
        switch (fn_80253DE0(a)) {
        case 6:
            fn_80253DB0(a, 0, 0);
            break;
        case 7:
            fn_80253DB0(a, 1, 0);
            break;
        case 8:
            fn_80253DB0(a, 2, 0);
            break;
        case 9:
            fn_80253DB0(a, 3, 0);
            break;
        case 10:
            fn_80253DB0(a, 4, 0);
            break;
        case 11:
            fn_80253DB0(a, 5, 0);
            break;
        }
    }
}

void fn_8014E9C8(void) {
    u32 i;
    for (i = 0; i < 0x14; i++) {
        fn_8014E964((u8)i, 0);
    }
    for (i = 0x16; i < 0x20; i++) {
        fn_8014E964((u8)i, 0);
    }
    if ((GW_D30 >> 21) & 1) {
        GW_D30 &= ~0x200000;
        GW_D30 &= ~0x8000000;
        fn_8011F050();
    }
    if ((GW_D30 >> 20) & 1) {
        GW_D30 &= ~0x100000;
        fn_800E7044();
    }
    if ((GW_D30 >> 19) & 1) {
        GW_D30 &= ~0x80000;
        fn_8009FC9C();
        memcpy(*(u8**)(lbl_8063D578 + 0xd28) + 0x8a, lbl_8063D578 + 0xdcc, 0xe);
    }
    fn_80056330();
    if (*(u16*)(lbl_8063D578 + 0xd6c) != 0) {
        fn_802502D4(*(u16*)(lbl_8063D578 + 0xd6c));
        *(u16*)(lbl_8063D578 + 0xd6c) = 0;
    }
    fn_800598F8(0, 0);
}
#pragma dont_inline reset

}

extern "C" {

struct Unk20 {
    u32 w[8];
};
struct Unk28 {
    Unk20 s;
    u32 pad[2];
};
struct UnkColor {
    u8 r, g, b, a;
};

extern const f32 lbl_80641414;
extern const f32 lbl_80641444;
extern const f64 lbl_80641430;
extern const f64 lbl_80641438;

void fn_8000B170(int, int, f32);
void fn_801558F0(void*, void*);
f64 fn_8015F7A0(void);
u32 fn_80059A6C(int, int, int, int);
void fn_800E71B0(int, Unk20);
void fn_802504A0(int, int, int, UnkColor, int, f32);

void fn_80149234(void) {
    u8* g;
    switch (*(u16*)(lbl_8063D578 + 0xc4)) {
    case 0xa4:
        fn_8000B170(0x222, 0, lbl_80641414);
        *(u8**)(lbl_8063D578 + 0xef4) = *(u8**)(lbl_8063D578 + 0xd28) + lbl_8063D578[0xd4a] * 0x8c + 0x21f8;
        fn_801558F0(*(void**)(lbl_8063D578 + 0xef0), *(void**)(lbl_8063D578 + 0xef4));
        g = lbl_8063D578;
        *(f64*)(g + 0xd38) = fn_8015F7A0();
        *(u16*)(g + 0xc4) = 0xa5;
        break;
    case 0xa5:
        fn_801558F0(*(void**)(lbl_8063D578 + 0xef0), *(void**)(lbl_8063D578 + 0xef4));
        g = lbl_8063D578;
        if (fn_8015F7A0() - *(f64*)(g + 0xd38) >= lbl_80641430) {
            if (fn_8015F7A0() - *(f64*)(g + 0xd38) >= lbl_80641438) {
                *(u16*)(g + 0xc4) = 0x9d;
            }
            if (fn_80059A6C(0x80, 0, 0, 1) == 0x80000000) {
                *(u16*)(lbl_8063D578 + 0xc4) = 0x9d;
            }
        }
        break;
    }
}

void fn_80149630(s16 a, int b) {
    int v;
    Unk28 buf;
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 1:
        fn_80253EDC(a, b, 6, &buf);
        fn_80059A3C(1, &buf);
        break;
    case 2:
        fn_80253EDC(a, b, 6, &buf);
        fn_80059A3C(2, &buf);
        break;
    case 4:
        fn_80253EDC(a, b, 6, &buf);
        fn_800E71B0(0, buf.s);
        break;
    }
}

void fn_8014AB70(int a, u8* b) {
    u32 v;
    fn_80253EDC(a, (int)b, 3, &v);
    switch (lbl_8063D578[0xd40]) {
    case 0:
        if (v == 5) {
            u8* g = lbl_8063D578;
            UnkColor col;
            u16 arr[15];
            col.r = 0xff;
            col.g = 0xff;
            col.b = 0xff;
            col.a = b[0x11];
            for (int i = 0; i < 4; i++) {
                arr[i] = ((u16*)(g + 0xd8))[i];
                arr[i + 5] = ((u16*)(g + 0xe0))[i];
                arr[i + 10] = ((u16*)(g + 0xe8))[i];
            }
            arr[4] = 0x2d;
            arr[9] = 0x2d;
            arr[14] = 0;
            fn_8015C308(0xe, (int)arr);
            fn_802504A0(0x510b, 0x140, 0xe6, col, 0x84, lbl_80641444);
        }
        break;
    }
}

}

extern "C" {

void* memset(void*, int, u32);
void fn_8014F748(int);
void fn_802503D8(int, void*);
extern u8 lbl_80487250[];
extern u8 lbl_80487278[];

void fn_8014F488(void) {
    lbl_8063D578[0xdf1] = 0;
    lbl_8063D578[0xdfd] = 0;
    lbl_8063D578[0xedc] = 0;
    lbl_8063D578[0xee2] = 0;
    lbl_8063D578[0xdf2] = 0;
    lbl_8063D578[0xdfe] = 0;
    lbl_8063D578[0xedd] = 0;
    lbl_8063D578[0xee3] = 0;
    lbl_8063D578[0xdf3] = 0;
    lbl_8063D578[0xdff] = 0;
    lbl_8063D578[0xede] = 0;
    lbl_8063D578[0xee4] = 0;
    lbl_8063D578[0xdf4] = 0;
    lbl_8063D578[0xe00] = 0;
    lbl_8063D578[0xedf] = 0;
    lbl_8063D578[0xee5] = 0;
    lbl_8063D578[0xdf5] = 0;
    lbl_8063D578[0xe01] = 0;
    lbl_8063D578[0xee0] = 0;
    lbl_8063D578[0xee6] = 0;
    lbl_8063D578[0xdf6] = 0;
    lbl_8063D578[0xe02] = 0;
    lbl_8063D578[0xee1] = 0;
    lbl_8063D578[0xee7] = 0;
    lbl_8063D578[0xdf7] = 0;
    lbl_8063D578[0xe03] = 0;
    lbl_8063D578[0xdf8] = 0;
    lbl_8063D578[0xe04] = 0;
    memset(lbl_8063D578 + 0xe09, 0, 0x80);
    fn_8014F748(0);
}

#pragma dont_inline on
void fn_80149488(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
    case 4:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(1, buf);
        break;
    case 5:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(2, buf);
        break;
    case 6:
        fn_80253EDC(a, b, 6, buf);
        fn_80059A3C(3, buf);
        break;
    case 10:
        fn_8014FC0C(a, (u8*)b, 0x50bc);
        break;
    case 14:
        fn_8014FC0C(a, (u8*)b, 0x50bd);
        break;
    case 9:
        fn_8014FC0C(a, (u8*)b, 0x51de);
        break;
    case 13:
        fn_8014FC0C(a, (u8*)b, 0x51de);
        break;
    }
}
#pragma dont_inline reset

void fn_8014C3EC(s16 a, u8* b) {
    u8* tmp;
    int v;
    u8* p;
    int id = 0;
    fn_80253E8C(a, (int)b, 3, &v);
    fn_80253E8C(a, (int)b, 5, &tmp);
    p = tmp;
    switch (v) {
    case 6:
        id = 0x4646;
        *(u8**)p = lbl_80487250;
        break;
    case 8:
        id = 0x4647;
        *(u8**)p = lbl_80487278;
        break;
    case 4:
        fn_80253EB4(a, (int)b, 2, 0x5237);
        break;
    }
    if (id != 0) {
        fn_802503D8(id, *(void**)p);
        p[4] = b[2];
        p[5] = b[3];
        p[6] = b[4];
        p[7] = b[5];
        p[9] = 0x84;
        fn_80253EB4(a, (int)b, 2, -2);
    }
}

}

extern "C" {

int fn_80166FB0(int);
int fn_8016704C(int);
int fn_80167098(int);
s64 fn_80166FF4(int);
int fn_80166F64(int);
int fn_80166ED0(int);
u8 fn_800E5410(int);

void fn_8014BDB8(s16 a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 3:
        b[2] >>= 2;
        b[3] >>= 2;
        b[4] >>= 2;
        break;
    case 4:
        fn_80253EB4(a, (int)b, 2, 0x3141);
        break;
    case 5:
        fn_80253EB4(a, (int)b, 2, 0x2a34);
        break;
    case 7:
        fn_80253EB4(a, (int)b, 2, 0x2a32);
        break;
    case 8:
        if (lbl_8063D578[0xd45] == 1) {
            fn_80253EB4(a, (int)b, 2, 0x4636);
        } else {
            fn_80253EB4(a, (int)b, 2, 0x4637);
        }
        break;
    case 11:
        fn_80253EB4(a, (int)b, 2, 0x2a36);
        break;
    }
}

void fn_8014EAD0(void) {
    u16 count = 0;
    int i;
    for (i = 0; i < 0x1e; i++) {
        if (fn_80166FB0(i)) {
            ((int*)(lbl_8063D578 + 0x17c))[count] = fn_8016704C(i);
            ((int*)(lbl_8063D578 + 0x104))[count] = fn_80167098(i);
            ((s64*)(lbl_8063D578 + 0x270))[count] = fn_80166FF4(i);
            ((int*)(lbl_8063D578 + 0x1f4))[count] = fn_80166F64(i);
            ((int*)(lbl_8063D578 + 0x360))[count] = fn_80166ED0(i);
            lbl_8063D578[0x3d8 + count] = fn_800E5410(((int*)(lbl_8063D578 + 0x104))[count]);
            ((int*)(lbl_8063D578 + 0x3f8))[count] = i;
            count++;
        }
    }
    *(u16*)(lbl_8063D578 + 0xf8) = lbl_8063D578[0xd48];
    *(u16*)(lbl_8063D578 + 0xfa) = lbl_8063D578[0xd48];
    *(u16*)(lbl_8063D578 + 0xf8) = 0;
    *(u16*)(lbl_8063D578 + 0xfa) = 0;
    *(u16*)(lbl_8063D578 + 0xfc) = count;
}

}

extern "C" {

u32 fn_801502A0(void*, int, int);

void fn_8014F748(int x) {
    u32 m;
    if (lbl_8063D578[0xdf7] == 3) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (lbl_8063D578[0xdf1 + i] == 7) {
            lbl_8063D578[0xdf1 + i] = 0;
        }
    }
    m = fn_801502A0(*(u8**)(lbl_8063D578 + 0xd28) + 0x1ffc, x, 0xff);
    if (m & 0x04000000) lbl_8063D578[0xdf1] = 7;
    if (m & 0x08000000) lbl_8063D578[0xdf2] = 7;
    if (m & 0x10000000) lbl_8063D578[0xdf3] = 7;
    if (m & 0x20000000) lbl_8063D578[0xdf4] = 7;
    if (m & 0x40000000) lbl_8063D578[0xdf5] = 7;
    if (m & 0x80000000) lbl_8063D578[0xdf6] = 7;
    if (m & 0x400) {
        u8* g = lbl_8063D578;
        if (*(u16*)(*(u8**)(g + 0xd28) + 0x90) == 0) {
            g[0xdf7] = 1;
        } else {
            g[0xdf7] = 2;
        }
    } else {
        lbl_8063D578[0xdf7] = 0;
    }
}

#define SHIFT_RGB(b) \
    b[2] >>= 2; \
    b[3] >>= 2; \
    b[4] >>= 2;

void fn_8014AC84(s16 a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 9:
        fn_80253EB4(a, (int)b, 2, 0x50fb);
        break;
    case 10:
        fn_80253EB4(a, (int)b, 2, 0x50fc);
        break;
    case 12:
        fn_80253EB4(a, (int)b, 2, 0x50fd);
        break;
    case 14:
        fn_80253EB4(a, (int)b, 2, 0x50fe);
        break;
    case 16:
        fn_80253EB4(a, (int)b, 2, 0x50ff);
        break;
    case 18:
        fn_80253EB4(a, (int)b, 2, 0x5100);
        break;
    case 20:
        fn_80253EB4(a, (int)b, 2, 0x5101);
        break;
    case 6:
        if (lbl_8063D578[0xd48] == 0) {
            SHIFT_RGB(b)
        }
        break;
    case 7:
        if (lbl_8063D578[0xd48] == *(u16*)(lbl_8063D578 + 0xfc) - 1) {
            SHIFT_RGB(b)
        }
        break;
    }
}

}

extern "C" {

void fn_800599C8(int, int, int, int, int, int);
extern const f32 lbl_80641450;
extern const f32 lbl_80641454;

void fn_8014FCFC(void) {
    if (((u32*)(lbl_8063D578 + 0xc68))[lbl_8063D578[0xd49]] == 4) {
        fn_800599C8(1, 0, 0, 2, 5, 0);
        fn_800599C8(2, 0, 1, 7, 5, 0);
        fn_800599C8(5, 1, 0, 0x63, 0, 0);
        fn_800599C8(7, 0, 2, 0, 8, 0);
        fn_800599C8(8, 7, 2, 0, 0x63, 0);
        fn_800599C8(0x63, 8, 5, 0, 0, 0);
    } else {
        fn_800599C8(1, 0, 0, 0, 0, 0);
        fn_800599C8(2, 0, 0, 0, 0, 0);
        fn_800599C8(5, 0, 0, 0x63, 0, 0);
        fn_800599C8(7, 0, 0, 0, 8, 0);
        fn_800599C8(8, 7, 0, 0, 0x63, 0);
        fn_800599C8(0x63, 8, 5, 0, 0, 0);
    }
}

void fn_8014BEE4(s16 a, u8* b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
    case 1:
        fn_80253EDC(a, (int)b, 6, buf);
        fn_80059A3C(2, buf);
        break;
    case 2:
        fn_80253EDC(a, (int)b, 6, buf);
        fn_80059A3C(3, buf);
        break;
    case 14: {
        int id = 0;
        fn_80253EDC(a, (int)b, 6, buf);
        int x = buf[0] - lbl_80641450;
        int y = buf[4] - lbl_80641454;
        s16 w = buf[1] - buf[0];
        s16 h = buf[6] - buf[4];
        u32 color = b[0x11] | 0xFFFFFF00;
        switch (*(int*)(lbl_8063D578 + 0xd4)) {
        case 1:
            id = 0x521b;
            break;
        case 2:
            id = 0x2a38;
            break;
        case 3:
            id = 0x521c;
            break;
        case 0x63:
            id = 0x2a57;
            break;
        }
        if (id != 0) {
            fn_80250134(id, x, y, w, h, color);
        }
        break;
    }
    }
}

}

extern "C" {

int fn_80163434(void);
void fn_80168B04(int);
int fn_80165354(void);
void fn_80168100(int, void*);
int fn_80168148(int, void*);

#pragma dont_inline on
int fn_8014F2F8(void) {
    int id;
    memcpy(lbl_8063D578 + 0xd94, *(u8**)(lbl_8063D578 + 0xd28) + 0x8a, 0xe);
    *(u32*)(lbl_8063D578 + 0xd8c) = *(u32*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x10);
    *(u32*)(lbl_8063D578 + 0xd90) = *(u32*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x8);
    *(u16*)(lbl_8063D578 + 0xda2) = *(u32*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x4) >> 28;
    switch (*(u32*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x4) >> 28) {
    case 0:
        id = 0x5531;
        break;
    case 1:
        id = 0x5532;
        break;
    case 2:
        id = 0x5532;
        break;
    default:
        fn_8015C308(0xf, (int)(*(u8**)(lbl_8063D578 + 0xd24) + 0x660e2 + ((*(u32*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x4) >> 28) - 3) * 0x18));
        id = 0x3f9;
        break;
    }
    fn_802503D8(id, lbl_8063D578 + 0xda4);
    *(int*)(lbl_8063D578 + 0xd88) = fn_80163434();
    if (*(int*)(lbl_8063D578 + 0xd88) == 0) {
        (*(int*)(lbl_8063D578 + 0xd88))++;
    }
    fn_80168B04(*(int*)(lbl_8063D578 + 0xd88));
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(*(u8**)(lbl_8063D578 + 0xd24) + 0x10, 4, b, a, (int)(lbl_8063D578 + 0xd88), 0x44);
    fn_8014F2CC(*(void**)(lbl_8063D578 + 0xd88), lbl_8063D578 + 0xd88);
    if (fn_80165354() < 0) {
        fn_8014F214();
        return 0;
    }
    *(u32*)(lbl_8063D578 + 0xd30) |= 0x02000000;
    return 1;
}
#pragma dont_inline reset

void fn_8014F5A4(void) {
    u8* g = lbl_8063D578;
    if (g[0xdf0] == 0) {
        fn_80168100(0, g + 0xdf1);
        lbl_8063D578[0xdf0] = 1;
    }
    if (fn_80168148(0, lbl_8063D578 + 0xdfd)) {
        u8 count = 0;
        u32 i;
        for (i = 0; i < 6; i++) {
            u8 c = lbl_8063D578[0xdfd + i];
            if (c != 0 && c != 7) {
                count++;
            }
        }
        for (u8 j = 0; j < 6; j++) {
            if (j < count) {
                g[0xee2 + j] = 1;
            } else {
                g[0xee2 + j] = 0;
            }
        }
    }
}

}

extern "C" {

u64 fn_80164F58(void);
extern u64 lbl_8041D468[];

void fn_8014DA84(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 5:
        switch (lbl_8063D578[0xd41]) {
        case 2:
            fn_80253EB4(a, b, 2, 0x50c2);
            break;
        case 1:
            fn_80253EB4(a, b, 2, 0x50bb);
            break;
        case 3:
        case 4:
            fn_80253EB4(a, b, 2, 0x50e5);
            break;
        }
        break;
    case 8:
        switch (lbl_8063D578[0xd41]) {
        case 1:
        case 2:
        case 3:
        case 4:
            fn_80253EB4(a, b, 2, 0x50a9);
            break;
        }
        break;
    case 10:
        switch (lbl_8063D578[0xd41]) {
        case 1:
        case 2:
        case 3:
        case 4:
            fn_80253EB4(a, b, 2, 0x50aa);
            break;
        }
        break;
    case 3:
        switch (lbl_8063D578[0xd41]) {
        case 2:
            fn_80253EB4(a, b, 2, 0x516d);
            break;
        case 1:
            fn_80253EB4(a, b, 2, 0x5186);
            break;
        case 3:
            fn_80253EB4(a, b, 2, 0x50e6);
            break;
        case 4:
            fn_80253EB4(a, b, 2, 0x5253);
            break;
        }
        break;
    }
}

int fn_8014EF80(void) {
    u64 val = fn_80164F58();
    if (val != 0) {
        for (u16 i = 0; i < 12; i++) {
            ((u16*)(lbl_8063D578 + 0xd8))[i] = val % lbl_8041D468[i] / lbl_8041D468[i + 1] + 0x30;
        }
        return 1;
    }
    *(u16*)(lbl_8063D578 + 0xd8) = 0;
    return 0;
}

}

extern "C" {

#define GW_C68(i) (((u32*)(lbl_8063D578 + 0xc68))[i])

void fn_80149C0C(s16 a, u8* b) {
    int v;
    u16 idx = 0xffff;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 15:
        if (*(u16*)(lbl_8063D578 + 0xfc) < 2) {
            SHIFT_RGB(b)
        }
        break;
    case 20:
        if (*(u16*)(lbl_8063D578 + 0xfc) < 3) {
            SHIFT_RGB(b)
        }
        break;
    case 25:
        if (*(u16*)(lbl_8063D578 + 0xfc) < 4) {
            SHIFT_RGB(b)
        }
        break;
    case 9:
        idx = *(u16*)(lbl_8063D578 + 0xf8) - 1;
        break;
    case 14:
        idx = *(u16*)(lbl_8063D578 + 0xf8);
        break;
    case 19:
        idx = *(u16*)(lbl_8063D578 + 0xf8) + 1;
        break;
    case 24:
        idx = *(u16*)(lbl_8063D578 + 0xf8) + 2;
        break;
    case 29:
        idx = *(u16*)(lbl_8063D578 + 0xf8) + 3;
        break;
    }
    if (idx < *(u16*)(lbl_8063D578 + 0xfc)) {
        if (GW_C68(idx) != 4) {
            fn_80253EB4(a, (int)b, 1, 0);
        }
    } else if (idx < 4) {
        fn_80253EB4(a, (int)b, 1, 0);
    }
    u8* g = lbl_8063D578;
    if (*(u16*)(g + 0xf8) != *(u16*)(g + 0xfa) && *(u16*)(g + 0x100) == fn_80253DE0(a)) {
        *(u16*)(lbl_8063D578 + 0xf8) = *(u16*)(lbl_8063D578 + 0xfa);
    }
}

void fn_8014A510(s16 a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 3:
        if (GW_C68(lbl_8063D578[0xd49]) == 4) {
            fn_80253EB4(a, (int)b, 2, 0x50df);
        }
        break;
    case 8:
        fn_80253EB4(a, (int)b, 2, 0x50de);
        switch (GW_C68(lbl_8063D578[0xd49])) {
        case 0:
            fn_80253EB4(a, (int)b, 2, 0x51a1);
            break;
        case 1:
            fn_80253EB4(a, (int)b, 2, 0x50ac);
            break;
        case 2:
        case 3:
            fn_80253EB4(a, (int)b, 2, 0x50af);
            break;
        case 4:
            fn_80253EB4(a, (int)b, 2, 0x50ad);
            break;
        case 5:
            fn_80253EB4(a, (int)b, 2, 0x50ae);
            break;
        }
        break;
    case 6:
        if (GW_C68(lbl_8063D578[0xd49]) == 4) {
            if (*(int*)(lbl_8063D578 + lbl_8063D578[0xd49] * 0x44 + 0x478) == 2) {
                fn_80253EB4(a, (int)b, 2, 0x50b3);
            } else {
                fn_80253EB4(a, (int)b, 2, 0x50b4);
            }
        }
        break;
    case 11:
    case 13:
    case 14:
        if (GW_C68(lbl_8063D578[0xd49]) != 4) {
            SHIFT_RGB(b)
        }
        break;
    }
}

}

extern "C" {

void fn_8005B294(s16, int, int);

#define FC_SHIFT(n) \
    if (*(u16*)(lbl_8063D578 + 0xfc) < n) { \
        SHIFT_RGB(b) \
    } \
    break;

void fn_8014B41C(s16 a, u8* b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
    case 4:
        fn_80253EB4(a, (int)b, 2, 0x50e7);
        break;
    case 2:
        fn_80253EB4(a, (int)b, 1, 0);
        break;
    case 9: FC_SHIFT(1)
    case 13: FC_SHIFT(2)
    case 17: FC_SHIFT(3)
    case 21: FC_SHIFT(4)
    case 25: FC_SHIFT(5)
    case 29: FC_SHIFT(6)
    }
    u8* g = lbl_8063D578;
    if (*(u16*)(g + 0xf8) != *(u16*)(g + 0xfa) && *(u16*)(g + 0x100) == fn_80253DE0(a)) {
        *(u16*)(lbl_8063D578 + 0xf8) = *(u16*)(lbl_8063D578 + 0xfa);
    }
}

#define EE8(k) fn_80253EB4(a, b, 1, ((int*)(lbl_8063D578 + 0xee8))[lbl_8063D578[0xee2 + k]]); break;
#define B294(off) fn_8005B294(a, b, *(int*)(lbl_8063D578 + off)); break;

void fn_8014D148(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 2: EE8(0)
    case 3: EE8(1)
    case 4: EE8(2)
    case 5: EE8(3)
    case 6: EE8(4)
    case 7: EE8(5)
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
        fn_80253EB4(a, b, 1, 0);
        break;
    case 57:
        fn_80253EB4(a, b, 2, 0);
        break;
    case 61:
        fn_80253EB4(a, b, 2, 0);
        break;
    case 14: B294(0xea4)
    case 20: B294(0xea8)
    case 26: B294(0xeac)
    case 32: B294(0xeb0)
    case 38: B294(0xeb4)
    case 44: B294(0xeb8)
    }
}

}

extern "C" {

void fn_8014A2C0(s16 a, u8* b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    u32 color;
    int x = buf[0];
    int y = buf[4];
    s16 w = buf[1] - buf[0];
    s16 h = buf[6] - buf[4];
    color = b[0x11] | 0xFFFFFF00;
    switch ((u32)v) {
    case 1:
        fn_8015C308(8, *(u16*)(lbl_8063D578 + 0xfc));
        fn_80250134(0x3ed, x, y, w, h, color);
        break;
    case 3:
        fn_80059A3C(5, buf);
        break;
    case 9:
        fn_8015C308(0xe, (int)(*(u8**)(lbl_8063D578 + 0xd24) + 0x10));
        fn_80250134(0x50da, x, y, w, h, color);
        break;
    case 6:
        if (lbl_8063D578[0xd21] != 1) {
            int id = 0;
            switch (*(int*)(lbl_8063D578 + 0xd1c)) {
            case 0:
                id = 0x50b1;
                break;
            case 1:
                id = 0x50b0;
                break;
            case 4:
                id = 0x50b2;
                break;
            }
            if (id != 0) {
                fn_8015C308(0xe, ((int*)(lbl_8063D578 + 0x17c))[lbl_8063D578[0xd20]]);
                fn_8015C308(0x10, fn_802502F4(id));
                fn_80250134(0x50dc, x + *(s16*)(lbl_8063D578 + 0xd22), y, w, h, color);
            }
            if (!GSrender::sInstance->_unkCondition1()) {
                *(s16*)(lbl_8063D578 + 0xd22) -= 3;
            }
            if (*(s16*)(lbl_8063D578 + 0xd22) < -0x352) {
                *(s16*)(lbl_8063D578 + 0xd22) = 0x352;
                lbl_8063D578[0xd21]++;
            }
        }
        break;
    }
}

}

extern "C" {

extern u16 lbl_8041D438[];
extern u16 lbl_8041D450[];
void fn_8015CC78(int, int, int, int);

void fn_8014E3F0(s16 a, u8* b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
    case 0:
        switch (*(u16*)(lbl_8063D578 + 0xd0)) {
        case 5:
        case 10:
            *(f32*)(b + 0x50) += *(f32*)(b + 0x50) - *(f32*)(b + 0x4c);
            *(f32*)(b + 0x54) += *(f32*)(b + 0x54) - *(f32*)(b + 0x4c);
            break;
        }
        break;
    case 1: {
        u16 id1 = lbl_8041D438[*(u16*)(lbl_8063D578 + 0xd0)];
        u16 id2 = lbl_8041D450[*(u16*)(lbl_8063D578 + 0xd0)];
        switch (*(u16*)(lbl_8063D578 + 0xd0)) {
        case 10:
            fn_8015CC78(lbl_8063D578[0xd48] + 1, 2, 0xe, 1);
            if (((int*)(lbl_8063D578 + 0x104))[lbl_8063D578[0xd48]] == 0) {
                fn_8015C308(0xf, fn_802502F4(0x50f0));
            } else {
                fn_8015C308(0xf, ((int*)(lbl_8063D578 + 0x17c))[lbl_8063D578[0xd48]]);
            }
            break;
        case 3:
            switch (*(int*)(lbl_8063D578 + 0xd4)) {
            case 1:
                id2 = 0x2a3d;
                break;
            case 2:
                id2 = 0x2a3e;
                break;
            case 0x63:
                id2 = 0x2a57;
                break;
            }
            break;
        case 4:
            switch (*(int*)(lbl_8063D578 + 0xd4)) {
            case 1:
                id2 = 0x2a44;
                break;
            case 2:
                id2 = 0x2a45;
                break;
            }
            break;
        case 11: {
            u8* p = *(u8**)(lbl_8063D578 + 0xd28);
            u16 k = *(u16*)(p + 0x90);
            if (k != 0 && k != 7) {
                fn_8015C308(0x17, k);
            } else {
                if (k == 7) {
                    if (*(int*)(p + 8) == 1) {
                        fn_8015C308(0x17, 4);
                    } else {
                        fn_8015C308(0x17, 3);
                    }
                }
                if (*(u16*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x90) == 0) {
                    id1 = 0xe9e;
                }
            }
            break;
        }
        }
        if (id1 != 0) {
            fn_80253EDC(a, (int)b, 6, buf);
            s16 w = buf[1] - buf[0];
            s16 h = buf[6] - buf[4];
            fn_80250134(id1, buf[0], buf[4], w, h, b[0x11] | 0xFFFFFF00);
        }
        if (id2 != 0xffff) {
            fn_8015C4F4(2, id2);
        }
        break;
    }
    }
}

}

extern "C" {

extern u8 lbl_80486D28[];

void fn_8013F044(void) {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        ((int*)lbl_8063D578)[i] = 0;
        ((s16*)(lbl_8063D578 + 0x80))[i] = -1;
    }
    *(int*)(lbl_8063D578 + 0xc0) = -1;
    lbl_8063D578[0xd43] = 1;
    lbl_8063D578[0xd44] = 3;
    lbl_8063D578[0xd45] = 2;
    lbl_8063D578[0xd46] = 1;
    lbl_8063D578[0xd47] = 1;
    lbl_8063D578[0xd48] = 0;
    for (i = 0; i < 14; i++) {
        ((u16*)(lbl_8063D578 + 0xd8))[i] = 0;
        ((u16*)(lbl_8063D578 + 0xd4c))[i] = 0;
    }
    GW_D30 &= ~0x10000000;
    lbl_8063D578[0xd41] = 0;
    lbl_8063D578[0xd42] = 0;
    for (i = 0; i < 6; i++) {
        ((u8**)(lbl_8063D578 + 0xebc))[i] = lbl_80486D28 + i * 0xdc;
    }
    for (i = 0; i < 0x1e; i++) {
        memset(lbl_8063D578 + 0x470 + i * 0x44, 0, 0x44);
        ((u16*)(lbl_8063D578 + 0xce0))[i] = 0x2d;
    }
}

}

extern "C" {

extern const u8 lbl_80641478[];

}

static inline u8* Slots(void) {
    return lbl_8063D578 + 0xdf1;
}

extern "C" {

int fn_8014F8BC(int slot, int sound) {
    int ret = 0;
    u8 cur = *(lbl_8063D578 + 0xdf1 + slot);
    if (cur != 0 && cur != 7) {
        *(lbl_8063D578 + 0xdf1 + slot) = 0;
        ret = 1;
        for (u8 i = 0; i < 6; i++) {
            u8 c = lbl_8063D578[0xdf1 + i];
            if (c != 0 && c != 7 && c >= cur) {
                lbl_8063D578[0xdf1 + i] = c - 1;
            }
        }
        if (sound) {
            fn_8000B170(0x21f, 0, lbl_80641414);
        }
    } else if (cur == 0) {
        u8 n = 1;
        for (int k = 0; k < 6; k++) {
            u8 c = lbl_8063D578[0xdf1 + k];
            if (c != 0 && c != 7) {
                n++;
            }
        }
        *(lbl_8063D578 + 0xdf1 + slot) = n;
        ret = 1;
        if (sound) {
            fn_8000B170(0x21f, 0, lbl_80641414);
        }
    }
    u8 cnt = 0;
    u8 mask = 0;
    for (u8 i = 0; i < 6; i++) {
        u8 c = lbl_8063D578[0xdf1 + i];
        if (c != 0 && c != 7) {
            cnt++;
            mask |= lbl_80641478[i];
        }
    }
    for (u8 i = 0; i < 6; i++) {
        if (i < cnt) {
            lbl_8063D578[0xedc + i] = 1;
        } else {
            lbl_8063D578[0xedc + i] = 0;
        }
    }
    fn_8014F748(mask);
    lbl_8063D578[0xdf0] = 0;
    return ret;
}

}

static inline int GetCur17C(void) {
    return ((int*)(lbl_8063D578 + 0x17c))[lbl_8063D578[0xd49]];
}

extern "C" {

void fn_8014DCF4(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    if (lbl_8063D578[0xd42] == 11 && ((*(u32*)(lbl_8063D578 + 0xd30) >> 22) & 1)) {
        switch (v) {
        case 2:
        case 3:
            return;
        }
    }
    switch (v) {
    case 3:
        switch (lbl_8063D578[0xd42]) {
        case 2:
        case 3:
        case 4:
        case 5:
            fn_80253EB4(a, b, 2, 0x50c6);
            break;
        case 1:
            fn_80253EB4(a, b, 2, 0x50bb);
            break;
        case 6:
        case 8:
        case 9:
            fn_80253EB4(a, b, 2, 0x50cd);
            break;
        case 11:
            fn_80253EB4(a, b, 2, 0x50e5);
            break;
        case 10:
            fn_80253EB4(a, b, 2, 0x50e5);
            break;
        }
        break;
    case 5:
        switch (lbl_8063D578[0xd42]) {
        case 2:
            fn_80253EB4(a, b, 2, 0x50c7);
            break;
        case 3:
            fn_8014F164();
            fn_80253EB4(a, b, 2, 0x50c9);
            break;
        case 4:
            fn_80253EB4(a, b, 2, 0x50cc);
            break;
        case 5:
            fn_80253EB4(a, b, 2, 0x50ca);
            break;
        case 1:
            fn_80253EB4(a, b, 2, 0x518c);
            break;
        case 6:
            fn_80253EB4(a, b, 2, 0x520c);
            break;
        case 9:
            fn_8015C308(0xe, GetCur17C());
            fn_80253EB4(a, b, 2, 0x50ba);
            break;
        case 8:
            fn_8015C308(0xe, (int)(*(u8**)(lbl_8063D578 + 0xd28) + 0x4ecc));
            fn_80253EB4(a, b, 2, 0x50b9);
            break;
        case 11:
            if (*(u16*)(lbl_8063D578 + 0xd80) == 0x50ba) {
                fn_8015C308(0xe, GetCur17C());
            }
            fn_80253EB4(a, b, 2, *(u16*)(lbl_8063D578 + 0xd80));
            break;
        case 10:
            fn_80253EB4(a, b, 2, 0x5129);
            break;
        }
        break;
    case 7:
        switch (lbl_8063D578[0xd42]) {
        case 2:
            fn_80253EB4(a, b, 2, 0x50c8);
            break;
        case 4:
        case 5:
        case 9:
            fn_80253EB4(a, b, 2, 0x516e);
            break;
        case 11:
            fn_80253EB4(a, b, 2, *(u16*)(lbl_8063D578 + 0xd82));
            break;
        case 10:
            fn_80253EB4(a, b, 2, 0x50ab);
            break;
        }
        break;
    case 6:
        switch (lbl_8063D578[0xd42]) {
        case 1:
        case 3:
        case 6:
        case 8:
            fn_80253EB4(a, b, 1, 0);
            break;
        }
        break;
    }
}

}

extern "C" {

u32 fn_801670E4(int);
u32* fn_8016722C(int);

void fn_8014EBFC(int flag) {
    u16 count = 0;
    if (!((GW_D30 >> 26) & 1)) {
        for (int i = 0; i < 0x1e; i++) {
            if (fn_80166FB0(i)) {
                *(int*)(lbl_8063D578 + 0x17c) = fn_8016704C(i);
                *(int*)(lbl_8063D578 + 0x104) = fn_80167098(i);
                *(s64*)(lbl_8063D578 + 0x270) = fn_80166FF4(i);
                *(int*)(lbl_8063D578 + 0x1f4) = fn_80166F64(i);
                *(int*)(lbl_8063D578 + 0x360) = fn_80166ED0(i);
                lbl_8063D578[0x3d8] = fn_800E5410(*(int*)(lbl_8063D578 + 0x104));
                GW_C68(0) = 0;
                memset(lbl_8063D578 + 0x470, 0, 0x44);
            }
        }
        *(u16*)(lbl_8063D578 + 0xfc) = 0;
        return;
    }
    u8 sel = 0xff;
    for (int i = 0; i < 0x1e; i++) {
        if (fn_80166FB0(i)) {
            int skip = 0;
            switch (fn_801670E4(i)) {
            case 0:
                if (GW_C68(count) != fn_801670E4(i)) {
                    sel = count;
                }
                break;
            case 1:
                if (GW_C68(count) == 0) {
                    sel = count;
                }
                break;
            case 4:
                if (GW_C68(count) != fn_801670E4(i)) {
                    u32* p = fn_8016722C(i);
                    u32 first = *(u32*)(lbl_8063D578 + count * 0x44 + 0x470);
                    if (*p == first) {
                        skip = 1;
                    } else if (first == 0 && ((u16*)(lbl_8063D578 + 0xce0))[count] != 0) {
                        ((u16*)(lbl_8063D578 + 0xce0))[count]--;
                        skip = 1;
                    } else {
                        sel = count;
                    }
                }
                break;
            }
            if (skip) {
                count++;
                continue;
            }
            GW_C68(count) = fn_801670E4(i);
            ((int*)(lbl_8063D578 + 0x17c))[count] = fn_8016704C(i);
            ((int*)(lbl_8063D578 + 0x104))[count] = fn_80167098(i);
            ((s64*)(lbl_8063D578 + 0x270))[count] = fn_80166FF4(i);
            ((int*)(lbl_8063D578 + 0x1f4))[count] = fn_80166F64(i);
            ((int*)(lbl_8063D578 + 0x360))[count] = fn_80166ED0(i);
            lbl_8063D578[0x3d8 + count] = fn_800E5410(((int*)(lbl_8063D578 + 0x104))[count]);
            ((int*)(lbl_8063D578 + 0x3f8))[count] = i;
            if (GW_C68(count) == 4) {
                memcpy(lbl_8063D578 + count * 0x44 + 0x470, fn_8016722C(i), 0x44);
            }
            count++;
        }
    }
    if (flag) {
        if (sel != 0xff) {
            lbl_8063D578[0xd20] = sel;
            lbl_8063D578[0xd21] = 0;
            *(s16*)(lbl_8063D578 + 0xd22) = 0x352;
            *(u32*)(lbl_8063D578 + 0xd1c) = GW_C68(sel);
            fn_8000B170(0x25f, 0, lbl_80641414);
        }
    } else {
        lbl_8063D578[0xd21] = 1;
    }
    *(u16*)(lbl_8063D578 + 0xfc) = count;
}

}

extern "C" {

extern const f32 lbl_80641440;

struct Entry44 {
    u8 data[0x44];
};

void fn_8014A71C(s16 a, u8* b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    u32 color;
    int x = buf[0];
    int y = buf[4];
    s16 w = buf[1] - buf[0];
    s16 h = buf[6] - buf[4];
    color = b[0x11] | 0xFFFFFF00;
    switch ((u32)v) {
    case 12:
        if (GW_C68(lbl_8063D578[0xd49]) != 4) {
            color = b[0x11] | 0x7f7f7f00;
        }
        fn_80250134(0x50e3, x, y, w, h, color);
        break;
    case 15:
        if (GW_C68(lbl_8063D578[0xd49]) != 4) {
            color = b[0x11] | 0x7f7f7f00;
        }
        fn_80250134(0x50e4, x, y, w, h, color);
        break;
    case 1:
        if (GW_C68(lbl_8063D578[0xd49]) != 4) {
            buf[7] = lbl_80641440;
            buf[6] = lbl_80641440;
            buf[5] = lbl_80641440;
            buf[4] = lbl_80641440;
            buf[3] = lbl_80641440;
            buf[2] = lbl_80641440;
            buf[1] = lbl_80641440;
            buf[0] = lbl_80641440;
        }
        fn_80059A3C(1, buf);
        break;
    case 2:
        if (GW_C68(lbl_8063D578[0xd49]) != 4) {
            buf[7] = lbl_80641440;
            buf[6] = lbl_80641440;
            buf[5] = lbl_80641440;
            buf[4] = lbl_80641440;
            buf[3] = lbl_80641440;
            buf[2] = lbl_80641440;
            buf[1] = lbl_80641440;
            buf[0] = lbl_80641440;
        }
        fn_80059A3C(2, buf);
        break;
    case 4:
        if (GW_C68(lbl_8063D578[0xd49]) == 4) {
            int id;
            memset(lbl_8063D578 + 0xefe, 0, 0x28);
            switch (*(u16*)(lbl_8063D578 + lbl_8063D578[0xd49] * 0x44 + 0x48a)) {
            case 0:
                id = 0x3069;
                break;
            case 1:
                id = 0x306a;
                break;
            case 2:
                id = 0x306b;
                break;
            default:
                fn_8015C308(0xf, (int)(lbl_8063D578 + 0x48c + lbl_8063D578[0xd49] * 0x44));
                id = 0x3f9;
                break;
            }
            fn_802503D8(id, lbl_8063D578 + 0xefe);
            fn_8015C308(0xe, (int)(lbl_8063D578 + 0xefe));
            fn_80250134(0x50dd, x, y, w, h, color);
        }
        break;
    case 5:
        if (GW_C68(lbl_8063D578[0xd49]) == 4) {
            int saved = *(int*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x10);
            *(int*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x10) = *(int*)(lbl_8063D578 + lbl_8063D578[0xd49] * 0x44 + 0x474);
            fn_8014F164();
            fn_80250134(0x50dd, x, y, w, h, color);
            *(int*)(*(u8**)(lbl_8063D578 + 0xd28) + 0x10) = saved;
        }
        break;
    case 7:
        if (((int*)(lbl_8063D578 + 0x104))[lbl_8063D578[0xd49]] == 0) {
            fn_80250134(0x50f0, x, y, w, h, color);
        } else {
            fn_8015C308(0xe, ((int*)(lbl_8063D578 + 0x17c))[lbl_8063D578[0xd49]]);
            fn_80250134(0x50dd, x, y, w, h, color);
        }
        break;
    }
}

}

extern "C" {

void fn_80253F04(s16, int, int, int);

#define GW_F8 (*(u16*)(lbl_8063D578 + 0xf8))
#define GW_FC (*(u16*)(lbl_8063D578 + 0xfc))
#define DRAW(id) fn_80250134(id, x, y, w, h, color)

void fn_80149E18(s16 a, u8* b) {
    u32 color;
    int x;
    int y;
    s16 w;
    s16 h;
    u16 idxA = 0xffff;
    u16 idxB = idxA;
    u16 idxC = idxA;
    int flag = 0;
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    x = buf[0];
    y = buf[4];
    w = buf[1] - buf[0];
    h = buf[6] - buf[4];
    color = b[0x11] | 0xFFFFFF00;
    switch ((u32)v) {
    case 1: fn_80059A3C(1, buf); break;
    case 2: fn_80059A3C(2, buf); break;
    case 3: fn_80059A3C(3, buf); break;
    case 4: fn_80059A3C(4, buf); break;
    case 7: idxA = GW_F8 - 1; break;
    case 12: idxA = GW_F8; break;
    case 17: idxA = GW_F8 + 1; break;
    case 22: idxA = GW_F8 + 2; break;
    case 27: idxA = GW_F8 + 3; break;
    case 6: flag = 1; idxB = GW_F8 - 1; break;
    case 11: flag = 1; idxB = GW_F8; break;
    case 16: flag = 1; idxB = GW_F8 + 1; break;
    case 21: flag = 1; idxB = GW_F8 + 2; break;
    case 26: flag = 1; idxB = GW_F8 + 3; break;
    case 8: idxC = GW_F8 - 1; break;
    case 13: idxC = GW_F8; break;
    case 18: idxC = GW_F8 + 1; break;
    case 23: idxC = GW_F8 + 2; break;
    case 28: idxC = GW_F8 + 3; break;
    }
    if (idxA < GW_FC) {
        if (((int*)(lbl_8063D578 + 0x104))[idxA] == 0) {
            DRAW(0x50f0);
        } else {
            fn_8015C308(0xe, ((int*)(lbl_8063D578 + 0x17c))[idxA]);
            DRAW(0x50d2);
        }
    }
    if (flag && idxB >= GW_FC) {
        fn_80253F04(a, (int)b, 2, 0);
    }
    if (idxC < GW_FC) {
        switch (GW_C68(idxC)) {
        case 0: DRAW(0x51a1); break;
        case 1: DRAW(0x50ac); break;
        case 2:
        case 3: DRAW(0x50af); break;
        case 4: DRAW(0x50ad); break;
        case 5: DRAW(0x50ae); break;
        }
    }
}

}

extern "C" {

extern const f32 lbl_80641460;
extern const f32 lbl_80641464;
extern const f32 lbl_80641468;
extern const f32 lbl_8064146C;
void fn_8012D530(int, void*, u8);
void fn_8012D640(int, void*, u8, int);
void fn_8005B328(s16, u8*, int, int);

#define F32AT(p, off) (*(f32*)((p) + (off)))
#define GWI(off) (*(int*)(lbl_8063D578 + (off)))

#pragma dont_inline on
void fn_8014CD2C(s16 a, u8* b) {
    u8 c;
    u32 color;
    int x;
    int y;
    s16 w;
    s16 h;
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
    case 14:
    case 20:
    case 26:
    case 32:
    case 38:
    case 44:
        F32AT(b, 0x38) -= lbl_80641460;
        F32AT(b, 0x44) -= lbl_80641460;
        F32AT(b, 0x3c) -= lbl_80641464;
        F32AT(b, 0x40) -= lbl_80641464;
        F32AT(b, 0x48) += lbl_80641468;
        F32AT(b, 0x4c) += lbl_80641468;
        break;
    }
    fn_80253EDC(a, (int)b, 6, buf);
    x = buf[0];
    y = buf[4];
    w = buf[1] - buf[0];
    h = buf[6] - buf[4];
    c = b[0x11];
    color = c | 0xFFFFFF00;
    if (fn_8014E980(0x16)) {
        switch (v) {
        case 51:
        case 52:
        case 53:
        case 54:
        case 55:
        case 56:
            return;
        }
    }
    switch (v) {
    case 57:
        F32AT(b, 0x38) += lbl_8064146C;
        F32AT(b, 0x3c) += lbl_8064146C;
        F32AT(b, 0x40) += lbl_8064146C;
        F32AT(b, 0x44) += lbl_8064146C;
        break;
    case 8:
        fn_8015C308(0xf, GWI(0xed4));
        DRAW(0x3f9);
        break;
    case 10: fn_8012D530(GWI(0xe8c), buf, c); break;
    case 16: fn_8012D530(GWI(0xe90), buf, c); break;
    case 22: fn_8012D530(GWI(0xe94), buf, c); break;
    case 28: fn_8012D530(GWI(0xe98), buf, c); break;
    case 34: fn_8012D530(GWI(0xe9c), buf, c); break;
    case 40: fn_8012D530(GWI(0xea0), buf, c); break;
    case 11: fn_8012D640(GWI(0xe8c), buf, c, 1); break;
    case 17: fn_8012D640(GWI(0xe90), buf, c, 1); break;
    case 23: fn_8012D640(GWI(0xe94), buf, c, 1); break;
    case 29: fn_8012D640(GWI(0xe98), buf, c, 1); break;
    case 35: fn_8012D640(GWI(0xe9c), buf, c, 1); break;
    case 41: fn_8012D640(GWI(0xea0), buf, c, 1); break;
    case 13: fn_8005B328(a, b, GWI(0xe8c), 0); break;
    case 19: fn_8005B328(a, b, GWI(0xe90), 0); break;
    case 25: fn_8005B328(a, b, GWI(0xe94), 0); break;
    case 31: fn_8005B328(a, b, GWI(0xe98), 0); break;
    case 37: fn_8005B328(a, b, GWI(0xe9c), 0); break;
    case 43: fn_8005B328(a, b, GWI(0xea0), 0); break;
    case 51: fn_80059A3C(0x33, buf); break;
    case 52: fn_80059A3C(0x34, buf); break;
    case 53: fn_80059A3C(0x35, buf); break;
    case 54: fn_80059A3C(0x36, buf); break;
    case 55: fn_80059A3C(0x37, buf); break;
    case 56: fn_80059A3C(0x38, buf); break;
    }
}
#pragma dont_inline reset

}

extern "C" {

int fn_8005AC60(int, int);
extern int lbl_8041DC78[];

#define EE8B(k) fn_80253EB4(a, b, 1, ((int*)(lbl_8063D578 + 0xee8))[lbl_8063D578[0xedc + k]]); break;
#define SLOT_EMPTY(k) \
    if (lbl_8063D578[0xdf1 + k] == 0 || lbl_8063D578[0xdf1 + k] == 7) { \
        fn_80253EB4(a, b, 1, 0); \
    } \
    break;
#define SLOT_NAME(k) { \
    u8 c = lbl_8063D578[0xdf1 + k]; \
    if (c != 0 && c != 7) { \
        fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1])); \
    } \
    break; }

void fn_8014C6A0(s16 a, int b) {
    u32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
    case 2: EE8B(0)
    case 3: EE8B(1)
    case 4: EE8B(2)
    case 5: EE8B(3)
    case 6: EE8B(4)
    case 7: EE8B(5)
    case 45: SLOT_EMPTY(0)
    case 46: SLOT_EMPTY(1)
    case 47: SLOT_EMPTY(2)
    case 48: SLOT_EMPTY(3)
    case 49: SLOT_EMPTY(4)
    case 50: SLOT_EMPTY(5)
    case 57: {
        int id = 0;
        switch (lbl_8063D578[0xdf7]) {
        case 0:
        case 1:
            switch ((lbl_8063D578 + lbl_8063D578[0xd4a])[0xdf1]) {
            case 0:
                id = 0x2a68;
                break;
            case 7:
                id = 0;
                break;
            default:
                id = 0x2a69;
                break;
            }
            break;
        }
        fn_80253EB4(a, b, 2, id);
        break;
    }
    case 58:
        switch (lbl_8063D578[0xdf7]) {
        case 0:
        case 1:
            switch (lbl_8063D578[0xefa]) {
            case 0:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3d));
                break;
            case 1:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3e));
                break;
            case 2:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3c));
                break;
            }
            break;
        }
        break;
    case 59:
        if (lbl_8063D578[0xdf7] == 1) {
            fn_80253EB4(a, b, 2, 0x2a6b);
        }
        break;
    case 60:
        if (lbl_8063D578[0xdf7] == 1) {
            switch (lbl_8063D578[0xefa]) {
            case 0:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3e));
                break;
            case 1:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3d));
                break;
            default:
                fn_80253EB4(a, b, 1, fn_8005A9F8(0x3b));
                break;
            }
        }
        break;
    case 12: SLOT_NAME(0)
    case 18: SLOT_NAME(1)
    case 24: SLOT_NAME(2)
    case 30: SLOT_NAME(3)
    case 36: SLOT_NAME(4)
    case 42: SLOT_NAME(5)
    case 14: B294(0xe8c)
    case 20: B294(0xe90)
    case 26: B294(0xe94)
    case 32: B294(0xe98)
    case 38: B294(0xe9c)
    case 44: B294(0xea0)
    }
}

}

extern "C" {

int fn_8015F6E0(void);
int fn_8011C974(void);
u8* fn_8015F690(void);
int fn_80055D98(int, int);
s16 fn_80253C38(int, void*, void*, void*, int, int, int, int);
int fn_80253F6C(int, void*, int);
void fn_800576B0(void);
void fn_80162FD4(void);
void fn_8016532C(void);
void fn_800579FC(int);
void fn_800562BC(void);
void fn_80162940(int, int, int);
void fn_800563EC(int, int);
extern const f32 lbl_80641410;
void fn_8014AE08(void);
void fn_8014B634(s16, u8*);
void fn_8014C078(void);
void fn_8014D370(void);
void fn_8014999C(void);

#pragma dont_inline on
void fn_8013F31C(void) {
    GWI(0xd24) = fn_8015F6E0();
    GWI(0xd28) = fn_8011C974();
    lbl_8063D578[0xefa] = *(int*)(fn_8015F690() + 0x4c);
    GSfsys::loadFsys(0x404);
    GSfsys::loadFsys(0x405);
    GWI(0x0) = fn_80055D98(0x404, 0x23831a00);
    GWI(0x4) = fn_80055D98(0x404, 0x23841a00);
    GWI(0x8) = fn_80055D98(0x404, 0x23851a00);
    GWI(0xc) = fn_80055D98(0x404, 0x23861a00);
    GWI(0x10) = fn_80055D98(0x404, 0x23871a00);
    GWI(0x14) = fn_80055D98(0xe, 0x23881a00);
    GWI(0x18) = fn_80055D98(0xe, 0x23891a00);
    GWI(0x1c) = fn_80055D98(0x404, 0x238a1a00);
    GWI(0x20) = fn_80055D98(0x404, 0x238b1a00);
    GWI(0x28) = fn_80055D98(0x404, 0x238c1a00);
    GWI(0x2c) = fn_80055D98(0x404, 0x238d1a00);
    GWI(0x30) = fn_80055D98(0x404, 0x238e1a00);
    GWI(0x34) = fn_80055D98(0x404, 0x238f1a00);
    GWI(0x38) = fn_80055D98(0x404, 0x23901a00);
    GWI(0x3c) = fn_80055D98(0x404, 0x23911a00);
    GWI(0x40) = fn_80055D98(0x404, 0x23921a00);
    GWI(0x44) = fn_80055D98(0x404, 0x23961a00);
    GWI(0x48) = fn_80055D98(0x404, 0x272d1a00);
    GWI(0x4c) = fn_80055D98(0x404, 0x272d1a00);
    GWI(0x58) = fn_80055D98(0x404, 0x27bb1a00);
    GWI(0x5c) = fn_80055D98(0x404, 0x27981a00);
    GWI(0x60) = fn_80055D98(0x404, 0x27991a00);
    GWI(0x64) = fn_80055D98(0xe, 0x44f1a00);
    GWI(0x68) = fn_80055D98(0x404, 0x27531a00);
    GWI(0x6c) = fn_80055D98(0x404, 0x27331a00);
    GWI(0x70) = fn_80055D98(0xe, 0x4501a00);
    GWI(0x74) = fn_80055D98(0xe, 0x44f1a00);
    GWI(0x78) = fn_80055D98(0xe, 0x19a51a00);
    GWI(0x7c) = fn_80055D98(0xe, 0x44e1a00);
    *(s16*)(lbl_8063D578 + 0x8e) = fn_80253C38(GWI(0x1c), 0, (void*)fn_80149C0C, (void*)fn_80149E18, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xbc) = fn_80253C38(GWI(0x78), (void*)fn_8014E354, (void*)fn_8014E3C4, (void*)fn_8014E3F0, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x80) = fn_80253C38(GWI(0x0), 0, (void*)fn_80149348, (void*)fn_80149374, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x82) = fn_80253C38(GWI(0x4), 0, (void*)fn_801493A0, (void*)fn_80149488, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x84) = fn_80253C38(GWI(0x8), 0, (void*)fn_801495A8, (void*)fn_80149630, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x86) = fn_80253C38(GWI(0xc), 0, (void*)fn_80149744, (void*)fn_801497F0, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x88) = fn_80253C38(GWI(0x10), 0, (void*)fn_801498C0, (void*)fn_801498EC, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x8a) = fn_80253C38(GWI(0x14), 0, (void*)fn_80149918, (void*)fn_80149944, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x90) = fn_80253C38(GWI(0x20), 0, (void*)fn_8014A1E8, (void*)fn_8014A2C0, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x94) = fn_80253C38(GWI(0x28), 0, (void*)fn_8014A510, (void*)fn_8014A71C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x96) = fn_80253C38(GWI(0x2c), 0, (void*)fn_8014AAA4, (void*)fn_8014AB70, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x98) = fn_80253C38(GWI(0x30), 0, (void*)fn_8014AC84, (void*)fn_8014AE08, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x9a) = fn_80253C38(GWI(0x34), 0, (void*)fn_8014B41C, (void*)fn_8014B634, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x9c) = fn_80253C38(GWI(0x38), 0, (void*)fn_8014BCA0, (void*)fn_8014BCCC, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x9e) = fn_80253C38(GWI(0x3c), 0, (void*)fn_8014BCF8, (void*)fn_8014BD24, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xa0) = fn_80253C38(GWI(0x40), 0, (void*)fn_8014BD50, (void*)fn_8014BD7C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xa2) = fn_80253C38(GWI(0x44), (void*)fn_8014BDA8, (void*)fn_8014BDB8, (void*)fn_8014BEE4, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xa4) = fn_80253C38(GWI(0x48), 0, (void*)fn_8014C074, (void*)fn_8014C078, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xa6) = fn_80253C38(GWI(0x4c), 0, (void*)fn_8014C2B8, (void*)fn_8014C34C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xae) = fn_80253C38(GWI(0x5c), (void*)fn_8014C598, (void*)fn_8014C6A0, (void*)fn_8014CD2C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xb0) = fn_80253C38(GWI(0x60), 0, (void*)fn_8014D148, (void*)fn_8014D370, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xac) = fn_80253C38(GWI(0x58), 0, (void*)fn_8014C3EC, (void*)fn_8014C50C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xb2) = fn_80253C38(GWI(0x64), 0, (void*)fn_8014D8EC, (void*)fn_8014D9E4, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xb4) = fn_80253C38(GWI(0x68), 0, (void*)fn_8014DA84, (void*)fn_8014DC54, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xb6) = fn_80253C38(GWI(0x6c), 0, (void*)fn_8014DCF4, (void*)fn_8014E050, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xb8) = fn_80253C38(GWI(0x70), 0, (void*)fn_8014E054, (void*)fn_8014E0E8, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xba) = fn_80253C38(GWI(0x74), 0, (void*)fn_8014E1EC, (void*)fn_8014E2B4, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0xbe) = fn_80253C38(GWI(0x7c), (void*)fn_8014E6C0, (void*)fn_8014E730, (void*)fn_8014E79C, -1, 0, 1, 0);
    *(s16*)(lbl_8063D578 + 0x8c) = fn_80253C38(GWI(0x18), 0, (void*)fn_80149970, (void*)fn_8014999C, -1, 0, 1, 0);
    fn_80253DF0(*(s16*)(lbl_8063D578 + 0x8c), 9, 2);
    fn_80253E10(*(s16*)(lbl_8063D578 + 0xb2), lbl_80641410, 4);
    GWI(0xc0) = fn_80253F6C(0, (void*)fn_80149234, -1);
    GSfsys::fn_80249890(0x404);
    GScache::freeFsysCacheEntries(0x404);
    fn_800576B0();
    GW_D30 &= ~0x200000;
    GW_D30 &= ~0x100000;
    GW_D30 &= ~0x80000;
    switch (fn_80162A90(0x25e)) {
    case 1:
        *(u16*)(lbl_8063D578 + 0xc4) = 1;
        *(u16*)(lbl_8063D578 + 0xc6) = 0;
        memset(*(u8**)(lbl_8063D578 + 0xd28) + 0xd3e0, 0, 0x6ec);
        memset(*(u8**)(lbl_8063D578 + 0xd28) + 0xccf4, 0, 0x6ec);
        memset(*(u8**)(lbl_8063D578 + 0xd28) + 0xc608, 0, 0x6ec);
        GW_D30 &= ~0x10000000;
        fn_80162FD4();
        break;
    case 2:
        *(u16*)(lbl_8063D578 + 0xc4) = 0xa6;
        break;
    case 5:
        if (fn_80162A90(0x262) == 0) {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x18;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x29;
        }
        break;
    case 6:
        if (fn_80162A90(0x262) == 0) {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x22;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x29;
        }
        break;
    case 7:
        *(u16*)(lbl_8063D578 + 0xc4) = 0x22;
        *(u16*)(lbl_8063D578 + 0xc6) = 5;
        lbl_8063D578[0xdda] = 0;
        break;
    case 8:
        if (fn_80162A90(0x262) == 0) {
            GW_D30 |= 0x8000;
            *(u16*)(lbl_8063D578 + 0xc4) = 0x6c;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x77;
        }
        break;
    case 9:
        if (fn_80162A90(0x262) == 0) {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x70;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x77;
        }
        break;
    case 10:
        if (fn_80162A90(0x262) == 0) {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x5c;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x81;
        }
        break;
    case 11:
        if (fn_80162A90(0x262) == 0) {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x7a;
        } else {
            *(u16*)(lbl_8063D578 + 0xc4) = 0x81;
        }
        break;
    case 12:
        fn_8016532C();
        fn_8014F214();
        *(u16*)(lbl_8063D578 + 0xc6) = 5;
        *(u16*)(lbl_8063D578 + 0xc4) = 0x50;
        lbl_8063D578[0xddb] = 0;
        lbl_8063D578[0xdda] = GW_FLAG6() ? 2 : 0;
        break;
    case 13:
        break;
    }
    fn_800579FC(3);
    GW_D30 &= ~0x80000000;
    fn_800562BC();
    fn_80162940(0x261, 4, 1);
    fn_800563EC(0xe, 0);
    GW_D30 &= ~0x08000000;
}
#pragma dont_inline reset

}

extern "C" {

void fn_8014B634(s16 a, u8* b) {
    u16 idxA = 0xffff;
    u16 idxB = idxA;
    u16 idxC = idxA;
    u32 v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
    case 2: {
        u32 color;
        int x;
        int y;
        s16 w;
        s16 h;
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        color = b[0x11] | 0xFFFFFF00;
        if (GW_FC != 0) {
            fn_8015C308(0x1b, GW_F8 + *(u16*)(lbl_8063D578 + 0x102));
        } else {
            fn_8015C308(0x1b, 0);
        }
        fn_8015C308(0x1c, GW_FC);
        DRAW(0x43e3);
        break;
    }
    case 33: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(1, buf); break;
    case 34: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(2, buf); break;
    case 35: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(3, buf); break;
    case 36: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(4, buf); break;
    case 37: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(5, buf); break;
    case 38: fn_80253EDC(a, (int)b, 6, buf); fn_80059A3C(6, buf); break;
    case 6: idxA = GW_F8 - 1; break;
    case 10: idxA = GW_F8; break;
    case 14: idxA = GW_F8 + 1; break;
    case 18: idxA = GW_F8 + 2; break;
    case 22: idxA = GW_F8 + 3; break;
    case 26: idxA = GW_F8 + 4; break;
    case 30: idxA = GW_F8 + 5; break;
    case 7: idxB = GW_F8 - 1; break;
    case 11: idxB = GW_F8; break;
    case 15: idxB = GW_F8 + 1; break;
    case 19: idxB = GW_F8 + 2; break;
    case 23: idxB = GW_F8 + 3; break;
    case 27: idxB = GW_F8 + 4; break;
    case 31: idxB = GW_F8 + 5; break;
    case 8: idxC = GW_F8 - 1; break;
    case 12: idxC = GW_F8; break;
    case 16: idxC = GW_F8 + 1; break;
    case 20: idxC = GW_F8 + 2; break;
    case 24: idxC = GW_F8 + 3; break;
    case 28: idxC = GW_F8 + 4; break;
    case 32: idxC = GW_F8 + 5; break;
    }
    if (idxA < GW_FC) {
        u32 color;
        int x;
        int y;
        s16 w;
        s16 h;
        color = b[0x11] | 0xFFFFFF00;
        if (((int*)(lbl_8063D578 + 0x104))[idxA] == 0) {
            color = b[0x11] | 0xffcf5f00;
        }
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        fn_8015CC78(idxA + 1, 2, 0xe, 1);
        DRAW(0x50ec);
        fn_80250134(0x50ed, x + 0x26, y, w, h, color);
    }
    if (idxB < GW_FC) {
        int x;
        int y;
        s16 w;
        s16 h;
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        u8 c = b[0x11];
        if (((int*)(lbl_8063D578 + 0x104))[idxB] == 0) {
            fn_80250134(0x50f0, x, y, w, h, c | 0xffcf5f00);
        } else {
            fn_8015C308(0xe, ((int*)(lbl_8063D578 + 0x17c))[idxB]);
            fn_80250134(0x50ee, x, y, w, h, c | 0xFFFFFF00);
        }
    }
    if (idxC < GW_FC) {
        u32 color;
        int x;
        int y;
        s16 w;
        s16 h;
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        u8 c = b[0x11];
        if (((int*)(lbl_8063D578 + 0x104))[idxC] == 0) {
            fn_80250134(0x50f8, x, y, w, h, c | 0xffcf5f00);
        } else {
            color = c | 0xFFFFFF00;
            if (((int*)(lbl_8063D578 + 0x1f4))[idxC] == 0) {
                DRAW(0x50f9);
            } else {
                fn_8015C308(0x18, ((int*)(lbl_8063D578 + 0x1f4))[idxC]);
                DRAW(0x50ef);
            }
        }
    }
}

}
