#include ".unsorted/8038F424.hpp"

extern "C" {

s32 fn_803B2C3C(u8 *a, u8 *b) {
    if (b[0x311f] == 0 && fn_803ADCD8(a) != 0 && !(fn_803ADCD8(a) & 0x40)) {
        *(u32 *)(b + 8) = 0x29;
    }
    lbl_80405178[*(u32 *)(b + 8)](a, b);
    return *(u32 *)(b + 8) == 0x2b;
}

void fn_803B2CD4(u8 *p) {
    fn_8016E0A0(*(u8 **)(p + 0x2120));
    fn_8016E0A0(p);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B2D0C(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    fn_803B6334(a, b, c, d, e);
    fn_803B67D4(a, b, c, d, e);
}

void fn_803B2D68(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) {
        fn_803BA360(a, b, i, b[i + 0x219c]);
    }
    *(u16 *)(b + 0x3122) = *(u32 *)(b + 0x2e4c);
    *(u32 *)(b + 8) = 1;
}
}

#pragma pop

extern "C" {

void fn_803B2DE0(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0);
    *(u32 *)(b + 8) = 0x15;
    *(u32 *)(b + 0xc) = 2;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B2E28(u8 *a, u8 *b) {
    if (fn_803BD46C(a, b)) {
        fn_803BA9D4(b, 2, 0x29);
        *(u32 *)(b + 8) = 0x15;
        *(u32 *)(b + 0xc) = 3;
    } else {
        *(u32 *)(b + 8) = 3;
    }
    fn_803C04C4(a, b);
}
}

#pragma pop

extern "C" {

void fn_803B2EA0(u8 *a, u8 *b) {
    s32 r = fn_803C0B8C(a, b);
    if (r) {
        fn_803BA9D4(b, 2, r);
        *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
        *(u32 *)(b + 8) = 0x15;
    } else {
        fn_803C04C4(a, b);
        *(u32 *)(b + 8) = 4;
        fn_8016E2E4(8);
    }
}
}

#pragma push
#pragma optimize_for_size on

extern "C" {

void fn_803B2F20(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) {
        b[i] = 0;
        *(u32 *)(b + i * 0xc0 + 0x2dc4) = *(u32 *)(b + i * 0xc0 + 0x2dc0);
    }
    fn_8017CED8(a);
    fn_8016E2E4(0xf);
    fn_803ADCB8(a, 0);
    *(u32 *)(b + 8) = 5;
}
}

#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B3E70(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    fn_803C04C4(a, b);
    if (*(s32 *)(b + 0xec) == n) {
        *(u32 *)(b + 0xec) = 0;
        *(u32 *)(b + 8) = 9;
        fn_8016FA4C(0x15, 0);
        fn_8016E2E4(10);
    } else {
        u8 *q = b + *(u32 *)(b + 0xec);
        *(u32 *)(b + 8) = *(u32 *)(b + q[0x21e8] * 16 + 0x21a8);
        *(u32 *)lbl_8048CDE8 = q[0x21e8];
        fn_8016FA4C(3, lbl_8048CDE8);
    }
}
}

#pragma pop

extern "C" {

void fn_803B608C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 9);
    u32 v = b[*(u32 *)(b + 0xec) + 0x21e8];
    *(u32 *)(b + 0x64) = v;
    *(u32 *)(b + 0x78) = v;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x28;
    *(u32 *)(b + 0x138) = 0;
    *(u32 *)(b + 0x216c) |= 0x80000000;
    fn_8016D1C0(2, 0);
}

void fn_803B6104(u8 *a, u8 *b) {
    *(u32 *)(b + 0x64) = b[*(u32 *)(b + 0xec) + 0x21e8];
    fn_803BA9D4(b, 2, 3);
    *(u32 *)(b + 0xb4) = 0;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x2a;
}

void fn_803B6164(void) {}

void fn_803B6168(void) {}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B616C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0xe4);
    *(u32 *)(b + 0x64) = 0;
    *(u32 *)(b + 0x6c) = 1;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x27;
    *(s32 *)(b + 0x138) = (s32)LCRNG_Next() % 10;
    if (b[0x311d]) {
        b[0x311d]--;
    }
    if (*(u32 *)(b + 0x138)) {
        *(u32 *)(b + 0x130) = 1;
        if (b[0x311c]) {
            b[0x311c]--;
        }
    }
}
}

