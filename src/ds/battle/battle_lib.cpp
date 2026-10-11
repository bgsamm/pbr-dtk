#include ".unsorted/8038F424.hpp"

extern "C" {

void fn_803BA9D4(u8 *p, u32 a, u32 b) {
    *(u32 *)(p + 0xac) = a;
    *(u32 *)(p + 0xb0) = b;
    *(u32 *)(p + 0xb4) = 0;
    NARC_ReadWholeMemberByIndexPair(p + 0x2700, a, b);
}

void fn_803BA9EC(u8 *p, u32 a, u32 b) {
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xbc) = *(u32 *)(p + 0xac);
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xcc) = *(u32 *)(p + 0xb0);
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xdc) = *(u32 *)(p + 0xb4);
    (*(u32 *)(p + 0xb8))++;
    *(u32 *)(p + 0xac) = a;
    *(u32 *)(p + 0xb0) = b;
    *(u32 *)(p + 0xb4) = 0;
    NARC_ReadWholeMemberByIndexPair(p + 0x2700, a, b);
}

s32 fn_803BAA4C(u8 *p) {
    if (*(u32 *)(p + 0xb8) != 0) {
        (*(u32 *)(p + 0xb8))--;
        fn_803BA9D4(p, *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xbc), *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xcc));
        *(u32 *)(p + 0xb4) = *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xdc);
        return 0;
    }
    return 1;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803BABF0(u8 *p) {
    s32 i;
    s32 j;
    s32 k;
    s32 s = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 16; k++) {
                s += p[i * 0x40 + j * 0x10 + k + 0x2200];
            }
        }
    }
    if (s == 0) {
        *(u32 *)(p + 0x3148) = 0;
    }
    return s == 0;
}
}

#pragma pop

