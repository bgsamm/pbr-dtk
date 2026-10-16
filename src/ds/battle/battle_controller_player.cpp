#include "ds/battle/battle_controller_player.hpp"

#include ".unsorted/8016A25C.hpp"
#include ".unsorted/8016E2B8.hpp"
#include ".unsorted/8038F424.hpp"
#include "ds/DSbridge.hpp"
#include "ds/battle/battle_common.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_display.hpp"
#include "ds/battle/battle_io_command.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_system.hpp"
#include "ds/constants/items.hpp"
#include "ds/constants/types.hpp"
#include "ds/move_table.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"

#include <string.h>

// TODO Defined in 8017E954.cpp with a single argument; the call here also sets a second one.
extern "C" {
void fn_8017EC1C(BattleSystem *battleSys, u32 *battlerActions);
}

static BOOL BattleControllerPlayer_HasNoTarget(BattleSystem *battleSys, BattleContext *battleCtx);
static int BattleControllerPlayer_CheckMoveHitAccuracy(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move);
static int BattleControllerPlayer_CheckMoveHitOverrides(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move);
static BOOL BattleControllerPlayer_CheckBattleOver(BattleSystem *battleSys, BattleContext *battleCtx);
static BOOL BattleControllerPlayer_AnyExpPayout(BattleContext *battleCtx, int nextCmd, int nextCmdNoExp);
static BOOL
BattleControllerPlayer_AnyFainted(BattleContext *battleCtx, int nextCmd, int nextCmdNoFainted, BOOL onlyFaint);
static void BattleControllerPlayer_InitBattleMons(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_StartEncounter(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_TrainerMessage(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_ShowBattleMon(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_InitCommandSelection(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CommandSelectionInput(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CalcTurnOrder(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckPreMoveActions(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_BranchActions(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckFieldConditions(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckMonConditions(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckSideConditions(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_TurnEnd(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_FightCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_ItemCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_SwitchCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_FleeCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_SafariBallCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_SafariBaitCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_SafariRockCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_SafariFleeCommand(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_ExecScript(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_BeforeMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_TryMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_PrimaryEffect(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckMoveFailure(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_UseMove(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_UpdateHP(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_AfterMoveMessage(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LeftoverState29(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LeftoverState32(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LoopWhileFainted(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_FaintAfterSelfdestruct(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_AfterMoveEffects(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_TriggerAfterHitEffects(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LeftoverState37(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LoopMultiHit(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_LoopSpreadMoves(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_UpdateMoveBuffers(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_UpdateFlagsWhenHit(BattleSystem *battleSys, BattleContext *battleCtx);
static BOOL BattleControllerPlayer_CriticalMessage(BattleSystem *battleSys, BattleContext *battleCtx);
static BOOL BattleControllerPlayer_FollowupMessage(BattleSystem *battleSys, BattleContext *battleCtx);
static BOOL BattleControllerPlayer_RageBuilding(BattleSystem *battleSys, BattleContext *battleCtx);
static BOOL BattleControllerPlayer_CheckExtraFlinch(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_MoveEnd(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_CheckAnyFainted(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_HandleResult(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_EndFight(BattleSystem *battleSys, BattleContext *battleCtx);
static void BattleControllerPlayer_EndWait(BattleSystem *battleSys, BattleContext *battleCtx);

static void (*const sBattleControlCommands[])(BattleSystem *battleSys, BattleContext *battleCtx) = {
    BattleControllerPlayer_InitBattleMons,
    BattleControllerPlayer_StartEncounter,
    BattleControllerPlayer_TrainerMessage,
    BattleControllerPlayer_ShowBattleMon,
    BattleControllerPlayer_InitCommandSelection,
    BattleControllerPlayer_CommandSelectionInput,
    BattleControllerPlayer_CalcTurnOrder,
    BattleControllerPlayer_CheckPreMoveActions,
    BattleControllerPlayer_BranchActions,
    BattleControllerPlayer_CheckFieldConditions,
    BattleControllerPlayer_CheckMonConditions,
    BattleControllerPlayer_CheckSideConditions,
    BattleControllerPlayer_TurnEnd,
    BattleControllerPlayer_FightCommand,
    BattleControllerPlayer_ItemCommand,
    BattleControllerPlayer_SwitchCommand,
    BattleControllerPlayer_FleeCommand,
    BattleControllerPlayer_SafariBallCommand,
    BattleControllerPlayer_SafariBaitCommand,
    BattleControllerPlayer_SafariRockCommand,
    BattleControllerPlayer_SafariFleeCommand,
    BattleControllerPlayer_ExecScript,
    BattleControllerPlayer_BeforeMove,
    BattleControllerPlayer_TryMove,
    BattleControllerPlayer_PrimaryEffect,
    BattleControllerPlayer_CheckMoveFailure,
    BattleControllerPlayer_UseMove,
    BattleControllerPlayer_UpdateHP,
    BattleControllerPlayer_AfterMoveMessage,
    BattleControllerPlayer_LeftoverState29,
    BattleControllerPlayer_AfterMoveEffects,
    BattleControllerPlayer_LoopMultiHit,
    BattleControllerPlayer_LeftoverState32,
    BattleControllerPlayer_LoopWhileFainted,
    BattleControllerPlayer_LoopSpreadMoves,
    BattleControllerPlayer_FaintAfterSelfdestruct,
    BattleControllerPlayer_TriggerAfterHitEffects,
    BattleControllerPlayer_LeftoverState37,
    BattleControllerPlayer_UpdateMoveBuffers,
    BattleControllerPlayer_MoveEnd,
    BattleControllerPlayer_CheckAnyFainted,
    BattleControllerPlayer_HandleResult,
    BattleControllerPlayer_EndFight,
    BattleControllerPlayer_EndWait,
};

BattleContext *BattleContext_New(BattleSystem *battleSys) {
    BattleContext *battleCtx = (BattleContext *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleContext));

    memset(battleCtx, 0, sizeof(BattleContext));

    BattleContext_Init(battleCtx);
    BattleContext_InitCounters(battleSys, battleCtx);

    for (u8 i = 0; i < MAX_BATTLERS; i++) {
        for (u8 j = 0; j < 4; j++) {
            battleCtx->unk314C[i][j] = 0xFF;
        }
    }

    for (u8 i = 0; i < MAX_BATTLERS; i++) {
        for (u8 j = 0; j < MAX_PARTY_SIZE; j++) {
            battleCtx->unk315C[i][j]._00 = -1;
            battleCtx->unk315C[i][j]._02 = 0;
            battleCtx->unk315C[i][j]._03 = 0;

            for (u8 k = 0; k < 4; k++) {
                battleCtx->unk315C[i][j]._04[k] = 0;
            }

            for (u8 k = 0; k < 28; k++) {
                battleCtx->unk315C[i][j]._0C[k] = 0;
            }

            battleCtx->unk315C[i][j]._44 = 0;
        }
    }

    MoveTable_Load(battleCtx->aiContext.moveTable);
    battleCtx->aiContext.itemTable = ItemTable_Load(HEAP_ID_BATTLE);

    return battleCtx;
}

BOOL BattleContext_Main(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->battleEndFlag == FALSE && fn_803ADCD8(battleSys) &&
        (fn_803ADCD8(battleSys) & BATTLE_RESULT_TRY_FLEE_WAIT) == FALSE) {
        battleCtx->command = BATTLE_CONTROL_RESULT;
    }

    sBattleControlCommands[battleCtx->command](battleSys, battleCtx);

    if (battleCtx->command == BATTLE_CONTROL_END_WAIT) {
        return TRUE;
    }

    return FALSE;
}

void BattleContext_Free(BattleContext *battleCtx) {
    fn_8016E0A0(battleCtx->aiContext.itemTable);
    fn_8016E0A0(battleCtx);
}

void BattleControllerPlayer_CheckMoveHit(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move) {
    BattleControllerPlayer_CheckMoveHitAccuracy(battleSys, battleCtx, attacker, defender, move);
    BattleControllerPlayer_CheckMoveHitOverrides(battleSys, battleCtx, attacker, defender, move);
}

static void BattleControllerPlayer_InitBattleMons(BattleSystem *battleSys, BattleContext *battleCtx) {
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    for (int i = 0; i < maxBattlers; i++) {
        BattleSystem_InitBattleMon(battleSys, battleCtx, i, battleCtx->selectedPartySlot[i]);
    }

    battleCtx->hpTemp = battleCtx->battleMons[BATTLER_THEM].curHP;
    battleCtx->command = BATTLE_CONTROL_START_ENCOUNTER;
}

static void BattleControllerPlayer_StartEncounter(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_START_ENCOUNTER);
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_TRAINER_MESSAGE;
}

static void BattleControllerPlayer_TrainerMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (BattleSystem_CheckTrainerMessage(battleSys, battleCtx)) {
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_TRAINER_MESSAGE);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_SHOW_BATTLE_MON;
    } else {
        battleCtx->command = BATTLE_CONTROL_SHOW_BATTLE_MON;
    }

    BattleSystem_SortMonSpeedOrder(battleSys, battleCtx);
}

static void BattleControllerPlayer_ShowBattleMon(BattleSystem *battleSys, BattleContext *battleCtx) {
    int nextSeq = BattleSystem_TriggerEffectOnSwitch(battleSys, battleCtx);

    if (nextSeq) {
        LOAD_SUBSEQ(nextSeq);
        battleCtx->commandNext = battleCtx->command;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    } else {
        BattleSystem_SortMonSpeedOrder(battleSys, battleCtx);
        battleCtx->command = BATTLE_CONTROL_INIT_COMMAND_SELECTION;
        fn_8016E2E4(8);
    }
}

static void BattleControllerPlayer_InitCommandSelection(BattleSystem *battleSys, BattleContext *battleCtx) {
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    for (int i = 0; i < maxBattlers; i++) {
        battleCtx->curCommandState[i] = 0;
        battleCtx->battleMons[i].moveEffectsTemp = battleCtx->battleMons[i].moveEffectsMask;
    }

    fn_8017CED8((u8 *)battleSys);
    fn_8016E2E4(15);
    BattleSystem_SetCommandSelectionFlags(battleSys, 0);

    battleCtx->command = BATTLE_CONTROL_COMMAND_SELECTION_INPUT;
}

// Unlike in Platinum, there is no state waiting for the AI.
enum CommandSelectionState {
    COMMAND_SELECTION_INIT = 0,
    COMMAND_SELECTION_SELECT,
    COMMAND_SELECTION_MOVE_SELECT_INIT,
    COMMAND_SELECTION_MOVE_SELECT,
    COMMAND_SELECTION_TARGET_SELECT_INIT,
    COMMAND_SELECTION_TARGET_SELECT,
    COMMAND_SELECTION_ITEM_SELECT_INIT,
    COMMAND_SELECTION_ITEM_SELECT,
    COMMAND_SELECTION_PARTY_SELECT_INIT,
    COMMAND_SELECTION_PARTY_SELECT,
    COMMAND_SELECTION_RUN_SELECT_INIT,
    COMMAND_SELECTION_RUN_SELECT,
    COMMAND_SELECTION_WAIT,
    COMMAND_SELECTION_END,
    COMMAND_SELECTION_ALERT_MESSAGE_WAIT,
    COMMAND_SELECTION_STRUGGLE_MESSAGE,
    COMMAND_SELECTION_CLEAR_TOUCH_SCREEN,
};

// pokeplatinum SingleControllerForSide, written in line in this game.
#define SINGLE_CONTROLLER_FOR_SIDE(battler, side)                                                                      \
    ((battler) == (side) + 2 && battleCtx->curCommandState[side] != COMMAND_SELECTION_END)

static inline BOOL BattleControllerPlayer_MustSelectTarget(BattleSystem *battleSys,
                                                           BattleContext *battleCtx,
                                                           u8 battler,
                                                           u32 battleType,
                                                           int *range,
                                                           int moveSlot,
                                                           u32 *target) {
    if (battleCtx->battleMons[battler].moves[moveSlot] == MOVE_CURSE &&
        Move_IsGhostCurse(battleCtx, battleCtx->battleMons[battler].moves[moveSlot], battler) == FALSE) {
        *range = RANGE_USER;
    } else {
        *range = MOVE_DATA(battleCtx->battleMons[battler].moves[moveSlot]).range;
    }

    if (battleType & BATTLE_TYPE_DOUBLES) {
        if (*range == RANGE_ALLY) {
            if ((battleCtx->battlersSwitchingMask & FlagIndex(BattleSystem_GetPartner(battleSys, battler))) == FALSE) {
                return TRUE;
            }

            return FALSE;
        }

        return TRUE;
    }

    if (*range & RANGE_MY_SIDE) {
        *target = battler;
    } else {
        *target = battler ^ 1;
    }

    return FALSE;
}

// Unlike in Platinum, nothing here is recorded, and the AI and running away are not checked.
static void BattleControllerPlayer_CommandSelectionInput(BattleSystem *battleSys, BattleContext *battleCtx) {
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    int battleType = BattleSystem_GetBattleType(battleSys);
    BattleMessage msg;
    int i;
    int battlersDone = 0;

    for (i = 0; i < maxBattlers; i++) {
        switch (battleCtx->curCommandState[i]) {
            case COMMAND_SELECTION_INIT:
                // No need to start again if the same controller acts for both battlers on a side.
                if ((battleType & BATTLE_TYPE_DOUBLES) && (battleType & BATTLE_TYPE_2vs2) == FALSE &&
                    (SINGLE_CONTROLLER_FOR_SIDE(i, BATTLER_US) || SINGLE_CONTROLLER_FOR_SIDE(i, BATTLER_THEM))) {
                    break;
                }

                if (battleCtx->battlersSwitchingMask & FlagIndex(i)) {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                    battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_MOVE_END;
                    break;
                } else if (Battler_CanPickCommand(battleCtx, i) == FALSE) {
                    battleCtx->turnFlags[i].ppDecremented = TRUE;
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                    battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_FIGHT;
                    break;
                }

                BattleController_EmitSetCommandSelection(battleSys, battleCtx, i, battleCtx->selectedPartySlot[i]);
                battleCtx->curCommandState[i] = COMMAND_SELECTION_SELECT;
                // fall-through

            case COMMAND_SELECTION_SELECT:
                if (BattleContext_IOBufferVal(battleCtx, i)) {
                    battleCtx->battlerActions[i][BATTLE_ACTION_SELECTED_COMMAND] = battleCtx->ioBuffer[i][0];

                    if (battleType & BATTLE_TYPE_PAL_PARK) {
                        switch (BattleContext_IOBufferVal(battleCtx, i)) {
                            case PLAYER_INPUT_PAL_PARK_BALL:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_SAFARI_BALL;
                                break;

                            case PLAYER_INPUT_PAL_PARK_RUN:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_RUN;
                                break;
                        }

                        break;
                    } else if (battleType & BATTLE_TYPE_SAFARI) {
                        switch (BattleContext_IOBufferVal(battleCtx, i)) {
                            case PLAYER_INPUT_SAFARI_BALL:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_SAFARI_BALL;
                                break;

                            case PLAYER_INPUT_SAFARI_BAIT:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_SAFARI_BAIT;
                                break;

                            case PLAYER_INPUT_SAFARI_ROCK:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_SAFARI_ROCK;
                                break;

                            case PLAYER_INPUT_SAFARI_RUN:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_RUN;
                                break;

                            case PLAYER_INPUT_SAFARI_WAIT:
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_SAFARI_WAIT;
                                break;
                        }

                        break;
                    }

                    switch (BattleContext_IOBufferVal(battleCtx, i)) {
                        case PLAYER_INPUT_FIGHT:
                            if (BattleSystem_CheckInvalidMoves(battleSys, battleCtx, i, 0, CHECK_INVALID_ALL) ==
                                STRUGGLING_ALL) {
                                // No move to choose when every move is out of PP
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_STRUGGLE_MESSAGE;
                            } else if (battleCtx->battleMons[i].moveEffectsData.encoredMove) {
                                // No move to choose under Encore
                                battleCtx->moveSlot[i] = battleCtx->battleMons[i].moveEffectsData.encoredMoveSlot;
                                battleCtx->moveSelected[i] = battleCtx->battleMons[i].moveEffectsData.encoredMove;
                                battleCtx->battlerActions[i][BATTLE_ACTION_TEMP_VALUE] = 0;
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_CLEAR_TOUCH_SCREEN;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                            } else {
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_MOVE_SELECT_INIT;
                            }

                            battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_FIGHT;
                            break;

                        case PLAYER_INPUT_ITEM:
                            if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_FRONTIER_LINK) {
                                msg.id = 593;
                                msg.tags = TAG_NONE;
                                BattleController_EmitSetAlertMessage(battleSys, i, msg);

                                battleCtx->curCommandState[i] = COMMAND_SELECTION_ALERT_MESSAGE_WAIT;
                                battleCtx->nextCommandState[i] = COMMAND_SELECTION_INIT;
                            } else {
                                battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_ITEM;
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_ITEM_SELECT_INIT;
                            }
                            break;

                        case PLAYER_INPUT_PARTY:
                            battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_PARTY;
                            battleCtx->curCommandState[i] = COMMAND_SELECTION_PARTY_SELECT_INIT;
                            break;

                        case PLAYER_INPUT_RUN:
                            battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_RUN;
                            battleCtx->curCommandState[i] = COMMAND_SELECTION_RUN_SELECT_INIT;
                            break;

                        case PLAYER_INPUT_CANCEL:
                            if ((battleType & BATTLE_TYPE_UNK_15) || (battleType & BATTLE_TYPE_UNK_16)) {
                                BattleController_EmitStopGaugeAnimation(battleSys, i);
                                battleCtx->curCommandState[i] = COMMAND_SELECTION_INIT;
                                battleCtx->curCommandState[BattleSystem_GetPartner(battleSys, i)] =
                                    COMMAND_SELECTION_INIT;
                            } else if ((battleType & BATTLE_TYPE_DOUBLES) && i == BATTLER_PLAYER_2) {
                                BattleController_EmitStopGaugeAnimation(battleSys, i);
                                battleCtx->curCommandState[BATTLER_PLAYER_1] = COMMAND_SELECTION_INIT;
                                battleCtx->curCommandState[BATTLER_PLAYER_2] = COMMAND_SELECTION_INIT;
                            }

                            break;
                    }
                }
                break;

            case COMMAND_SELECTION_MOVE_SELECT_INIT:
                BattleController_EmitShowMoveSelectMenu(battleSys, battleCtx, i);
                battleCtx->curCommandState[i] = COMMAND_SELECTION_MOVE_SELECT;
                // fall-through

            case COMMAND_SELECTION_MOVE_SELECT:
                if (BattleContext_IOBufferVal(battleCtx, i) == PLAYER_INPUT_CANCEL) {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_INIT;
                } else if (BattleContext_IOBufferVal(battleCtx, i)) {
                    if ((battleCtx->ioBuffer[i][0] - 1) == 4) {
                        battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_RUN;
                        battleCtx->curCommandState[i] = COMMAND_SELECTION_RUN_SELECT_INIT;
                        break;
                    } else if (BattleSystem_CanUseMove(battleSys, battleCtx, i, battleCtx->ioBuffer[i][0] - 1, &msg) ==
                               FALSE) {
                        BattleController_EmitSetAlertMessage(battleSys, i, msg);
                        battleCtx->curCommandState[i] = COMMAND_SELECTION_ALERT_MESSAGE_WAIT;
                        battleCtx->nextCommandState[i] = COMMAND_SELECTION_MOVE_SELECT_INIT;
                    } else {
                        battleCtx->battlerActions[i][BATTLE_ACTION_TEMP_VALUE] = battleCtx->ioBuffer[i][0];
                        battleCtx->moveSlot[i] = battleCtx->ioBuffer[i][0] - 1;
                        battleCtx->moveSelected[i] = battleCtx->battleMons[i].moves[battleCtx->moveSlot[i]];
                        battleCtx->curCommandState[i] = COMMAND_SELECTION_TARGET_SELECT_INIT;

                        if (BattlerData_GetBootState(BattleSystem_GetBattlerData(battleSys, i)) !=
                            BATTLER_BOOT_STATE_AI) {
                            fn_8016E444((u8)i);
                            fn_8016E2E4(0xD);
                        }
                    }
                }
                break;

            case COMMAND_SELECTION_TARGET_SELECT_INIT:
                int target;
                if (BattleControllerPlayer_MustSelectTarget(
                        battleSys,
                        battleCtx,
                        i,
                        battleType,
                        &target,
                        battleCtx->moveSlot[i],
                        &battleCtx->battlerActions[i][BATTLE_ACTION_CHOOSE_TARGET])) {
                    BattleCommand_EmitShowTargetSelectMenu(battleSys, battleCtx, target, i);
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_TARGET_SELECT;
                } else {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                }
                break;

            case COMMAND_SELECTION_TARGET_SELECT:
                if (BattleContext_IOBufferVal(battleCtx, i) == PLAYER_INPUT_CANCEL) {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_MOVE_SELECT_INIT;
                } else if (BattleContext_IOBufferVal(battleCtx, i)) {
                    battleCtx->battlerActions[i][BATTLE_ACTION_CHOOSE_TARGET] = battleCtx->ioBuffer[i][0] - 1;
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                }
                break;

            case COMMAND_SELECTION_ITEM_SELECT_INIT:
                BattleController_EmitShowBagMenu(battleSys, battleCtx, i);
                battleCtx->curCommandState[i] = COMMAND_SELECTION_ITEM_SELECT;
                // fall-through

            case COMMAND_SELECTION_ITEM_SELECT:
                if (BattleContext_IOBufferVal(battleCtx, i) == PLAYER_INPUT_CANCEL) {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_INIT;
                } else if (BattleContext_IOBufferVal(battleCtx, i)) {
                    u32 *data = (u32 *)&battleCtx->ioBuffer[i][0];
                    battleCtx->battlerActions[i][BATTLE_ACTION_TEMP_VALUE] = *data;
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                }
                break;

            case COMMAND_SELECTION_PARTY_SELECT_INIT:
                int doublesSelection = MAX_PARTY_SIZE;
                BOOL canSwitch = Battler_IsTrapped(battleSys, battleCtx, i);

                // Check the partner's choice in a double battle
                if ((BattleSystem_GetBattlerType(battleSys, i) == BATTLER_TYPE_PLAYER_SIDE_SLOT_2 ||
                     BattleSystem_GetBattlerType(battleSys, i) == BATTLER_TYPE_ENEMY_SIDE_SLOT_2) &&
                    ((battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_TRAINER_DOUBLES ||
                     (battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_LINK_DOUBLES ||
                     ((battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_TAG_DOUBLES &&
                      BattleSystem_GetBattlerType(battleSys, i) == BATTLER_TYPE_PLAYER_SIDE_SLOT_2))) {
                    int partner = BattleSystem_GetPartner(battleSys, i);

                    if (battleCtx->battlerActions[partner][BATTLE_ACTION_PICK_COMMAND] == BATTLE_CONTROL_PARTY) {
                        doublesSelection = battleCtx->battlerActions[partner][BATTLE_ACTION_TEMP_VALUE];
                    }
                }

                BattleController_EmitShowPartyMenu(battleSys, battleCtx, i, 0, canSwitch, doublesSelection);
                battleCtx->curCommandState[i] = COMMAND_SELECTION_PARTY_SELECT;
                // fall-through

            case COMMAND_SELECTION_PARTY_SELECT:
                if (BattleContext_IOBufferVal(battleCtx, i) == PLAYER_INPUT_CANCEL) {
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_INIT;
                } else if (BattleContext_IOBufferVal(battleCtx, i)) {
                    battleCtx->battlerActions[i][BATTLE_ACTION_TEMP_VALUE] = battleCtx->ioBuffer[i][0] - 1;
                    battleCtx->switchedPartySlot[i] = battleCtx->ioBuffer[i][0] - 1;
                    battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;
                }
                break;

            case COMMAND_SELECTION_RUN_SELECT_INIT: battleCtx->curCommandState[i] = COMMAND_SELECTION_RUN_SELECT; break;

            case COMMAND_SELECTION_RUN_SELECT:
                battleCtx->curCommandState[i] = COMMAND_SELECTION_WAIT;

                if ((battleType & BATTLE_TYPE_DOUBLES) && (battleType & BATTLE_TYPE_2vs2) == FALSE &&
                    (battleCtx->curCommandState[i] == COMMAND_SELECTION_WAIT)) {
                    battleCtx->curCommandState[BattleSystem_GetPartner(battleSys, i)] = COMMAND_SELECTION_WAIT;
                }
                break;

            case COMMAND_SELECTION_WAIT:
                BattleController_EmitStopGaugeAnimation(battleSys, i);

                if ((battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_LINK_DOUBLES) {
                    if (battleCtx->curCommandState[BattleSystem_GetPartner(battleSys, i)] == COMMAND_SELECTION_END) {
                        BattleController_EmitPrintLinkWaitMessage(battleSys, i);
                    }
                } else {
                    BattleController_EmitPrintLinkWaitMessage(battleSys, i);
                }

                battleCtx->curCommandState[i] = COMMAND_SELECTION_END;

                if (BattlerData_GetBootState(BattleSystem_GetBattlerData(battleSys, i)) != BATTLER_BOOT_STATE_AI) {
                    fn_8016E458((u8)i);
                    fn_8016E2E4(0xE);
                }
                // fall-through

            case COMMAND_SELECTION_END: battlersDone++; break;

            case COMMAND_SELECTION_ALERT_MESSAGE_WAIT:
                if (BattleContext_IOBufferVal(battleCtx, i)) {
                    BattleIO_ClearBuffer(battleCtx, i);
                    battleCtx->curCommandState[i] = battleCtx->nextCommandState[i];
                }
                break;

            case COMMAND_SELECTION_STRUGGLE_MESSAGE:
                msg.tags = TAG_NICKNAME;
                msg.id = 608;
                msg.params[0] = BattleSystem_NicknameTag(battleCtx, i);
                BattleController_EmitSetAlertMessage(battleSys, i, msg);

                battleCtx->turnFlags[i].struggling = TRUE;
                battleCtx->curCommandState[i] = COMMAND_SELECTION_ALERT_MESSAGE_WAIT;
                battleCtx->nextCommandState[i] = COMMAND_SELECTION_WAIT;
                break;

            case COMMAND_SELECTION_CLEAR_TOUCH_SCREEN:
                BattleController_EmitClearTouchScreen(battleSys, i);
                battleCtx->curCommandState[i] = battleCtx->nextCommandState[i];
                break;
        }
    }

    if (battlersDone == maxBattlers) {
        battleCtx->command = BATTLE_CONTROL_CALC_TURN_ORDER;
        for (i = 0; i < maxBattlers; i++) {
            if (battleCtx->battlerActions[i][BATTLE_ACTION_PICK_COMMAND] == BATTLE_CONTROL_PARTY) {
                BattleSystem_SwitchSlots(battleSys, battleCtx, i, battleCtx->switchedPartySlot[i]);
            }
        }

        fn_8016E2E4(7);
        lbl_8048CDE8.args[0] = battleCtx->totalTurns;
        fn_8016FA4C(1, &lbl_8048CDE8);
    }
}

static void BattleControllerPlayer_CalcTurnOrder(BattleSystem *battleSys, BattleContext *battleCtx) {
    int battler, i, j;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int order = 0;

    if (battleType & (BATTLE_TYPE_SAFARI | BATTLE_TYPE_PAL_PARK)) {
        for (battler = 0; battler < maxBattlers; battler++) {
            battleCtx->battlerActionOrder[battler] = battler;
        }
    } else {
        // Any battler that runs or forfeits goes first.
        for (battler = 0; battler < maxBattlers; battler++) {
            if (battleCtx->battlerActions[battler][BATTLE_ACTION_SELECTED_COMMAND] == PLAYER_INPUT_RUN) {
                order = 5;
                break;
            }
        }

        if (order == 5) {
            battleCtx->battlerActionOrder[0] = battler;
            order = 1;

            for (i = 0; i < maxBattlers; i++) {
                if (i != battler) {
                    battleCtx->battlerActionOrder[order] = i;
                    order++;
                }
            }
        } else {
            for (battler = 0; battler < maxBattlers; battler++) {
                if (battleCtx->battlerActions[battler][BATTLE_ACTION_SELECTED_COMMAND] == PLAYER_INPUT_ITEM ||
                    battleCtx->battlerActions[battler][BATTLE_ACTION_SELECTED_COMMAND] == PLAYER_INPUT_PARTY) {
                    battleCtx->battlerActionOrder[order] = battler;
                    order++;
                }
            }

            for (battler = 0; battler < maxBattlers; battler++) {
                if (battleCtx->battlerActions[battler][BATTLE_ACTION_SELECTED_COMMAND] != PLAYER_INPUT_ITEM &&
                    battleCtx->battlerActions[battler][BATTLE_ACTION_SELECTED_COMMAND] != PLAYER_INPUT_PARTY) {
                    battleCtx->battlerActionOrder[order] = battler;
                    order++;
                }
            }

            for (i = 0; i < maxBattlers - 1; i++) {
                for (j = i + 1; j < maxBattlers; j++) {
                    int battler1 = battleCtx->battlerActionOrder[i];
                    int battler2 = battleCtx->battlerActionOrder[j];

                    if (battleCtx->battlerActions[battler1][BATTLE_ACTION_SELECTED_COMMAND] ==
                        battleCtx->battlerActions[battler2][BATTLE_ACTION_SELECTED_COMMAND]) {
                        BOOL skipPriority =
                            battleCtx->battlerActions[battler1][BATTLE_ACTION_SELECTED_COMMAND] != PLAYER_INPUT_FIGHT;

                        if (BattleSystem_CompareBattlerSpeed(battleSys, battleCtx, battler1, battler2, skipPriority)) {
                            battleCtx->battlerActionOrder[i] = battler2;
                            battleCtx->battlerActionOrder[j] = battler1;
                        }
                    }
                }
            }
        }
    }

    battleCtx->command = BATTLE_CONTROL_CHECK_PRE_MOVE_ACTIONS;
}

enum PreMoveActionState {
    PRE_MOVE_ACTION_STATE_TIGHTEN_FOCUS = 0,
    PRE_MOVE_ACTION_STATE_CHECK_RAGE_FLAG,
    PRE_MOVE_ACTION_STATE_SPEED_RNG,
    PRE_MOVE_ACTION_END,
};

enum ControllerLoopState {
    STATE_PROCESSING = 0,
    STATE_BREAK_OUT,
    STATE_DONE,
};

static void BattleControllerPlayer_CheckPreMoveActions(BattleSystem *battleSys, BattleContext *battleCtx) {
    int state = STATE_PROCESSING;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    int battler;

    fn_8017EC1C(battleSys, &battleCtx->battlerActions[0][0]);

    do {
        switch (battleCtx->turnStartCheckState) {
            case PRE_MOVE_ACTION_STATE_TIGHTEN_FOCUS:
                while (battleCtx->turnStartCheckTemp < maxBattlers) {
                    battler = battleCtx->battlerActionOrder[battleCtx->turnStartCheckTemp];

                    if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
                        battleCtx->turnStartCheckTemp++;
                        continue;
                    }

                    battleCtx->turnStartCheckTemp++;

                    if ((battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) == FALSE &&
                        Battler_SelectedMove(battleCtx, battler) == MOVE_FOCUS_PUNCH &&
                        Battler_CheckTruant(battleCtx, battler) == FALSE &&
                        battleCtx->turnFlags[battler].struggling == FALSE) {
                        BattleController_EmitClearMessageBox(battleSys);
                        battleCtx->msgBattlerTemp = battler;
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_TIGHTEN_FOCUS);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                        return;
                    }
                }

                battleCtx->turnStartCheckTemp = 0;
                battleCtx->turnStartCheckState++;
                break;
            case PRE_MOVE_ACTION_STATE_CHECK_RAGE_FLAG:
                for (battler = 0; battler < maxBattlers; battler++) {
                    if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_RAGE &&
                        Battler_SelectedMove(battleCtx, battler) != MOVE_RAGE) {
                        // As in pokeplatinum, this clears every volatile status except Rage.
                        battleCtx->battleMons[battler].statusVolatile &= VOLATILE_CONDITION_RAGE;
                    }
                }

                battleCtx->turnStartCheckState++;
                break;
            case PRE_MOVE_ACTION_STATE_SPEED_RNG:
                for (battler = 0; battler < MAX_BATTLERS; battler++) {
                    battleCtx->speedRand[battler] = LCRNG_Next();
                }

                battleCtx->turnStartCheckState++;
                break;
            case PRE_MOVE_ACTION_END:
                battleCtx->turnStartCheckState = 0;
                state = STATE_DONE;
                break;
        }
    } while (state == STATE_PROCESSING);

    if (state == STATE_DONE) {
        battleCtx->command = BATTLE_CONTROL_BRANCH_ACTIONS;
    }
}

static void BattleControllerPlayer_BranchActions(BattleSystem *battleSys, BattleContext *battleCtx) {
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    BattleSystem_SortMonSpeedOrder(battleSys, battleCtx);

    if (battleCtx->turnOrderCounter == maxBattlers) {
        battleCtx->turnOrderCounter = 0;
        battleCtx->command = BATTLE_CONTROL_CHECK_FIELD_CONDITIONS;
        fn_8016FA4C(0x15, NULL);
        fn_8016E2E4(10);
    } else {
        battleCtx->command = battleCtx->battlerActions[battleCtx->battlerActionOrder[battleCtx->turnOrderCounter]][0];
        lbl_8048CDE8.args[0] = battleCtx->battlerActionOrder[battleCtx->turnOrderCounter];
        fn_8016FA4C(3, &lbl_8048CDE8);
    }
}

// pokeplatinum PrepareSubroutineSequence, written in line in this game.
#define PREPARE_SUBROUTINE_SEQUENCE(script)                                                                            \
    LOAD_SUBSEQ(script);                                                                                               \
    battleCtx->commandNext = battleCtx->command;                                                                       \
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT

enum FieldConditionCheckState {
    FIELD_COND_CHECK_START = 0,

    FIELD_COND_CHECK_STATE_REFLECT = FIELD_COND_CHECK_START,
    FIELD_COND_CHECK_STATE_LIGHT_SCREEN,
    FIELD_COND_CHECK_STATE_MIST,
    FIELD_COND_CHECK_STATE_SAFEGUARD,
    FIELD_COND_CHECK_STATE_TAILWIND,
    FIELD_COND_CHECK_STATE_LUCKY_CHANT,
    FIELD_COND_CHECK_STATE_WISH,
    FIELD_COND_CHECK_STATE_RAINING,
    FIELD_COND_CHECK_STATE_SANDSTORM,
    FIELD_COND_CHECK_STATE_SUNNY,
    FIELD_COND_CHECK_STATE_HAILING,
    FIELD_COND_CHECK_STATE_DEEP_FOG,
    FIELD_COND_CHECK_STATE_GRAVITY,

    FIELD_COND_CHECK_END,
};

// pokeplatinum StepFieldConditionCheck, written in line in this game.
#define STEP_FIELD_CONDITION_CHECK(state)                                                                              \
    if (state == STATE_PROCESSING) {                                                                                   \
        battleCtx->fieldConditionCheckState++;                                                                         \
        battleCtx->fieldConditionCheckTemp = 0;                                                                        \
    }

static void BattleControllerPlayer_CheckFieldConditions(BattleSystem *battleSys, BattleContext *battleCtx) {
    int state = STATE_PROCESSING;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    int side;

    do {
        if (BattleControllerPlayer_AnyFainted(battleCtx, battleCtx->command, battleCtx->command, 1) == TRUE) {
            return;
        }

        if (BattleControllerPlayer_AnyExpPayout(battleCtx, battleCtx->command, battleCtx->command) == TRUE) {
            return;
        }

        if (BattleControllerPlayer_CheckBattleOver(battleSys, battleCtx) == TRUE) {
            return;
        }

        switch (battleCtx->fieldConditionCheckState) {
            case FIELD_COND_CHECK_STATE_REFLECT:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_REFLECT &&
                        --battleCtx->sideConditions[side].reflectTurns == 0) {
                        battleCtx->sideConditionsMask[side] &= ~SIDE_CONDITION_REFLECT;
                        battleCtx->msgMoveTemp = MOVE_REFLECT;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_MOVE_EFFECT_END);
                        battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = side;
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_LIGHT_SCREEN:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_LIGHT_SCREEN &&
                        --battleCtx->sideConditions[side].lightScreenTurns == 0) {
                        battleCtx->sideConditionsMask[side] &= ~SIDE_CONDITION_LIGHT_SCREEN;
                        battleCtx->msgMoveTemp = MOVE_LIGHT_SCREEN;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_MOVE_EFFECT_END);
                        battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = side;
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_MIST:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_MIST &&
                        --battleCtx->sideConditions[side].mistTurns == 0) {
                        battleCtx->sideConditionsMask[side] &= ~SIDE_CONDITION_MIST;
                        battleCtx->msgMoveTemp = MOVE_MIST;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_MOVE_EFFECT_END);
                        battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = side;
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_SAFEGUARD:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_SAFEGUARD &&
                        --battleCtx->sideConditions[side].safeguardTurns == 0) {
                        battleCtx->sideConditionsMask[side] &= ~SIDE_CONDITION_SAFEGUARD;
                        battleCtx->msgBattlerTemp = battleCtx->sideConditions[side].safeguardUser;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_SAFEGUARD_END);
                        battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = side;
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_TAILWIND:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_TAILWIND) {
                        battleCtx->sideConditionsMask[side] -= SIDE_CONDITION_TAILWIND_0;

                        if ((battleCtx->sideConditionsMask[side] & SIDE_CONDITION_TAILWIND) == FALSE) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_TAILWIND_END);
                            battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                            state = STATE_BREAK_OUT;
                            lbl_8048CE28._0C = side;
                        }
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_LUCKY_CHANT:
                while (battleCtx->fieldConditionCheckTemp < NUM_BATTLE_SIDES) {
                    side = battleCtx->fieldConditionCheckTemp;

                    if (battleCtx->sideConditionsMask[side] & SIDE_CONDITION_LUCKY_CHANT) {
                        battleCtx->sideConditionsMask[side] -= SIDE_CONDITION_LUCKY_CHANT_0;

                        if ((battleCtx->sideConditionsMask[side] & SIDE_CONDITION_LUCKY_CHANT) == FALSE) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_LUCKY_CHANT_END);
                            battleCtx->msgBattlerTemp = BattleSystem_SideToBattler(battleSys, battleCtx, side);
                            state = STATE_BREAK_OUT;
                            lbl_8048CE28._0C = side;
                        }
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_WISH:
                while (battleCtx->fieldConditionCheckTemp < maxBattlers) {
                    side = battleCtx->monSpeedOrder[battleCtx->fieldConditionCheckTemp]; // a battler here

                    if (battleCtx->fieldConditions.wishTurns[side] &&
                        --battleCtx->fieldConditions.wishTurns[side] == 0 && battleCtx->battleMons[side].curHP) {
                        battleCtx->msgBattlerTemp = side;

                        battleCtx->msgBuffer.tags = TAG_NICKNAME;
                        battleCtx->msgBuffer.id = 533;
                        battleCtx->msgBuffer.params[0] = side | (battleCtx->fieldConditions.wishTarget[side] << 8);

                        battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[side].maxHP, 2);

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WISH_HEAL);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = side;
                    }

                    battleCtx->fieldConditionCheckTemp++;
                    if (state) {
                        break;
                    }
                }

                STEP_FIELD_CONDITION_CHECK(state);
                break;

            case FIELD_COND_CHECK_STATE_RAINING:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_RAINING) {
                    if (battleCtx->fieldConditionsMask & FIELD_CONDITION_RAINING_PERM) {
                        battleCtx->msgBuffer.id = 801;
                        battleCtx->msgBuffer.tags = TAG_NONE;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                    } else {
                        if (--battleCtx->fieldConditions.weatherTurns == 0) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_RAINING_END);
                        } else {
                            battleCtx->msgBuffer.id = 801;
                            battleCtx->msgBuffer.tags = TAG_NONE;

                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                        }
                    }

                    battleCtx->scriptTemp = BATTLE_ANIMATION_WEATHER_RAIN;
                    state = STATE_BREAK_OUT;
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_STATE_SANDSTORM:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_SANDSTORM) {
                    if (battleCtx->fieldConditionsMask & FIELD_CONDITION_SANDSTORM_PERM) {
                        battleCtx->msgBuffer.id = 805;
                        battleCtx->msgBuffer.tags = TAG_NONE;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                    } else {
                        if (--battleCtx->fieldConditions.weatherTurns == 0) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_SANDSTORM_END);
                        } else {
                            battleCtx->msgBuffer.id = 805;
                            battleCtx->msgBuffer.tags = TAG_NONE;

                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                        }
                    }

                    battleCtx->scriptTemp = BATTLE_ANIMATION_WEATHER_SAND;
                    state = STATE_BREAK_OUT;
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_STATE_SUNNY:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_SUNNY) {
                    if (battleCtx->fieldConditionsMask & FIELD_CONDITION_SUNNY_PERM) {
                        battleCtx->msgBuffer.id = 808;
                        battleCtx->msgBuffer.tags = TAG_NONE;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                    } else {
                        if (--battleCtx->fieldConditions.weatherTurns == 0) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_SUNNY_END);
                        } else {
                            battleCtx->msgBuffer.id = 808;
                            battleCtx->msgBuffer.tags = TAG_NONE;

                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                        }
                    }

                    battleCtx->scriptTemp = BATTLE_ANIMATION_WEATHER_SUN;
                    state = STATE_BREAK_OUT;
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_STATE_HAILING:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_HAILING) {
                    if (battleCtx->fieldConditionsMask & FIELD_CONDITION_HAILING_PERM) {
                        battleCtx->msgBuffer.id = 811;
                        battleCtx->msgBuffer.tags = TAG_NONE;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                    } else {
                        if (--battleCtx->fieldConditions.weatherTurns == 0) {
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_HAILING_END);
                        } else {
                            battleCtx->msgBuffer.id = 811;
                            battleCtx->msgBuffer.tags = TAG_NONE;

                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);
                        }
                    }

                    battleCtx->scriptTemp = BATTLE_ANIMATION_WEATHER_HAIL;
                    state = STATE_BREAK_OUT;
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_STATE_DEEP_FOG:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_DEEP_FOG) {
                    battleCtx->msgBuffer.id = 813;
                    battleCtx->msgBuffer.tags = TAG_NONE;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WEATHER_CONTINUES);

                    battleCtx->scriptTemp = BATTLE_ANIMATION_WEATHER_FOG;
                    state = STATE_BREAK_OUT;
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_STATE_GRAVITY:
                if (battleCtx->fieldConditionsMask & FIELD_CONDITION_GRAVITY) {
                    battleCtx->fieldConditionsMask -= FIELD_CONDITION_GRAVITY_0;

                    if ((battleCtx->fieldConditionsMask & FIELD_CONDITION_GRAVITY) == 0) {
                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_GRAVITY_END);
                        state = STATE_BREAK_OUT;
                    }
                }

                battleCtx->fieldConditionCheckState++;
                break;

            case FIELD_COND_CHECK_END: state = STATE_DONE; break;
        }
    } while (state == STATE_PROCESSING);

    if (state == STATE_BREAK_OUT) {
        BattleController_EmitClearMessageBox(battleSys);
    }

    if (state == STATE_DONE) {
        battleCtx->fieldConditionCheckState = FIELD_COND_CHECK_START;
        battleCtx->command = BATTLE_CONTROL_CHECK_MON_CONDITIONS;
    }
}

enum MonCondCheckState {
    MON_COND_CHECK_START = 0,

    MON_COND_CHECK_STATE_INGRAIN = MON_COND_CHECK_START,
    MON_COND_CHECK_STATE_AQUA_RING,
    MON_COND_CHECK_STATE_ABILITY,
    MON_COND_CHECK_STATE_USE_ITEM,
    MON_COND_CHECK_STATE_LEFTOVERS,
    MON_COND_CHECK_STATE_LEECH_SEED,
    MON_COND_CHECK_STATE_POISON,
    MON_COND_CHECK_STATE_TOXIC,
    MON_COND_CHECK_STATE_BURN,
    MON_COND_CHECK_STATE_NIGHTMARE,
    MON_COND_CHECK_STATE_CURSE,
    MON_COND_CHECK_STATE_BIND,
    MON_COND_CHECK_STATE_BAD_DREAMS,
    MON_COND_CHECK_STATE_UPROAR,
    MON_COND_CHECK_STATE_THRASH,
    MON_COND_CHECK_STATE_DISABLE,
    MON_COND_CHECK_STATE_ENCORE,
    MON_COND_CHECK_STATE_LOCK_ON,
    MON_COND_CHECK_STATE_CHARGE,
    MON_COND_CHECK_STATE_TAUNT,
    MON_COND_CHECK_STATE_MAGNET_RISE,
    MON_COND_CHECK_STATE_HEAL_BLOCK,
    MON_COND_CHECK_STATE_EMBARGO,
    MON_COND_CHECK_STATE_YAWN,
    MON_COND_CHECK_STATE_ITEM_CONDITION,
    MON_COND_CHECK_STATE_ITEM_DETRIMENTAL_EFFECT,

    MON_COND_CHECK_END,
};

// TODO Does not match yet: only the register allocation of four turn counters differs (99.76 %).
static void BattleControllerPlayer_CheckMonConditions(BattleSystem *battleSys, BattleContext *battleCtx) {
    u8 state = STATE_PROCESSING;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    if (BattleControllerPlayer_AnyFainted(battleCtx, battleCtx->command, battleCtx->command, 1) == TRUE ||
        BattleControllerPlayer_AnyExpPayout(battleCtx, battleCtx->command, battleCtx->command) == TRUE ||
        BattleControllerPlayer_CheckBattleOver(battleSys, battleCtx) == TRUE) {
        return;
    }

    int i, battler;
    while (battleCtx->monConditionCheckTemp < maxBattlers) {
        battler = battleCtx->monSpeedOrder[battleCtx->monConditionCheckTemp];

        if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
            battleCtx->monConditionCheckTemp++;
            continue;
        }

        switch (battleCtx->monConditionCheckState) {
            case MON_COND_CHECK_STATE_INGRAIN:
                if ((battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_INGRAIN) &&
                    battleCtx->battleMons[battler].curHP != battleCtx->battleMons[battler].maxHP &&
                    battleCtx->battleMons[battler].curHP) {
                    if (battleCtx->battleMons[battler].moveEffectsData.healBlockTurns) {
                        battleCtx->msgBattlerTemp = battler;
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_CANNOT_HEAL);
                    } else {
                        battleCtx->msgBattlerTemp = battler;
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_INGRAIN_HEAL);
                    }

                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_AQUA_RING:
                if ((battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_AQUA_RING) &&
                    battleCtx->battleMons[battler].curHP != battleCtx->battleMons[battler].maxHP &&
                    battleCtx->battleMons[battler].curHP) {
                    if (battleCtx->battleMons[battler].moveEffectsData.healBlockTurns) {
                        battleCtx->msgBattlerTemp = battler;
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_CANNOT_HEAL);
                    } else {
                        battleCtx->msgBattlerTemp = battler;
                        battleCtx->msgMoveTemp = MOVE_AQUA_RING;
                        battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[battler].maxHP, 16);
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_AQUA_RING_HEAL);
                    }

                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_ABILITY:
                if (BattleSystem_TriggerTurnEndAbility(battleCtx, battler) == TRUE) {
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_USE_ITEM:
                if (BattleSystem_TriggerHeldItem(battleSys, battleCtx, battler) == TRUE) {
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_LEFTOVERS:
                if (BattleSystem_TriggerLeftovers(battleSys, battleCtx, battler) == TRUE) {
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_LEECH_SEED:
                if ((battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_LEECH_SEED) &&
                    battleCtx
                        ->battleMons[battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_LEECH_SEED_RECIPIENT]
                        .curHP &&
                    Battler_Ability(battleCtx, battler) != ABILITY_MAGIC_GUARD &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->msgAttacker =
                        battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_LEECH_SEED_RECIPIENT;
                    battleCtx->msgDefender = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_LEECH_SEED_EFFECT);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_POISON:
                if ((battleCtx->battleMons[battler].status & MON_CONDITION_POISON) &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->msgBattlerTemp = battler;
                    battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[battler].maxHP * -1, 8);

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_POISON_DAMAGE);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_TOXIC:
                if ((battleCtx->battleMons[battler].status & MON_CONDITION_TOXIC) &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->msgBattlerTemp = battler;
                    battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[battler].maxHP, 16);

                    // Below the maximum Toxic stage, advance the counter.
                    if ((battleCtx->battleMons[battler].status & MON_CONDITION_TOXIC_COUNTER) !=
                        MON_CONDITION_TOXIC_COUNTER) {
                        battleCtx->battleMons[battler].status += MON_CONDITION_TOXIC_COUNTER_0;
                    }

                    battleCtx->hpCalcTemp *=
                        ((battleCtx->battleMons[battler].status & MON_CONDITION_TOXIC_COUNTER) >> 8);
                    battleCtx->hpCalcTemp *= -1;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_POISON_DAMAGE);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_BURN:
                if ((battleCtx->battleMons[battler].status & MON_CONDITION_BURN) &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_BURN_DAMAGE);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_NIGHTMARE:
                if ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_NIGHTMARE) &&
                    battleCtx->battleMons[battler].curHP) {
                    if (battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) {
                        battleCtx->msgBattlerTemp = battler;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_NIGHTMARE_EFFECT);
                        state = STATE_BREAK_OUT;
                    } else {
                        battleCtx->battleMons[battler].statusVolatile &= ~VOLATILE_CONDITION_NIGHTMARE;
                    }
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_CURSE:
                if ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_CURSE) &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_CURSE_DAMAGE);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_BIND:
                if ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_BIND) &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->battleMons[battler].statusVolatile -= VOLATILE_CONDITION_BIND_0;

                    if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_BIND) {
                        battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[battler].maxHP * -1, 16);
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_BIND_EFFECT);
                    } else {
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_BIND_END);
                        lbl_8048CE28._0C = battler;
                    }

                    battleCtx->msgMoveTemp = battleCtx->battleMons[battler].moveEffectsData.bindingMove;
                    battleCtx->msgBattlerTemp = battler;
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_BAD_DREAMS:
                battleCtx->scriptTemp = BattleSystem_CountAbility(battleSys,
                                                                  battleCtx,
                                                                  COUNT_ALIVE_BATTLERS_THEIR_SIDE_FLAG,
                                                                  battler,
                                                                  ABILITY_BAD_DREAMS);

                if ((battleCtx->battleMons[battler].status & MON_CONDITION_SLEEP) &&
                    Battler_Ability(battleCtx, battler) != ABILITY_MAGIC_GUARD &&
                    battleCtx->battleMons[battler].curHP && battleCtx->scriptTemp) {
                    battleCtx->hpCalcTemp = BattleSystem_Divide(battleCtx->battleMons[battler].maxHP * -1, 8);

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_BAD_DREAMS);
                    battleCtx->battleStatusMask |= SYSCTL_SKIP_SPRITE_BLINK;
                    battleCtx->msgBattlerTemp = battler;
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_UPROAR:
                if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_UPROAR) {
                    u8 j;
                    for (j = 0; j < maxBattlers; j++) {
                        if ((battleCtx->battleMons[j].status & MON_CONDITION_SLEEP) && battleCtx->battleMons[j].curHP &&
                            Battler_Ability(battleCtx, j) != ABILITY_SOUNDPROOF) {
                            battleCtx->msgBattlerTemp = j;
                            PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_WAKE_UP);
                            lbl_8048CE28._0C = j;
                            break;
                        }
                    }

                    if (j != maxBattlers) {
                        state = STATE_DONE;
                        break;
                    }

                    battleCtx->battleMons[battler].statusVolatile -= VOLATILE_CONDITION_UPROAR_0;

                    if (BattleContext_MoveFailed(battleCtx, battler)) {
                        i = BATTLE_SUBSCRIPT_UPROAR_END;
                        battleCtx->battleMons[battler].statusVolatile &= ~VOLATILE_CONDITION_UPROAR;
                        battleCtx->fieldConditionsMask &=
                            ((FlagIndex(battler) << FIELD_CONDITION_UPROAR_SHIFT) ^ 0xFFFFFFFF);
                    } else if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_UPROAR) {
                        i = BATTLE_SUBSCRIPT_UPROAR_CONTINUES;
                    } else {
                        i = BATTLE_SUBSCRIPT_UPROAR_END;
                        battleCtx->battleMons[battler].statusVolatile &= ~VOLATILE_CONDITION_UPROAR;
                        battleCtx->fieldConditionsMask &=
                            ((FlagIndex(battler) << FIELD_CONDITION_UPROAR_SHIFT) ^ 0xFFFFFFFF);
                    }

                    battleCtx->msgBattlerTemp = battler;
                    PREPARE_SUBROUTINE_SEQUENCE(i);
                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                if (state != STATE_DONE) {
                    battleCtx->monConditionCheckState++;
                }
                break;

            case MON_COND_CHECK_STATE_THRASH:
                if (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_THRASH) {
                    battleCtx->battleMons[battler].statusVolatile -= VOLATILE_CONDITION_THRASH_0;

                    if (BattleContext_MoveFailed(battleCtx, battler)) {
                        battleCtx->battleMons[battler].statusVolatile &= ~VOLATILE_CONDITION_THRASH;
                    } else if ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_THRASH) == FALSE &&
                               (battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_CONFUSION) ==
                                   FALSE) {
                        battleCtx->sideEffectMon = battler;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_THRASH_END);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = battler;
                    }
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_DISABLE:
                if (battleCtx->battleMons[battler].moveEffectsData.disabledMove) {
                    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
                        if (battleCtx->battleMons[battler].moveEffectsData.disabledMove ==
                            battleCtx->battleMons[battler].moves[i]) {
                            break;
                        }
                    }

                    if (i == LEARNED_MOVES_MAX) {
                        battleCtx->battleMons[battler].moveEffectsData.disabledTurns = 0;
                    }

                    if (battleCtx->battleMons[battler].moveEffectsData.disabledTurns) {
                        battleCtx->battleMons[battler].moveEffectsData.disabledTurns--;
                    } else {
                        battleCtx->battleMons[battler].moveEffectsData.disabledMove = MOVE_NONE;
                        battleCtx->msgBattlerTemp = battler;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_DISABLE_END);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = battler;
                    }
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_ENCORE:
                if (battleCtx->battleMons[battler].moveEffectsData.encoredMove) {
                    for (i = 0; i < LEARNED_MOVES_MAX; i++) {
                        if (battleCtx->battleMons[battler].moveEffectsData.encoredMove ==
                            battleCtx->battleMons[battler].moves[i]) {
                            break;
                        }
                    }

                    if (i == LEARNED_MOVES_MAX ||
                        (i != LEARNED_MOVES_MAX && battleCtx->battleMons[battler].ppCur[i] == 0)) {
                        battleCtx->battleMons[battler].moveEffectsData.encoredTurns = 0;
                    }

                    if (battleCtx->battleMons[battler].moveEffectsData.encoredTurns) {
                        battleCtx->battleMons[battler].moveEffectsData.encoredTurns--;
                    } else {
                        battleCtx->battleMons[battler].moveEffectsData.encoredMove = MOVE_NONE;
                        battleCtx->msgBattlerTemp = battler;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_ENCORE_END);
                        state = STATE_BREAK_OUT;
                        lbl_8048CE28._0C = battler;
                    }
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_LOCK_ON:
                if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_LOCK_ON) {
                    battleCtx->battleMons[battler].moveEffectsMask -= (1 << MOVE_EFFECT_LOCK_ON_SHIFT);
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_CHARGE:
                if (battleCtx->battleMons[battler].moveEffectsData.chargedTurns &&
                    --battleCtx->battleMons[battler].moveEffectsData.chargedTurns == 0) {
                    battleCtx->battleMons[battler].moveEffectsMask &= ~MOVE_EFFECT_CHARGE;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_TAUNT:
                if (battleCtx->battleMons[battler].moveEffectsData.tauntedTurns &&
                    --battleCtx->battleMons[battler].moveEffectsData.tauntedTurns == 0) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_TAUNT_END);
                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_MAGNET_RISE:
                if (battleCtx->battleMons[battler].moveEffectsData.magnetRiseTurns &&
                    --battleCtx->battleMons[battler].moveEffectsData.magnetRiseTurns == 0) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_MAGNET_RISE_END);
                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_HEAL_BLOCK:
                if (battleCtx->battleMons[battler].moveEffectsData.healBlockTurns &&
                    --battleCtx->battleMons[battler].moveEffectsData.healBlockTurns == 0) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_HEAL_BLOCK_END);
                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_EMBARGO:
                if (battleCtx->battleMons[battler].moveEffectsData.embargoTurns &&
                    --battleCtx->battleMons[battler].moveEffectsData.embargoTurns == 0) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_EMBARGO_END);
                    state = STATE_BREAK_OUT;
                    lbl_8048CE28._0C = battler;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_YAWN:
                if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_YAWN) {
                    battleCtx->battleMons[battler].moveEffectsMask -= MOVE_EFFECT_YAWN_0;

                    if ((battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_YAWN) == FALSE) {
                        battleCtx->sideEffectMon = battler;
                        battleCtx->sideEffectType = SIDE_EFFECT_TYPE_MOVE_EFFECT;

                        PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_FALL_ASLEEP);
                        state = STATE_BREAK_OUT;
                    }
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_STATE_ITEM_CONDITION: {
                int nextSeq;

                if (BattleSystem_TriggerHeldItemOnStatus(battleSys, battleCtx, battler, &nextSeq) == TRUE) {
                    battleCtx->msgBattlerTemp = battler;

                    PREPARE_SUBROUTINE_SEQUENCE(nextSeq);
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;
            }

            case MON_COND_CHECK_STATE_ITEM_DETRIMENTAL_EFFECT:
                if (BattleSystem_TriggerDetrimentalHeldItem(battleSys, battleCtx, battler) == TRUE) {
                    state = STATE_BREAK_OUT;
                }

                battleCtx->monConditionCheckState++;
                break;

            case MON_COND_CHECK_END:
                battleCtx->monConditionCheckState = MON_COND_CHECK_START;
                battleCtx->monConditionCheckTemp++;
                break;
        }

        if (state) {
            BattleController_EmitClearMessageBox(battleSys);
            return;
        }
    }

    battleCtx->monConditionCheckState = MON_COND_CHECK_START;
    battleCtx->monConditionCheckTemp = 0;
    battleCtx->command = BATTLE_CONTROL_CHECK_SIDE_CONDITIONS;
}

