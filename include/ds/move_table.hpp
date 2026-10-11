#pragma once

#include "decomp.h"

#include <revolution/types.h>

#define MAX_MOVES 468

#define NARC_INDEX_MOVE_TABLE 10

enum MoveAttribute {
    MOVEATTRIBUTE_EFFECT,
    MOVEATTRIBUTE_CLASS,
    MOVEATTRIBUTE_POWER,
    MOVEATTRIBUTE_TYPE,
    MOVEATTRIBUTE_ACCURACY,
    MOVEATTRIBUTE_PP,
    MOVEATTRIBUTE_EFFECT_CHANCE,
    MOVEATTRIBUTE_RANGE,
    MOVEATTRIBUTE_PRIORITY,
    MOVEATTRIBUTE_FLAGS,
    MOVEATTRIBUTE_CONTEST_EFFECT,
    MOVEATTRIBUTE_CONTEST_TYPE,
};

// size: 0x10
struct MoveTable {
    /* 0x0 */ u16 effect;
    /* 0x2 */ u8 moveClass;
    /* 0x3 */ u8 power;
    /* 0x4 */ u8 type;
    /* 0x5 */ u8 accuracy;
    /* 0x6 */ u8 pp;
    /* 0x7 */ u8 effectChance;
    /* 0x8 */ u16 range;
    /* 0xA */ s8 priority;
    /* 0xB */ u8 flags;
    /* 0xC */ u8 contestEffect;
    /* 0xD */ u8 contestType;
    /* 0xE */ u8 padding[2];
};

void MoveTable_Load(MoveTable *moveTable);
u32 MoveTable_LoadParam(u32 move, u32 param);
u8 MoveTable_CalcMaxPP(u32 move, u8 ppUps);
u32 MoveTable_Get(MoveTable *entry, u32 param) NO_INLINE;
void MoveTable_LoadEntry(u32 move, MoveTable *entry);
