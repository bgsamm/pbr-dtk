#include ".unsorted/8038F424.hpp"

extern "C" {

u8 *fn_803A60D8(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x194);
    memset(m, 0, 0x194);
    m[0x184] = b[0];
    m[0x185] = b[1];
    return m;
}

void fn_803a6138(u8 *a, u8 *b) {
    u8 i = b[0x84];
    if (i) {
        lbl_80405048[i](a, b);
    }
}

void fn_803a6160(u8 *a, u8 *b, s32 c) {
    if (c != 2) {
        fn_803D9808(b + 0x28);
    }
    fn_803D9850(b);
    fn_8016E0A0(b);
}

void fn_803A61A8(void) {}

void fn_803A61AC(u8 *a, u8 *b) {
    fn_803A7418();
    fn_803B2570((u32)a, b[0x184], 1);
    b[0x84] = 0;
}

void fn_803A61FC(u8 *a, u8 *b) {
    fn_803A742C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6234(u8 *a, u8 *b) {
    fn_803A74B8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A626C(u8 *a, u8 *b) {
    fn_803A7524(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A62A4(u8 *a, u8 *b) {
    fn_803A75A0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A62DC(u8 *a, u8 *b) {
    fn_803A7628(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6314(u8 *a, u8 *b) {
    fn_803D9804(*(u32 *)(b + 0x20));
    fn_803B2570((u32)a, b[0x184], 7);
    b[0x84] = 0;
}

void fn_803A6368(u8 *a, u8 *b) {
    fn_803A7694(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A63A0(u8 *a, u8 *b) {
    fn_803A7708(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A63D8(u8 *a, u8 *b) {
    fn_803A7774(a, b);
    b[0x84] = 0;
}

void fn_803A640C(u8 *a, u8 *b) {
    fn_803A77E4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6444(u8 *a, u8 *b) {
    fn_803A7858(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A647C(u8 *a, u8 *b) {
    fn_803A78CC(a, b);
    b[0x84] = 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A64B0(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    fn_803ADCC0(a, b[0xad]);
    fn_803A7940(a, b, c);
    b[0x84] = 0;
}
}

#pragma pop

extern "C" {

void fn_803A6508(u8 *a, u8 *b) {
    fn_803A7AB8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6540(u8 *a, u8 *b) {
    fn_803A7B88(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6578(u8 *a, u8 *b) {
    fn_803A7C9C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A65B0(u8 *a, u8 *b) {
    fn_803A7DC8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A65E8(u8 *a, u8 *b) {
    fn_803A7EAC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6620(u8 *a, u8 *b) {
    fn_803A7F44(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6658(u8 *a, u8 *b) {
    fn_803A8010(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6690(u8 *a, u8 *b) {
    fn_803A80A8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A66C8(u8 *a, u8 *b) {
    if (fn_803D97FC(*(u32 *)(b + 0x20), 2) == 1) {
        fn_803B2570((u32)a, b[0x184], 0x17);
    } else {
        fn_803A828C(a, b);
    }
    b[0x84] = 0;
}

void fn_803A6738(u8 *a, u8 *b) {
    fn_803A82EC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6770(u8 *a, u8 *b) {
    fn_803A83B4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A67A8(u8 *a, u8 *b) {
    fn_803A8444(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A67E0(u8 *a, u8 *b) {
    fn_803A84C0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6818(u8 *a, u8 *b) {
    fn_803A84CC(a, b);
    b[0x84] = 0;
}

void fn_803A684C(u8 *a, u8 *b) {
    fn_803A853C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6884(u8 *a, u8 *b) {
    fn_803A85A8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A68BC(u8 *a, u8 *b) {
    fn_803A85B4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A68F4(u8 *a, u8 *b) {
    fn_803A8620(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A692C(u8 *a, u8 *b) {
    fn_803A87D0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6964(u8 *a, u8 *b) {
    fn_803A8980(a, b);
    b[0x84] = 0;
}

void fn_803A6998(u8 *a, u8 *b) {
    fn_803A8B14(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A69D0(u8 *a, u8 *b) {
    fn_803A9068(a, b);
    b[0x84] = 0;
}

void fn_803A6A04(u8 *a, u8 *b) {
    fn_803A90D0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6A3C(u8 *a, u8 *b) {
    fn_803A9264(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6BA4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}

void fn_803A6BE0(u8 *a, u8 *b) {
    fn_803D980C(b + 0x28);
    fn_803D9850(b);
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}

void fn_803A6D0C(u8 *a, u8 *b) {
    fn_803A9270(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6D44(u8 *a, u8 *b) {
    fn_803A92F4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6D7C(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}

void fn_803A6DB8(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x2e);
    b[0x84] = 0;
}

void fn_803A6DF4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x2f);
    b[0x84] = 0;
}

void fn_803A6E30(u8 *a, u8 *b) {
    fn_803A9360(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6E68(u8 *a, u8 *b) {
    fn_803A93CC(a, b, b + 0x84);
    b[0x84] = 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A6EA0(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    if ((u8)BattleSystem_GetBattlerSide((BattleSystem *)a, b[0x184])) {
        fn_803A9438(a, b, c);
    } else {
        fn_803B2570((u32)a, b[0x184], 0x32);
    }
    b[0x84] = 0;
}

void fn_803A6F14(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    if ((u8)BattleSystem_GetBattlerSide((BattleSystem *)a, b[0x184])) {
        fn_803A94A4(a, b, c);
    } else {
        fn_803B2570((u32)a, b[0x184], 0x33);
    }
    b[0x84] = 0;
}
}

#pragma pop

extern "C" {

void fn_803A6F88(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x34);
    b[0x84] = 0;
}

void fn_803A6FC4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x35);
    b[0x84] = 0;
}

void fn_803A7000(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}

void fn_803A703C(u8 *a, u8 *b) {
    fn_803A9510(a, b);
    b[0x84] = 0;
}

void fn_803A7070(u8 *a, u8 *b) {
    fn_803A951C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A70A8(u8 *a, u8 *b) {
    fn_803A9528(a, b);
    b[0x84] = 0;
}

void fn_803A70DC(u8 *a, u8 *b) {
    fn_803A9590(a, b);
    b[0x84] = 0;
}

void fn_803A7110(u8 *a, u8 *b) {
    fn_803A95A4(a, b);
    b[0x84] = 0;
}

void fn_803A7144(u8 *a, u8 *b) {
    fn_803A975C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A717C(u8 *a, u8 *b) {
    fn_803A989C(a, b);
    b[0x84] = 0;
}

void fn_803A71B0(u8 *a, u8 *b) {
    fn_803A99A0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A71E8(u8 *a, u8 *b) {
    fn_803A99AC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A7220(u8 *a, u8 *b) {
    fn_803A99B8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A73DC(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x42);
    b[0x84] = 0;
}

void fn_803A7418(void) {
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB190), (void *)0, 0);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A742C(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x2c);
    m[0x12] = 0;
    *(u8 **)m = a;
    m[0x10] = c[0];
    m[0x11] = b[0x184];
    *(u16 *)(m + 0x16) = *(u16 *)(c + 2);
    *(u32 *)(m + 0x18) = *(u32 *)(c + 8);
    *(u32 *)(m + 0x1c) = b[0x185];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A99C4), (void *)m, 0);
}

void fn_803A74B8(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xa4);
    m[0x88] = c[0];
    m[0x89] = b[0x184];
    *(u8 **)m = a;
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9A18), (void *)m, 0);
}

void fn_803A7524(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xa4);
    m[0x8b] = 0;
    *(u8 **)m = a;
    m[0x88] = c[0];
    m[0x89] = b[0x184];
    *(u16 *)(m + 0x8e) = *(u16 *)(c + 2);
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9A6C), (void *)m, 0);
}

void fn_803A75A0(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x74);
    *(u8 **)m = a;
    m[0x68] = c[0];
    m[0x69] = b[0x184];
    *(u8 **)(m + 4) = b;
    *(u32 *)(m + 8) = *(u32 *)(b + 0x20);
    m[0x6b] = 0;
    m[0x6c] = c[1];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9AC0), (void *)m, 0);
}

void fn_803A7628(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9B14), (void *)m, 0);
}

void fn_803A7694(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x24);
    *(u8 **)m = a;
    m[0x10] = c[0];
    m[0x11] = b[0x184];
    m[0x12] = 0;
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9B68), (void *)m, 0);
}

void fn_803A7708(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x1c);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9BBC), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A7774(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = b[0x84];
    m[9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9C10), (void *)m, 0);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A77E4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = c[0];
    m[9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9C64), (void *)m, 0);
}

void fn_803A7858(u8 *a, u8 *b, u8 *c) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    q[0x18] = b[0x184];
    q[0x40] = c[0];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803A9CB8), (void *)q, 1000);
}

void fn_803A78CC(u8 *a, u8 *b) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    q[0x18] = b[0x184];
    q[0x40] = b[0x84];
    *(u32 *)(q + 0x10) = (u32)fn_803DEF00((Unk8063D230Func)((void *)fn_803A9D0C), (void *)q, 1000);
}
}

#pragma pop

extern "C" {

void fn_803A7C68(S8 *d, S8 *s) {
    *d = *s;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A7EAC(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x1c);
    m[0xe] = 0;
    *(u8 **)m = a;
    m[0xc] = c[0];
    m[0xd] = b[0x184];
    *(u8 **)(m + 4) = b + 0x28;
    *(u32 *)(m + 0x10) = *(u16 *)(c + 2);
    m[0xf] = c[1];
    *(u16 *)(m + 0x18) = *(u32 *)(c + 4);
    *(u32 *)(m + 0x14) = *(u32 *)(c + 8);
    fn_803DEF00((Unk8063D230Func)(*(void **)(b + 0x14)), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A828C(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xc);
    *(u8 **)m = a;
    m[8] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AAE74), (void *)m, 0);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A83B4(u8 *a, u8 *b, u8 *c) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    u8 f = b[0x185];
    u8 cv = c[0];
    u8 bv = b[0x184];
    q[0x40] = cv;
    q[0x18] = bv;
    if (f == 0) {
        *(u32 *)(q + 0x10) = (u32)fn_803DEF00((Unk8063D230Func)((void *)fn_803AAF1C), (void *)q, 1000);
    } else {
        fn_803B2570((u32)a, bv, cv);
    }
}

void fn_803A8444(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x74);
    m[0x66] = 0;
    *(u8 **)m = a;
    m[0x64] = c[0];
    m[0x65] = b[0x184];
    *(u16 *)(m + 0x68) = *(u16 *)(c + 2);
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AAF70), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A84C0(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A84CC(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 8);
    m[6] = 0;
    *(u8 **)m = a;
    m[4] = b[0x84];
    m[5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AAFC4), (void *)m, 0);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A853C(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x68);
    *(u8 **)m = a;
    m[0x60] = c[0];
    m[0x61] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB018), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A85A8(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A85B4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x8);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB0C0), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A9068(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xc);
    *(u8 **)m = a;
    m[8] = b[0x84];
    m[9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB06C), (void *)m, 0);
}

void fn_803A9264(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803A9270(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = c[0];
    m[9] = b[0x184];
    *(u16 *)(m + 0xc) = *(u16 *)(c + 2);
    m[0xe] = c[1];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB1D0), (void *)m, 0);
}

void fn_803A92F4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB1D4), (void *)m, 0);
}

void fn_803A9360(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB228), (void *)m, 0);
}

void fn_803A93CC(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB27C), (void *)m, 0);
}

void fn_803A9438(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB228), (void *)m, 0);
}

void fn_803A94A4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB27C), (void *)m, 0);
}
}

