#include "ds/battle/battle_controller.hpp"

#include "ds/DSbridge.hpp"
#include "ds/battle/battle_common.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_context.hpp"
#include "ds/battle/battle_display.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_system.hpp"
#include "ds/constants/abilities.hpp"
#include "ds/move_table.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"

#include <string.h>

static void SendMessage(BattleSystem *battleSys, int recipient, int battler, void *message, u8 size);
static void PartyGaugeData_New(
    BattleSystem *battleSys, BattleContext *battleCtx, PartyGaugeData *partyGauge, int command, int battler);

// The commands sent as an int are read back as their first byte, as on the DS: the game stores them little-endian.
#define SWAP_BYTES_32(value)                                                                                           \
    ((((value) & 0xFF) << 24) | (((value) & 0xFF00) << 8) | (((value) & 0xFF0000) >> 8) | (((u32)(value) >> 24) & 0xFF))

static inline BOOL BattleController_RecvLocalMessage(BattleSystem *battleSys, void *message) {
    u8 *src = (u8 *)message;
    u8 recipient;
    u8 battler;
    int size;
    int i;
    BOOL success = FALSE;

    recipient = src[0];
    battler = src[1];
    size = src[3] | (src[2] << 8);

    src += sizeof(BattleMessageInfo);

    if (recipient == COMM_RECIPIENT_SERVER) {
        if (battleSys->battleCtx->ioBuffer[battler][0] == 0) {
            for (i = 0; i < size; i++) {
                battleSys->battleCtx->ioBuffer[battler][i] = src[i];
            }

            success = TRUE;
        }
    } else if (recipient == COMM_RECIPIENT_CLIENT) {
        if (battleSys->battlers[battler]->data[0] == 0) {
            for (i = 0; i < size; i++) {
                battleSys->battlers[battler]->data[i] = src[i];
            }

            success = TRUE;
        }
    } else if (recipient == COMM_RECIPIENT_QUEUE) {
        int val = src[0];
        int id = src[1];

        if (BattleSystem_IsInitialized(battleSys)) {
            BattleIO_DequeueVal(battleSys->battleCtx, id, battler, val);
        }

        success = TRUE;
    }

    return success;
}

void BattleController_TryRecvLocalMessage(BattleSystem *battleSys) {
    u8 *src;
    u16 *readIndex;
    u16 *writeIndex;
    u16 *endIndex;
    int size;

    src = BattleSystem_GetServerMessage(battleSys);
    readIndex = BattleSystem_GetServerReadIndex(battleSys);
    writeIndex = BattleSystem_GetServerWriteIndex(battleSys);
    endIndex = BattleSystem_GetServerEndIndex(battleSys);

    if (readIndex[0] == writeIndex[0]) {
        return;
    }

    if (readIndex[0] == endIndex[0]) {
        readIndex[0] = 0;
        endIndex[0] = 0;
    }

    if (BattleController_RecvLocalMessage(battleSys, (void *)&src[readIndex[0]]) == TRUE) {
        size = sizeof(BattleMessageInfo) + (src[readIndex[0] + 3] | (src[readIndex[0] + 2] << 8));
        readIndex[0] += size;
    }
}

static inline void
BattleController_SendLocalMessage(BattleSystem *battleSys, int recipient, int battler, void *message, u8 size) {
    int i;
    BattleMessageInfo info;
    u8 *src;
    u8 *dest;
    u16 *writeIndex;
    u16 *endIndex;

    dest = BattleSystem_GetServerMessage(battleSys);
    writeIndex = BattleSystem_GetServerWriteIndex(battleSys);
    endIndex = BattleSystem_GetServerEndIndex(battleSys);

    if (writeIndex[0] + sizeof(BattleMessageInfo) + size + 1 > 0x1000) {
        endIndex[0] = writeIndex[0];
        writeIndex[0] = 0;
    }

    info.recipient = recipient;
    info.battler = battler;
    info.size = size;

    src = (u8 *)&info;

    for (i = 0; i < sizeof(BattleMessageInfo); i++) {
        dest[writeIndex[0]] = src[i];
        writeIndex[0]++;
    }

    src = (u8 *)message;

    for (i = 0; i < size; i++) {
        dest[writeIndex[0]] = src[i];
        writeIndex[0]++;
    }
}

static void SendMessage(BattleSystem *battleSys, int recipient, int battler, void *message, u8 size) {
    u8 *data = (u8 *)message;

    if (battleSys->battleType & BATTLE_TYPE_LINK) {
        if (recipient == COMM_RECIPIENT_CLIENT) {
            for (int i = 0; i < fn_803D985C(); i++) {
                BattleIO_EnqueueVal(battleSys->battleCtx, i, battler, *data);
            }
        }

        fn_803AB530(battleSys, recipient, battler, message, size);
    } else {
        if (recipient == COMM_RECIPIENT_CLIENT) {
            BattleIO_EnqueueVal(battleSys->battleCtx, 0, battler, *data);
        }

        BattleController_SendLocalMessage(battleSys, recipient, battler, message, size);
    }
}

void BattleController_EmitSetupBattleUI(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SETUP_UI);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitSetEncounter(BattleSystem *battleSys, int battler) {
    MonEncounterMessage message;
    int i;

    message.command = BATTLE_COMMAND_SET_ENCOUNTER;
    message.gender = battleSys->battleCtx->battleMons[battler].gender;
    message.isShiny = battleSys->battleCtx->battleMons[battler].isShiny;
    message.species = battleSys->battleCtx->battleMons[battler].species;
    message.personality = battleSys->battleCtx->battleMons[battler].personality;
    message.cryModulation =
        Battler_CryModulation(battleSys->battleCtx, battler, BattleSystem_GetBattlerType(battleSys, battler), 1);
    message.formNum = battleSys->battleCtx->battleMons[battler].formNum;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MOVE_1 + i), NULL);
        message.curPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_CUR_PP_1 + i), NULL);
        message.maxPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MAX_PP_1 + i), NULL);
    }

    BattleMon_Get(battleSys->battleCtx, battler, BATTLEMON_NICKNAME, &message.nickname);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MonEncounterMessage));
}

void BattleController_EmitShowEncounter(BattleSystem *battleSys, int battler) {
    MonShowMessage message;
    int i;

    message.command = BATTLE_COMMAND_SHOW_ENCOUNTER;
    message.gender = battleSys->battleCtx->battleMons[battler].gender;
    message.isShiny = battleSys->battleCtx->battleMons[battler].isShiny;
    message.species = battleSys->battleCtx->battleMons[battler].species;
    message.personality = battleSys->battleCtx->battleMons[battler].personality;
    message.cryModulation =
        Battler_CryModulation(battleSys->battleCtx, battler, BattleSystem_GetBattlerType(battleSys, battler), 1);
    message.selectedPartySlot = battleSys->battleCtx->selectedPartySlot[battler];
    message.formNum = battleSys->battleCtx->battleMons[battler].formNum;
    message.capturedBall = battleSys->battleCtx->battleMons[battler].capturedBall;
    message.partnerPartySlot = battleSys->battleCtx->selectedPartySlot[BattleSystem_GetPartner(battleSys, battler)];

    BattleSystem_GetBattleParticipantMask(battleSys, battler, message.selectedPartySlot);

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MOVE_1 + i), NULL);
        message.curPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_CUR_PP_1 + i), NULL);
        message.maxPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MAX_PP_1 + i), NULL);
    }

    BattleMon_Get(battleSys->battleCtx, battler, BATTLEMON_NICKNAME, &message.nickname);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MonShowMessage));
}

