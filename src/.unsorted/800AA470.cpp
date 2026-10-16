#include ".unsorted/800AA470.hpp"

#include "common.hpp"

#pragma dont_inline on

void *operator new(unsigned long size);
#pragma optimize_for_size on

struct Bits176 {
    u16 idx : 8;
    u16 f7 : 1;
    u16 pad : 6;
    u16 f0 : 1;
};

extern "C" {

extern u8 *lbl_8063D500;
#define WK(t, o) (*(t *)(lbl_8063D500 + (o)))
#define WB() ((Bits176 *)(lbl_8063D500 + 0x176))

extern const f32 lbl_80640F44;
extern const f32 lbl_80640F68;
extern const f32 lbl_80640F4C;

void fn_80253E10(s16 a, s32 b, f32 c);
void fn_80253E8C(s16 a, u8 *b, s32 c, void *d);
void fn_80253EB4(s16 a, u8 *b, s32 c, s32 d);
void fn_80253EDC(s16 a, u8 *b, s32 c, void *d);
s32 fn_8005A9F8(s32 a);
void fn_80059A3C(s32 a, void *b);
void fn_800B0F44(s16 a, u8 *b, s32 c, void *d, s32 e);
void fn_8005A44C(void);
s16 fn_802503D8(s32 a, void *b);
void fn_800B8088(s16 a, u8 *b, u16 c);
extern u8 lbl_8047CB24[];

void fn_800B9A64(s32 a, u8 *b, s32 c, void *d, s32 e) {
    fn_800B0F44(a, b, c, d, e);
}

void fn_800B7704(s16 a) {
    fn_80253E10(a, 4, lbl_80640F44);
}

void fn_800B98FC(f32 a, f32 b) {
    *(volatile f32 *)0xCC008000 = a;
    *(volatile f32 *)0xCC008000 = b;
}

void fn_800B990C(f32 a, f32 b) {
    *(volatile f32 *)0xCC008000 = a;
    *(volatile f32 *)0xCC008000 = b;
}

BOOL fn_800ABAE8(void) {
    return WK(s32, 0xd0) != 0;
}
BOOL fn_800B8E3C(void) {
    return WK(s32, 0xc8) != 0;
}

void fn_800AAE2C(s32 a) {
    WK(s32, 0xc8) = 0;
    WK(s32, 0xd0) = a;
    WK(s32, 0xd4) = 0;
}

void fn_800B40E0(s16 a) {
    if (WK(u8, 0xe2) == 0x14) {
        fn_80253E10(a, 3, lbl_80640F68);
    } else {
        fn_80253E10(a, 3, lbl_80640F4C);
    }
}

BOOL fn_800B9494(s32 i) {
    if (WB()->f0 && WK(u16 *, 0xd8)[i] == 0xfedc) {
        return 0;
    }
    return 1;
}

void fn_800B9458(void) {
    if (WK(u16 *, 0xd8)[WK(u8, 0x176)] == 0xfedc) {
        WB()->f0 = 1;
    } else {
        WB()->f0 = 0;
    }
}

BOOL fn_800B9410(void) {
    u16 i;
    for (i = 0; i < WK(u16, 0xe0) - 1; i++) {
        if (WK(u16 *, 0xd8)[i] == 0xfedc) {
            return 0;
        }
    }
    return 1;
}

void fn_800B9A6C(s16 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 2: fn_80253EB4(a, b, 2, 0x1a5d); break;
    }
}

void fn_800B7298(s16 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 1: fn_80253EB4(a, b, 1, fn_8005A9F8(0x1a)); break;
    }
}

void fn_800B7304(s16 a, u8 *b) {
    s32 v;
    u8 buf[0x2c];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(0x14, buf);
            break;
    }
}

void fn_800B7374(s16 a, u8 *b) {
    s32 v;
    u8 buf[0x2c];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
    }
}

void fn_800B0F10(void) {
    switch (WK(s32, 0xc8)) {
        case 3:
        case 10:
        case 20:
        case 25:
        case 35:
        case 41:
        case 46:
        case 52:
        case 57: fn_8005A44C(); break;
    }
}

void fn_800B98B4(u8 *p, u8 i, u8 *q) {
    u8 *base = *(u8 **)(p + 0x1638) + i * 4;
    if (*(u8 **)(base + 0x153c) != q || (q[7] & 1) == 1) {
        *(u8 **)(base + 0x153c) = q;
        *(u32 *)(*(u8 **)(p + 0x1638) + 0x1538) |= 1 << i;
    }
}

void fn_800B73E4(s32 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if (WK(u16, 0xe0) - 10 < WK(u8, 0xf4)) {
                b[2] = b[2] >> 2;
                b[3] = b[3] >> 2;
                b[4] = b[4] >> 2;
            }
            break;
    }
}

void fn_800B50FC(s16 a, u8 *b) {
    u16 idx = 0xffff;
    s32 v;
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 3: idx = 0; break;
        case 6: idx = 1; break;
    }
    if (idx != 0xffff) {
        u16 w = WK(u16 *, 0xd8)[idx];
        if (w != 0) {
            fn_800B8088(a, b, w);
        }
    }
}

void fn_800B527C(s16 a, u8 *b) {
    u16 idx = 0xffff;
    s32 v;
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 3:  idx = 0; break;
        case 6:  idx = 1; break;
        case 0:  break;
        case 10: break;
    }
    if (idx != 0xffff) {
        u16 w = WK(u16 *, 0xd8)[idx];
        if (w != 0) {
            fn_800B8088(a, b, w);
        }
    }
}