extern "C" {

void fn_803BAC68(u8 *p) {
    (*(u32 *)(p + 0x3148))++;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803BAC78(u8 *p, s32 i) {
    for (s32 j = 0; j < 0x100; j++) {
        p[i * 0x100 + j + 0x2300] = 0;
    }
}
}

#pragma pop

extern "C" {

void fn_803BB728(u8 *p, s32 i, u32 a, u32 b) {
    fn_803BB744(p + i * 0xc0 + 0x2d40, a, b);
}

void fn_803BC450(u8 *p, u32 i) {
    *(u32 *)(p + ((i << 1) & 4) + 0xa4) = 0;
}

void fn_803BD374(u8 *a, u8 *b, s32 c) {
    if (*(u16 *)(b + c * 0xc0 + 0x2db8) == 0) {
        *(u16 *)(b + (u8)c * 2 + 0x394) = 0;
    }
    fn_803B1AC4(a, b, c);
}

void fn_803BD39C(u8 *a, u8 *b, u32 c) {
    *(u32 *)(b + c * 0xc0 + 0x2db0) |= 0x1000;
    *(u32 *)(b + c * 4 + 0x304c) = *(u32 *)(b + 0x3044);
}

void fn_803BD3C4(u8 *a, u8 *b, u32 c) {
    u8 *q = b + c * 0xc0;
    *(u32 *)(q + 0x2db0) &= ~0x1000;
    *(u32 *)(q + 0x2db0) &= ~0x300;
    *(u32 *)(q + 0x2dc0) &= 0xdffbff3f;
    *(u32 *)(q + 0x2dc8) &= ~0x1f800;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803BD840(u8 *a, u8 *b) {
    for (s32 i = 0; i < 4; i++) {
        *(u16 *)(b + i * 2 + 0x306c) = 0xff;
        b[i + 0x21a0] = 6;
        *(u16 *)(b + i * 2 + 0x310c) = LCRNG_Next();
    }
    *(u32 *)(b + 0x2168) = 1;
    *(u32 *)(b + 0x174) = 1;
    if (!(fn_803AC840(a) & 2)) {
        b[0x3108] |= fn_803DD920(2);
        b[0x3108] |= fn_803DD920(3);
    }
    b[0x311c] = 6;
    b[0x311d] = 6;
}

s32 fn_803BE72C(u8 *p, u32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (v == *(u16 *)(p + i * 2 + 0xc)) {
            break;
        }
    }
    return i;
}
}

#pragma pop

extern "C" {

u32 fn_803BF1C4(u8 *p, s32 i) {
    BF_344 *f = (BF_344 *)(p + i * 4 + 0x344);
    if (f->b0 || f->b1 || f->b2 || f->b3 || f->b4 || f->b5 || f->b6 || f->b8 || f->b7) {
        return 1;
    }
    return 0;
}

u32 fn_803BF32C(u8 *p, s32 i) {
    return i | (p[i + 0x219c] << 8);
}

u16 fn_803BF340(u8 *p, s32 i) {
    u16 r = 0;
    u8 *q = p + i * 16;
    if (*(u32 *)(q + 0x21b4) == 1) {
        s32 k = *(s32 *)(q + 0x21b0);
        if (k != 0) {
            r = *(u16 *)(p + i * 0xc0 + k * 2 + 0x2d4a);
        }
    }
    return r;
}

s32 fn_803BF758(u8 *p, s32 i) {
    switch (*(u16 *)(p + i * 16 + 0x3de)) {
        case 0x1a:
        case 0x27:
        case 0x4b:
        case 0x91:
        case 0x97:
        case 0x9b:
        case 0xff:
        case 0x100:
        case 0x107:
        case 0x110: return 1;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

u32 fn_803BF7E8(u32 i, u8 *x, u8 *y, u8 *z) {
    u32 r = 1;
    if (i >= 0x70) {
        i = (u32)(u16)LCRNG_Next() % 0x70;
        r = 0;
    }
    u8 t0 = lbl_80405248[i * 3];
    u8 t1 = lbl_80405248[i * 3 + 1];
    *x = t0;
    u8 t2 = lbl_80405248[i * 3 + 2];
    *y = t1;
    *z = t2;
    return r;
}
}

#pragma pop

extern "C" {

u32 fn_803BF8E4(u32 v) {
    if (v == 0 || v == 0xd6 || v == 0x17f || v == 0x112 || v == 0x17e ||
        (u16)(v - 0xffff0076 + 0x10000 - 0x10000) <= 1) {
        return 1;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

u32 fn_803BF930(u8 *a, u32 mv, u32 c) {
    u32 r = 0;
    if (mv == 0xae && (fn_803BACA4(a, c, 0x1b, 0) == 7 || fn_803BACA4(a, c, 0x1c, 0) == 7)) {
        r = 1;
    }
    return r;
}

u32 fn_803BF9AC(u8 *a, u8 *b, s32 i) {
    u8 *q;
    u32 r;
    u32 k;
    r = 0;
    k = (u8)fn_803ACCE4(a, i);
    q = b + i * 0xc0;
    if (*(u16 *)(q + 0x2db8) != 0 && (((*(u32 *)(b + k * 8 + 0x1c4) >> 3) & 0x3f) & fn_803DD920(b[i + 0x219c])) == 0 &&
        (u8)Item_IsMail(*(u16 *)(q + 0x2db8)) == 0) {
        r = 1;
    }
    return r;
}
}

#pragma pop

extern "C" {

u32 fn_803BFA40(u8 *p, s32 i) {
    return (u8)Item_IsMail(*(u16 *)(p + i * 0xc0 + 0x2db8)) == 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803BFB90(u8 *a, s32 b, s32 c, s32 d) {
    u32 r = 0;
    if ((u8)fn_803BFB18(a, b) != 0x68) {
        if (d == (u8)fn_803BFB18(a, c)) {
            r = 1;
        }
    } else {
        if (d == (u8)fn_803BFB18(a, c)) {
            u32 *q = (u32 *)(a + b * 0x1c + 0x2d4);
            if (!((*q >> 28) & 1)) {
                *q |= 0x10000000;
                *(u32 *)(a + 0x213c) |= 0x800000;
            }
        }
    }
    return r;
}

u32 fn_803C02EC(u8 *a, s32 i) {
    u32 r = 0;
    if ((u8)fn_803BFB18(a, i) == 0x36 && (*(u32 *)(a + 0x150) & 1) != ((*(u32 *)(a + i * 0xc0 + 0x2dc8) >> 1) & 1)) {
        r = 1;
    }
    return r;
}

u32 fn_803C035C(u8 *a, u8 *b, s32 c, s32 mv) {
    u32 r = 0;
    s32 n = fn_803AC860(a);
    u32 k = (u8)fn_803ACCE4(a, c);
    for (s32 i = 0; i < n; i++) {
        if (k != (u8)fn_803ACCE4(a, i) && (*(u32 *)(b + i * 0xc0 + 0x2dc0) & 0x2000)) {
            s32 j;
            for (j = 0; j < 4; j++) {
                if (mv == *(u16 *)(b + i * 0xc0 + j * 2 + 0x2d4c)) {
                    break;
                }
            }
            if (j != 4) {
                r = 1;
            }
        }
    }
    return r;
}

u32 fn_803C0434(u8 *a, u8 *b, u32 m) {
    u32 r = 0;
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) {
        if (m & *(u32 *)(b + i * 0xc0 + 0x2dc0)) {
            r = 1;
            break;
        }
    }
    return r;
}
}

#pragma pop

extern "C" {

void fn_803C04A4(u8 *a, u8 *b) {
    *(u32 *)(b + 0x216c) = 0;
    *(u32 *)(b + 0x2150) = 1;
    *(u32 *)(b + 0x213c) &= ~0x100000;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803C04C4(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    s32 i;
    for (i = 0; i < n; i++) {
        b[i + 0x21ec] = i;
    }
    for (i = 0; i < n - 1; i++) {
        for (s32 j = i + 1; j < n; j++) {
            u8 x = b[i + 0x21ec];
            u8 y = b[j + 0x21ec];
            if (fn_803BBB80(a, b, x, y, 1)) {
                b[i + 0x21ec] = y;
                b[j + 0x21ec] = x;
            }
        }
    }
}

u32 fn_803C0584(u8 *a, u8 *b, u32 c, s32 v) {
    u32 r = 0;
    if ((*(u32 *)(b + 0x180) & 0x7000) == 0) {
        return r;
    }
    for (s32 i = 0; i < 6; i++) {
        if (v == lbl_80405398[i]) {
            return 1;
        }
    }
    return r;
}

u32 fn_803C05C8(u8 *a, u8 *b, s32 c, s32 v) {
    if (((*(u32 *)(b + c * 0xc0 + 0x2dcc) >> 13) & 7) == 0) {
        return 0;
    }
    for (s32 i = 0; i < 14; i++) {
        if (v == lbl_804053A4[i]) {
            return 1;
        }
    }
    return 0;
}

s32 fn_803C06A4(u8 *a, u8 *b, s32 c) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (*(u16 *)(b + c * 0xc0 + i * 2 + 0x2d4c) == 0) {
            return i;
        }
    }
    return i;
}

u32 fn_803C06DC(u32 v) {
    for (u8 i = 0; i < 12; i++) {
        if (v == lbl_80473AB4[i]) {
            return 1;
        }
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803C0B68(s32 a, s32 b) {
    s32 s;
    if (a == 0) {
        return a;
    }
    s = 1;
    if (a < 0) {
        s = -1;
    }
    a = a / b;
    if (a == 0) {
        return s;
    }
    return a;
}

u16 fn_803C3D6C(u8 *p, s32 i) {
    if ((u8)fn_803BFB18(p, i) == 0x67) {
        return 0;
    }
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) {
        return 0;
    }
    return *(u16 *)(q + 0x2db8);
}

s32 fn_803C3DD8(u8 *p, s32 i) {
    return *(u32 *)(p + i * 16 + 0x21a8) == 0x27;
}

u32 fn_803C40BC(u8 *p, s32 i) {
    return Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)), ITEM_PARAM_HOLD_EFFECT);
}

u32 fn_803C4100(u8 *p, s32 i, s32 c) {
    u16 v;
    switch (c) {
        case 0: v = fn_803C3D6C(p, i); break;
        case 2:
            if ((*(u32 *)(p + i * 0xc0 + 0x2dcc) >> 10) & 7) {
                return 0;
            }
        case 1: v = *(u16 *)(p + i * 0xc0 + 0x2db8); break;
    }
    Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), v), ITEM_PARAM_EFFECT_PARAM);
}

