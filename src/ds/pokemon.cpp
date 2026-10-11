#include "ds/pokemon.hpp"

#include "ds/DSbridge.hpp"
#include "ds/charcode.hpp"
#include "ds/message.hpp"
#include "ds/message_util.hpp"
#include "ds/move_table.hpp"
#include "ds/party.hpp"
#include "ds/strbuf.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
extern Unk8063CE34 lbl_8063CE34;
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
u8 fn_8039188C(u8 **file, s32 species);
u8 fn_803918C0(u8 **file, s32 species);
u8 fn_803918F4(u8 **file, s32 species);
u8 fn_80391928(u8 **file, s32 species);
u8 fn_8039195C(u8 **file, s32 species);
u8 fn_80391990(u8 **file, s32 species);
u8 fn_803919C4(u8 **file, s32 species);
u8 fn_803919F8(u8 **file, s32 species);
u8 fn_80391A2C(u8 **file, s32 species);
u8 fn_80391A60(u8 **file, s32 species);
u32 fn_80391A94(u8 **file, s32 species);
u32 fn_80391ACC(u8 **file, s32 species);
u32 fn_80391B04(u8 **file, s32 species);
u32 fn_80391B3C(u8 **file, s32 species);
u32 fn_80391B74(u8 **file, s32 species);
u32 fn_80391BAC(u8 **file, s32 species);
u16 fn_80391BE4(u8 **file, s32 species);
u16 fn_80391C18(u8 **file, s32 species);
u8 fn_80391C4C(u8 **file, s32 species);
u8 fn_80391C80(u8 **file, s32 species);
u8 fn_80391CB4(u8 **file, s32 species);
u8 fn_80391CE8(u8 **file, s32 species);
u8 fn_80391D1C(u8 **file, s32 species);
u8 fn_80391D50(u8 **file, s32 species);
u8 fn_80391D84(u8 **file, s32 species);
u8 fn_80391DB8(u8 **file, s32 species);
u8 fn_80391E20(u8 **file, s32 species);
u32 fn_80391E54(u8 **file, s32 species);
u32 fn_80391E8C(u8 **file, s32 species);
u32 fn_80391EC4(u8 **file, s32 species);
u32 fn_80391EF8(u8 **file, s32 species);
u32 fn_80391F2C(u8 **file, s32 species);
u32 fn_80391F60(u8 **file, s32 species);
u32 fn_80392560(u8 **file, s32 expRate, u32 level);
u8 fn_80392820(u8 **file, s32 index, u32 slot);
u16 fn_80392878(u8 **file, s32 index, u32 slot);
void *fn_803AC828();
Party *fn_803AC868(void *battleParties, u32 side);

extern const u8 gGameVersion;
extern const u8 gGameLanguage;
}

/* lbl_80405BE0 */ static const s8 sNatureFlavorAffinities[NUM_NATURES][5] = {
    { 0,  0,  0,  0,  0},
    { 1,  0,  0,  0, -1},
    { 1,  0, -1,  0,  0},
    { 1, -1,  0,  0,  0},
    { 1,  0,  0, -1,  0},
    {-1,  0,  0,  0,  1},
    { 0,  0,  0,  0,  0},
    { 0,  0, -1,  0,  1},
    { 0, -1,  0,  0,  1},
    { 0,  0,  0, -1,  1},
    {-1,  0,  1,  0,  0},
    { 0,  0,  1,  0, -1},
    { 0,  0,  0,  0,  0},
    { 0, -1,  1,  0,  0},
    { 0,  0,  1, -1,  0},
    {-1,  1,  0,  0,  0},
    { 0,  1,  0,  0, -1},
    { 0,  1, -1,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  1,  0, -1,  0},
    {-1,  0,  0,  1,  0},
    { 0,  0,  0,  1, -1},
    { 0,  0, -1,  1,  0},
    { 0, -1,  0,  1,  0},
    { 0,  0,  0,  0,  0},
};

/* lbl_80405C5D */ static const s8 sNatureStatAffinities[NUM_NATURES][5] = {
    { 0,  0,  0,  0,  0},
    { 1, -1,  0,  0,  0},
    { 1,  0, -1,  0,  0},
    { 1,  0,  0, -1,  0},
    { 1,  0,  0,  0, -1},
    {-1,  1,  0,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  1, -1,  0,  0},
    { 0,  1,  0, -1,  0},
    { 0,  1,  0,  0, -1},
    {-1,  0,  1,  0,  0},
    { 0, -1,  1,  0,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  1, -1,  0},
    { 0,  0,  1,  0, -1},
    {-1,  0,  0,  1,  0},
    { 0, -1,  0,  1,  0},
    { 0,  0, -1,  1,  0},
    { 0,  0,  0,  0,  0},
    { 0,  0,  0,  1, -1},
    {-1,  0,  0,  0,  1},
    { 0, -1,  0,  0,  1},
    { 0,  0, -1,  0,  1},
    { 0,  0,  0, -1,  1},
    { 0,  0,  0,  0,  0},
};

/* lbl_80405CDA */ static const s8 sFriendshipChangeTable[10][3] = {
    { 5,  3,   2},
    { 5,  3,   2},
    { 1,  1,   0},
    { 3,  2,   1},
    { 1,  1,   0},
    { 1,  1,   1},
    {-1, -1,  -1},
    {-5, -5, -10},
    {-5, -5, -10},
    { 3,  2,   1},
};

// The original inlines these where they are used, so they exist both as functions and inline.
static inline u8 BoxPokemon_InlineGetNature(BoxPokemon *boxMon) {
    BOOL reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    u32 personality = BoxPokemon_GetValue(boxMon, MON_DATA_PERSONALITY, NULL);
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
    return personality % NUM_NATURES;
}

static inline u32 SpeciesData_InlineGetSpeciesValue(s32 species, u32 param) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u32 value;
    SpeciesData_LoadSpecies(species, speciesData);
    value = SpeciesData_GetValue(speciesData, param);
    fn_8016E0A0(speciesData);
    return value;
}

static inline u32 Pokemon_InlineGetSpeciesBaseExpAt(s32 species, s32 level) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u32 expRate;
    SpeciesData_LoadSpecies(species, speciesData);
    expRate = SpeciesData_GetValue(speciesData, SPECIES_DATA_EXP_RATE);
    fn_8016E0A0(speciesData);
    return Pokemon_GetExpRateBaseExpAt(expRate, level);
}

void Pokemon_Init(Pokemon *mon) {
    memset(mon, 0, sizeof(Pokemon));
}

u32 Pokemon_StructSize() {
    return sizeof(Pokemon);
}

Pokemon *Pokemon_New(u32 heapId) {
    Pokemon *mon = (Pokemon *)fn_8016DF70(heapId, sizeof(Pokemon));
    memset(mon, 0, sizeof(Pokemon));
    return mon;
}

BOOL Pokemon_ExitDecryptionContext(Pokemon *mon, BOOL encrypt) {
    BOOL wasDecrypted = FALSE;
    if (mon->box.partyDecrypted == TRUE && encrypt == TRUE) {
        wasDecrypted = TRUE;
        mon->box.partyDecrypted = FALSE;
        mon->box.boxDecrypted = FALSE;
        mon->box.checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
    }
    return wasDecrypted;
}

BOOL BoxPokemon_EnterDecryptionContext(BoxPokemon *boxMon) {
    BOOL wasEncrypted = FALSE;
    if (!boxMon->boxDecrypted) {
        wasEncrypted = TRUE;
        boxMon->boxDecrypted = TRUE;
    }
    return wasEncrypted;
}

BOOL BoxPokemon_ExitDecryptionContext(BoxPokemon *boxMon, BOOL encrypt) {
    BOOL wasDecrypted = FALSE;
    if (boxMon->boxDecrypted == TRUE && encrypt == TRUE) {
        wasDecrypted = TRUE;
        boxMon->boxDecrypted = FALSE;
        boxMon->checksum = Pokemon_GetDataChecksum(boxMon->data, sizeof(boxMon->data));
    }
    return wasDecrypted;
}

void Pokemon_InitWith(
    Pokemon *mon, u32 species, u32 level, u32 ivs, BOOL useMonPersonality, u32 monPersonality, u32 otIDType, u32 otID) {
    u32 zero;
    u8 ballCapsule[4];
    memset(mon, 0, sizeof(Pokemon));
    BoxPokemon_InitWith(&mon->box, species, level, ivs, useMonPersonality, monPersonality, otIDType, otID);
    Pokemon_SetValue(mon, MON_DATA_LEVEL, &level);
    zero = 0;
    Pokemon_SetValue(mon, MON_DATA_BALL_CAPSULE_ID, &zero);
    memset(ballCapsule, 0, sizeof(ballCapsule));
    Pokemon_SetValue(mon, MON_DATA_BALL_CAPSULE, ballCapsule);
    Pokemon_CalcLevelAndStats(mon);
}

