#pragma once

#include <revolution/types.h>

#define NARC_INDEX_TRAINER_DATA 58
#define NARC_INDEX_TRAINER_PARTY 59

BOOL Trainer_Load(u32 trainerID, void *trainerData);
BOOL Trainer_LoadParty(u32 trainerID, void *trainerParty);
BOOL Trainer_HasMessageType(int trainerID, int msgType, int heapID);

// Only the name is used so far (pokeplatinum Trainer).
// size: unknown
struct Trainer {
    /* 0x0 */ u8 header[0x14];
    /* 0x14 */ u16 name[8];
};
