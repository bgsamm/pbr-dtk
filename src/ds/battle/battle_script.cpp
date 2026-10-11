#include ".unsorted/8038F424.hpp"

#include "common.hpp"

extern "C" {

s32 fn_803C94CC(u8 *a, u8 *b) {
    return lbl_804056D8[*(u32 *)(b + *(u32 *)(b + 0xb4) * 4 + 0x2700)](a, b);
}

s32 fn_803C94F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803AF748(a, 0);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803C9528(u8 *a, u8 *b) {
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    s32 i;
    switch (fn_803D6E6C(b)) {
        case 0:
        default:
            for (i = 0; i < n; i++) {
                fn_803AF780(a, i);
                fn_803ADE5C(a, i);
            }
            break;
        case 3: break;
        case 4:
            for (i = 0; i < n; i++) {
                if (((u8 *)BattleSystem_GetBattlerData((BattleSystem *)a, i))[0x185] & 1) {
                    fn_803AF780(a, i);
                    fn_803ADE5C(a, i);
                }
            }
            break;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803C9F44(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803AFEB4(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CA838(u8 *a, u8 *b) {
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    for (s32 i = 0; i < n; i++) {
        fn_803B1BF0(a, i);
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CAC9C(u8 *a, u8 *b) {
    if (BattleIO_QueueIsEmpty((BattleContext *)b)) {
        (*(u32 *)(b + 0xb4))++;
    } else {
        BattleIO_UpdateTimeout((BattleContext *)b);
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on

extern "C" {

s32 fn_803CAEB8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0x2144) = 1;
    } else {
        fn_803CACF0(a, b);
        *(s32 *)(b + 0x2144) = BattleSystem_CalcDamageVariance((BattleContext *)b, *(s32 *)(b + 0x2144)) * -1;
    }
    return 0;
}
}

#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CAF20(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803CACF0(a, b);
    *(s32 *)(b + 0x2144) *= -1;
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CAF68(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (!(*(u32 *)(b + 0x213c) & 1)) {
        fn_803B0F14(a, b);
        lbl_8048CE28.pendingCommand = 7;
        lbl_8048CE28._0C = *(u32 *)(b + 0x64);
    }
    *(u32 *)(b + 0x213c) |= 1;
    *(u32 *)(b + 0x2140) |= 4;
    return 0;
}

s32 fn_803CAFE0(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x30];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    fn_803B0F68(a, b, out);
    if (lbl_8048CE28.pendingCommand == 0) {
        lbl_8048CE28.pendingCommand = 10;
    }
    return 0;
}

s32 fn_803CB070(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x30];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    out[1] |= 0x80;
    fn_803B0F68(a, b, out);
    lbl_8048CE28.pendingCommand = 10;
    return 0;
}

s32 fn_803CB100(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B0F68(a, b, b + 0xf4);
    lbl_8048CE28.pendingCommand = 10;
    return 0;
}

s32 fn_803CB144(u8 *a, u8 *b) {
    u8 buf[0x20];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, b + 0xf4);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CB1A8(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x24];
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    out[1] |= 0x40;
    *(u32 *)(out + 0x20) = fn_803D803C(a, b, n);
    fn_803B0F68(a, b, out);
    lbl_8048CE28.pendingCommand = 10;
    return 0;
}

s32 fn_803CB438(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 w = fn_803D6E6C(b);
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u16 m;
    if (w == 0xff) {
        m = *(u32 *)(b + 0x124);
    } else {
        m = *(u32 *)(b + 0x3044);
    }
    u32 rx = fn_803D803C(a, b, x);
    u32 ry = fn_803D803C(a, b, y);
    if ((!(*(u32 *)(b + 0x213c) & 0x4000) && fn_803ADBB4(a) == 1) || m == 0x90) {
        *(u32 *)(b + 0x213c) |= 0x4000;
        fn_803B0FF0(a, b, m, rx, ry);
        *(u32 *)&lbl_8048CDE8 = ry;
        *(u32 *)((u8 *)&lbl_8048CDE8 + 4) = rx;
        *(u32 *)((u8 *)&lbl_8048CDE8 + 8) = m;
        fn_8016FA4C(0x10, &lbl_8048CDE8);
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CB5B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    u8 *q = b + r * 0xc0;
    s32 d = *(s32 *)(b + 0x215c);
    s32 hp = *(s32 *)(q + 0x2d8c);
    if (d + hp <= 0) {
        *(s32 *)(b + 0x2148) = -hp;
    } else {
        *(s32 *)(b + 0x2148) = d;
    }
    if (*(s32 *)(b + 0x2148) < 0) {
        *(s32 *)(b + r * 4 + 0x164) -= *(s32 *)(b + 0x2148);
    }
    s32 nh = *(s32 *)(q + 0x2d8c) + *(s32 *)(b + 0x215c);
    *(s32 *)(q + 0x2d8c) = nh;
    if (nh < 0) {
        *(s32 *)(q + 0x2d8c) = 0;
    } else if ((u32)nh > *(u32 *)(b + r * 0xc0 + 0x2d90)) {
        *(u32 *)(q + 0x2d8c) = *(u32 *)(b + r * 0xc0 + 0x2d90);
    }
    BattleMon_CopyToParty((BattleSystem *)a, (BattleContext *)b, r);
    return 0;
}

s32 fn_803CBA04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B12A4(a, b, *(u32 *)(b + 0x74));
    *(u32 *)(b + 0x213c) &= (FlagIndex(*(u32 *)(b + 0x74)) << 24) ^ 0xffffffff;
    *(u32 *)(b + 0x2140) |= FlagIndex(*(u32 *)(b + 0x74)) << 28;
    *(u32 *)(b + *(u32 *)(b + 0x74) * 16 + 0x21a8) = 0x27;
    BattleSystem_CleanupFaintedMon((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x74));
    fn_8016E2E4(2);
    *(u32 *)&lbl_8048CDE8 = *(u32 *)(b + 0x74);
    fn_8016FA4C(0xf, &lbl_8048CDE8);
    return 0;
}

s32 fn_803CBACC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    *(u32 *)(b + 0xf0) = 0;
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CBB14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B13E0(a, (u32)b, y, fn_803D803C(a, b, x));
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CBE50(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1420(a);
    return 0;
}

s32 fn_803CBE80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    BattleSystem_LoadScript((BattleContext *)b, 2, fn_803D6E6C(b));
    return 0;
}

s32 fn_803CBED0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    BattleSystem_LoadScript((BattleContext *)b, 0x1f, *(u16 *)(b + *(u32 *)(b + 0x3044) * 16 + 0x3de));
    return 0;
}

s32 fn_803CBF18(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0x3044) = *(u32 *)(b + 0x124);
    struct BF_213C {
        u32 hi : 17;
        u32 f14 : 1;
        u32 mid : 13;
        u32 f0 : 1;
    };
    ((BF_213C *)(b + 0x213c))->f0 = 0;
    ((BF_213C *)(b + 0x213c))->f14 = 0;
    if (n == 0) {
        *(u32 *)(b + 0x6c) = BattleSystem_Defender((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x64), (u16) * (u32 *)(b + 0x3044), 1, 0);
        BattleSystem_CheckRedirectionAbilities((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x64), (u16) * (u32 *)(b + 0x124));
        *(u32 *)(b + *(u32 *)(b + 0x64) * 16 + 0x21ac) = *(u32 *)(b + 0x6c);
    }
    if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0xc) = 0x26;
        BattleSystem_LoadScript((BattleContext *)b, 2, 0x119);
    } else {
        BattleSystem_LoadScript((BattleContext *)b, 1, *(u32 *)(b + 0x3044));
    }
    *(u32 *)&lbl_8048CDE8 = *(u32 *)(b + 0x64);
    *(u32 *)((u8 *)&lbl_8048CDE8 + 4) = *(u32 *)(b + 0x3044);
    fn_8016FA4C(0x19, &lbl_8048CDE8);
    return 0;
}