#pragma pop

extern "C" {

void fn_803A9510(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x37);
}

void fn_803A951C(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A9528(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0xc] = b[0x84];
    m[0xd] = b[0x184];
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB2D0), (void *)m, 0);
}

void fn_803A9590(u8 *a, u8 *b) {
    fn_803DEF00((Unk8063D230Func)((void *)fn_803AB324), (void *)a, 0);
}

void fn_803A99A0(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99AC(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99B8(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99C4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9A18(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9A6C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9AC0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9B14(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9B68(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9BBC(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9C10(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9C64(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9CB8(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9D0C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9E68(u8 *a, u8 *m) {
    fn_8017C9E0(*(u32 *)m, m[9]);
    BattleSystem_GetBattleContext(*(BattleSystem **)m);
    s32 v = fn_803C93C4(*(BattleSystem **)m, m[9], 0);
    if (v == 0xff) {
        v = 1;
    }
    fn_803B07B4(*(u8 **)m, m[9], v);
    fn_803B2570(*(u32 *)m, m[9], m[8]);
    fn_8016E0A0(m);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AA430(void) {}

void fn_803AADCC(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAE20(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAE74(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[8], 0x17);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAEC8(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAF1C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAF70(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x65], b[0x64]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAFC4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB018(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x61], b[0x60]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB06C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB0C0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB114(u8 *a, u8 *m) {
    if (fn_8016E430(m[5]) == 0xff) {
        fn_803B1908(*(u8 **)m, m[5]);
        fn_803B2570(*(u32 *)m, m[5], m[4]);
        fn_8016E0A0(m);
        fn_803DEF3C((Unk8063D230 *)a);
    } else {
        fn_8016E2E4(0xc);
    }
}

void fn_803AB190(u8 *a, u8 *b) {
    if (b) {
        fn_8016E0A0(b);
    }
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB1D0(void) {}

void fn_803AB1D4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB228(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB27C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB2D0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB324(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

u8 BattlerData_GetBattlerType(BattlerData *battlerData) {
    return *(u8 *)((u8 *)battlerData + 0x185);
}

u8 fn_803AB51C(u8 *p) {
    return *(u8 *)(p + 0x186);
}

u8 *fn_803AB524(u8 *p) {
    return p + 0x28;
}

void fn_803AB52C(void) {}

void fn_803AB530(void) {}

void fn_803AC820(u32 v) {
    lbl_806405C0 = v;
}

BattleSystem *fn_803AC828(void) {
    return (BattleSystem *)lbl_806405C0;
}

s32 fn_803AC830(void) {
    return 8;
}

u32 fn_803AC838(u8 *p) {
    return *(u32 *)(p + 0x4);
}

u32 BattleSystem_GetBattleType(BattleSystem *battleSys) {
    return battleSys->battleType;
}

BattleContext *BattleSystem_GetBattleContext(BattleSystem *battleSys) {
    return battleSys->battleCtx;
}

BattlerData *BattleSystem_GetBattlerData(BattleSystem *battleSys, int battler) {
    return battleSys->battlers[battler];
}

int BattleSystem_GetMaxBattlers(BattleSystem *battleSys) {
    return battleSys->maxBattlers;
}

Party *BattleSystem_GetParty(BattleSystem *battleSys, int battler) {
    u8 *p = (u8 *)battleSys;
    u32 i = battler;
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34))) & 1))) {
        return (Party *)(*(u32 *)(p + (i) * 4 + 0x68));
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return (Party *)(*(u32 *)(p + (i & 1) * 4 + 0x68));
    }
    return (Party *)(*(u32 *)(p + (i) * 4 + 0x68));
}

int BattleSystem_GetPartyCount(BattleSystem *battleSys, int battler) {
    u8 *p = (u8 *)battleSys;
    u32 i = (u32)battler;
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34))) & 1))) {
        return Party_GetCurrentCount((const Party *)((Party *)(*(u8 **)(p + (i) * 4 + 0x68))));
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return Party_GetCurrentCount((const Party *)((Party *)(*(u8 **)(p + (i & 1) * 4 + 0x68))));
    }
    return Party_GetCurrentCount((const Party *)((Party *)(*(u8 **)(p + (i) * 4 + 0x68))));
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

Pokemon *BattleSystem_GetPartyPokemon(BattleSystem *battleSys, int battler, int partySlot) {
    u8 *p = (u8 *)battleSys;
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + battler * 4 + 0x34))) & 1))) {
        return (Pokemon *)Party_GetPokemonBySlotIndex((const Party *)((Party *)(*(u8 **)(p + battler * 4 + 0x68))), partySlot);
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return (Pokemon *)Party_GetPokemonBySlotIndex((const Party *)((Party *)(*(u8 **)(p + (battler & 1) * 4 + 0x68))), partySlot);
    }
    return (Pokemon *)Party_GetPokemonBySlotIndex((const Party *)((Party *)(*(u8 **)(p + battler * 4 + 0x68))), partySlot);
}
}

