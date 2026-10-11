#include ".unsorted/8038F424.hpp"

extern "C" {

void fn_803AF748(u8 *a, u32 b) {
    u32 v = 0x1000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803AFEB4(u8 *a, u32 b) {
    u32 v = 0x7000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803AFEEC(u8 *p, u32 i) {
    Msg4 m;
    m.cmd = 8;
    m.b = p[i * 0x2c + 0xad];
    m.a = p[i + 0xa8];
    fn_803AF5F0(p, 1, i, &m, 4);
}

void fn_803AFF40(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.a = c;
    m.cmd = 9;
    u32 k = BattleSystem_GetPartner((BattleSystem *)a, b);
    m.b = (*(u8 **)(a + 0x30))[k + 0x219c];
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803AFFAC(u8 *a, u32 b) {
    u32 v = 0xa000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803AFFE4(u8 *p, u32 i, u32 v) {
    Msg8b m;
    m.cmd = 0xb;
    m.b = p[i * 0x2c + 0xad];
    m.a = p[i + 0xa8];
    m.c = v;
    fn_803AF5F0(p, 1, i, &m, 8);
}

void fn_803B01CC(u8 *a, u32 b) {
    u32 v = 0xd000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B07B4(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}

void fn_803B08DC(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}

void fn_803B0AB8(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}

void fn_803B0D58(u8 *a, u32 b, void *c) {
    fn_803AF5F0(a, 0, b, c, 4);
}

void fn_803B0E4C(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B0E94(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f, u32 g) {
    BattleIO_ClearBuffer((BattleContext *)b, c);
    struct {
        u8 cmd;
        u8 e;
        u16 d;
        u32 f;
        u32 g;
    } m;
    m.d = d;
    m.cmd = 0x13;
    m.e = e;
    m.f = f;
    m.g = g;
    fn_803AF5F0(a, 1, c, &m, 0xc);
}
}

#pragma pop

extern "C" {

void fn_803B0F14(u8 *a, u8 *b) {
    Msg4 m;
    m.cmd = 0x14;
    m.a = b[*(u32 *)(b + 0x64) + 0x219c];
    m.b = *(u32 *)(b + 0x3044);
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), &m, 4);
}

void fn_803B0F68(u8 *a, u8 *b, u8 *c) {
    c[0] = 0x15;
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), c, 0x24);
}

void fn_803B0F88(u8 *a, u8 *b, u32 c) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 0, 0, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), c);
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), m, 0x58);
}

void fn_803B0FF0(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 0, 0, d, e, c);
    fn_803AF5F0(a, 1, d, m, 0x58);
}