enum SideConditionCheckState {
    SIDE_COND_CHECK_STATE_FUTURE_SIGHT = 0,
    SIDE_COND_CHECK_STATE_PERISH_SONG,
    SIDE_COND_CHECK_STATE_TRICK_ROOM,
    SIDE_COND_CHECK_END,
};

static void BattleControllerPlayer_CheckSideConditions(BattleSystem *battleSys, BattleContext *battleCtx) {
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    if (BattleControllerPlayer_AnyFainted(battleCtx, battleCtx->command, battleCtx->command, 1) == TRUE) {
        return;
    }

    BattleController_EmitClearMessageBox(battleSys);

    int battler;

    switch (battleCtx->sideConditionCheckState) {
        case SIDE_COND_CHECK_STATE_FUTURE_SIGHT:
            while (battleCtx->sideConditionCheckTemp < maxBattlers) {
                battler = battleCtx->monSpeedOrder[battleCtx->sideConditionCheckTemp];

                if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
                    battleCtx->sideConditionCheckTemp++;
                    continue;
                }

                battleCtx->sideConditionCheckTemp++;

                if (battleCtx->fieldConditions.futureSightTurns[battler] &&
                    --battleCtx->fieldConditions.futureSightTurns[battler] == FALSE &&
                    battleCtx->battleMons[battler].curHP) {
                    battleCtx->sideConditionsMask[BattleSystem_GetBattlerSide(battleSys, battler)] &=
                        ~SIDE_CONDITION_FUTURE_SIGHT;
                    battleCtx->msgBuffer.id = 475;
                    battleCtx->msgBuffer.tags = TAG_NICKNAME_MOVE;
                    battleCtx->msgBuffer.params[0] = BattleSystem_NicknameTag(battleCtx, battler);
                    battleCtx->msgBuffer.params[1] = battleCtx->fieldConditions.futureSightMove[battler];
                    battleCtx->msgBattlerTemp = battler;
                    battleCtx->msgAttacker = battleCtx->fieldConditions.futureSightAttacker[battler];
                    battleCtx->msgMoveTemp = battleCtx->fieldConditions.futureSightMove[battler];
                    battleCtx->hpCalcTemp = battleCtx->fieldConditions.futureSightDamage[battler];
                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_FUTURE_SIGHT_DAMAGE);
                    return;
                }
            }

            battleCtx->sideConditionCheckState++;
            battleCtx->sideConditionCheckTemp = 0;
            // fall-through
        case SIDE_COND_CHECK_STATE_PERISH_SONG:
            while (battleCtx->sideConditionCheckTemp < maxBattlers) {
                battler = battleCtx->monSpeedOrder[battleCtx->sideConditionCheckTemp];

                if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
                    battleCtx->sideConditionCheckTemp++;
                    continue;
                }

                battleCtx->sideConditionCheckTemp++;

                if (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_PERISH_SONG) {
                    if (battleCtx->battleMons[battler].moveEffectsData.perishSongTurns == 0) {
                        battleCtx->battleMons[battler].moveEffectsMask &= ~MOVE_EFFECT_PERISH_SONG;
                        battleCtx->msgTemp = battleCtx->battleMons[battler].moveEffectsData.perishSongTurns;
                        battleCtx->hpCalcTemp = battleCtx->battleMons[battler].curHP * -1;
                        battleCtx->battleStatusMask |= SYSCTL_SKIP_SPRITE_BLINK;
                    } else {
                        battleCtx->msgTemp = battleCtx->battleMons[battler].moveEffectsData.perishSongTurns;
                        battleCtx->battleMons[battler].moveEffectsData.perishSongTurns--;
                    }

                    battleCtx->msgBattlerTemp = battler;
                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_CONTINUE_PERISH_SONG);
                    lbl_8048CE28._0C = battler;
                    return;
                }
            }

            battleCtx->sideConditionCheckState++;
            battleCtx->sideConditionCheckTemp = 0;
            // fall-through
        case SIDE_COND_CHECK_STATE_TRICK_ROOM:
            if (battleCtx->fieldConditionsMask & FIELD_CONDITION_TRICK_ROOM) {
                battleCtx->fieldConditionsMask -= FIELD_CONDITION_TRICK_ROOM_0;

                if ((battleCtx->fieldConditionsMask & FIELD_CONDITION_TRICK_ROOM) == FALSE) {
                    PREPARE_SUBROUTINE_SEQUENCE(BATTLE_SUBSCRIPT_TRICK_ROOM_END);
                    return;
                }
            }

            battleCtx->sideConditionCheckState++;
            battleCtx->sideConditionCheckTemp = 0;
            break;
        default: break;
    }

    battleCtx->sideConditionCheckState = 0;
    battleCtx->sideConditionCheckTemp = 0;
    battleCtx->command = BATTLE_CONTROL_TURN_END;
}

