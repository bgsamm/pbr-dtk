#pragma once

#include "decomp.h"
#include "ds/constants/abilities.hpp"
#include "ds/constants/moves.hpp"
#include "ds/constants/species.hpp"

#include <revolution/types.h>

/*
 * Pokemon data, inherited from Pokemon Diamond and Pearl. Names follow
 * pret/pokeplatinum; the MON_DATA values follow pret/pokediamond, which the
 * game uses (they differ from Platinum from MON_DATA_NICKNAME on).
 * Unlike on the DS, the data blocks are not encrypted.
 */

#define MAX_PARTY_SIZE 6
#define LEARNED_MOVES_MAX 4
#define MAX_POKEMON_LEVEL 100
#define MON_NAME_LEN 10
#define TRAINER_NAME_LEN 7

#define SPECIES_NONE 0
#define SPECIES_NIDORAN_F 29
#define SPECIES_NIDORAN_M 32
#define SPECIES_SHEDINJA 292
#define SPECIES_DEOXYS 386
#define SPECIES_WORMADAM 413
#define SPECIES_EGG 494
#define SPECIES_BAD_EGG 495

#define MOVE_TABLE_FULL 0xFFFF
#define MOVE_ALREADY_KNOWN 0xFFFE

#define HOLD_EFFECT_FRIENDSHIP_UP 52

#define NUM_NATURES 25
#define POKEBALL_LUXURY 11