u32 fn_803C4194(u8 *p, s32 i) {
    return Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)),
                    ITEM_PARAM_NATURAL_GIFT_POWER);
}

u32 fn_803C41D8(u8 *p, s32 i) {
    return Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)), ITEM_PARAM_NATURAL_GIFT_TYPE);
}

void fn_803C421C(u8 *p, s32 i) {
    Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(p + i * 0xc0 + 0x2db8)),
             ITEM_PARAM_PLUCK_EFFECT);
}

u32 fn_803C4258(u8 *p, s32 i) {
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) {
        return 0;
    }
    Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(q + 0x2db8)), ITEM_PARAM_FLING_EFFECT);
}

u32 fn_803C42A4(u8 *p, s32 i) {
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) {
        return 0;
    }
    Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(q + 0x2db8)), ITEM_PARAM_FLING_POWER);
}

void fn_803C5828(u8 *a, u8 *b) {
    if (fn_803C40BC(b, *(u32 *)(b + 0x64)) == 0x68) {
        u32 i = *(u32 *)(b + 0x64);
        u8 *q = b + i * 0xc0;
        u32 v = *(u32 *)(q + 0x2db0);
        if (!(v & 0xc00) && !(v & 0x70) && !(*(u32 *)(b + 0x213c) & 0x200) && !(v & 0x1000)) {
            if (*(u32 *)(b + 0x3040) == *(u16 *)(b + i * 2 + 0x30dc)) {
                BF_2DCC *f = (BF_2DCC *)(q + 0x2dcc);
                if (f->k < 10) {
                    f->k++;
                }
            } else {
                ((BF_2DCC *)(q + 0x2dcc))->k = 0;
                *(u16 *)(b + *(u32 *)(b + 0x64) * 2 + 0x30dc) = *(u32 *)(b + 0x3040);
            }
        }
    } else {
        ((BF_2DCC *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc))->k = 0;
    }
}