static inline BOOL BattleControllerPlayer_ReplaceFainted(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;
    int i;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int retCommand = battleCtx->command;

    for (i = 0; i < maxBattlers; i++) {
        battleCtx->battlerStatusFlags[i] &= ~BATTLER_STATUS_SWITCHING;

        if (((battleType & BATTLE_TYPE_DOUBLES) && (battleType & BATTLE_TYPE_2vs2_TAG) == FALSE) ||
            ((battleType & BATTLE_TYPE_TAG) && BattleSystem_GetBattlerSide(battleSys, i) == FALSE)) {
            // If both of this side's Pokemon have fainted, replace slot 1 first.
            if (battleCtx->battleMons[i].curHP == 0 && battleCtx->battleMons[i ^ 2].curHP == 0 && (i & 2)) {
                continue;
            }

            if (battleCtx->battleMons[i].curHP == 0) {
                int j;
                int curHP;
                int totalHP = 0;
                int monsAlive = 0;
                Party *party = BattleSystem_GetParty(battleSys, i);
                BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, i);

                for (j = 0; j < Party_GetCurrentCount(party); j++) {
                    Pokemon *mon = Party_GetPokemonBySlotIndex(party, j);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                        Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG &&
                        (curHP = Pokemon_GetValue(mon, MON_DATA_HP, NULL))) {
                        monsAlive++;

                        if (battleCtx->selectedPartySlot[i ^ 2] != j) {
                            totalHP += curHP;
                        }
                    }
                }

                if (totalHP == 0) {
                    battleCtx->battlersSwitchingMask |= FlagIndex(i);
                    battleCtx->selectedPartySlot[i] = MAX_PARTY_SIZE;
                } else {
                    battleCtx->commandNext = retCommand;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->battlerStatusFlags[i] |= BATTLER_STATUS_SWITCHING;
                }
            }
        } else if (battleCtx->battleMons[i].curHP == 0) {
            int j;
            int curHP = 0;
            Party *party = BattleSystem_GetParty(battleSys, i);
            BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, i);

            for (j = 0; j < Party_GetCurrentCount(party); j++) {
                Pokemon *mon = Party_GetPokemonBySlotIndex(party, j);

                if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                    Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                    curHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                }
            }

            if (curHP == 0) {
                battleCtx->battlersSwitchingMask |= FlagIndex(i);
                battleCtx->selectedPartySlot[i] = MAX_PARTY_SIZE;
            } else {
                battleCtx->commandNext = retCommand;
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                battleCtx->battlerStatusFlags[i] |= BATTLER_STATUS_SWITCHING;
            }
        }
    }

    if (battleCtx->command == BATTLE_CONTROL_EXEC_SCRIPT) {
        if ((battleType & BATTLE_TYPE_FORCED_SET_MODE) == FALSE &&
            BattleSystem_GetBattleStyle(battleSys) == OPTIONS_BATTLE_STYLE_SHIFT &&
            ((battleCtx->battlerStatusFlags[0] & BATTLER_STATUS_SWITCHING) == FALSE ||
             (battleCtx->battlerStatusFlags[1] & BATTLER_STATUS_SWITCHING) == FALSE) &&
            BattleSystem_AnyReplacementMons(battleSys, battleCtx, BATTLER_US)) {
            // If the player is replacing a fainted Pokemon, the script skips straight to the party list.
            if (battleCtx->battlerStatusFlags[0] & BATTLER_STATUS_SWITCHING) {
                battleCtx->scriptTemp = FALSE;
            } else {
                battleCtx->scriptTemp = TRUE;
            }

            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_REPLACE_FAINTED);
        } else {
            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SHOW_PARTY_LIST);
        }

        result = TRUE;
    }

    return result;
}