void BattleController_EmitShowPokemon(BattleSystem *battleSys, int battler, int capturedBall, int quickSendOut) {
    MonShowMessage message;
    int i;

    message.command = BATTLE_COMMAND_SHOW_POKEMON;

    if (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
        message.gender = battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedGender;
        message.personality = battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedPID;
    } else {
        message.gender = battleSys->battleCtx->battleMons[battler].gender;
        message.personality = battleSys->battleCtx->battleMons[battler].personality;
    }

    message.isShiny = battleSys->battleCtx->battleMons[battler].isShiny;
    message.species = battleSys->battleCtx->battleMons[battler].species;
    message.cryModulation =
        Battler_CryModulation(battleSys->battleCtx, battler, BattleSystem_GetBattlerType(battleSys, battler), 0);
    message.selectedPartySlot = battleSys->battleCtx->selectedPartySlot[battler];
    message.formNum = battleSys->battleCtx->battleMons[battler].formNum;

    if (capturedBall) {
        message.capturedBall = capturedBall;
    } else {
        message.capturedBall = battleSys->battleCtx->battleMons[battler].capturedBall;
    }

    message.isQuickSendOut = quickSendOut;
    message.isSubstitute =
        (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) != 0;

    BattleSystem_GetBattleParticipantMask(battleSys, battler, message.selectedPartySlot);

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MOVE_1 + i), NULL);
        message.curPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_CUR_PP_1 + i), NULL);
        message.maxPP[i] =
            BattleMon_Get(battleSys->battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MAX_PP_1 + i), NULL);
    }

    BattleMon_Get(battleSys->battleCtx, battler, BATTLEMON_NICKNAME, &message.nickname);

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.battleMonSpecies[i] = battleSys->battleCtx->battleMons[i].species;
        message.battleMonIsShiny[i] = battleSys->battleCtx->battleMons[i].isShiny;
        message.battleMonFormNums[i] = battleSys->battleCtx->battleMons[i].formNum;

        if (battleSys->battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            message.battleMonGenders[i] = battleSys->battleCtx->battleMons[i].moveEffectsData.transformedGender;
            message.battleMonPersonalities[i] = battleSys->battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            message.battleMonGenders[i] = battleSys->battleCtx->battleMons[i].gender;
            message.battleMonPersonalities[i] = battleSys->battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MonShowMessage));
}

void BattleController_EmitReturnPokemon(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    MonReturnMessage message;
    int face;
    int formNum;
    int i;

    if (battleSys->battlers[battler]->battlerType & BATTLER_TYPE_SOLO_ENEMY) {
        face = FACE_FRONT;
    } else {
        face = FACE_BACK;
    }

    formNum = battleSys->battleCtx->battleMons[battler].formNum;
    message.command = BATTLE_COMMAND_RETURN_POKEMON;

    if (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
        message.yOffset = fn_803DC160(battleSys->battleCtx->battleMons[battler].species,
                                      battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedGender,
                                      face,
                                      formNum,
                                      battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedPID);
    } else {
        message.yOffset = fn_803DC160(battleSys->battleCtx->battleMons[battler].species,
                                      battleSys->battleCtx->battleMons[battler].gender,
                                      face,
                                      formNum,
                                      battleSys->battleCtx->battleMons[battler].personality);
    }

    message.capturedBall = battleSys->battleCtx->battleMons[battler].capturedBall;
    message.isSubstitute =
        (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) != 0;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.battleMonSpecies[i] = battleCtx->battleMons[i].species;
        message.battleMonIsShiny[i] = battleCtx->battleMons[i].isShiny;
        message.battleMonFormNums[i] = battleCtx->battleMons[i].formNum;

        if (battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            message.battleMonGenders[i] = battleCtx->battleMons[i].moveEffectsData.transformedGender;
            message.battleMonPersonalities[i] = battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            message.battleMonGenders[i] = battleCtx->battleMons[i].gender;
            message.battleMonPersonalities[i] = battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MonReturnMessage));
}

void BattleController_EmitDeletePokemon(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_DELETE_POKEMON);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitSetTrainerEncounter(BattleSystem *battleSys, int battler) {
    TrainerEncounterMessage message;

    message.command = BATTLE_COMMAND_SET_TRAINER_ENCOUNTER;
    message.trainerType = battleSys->trainers[battler].trainerType;
    message.unread = battleSys->unwritten[battler];

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(TrainerEncounterMessage));
}

void BattleController_EmitThrowTrainerBall(BattleSystem *battleSys, int battler, int ballTypeIn) {
    TrainerThrowBallMessage message;

    message.command = BATTLE_COMMAND_THROW_TRAINER_BALL;
    message.ballTypeIn = ballTypeIn;
    message.selectedPartySlot = battleSys->battleCtx->selectedPartySlot[BattleSystem_GetPartner(battleSys, battler)];

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(TrainerThrowBallMessage));
}

void BattleController_EmitSlideTrainerOut(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SLIDE_TRAINER_OUT);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitSlideTrainerIn(BattleSystem *battleSys, int battler, int posIn) {
    TrainerSlideInMessage message;

    message.command = BATTLE_COMMAND_SLIDE_TRAINER_IN;
    message.trainerType = battleSys->trainers[battler].trainerType;
    message.unread = battleSys->unwritten[battler];
    message.posIn = posIn;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(TrainerSlideInMessage));
}

void BattleController_EmitSlideHealthBoxIn(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int delay) {
    HealthBoxData healthboxData;
    Pokemon *mon = BattleSystem_GetPartyPokemon(battleSys, battler, battleCtx->selectedPartySlot[battler]);
    int species = Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
    int level = Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);

    healthboxData.command = BATTLE_COMMAND_SLIDE_HEALTHBOX_IN;
    healthboxData.level = battleCtx->battleMons[battler].level;
    healthboxData.curHP = battleCtx->battleMons[battler].curHP;
    healthboxData.maxHP = battleCtx->battleMons[battler].maxHP;
    healthboxData.selectedPartySlot = battleCtx->selectedPartySlot[battler];
    healthboxData.status = Battler_StatusCondition(battleCtx, battler);

    if ((battleCtx->battleMons[battler].species == SPECIES_NIDORAN_F ||
         battleCtx->battleMons[battler].species == SPECIES_NIDORAN_M) &&
        battleCtx->battleMons[battler].hasNickname == FALSE) {
        healthboxData.gender = GENDER_NONE;
    } else {
        healthboxData.gender = battleCtx->battleMons[battler].gender;
    }

    healthboxData.expFromLastLevel = battleCtx->battleMons[battler].exp - Pokemon_GetSpeciesBaseExpAt(species, level);
    healthboxData.expToNextLevel =
        Pokemon_GetSpeciesBaseExpAt(species, level + 1) - Pokemon_GetSpeciesBaseExpAt(species, level);
    healthboxData.speciesCaught = BattleSystem_HasCaughtSpecies(battleSys, battleCtx->battleMons[battler].species);
    healthboxData.numSafariBalls = BattleSystem_GetNumSafariBalls(battleSys);
    healthboxData.delay = delay;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &healthboxData, sizeof(HealthBoxData));
}