void BoxPokemon_InitWith(BoxPokemon *boxMon,
                         u32 species,
                         u32 level,
                         u32 ivs,
                         BOOL useMonPersonality,
                         u32 monPersonality,
                         u32 otIDType,
                         u32 otID) {
    u32 value;
    u32 iv;
    u32 tmp;
    BOOL reencrypt;
    memset(boxMon, 0, sizeof(BoxPokemon));
    reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    if (!useMonPersonality) {
        monPersonality = LCRNG_Next() | (LCRNG_Next() << 16);
    }
    BoxPokemon_SetValue(boxMon, MON_DATA_PERSONALITY, &monPersonality);
    if ((s32)otIDType == 2) {
        do {
            otID = LCRNG_Next() | (LCRNG_Next() << 16);
        } while ((((monPersonality & 0xFFFF) ^ (monPersonality >> 16)) ^ ((otID >> 16) ^ (otID & 0xFFFF))) < 8);
    } else if ((s32)otIDType != 1) {
        otID = 0;
    }
    BoxPokemon_SetValue(boxMon, MON_DATA_OT_ID, &otID);
    tmp = gGameLanguage;
    BoxPokemon_SetValue(boxMon, MON_DATA_LANGUAGE, &tmp);
    BoxPokemon_SetValue(boxMon, MON_DATA_SPECIES, &species);
    BoxPokemon_SetValue(boxMon, MON_DATA_SPECIES_NAME, NULL);
    value = Pokemon_GetSpeciesBaseExpAt(species, level);
    BoxPokemon_SetValue(boxMon, MON_DATA_EXPERIENCE, &value);
    value = SpeciesData_InlineGetSpeciesValue(species, SPECIES_DATA_BASE_FRIENDSHIP);
    BoxPokemon_SetValue(boxMon, MON_DATA_FRIENDSHIP, &value);
    BoxPokemon_SetValue(boxMon, MON_DATA_MET_LEVEL, &level);
    tmp = gGameVersion;
    BoxPokemon_SetValue(boxMon, MON_DATA_MET_GAME, &tmp);
    value = 4;
    BoxPokemon_SetValue(boxMon, MON_DATA_POKEBALL, &value);
    if ((s32)ivs < 32) {
        BoxPokemon_SetValue(boxMon, MON_DATA_HP_IV, &ivs);
        BoxPokemon_SetValue(boxMon, MON_DATA_ATK_IV, &ivs);
        BoxPokemon_SetValue(boxMon, MON_DATA_DEF_IV, &ivs);
        BoxPokemon_SetValue(boxMon, MON_DATA_SPEED_IV, &ivs);
        BoxPokemon_SetValue(boxMon, MON_DATA_SPATK_IV, &ivs);
        BoxPokemon_SetValue(boxMon, MON_DATA_SPDEF_IV, &ivs);
    } else {
        value = LCRNG_Next();
        iv = value & 0x1F;
        BoxPokemon_SetValue(boxMon, MON_DATA_HP_IV, &iv);
        iv = (value & 0x3E0) >> 5;
        BoxPokemon_SetValue(boxMon, MON_DATA_ATK_IV, &iv);
        iv = (value & 0x7C00) >> 10;
        BoxPokemon_SetValue(boxMon, MON_DATA_DEF_IV, &iv);
        value = LCRNG_Next();
        iv = value & 0x1F;
        BoxPokemon_SetValue(boxMon, MON_DATA_SPEED_IV, &iv);
        iv = (value & 0x3E0) >> 5;
        BoxPokemon_SetValue(boxMon, MON_DATA_SPATK_IV, &iv);
        iv = (value & 0x7C00) >> 10;
        BoxPokemon_SetValue(boxMon, MON_DATA_SPDEF_IV, &iv);
    }
    value = SpeciesData_InlineGetSpeciesValue(species, SPECIES_DATA_ABILITY_1);
    iv = SpeciesData_InlineGetSpeciesValue(species, SPECIES_DATA_ABILITY_2);
    if (iv != 0) {
        if (monPersonality & 1) {
            BoxPokemon_SetValue(boxMon, MON_DATA_ABILITY, &iv);
        } else {
            BoxPokemon_SetValue(boxMon, MON_DATA_ABILITY, &value);
        }
    } else {
        BoxPokemon_SetValue(boxMon, MON_DATA_ABILITY, &value);
    }
    value = BoxPokemon_GetGender(boxMon);
    BoxPokemon_SetValue(boxMon, MON_DATA_GENDER, &value);
    BoxPokemon_SetDefaultMoves(boxMon);
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
}

void Pokemon_CalcLevelAndStats(Pokemon *mon) {
    BOOL reencrypt = Pokemon_EnterDecryptionContext(mon);
    u32 level = BoxPokemon_GetLevel(&mon->box);
    Pokemon_SetValue(mon, MON_DATA_LEVEL, &level);
    Pokemon_CalcStats(mon);
    Pokemon_ExitDecryptionContext(mon, reencrypt);
}

void Pokemon_CalcStats(Pokemon *mon) {
    BOOL reencrypt = Pokemon_EnterDecryptionContext(mon);
    s32 level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
    s32 maxHP = Pokemon_GetValue(mon, MON_DATA_MAX_HP, NULL);
    s32 hp = Pokemon_GetValue(mon, MON_DATA_HP, NULL);
    s32 hpIV = Pokemon_GetValue(mon, MON_DATA_HP_IV, NULL);
    s32 hpEV = Pokemon_GetValue(mon, MON_DATA_HP_EV, NULL);
    s32 atkIV = Pokemon_GetValue(mon, MON_DATA_ATK_IV, NULL);
    s32 atkEV = Pokemon_GetValue(mon, MON_DATA_ATK_EV, NULL);
    s32 defIV = Pokemon_GetValue(mon, MON_DATA_DEF_IV, NULL);
    s32 defEV = Pokemon_GetValue(mon, MON_DATA_DEF_EV, NULL);
    s32 speedIV = Pokemon_GetValue(mon, MON_DATA_SPEED_IV, NULL);
    s32 speedEV = Pokemon_GetValue(mon, MON_DATA_SPEED_EV, NULL);
    s32 spAtkIV = Pokemon_GetValue(mon, MON_DATA_SPATK_IV, NULL);
    s32 spAtkEV = Pokemon_GetValue(mon, MON_DATA_SPATK_EV, NULL);
    s32 spDefIV = Pokemon_GetValue(mon, MON_DATA_SPDEF_IV, NULL);
    s32 spDefEV = Pokemon_GetValue(mon, MON_DATA_SPDEF_EV, NULL);
    s32 form = Pokemon_GetValue(mon, MON_DATA_FORM, NULL);
    s32 species = Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    s32 newMaxHP;
    s32 newAttack;
    s32 newDefense;
    s32 newSpeed;
    s32 newSpAtk;
    s32 newSpDef;
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    SpeciesData_LoadSpecies(Pokemon_GetFormNarcIndex(species, form), speciesData);
    if (species == SPECIES_SHEDINJA) {
        newMaxHP = 1;
    } else {
        newMaxHP = ((2 * speciesData->baseHP + hpIV + hpEV / 4) * level / 100) + level + 10;
    }
    Pokemon_SetValue(mon, MON_DATA_MAX_HP, &newMaxHP);
    newAttack = ((2 * speciesData->baseAttack + atkIV + atkEV / 4) * level / 100) + 5;
    newAttack = Pokemon_GetNatureStatValue(BoxPokemon_InlineGetNature(&mon->box), newAttack, 1);
    Pokemon_SetValue(mon, MON_DATA_ATK, &newAttack);
    newDefense = ((2 * speciesData->baseDefense + defIV + defEV / 4) * level / 100) + 5;
    newDefense = Pokemon_GetNatureStatValue(BoxPokemon_InlineGetNature(&mon->box), newDefense, 2);
    Pokemon_SetValue(mon, MON_DATA_DEF, &newDefense);
    newSpeed = ((2 * speciesData->baseSpeed + speedIV + speedEV / 4) * level / 100) + 5;
    newSpeed = Pokemon_GetNatureStatValue(BoxPokemon_InlineGetNature(&mon->box), newSpeed, 3);
    Pokemon_SetValue(mon, MON_DATA_SPEED, &newSpeed);
    newSpAtk = ((2 * speciesData->baseSpAttack + spAtkIV + spAtkEV / 4) * level / 100) + 5;
    newSpAtk = Pokemon_GetNatureStatValue(BoxPokemon_InlineGetNature(&mon->box), newSpAtk, 4);
    Pokemon_SetValue(mon, MON_DATA_SP_ATK, &newSpAtk);
    newSpDef = ((2 * speciesData->baseSpDefense + spDefIV + spDefEV / 4) * level / 100) + 5;
    newSpDef = Pokemon_GetNatureStatValue(BoxPokemon_InlineGetNature(&mon->box), newSpDef, 5);
    Pokemon_SetValue(mon, MON_DATA_SP_DEF, &newSpDef);
    fn_8016E0A0(speciesData);
    if (hp != 0 || maxHP == 0) {
        if (species == SPECIES_SHEDINJA) {
            hp = 1;
        } else if (hp == 0) {
            hp = newMaxHP;
        } else {
            hp += newMaxHP - maxHP;
        }
    }
    if (hp != 0) {
        Pokemon_SetValue(mon, MON_DATA_HP, &hp);
    }
    Pokemon_ExitDecryptionContext(mon, reencrypt);
}
// TODO Copies a BoxPokemon member by member and returns dst, like an implicit operator=.