enum PokemonDataParam {
    MON_DATA_PERSONALITY              = 0,
    MON_DATA_IS_PARTY_DECRYPTED       = 1,
    MON_DATA_IS_BOX_DECRYPTED         = 2,
    MON_DATA_CHECKSUM_FAILED          = 3,
    MON_DATA_CHECKSUM                 = 4,
    MON_DATA_SPECIES                  = 5,
    MON_DATA_HELD_ITEM                = 6,
    MON_DATA_OT_ID                    = 7,
    MON_DATA_EXPERIENCE               = 8,
    MON_DATA_FRIENDSHIP               = 9,
    MON_DATA_ABILITY                  = 10,
    MON_DATA_MARKINGS                 = 11,
    MON_DATA_LANGUAGE                 = 12,
    MON_DATA_HP_EV                    = 13,
    MON_DATA_ATK_EV                   = 14,
    MON_DATA_DEF_EV                   = 15,
    MON_DATA_SPEED_EV                 = 16,
    MON_DATA_SPATK_EV                 = 17,
    MON_DATA_SPDEF_EV                 = 18,
    MON_DATA_COOL                     = 19,
    MON_DATA_BEAUTY                   = 20,
    MON_DATA_CUTE                     = 21,
    MON_DATA_SMART                    = 22,
    MON_DATA_TOUGH                    = 23,
    MON_DATA_SHEEN                    = 24,
    MON_DATA_SINNOH_CHAMP_RIBBON      = 25,
    MON_DATA_UNUSED_RIBBON_53         = 53,
    MON_DATA_MOVE1                    = 54,
    MON_DATA_MOVE2                    = 55,
    MON_DATA_MOVE3                    = 56,
    MON_DATA_MOVE4                    = 57,
    MON_DATA_MOVE1_PP                 = 58,
    MON_DATA_MOVE2_PP                 = 59,
    MON_DATA_MOVE3_PP                 = 60,
    MON_DATA_MOVE4_PP                 = 61,
    MON_DATA_MOVE1_PP_UPS             = 62,
    MON_DATA_MOVE2_PP_UPS             = 63,
    MON_DATA_MOVE3_PP_UPS             = 64,
    MON_DATA_MOVE4_PP_UPS             = 65,
    MON_DATA_MOVE1_MAX_PP             = 66,
    MON_DATA_MOVE2_MAX_PP             = 67,
    MON_DATA_MOVE3_MAX_PP             = 68,
    MON_DATA_MOVE4_MAX_PP             = 69,
    MON_DATA_HP_IV                    = 70,
    MON_DATA_ATK_IV                   = 71,
    MON_DATA_DEF_IV                   = 72,
    MON_DATA_SPEED_IV                 = 73,
    MON_DATA_SPATK_IV                 = 74,
    MON_DATA_SPDEF_IV                 = 75,
    MON_DATA_IS_EGG                   = 76,
    MON_DATA_HAS_NICKNAME             = 77,
    MON_DATA_COOL_RIBBON              = 78,
    MON_DATA_WORLD_RIBBON             = 109,
    MON_DATA_FATEFUL_ENCOUNTER        = 110,
    MON_DATA_GENDER                   = 111,
    MON_DATA_FORM                     = 112,
    MON_DATA_UNUSED_113               = 113,
    MON_DATA_UNUSED_114               = 114,
    MON_DATA_UNUSED_115               = 115,
    MON_DATA_NICKNAME                 = 116,
    MON_DATA_NICKNAME_FLAT_COMPARE    = 117,
    MON_DATA_NICKNAME_STRING          = 118,
    MON_DATA_NICKNAME_STRING_AND_FLAG = 119,
    MON_DATA_UNUSED_120               = 120,
    MON_DATA_MET_GAME                 = 121,
    MON_DATA_SUPER_COOL_RIBBON        = 122,
    MON_DATA_UNUSED_RIBBON_142        = 142,
    MON_DATA_OT_NAME                  = 143,
    MON_DATA_OT_NAME_STRING           = 144,
    MON_DATA_EGG_YEAR                 = 145,
    MON_DATA_EGG_MONTH                = 146,
    MON_DATA_EGG_DAY                  = 147,
    MON_DATA_MET_YEAR                 = 148,
    MON_DATA_MET_MONTH                = 149,
    MON_DATA_MET_DAY                  = 150,
    MON_DATA_EGG_LOCATION             = 151,
    MON_DATA_MET_LOCATION             = 152,
    MON_DATA_POKERUS                  = 153,
    MON_DATA_POKEBALL                 = 154,
    MON_DATA_MET_LEVEL                = 155,
    MON_DATA_OT_GENDER                = 156,
    MON_DATA_MET_TERRAIN              = 157,
    MON_DATA_RESERVED_158             = 158,
    MON_DATA_STATUS                   = 159,
    MON_DATA_LEVEL                    = 160,
    MON_DATA_BALL_CAPSULE_ID          = 161,
    MON_DATA_HP                       = 162,
    MON_DATA_MAX_HP                   = 163,
    MON_DATA_ATK                      = 164,
    MON_DATA_DEF                      = 165,
    MON_DATA_SPEED                    = 166,
    MON_DATA_SP_ATK                   = 167,
    MON_DATA_SP_DEF                   = 168,
    MON_DATA_MAIL                     = 169,
    MON_DATA_BALL_CAPSULE             = 170,
    MON_DATA_SPECIES_EXISTS           = 171,
    MON_DATA_SANITY_IS_EGG            = 172,
    MON_DATA_SPECIES_OR_EGG           = 173,
    MON_DATA_COMBINED_IVS             = 174,
    MON_DATA_NO_PRINT_GENDER          = 175,
    MON_DATA_TYPE_1                   = 176,
    MON_DATA_TYPE_2                   = 177,
    MON_DATA_SPECIES_NAME             = 178,
};

enum SpeciesDataParam {
    SPECIES_DATA_BASE_HP               = 0,
    SPECIES_DATA_BASE_ATK              = 1,
    SPECIES_DATA_BASE_DEF              = 2,
    SPECIES_DATA_BASE_SPEED            = 3,
    SPECIES_DATA_BASE_SP_ATK           = 4,
    SPECIES_DATA_BASE_SP_DEF           = 5,
    SPECIES_DATA_TYPE_1                = 6,
    SPECIES_DATA_TYPE_2                = 7,
    SPECIES_DATA_CATCH_RATE            = 8,
    SPECIES_DATA_BASE_EXP              = 9,
    SPECIES_DATA_EV_HP_YIELD           = 10,
    SPECIES_DATA_EV_ATK_YIELD          = 11,
    SPECIES_DATA_EV_DEF_YIELD          = 12,
    SPECIES_DATA_EV_SPEED_YIELD        = 13,
    SPECIES_DATA_EV_SP_ATK_YIELD       = 14,
    SPECIES_DATA_EV_SP_DEF_YIELD       = 15,
    SPECIES_DATA_HELD_ITEM_COMMON      = 16,
    SPECIES_DATA_HELD_ITEM_RARE        = 17,
    SPECIES_DATA_GENDER_RATIO          = 18,
    SPECIES_DATA_HATCH_CYCLES          = 19,
    SPECIES_DATA_BASE_FRIENDSHIP       = 20,
    SPECIES_DATA_EXP_RATE              = 21,
    SPECIES_DATA_EGG_GROUP_1           = 22,
    SPECIES_DATA_EGG_GROUP_2           = 23,
    SPECIES_DATA_ABILITY_1             = 24,
    SPECIES_DATA_ABILITY_2             = 25,
    SPECIES_DATA_GREAT_MARSH_FLEE_RATE = 26,
    SPECIES_DATA_BODY_COLOR            = 27,
    SPECIES_DATA_FLIP_SPRITE           = 28,
    SPECIES_DATA_TM_LEARNSET_MASK_1    = 29,
    SPECIES_DATA_TM_LEARNSET_MASK_2    = 30,
    SPECIES_DATA_TM_LEARNSET_MASK_3    = 31,
    SPECIES_DATA_TM_LEARNSET_MASK_4    = 32,
};