void BattleController_EmitSlideHealthBoxOut(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SLIDE_HEALTHBOX_OUT);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitSetCommandSelection(BattleSystem *battleSys,
                                              BattleContext *battleCtx,
                                              int battler,
                                              int partySlot) {
    CommandSetMessage message;
    int i;
    int battlerType;
    int monSpeciesOrEgg;
    int cnt;
    Party *party;
    Pokemon *pokemon;
    u32 battleType;
    int battlersCanPickCommandMask;

    memset(&message, 0, sizeof(CommandSetMessage));
    BattleIO_ClearBuffer(BattleSystem_GetBattleContext(battleSys), battler);

    battlersCanPickCommandMask = 0;

    for (i = 0; i < BattleSystem_GetMaxBattlers(battleSys); i++) {
        if (Battler_CanPickCommand(battleCtx, i) == FALSE) {
            battlersCanPickCommandMask |= FlagIndex(i);
        }
    }

    message.command = BATTLE_COMMAND_SET_COMMAND_SELECTION;
    message.partySlot = partySlot;
    message.switchingOrCanPickCommandMask = battleCtx->battlersSwitchingMask | battlersCanPickCommandMask;

    battleType = BattleSystem_GetBattleType(battleSys);

    if ((battleType & BATTLE_TYPE_DOUBLES) && (battleType & BATTLE_TYPE_2vs2) == FALSE) {
        battlerType = battler & BATTLER_THEM;
    } else {
        battlerType = battler;
    }

    party = BattleSystem_GetParty(battleSys, battlerType);
    cnt = 0;

    for (i = 0; i < Party_GetCurrentCount(party); i++) {
        pokemon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battlerType][i]);
        monSpeciesOrEgg = Pokemon_GetValue(pokemon, MON_DATA_SPECIES_OR_EGG, NULL);

        if (monSpeciesOrEgg && monSpeciesOrEgg != SPECIES_EGG) {
            if (Pokemon_GetValue(pokemon, MON_DATA_HP, NULL)) {
                if (Pokemon_GetValue(pokemon, MON_DATA_STATUS, NULL)) {
                    message.ballStatus[PARTY_GAUGE_OURS][cnt] = STOCK_STATUS_HAS_STATUS_CONDITION;
                } else {
                    message.ballStatus[PARTY_GAUGE_OURS][cnt] = STOCK_STATUS_MON_ALIVE;
                }
            } else {
                message.ballStatus[PARTY_GAUGE_OURS][cnt] = STOCK_STATUS_MON_FAINTED;
            }

            if (battleType & (BATTLE_TYPE_LINK | BATTLE_TYPE_SAFARI | BATTLE_TYPE_FRONTIER | BATTLE_TYPE_PAL_PARK)) {
                message.expPercents[cnt] = 0;
            } else {
                message.expPercents[cnt] = Pokemon_GetPercentToNextLevel(pokemon);
            }

            cnt++;
        }
    }

    if (((battleType & (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2)) == (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2)) ||
        (battleType & BATTLE_TYPE_TAG) ||
        // The flags from BATTLE_TYPE_FRONTIER up are ignored.
        (battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_TRAINER_WITH_AI_PARTNER) {
        if (BattleSystem_GetBattlerSide(battleSys, battler)) {
            battlerType = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
        } else {
            battlerType = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_1);
        }

        party = BattleSystem_GetParty(battleSys, battlerType);
        cnt = 0;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            pokemon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battlerType][i]);
            monSpeciesOrEgg = Pokemon_GetValue(pokemon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (monSpeciesOrEgg && monSpeciesOrEgg != SPECIES_EGG) {
                if (Pokemon_GetValue(pokemon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(pokemon, MON_DATA_STATUS, NULL)) {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_FAINTED;
                }

                cnt++;
            }
        }

        if (BattleSystem_GetBattlerSide(battleSys, battler)) {
            battlerType = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
        } else {
            battlerType = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_2);
        }

        party = BattleSystem_GetParty(battleSys, battlerType);
        cnt = 3;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            pokemon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battlerType][i]);
            monSpeciesOrEgg = Pokemon_GetValue(pokemon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (monSpeciesOrEgg && monSpeciesOrEgg != SPECIES_EGG) {
                if (Pokemon_GetValue(pokemon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(pokemon, MON_DATA_STATUS, NULL)) {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_FAINTED;
                }

                cnt++;
            }
        }
    } else {
        battlerType = BattleSystem_GetEnemyInSlot(battleSys, battler, ENEMY_IN_SLOT_LEFT);
        party = BattleSystem_GetParty(battleSys, battlerType);
        cnt = 0;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            pokemon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battlerType][i]);
            monSpeciesOrEgg = Pokemon_GetValue(pokemon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (monSpeciesOrEgg && monSpeciesOrEgg != SPECIES_EGG) {
                if (Pokemon_GetValue(pokemon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(pokemon, MON_DATA_STATUS, NULL)) {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    message.ballStatus[PARTY_GAUGE_THEIRS][cnt] = STOCK_STATUS_MON_FAINTED;
                }

                cnt++;
            }
        }
    }

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] = BattleMon_Get(battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MOVE_1 + i), NULL);
        message.curPP[i] = BattleMon_Get(battleCtx, battler, (enum BattleMonParam)(BATTLEMON_CUR_PP_1 + i), NULL);
        message.maxPP[i] = BattleMon_Get(battleCtx, battler, (enum BattleMonParam)(BATTLEMON_MAX_PP_1 + i), NULL);
    }

    message.curHP = battleCtx->battleMons[battler].curHP;
    message.maxHP = battleCtx->battleMons[battler].maxHP;

    if (message.curHP) {
        if (battleCtx->battleMons[battler].status) {
            message.ballStatusBattler = STOCK_STATUS_HAS_STATUS_CONDITION;
        } else {
            message.ballStatusBattler = STOCK_STATUS_MON_ALIVE;
        }
    } else {
        message.ballStatusBattler = STOCK_STATUS_MON_FAINTED;
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(CommandSetMessage));
}

