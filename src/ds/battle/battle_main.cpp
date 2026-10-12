// 803AB534-803AC820 (part of battle_main.c): creation and teardown of the battle.

#include ".unsorted/8038F424.hpp"
#include "ds/DSbridge.hpp"
#include "ds/battle/battle_common.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_controller.hpp"
#include "ds/battle/battle_controller_player.hpp"
#include "ds/battle/battle_display.hpp"
#include "ds/battle/battle_io_command.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_system.hpp"
#include "ds/field_battle_data_transfer.hpp"
#include "ds/message.hpp"
#include "ds/overlay_manager.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"
#include "ds/strbuf.hpp"
#include "ds/string_template.hpp"
#include "ds/trainer_info.hpp"

#include <string.h>

static const u8 sSingleBattleBattlerTypes[MAX_BATTLERS / 2] = {
    BATTLER_TYPE_SOLO_PLAYER,
    BATTLER_TYPE_SOLO_ENEMY,
};

static const u8 sLinkSingleBattleBattlerTypes[MAX_BATTLERS / 2][MAX_BATTLERS / 2] = {
    {BATTLER_TYPE_SOLO_PLAYER,  BATTLER_TYPE_SOLO_ENEMY},
    { BATTLER_TYPE_SOLO_ENEMY, BATTLER_TYPE_SOLO_PLAYER},
};

static const u8 sDoubleBattleBattlerTypes[MAX_BATTLERS] = {
    BATTLER_TYPE_PLAYER_SIDE_SLOT_1,
    BATTLER_TYPE_ENEMY_SIDE_SLOT_1,
    BATTLER_TYPE_PLAYER_SIDE_SLOT_2,
    BATTLER_TYPE_ENEMY_SIDE_SLOT_2,
};

static const u8 sLinkDoubleBattleBattlerTypes[MAX_BATTLERS / 2][MAX_BATTLERS] = {
    {BATTLER_TYPE_PLAYER_SIDE_SLOT_1,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_1, BATTLER_TYPE_PLAYER_SIDE_SLOT_2,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_2 },
    { BATTLER_TYPE_ENEMY_SIDE_SLOT_1,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_1,  BATTLER_TYPE_ENEMY_SIDE_SLOT_2,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_2},
};

static const u8 sLink2vs2BattleBattlerTypes[MAX_BATTLERS][MAX_BATTLERS] = {
    {BATTLER_TYPE_PLAYER_SIDE_SLOT_1,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_2, BATTLER_TYPE_PLAYER_SIDE_SLOT_2,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_1 },
    { BATTLER_TYPE_ENEMY_SIDE_SLOT_1,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_2,  BATTLER_TYPE_ENEMY_SIDE_SLOT_2,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_1},
    {BATTLER_TYPE_PLAYER_SIDE_SLOT_1,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_2, BATTLER_TYPE_PLAYER_SIDE_SLOT_2,
     BATTLER_TYPE_ENEMY_SIDE_SLOT_1 },
    { BATTLER_TYPE_ENEMY_SIDE_SLOT_1,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_2,  BATTLER_TYPE_ENEMY_SIDE_SLOT_2,
     BATTLER_TYPE_PLAYER_SIDE_SLOT_1},
};

