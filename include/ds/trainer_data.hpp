#pragma once

#include <revolution/types.h>

#define NARC_INDEX_TRAINER_DATA 58
#define NARC_INDEX_TRAINER_PARTY 59

BOOL Trainer_HasMessageType(int trainerID, int msgType, int heapID);
BOOL Trainer_Load(u32 trainerID, void *trainerData);
BOOL Trainer_LoadParty(u32 trainerID, void *trainerParty);

// Only the fields used so far (pokeplatinum TrainerHeader).
// size: 0x14
struct TrainerHeader {
    /* 0x0 */ u8 monDataType;
    /* 0x1 */ u8 trainerType;
    /* 0x2 */ u8 sprite;
    /* 0x3 */ u8 partySize;
    /* 0x4 */ u16 items[4];
    /* 0xC */ u32 aiMask;
    /* 0x10 */ u32 battleType;
};

// pokeplatinum Trainer with the TrainerHeader fields in line: Battle_Main copies them one by one.
// size: 0x2C (stride of BattleSystem::trainers)
struct Trainer {
    /* 0x0 */ u8 monDataType;
    /* 0x1 */ u8 trainerType;
    /* 0x2 */ u8 sprite;
    /* 0x3 */ u8 partySize;
    /* 0x4 */ u16 items[4];
    /* 0xC */ u32 aiMask;
    /* 0x10 */ u32 battleType;
    /* 0x14 */ u16 name[8];
    /* 0x24 */ u32 unk24;
    /* 0x28 */ u32 unk28;
};