void BattleController_EmitSelectedCommand(BattleSystem *battleSys, int battler, int command) {
    command = SWAP_BYTES_32(command);
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &command, sizeof(int));
}

void BattleController_EmitShowMoveSelectMenu(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    BattleIO_ClearBuffer(BattleSystem_GetBattleContext(battleSys), battler);
    MoveSelectMenuMessage message;

    message.command = BATTLE_COMMAND_SHOW_MOVE_SELECT_MENU;
    message.partySlot = battleCtx->selectedPartySlot[battler];

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] = battleCtx->battleMons[battler].moves[i];
        message.ppCur[i] = battleCtx->battleMons[battler].ppCur[i];
        message.ppMax[i] =
            MoveTable_CalcMaxPP(battleCtx->battleMons[battler].moves[i], battleCtx->battleMons[battler].ppUps[i]);
    }

    message.invalidMoves = BattleSystem_CheckInvalidMoves(battleSys, battleCtx, battler, 0, CHECK_INVALID_ALL);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MoveSelectMenuMessage));
}

void BattleController_EmitSelectedMove(BattleSystem *battleSys, int battler, int command) {
    command = SWAP_BYTES_32(command);
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &command, sizeof(int));
}

void BattleCommand_EmitShowTargetSelectMenu(BattleSystem *battleSys, BattleContext *battleCtx, int range, int battler) {
    TargetSelectMenuMessage message;
    int i;
    u32 battleType;

    BattleIO_ClearBuffer(battleCtx, battler);
    battleType = BattleSystem_GetBattleType(battleSys);

    message.command = BATTLE_COMMAND_SHOW_TARGET_SELECT_MENU;
    message.range = range;

    if ((battleType & BATTLE_TYPE_DOUBLES) == FALSE || (battleType & BATTLE_TYPE_2vs2) ||
        ((battleType & BATTLE_TYPE_DOUBLES) && battler >= 2)) {
        message.shouldHidePanel = 1;
    } else {
        message.shouldHidePanel = 0;
    }

    for (i = 0; i < MAX_BATTLERS; i++) {
        if (battleCtx->battleMons[i].curHP) {
            message.targetMon[i].curHP = battleCtx->battleMons[i].curHP;
            message.targetMon[i].maxHP = battleCtx->battleMons[i].maxHP;
            message.targetMon[i].isPresent = 1;

            if ((battleCtx->battleMons[i].species == SPECIES_NIDORAN_F ||
                 battleCtx->battleMons[i].species == SPECIES_NIDORAN_M) &&
                battleCtx->battleMons[i].hasNickname == FALSE) {
                message.targetMon[i].gender = GENDER_NONE;
            } else {
                message.targetMon[i].gender = battleCtx->battleMons[i].gender;
            }

            message.targetMon[i].partySlot = battleCtx->selectedPartySlot[i];

            if (battleCtx->battleMons[i].status) {
                message.targetMon[i].stockStatus = STOCK_STATUS_HAS_STATUS_CONDITION;
            } else {
                message.targetMon[i].stockStatus = STOCK_STATUS_MON_ALIVE;
            }
        } else {
            message.targetMon[i].isPresent = 0;
            message.targetMon[i].stockStatus = STOCK_STATUS_MON_FAINTED;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(TargetSelectMenuMessage));
}

void BattleController_EmitSelectedTarget(BattleSystem *battleSys, int battler, int command) {
    command = SWAP_BYTES_32(command);
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &command, sizeof(int));
}

void BattleController_EmitShowBagMenu(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    BagMenuMessage message;
    int i, j;

    BattleIO_ClearBuffer(battleCtx, battler);

    message.command = BATTLE_COMMAND_SHOW_BAG_MENU;

    for (i = 0; i < MAX_BATTLERS; i++) {
        message.partySlots[i] = battleCtx->selectedPartySlot[i];

        for (j = 0; j < MAX_PARTY_SIZE; j++) {
            message.partyOrder[i][j] = battleCtx->partyOrder[i][j];
        }

        message.embargoTurns[i] = battleCtx->battleMons[i].moveEffectsData.embargoTurns;
    }

    if (BattleSystem_GetBattleType(battleSys) == BATTLE_TYPE_AI_PARTNER) {
        if ((battleCtx->battlersSwitchingMask & FlagIndex(1)) == FALSE &&
            (battleCtx->battlersSwitchingMask & FlagIndex(3)) == FALSE) {
            message.hasTwoOpponents = TRUE;
            message.semiInvulnerable = FALSE;
            message.substitute = FALSE;
        } else if ((battleCtx->battlersSwitchingMask & FlagIndex(1)) == FALSE) {
            message.hasTwoOpponents = FALSE;

            if (battleCtx->battleMons[1].moveEffectsMask & MOVE_EFFECT_SEMI_INVULNERABLE) {
                message.semiInvulnerable = TRUE;
                message.substitute = FALSE;
            } else if (battleCtx->battleMons[1].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) {
                message.semiInvulnerable = FALSE;
                message.substitute = TRUE;
            } else {
                message.semiInvulnerable = FALSE;
                message.substitute = FALSE;
            }
        } else {
            message.hasTwoOpponents = FALSE;

            if (battleCtx->battleMons[3].moveEffectsMask & MOVE_EFFECT_SEMI_INVULNERABLE) {
                message.semiInvulnerable = TRUE;
                message.substitute = FALSE;
            } else if (battleCtx->battleMons[3].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) {
                message.semiInvulnerable = FALSE;
                message.substitute = TRUE;
            } else {
                message.semiInvulnerable = FALSE;
                message.substitute = FALSE;
            }
        }
    } else if (BattleSystem_GetBattleType(battleSys) == BATTLE_TYPE_WILD_MON) {
        message.hasTwoOpponents = FALSE;

        if (battleCtx->battleMons[1].moveEffectsMask & MOVE_EFFECT_SEMI_INVULNERABLE) {
            message.semiInvulnerable = TRUE;
            message.substitute = FALSE;
        } else if (battleCtx->battleMons[1].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) {
            message.semiInvulnerable = FALSE;
            message.substitute = TRUE;
        } else {
            message.semiInvulnerable = FALSE;
            message.substitute = FALSE;
        }
    } else {
        message.hasTwoOpponents = FALSE;
        message.semiInvulnerable = FALSE;
        message.substitute = FALSE;
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(BagMenuMessage));
}

void BattleController_EmitSelectedBagItem(BattleSystem *battleSys, int battler, BattleItemUse message) {
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &message, sizeof(BattleItemUse));
}

