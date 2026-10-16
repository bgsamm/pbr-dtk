#pragma once

#include <revolution.h>

struct PokemonDeck;
struct PokemonDeckEntry;
struct TrainerDeckEntry;

struct UnkStruct1;
struct UnkStruct2;

class Battle {
private:
    u32 fn_8017831C(u32 coloId);
    void fn_80178E10(UnkStruct2 *_r4, PokemonDeckEntry *pokemon, UnkStruct1 *_r6, u32 _r7);
    void fn_8017A028(
        PokemonDeck *pokeDeck, PokemonDeckEntry **entries, PokemonDeckEntry **result, u32 count, u32 start, u32 end);
    bool fn_8017A754(u32 coloId, TrainerDeckEntry *trainer, UnkStruct1 *_r6);

private:
    /* 0x00 */ u8 _00[0x71];
    /* 0x71 */ u8 _71;
};