void fn_800B4F5C(s16 a, u8 *b) {
    u16 idx = 0xffff;
    s32 v;
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 3:  idx = 0; break;
        case 6:  idx = 1; break;
        case 9:  idx = 2; break;
        case 12: idx = 3; break;
        case 15: idx = 4; break;
        case 0:  break;
    }
    if (idx != 0xffff) {
        u16 w = WK(u16 *, 0xd8)[idx];
        if (w != 0) {
            fn_800B8088(a, b, w);
        }
    }
}

void fn_800B7664(s16 a, u8 *b) {
    s32 v;
    u8 buf[0x2c];
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
}

void fn_800B78C0(s16 a, u8 *b) {
    s32 v;
    u8 buf[0x2c];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(7, buf);
            break;
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(8, buf);
            break;
    }
}

void fn_800B75BC(s16 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 3: fn_800B0F44(a, b, 0x1acd, lbl_8047CB24, 1); break;
        case 5: fn_800B0F44(a, b, 0x1ace, lbl_8047CB24 + 0x14, 1); break;
    }
}

void fn_800B0F44(s16 a, u8 *b, s32 c, void *d, s32 e) {
    u8 *tmp;
    u8 *p;
    fn_80253E8C(a, b, 5, &tmp);
    p = tmp;
    *(void **)p = d;
    if (fn_802503D8(c, d)) {
        if (e) {
            p[4] = 0xff;
            p[5] = 0xff;
            p[6] = 0xff;
        } else {
            p[4] = 0x7f;
            p[5] = 0x7f;
            p[6] = 0x7f;
        }
        p[7] = b[5];
        p[9] = 0x84;
        fn_80253EB4(a, b, 2, -2);
    }
}

extern u16 lbl_8063EEC4;
extern u8 lbl_8063CE34[];
extern u8 lbl_8063D50C[];
extern void *lbl_8063EEC0;
extern u16 lbl_8040F508[][10];
extern u16 lbl_8040F544[][10];
extern u8 lbl_8047C714[][0x14];
u32 fn_800B837C(u16 a);
void fn_800B84F8(u32 a);
void fn_800B7E74(u32 a);
u16 fn_80390C2C(void *a);
u8 fn_800B9C4C(u16 a);
void *fn_8023C814(void *p, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h, s32 i);

s32 fn_800B99F4(void) {
    u16 i;
    if (lbl_8063EEC4 == 0) {
        return 0;
    }
    for (i = 0; i < WK(u16, 0xe0); i++) {
        if (!WB()->f7) {
            fn_800B84F8(fn_800B837C(i));
        }
    }
    return 2;
}

void fn_800B8484(void) {
    u16 i;
    WK(u16 *, 0xd8)[WK(u16, 0xe0)] = 0;
    if (WK(u8, 0xf4) != 0) {
        for (i = WK(u8, 0x176); i < WK(u16, 0xe0); i++) {
            WK(u16 *, 0xd8)[i] = WK(u16 *, 0xd8)[i + 1];
        }
        WK(u8, 0xf4)--;
    }
    fn_800B7E74(WK(u32, 0xe4));
}

BOOL fn_800B9BC8(u32 a) {
    u16 n = fn_80390C2C(lbl_8063CE34 + 0x34);
    u16 i;
    for (i = 0; i < n; i++) {
        if (lbl_8063D50C[a] & fn_800B9C4C(i)) {
            return 1;
        }
    }
    return 0;
}

void fn_800AA470(void) {
    s32 i;
    for (i = 0; i < 0x20; i++) {
        ((u32 *)lbl_8063D500)[i] = 0;
        ((s16 *)(lbl_8063D500 + 0x80))[i] = -1;
    }
    {
        void *p = operator new(0x3d4);
        if (p) {
            p = fn_8023C814(p, 0, 4, 0, 0, 1, 5, 1, 1, 4);
        }
        lbl_8063EEC0 = p;
    }
}

void fn_800B7960(s16 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 8:  fn_80253EB4(a, b, 2, 0x1a64); break;
        case 11: fn_80253EB4(a, b, 2, 0x1a65); break;
        case 14: fn_80253EB4(a, b, 2, 0x1a66); break;
        case 18: fn_80253EB4(a, b, 2, 0x3159); break;
    }
}

void fn_800B0FFC(s16 a, u8 *b, u16 c, s32 d) {
    if (WK(u8, 0xe2) == 0x13) {
        if (d) {
            fn_800B0F44(a, b, lbl_8040F508[2][c], lbl_8047C714[c], 1);
        } else {
            fn_80253EB4(a, b, 2, lbl_8040F544[2][c]);
        }
    } else {
        if (d) {
            fn_800B0F44(a, b, lbl_8040F508[WK(u32, 0xe4) & 1][c], lbl_8047C714[c], 1);
        } else {
            fn_80253EB4(a, b, 2, lbl_8040F544[WK(u32, 0xe4) & 1][c]);
        }
    }
}

void fn_800B77F8(s32 a, u8 *b) {
    s32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 2:
            if (WK(u16, 0x17a) == 0) {
                b[2] = b[2] >> 2;
                b[3] = b[3] >> 2;
                b[4] = b[4] >> 2;
            }
            break;
        case 3:
            if (WK(u16, 0x17a) + 6 >= WK(u16, 0x17e)) {
                b[2] = b[2] >> 2;
                b[3] = b[3] >> 2;
                b[4] = b[4] >> 2;
            }
            break;
    }
}
}