s32 fn_803CC028(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if ((BattleSystem_GetBattleType((BattleSystem *)a) & 0x400) || (BattleSystem_GetBattleStatusMask((BattleSystem *)a) & 1)) {
        *(u32 *)(b + 0x2150) = 1;
    } else if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0x2150) = 1;
    } else {
        *(u32 *)(b + 0x2150) = BattleSystem_CalcCriticalMulti((BattleContext *)b, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), *(u32 *)(b + 0x214c), BattleContext_Get((BattleSystem *)a, (BattleContext *)((u32)b), (enum BattleContextParam)0, *(u32 *)(b + 0x6c)));
    }
    return 0;
}

s32 fn_803CC0D8(u8 *a, u8 *b) {
    BattleSystem_GetBattleType((BattleSystem *)a);
    (u32)BattleSystem_GetBattlerData((BattleSystem *)a, *(u32 *)(b + 0x74));
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0xb4) += n;
    return 0;
}

s32 fn_803CC140(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u8 **)(b + 0x178) = (u8 *)fn_8016DF70(5, 0x50);
    **(u8 ***)(b + 0x178) = a;
    *(u8 **)(*(u8 **)(b + 0x178) + 4) = b;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x20) = 0;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x40) = 0;
    fn_803DEF00((Unk8063D230Func)((void *)fn_803D71CC), (void *)(*(u8 **)(b + 0x178)), 0);
    return 0;
}

s32 fn_803CC1C8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x178) == 0) {
        (*(u32 *)(b + 0xb4))++;
    }
    return 0;
}

s32 fn_803CC1E8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CC4B0(u8 *a, u8 *b) {
    u8 *q;
    s32 i;
    (*(u32 *)(b + 0xb4))++;
    switch (fn_803D6E6C(b)) {
        case 1:    i = *(u32 *)(b + 0x64); break;
        case 6:    i = *(u32 *)(b + 0x78); break;
        case 0x12: i = *(u32 *)(b + 0x6c); break;
    }
    *(u32 *)(b + i * 4 + 0x13c) &= ~1;
    b[0x3108] &= FlagIndex(i) ^ 0xffffffff;
    q = b + i;
    u8 v = q[0x21a0];
    q[0x219c] = v;
    q[0x21a0] = 6;
    BattleSystem_InitBattleMon((BattleSystem *)a, (BattleContext *)b, i, v);
    BattleSystem_SwitchSlots((BattleSystem *)a, (BattleContext *)b, i, q[0x219c]);
    *(u16 *)(b + 0x3122) = *(u32 *)(b + 0x2e4c);
    BattleSystem_UpdateAfterSwitch((BattleSystem *)a, (BattleContext *)b, i);
    return 0;
}
}

#pragma pop

#pragma push
#pragma optimize_for_size on

extern "C" {

s32 fn_803CC5B4(u8 *a, u8 *b) {
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    u32 m = fn_803D6E6C(b);
    for (s32 i = 0; i < n; i++) {
        if (*(u32 *)(b + i * 4 + 0x13c) & 1) {
            *(u32 *)(b + 0x78) = i;
            *(u32 *)(b + 0xb4) += m;
            break;
        }
    }
    return 0;
}
}

#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CC648(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u8 **)(b + 0x178) = (u8 *)fn_8016DF70(5, 0x50);
    **(u8 ***)(b + 0x178) = a;
    *(u8 **)(*(u8 **)(b + 0x178) + 4) = b;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x20) = 0;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x1c) = n;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x24) = *(u32 *)(b + 0x128);
    fn_803DEF00((Unk8063D230Func)((void *)fn_803D8004), (void *)(*(u8 **)(b + 0x178)), 0);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CC6E8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x178) == 0) {
        (*(u32 *)(b + 0xb4))++;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CC708(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (b[0x217d] == 0) {
        if (x == 0) {
            if ((u8)Battler_Ability((BattleContext *)b, *(u32 *)(b + 0x64)) == 0x5c) {
                x = 5;
            } else {
                x = LCRNG_Next() & 3;
                if (x < 2) {
                    x += 2;
                } else {
                    x = (LCRNG_Next() & 3) + 2;
                }
            }
        }
        b[0x217c] = x;
        b[0x217d] = x;
        *(u32 *)(b + 0x2188) = y;
    }
    return 0;
}

s32 fn_803CD270(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    *(u32 *)(b + fn_803D803C(a, b, x) * 4 + 0x218c) |= y;
    return 0;
}

s32 fn_803CD2F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B1458(a, fn_803D803C(a, b, x), y);
    return 0;
}