extern "C" {

enum BattleState {
    BATTLE_STATE_CREATE_HEAP = 0,
    BATTLE_STATE_INIT_LINK_COMM,
    BATTLE_STATE_WAIT_LINK_COMM,
    BATTLE_STATE_INIT_PARTNER_INTRO,
    BATTLE_STATE_WAIT_PARTNER_INTRO,
    BATTLE_STATE_INIT_TRAINER_INTRO,
    BATTLE_STATE_WAIT_TRAINER_INTRO,
    BATTLE_STATE_SYNC_BATTLE_START,
    BATTLE_STATE_INIT_GRAPHICS,
    BATTLE_STATE_MAIN,
    BATTLE_STATE_HANDLE_BATTLE_RESULT,
    BATTLE_STATE_LINK_BATTLE_END,
    BATTLE_STATE_LINK_BATTLE_FINISH,
    BATTLE_STATE_CHECK_EVOLUTION,
    BATTLE_STATE_WAIT_FOR_EVOLUTION,
    BATTLE_STATE_FINISH,
};

// pokeplatinum BattleSys_New, inlined in Battle_Main
static inline void BattleSys_New(BattleSystem *battleSys, FieldBattleDTO *dto) {
    int i;
    BattlerInitData battlerInitData;
    Pokemon *mon;
    int slot;

    battleSys->battleType = dto->battleType;

    for (i = 0; i < MAX_BATTLERS; i++) {
        battleSys->trainerInfo[i] = TrainerInfo_New(HEAP_ID_BATTLE);
        TrainerInfo_Copy(dto->trainerInfo[i], battleSys->trainerInfo[i]);
        battleSys->chatotCries[i] = dto->chatotCries[i];
    }

    battleSys->pcBoxes = dto->pcBoxes;
    battleSys->options = dto->options;
    battleSys->palPad = dto->palPad;
    battleSys->bagCursor = dto->bagCursor;
    battleSys->poketch = dto->poketch;
    battleSys->mapEvolutionMethod = dto->mapEvolutionMethod;
    battleSys->captureAttempt = dto->captureAttempt;
    battleSys->safariBalls = dto->countSafariBalls;
    battleSys->terrain = dto->terrain;
    battleSys->background = dto->background;
    battleSys->mapHeader = dto->mapLabelTextID;
    battleSys->time = dto->timeOfDay;
    battleSys->battleStatusMask = dto->battleStatusMask;
    battleSys->rulesetMask = dto->rulesetMask;
    battleSys->visitedContestHall = dto->visitedContestHall;
    battleSys->metBebe = dto->metBebe;
    battleSys->fieldWeather = dto->fieldWeather;
    battleSys->records = dto->records;

    for (i = 0; i < MAX_BATTLERS; i++) {
        battleSys->trainerIDs[i] = dto->trainerIDs[i];
        battleSys->trainers[i] = dto->trainers[i];
    }

    battleSys->battleCtx = BattleContext_New(battleSys);

    for (i = 0; i < MAX_BATTLERS; i++) {
        battleSys->parties[i] = Party_New(HEAP_ID_BATTLE);
    }

    if (battleSys->battleType & BATTLE_TYPE_LINK) {
        int netIDs[MAX_BATTLERS];
        int versions[MAX_BATTLERS];

        fn_803AB52C(battleSys);

        for (i = 0; i < MAX_BATTLERS; i++) {
            netIDs[i] = i;
            versions[i] = dto->systemVersion[i];
        }

        int netID = fn_803D9848();
        int connectedCount = fn_803D985C();

        // pokeplatinum BattleMain_AssignRecordingRoles, without the recording roles: sort the players by version.
        for (i = 0; i < connectedCount - 1; i++) {
            for (int j = i + 1; j < connectedCount; j++) {
                if (versions[i] < versions[j]) {
                    int tmp = netIDs[i];
                    netIDs[i] = netIDs[j];
                    netIDs[j] = tmp;
                    tmp = versions[i];
                    versions[i] = versions[j];
                    versions[j] = tmp;
                }
            }
        }

        if (netIDs[0] == netID) {
            battleSys->battleInitialized = TRUE;
        }

        if (battleSys->battleType & BATTLE_TYPE_FRONTIER) {
            for (i = 0; i < MAX_BATTLERS; i++) {
                battlerInitData.battler = i;
                battlerInitData.battlerType = sDoubleBattleBattlerTypes[i];
                battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            }

            battleSys->maxBattlers = i;

            for (i = 0; i < MAX_BATTLERS; i++) {
                BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
                Party_Copy(dto->parties[i], battleSys->parties[i]);
            }

            for (i = 0; i < battleSys->maxBattlers; i++) {
                for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i]); slot++) {
                    mon = Party_GetPokemonBySlotIndex(battleSys->parties[i], slot);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                }

                BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
            }

            BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);
        } else if (battleSys->battleType & BATTLE_TYPE_2vs2) {
            for (i = 0; i < MAX_BATTLERS; i++) {
                battlerInitData.battler = i;
                battlerInitData.battlerType = sLink2vs2BattleBattlerTypes[fn_803D983C(0)][fn_803D983C(i)];
                battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            }

            battleSys->maxBattlers = i;

            for (i = 0; i < MAX_BATTLERS; i++) {
                BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
                Party_Copy(dto->parties[i], battleSys->parties[i]);
            }

            for (i = 0; i < battleSys->maxBattlers; i++) {
                for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i]); slot++) {
                    mon = Party_GetPokemonBySlotIndex(battleSys->parties[i], slot);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                }

                BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
            }

            BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);
        } else if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
            for (i = 0; i < MAX_BATTLERS; i++) {
                battlerInitData.battler = i;
                battlerInitData.battlerType = sLinkDoubleBattleBattlerTypes[0][i];
                battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
                BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
            }

            battleSys->maxBattlers = i;

            for (i = 0; i < MAX_BATTLERS; i++) {
                Party_Copy(dto->parties[i], battleSys->parties[i]);
            }

            for (i = 0; i < battleSys->maxBattlers; i++) {
                for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i & 1]); slot++) {
                    mon = Party_GetPokemonBySlotIndex(battleSys->parties[i & 1], slot);

                    if (i > BATTLER_ENEMY_1) {
                        if (BattleContext_Get(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i & 1) !=
                                slot &&
                            Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                            Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                            Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                            break;
                        }
                    } else {
                        if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                            Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                            Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                            break;
                        }
                    }
                }

                BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
            }
        } else {
            for (i = 0; i < MAX_BATTLERS / 2; i++) {
                battlerInitData.battler = i;
                battlerInitData.battlerType = sLinkSingleBattleBattlerTypes[0][i];
                battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
                BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
            }

            battleSys->maxBattlers = i;

            for (i = 0; i < MAX_BATTLERS; i++) {
                Party_Copy(dto->parties[i], battleSys->parties[i]);

                for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i]); slot++) {
                    mon = Party_GetPokemonBySlotIndex(battleSys->parties[i], slot);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                }

                BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
            }
        }

        BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);
    } else if (battleSys->battleType & BATTLE_TYPE_TAG) {
        int playerSlot;

        for (i = 0; i < MAX_BATTLERS; i++) {
            battlerInitData.battler = i;
            battlerInitData.battlerType = sDoubleBattleBattlerTypes[i];
            battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
        }

        battleSys->maxBattlers = i;

        for (i = 0; i < MAX_BATTLERS; i++) {
            Party_Copy(dto->parties[i], battleSys->parties[i]);
        }

        for (i = 0; i < battleSys->maxBattlers; i++) {
            for (slot = 0; slot < BattleSystem_GetPartyCount(battleSys, i); slot++) {
                mon = BattleSystem_GetPartyPokemon(battleSys, i, slot);

                if (i == BATTLER_PLAYER_2) {
                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL) && playerSlot != slot) {
                        break;
                    }
                } else {
                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                }
            }

            BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);

            if (i == BATTLER_PLAYER_1) {
                playerSlot = slot;
            }
        }

        BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);

        if ((battleSys->battleType & BATTLE_TYPE_UNK_18) == FALSE) {
            battleSys->battleInitialized = TRUE;
        }
    } else if (battleSys->battleType & BATTLE_TYPE_2vs2) {
        for (i = 0; i < MAX_BATTLERS; i++) {
            battlerInitData.battler = i;
            battlerInitData.battlerType = sDoubleBattleBattlerTypes[i];
            battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
        }

        battleSys->maxBattlers = i;

        for (i = 0; i < MAX_BATTLERS; i++) {
            Party_Copy(dto->parties[i], battleSys->parties[i]);
        }

        for (i = 0; i < battleSys->maxBattlers; i++) {
            for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i]); slot++) {
                mon = Party_GetPokemonBySlotIndex(battleSys->parties[i], slot);

                if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                    Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE && Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                    break;
                }
            }

            BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
        }

        BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);

        if ((battleSys->battleType & BATTLE_TYPE_UNK_18) == FALSE) {
            battleSys->battleInitialized = TRUE;
        }
    } else if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        for (i = 0; i < MAX_BATTLERS; i++) {
            battlerInitData.battler = i;
            battlerInitData.battlerType = sDoubleBattleBattlerTypes[i];
            battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
        }

        battleSys->maxBattlers = i;

        for (i = 0; i < MAX_BATTLERS; i++) {
            Party_Copy(dto->parties[i], battleSys->parties[i]);
        }

        for (i = 0; i < battleSys->maxBattlers; i++) {
            for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i & 1]); slot++) {
                mon = Party_GetPokemonBySlotIndex(battleSys->parties[i & 1], slot);

                if (i > BATTLER_ENEMY_1) {
                    if (BattleContext_Get(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i & 1) !=
                            slot &&
                        Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                } else {
                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                        Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        break;
                    }
                }
            }

            BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
        }

        BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);

        if ((battleSys->battleType & BATTLE_TYPE_UNK_18) == FALSE) {
            battleSys->battleInitialized = TRUE;
        }
    } else {
        for (i = 0; i < MAX_BATTLERS / 2; i++) {
            battlerInitData.battler = i;
            battlerInitData.battlerType = sSingleBattleBattlerTypes[i];
            battleSys->battlers[i] = BattlerData_New(battleSys, &battlerInitData);
            BattlerData_SetTaskFuncs(battleSys, battleSys->battlers[i]);
        }

        battleSys->maxBattlers = i;

        for (i = 0; i < MAX_BATTLERS; i++) {
            Party_Copy(dto->parties[i], battleSys->parties[i]);

            for (slot = 0; slot < Party_GetCurrentCount(battleSys->parties[i]); slot++) {
                mon = Party_GetPokemonBySlotIndex(battleSys->parties[i], slot);

                if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                    Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE && Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                    break;
                }
            }

            BattleContext_Set(battleSys, battleSys->battleCtx, BATTLECTX_SELECTED_PARTY_SLOT, i, slot);
        }

        BattleSystem_InitPartyOrder(battleSys, battleSys->battleCtx);

        if ((battleSys->battleType & BATTLE_TYPE_UNK_18) == FALSE) {
            battleSys->battleInitialized = TRUE;
        }
    }
}

