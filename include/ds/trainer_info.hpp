#pragma once

#include <revolution/types.h>

#define MONEY_MAX 999999

// size: 0x20
struct TrainerInfo {
    /* 0x0 */ u16 name[8];
    /* 0x10 */ u32 id;
    /* 0x14 */ u32 money;
    /* 0x18 */ u8 gender;
    /* 0x19 */ u8 language;
    /* 0x1A */ u8 badgeMask;
    /* 0x1B */ u8 appearance;
    /* 0x1C */ u8 gameCode;
    /* 0x1D */ u8 unk1D[0x3];
};

s32 fn_803DA018(const TrainerInfo *info);
TrainerInfo *TrainerInfo_New(u32 heapId);
void TrainerInfo_Copy(const TrainerInfo *src, TrainerInfo *dst);
void TrainerInfo_SetName(TrainerInfo *info, const u16 *name);
const u16 *TrainerInfo_Name(const TrainerInfo *info);
u32 TrainerInfo_ID(const TrainerInfo *info);
u32 TrainerInfo_Gender(const TrainerInfo *info);
s32 TrainerInfo_BadgeCount(const TrainerInfo *info);
u32 TrainerInfo_Money(const TrainerInfo *info);
u32 TrainerInfo_GiveMoney(TrainerInfo *info, u32 money);
u32 TrainerInfo_TakeMoney(TrainerInfo *info, u32 money);
u8 TrainerInfo_GameCode(const TrainerInfo *info);