#define GENDER_RATIO_MALE_ONLY 0
#define GENDER_RATIO_FEMALE_ONLY 254
#define GENDER_RATIO_NO_GENDER 255

#define GENDER_MALE 0
#define GENDER_FEMALE 1
#define GENDER_NONE 2

// size: 0x20
struct PokemonDataBlockA {
    /* 0x0 */ u16 species;
    /* 0x2 */ u16 heldItem;
    /* 0x4 */ u32 otID;
    /* 0x8 */ u32 exp;
    /* 0xC */ u8 friendship;
    /* 0xD */ u8 ability;
    /* 0xE */ u8 markings;
    /* 0xF */ u8 originLanguage;
    /* 0x10 */ u8 hpEV;
    /* 0x11 */ u8 atkEV;
    /* 0x12 */ u8 defEV;
    /* 0x13 */ u8 speedEV;
    /* 0x14 */ u8 spAtkEV;
    /* 0x15 */ u8 spDefEV;
    /* 0x16 */ u8 cool;
    /* 0x17 */ u8 beauty;
    /* 0x18 */ u8 cute;
    /* 0x19 */ u8 smart;
    /* 0x1A */ u8 tough;
    /* 0x1B */ u8 sheen;
    /* 0x1C */ u32 ribbonsDS1;
};

// size: 0x20
struct PokemonDataBlockB {
    /* 0x0 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x8 */ u8 moveCurrentPPs[LEARNED_MOVES_MAX];
    /* 0xC */ u8 movePPUps[LEARNED_MOVES_MAX];
    /* 0x10 */ u32 hpIV : 5;
    /* 0x10 */ u32 atkIV : 5;
    /* 0x10 */ u32 defIV : 5;
    /* 0x10 */ u32 speedIV : 5;
    /* 0x10 */ u32 spAtkIV : 5;
    /* 0x10 */ u32 spDefIV : 5;
    /* 0x10 */ u32 isEgg : 1;
    /* 0x10 */ u32 hasNickname : 1;
    /* 0x14 */ u32 ribbonsGBA;
    /* 0x18 */ u8 fatefulEncounter : 1;
    /* 0x18 */ u8 gender : 2;
    /* 0x18 */ u8 form : 5;
    /* 0x19 */ u8 unused1;
    /* 0x1A */ u16 unused2;
    /* 0x1C */ u32 unused3;
};

// size: 0x20
struct PokemonDataBlockC {
    /* 0x0 */ u16 nickname[MON_NAME_LEN + 1];
    /* 0x16 */ u8 unused;
    /* 0x17 */ u8 originGame;
    /* 0x18 */ u64 ribbonsDS2;
};

// size: 0x20
struct PokemonDataBlockD {
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
    /* 0x1C */ u8 metLevel : 7;
    /* 0x1C */ u8 otGender : 1;
    /* 0x1D */ u8 metTerrain;
    /* 0x1E */ u16 unused;
};

enum PokemonDataBlockID {
    DATA_BLOCK_A = 0,
    DATA_BLOCK_B = 1,
    DATA_BLOCK_C = 2,
    DATA_BLOCK_D = 3,
};

// size: 0x88
struct BoxPokemon {
    /* 0x0 */ u32 personality;
    /* 0x4 */ u16 partyDecrypted : 1;
    /* 0x4 */ u16 boxDecrypted : 1;
    /* 0x4 */ u16 checksumFailed : 1;
    /* 0x4 */ u16 unused : 13;
    /* 0x6 */ u16 checksum;
    /* 0x8 */ u8 data[0x80];
};

