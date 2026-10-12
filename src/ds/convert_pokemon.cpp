#include "ds/convert_pokemon.hpp"

#include "ds/DSbridge.hpp"
#include "ds/message.hpp"
#include "ds/party.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
void fn_80177080(u16 *dst, const void *src, u32 length);
void fn_8017714C(u16 *dst, u16 *src, u32 size);
}

static u32 Swap16(u16 value);
static u32 Swap32(u32 value);
static u64 Swap64(u64 value);

// TODO Encrypts or decrypts DS data in place with the LCRNG, like EncodeData in the DS games.
void fn_803E02B4(u16 *data, u32 size, u32 seed) {
    u32 i;
    for (i = 0; i < size / 2; i++) {
        u32 value = Swap16(data[i]);
        seed = seed * 1103515245 + 24691;
        data[i] = Swap16(value ^ (seed >> 16));
    }
}

u32 DSPokemon_GetDataChecksum(u16 *data, u32 size) {
    u32 i;
    u32 checksum = 0;
    for (i = 0; i < size / 2; i++) {
        checksum += Swap16(data[i]);
    }
    return checksum;
}

BOOL DSPokemon_ExitDecryptionContext(DSPokemon *mon, BOOL encrypt) {
    DSBoxPokemon swapped;
    BOOL wasDecrypted = FALSE;
    u32 checksum;
    swapped.flags.raw = Swap16(mon->flags.raw);
    if (swapped.flags.bits.partyDecrypted == TRUE && encrypt == TRUE) {
        wasDecrypted = TRUE;
        swapped.flags.bits.partyDecrypted = FALSE;
        swapped.flags.bits.boxDecrypted = FALSE;
        mon->flags.raw = Swap16(swapped.flags.raw);
        fn_803E02B4((u16 *)&mon->party, sizeof(mon->party), Swap32(mon->personality));
        checksum = DSPokemon_GetDataChecksum(mon->data, sizeof(mon->data));
        fn_803E02B4(mon->data, sizeof(mon->data), (u16)checksum);
        mon->checksum = Swap16((u16)checksum);
    }
    return wasDecrypted;
}

BOOL DSPokemon_EnterDecryptionContext(DSPokemon *mon) {
    DSBoxPokemon swapped;
    BOOL wasEncrypted = FALSE;
    u32 checksum;
    swapped.flags.raw = Swap16(mon->flags.raw);
    if (!swapped.flags.bits.partyDecrypted) {
        wasEncrypted = TRUE;
        fn_803D989C(swapped.flags.bits.boxDecrypted == FALSE,
                    "ppp\x82\xaa\x8d\x82\x91\xac\x89\xbb\x83\x82\x81["
                    "\x83h\x82\xc9\x82\xc8\x82\xc1\x82\xc4\x82\xa2\x82\xdc\x82\xb7\n");
        swapped.flags.bits.partyDecrypted = TRUE;
        swapped.flags.bits.boxDecrypted = TRUE;
        mon->flags.raw = Swap16(swapped.flags.raw);
        fn_803E02B4((u16 *)&mon->party, sizeof(mon->party), Swap32(mon->personality));
        checksum = Swap16(mon->checksum);
        fn_803E02B4(mon->data, sizeof(mon->data), (u16)checksum);
    }
    return wasEncrypted;
}

BOOL DSBoxPokemon_EnterDecryptionContext(DSBoxPokemon *boxMon) {
    DSBoxPokemon swapped;
    BOOL wasEncrypted = FALSE;
    u32 checksum;
    swapped.flags.raw = Swap16(boxMon->flags.raw);
    if (!swapped.flags.bits.boxDecrypted) {
        wasEncrypted = TRUE;
        swapped.flags.bits.boxDecrypted = TRUE;
        boxMon->flags.raw = Swap16(swapped.flags.raw);
        Swap32(boxMon->personality);
        checksum = Swap16(boxMon->checksum);
        fn_803E02B4(boxMon->data, sizeof(boxMon->data), (u16)checksum);
    }
    return wasEncrypted;
}

