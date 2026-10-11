#include "ds/party.hpp"

#include "ds/trainer_data.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
}

s32 Party_SaveSize() {
    return sizeof(Party);
}

Party *Party_New(u32 heapId) {
    Party *party = (Party *)fn_8016DF70(heapId, sizeof(Party));
    Party_InitWithCapacity(party, MAX_PARTY_SIZE);
    return party;
}

void Party_Init(Party *party) {
    Party_InitWithCapacity(party, MAX_PARTY_SIZE);
}

void Party_InitWithCapacity(Party *party, s32 capacity) {
    memset(party, 0, sizeof(Party));
    party->capacity = capacity;
    party->currentCount = 0;
    for (s32 i = 0; i < MAX_PARTY_SIZE; i++) {
        Pokemon_Init(&party->pokemon[i]);
    }
}

BOOL Party_AddPokemon(Party *party, Pokemon *mon) {
    if (party->currentCount >= party->capacity) {
        return FALSE;
    }
    fn_803DE8F0(&party->pokemon[party->currentCount], mon);
    party->currentCount++;
    return TRUE;
}
// TODO Copies a Pokemon (box, then party data) and returns dst, like an implicit operator=.

Pokemon *fn_803DE8F0(Pokemon *dst, const Pokemon *src) {
    *dst = *src;
    return dst;
}

s32 Party_GetCurrentCount(const Party *party) {
    return party->currentCount;
}

Pokemon *Party_GetPokemonBySlotIndex(const Party *party, s32 slot) {
    return (Pokemon *)&party->pokemon[slot];
}

void Party_Copy(const Party *src, Party *dst) {
    *dst = *src;
}
// This game has no trainer messages in the DS data: the battle engine never finds one.
BOOL Trainer_HasMessageType(int trainerID, int msgType, int heapID) {
    return FALSE;
}