BoxPokemon *fn_803DAE24(BoxPokemon *dst, const BoxPokemon *src) {
    *dst = *src;
    return dst;
}
// TODO Reads a value of a Pokemon in a battle party; side and slot come from the battle code.

u32 fn_803DAE64(u32 side, s32 slot, u32 param, void *dest) {
    Party *party;
    if (side > 3) {
        return 0;
    }
    if ((u32)slot >= MAX_PARTY_SIZE) {
        return 0;
    }
    party = fn_803AC868(fn_803AC828(), side);
    if (slot >= Party_GetCurrentCount(party)) {
        return 0;
    }
    return Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, slot), param, dest);
}

u32 BoxPokemon_GetValue(BoxPokemon *boxMon, u32 param, void *dest) {
    if (!boxMon->boxDecrypted) {
        u16 checksum = Pokemon_GetDataChecksum(boxMon->data, sizeof(boxMon->data));
        if (checksum != boxMon->checksum) {
            fn_803D989C(checksum == boxMon->checksum, "checksum Crash!\n");
            boxMon->checksumFailed = TRUE;
        }
    }
    return BoxPokemon_GetDataInternal(boxMon, param, dest);
}

u32 BoxPokemon_GetDataInternal(BoxPokemon *boxMon, s32 param, void *dest) {
    u32 result = 0;
    PokemonDataBlockA *blockA = (PokemonDataBlockA *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_A);
    PokemonDataBlockB *blockB = (PokemonDataBlockB *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_B);
    PokemonDataBlockC *blockC = (PokemonDataBlockC *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_C);
    PokemonDataBlockD *blockD = (PokemonDataBlockD *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_D);

    switch (param) {
        default:
        case MON_DATA_UNUSED_115:
        case MON_DATA_NICKNAME_FLAT_COMPARE:
        case MON_DATA_STATUS:
        case MON_DATA_BALL_CAPSULE_ID:
        case MON_DATA_HP:
        case MON_DATA_MAX_HP:
        case MON_DATA_ATK:
        case MON_DATA_DEF:
        case MON_DATA_SPEED:
        case MON_DATA_SP_ATK:
        case MON_DATA_SP_DEF:
        case MON_DATA_MAIL:
        case MON_DATA_BALL_CAPSULE:          result = 0; break;
        case MON_DATA_PERSONALITY:           result = boxMon->personality; break;
        case MON_DATA_IS_PARTY_DECRYPTED:    result = boxMon->partyDecrypted; break;
        case MON_DATA_IS_BOX_DECRYPTED:      result = boxMon->boxDecrypted; break;
        case MON_DATA_CHECKSUM_FAILED:       result = boxMon->checksumFailed; break;
        case MON_DATA_CHECKSUM:              result = boxMon->checksum; break;
        case MON_DATA_SPECIES_EXISTS:        result = (blockA->species != SPECIES_NONE); break;
        case MON_DATA_SANITY_IS_EGG:
            result = boxMon->checksumFailed;
            if (!result) {
                result = blockB->isEgg;
            }
            break;
        case MON_DATA_SPECIES_OR_EGG:
            result = blockA->species;
            if (result == SPECIES_NONE) {
                break;
            }
            if (blockB->isEgg || boxMon->checksumFailed) {
                result = SPECIES_EGG;
            }
            break;
        case MON_DATA_LEVEL: result = Pokemon_GetSpeciesLevelAt(blockA->species, blockA->exp); break;
        case MON_DATA_SPECIES:
            if (boxMon->checksumFailed) {
                result = SPECIES_EGG;
            } else {
                result = blockA->species;
            }
            break;
        case MON_DATA_HELD_ITEM:                result = blockA->heldItem; break;
        case MON_DATA_OT_ID:                    result = blockA->otID; break;
        case MON_DATA_EXPERIENCE:               result = blockA->exp; break;
        case MON_DATA_FRIENDSHIP:               result = blockA->friendship; break;
        case MON_DATA_ABILITY:                  result = blockA->ability; break;
        case MON_DATA_MARKINGS:                 result = blockA->markings; break;
        case MON_DATA_LANGUAGE:                 result = blockA->originLanguage; break;
        case MON_DATA_HP_EV:                    result = blockA->hpEV; break;
        case MON_DATA_ATK_EV:                   result = blockA->atkEV; break;
        case MON_DATA_DEF_EV:                   result = blockA->defEV; break;
        case MON_DATA_SPEED_EV:                 result = blockA->speedEV; break;
        case MON_DATA_SPATK_EV:                 result = blockA->spAtkEV; break;
        case MON_DATA_SPDEF_EV:                 result = blockA->spDefEV; break;
        case MON_DATA_COOL:                     result = blockA->cool; break;
        case MON_DATA_BEAUTY:                   result = blockA->beauty; break;
        case MON_DATA_CUTE:                     result = blockA->cute; break;
        case MON_DATA_SMART:                    result = blockA->smart; break;
        case MON_DATA_TOUGH:                    result = blockA->tough; break;
        case MON_DATA_SHEEN:                    result = blockA->sheen; break;
        case MON_DATA_SINNOH_CHAMP_RIBBON:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 1:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 2:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 3:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 4:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 5:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 6:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 7:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 8:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 9:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 10:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 11:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 12:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 13:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 14:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 15:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 16:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 17:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 18:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 19:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 20:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 21:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 22:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 23:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 24:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 25:
        case MON_DATA_SINNOH_CHAMP_RIBBON + 26:
        case MON_DATA_UNUSED_RIBBON_53:         {
            u64 mask = (u64)1 << (param - MON_DATA_SINNOH_CHAMP_RIBBON);
            result = (blockA->ribbonsDS1 & mask) != 0;
        } break;
        // Indexed through a byte pointer: indexing the array directly folds the offset differently.
        case MON_DATA_MOVE1:
        case MON_DATA_MOVE2:
        case MON_DATA_MOVE3:
        case MON_DATA_MOVE4:    result = *(u16 *)((u8 *)blockB->moves + (param - MON_DATA_MOVE1) * sizeof(u16)); break;
        case MON_DATA_MOVE1_PP:
        case MON_DATA_MOVE2_PP:
        case MON_DATA_MOVE3_PP:
        case MON_DATA_MOVE4_PP: result = blockB->moveCurrentPPs[param - MON_DATA_MOVE1_PP]; break;
        case MON_DATA_MOVE1_PP_UPS:
        case MON_DATA_MOVE2_PP_UPS:
        case MON_DATA_MOVE3_PP_UPS:
        case MON_DATA_MOVE4_PP_UPS: result = blockB->movePPUps[param - MON_DATA_MOVE1_PP_UPS]; break;
        case MON_DATA_MOVE1_MAX_PP:
        case MON_DATA_MOVE2_MAX_PP:
        case MON_DATA_MOVE3_MAX_PP:
        case MON_DATA_MOVE4_MAX_PP:
            result = MoveTable_CalcMaxPP(*(u16 *)((u8 *)blockB->moves + (param - MON_DATA_MOVE1_MAX_PP) * sizeof(u16)),
                                         blockB->movePPUps[param - MON_DATA_MOVE1_MAX_PP]);
            break;
        case MON_DATA_HP_IV:    result = blockB->hpIV; break;
        case MON_DATA_ATK_IV:   result = blockB->atkIV; break;
        case MON_DATA_DEF_IV:   result = blockB->defIV; break;
        case MON_DATA_SPEED_IV: result = blockB->speedIV; break;
        case MON_DATA_SPATK_IV: result = blockB->spAtkIV; break;
        case MON_DATA_SPDEF_IV: result = blockB->spDefIV; break;
        case MON_DATA_IS_EGG:
            result = boxMon->checksumFailed;
            if (!result) {
                result = blockB->isEgg;
            }
            break;
        case MON_DATA_HAS_NICKNAME:     result = blockB->hasNickname; break;
        case MON_DATA_COOL_RIBBON:
        case MON_DATA_COOL_RIBBON + 1:
        case MON_DATA_COOL_RIBBON + 2:
        case MON_DATA_COOL_RIBBON + 3:
        case MON_DATA_COOL_RIBBON + 4:
        case MON_DATA_COOL_RIBBON + 5:
        case MON_DATA_COOL_RIBBON + 6:
        case MON_DATA_COOL_RIBBON + 7:
        case MON_DATA_COOL_RIBBON + 8:
        case MON_DATA_COOL_RIBBON + 9:
        case MON_DATA_COOL_RIBBON + 10:
        case MON_DATA_COOL_RIBBON + 11:
        case MON_DATA_COOL_RIBBON + 12:
        case MON_DATA_COOL_RIBBON + 13:
        case MON_DATA_COOL_RIBBON + 14:
        case MON_DATA_COOL_RIBBON + 15:
        case MON_DATA_COOL_RIBBON + 16:
        case MON_DATA_COOL_RIBBON + 17:
        case MON_DATA_COOL_RIBBON + 18:
        case MON_DATA_COOL_RIBBON + 19:
        case MON_DATA_COOL_RIBBON + 20:
        case MON_DATA_COOL_RIBBON + 21:
        case MON_DATA_COOL_RIBBON + 22:
        case MON_DATA_COOL_RIBBON + 23:
        case MON_DATA_COOL_RIBBON + 24:
        case MON_DATA_COOL_RIBBON + 25:
        case MON_DATA_COOL_RIBBON + 26:
        case MON_DATA_COOL_RIBBON + 27:
        case MON_DATA_COOL_RIBBON + 28:
        case MON_DATA_COOL_RIBBON + 29:
        case MON_DATA_COOL_RIBBON + 30:
        case MON_DATA_WORLD_RIBBON:     {
            u64 mask = (u64)1 << (param - MON_DATA_COOL_RIBBON);
            result = (blockB->ribbonsGBA & mask) != 0;
        } break;
        case MON_DATA_FATEFUL_ENCOUNTER: result = blockB->fatefulEncounter; break;
        case MON_DATA_GENDER:            result = blockB->gender; break;
        case MON_DATA_FORM:              result = blockB->form; break;
        case MON_DATA_UNUSED_113:        result = blockB->unused1; break;
        case MON_DATA_UNUSED_114:        result = blockB->unused2; break;
        case MON_DATA_NICKNAME:
            if (boxMon->checksumFailed) {
                MessageLoader_GetSpeciesName(SPECIES_BAD_EGG, 0, (u16 *)dest);
            } else {
                u16 *nickname = (u16 *)dest;
                for (result = 0; result < MON_NAME_LEN; result++) {
                    nickname[result] = blockC->nickname[result];
                }
                nickname[result] = CHAR_EOS;
            }
            break;
        case MON_DATA_NICKNAME_STRING_AND_FLAG: result = blockB->hasNickname;
        case MON_DATA_NICKNAME_STRING:
            if (boxMon->checksumFailed) {
                Strbuf *speciesName = MessageUtil_SpeciesName(SPECIES_BAD_EGG, 0);
                Strbuf_Copy((Strbuf *)dest, speciesName);
                Strbuf_Free(speciesName);
            } else {
                Strbuf_CopyChars((Strbuf *)dest, blockC->nickname);
            }
            break;
        case MON_DATA_UNUSED_120:             result = blockC->unused; break;
        case MON_DATA_MET_GAME:               result = blockC->originGame; break;
        case MON_DATA_SUPER_COOL_RIBBON:
        case MON_DATA_SUPER_COOL_RIBBON + 1:
        case MON_DATA_SUPER_COOL_RIBBON + 2:
        case MON_DATA_SUPER_COOL_RIBBON + 3:
        case MON_DATA_SUPER_COOL_RIBBON + 4:
        case MON_DATA_SUPER_COOL_RIBBON + 5:
        case MON_DATA_SUPER_COOL_RIBBON + 6:
        case MON_DATA_SUPER_COOL_RIBBON + 7:
        case MON_DATA_SUPER_COOL_RIBBON + 8:
        case MON_DATA_SUPER_COOL_RIBBON + 9:
        case MON_DATA_SUPER_COOL_RIBBON + 10:
        case MON_DATA_SUPER_COOL_RIBBON + 11:
        case MON_DATA_SUPER_COOL_RIBBON + 12:
        case MON_DATA_SUPER_COOL_RIBBON + 13:
        case MON_DATA_SUPER_COOL_RIBBON + 14:
        case MON_DATA_SUPER_COOL_RIBBON + 15:
        case MON_DATA_SUPER_COOL_RIBBON + 16:
        case MON_DATA_SUPER_COOL_RIBBON + 17:
        case MON_DATA_SUPER_COOL_RIBBON + 18:
        case MON_DATA_SUPER_COOL_RIBBON + 19:
        case MON_DATA_UNUSED_RIBBON_142:      {
            u64 mask = (u64)1 << (param - MON_DATA_SUPER_COOL_RIBBON);
            result = (blockC->ribbonsDS2 & mask) != 0;
        } break;
        case MON_DATA_OT_NAME: {
            u16 *otName = (u16 *)dest;
            for (result = 0; result < TRAINER_NAME_LEN; result++) {
                otName[result] = blockD->otName[result];
            }
            otName[result] = CHAR_EOS;
        } break;
        case MON_DATA_OT_NAME_STRING: Strbuf_CopyChars((Strbuf *)dest, blockD->otName); break;
        case MON_DATA_EGG_YEAR:       result = blockD->eggYear; break;
        case MON_DATA_EGG_MONTH:      result = blockD->eggMonth; break;
        case MON_DATA_EGG_DAY:        result = blockD->eggDay; break;
        case MON_DATA_MET_YEAR:       result = blockD->metYear; break;
        case MON_DATA_MET_MONTH:      result = blockD->metMonth; break;
        case MON_DATA_MET_DAY:        result = blockD->metDay; break;
        case MON_DATA_EGG_LOCATION:   result = blockD->eggLocation; break;
        case MON_DATA_MET_LOCATION:   result = blockD->metLocation; break;
        case MON_DATA_POKERUS:        result = blockD->pokerus; break;
        case MON_DATA_POKEBALL:       result = blockD->pokeball; break;
        case MON_DATA_MET_LEVEL:      result = blockD->metLevel; break;
        case MON_DATA_OT_GENDER:      result = blockD->otGender; break;
        case MON_DATA_MET_TERRAIN:    result = blockD->metTerrain; break;
        case MON_DATA_RESERVED_158:   result = blockD->unused; break;
        case MON_DATA_COMBINED_IVS:
            result = (blockB->hpIV << 0) | (blockB->atkIV << 5) | (blockB->defIV << 10) | (blockB->speedIV << 15) |
                     (blockB->spAtkIV << 20) | (blockB->spDefIV << 25);
            break;
        case MON_DATA_NO_PRINT_GENDER:
            if ((blockA->species == SPECIES_NIDORAN_F || blockA->species == SPECIES_NIDORAN_M) &&
                !blockB->hasNickname) {
                result = FALSE;
            } else {
                result = TRUE;
            }
            break;
        case MON_DATA_TYPE_1:
        case MON_DATA_TYPE_2:
            if (blockA->species == SPECIES_ARCEUS && blockA->ability == ABILITY_MULTITYPE) {
                result = Pokemon_GetArceusTypeOf(Item_LoadParam(blockA->heldItem, ITEM_PARAM_HOLD_EFFECT, 0));
            } else {
                result = SpeciesData_GetFormValue(blockA->species,
                                                  blockB->form,
                                                  param - MON_DATA_TYPE_1 + SPECIES_DATA_TYPE_1);
            }
            break;
        case MON_DATA_SPECIES_NAME: MessageLoader_GetSpeciesName(blockA->species, 0, (u16 *)dest); break;
    }
    return result;
}