#pragma pop

extern "C" {

void fn_803B621C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0xe5);
    *(u32 *)(b + 0x64) = 0;
    *(u32 *)(b + 0x6c) = 1;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x27;
}

s32 fn_803B6274(u8 *a, u8 *b) {
    s32 r = 0;
    if ((*(s32 *)(b + 0x6c) == 0xff && fn_803BF758(b, *(u32 *)(b + 0x3044)) == 0) ||
        (*(s32 *)(b + 0x6c) == 0xff && fn_803BF758(b, *(u32 *)(b + 0x3044)) == 1 &&
         ((*(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) & 0x1000) || (*(u32 *)(b + 0x213c) & 0x200)))) {
        fn_803BA9D4(b, 2, 0x119);
        *(u32 *)(b + 0xc) = 0x26;
        r = 1;
        *(u32 *)(b + 8) = 0x15;
    }
    return r;
}

void fn_803B6A64(u8 *a, u8 *b) {
    if (fn_803C94CC(a, b) == 1) {
        *(u32 *)(b + 0xb4) = 0;
        *(u32 *)(b + 0x8) = *(u32 *)(b + 0xc);
    }
}

void fn_803B7D48(u8 *a, u8 *b) {
    u32 v;
    if (fn_803BC520(a, b, &v) == 1) {
        fn_803BA9D4(b, 2, v);
        *(u32 *)(b + 8) = 0x15;
        *(u32 *)(b + 0xc) = 0x19;
    } else {
        *(u32 *)(b + 8) = 0x19;
    }
}

void fn_803B7E98(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 1);
    *(u32 *)(b + 8) = 0x15;
    *(u32 *)(b + 0xc) = 0x1b;
}

void fn_803B8798(void) {}

void fn_803B8B50(void) {}

void fn_803B8CD8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x213c) & 0x0f000000) {
        fn_803B9BF0(b, 0x21, 0x21, 0);
    } else {
        *(u32 *)(b + 8) = 0x22;
    }
}

void fn_803B8F64(u8 *a, u8 *b) {
    u32 v = *(u32 *)(b + 0x213c) & 0xf0000000;
    if (v) {
        *(u32 *)(b + 0x74) = fn_803DD940(v >> 28);
        *(u32 *)(b + 0x213c) &= 0x0fffffff;
        fn_803BA9D4(b, 2, 0x115);
        *(u32 *)(b + 0x8) = 0x15;
        *(u32 *)(b + 0xc) = 0x24;
    } else {
        *(u32 *)(b + 0x8) = 0x24;
    }
}

void fn_803B9294(void) {}

void fn_803B96E8(u8 *a, u8 *b) {
    if (fn_803B9BF0(b, *(u32 *)(b + 8), *(u32 *)(b + 8), 1) != 1) {
        *(u32 *)(b + 8) = 0x27;
    }
}

void fn_803B9734(u8 *a, u8 *b) {
    *(u32 *)(b + 0x8) = 0x2a;
    b[0x311f] = 1;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B9748(u8 *a, u8 *b) {
    u32 f = fn_803AC840(a) & 4;
    if (!f) {
        u8 *x = fn_803AC868(a, 0);
        fn_803DC988(x);
        fn_803DCB44(x);
    }
    if (f) {
        fn_803D9844(0);
    }
    *(u32 *)(b + 8) = 0x2b;
}
}

#pragma pop

extern "C" {

void fn_803B97BC(void) {}

s32 fn_803BA074(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0x10);
    *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
    *(u32 *)(b + 8) = 0x15;
    return 1;
}

s32 fn_803BA0C0(u8 *a, u8 *b) {
    s32 r = 0;
    u32 v = *(u32 *)(b + 0x216c);
    if (v) {
        if (b[0x217d] != 0) {
            if (*(s32 *)(b + 0x74) != 0xff || b[0x217c] == 1 || (v & 0x4000)) {
                r = 1;
            }
        } else {
            r = 1;
        }
    }
    if (r == 1) {
        fn_803BA9D4(b, 2, 0x15);
        *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
        *(u32 *)(b + 8) = 0x15;
    }
    return r;
}
}
