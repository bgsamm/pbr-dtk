#include "ds/trainer_data.hpp"

#include "ds/DSbridge.hpp"

// This game has no trainer messages in the DS data: the battle engine never finds one.
BOOL Trainer_HasMessageType(int trainerID, int msgType, int heapID) {
    return FALSE;
}

BOOL Trainer_Load(u32 trainerID, void *trainerData) {
    return NARC_ReadWholeMemberByIndexPair(trainerData, NARC_INDEX_TRAINER_DATA, trainerID);
}

BOOL Trainer_LoadParty(u32 trainerID, void *trainerParty) {
    return NARC_ReadWholeMemberByIndexPair(trainerParty, NARC_INDEX_TRAINER_PARTY, trainerID);
}