void Pokemon_SetValue(Pokemon *mon, u32 param, const void *value) {
    if (!mon->box.partyDecrypted) {
        u16 checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
        if (checksum != mon->box.checksum) {
            fn_803D989C(checksum == mon->box.checksum, "checksum Crash!\n");
            mon->box.checksumFailed = TRUE;
            return;
        }
    }
    // value points to a u32; the narrower fields take its low part.
    switch (param) {
        case MON_DATA_STATUS:          mon->party.status = *(const u32 *)value; break;
        case MON_DATA_LEVEL:           mon->party.level = ((const u8 *)value)[3]; break;
        case MON_DATA_BALL_CAPSULE_ID: mon->party.ballCapsuleID = ((const u8 *)value)[3]; break;
        case MON_DATA_HP:              mon->party.hp = ((const u16 *)value)[1]; break;
        case MON_DATA_MAX_HP:          mon->party.maxHP = ((const u16 *)value)[1]; break;
        case MON_DATA_ATK:             mon->party.attack = ((const u16 *)value)[1]; break;
        case MON_DATA_DEF:             mon->party.defense = ((const u16 *)value)[1]; break;
        case MON_DATA_SPEED:           mon->party.speed = ((const u16 *)value)[1]; break;
        case MON_DATA_SP_ATK:          mon->party.spAtk = ((const u16 *)value)[1]; break;
        case MON_DATA_SP_DEF:          mon->party.spDef = ((const u16 *)value)[1]; break;
        case MON_DATA_MAIL:
        case MON_DATA_BALL_CAPSULE:    break;
        default:                       BoxPokemon_SetDataInternal(&mon->box, param, value); break;
    }
    if (!mon->box.partyDecrypted) {
        mon->box.checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
    }
}

