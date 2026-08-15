#include ".unsorted/80177C24.hpp"

#include "gs/GScache.hpp"
#include "types/pokemonDeck.hpp"
#include "types/trainerDeck.hpp"

extern "C" void fn_803DB678(void *to, u32 attrId, void *from);

struct UnkStruct2 {
    /* 0x00 */ u8 _00[0x88];
    /* 0x88 */ u8 _88;
    /* 0x89 */ u8 _89;
    /* 0x8A */ s8 _8A;
};

struct UnkStruct1 {
    /* 0x00 */ u8 _00[0x30];
    /* 0x30 */ UnkStruct2 *_30[6];
    /* 0x48 */ UnkStruct2 *_48[6];
};

bool Battle::fn_8017A754(u32 coloId, TrainerDeckEntry *trainer, UnkStruct1 *_r6) {
    PokemonDeck *pokeDeck = (PokemonDeck *)GScache::getCacheEntryBuffer(0xc8, fn_8017831C(coloId));

    if (!pokeDeck) {
        return false;
    }

    PokemonDeckEntry *deckEntries = pokeDeck->mEntries;

    if (!deckEntries) {
        return false;
    }

    PokemonDeckEntry *entries[6];

    for (s32 i = 0; i < trainer->mTeamSize; i++) {
        UnkStruct2 *unk = _r6->_48[i];
    
        entries[i] = deckEntries + trainer->mPokeDeckStart + i;
        fn_80178E10(unk, entries[i], _r6, 0xff);
    }

    for (s32 i = trainer->mTeamSize; i < 6; i++) {
        UnkStruct2 *unk = _r6->_48[i];
        u32 species = 0;
        fn_803DB678(unk, 0x5, &species);
        unk->_88 = 0;
        unk->_89 = 0;
        unk->_8A &= ~(0x80);
    }

    if (_71) {
        PokemonDeckEntry *result[6];
        fn_8017A028(pokeDeck, entries, result, 6, 0x54, 0x18C);

        for (s32 i = 0; i < 6; i++) {
            fn_80178E10(_r6->_30[i], result[i], _r6, 0xff);
        }
    }

    return true;
}