void *DSBoxPokemon_GetDataBlock(DSBoxPokemon *boxMon, u32 personality, u32 blockID) {
    u8 *dataBlock;
    u8 *dataBlocks;
    personality = (personality & 0x3E000) >> 13;
    fn_803D989C(personality <= 31, "PokeParaAdrsGet:Index Over!");
    switch (personality) {
        case 0:
        case 24:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 1:
        case 25:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 2:
        case 26:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 3:
        case 27:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 4:
        case 28:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 5:
        case 29:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 6:
        case 30:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 7:
        case 31:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 8:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 9:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 10:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 11:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 12:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 13:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 14:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 15:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 16:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 17:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 18:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 19:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 20:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 21:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 22:
            dataBlocks = (u8 *)boxMon->data;
            switch (blockID) {
                case DATA_BLOCK_A: dataBlock = dataBlocks + 2 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_B: dataBlock = dataBlocks + 3 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_C: dataBlock = dataBlocks + 1 * sizeof(PokemonDataBlockA); break;
                case DATA_BLOCK_D: dataBlock = dataBlocks + 0 * sizeof(PokemonDataBlockA); break;
            }
            break;
        case 23:
            dataBlocks = (u8 *)boxMon->data;
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
void BoxPokemon_FromDS(DSBoxPokemon *src, BoxPokemon *dst) {
    DSBoxPokemon swapped;
    DSPokemonDataBlockB swappedB;
    PokemonDataBlockA *srcA;
    DSPokemonDataBlockB *srcB;
    PokemonDataBlockC *srcC;
    DSPokemonDataBlockD *srcD;
    PokemonDataBlockA *dstA;
    PokemonDataBlockB *dstB;
    PokemonDataBlockC *dstC;
    PokemonDataBlockD *dstD;
    s32 i;

    dst->personality = Swap32(src->personality);
    swapped.flags.raw = Swap16(src->flags.raw);
    dst->checksumFailed = swapped.flags.bits.checksumFailed;
    dst->boxDecrypted = swapped.flags.bits.boxDecrypted;
    dst->partyDecrypted = swapped.flags.bits.partyDecrypted;
    dst->checksum = Swap16(src->checksum);

    srcA = (PokemonDataBlockA *)DSBoxPokemon_GetDataBlock(src, Swap32(src->personality), DATA_BLOCK_A);
    srcB = (DSPokemonDataBlockB *)DSBoxPokemon_GetDataBlock(src, Swap32(src->personality), DATA_BLOCK_B);
    srcC = (PokemonDataBlockC *)DSBoxPokemon_GetDataBlock(src, Swap32(src->personality), DATA_BLOCK_C);
    srcD = (DSPokemonDataBlockD *)DSBoxPokemon_GetDataBlock(src, Swap32(src->personality), DATA_BLOCK_D);
    dstA = (PokemonDataBlockA *)BoxPokemon_GetDataBlock(dst, dst->personality, DATA_BLOCK_A);
    dstB = (PokemonDataBlockB *)BoxPokemon_GetDataBlock(dst, dst->personality, DATA_BLOCK_B);
    dstC = (PokemonDataBlockC *)BoxPokemon_GetDataBlock(dst, dst->personality, DATA_BLOCK_C);
    dstD = (PokemonDataBlockD *)BoxPokemon_GetDataBlock(dst, dst->personality, DATA_BLOCK_D);

    dstA->species = Swap16(srcA->species);
    dstA->heldItem = Swap16(srcA->heldItem);
    dstA->otID = Swap32(srcA->otID);
    dstA->exp = Swap32(srcA->exp);
    dstA->friendship = srcA->friendship;
    dstA->ability = srcA->ability;
    dstA->markings = srcA->markings;
    dstA->originLanguage = srcA->originLanguage;
    dstA->hpEV = srcA->hpEV;
    dstA->atkEV = srcA->atkEV;
    dstA->defEV = srcA->defEV;
    dstA->speedEV = srcA->speedEV;
    dstA->spAtkEV = srcA->spAtkEV;
    dstA->spDefEV = srcA->spDefEV;
    dstA->cool = srcA->cool;
    dstA->beauty = srcA->beauty;
    dstA->cute = srcA->cute;
    dstA->smart = srcA->smart;
    dstA->tough = srcA->tough;
    dstA->sheen = srcA->sheen;
    dstA->ribbonsDS1 = Swap32(srcA->ribbonsDS1);

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        dstB->moves[i] = Swap16(srcB->moves[i]);
        dstB->moveCurrentPPs[i] = srcB->moveCurrentPPs[i];
        dstB->movePPUps[i] = srcB->movePPUps[i];
    }
    swappedB.ivs.raw = Swap32(srcB->ivs.raw);
    dstB->hasNickname = swappedB.ivs.bits.hasNickname;
    dstB->isEgg = swappedB.ivs.bits.isEgg;
    dstB->spDefIV = swappedB.ivs.bits.spDefIV;
    dstB->spAtkIV = swappedB.ivs.bits.spAtkIV;
    dstB->speedIV = swappedB.ivs.bits.speedIV;
    dstB->defIV = swappedB.ivs.bits.defIV;
    dstB->atkIV = swappedB.ivs.bits.atkIV;
    dstB->hpIV = swappedB.ivs.bits.hpIV;
    dstB->ribbonsGBA = Swap32(srcB->ribbonsGBA);
    dstB->form = srcB->form;
    dstB->gender = srcB->gender;
    dstB->fatefulEncounter = srcB->fatefulEncounter;
    dstB->unused1 = srcB->unused1;
    dstB->unused2 = Swap16(srcB->unused2);
    dstB->unused3 = (u16)Swap16(srcB->unused3);

    for (i = 0; i < MON_NAME_LEN + 1; i++) {
        dstC->nickname[i] = Swap16(srcC->nickname[i]);
    }
    dstC->unused = srcC->unused;
    dstC->originGame = srcC->originGame;
    dstC->ribbonsDS2 = Swap64(srcC->ribbonsDS2);

    for (i = 0; i < TRAINER_NAME_LEN + 1; i++) {
        dstD->otName[i] = Swap16(srcD->otName[i]);
    }
    dstD->eggYear = srcD->eggYear;
    dstD->eggMonth = srcD->eggMonth;
    dstD->eggDay = srcD->eggDay;
    dstD->metYear = srcD->metYear;
    dstD->metMonth = srcD->metMonth;
    dstD->metDay = srcD->metDay;
    dstD->eggLocation = Swap16(srcD->eggLocation);
    dstD->metLocation = Swap16(srcD->metLocation);
    dstD->pokerus = srcD->pokerus;
    dstD->pokeball = srcD->pokeball;
    dstD->otGender = srcD->otGender;
    dstD->metLevel = srcD->metLevel;
    dstD->metTerrain = srcD->metTerrain;
    dstD->unused = Swap16(srcD->unused);
}

void Pokemon_FromDS(DSPokemon *src, Pokemon *dst) {
    const DSPartyPokemon *srcParty = &src->party;
    BoxPokemon_FromDS((DSBoxPokemon *)src, &dst->box);
    dst->party.status = Swap32(srcParty->status);
    dst->party.level = srcParty->level;
    dst->party.ballCapsuleID = srcParty->ballCapsuleID;
    dst->party.hp = Swap16(srcParty->hp);
    dst->party.maxHP = Swap16(srcParty->maxHP);
    dst->party.attack = Swap16(srcParty->attack);
    dst->party.defense = Swap16(srcParty->defense);
    dst->party.speed = Swap16(srcParty->speed);
    dst->party.spAtk = Swap16(srcParty->spAtk);
    dst->party.spDef = Swap16(srcParty->spDef);
    memset(&dst->party.unk14[0], 0, 4);
    memset(&dst->party.unk14[4], 0, 4);
}

void Party_FromDS(DSParty *src, Party *dst) {
    s32 slot;
    s32 i;
    u16 nickname[32];
    u16 unused[32];
    dst->capacity = Swap32(src->capacity);
    dst->currentCount = Swap32(src->currentCount);
    if (dst->currentCount <= MAX_PARTY_SIZE) {
        for (slot = dst->currentCount; slot < MAX_PARTY_SIZE; slot++) {
            memset(&src->pokemon[slot], 0, sizeof(DSPokemon));
        }
    }
    for (i = 0; i < MAX_PARTY_SIZE; i++) {
        BOOL reencrypt = DSPokemon_EnterDecryptionContext(&src->pokemon[i]);
        BOOL checksumValid = DSBoxPokemon_IsChecksumValid((DSBoxPokemon *)&src->pokemon[i]);
        Pokemon_FromDS(&src->pokemon[i], &dst->pokemon[i]);
        if (!checksumValid) {
            dst->pokemon[i].box.checksumFailed = TRUE;
            fn_80177080(nickname,
                        BoxPokemon_GetDataBlock(&dst->pokemon[i].box, dst->pokemon[i].box.personality, DATA_BLOCK_C),
                        MON_NAME_LEN + 1);
            fn_8017714C(unused, nickname, 0x40);
        }
        DSPokemon_ExitDecryptionContext(&src->pokemon[i], reencrypt);
    }
}

void Pokemon_ToDS(Pokemon *src, DSPokemon *dst, BOOL encrypt) {
    PokemonDataBlockA *dstA;
    DSPokemonDataBlockB *dstB;
    PokemonDataBlockC *dstC;
    DSPokemonDataBlockD *dstD;
    PokemonDataBlockA *srcA;
    PokemonDataBlockB *srcB;
    PokemonDataBlockC *srcC;
    PokemonDataBlockD *srcD;
    s32 i;

    dst->personality = Swap32(src->box.personality);
    dst->flags.raw = 0;
    dst->flags.bits.checksumFailed = src->box.checksumFailed;
    dst->flags.bits.boxDecrypted = src->box.boxDecrypted;
    dst->flags.bits.partyDecrypted = src->box.partyDecrypted;
    dst->flags.raw = Swap16(dst->flags.raw);
    dst->checksum = Swap16(src->box.checksum);

    dstA = (PokemonDataBlockA *)DSBoxPokemon_GetDataBlock((DSBoxPokemon *)dst, Swap32(dst->personality), DATA_BLOCK_A);
    dstB =
        (DSPokemonDataBlockB *)DSBoxPokemon_GetDataBlock((DSBoxPokemon *)dst, Swap32(dst->personality), DATA_BLOCK_B);
    dstC = (PokemonDataBlockC *)DSBoxPokemon_GetDataBlock((DSBoxPokemon *)dst, Swap32(dst->personality), DATA_BLOCK_C);
    dstD =
        (DSPokemonDataBlockD *)DSBoxPokemon_GetDataBlock((DSBoxPokemon *)dst, Swap32(dst->personality), DATA_BLOCK_D);
    srcA = (PokemonDataBlockA *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, DATA_BLOCK_A);
    srcB = (PokemonDataBlockB *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, DATA_BLOCK_B);
    srcC = (PokemonDataBlockC *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, DATA_BLOCK_C);
    srcD = (PokemonDataBlockD *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, DATA_BLOCK_D);

    dstA->species = Swap16(srcA->species);
    dstA->heldItem = Swap16(srcA->heldItem);
    dstA->otID = Swap32(srcA->otID);
    dstA->exp = Swap32(srcA->exp);
    dstA->friendship = srcA->friendship;
    dstA->ability = srcA->ability;
    dstA->markings = srcA->markings;
    dstA->originLanguage = srcA->originLanguage;
    dstA->hpEV = srcA->hpEV;
    dstA->atkEV = srcA->atkEV;
    dstA->defEV = srcA->defEV;
    dstA->speedEV = srcA->speedEV;
    dstA->spAtkEV = srcA->spAtkEV;
    dstA->spDefEV = srcA->spDefEV;
    dstA->cool = srcA->cool;
    dstA->beauty = srcA->beauty;
    dstA->cute = srcA->cute;
    dstA->smart = srcA->smart;
    dstA->tough = srcA->tough;
    dstA->sheen = srcA->sheen;
    dstA->ribbonsDS1 = Swap32(srcA->ribbonsDS1);

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        dstB->moves[i] = Swap16(srcB->moves[i]);
        dstB->moveCurrentPPs[i] = srcB->moveCurrentPPs[i];
        dstB->movePPUps[i] = srcB->movePPUps[i];
    }
    dstB->ivs.bits.hasNickname = srcB->hasNickname;
    dstB->ivs.bits.isEgg = srcB->isEgg;
    dstB->ivs.bits.spDefIV = srcB->spDefIV;
    dstB->ivs.bits.spAtkIV = srcB->spAtkIV;
    dstB->ivs.bits.speedIV = srcB->speedIV;
    dstB->ivs.bits.defIV = srcB->defIV;
    dstB->ivs.bits.atkIV = srcB->atkIV;
    dstB->ivs.bits.hpIV = srcB->hpIV;
    dstB->ivs.raw = Swap32(dstB->ivs.raw);
    dstB->ribbonsGBA = Swap32(srcB->ribbonsGBA);
    dstB->form = srcB->form;
    dstB->gender = srcB->gender;
    dstB->fatefulEncounter = srcB->fatefulEncounter;
    dstB->unused1 = srcB->unused1;
    dstB->unused2 = Swap16(srcB->unused2);
    dstB->unused3 = (u16)Swap16(srcB->unused3);

    for (i = 0; i < MON_NAME_LEN + 1; i++) {
        dstC->nickname[i] = Swap16(srcC->nickname[i]);
    }
    dstC->unused = srcC->unused;
    dstC->originGame = srcC->originGame;
    dstC->ribbonsDS2 = Swap64(srcC->ribbonsDS2);

    for (i = 0; i < TRAINER_NAME_LEN + 1; i++) {
        dstD->otName[i] = Swap16(srcD->otName[i]);
    }
    dstD->eggYear = srcD->eggYear;
    dstD->eggMonth = srcD->eggMonth;
    dstD->eggDay = srcD->eggDay;
    dstD->metYear = srcD->metYear;
    dstD->metMonth = srcD->metMonth;
    dstD->metDay = srcD->metDay;
    dstD->eggLocation = Swap16(srcD->eggLocation);
    dstD->metLocation = Swap16(srcD->metLocation);
    dstD->pokerus = srcD->pokerus;
    dstD->pokeball = srcD->pokeball;
    dstD->otGender = srcD->otGender;
    dstD->metLevel = srcD->metLevel;
    dstD->metTerrain = srcD->metTerrain;
    dstD->unused = Swap16(srcD->unused);

    dst->party.status = Swap32(src->party.status);
    dst->party.level = src->party.level;
    dst->party.ballCapsuleID = src->party.ballCapsuleID;
    dst->party.hp = Swap16(src->party.hp);
    dst->party.maxHP = Swap16(src->party.maxHP);
    dst->party.attack = Swap16(src->party.attack);
    dst->party.defense = Swap16(src->party.defense);
    dst->party.speed = Swap16(src->party.speed);
    dst->party.spAtk = Swap16(src->party.spAtk);
    dst->party.spDef = Swap16(src->party.spDef);
    memset(dst->party.mail, 0, sizeof(dst->party.mail));
    memset(dst->party.ballCapsule, 0, sizeof(dst->party.ballCapsule));
    if (encrypt) {
        DSPokemon_ExitDecryptionContext(dst, TRUE);
    }
}