void BoxPokemon_SetValue(BoxPokemon *boxMon, u32 param, const void *value) {
    if (!boxMon->boxDecrypted) {
        u16 checksum = Pokemon_GetDataChecksum(boxMon->data, sizeof(boxMon->data));
        if (checksum != boxMon->checksum) {
            fn_803D989C(checksum == boxMon->checksum, "checksum Crash!\n");
            boxMon->checksumFailed = TRUE;
            return;
        }
    }
    BoxPokemon_SetDataInternal(boxMon, param, value);
    if (!boxMon->boxDecrypted) {
        boxMon->checksum = Pokemon_GetDataChecksum(boxMon->data, sizeof(boxMon->data));
    }
}

SpeciesData *SpeciesData_FromMonSpecies(s32 species, u32 heapId) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(heapId, sizeof(SpeciesData));
    SpeciesData_LoadSpecies(species, speciesData);
    return speciesData;
}

u32 SpeciesData_GetValue(SpeciesData *speciesData, u32 param) {
    u32 result;
    switch (param) {
        case SPECIES_DATA_BASE_HP:               result = speciesData->baseHP; break;
        case SPECIES_DATA_BASE_ATK:              result = speciesData->baseAttack; break;
        case SPECIES_DATA_BASE_DEF:              result = speciesData->baseDefense; break;
        case SPECIES_DATA_BASE_SPEED:            result = speciesData->baseSpeed; break;
        case SPECIES_DATA_BASE_SP_ATK:           result = speciesData->baseSpAttack; break;
        case SPECIES_DATA_BASE_SP_DEF:           result = speciesData->baseSpDefense; break;
        case SPECIES_DATA_TYPE_1:                result = speciesData->types[0]; break;
        case SPECIES_DATA_TYPE_2:                result = speciesData->types[1]; break;
        case SPECIES_DATA_CATCH_RATE:            result = speciesData->catchRate; break;
        case SPECIES_DATA_BASE_EXP:              result = speciesData->baseExpReward; break;
        case SPECIES_DATA_EV_HP_YIELD:           result = speciesData->hpYield; break;
        case SPECIES_DATA_EV_ATK_YIELD:          result = speciesData->attackYield; break;
        case SPECIES_DATA_EV_DEF_YIELD:          result = speciesData->defenseYield; break;
        case SPECIES_DATA_EV_SPEED_YIELD:        result = speciesData->speedYield; break;
        case SPECIES_DATA_EV_SP_ATK_YIELD:       result = speciesData->spAttackYield; break;
        case SPECIES_DATA_EV_SP_DEF_YIELD:       result = speciesData->spDefenseYield; break;
        case SPECIES_DATA_HELD_ITEM_COMMON:      result = speciesData->wildHeldItems[0]; break;
        case SPECIES_DATA_HELD_ITEM_RARE:        result = speciesData->wildHeldItems[1]; break;
        case SPECIES_DATA_GENDER_RATIO:          result = speciesData->genderRatio; break;
        case SPECIES_DATA_HATCH_CYCLES:          result = speciesData->hatchCycles; break;
        case SPECIES_DATA_BASE_FRIENDSHIP:       result = speciesData->baseFriendship; break;
        case SPECIES_DATA_EXP_RATE:              result = speciesData->expRate; break;
        case SPECIES_DATA_EGG_GROUP_1:           result = speciesData->eggGroups[0]; break;
        case SPECIES_DATA_EGG_GROUP_2:           result = speciesData->eggGroups[1]; break;
        case SPECIES_DATA_ABILITY_1:             result = speciesData->abilities[0]; break;
        case SPECIES_DATA_ABILITY_2:             result = speciesData->abilities[1]; break;
        case SPECIES_DATA_GREAT_MARSH_FLEE_RATE: result = speciesData->greatMarshFleeRate; break;
        case SPECIES_DATA_BODY_COLOR:            result = speciesData->bodyColor; break;
        case SPECIES_DATA_FLIP_SPRITE:           result = speciesData->flipSprite; break;
        case SPECIES_DATA_TM_LEARNSET_MASK_1:    result = speciesData->tmLearnsetMasks[0]; break;
        case SPECIES_DATA_TM_LEARNSET_MASK_2:    result = speciesData->tmLearnsetMasks[1]; break;
        case SPECIES_DATA_TM_LEARNSET_MASK_3:    result = speciesData->tmLearnsetMasks[2]; break;
        case SPECIES_DATA_TM_LEARNSET_MASK_4:    result = speciesData->tmLearnsetMasks[3]; break;
    }
    return result;
}

void SpeciesData_Free(SpeciesData *speciesData) {
    fn_8016E0A0(speciesData);
}

u32 SpeciesData_GetFormValue(s32 species, s32 form, u32 param) {
    SpeciesData *speciesData;
    u32 result;
    species = Pokemon_GetFormNarcIndex(species, form);
    speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    SpeciesData_LoadSpecies(species, speciesData);
    result = SpeciesData_GetValue(speciesData, param);
    fn_8016E0A0(speciesData);
    return result;
}

u32 SpeciesData_GetSpeciesValue(s32 species, u32 param) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u32 value;
    SpeciesData_LoadSpecies(species, speciesData);
    value = SpeciesData_GetValue(speciesData, param);
    fn_8016E0A0(speciesData);
    return value;
}

u8 Pokemon_GetPercentToNextLevel(Pokemon *mon) {
    u16 species;
    u8 level;
    BOOL reencrypt;
    u32 currentLevelExp;
    reencrypt = Pokemon_EnterDecryptionContext(mon);
    species = Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
    currentLevelExp = Pokemon_InlineGetSpeciesBaseExpAt(species, level);
    u32 nextLevelExp = Pokemon_InlineGetSpeciesBaseExpAt(species, level + 1);
    u32 exp = Pokemon_GetValue(mon, MON_DATA_EXPERIENCE, NULL);
    Pokemon_ExitDecryptionContext(mon, reencrypt);
    return ((exp - currentLevelExp) * 100) / (nextLevelExp - currentLevelExp);
}

u32 Pokemon_GetCurrentLevelBaseExp(Pokemon *mon) {
    u32 level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
    return Pokemon_GetSpeciesBaseExpAt(Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL), level);
}

u32 Pokemon_GetSpeciesBaseExpAt(s32 species, s32 level) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u32 expRate;
    SpeciesData_LoadSpecies(species, speciesData);
    expRate = SpeciesData_GetValue(speciesData, SPECIES_DATA_EXP_RATE);
    fn_8016E0A0(speciesData);
    return Pokemon_GetExpRateBaseExpAt(expRate, level);
}

u32 BoxPokemon_GetLevel(BoxPokemon *boxMon) {
    u32 species;
    u32 exp;
    BOOL reencrypt;
    reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    species = BoxPokemon_GetValue(boxMon, MON_DATA_SPECIES, NULL);
    exp = BoxPokemon_GetValue(boxMon, MON_DATA_EXPERIENCE, NULL);
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
    return Pokemon_GetSpeciesLevelAt(species, exp);
}

u32 Pokemon_GetSpeciesLevelAt(u16 species, u32 exp) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u32 level;
    SpeciesData_LoadSpecies(species, speciesData);
    level = SpeciesData_GetLevelAt(speciesData, species, exp);
    fn_8016E0A0(speciesData);
    return level;
}

u32 SpeciesData_GetLevelAt(SpeciesData *speciesData, u16 species, u32 exp) {
    /* lbl_8063D098 */ static u32 monExpTable[MAX_POKEMON_LEVEL + 1];
    s32 level;
    Pokemon_LoadExperienceTableOf(SpeciesData_GetValue(speciesData, SPECIES_DATA_EXP_RATE), monExpTable);
    for (level = 1; level < MAX_POKEMON_LEVEL + 1; level++) {
        if (monExpTable[level] > exp) {
            break;
        }
    }
    return level - 1;
}

u8 BoxPokemon_GetNature(BoxPokemon *boxMon) {
    return BoxPokemon_InlineGetNature(boxMon);
}

u16 Pokemon_GetNatureStatValue(u8 nature, u16 statValue, u8 statType) {
    if (statType < 1 || statType > 5) {
        return statValue;
    }
    switch (sNatureStatAffinities[nature][statType - 1]) {
        case 1:
            statValue = statValue * 110;
            statValue = statValue / 100;
            break;
        case -1: statValue = (u16)(statValue * 90) / 100; break;
    }
    return statValue;
}