s32 fn_803CD4E0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 y;
    s32 x;
    x = fn_803D6E6C(b);
    y = fn_803D6E6C(b);
    *(u32 *)(b + 0x134) = y + (s32)LCRNG_Next() % (x + 1);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CD978(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0xb4) += n;
    return 0;
}

s32 fn_803CD9C4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    BattleSystem_CallScript((BattleContext *)b, 2, fn_803D6E6C(b));
    return 0;
}

s32 fn_803CDA14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 *r = fn_803D6E8C(a, b, fn_803D6E6C(b));
    BattleSystem_CallScript((BattleContext *)b, 2, *r);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CDC28(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    s32 j;
    s32 i;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 8; j++) {
            b[i * 0xc0 + j + 0x2d58] = 6;
        }
        *(u32 *)(b + i * 0xc0 + 0x2db0) &= ~0x100000;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CDCB0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    Battler_LockMoveChoice((BattleSystem *)a, (BattleContext *)b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CDD1C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    Battler_UnlockMoveChoice((BattleSystem *)a, (BattleContext *)b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CDD88(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B1570(a, fn_803D803C(a, b, x), y);
    return 0;
}

s32 fn_803CDE04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B15AC(a, fn_803D803C(a, b, x), y);
    return 0;
}

s32 fn_803CE014(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 v;
    if (a[0x23e4] == 1) {
        v = fn_803CDE80(a, b, 1);
        if ((*(u32 *)(a + 0x2c) & 0x10) || *(u32 *)(a + 0x2c) == 0x4b) {
            v += fn_803CDE80(a, b, 3);
        }
        TrainerInfo_GiveMoney((TrainerInfo *)((u8 *)BattleSystem_GetTrainerInfo((BattleSystem *)a, 0)), v);
    } else {
        v = BattleSystem_CalcMoneyPenalty((Party *)(*(u8 **)(a + 0x68)), (TrainerInfo *)(*(u8 **)(a + 0x48)));
        TrainerInfo_TakeMoney((TrainerInfo *)((u8 *)BattleSystem_GetTrainerInfo((BattleSystem *)a, 0)), v);
    }
    if (v) {
        *(s32 *)(b + 0x130) = v;
    } else {
        *(s32 *)(b + 0x130) = 0;
    }
    return 0;
}

s32 fn_803CE560(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B16B4(a, b, r, b[r + 0x219c]);
    return 0;
}

s32 fn_803CE5D4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B1704(a, b, r, b[r + 0x219c]);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CE648(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1764(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CE6B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1798(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CE720(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B15AC(a, fn_803D803C(a, b, fn_803D6E6C(b)), *(u32 *)(b + 0x130));
    return 0;
}

s32 fn_803CED18(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 v = *(s32 *)(b + 0x14c) * *(s32 *)(b + 0x2168);
    *(s32 *)(b + 0x130) = v;
    if (v > 0xffff) {
        *(s32 *)(b + 0x130) = 0xffff;
    }
    TrainerInfo_GiveMoney((TrainerInfo *)((u8 *)BattleSystem_GetTrainerInfo((BattleSystem *)a, 0)), *(u32 *)(b + 0x130));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803CEFFC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x64));
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 0x40) {
        *(u32 *)(b + 0xb4) += n;
        *(u32 *)(b + 0x216c) |= 0x40;
    } else {
        *q |= 0x40;
        BF_1C4 *f = (BF_1C4 *)(b + k * 8 + 0x1c4);
        f->x = 5;
        f->y = *(u32 *)(b + 0x64);
    }
    return 0;
}

s32 fn_803CF3B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, x);
    *r = BattleSystem_Divide(*r, y);
    return 0;
}

s32 fn_803CF434(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    s32 *r1 = (s32 *)fn_803D6E8C(a, b, x);
    s32 *r2 = (s32 *)fn_803D6E8C(a, b, y);
    s32 s = 1;
    if (*r1 < 0) {
        s = -1;
    }
    if ((*r1 = *r1 / *r2) == 0) {
        *r1 = s;
    }
    return 0;
}

s32 fn_803CF6A4(u8 *a, u8 *b) {
    u16 v;
    s32 i;
    (*(u32 *)(b + 0xb4))++;
    do {
        do {
            v = (s32)LCRNG_Next() % 0x1d3 + 1;
            for (i = 0; i < 4; i++) {
                if (v == *(u16 *)(b + *(u32 *)(b + 0x64) * 0xc0 + i * 2 + 0x2d4c)) {
                    break;
                }
            }
        } while (i != 4);
    } while (Move_CanBeMetronomed(v) == 0);
    *(u32 *)(b + 0x124) = v;
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803CF758(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 j = Battler_SlotForMove((BattleMon *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d40), *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c));
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    u16 m;
    if (*(u16 *)(q + 0x2de8) == 0 && j != 4 && q[j + 0x2d6c] != 0 &&
        (m = *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c)) != 0) {
        *(u32 *)(b + 0x124) = m;
        *(u16 *)(q + 0x2de8) = m;
        ((BF_2DC8b *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2dc8))->t = (s32)LCRNG_Next() % 4 + 3;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

u8 fn_803D01BC(s32 a, s32 b) {
    s32 i;
    s32 v = App_PixelCount(a, b, 0x40);
    for (i = 0; i < 6; i++) {
        if (v <= lbl_80405A50[i].a) {
            break;
        }
    }
    return lbl_80405A50[i].b;
}

s32 fn_803D02D8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 i6c = *(u32 *)(b + 0x6c);
    u16 mv = *(u16 *)(b + i6c * 2 + 0x307c);
    if (mv) {
        s32 j = Battler_SlotForMove((BattleMon *)(b + i6c * 0xc0 + 0x2d40), mv);
        u8 pp;
        if (j == 4 || (pp = b[*(u32 *)(b + 0x6c) * 0xc0 + j + 0x2d6c]) == 0) {
            *(u32 *)(b + 0xb4) += n;
        } else {
            s32 d = 4;
            if (pp < 4) {
                d = pp;
            }
            *(u32 *)(b + 0x124) = *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c);
            *(s32 *)(b + 0x130) = d;
            b[*(u32 *)(b + 0x6c) * 0xc0 + j + 0x2d6c] -= d;
            BattleMon_CopyToParty((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x6c));
        }
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D091C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 q = BattleSystem_Divide(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90), 4);
    u8 *p = b + *(u32 *)(b + 0x64) * 0xc0;
    if (*(s32 *)(p + 0x2d8c) <= q) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(s32 *)(b + 0x215c) = -q;
        *(s32 *)(p + 0x2de0) = q;
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) &= ~0xe000;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D0EC8(u8 *a, u8 *b) {
    u32 k;
    BF_1C8 *f;
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x64)) ^ 1;
    f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    if (f->t == 3) {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x80000000;
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + k * 4 + 0x1bc) |= 4;
        f->t++;
    }
    return 0;
}

