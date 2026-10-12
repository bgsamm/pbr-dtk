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
    /* 0x2 */ u8 unk2[0x12];
};

// Only the fields used so far (pokeplatinum Trainer).
// size: 0x2C (stride of BattleSystem::trainers)
struct Trainer {
    /* 0x0 */ TrainerHeader header;
    /* 0x14 */ u16 name[8];
    /* 0x24 */ u8 unk24[0x8];
};