static void BattleControllerPlayer_TurnEnd(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (BattleControllerPlayer_AnyExpPayout(battleCtx, battleCtx->command, battleCtx->command) == TRUE) {
        return;
    }

    if (BattleControllerPlayer_CheckBattleOver(battleSys, battleCtx) == TRUE) {
        return;
    }

    if (BattleControllerPlayer_ReplaceFainted(battleSys, battleCtx) == TRUE) {
        return;
    }

    battleCtx->totalTurns++;
    battleCtx->meFirstTurnOrder++;

    BattleContext_Init(battleCtx);
    BattleSystem_SetupNextTurn(battleSys, battleCtx);

    battleCtx->command = BATTLE_CONTROL_TRAINER_MESSAGE;
    fn_8016E2E4(5);
    fn_8016FA4C(2, NULL);

    for (u8 i = 0; i < MAX_BATTLERS; i++) {
        for (u8 j = 0; j < 4; j++) {
            battleCtx->unk314C[i][j] = 0xFF;
        }
    }

    // The values read here are unused.
    for (int i = 0; i < 2; i++) {
        int j;
        Party *party = BattleSystem_GetParty(battleSys, i);

        for (j = 0; j < Party_GetCurrentCount(party); j++) {
            Pokemon *mon = BattleSystem_GetPartyPokemon(battleSys, i, j);

            Pokemon_GetValue(mon, MON_DATA_HP, NULL);
            Pokemon_GetValue(mon, MON_DATA_MAX_HP, NULL);
            Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL);
            Pokemon_GetValue(mon, MON_DATA_LEVEL, NULL);
        }
    }
}

static void BattleControllerPlayer_FightCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL randomizeTarget = FALSE;

    battleCtx->attacker = battleCtx->battlerActionOrder[battleCtx->turnOrderCounter];

    if (ATTACKER_TURN_FLAGS.struggling) {
        battleCtx->moveTemp = MOVE_STRUGGLE;
        randomizeTarget = TRUE;
    } else if (ATTACKING_MON.moveEffectsData.encoredMove &&
               ATTACKING_MON.moveEffectsData.encoredMove ==
                   ATTACKING_MON.moves[ATTACKING_MON.moveEffectsData.encoredMoveSlot]) {
        battleCtx->moveTemp = ATTACKING_MON.moveEffectsData.encoredMove;
        randomizeTarget = TRUE;
    } else if (ATTACKING_MON.moveEffectsData.encoredMove &&
               ATTACKING_MON.moveEffectsData.encoredMove !=
                   ATTACKING_MON.moves[ATTACKING_MON.moveEffectsData.encoredMoveSlot]) {
        battleCtx->moveTemp = ATTACKING_MON.moves[ATTACKING_MON.moveEffectsData.encoredMoveSlot];
        ATTACKING_MON.moveEffectsData.encoredMove = MOVE_NONE;
        ATTACKING_MON.moveEffectsData.encoredMoveSlot = 0;
        ATTACKING_MON.moveEffectsData.encoredTurns = 0;
        randomizeTarget = TRUE;
    } else if (Battler_CanPickCommand(battleCtx, battleCtx->attacker) == FALSE) {
        battleCtx->moveTemp = battleCtx->moveLockedInto[battleCtx->attacker];
    } else if (battleCtx->moveSelected[battleCtx->attacker] !=
               ATTACKING_MON.moves[battleCtx->moveSlot[battleCtx->attacker]]) {
        battleCtx->moveTemp = ATTACKING_MON.moves[battleCtx->moveSlot[battleCtx->attacker]];
        randomizeTarget = TRUE;
    } else {
        battleCtx->moveTemp = ATTACKING_MON.moves[battleCtx->moveSlot[battleCtx->attacker]];
    }

    battleCtx->moveCur = battleCtx->moveTemp;
    battleCtx->command = BATTLE_CONTROL_BEFORE_MOVE;
    battleCtx->defender =
        BattleSystem_Defender(battleSys, battleCtx, battleCtx->attacker, battleCtx->moveTemp, randomizeTarget, 0);
    BattleController_EmitClearMessageBox(battleSys);
}

static void BattleControllerPlayer_ItemCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    battleCtx->attacker = battleCtx->battlerActionOrder[battleCtx->turnOrderCounter];
    battleCtx->defender = BattleSystem_RandomOpponent(battleSys, battleCtx, battleCtx->attacker);

    BattleItemUse *used = (BattleItemUse *)&battleCtx->battlerActions[battleCtx->attacker][BATTLE_ACTION_TEMP_VALUE];
    int nextSeq;

    if (BattleSystem_GetBattlerSide(battleSys, battleCtx->attacker)) {
        switch (battleCtx->aiContext.usedItemType[battleCtx->attacker >> 1]) {
            case ITEM_AI_CATEGORY_FULL_RESTORE: nextSeq = BATTLE_SUBSCRIPT_USE_FULL_RESTORE; break;
            case ITEM_AI_CATEGORY_RECOVER_HP:   nextSeq = BATTLE_SUBSCRIPT_USE_POTION; break;
            case ITEM_AI_CATEGORY_RECOVER_STATUS:
                if ((battleCtx->aiContext.usedItemCondition[battleCtx->attacker >> 1] & ITEM_RECOVER_CONFUSION) &&
                    (battleCtx->aiContext.usedItemCondition[battleCtx->attacker >> 1] & ITEM_RECOVER_FULL)) {
                    battleCtx->msgTemp = 6;
                } else {
                    battleCtx->msgTemp = LowestBit(battleCtx->aiContext.usedItemCondition[battleCtx->attacker >> 1]);
                }

                nextSeq = BATTLE_SUBSCRIPT_USE_STATUS_RECOVERY;
                break;
            case ITEM_AI_CATEGORY_STAT_BOOSTER:
                battleCtx->msgTemp = battleCtx->aiContext.usedItemCondition[battleCtx->attacker >> 1];
                nextSeq = BATTLE_SUBSCRIPT_USE_STAT_BOOSTER;
                break;
            case ITEM_AI_CATEGORY_GUARD_SPEC: nextSeq = BATTLE_SUBSCRIPT_USE_GUARD_SPEC; break;
        }

        battleCtx->msgItemTemp = battleCtx->aiContext.usedItem[battleCtx->attacker >> 1];
    } else {
        switch (used->category) {
            case ITEM_BATTLE_CATEGORY_RECOVER_STATUS:
            case ITEM_BATTLE_CATEGORY_RECOVER_HP:
            case ITEM_BATTLE_CATEGORY_BATTLE_ITEMS:
                if (used->item == ITEM_POKE_DOLL || used->item == ITEM_FLUFFY_TAIL) {
                    nextSeq = BATTLE_SUBSCRIPT_ESCAPE_ITEM;
                } else {
                    nextSeq = BATTLE_SUBSCRIPT_BATTLE_ITEM;
                }
                break;
            case ITEM_BATTLE_CATEGORY_POKE_BALLS:
                // Empty in this game.
                break;
        }

        battleCtx->msgItemTemp = used->item;
    }

    LOAD_SUBSEQ(nextSeq);
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_MOVE_END;
    battleCtx->moveStatusFlags |= MOVE_STATUS_NO_MORE_WORK;
}

static void BattleControllerPlayer_SwitchCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SWITCH_POKEMON);
    battleCtx->switchedMon = battleCtx->attacker = battleCtx->battlerActionOrder[battleCtx->turnOrderCounter];
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_CHECK_ANY_FAINTED;
    battleCtx->scriptTemp = 0;
    battleCtx->moveStatusFlags |= MOVE_STATUS_NO_MORE_WORK;
    fn_8016D1C0(2);
}

static void BattleControllerPlayer_FleeCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    battleCtx->attacker = battleCtx->battlerActionOrder[battleCtx->turnOrderCounter];
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_ESCAPE);
    battleCtx->scriptCursor = 0;
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_FIGHT_END;
}

// Empty in this game.
static void BattleControllerPlayer_SafariBallCommand(BattleSystem *battleSys, BattleContext *battleCtx) {}

// Empty in this game.
static void BattleControllerPlayer_SafariBaitCommand(BattleSystem *battleSys, BattleContext *battleCtx) {}

static void BattleControllerPlayer_SafariRockCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SAFARI_THROW_ROCK);
    battleCtx->attacker = BATTLER_US;
    battleCtx->defender = BATTLER_THEM;
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_MOVE_END;
    battleCtx->scriptTemp = LCRNG_Next() % 10;

    if (battleCtx->safariEscapeCount) {
        battleCtx->safariEscapeCount--;
    }

    if (battleCtx->scriptTemp) {
        battleCtx->msgTemp = 1;

        if (battleCtx->safariCatchStage) {
            battleCtx->safariCatchStage--;
        }
    }
}

static void BattleControllerPlayer_SafariFleeCommand(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SAFARI_ESCAPE);
    battleCtx->attacker = BATTLER_US;
    battleCtx->defender = BATTLER_THEM;
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_MOVE_END;
}

// Unlike in Platinum, the target is not changed here for charging moves.
static BOOL BattleControllerPlayer_HasNoTarget(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;

    if ((battleCtx->defender == BATTLER_NONE && Move_IsMultiTurn(battleCtx, battleCtx->moveCur) == FALSE) ||
        (battleCtx->defender == BATTLER_NONE && Move_IsMultiTurn(battleCtx, battleCtx->moveCur) == TRUE &&
         ((ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_MOVE_LOCKED) ||
          (battleCtx->battleStatusMask & SYSCTL_LAST_OF_MULTI_TURN)))) {
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_NO_TARGET);
        battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

        result = TRUE;
    }

    return result;
}

// The accuracy multiplier for each combined stage, from -6 to +6.
static const Fraction sHitRateByStage[] = {
    { 33, 100},
    { 36, 100},
    { 43, 100},
    { 50, 100},
    { 60, 100},
    { 75, 100},
    {  1,   1},
    {133, 100},
    {166, 100},
    {  2,   1},
    {233, 100},
    {133,  50},
    {  3,   1},
};

static int BattleControllerPlayer_CheckMoveHitAccuracy(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move) {
    u8 moveType;
    s8 evaStages;
    s8 accStages;
    u8 moveClass;
    s8 sumStages;
    u16 hitRate;
    int itemEffect;
    int itemPower;

    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_CATCH_TUTORIAL) {
        return 0;
    }

    // pokeplatinum CalcMoveType, written in line in this game; the type is unused.
    if (Battler_Ability(battleCtx, attacker) == ABILITY_NORMALIZE) {
        moveType = TYPE_NORMAL;
    } else if (battleCtx->moveType) {
        moveType = battleCtx->moveType;
    } else {
        moveType = MOVE_DATA(move).type;
    }

    moveClass = MOVE_DATA(move).moveClass;
    accStages = battleCtx->battleMons[attacker].statBoosts[BATTLE_STAT_ACCURACY] - 6;
    evaStages = 6 - battleCtx->battleMons[defender].statBoosts[BATTLE_STAT_EVASION];

    if (Battler_Ability(battleCtx, attacker) == ABILITY_SIMPLE) {
        accStages *= 2;
    }
    if (Battler_IgnorableAbility(battleCtx, attacker, defender, ABILITY_SIMPLE) == TRUE) {
        evaStages *= 2;
    }
    if (Battler_IgnorableAbility(battleCtx, attacker, defender, ABILITY_UNAWARE) == TRUE) {
        accStages = 0;
    }
    if (Battler_Ability(battleCtx, attacker) == ABILITY_UNAWARE) {
        evaStages = 0;
    }
    if (MON_IS_IDENTIFIED(defender) && evaStages < 0) {
        evaStages = 0;
    }

    sumStages = 6 + evaStages + accStages;
    if (sumStages < 0) {
        sumStages = 0;
    }
    if (sumStages > 12) {
        sumStages = 12;
    }

    hitRate = MOVE_DATA(move).accuracy;
    if (hitRate == 0) {
        return 0;
    }

    // Charging moves ignore accuracy on their first turn.
    if (battleCtx->battleStatusMask & SYSCTL_FIRST_OF_MULTI_TURN) {
        return 0;
    }

    // These moves use their own formula.
    if (battleCtx->battleStatusMask & SYSCTL_NONSTANDARD_ACC_CHECK) {
        return 0;
    }

    if (NO_CLOUD_NINE && WEATHER_IS_SUN && MOVE_DATA(move).effect == BATTLE_EFFECT_THUNDER) {
        hitRate = 50;
    }

    hitRate *= sHitRateByStage[sumStages].numerator;
    hitRate /= sHitRateByStage[sumStages].denominator;

    if (Battler_Ability(battleCtx, attacker) == ABILITY_COMPOUND_EYES) {
        hitRate = hitRate * 130 / 100;
    }

    if (NO_CLOUD_NINE) {
        if (WEATHER_IS_SAND && Battler_IgnorableAbility(battleCtx, attacker, defender, ABILITY_SAND_VEIL) == TRUE) {
            hitRate = hitRate * 80 / 100;
        }

        if (WEATHER_IS_HAIL && Battler_IgnorableAbility(battleCtx, attacker, defender, ABILITY_SNOW_CLOAK) == TRUE) {
            hitRate = hitRate * 80 / 100;
        }

        if (battleCtx->fieldConditionsMask & FIELD_CONDITION_DEEP_FOG) {
            hitRate = hitRate * 6 / 10;
        }
    }

    if (Battler_Ability(battleCtx, attacker) == ABILITY_HUSTLE && moveClass == CLASS_PHYSICAL) {
        hitRate = hitRate * 80 / 100;
    }

    if (Battler_IgnorableAbility(battleCtx, attacker, defender, ABILITY_TANGLED_FEET) == TRUE &&
        (battleCtx->battleMons[defender].statusVolatile & VOLATILE_CONDITION_CONFUSION)) {
        hitRate = hitRate * 50 / 100;
    }

    itemEffect = Battler_HeldItemEffect(battleCtx, defender);
    itemPower = Battler_HeldItemPower(battleCtx, defender, ITEM_POWER_CHECK_ALL);

    if (itemEffect == HOLD_EFFECT_ACC_REDUCE) {
        hitRate = hitRate * (100 - itemPower) / 100;
    }

    itemEffect = Battler_HeldItemEffect(battleCtx, attacker);
    itemPower = Battler_HeldItemPower(battleCtx, attacker, ITEM_POWER_CHECK_ALL);

    if (itemEffect == HOLD_EFFECT_ACCURACY_UP) {
        hitRate = hitRate * (100 + itemPower) / 100;
    }

    if (itemEffect == HOLD_EFFECT_ACCURACY_UP_SLOWER && Battler_MovedThisTurn(battleCtx, defender) == TRUE) {
        hitRate = hitRate * (100 + itemPower) / 100;
    }

    if (battleCtx->battleMons[attacker].moveEffectsData.micleBerry) {
        battleCtx->battleMons[attacker].moveEffectsData.micleBerry = FALSE;
        hitRate = hitRate * 120 / 100;
    }

    if (battleCtx->fieldConditionsMask & FIELD_CONDITION_GRAVITY) {
        hitRate = hitRate * 10 / 6;
    }

    if ((LCRNG_Next() % 100) + 1 > hitRate) {
        battleCtx->moveStatusFlags |= MOVE_STATUS_MISSED;
    }

    return 0;
}