s32 fn_803D0F94(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 t = *(u32 *)(b + (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, r) * 8 + 0x1c8) >> 30;
    u8 *q;
    if (t && *(u32 *)((q = b + r * 0xc0) + 0x2d8c)) {
        *(s32 *)(b + 0x215c) = (5 - t) * 2;
        s32 m = *(s32 *)(q + 0x2d90);
        m *= -1;
        *(s32 *)(b + 0x215c) = BattleSystem_Divide(m, *(s32 *)(b + 0x215c));
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D1064(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 cnt = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    *(s32 *)(b + 0x134) = cnt;
    s32 k = 0;
    for (s32 i = 0; i < cnt; i++) {
        u8 *q = b + i * 0xc0;
        if ((*(u32 *)(q + 0x2dc0) & 0x20) || *(u32 *)(q + 0x2d8c) == 0 ||
            Battler_IgnorableAbility((BattleContext *)b, *(u32 *)(b + 0x64), i, 0x2b) == 1) {
            k++;
        } else {
            *(u32 *)(q + 0x2dc0) |= 0x20;
            *(u32 *)(q + 0x2dc8) |= 0x60000;
        }
    }
    if (k == cnt) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D1150(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 *r = fn_803D6E8C(a, b, fn_803D6E6C(b));
    *r = b[*(u32 *)(b + 0x3104) + 0x21ec];
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D11BC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, x);
    if (*r < (u32)BattleSystem_GetMaxBattlers((BattleSystem *)a)) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D1788(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    BF_2DC8 *f = (BF_2DC8 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dc8);
    if (f->k < 5) {
        f->k++;
    }
    *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
    for (u32 i = 1; i < ((BF_2DC8 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dc8))->k; i++) {
        *(u32 *)(b + 0x2154) *= 2;
    }
    return 0;
}

s32 fn_803D180C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 y = *(u32 *)(b + 0x118);
    u8 *px = b + *(u32 *)(b + 0x94) * 0xc0;
    u32 kx = (px[0x2dbe] >> 4) & 0xf;
    u32 ky = (b[y * 0xc0 + 0x2dbe] >> 4) & 0xf;
    if (ky == kx || (*(u32 *)(px + 0x2db0) & 0xf0000) || ky == 2 || kx == 2) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + *(u32 *)(b + 0x94) * 0xc0 + 0x2db0) |= FlagIndex(y) << 16;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D18CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x64));
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 8) {
        *(u32 *)(b + 0xb4) += n;
        *(u32 *)(b + 0x216c) |= 0x40;
    } else {
        *q |= 8;
        BF_1C4b *f = (BF_1C4b *)(b + k * 8 + 0x1c4);
        f->x = 5;
        f->y = *(u32 *)(b + 0x64);
        b[0xf5] = 1;
        *(u32 *)(b + 0xf8) = *(u32 *)(b + 0x64);
        *(u16 *)(b + 0xf6) = 0xc6;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D19A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 r = (u8)LCRNG_Next();
    if (r < 0x66) {
        *(u32 *)(b + 0x2154) = 40;
    } else if (r < 0xb2) {
        *(u32 *)(b + 0x2154) = 80;
    } else if (r < 0xcc) {
        *(u32 *)(b + 0x2154) = 120;
    } else {
        *(s32 *)(b + 0x215c) = BattleSystem_Divide(*(s32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d90), 4);
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D1A58(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (b[0x3120] == 0) {
        u8 v = (s32)LCRNG_Next() % 100;
        b[0x3120] = v;
        if (v < 5) {
            *(u32 *)(b + 0x2154) = 10;
            b[0x3120] = 4;
        } else if (v < 15) {
            *(u32 *)(b + 0x2154) = 30;
            b[0x3120] = 5;
        } else if (v < 35) {
            *(u32 *)(b + 0x2154) = 50;
            b[0x3120] = 6;
        } else if (v < 65) {
            *(u32 *)(b + 0x2154) = 70;
            b[0x3120] = 7;
        } else if (v < 85) {
            *(u32 *)(b + 0x2154) = 90;
            b[0x3120] = 8;
        } else if (v < 95) {
            *(u32 *)(b + 0x2154) = 110;
            b[0x3120] = 9;
        } else {
            *(u32 *)(b + 0x2154) = 150;
            b[0x3120] = 10;
        }
    }
    *(u32 *)(b + 0x130) = b[0x3120];
    return 0;
}

s32 fn_803D1B7C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    s32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    x = fn_803D803C(a, b, x);
    if (BattleSystem_AnyReplacementMons((BattleSystem *)a, (BattleContext *)b, x) == 0) {
        *(u32 *)(b + 0xb4) += z;
    } else if (y == 1) {
        *(u32 *)(b + x * 4 + 0x13c) |= 1;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D1DFC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if ((*(u32 *)(b + 0x180) & 0x80ff) == 0 || BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0xd) || BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0x4c)) {
        *(u32 *)(b + 0x215c) = *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90) >> 1;
    } else if (*(u32 *)(b + 0x180) & 0x30) {
        *(s32 *)(b + 0x215c) = BattleSystem_Divide(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90) * 20, 30);
    } else {
        *(s32 *)(b + 0x215c) = BattleSystem_Divide(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90), 4);
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D1F84(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    for (s32 i = 0; i < 8; i++) {
        b[*(u32 *)(b + 0x64) * 0xc0 + i + 0x2d58] = b[*(u32 *)(b + 0x6c) * 0xc0 + i + 0x2d58];
    }
    *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) |= *(u32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2db0) & 0x100000;
    return 0;
}