#pragma pop

extern "C" {

u32 fn_803ACA58(u8 *p) {
    return *(u32 *)(p + 0x164);
}

u32 fn_803ACA60(u8 *p) {
    return *(u32 *)(p + 0xc);
}

u32 fn_803ACA68(u8 *p) {
    return *(u32 *)(p + 0x10);
}

u8 *fn_803ACA70(u8 *p) {
    return p + 0x11ec;
}

u8 *fn_803ACA78(u8 *p) {
    return p + 0x23b2;
}

u8 *fn_803ACA80(u8 *p) {
    return p + 0x23b4;
}

u8 *fn_803ACA88(u8 *p) {
    return p + 0x23b6;
}

u32 fn_803ACA90(u8 *p) {
    return *(u32 *)(p + 0x18);
}

u16 Battler_GetTrainerID(BattleSystem *battleSys, int battler) {
    u8 *p = (u8 *)battleSys;
    u32 i = battler;
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34))) & 1))) {
        return (*(u16 *)(p + (i) * 2 + 0xa0));
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return (*(u16 *)(p + (i & 1) * 2 + 0xa0));
    }
    return (*(u16 *)(p + (i) * 2 + 0xa0));
}

u8 *fn_803ACB30(u8 *p, u32 i) {
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34))) & 1))) {
        return (p + (i) * 0x2c + 0xac);
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return (p + (i & 1) * 0x2c + 0xac);
    }
    return (p + (i) * 0x2c + 0xac);
}

