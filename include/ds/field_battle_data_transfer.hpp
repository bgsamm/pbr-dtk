#pragma once

#include <revolution/types.h>

struct Bag;
struct Party;
struct TrainerInfo;

#define MAX_BATTLERS 4

// size: 0x17C
struct FieldBattleDTO {
    /* 0x0 */ u32 battleType;
    /* 0x4 */ Party *parties[MAX_BATTLERS];
    /* 0x14 */ u32 _14;
    /* 0x18 */ u8 unk18[0xC0];
    /* 0xD8 */ TrainerInfo *trainerInfo[MAX_BATTLERS];
    /* 0xE8 */ Bag *bag;
    /* 0xEC */ u32 _EC;
    /* 0xF0 */ u32 _F0;
    /* 0xF4 */ u8 unkF4[0x3C];
    /* 0x130 */ u32 _130;
    /* 0x134 */ u32 _134;
    /* 0x138 */ u8 unk138[0x8];
    /* 0x140 */ u32 _140;
    /* 0x144 */ u8 unk144[0x10];
    /* 0x154 */ u32 _154;
    /* 0x158 */ u8 unk158[0x14];
    /* 0x16C */ u32 _16C;
    /* 0x170 */ u8 unk170[0x4];
    /* 0x174 */ u32 _174;
    /* 0x178 */ u8 unk178[0x4];
};

FieldBattleDTO *FieldBattleDTO_New(u32 heapId, u32 battleType, u32 arg2, u32 arg3, u32 arg4);