static int BattleControllerPlayer_CheckMoveHitOverrides(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move) {
    if (battleCtx->battleStatusMask & SYSCTL_FIRST_OF_MULTI_TURN) {
        return 0;
    }

    if (battleCtx->turnFlags[defender].protecting && (MOVE_DATA(move).flags & MOVE_FLAG_CAN_PROTECT) &&
        (move != MOVE_CURSE || Move_IsGhostCurse(battleCtx, move, attacker) == TRUE) // a Ghost's Curse can be blocked
        && (Move_IsMultiTurn(battleCtx, move) == FALSE || (battleCtx->battleStatusMask & SYSCTL_LAST_OF_MULTI_TURN))) {
        Battler_UnlockMoveChoice(battleSys, battleCtx, attacker);
        battleCtx->moveStatusFlags |= MOVE_STATUS_PROTECTED;
        return 0;
    }

    // Unlike in Platinum, No Guard is read from the current attacker and defender rather than the arguments.
    if ((battleCtx->battleStatusMask & SYSCTL_NONSTANDARD_ACC_CHECK) == FALSE &&
        (MON_IS_LOCKED_ONTO(attacker, defender) ||
         Battler_Ability(battleCtx, battleCtx->attacker) == ABILITY_NO_GUARD ||
         Battler_Ability(battleCtx, battleCtx->defender) == ABILITY_NO_GUARD)) {
        battleCtx->moveStatusFlags &= ~MOVE_STATUS_MISSED;
        return 0;
    }

    if (NO_CLOUD_NINE) {
        if (WEATHER_IS_RAIN && MOVE_DATA(move).effect == BATTLE_EFFECT_THUNDER) {
            battleCtx->moveStatusFlags &= ~MOVE_STATUS_MISSED;
        }

        if (WEATHER_IS_HAIL && MOVE_DATA(move).effect == BATTLE_EFFECT_BLIZZARD) {
            battleCtx->moveStatusFlags &= ~MOVE_STATUS_MISSED;
        }
    }

    if ((battleCtx->moveStatusFlags & MOVE_STATUS_BYPASSED_ACCURACY) == FALSE &&
        CURRENT_MOVE_DATA.range != RANGE_OPPONENT_SIDE &&
        (((battleCtx->battleStatusMask & SYSCTL_HIT_DURING_FLY) == FALSE &&
          (battleCtx->battleMons[defender].moveEffectsMask & MOVE_EFFECT_AIRBORNE)) ||
         ((battleCtx->battleStatusMask & SYSCTL_HIT_DURING_SHADOW_FORCE) == FALSE &&
          (battleCtx->battleMons[defender].moveEffectsMask & MOVE_EFFECT_SHADOW_FORCE)) ||
         ((battleCtx->battleStatusMask & SYSCTL_HIT_DURING_DIG) == FALSE &&
          (battleCtx->battleMons[defender].moveEffectsMask & MOVE_EFFECT_UNDERGROUND)) ||
         ((battleCtx->battleStatusMask & SYSCTL_HIT_DURING_DIVE) == FALSE &&
          (battleCtx->battleMons[defender].moveEffectsMask & MOVE_EFFECT_UNDERWATER)))) {
        battleCtx->moveStatusFlags |= MOVE_STATUS_SEMI_INVULNERABLE;
    }

    return 0;
}

enum CheckStatusState {
    CHECK_STATUS_START = 0,
    CHECK_STATUS_STATE_SLEEP,
    CHECK_STATUS_STATE_FREEZE,
    CHECK_STATUS_STATE_TRUANT,
    CHECK_STATUS_STATE_RECHARGING,
    CHECK_STATUS_STATE_FLINCH,
    CHECK_STATUS_STATE_DISABLE,
    CHECK_STATUS_STATE_TAUNT,
    CHECK_STATUS_STATE_IMPRISON,
    CHECK_STATUS_STATE_GRAVITY,
    CHECK_STATUS_STATE_HEAL_BLOCK,
    CHECK_STATUS_STATE_CONFUSION,
    CHECK_STATUS_STATE_PARALYSIS,
    CHECK_STATUS_STATE_ATTRACT,
    CHECK_STATUS_STATE_BIDE,
    CHECK_STATUS_STATE_SELF_THAW,
    CHECK_STATUS_END,
};

enum CheckStatusResult {
    CHECK_STATUS_LOOP_BACK = 0,
    CHECK_STATUS_DISRUPT_MOVE,
    CHECK_STATUS_GO_TO_SCRIPT,
    CHECK_STATUS_DONE,
};

static inline BOOL BattleControllerPlayer_CheckStatusDisruption(BattleSystem *battleSys, BattleContext *battleCtx) {
    int moveEffect = battleCtx->aiContext.moveTable[battleCtx->moveCur].effect;
    int result = CHECK_STATUS_LOOP_BACK;

    do {
        switch (battleCtx->statusCheckState) {
            case CHECK_STATUS_START:
                ATTACKING_MON.statusVolatile &= ~VOLATILE_CONDITION_DESTINY_BOND;
                ATTACKING_MON.moveEffectsMask &= ~MOVE_EFFECT_GRUDGE;
                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_SLEEP:
                if (ATTACKING_MON.status & MON_CONDITION_SLEEP) {
                    if ((battleCtx->fieldConditionsMask & FIELD_CONDITION_UPROAR) &&
                        Battler_Ability(battleCtx, battleCtx->attacker) != ABILITY_SOUNDPROOF) {
                        battleCtx->msgBattlerTemp = battleCtx->attacker;

                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_WAKE_UP);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                        result = CHECK_STATUS_GO_TO_SCRIPT;
                        lbl_8048CE28._0C = battleCtx->attacker;
                    } else if ((battleCtx->moveCur != MOVE_SLEEP_TALK && battleCtx->moveTemp == MOVE_SLEEP_TALK) ==
                               FALSE) {
                        int sleepDec;
                        if (Battler_Ability(battleCtx, battleCtx->attacker) == ABILITY_EARLY_BIRD) {
                            sleepDec = 2;
                        } else {
                            sleepDec = 1;
                        }

                        if ((ATTACKING_MON.status & MON_CONDITION_SLEEP) < sleepDec) {
                            ATTACKING_MON.status &= ~MON_CONDITION_SLEEP;
                        } else {
                            ATTACKING_MON.status -= sleepDec;
                        }

                        if (ATTACKING_MON.status & MON_CONDITION_SLEEP) {
                            if (battleCtx->moveCur != MOVE_SNORE && battleCtx->moveTemp != MOVE_SLEEP_TALK) {
                                LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SLEEPING);

                                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                                battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                                result = CHECK_STATUS_GO_TO_SCRIPT;
                            }
                        } else {
                            battleCtx->msgBattlerTemp = battleCtx->attacker;

                            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_WAKE_UP);
                            battleCtx->commandNext = battleCtx->command;
                            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                            result = CHECK_STATUS_GO_TO_SCRIPT;
                            lbl_8048CE28._0C = battleCtx->attacker;
                        }
                    }
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_FREEZE:
                if (ATTACKING_MON.status & MON_CONDITION_FREEZE) {
                    if (LCRNG_Next() % 5 != 0) {
                        if (moveEffect != BATTLE_EFFECT_THAW_AND_BURN_HIT &&
                            moveEffect != BATTLE_EFFECT_RECOIL_BURN_HIT) {
                            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FROZEN);
                            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                            battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                            result = CHECK_STATUS_DISRUPT_MOVE;
                        }
                    } else {
                        battleCtx->msgBattlerTemp = battleCtx->attacker;

                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_THAW_OUT);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                        result = CHECK_STATUS_GO_TO_SCRIPT;
                    }
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_TRUANT:
                if (Battler_CheckTruant(battleCtx, battleCtx->attacker) == TRUE) {
                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_LOAFING_AROUND);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_RECHARGING:
                if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_RECHARGING) {
                    ATTACKING_MON.statusVolatile &= ~VOLATILE_CONDITION_RECHARGING;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_RECHARGING);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_FLINCH:
                if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_FLINCH) {
                    ATTACKING_MON.statusVolatile &= ~VOLATILE_CONDITION_FLINCH;
                    battleCtx->moveFailFlags[battleCtx->attacker].flinched = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FLINCHED);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_DISABLE:
                if (ATTACKING_MON.moveEffectsData.disabledMove == battleCtx->moveTemp) {
                    battleCtx->moveFailFlags[battleCtx->attacker].disabled = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_IS_DISABLED);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_TAUNT:
                if (ATTACKING_MON.moveEffectsData.tauntedTurns &&
                    battleCtx->aiContext.moveTable[battleCtx->moveCur].power == 0) {
                    battleCtx->moveFailFlags[battleCtx->attacker].taunted = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_FAIL_TAUNTED);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_IMPRISON:
                if (Move_Imprisoned(battleSys, battleCtx, battleCtx->attacker, battleCtx->moveCur)) {
                    battleCtx->moveFailFlags[battleCtx->attacker].imprisoned = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_IS_IMPRISONED);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_GRAVITY:
                if (Move_FailsInHighGravity(battleSys, battleCtx, battleCtx->attacker, battleCtx->moveCur)) {
                    battleCtx->moveFailFlags[battleCtx->attacker].gravity = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_FAIL_GRAVITY);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_HEAL_BLOCK:
                if (Move_HealBlocked(battleSys, battleCtx, battleCtx->attacker, battleCtx->moveCur)) {
                    battleCtx->moveFailFlags[battleCtx->attacker].healBlocked = TRUE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_IS_HEAL_BLOCKED);
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                    result = CHECK_STATUS_DISRUPT_MOVE;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_CONFUSION:
                battleCtx->statusCheckState++;

                if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_CONFUSION) {
                    ATTACKING_MON.statusVolatile -= VOLATILE_CONDITION_CONFUSION_0;

                    if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_CONFUSION) {
                        if (LCRNG_Next() & 1) {
                            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_CONFUSED);
                            battleCtx->commandNext = battleCtx->command;
                            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                            result = CHECK_STATUS_GO_TO_SCRIPT;
                        } else {
                            battleCtx->moveFailFlags[battleCtx->attacker].confused = TRUE;
                            battleCtx->defender = battleCtx->attacker;
                            battleCtx->msgBattlerTemp = battleCtx->defender;

                            battleCtx->hpCalcTemp = CALC_SELF_HIT(MOVE_STRUGGLE, 40);
                            battleCtx->hpCalcTemp = BattleSystem_CalcDamageVariance(battleCtx, battleCtx->hpCalcTemp);
                            battleCtx->hpCalcTemp *= -1;
                            battleCtx->battleStatusMask |= SYSCTL_SKIP_SPRITE_BLINK;

                            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_HURT_SELF_IN_CONFUSION);
                            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                            battleCtx->commandNext = BATTLE_CONTROL_LOOP_FAINTED;

                            result = CHECK_STATUS_DISRUPT_MOVE;
                        }
                    } else {
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SNAP_OUT_OF_CONFUSION);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        result = CHECK_STATUS_GO_TO_SCRIPT;
                    }
                }
                break;

            case CHECK_STATUS_STATE_PARALYSIS:
                if ((ATTACKING_MON.status & MON_CONDITION_PARALYSIS) &&
                    Battler_Ability(battleCtx, battleCtx->attacker) != ABILITY_MAGIC_GUARD) {
                    if (LCRNG_Next() % 4 == 0) {
                        battleCtx->moveFailFlags[battleCtx->attacker].paralyzed = TRUE;

                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FULLY_PARALYZED);
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                        battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                        result = CHECK_STATUS_DISRUPT_MOVE;
                    }
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_ATTRACT:
                if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_ATTRACT) {
                    battleCtx->msgBattlerTemp = LowestBit((ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_ATTRACT) >>
                                                          VOLATILE_CONDITION_ATTRACT_SHIFT);

                    if (LCRNG_Next() & 1) {
                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_INFATUATED);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        result = CHECK_STATUS_GO_TO_SCRIPT;
                    } else {
                        battleCtx->moveFailFlags[battleCtx->attacker].infatuated = TRUE;

                        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_IMMOBILIZED_BY_LOVE);
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                        battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;

                        result = CHECK_STATUS_DISRUPT_MOVE;
                    }
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_STATE_BIDE:
                battleCtx->statusCheckState++;

                if (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_BIDE) {
                    ATTACKING_MON.statusVolatile -= VOLATILE_CONDITION_BIDE_0;

                    if ((ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_BIDE) == FALSE &&
                        battleCtx->storedDamage[battleCtx->attacker]) {
                        battleCtx->damage = battleCtx->storedDamage[battleCtx->attacker] * 2;

                        if (battleCtx->battleMons[battleCtx->lastHitByBattler[battleCtx->attacker]].curHP) {
                            battleCtx->defender = battleCtx->lastHitByBattler[battleCtx->attacker];
                        } else {
                            battleCtx->defender =
                                BattleSystem_RandomOpponent(battleSys, battleCtx, battleCtx->attacker);

                            if (DEFENDING_MON.curHP == 0) {
                                LOAD_SUBSEQ(BATTLE_SUBSCRIPT_BIDE_NO_TARGET);
                                battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;
                                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                                result = CHECK_STATUS_GO_TO_SCRIPT;
                                break;
                            }
                        }
                    }

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_BIDE_END);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    result = CHECK_STATUS_GO_TO_SCRIPT;
                }
                break;

            case CHECK_STATUS_STATE_SELF_THAW:
                if ((ATTACKING_MON.status & MON_CONDITION_FREEZE) &&
                    (moveEffect == BATTLE_EFFECT_THAW_AND_BURN_HIT || moveEffect == BATTLE_EFFECT_RECOIL_BURN_HIT)) {
                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_DEFROSTED_BY_MOVE);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    result = CHECK_STATUS_GO_TO_SCRIPT;
                }

                battleCtx->statusCheckState++;
                break;

            case CHECK_STATUS_END:
                battleCtx->statusCheckState = CHECK_STATUS_START;
                result = CHECK_STATUS_DONE;
                break;
        }
    } while (result == CHECK_STATUS_LOOP_BACK);

    BattleMon_CopyToParty(battleSys, battleCtx, battleCtx->attacker);

    if (result == CHECK_STATUS_DISRUPT_MOVE) {
        battleCtx->battleStatusMask |= SYSCTL_CHECK_LOOP_ONLY_ONCE;
        battleCtx->moveStatusFlags |= MOVE_STATUS_NO_MORE_WORK;
    }

    return result != CHECK_STATUS_DONE;
}

enum ObedienceCheckResult {
    OBEY_CHECK_SUCCESS = 0,
    OBEY_CHECK_DO_NOTHING,
    OBEY_CHECK_DIFFERENT_MOVE,
    OBEY_CHECK_HIT_SELF,
};

// Unlike in Platinum, every Pokemon obeys; only the two reads remain.
static inline int
BattleControllerPlayer_CheckObedience(BattleSystem *battleSys, BattleContext *battleCtx, int *nextSeq) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    TrainerInfo *trInfo = BattleSystem_GetTrainerInfo(battleSys, 0);

    return OBEY_CHECK_SUCCESS;
}

static inline BOOL BattleControllerPlayer_DecrementPP(BattleSystem *battleSys, BattleContext *battleCtx) {
    int ppCost = 1;
    if (ATTACKER_SELF_TURN_FLAGS.skipPressureCheck == FALSE && battleCtx->defender != BATTLER_NONE) {
        if (battleCtx->moveTemp == MOVE_IMPRISON) {
            ppCost += BattleSystem_CountAbility(battleSys,
                                                battleCtx,
                                                COUNT_ALIVE_BATTLERS_THEIR_SIDE,
                                                battleCtx->attacker,
                                                ABILITY_PRESSURE);
        } else {
            switch (battleCtx->aiContext.moveTable[battleCtx->moveTemp].range) {
                case RANGE_ALL_ADJACENT:
                case RANGE_FIELD:
                    // Number of Pokemon on the field with Pressure
                    ppCost += BattleSystem_CountAbility(battleSys,
                                                        battleCtx,
                                                        COUNT_ALIVE_BATTLERS_EXCEPT_ME,
                                                        battleCtx->attacker,
                                                        ABILITY_PRESSURE);
                    break;

                case RANGE_ADJACENT_OPPONENTS:
                case RANGE_OPPONENT_SIDE:
                    // Number of Pokemon on the opposing side with Pressure
                    ppCost += BattleSystem_CountAbility(battleSys,
                                                        battleCtx,
                                                        COUNT_ALIVE_BATTLERS_THEIR_SIDE,
                                                        battleCtx->attacker,
                                                        ABILITY_PRESSURE);
                    break;

                case RANGE_USER_SIDE:
                case RANGE_USER:
                case RANGE_USER_OR_ALLY:
                case RANGE_ALLY:         break;

                default:
                    if (battleCtx->attacker != battleCtx->defender &&
                        Battler_Ability(battleCtx, battleCtx->defender) == ABILITY_PRESSURE) {
                        ppCost++;
                    }

                    break;
            }
        }
    }

    int moveSlot = Battler_SlotForMove(&ATTACKING_MON, battleCtx->moveTemp);
    if (ATTACKER_TURN_FLAGS.ppDecremented == FALSE && ATTACKER_TURN_FLAGS.struggling == FALSE) {
        ATTACKER_TURN_FLAGS.ppDecremented = TRUE;

        if (ATTACKING_MON.ppCur[moveSlot] && moveSlot < LEARNED_MOVES_MAX) {
            if (ATTACKING_MON.ppCur[moveSlot] > ppCost) {
                ATTACKING_MON.ppCur[moveSlot] -= ppCost;
            } else {
                ATTACKING_MON.ppCur[moveSlot] = 0;
            }

            BattleMon_CopyToParty(battleSys, battleCtx, battleCtx->attacker);
        } else {
            battleCtx->moveStatusFlags |= MOVE_STATUS_NO_PP;
        }
    } else if (ATTACKING_MON.ppCur[moveSlot] == 0 &&
               (battleCtx->battleStatusMask & SYSCTL_LAST_OF_MULTI_TURN) == FALSE &&
               (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_MOVE_LOCKED) == FALSE &&
               (ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_THRASH) == FALSE &&
               MON_IS_UPROARING(battleCtx->attacker) == FALSE && moveSlot < LEARNED_MOVES_MAX) {
        battleCtx->moveStatusFlags |= MOVE_STATUS_NO_PP;
    }

    return FALSE;
}

static inline BOOL BattleControllerPlayer_MoveStolen(BattleSystem *battleSys, BattleContext *battleCtx) {
    int i, battler;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    if (battleCtx->defender == BATTLER_NONE) {
        return FALSE;
    }

    if ((battleCtx->moveStatusFlags & MOVE_STATUS_NO_EFFECTS) == FALSE && DEFENDER_TURN_FLAGS.magicCoat &&
        (CURRENT_MOVE_DATA.flags & MOVE_FLAG_CAN_MAGIC_COAT)) {
        DEFENDER_TURN_FLAGS.magicCoat = FALSE;

        battleCtx->moveProtect[battleCtx->attacker] = FALSE;
        battleCtx->movePrevByBattler[battleCtx->attacker] = battleCtx->moveTemp;
        battleCtx->movePrev = battleCtx->moveTemp;

        battleCtx->battleStatusMask |= SYSCTL_REUSE_LAST_MOVE;

        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MAGIC_COAT);
        battleCtx->commandNext = battleCtx->command;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

        BattleSystem_DecPPForPressure(battleCtx, battleCtx->defender, battleCtx->attacker);
        return TRUE;
    }

    for (i = 0; i < maxBattlers; i++) {
        battler = battleCtx->monSpeedOrder[i];
        if ((battleCtx->moveStatusFlags & MOVE_STATUS_NO_EFFECTS) == FALSE && battleCtx->turnFlags[battler].snatching &&
            (CURRENT_MOVE_DATA.flags & MOVE_FLAG_CAN_SNATCH)) {
            battleCtx->msgBattlerTemp = battler;
            battleCtx->turnFlags[battler].snatching = FALSE;

            if ((battleCtx->battleStatusMask & SYSCTL_REUSE_LAST_MOVE) == FALSE) {
                battleCtx->moveProtect[battleCtx->attacker] = 0;
                battleCtx->movePrevByBattler[battleCtx->attacker] = battleCtx->moveTemp;
                battleCtx->movePrev = battleCtx->moveTemp;

                battleCtx->battleStatusMask |= SYSCTL_REUSE_LAST_MOVE;
            }

            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_SNATCH);
            battleCtx->commandNext = battleCtx->command;
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

            BattleSystem_DecPPForPressure(battleCtx, battler, battleCtx->attacker);
            return TRUE;
        }
    }

    return FALSE;
}

enum BeforeMoveState {
    BEFORE_MOVE_START = 0,

    BEFORE_MOVE_STATE_QUICK_CLAW = BEFORE_MOVE_START,
    BEFORE_MOVE_STATE_STATUS_DISRUPTION,
    BEFORE_MOVE_STATE_CHECK_OBEDIENCE,
    BEFORE_MOVE_STATE_DECREMENT_PP,
    BEFORE_MOVE_STATE_CHECK_TARGET_EXISTS,
    BEFORE_MOVE_STATE_CHECK_STOLEN,
    BEFORE_MOVE_STATE_REDIRECT_TARGET,

