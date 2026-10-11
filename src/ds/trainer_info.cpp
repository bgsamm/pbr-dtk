#include "ds/trainer_info.hpp"

#include "ds/charcode_util.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
}
// TODO Always returns 0; the battle code switches on the result.

s32 fn_803DA018(const TrainerInfo *info) {
    return 0;
}

TrainerInfo *TrainerInfo_New(u32 heapId) {
    TrainerInfo *info = (TrainerInfo *)fn_8016DF70(heapId, sizeof(TrainerInfo));
    memset(info, 0, sizeof(TrainerInfo));
    return info;
}

void TrainerInfo_Copy(const TrainerInfo *src, TrainerInfo *dst) {
    memcpy(dst, src, sizeof(TrainerInfo));
}

void TrainerInfo_SetName(TrainerInfo *info, const u16 *name) {
    CharCode_Length(name);
    CharCode_Copy(info->name, name);
}

const u16 *TrainerInfo_Name(const TrainerInfo *info) {
    return info->name;
}

u32 TrainerInfo_ID(const TrainerInfo *info) {
    return info->id;
}

u32 TrainerInfo_Gender(const TrainerInfo *info) {
    return info->gender;
}

s32 TrainerInfo_BadgeCount(const TrainerInfo *info) {
    u32 mask = info->badgeMask;
    s32 count = 0;
    while (mask != 0) {
        if (mask & 1) {
            count++;
        }
        mask >>= 1;
    }
    return count;
}

u32 TrainerInfo_Money(const TrainerInfo *info) {
    return info->money;
}

u32 TrainerInfo_GiveMoney(TrainerInfo *info, u32 money) {
    if (money > MONEY_MAX) {
        info->money = MONEY_MAX;
    } else {
        info->money += money;
    }
    if (info->money > MONEY_MAX) {
        info->money = MONEY_MAX;
    }
    return info->money;
}

u32 TrainerInfo_TakeMoney(TrainerInfo *info, u32 money) {
    if (info->money < money) {
        info->money = 0;
    } else {
        info->money -= money;
    }
    return info->money;
}

u8 TrainerInfo_GameCode(const TrainerInfo *info) {
    return info->gameCode;
}
