#include ".unsorted/80263CBC.hpp"

#include "common.hpp"

extern "C" {

s32 fn_80263D18(void) { return 300; }
s32 fn_80263D20(void) { return 40; }
s32 fn_80264414(void) { return 0; }
s32 fn_802644CC(void) { return -1; }
u32 fn_802644D4(u8 *p) { return *(u32 *)(p + 0x3c50); }
u32 fn_80264614(u8 *p) { return *(u32 *)(p + 0x3c38); }
void fn_80266F3C(u8 *p, u32 v) { *(u32 *)(p + 0x3d18) = v; }
u32 fn_80267034(u8 *p) { return *(u32 *)(p + 0x3388); }
s32 fn_802670F8(void) { return 1020; }
s32 fn_802672E0(void) { return -1; }
void fn_80267374(void) {}
void fn_802673B4(void) {}
void fn_802673B8(u8 *p) {}

}

#include "common.hpp"

extern "C" {

void fn_8025E47C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_802643F8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025E47C(a1, a1, a2, a3, a4, a5, a6, a7); }
BOOL fn_802644DC(u8 *p) { return *(u32 *)(p + 0x3c38) != 0; }
BOOL fn_802644F0(u8 *p) { return *(u32 *)(p + 0x3c70) != 0; }
void fn_80266FBC(u8 *p) { *(u32 *)(p + 0x3d18) = 0x0; }

}

// Wi-Fi network manager
#define F32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F16(p, o) (*(u16 *)((u8 *)(p) + (o)))

struct WifiVObj {
    virtual void v00();
    virtual void v01();
    virtual void v02(); // 0x10
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual s32 v06();
    virtual void v07();
    virtual s32 v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(); // 0x3c
    virtual void v14();
    virtual s32 v15();
    virtual void v16();
    virtual void v17();
    virtual u8 v18(); // 0x50
    virtual u16 v19();
    virtual s32 v20(u32);
    virtual s32 v21(void *, u32, u8);
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
};