// Pokemon_IsEmpty is not a function of its own here.
static inline BOOL Pokemon_InlineIsEmpty(Pokemon *mon) {
    BoxPokemon *boxMon = &mon->box;
    PokemonDataBlockA *blockA;
    PokemonDataBlockC *blockC;
    if (mon->box.personality != 0 || mon->box.checksum != 0) {
        return FALSE;
    }
    blockA = (PokemonDataBlockA *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_A);
    BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_B);
    blockC = (PokemonDataBlockC *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_C);
    BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_D);
    if (blockA->species != SPECIES_NONE || blockA->otID != 0) {
        return FALSE;
    }
    return blockC->nickname[0] == 0;
}

void Party_ToDS(Party *src, DSParty *dst, BOOL encrypt) {
    s32 i;
    dst->capacity = Swap32(src->capacity);
    dst->currentCount = Swap32(src->currentCount);
    for (i = 0; i < MAX_PARTY_SIZE; i++) {
        BOOL reencrypt;
        Pokemon *mon = &src->pokemon[i];
        reencrypt = Pokemon_EnterDecryptionContext(mon);
        Pokemon_ToDS(mon, &dst->pokemon[i], encrypt);
        Pokemon_ExitDecryptionContext(mon, reencrypt);
    }
    for (i = 0; i < MAX_PARTY_SIZE; i++) {
        if (Pokemon_InlineIsEmpty(&src->pokemon[i])) {
            break;
        }
    }
    dst->currentCount = Swap32(i);
}