// size: 0x1C (0x88 to 0xA4 in Pokemon); the DS version also holds the mail and the ball capsule
struct PartyPokemon {
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
    /* 0x14 */ u8 unk14[0x8];
};

// size: 0xA4
struct Pokemon {
    /* 0x0 */ BoxPokemon box;
    /* 0x88 */ PartyPokemon party;
};

// size: 0x2C
struct SpeciesData {
    /* 0x0 */ u8 baseHP;
    /* 0x1 */ u8 baseAttack;
    /* 0x2 */ u8 baseDefense;
    /* 0x3 */ u8 baseSpeed;
    /* 0x4 */ u8 baseSpAttack;
    /* 0x5 */ u8 baseSpDefense;
    /* 0x6 */ u8 types[2];
    /* 0x8 */ u8 catchRate;
    /* 0x9 */ u8 baseExpReward;
    /* 0xA */ u16 hpYield : 2;
    /* 0xA */ u16 attackYield : 2;
    /* 0xA */ u16 defenseYield : 2;
    /* 0xA */ u16 speedYield : 2;
    /* 0xA */ u16 spAttackYield : 2;
    /* 0xA */ u16 spDefenseYield : 2;
    /* 0xA */ u16 padding_0A : 4;
    /* 0xC */ u16 wildHeldItems[2];
    /* 0x10 */ u8 genderRatio;
    /* 0x11 */ u8 hatchCycles;
    /* 0x12 */ u8 baseFriendship;
    /* 0x13 */ u8 expRate;
    /* 0x14 */ u8 eggGroups[2];
    /* 0x16 */ u8 abilities[2];
    /* 0x18 */ u8 greatMarshFleeRate;
    /* 0x19 */ u8 bodyColor : 7;
    /* 0x19 */ u8 flipSprite : 1;
    /* 0x1A */ u8 padding_1A[2];
    /* 0x1C */ u32 tmLearnsetMasks[4];
};

struct Party;

void Pokemon_Init(Pokemon *mon);
u32 Pokemon_StructSize();
Pokemon *Pokemon_New(u32 heapId);
BOOL Pokemon_ExitDecryptionContext(Pokemon *mon, BOOL encrypt);
BOOL BoxPokemon_EnterDecryptionContext(BoxPokemon *boxMon);
BOOL BoxPokemon_ExitDecryptionContext(BoxPokemon *boxMon, BOOL encrypt);
void Pokemon_InitWith(
    Pokemon *mon, u32 species, u32 level, u32 ivs, BOOL useMonPersonality, u32 monPersonality, u32 otIDType, u32 otID);
void BoxPokemon_InitWith(BoxPokemon *boxMon,
                         u32 species,
                         u32 level,
                         u32 ivs,
                         BOOL useMonPersonality,
                         u32 monPersonality,
                         u32 otIDType,
                         u32 otID);