extern "C" {

extern s32 lbl_8063FA10;
extern s32 lbl_8063FA14;
extern s32 lbl_8063FA18;
extern char lbl_80425E60[];
extern char lbl_804263E0[];
extern char lbl_804263F0[];
extern char lbl_804263FC[];

void fn_8031D4B0(void *);
void fn_8031D51C(void *);
void fn_8031D510(void *);
void fn_8031E014(void);
char *fn_8025E4E8(void);
int sprintf(char *, const char *, ...);
void *memset(void *, int, unsigned long);
s32 fn_8031C4A4(s32 *, s32 *);
void fn_8025E4D0(u32);
s32 fn_80322E74(void);
s32 fn_80267098(u8 *);
u32 fn_80266660(u8 *);
void fn_8031C890(void);
void fn_8031C598(s32, char *, u32, void *, void *);
void fn_8031CB2C(s32);
void fn_802676B4(u8 *, s32);
s32 fn_8025BDA4(void);
void fn_8025BEB4(void);
s32 fn_8025BD9C(void);
s32 fn_802F4D18(void);
u32 fn_802F4FE8(s32, s32);
void fn_802672E8(u8 *);
s32 fn_8025E80C(void *, void *, u32);
void fn_8025E7D8(void *, void *, u32);
void fn_80265FF0(u32, u32);
void fn_80265FF8(u32, u32, u32);

void fn_80263CBC(u8 *p) {
    if (lbl_8063FA10 == 0) {
        fn_8031D4B0(&lbl_8063FA14);
        lbl_8063FA10 = 1;
        fn_8031D51C((void *)fn_80265FF0);
        fn_8031D510((void *)fn_80265FF8);
    }
}

void fn_80263D0C(void) {
    lbl_8063FA10 = 0;
    fn_8031E014();
}

s32 fn_80263D28(u8 *p) {
    s32 r = 10;
    u8 *q = p;
    for (s32 i = 0; i < 2; i++) {
        if (F32(q, 0x6524) != 0 && F32(q, 0x6520) == 0) {
            if (F32(q, 0x6528) / 100 > r) r = F32(q, 0x6528);
        }
        q += 16;
    }
    if (r > 40) r = 40;
    return r;
}

char *fn_80263DB8(u8 *p, u32 code) {
    char *base = lbl_80425E60;
    switch (code) {
    case 0: return base + 0x0;
    case 1: return base + 0x1c;
    case 2: return base + 0x38;
    case 3: return base + 0x58;
    case 4: return base + 0x7c;
    case 5: return base + 0x98;
    case 6: return base + 0xb8;
    case 7: return base + 0xdc;
    case 8: return base + 0xf8;
    case 9: return base + 0x114;
    case 10: return base + 0x130;
    case 11: return base + 0x14c;
    case 12: return base + 0x16c;
    case 13: return base + 0x190;
    case 14: return base + 0x1b0;
    case 15: return base + 0x1d8;
    case 16: return base + 0x1f8;
    case 17: return base + 0x214;
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, base + 0x230, code);
    return buf;
}

char *fn_80263EC4(u32 code) {
    char *base = lbl_80425E60;
    switch (code) {
    case 0: return base + 0x28c;
    case 1: return base + 0x2a0;
    case 2: return base + 0x2b8;
    case 3: return base + 0x2cc;
    case 4: return base + 0x2ec;
    case 5: return base + 0x308;
    case 6: return base + 0x31c;
    case 7: return base + 0x330;
    case 8: return base + 0x344;
    case 9: return base + 0x360;
    case 10: return base + 0x370;
    case 11: return base + 0x38c;
    case 12: return base + 0x3a8;
    case 13: return base + 0x3c8;
    case 14: return base + 0x3e0;
    case 15: return base + 0x3f4;
    case 16: return base + 0x408;
    case 17: return base + 0x41c;
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, base + 0x430, code);
    return buf;
}

char *fn_80263FD0(u32 code) {
    char *base = lbl_80425E60;
    switch (code) {
    case 0: return base + 0x490;
    case 1: return base + 0x4a8;
    case 2: return base + 0x4b8;
    case 3: return base + 0x4d0;
    case 4: return base + 0x4e8;
    case 5: return base + 0x504;
    case 6: return base + 0x51c;
    case 7: return base + 0x538;
    }
    char *buf = fn_8025E4E8();
    sprintf(buf, base + 0x548, code);
    return buf;
}

char *fn_8026408C(s32 v) {
    char *buf = fn_8025E4E8();
    if (v < 0) v = -v;
    sprintf(buf, lbl_804263E0, v);
    return buf;
}

#pragma dont_inline on
char *fn_802640DC(u8 *p) {
    s32 code;
    s32 type;
    s32 err;
    char *buf = fn_8025E4E8();
    if (F32(p, 0x3d18) != 0) {
        type = 2;
        err = 5;
        code = F32(p, 0x3d18);
    } else {
        err = fn_8031C4A4(&code, &type);
    }
    sprintf(buf, lbl_804263F0, fn_80263EC4(err), fn_80263FD0(type), fn_8026408C(code));
    return buf;
}
#pragma dont_inline reset

void fn_80264300(u8 *p) {
    memset(p + 0x6540, 0, 0x20);
    memset(p + 0x6560, 0, 0x20);
}

void fn_80264348(u8 *p, u8 i) {
    if (i < 2) {
        memset(p + 0x6520 + i * 16, 0, 0x10);
        F32(p + i * 4, 0x3d1c) = 0;
    }
}

#pragma dont_inline on
void fn_802643AC(u8 *p) {
    for (u32 i = 0; i < 2; i++) {
        fn_80264348(p, i);
    }
}
#pragma dont_inline reset

void fn_80264400(u32 a, u32 b) {
    if (b) fn_8025E4D0(b);
}

s32 fn_8026441C(u8 *p) {
    if (F32(p, 0x3c50)) return -1;
    if (F32(p, 0x3d14)) return -1;
    F32(p, 0x3c50) = 1;
    return 0;
}

s32 fn_80264454(u8 *p) {
    if (F32(p, 0x3c50) == 0) return -1;
    if (F32(p, 0x3d14)) return -1;
    ((WifiVObj *)p)->v13();
    F32(p, 0x3c50) = 0;
    F32(p, 0x3c58) = 1;
    F32(p, 0x3c5c) = 1;
    return 0;
}

s32 fn_80264504(u8 *p) {
    s32 a;
    s32 b;
    switch (F32(p, 0x3c38)) {
    case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
        return 1;
    case 16:
        fn_8031C4A4(&a, &b);
        if (b == 1) return 1;
        break;
    }
    return 0;
}

s32 fn_80264570(u8 *p) {
    switch (F32(p, 0x3c38)) {
    case 8: case 9: case 10: case 11: case 12: case 13:
        return 1;
    }
    if (F32(p, 0x3c60) || F32(p, 0x3c64) || F32(p, 0x3c68)) return 1;
    return 0;
}

s32 fn_802645C4(u8 *p) {
    switch (F32(p, 0x3c38)) {
    case 12: case 13:
        return 1;
    }
    return 0;
}

s32 fn_802645EC(u8 *p) {
    switch (F32(p, 0x3c38)) {
    case 16: case 17:
        return 1;
    }
    return 0;
}

#pragma dont_inline on
void fn_8026461C(u8 *p, s32 st) {
    fn_80322E74();
    fn_80267098(p);
    fn_80266660(p);
    ((WifiVObj *)p)->v18();
    F32(p, 0x3c38) = st;
    F32(p, 0x3c40) = 0;
}
#pragma dont_inline reset

void fn_80264684(u8 *p) {
    if (lbl_8063FA18) {
        lbl_8063FA18 = 0;
        fn_8031C890();
    }
}

void fn_802643F8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

#pragma dont_inline on
void fn_802646A0(u8 *p) {
    if (lbl_8063FA18 == 0) {
        lbl_8063FA18 = 1;
        fn_8031C598(1, lbl_804263FC, 0x5250424a, (void *)fn_802643F8, (void *)fn_80264400);
        fn_8031CB2C(0);
        fn_802676B4(p, 0);
    }
}
#pragma dont_inline reset

void fn_80264718(u8 *p) {
    switch (F32(p, 0x3c40)) {
    case 0:
        F32(p, 0x3390) = 0;
        F32(p, 0x3394) = 0;
        F32(p, 0x338c) = 0;
        F32(p, 0x3c40)++;
        break;
    case 1:
        if (F32(p, 0x3c50)) fn_8026461C(p, 1);
        break;
    }
}

void fn_80264764(u8 *p) {
    F32(p, 0x3390) = 0;
    F32(p, 0x3394) = 0;
    F32(p, 0x338c) = 0;
    F32(p, 0x3c6c) = 0;
    F32(p, 0x3c70) = 0;
    F32(p, 0x33a8) = 0;
    F32(p, 0x33ac) = 0;
    F32(p, 0x33b0) = 0;
    fn_8026461C(p, 2);
}

void fn_80264790(u8 *p) {
    switch (F32(p, 0x3c40)) {
    case 0:
        F32(p, 0x338c) = 0;
        if (fn_8025BDA4() == 0) {
            F32(p, 0x3c40) = 99;
        } else {
            F32(p, 0x3c40)++;
        }
        break;
    case 1:
        F32(p, 0x3c40)++;
        break;
    case 2:
        F32(p, 0x3c40)++;
        break;
    case 3:
        if (F32(p, 0x3c50) == 0) {
            F32(p, 0x3c58) = 0;
            fn_8025BEB4();
            fn_8026461C(p, 0);
        } else {
            fn_8026461C(p, 3);
        }
        break;
    case 99:
        if (F32(p, 0x3c50) == 0) {
            fn_8026461C(p, 0);
        } else {
            F32(p, 0x338c) = 1;
            s32 h = fn_8025BD9C();
            fn_80266F3C(p, fn_802F4FE8(h, fn_802F4D18()));
        }
        break;
    }
}

void fn_802648B4(u8 *p) {
    F32(p, 0x339c) = 0;
    fn_802672E8(p);
    fn_802646A0(p);
    fn_8026461C(p, 4);
}

s32 fn_802648FC(u8 *p) {
    if (F32(p, 0x3c6c)) return -1;
    if (F32(p, 0x3390)) return F32(p, 0x3394) != 0;
    return -1;
}

#pragma dont_inline on
s32 fn_80264938(u8 *p, void *key) {
    u8 *q = p + 0x33b8;
    for (s32 i = 0; i < 64; i++) {
        if (F16(p + i * 0x22, 0x33d8) == 1 && fn_8025E80C(q + i * 0x22, key, 0x10) == 0) return 1;
    }
    return 0;
}
#pragma dont_inline reset

void fn_802649C8(u8 *p) {
    F32(p, 0x33b4) = 0;
    memset(p + 0x33b8, 0, 0x880);
}

void fn_802649E0(u8 *p, void *key) {
    if (fn_80264938(p, key) == 0) {
        if (F32(p, 0x33b4) >= 64) F32(p, 0x33b4) = 0;
        fn_8025E7D8(p + F32(p, 0x33b4) * 0x22 + 0x33b8, key, 0x10);
        F16(p + F32(p, 0x33b4) * 0x22, 0x33d8) = 1;
        F32(p, 0x33b4)++;
    }
}


extern s32 lbl_80503BF8[32];
void fn_80321E84(void);
void *fn_802674DC(u8 *);
s32 fn_80333578(void *);
void fn_80333584(void *);
void fn_80267690(u8 *);
s32 fn_803223C4(s32, void *, void *, void *, void *, void *, void *);
void fn_8031F484(void *, void *);
void *memcpy(void *, const void *, unsigned long);
s32 fn_803243B0(void);
s32 fn_80322978(void);
s64 fn_803338A4(void *);
u32 fn_8025E370(void);
u16 fn_8025E78C(void *, u32);
void DCFlushRange(void *, u32);
void fn_8031F2E4(void *, u32);
void fn_80267378(u8 *);

#pragma dont_inline on
void fn_80264DC8(u8 *p) {
    F32(p, 0x3390) = 0;
    fn_802673B4();
    if (F32(p, 0x66a0) == 0) fn_80321E84();
    fn_802673B8(p);
}

void fn_80264ED8(s32 res, s32 b, u8 *p) {
    if (res == 0) {
        if (b) fn_80267690(p);
        F32(p, 0x339c) = 1;
    }
}


void fn_80264F20(s32 idx, s32 b, char *str, u8 *p);

void fn_80265138(s32 a, s32 b, u8 *p) {
    fn_80267690(p);
    F32(p, 0x3388)++;
}

void fn_80265174(s32 a, u8 *p) {
    fn_80267690(p);
    F32(p, 0x3388)++;
}

void fn_80264E14(s32 res, s32 x, u8 *p) {
    if (res) {
        F32(p, 0x3c70) = 0;
        return;
    }
    F32(p, 0x1c4c) = x;
    if (fn_80333578(fn_802674DC(p))) {
        fn_80333584(fn_802674DC(p));
        fn_80267690(p);
    }
    F32(p, 0x3398) = 0;
    if (fn_803223C4(0, (void *)fn_80264ED8, p, (void *)fn_80264F20, p, (void *)fn_80265138, p) == 0) {
        F32(p, 0x3c70) = 0;
    } else {
        fn_8031F484((void *)fn_80265174, p);
    }
}

void fn_80265074(u8 *p, s32 i) {
    if (!(i >= 0 && i <= 30)) return;
    memset(p + 0x1d08 + i * 0xb8, 0, 0xb8);
    memset(p + 0x3298 + i * 8, 0, 8);
}

void fn_802650EC(u8 *p) {
    for (s32 i = 0; i < 30; i++) {
        fn_80265074(p, i);
    }
}

void fn_802651B0(u8 *p) {
    fn_80267374();
    if (F32(p, 0x3c50) && F32(p, 0x3c58)) F32(p, 0x3c58) = 0;
    F32(p, 0x33a8) = 0;
    F32(p, 0x3c7c) = 0;
    F32(p, 0x3c80) = 0;
    fn_8026461C(p, 6);
}

void fn_80265218(void) {
    for (s32 i = 0; i < 32; i++) {
        lbl_80503BF8[i] = -1;
    }
}

void fn_802652A4(s32 v) {
    for (s32 i = 0; i < 32; i++) {
        if (lbl_80503BF8[i] < 0) {
            lbl_80503BF8[i] = v;
            return;
        }
    }
}

void fn_802652E8(s32 v) {
    s32 n;
    s32 i;
    for (i = 0; i < 32; i++) {
        if (v == lbl_80503BF8[i]) {
            lbl_80503BF8[i] = -1;
            break;
        }
    }
    n = 0;
    for (s32 j = 0; j < 32; j++) {
        if (lbl_80503BF8[j] >= 0) {
            lbl_80503BF8[n++] = lbl_80503BF8[j];
        }
    }
    for (; n < 32; n++) {
        lbl_80503BF8[n] = -1;
    }
}

s32 fn_80265488(u8 *p, s32 *out, s32 max) {
    u32 mask = fn_80266660(p);
    s32 n = 0;
    u8 self = ((WifiVObj *)p)->v18();
    for (s32 i = 0; i < 32; i++) {
        if (self != i && (mask & (1 << i))) n++;
    }
    if (n > max) n = max;
    memcpy(out, lbl_80503BF8, n * 4);
    return n;
}

void fn_8026560C(s32 res, s32 b, s32 c, u8 idx, s32 aid, u8 *p) {
    if (aid >= 0) fn_802652E8(aid);
    if (res == 0) {
        switch (F32(p, 0x3c84)) {
        case 1:
            F32(p + idx * 16, 0x6524) = 0;
            if (fn_80267098(p) <= 1) fn_8026461C(p, 6);
            break;
        case 2:
            if (c) {
                fn_8026461C(p, 6);
            } else {
                fn_80264348(p, idx);
                F32(p, 0x3c5c) = 1;
                fn_803243B0();
            }
            break;
        case 3:
            if (c) {
                fn_80322978();
                fn_8026461C(p, 6);
            }
            break;
        }
    }
}

void fn_80265714(u8 *p) {
    *(s64 *)(p + 0x1c50) = fn_803338A4(fn_802674DC(p));
    F16(p, 0x1c86) = fn_8025E370();
    F16(p, 0x1c84) = 0;
    F16(p, 0x1c84) = fn_8025E78C(p + 0x1c50, 0xb8);
    DCFlushRange(p + 0x1c50, 0xb8);
    fn_8031F2E4(p + 0x1c50, 0xb8);
}

void fn_80265784(u8 *p) {
    F32(p, 0x3c70) = 0;
    fn_80267378(p);
    fn_80265714(p);
    F32(p, 0x3c78) = 0;
    fn_8026461C(p, 7);
}
void fn_80321FEC(void);
s32 fn_803331D0(void *);
void *fn_802674E4(u8 *, s32);
u8 fn_8031F198(void *, u8 *, u8 *, s32);
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void fn_8031C2B4(char *, u32, void *, u32);
void fn_8026806C(u8 *, s32, s32, s32, void *, s32, s32);

void fn_80264F20(s32 idx, s32 b, char *str, u8 *p) {
    u8 *q;
    if (idx >= 0 && idx < 30) {
        u8 buf[0xb8];
        u8 x9;
        u8 x8;
        memset(buf, 0, 0xb8);
        fn_8031C2B4(str, strlen(str), buf, 0xb8);
        if ((u16)fn_8025E78C(buf, 0xb8) == 0) {
            memcpy(p + 0x1d08 + idx * 0xb8, buf, 0xb8);
            fn_8026806C(p, idx, *(s32 *)(buf + 0), *(s32 *)(buf + 4), buf + 0xc, *(s32 *)(buf + 0x2c), *(s32 *)(buf + 0x30));
        } else {
            memset(p + 0x1d08 + idx * 0xb8, 0, 0xb8);
        }
        u8 r = fn_8031F198(fn_802674E4(p, idx), &x9, &x8, 0);
        s32 off = idx * 8;
        p[off + 0x3299] = x9;
        p[off + 0x329a] = x8;
        p[off + 0x329b] = 1;
        if (r != p[off + 0x3298]) F32(p + off, 0x329c) = fn_8025E370();
        p[off + 0x3298] = r;
        F32(p, 0x3388)++;
    }
}

void fn_802657D8(u8 *p) {
    F32(p, 0x3c84) = 0;
    fn_802643AC(p);
    fn_80265218();
    if (F32(p, 0x3c50) == 0) F32(p, 0x3c58) = 1;
    if (F32(p, 0x3c58)) {
        F32(p, 0x3c58) = 0;
        fn_80264DC8(p);
        fn_8026461C(p, 14);
        return;
    }
    if (F32(p, 0x66a0) == 0 && F32(p, 0x3398)) {
        F32(p, 0x3398) = 0;
        fn_803223C4(0, (void *)fn_80264ED8, p, (void *)fn_80264F20, p, (void *)fn_80265138, p);
    }
    if (F32(p, 0x3c5c)) F32(p, 0x3c5c) = 0;
    if (fn_80322E74() == 6) F32(p, 0x3c6c) = 1;
    if (F32(p, 0x3c6c)) {
        F32(p, 0x3390) = 0;
        F32(p, 0x3c6c) = 0;
        F32(p, 0x3c70) = 1;
        fn_80264DC8(p);
        fn_8026461C(p, 4);
        return;
    }
    if (F32(p, 0x3c60)) {
        fn_8026461C(p, 10);
        F32(p, 0x3c60) = 0;
        return;
    }
    if (F32(p, 0x3c64)) {
        fn_8026461C(p, 9);
        F32(p, 0x3c64) = 0;
        return;
    }
    if (F32(p, 0x3c68)) {
        fn_8026461C(p, 8);
        F32(p, 0x3c68) = 0;
        return;
    }
    if (F32(p, 0x66a0) == 0) fn_80321FEC();
}

s32 fn_80265A80(u8 *p, u8 a, char *str, s32 c, u8 d) {
    if (F32(p, 0x3c58)) return -2;
    if (F32(p, 0x3c60) || F32(p, 0x3c64) || F32(p, 0x3c68)) return -2;
    switch (F32(p, 0x3c38)) {
    case 6: case 7:
        break;
    default:
        return -3;
    }
    if (a > 2 || a < 2 || d > 2) return -4;
    if (c) {
        if (d >= a || d < 2) return -5;
    } else if (d) {
        return -1;
    }
    p[0x3c88] = a;
    p[0x3c89] = d;
    F32(p, 0x3c8c) = c;
    if (str) {
        if (strlen(str) + 1 >= 0x80) {
            p[0x3c90] = 0;
        } else {
            strcpy((char *)p + 0x3c90, str);
        }
    } else {
        p[0x3c90] = 0;
    }
    F32(p, 0x3c60) = 1;
    return 0;
}

s32 fn_80265BB0(u8 *p, u8 a) {
    if (F32(p, 0x3c58)) return -2;
    if (F32(p, 0x3c60) || F32(p, 0x3c64) || F32(p, 0x3c68)) return -2;
    if (a <= 1 || a > 2) return -1;
    p[0x3c88] = a;
    F32(p, 0x3c64) = 1;
    return 0;
}

s32 fn_80265C1C(u8 *p, s32 i) {
    u8 x9;
    u8 x8;
    if (F32(p, 0x3c58)) return -2;
    if (F32(p, 0x3c60) || F32(p, 0x3c64) || F32(p, 0x3c68)) return -2;
    switch (F32(p, 0x3c38)) {
    case 6: case 7:
        break;
    default:
        return -3;
    }
    if (i >= 30) return -4;
    if (fn_803331D0(fn_802674E4(p, i)) == 0) return -5;
    if (fn_8031F198(fn_802674E4(p, i), &x9, &x8, 0) != 6) return -6;
    if (x8 >= x9) return -7;
    F32(p, 0x3d10) = i;
    F32(p, 0x3c68) = 1;
    return 0;
}
void fn_8025E86C(void);
void *fn_8025DFD0(void);
u8 *fn_8025E31C(void *);
void fn_8025EDC8(u8 *, u32);
void fn_8025EC68(u8 *, u32, u16, u8, s32);
s32 fn_803225B8(u8, void *, void *, void *, void *);
s32 fn_803226C4(s32, void *, void *, void *, void *);

s32 fn_80265D2C(u8 *p) {
    if (F32(p, 0x66a0)) {
        fn_80263D0C();
        fn_8026461C(p, 6);
        return 0;
    }
    switch (F32(p, 0x3c38)) {
    case 11:
        if (fn_803243B0() == 0) return -1;
        break;
    case 12: case 13:
        switch (fn_80322978()) {
        case 0:
            break;
        case 1:
            fn_803243B0();
            fn_8026461C(p, 6);
            break;
        default:
            fn_803243B0();
            fn_8026461C(p, 6);
            break;
        }
        break;
    }
    return 0;
}

s32 fn_80265DEC(u8 *p) {
    F32(p, 0x3c60) = 0;
    F32(p, 0x3c64) = 0;
    F32(p, 0x3c68) = 0;
    if (F32(p, 0x3c5c)) return -1;
    F32(p, 0x3c60) = 0;
    F32(p, 0x3c64) = 0;
    F32(p, 0x3c68) = 0;
    F32(p, 0x3c5c) = 1;
    return 0;
}

s32 fn_80265E2C(u8 *p, void *key) {
    if (F32(p, 0x3c58)) return -2;
    if (F32(p, 0x3c60) || F32(p, 0x3c64) || F32(p, 0x3c68)) return -2;
    switch (F32(p, 0x3c38)) {
    case 6: case 7:
        break;
    default:
        return -3;
    }
    fn_8025E86C();
    if (fn_80264938(p, key)) return 0;
    F32(p, 0x3390) = 0;
    F32(p, 0x3c6c) = 1;
    return 0;
}

void fn_80265EF0(u32 a, u8 idx) {
    u8 *o = fn_8025E31C(fn_8025DFD0());
    u8 *q = o + idx * 4;
    u32 v = F32(q, 0x3d1c);
    s32 n = 0;
    if (v) {
        if ((u32)F32(o, 0x3d1c) == v) n = 1;
        if ((u32)F32(o, 0x3d20) == v) n++;
        if (n <= 1) fn_8025EDC8(o, v);
        F32(q, 0x3d1c) = 0;
    }
}

void fn_80265F6C(u8 idx, u32 a, u32 c) {
    u8 *o = fn_8025E31C(fn_8025DFD0());
    if (idx < 2) {
        u8 *q = o + idx * 16;
        F32(q, 0x652c) = fn_8025E370();
        if (F32(q, 0x652c) == 0) F32(q, 0x652c) = 1;
    }
    fn_8025EC68(o, a, c, idx, 1);
}

void fn_80265FF0(u32 a, u32 b) {
    fn_80265EF0(a, b);
}

void fn_80265FF8(u32 a, u32 b, u32 c) {
    fn_80265F6C(a, b, c);
}

void fn_80266000(s32 v, u8 idx) {
    u8 *o = fn_8025E31C(fn_8025DFD0());
    if (idx < 2) {
        u8 *q = o + idx * 16;
        F32(q, 0x6528) = v;
        s32 t = fn_8025E370();
        F32(q, 0x652c) = t;
        if (t == 0) F32(q, 0x652c) = 1;
    }
}

void fn_802661D0(s32 res, s32 b, s32 c, s32 d, s32 aid, u8 *p) {
    if (res) return;
    if (b == 0) {
        F32(p, 0x33a0) = 1;
        if (aid >= 0) fn_802652A4(aid);
    } else {
        if (c || d) F32(p, 0x33a4) = 1;
        if (aid >= 0) fn_802652E8(aid);
    }
}

void fn_80266224(s32 aid) {
    if (aid >= 0) fn_802652A4(aid);
}

void fn_80266068(u8 *p) {
    if (F32(p, 0x3c5c)) {
        fn_8026461C(p, 7);
        F32(p, 0x3c5c) = 0;
        return;
    }
    F32(p, 0x3c84) = 2;
    F32(p, 0x33a0) = 0;
    F32(p, 0x33a4) = 0;
    fn_80265218();
    if (fn_803225B8(p[0x3c88], (void *)fn_802661D0, p, (void *)fn_80266224, p) == 0) {
        F32(p, 0x3c84) = 0;
        fn_8026461C(p, 6);
    } else {
        fn_8026461C(p, 11);
    }
}

void fn_80266118(u8 *p) {
    if (F32(p, 0x3c5c)) {
        fn_8026461C(p, 7);
        F32(p, 0x3c5c) = 0;
        return;
    }
    F32(p, 0x3c84) = 3;
    F32(p, 0x33a0) = 0;
    F32(p, 0x33a4) = 0;
    fn_80265218();
    fn_802652A4(F32(p, 0x3d10));
    if (fn_803226C4(F32(p, 0x3d10), (void *)fn_802661D0, p, (void *)fn_80266224, p) == 0) {
        F32(p, 0x3c84) = 0;
        fn_8026461C(p, 6);
    } else {
        fn_8026461C(p, 11);
    }
}

void fn_80266234(s32 v) {
    u8 *o = fn_8025E31C(fn_8025DFD0());
    if (v == 0) F32(o, 0x33a0) = 1;
}
extern char lbl_8063DA28[4];
extern char lbl_8063DA2C[4];
extern char lbl_8063DA30[4];
extern char lbl_8063DA34[4];
s32 fn_80324800(void *, char *, s32);
void fn_8031D528(void);
u32 fn_80322C58(void);

void fn_80266464(s32 res, s32 b, u8 *p) {
    if (res) return;
    if (b == 0) {
        F32(p, 0x33a0) = 1;
    } else {
        F32(p, 0x33a4) = 1;
    }
}

s32 fn_8026648C(void *a, u8 *p) {
    s32 x = fn_80324800(a, lbl_8063DA28, -1);
    s32 y = fn_80324800(a, lbl_8063DA2C, -1);
    fn_80324800(a, lbl_8063DA30, -1);
    fn_80324800(a, lbl_8063DA34, -1);
    if (x != F32(p, 0x6564)) return 0;
    return y == F32(p, 0x656c);
}

u32 fn_80266538(u8 *p) {
    return (u32)F32(p, 0x3c80) / 10;
}

void fn_80266550(u8 *p) {
    if (F32(p, 0x66a0)) {
        fn_8031D528();
    } else {
        fn_80321FEC();
    }
    switch (F32(p, 0x3c40)) {
    case 0:
        F32(p, 0x3c7c) = fn_8025E370();
        F32(p, 0x3c40)++;
        break;
    case 1:
        break;
    }
    F32(p, 0x3c80) = fn_8025E370() - F32(p, 0x3c7c);
    if (F32(p, 0x33a0)) {
        F32(p, 0x33a0) = 0;
        fn_8026461C(p, 12);
    }
    if (F32(p, 0x33a4)) {
        F32(p, 0x33a4) = 0;
        fn_8026461C(p, 6);
    }
    if (F32(p, 0x3c58)) fn_80265DEC(p);
    if (F32(p, 0x3c84) == 3 && (u32)F32(p, 0x3c80) >= 450) fn_80265DEC(p);
    if (F32(p, 0x3c5c)) {
        F32(p, 0x3c5c) = 0;
        fn_80265D2C(p);
    }
}

u32 fn_80266660(u8 *p) {
    u32 mask;
    if (F32(p, 0x66a0)) {
        mask = 0;
        s32 n = fn_80267098(p);
        for (s32 i = 0; i < n; i++) {
            mask |= 1 << i;
        }
    } else {
        mask = fn_80322C58();
    }
    return mask;
}

void fn_80266784(u8 *p) {
    u32 t = fn_8025E370();
    u32 mask = fn_80266660(p);
    u32 self = ((WifiVObj *)p)->v18();
    for (u8 i = 0; i < 2; i++) {
        u8 *q = p + i * 16;
        if (self == i) {
            F32(q, 0x6520) = 1;
            F32(q, 0x6524) = 1;
            F32(q, 0x6528) = 0;
            F32(q, 0x652c) = t;
        } else if (mask & (1 << i)) {
            F32(q, 0x6520) = 0;
            F32(q, 0x6524) = 1;
            F32(q, 0x6528) = 0;
            F32(q, 0x652c) = t;
        } else {
            F32(q, 0x6520) = 0;
            F32(q, 0x6524) = 0;
            F32(q, 0x6528) = 0;
            F32(q, 0x652c) = 0;
        }
    }
    F32(p, 0x651c) = fn_8025E370() - self * 10;
    fn_8026461C(p, 13);
}
s32 fn_8031C48C(s32 *);
void fn_8031C550(void);
s32 fn_8031E08C(void);
s32 fn_80322BF8(void);
s32 fn_80322B9C(void);
s32 fn_8025ECF8(u8 *, u32, u32, s32, u32);
s32 fn_80322A70(u8);
s32 fn_80322DC8(u8);
void fn_8025EE18(u8 *);
void fn_8025CC38(void);
void fn_8032432C(void);
s32 fn_8025CC48(void);
void fn_8025CCA4(s32, s32);
s32 fn_8025CC94(void);

void fn_80267324(u8 *p);

void fn_80266B80(u8 *p) {
    fn_80264300(p);
    F32(p, 0x3c60) = 0;
    F32(p, 0x3c64) = 0;
    F32(p, 0x3c68) = 0;
    fn_80264684(p);
    fn_8025BEB4();
    fn_80267324(p);
    fn_8026461C(p, 15);
}

void fn_80266BDC(u8 *p) {
    F32(p, 0x3c58) = 0;
    fn_8026461C(p, 0);
}

s32 fn_80266EE8(u8 *p) {
    s32 a;
    s32 b;
    if (F32(p, 0x3c54) == 0) return -1;
    F32(p, 0x3c54) = 0;
    fn_8031C4A4(&a, &b);
    return b == 1;
}

s32 fn_80266F44(u8 *p) {
    s32 x;
    if (F32(p, 0x3d18)) return 5;
    return fn_8031C48C(&x);
}

s32 fn_80266F7C(u8 *p) {
    s32 x;
    if (F32(p, 0x3d18)) return -F32(p, 0x3d18);
    fn_8031C48C(&x);
    return -x;
}

void fn_80266FC8(u8 *p) {
    fn_8031C550();
    fn_80266FBC(p);
}

s32 fn_80266FFC(u8 *p) {
    s32 a;
    s32 b;
    fn_8031C4A4(&a, &b);
    return b == 7;
}

u32 fn_8026703C(u8 *p) {
    if (F32(p, 0x66a0)) {
        if (((WifiVObj *)p)->v08()) return (u16)fn_8031E08C();
        return 0;
    }
    return (u8)fn_80322BF8();
}

s32 fn_80267098(u8 *p) {
    if (F32(p, 0x66a0)) {
        if (lbl_8063FA10 && ((WifiVObj *)p)->v08()) return 2;
        return 1;
    }
    return fn_80322B9C();
}

s32 fn_80267100(u8 *p, u32 a, u32 b, u32 c) {
    if (((WifiVObj *)p)->v08() == 0) return -1;
    if (b > ((WifiVObj *)p)->v19()) return -1;
    if (((WifiVObj *)p)->v20(c) == 0) return -1;
    s32 r = fn_8025ECF8(p, a, b, 1, c);
    if (r < 0) b = r;
    return b;
}

s32 fn_802671E4(u8 *p, u32 x) {
    if (((WifiVObj *)p)->v20(x) == 0) return -1;
    if (F32(p, 0x66a0)) {
        F32(p, 0x3c58) = 1;
        return 0;
    }
    return fn_80322A70(x);
}

s32 fn_8026725C(u8 *p, s32 x) {
    if (((WifiVObj *)p)->v08() == 0) return 0;
    if (F32(p, 0x66a0)) return x < p[0x3c88];
    return fn_80322DC8(x);
}

void fn_802672E8(u8 *p) {
    fn_8025EE18(p);
    fn_802650EC(p);
    fn_802649C8(p);
}

void fn_80267324(u8 *p) {
    if (F32(p, 0x66a4)) {
        fn_8025CC38();
        F32(p, 0x66a4) = 0;
    }
    fn_8025EE18(p);
    fn_802650EC(p);
}

void fn_80267378(u8 *p) {
    fn_8025EE18(p);
    if (F32(p, 0x66a0) == 0) fn_8032432C();
}

s32 fn_802673BC(u8 *p, s32 a, s32 b) {
    if (b < 0 || b > 6) return -1;
    if (a == 0) return -1;
    if (((WifiVObj *)p)->v06() == 0) return -3;
    if (fn_8025CC48() == 0) return -2;
    fn_8025CCA4(a, b);
    return 0;
}

s32 fn_8026745C(u8 *p, s32 *out) {
    if (fn_8025CC48() == 0) return 0;
    s32 r = fn_8025CC94();
    if (r >= 0) {
        *out = r;
        r = 1;
    }
    return r;
}
s32 fn_8025EF54(u8 *);
u32 fn_8025EFA4(u8 *, u16 *, u16 *);
s32 fn_8031E0B0(u16, u32, u16, s32);
s32 fn_80330D88(u8, u32, u16);
void fn_8025F00C(u8 *);
void fn_80267534(u8 *);

s32 fn_80266A7C(u8 *p) {
    u16 xa;
    u16 x8;
    if (fn_8025EF54(p) == 0) return -1;
    u32 h = fn_8025EFA4(p, &xa, &x8);
    if (h == 0) return -1;
    if (x8 >= 2) return -1;
    if (F32(p + x8 * 4, 0x3d1c)) return -1;
    F32(p + x8 * 4, 0x3d1c) = h;
    s32 r;
    if (F32(p, 0x66a0)) {
        r = fn_8031E0B0(x8, h, xa, 0);
    } else {
        r = fn_80330D88(x8, h, xa);
    }
    if (r == 0) {
        F32(p + x8 * 4, 0x3d1c) = 0;
        return -1;
    }
    F32(p + x8 * 4, 0x6580) = fn_8025E370();
    fn_8025F00C(p);
    return 0;
}

void fn_80330EEC(u8);
void fn_8025F934(u8 *, s32);

void fn_802668B0(u8 *p) {
    if (F32(p, 0x66a0)) {
        fn_8031D528();
    } else {
        fn_80321FEC();
        u32 t = fn_8025E370();
        if (t - F32(p, 0x651c) >= 50) {
            for (u8 i = 0; i < 2; i++) {
                u8 *q = p + i * 16;
                if (F32(q, 0x6520)) {
                    F32(q, 0x652c) = t;
                } else {
                    if (F32(q, 0x6524) && t - F32(q, 0x652c) > 300) {
                        F32(q, 0x6524) = 0;
                        fn_80322A70(i);
                    }
                    if (F32(q, 0x6524)) fn_80330EEC(i);
                }
            }
            F32(p, 0x651c) = t;
        }
    }
    fn_8025F934(p, 1);
    for (s32 k = 0; k < 8; k++) {
        if (fn_80266A7C(p)) break;
        fn_80321FEC();
    }
    if (F32(p, 0x66a0)) {
        fn_8031D528();
    } else {
        fn_80321FEC();
    }
    u32 now = fn_8025E370();
    for (u8 i = 0; i < 2; i++) {
        u8 *q = p + i * 16;
        if (F32(q, 0x6520) == 0 && F32(q, 0x6524)) {
            u8 *r = p + i * 4;
            if (now - F32(r, 0x6580) >= 50) {
                u16 msg[3];
                msg[0] = 14;
                msg[1] = 6;
                msg[2] = 0;
                ((WifiVObj *)p)->v21(msg, 6, i);
                F32(r, 0x6580) = now;
            }
        }
    }
    if (F32(p, 0x3c58)) fn_80265DEC(p);
    if (F32(p, 0x3c5c)) fn_80265D2C(p);
}

void fn_80266BEC(u8 *p) {
    s32 a;
    s32 b;
    F32(p, 0x3c70) = 0;
    if (F32(p, 0x3c54) == 0) {
        fn_8031C4A4(&a, &b);
        switch ((u32)b) {
        case 0:
            fn_8026461C(p, 14);
            break;
        case 1:
            fn_80267534(p);
            fn_8026461C(p, 6);
            break;
        case 3:
        case 6:
            fn_802643AC(p);
            fn_80265218();
            fn_80264DC8(p);
            ((WifiVObj *)p)->v02();
            fn_8026461C(p, 14);
            break;
        case 7:
            fn_8026461C(p, 17);
            break;
        default:
            fn_8026461C(p, 17);
            break;
        }
        fn_8031C550();
        fn_80266FBC(p);
    }
}
extern char lbl_8042640C[];
extern char lbl_80426424[];
extern char lbl_8063DA20[6];
void fn_8025BBFC(char *, char *, s32);

void fn_80265978(u8 *p, u32 a, char *b, s32 c) {
    char buf[0x80];
    s32 n;
    F32(p, 0x6544) = 2;
    F32(p, 0x654c) = a;
    *(char **)(p + 0x6554) = b;
    F32(p, 0x655c) = c;
    sprintf(buf, lbl_8042640C, 2, a);
    if (fn_80266538(p) <= 30) {
        n = 0;
    } else {
        n = fn_80266538(p) <= 60 ? 1 : 2;
    }
    strcat(buf, lbl_8063DA20);
    fn_8025BBFC(buf + strlen(buf), b, n);
    if (c) sprintf(buf + strlen(buf), lbl_80426424, c);
    fn_80265A80(p, 2, buf, 0, 0);
}
void fn_8025F4E0(void);
void fn_8025CACC(void);

s32 fn_8031DFFC(u8, void *);
u8 fn_80324440(u8, char *, void *);
void fn_8032488C(s32, void *, s32);
s32 fn_803224B0(u8, char *, void *, void *, void *, void *);

void fn_80266274(u8 *p) {
    if (F32(p, 0x3c5c)) {
        fn_8026461C(p, 7);
        F32(p, 0x3c5c) = 0;
        return;
    }
    F32(p, 0x3c84) = 1;
    F32(p, 0x33a0) = 0;
    F32(p, 0x33a4) = 0;
    fn_80265218();
    if (F32(p, 0x66a0)) {
        fn_80263CBC(p);
        if (fn_8031DFFC(p[0x3c88], (void *)fn_80266234) == 0) {
            F32(p, 0x3c84) = 0;
            fn_8026461C(p, 6);
        } else {
            fn_8026461C(p, 11);
        }
        return;
    }
    F32(p, 0x6564) = F32(p, 0x6544);
    F32(p, 0x656c) = F32(p, 0x654c);
    F32(p, 0x6574) = F32(p, 0x6554);
    F32(p, 0x657c) = F32(p, 0x655c);
    p[0x6560] = fn_80324440(p[0x6560], lbl_8063DA28, p + 0x6564);
    p[0x6568] = fn_80324440(p[0x6568], lbl_8063DA2C, p + 0x656c);
    p[0x6570] = fn_80324440(p[0x6570], lbl_8063DA30, p + 0x6574);
    p[0x6578] = fn_80324440(p[0x6578], lbl_8063DA34, p + 0x657c);
    u8 buf[8];
    memset(buf, 0, 8);
    if (F32(p, 0x3c8c) && p[0x3c89] < p[0x3c88]) {
        buf[0] = 1;
        buf[1] = p[0x3c89];
        *(s32 *)(buf + 4) = F32(p, 0x3c8c);
    } else {
        buf[0] = 0;
    }
    fn_8032488C(0, buf, 8);
    if (fn_803224B0(p[0x3c88], ((s8 *)p)[0x3c90] ? (char *)(p + 0x3c90) : (char *)0, (void *)fn_80266464, p, (void *)fn_8026648C, p) == 0) {
        F32(p, 0x3c84) = 0;
        fn_8026461C(p, 6);
    } else {
        fn_8026461C(p, 11);
    }
}

extern f32 lbl_8063D988;
extern const f32 lbl_80642608;
extern const f32 lbl_8064260C;
extern const f32 lbl_80642610;
extern char lbl_8063DA18[7];
void *fn_80267504(u8 *);
void fn_80321BFC(void *, void *, s32, char *, char *, s32, s32, void *, void *);
s32 fn_80322260(void *, s32, void *, void *);
s32 fn_80335DB4(void);
void *fn_802677F8(u8 *);
void fn_8025CAA8(void *);
void fn_80322950(void *, void *);
void fn_80330F94(void *);
void fn_80330FB4(void *);
void fn_80330FD4(void *);
void fn_80330E7C(u8, void *, u32);

void fn_80264A70(u8 *p) {
    switch (F32(p, 0x3c40)) {
    case 0:
        F32(p, 0x3c4c) = (s32)(lbl_80642608 + lbl_8064260C * lbl_8063D988);
        F32(p, 0x3c40)++;
        break;
    case 1:
        if (F32(p, 0x3c4c)-- <= 0) F32(p, 0x3c40)++;
        break;
    case 2:
        F32(p, 0x3c6c) = 0;
        F32(p, 0x3c40)++;
        break;
    case 3:
        if (F32(p, 0x66a0)) {
            F32(p, 0x3c40) = 50;
        } else {
            F32(p, 0x3c40) = 10;
        }
        break;
    case 10: {
        memset(p + 0x1c28, 0, 4);
        fn_80321BFC(p + 0x1c28, fn_802674DC(p), 0x2a93, lbl_804263FC, lbl_8063DA18, 0, 0, fn_802674E4(p, 0), fn_80267504(p));
        F32(p, 0x339c) = 0;
        if (fn_80322260(p + 4, 0, (void *)fn_80264E14, p) == 0) {
            fn_80264DC8(p);
            ((WifiVObj *)p)->v02();
            F32(p, 0x3c70) = 0;
            fn_8026461C(p, 14);
        } else {
            F32(p, 0x3c4c) = (s32)(lbl_80642608 + lbl_80642610 * lbl_8063D988);
            F32(p, 0x3c40)++;
        }
        break;
    }
    case 11:
        fn_80321FEC();
        if (F32(p, 0x3c4c)-- <= 0) {
            fn_80264DC8(p);
            ((WifiVObj *)p)->v02();
            F32(p, 0x3c70) = 0;
            fn_8026461C(p, 14);
        } else if (F32(p, 0x339c)) {
            F32(p, 0x3394) = 0;
            if (fn_80335DB4() == 2) F32(p, 0x3394) = 1;
            F32(p, 0x3390) = 1;
            if (F32(p, 0x3394) == 0) fn_802649E0(p, p + 4);
            if (F32(p, 0x66a4) == 0) {
                fn_8025CAA8(fn_802677F8(p));
                F32(p, 0x66a4) = 1;
            }
            fn_80267534(p);
            F32(p, 0x33a0) = 0;
            F32(p, 0x33a4) = 0;
            fn_80322950((void *)fn_8026560C, p);
            fn_80330F94((void *)fn_80265EF0);
            fn_80330FB4((void *)fn_80265F6C);
            fn_80330FD4((void *)fn_80266000);
            for (u8 i = 0; i < 2; i++) {
                fn_80330E7C(i, p + 0x451c + i * 0x1000, 0x1000);
            }
            fn_8026461C(p, 5);
        }
        break;
    case 50:
        F32(p, 0x33a0) = 0;
        F32(p, 0x33a4) = 0;
        fn_80263CBC(p);
        F32(p, 0x3394) = 0;
        F32(p, 0x3390) = 1;
        fn_8026461C(p, 5);
        break;
    }
}

extern u8 lbl_80425A00[];
extern u8 lbl_80426498[];

u8 *fn_8026419C(u8 *p) {
    *(void **)p = lbl_80425A00;
    u8 *e = p + 0x24;
    do {
        e[0] = 0;
        e[1] = 0;
        *(u16 *)(e + 2) = 0;
        *(u16 *)(e + 4) = 0;
        e[6] = 0;
        e[7] = 0;
        F32(e, 0x8) = 0;
        F32(e, 0xc) = 0;
        F32(e, 0x10) = 0;
        F32(e, 0x14) = 0;
        F32(e, 0x18) = 0;
        F32(e, 0x1c) = 0;
        F32(e, 0x20) = 0;
        F32(e, 0x24) = 0;
        F32(e, 0x28) = 200;
        F32(e, 0x2c) = 50;
        F32(e, 0x30) = 10;
        e += 0x74;
    } while (e < p + 0xea4);
    F32(p, 0xee4) = 0;
    F32(p, 0xee8) = 0;
    F32(p, 0xeec) = 0;
    F32(p, 0xef0) = 0;
    *(void **)p = lbl_80426498;
    F32(p, 0x3c38) = 0;
    F32(p, 0x3c3c) = 0;
    F32(p, 0x3c40) = 0;
    F32(p, 0x1c2c) = 0;
    F32(p, 0x66a0) = 0;
    F32(p, 0x3c50) = 0;
    F32(p, 0x3c54) = 0;
    F32(p, 0x3c74) = 0;
    F32(p, 0x3c60) = 0;
    F32(p, 0x3c64) = 0;
    F32(p, 0x3c68) = 0;
    F32(p, 0x3c84) = 0;
    p[0x3c88] = 0;
    F32(p, 0x3390) = 0;
    F32(p, 0x3394) = 0;
    F32(p, 0x338c) = 0;
    F32(p, 0x3c6c) = 0;
    F32(p, 0x3c70) = 0;
    F32(p, 0x3c58) = 0;
    F32(p, 0x3c5c) = 0;
    F32(p, 0x3d14) = 0;
    F32(p, 0x3388) = 0;
    memset(p + 0x1c50, 0, 0xb8);
    fn_80266FC8(p);
    F32(p, 0x651c) = 0;
    fn_802643AC(p);
    fn_80265218();
    fn_802650EC(p);
    fn_80264300(p);
    fn_802649C8(p);
    F32(p, 0x66a4) = 0;
    return p;
}

s32 fn_80266CE0(u8 *p) {
    u8 changed = 0;
    fn_8025F4E0();
    switch ((u32)F32(p, 0x3c38)) {
    case 0: fn_80264718(p); break;
    case 1: fn_80264764(p); break;
    case 2: fn_80264790(p); break;
    case 3: fn_802648B4(p); break;
    case 4: fn_80264A70(p); break;
    case 5: fn_802651B0(p); break;
    case 6: fn_80265784(p); break;
    case 7: fn_802657D8(p); break;
    case 8: fn_80266118(p); break;
    case 9: fn_80266068(p); break;
    case 10: fn_80266274(p); break;
    case 11: fn_80266550(p); break;
    case 12: fn_80266784(p); break;
    case 13: fn_802668B0(p); break;
    case 14: fn_80266B80(p); break;
    case 15: fn_80266BDC(p); break;
    case 16: fn_80266BEC(p); break;
    }
    if (F32(p, 0x3c78) && ((WifiVObj *)p)->v06()) {
        if (F32(p, 0x3c78) <= 1) {
            fn_80265714(p);
            F32(p, 0x3c78) = 0;
        } else {
            F32(p, 0x3c78)--;
        }
    }
    if (F32(p, 0x3c38) == 16) {
    } else if (((WifiVObj *)p)->v15()) {
        F32(p, 0x3c44) = F32(p, 0x3c38);
        F32(p, 0x3c48) = F32(p, 0x3c40);
        F32(p, 0x3c54) = 1;
        fn_8026461C(p, 16);
    }
    if (F32(p, 0x3c3c) != F32(p, 0x3c38)) {
        changed = 1;
        F32(p, 0x3c3c) = F32(p, 0x3c38);
        F32(p, 0x3388)++;
    }
    if (((WifiVObj *)p)->v06()) fn_8025CACC();
    return changed;
}
#pragma dont_inline reset

}