TrainerInfo *BattleSystem_GetTrainerInfo(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2)
        || ((battleSys->battleType & BATTLE_TYPE_TAG)
            && (BattlerData_GetBattlerType(battleSys->battlers[battler]) & BATTLER_TYPE_SOLO_ENEMY))) {
        return battleSys->trainerInfo[battler];
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return battleSys->trainerInfo[battler & 1];
    }

    return battleSys->trainerInfo[battler];
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803ACC64(u8 *p, s32 v) {
    s32 i;
    for (i = 0; i < *(s32 *)(p + 0x44); i++) {
        if (v == (u8)BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34)))) {
            break;
        }
    }
    return i;
}
}

#pragma pop

extern "C" {

u8 BattleSystem_GetBattlerType(BattleSystem *battleSys, int battler) {
    u8 *p = (u8 *)battleSys;
    s32 i = (s32)battler;
    return BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34)));
}

u8 BattleSystem_GetBattlerSide(BattleSystem *battleSys, int battler) {
    return BattlerData_GetBattlerType(battleSys->battlers[battler]) & 1;
}

s32 fn_803ACD14(u8 *p) {
    s32 v = *(s32 *)(p + 0x23c4);
    if (v > 12 || v < 0) {
        return 12;
    }
    return v;
}

u32 fn_803ACD30(u8 *p) {
    return *(u32 *)(p + 0x23cc);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

int BattleSystem_GetPartner(BattleSystem *battleSys, int battler) {
    int i;
    int maxBattlers = battleSys->maxBattlers;

    if ((battleSys->battleType & BATTLE_TYPE_DOUBLES) == FALSE) {
        return battler;
    }

    for (i = 0; i < maxBattlers; i++) {
        if (i != battler
            && (BattlerData_GetBattlerType(battleSys->battlers[i]) & 1)
                == (BattlerData_GetBattlerType(battleSys->battlers[battler]) & 1)) {
            break;
        }
    }

    return i;
}

int BattleSystem_GetEnemyInSlot(BattleSystem *battleSys, int battler, int slot) {
    u8 *p = (u8 *)battleSys;
    s32 i = (s32)battler;
    s32 m = (s32)slot;
    s32 n = *(s32 *)(p + 0x44);
    if (!(*(u32 *)(p + 0x2c) & 2)) {
        return i ^ 1;
    }
    u8 **pi = (u8 **)(p + i * 4);
    s32 j;
    for (j = 0; j < n; j++) {
        if (j != i) {
            u8 **pj = (u8 **)(p + j * 4);
            if (m == (BattlerData_GetBattlerType((BattlerData *)(pj[0x34 / 4])) & 2)) {
                u32 x = BattlerData_GetBattlerType((BattlerData *)(pi[0x34 / 4])) & 1;
                if ((u32)(BattlerData_GetBattlerType((BattlerData *)(pj[0x34 / 4])) & 1) != x) {
                    break;
                }
            }
        }
    }
    return j;
}
}