// pokeplatinum BattleMain_ExecuteBattlerCommands, inlined in Battle_Main
static inline int BattleMain_ExecuteBattlerCommands(ApplicationManager *appMan) {
    BattleSystem *battleSys = (BattleSystem *)ApplicationManager_Data(appMan);
    lbl_806405C0 = battleSys;

    if (battleSys->battleInitialized) {
        if (battleSys->battleType & BATTLE_TYPE_LINK) {
            BattleContext_Main(battleSys, battleSys->battleCtx);
        } else {
            battleSys->commandIsEndWait = BattleContext_Main(battleSys, battleSys->battleCtx);
            BattleController_TryRecvLocalMessage(battleSys);
        }
    }

    if (battleSys->battleInitialized) {
        for (int battler = 0; battler < battleSys->maxBattlers; battler++) {
            BattleSystem_ExecuteBattlerCommand(battleSys, battleSys->battlers[battler]);
        }
    }

    return battleSys->commandIsEndWait;
}

// TODO probably Battle_Main (pret). The state numbers are Platinum's; the battle system is created in the
// partner intro state (pokeplatinum BattleSys_New, inlined) and the main state runs the battlers
// (BattleMain_ExecuteBattlerCommands, inlined). The teardown is fn_803AC5F0, called by the game code.
BOOL fn_803AB534(ApplicationManager *appMan, s32 *state) {
    FieldBattleDTO *dto = (FieldBattleDTO *)ApplicationManager_Args(appMan);

    switch (*state) {
        case BATTLE_STATE_CREATE_HEAP:
            if (dto->battleType & BATTLE_TYPE_LINK) {
                *state = BATTLE_STATE_INIT_LINK_COMM;
            } else {
                *state = BATTLE_STATE_INIT_PARTNER_INTRO;
            }
            break;

        case BATTLE_STATE_INIT_LINK_COMM:
            ApplicationManager_NewData(appMan, 0x1028, HEAP_ID_BATTLE);
            *state = BATTLE_STATE_WAIT_LINK_COMM;
            break;

        case BATTLE_STATE_WAIT_LINK_COMM:
            fn_8016E0A0(ApplicationManager_Data(appMan));
            *state = BATTLE_STATE_INIT_PARTNER_INTRO;
            break;

        case BATTLE_STATE_INIT_PARTNER_INTRO: {
            BattleSystem *battleSys =
                (BattleSystem *)ApplicationManager_NewData(appMan, sizeof(BattleSystem), HEAP_ID_BATTLE);

            dto = (FieldBattleDTO *)ApplicationManager_Args(appMan);
            fn_803D9848();
            memset(battleSys, 0, sizeof(BattleSystem));
            BattleSys_New(battleSys, dto);

            *state = BATTLE_STATE_INIT_TRAINER_INTRO;
            break;
        }

        case BATTLE_STATE_WAIT_PARTNER_INTRO: *state = BATTLE_STATE_INIT_TRAINER_INTRO; break;

        case BATTLE_STATE_INIT_TRAINER_INTRO: *state = BATTLE_STATE_INIT_GRAPHICS; break;

        case BATTLE_STATE_WAIT_TRAINER_INTRO:
            fn_803D9854(2);
            *state = BATTLE_STATE_SYNC_BATTLE_START;
            fn_803D986C(61);
            break;

        case BATTLE_STATE_SYNC_BATTLE_START:
            if (fn_803D9864(61)) {
                *state = BATTLE_STATE_INIT_GRAPHICS;
            }
            break;

        case BATTLE_STATE_INIT_GRAPHICS: {
            fn_803D9858(0, 0);

            BattleSystem *battleSys = (BattleSystem *)ApplicationManager_Data(appMan);
            lbl_806405C0 = battleSys;

            battleSys->msgLoader = MessageLoader_Init(1, 0x1B, 0, HEAP_ID_BATTLE);
            battleSys->attackMsgLoader = MessageLoader_Init(1, 0x1B, 1, HEAP_ID_BATTLE);
            battleSys->strFormatter = StringTemplate_Default(HEAP_ID_BATTLE);
            battleSys->msgBuffer = Strbuf_Init(0x140, HEAP_ID_BATTLE);

            *state = BATTLE_STATE_MAIN;
            break;
        }

        case BATTLE_STATE_MAIN:
            if (BattleMain_ExecuteBattlerCommands(appMan) == TRUE) {
                *state = BATTLE_STATE_HANDLE_BATTLE_RESULT;
            }
            break;

        case BATTLE_STATE_HANDLE_BATTLE_RESULT: *state = BATTLE_STATE_LINK_BATTLE_END; break;

        case BATTLE_STATE_LINK_BATTLE_END:
            fn_803D9854(2);
            fn_803D986C(62);
            *state = BATTLE_STATE_LINK_BATTLE_FINISH;
            break;

        case BATTLE_STATE_LINK_BATTLE_FINISH:
            if (fn_803D9864(62)) {
                *state = BATTLE_STATE_FINISH;
            }
            break;

        case BATTLE_STATE_CHECK_EVOLUTION:    *state = BATTLE_STATE_FINISH; break;

        case BATTLE_STATE_WAIT_FOR_EVOLUTION: break;

        case BATTLE_STATE_FINISH:             return TRUE;
    }

    return FALSE;
}

