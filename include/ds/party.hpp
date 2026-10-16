#pragma once

#include "ds/pokemon.hpp"

// size: 0x3E0
struct Party {
    /* 0x0 */ s32 capacity;
    /* 0x4 */ s32 currentCount;
    /* 0x8 */ Pokemon pokemon[MAX_PARTY_SIZE];
};

s32 Party_SaveSize();
Party *Party_New(u32 heapId);
void Party_Init(Party *party);
void Party_InitWithCapacity(Party *party, s32 capacity);
BOOL Party_AddPokemon(Party *party, Pokemon *mon);
Pokemon *fn_803DE8F0(Pokemon *dst, const Pokemon *src);
s32 Party_GetCurrentCount(const Party *party);
Pokemon *Party_GetPokemonBySlotIndex(const Party *party, s32 slot);
void Party_Copy(const Party *src, Party *dst);