#pragma pop

extern "C" {

u32 fn_803ADB9C(u8 *p) {
    return *(u32 *)(p + 0x23d0);
}

u8 fn_803ADBA4(u8 *p) {
    return *(u8 *)(p + 0x23c0);
}

u32 fn_803ADBAC(u8 *p) {
    return *(u32 *)(p + 0x23d8);
}

s32 fn_803ADBB4(u8 *a) {
    return 1;
}

s32 fn_803ADBBC(void) {
    return 0;
}

s32 fn_803ADBC4(void) {
    return 1;
}

u32 fn_803ADBCC(u8 *p, u32 i) {
    if ((*(u32 *)(p + 0x2c) & 8) || ((*(u32 *)(p + 0x2c) & 0x10) && (BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34))) & 1))) {
        return (*(u32 *)(p + (i) * 4 + 0x78));
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return (*(u32 *)(p + (i & 1) * 4 + 0x78));
    }
    return (*(u32 *)(p + (i) * 4 + 0x78));
}

void fn_803ADC64(u8 *p, s32 i, u32 v) {
    p[i + 0x23dc] |= FlagIndex(v);
}

int BattleSystem_GetFieldWeather(BattleSystem *battleSys) {
    return *(u32 *)((u8 *)battleSys + 0x23f0);
}