void fn_803C590C(u8 *a, u8 *b) {
    if (fn_803C40BC(b, *(u32 *)(b + 0x64)) == 0x68) {
        if (*(u32 *)(b + 0x216c) & 0x801fda49) {
            u32 i = *(u32 *)(b + 0x64);
            if (*(u32 *)(b + 0x3040) == *(u16 *)(b + i * 2 + 0x30dc)) {
                u8 *q = b + i * 0xc0;
                BF_2DCC *f = (BF_2DCC *)(q + 0x2dcc);
                u32 k = f->k;
                if (k && !((*(u32 *)(b + i * 0x1c + 0x2d4) >> 23) & 7)) {
                    u32 v = *(u32 *)(q + 0x2db0);
                    if (!(v & 0xc00) && !(v & 0x70) && !(*(u32 *)(b + 0x213c) & 0x200) && !(v & 0x1000)) {
                        f->k = k - 1;
                    }
                }
            }
        }
    } else {
        ((BF_2DCC *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc))->k = 0;
    }
}

s32 fn_803C59F0(void) {
    return 0;
}

u32 fn_803C59F8(u8 *p, s32 i) {
    u32 r = 1;
    u32 v = *(u32 *)(p + i * 0xc0 + 0x2db0);
    if ((v & 0x400000) || (v & 0xc00) || (v & 0x70) || (v & 0x1000)) {
        r = 0;
    }
    return r;
}

u8 fn_803C5A34(u8 *p, s32 i) {
    return p[i * 0x100 + 0x2300];
}