void Pokemon_UpdateFriendship(Pokemon *mon, u8 event, u16 mapID) {
    u16 species;
    s16 friendship;
    u8 tableIndex;
    u8 holdEffect;
    s8 change;
    s32 value;
    if (event == 5) {
        if (LCRNG_Next() & 1) {
            return;
        }
    }
    species = Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL);
    if (species == SPECIES_NONE || species == SPECIES_EGG) {
        return;
    }
    holdEffect = Item_LoadParam(Pokemon_GetValue(mon, MON_DATA_HELD_ITEM, NULL), ITEM_PARAM_HOLD_EFFECT, 0);
    tableIndex = 0;
    friendship = Pokemon_GetValue(mon, MON_DATA_FRIENDSHIP, NULL);
    if (friendship >= 100) {
        tableIndex = 1;
    }
    if (friendship >= 200) {
        tableIndex++;
    }
    change = sFriendshipChangeTable[event][tableIndex];
    if (change > 0 && Pokemon_GetValue(mon, MON_DATA_POKEBALL, NULL) == POKEBALL_LUXURY) {
        change++;
    }
    if (change > 0 && Pokemon_GetValue(mon, MON_DATA_EGG_LOCATION, NULL) == mapID) {
        change++;
    }
    if (change > 0 && holdEffect == HOLD_EFFECT_FRIENDSHIP_UP) {
        change = change * 150 / 100;
    }
    friendship += change;
    if (friendship < 0) {
        friendship = 0;
    }
    if (friendship > 255) {
        friendship = 255;
    }
    value = friendship;
    Pokemon_SetValue(mon, MON_DATA_FRIENDSHIP, &value);
}

u8 Pokemon_GetGender(Pokemon *mon) {
    return BoxPokemon_GetGender(&mon->box);
}

u8 Pokemon_GetGenderOf(u16 species, u32 personality) {
    SpeciesData *speciesData = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    u8 gender;
    SpeciesData_LoadSpecies(species, speciesData);
    gender = SpeciesData_GetGenderOf(speciesData, species, personality);
    fn_8016E0A0(speciesData);
    return gender;
}

u8 SpeciesData_GetGenderOf(SpeciesData *speciesData, u16 species, u32 personality) {
    u8 genderRatio = SpeciesData_GetValue(speciesData, SPECIES_DATA_GENDER_RATIO);
    switch (genderRatio) {
        case GENDER_RATIO_MALE_ONLY:   return GENDER_MALE;
        case GENDER_RATIO_FEMALE_ONLY: return GENDER_FEMALE;
        case GENDER_RATIO_NO_GENDER:   return GENDER_NONE;
    }
    return (u32)genderRatio > (u32)(u8)personality;
}

u8 BoxPokemon_IsShiny(BoxPokemon *boxMon) {
    u32 otID = BoxPokemon_GetValue(boxMon, MON_DATA_OT_ID, NULL);
    return Pokemon_IsPersonalityShiny(otID, BoxPokemon_GetValue(boxMon, MON_DATA_PERSONALITY, NULL));
}

u8 Pokemon_IsPersonalityShiny(u32 otID, u32 personality) {
    return (((personality & 0xFFFF) ^ (personality >> 16)) ^ ((otID >> 16) ^ (otID & 0xFFFF))) < 8;
}
// TODO Returns 0; sits between the shiny and the structure size functions.

s32 fn_803DC160() {
    return 0;
}

u32 Pokemon_GetStructSize() {
    return sizeof(Pokemon);
}

u8 Pokemon_GetUnownLetterOf(u32 personality) {
    return (((personality & 0x3000000) >> 18) | ((personality & 0x30000) >> 12) | ((personality & 0x300) >> 6) |
            (personality & 0x3)) %
           28;
}

BoxPokemon *Pokemon_GetBoxPokemon(Pokemon *mon) {
    return &mon->box;
}

BOOL Pokemon_ShouldLevelUp(Pokemon *mon) {
    u32 exp;
    u32 level;
    u32 expRate;
    u16 species;
    u8 nextLevel;
    species = Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    nextLevel = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL) + 1;
    exp = Pokemon_GetValue(mon, MON_DATA_EXPERIENCE, NULL);
    expRate = SpeciesData_InlineGetSpeciesValue(species, SPECIES_DATA_EXP_RATE);
    {
        u32 maxExp = Pokemon_GetExpRateBaseExpAt(expRate, MAX_POKEMON_LEVEL);
        if (exp > maxExp) {
            exp = maxExp;
            Pokemon_SetValue(mon, MON_DATA_EXPERIENCE, &exp);
        }
    }
    if (nextLevel > MAX_POKEMON_LEVEL) {
        return FALSE;
    }
    if (exp >= Pokemon_GetExpRateBaseExpAt(expRate, nextLevel)) {
        level = nextLevel;
        Pokemon_SetValue(mon, MON_DATA_LEVEL, &level);
        return TRUE;
    }
    return FALSE;
}

void BoxPokemon_SetDefaultMoves(BoxPokemon *boxMon) {
    u16 species;
    u8 level;
    BOOL reencrypt;
    u32 form;
    u16 *levelUpMoves;
    s32 i;
    levelUpMoves = (u16 *)fn_8016DF70(0, 0x2C);
    reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    species = BoxPokemon_GetValue(boxMon, MON_DATA_SPECIES, NULL);
    form = BoxPokemon_GetValue(boxMon, MON_DATA_FORM, NULL);
    level = BoxPokemon_GetLevel(boxMon);
    fn_803DCD20(Pokemon_GetFormNarcIndex(species, form), levelUpMoves);
    for (i = 0; levelUpMoves[i] != 0xFFFF; i++) {
        u32 move;
        if ((levelUpMoves[i] & 0xFE00) > (level << 9)) {
            break;
        }
        move = levelUpMoves[i] & 0x1FF;
        if (BoxPokemon_AddMove(boxMon, move) == MOVE_TABLE_FULL) {
            BoxPokemon_ReplaceMove(boxMon, move);
        }
    }
    fn_8016E0A0(levelUpMoves);
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
}

u16 BoxPokemon_AddMove(BoxPokemon *boxMon, u16 move) {
    s32 i;
    u16 result;
    BOOL reencrypt;
    result = MOVE_TABLE_FULL;
    reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        u16 slotMove = BoxPokemon_GetValue(boxMon, MON_DATA_MOVE1 + i, NULL);
        if (slotMove == MOVE_NONE) {
            BoxPokemon_SetMoveSlot(boxMon, move, i);
            result = move;
            break;
        }
        if (slotMove == move) {
            result = MOVE_ALREADY_KNOWN;
            break;
        }
    }
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
    return result;
}

void BoxPokemon_ReplaceMove(BoxPokemon *boxMon, u16 move) {
    u16 moves[LEARNED_MOVES_MAX];
    u8 pps[LEARNED_MOVES_MAX];
    u8 ppUps[LEARNED_MOVES_MAX];
    u32 value;
    BOOL reencrypt;
    s32 i;
    reencrypt = BoxPokemon_EnterDecryptionContext(boxMon);
    for (i = 0; i < LEARNED_MOVES_MAX - 1; i++) {
        moves[i] = BoxPokemon_GetValue(boxMon, MON_DATA_MOVE2 + i, NULL);
        pps[i] = BoxPokemon_GetValue(boxMon, MON_DATA_MOVE2_PP + i, NULL);
        ppUps[i] = BoxPokemon_GetValue(boxMon, MON_DATA_MOVE2_PP_UPS + i, NULL);
    }
    moves[3] = move;
    pps[3] = MoveTable_LoadParam(move, MOVEATTRIBUTE_PP);
    ppUps[3] = 0;
    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        value = moves[i];
        BoxPokemon_SetValue(boxMon, MON_DATA_MOVE1 + i, &value);
        value = pps[i];
        BoxPokemon_SetValue(boxMon, MON_DATA_MOVE1_PP + i, &value);
        value = ppUps[i];
        BoxPokemon_SetValue(boxMon, MON_DATA_MOVE1_PP_UPS + i, &value);
    }
    BoxPokemon_ExitDecryptionContext(boxMon, reencrypt);
}

void Pokemon_SetMoveSlot(Pokemon *mon, u16 move, u8 slot) {
    BoxPokemon_SetMoveSlot(&mon->box, move, slot);
}

u16 Pokemon_LevelUpMove(Pokemon *mon, s32 *index, u16 *move) {
    u16 *levelUpMoves;
    u16 result;
    u16 species;
    u32 form;
    u8 level;
    result = MOVE_NONE;
    levelUpMoves = (u16 *)fn_8016DF70(0, 0x2C);
    species = Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    form = Pokemon_GetValue(mon, MON_DATA_FORM, NULL);
    level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
    fn_803DCD20(Pokemon_GetFormNarcIndex(species, form), levelUpMoves);
    if (levelUpMoves[*index] == 0xFFFF) {
        fn_8016E0A0(levelUpMoves);
        return MOVE_NONE;
    }
    while ((level << 9) != (levelUpMoves[*index] & 0xFE00)) {
        (*index)++;
        if (levelUpMoves[*index] == 0xFFFF) {
            fn_8016E0A0(levelUpMoves);
            return MOVE_NONE;
        }
    }
    if ((level << 9) == (levelUpMoves[*index] & 0xFE00)) {
        *move = levelUpMoves[*index] & 0x1FF;
        (*index)++;
        result = BoxPokemon_AddMove(&mon->box, *move);
    }
    fn_8016E0A0(levelUpMoves);
    return result;
}