    BEFORE_MOVE_END,
};

static void BattleControllerPlayer_BeforeMove(BattleSystem *battleSys, BattleContext *battleCtx) {
    switch (battleCtx->beforeMoveCheckState) {
        case BEFORE_MOVE_STATE_QUICK_CLAW:
            // pokeplatinum LoadQuickClawCheck, written in line in this game.
            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_CHECK_QUICK_CLAW);
            battleCtx->commandNext = battleCtx->command;
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
            battleCtx->beforeMoveCheckState++;
            return;

        case BEFORE_MOVE_STATE_STATUS_DISRUPTION:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_STATUS_CHECK) == FALSE &&
                BattleControllerPlayer_CheckStatusDisruption(battleSys, battleCtx) == TRUE) {
                return;
            }
            battleCtx->beforeMoveCheckState++;

        case BEFORE_MOVE_STATE_CHECK_OBEDIENCE:
            int result;
            int nextSeq;

            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_OBEDIENCE_CHECK) == FALSE) {
                result = BattleControllerPlayer_CheckObedience(battleSys, battleCtx, &nextSeq);

                if (result) {
                    switch (result) {
                        case OBEY_CHECK_DO_NOTHING: battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS; break;
                        case OBEY_CHECK_DIFFERENT_MOVE: battleCtx->commandNext = battleCtx->command; break;
                        case OBEY_CHECK_HIT_SELF:       battleCtx->commandNext = BATTLE_CONTROL_LOOP_FAINTED; break;
                    }

                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    LOAD_SUBSEQ(nextSeq);

                    return;
                }
            }

            battleCtx->beforeMoveCheckState++;

        case BEFORE_MOVE_STATE_DECREMENT_PP:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_PP_DECREMENT) == FALSE &&
                BattleControllerPlayer_DecrementPP(battleSys, battleCtx) == TRUE) {
                return;
            }

            battleCtx->beforeMoveCheckState++;

        case BEFORE_MOVE_STATE_CHECK_TARGET_EXISTS:
            if (BattleControllerPlayer_HasNoTarget(battleSys, battleCtx) == TRUE) {
                return;
            }

            battleCtx->beforeMoveCheckState++;

        case BEFORE_MOVE_STATE_CHECK_STOLEN:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_STOLEN_CHECK) == FALSE &&
                BattleControllerPlayer_MoveStolen(battleSys, battleCtx) == 1) {
                return;
            }

            battleCtx->beforeMoveCheckState++;

        case BEFORE_MOVE_STATE_REDIRECT_TARGET:
            BattleSystem_CheckRedirectionAbilities(battleSys, battleCtx, battleCtx->attacker, battleCtx->moveCur);
            battleCtx->beforeMoveCheckState = BEFORE_MOVE_START;
    }

    if (battleCtx->moveStatusFlags & MOVE_STATUS_NO_EFFECTS) {
        battleCtx->command = BATTLE_CONTROL_MOVE_FAILED;
    } else {
        battleCtx->battleStatusMask2 |= SYSCTL_MOVE_SUCCEEDED;

        BattleSystem_LoadScript(battleCtx, NARC_INDEX_BATTLE__SKILL__WAZA_SEQ, battleCtx->moveCur);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_TRY_MOVE;

        BattleSystem_UpdateLastResort(battleSys, battleCtx);
    }

    BattleSystem_UpdateMetronomeCount(battleSys, battleCtx);

    // TODO What this flag of the command arguments means (cleared at MoveEnd)
    if (lbl_8048CDE8.args[15] == 0) {
        lbl_8048CDE8.args[0] = battleCtx->moveCur;
        lbl_8048CDE8.args[15] = 1;
        fn_8016FA4C(5, &lbl_8048CDE8);
    }
}

static void BattleControllerPlayer_ExecScript(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (fn_803C94CC((u8 *)battleSys, (u8 *)battleCtx) == TRUE) {
        battleCtx->scriptCursor = 0;
        battleCtx->command = battleCtx->commandNext;
    }
}

static inline int BattleControllerPlayer_CheckTypeChart(BattleSystem *battleSys, BattleContext *battleCtx) {
    if ((CURRENT_MOVE_DATA.range != RANGE_USER && CURRENT_MOVE_DATA.range != RANGE_USER_SIDE &&
         CURRENT_MOVE_DATA.power && (battleCtx->battleStatusMask & SYSCTL_IGNORE_IMMUNITIES) == FALSE &&
         (battleCtx->battleStatusMask & SYSCTL_FIRST_OF_MULTI_TURN) == FALSE) ||
        battleCtx->moveCur == MOVE_THUNDER_WAVE) {
        battleCtx->damage = BattleSystem_ApplyTypeChart(battleSys,
                                                        battleCtx,
                                                        battleCtx->moveCur,
                                                        battleCtx->moveType,
                                                        battleCtx->attacker,
                                                        battleCtx->defender,
                                                        battleCtx->damage,
                                                        &battleCtx->moveStatusFlags);

        if (battleCtx->moveStatusFlags & MOVE_STATUS_INEFFECTIVE) {
            battleCtx->moveFailFlags[battleCtx->attacker].noEffect = TRUE;
        }
    }

    return 0;
}

enum ImmunityAbilityState {
    IMMUNITY_ABILITY_STATE_START = 0,

    IMMUNITY_ABILITY_STATE_CHECK = IMMUNITY_ABILITY_STATE_START,

    IMMUNITY_ABILITY_STATE_END,
};

static inline BOOL BattleControllerPlayer_TriggerImmunityAbilities(BattleSystem *battleSys, BattleContext *battleCtx) {
    int result = STATE_PROCESSING;

    do {
        switch (battleCtx->abilityCheckState) {
            case IMMUNITY_ABILITY_STATE_CHECK:
                int nextSeq = BattleSystem_TriggerImmunityAbility(battleCtx, battleCtx->attacker, battleCtx->defender);

                if ((nextSeq && (battleCtx->moveStatusFlags & MOVE_STATUS_DID_NOT_HIT) == FALSE) ||
                    nextSeq == BATTLE_SUBSCRIPT_BLOCKED_BY_SOUNDPROOF) {
                    LOAD_SUBSEQ(nextSeq);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    battleCtx->moveStatusFlags |= MOVE_STATUS_NO_MORE_WORK;

                    result = STATE_BREAK_OUT;
                }

                battleCtx->abilityCheckState++;
                break;

            case IMMUNITY_ABILITY_STATE_END:
                battleCtx->abilityCheckState = IMMUNITY_ABILITY_STATE_START;
                result = STATE_DONE;
                break;
        }
    } while (result == STATE_PROCESSING);

    return result != STATE_DONE;
}

enum TryMoveState {
    TRY_MOVE_START = 0,

    TRY_MOVE_STATE_CHECK_VALID_TARGET = TRY_MOVE_START,
    TRY_MOVE_STATE_TRIGGER_REDIRECTION_ABILITIES,
    TRY_MOVE_STATE_CHECK_MOVE_HITS,
    TRY_MOVE_STATE_CHECK_MOVE_HIT_OVERRIDES,
    TRY_MOVE_STATE_CHECK_TYPE_CHART,
    TRY_MOVE_STATE_TRIGGER_IMMUNITY_ABILITIES,

    TRY_MOVE_END,
};

static void BattleControllerPlayer_TryMove(BattleSystem *battleSys, BattleContext *battleCtx) {
    Party *party;
    Pokemon *mon;
    int monsAlive;
    int i;

    switch (battleCtx->tryMoveCheckState) {
        case TRY_MOVE_STATE_CHECK_VALID_TARGET:
            battleCtx->tryMoveCheckState++;

            if (BattleControllerPlayer_HasNoTarget(battleSys, battleCtx) == TRUE) {
                return;
            }

        case TRY_MOVE_STATE_TRIGGER_REDIRECTION_ABILITIES:
            battleCtx->tryMoveCheckState++;

            if (BattleSystem_TriggerRedirectionAbilities(battleSys, battleCtx) == TRUE) {
                return;
            }

        case TRY_MOVE_STATE_CHECK_MOVE_HITS:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_ACCURACY_CHECK) == FALSE &&
                battleCtx->defender != BATTLER_NONE &&
                BattleControllerPlayer_CheckMoveHitAccuracy(battleSys,
                                                            battleCtx,
                                                            battleCtx->attacker,
                                                            battleCtx->defender,
                                                            battleCtx->moveCur) == 1) {
                return;
            }

            battleCtx->tryMoveCheckState++;

        case TRY_MOVE_STATE_CHECK_MOVE_HIT_OVERRIDES:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_ACCURACY_OVERRIDES) == FALSE &&
                battleCtx->defender != BATTLER_NONE &&
                BattleControllerPlayer_CheckMoveHitOverrides(battleSys,
                                                             battleCtx,
                                                             battleCtx->attacker,
                                                             battleCtx->defender,
                                                             battleCtx->moveCur) == 1) {
                return;
            }

            battleCtx->tryMoveCheckState++;

        case TRY_MOVE_STATE_CHECK_TYPE_CHART:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_TYPE_CHART_CHECK) == FALSE &&
                battleCtx->defender != BATTLER_NONE &&
                BattleControllerPlayer_CheckTypeChart(battleSys, battleCtx) == 1) {
                return;
            }

            battleCtx->tryMoveCheckState++;

        case TRY_MOVE_STATE_TRIGGER_IMMUNITY_ABILITIES:
            if ((battleCtx->multiHitCheckFlags & SYSCTL_SKIP_IMMUNITY_TRIGGERS) == FALSE &&
                battleCtx->defender != BATTLER_NONE &&
                BattleControllerPlayer_TriggerImmunityAbilities(battleSys, battleCtx) == 1) {
                return;
            }

            // TODO What this rule flag is: under it, Destiny Bond and Perish Song fail when the user's side has a
            // single Pokemon left.
            if ((fn_803AF43C(battleSys) & 0x10) &&
                (battleCtx->moveCur == MOVE_DESTINY_BOND || battleCtx->moveCur == MOVE_PERISH_SONG) &&
                (battleCtx->moveStatusFlags & MOVE_STATUS_DID_NOT_HIT) == FALSE &&
                (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2) == FALSE) {
                monsAlive = 0;
                party = BattleSystem_GetParty(battleSys, battleCtx->attacker & 1);

                for (i = 0; i < Party_GetCurrentCount(party); i++) {
                    mon = Party_GetPokemonBySlotIndex(party, i);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                        Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG &&
                        Pokemon_GetValue(mon, MON_DATA_HP, NULL)) {
                        monsAlive++;
                    }
                }

                if (monsAlive == 1) {
                    battleCtx->moveStatusFlags |= MOVE_STATUS_FAILED;
                }
            }

            battleCtx->tryMoveCheckState++;

        case TRY_MOVE_END: battleCtx->tryMoveCheckState = TRY_MOVE_START; break;
    }

    battleCtx->command = BATTLE_CONTROL_PRIMARY_EFFECT;
}

static void BattleControllerPlayer_PrimaryEffect(BattleSystem *battleSys, BattleContext *battleCtx) {
    int nextSeq;

    if (BattleSystem_TriggerPrimaryEffect(battleSys, battleCtx, &nextSeq) == TRUE) {
        LOAD_SUBSEQ(nextSeq);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_MOVE_FAILED;
    } else {
        battleCtx->command = BATTLE_CONTROL_MOVE_FAILED;
    }
}

static void BattleControllerPlayer_CheckMoveFailure(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->moveStatusFlags & MOVE_STATUS_NO_MORE_WORK) {
        battleCtx->command = BATTLE_CONTROL_LOOP_SPREAD_MOVES;
    } else if (battleCtx->moveStatusFlags & MOVE_STATUS_NO_PP) {
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_NO_PP);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;
    } else if (battleCtx->multiHitLoop && (battleCtx->moveStatusFlags & MOVE_STATUS_MISSED)) {
        // Thrashing moves have their own status flag.
        battleCtx->moveStatusFlags &= ~MOVE_STATUS_MISSED;
        battleCtx->moveStatusFlags |= MOVE_STATUS_MULTI_HIT_DISRUPTED;
        battleCtx->command = BATTLE_CONTROL_AFTER_MOVE_MESSAGE;
    } else if (battleCtx->moveStatusFlags & MOVE_STATUS_DID_NOT_HIT) {
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MISSED);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_LOOP_FAINTED; // crash damage can make a Pokemon faint
        lbl_8048CDE8.args[0] = battleCtx->defender;
        fn_8016FA4C(0x14, &lbl_8048CDE8);
    } else {
        battleCtx->command = BATTLE_CONTROL_USE_MOVE;
    }
}

static void BattleControllerPlayer_UseMove(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_USE_MOVE);
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    battleCtx->commandNext = BATTLE_CONTROL_UPDATE_HP;
}

// Empty in this game.
static void BattleControllerPlayer_UpdateHP(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->moveStatusFlags & MOVE_STATUS_ONE_HIT_KO) {
        battleCtx->damage = DEFENDING_MON.maxHP * -1;
    }

    if (battleCtx->damage) {
        int itemEffect = Battler_HeldItemEffect(battleCtx, battleCtx->defender);
        int itemPower = Battler_HeldItemPower(battleCtx, battleCtx->defender, ITEM_POWER_CHECK_ALL);

        // "Damage is positive" in Shift-JIS
        fn_803D989C(battleCtx->damage < 0, "\x83\x5F\x83\x81\x81\x5B\x83\x57\x82\xAA\x81\x7B\x82\xC5\x82\xB7\n");

        if (BattleSystem_GetBattlerSide(battleSys, battleCtx->attacker) ==
            BattleSystem_GetBattlerSide(battleSys, battleCtx->defender)) {
            BattleController_EmitIncrementRecord(battleSys, battleCtx->attacker, 0, RECORD_ATTACKED_ALLY);
        }

        battleCtx->lastHitByBattler[battleCtx->defender] = battleCtx->attacker;

        if ((DEFENDING_MON.statusVolatile & VOLATILE_CONDITION_SUBSTITUTE) && battleCtx->damage < 0) {
            if (DEFENDING_MON.moveEffectsData.substituteHP + battleCtx->damage <= 0) {
                ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt += DEFENDING_MON.moveEffectsData.substituteHP * -1;
                DEFENDING_MON.statusVolatile &= ~VOLATILE_CONDITION_SUBSTITUTE;
                battleCtx->hitDamage = DEFENDING_MON.moveEffectsData.substituteHP * -1;
                DEFENDING_MON.moveEffectsData.substituteHP = 0;
            } else {
                ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt += battleCtx->damage;
                DEFENDING_MON.moveEffectsData.substituteHP += battleCtx->damage;
                battleCtx->hitDamage = battleCtx->damage;
            }

            DEFENDER_SELF_TURN_FLAGS.statusFlags |= SELF_TURN_FLAG_SUBSTITUTE_HIT;
            battleCtx->msgBattlerTemp = battleCtx->defender;

            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_HIT_SUBSTITUTE);
            lbl_8048CE28._0C = battleCtx->defender;
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
            battleCtx->commandNext = BATTLE_CONTROL_AFTER_MOVE_MESSAGE;

            return;
        }

        if (CURRENT_MOVE_DATA.effect == BATTLE_EFFECT_LEAVE_WITH_1_HP && DEFENDING_MON.curHP + battleCtx->damage <= 0) {
            battleCtx->damage = (DEFENDING_MON.curHP - 1) * -1;
            lbl_8048CE28._1C = TRUE;
        }

        if (DEFENDER_TURN_FLAGS.enduring == 0) {
            if (itemEffect == HOLD_EFFECT_MAYBE_ENDURE && (LCRNG_Next() % 100) < itemPower) {
                DEFENDER_SELF_TURN_FLAGS.focusItemActivated = TRUE;
            }

            if (itemEffect == HOLD_EFFECT_ENDURE && DEFENDING_MON.curHP == DEFENDING_MON.maxHP) {
                DEFENDER_SELF_TURN_FLAGS.focusItemActivated = TRUE;
            }
        }

        if ((DEFENDER_TURN_FLAGS.enduring || DEFENDER_SELF_TURN_FLAGS.focusItemActivated) &&
            DEFENDING_MON.curHP + battleCtx->damage <= 0) {
            battleCtx->damage = (DEFENDING_MON.curHP - 1) * -1;

            if (DEFENDER_TURN_FLAGS.enduring) {
                battleCtx->moveStatusFlags |= MOVE_STATUS_ENDURED;
            } else {
                battleCtx->moveStatusFlags |= MOVE_STATUS_ENDURED_ITEM;
            }

            lbl_8048CE28._1C = TRUE;
        }

        battleCtx->storedDamage[battleCtx->defender] += battleCtx->damage;

        if (battleCtx->battleMons[battleCtx->defender].timesDamaged < 0xFF) {
            battleCtx->battleMons[battleCtx->defender].timesDamaged++;
        }

        if (CURRENT_MOVE_DATA.moveClass == CLASS_PHYSICAL) {
            DEFENDER_TURN_FLAGS.physicalDamageTakenFrom[battleCtx->attacker] = battleCtx->damage;
            DEFENDER_TURN_FLAGS.physicalDamageLastAttacker = battleCtx->attacker;
            DEFENDER_TURN_FLAGS.physicalDamageAttackerMask |= FlagIndex(battleCtx->attacker);
            DEFENDER_SELF_TURN_FLAGS.physicalDamageTaken = battleCtx->damage;
            DEFENDER_SELF_TURN_FLAGS.physicalDamageLastAttacker = battleCtx->attacker;
        } else if (CURRENT_MOVE_DATA.moveClass == CLASS_SPECIAL) {
            DEFENDER_TURN_FLAGS.specialDamageTakenFrom[battleCtx->attacker] = battleCtx->damage;
            DEFENDER_TURN_FLAGS.specialDamageLastAttacker = battleCtx->attacker;
            DEFENDER_TURN_FLAGS.specialDamageAttackerMask |= FlagIndex(battleCtx->attacker);
            DEFENDER_SELF_TURN_FLAGS.specialDamageTaken = battleCtx->damage;
            DEFENDER_SELF_TURN_FLAGS.specialDamageLastAttacker = battleCtx->attacker;
        }

        if (DEFENDING_MON.curHP + battleCtx->damage <= 0) {
            ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt += DEFENDING_MON.curHP * -1;
        } else {
            ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt += battleCtx->damage;
        }

        DEFENDER_TURN_FLAGS.lastDamageTaken = battleCtx->damage;
        DEFENDER_TURN_FLAGS.lastAttacker = battleCtx->attacker;
        battleCtx->msgBattlerTemp = battleCtx->defender;
        battleCtx->hpCalcTemp = battleCtx->damage;

        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_UPDATE_HP);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_AFTER_MOVE_MESSAGE;
        battleCtx->battleStatusMask |= SYSCTL_MOVE_HIT;
    } else {
        battleCtx->command = BATTLE_CONTROL_AFTER_MOVE_MESSAGE;
    }
}

// pokeplatinum CalcCurrentMoveType, written in line in this game.
#define CALC_CURRENT_MOVE_TYPE(moveType)                                                                               \
    if (Battler_Ability(battleCtx, battleCtx->attacker) == ABILITY_NORMALIZE) {                                        \
        moveType = TYPE_NORMAL;                                                                                        \
    } else if (battleCtx->moveType) {                                                                                  \
        moveType = battleCtx->moveType;                                                                                \
    } else {                                                                                                           \
        moveType = CURRENT_MOVE_DATA.type;                                                                             \
    }

// Unlike in Platinum, there is no Shaymin form check here.
enum AfterMoveMessageState {
    AFTER_MOVE_MESSAGE_START = 0,

    ONE_HIT_CRITICAL = 0,
    ONE_HIT_STATUS,
    ONE_HIT_TRIGGER_SECONDARY,
    ONE_HIT_RAGE,
    ONE_HIT_TRIGGER_ABILITY,
    ONE_HIT_EXTRA_FLINCH,

    MULTI_HIT_CRITICAL = 0,
    MULTI_HIT_TRIGGER_SECONDARY,
    MULTI_HIT_RAGE,
    MULTI_HIT_TRIGGER_ABILITY,
    MULTI_HIT_STATUS,
    MULTI_HIT_EXTRA_FLINCH,
};