// TODO probably BattleMain_CopyBattleSysToDTOAndFree (pret); the battle results are mostly not copied back in this
// game.
void fn_803AC5F0(void) {
    ApplicationManager *appMan = fn_803D9E48();
    BattleSystem *battleSys = (BattleSystem *)ApplicationManager_Data(appMan);
    FieldBattleDTO *dto = (FieldBattleDTO *)ApplicationManager_Args(appMan);
    int battlerId;

    if ((battleSys->battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_AI_PARTNER) {
        // Only the first three Pokemon of the player's party go back.
        for (battlerId = 0; battlerId < 3; battlerId++) {
            Pokemon *src = Party_GetPokemonBySlotIndex(battleSys->parties[BATTLER_US], battlerId);
            Pokemon *dst = Party_GetPokemonBySlotIndex(dto->parties[BATTLER_US], battlerId);

            Pokemon_Copy(src, dst);
        }

        for (battlerId = 0; battlerId < MAX_BATTLERS; battlerId++) {
            fn_8016E0A0(battleSys->parties[battlerId]);
            fn_8016E0A0(battleSys->trainerInfo[battlerId]);
        }
    } else {
        for (battlerId = 0; battlerId < MAX_BATTLERS; battlerId++) {
            Party_Copy(battleSys->parties[battlerId], dto->parties[battlerId]);
            fn_8016E0A0(battleSys->parties[battlerId]);
            fn_8016E0A0(battleSys->trainerInfo[battlerId]);
        }
    }

    dto->resultMask = battleSys->resultMask;
    dto->leveledUpMonsMask = BattleContext_Get(battleSys, battleSys->battleCtx, BATTLECTX_LEVEL_UP_MONS, 0);

    fn_8016E0A0(battleSys->msgBuffer);
    MessageLoader_Free(battleSys->msgLoader);
    MessageLoader_Free(battleSys->attackMsgLoader);
    StringTemplate_Free(battleSys->strFormatter);
    BattleContext_Free(battleSys->battleCtx);

    for (battlerId = 0; battlerId < battleSys->maxBattlers; battlerId++) {
        BattlerData_Delete(battleSys, battleSys->battlers[battlerId], battleSys->renderMode);
    }

    fn_8016E0A0(battleSys);
    fn_803D9854(0);

    if (!fn_803D9870()) {
        fn_803D9854(1);
    }
}

// TODO Counts the battlers up to the first one of a single controller in a double battle
int fn_803AC78C(void) {
    BattleSystem *battleSys = lbl_806405C0;
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    int count = 0;

    for (u8 i = 0; i < maxBattlers; i++) {
        if ((battleType & BATTLE_TYPE_2vs2) == FALSE && (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) &&
            i > 1) {
            break;
        }

        count++;
    }

    return count;
}
}