void BattleController_EmitShowPartyMenu(
    BattleSystem *battleSys, BattleContext *battleCtx, int battler, int listMode, int canSwitch, int doublesSelection) {
    PartyMenuMessage message;
    int i, j;

    BattleIO_ClearBuffer(battleCtx, battler);

    message.command = BATTLE_COMMAND_SHOW_PARTY_MENU;
    message.battler = battler;
    message.listMode = listMode;
    message.canSwitch = canSwitch;
    message.doublesSelection = doublesSelection;
    message.battlersSwitchingMask = battleCtx->battlersSwitchingMask;

    for (i = 0; i < MAX_BATTLERS; i++) {
        message.selectedPartySlot[i] = battleCtx->selectedPartySlot[i];

        for (j = 0; j < MAX_PARTY_SIZE; j++) {
            message.partyOrder[i][j] = battleCtx->partyOrder[i][j];
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(PartyMenuMessage));
}

void BattleController_EmitPartyMenuResult(BattleSystem *battleSys, int battler, int command) {
    command = SWAP_BYTES_32(command);
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &command, sizeof(int));
}

void BattleController_EmitShowYesNoMenu(BattleSystem *battleSys,
                                        BattleContext *battleCtx,
                                        int battler,
                                        int promptMsg,
                                        int yesNoType,
                                        int move,
                                        int nickname) {
    YesNoMenuMessage message;

    BattleIO_ClearBuffer(battleCtx, battler);

    message.command = BATTLE_COMMAND_SHOW_YES_NO_MENU;
    message.promptMsg = promptMsg;
    message.yesNoType = yesNoType;
    message.move = move;
    message.nickname = nickname;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(YesNoMenuMessage));
}

void BattleController_EmitPrintAttackMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    AttackMsgMessage message;

    message.command = BATTLE_COMMAND_PRINT_ATTACK_MESSAGE;
    message.partySlot = battleCtx->selectedPartySlot[battleCtx->attacker];
    message.move = battleCtx->moveCur;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battleCtx->attacker, &message, sizeof(AttackMsgMessage));
}

void BattleController_EmitPrintMessage(BattleSystem *battleSys, BattleContext *battleCtx, BattleMessage *battleMsg) {
    battleMsg->commandCode = BATTLE_COMMAND_PRINT_MESSAGE;
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battleCtx->attacker, battleMsg, sizeof(BattleMessage));
}

void BattleController_EmitPlayMoveAnimation(BattleSystem *battleSys, BattleContext *battleCtx, u16 move) {
    MoveAnimation animation;

    BattleController_SetMoveAnimation(battleSys,
                                      battleCtx,
                                      &animation,
                                      0,
                                      0,
                                      battleCtx->attacker,
                                      battleCtx->defender,
                                      move);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battleCtx->attacker, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitPlayMoveAnimationA2D(
    BattleSystem *battleSys, BattleContext *battleCtx, u16 move, int attacker, int defender) {
    MoveAnimation animation;

    BattleController_SetMoveAnimation(battleSys, battleCtx, &animation, 0, 0, attacker, defender, move);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, attacker, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitFlickerBattlerSprite(BattleSystem *battleSys, int battler, u32 unused) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_FLICKER_BATTLER);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitUpdateHPGauge(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    HPGaugeUpdateMessage message;
    Pokemon *pokemon = BattleSystem_GetPartyPokemon(battleSys, battler, battleCtx->selectedPartySlot[battler]);
    int species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
    int level = Pokemon_GetValue(pokemon, MON_DATA_LEVEL, NULL);

    message.command = BATTLE_COMMAND_UPDATE_HP_GAUGE;
    message.level = battleCtx->battleMons[battler].level;
    message.curHP = battleCtx->battleMons[battler].curHP;
    message.maxHP = battleCtx->battleMons[battler].maxHP;
    message.hpCalcTemp = battleCtx->hpCalcTemp;

    if ((battleCtx->battleMons[battler].species == SPECIES_NIDORAN_F ||
         battleCtx->battleMons[battler].species == SPECIES_NIDORAN_M) &&
        battleCtx->battleMons[battler].hasNickname == FALSE) {
        message.gender = GENDER_NONE;
    } else {
        message.gender = battleCtx->battleMons[battler].gender;
    }

    message.exp = battleCtx->battleMons[battler].exp - Pokemon_GetSpeciesBaseExpAt(species, level);
    message.expToNextLevel =
        Pokemon_GetSpeciesBaseExpAt(species, level + 1) - Pokemon_GetSpeciesBaseExpAt(species, level);

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(HPGaugeUpdateMessage));
}

void BattleController_EmitUpdateExpGauge(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int curExp) {
    ExpGaugeUpdateMessage message;
    Pokemon *pokemon = BattleSystem_GetPartyPokemon(battleSys, battler, battleCtx->selectedPartySlot[battler]);
    int species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
    int level = Pokemon_GetValue(pokemon, MON_DATA_LEVEL, NULL);

    message.command = BATTLE_COMMAND_UPDATE_EXP_GAUGE;
    message.curExp = curExp;
    message.gainedExp = battleCtx->battleMons[battler].exp - Pokemon_GetSpeciesBaseExpAt(species, level);
    message.expToNextLevel =
        Pokemon_GetSpeciesBaseExpAt(species, level + 1) - Pokemon_GetSpeciesBaseExpAt(species, level);

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(ExpGaugeUpdateMessage));
}

void BattleController_EmitPlayFaintingSequence(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    FaintingSequenceMessage message;
    int i;

    message.command = BATTLE_COMMAND_PLAY_FAINTING_SEQUENCE;
    message.species = battleCtx->battleMons[battler].species;
    message.form = battleCtx->battleMons[battler].formNum;
    message.isSubstitute = (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) != 0;
    message.isTransformed = (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRANSFORM) != 0;

    if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
        message.gender = battleCtx->battleMons[battler].moveEffectsData.transformedGender;
        message.personality = battleCtx->battleMons[battler].moveEffectsData.transformedPID;
    } else {
        message.gender = battleCtx->battleMons[battler].gender;
        message.personality = battleCtx->battleMons[battler].personality;
    }

    for (i = 0; i < MAX_BATTLERS; i++) {
        message.monSpecies[i] = battleCtx->battleMons[i].species;
        message.monShiny[i] = battleCtx->battleMons[i].isShiny;
        message.monFormNums[i] = battleCtx->battleMons[i].formNum;

        if (battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            message.monGenders[i] = battleCtx->battleMons[i].moveEffectsData.transformedGender;
            message.monPersonalities[i] = battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            message.monGenders[i] = battleCtx->battleMons[i].gender;
            message.monPersonalities[i] = battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(FaintingSequenceMessage));
}

void BattleController_EmitPlaySound(BattleSystem *battleSys, BattleContext *battleCtx, int sdatID, int battler) {
    PlaySoundMessage message;

    message.command = BATTLE_COMMAND_PLAY_SOUND;
    message.sdatID = sdatID;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(PlaySoundMessage));
}