static void BattleControllerPlayer_AfterMoveMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    switch (battleCtx->afterMoveMessageType) {
        case AFTER_MOVE_MESSAGE_ONE_HIT:
            switch (battleCtx->afterMoveMessageState) {
                case ONE_HIT_CRITICAL:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_CriticalMessage(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                case ONE_HIT_STATUS:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_FollowupMessage(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                case ONE_HIT_TRIGGER_SECONDARY:
                    int secondaryEffSeq;

                    battleCtx->afterMoveMessageState++;
                    if (BattleSystem_TriggerSecondaryEffect(battleSys, battleCtx, &secondaryEffSeq) == TRUE &&
                        (battleCtx->moveStatusFlags & MOVE_STATUS_DID_NOT_HIT) == FALSE) {
                        LOAD_SUBSEQ(secondaryEffSeq);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        return;
                    }

                case ONE_HIT_RAGE:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_RageBuilding(battleSys, battleCtx) == TRUE) {
                        lbl_8048CE28._0C = battleCtx->defender;
                        return;
                    }

                case ONE_HIT_TRIGGER_ABILITY:
                    int abilitySeq;

                    battleCtx->afterMoveMessageState++;
                    if (BattleSystem_TriggerAbilityOnHit(battleSys, battleCtx, &abilitySeq) == TRUE) {
                        LOAD_SUBSEQ(abilitySeq);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        return;
                    }

                case ONE_HIT_EXTRA_FLINCH:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_CheckExtraFlinch(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                default: break;
            }
            break;

        case AFTER_MOVE_MESSAGE_MULTI_HIT:
            switch (battleCtx->afterMoveMessageState) {
                case MULTI_HIT_CRITICAL:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_CriticalMessage(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                case MULTI_HIT_TRIGGER_SECONDARY:
                    int secondaryEffSeq;

                    battleCtx->afterMoveMessageState++;
                    if (BattleSystem_TriggerSecondaryEffect(battleSys, battleCtx, &secondaryEffSeq) == TRUE &&
                        (battleCtx->moveStatusFlags & MOVE_STATUS_DID_NOT_HIT) == FALSE) {
                        LOAD_SUBSEQ(secondaryEffSeq);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        return;
                    }

                case MULTI_HIT_RAGE:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_RageBuilding(battleSys, battleCtx) == TRUE) {
                        lbl_8048CE28._0C = battleCtx->defender;
                        return;
                    }

                case MULTI_HIT_TRIGGER_ABILITY:
                    int abilitySeq;

                    battleCtx->afterMoveMessageState++;
                    if (BattleSystem_TriggerAbilityOnHit(battleSys, battleCtx, &abilitySeq) == TRUE) {
                        LOAD_SUBSEQ(abilitySeq);
                        battleCtx->commandNext = battleCtx->command;
                        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                        return;
                    }

                case MULTI_HIT_STATUS:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_FollowupMessage(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                case MULTI_HIT_EXTRA_FLINCH:
                    battleCtx->afterMoveMessageState++;
                    if (BattleControllerPlayer_CheckExtraFlinch(battleSys, battleCtx) == TRUE) {
                        return;
                    }

                default: break;
            }
            break;
    }

    battleCtx->afterMoveMessageState = AFTER_MOVE_MESSAGE_START;
    battleCtx->command = BATTLE_CONTROL_AFTER_MOVE_EFFECT;
}

static void BattleControllerPlayer_LeftoverState29(BattleSystem *battleSys, BattleContext *battleCtx) {}

// Empty in this game.
enum AfterMoveEffectState {
    AFTER_MOVE_EFFECT_START = 0,

    AFTER_MOVE_EFFECT_TOGGLE_VANISH_FLAG = AFTER_MOVE_EFFECT_START,
    AFTER_MOVE_EFFECT_SYNCHRONIZE_STATUS,
    AFTER_MOVE_EFFECT_TRIGGER_SWITCH_IN_EFFECTS,
    AFTER_MOVE_EFFECT_ATTACKER_ITEM,
    AFTER_MOVE_EFFECT_DEFENDER_ITEM,
    AFTER_MOVE_EFFECT_TRIGGER_ITEMS_ON_HIT,
    AFTER_MOVE_EFFECT_THAW_DEFENDER,
    AFTER_MOVE_EFFECT_HELD_ITEM_STATUS,

    AFTER_MOVE_EFFECT_END,
};

static void BattleControllerPlayer_AfterMoveEffects(BattleSystem *battleSys, BattleContext *battleCtx) {
    switch (battleCtx->afterMoveEffectState) {
        case AFTER_MOVE_EFFECT_TOGGLE_VANISH_FLAG:
            BOOL anyFlipped = FALSE;
            while (battleCtx->afterMoveEffectTemp < BattleSystem_GetMaxBattlers(battleSys)) {
                if ((battleCtx->battleMons[battleCtx->afterMoveEffectTemp].moveEffectsMask &
                     MOVE_EFFECT_SEMI_INVULNERABLE) == FALSE &&
                    (battleCtx->battleMons[battleCtx->afterMoveEffectTemp].moveEffectsTemp &
                     MOVE_EFFECT_SEMI_INVULNERABLE)) {
                    battleCtx->battleMons[battleCtx->afterMoveEffectTemp].moveEffectsTemp &=
                        ~MOVE_EFFECT_SEMI_INVULNERABLE;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_VANISH_OFF);
                    battleCtx->msgBattlerTemp = battleCtx->afterMoveEffectTemp;
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                    anyFlipped = TRUE;
                }

                battleCtx->afterMoveEffectTemp++;

                if (anyFlipped) {
                    return;
                }
            }

            battleCtx->afterMoveEffectState++;
            battleCtx->afterMoveEffectTemp = 0;

        case AFTER_MOVE_EFFECT_SYNCHRONIZE_STATUS:
            battleCtx->afterMoveEffectState++;

            if (BattleSystem_SynchronizeStatus(battleSys, battleCtx, battleCtx->command) == TRUE) {
                return;
            }

        case AFTER_MOVE_EFFECT_TRIGGER_SWITCH_IN_EFFECTS:
            int switchinSeq = BattleSystem_TriggerEffectOnSwitch(battleSys, battleCtx);
            if (switchinSeq) {
                LOAD_SUBSEQ(switchinSeq);
                battleCtx->commandNext = battleCtx->command;
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                return;
            }

            battleCtx->afterMoveEffectState++;

        case AFTER_MOVE_EFFECT_ATTACKER_ITEM:
            battleCtx->afterMoveEffectState++;

            if (BattleSystem_TriggerHeldItem(battleSys, battleCtx, battleCtx->attacker) == TRUE) {
                return;
            }

        case AFTER_MOVE_EFFECT_DEFENDER_ITEM:
            battleCtx->afterMoveEffectState++;

            if (battleCtx->defender != BATTLER_NONE &&
                BattleSystem_TriggerHeldItem(battleSys, battleCtx, battleCtx->defender) == TRUE) {
                return;
            }

        case AFTER_MOVE_EFFECT_TRIGGER_ITEMS_ON_HIT:
            battleCtx->afterMoveEffectState++;

            int itemSeq;
            if (BattleSystem_TriggerHeldItemOnHit(battleSys, battleCtx, &itemSeq) == TRUE) {
                LOAD_SUBSEQ(itemSeq);
                battleCtx->commandNext = battleCtx->command;
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                return;
            }

        case AFTER_MOVE_EFFECT_THAW_DEFENDER:
            int moveType;
            CALC_CURRENT_MOVE_TYPE(moveType);
            battleCtx->afterMoveEffectState++;

            if (battleCtx->defender != BATTLER_NONE && (DEFENDING_MON.status & MON_CONDITION_FREEZE) &&
                (battleCtx->moveStatusFlags & MOVE_STATUS_MULTI_HIT_DISRUPTED) == FALSE &&
                battleCtx->defender != battleCtx->attacker &&
                (DEFENDER_SELF_TURN_FLAGS.physicalDamageTaken || DEFENDER_SELF_TURN_FLAGS.specialDamageTaken) &&
                DEFENDING_MON.curHP && moveType == TYPE_FIRE) {
                battleCtx->msgBattlerTemp = battleCtx->defender;

                LOAD_SUBSEQ(BATTLE_SUBSCRIPT_THAW_OUT);
                battleCtx->commandNext = battleCtx->command;
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                return;
            }

        case AFTER_MOVE_EFFECT_HELD_ITEM_STATUS:
            int battler;
            BOOL result = FALSE;
            int nextSeq;

            while (battleCtx->afterMoveEffectTemp < BattleSystem_GetMaxBattlers(battleSys)) {
                battler = battleCtx->monSpeedOrder[battleCtx->afterMoveEffectTemp];

                if (battleCtx->battlersSwitchingMask & FlagIndex(battler)) {
                    battleCtx->afterMoveEffectTemp++;
                    continue;
                }

                battleCtx->afterMoveEffectTemp++;

                if (BattleSystem_TriggerHeldItemOnStatus(battleSys, battleCtx, battler, &nextSeq) == TRUE) {
                    battleCtx->msgBattlerTemp = battler;

                    LOAD_SUBSEQ(nextSeq);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    result = TRUE;
                    break;
                }
            }

            if (result == FALSE) {
                battleCtx->afterMoveEffectState++;
                battleCtx->afterMoveEffectTemp = 0;
            }
            break;

        default: break;
    }

    battleCtx->afterMoveEffectState = AFTER_MOVE_EFFECT_START;
    battleCtx->afterMoveEffectTemp = 0;
    battleCtx->command = BATTLE_CONTROL_LOOP_MULTI_HIT;
}

static void BattleControllerPlayer_LeftoverState32(BattleSystem *battleSys, BattleContext *battleCtx) {}

static void BattleControllerPlayer_LoopMultiHit(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->multiHitNumHits) {
        if (battleCtx->faintedMon == BATTLER_NONE &&
            (ATTACKING_MON.status & MON_CONDITION_SLEEP) == FALSE // e.g., Effect Spore
            && (battleCtx->moveStatusFlags & MOVE_STATUS_MULTI_HIT_DISRUPTED) == FALSE) {
            if (--battleCtx->multiHitCounter) {
                battleCtx->multiHitLoop = TRUE;
                BattleSystem_SetupLoop(battleSys, battleCtx);

                battleCtx->battleStatusMask &= ~SYSCTL_PLAYED_MOVE_ANIMATION; // play the animation again
                battleCtx->multiHitCheckFlags = battleCtx->multiHitAccuracyCheck;

                BattleSystem_LoadScript(battleCtx,
                                        NARC_INDEX_BATTLE__SKILL__WAZA_SEQ,
                                        battleCtx->moveCur); // the move again
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                battleCtx->commandNext = BATTLE_CONTROL_TRY_MOVE;
            } else {
                battleCtx->msgTemp = battleCtx->multiHitNumHits;

                LOAD_SUBSEQ(BATTLE_SUBSCRIPT_HIT_X_TIMES);
                battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
                battleCtx->commandNext = BATTLE_CONTROL_LOOP_FAINTED;
                lbl_8048CE28._0C = battleCtx->defender;
            }
        } else {
            if (battleCtx->faintedMon != BATTLER_NONE || (ATTACKING_MON.status & MON_CONDITION_SLEEP)) {
                // The loop ends at once when the attacker falls asleep (e.g., Effect Spore) or the target faints.
                battleCtx->msgTemp = battleCtx->multiHitNumHits - battleCtx->multiHitCounter + 1;
            } else {
                battleCtx->msgTemp = battleCtx->multiHitNumHits - battleCtx->multiHitCounter;
            }

            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_HIT_X_TIMES);
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
            battleCtx->commandNext = BATTLE_CONTROL_LOOP_FAINTED;
            lbl_8048CE28._0C = battleCtx->defender;
        }

        BattleController_EmitClearMessageBox(battleSys);
    } else {
        battleCtx->command = BATTLE_CONTROL_LOOP_FAINTED;
    }
}

static void BattleControllerPlayer_LoopWhileFainted(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->battleStatusMask & SYSCTL_MON_FAINTED) {
        BattleControllerPlayer_AnyFainted(battleCtx, BATTLE_CONTROL_LOOP_FAINTED, BATTLE_CONTROL_LOOP_FAINTED, 0);
    } else {
        battleCtx->command = BATTLE_CONTROL_LOOP_SPREAD_MOVES;
    }
}

static void BattleControllerPlayer_LoopSpreadMoves(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (battleCtx->battleStatusMask2 & SYSCTL_MAGIC_COAT_REFLECTED) {
        battleCtx->battleStatusMask2 &= ~SYSCTL_MAGIC_COAT_REFLECTED;
        battleCtx->defender = battleCtx->attacker;
        battleCtx->attacker = battleCtx->magicCoatMon;
    }

    BattleControllerPlayer_UpdateFlagsWhenHit(battleSys, battleCtx);

    if (CURRENT_MOVE_DATA.range == RANGE_ADJACENT_OPPONENTS &&
        (battleCtx->battleStatusMask & SYSCTL_CHECK_LOOP_ONLY_ONCE) == FALSE &&
        battleCtx->battlerCounter < BattleSystem_GetMaxBattlers(battleSys)) {
        battleCtx->multiHitCheckFlags = SYSCTL_HIT_MULTIPLE_TARGETS;

        int maxBattlers = BattleSystem_GetMaxBattlers(battleSys); // unused
        BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, battleCtx->attacker);
        u8 battlerType = BattlerData_GetBattlerType(battlerData);

        do {
            int battler = battleCtx->monSpeedOrder[battleCtx->battlerCounter++];
            if ((battleCtx->battlersSwitchingMask & FlagIndex(battler)) == FALSE &&
                battleCtx->battleMons[battler].curHP) {
                battlerData = BattleSystem_GetBattlerData(battleSys, battler);

                // Loop back to the start of the move if the battlers are on opposite sides.
                if (((battlerType & BATTLER_THEM) &&
                     (BattlerData_GetBattlerType(battlerData) & BATTLER_THEM) == FALSE) ||
                    ((battlerType & BATTLER_THEM) == FALSE &&
                     (BattlerData_GetBattlerType(battlerData) & BATTLER_THEM))) {
                    BattleSystem_SetupLoop(battleSys, battleCtx);
                    battleCtx->defender = battler;
                    battleCtx->command = BATTLE_CONTROL_BEFORE_MOVE;
                    fn_8016FA4C(0x1A, NULL);
                    break;
                }
            }
        } while (battleCtx->battlerCounter < BattleSystem_GetMaxBattlers(battleSys));

        BattleController_EmitClearMessageBox(battleSys);
    } else if (CURRENT_MOVE_DATA.range == RANGE_ALL_ADJACENT &&
               (battleCtx->battleStatusMask & SYSCTL_CHECK_LOOP_ONLY_ONCE) == FALSE &&
               battleCtx->battlerCounter < BattleSystem_GetMaxBattlers(battleSys)) {
        battleCtx->multiHitCheckFlags = SYSCTL_HIT_MULTIPLE_TARGETS;
        int maxBattlers = BattleSystem_GetMaxBattlers(battleSys); // unused

        do {
            int battler = battleCtx->monSpeedOrder[battleCtx->battlerCounter++];
            if ((battleCtx->battlersSwitchingMask & FlagIndex(battler)) == FALSE &&
                battleCtx->battleMons[battler].curHP && battler != battleCtx->attacker) {
                BattleSystem_SetupLoop(battleSys, battleCtx);
                battleCtx->defender = battler;
                battleCtx->command = BATTLE_CONTROL_BEFORE_MOVE;
                fn_8016FA4C(0x1A, NULL);
                break;
            }
        } while (battleCtx->battlerCounter < BattleSystem_GetMaxBattlers(battleSys));

        BattleController_EmitClearMessageBox(battleSys);
    } else {
        battleCtx->command = BATTLE_CONTROL_FAINT_AFTER_SELFDESTRUCT;
    }
}

static void BattleControllerPlayer_FaintAfterSelfdestruct(BattleSystem *battleSys, BattleContext *battleCtx) {
    u32 selfdestructMask = battleCtx->battleStatusMask & SYSCTL_MON_SELFDESTRUCTED;

    if (selfdestructMask) {
        battleCtx->faintedMon = LowestBit(selfdestructMask >> SYSCTL_MON_SELFDESTRUCTED_SHIFT);
        battleCtx->battleStatusMask &= ~SYSCTL_MON_SELFDESTRUCTED;
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_AFTER_SELFDESTRUCT);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = BATTLE_CONTROL_TRIGGER_AFTER_HIT_EFFECTS;
    } else {
        battleCtx->command = BATTLE_CONTROL_TRIGGER_AFTER_HIT_EFFECTS;
    }
}

// Empty in this game.
enum AfterMoveHitState {
    AFTER_MOVE_HIT_START = 0,

    AFTER_MOVE_HIT_STATE_RAGE = AFTER_MOVE_HIT_START,
    AFTER_MOVE_HIT_STATE_SHELL_BELL,
    AFTER_MOVE_HIT_STATE_LIFE_ORB,

    AFTER_MOVE_HIT_STATE_END,
};

static inline BOOL BattleControllerPlayer_TriggerAfterMoveHitEffects(BattleSystem *battleSys,
                                                                     BattleContext *battleCtx) {
    int machineState = STATE_PROCESSING;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys); // unused
    int itemEffect = Battler_HeldItemEffect(battleCtx, battleCtx->attacker);
    int itemPower = Battler_HeldItemPower(battleCtx, battleCtx->attacker, ITEM_POWER_CHECK_ALL);

    if (BattleControllerPlayer_AnyFainted(battleCtx, battleCtx->command, battleCtx->command, TRUE) == TRUE) {
        return TRUE;
    }

    do {
        switch (battleCtx->afterMoveHitCheckState) {
            case AFTER_MOVE_HIT_STATE_RAGE:
                if ((ATTACKING_MON.statusVolatile & VOLATILE_CONDITION_RAGE) && battleCtx->moveCur != MOVE_RAGE) {
                    ATTACKING_MON.statusVolatile &= ~VOLATILE_CONDITION_RAGE;
                }

                battleCtx->afterMoveHitCheckState++;
                break;

            case AFTER_MOVE_HIT_STATE_SHELL_BELL:
                if (battleCtx->defender != BATTLER_NONE && itemEffect == HOLD_EFFECT_HP_RESTORE_ON_DMG &&
                    (battleCtx->battleStatusMask2 & SYSCTL_UTURN_ACTIVE) == FALSE &&
                    (battleCtx->battleStatusMask & SYSCTL_MOVE_HIT) && ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt &&
                    battleCtx->attacker != battleCtx->defender && ATTACKING_MON.curHP < ATTACKING_MON.maxHP &&
                    ATTACKING_MON.curHP) {
                    battleCtx->hpCalcTemp =
                        BattleSystem_Divide(ATTACKER_SELF_TURN_FLAGS.shellBellDamageDealt * -1, itemPower);
                    battleCtx->msgBattlerTemp = battleCtx->attacker;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_RESTORE_A_LITTLE_HP);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    machineState = STATE_BREAK_OUT;
                }

                battleCtx->afterMoveHitCheckState++;
                break;

            case AFTER_MOVE_HIT_STATE_LIFE_ORB:
                if (itemEffect == HOLD_EFFECT_HP_DRAIN_ON_ATK &&
                    Battler_Ability(battleCtx, battleCtx->attacker) != ABILITY_MAGIC_GUARD &&
                    (battleCtx->battleStatusMask2 & SYSCTL_UTURN_ACTIVE) == FALSE &&
                    (battleCtx->battleStatusMask & SYSCTL_MOVE_HIT) && CURRENT_MOVE_DATA.moveClass != CLASS_STATUS &&
                    ATTACKING_MON.curHP) {
                    battleCtx->hpCalcTemp =
                        BattleSystem_Divide(battleCtx->battleMons[battleCtx->attacker].maxHP * -1, 10);
                    battleCtx->msgBattlerTemp = battleCtx->attacker;

                    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_LOSE_HP_FROM_ITEM);
                    lbl_8048CDE8.args[0] = battleCtx->attacker;
                    lbl_8048CDE8.args[1] = 10;
                    lbl_8048CDE8.args[2] = 0;
                    lbl_8048CDE8.args[3] = HOLD_EFFECT_HP_DRAIN_ON_ATK;
                    fn_8016FA4C(0xE, &lbl_8048CDE8);
                    battleCtx->commandNext = battleCtx->command;
                    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

                    machineState = STATE_BREAK_OUT;
                }

                battleCtx->afterMoveHitCheckState++;
                break;

            case AFTER_MOVE_HIT_STATE_END:
                battleCtx->afterMoveHitCheckState = 0;
                battleCtx->afterMoveHitCheckTemp = 0;
                machineState = STATE_DONE;
                break;
        }
    } while (machineState == STATE_PROCESSING);

    return machineState == STATE_BREAK_OUT;
}

static void BattleControllerPlayer_TriggerAfterHitEffects(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (BattleControllerPlayer_TriggerAfterMoveHitEffects(battleSys, battleCtx) == TRUE) {
        return;
    }

    battleCtx->command = BATTLE_CONTROL_UPDATE_MOVE_BUFFERS;
}

static void BattleControllerPlayer_LeftoverState37(BattleSystem *battleSys, BattleContext *battleCtx) {}

