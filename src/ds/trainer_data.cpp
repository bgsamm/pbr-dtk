#include "ds/trainer_data.hpp"

#include "ds/DSbridge.hpp"

BOOL Trainer_Load(u32 trainerID, void *trainerData) {
    return NARC_ReadWholeMemberByIndexPair(trainerData, NARC_INDEX_TRAINER_DATA, trainerID);
}

BOOL Trainer_LoadParty(u32 trainerID, void *trainerParty) {
    return NARC_ReadWholeMemberByIndexPair(trainerParty, NARC_INDEX_TRAINER_PARTY, trainerID);
}