u32 fn_803C5A44(u8 *p, s32 i) {
    u32 r = 0;
    if (*(u32 *)(p + i * 0x1c + 0x2e8) & 8) {
        r = 1;
    }
    return r;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

u32 fn_803C5A68(u8 *a, u8 *mon) {
    u16 buf[8];
    u8 *x = (u8 *)fn_803ACBCC(a, 0);
    u32 v1 = fn_803DA0C0(x);
    u32 v2 = fn_803DA0C8(x);
    u8 *v3 = fn_803DA0BC(x);
    GetMonDataInternal(mon, 0x8f, buf);
    if (v1 == GetMonDataInternal(mon, 7, 0) && v2 == GetMonDataInternal(mon, 0x9c, 0) && fn_803DECAC(v3, buf, 7) == 0) {
        return 1;
    }
    return 0;
}

void fn_803C5FCC(u8 *a, u8 *b) {
    for (s32 i = 0; i < (s32)fn_803AC860(a); i++) {
        for (s32 j = 0; j < 6; j++) {
            b[i * 6 + j + 0x312c] = j;
        }
        fn_803C605C(a, b, i, b[i + 0x219c]);
    }
}
}

#pragma pop

extern "C" {

u32 fn_803C6154(u8 i, u32 v) {
    return v * lbl_80405402[i].a / lbl_80405402[i].b;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803C8448(u8 *p, s32 v) {
    if (v != 0) {
        v *= 100 - (s32)LCRNG_Next() % 16;
        v /= 100;
        if (v == 0) {
            v = 1;
        }
    }
    return v;
}

s32 fn_803C8688(u32 v) {
    s32 i = 0;
    while (lbl_8040543A[i] != 0xffff) {
        if (v == lbl_8040543A[i]) {
            break;
        }
        i++;
    }
    return lbl_8040543A[i] == 0xffff;
}

u32 fn_803C86CC(u8 *p, u16 x) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (*(u16 *)(p + x * 16 + 0x3de) == *(u16 *)(p + lbl_80405470[i] * 16 + 0x3de)) {
            break;
        }
    }
    return i == 6;
}

u32 fn_803C8724(u8 *p, u16 x) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (*(u16 *)(p + x * 16 + 0x3de) == *(u16 *)(p + lbl_8040547C[i] * 16 + 0x3de)) {
            break;
        }
    }
    return i == 6;
}
}

#pragma pop

extern "C" {

u32 fn_803C877C(u8 *p, u16 a, u32 b) {
    return Item_Get(ItemTable_Index((ItemData *)*(u8 **)(p + 0x2120), a), (ItemDataParam)b);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803C87B4(u8 *a, u32 x, s32 v) {
    s32 n = fn_803AC860(a);
    s32 i;
    for (i = 0; i < n; i++) {
        if (v == (u8)fn_803ACCE4(a, i)) {
            break;
        }
    }
    return i;
}

void fn_803C8820(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n - 1; i++) {
        for (s32 j = i + 1; j < n; j++) {
            u8 x = b[i + 0x21e8];
            u8 y = b[j + 0x21e8];
            u32 kx = *(u32 *)(b + x * 16 + 0x21b4);
            if (kx == *(u32 *)(b + y * 16 + 0x21b4) && fn_803BBB80(a, b, x, y, kx - 1 != 0)) {
                b[i + 0x21e8] = y;
                b[j + 0x21e8] = x;
            }
        }
    }
}
}

#pragma pop