void fn_803ADCB8(u8 *p, u32 v) {
    *(u32 *)(p + 0x2404) = v;
}

void fn_803ADCC0(u8 *p, u8 v) {
    *(u8 *)(p + 0x2408) = v;
}

u8 *fn_803ADCC8(u8 *p, s32 i) {
    return fn_803AB524(*(u8 **)(p + i * 4 + 0x34));
}

u8 fn_803ADCD8(u8 *p) {
    return *(u8 *)(p + 0x23e4);
}

void fn_803ADCE0(u8 *p, u8 v) {
    *(u8 *)(p + 0x23e4) = v;
}

void fn_803ADCE8(u8 *p, u32 v) {
    ((BF_3_2_3 *)(p + 0x23c3))->b = v;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803ADCF8(u8 *p, u8 *out) {
    for (s32 i = 0; i < *(s32 *)(p + 0x44); i++) {
        out[(u8)BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34)))] = i;
    }
}

void fn_803ADD64(u8 *p, u8 *out) {
    u8 *o;
    s32 i;
    for (i = 0; i < 4; i++) {
        out[i] = 0xff;
    }
    o = out;
    for (i = 0; i < *(s32 *)(p + 0x44); i++) {
        *o = BattlerData_GetBattlerType((BattlerData *)(*(u8 **)(p + i * 4 + 0x34)));
        o++;
    }
}

u32 fn_803ADDE8(u8 *a, u8 *b) {
    u32 i = (u8)TrainerInfo_BadgeCount((const TrainerInfo *)b);
    u32 v = lbl_80405168[i] * (Party_GetMaxLevel((Party *)a) * 4);
    u32 mx = TrainerInfo_Money((const TrainerInfo *)b);
    if (v > mx) {
        v = mx;
    }
    return v;
}
}

#pragma pop

extern "C" {

void fn_803ADE5C(u8 *a, u32 b) {}

void fn_803ADE60(u8 *p, u32 a) {
    fn_803D97E4(*(u8 **)(p + 0x60), (u16)a);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803ADE6C(u8 *a, u8 *b, Rec24 *c) {
    Rec24 tmp;
    fn_803ADEF0(&tmp, c);
    fn_803ADF40(a, (u8 *)c, 0);
    fn_803AE378(a, (u8 *)c, b, 0);
    fn_803AF334(a, (u32)b, (u8 *)c);
    fn_803D9A44(*(Strbuf **)(a + 0x18), &tmp);
}
}

#pragma pop

extern "C" {

void fn_803ADEF0(Rec24 *d, Rec24 *s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
    d->f = s->f;
}

void fn_803AF334(u8 *p, u32 a, u8 *c) {
    void *s = MessageLoader_GetNewString((const MessageLoader *)a, *(u16 *)(c + 2));
    StringTemplate_Format((const StringTemplate *)(*(u32 *)(p + 0x14)), (Strbuf *)(*(u32 *)(p + 0x18)), (const Strbuf *)s);
    Strbuf_Free((Strbuf *)s);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803AF38C(u8 *a, u8 *b, u8 *c) {
    fn_803ADF40(a, b, 1);
    fn_803AE378(a, b, c, 1);
    fn_803AF334(a, (u32)c, b);
}

u16 fn_803AF3F0(u32 v) {
    for (s32 i = 0; lbl_804732E8[i] != 0; i += 2) {
        if (v == lbl_804732E8[i]) {
            return lbl_804732E8[i + 1];
        }
    }
}
}

#pragma pop

extern "C" {

u32 fn_803AF43C(u8 *p) {
    return *(u32 *)(p + 0x23e0);
}
}
