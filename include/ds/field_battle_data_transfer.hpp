#pragma once

#include "ds/battle/battle_constants.hpp"
#include "ds/trainer_data.hpp"

#include <revolution/types.h>

struct Bag;
struct PCBoxes;
struct Party;
struct TrainerInfo;

// size: 0x17C
struct FieldBattleDTO {
    /* 0x0 */ u32 battleType;
    /* 0x4 */ Party *parties[MAX_BATTLERS];
    /* 0x14 */ u32 resultMask;
    /* 0x18 */ u32 trainerIDs[MAX_BATTLERS];
    /* 0x28 */ Trainer trainers[MAX_BATTLERS];
    /* 0xD8 */ TrainerInfo *trainerInfo[MAX_BATTLERS];
    /* 0xE8 */ Bag *bag;
    /* 0xEC */ void *bagCursor;
    /* 0xF0 */ void *pokedex;
    /* 0xF4 */ PCBoxes *pcBoxes;
    /* 0xF8 */ void *chatotCries[MAX_BATTLERS];
    /* 0x108 */ u32 poketch;
    /* 0x10C */ u8 unk10C[0x4];
    /* 0x110 */ u32 options;
    /* 0x114 */ u32 captureAttempt;
    /* 0x118 */ u8 unk118[0xC];
    /* 0x124 */ u32 records;
    /* 0x128 */ u8 unk128[0x4];
    /* 0x12C */ u32 palPad;
    /* 0x130 */ u32 background;
    /* 0x134 */ u32 terrain;
    /* 0x138 */ u32 mapLabelTextID;
    /* 0x13C */ u8 unk13C[0x4];
    /* 0x140 */ u32 timeOfDay;
    /* 0x144 */ u32 mapEvolutionMethod;
    /* 0x148 */ u32 visitedContestHall;
    /* 0x14C */ u32 metBebe;
    /* 0x150 */ u8 unk150[0x4];
    /* 0x154 */ u32 fieldWeather;
    /* 0x158 */ int leveledUpMonsMask;
    /* 0x15C */ u32 systemVersion[MAX_BATTLERS];
    /* 0x16C */ u32 battleStatusMask;
    /* 0x170 */ int countSafariBalls;
    /* 0x174 */ u32 rulesetMask;
    /* 0x178 */ u8 unk178[0x4];
};

FieldBattleDTO *FieldBattleDTO_New(u32 heapId, u32 battleType, u32 arg2, u32 arg3, u32 arg4);
