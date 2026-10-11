#pragma once

#include "ds/DSbridge.hpp"
#include "ds/battle/battle_system.hpp"

enum CountAbilityMode {
    COUNT_ALL_BATTLERS_OUR_SIDE = 0,
    COUNT_ALIVE_BATTLERS_OUR_SIDE,
    COUNT_ALL_BATTLERS_THEIR_SIDE,
    COUNT_ALIVE_BATTLERS_THEIR_SIDE,
    COUNT_ALIVE_BATTLERS_THEIR_SIDE_FLAG,
    COUNT_ALL_BATTLERS,
    COUNT_ALL_BATTLERS_EXCEPT_ME,
    COUNT_ALL_BATTLERS_EXCEPT_ME_RETURN_BATTLER,
    COUNT_ALIVE_BATTLERS,
    COUNT_ALIVE_BATTLERS_EXCEPT_ME,
};

enum BattleContextParam {
    BATTLECTX_SIDE_CONDITIONS_MASK = 0,
    BATTLECTX_SIDE_MIST_TURNS,
    BATTLECTX_SELECTED_PARTY_SLOT,
    BATTLECTX_TOTAL_TURNS,
    BATTLECTX_LEVEL_UP_MONS,
    BATTLECTX_SAFARI_ESCAPE_COUNT,
    BATTLECTX_TOTAL_FAINTED_FOR,
    BATTLECTX_TOTAL_DAMAGE_FOR,
    BATTLECTX_ACTION_FOR,
    BATTLECTX_AICTX_DEFENDER,
    BATTLECTX_SWITCHING_MASK,
    BATTLECTX_AICTX_SELECTED_TARGET,
    BATTLECTX_ACTION_TEMP_FOR,
    BATTLECTX_MOVE_PROTECT_FOR,
    BATTLECTX_MOVE_PREV_FOR,
    BATTLECTX_MOVE_COPIED_FOR,
    BATTLECTX_RECYCLE_ITEM_FOR,
    BATTLECTX_MOVE_SKETCHED_FOR,
};

enum HeldItemPowerOp {
    ITEM_POWER_CHECK_ALL = 0,
    ITEM_POWER_CHECK_NONE,
    ITEM_POWER_CHECK_EMBARGO,
};

void BattleSystem_InitBattleMon(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int partySlot);
void BattleSystem_ReloadPokemon(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int partySlot);
void BattleSystem_LoadScript(BattleContext *battleCtx, int narc, int file);
void BattleSystem_CallScript(BattleContext *battleCtx, int narc, int file);
BOOL BattleSystem_PopScript(BattleContext *battleCtx);
void BattleIO_EnqueueVal(BattleContext *battleCtx, int id, int battler, int val);
void BattleIO_DequeueVal(BattleContext *battleCtx, int id, int battler, int val);
BOOL BattleIO_QueueIsEmpty(BattleContext *battleCtx);
void BattleIO_UpdateTimeout(BattleContext *battleCtx);
void BattleIO_ClearBuffer(BattleContext *battleCtx, int battler);
int BattleMon_Get(BattleContext *battleCtx, int battler, enum BattleMonParam paramID, void *buf);
void BattleMon_Set(BattleContext *battleCtx, int battler, enum BattleMonParam paramID, const void *buf);
void Battler_AddVal(BattleContext *battleCtx, int battler, enum BattleMonParam paramID, int val);
void BattleMon_AddVal(BattleMon *mon, enum BattleMonParam paramID, int val);

int fn_803BED40(BattleSystem *battleSys,
                BattleContext *battleCtx,
                int move,
                int inType,
                int attacker,
                int defender,
                int damage,
                u32 *moveStatusMask);
BOOL fn_803BFC44(BattleContext *battleCtx, int attacker, int defender, int ability);
int MapSideEffectToSubscript(BattleContext *battleCtx, int type, u32 mask);

u8 BattleSystem_CompareBattlerSpeed(
    BattleSystem *battleSys, BattleContext *battleCtx, int battler1, int battler2, BOOL ignoreQuickClaw);