void BattleController_EmitFadeOut(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_FADE_OUT);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitToggleVanish(BattleSystem *battleSys, int battler, int toggle) {
    ToggleVanishMessage message;
    int i;

    message.command = BATTLE_COMMAND_TOGGLE_VANISH;
    message.toggle = toggle;
    message.isSubstitute =
        (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) != 0;

    for (i = 0; i < MAX_BATTLERS; i++) {
        message.species[i] = battleSys->battleCtx->battleMons[i].species;
        message.isShiny[i] = battleSys->battleCtx->battleMons[i].isShiny;
        message.formNum[i] = battleSys->battleCtx->battleMons[i].formNum;

        if (battleSys->battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            message.gender[i] = battleSys->battleCtx->battleMons[i].moveEffectsData.transformedGender;
            message.personality[i] = battleSys->battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            message.gender[i] = battleSys->battleCtx->battleMons[i].gender;
            message.personality[i] = battleSys->battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(ToggleVanishMessage));
}

void BattleController_EmitSetStatusIcon(BattleSystem *battleSys, int battler, int status) {
    SetStatusIconMessage message;

    message.command = BATTLE_COMMAND_SET_STATUS_ICON;
    message.status = status;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(SetStatusIconMessage));
}

void BattleController_EmitTrainerMessage(BattleSystem *battleSys, int battler, int msg) {
    TrainerMsgMessage message;

    message.command = BATTLE_COMMAND_PRINT_TRAINER_MESSAGE;
    message.msg = msg;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(TrainerMsgMessage));
}

void BattleController_EmitPlayStatusEffect(BattleSystem *battleSys,
                                           BattleContext *battleCtx,
                                           int battler,
                                           int secondaryAnimID) {
    MoveAnimation animation;

    BattleController_SetMoveAnimation(battleSys, battleCtx, &animation, 1, secondaryAnimID, battler, battler, 0);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitPlayStatusEffectAToD(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int secondaryAnimID) {
    MoveAnimation animation;

    BattleController_SetMoveAnimation(battleSys, battleCtx, &animation, 1, secondaryAnimID, attacker, defender, 0);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, attacker, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitRecallMessage(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int partySlot) {
    RecallMsgMessage message;

    message.command = BATTLE_COMMAND_PRINT_RECALL_MESSAGE;
    message.partySlot = partySlot;
    message.hpPercent = (battleCtx->hpTemp - battleCtx->battleMons[1].curHP) * 100 / battleCtx->hpTemp;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(RecallMsgMessage));
}

void BattleController_EmitSendOutMessage(BattleSystem *battleSys,
                                         BattleContext *battleCtx,
                                         int battler,
                                         int partySlot) {
    SendOutMsgMessage message;

    message.command = BATTLE_COMMAND_PRINT_SEND_OUT_MESSAGE;
    message.partySlot = partySlot;

    if (battleCtx->battleMons[1].curHP == 0) {
        message.hpPercent = 1000;
    } else {
        message.hpPercent = battleCtx->battleMons[1].curHP * 1000 / battleCtx->battleMons[1].maxHP;
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(SendOutMsgMessage));
}

void BattleController_EmitBattleStartMessage(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_PRINT_BATTLE_START_MESSAGE);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitLeadMonMessage(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    LeadMonMsgMessage message;
    int i;

    message.command = BATTLE_COMMAND_PRINT_LEAD_MON_MESSAGE;

    for (i = 0; i < BattleSystem_GetMaxBattlers(battleSys); i++) {
        message.partySlot[i] = battleCtx->selectedPartySlot[i];
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(LeadMonMsgMessage));
}

void BattleController_EmitPlayLevelUpAnimation(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_PLAY_LEVEL_UP_ANIMATION);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitSetAlertMessage(BattleSystem *battleSys, int battler, BattleMessage msg) {
    BattleIO_ClearBuffer(BattleSystem_GetBattleContext(battleSys), battler);
    AlertMsgMessage message;

    message.command = BATTLE_COMMAND_SET_ALERT_MESSAGE;
    message.msg = msg;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(AlertMsgMessage));
}

void BattleController_EmitAlertMessageAck(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SETUP_UI);
    SendMessage(battleSys, COMM_RECIPIENT_SERVER, battler, &command, sizeof(int));
}

void BattleController_EmitRefreshHPGauge(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    RefreshHPGaugeMessage message;
    Pokemon *pokemon;
    int species;
    int level;

    pokemon = BattleSystem_GetPartyPokemon(battleSys, battler, battleCtx->selectedPartySlot[battler]);
    species = Pokemon_GetValue(pokemon, MON_DATA_SPECIES, NULL);
    level = Pokemon_GetValue(pokemon, MON_DATA_LEVEL, NULL);

    message.command = BATTLE_COMMAND_REFRESH_HP_GAUGE;
    message.level = battleCtx->battleMons[battler].level;
    message.curHP = battleCtx->battleMons[battler].curHP;
    message.maxHP = battleCtx->battleMons[battler].maxHP;
    message.partySlot = battleCtx->selectedPartySlot[battler];
    message.status = Battler_StatusCondition(battleCtx, battler);

    if ((battleCtx->battleMons[battler].species == SPECIES_NIDORAN_F ||
         battleCtx->battleMons[battler].species == SPECIES_NIDORAN_M) &&
        battleCtx->battleMons[battler].hasNickname == FALSE) {
        message.gender = GENDER_NONE;
    } else {
        message.gender = battleCtx->battleMons[battler].gender;
    }

    message.curExp = battleCtx->battleMons[battler].exp - Pokemon_GetSpeciesBaseExpAt(species, level);
    message.maxExp = Pokemon_GetSpeciesBaseExpAt(species, level + 1) - Pokemon_GetSpeciesBaseExpAt(species, level);
    message.caughtSpecies = BattleSystem_HasCaughtSpecies(battleSys, battleCtx->battleMons[battler].species);
    message.numSafariBalls = BattleSystem_GetNumSafariBalls(battleSys);

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(RefreshHPGaugeMessage));
}

void BattleController_EmitUpdatePartyMon(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    UpdatePartyMonMessage message;
    int i;

    message.command = BATTLE_COMMAND_UPDATE_PARTY_MON;
    message.partySlot = battleCtx->selectedPartySlot[battler];
    message.mimickedMoveSlot = battleCtx->battleMons[battler].moveEffectsData.mimickedMoveSlot;
    message.curHP = battleCtx->battleMons[battler].curHP;
    message.heldItem = battleCtx->battleMons[battler].heldItem;
    message.knockedOffItemsMask =
        battleCtx->sideConditions[BattleSystem_GetBattlerSide(battleSys, battler)].knockedOffItemsMask;

    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
        message.moves[i] = battleCtx->battleMons[battler].moves[i];
        message.ppCur[i] = battleCtx->battleMons[battler].ppCur[i];
    }

    if (message.curHP) {
        message.status = (battleCtx->battleMons[battler].status & ~MON_CONDITION_TOXIC_COUNTER);
        message.statusVolatile = battleCtx->battleMons[battler].statusVolatile;
    } else {
        message.status = 0;
        message.statusVolatile = battleCtx->battleMons[battler].statusVolatile;
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(UpdatePartyMonMessage));
}