s32 fn_803D2168(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 w0 = fn_803D6E6C(b);
    u32 x0 = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 w = fn_803D803C(a, b, w0);
    u32 x = fn_803D803C(a, b, x0);
    fn_803B2D0C(a, b, w, x, (u32)fn_803D90A0(b, y));
    if (*(u32 *)(b + 0x216c) & 0x1fd849) {
        *(u32 *)(b + 0xb4) += z;
        *(u32 *)&lbl_8048CDE8 = x;
        fn_8016FA4C(0xb, &lbl_8048CDE8);
    }
    return 0;
}

s32 fn_803D225C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (Battler_IsTrappedMsg((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x64), (BattleMessage *)0)) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D25D4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u8 *q = b + (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x64)) * 8;
    ((BF_2700 *)(q + 0x1c4))->sel = 1;
    ((BF_2700 *)(q + 0x1c4))->who = *(u32 *)(b + 0x64);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D2634(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_GetBattleType((BattleSystem *)a) & 2) {
        u32 r = fn_803D803C(a, b, 0x10);
        if (!(b[0x3108] & FlagIndex(r)) && *(u32 *)(b + r * 16 + 0x21a8) != 0x27 && *(u32 *)(b + r * 0xc0 + 0x2d8c) &&
            !((*(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) >> 28) & 1) &&
            !((*(u32 *)(b + r * 64 + 0x1d4) >> 28) & 1)) {
            *(u32 *)(b + 0x118) = r;
            *(u32 *)(b + r * 64 + 0x1d4) |= 0x10000000;
        } else {
            *(u32 *)(b + 0xb4) += n;
        }
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D28DC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x64);
    if (q[0x18c]) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        q[0x18c] = 2;
        u8 *r = b + *(u32 *)(b + 0x64);
        r[0x1b8] = r[0x219c];
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D2AB4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 i;
    s32 c = 0;
    for (i = 0; i < (s32)BattleSystem_GetMaxBattlers((BattleSystem *)a); i++) {
        if (*(u32 *)(b + i * 0xc0 + 0x2d8c)) {
            c++;
        }
    }
    if (*(u32 *)(b + 0xec) == c - 1) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) |= 0x8000000;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D2C80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 o = *(u32 *)(b + 0x64) * 64;
    if ((*(u32 *)(b + o + *(u32 *)(b + 0x6c) * 4 + 0x1d8) != 0 &&
         (*(u32 *)(b + o + 0x1ec) & FlagIndex(*(u32 *)(b + 0x6c)))) ||
        (*(u32 *)(b + o + *(u32 *)(b + 0x6c) * 4 + 0x1f0) != 0 &&
         (*(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x204) & FlagIndex(*(u32 *)(b + 0x6c))))) {
        *(u32 *)(b + 0x2158) = 20;
    } else {
        *(u32 *)(b + 0x2158) = 10;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D2D44(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x6c));
    lbl_8048CE28._20 = 0;
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 1) {
        lbl_8048CE28._20 |= 1;
    }
    if (*q & 2) {
        lbl_8048CE28._20 |= 2;
    }
    if ((*q & 1) || (*q & 2)) {
        *q &= ~3;
        BF_1C4c *f = (BF_1C4c *)(b + k * 8 + 0x1c4);
        f->x = 0;
        f->y = 0;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D2E38(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    if (*(u32 *)(q + 0x2dc0) & 0x1800) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(q + 0x2dc0) |= 0x1000;
    }
    return 0;
}

s32 fn_803D3018(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(u32 *)(b + 0x2154) == 0) {
        u8 *q = b + *(u32 *)(b + 0x64) * 0xc0;
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * *(u32 *)(q + 0x2d8c) / *(u32 *)(q + 0x2d90);
        if (*(u32 *)(b + 0x2154) == 0) {
            *(u32 *)(b + 0x2154) = 1;
        }
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D333C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 i;
    s32 c = 0;
    for (i = 0; i < (s32)BattleSystem_GetMaxBattlers((BattleSystem *)a); i++) {
        if (*(u32 *)(b + i * 0xc0 + 0x2d8c)) {
            c++;
        }
    }
    if (*(u32 *)(b + 0xec) == c - 1) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) |= 0x4000000;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D34C8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0xd) == 0 && BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0x4c) == 0) {
        u32 fl = *(u32 *)(b + 0x180);
        if (fl & 0x80ff) {
            *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * 2;
            if (fl & 3) {
                *(u32 *)(b + 0x2160) = 11;
            }
            if (*(u32 *)(b + 0x180) & 0xc) {
                *(u32 *)(b + 0x2160) = 5;
            }
            if (*(u32 *)(b + 0x180) & 0x30) {
                *(u32 *)(b + 0x2160) = 10;
            }
            if (*(u32 *)(b + 0x180) & 0xc0) {
                *(u32 *)(b + 0x2160) = 15;
            }
        } else {
            *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
        }
    }
    return 0;
}

s32 fn_803D37FC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x2144) = BattleSystem_ApplyTypeChart((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x3044), *(u32 *)(b + 0x2160), *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), *(u32 *)(b + 0x2144), (u32 *)(b + 0x216c));
    return 0;
}

s32 fn_803D3B28(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(s32 *)(b + 0x2154) =
        *(u32 *)(b + *(u32 *)(b + 0x6c) * 4 + 0x21f0) * 25 / *(u32 *)(b + *(u32 *)(b + 0x64) * 4 + 0x21f0) + 1;
    if (*(s32 *)(b + 0x2154) > 150) {
        *(s32 *)(b + 0x2154) = 150;
    }
    return 0;
}

s32 fn_803D3D00(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(u32 *)(b + *(u32 *)(b + 0x6c) * 16 + 0x21a8) == 0x27) {
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * 2;
    } else {
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
    }
    return 0;
}

s32 fn_803D3D5C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 k = *(u32 *)(b + 0x64);
    u8 v = b[k * 0xc0 + *(u16 *)(b + k * 2 + 0x30bc) + 0x2d6c];
    if (v > 4) {
        v = 4;
    }
    *(u32 *)(b + 0x2154) = lbl_80643000[v];
    return 0;
}

s32 fn_803D3DA8(u8 *a, u8 *b) {
    u32 idx = *(u32 *)(b + 0x6c);
    u8 *q;
    (*(u32 *)(b + 0xb4))++;
    q = b + idx * 0xc0;
    *(u32 *)(b + 0x2154) = *(u32 *)(q + 0x2d8c) * 0x78 / *(u32 *)(q + 0x2d90) + 1;
    return 0;
}