BOOL DSBoxPokemon_IsChecksumValid(DSBoxPokemon *boxMon) {
    return (u16)Swap16(DSPokemon_GetDataChecksum(boxMon->data, sizeof(boxMon->data))) == boxMon->checksum;
}

u32 DSParty_CountValidPokemon(DSParty *party) {
    DSPokemon *mon;
    u32 capacity;
    u32 count;
    u32 validCount;
    u32 i;
    BOOL reencrypt;
    capacity = Swap32(party->capacity);
    count = Swap32(party->currentCount);
    validCount = 0;
    if (capacity > MAX_PARTY_SIZE) {
        capacity = MAX_PARTY_SIZE;
    }
    if (count > MAX_PARTY_SIZE) {
        count = MAX_PARTY_SIZE;
    }
    if (count > capacity) {
        count = capacity;
    }
    for (i = 0; i < count; i++) {
        mon = &party->pokemon[i];
        reencrypt = DSPokemon_EnterDecryptionContext(mon);
        if (DSBoxPokemon_IsChecksumValid((DSBoxPokemon *)mon)) {
            validCount++;
        }
        DSPokemon_ExitDecryptionContext(mon, reencrypt);
    }
    return validCount;
}

void BoxPokemon_ResetNickname(BoxPokemon *boxMon, BOOL force) {
    PokemonDataBlockA *blockA;
    PokemonDataBlockB *blockB;
    PokemonDataBlockC *blockC;
    BoxPokemon_EnterDecryptionContext(boxMon);
    blockA = (PokemonDataBlockA *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_A);
    blockB = (PokemonDataBlockB *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_B);
    blockC = (PokemonDataBlockC *)BoxPokemon_GetDataBlock(boxMon, boxMon->personality, DATA_BLOCK_C);
    if (force || blockB->hasNickname) {
        blockB->hasNickname = FALSE;
        MessageLoader_GetSpeciesName(blockA->species, 0, blockC->nickname);
    }
}

static u32 Swap16(u16 value) {
    return (u16)(((value & 0xFF) << 8) + ((value >> 8) & 0xFF));
}

static u32 Swap32(u32 value) {
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value >> 24) & 0xFF);
}

static u64 Swap64(u64 value) {
    u32 low = Swap32(value & 0xFFFFFFFF);
    u32 high = Swap32((value >> 32) & 0xFFFFFFFF);
    return ((u64)low << 32) | high;
}