extern "C" {

s32 fn_803C88E8(void) {
    return 1;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803C8BC8(u8 *a, s32 b, s32 c) {
    if (fn_803BFB18(a, c) == 0x2e && c != 0xff) {
        u8 *q = a + b * 0xc0;
        q += *(u16 *)(a + b * 2 + 0x30bc);
        if (q[0x2d6c]) {
            q[0x2d6c]--;
        }
    }
}

s32 fn_803C8F1C(u8 *b, u32 x, s32 m, s32 v, s32 f, u32 *p) {
    u32 fl = *(u32 *)(b + 0x213c);
    if (!(fl & 0x800) && !(fl & 0x8000) && v != 0) {
        v = fn_803C0B68(v * m, 10);
    }
    switch (m) {
        case 0: *p = (*p | 8) & ~6; break;
        case 5:
            if (f) {
                if (*p & 2) {
                    *p &= ~2;
                } else {
                    *p |= 4;
                }
            }
            break;
        case 0x14:
            if (f) {
                if (*p & 4) {
                    *p &= ~4;
                } else {
                    *p |= 2;
                }
            }
            break;
    }
    return v;
}
}

#pragma pop

extern "C" {

u32 fn_803C9010(u8 *p, s32 i) {
    switch (*(u16 *)(p + i * 16 + 0x3de)) {
        case 0x1a:
        case 0x27:
        case 0x4b:
        case 0x91:
        case 0x97:
        case 0x9b:
        case 0xff:
        case 0x100:
        case 0x107:
        case 0x111: return *(u32 *)(p + 0x213c) & 0x200;
    }
    return 1;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803C90A4(u8 *p, u8 i) {
    for (s32 j = 0; j < 4; j++) {
        *(u16 *)(p + i * 8 + j * 2 + 0x370) = 0;
    }
}
}

#pragma pop

extern "C" {

u8 *fn_803C90D0(u8 *p, s32 i) {
    return p + i * 0xc0 + 0x2d40;
}

s32 fn_803C90E0(void) {
    return 192;
}

u8 *fn_803C90E8(u8 *p, u8 i) {
    return p + i * 8 + 0x1c4;
}

u8 *fn_803C90F8(u8 *p, s32 i) {
    return p + i * 0xc0 + 0x2dc8;
}

u8 *fn_803C9108(u8 *p) {
    return p + 0x184;
}

u8 fn_803C9110(void) {
    u32 x = fn_803AC828();
    return fn_803C8C48(x, fn_803AC848((u8 *)x), 3, 0);
}

u32 fn_803C9158(void) {
    return *(u32 *)((u8 *)fn_803AC848((u8 *)fn_803AC828()) + 0x180);
}

bool fn_803C9180(u32 m) {
    return (m & *(u32 *)((u8 *)fn_803AC848((u8 *)fn_803AC828()) + 0x180)) != 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

u8 fn_803C91C0(u32 i, s32 j) {
    u32 x = fn_803AC828();
    u8 *base = (u8 *)fn_803AC848((u8 *)x);
    if (fn_803AC840((u8 *)x) & 2) {
        i &= 1;
    }
    u8 *q = base + (u8)i * 6;
    return q[j + 0x312c];
}
}

#pragma pop

extern "C" {

u8 fn_803C922C(s32 i, s32 j) {
    u32 fl = fn_803AC840((u8 *)fn_803AC828());
    if (fl & 8) {
        if (j > 0) {
            return 0xff;
        }
        return i;
    }
    if (fl & 2) {
        if (j > 1) {
            return 0xff;
        }
        if (i > 1) {
            return 0xff;
        }
        return i + j * 2;
    }
    if (j > 0) {
        return 0xff;
    }
    return i;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803C9378(u8 *p, u8 i, s32 j, u8 v) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 4;
    q[j + 0x314c] = v;
}
}

#pragma pop

extern "C" {

u8 fn_803C93C4(u8 *p, u8 i, s32 j) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 4;
    return q[j + 0x314c];
}

u8 *fn_803C940C(u8 *p, u32 x, s32 i, s32 j) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 0x1b0;
    return q + j * 0x48 + 0x315c;
}

u8 *fn_803C9458(u8 *p, s32 i) {
    return (u8 *)fn_803AC848(p) + i * 6 + 0x312c;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803C9490(u8 *p, u16 *s) {
    if (p == 0) {
        return;
    }
    if (s == 0) {
    } else {
        for (s32 i = 0; i < 11; i++) {
            *(u16 *)(p + i * 2 + 0x36) = *s++;
        }
    }
}
}

#pragma pop