static void BattleControllerPlayer_UpdateMoveBuffers(BattleSystem *battleSys, BattleContext *battleCtx) {
    u8 itemEffect = Battler_HeldItemEffect(battleCtx, battleCtx->attacker);

    if ((battleCtx->battleStatusMask & SYSCTL_FIRST_OF_MULTI_TURN) ||
        (battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN)) {
        if (itemEffect == HOLD_EFFECT_CHOICE_ATK || itemEffect == HOLD_EFFECT_CHOICE_SPEED ||
            itemEffect == HOLD_EFFECT_CHOICE_SPATK) {
            if (battleCtx->moveTemp != MOVE_STRUGGLE &&
                (battleCtx->moveTemp != MOVE_U_TURN || (battleCtx->battleStatusMask2 & SYSCTL_UTURN_ACTIVE) == FALSE) &&
                (battleCtx->moveTemp != MOVE_BATON_PASS ||
                 (battleCtx->battleStatusMask2 & SYSCTL_MOVE_SUCCEEDED) == FALSE)) {
                ATTACKING_MON.moveEffectsData.choiceLockedMove = battleCtx->moveTemp;
            }
        } else {
            ATTACKING_MON.moveEffectsData.choiceLockedMove = MOVE_NONE;
        }
    }

    if ((battleCtx->battleStatusMask & SYSCTL_REUSE_LAST_MOVE) == FALSE) {
        if (battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN) {
            battleCtx->moveProtect[battleCtx->attacker] = battleCtx->moveCur;
            battleCtx->movePrev = battleCtx->moveTemp;
        } else {
            battleCtx->moveProtect[battleCtx->attacker] = MOVE_NONE;
            battleCtx->movePrev = MOVE_NONE;
        }

        if (battleCtx->battleStatusMask2 & SYSCTL_MOVE_SUCCEEDED) {
            battleCtx->movePrevByBattler[battleCtx->attacker] = battleCtx->moveTemp;
        } else {
            battleCtx->movePrevByBattler[battleCtx->attacker] = MOVE_NONE;
        }
    }

    if (battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN) {
        battleCtx->moveSketched[battleCtx->attacker] = battleCtx->moveTemp;
    }

    BattleControllerPlayer_UpdateFlagsWhenHit(battleSys, battleCtx);
    BattleSystem_VerifyMetronomeCount(battleSys, battleCtx);

    battleCtx->command = BATTLE_CONTROL_MOVE_END;
}

static inline BOOL BattleControllerPlayer_ToggleSemiInvulnMons(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;

    while (battleCtx->vanishedCheckTemp < BattleSystem_GetMaxBattlers(battleSys)) {
        if ((battleCtx->battleMons[battleCtx->vanishedCheckTemp].moveEffectsMask & MOVE_EFFECT_SEMI_INVULNERABLE) ==
                FALSE &&
            (battleCtx->battleMons[battleCtx->vanishedCheckTemp].moveEffectsTemp & MOVE_EFFECT_SEMI_INVULNERABLE)) {
            battleCtx->battleMons[battleCtx->vanishedCheckTemp].moveEffectsTemp &= ~MOVE_EFFECT_SEMI_INVULNERABLE;

            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_VANISH_OFF);
            battleCtx->msgBattlerTemp = battleCtx->vanishedCheckTemp;
            battleCtx->commandNext = battleCtx->command;
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

            result = TRUE;
        }

        battleCtx->vanishedCheckTemp++;
        if (result == TRUE) {
            break;
        }
    }

    if (result == FALSE) {
        battleCtx->vanishedCheckTemp = 0;
    }

    return result;
}

static inline void BattleControllerPlayer_ClearFlags(BattleSystem *battleSys, BattleContext *battleCtx) {
    int i;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);

    for (i = 0; i < maxBattlers; i++) {
        battleCtx->battleMons[i].statusVolatile &= (battleCtx->clearVolatileStatus[i] ^ 0xFFFFFFFF);
        battleCtx->clearVolatileStatus[i] = VOLATILE_CONDITION_NONE;
    }

    battleCtx->moveHit[battleCtx->attacker] = MOVE_NONE;
    battleCtx->conversion2Move[battleCtx->attacker] = MOVE_NONE;
}

static void BattleControllerPlayer_MoveEnd(BattleSystem *battleSys, BattleContext *battleCtx) {
    if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_NO_MOVES) == FALSE) {
        if (BattleSystem_RecoverStatusByAbility(battleSys, battleCtx, battleCtx->attacker, FALSE) == TRUE) {
            return;
        }

        if (battleCtx->defender != BATTLER_NONE &&
            BattleSystem_RecoverStatusByAbility(battleSys, battleCtx, battleCtx->defender, FALSE) == TRUE) {
            return;
        }

        if (BattleControllerPlayer_AnyExpPayout(battleCtx, battleCtx->command, battleCtx->command) == TRUE) {
            return;
        }

        if (BattleControllerPlayer_CheckBattleOver(battleSys, battleCtx) == TRUE) {
            return;
        }

        int nextSeq = BattleSystem_TriggerEffectOnSwitch(battleSys, battleCtx);
        if (nextSeq) {
            LOAD_SUBSEQ(nextSeq);
            battleCtx->commandNext = battleCtx->command;
            battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

            return;
        }

        if (BattleControllerPlayer_ToggleSemiInvulnMons(battleSys, battleCtx) == TRUE) {
            return;
        }

        BattleControllerPlayer_ClearFlags(battleSys, battleCtx);
    }

    battleCtx->battlerActions[battleCtx->battlerActionOrder[battleCtx->turnOrderCounter]][BATTLE_ACTION_PICK_COMMAND] =
        BATTLE_CONTROL_MOVE_END;
    if (ATTACKER_SELF_TURN_FLAGS.trickRoomActivated) {
        BattleSystem_SortMonActionOrder(battleSys, battleCtx);
        BattleSystem_SortMonSpeedOrder(battleSys, battleCtx);
        battleCtx->turnOrderCounter = 0;
    } else {
        battleCtx->turnOrderCounter++;
    }

    BattleContext_Init(battleCtx);
    battleCtx->command = BATTLE_CONTROL_BRANCH_ACTIONS;
    fn_8016E2E4(2);

    // TODO What this flag of the command arguments means
    if (lbl_8048CDE8.args[15]) {
        fn_8016FA4C(6, NULL);
        lbl_8048CDE8.args[15] = 0;
    }

    fn_8016FA4C(4, NULL);
}

static void BattleControllerPlayer_CheckAnyFainted(BattleSystem *battleSys, BattleContext *battleCtx) {
    if (BattleControllerPlayer_AnyFainted(battleCtx, battleCtx->command, battleCtx->command, TRUE) != TRUE) {
        battleCtx->command = BATTLE_CONTROL_MOVE_END;
    }
}

static void BattleControllerPlayer_HandleResult(BattleSystem *battleSys, BattleContext *battleCtx) {
    battleCtx->command = BATTLE_CONTROL_FIGHT_END;
    battleCtx->battleEndFlag = TRUE;
}

static void BattleControllerPlayer_EndFight(BattleSystem *battleSys, BattleContext *battleCtx) {
    u32 battleType = BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK;

    if (battleType == FALSE) {
        Party *playerParty = BattleSystem_GetParty(battleSys, BATTLER_US);
        Pokemon_ApplyPokerus(playerParty);
        Pokemon_ValidatePokerus(playerParty);
    }

    if (battleType) {
        fn_803D9844(0);
    }

    battleCtx->command = BATTLE_CONTROL_END_WAIT;
}

// Empty in this game.
static void BattleControllerPlayer_EndWait(BattleSystem *battleSys, BattleContext *battleCtx) {}

// Unlike in Platinum, no victory music is started here. The flags from BATTLE_TYPE_FRONTIER up are ignored. When the
// last Pokemon faint together after Selfdestruct or Explosion under the rule this checks, the side that used the move
// loses.
// TODO Does not match yet: only the register allocation differs (98 %).
static BOOL BattleControllerPlayer_CheckBattleOver(BattleSystem *battleSys, BattleContext *battleCtx) {
    int i;
    u8 battleResult = 0;
    int maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int remainingHP = 0;

    for (i = 0; i < maxBattlers; i++) {
        if (((battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_AI_PARTNER ||
             (battleType & (BATTLE_TYPE_FRONTIER - 1)) == BATTLE_TYPE_TRAINER_WITH_AI_PARTNER) &&
            BattleSystem_GetBattlerSide(battleSys, i) == BATTLER_US) {
            if (BattleSystem_GetBattlerType(battleSys, i) == BATTLER_TYPE_PLAYER_SIDE_SLOT_1) {
                if (battleCtx->battleMons[i].curHP == 0) {
                    int totalPartyHP = 0;
                    Party *party = BattleSystem_GetParty(battleSys, i);
                    BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, i);

                    for (int j = 0; j < Party_GetCurrentCount(party); j++) {
                        Pokemon *mon = Party_GetPokemonBySlotIndex(party, j);

                        if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                            Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                            totalPartyHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                        }
                    }

                    remainingHP += totalPartyHP;

                    if (totalPartyHP == 0) {
                        battleResult |= BATTLE_RESULT_LOSE;
                    }
                } else {
                    remainingHP++;
                }
            }
        } else if ((battleType & BATTLE_TYPE_2vs2) ||
                   ((battleType & BATTLE_TYPE_TAG) && BattleSystem_GetBattlerSide(battleSys, i))) {
            if (battleCtx->battleMons[i].curHP == 0) {
                int totalPartyHP = 0;
                Party *party = BattleSystem_GetParty(battleSys, i);
                Party *partnerParty = BattleSystem_GetParty(battleSys, BattleSystem_GetPartner(battleSys, i));
                BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, i);

                for (int j = 0; j < Party_GetCurrentCount(party); j++) {
                    Pokemon *mon = Party_GetPokemonBySlotIndex(party, j);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                        Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                        totalPartyHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                    }
                }

                for (int j = 0; j < Party_GetCurrentCount(partnerParty); j++) {
                    Pokemon *mon = Party_GetPokemonBySlotIndex(partnerParty, j);

                    if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                        Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                        totalPartyHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                    }
                }

                remainingHP += totalPartyHP;

                if (totalPartyHP == 0) {
                    if (BattlerData_GetBattlerType(battlerData) & BATTLER_THEM) {
                        battleResult |= BATTLE_RESULT_WIN;
                    } else {
                        battleResult |= BATTLE_RESULT_LOSE;
                    }
                }
            } else {
                remainingHP++;
            }
        } else if (battleCtx->battleMons[i].curHP == 0) {
            int totalPartyHP = 0;
            Party *party = BattleSystem_GetParty(battleSys, i);
            BattlerData *battlerData = BattleSystem_GetBattlerData(battleSys, i);

            for (int j = 0; j < Party_GetCurrentCount(party); j++) {
                Pokemon *mon = Party_GetPokemonBySlotIndex(party, j);

                if (Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE &&
                    Pokemon_GetValue(mon, MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG) {
                    totalPartyHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                }
            }

            remainingHP += totalPartyHP;

            if (totalPartyHP == 0) {
                if (BattlerData_GetBattlerType(battlerData) & BATTLER_THEM) {
                    battleResult |= BATTLE_RESULT_WIN;
                } else {
                    battleResult |= BATTLE_RESULT_LOSE;
                }
            }
        } else {
            remainingHP++;
        }
    }

    if (battleResult && remainingHP == 0 && (fn_803AF43C(battleSys) & 8) &&
        (battleCtx->moveCur == MOVE_SELFDESTRUCT || battleCtx->moveCur == MOVE_EXPLOSION)) {
        battleResult = 2 - (battleCtx->attacker & 1);
    }

    if (battleResult) {
        BattleSystem_SetResultMask(battleSys, battleResult);
        fn_8016FA4C(0x17, NULL);
    }

    return battleResult != 0;
}

static BOOL
BattleControllerPlayer_AnyFainted(BattleContext *battleCtx, int nextCmd, int nextCmdNoFainted, BOOL onlyFaint) {
    int i = 0;
    int battlerBit = FlagIndex(battleCtx->monSpeedOrder[i]) << SYSCTL_MON_FAINTED_SHIFT;

    if (battleCtx->battleStatusMask & SYSCTL_MON_FAINTED) {
        while ((battleCtx->battleStatusMask & battlerBit) == FALSE) {
            i++;
            battlerBit = FlagIndex(battleCtx->monSpeedOrder[i]) << SYSCTL_MON_FAINTED_SHIFT;
        }

        battleCtx->battleStatusMask &= (battlerBit ^ 0xFFFFFFFF);
        battleCtx->faintedMon = LowestBit(battlerBit >> SYSCTL_MON_FAINTED_SHIFT);

        if (onlyFaint == TRUE) {
            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FAINT_MON);
        } else {
            LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FAINT_CHECK_DESTINY_BOND);
        }

        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = nextCmd;
        battleCtx->battlerActions[battleCtx->faintedMon][BATTLE_ACTION_PICK_COMMAND] = BATTLE_CONTROL_MOVE_END;

        return TRUE;
    }

    battleCtx->command = nextCmdNoFainted;
    return FALSE;
}

static BOOL BattleControllerPlayer_AnyExpPayout(BattleContext *battleCtx, int nextCmd, int nextCmdNoExp) {
    if (battleCtx->battleStatusMask2 & SYSCTL_PAYOUT_EXP) {
        int battler = 1 << SYSCTL_PAYOUT_EXP_SHIFT;

        while ((battleCtx->battleStatusMask2 & battler) == FALSE) {
            battler = battler << 1;
        }

        battleCtx->battleStatusMask2 &= (battler ^ 0xFFFFFFFF);
        battleCtx->faintedMon = LowestBit(battler >> SYSCTL_PAYOUT_EXP_SHIFT);
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_GRANT_EXP);
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        battleCtx->commandNext = nextCmd;

        return TRUE;
    }

    battleCtx->command = nextCmdNoExp;
    return FALSE;
}

static void BattleControllerPlayer_UpdateFlagsWhenHit(BattleSystem *battleSys, BattleContext *battleCtx) {
    int moveType;
    CALC_CURRENT_MOVE_TYPE(moveType);

    if ((MOVE_DATA(battleCtx->moveTemp).flags & MOVE_FLAG_CAN_MIRROR_MOVE) &&
        (battleCtx->battleStatusMask & SYSCTL_REUSE_LAST_MOVE) == FALSE && battleCtx->defender != BATTLER_NONE &&
        battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN) {
        battleCtx->moveCopied[battleCtx->defender] = battleCtx->moveTemp;
        battleCtx->moveCopiedHit[battleCtx->defender][battleCtx->attacker] = battleCtx->moveTemp;
    }

    if (battleCtx->defender != BATTLER_NONE) {
        u8 itemEffect = Battler_HeldItemEffect(battleCtx, battleCtx->defender);
        if (((battleCtx->battleStatusMask & SYSCTL_FIRST_OF_MULTI_TURN) ||
             (battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN)) &&
            (itemEffect != HOLD_EFFECT_CHOICE_ATK && itemEffect != HOLD_EFFECT_CHOICE_SPEED &&
             itemEffect != HOLD_EFFECT_CHOICE_SPATK)) {
            DEFENDING_MON.moveEffectsData.choiceLockedMove = MOVE_NONE;
        }

        if ((battleCtx->battleStatusMask & SYSCTL_REUSE_LAST_MOVE) == FALSE) {
            if (battleCtx->battleStatusMask2 & SYSCTL_ATTACK_MESSAGE_SHOWN) {
                battleCtx->moveHit[battleCtx->defender] = battleCtx->moveCur;
                battleCtx->moveHitBattler[battleCtx->defender] = battleCtx->attacker;
                battleCtx->moveHitType[battleCtx->defender] = moveType;
                battleCtx->movePrev = battleCtx->moveTemp;
            } else {
                battleCtx->moveHit[battleCtx->defender] = MOVE_NONE;
                battleCtx->moveHitBattler[battleCtx->defender] = BATTLER_NONE;
                battleCtx->moveHitType[battleCtx->defender] = TYPE_NORMAL;
                battleCtx->movePrev = MOVE_NONE;
            }

            if ((battleCtx->battleStatusMask2 & SYSCTL_MOVE_SUCCEEDED) &&
                (battleCtx->moveStatusFlags & MOVE_STATUS_NO_EFFECTS) == FALSE) {
                switch (CURRENT_MOVE_DATA.range) {
                    case RANGE_USER:
                    case RANGE_USER_SIDE:
                    case RANGE_FIELD:
                    case RANGE_OPPONENT_SIDE:
                    case RANGE_ALLY:
                    case RANGE_USER_OR_ALLY:
                        battleCtx->conversion2Move[battleCtx->defender] = MOVE_NONE;
                        battleCtx->conversion2Battler[battleCtx->defender] = BATTLER_NONE;
                        battleCtx->conversion2Type[battleCtx->defender] = TYPE_NORMAL;
                        break;

                    default:
                        battleCtx->conversion2Move[battleCtx->defender] = battleCtx->moveCur;
                        battleCtx->conversion2Battler[battleCtx->defender] = battleCtx->attacker;
                        battleCtx->conversion2Type[battleCtx->defender] = moveType;
                        break;
                }
            } else {
                battleCtx->conversion2Move[battleCtx->defender] = MOVE_NONE;
                battleCtx->conversion2Battler[battleCtx->defender] = BATTLER_NONE;
                battleCtx->conversion2Type[battleCtx->defender] = TYPE_NORMAL;
            }
        }
    }
}

static BOOL BattleControllerPlayer_CriticalMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    LOAD_SUBSEQ(BATTLE_SUBSCRIPT_CRITICAL_HIT);
    battleCtx->commandNext = battleCtx->command;
    battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

    return TRUE;
}

static BOOL BattleControllerPlayer_FollowupMessage(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;
    if (battleCtx->moveStatusFlags) {
        if (battleCtx->multiHitNumHits) {
            if (battleCtx->faintedMon != BATTLER_NONE || battleCtx->multiHitCounter == 1 ||
                (battleCtx->moveStatusFlags & MOVE_STATUS_MULTI_HIT_DISRUPTED)) {
                result = TRUE;
            }
        } else {
            result = TRUE;
        }
    }

    if (result == TRUE) {
        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_MOVE_FOLLOWUP_MESSAGE);
        battleCtx->commandNext = battleCtx->command;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
    }

    return result;
}

static BOOL BattleControllerPlayer_RageBuilding(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;
    if (battleCtx->defender == BATTLER_NONE) {
        return result;
    }

    if ((DEFENDING_MON.statusVolatile & VOLATILE_CONDITION_RAGE) &&
        (battleCtx->moveStatusFlags & MOVE_STATUS_MULTI_HIT_DISRUPTED) == FALSE &&
        battleCtx->defender != battleCtx->attacker && DEFENDING_MON.curHP &&
        (DEFENDER_SELF_TURN_FLAGS.physicalDamageTaken || DEFENDER_SELF_TURN_FLAGS.specialDamageTaken) &&
        DEFENDING_MON.statBoosts[BATTLE_STAT_ATTACK] < 12) {
        DEFENDING_MON.statBoosts[BATTLE_STAT_ATTACK]++;

        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_RAGE_IS_BUILDING);
        battleCtx->commandNext = battleCtx->command;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;
        result = TRUE;
    }

    return result;
}

static BOOL BattleControllerPlayer_CheckExtraFlinch(BattleSystem *battleSys, BattleContext *battleCtx) {
    BOOL result = FALSE;
    int itemEffect = Battler_HeldItemEffect(battleCtx, battleCtx->attacker);
    int itemPower = Battler_HeldItemPower(battleCtx, battleCtx->attacker, ITEM_POWER_CHECK_ALL);

    if (battleCtx->defender != BATTLER_NONE && itemEffect == HOLD_EFFECT_SOMETIMES_FLINCH &&
        (battleCtx->moveStatusFlags & MOVE_STATUS_NO_EFFECTS) == FALSE &&
        (DEFENDER_SELF_TURN_FLAGS.physicalDamageTaken || DEFENDER_SELF_TURN_FLAGS.specialDamageTaken) &&
        (LCRNG_Next() % 100) < itemPower && (CURRENT_MOVE_DATA.flags & MOVE_FLAG_TRIGGERS_KINGS_ROCK) &&
        DEFENDING_MON.curHP) {
        battleCtx->sideEffectMon = battleCtx->defender;
        battleCtx->sideEffectType = SIDE_EFFECT_TYPE_INDIRECT;

        LOAD_SUBSEQ(BATTLE_SUBSCRIPT_FLINCH_MON);
        battleCtx->commandNext = battleCtx->command;
        battleCtx->command = BATTLE_CONTROL_EXEC_SCRIPT;

        result = TRUE;
    }

    return result;
}