s32 fn_803D3F04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (Move_IsInvoker((u16) * (u32 *)(b + 0x3048)) == 0 && *(u32 *)(b + 0x3048) != 0 &&
        Move_CanBeMetronomed((u16) * (u32 *)(b + 0x3048)) == 1) {
        *(u32 *)(b + 0x124) = *(u32 *)(b + 0x3048);
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D3F98(u8 *a, u8 *b) {
    s32 i;
    s32 s = 0;
    (*(u32 *)(b + 0xb4))++;
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    for (i = 0; i < 8; i++) {
        s8 v = q[i + 0x2d58];
        if (v > 6) {
            s = s + v - 6;
        }
    }
    *(s32 *)(b + 0x2154) = s * 20 + 60;
    if (*(s32 *)(b + 0x2154) > 200) {
        *(s32 *)(b + 0x2154) = 200;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D4008(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    u32 m = *(u16 *)(q + 0x2dec);
    if (m != 0 && m == *(u16 *)(q + *(u16 *)(q + 0x2dee) * 2 + 0x2d4c)) {
    } else {
        m = (u16)Battler_SelectedMove((BattleContext *)b, *(u32 *)(b + 0x6c));
    }
    if (*(u32 *)(b + *(u32 *)(b + 0x6c) * 16 + 0x21a8) == 0x27 ||
        (b[m * 16 + 0x3e1] == 0 && !(*(u32 *)(b + *(u32 *)(b + 0x6c) * 64 + 0x1d4) >> 31))) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

s32 fn_803D43A8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (((*(u32 *)(b + *(u32 *)(b + 0x6c) * 64 + 0x1d4) >> 29) & 1) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

s32 fn_803D440C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    if (*(u32 *)(q + 0x2dac) != 0 || (*(u32 *)(q + 0x2db0) & 0x1000000) ||
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dac) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D4494(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 k = Battler_CountMoves((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x64));
    if (((*(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc) >> 19) & 7) < (u32)(k - 1) || k < 2) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

s32 fn_803D4528(u8 *a, u8 *b) {
    u32 k;
    BF_1C8 *f;
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, *(u32 *)(b + 0x64)) ^ 1;
    f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    if (f->u == 2) {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x80000000;
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + k * 4 + 0x1bc) |= 0x400;
        f->u++;
    }
    return 0;
}

s32 fn_803D45F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, r);
    BF_1C8 *f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    u32 t = f->u;
    if (t) {
        *(u32 *)(b + 0x134) = t;
        *(u32 *)(b + 0x88) = 6;
        *(u32 *)(b + 0x94) = r;
        if (BattleMon_Get((BattleContext *)b, *(u32 *)(b + 0x78), (enum BattleMonParam)0x1b, (void *)0) == 3 || BattleMon_Get((BattleContext *)b, *(u32 *)(b + 0x78), (enum BattleMonParam)0x1c, (void *)0) == 3) {
            *(u32 *)(b + k * 4 + 0x1bc) &= ~0x400;
            f->u = 0;
            *(u32 *)(b + 0x134) = 0;
        }
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D48F8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 r1 = fn_803D803C(a, b, x);
    u32 k = (u8)BattleSystem_GetBattlerSide((BattleSystem *)a, fn_803D803C(a, b, y));
    if ((u8)BattleSystem_GetBattlerSide((BattleSystem *)a, r1) == k) {
        *(u32 *)(b + 0xb4) += z;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D4C24(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x08000000;
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D4C50(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (Battler_MovedThisTurn((BattleContext *)b, fn_803D803C(a, b, x)) == 1) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D4CDC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 w = fn_803D6E6C(b);
    u32 x = fn_803D6E6C(b);
    s32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    if (w == 0) {
        if (y == (s32)Battler_HeldItemEffect((BattleContext *)b, r)) {
            *(u32 *)(b + 0xb4) += z;
        }
    } else {
        if (y != (s32)Battler_HeldItemEffect((BattleContext *)b, r)) {
            *(u32 *)(b + 0xb4) += z;
        }
    }
    return 0;
}

s32 fn_803D4DA8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, y);
    *r = BattleSystem_GetItemData((BattleContext *)b, Battler_HeldItem((BattleContext *)b, fn_803D803C(a, b, x)), (enum ItemDataParam)1);
    return 0;
}
}

#pragma pop

extern "C" {

u8 fn_803D4EE8(u32 i) {
    if (i > 12) {
        return 0;
    }
    return lbl_80405AC1[i];
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D4F08(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if ((u8)Battler_Ability((BattleContext *)b, *(u32 *)(b + 0x64)) == 0x79) {
        *(u32 *)(b + 0xb4) += n;
        return 0;
    }
    s32 t = lbl_80405AC1[BattleSystem_GetTerrain((BattleSystem *)a)];
    if (t != BattleMon_Get((BattleContext *)b, *(u32 *)(b + 0x64), (enum BattleMonParam)0x1b, (void *)0) && t != BattleMon_Get((BattleContext *)b, *(u32 *)(b + 0x64), (enum BattleMonParam)0x1c, (void *)0)) {
        b[*(u32 *)(b + 0x64) * 0xc0 + 0x2d64] = t;
        b[*(u32 *)(b + 0x64) * 0xc0 + 0x2d65] = t;
        *(s32 *)(b + 0x130) = t;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

u16 fn_803D5004(u32 i) {
    if (i > 12) {
        return 0;
    }
    return lbl_80405ACE[(u8)i];
}

s32 fn_803D5028(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x124) = lbl_80405ACE[BattleSystem_GetTerrain((BattleSystem *)a)];
    return 0;
}

s32 fn_803D5078(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x2174) = lbl_80405AE8[BattleSystem_GetTerrain((BattleSystem *)a)];
    return 0;
}

s32 fn_803D50C8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 r = Battler_NaturalGiftPower((BattleContext *)b, *(u32 *)(b + 0x64));
    if (r) {
        *(u32 *)(b + 0x2154) = r;
        *(u32 *)(b + 0x2160) = Battler_NaturalGiftType((BattleContext *)b, *(u32 *)(b + 0x64));
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D514C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (*(u16 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2db8) != 0 &&
        Battler_IgnorableAbility((BattleContext *)b, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), 0x3c) == 1) {
        *(u32 *)(b + 0xb4) += x;
    } else if (BattleSystem_PluckBerry((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x6c)) != 1) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D520C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_FlingItem((BattleSystem *)a, (BattleContext *)b, *(u32 *)(b + 0x64)) != 1) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D5280(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B0E94(a, b, 0, 0, fn_803D6E6C(b), 0, 0);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D52EC(u8 *a, u8 *b) {
    u8 v = BattleContext_IOBufferVal((BattleContext *)b, 0);
    if (v) {
        (*(u32 *)(b + 0xb4))++;
        u32 x = fn_803D6E6C(b);
        u32 y = fn_803D6E6C(b);
        if (v == 0xff) {
            *(u32 *)(b + 0xb4) += y;
        } else {
            *(u32 *)(b + 0xb4) += x;
        }
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D5380(u8 *a, u8 *b) {
    BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    fn_803B0D6C(a, b, 0, 0, 0, 6);
    *(u32 *)(b + 0x78) = 0;
    return 0;
}

s32 fn_803D53EC(u8 *a, u8 *b) {
    u8 v = BattleContext_IOBufferVal((BattleContext *)b, 0);
    if (v) {
        (*(u32 *)(b + 0xb4))++;
        u32 n = fn_803D6E6C(b);
        if (v == 0xff) {
            *(u32 *)(b + 0xb4) += n;
        } else {
            b[0x21a0] = v - 1;
        }
    }
    return 0;
}

s32 fn_803D5470(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (BattleSystem_GetBattleType((BattleSystem *)a) & 4) {
        fn_803B24E4(a);
    }
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D5660(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u16 v;
    if ((u8)Battler_Ability((BattleContext *)b, *(u32 *)(b + 0x64)) == 0x20) {
        v = b[*(u32 *)(b + 0x3044) * 16 + 0x3e5] * 2;
    } else {
        v = b[*(u32 *)(b + 0x3044) * 16 + 0x3e5];
    }
    if ((s32)LCRNG_Next() % 100 < v && *(u32 *)(b + *(u32 *)(b + 0x94) * 0xc0 + 0x2d8c) != 0) {
        return 0;
    }
    *(u32 *)(b + 0xb4) += n;
    return 0;
}

s32 fn_803D5738(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x64) * 0xc0;
    if (*(u16 *)(q + 0x2d40) == 0x1b9 && *(u32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d8c) &&
        !(*(u32 *)(q + 0x2db0) & 0x200000)) {
        s32 p;
        switch (fn_803DA018((const TrainerInfo *)(BattleSystem_GetChatotCry((BattleSystem *)a, *(u32 *)(b + 0x64))))) {
            case 0:
            default: p = 0; break;
            case 1:  p = 10; break;
            case 2:  p = 30; break;
        }
        if ((s32)LCRNG_Next() % 100 > p) {
            *(u32 *)(b + 0xb4) += n;
        }
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D583C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 v = fn_803D6E6C(b);
    *(u32 *)(b + 0x134) = MoveTable_Get((MoveTable *)(b + *(u32 *)(b + 0x3044) * 16 + 0x3de), v);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D5898(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    fn_803B1D18(a, fn_803D803C(a, b, x), y, z);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D5924(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B1D58(a, r);
    *(u32 *)&lbl_8048CDE8 = r;
    *(u32 *)((u8 *)&lbl_8048CDE8 + 4) = ((*(u8 **)(a + 0x30))[r * 0xc0 + 0x2d66] >> 3) & 0x1f;
    fn_8016FA4C(0x16, &lbl_8048CDE8);
    return 0;
}

s32 fn_803D59BC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1E18(a, 0);
    return 0;
}

s32 fn_803D59F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    BattleSystem_UseBagItem((BattleSystem *)a, r, b[r + 0x219c], 0, *(u32 *)(b + 0x128));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D5A68(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (Battler_CanEscape((BattleSystem *)a, (BattleContext *)b, fn_803D803C(a, b, x))) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D5AF8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1E88(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D5B60(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1EE8(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D5BC8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1F48(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D5C30(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1FA8(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D5C98(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2008(a);
    return 0;
}

s32 fn_803D5CC8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2040(a);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D5CF8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    fn_803B2078(a, fn_803D803C(a, b, x), y, z);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D5D84(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2118(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D5DF0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_TriggerAbilityOnHit((BattleSystem *)a, (BattleContext *)b, (int *)(b + 0x138)) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

s32 fn_803D5E64(u8 *a, u8 *b) {
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    s32 c = fn_803D6E6C(b);
    s32 i;
    switch (c) {
        case 3:
            for (i = 0; i < n; i++) {
                if (!(((u8 *)BattleSystem_GetBattlerData((BattleSystem *)a, i))[0x185] & 1)) {
                    fn_803B21EC(a, i);
                }
            }
            break;
        case 4:
            for (i = 0; i < n; i++) {
                if (((u8 *)BattleSystem_GetBattlerData((BattleSystem *)a, i))[0x185] & 1) {
                    fn_803B21EC(a, i);
                }
            }
            break;
        default: fn_803B21EC(a, fn_803D803C(a, b, c)); break;
    }
    return 0;
}

s32 fn_803D5F64(u8 *a, u8 *b) {
    s32 n = BattleSystem_GetMaxBattlers((BattleSystem *)a);
    (*(u32 *)(b + 0xb4))++;
    s32 c = fn_803D6E6C(b);
    s32 i;
    switch (c) {
        case 3:
            for (i = 0; i < n; i++) {
                if (!(((u8 *)BattleSystem_GetBattlerData((BattleSystem *)a, i))[0x185] & 1)) {
                    fn_803B2224(a, i);
                }
            }
            break;
        case 4:
            for (i = 0; i < n; i++) {
                if (((u8 *)BattleSystem_GetBattlerData((BattleSystem *)a, i))[0x185] & 1) {
                    fn_803B2224(a, i);
                }
            }
            break;
        default: fn_803B2224(a, fn_803D803C(a, b, c)); break;
    }
    return 0;
}

s32 fn_803D62F0(u8 *a, u8 *b) {
    s32 buf[7];
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 cnt = 0;
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    for (s32 i = 1; i < 8; i++) {
        if ((s8)q[i + 0x2d58] < 12) {
            buf[cnt] = i - 1;
            cnt++;
        }
    }
    if (cnt) {
        *(u32 *)(b + 0x2170) = (buf[(s32)LCRNG_Next() % cnt] + 0x27) | 0x80000000;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D63CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    *(u16 *)(b + r * 2 + 0x3124) = *(u16 *)(b + r * 0xc0 + 0x2db8);
    *(u16 *)(b + r * 0xc0 + 0x2db8) = 0;
    BattleMon_CopyToParty((BattleSystem *)a, (BattleContext *)b, r);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D6458(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u16 *q = (u16 *)(b + *(u32 *)(b + 0x64) * 2 + 0x3124);
    if (*q) {
        *(u32 *)(b + 0x128) = *q;
        *q = 0;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

s32 fn_803D64CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_TriggerHeldItemOnHit((BattleSystem *)a, (BattleContext *)b, (int *)(b + 0x138)) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D6540(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B225C(a);
    return 0;
}

s32 fn_803D6570(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2294(a, b);
    return 0;
}

s32 fn_803D65A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2334(a);
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D65D0(u8 *a, u8 *b) {
    u32 r;
    s32 hit = 0;
    (*(u32 *)(b + 0xb4))++;
    r = fn_803D803C(a, b, fn_803D6E6C(b));
    s32 ab = Battler_HeldItemEffect((BattleContext *)b, r);
    s32 v = Battler_HeldItemPower((BattleContext *)b, r, (enum HeldItemPowerOp)0);
    if (ab == 0x40 && (s32)LCRNG_Next() % 100 < v) {
        hit = 1;
    }
    if (ab == 0x66 && *(u32 *)(b + r * 0xc0 + 0x2d8c) == *(u32 *)(b + r * 0xc0 + 0x2d90)) {
        hit = 1;
    }
    if (hit) {
        s32 hp = *(s32 *)(b + r * 0xc0 + 0x2d8c);
        if (*(s32 *)(b + 0x215c) + hp <= 0) {
            *(s32 *)(b + 0x215c) = -(hp - 1);
            *(u32 *)(b + 0x216c) |= 0x100;
            *(u32 *)((u8 *)&lbl_8048CE28 + 0x1c) = 1;
        }
    }
    return 0;
}

s32 fn_803D66F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 o = r * 0xc0;
    if (*(u32 *)(b + o + 0x2d8c) && b[r + 0x219c] != 6) {
        u8 *m = (u8 *)BattleSystem_GetPartyPokemon((BattleSystem *)a, r, b[r + 0x219c]);
        u32 v1 = Pokemon_GetValue((Pokemon *)m, 10, (void *)0);
        u32 v2 = Pokemon_GetValue((Pokemon *)m, 0x9f, (void *)0);
        if ((b + o)[0x2d67] != 0x1e && Ability_ForbidsStatus((BattleContext *)b, v1, v2) == 0) {
            *(u32 *)(b + 0xb4) += y;
        }
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D67F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    if ((*(u32 *)(b + r * 0xc0 + 0x2db0) & 0x1000000) || (*(u32 *)(b + r * 0x1c + 0x2e8) & 8)) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

s32 fn_803D6894(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0xd) || BattleSystem_CountAbility((BattleSystem *)a, (BattleContext *)b, (enum CountAbilityMode)8, 0, 0x4c)) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D6930(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x6c) = BattleSystem_RandomOpponent((BattleSystem *)a, (BattleContext *)b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D69A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (BattleSystem_TriggerHeldItemOnPivotMove((BattleSystem *)a, (BattleContext *)b, (int *)(b + 0x138)) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D6A14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B236C(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D6A80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2440(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

s32 fn_803D6AEC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B24A8(a, fn_803D803C(a, b, x), y);
    return 0;
}
}

#pragma pop

extern "C" {

s32 fn_803D6B68(void) {
    return 0;
}

void fn_803D6B70(u8 *a, u8 *b) {
    BattleSystem_PopScript((BattleContext *)b);
}

s32 fn_803D6B78(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    lbl_8048CE28._0C = fn_803D803C(a, b, fn_803D6E6C(b));
    return 0;
}

s32 fn_803D6BE0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    return 0;
}

u32 fn_803D6E6C(u8 *p) {
    u32 i = *(u32 *)(p + 0xb4);
    u32 r = *(u32 *)(p + i * 4 + 0x2700);
    *(u32 *)(p + 0xb4) = i + 1;
    return r;
}

void fn_803D8004(u8 *a, u8 *b) {
    fn_8016E0A0(b);
    fn_803DEF3C((Unk8063D230 *)a);
}

u32 fn_803D903C(u8 *a, u8 *b, s32 c) {
    u32 r = fn_803D803C(a, b, c);
    if (c == 0x16) {
        return r | (b[r + 0x21a0] << 8);
    }
    return r | (b[r + 0x219c] << 8);
}

u8 *fn_803D90A0(u8 *p, s32 i) {
    switch (i) {
        case 1:    p = *(u8 **)(p + 0x3044); break;
        case 0xff: p = *(u8 **)(p + 0x124); break;
    }
    return p;
}

u8 *fn_803D915C(u8 *p, s32 i) {
    if (i == 0xff) {
        p = *(u8 **)(p + 0x130);
    }
    return p;
}

u8 *fn_803D916C(u8 *p, s32 i) {
    if (i == 0xff) {
        p = *(u8 **)(p + 0x130);
    }
    return p;
}

u32 fn_803D917C(u8 *a, u8 *b, s32 c) {
    u32 r;
    switch (c) {
        case 0xff: return *(u32 *)(b + 0x12c);
        default:
            r = fn_803D803C(a, b, c);
            u8 *q = b + (u8)r;
            return q[0x390] = b[r * 0xc0 + 0x2d67];
    }
}

u8 *fn_803D91D4(u8 *p, s32 i) {
    if (i == 0xff) {
        p = *(u8 **)(p + 0x130);
    }
    return p;
}

u8 *fn_803D91E4(u8 *p, s32 i) {
    if (i == 0xff) {
        p = *(u8 **)(p + 0x130);
    }
    return p;
}
}
