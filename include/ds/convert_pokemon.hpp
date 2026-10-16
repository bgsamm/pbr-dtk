#pragma once

#include "ds/pokemon.hpp"

/*
 * Pokemon in the format of the DS games: little-endian and encrypted. The
 * bitfields are declared in reverse so that they fall on the same bits as on
 * the DS.
 */

// size: 0x2
union DSBoxPokemonFlags {
    u16 raw;
    struct {
        u16 unused : 13;
        u16 checksumFailed : 1;
        u16 boxDecrypted : 1;
        u16 partyDecrypted : 1;
    } bits;
};

// size: 0x88
struct DSBoxPokemon {
    /* 0x0 */ u32 personality;
    /* 0x4 */ DSBoxPokemonFlags flags;
    /* 0x6 */ u16 checksum;
    /* 0x8 */ u16 data[0x40];
};

// size: 0x64
struct DSPartyPokemon {
    /* 0x0 */ u32 status;
    /* 0x4 */ u8 level;
    /* 0x5 */ u8 ballCapsuleID;
    /* 0x6 */ u16 hp;
    /* 0x8 */ u16 maxHP;
    /* 0xA */ u16 attack;
    /* 0xC */ u16 defense;
    /* 0xE */ u16 speed;
    /* 0x10 */ u16 spAtk;
    /* 0x12 */ u16 spDef;
    /* 0x14 */ u8 mail[0x38];
    /* 0x4C */ u8 ballCapsule[0x18];
};

// size: 0xEC
struct DSPokemon {
    /* 0x0 */ u32 personality;
    /* 0x4 */ DSBoxPokemonFlags flags;
    /* 0x6 */ u16 checksum;
    /* 0x8 */ u16 data[0x40];
    /* 0x88 */ DSPartyPokemon party;
};

// size: 0x4
union DSPokemonIVs {
    u32 raw;
    struct {
        u32 hasNickname : 1;
        u32 isEgg : 1;
        u32 spDefIV : 5;
        u32 spAtkIV : 5;
        u32 speedIV : 5;
        u32 defIV : 5;
        u32 atkIV : 5;
        u32 hpIV : 5;
    } bits;
};

// size: 0x20
struct DSPokemonDataBlockB {
    /* 0x0 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x8 */ u8 moveCurrentPPs[LEARNED_MOVES_MAX];
    /* 0xC */ u8 movePPUps[LEARNED_MOVES_MAX];
    /* 0x10 */ DSPokemonIVs ivs;
    /* 0x14 */ u32 ribbonsGBA;
    /* 0x18 */ u8 form : 5;
    /* 0x18 */ u8 gender : 2;
    /* 0x18 */ u8 fatefulEncounter : 1;
    /* 0x19 */ u8 unused1;
    /* 0x1A */ u16 unused2;
    /* 0x1C */ u32 unused3;
};

// size: 0x20
struct DSPokemonDataBlockD {
    /* 0x0 */ u16 otName[TRAINER_NAME_LEN + 1];
    /* 0x10 */ u8 eggYear;
    /* 0x11 */ u8 eggMonth;
    /* 0x12 */ u8 eggDay;
    /* 0x13 */ u8 metYear;
    /* 0x14 */ u8 metMonth;
    /* 0x15 */ u8 metDay;
    /* 0x16 */ u16 eggLocation;
    /* 0x18 */ u16 metLocation;
    /* 0x1A */ u8 pokerus;
    /* 0x1B */ u8 pokeball;
    /* 0x1C */ u8 otGender : 1;
    /* 0x1C */ u8 metLevel : 7;
    /* 0x1D */ u8 metTerrain;
    /* 0x1E */ u16 unused;
};

// size: 0x5A8
struct DSParty {
    /* 0x0 */ u32 capacity;
    /* 0x4 */ u32 currentCount;
    /* 0x8 */ DSPokemon pokemon[MAX_PARTY_SIZE];
};

struct Party;

void fn_803E02B4(u16 *data, u32 size, u32 seed);
u32 DSPokemon_GetDataChecksum(u16 *data, u32 size);
BOOL DSPokemon_ExitDecryptionContext(DSPokemon *mon, BOOL encrypt);
BOOL DSPokemon_EnterDecryptionContext(DSPokemon *mon);
BOOL DSBoxPokemon_EnterDecryptionContext(DSBoxPokemon *boxMon);
void *DSBoxPokemon_GetDataBlock(DSBoxPokemon *boxMon, u32 personality, u32 blockID);
void BoxPokemon_FromDS(DSBoxPokemon *src, BoxPokemon *dst);
void Pokemon_FromDS(DSPokemon *src, Pokemon *dst);
void Party_FromDS(DSParty *src, Party *dst);
void Pokemon_ToDS(Pokemon *src, DSPokemon *dst, BOOL encrypt);
void Party_ToDS(Party *src, DSParty *dst, BOOL encrypt);
BOOL DSBoxPokemon_IsChecksumValid(DSBoxPokemon *boxMon);
u32 DSParty_CountValidPokemon(DSParty *party);
void BoxPokemon_ResetNickname(BoxPokemon *boxMon, BOOL force);