void BattleSystem_ClearSideExpGain(BattleContext *battleCtx, int battler);
void BattleSystem_FlagBattlerExpGain(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_TriggerPrimaryEffect(BattleSystem *battleSys, BattleContext *battleCtx, int *effect);
BOOL BattleSystem_TriggerSecondaryEffect(BattleSystem *battleSys, BattleContext *battleCtx, int *effect);
int BattleSystem_Defender(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, u16 move, BOOL randomize, int inRange);
void BattleSystem_CheckRedirectionAbilities(BattleSystem *battleSys, BattleContext *battleCtx, int attacker, u16 move);
BOOL BattleSystem_TriggerRedirectionAbilities(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleMon_CopyToParty(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
void Battler_LockMoveChoice(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
void Battler_UnlockMoveChoice(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
int Battler_StatusCondition(BattleContext *battleCtx, int battler);
BOOL BattleSystem_CheckTrainerMessage(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleContext_Init(BattleContext *battleCtx);
void BattleContext_InitCounters(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleSystem_UpdateAfterSwitch(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
void BattleSystem_CleanupFaintedMon(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
void BattleSystem_SetupNextTurn(BattleSystem *battleSys, BattleContext *battleCtx);
int BattleSystem_CheckInvalidMoves(
    BattleSystem *battleSys, BattleContext *battleCtx, int battler, int invalidMoves, int opMask);
BOOL BattleSystem_CanUseMove(
    BattleSystem *battleSys, BattleContext *battleCtx, int battler, int moveSlot, BattleMessage *msgOut);
int Battler_SlotForMove(BattleMon *mon, u16 move);
int BattleSystem_ApplyTypeChart(BattleSystem *battleSys,
                                BattleContext *battleCtx,
                                int move,
                                int inType,
                                int attacker,
                                int defender,
                                int damage,
                                u32 *moveStatusMask);
BOOL BattleContext_MoveFailed(BattleContext *battleCtx, int battler);
u8 BattleSystem_CountAliveBattlers(BattleSystem *battleSys, BattleContext *battleCtx, BOOL sameSide, int defender);
int BattleSystem_NicknameTag(BattleContext *battleSys, int battler);
u16 Battler_SelectedMove(BattleContext *battleCtx, int battler);
int BattleSystem_CountAbility(
    BattleSystem *battleSys, BattleContext *battleCtx, enum CountAbilityMode mode, int battler, int ability);
BOOL Move_IsMultiTurn(BattleContext *battleCtx, int move);
BOOL BattleSystem_TypeMatchup(int idx, u8 *moveType, u8 *vsType, u8 *multi);
int BattleSystem_TypeMatchupMultiplier(u8 attackingType, u8 defendingType1, u8 defendingType2);
BOOL Move_IsInvoker(u16 move);
BOOL Move_IsGhostCurse(BattleContext *battleCtx, u16 move, int battler);
BOOL BattleSystem_CanStealItem(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_NotHoldingMail(BattleContext *battleCtx, int battler);
BOOL BattleSystem_CanWhirlwind(BattleContext *battleCtx);
u8 Battler_Ability(BattleContext *battleCtx, int battler);
BOOL Battler_IgnorableAbility(BattleContext *battleCtx, int attacker, int defender, int ability);
BOOL BattleSystem_AnyReplacementMons(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL Battler_IsTrappedMsg(BattleSystem *battleSys, BattleContext *battleCtx, int battler, BattleMessage *msgOut);
BOOL Battler_CanEscape(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL Battler_CheckTruant(BattleContext *battleCtx, int battler);
BOOL Move_Imprisoned(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move);
BOOL BattleSystem_AnyBattlersWithMoveEffect(BattleSystem *battleSys, BattleContext *battleCtx, int effectMask);
void BattleSystem_SetupLoop(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleSystem_SortMonSpeedOrder(BattleSystem *battleSys, BattleContext *battleCtx);
BOOL Move_FailsInHighGravity(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move);
BOOL Move_HealBlocked(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int move);
void BattleSystem_UpdateLastResort(BattleSystem *battleSys, BattleContext *battleCtx);
int Battler_CountMoves(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
int BattleSystem_TriggerImmunityAbility(BattleContext *battleCtx, int attacker, int defender);
BOOL BattleSystem_TriggerTurnEndAbility(BattleContext *battleCtx, int battler);
int BattleSystem_Divide(int dividend, int divisor);
int BattleSystem_TriggerEffectOnSwitch(BattleSystem *battleSys, BattleContext *battleCtx);
int BattleSystem_RandomOpponent(BattleSystem *battleSys, BattleContext *battleCtx, int attacker);
BOOL BattleSystem_TriggerAbilityOnHit(BattleSystem *battleSys, BattleContext *battleCtx, int *subscript);
BOOL BattleSystem_RecoverStatusByAbility(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int skipLoad);
BOOL Ability_ForbidsStatus(BattleContext *battleSys, int ability, int status);
BOOL BattleSystem_SynchronizeStatus(BattleSystem *battleSys, BattleContext *battleCtx, int controllerCommand);
BOOL BattleSystem_TriggerHeldItem(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_TriggerLeftovers(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_TriggerHeldItemOnStatus(BattleSystem *battleSys,
                                          BattleContext *battleCtx,
                                          int battler,
                                          int *subscript);
BOOL BattleSystem_TriggerDetrimentalHeldItem(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
u16 Battler_HeldItem(BattleContext *battleCtx, int battler);
BOOL Battler_MovedThisTurn(BattleContext *battleCtx, int battler);
BOOL BattleSystem_TriggerHeldItemOnHit(BattleSystem *battleSys, BattleContext *battleCtx, int *subscript);
s32 Battler_HeldItemEffect(BattleContext *battleCtx, int battler);
s32 Battler_HeldItemPower(BattleContext *battleCtx, int battler, enum HeldItemPowerOp opcode);
s32 Battler_NaturalGiftPower(BattleContext *battleCtx, int battler);
s32 Battler_NaturalGiftType(BattleContext *battleCtx, int battler);
s32 Battler_ItemPluckEffect(BattleContext *battleCtx, int battler);
s32 Battler_ItemFlingEffect(BattleContext *battleCtx, int battler);
s32 Battler_ItemFlingPower(BattleContext *battleCtx, int battler);
BOOL Battler_IsTrapped(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_PluckBerry(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
BOOL BattleSystem_FlingItem(BattleSystem *battleSys, BattleContext *battleCtx, int battler);
void BattleSystem_UpdateMetronomeCount(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleSystem_VerifyMetronomeCount(BattleSystem *battleSys, BattleContext *battleCtx);
int Battler_CryModulation(BattleContext *battleCtx, int battler, int battlerType, BOOL encounter);
BOOL Battler_CanPickCommand(BattleContext *battleSys, int battler);
u8 BattleContext_IOBufferVal(BattleContext *battleCtx, int battler);
BOOL Battler_SubstituteWasHit(BattleContext *battleCtx, int battler);
BOOL BattleSystem_PokemonIsOT(BattleSystem *battleSys, Pokemon *mon);
BOOL BattleSystem_TriggerFormChange(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleSystem_InitPartyOrder(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleSystem_SwitchSlots(BattleSystem *battleSys, BattleContext *battleCtx, int battler, int partySlot);
u32 ApplyStatStage(u8 stage, u32 stat);
int BattleSystem_CalcDamageVariance(BattleContext *battleCtx, int damage);
int BattleSystem_CalcCriticalMulti(
    BattleContext *battleCtx, int attacker, int defender, int criticalStage, u32 sideConditions);
BOOL Move_CanBeMimicked(u16 move);
BOOL Move_CanBeMetronomed(u16 move);
BOOL Move_CanBeEncored(BattleContext *battleCtx, u16 move);
BOOL Move_MeFirstCanCopy(BattleContext *battleCtx, u16 move);
s32 BattleSystem_GetItemData(BattleContext *battleCtx, u16 item, enum ItemDataParam paramID);
int BattleSystem_SideToBattler(BattleSystem *battleSys, BattleContext *battleCtx, int side);
void BattleSystem_SortMonActionOrder(BattleSystem *battleSys, BattleContext *battleCtx);
BOOL BattleSystem_ShouldShowStatusEffect(BattleContext *battleCtx, int battler, int status);
BOOL BattleSystem_TriggerHeldItemOnPivotMove(BattleSystem *battleSys, BattleContext *battleCtx, int *subscript);
void BattleSystem_DecPPForPressure(BattleContext *battleCtx, int attacker, int defender);
int BattleContext_Get(BattleSystem *battleSys, BattleContext *battleCtx, enum BattleContextParam paramID, int battler);
void BattleContext_Set(
    BattleSystem *battleSys, BattleContext *battleCtx, enum BattleContextParam paramID, int battler, int val);

// Accessors used by the game code
extern "C" {
BattleMon *fn_803C90D0(BattleContext *battleCtx, int battler);
int fn_803C90E0(void);
SideConditions *fn_803C90E8(BattleContext *battleCtx, u8 side);
MoveEffectsData *fn_803C90F8(BattleContext *battleCtx, int battler);
FieldConditions *fn_803C9108(BattleContext *battleCtx);
u8 fn_803C9110(void);
u32 fn_803C9158(void);
BOOL fn_803C9180(u32 mask);
u8 fn_803C91C0(int battler, int slot);
u8 fn_803C922C(int trainer, int slot);
u8 fn_803C92C8(u32 battleType, u8 battler);
void fn_803C9378(BattleSystem *battleSys, u8 battler, int slot, u8 value);
u8 fn_803C93C4(BattleSystem *battleSys, u8 battler, int slot);
Unk803C940C *fn_803C940C(BattleSystem *battleSys, int unused, int battler, int partySlot);
u8 *fn_803C9458(BattleSystem *battleSys, int battler);
void fn_803C9490(BattleMon *battleMon, const u16 *nickname);
}