void fn_803B1058(u8 *a, u32 b) {
    u32 v = 0x17000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B13E0(u8 *a, u32 x, u32 c, u32 b) {
    Msg4 m;
    m.cmd = 0x1b;
    m.b = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B1420(u8 *a) {
    u32 v = 0x1c000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B1570(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x1e;
    m.a = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B15AC(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x1f;
    m.a = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B15E8(u8 *a, u8 *b, u32 c, u32 d) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 1, d, c, c, 0);
    fn_803AF5F0(a, 1, c, m, 0x58);
}

void fn_803B1650(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 1, e, c, d, 0);
    fn_803AF5F0(a, 1, c, m, 0x58);
}

void fn_803B16B4(u8 *a, u8 *b, u32 c, u8 d) {
    Msg4 m;
    m.cmd = 0x20;
    m.a = d;
    s16 mx = *(s16 *)(b + 0x3122);
    m.b = (mx - *(s32 *)(b + 0x2e4c)) * 100 / mx;
    fn_803AF5F0(a, 1, c, &m, 4);
}

void fn_803B1704(u8 *a, u8 *b, u32 c, u8 d) {
    Msg4 m;
    m.a = d;
    m.cmd = 0x21;
    u32 v = *(u32 *)(b + 0x2e4c);
    if (v == 0) {
        m.b = 1000;
    } else {
        m.b = v * 1000 / *(u32 *)(b + 0x2e50);
    }
    fn_803AF5F0(a, 1, c, &m, 4);
}

void fn_803B1764(u8 *a, u8 *b, u32 c) {
    u32 v = 0x22000000;
    fn_803AF5F0(a, 1, c, &v, 4);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B1798(u8 *a, u8 *b, u32 c) {
    u8 m[8];
    m[0] = 0x23;
    u8 *q = m;
    for (s32 i = 0; i < (s32)BattleSystem_GetMaxBattlers((BattleSystem *)a); i++) {
        q[i + 4] = b[i + 0x219c];
    }
    fn_803AF5F0(a, 1, c, m, 8);
}
}

#pragma pop

extern "C" {

void fn_803B1820(u8 *a, u32 b) {
    u32 v = 0x24000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1908(u8 *a, u32 b) {
    u32 v = 0x1000000;
    fn_803AF5F0(a, 0x0, b, &v, 4);
}

void fn_803B1BF0(u8 *a, u32 b) {
    u32 v = 0x28000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1C28(u8 *a, u32 b) {
    u32 v = 0x29000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1C60(u8 *a, u8 *b, u32 c, u16 d) {
    Msg4 m;
    m.cmd = 0x2a;
    m.b = d;
    m.a = b[c * 0xc0 + 0x2d67];
    fn_803AF5F0(a, 1, c, &m, 4);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B1CA8(u8 *a, u32 b, u32 c, u32 d) {
    BattleIO_ClearBuffer((BattleContext *)((u8 *)BattleSystem_GetBattleContext((BattleSystem *)a)), b);
    Msg4 m;
    m.b = c;
    m.cmd = 0x2b;
    m.a = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}
}

#pragma pop

extern "C" {

void fn_803B1D18(u8 *a, u32 b, u32 c, u32 d) {
    Msg4b m;
    m.cmd = 0x2c;
    m.a = c;
    m.b = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B1E18(u8 *a, u32 b) {
    u32 v = 0x2e000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1E50(u8 *a, u32 b) {
    u32 v = 0x2f000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1E88(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x30, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}

void fn_803B1EE8(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x31, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}

void fn_803B1F48(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x32, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}

void fn_803B1FA8(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x33, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}

void fn_803B2008(u8 *a) {
    u32 v = 0x34000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2040(u8 *a) {
    u32 v = 0x35000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2078(u8 *a, u32 b, u32 c, u32 d) {
    Msg4 m;
    m.cmd = 0x36;
    m.a = c;
    m.b = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B20B8(u8 *a, u32 b) {
    u32 v = 0x37000000;
    if (BattleSystem_GetBattleType((BattleSystem *)a) & 4) {
        fn_803AF5F0(a, 1, b, &v, 4);
    }
}

void fn_803B21EC(u8 *a, u32 b) {
    u32 v = 0x39000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B2224(u8 *a, u32 b) {
    u32 v = 0x3a000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B225C(u8 *a) {
    u32 v = 0x3b000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803B2294(u8 *a, u8 *b) {
    Msg4 m;
    m.cmd = 0x3c;
    m.a = 0;
    for (s32 i = 0; i < (s32)BattleSystem_GetMaxBattlers((BattleSystem *)a); i++) {
        if (*(u32 *)(b + i * 16 + 0x21a8) == 0x10) {
            m.a |= FlagIndex(i);
        }
    }
    fn_803AF5F0(a, 1, 0, &m, 4);
}
}

#pragma pop

extern "C" {

void fn_803B2334(u8 *a) {
    u32 v = 0x3d000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2440(u8 *a, u8 *b, u32 c) {
    Msg4 m;
    m.cmd = 0x3f;
    u32 f = *(u32 *)(b + 0x216c);
    if (f & 2) {
        m.a = 2;
    } else if (f & 4) {
        m.a = 1;
    } else {
        m.a = 0;
    }
    fn_803AF5F0(a, 1, c, &m, 4);
}

void fn_803B24A8(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x40;
    m.b = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}

void fn_803B24E4(u8 *a) {
    Msg8 m;
    m.cmd = 0x41;
    m.v = fn_803ADCD8(a);
    fn_803AF5F0(a, 1, 0, &m, 8);
}

void fn_803B2538(u8 *a) {
    u32 v = 0x42000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2570(u32 a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = c;
    m.a = fn_803D9848(a, b);
    fn_803AF5F0((u8 *)a, 2, b, &m, 4);
}
}