void BattleController_EmitSlideInPanel(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SLIDE_IN_PANEL);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitStopGaugeAnimation(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_STOP_GAUGE_ANIMATION);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitRefreshPartyStatus(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move) {
    RefreshPartyStatusMessage message;

    message.command = BATTLE_COMMAND_REFRESH_PARTY_STATUS;
    message.move = move;
    message.ability = battleCtx->battleMons[battler].ability;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(RefreshPartyStatusMessage));
}

void BattleController_EmitForgetMove(BattleSystem *battleSys, int battler, int move, int slot) {
    ForgetMoveMessage message;

    BattleIO_ClearBuffer(BattleSystem_GetBattleContext(battleSys), battler);

    message.command = BATTLE_COMMAND_FORGET_MOVE;
    message.move = move;
    message.slot = slot;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(RefreshPartyStatusMessage));
}

void BattleController_EmitSetMosaic(BattleSystem *battleSys, int battler, int intensity, int wait) {
    MosaicSetMessage message;

    message.command = BATTLE_COMMAND_SET_MOSAIC;
    message.intensity = intensity;
    message.wait = wait;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MosaicSetMessage));
}

void BattleController_EmitChangeWeatherForm(BattleSystem *battleSys, int battler) {
    MonChangeFormMessage message;

    message.command = BATTLE_COMMAND_CHANGE_WEATHER_FORM;
    message.species = battleSys->battleCtx->battleMons[battler].species;
    message.isShiny = battleSys->battleCtx->battleMons[battler].isShiny;

    if (battleSys->battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
        message.gender = battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedGender;
        message.personality = battleSys->battleCtx->battleMons[battler].moveEffectsData.transformedPID;
    } else {
        message.gender = battleSys->battleCtx->battleMons[battler].gender;
        message.personality = battleSys->battleCtx->battleMons[battler].personality;
    }

    message.formNum = battleSys->battleCtx->battleMons[battler].formNum;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MonChangeFormMessage));
}

void BattleController_EmitUpdateBG(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_UPDATE_BG);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitClearTouchScreen(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_CLEAR_TOUCH_SCREEN);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitShowBattleStartPartyGauge(BattleSystem *battleSys, int battler) {
    PartyGaugeData gauge;

    PartyGaugeData_New(battleSys, battleSys->battleCtx, &gauge, BATTLE_COMMAND_SHOW_BATTLE_START_PARTY_GAUGE, battler);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &gauge, sizeof(PartyGaugeData));
}

void BattleController_EmitHideBattleStartPartyGauge(BattleSystem *battleSys, int battler) {
    PartyGaugeData gauge;

    PartyGaugeData_New(battleSys, battleSys->battleCtx, &gauge, BATTLE_COMMAND_HIDE_BATTLE_START_PARTY_GAUGE, battler);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &gauge, sizeof(PartyGaugeData));
}

void BattleController_EmitShowPartyGauge(BattleSystem *battleSys, int battler) {
    PartyGaugeData gauge;

    PartyGaugeData_New(battleSys, battleSys->battleCtx, &gauge, BATTLE_COMMAND_SHOW_PARTY_GAUGE, battler);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &gauge, sizeof(PartyGaugeData));
}

void BattleController_EmitHidePartyGauge(BattleSystem *battleSys, int battler) {
    PartyGaugeData gauge;

    PartyGaugeData_New(battleSys, battleSys->battleCtx, &gauge, BATTLE_COMMAND_HIDE_PARTY_GAUGE, battler);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &gauge, sizeof(PartyGaugeData));
}

void BattleController_EmitLoadPartyGaugeGraphics(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_LOAD_PARTY_GAUGE_GRAPHICS);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitFreePartyGaugeGraphics(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_FREE_PARTY_GAUGE_GRAPHICS);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitIncrementRecord(BattleSystem *battleSys, int battler, int battlerType, int record) {
    RecordIncrementMessage message;

    message.command = BATTLE_COMMAND_INCREMENT_RECORD;
    message.battlerType = battlerType;
    message.record = record;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(RecordIncrementMessage));
}

// No recorded inputs in this game: only the command is sent, and only in link battles.
void BattleController_EmitPrintLinkWaitMessage(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_PRINT_LINK_WAIT_MESSAGE);

    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) {
        SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
    }
}

void BattleController_EmitRestoreSprite(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    int i;
    MoveAnimation animation;

    animation.command = BATTLE_COMMAND_RESTORE_SPRITE;

    for (i = 0; i < MAX_BATTLERS; i++) {
        animation.species[i] = battleCtx->battleMons[i].species;
        animation.isShiny[i] = battleCtx->battleMons[i].isShiny;
        animation.formNums[i] = battleCtx->battleMons[i].formNum;

        if (battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            animation.genders[i] = battleCtx->battleMons[i].moveEffectsData.transformedGender;
            animation.personalities[i] = battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            animation.genders[i] = battleCtx->battleMons[i].gender;
            animation.personalities[i] = battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitSpriteToOAM(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_SPRITE_TO_OAM);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitOAMToSprite(BattleSystem *battleSys, int battler) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_OAM_TO_SPRITE);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &command, sizeof(int));
}

void BattleController_EmitResultMessage(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_PRINT_RESULT_MESSAGE);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitEscapeMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    EscapeMsgMessage message;
    int i;

    message.command = BATTLE_COMMAND_PRINT_ESCAPE_MESSAGE;
    message.escaperBitmask = 0;

    for (i = 0; i < BattleSystem_GetMaxBattlers(battleSys); i++) {
        if (battleCtx->battlerActions[i][0] == BATTLE_CONTROL_RUN) {
            message.escaperBitmask |= FlagIndex(i);
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &message, sizeof(EscapeMsgMessage));
}

void BattleController_EmitForfeitMessage(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_PRINT_FORFEIT_MESSAGE);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitRefreshSprite(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    int i;
    MoveAnimation animation;

    animation.command = BATTLE_COMMAND_REFRESH_SPRITE;

    for (i = 0; i < MAX_BATTLERS; i++) {
        animation.species[i] = battleCtx->battleMons[i].species;
        animation.isShiny[i] = battleCtx->battleMons[i].isShiny;
        animation.formNums[i] = battleCtx->battleMons[i].formNum;

        if (battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
            animation.genders[i] = battleCtx->battleMons[i].moveEffectsData.transformedGender;
            animation.personalities[i] = battleCtx->battleMons[i].moveEffectsData.transformedPID;
        } else {
            animation.genders[i] = battleCtx->battleMons[i].gender;
            animation.personalities[i] = battleCtx->battleMons[i].personality;
        }
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &animation, sizeof(MoveAnimation));
}

void BattleController_EmitPlayMoveHitSoundEffect(BattleSystem *battleSys, BattleContext *battleCtx, int battler) {
    MoveHitSoundMessage message;

    message.command = BATTLE_COMMAND_FLY_MOVE_HIT_SOUND_EFFECT;

    if (battleCtx->moveStatusFlags & MOVE_STATUS_SUPER_EFFECTIVE) {
        message.effectiveness = 2;
    } else if (battleCtx->moveStatusFlags & MOVE_STATUS_NOT_VERY_EFFECTIVE) {
        message.effectiveness = 1;
    } else {
        message.effectiveness = 0;
    }

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MoveHitSoundMessage));
}

