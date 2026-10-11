#include ".unsorted/8038F424.hpp"

extern "C" {

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
        BattleController_EmitClearCommand((BattleSystem *)a, bv, cv);
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
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
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
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
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
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
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
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], 0x37);
}

void fn_803A951C(u8 *a, u8 *b, u8 *c) {
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
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
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
}

void fn_803A99AC(u8 *a, u8 *b, u8 *c) {
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
}

void fn_803A99B8(u8 *a, u8 *b, u8 *c) {
    BattleController_EmitClearCommand((BattleSystem *)a, b[0x184], c[0]);
}

void fn_803A99C4(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9A18(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9A6C(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9AC0(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9B14(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9B68(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9BBC(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9C10(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9C64(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9CB8(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)(b + 0xc)), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803A9D0C(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)(b + 0xc)), b[0x18], b[0x40]);
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
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)m), m[9], m[8]);
    fn_8016E0A0(m);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AA430(void) {}

void fn_803AADCC(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAE20(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAE74(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[8], 0x17);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAEC8(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)(b + 0xc)), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAF1C(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)(b + 0xc)), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAF70(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x65], b[0x64]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AAFC4(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB018(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x61], b[0x60]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB06C(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB0C0(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB114(u8 *a, u8 *m) {
    if (fn_8016E430(m[5]) == 0xff) {
        fn_803B1908(*(u8 **)m, m[5]);
        BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)m), m[5], m[4]);
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
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB228(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB27C(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB2D0(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

void fn_803AB324(u8 *a, u8 *b) {
    BattleController_EmitClearCommand((BattleSystem *)(*(u32 *)b), b[0xd], b[0xc]);
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
}