void Pokemon_CalcLevelAndStats(Pokemon *mon);
void Pokemon_CalcStats(Pokemon *mon);
BoxPokemon *fn_803DAE24(BoxPokemon *dst, const BoxPokemon *src);
u32 fn_803DAE64(u32 side, s32 slot, u32 param, void *dest);
u32 BoxPokemon_GetValue(BoxPokemon *boxMon, u32 param, void *dest);
u32 BoxPokemon_GetDataInternal(BoxPokemon *boxMon, s32 param, void *dest);
void Pokemon_SetValue(Pokemon *mon, u32 param, const void *value);
void BoxPokemon_SetValue(BoxPokemon *boxMon, u32 param, const void *value);
SpeciesData *SpeciesData_FromMonSpecies(s32 species, u32 heapId);
u32 SpeciesData_GetValue(SpeciesData *speciesData, u32 param) NO_INLINE;
void SpeciesData_Free(SpeciesData *speciesData);
u32 SpeciesData_GetFormValue(s32 species, s32 form, u32 param) NO_INLINE;
u32 SpeciesData_GetSpeciesValue(s32 species, u32 param);
u8 Pokemon_GetPercentToNextLevel(Pokemon *mon);
u32 Pokemon_GetCurrentLevelBaseExp(Pokemon *mon);
u32 Pokemon_GetSpeciesBaseExpAt(s32 species, s32 level) NO_INLINE;
u32 BoxPokemon_GetLevel(BoxPokemon *boxMon);
u32 Pokemon_GetSpeciesLevelAt(u16 species, u32 exp) NO_INLINE;
u32 SpeciesData_GetLevelAt(SpeciesData *speciesData, u16 species, u32 exp);
u8 BoxPokemon_GetNature(BoxPokemon *boxMon);
u16 Pokemon_GetNatureStatValue(u8 nature, u16 statValue, u8 statType);
void Pokemon_UpdateFriendship(Pokemon *mon, u8 event, u16 mapID);
u8 Pokemon_GetGender(Pokemon *mon);
u8 BoxPokemon_GetGender(BoxPokemon *boxMon);
u8 Pokemon_GetGenderOf(u16 species, u32 personality);
u8 SpeciesData_GetGenderOf(SpeciesData *speciesData, u16 species, u32 personality);
u8 BoxPokemon_IsShiny(BoxPokemon *boxMon);
u8 Pokemon_IsPersonalityShiny(u32 otID, u32 personality);
// TODO probably LoadPokemonSpriteYOffset (pret): the battle controller passes it a species, gender, face, form
// and personality.
u8 fn_803DC160(u16 species, u8 gender, int face, u8 formNum, u32 personality);
u32 Pokemon_GetStructSize();
u8 Pokemon_GetUnownLetterOf(u32 personality);
BoxPokemon *Pokemon_GetBoxPokemon(Pokemon *mon);
BOOL Pokemon_ShouldLevelUp(Pokemon *mon);
void BoxPokemon_SetDefaultMoves(BoxPokemon *boxMon);
u16 BoxPokemon_AddMove(BoxPokemon *boxMon, u16 move);
void BoxPokemon_ReplaceMove(BoxPokemon *boxMon, u16 move);
void Pokemon_SetMoveSlot(Pokemon *mon, u16 move, u8 slot);
void BoxPokemon_SetMoveSlot(BoxPokemon *boxMon, u16 move, u8 slot);
u16 Pokemon_LevelUpMove(Pokemon *mon, s32 *index, u16 *move);
void Pokemon_FromBoxPokemon(BoxPokemon *boxMon, Pokemon *mon);
u8 Party_GetMaxLevel(Party *party);
void Pokemon_Copy(Pokemon *src, Pokemon *dst);
void BoxPokemon_Copy(BoxPokemon *src, BoxPokemon *dst);
s8 Pokemon_GetFlavorAffinity(Pokemon *mon, s32 flavor);
s8 Pokemon_GetFlavorAffinityOf(u32 personality, s32 flavor);
void Pokemon_ApplyPokerus(Party *party);
u8 Pokemon_HasPokerus(Party *party, u8 mask);
void Pokemon_ValidatePokerus(Party *party);
u8 Pokemon_GetArceusTypeOf(u16 holdEffect);
void fn_803DCD20(s32 index, u16 *moves);
void Pokemon_LoadLevelUpMovesOf(s32 species, s32 form, u16 *moves);
BOOL Pokemon_CanLearnTM(Pokemon *mon, u8 tm);
BOOL CanPokemonFormLearnTM(u16 species, u32 form, u8 tm);
void SpeciesData_LoadSpecies(s32 species, SpeciesData *speciesData);
u16 Pokemon_GetDataChecksum(void *data, u32 bytes);
void *BoxPokemon_GetDataBlock(BoxPokemon *boxMon, u32 personality, u32 blockID);
s32 Pokemon_GetFormNarcIndex(s32 species, s32 form);
u32 FlagIndex(s32 num);
s32 LowestBit(u32 flag);
BOOL Pokemon_EnterDecryptionContext(Pokemon *mon);
u32 Pokemon_GetValue(Pokemon *mon, u32 param, void *dest);
void BoxPokemon_SetDataInternal(BoxPokemon *boxMon, u32 param, const void *value);
void Pokemon_IncreaseValue(Pokemon *mon, u32 param, s32 value);
void BoxPokemon_IncreaseDataInternal(BoxPokemon *boxMon, u32 param, s32 value);
void Pokemon_LoadExperienceTableOf(s32 expRate, u32 *expTable);
u32 Pokemon_GetExpRateBaseExpAt(s32 expRate, s32 level);