void BattleController_EmitPlayMusic(BattleSystem *battleSys, int battler, int bgmID) {
    MusicPlayMessage message;

    message.command = BATTLE_COMMAND_PLAY_MUSIC;
    message.bgmID = bgmID;

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, battler, &message, sizeof(MusicPlayMessage));
}

void BattleController_EmitSubmitResult(BattleSystem *battleSys) {
    ResultSubmitMessage message;

    message.command = BATTLE_COMMAND_SUBMIT_RESULT;
    message.resultMask = fn_803ADCD8(battleSys);

    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &message, sizeof(ResultSubmitMessage));
}

void BattleController_EmitClearMessageBox(BattleSystem *battleSys) {
    int command = SWAP_BYTES_32(BATTLE_COMMAND_CLEAR_MESSAGE_BOX);
    SendMessage(battleSys, COMM_RECIPIENT_CLIENT, 0, &command, sizeof(int));
}

void BattleController_EmitClearCommand(BattleSystem *battleSys, int battler, int command) {
    CommandClearMsg message;

    message.command = command;
    message.netID = fn_803D9848();

    SendMessage(battleSys, COMM_RECIPIENT_QUEUE, battler, &message, sizeof(CommandClearMsg));
}

void BattleController_SetMoveAnimation(BattleSystem *battleSys,
                                       BattleContext *battleCtx,
                                       MoveAnimation *animation,
                                       int animMode,
                                       int secondaryAnimID,
                                       int attacker,
                                       int defender,
                                       u16 move) {
    int i;

    animation->command = BATTLE_COMMAND_SET_MOVE_ANIMATION;
    animation->move = move;
    animation->attacker = attacker;
    animation->defender = defender;
    animation->animMode = animMode;
    animation->secondaryAnimID = secondaryAnimID;
    animation->terrain = BattleSystem_GetTerrain(battleSys);

    if (battleCtx != NULL) {
        animation->damage = battleCtx->damage;

        if (battleCtx->movePower) {
            animation->power = battleCtx->movePower;
        } else {
            animation->power = battleCtx->aiContext.moveTable[move].power;
        }

        animation->friendship = battleCtx->battleMons[attacker].friendship;

        if (BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALIVE_BATTLERS, 0, ABILITY_CLOUD_NINE) == 0 &&
            BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALIVE_BATTLERS, 0, ABILITY_AIR_LOCK) == 0) {
            animation->fieldConditions = battleCtx->fieldConditionsMask;
        } else {
            animation->fieldConditions = 0;
        }

        animation->effectChance = battleCtx->moveEffectChance;
        animation->isSubstitute = (battleCtx->battleMons[attacker].statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) != 0;
        animation->isTransformed = (battleCtx->battleMons[attacker].statusVolatile & VOLATILE_CONDITION_TRANSFORM) != 0;

        for (i = 0; i < MAX_BATTLERS; i++) {
            animation->species[i] = battleCtx->battleMons[i].species;
            animation->isShiny[i] = battleCtx->battleMons[i].isShiny;
            animation->formNums[i] = battleCtx->battleMons[i].formNum;
            animation->moveEffectMasks[i] = battleCtx->battleMons[i].moveEffectsMask;

            if (battleCtx->battleMons[i].statusVolatile & VOLATILE_CONDITION_TRANSFORM) {
                animation->genders[i] = battleCtx->battleMons[i].moveEffectsData.transformedGender;
                animation->personalities[i] = battleCtx->battleMons[i].moveEffectsData.transformedPID;
            } else {
                animation->genders[i] = battleCtx->battleMons[i].gender;
                animation->personalities[i] = battleCtx->battleMons[i].personality;
            }
        }
    }
}

static void PartyGaugeData_New(
    BattleSystem *battleSys, BattleContext *battleCtx, PartyGaugeData *partyGauge, int command, int battler) {
    memset(partyGauge, 0, sizeof(PartyGaugeData));
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    partyGauge->command = command;
    int battler1;
    int i;
    int slot;
    Party *party;
    Pokemon *mon;
    int species;

    if ((battleType & (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2)) == (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2) ||
        ((battleType & BATTLE_TYPE_TAG) && BattleSystem_GetBattlerSide(battleSys, battler)) ||
        ((battleType == BATTLE_TYPE_TRAINER_WITH_AI_PARTNER) && BattleSystem_GetBattlerSide(battleSys, battler)) ||
        battleType == BATTLE_TYPE_FRONTIER_WITH_AI_PARTNER) {
        if (BattleSystem_GetBattlerType(battleSys, battler) == BATTLER_PLAYER_2 ||
            BattleSystem_GetBattlerType(battleSys, battler) == BATTLER_ENEMY_2) {
            battler1 = battler;
            battler = BattleSystem_GetPartner(battleSys, battler);
        } else {
            battler1 = BattleSystem_GetPartner(battleSys, battler);
        }

        party = BattleSystem_GetParty(battleSys, battler1);
        slot = 0;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            mon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battler1][i]);
            species = Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (species && species != SPECIES_EGG) {
                if (Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(mon, MON_DATA_STATUS, NULL)) {
                        partyGauge->status[slot] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        partyGauge->status[slot] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    partyGauge->status[slot] = STOCK_STATUS_MON_FAINTED;
                }

                slot++;
            }
        }
        party = BattleSystem_GetParty(battleSys, battler);
        slot = 3;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            mon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battler][i]);
            species = Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (species && species != SPECIES_EGG) {
                if (Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(mon, MON_DATA_STATUS, NULL)) {
                        partyGauge->status[slot] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        partyGauge->status[slot] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    partyGauge->status[slot] = STOCK_STATUS_MON_FAINTED;
                }

                slot++;
            }
        }
    } else {
        if ((battleType & BATTLE_TYPE_DOUBLES) && (battleType & BATTLE_TYPE_2vs2) == FALSE) {
            battler = battler & 1;
        } else {
            battler = battler;
        }

        party = BattleSystem_GetParty(battleSys, battler);
        slot = 0;

        for (i = 0; i < Party_GetCurrentCount(party); i++) {
            mon = Party_GetPokemonBySlotIndex(party, battleCtx->partyOrder[battler][i]);
            species = Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL);

            if (species && species != SPECIES_EGG) {
                if (Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                    if (Pokemon_GetValue(mon, MON_DATA_STATUS, NULL)) {
                        partyGauge->status[slot] = STOCK_STATUS_HAS_STATUS_CONDITION;
                    } else {
                        partyGauge->status[slot] = STOCK_STATUS_MON_ALIVE;
                    }
                } else {
                    partyGauge->status[slot] = STOCK_STATUS_MON_FAINTED;
                }

                slot++;
            }
        }
    }
}