void Pokemon_FromBoxPokemon(BoxPokemon *boxMon, Pokemon *mon) {
    u32 zero = 0;
    u8 ballCapsule[4];
    fn_803DAE24(&mon->box, boxMon);
    if (mon->box.boxDecrypted) {
        mon->box.partyDecrypted = TRUE;
    }
    Pokemon_SetValue(mon, MON_DATA_STATUS, &zero);
    Pokemon_SetValue(mon, MON_DATA_HP, &zero);
    Pokemon_SetValue(mon, MON_DATA_MAX_HP, &zero);
    Pokemon_SetValue(mon, MON_DATA_BALL_CAPSULE_ID, &zero);
    memset(ballCapsule, 0, sizeof(ballCapsule));
    Pokemon_SetValue(mon, MON_DATA_BALL_CAPSULE, ballCapsule);
    Pokemon_CalcLevelAndStats(mon);
}

u8 Party_GetMaxLevel(Party *party) {
    s32 count = Party_GetCurrentCount(party);
    u8 maxLevel = 1;
    s32 i;
    Pokemon *mon;
    for (i = 0; i < count; i++) {
        mon = Party_GetPokemonBySlotIndex(party, i);
        if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) && !Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL)) {
            u8 level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
            if (level > maxLevel) {
                maxLevel = level;
            }
        }
    }
    return maxLevel;
}

void Pokemon_Copy(Pokemon *src, Pokemon *dst) {
    *dst = *src;
}

void BoxPokemon_Copy(BoxPokemon *src, BoxPokemon *dst) {
    fn_803DAE24(dst, src);
}

s8 Pokemon_GetFlavorAffinity(Pokemon *mon, s32 flavor) {
    return Pokemon_GetFlavorAffinityOf(BoxPokemon_GetValue(&mon->box, MON_DATA_PERSONALITY, NULL), flavor);
}

s8 Pokemon_GetFlavorAffinityOf(u32 personality, s32 flavor) {
    u8 nature = personality % NUM_NATURES;
    return sNatureFlavorAffinities[nature][flavor];
}

void Pokemon_ApplyPokerus(Party *party) {
    s32 count = Party_GetCurrentCount(party);
    Pokemon *mon;
    s32 slot;
    u16 rand = LCRNG_Next();
    if (rand == 0x4000 || rand == 0x8000 || rand == 0xC000) {
        do {
            slot = LCRNG_Next() % count;
            mon = Party_GetPokemonBySlotIndex(party, slot);
        } while (!Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) || Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL));
        if (!Pokemon_HasPokerus(party, FlagIndex(slot))) {
            u8 pokerus;
            u32 value;
            do {
                pokerus = LCRNG_Next();
            } while ((pokerus & 7) == 0);
            if (pokerus & 0xF0) {
                pokerus &= 7;
            }
            pokerus |= pokerus << 4;
            pokerus &= 0xF3;
            pokerus++;
            value = pokerus;
            Pokemon_SetValue(mon, MON_DATA_POKERUS, &value);
        }
    }
}

u8 Pokemon_HasPokerus(Party *party, u8 mask) {
    s32 slot = 0;
    s32 flag = 1;
    u8 result = 0;
    if (mask != 0) {
        do {
            if (mask & 1) {
                if (Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, slot), MON_DATA_POKERUS, NULL)) {
                    result |= flag;
                }
            }
            flag <<= 1;
            slot++;
        } while ((mask >>= 1) != 0);
    } else if (Pokemon_GetValue(Party_GetPokemonBySlotIndex(party, 0), MON_DATA_POKERUS, NULL)) {
        result = 1;
    }
    return result;
}

void Pokemon_ValidatePokerus(Party *party) {
    u8 pokerus;
    s32 count = Party_GetCurrentCount(party);
    Pokemon *neighbour;
    Pokemon *mon;
    s32 i;
    u32 previous;
    u32 next;
    if ((LCRNG_Next() % 3) == 0) {
        for (i = 0; i < count; i++) {
            mon = Party_GetPokemonBySlotIndex(party, i);
            if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL)) {
                pokerus = Pokemon_GetValue(mon, MON_DATA_POKERUS, NULL);
                if (pokerus & 0xF) {
                    if (i != 0) {
                        neighbour = Party_GetPokemonBySlotIndex(party, i - 1);
                        if (!(Pokemon_GetValue(neighbour, MON_DATA_POKERUS, NULL) & 0xF0)) {
                            previous = pokerus;
                            Pokemon_SetValue(neighbour, MON_DATA_POKERUS, &previous);
                        }
                    }
                    if (i < count - 1) {
                        neighbour = Party_GetPokemonBySlotIndex(party, i + 1);
                        if (!(Pokemon_GetValue(neighbour, MON_DATA_POKERUS, NULL) & 0xF0)) {
                            next = pokerus;
                            Pokemon_SetValue(neighbour, MON_DATA_POKERUS, &next);
                            i++;
                        }
                    }
                }
            }
        }
    }
}

// Plates; hold effects 125 to 140 in this game
u8 Pokemon_GetArceusTypeOf(u16 holdEffect) {
    switch (holdEffect) {
        case 125: return 10;
        case 126: return 11;
        case 127: return 13;
        case 128: return 12;
        case 129: return 15;
        case 130: return 1;
        case 131: return 3;
        case 132: return 4;
        case 133: return 2;
        case 134: return 14;
        case 135: return 6;
        case 136: return 5;
        case 137: return 7;
        case 138: return 16;
        case 139: return 17;
        case 140: return 8;
    }
    return 0;
}
// TODO Loads the level-up moves of a form index from the data file.

void fn_803DCD20(s32 index, u16 *moves) {
    for (u8 i = 0; i < 20; i++) {
        u8 level = fn_80392820(&lbl_8063CE34.levelUpMoveData, index, i);
        u16 move = fn_80392878(&lbl_8063CE34.levelUpMoveData, index, i);
        if (move != MOVE_NONE) {
            moves[i] = move | (level << 9);
        } else {
            moves[i] = 0xFFFF;
        }
    }
}

void Pokemon_LoadLevelUpMovesOf(s32 species, s32 form, u16 *moves) {
    fn_803DCD20(Pokemon_GetFormNarcIndex(species, form), moves);
}

BOOL Pokemon_CanLearnTM(Pokemon *mon, u8 tm) {
    u16 species = BoxPokemon_GetValue(&mon->box, MON_DATA_SPECIES_OR_EGG, NULL);
    return CanPokemonFormLearnTM(species, BoxPokemon_GetValue(&mon->box, MON_DATA_FORM, NULL), tm);
}

BOOL CanPokemonFormLearnTM(u16 species, u32 form, u8 tm) {
    u32 mask;
    u32 param;
    if (species == SPECIES_EGG) {
        return FALSE;
    }
    if (tm < 32) {
        mask = 1 << tm;
        param = SPECIES_DATA_TM_LEARNSET_MASK_1;
    } else if (tm < 64) {
        mask = 1 << (tm - 32);
        param = SPECIES_DATA_TM_LEARNSET_MASK_2;
    } else if (tm < 96) {
        mask = 1 << (tm - 64);
        param = SPECIES_DATA_TM_LEARNSET_MASK_3;
    } else {
        mask = 1 << (tm - 96);
        param = SPECIES_DATA_TM_LEARNSET_MASK_4;
    }
    return (SpeciesData_GetFormValue(species, form, param) & mask) != 0;
}

// Unlike the DS version, the data is read field by field from the species data file.
void SpeciesData_LoadSpecies(s32 species, SpeciesData *speciesData) {
    speciesData->baseHP = fn_8039188C(&lbl_8063CE34.speciesData, species);
    speciesData->baseAttack = fn_803918C0(&lbl_8063CE34.speciesData, species);
    speciesData->baseDefense = fn_803918F4(&lbl_8063CE34.speciesData, species);
    speciesData->baseSpeed = fn_80391928(&lbl_8063CE34.speciesData, species);
    speciesData->baseSpAttack = fn_8039195C(&lbl_8063CE34.speciesData, species);
    speciesData->baseSpDefense = fn_80391990(&lbl_8063CE34.speciesData, species);
    speciesData->types[0] = fn_803919C4(&lbl_8063CE34.speciesData, species);
    speciesData->types[1] = fn_803919F8(&lbl_8063CE34.speciesData, species);
    speciesData->catchRate = fn_80391A2C(&lbl_8063CE34.speciesData, species);
    speciesData->baseExpReward = fn_80391A60(&lbl_8063CE34.speciesData, species);
    speciesData->hpYield = fn_80391A94(&lbl_8063CE34.speciesData, species);
    speciesData->attackYield = fn_80391ACC(&lbl_8063CE34.speciesData, species);
    speciesData->defenseYield = fn_80391B04(&lbl_8063CE34.speciesData, species);
    speciesData->speedYield = fn_80391B3C(&lbl_8063CE34.speciesData, species);
    speciesData->spAttackYield = fn_80391B74(&lbl_8063CE34.speciesData, species);
    speciesData->spDefenseYield = fn_80391BAC(&lbl_8063CE34.speciesData, species);
    speciesData->wildHeldItems[0] = fn_80391BE4(&lbl_8063CE34.speciesData, species);
    speciesData->wildHeldItems[1] = fn_80391C18(&lbl_8063CE34.speciesData, species);
    speciesData->genderRatio = fn_80391C4C(&lbl_8063CE34.speciesData, species);
    speciesData->hatchCycles = fn_80391C80(&lbl_8063CE34.speciesData, species);
    speciesData->baseFriendship = fn_80391CB4(&lbl_8063CE34.speciesData, species);
    speciesData->expRate = fn_80391CE8(&lbl_8063CE34.speciesData, species);
    speciesData->eggGroups[0] = fn_80391D1C(&lbl_8063CE34.speciesData, species);
    speciesData->eggGroups[1] = fn_80391D50(&lbl_8063CE34.speciesData, species);
    speciesData->abilities[0] = fn_80391D84(&lbl_8063CE34.speciesData, species);
    speciesData->abilities[1] = fn_80391DB8(&lbl_8063CE34.speciesData, species);
    speciesData->greatMarshFleeRate = fn_80391E20(&lbl_8063CE34.speciesData, species);
    speciesData->bodyColor = fn_80391E54(&lbl_8063CE34.speciesData, species);
    speciesData->flipSprite = fn_80391E8C(&lbl_8063CE34.speciesData, species);
    speciesData->tmLearnsetMasks[0] = fn_80391EC4(&lbl_8063CE34.speciesData, species);
    speciesData->tmLearnsetMasks[1] = fn_80391EF8(&lbl_8063CE34.speciesData, species);
    speciesData->tmLearnsetMasks[2] = fn_80391F2C(&lbl_8063CE34.speciesData, species);
    speciesData->tmLearnsetMasks[3] = fn_80391F60(&lbl_8063CE34.speciesData, species);
}

u16 Pokemon_GetDataChecksum(void *data, u32 bytes) {
    u16 *halfWords = (u16 *)data;
    u16 checksum = 0;
    for (u32 i = 0; i < bytes / 2; i++) {
        checksum += halfWords[i];
    }
    return checksum;
}
void *BoxPokemon_GetDataBlock(BoxPokemon *boxMon, u32 personality, u32 blockID) {
    u8 *dataBlock;
    u8 *dataBlocks;
    personality = (personality & 0x3E000) >> 13;
    fn_803D989C(personality <= 31, "PokeParaAdrsGet:Index Over!");
    switch (personality) {
        case 0:
        case 24:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 1:
        case 25:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 2:
        case 26:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 3:
        case 27:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 4:
        case 28:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 5:
        case 29:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 6:
        case 30:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 7:
        case 31:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 8:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 9:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 10:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 11:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 12:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 13:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 14:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 15:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 16:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 17:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 18:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 19:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 20:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 21:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 22:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 23:
            dataBlocks = boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
    }
    return dataBlock;
}
s32 Pokemon_GetFormNarcIndex(s32 species, s32 form) {
    switch (species) {
        case SPECIES_DEOXYS:
            if (form != 0 && form <= 3) {
                species = 0x1EF + form;
            }
            break;
        case SPECIES_WORMADAM:
            if (form != 0 && form <= 2) {
                species = 0x1F2 + form;
            }
            break;
    }
    return species;
}

u32 FlagIndex(s32 num) {
    u32 flag = 1;
    for (s32 i = 0; i < num; i++) {
        flag <<= 1;
    }
    return flag;
}

s32 LowestBit(u32 flag) {
    s32 i;
    u32 mask;
    for (mask = 1, i = 0; i < 32; i++) {
        if (flag & mask) {
            break;
        }
        mask <<= 1;
    }
    return i;
}

BOOL Pokemon_EnterDecryptionContext(Pokemon *mon) {
    BOOL wasEncrypted = FALSE;
    if (!mon->box.partyDecrypted) {
        wasEncrypted = TRUE;
        fn_803D989C(mon->box.boxDecrypted == FALSE,
                    "ppp\x82\xaa\x8d\x82\x91\xac\x89\xbb\x83\x82\x81["
                    "\x83h\x82\xc9\x82\xc8\x82\xc1\x82\xc4\x82\xa2\x82\xdc\x82\xb7\n");
        mon->box.partyDecrypted = TRUE;
        mon->box.boxDecrypted = TRUE;
    }
    return wasEncrypted;
}

u32 Pokemon_GetValue(Pokemon *mon, u32 param, void *dest) {
    if (!mon->box.partyDecrypted) {
        u16 checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
        if (checksum != mon->box.checksum) {
            fn_803D989C(checksum == mon->box.checksum, "checksum Crash!\n");
            mon->box.checksumFailed = TRUE;
        }
    }
    switch (param) {
        case MON_DATA_STATUS:          return mon->party.status;
        case MON_DATA_LEVEL:           return mon->party.level;
        case MON_DATA_BALL_CAPSULE_ID: return mon->party.ballCapsuleID;
        case MON_DATA_HP:              return mon->party.hp;
        case MON_DATA_MAX_HP:          return mon->party.maxHP;
        case MON_DATA_ATK:             return mon->party.attack;
        case MON_DATA_DEF:             return mon->party.defense;
        case MON_DATA_SPEED:           return mon->party.speed;
        case MON_DATA_SP_ATK:          return mon->party.spAtk;
        case MON_DATA_SP_DEF:          return mon->party.spDef;
        case MON_DATA_MAIL:            return TRUE;
        case MON_DATA_BALL_CAPSULE:    return TRUE;
    }
    return BoxPokemon_GetDataInternal(&mon->box, param, dest);
}

void Pokemon_IncreaseValue(Pokemon *mon, u32 param, s32 value) {
    if (!mon->box.partyDecrypted) {
        u16 checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
        if (checksum != mon->box.checksum) {
            fn_803D989C(checksum == mon->box.checksum, "checksum Crash!\n");
            return;
        }
    }
    switch (param) {
        case MON_DATA_HP:
            if (mon->party.hp + value > mon->party.maxHP) {
                mon->party.hp = mon->party.maxHP;
            } else {
                mon->party.hp = mon->party.hp + value;
            }
            break;
        case MON_DATA_STATUS:
        case MON_DATA_LEVEL:
        case MON_DATA_BALL_CAPSULE_ID:
        case MON_DATA_MAX_HP:
        case MON_DATA_ATK:
        case MON_DATA_DEF:
        case MON_DATA_SPEED:
        case MON_DATA_SP_ATK:
        case MON_DATA_SP_DEF:
        case MON_DATA_MAIL:
            fn_803D989C(0, "Add\x82\xc5\x82\xab\x82\xc8\x82\xa2\x83p\x83\x89\x83\x81\x81[\x83^\x82\xc5\x82\xb7\n");
            break;
        default: BoxPokemon_IncreaseDataInternal(&mon->box, param, value); break;
    }
    if (!mon->box.partyDecrypted) {
        mon->box.checksum = Pokemon_GetDataChecksum(mon->box.data, sizeof(mon->box.data));
    }
}

void Pokemon_LoadExperienceTableOf(s32 expRate, u32 *expTable) {
    fn_803D989C(expRate < 8, "PokeGrowDataGet:TableIndexOver!");
    for (s32 i = 0; i < MAX_POKEMON_LEVEL + 1; i++) {
        expTable[i] = fn_80392560(&lbl_8063CE34.expData, expRate, i);
    }
}

u32 Pokemon_GetExpRateBaseExpAt(s32 expRate, s32 level) {
    u32 *expTable;
    u32 exp;
    fn_803D989C(expRate < 8, "PokeGrowParaGet:TableIndexOver!");
    fn_803D989C(level <= MAX_POKEMON_LEVEL + 1, "PokeGrowParaGet:Level Over!");
    expTable = (u32 *)fn_8016DF70(0, (MAX_POKEMON_LEVEL + 1) * sizeof(u32));
    Pokemon_LoadExperienceTableOf(expRate, expTable);
    exp = expTable[level];
    fn_8016E0A0(expTable);
    return exp;
}
