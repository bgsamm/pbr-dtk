#include "ds/battle/battle_display.hpp"

#include ".unsorted/8016E2B8.hpp"
#include ".unsorted/803D9EB4.hpp"
#include "ds/DSbridge.hpp"
#include "ds/battle/battle_common.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_controller.hpp"
#include "ds/battle/battle_lib.hpp"
#include "ds/battle/battle_strings.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"
#include "ds/strbuf.hpp"

#include <string.h>

// The DS animations are gone in this game: each task acknowledges its command and ends.

// Only the fields used so far (pokeplatinum MonEncounterData).
// size: 0x2C
struct MonEncounterData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0xC];
    /* 0x10 */ u8 command;
    /* 0x11 */ u8 battler;
    /* 0x12 */ u8 state;
    /* 0x13 */ u8 unk13[0x3];
    /* 0x16 */ u16 species;
    /* 0x18 */ int cryMod;
    /* 0x1C */ int battlerType;
    /* 0x20 */ u8 unk20[0xC];
};

// Only the fields used so far (pokeplatinum MonShowData).
// size: 0xA4
struct MonShowData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x84];
    /* 0x88 */ u8 command;
    /* 0x89 */ u8 battler;
    /* 0x8A */ u8 unk8A;
    /* 0x8B */ u8 state;
    /* 0x8C */ u8 unk8C[0x2];
    /* 0x8E */ u16 species;
    /* 0x90 */ u8 unk90[0x14];
};

// Only the fields used so far (pokeplatinum MonReturnData).
// size: 0x74
struct MonReturnData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ BattlerData *battlerData;
    /* 0x8 */ u32 monSprite;
    /* 0xC */ u8 unkC[0x5C];
    /* 0x68 */ u8 command;
    /* 0x69 */ u8 battler;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 state;
    /* 0x6C */ u8 yOffset;
    /* 0x6D */ u8 unk6D[0x7];
};

// Only the fields used so far (pokeplatinum OpenCaptureBallData).
// size: 0x10
struct OpenCaptureBallData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 unkA[0x6];
};

// Only the fields used so far (pokeplatinum TrainerEncounterData).
// size: 0x24
struct TrainerEncounterData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0xC];
    /* 0x10 */ u8 command;
    /* 0x11 */ u8 battler;
    /* 0x12 */ u8 state;
    /* 0x13 */ u8 unk13[0x11];
};

// Only the fields used so far (pokeplatinum TrainerThrowBallData).
// size: 0x1C
struct TrainerThrowBallData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 unkA[0x12];
};

// Only the fields used so far (pokeplatinum SlideTrainerOutData).
// size: 0x10
struct SlideTrainerOutData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 state;
    /* 0xB */ u8 unkB[0x5];
};

// Only the fields used so far (pokeplatinum SlideTrainerInData).
// size: 0x10
struct SlideTrainerInData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 state;
    /* 0xB */ u8 unkB[0x5];
};

// Only the fields used so far (pokeplatinum CommandSetData).
// size: 0x3C
struct CommandSetData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ HealthBox *healthbox;
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 state;
    /* 0xB */ s8 unused_0B;
    /* 0xC */ int input;
    /* 0x10 */ u8 ballStatus[PARTY_GAUGE_COUNT][MAX_PARTY_SIZE];
    /* 0x1C */ u8 expPercents[MAX_PARTY_SIZE];
    /* 0x22 */ u8 unk22;
    /* 0x23 */ u8 partySlot;
    /* 0x24 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x2C */ u8 curPP[LEARNED_MOVES_MAX];
    /* 0x30 */ u8 maxPP[LEARNED_MOVES_MAX];
    /* 0x34 */ u8 battlerType;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ s16 curHP;
    /* 0x38 */ u16 maxHP;
    /* 0x3A */ u8 ballStatusBattler;
    /* 0x3B */ u8 unk3B;
};

// pokeplatinum MoveSelectMenuData
// size: 0x24
struct MoveSelectMenuData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ HealthBox *healthbox;
    /* 0x8 */ int input;
    /* 0xC */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x14 */ u8 ppCur[LEARNED_MOVES_MAX];
    /* 0x18 */ u8 ppMax[LEARNED_MOVES_MAX];
    /* 0x1C */ u8 command;
    /* 0x1D */ u8 battler;
    /* 0x1E */ u8 battlerType;
    /* 0x1F */ u8 partySlot;
    /* 0x20 */ u8 state;
    /* 0x21 */ u8 unused;
    /* 0x22 */ u16 invalidMoves;
};

// pokeplatinum GiveUpMoveData
// size: 0x2
struct GiveUpMoveData {
    /* 0x0 */ u16 move;
};

// TODO What the target selection request sends to the Wii controls (see fn_8016E330).
// size: 0x10
struct Unk803AA178 {
    /* 0x0 */ u8 battlerTypes[MAX_BATTLERS];
    /* 0x4 */ u8 partySlots[MAX_BATTLERS];
    /* 0x8 */ u8 targetingLayout;
    /* 0x9 */ u8 unk9[0x7];
};

// pokeplatinum TargetSelectData, local to the target selection.
// size: 0x22
struct TargetSelectData {
    /* 0x0 */ TargetMonData targetMonData[MAX_BATTLERS];
    /* 0x20 */ u8 battlerType;
    /* 0x21 */ u8 targetingLayout;
};

// pokeplatinum TargetSelectMenuData, with the request of this game at the end.
// size: 0x44
struct TargetSelectMenuData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ HealthBox *healthbox;
    /* 0x8 */ int input;
    /* 0xC */ u8 command;
    /* 0xD */ u8 battler;
    /* 0xE */ u8 battlerType;
    /* 0xF */ u8 state;
    /* 0x10 */ TargetMonData targetMon[MAX_BATTLERS];
    /* 0x30 */ u16 range;
    /* 0x32 */ u8 shouldHidePanel;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ Unk803AA178 request;
};

// Only the fields used so far (pokeplatinum BattlePartyContext; the player party task sends it to the Wii controls).
// size: 0x28
struct BattlePartyContext {
    /* 0x0 */ Party *party;
    /* 0x4 */ BattleSystem *battleSys;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 doubleBattleFirstSelectedPartySlot;
    /* 0xA */ u8 playerPokemonPartySlot;
    /* 0xB */ u8 partnerPokemonPartySlot;
    /* 0xC */ u8 selectedPartyIndex;
    /* 0xD */ u8 unkD[0xB];
    /* 0x18 */ u16 selectedBattleBagItem;
    /* 0x1A */ u16 moveToLearn;
    /* 0x1C */ u32 battler;
    /* 0x20 */ u8 pokemonPartySlots[MAX_PARTY_SIZE];
    /* 0x26 */ u8 unk26[0x2];
};

// Only the fields used so far (pokeplatinum PartyMenuData).
// size: 0x34
struct PartyMenuData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ BattlePartyContext *battlePartyCtx;
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 state;
    /* 0xB */ u8 listMode;
    /* 0xC */ u8 partySlots[MAX_BATTLERS];
    /* 0x10 */ int canSwitch;
    /* 0x14 */ u16 selectedBattleBagItem;
    /* 0x16 */ u8 doublesSelection;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 battlersSwitchingMask;
    /* 0x19 */ u8 unk19[0x3];
    /* 0x1C */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
};

// Only the fields used so far (pokeplatinum BagMenuData).
// size: 0x34
struct BagMenuData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ PartyMenuData *partyMenuData;
    /* 0xC */ u8 command;
    /* 0xD */ u8 battler;
    /* 0xE */ u8 state;
    /* 0xF */ u8 battlerType;
    /* 0x10 */ u8 unk10[0x4];
    /* 0x14 */ u8 hasTwoOpponents;
    /* 0x15 */ u8 semiInvulnerable;
    /* 0x16 */ u8 substitute;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x30 */ u8 embargoTurns[MAX_BATTLERS];
};

// pokeplatinum YesNoMenuData
// size: 0x1C
struct YesNoMenuData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ HealthBox *healthbox;
    /* 0x8 */ int input;
    /* 0xC */ u8 command;
    /* 0xD */ u8 battler;
    /* 0xE */ u8 state;
    /* 0xF */ u8 yesNoType;
    /* 0x10 */ int promptMsg;
    /* 0x14 */ int nickname;
    /* 0x18 */ u16 move;
    /* 0x1A */ u16 msgIdx;
};

// pokeplatinum BattleMessageWaitTask
// size: 0x8
struct BattleMessageWaitTask {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 command;
    /* 0x5 */ u8 battler;
    /* 0x6 */ u8 msgIdx;
};

// Only the fields used so far (pokeplatinum SetMoveAnimationData).
// size: 0x70
struct SetMoveAnimationData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0xC];
    /* 0x10 */ MoveAnimation moveAnim;
    /* 0x68 */ u8 command;
    /* 0x69 */ u8 battler;
    /* 0x6A */ u8 state;
    /* 0x6B */ u8 unk6B[0x5];
};

// Only the fields used so far (pokeplatinum FlickerBattlerData).
// size: 0xC
struct FlickerBattlerData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 battler;
    /* 0x9 */ u8 unk9[0x3];
};

// Only the fields used so far (pokeplatinum FaintingSequenceData).
// size: 0x74
struct FaintingSequenceData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x60];
    /* 0x64 */ u8 command;
    /* 0x65 */ u8 battler;
    /* 0x66 */ u8 state;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ u16 species;
    /* 0x6A */ u8 unk6A[0xA];
};

// Only the fields used so far (pokeplatinum FadeOutData).
// size: 0x8
struct FadeOutData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 command;
    /* 0x5 */ u8 battler;
    /* 0x6 */ u8 state;
    /* 0x7 */ u8 unk7;
};

// Only the fields used so far (pokeplatinum ToggleVanishData).
// size: 0x68
struct ToggleVanishData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x5C];
    /* 0x60 */ u8 command;
    /* 0x61 */ u8 battler;
    /* 0x62 */ u8 unk62[0x6];
};

// Only the fields used so far (pokeplatinum PlayLevelUpAnimationData).
// size: 0xC
struct PlayLevelUpAnimationData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 unkA[0x2];
};

// Only the fields used so far (pokeplatinum AlertMsgData).
// size: 0xC
struct AlertMsgData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 command;
    /* 0x5 */ u8 battler;
    /* 0x6 */ u8 msgIdx;
    /* 0x7 */ u8 state;
    /* 0x8 */ u8 unk8[0x4];
};

// Only the fields used so far (pokeplatinum ForgetMoveData).
// size: 0x10
struct ForgetMoveData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 state;
    /* 0xB */ u8 unkB;
    /* 0xC */ u16 move;
    /* 0xE */ u8 slot;
    /* 0xF */ u8 unkF;
};

// Only the fields used so far (pokeplatinum SetMosaicData).
// size: 0x10
struct SetMosaicData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ u8 command;
    /* 0x9 */ u8 battler;
    /* 0xA */ u8 unkA[0x6];
};

// Only the fields used so far (pokeplatinum PartyGaugeTask).
// size: 0x10
struct PartyGaugeTask {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 command;
    /* 0x5 */ u8 battler;
    /* 0x6 */ u8 unk6[0xA];
};

// Only the fields used so far (pokeplatinum SpriteToOAMData).
// size: 0x10
struct SpriteToOAMData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x8];
    /* 0xC */ u8 command;
    /* 0xD */ u8 battler;
    /* 0xE */ u8 unkE[0x2];
};

// Only the fields used so far (pokeplatinum OAMToSpriteData).
struct OAMToSpriteData {
    /* 0x0 */ BattleSystem *battleSys;
    /* 0x4 */ u8 unk4[0x8];
    /* 0xC */ u8 command;
    /* 0xD */ u8 battler;
};

// TODO What the move selection request sends to the Wii controls (see fn_8016E330).
// size: 0x18
struct Unk8063D080 {
    /* 0x0 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x8 */ u8 ppCur[LEARNED_MOVES_MAX];
    /* 0xC */ u8 ppMax[LEARNED_MOVES_MAX];
    /* 0x10 */ u16 partySlot;
    /* 0x12 */ u8 unk12[0x6];
};

/* lbl_8063D080 */ static Unk8063D080 sUnk8063D080;

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
void fn_8016E394(u8 battler, BattleMessage *battleMsg, const u16 *text, u32 size);
void fn_8016E330(int request, u8 battler, int defaultChoice, void *data);
u32 fn_8016E478(u8 battler);
void fn_8017C9E0(BattleSystem *battleSys, int battler);
u8 fn_8017CB14(BattleSystem *battleSys, int battler);
}

static void Task_SetEncounter(Unk8063D230 *task, void *data);
static void Task_ShowEncounter(Unk8063D230 *task, void *data);
static void Task_ShowPokemon(Unk8063D230 *task, void *data);
static void Task_ReturnPokemon(Unk8063D230 *task, void *data);
static void Task_OpenCaptureBall(Unk8063D230 *task, void *data);
static void Task_SetTrainerEncounter(Unk8063D230 *task, void *data);
static void Task_ThrowTrainerBall(Unk8063D230 *task, void *data);
static void Task_SlideTrainerOut(Unk8063D230 *task, void *data);
static void Task_SlideTrainerIn(Unk8063D230 *task, void *data);
static void Task_SlideHealthBoxIn(Unk8063D230 *task, void *data);
static void Task_SlideHealthBoxOut(Unk8063D230 *task, void *data);
static void Task_SetMoveAnimation(Unk8063D230 *task, void *data);
static void Task_FlickerBattler(Unk8063D230 *task, void *data);
static void Task_UpdateHPGauge(Unk8063D230 *task, void *data);
static void Task_UpdateExpGauge(Unk8063D230 *task, void *data);
static void Task_PlayFaintingSequence(Unk8063D230 *task, void *data);
static void Task_FadeOut(Unk8063D230 *task, void *data);
static void Task_ToggleVanish(Unk8063D230 *task, void *data);
static void Task_PlayLevelUpAnimation(Unk8063D230 *task, void *data);
static void Task_WaitForBattleMessagePrint(Unk8063D230 *task, void *data);
static void Task_WaitForAlertMessagePrint(Unk8063D230 *task, void *data);
static void SysTask_SetupUI(Unk8063D230 *task, void *data);
static void Task_ForgetMove(Unk8063D230 *task, void *data);
static void Task_SetMosaic(Unk8063D230 *task, void *data);
static void Task_ShowPartyGauge(Unk8063D230 *task, void *data);
static void Task_HidePartyGauge(Unk8063D230 *task, void *data);
static void Task_SpriteToOAM(Unk8063D230 *task, void *data);
static void Task_OAMToSprite(Unk8063D230 *task, void *data);

static inline void LoadRecallMessage(BattleSystem *battleSys,
                                     BattlerData *battlerData,
                                     RecallMsgMessage *message,
                                     BattleMessage *battleMsg) {
    if (battlerData->battlerType & BATTLER_THEM) {
        if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) {
            battleMsg->id = BATTLE_STRING_LINK_TR_WITHDREW_POKEMON;
            battleMsg->tags = TAG_TRNAME_NICKNAME;
            battleMsg->params[0] = battlerData->battler;
            battleMsg->params[1] = battlerData->battler | (message->partySlot << 8);
        } else {
            battleMsg->id = BATTLE_STRING_TR_WITHDREW_POKEMON;
            battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME;
            battleMsg->params[0] = battlerData->battler;
            battleMsg->params[1] = battlerData->battler;
            battleMsg->params[2] = battlerData->battler | (message->partySlot << 8);
        }
    } else {
        if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) == FALSE &&
            (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) == FALSE) {
            if (message->hpPercent == 0) {
                battleMsg->id = BATTLE_STRING_POKEMON_SWITCH_OUT_COME_BACK;
            } else if (message->hpPercent < 25) {
                battleMsg->id = BATTLE_STRING_POKEMON_COME_BACK;
            } else if (message->hpPercent < 50) {
                battleMsg->id = BATTLE_STRING_POKEMON_GOOD_COME_BACK;
            } else if (message->hpPercent < 75) {
                battleMsg->id = BATTLE_STRING_POKEMON_OK_COME_BACK;
            } else {
                battleMsg->id = BATTLE_STRING_POKEMON_ENOUGH_GET_BACK;
            }
        } else {
            battleMsg->id = BATTLE_STRING_POKEMON_COME_BACK;
        }

        battleMsg->tags = TAG_NICKNAME;
        battleMsg->params[0] = battlerData->battler | (message->partySlot << 8);
    }
}

static inline void LoadSendOutMessage(BattleSystem *battleSys,
                                      BattlerData *battlerData,
                                      SendOutMsgMessage *message,
                                      BattleMessage *battleMsg) {
    if (battlerData->battlerType & BATTLER_THEM) {
        if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) == FALSE) {
            battleMsg->id = BATTLE_STRING_TR_SENT_OUT_POKEMON;
            battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME;
            battleMsg->params[0] = battlerData->battler;
            battleMsg->params[1] = battlerData->battler;
            battleMsg->params[2] = battlerData->battler | (message->partySlot << 8);
        } else {
            battleMsg->id = BATTLE_STRING_LINK_TR_SENT_OUT_POKEMON;
            battleMsg->tags = TAG_TRNAME_NICKNAME;
            battleMsg->params[0] = battlerData->battler;
            battleMsg->params[1] = battlerData->battler | (message->partySlot << 8);
        }
    } else {
        if ((BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) == FALSE &&
            (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) == FALSE) {
            if (message->hpPercent < 100) {
                battleMsg->id = BATTLE_STRING_YOUR_FOES_WEAK_GET_EM_POKEMON;
            } else if (message->hpPercent < 325) {
                battleMsg->id = BATTLE_STRING_JUST_A_LITTLE_MORE_HANG_IN_THERE_POKEMON;
            } else if (message->hpPercent < 550) {
                battleMsg->id = BATTLE_STRING_GO_FOR_IT_POKEMON;
            } else if (message->hpPercent < 775) {
                battleMsg->id = BATTLE_STRING_YOURE_IN_CHARGE_POKEMON;
            } else {
                battleMsg->id = BATTLE_STRING_GO_POKEMON;
            }
        } else {
            battleMsg->id = BATTLE_STRING_GO_POKEMON;
        }

        battleMsg->tags = TAG_NICKNAME;
        battleMsg->params[0] = battlerData->battler | (message->partySlot << 8);
    }
}

static inline void LoadBattleStartMessage(BattleSystem *battleSys, BattlerData *unused, BattleMessage *battleMsg) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int battler1;
    int battler2;

    if (battleType & BATTLE_TYPE_DOUBLES) {
        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_1);
        battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_2);
    } else {
        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_SOLO_ENEMY);
        battler2 = battler1;
    }

    if (battleType & BATTLE_TYPE_LINK) {
        if (battleType & BATTLE_TYPE_FRONTIER) {
            battleMsg->id = BATTLE_STRING_YOU_ARE_CHALLENGED_BY_TR1_AND_TR2;
            battleMsg->tags = TAG_TRCLASS_TRNAME_TRCLASS_TRNAME;
            battleMsg->params[0] = battler1;
            battleMsg->params[1] = battler1;
            battleMsg->params[2] = battler2;
            battleMsg->params[3] = battler2;
        } else if (battleType & BATTLE_TYPE_2vs2) {
            battleMsg->id = BATTLE_STRING_YOU_ARE_CHALLENGED_BY_LINK_TR1_AND_LINK_TR2;
            battleMsg->tags = TAG_TRNAME_TRNAME;
            battleMsg->params[0] = battler1;
            battleMsg->params[1] = battler2;
        } else {
            battleMsg->id = BATTLE_STRING_YOU_ARE_CHALLENGED_BY_LINK_TR;
            battleMsg->tags = TAG_TRNAME;
            battleMsg->params[0] = battler1;
        }
    } else {
        if (battleType & BATTLE_TYPE_TAG || battleType & BATTLE_TYPE_2vs2) {
            battleMsg->id = BATTLE_STRING_YOU_ARE_CHALLENGED_BY_TR1_AND_TR2;
            battleMsg->tags = TAG_TRCLASS_TRNAME_TRCLASS_TRNAME;
            battleMsg->params[0] = battler1;
            battleMsg->params[1] = battler1;
            battleMsg->params[2] = battler2;
            battleMsg->params[3] = battler2;
        } else {
            battleMsg->id = BATTLE_STRING_YOU_ARE_CHALLENGED_BY_TR;
            battleMsg->tags = TAG_TRCLASS_TRNAME;
            battleMsg->params[0] = battler1;
            battleMsg->params[1] = battler1;
        }
    }
}

static inline void LoadLeadMonMessage(BattleSystem *battleSys,
                                      BattlerData *battlerData,
                                      LeadMonMsgMessage *message,
                                      BattleMessage *battleMsg) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int battler1;
    int battler2;

    if (battlerData->battlerType & BATTLER_THEM) {
        if (battleType & BATTLE_TYPE_DOUBLES) {
            battler1 = battlerData->battler;
            battler2 = BattleSystem_GetPartner(battleSys, battlerData->battler);
        } else {
            battler1 = battlerData->battler;
            battler2 = battler1;
        }

        if (battleType & BATTLE_TYPE_LINK) {
            if (battleType & BATTLE_TYPE_FRONTIER) {
                battleMsg->id = BATTLE_STRING_TR1_SENT_OUT_POKEMON1_TR2_SENT_OUT_POKEMON2;
                battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME_TRCLASS_TRNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1;
                battleMsg->params[2] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[3] = battler2;
                battleMsg->params[4] = battler2;
                battleMsg->params[5] = battler2 | (message->partySlot[battler2] << 8);
            } else if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_LINK_TR1_SENT_OUT_POKEMON1_LINK_TR2_SENT_OUT_POKEMON2;
                battleMsg->tags = TAG_TRNAME_NICKNAME_TRNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[2] = battler2;
                battleMsg->params[3] = battler2 | (message->partySlot[battler2] << 8);
            } else if (battleType & BATTLE_TYPE_DOUBLES) {
                battleMsg->id = BATTLE_STRING_LINK_TR_SENT_OUT_POKEMON1_AND_POKEMON2;
                battleMsg->tags = TAG_TRNAME_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[2] = battler2 | (message->partySlot[battler2] << 8);
            } else {
                battleMsg->id = BATTLE_STRING_LINK_TR_SENT_OUT_POKEMON;
                battleMsg->tags = TAG_TRNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1 | (message->partySlot[battler1] << 8);
            }
        } else {
            if (battleType & BATTLE_TYPE_TAG || battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_TR1_SENT_OUT_POKEMON1_TR2_SENT_OUT_POKEMON2;
                battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME_TRCLASS_TRNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1;
                battleMsg->params[2] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[3] = battler2;
                battleMsg->params[4] = battler2;
                battleMsg->params[5] = battler2 | (message->partySlot[battler2] << 8);
            } else if (battleType & BATTLE_TYPE_DOUBLES) {
                battleMsg->id = BATTLE_STRING_TR_SENT_OUT_POKEMON1_AND_POKEMON2;
                battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1;
                battleMsg->params[2] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[3] = battler2 | (message->partySlot[battler2] << 8);
            } else {
                battleMsg->id = BATTLE_STRING_TR_SENT_OUT_POKEMON;
                battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1;
                battleMsg->params[2] = battler1 | (message->partySlot[battler1] << 8);
            }
        }
    } else {
        if (battleType & BATTLE_TYPE_LINK) {
            u8 networkID = fn_803D9848();

            if (battleType & BATTLE_TYPE_2vs2) {
                switch (fn_803D983C(networkID)) {
                    case 0:
                    case 3:
                        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
                        battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
                        break;
                    case 1:
                    case 2:
                        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
                        battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
                        break;
                }
            } else if (battleType & BATTLE_TYPE_DOUBLES) {
                battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
                battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
            } else {
                battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_SOLO_PLAYER);
                battler2 = battler1;
            }
        } else if (battleType & BATTLE_TYPE_2vs2) {
            battler1 = BattleSystem_GetPartner(battleSys, battlerData->battler);
            battler2 = battlerData->battler;
        } else if (battleType & BATTLE_TYPE_DOUBLES) {
            battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
            battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
        } else {
            battler1 = battlerData->battler;
            battler2 = battler1;
        }

        if (battleType & BATTLE_TYPE_LINK) {
            if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_LINK_TR_SENT_OUT_POKEMON1_GO_POKEMON2;
                battleMsg->tags = TAG_TRNAME_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[2] = battler2 | (message->partySlot[battler2] << 8);
            } else if (battleType & BATTLE_TYPE_DOUBLES) {
                battleMsg->id = BATTLE_STRING_GO_POKEMON1_AND_POKEMON2;
                battleMsg->tags = TAG_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[1] = battler2 | (message->partySlot[battler2] << 8);
            } else {
                battleMsg->id = BATTLE_STRING_GO_POKEMON;
                battleMsg->tags = TAG_NICKNAME;
                battleMsg->params[0] = battler1 | (message->partySlot[battler1] << 8);
            }
        } else {
            if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_TR_SENT_OUT_POKEMON1_GO_POKEMON2;
                battleMsg->tags = TAG_TRCLASS_TRNAME_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler1;
                battleMsg->params[2] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[3] = battler2 | (message->partySlot[battler2] << 8);
            } else if (battleType & BATTLE_TYPE_DOUBLES) {
                battleMsg->id = BATTLE_STRING_GO_POKEMON1_AND_POKEMON2;
                battleMsg->tags = TAG_NICKNAME_NICKNAME;
                battleMsg->params[0] = battler1 | (message->partySlot[battler1] << 8);
                battleMsg->params[1] = battler2 | (message->partySlot[battler2] << 8);
            } else {
                battleMsg->id = BATTLE_STRING_GO_POKEMON;
                battleMsg->tags = TAG_NICKNAME;
                battleMsg->params[0] = battler1 | (message->partySlot[battler1] << 8);
            }
        }
    }
}

static inline void LoadResultMessage(BattleSystem *battleSys, BattlerData *battlerData, BattleMessage *battleMsg) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);
    int battler1;
    int battler2;
    int battleResultMask = fn_803ADCD8(battleSys);

    if (battleType & BATTLE_TYPE_DOUBLES) {
        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_1);
        battler2 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_2);
    } else {
        battler1 = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_SOLO_ENEMY);
        battler2 = battler1;
    }

    switch (battleResultMask) {
        case BATTLE_RESULT_WIN:
            if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_PLAYER_DEFEATED_LINK_TR1_AND_LINK_TR2;
                battleMsg->tags = TAG_TRNAME_TRNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler2;
            } else {
                battleMsg->id = BATTLE_STRING_PLAYER_DEFEATED_LINK_TR;
                battleMsg->tags = TAG_TRNAME;
                battleMsg->params[0] = battler1;
            }
            break;
        case BATTLE_RESULT_LOSE:
            if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_PLAYER_LOST_AGAINST_LINK_TR1_AND_LINK_TR2;
                battleMsg->tags = TAG_TRNAME_TRNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler2;
            } else {
                battleMsg->id = BATTLE_STRING_PLAYER_LOST_AGAINST_LINK_TR;
                battleMsg->tags = TAG_TRNAME;
                battleMsg->params[0] = battler1;
            }
            break;
        case BATTLE_RESULT_DRAW:
            if (battleType & BATTLE_TYPE_2vs2) {
                battleMsg->id = BATTLE_STRING_PLAYER_DREW_AGAINST_LINK_TR1_AND_LINK_TR2;
                battleMsg->tags = TAG_TRNAME_TRNAME;
                battleMsg->params[0] = battler1;
                battleMsg->params[1] = battler2;
            } else {
                battleMsg->id = BATTLE_STRING_PLAYER_DREW_AGAINST_LINK_TR;
                battleMsg->tags = TAG_TRNAME;
                battleMsg->params[0] = battler1;
            }
            break;
    }
}

// The escape message is not printed in this game: only the result mask and the calls that filled the message remain.
static inline void LoadEscapeMessage(BattleSystem *battleSys, BattlerData *battlerData, EscapeMsgMessage *message) {
    int i;
    int playerMonCount = 0;
    int enemyMonCount = 0;

    for (i = 0; i < BattleSystem_GetMaxBattlers(battleSys); i++) {
        if (message->escaperBitmask & FlagIndex(i)) {
            if (BattleSystem_GetBattlerSide(battleSys, i)) {
                enemyMonCount++;
            } else {
                playerMonCount++;
            }
        }
    }

    if (playerMonCount && enemyMonCount) {
        BattleSystem_SetResultMask(battleSys,
                                   BATTLE_RESULT_DRAW | BATTLE_RESULT_TRY_FLEE | BATTLE_RESULT_TRY_FLEE_WAIT);
    } else if (playerMonCount) {
        BattleSystem_SetResultMask(battleSys,
                                   BATTLE_RESULT_LOSE | BATTLE_RESULT_TRY_FLEE | BATTLE_RESULT_TRY_FLEE_WAIT);
    } else {
        if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_2vs2) {
            BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_1);
            BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_2);
        } else if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_DOUBLES) {
            BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_ENEMY_SIDE_SLOT_1);
        } else {
            BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_SOLO_ENEMY);
        }

        BattleSystem_SetResultMask(battleSys, BATTLE_RESULT_WIN | BATTLE_RESULT_TRY_FLEE | BATTLE_RESULT_TRY_FLEE_WAIT);
    }
}

static inline void LoadForfeitMessage(BattleSystem *battleSys, BattlerData *battlerData, BattleMessage *battleMsg) {
    battleMsg->id = BATTLE_STRING_PLAYER_FORFEITED_THE_MATCH;
    battleMsg->tags = TAG_TRNAME;

    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_LINK) {
        if (fn_803D983C(fn_803D9848())) {
            battleMsg->params[0] = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_2);
        } else {
            battleMsg->params[0] = BattleSystem_GetBattlerOfType(battleSys, BATTLER_TYPE_PLAYER_SIDE_SLOT_1);
        }
    } else {
        battleMsg->params[0] = battlerData->battler;
    }

    BattleSystem_SetResultMask(battleSys, BATTLE_RESULT_LOSE | BATTLE_RESULT_TRY_FLEE | BATTLE_RESULT_TRY_FLEE_WAIT);
}

void BattleDisplay_InitTaskSetupUI(void) {
    fn_803DEF00(SysTask_SetupUI, NULL, 0);
}

void BattleDisplay_InitTaskSetEncounter(BattleSystem *battleSys,
                                        BattlerData *battlerData,
                                        MonEncounterMessage *message) {
    MonEncounterData *monEncounterData = (MonEncounterData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(MonEncounterData));

    monEncounterData->state = 0;
    monEncounterData->battleSys = battleSys;
    monEncounterData->command = message->command;
    monEncounterData->battler = battlerData->battler;
    monEncounterData->species = message->species;
    monEncounterData->cryMod = message->cryModulation;
    monEncounterData->battlerType = battlerData->battlerType;

    fn_803DEF00(Task_SetEncounter, monEncounterData, 0);
}

void BattleDisplay_InitTaskShowEncounter(BattleSystem *battleSys, BattlerData *battlerData, MonShowMessage *message) {
    MonShowData *monShowData = (MonShowData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(MonShowData));

    monShowData->command = message->command;
    monShowData->battler = battlerData->battler;
    monShowData->battleSys = battleSys;

    fn_803DEF00(Task_ShowEncounter, monShowData, 0);
}

void BattleDisplay_InitTaskShowPokemon(BattleSystem *battleSys, BattlerData *battlerData, MonShowMessage *message) {
    MonShowData *monShowData = (MonShowData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(MonShowData));

    monShowData->state = 0;
    monShowData->battleSys = battleSys;
    monShowData->command = message->command;
    monShowData->battler = battlerData->battler;
    monShowData->species = message->species;

    fn_803DEF00(Task_ShowPokemon, monShowData, 0);
}

void BattleDisplay_InitTaskReturnPokemon(BattleSystem *battleSys, BattlerData *battlerData, MonReturnMessage *message) {
    MonReturnData *monReturnData = (MonReturnData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(MonReturnData));

    monReturnData->battleSys = battleSys;
    monReturnData->command = message->command;
    monReturnData->battler = battlerData->battler;
    monReturnData->battlerData = battlerData;
    monReturnData->monSprite = battlerData->monSprite;
    monReturnData->state = 0;
    monReturnData->yOffset = message->yOffset;

    fn_803DEF00(Task_ReturnPokemon, monReturnData, 0);
}

void BattleDisplay_InitTaskOpenCaptureBall(BattleSystem *battleSys,
                                           BattlerData *battlerData,
                                           OpenCaptureBallMessage *message) {
    OpenCaptureBallData *openCaptureBallData =
        (OpenCaptureBallData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(OpenCaptureBallData));

    openCaptureBallData->battleSys = battleSys;
    openCaptureBallData->command = message->command;
    openCaptureBallData->battler = battlerData->battler;

    fn_803DEF00(Task_OpenCaptureBall, openCaptureBallData, 0);
}

void BattleDisplay_InitTaskSetTrainerEncounter(BattleSystem *battleSys,
                                               BattlerData *battlerData,
                                               TrainerEncounterMessage *message) {
    TrainerEncounterData *trainerEncounterData =
        (TrainerEncounterData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(TrainerEncounterData));

    trainerEncounterData->battleSys = battleSys;
    trainerEncounterData->command = message->command;
    trainerEncounterData->battler = battlerData->battler;
    trainerEncounterData->state = 0;

    fn_803DEF00(Task_SetTrainerEncounter, trainerEncounterData, 0);
}

void BattleDisplay_InitTaskThrowTrainerBall(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            TrainerThrowBallMessage *message) {
    TrainerThrowBallData *trainerThrowBallData =
        (TrainerThrowBallData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(TrainerThrowBallData));

    trainerThrowBallData->battleSys = battleSys;
    trainerThrowBallData->command = message->command;
    trainerThrowBallData->battler = battlerData->battler;

    fn_803DEF00(Task_ThrowTrainerBall, trainerThrowBallData, 0);
}

void BattleDisplay_InitTaskSlideTrainerOut(BattleSystem *battleSys, BattlerData *battlerData) {
    SlideTrainerOutData *slideTrainerOutData =
        (SlideTrainerOutData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(SlideTrainerOutData));

    slideTrainerOutData->state = 0;
    slideTrainerOutData->battleSys = battleSys;
    slideTrainerOutData->command = battlerData->data[0];
    slideTrainerOutData->battler = battlerData->battler;

    fn_803DEF00(Task_SlideTrainerOut, slideTrainerOutData, 0);
}

void BattleDisplay_InitTaskSlideTrainerIn(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          TrainerSlideInMessage *message) {
    SlideTrainerInData *slideTrainerInData =
        (SlideTrainerInData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(SlideTrainerInData));

    slideTrainerInData->state = 0;
    slideTrainerInData->battleSys = battleSys;
    slideTrainerInData->command = message->command;
    slideTrainerInData->battler = battlerData->battler;

    fn_803DEF00(Task_SlideTrainerIn, slideTrainerInData, 0);
}

void BattleDisplay_InitTaskSlideHealthBoxIn(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            HealthBoxData *healthboxData) {
    HealthBox *healthbox = &battlerData->healthbox;
    memset(&healthbox->state, 0, sizeof(u8));

    healthbox->battleSys = battleSys;
    healthbox->battler = battlerData->battler;
    healthbox->command = healthboxData->command;

    fn_803DEF00(Task_SlideHealthBoxIn, healthbox, 1000);
}

void BattleDisplay_InitTaskSlideHealthBoxOut(BattleSystem *battleSys, BattlerData *battlerData) {
    HealthBox *healthbox = &battlerData->healthbox;
    memset(&healthbox->state, 0, sizeof(u8));

    healthbox->battleSys = battleSys;
    healthbox->battler = battlerData->battler;
    healthbox->command = battlerData->data[0];

    healthbox->task_10 = fn_803DEF00(Task_SlideHealthBoxOut, healthbox, 1000);
}

void BattleDisplay_InitTaskSetCommandSelection(BattleSystem *battleSys,
                                               BattlerData *battlerData,
                                               CommandSetMessage *message) {
    CommandSetData *commandSetData = (CommandSetData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(CommandSetData));
    int i;
    memset(commandSetData, 0, sizeof(CommandSetData));

    commandSetData->state = 0;
    commandSetData->unused_0B = 0;
    commandSetData->battleSys = battleSys;
    commandSetData->command = message->command;
    commandSetData->battler = battlerData->battler;
    commandSetData->battlerType = battlerData->battlerType;
    commandSetData->healthbox = &battlerData->healthbox;
    commandSetData->partySlot = message->partySlot;
    commandSetData->curHP = message->curHP;
    commandSetData->maxHP = message->maxHP;
    commandSetData->ballStatusBattler = message->ballStatusBattler;

    for (i = 0; i < PARTY_GAUGE_COUNT; i++) {
        for (int j = 0; j < MAX_PARTY_SIZE; j++) {
            commandSetData->ballStatus[i][j] = message->ballStatus[i][j];
        }
    }

    for (i = 0; i < MAX_PARTY_SIZE; i++) {
        if (message->ballStatus[0][i] == STOCK_STATUS_MON_FAINTED) {
            commandSetData->expPercents[i] = 0;
        } else {
            commandSetData->expPercents[i] = message->expPercents[i];
        }
    }

    for (int battler = 0; battler < MAX_BATTLERS; battler++) {
        commandSetData->moves[battler] = message->moves[battler];
        commandSetData->curPP[battler] = message->curPP[battler];
        commandSetData->maxPP[battler] = message->maxPP[battler];
    }

    fn_803DEF00(battlerData->taskFuncs.setCommandSelection, commandSetData, 0);
}

void BattleDisplay_InitTaskShowMoveSelectMenu(BattleSystem *battleSys,
                                              BattlerData *battlerData,
                                              MoveSelectMenuMessage *message) {
    MoveSelectMenuData *moveSelectMenuData =
        (MoveSelectMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(MoveSelectMenuData));

    moveSelectMenuData->state = 0;
    moveSelectMenuData->battleSys = battleSys;
    moveSelectMenuData->command = battlerData->data[0];
    moveSelectMenuData->battler = battlerData->battler;
    moveSelectMenuData->battlerType = battlerData->battlerType;
    moveSelectMenuData->healthbox = &battlerData->healthbox;
    moveSelectMenuData->partySlot = message->partySlot;

    for (int i = 0; i < MAX_BATTLERS; i++) {
        moveSelectMenuData->moves[i] = message->moves[i];
        moveSelectMenuData->ppCur[i] = message->ppCur[i];
        moveSelectMenuData->ppMax[i] = message->ppMax[i];
    }

    moveSelectMenuData->invalidMoves = message->invalidMoves;

    fn_803DEF00(battlerData->taskFuncs.showMoveSelectMenu, moveSelectMenuData, 0);
}

// The game calls the copy assignment of TargetMonData instead of inlining it.
#pragma push
#pragma dont_inline on
void BattleDisplay_InitTaskShowTargetSelectMenu(BattleSystem *battleSys,
                                                BattlerData *battlerData,
                                                TargetSelectMenuMessage *message) {
    TargetSelectMenuData *targetSelectMenuData =
        (TargetSelectMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(TargetSelectMenuData));
    int maxBattlers;
    u32 battleType;
    u8 battlerTypes[6];

    targetSelectMenuData->state = 0;
    targetSelectMenuData->battleSys = battleSys;
    targetSelectMenuData->command = battlerData->data[0];
    targetSelectMenuData->battler = battlerData->battler;
    targetSelectMenuData->battlerType = battlerData->battlerType;
    targetSelectMenuData->range = message->range;
    targetSelectMenuData->healthbox = &battlerData->healthbox;
    targetSelectMenuData->shouldHidePanel = message->shouldHidePanel;

    BattleSystem_SetBattlerTypes(battleSys, &battlerTypes[0]);

    maxBattlers = BattleSystem_GetMaxBattlers(battleSys);
    battleType = BattleSystem_GetBattleType(battleSys);

    for (int i = 0; i < maxBattlers; i++) {
        targetSelectMenuData->targetMon[i] = message->targetMon[i];
    }

    fn_803DEF00(battlerData->taskFuncs.showTargetSelectMenu, targetSelectMenuData, 0);
}
#pragma pop

void BattleDisplay_InitTaskShowBagMenu(BattleSystem *battleSys, BattlerData *battlerData, BagMenuMessage *message) {
    BagMenuData *bagMenuData = (BagMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BagMenuData));

    bagMenuData->partyMenuData = (PartyMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyMenuData));
    bagMenuData->partyMenuData->battlePartyCtx =
        // TODO This game allocates 0x38 bytes here, exactly sizeof(BattlePartyContext) in pokeplatinum, but 0x28 for
        // the player party task.
        (BattlePartyContext *)fn_8016DF70(HEAP_ID_BATTLE, 0x38);
    bagMenuData->partyMenuData->battlePartyCtx->party = Party_New(HEAP_ID_BATTLE);
    bagMenuData->state = 0;
    bagMenuData->battleSys = battleSys;
    bagMenuData->command = message->command;
    bagMenuData->battler = battlerData->battler;
    bagMenuData->battlerType = battlerData->battlerType;
    bagMenuData->hasTwoOpponents = message->hasTwoOpponents;
    bagMenuData->semiInvulnerable = message->semiInvulnerable;
    bagMenuData->substitute = message->substitute;

    for (int i = 0; i < MAX_BATTLERS; i++) {
        bagMenuData->partyMenuData->partySlots[i] = message->partySlots[i];

        for (int j = 0; j < MAX_PARTY_SIZE; j++) {
            bagMenuData->partyOrder[i][j] = message->partyOrder[i][j];
        }

        bagMenuData->embargoTurns[i] = message->embargoTurns[i];
    }

    fn_803DEF00(battlerData->taskFuncs.showBagMenu, bagMenuData, 0);
}

void BattleDisplay_InitTaskShowPartyMenu(BattleSystem *battleSys, BattlerData *battlerData, PartyMenuMessage *message) {
    PartyMenuData *partyMenuData = (PartyMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyMenuData));

    partyMenuData->state = 0;
    partyMenuData->battleSys = battleSys;
    partyMenuData->command = message->command;
    partyMenuData->battler = message->battler;
    partyMenuData->listMode = message->listMode;
    partyMenuData->canSwitch = message->canSwitch;
    partyMenuData->doublesSelection = message->doublesSelection;
    partyMenuData->selectedBattleBagItem = 0;
    partyMenuData->battlersSwitchingMask = message->battlersSwitchingMask;

    for (int i = 0; i < MAX_BATTLERS; i++) {
        partyMenuData->partySlots[i] = message->selectedPartySlot[i];

        for (int j = 0; j < MAX_PARTY_SIZE; j++) {
            partyMenuData->partyOrder[i][j] = message->partyOrder[i][j];
        }
    }

    fn_803DEF00(battlerData->taskFuncs.showPartyMenu, partyMenuData, 0);
}

void BattleDisplay_InitTaskShowYesNoMenu(BattleSystem *battleSys, BattlerData *battlerData, YesNoMenuMessage *message) {
    YesNoMenuData *yesNoMenuData = (YesNoMenuData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(YesNoMenuData));

    yesNoMenuData->state = 0;
    yesNoMenuData->battleSys = battleSys;
    yesNoMenuData->command = message->command;
    yesNoMenuData->battler = battlerData->battler;
    yesNoMenuData->healthbox = &battlerData->healthbox;
    yesNoMenuData->promptMsg = message->promptMsg;
    yesNoMenuData->yesNoType = message->yesNoType;
    yesNoMenuData->move = message->move;
    yesNoMenuData->nickname = message->nickname;

    fn_803DEF00(battlerData->taskFuncs.showYesNoMenu, yesNoMenuData, 0);
}

void BattleDisplay_PrintAttackMessage(BattleSystem *battleSys, BattlerData *battlerData, AttackMsgMessage *message) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader = BattleSystem_GetAttackMessageLoader(battleSys);
    BattleMessage battleMsg;

    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = message->command;
    waitTask->battler = battlerData->battler;

    battleMsg.id = message->move * 3;
    battleMsg.commandCode = message->command;
    battleMsg.tags = TAG_NICKNAME_TRNAME;
    battleMsg.params[0] = battlerData->battler | (message->partySlot << 8);
    battleMsg.params[1] = battlerData->battler;

    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintMessage(BattleSystem *battleSys, BattlerData *battlerData, BattleMessage *battleMsg) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader = BattleSystem_GetMessageLoader(battleSys);

    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = battlerData->data[0];
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_InitTaskSetMoveAnimation(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            MoveAnimation *animation) {
    SetMoveAnimationData *setMoveAnimationData =
        (SetMoveAnimationData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(SetMoveAnimationData));

    setMoveAnimationData->state = 0;
    setMoveAnimationData->battleSys = battleSys;
    setMoveAnimationData->command = battlerData->data[0];
    setMoveAnimationData->battler = battlerData->battler;
    setMoveAnimationData->moveAnim = *animation;

    if (animation->animMode == 1 && animation->secondaryAnimID == 25) {
        battlerData->isAlternateSprite = 1;
    }

    if (animation->animMode == 1 && animation->secondaryAnimID == 26) {
        battlerData->isAlternateSprite = 0;
    }

    fn_803DEF00(Task_SetMoveAnimation, setMoveAnimationData, 0);
}

void BattleDisplay_InitTaskFlickerBattler(BattleSystem *battleSys, BattlerData *battlerData) {
    FlickerBattlerData *flickerBattlerData =
        (FlickerBattlerData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(FlickerBattlerData));

    flickerBattlerData->battleSys = battleSys;
    flickerBattlerData->battler = battlerData->battler;

    fn_803DEF00(Task_FlickerBattler, flickerBattlerData, 0);
}

void BattleDisplay_InitTaskUpdateHPGauge(BattleSystem *battleSys,
                                         BattlerData *battlerData,
                                         HPGaugeUpdateMessage *message) {
    HealthBox *healthbox = &battlerData->healthbox;
    memset(&healthbox->state, 0, sizeof(u8));

    healthbox->battleSys = battleSys;
    healthbox->command = message->command;
    healthbox->battler = battlerData->battler;
    healthbox->type = fn_803D9810(battlerData->battlerType, BattleSystem_GetBattleType(battleSys));
    healthbox->curHP = message->curHP;
    healthbox->maxHP = message->maxHP;
    healthbox->damage = message->hpCalcTemp;
    healthbox->level = message->level;

    if (message->hpCalcTemp == HP_CALC_INSTANT_ZERO) {
        healthbox->curHP = 0;
        healthbox->damage = 0;
    }

    healthbox->task_10 = fn_803DEF00(Task_UpdateHPGauge, healthbox, 1000);
}

void BattleDisplay_InitTaskUpdateExpGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          ExpGaugeUpdateMessage *message) {
    HealthBox *healthbox = &battlerData->healthbox;
    memset(&healthbox->state, 0, sizeof(u8));

    healthbox->battleSys = battleSys;
    healthbox->command = message->command;
    healthbox->battler = battlerData->battler;

    if (battlerData->battlerType == BATTLER_TYPE_SOLO_PLAYER) {
        healthbox->task_10 = fn_803DEF00(Task_UpdateExpGauge, healthbox, 1000);
    } else {
        BattleController_EmitClearCommand(healthbox->battleSys, healthbox->battler, healthbox->command);
    }
}

void BattleDisplay_InitTaskPlayFaintingSequence(BattleSystem *battleSys,
                                                BattlerData *battlerData,
                                                FaintingSequenceMessage *message) {
    FaintingSequenceData *faintingSequenceData =
        (FaintingSequenceData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(FaintingSequenceData));

    faintingSequenceData->state = 0;
    faintingSequenceData->battleSys = battleSys;
    faintingSequenceData->command = message->command;
    faintingSequenceData->battler = battlerData->battler;
    faintingSequenceData->species = message->species;

    fn_803DEF00(Task_PlayFaintingSequence, faintingSequenceData, 0);
}

void BattleDisplay_PlaySound(BattleSystem *battleSys, BattlerData *battlerData, PlaySoundMessage *message) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
}

void BattleDisplay_InitTaskFadeOut(BattleSystem *battleSys, BattlerData *battlerData) {
    FadeOutData *fadeOutData = (FadeOutData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(FadeOutData));

    fadeOutData->state = 0;
    fadeOutData->battleSys = battleSys;
    fadeOutData->command = battlerData->data[0];
    fadeOutData->battler = battlerData->battler;

    fn_803DEF00(Task_FadeOut, fadeOutData, 0);
}

void BattleDisplay_InitTaskToggleVanish(BattleSystem *battleSys,
                                        BattlerData *battlerData,
                                        ToggleVanishMessage *message) {
    ToggleVanishData *toggleVanishData = (ToggleVanishData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(ToggleVanishData));

    toggleVanishData->battleSys = battleSys;
    toggleVanishData->command = message->command;
    toggleVanishData->battler = battlerData->battler;

    fn_803DEF00(Task_ToggleVanish, toggleVanishData, 0);
}

void BattleDisplay_SetStatusIcon(BattleSystem *battleSys, BattlerData *battlerData, SetStatusIconMessage *message) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
}

void BattleDisplay_PrintTrainerMessage(BattleSystem *battleSys, BattlerData *battlerData, TrainerMsgMessage *message) {
    BattleMessageWaitTask *waitTask =
        (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = message->command;
    waitTask->battler = battlerData->battler;

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintRecallMessage(BattleSystem *battleSys, BattlerData *battlerData, RecallMsgMessage *message) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadRecallMessage(battleSys, battlerData, message, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = message->command;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintSendOutMessage(BattleSystem *battleSys, BattlerData *battlerData, SendOutMsgMessage *message) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadSendOutMessage(battleSys, battlerData, message, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = message->command;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintBattleStartMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadBattleStartMessage(battleSys, battlerData, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = BATTLE_COMMAND_PRINT_BATTLE_START_MESSAGE;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintLeadMonMessage(BattleSystem *battleSys, BattlerData *battlerData, LeadMonMsgMessage *message) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadLeadMonMessage(battleSys, battlerData, message, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = message->command;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_InitTaskPlayLevelUpAnimation(BattleSystem *battleSys, BattlerData *battlerData) {
    PlayLevelUpAnimationData *playLevelUpAnimationData =
        (PlayLevelUpAnimationData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PlayLevelUpAnimationData));

    playLevelUpAnimationData->battleSys = battleSys;
    playLevelUpAnimationData->command = battlerData->data[0];
    playLevelUpAnimationData->battler = battlerData->battler;

    fn_803DEF00(Task_PlayLevelUpAnimation, playLevelUpAnimationData, 0);
}

void BattleDisplay_SetAlertMessage(BattleSystem *battleSys, BattlerData *battlerData, AlertMsgMessage *message) {
    AlertMsgData *alertMsgData;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;
    Strbuf *msgBuffer;

    if (battlerData->bootState == BATTLER_BOOT_STATE_AI) {
        BattleController_EmitAlertMessageAck(battleSys, battlerData->battler);
        BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
    } else {
        msgLoader = BattleSystem_GetMessageLoader(battleSys);
        alertMsgData = (AlertMsgData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(AlertMsgData));

        alertMsgData->battleSys = battleSys;
        alertMsgData->command = message->command;
        alertMsgData->battler = battlerData->battler;
        alertMsgData->state = 0;

        battleMsg = message->msg;
        battleMsg.commandCode = message->command;

        if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_UNK_11) {
            lbl_806405C8 = 1;
        }

        if ((BattleSystem_GetBattleType(battleSys) & (BATTLE_TYPE_UNK_19 | BATTLE_TYPE_UNK_12)) ==
            (BATTLE_TYPE_UNK_19 | BATTLE_TYPE_UNK_12)) {
            lbl_806405C8 = 1;
        }

        alertMsgData->msgIdx =
            BattleMessage_Print(battleSys, msgLoader, &message->msg, BattleSystem_GetTextSpeed(battleSys));
        lbl_806405C8 = 0;

        msgBuffer = BattleSystem_GetMsgBuffer(battleSys);
        fn_8016E394(battlerData->battler,
                    &battleMsg,
                    Strbuf_GetData(msgBuffer),
                    (Strbuf_Length(msgBuffer) + 1) * sizeof(u16));

        fn_803DEF00(Task_WaitForAlertMessagePrint, alertMsgData, 0);
    }
}

void BattleDisplay_RefreshHPGauge(BattleSystem *battleSys, BattlerData *battlerData, RefreshHPGaugeMessage *message) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
}

void BattleDisplay_InitTaskForgetMove(BattleSystem *battleSys, BattlerData *battlerData, ForgetMoveMessage *message) {
    ForgetMoveData *forgetMoveData = (ForgetMoveData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(ForgetMoveData));

    forgetMoveData->state = 0;
    forgetMoveData->battleSys = battleSys;
    forgetMoveData->command = message->command;
    forgetMoveData->battler = battlerData->battler;
    forgetMoveData->move = message->move;
    forgetMoveData->slot = message->slot;

    fn_803DEF00(Task_ForgetMove, forgetMoveData, 0);
}

void BattleDisplay_InitTaskSetMosaic(BattleSystem *battleSys, BattlerData *battlerData, MosaicSetMessage *message) {
    SetMosaicData *setMosaicData = (SetMosaicData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(SetMosaicData));

    setMosaicData->battleSys = battleSys;
    setMosaicData->command = message->command;
    setMosaicData->battler = battlerData->battler;

    fn_803DEF00(Task_SetMosaic, setMosaicData, 0);
}

void BattleDisplay_InitTaskShowBattleStartPartyGauge(BattleSystem *battleSys,
                                                     BattlerData *battlerData,
                                                     PartyGaugeData *partyGauge) {
    PartyGaugeTask *task = (PartyGaugeTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyGaugeTask));

    task->battleSys = battleSys;
    task->command = partyGauge->command;
    task->battler = battlerData->battler;

    fn_803DEF00(Task_ShowPartyGauge, task, 0);
}

void BattleDisplay_InitTaskHideBattleStartPartyGauge(BattleSystem *battleSys,
                                                     BattlerData *battlerData,
                                                     PartyGaugeData *partyGauge) {
    PartyGaugeTask *task = (PartyGaugeTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyGaugeTask));

    task->battleSys = battleSys;
    task->command = partyGauge->command;
    task->battler = battlerData->battler;

    fn_803DEF00(Task_HidePartyGauge, task, 0);
}

void BattleDisplay_InitTaskShowPartyGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          PartyGaugeData *partyGauge) {
    PartyGaugeTask *task = (PartyGaugeTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyGaugeTask));

    task->battleSys = battleSys;
    task->command = partyGauge->command;
    task->battler = battlerData->battler;

    fn_803DEF00(Task_ShowPartyGauge, task, 0);
}

void BattleDisplay_InitTaskHidePartyGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          PartyGaugeData *partyGauge) {
    PartyGaugeTask *task = (PartyGaugeTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(PartyGaugeTask));

    task->battleSys = battleSys;
    task->command = partyGauge->command;
    task->battler = battlerData->battler;

    fn_803DEF00(Task_HidePartyGauge, task, 0);
}

void BattleDisplay_PrintLinkWaitMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_PRINT_LINK_WAIT_MESSAGE);
}

void BattleDisplay_RestoreSprite(BattleSystem *battleSys, BattlerData *battlerData, MoveAnimation *animation) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, animation->command);
}

void BattleDisplay_InitTaskSpriteToOAM(BattleSystem *battleSys, BattlerData *battlerData) {
    SpriteToOAMData *spriteToOAMData = (SpriteToOAMData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(SpriteToOAMData));

    spriteToOAMData->battleSys = battleSys;
    spriteToOAMData->command = battlerData->data[0];
    spriteToOAMData->battler = battlerData->battler;

    fn_803DEF00(Task_SpriteToOAM, spriteToOAMData, 0);
}

// The game passes the battle system where the task expects its data, which it then frees.
void BattleDisplay_InitTaskOAMToSprite(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803DEF00(Task_OAMToSprite, battleSys, 0);
}

void BattleDisplay_PrintResultMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadResultMessage(battleSys, battlerData, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = BATTLE_COMMAND_PRINT_RESULT_MESSAGE;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_PrintEscapeMessage(BattleSystem *battleSys, BattlerData *battlerData, EscapeMsgMessage *message) {
    LoadEscapeMessage(battleSys, battlerData, message);

    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_PRINT_ESCAPE_MESSAGE);
}

void BattleDisplay_PrintForfeitMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleMessageWaitTask *waitTask;
    MessageLoader *msgLoader;
    BattleMessage battleMsg;

    LoadForfeitMessage(battleSys, battlerData, &battleMsg);

    msgLoader = BattleSystem_GetMessageLoader(battleSys);
    waitTask = (BattleMessageWaitTask *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattleMessageWaitTask));

    waitTask->battleSys = battleSys;
    waitTask->command = BATTLE_COMMAND_PRINT_FORFEIT_MESSAGE;
    waitTask->battler = battlerData->battler;
    waitTask->msgIdx = BattleMessage_Print(battleSys, msgLoader, &battleMsg, BattleSystem_GetTextSpeed(battleSys));

    fn_803DEF00(Task_WaitForBattleMessagePrint, waitTask, 0);
}

void BattleDisplay_RefreshSprite(BattleSystem *battleSys, BattlerData *battlerData, MoveAnimation *animation) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, animation->command);
}

void BattleDisplay_FlyMoveHitSoundEffect(BattleSystem *battleSys,
                                         BattlerData *battlerData,
                                         MoveHitSoundMessage *message) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
}

void BattleDisplay_PlayMusic(BattleSystem *battleSys, BattlerData *battlerData, MusicPlayMessage *message) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
}

static void Task_SetEncounter(Unk8063D230 *task, void *data) {
    MonEncounterData *monEncounterData = (MonEncounterData *)data;

    BattleController_EmitClearCommand(monEncounterData->battleSys,
                                      monEncounterData->battler,
                                      monEncounterData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ShowEncounter(Unk8063D230 *task, void *data) {
    MonShowData *monShowData = (MonShowData *)data;

    BattleController_EmitClearCommand(monShowData->battleSys, monShowData->battler, monShowData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ShowPokemon(Unk8063D230 *task, void *data) {
    MonShowData *monShowData = (MonShowData *)data;

    BattleController_EmitClearCommand(monShowData->battleSys, monShowData->battler, monShowData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ReturnPokemon(Unk8063D230 *task, void *data) {
    MonReturnData *monReturnData = (MonReturnData *)data;

    BattleController_EmitClearCommand(monReturnData->battleSys, monReturnData->battler, monReturnData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_OpenCaptureBall(Unk8063D230 *task, void *data) {
    OpenCaptureBallData *openCaptureBallData = (OpenCaptureBallData *)data;

    BattleController_EmitClearCommand(openCaptureBallData->battleSys,
                                      openCaptureBallData->battler,
                                      openCaptureBallData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SetTrainerEncounter(Unk8063D230 *task, void *data) {
    TrainerEncounterData *trainerEncounterData = (TrainerEncounterData *)data;

    BattleController_EmitClearCommand(trainerEncounterData->battleSys,
                                      trainerEncounterData->battler,
                                      trainerEncounterData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ThrowTrainerBall(Unk8063D230 *task, void *data) {
    TrainerThrowBallData *trainerThrowBallData = (TrainerThrowBallData *)data;

    BattleController_EmitClearCommand(trainerThrowBallData->battleSys,
                                      trainerThrowBallData->battler,
                                      trainerThrowBallData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SlideTrainerOut(Unk8063D230 *task, void *data) {
    SlideTrainerOutData *slideTrainerOutData = (SlideTrainerOutData *)data;

    BattleController_EmitClearCommand(slideTrainerOutData->battleSys,
                                      slideTrainerOutData->battler,
                                      slideTrainerOutData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SlideTrainerIn(Unk8063D230 *task, void *data) {
    SlideTrainerInData *slideTrainerInData = (SlideTrainerInData *)data;

    BattleController_EmitClearCommand(slideTrainerInData->battleSys,
                                      slideTrainerInData->battler,
                                      slideTrainerInData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SlideHealthBoxIn(Unk8063D230 *task, void *data) {
    HealthBox *healthbox = (HealthBox *)data;

    BattleController_EmitClearCommand(healthbox->battleSys, healthbox->battler, healthbox->command);

    healthbox->task_10 = NULL;
    fn_803DEF3C(task);
}

static void Task_SlideHealthBoxOut(Unk8063D230 *task, void *data) {
    HealthBox *healthbox = (HealthBox *)data;

    BattleController_EmitClearCommand(healthbox->battleSys, healthbox->battler, healthbox->command);

    healthbox->task_10 = NULL;
    fn_803DEF3C(task);
}

// The player tasks send a request to the Wii controls (unit 8016E2B8) and wait for the answer.
static void Task_PlayerSetCommandSelection(Unk8063D230 *task, void *data) {
    CommandSetData *commandSetData = (CommandSetData *)data;

    BattleSystem_GetBattlerData(commandSetData->battleSys, commandSetData->battler);
    BattleSystem_GetBattleType(commandSetData->battleSys);

    switch (commandSetData->state) {
        case 0: commandSetData->state = 1; break;
        case 1: commandSetData->state = 4; break;
        case 4:
            fn_8016E330(1, commandSetData->battler, 1, NULL);
            commandSetData->state = 5;
            break;
        case 5:
            if (fn_8016E430(commandSetData->battler) != 0xFF) {
                fn_8016E2E4(9);
            } else {
                commandSetData->input = fn_8016E478(commandSetData->battler);
                commandSetData->state = 9;
            }
            break;
        case 9:
            BattleController_EmitSelectedCommand(commandSetData->battleSys,
                                                 commandSetData->battler,
                                                 commandSetData->input);
            BattleController_EmitClearCommand(commandSetData->battleSys,
                                              commandSetData->battler,
                                              commandSetData->command);
            fn_8016E0A0(data);
            fn_803DEF3C(task);
            break;
    }
}

static void Task_TrainerSetCommandSelection(Unk8063D230 *task, void *data) {
    CommandSetData *commandSetData = (CommandSetData *)data;

    fn_8017C9E0(commandSetData->battleSys, commandSetData->battler);
    BattleSystem_GetBattleContext(commandSetData->battleSys);

    int command = fn_803C93C4(commandSetData->battleSys, commandSetData->battler, 0);

    if (command == 0xFF) {
        command = 1;
    }

    BattleController_EmitSelectedCommand(commandSetData->battleSys, commandSetData->battler, command);
    BattleController_EmitClearCommand(commandSetData->battleSys, commandSetData->battler, commandSetData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

// TODO first usable move (BattleSystem_CanUseMove), counted from 1, or 0. Inlined in Task_PlayerShowMoveSelectMenu.
static inline int fn_803A9EFC_inline(MoveSelectMenuData *moveSelectMenuData) {
    BattleMessage battleMsg;

    for (int i = 0; i < LEARNED_MOVES_MAX; i++) {
        if ((moveSelectMenuData->invalidMoves & FlagIndex(i)) == FALSE &&
            BattleSystem_CanUseMove(moveSelectMenuData->battleSys,
                                    BattleSystem_GetBattleContext(moveSelectMenuData->battleSys),
                                    moveSelectMenuData->battler,
                                    i,
                                    &battleMsg)) {
            return i + 1;
        }
    }

    return 0;
}

static void Task_PlayerShowMoveSelectMenu(Unk8063D230 *task, void *data) {
    MoveSelectMenuData *moveSelectMenuData = (MoveSelectMenuData *)data;
    int i;

    switch (moveSelectMenuData->state) {
        case 0:
            for (i = 0; i < LEARNED_MOVES_MAX; i++) {
                sUnk8063D080.moves[i] = moveSelectMenuData->moves[i];
                sUnk8063D080.ppCur[i] = moveSelectMenuData->ppCur[i];
                sUnk8063D080.ppMax[i] = moveSelectMenuData->ppMax[i];
            }

            sUnk8063D080.partySlot = moveSelectMenuData->partySlot;

            fn_8016E330(2, moveSelectMenuData->battler, fn_803A9EFC_inline(moveSelectMenuData), &sUnk8063D080);
            moveSelectMenuData->state++;
            break;
        case 1:
            if (fn_8016E430(moveSelectMenuData->battler) != 0xFF) {
                fn_8016E2E4(9);
            } else {
                moveSelectMenuData->input = fn_8016E478(moveSelectMenuData->battler);
                moveSelectMenuData->state++;
            }
            break;
        case 2:
            BattleController_EmitSelectedMove(moveSelectMenuData->battleSys,
                                              moveSelectMenuData->battler,
                                              moveSelectMenuData->input);
            moveSelectMenuData->state++;
            break;
        case 3:
            BattleController_EmitClearCommand(moveSelectMenuData->battleSys,
                                              moveSelectMenuData->battler,
                                              moveSelectMenuData->command);
            fn_8016E0A0(data);
            fn_803DEF3C(task);
            break;
    }
}

static void Task_TrainerShowMoveSelectMenu(Unk8063D230 *task, void *data) {
    MoveSelectMenuData *moveSelectMenuData = (MoveSelectMenuData *)data;
    BattleSystem_GetBattleType(moveSelectMenuData->battleSys);
    int action = (u8)fn_803C93C4(moveSelectMenuData->battleSys, moveSelectMenuData->battler, 2) + 1;

    if (action - 1 == 0xFF || moveSelectMenuData->moves[action - 1] == MOVE_NONE) {
        do {
            action = LCRNG_Next() % LEARNED_MOVES_MAX + 1;
        } while (moveSelectMenuData->moves[action - 1] == MOVE_NONE);
    }

    BattleController_EmitSelectedMove(moveSelectMenuData->battleSys, moveSelectMenuData->battler, action);
    BattleController_EmitClearCommand(moveSelectMenuData->battleSys,
                                      moveSelectMenuData->battler,
                                      moveSelectMenuData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_PlayerShowTargetSelectMenu(Unk8063D230 *task, void *data) {
    TargetSelectMenuData *targetSelectMenuData = (TargetSelectMenuData *)data;
    TargetSelectData targetSelectData;
    u8 battlersByType[6];
    int i;
    int target;
    u32 battleType;

    switch (targetSelectMenuData->state) {
        case 0:
            memset(&targetSelectMenuData->request, 0, sizeof(Unk803AA178));
            BattleSystem_SetBattlerTypes(targetSelectMenuData->battleSys, targetSelectMenuData->request.battlerTypes);

            for (i = 0; i < MAX_BATTLERS; i++) {
                targetSelectData.targetMonData[i] = targetSelectMenuData->targetMon[i];

                if (targetSelectMenuData->targetMon[i].isPresent) {
                    targetSelectMenuData->request.partySlots[i] = targetSelectMenuData->targetMon[i].partySlot;
                } else {
                    targetSelectMenuData->request.partySlots[i] = 0xFF;
                }
            }

            targetSelectData.battlerType = targetSelectMenuData->battlerType;
            targetSelectData.targetingLayout =
                fn_803D9EB4(targetSelectMenuData->range, targetSelectMenuData->battlerType);
            targetSelectMenuData->request.targetingLayout = targetSelectData.targetingLayout;

            fn_8016E330(3,
                        targetSelectMenuData->battler,
                        BattleSystem_Defender(
                            targetSelectMenuData->battleSys,
                            BattleSystem_GetBattleContext(targetSelectMenuData->battleSys),
                            targetSelectMenuData->battler,
                            Battler_SelectedMove(BattleSystem_GetBattleContext(targetSelectMenuData->battleSys),
                                                 targetSelectMenuData->battler),
                            TRUE,
                            0) +
                            1,
                        &targetSelectMenuData->request);
            targetSelectMenuData->state++;
            break;
        case 1:
            if (fn_8016E430(targetSelectMenuData->battler) != 0xFF) {
                fn_8016E2E4(9);
                break;
            }

            target = fn_8016E478(targetSelectMenuData->battler);
            battleType = BattleSystem_GetBattleType(targetSelectMenuData->battleSys);

            if (target != 0xFF) {
                BattleSystem_SetBattlersByType(targetSelectMenuData->battleSys, battlersByType);

                if (battleType & BATTLE_TYPE_DOUBLES) {
                    target = battlersByType[target + 1] + 1;
                } else {
                    target = battlersByType[target - 1] + 1;
                }
            }

            BattleController_EmitSelectedTarget(targetSelectMenuData->battleSys, targetSelectMenuData->battler, target);
            BattleController_EmitClearCommand(targetSelectMenuData->battleSys,
                                              targetSelectMenuData->battler,
                                              targetSelectMenuData->command);
            fn_8016E0A0(data);
            fn_803DEF3C(task);
            break;
    }
}

static void Task_TrainerShowTargetSelectMenu(Unk8063D230 *task, void *data) {
    TargetSelectMenuData *targetSelectMenuData = (TargetSelectMenuData *)data;
    BattleContext *battleCtx = BattleSystem_GetBattleContext(targetSelectMenuData->battleSys);
    int selectedTarget = (u8)fn_803C93C4(targetSelectMenuData->battleSys, targetSelectMenuData->battler, 1) + 1;

    if (selectedTarget - 1 == 0xFF) {
        selectedTarget = BattleContext_Get(targetSelectMenuData->battleSys,
                                           battleCtx,
                                           BATTLECTX_AICTX_SELECTED_TARGET,
                                           targetSelectMenuData->battler) +
                         1;
    }

    fn_803D989C(selectedTarget < 5, "tp_ret\x82\xaa\x95s\x90\xb3\x82\xc5\x82\xb7:%d\n", selectedTarget);

    BattleController_EmitSelectedTarget(targetSelectMenuData->battleSys, targetSelectMenuData->battler, selectedTarget);
    BattleController_EmitClearCommand(targetSelectMenuData->battleSys,
                                      targetSelectMenuData->battler,
                                      targetSelectMenuData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

// Empty in this game.
static void Task_PlayerShowBagMenu(Unk8063D230 *task, void *data) {}

static void Task_TrainerShowBagMenu(Unk8063D230 *task, void *data) {
    BagMenuData *bagMenuData = (BagMenuData *)data;
    BattleItemUse used;

    used.item = 1;

    BattleController_EmitSelectedBagItem(bagMenuData->battleSys, bagMenuData->battler, used);
    BattleController_EmitClearCommand(bagMenuData->battleSys, bagMenuData->battler, bagMenuData->command);

    fn_8016E0A0(bagMenuData->partyMenuData->battlePartyCtx->party);
    fn_8016E0A0(bagMenuData->partyMenuData->battlePartyCtx);
    fn_8016E0A0(bagMenuData->partyMenuData);
    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_PlayerShowPartyMenu(Unk8063D230 *task, void *data) {
    PartyMenuData *partyMenuData = (PartyMenuData *)data;
    u32 battleType = BattleSystem_GetBattleType(partyMenuData->battleSys);
    Party *unused = BattleSystem_GetParty(partyMenuData->battleSys, partyMenuData->battler);
    BattlePartyContext *battlePartyCtx;
    int result;

    switch (partyMenuData->state) {
        case 0: {
            int i;
            int battler;
            int battler1, battler2;
            Pokemon *monSrc, *monDst;

            battlePartyCtx = (BattlePartyContext *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattlePartyContext));
            memset(battlePartyCtx, 0, sizeof(BattlePartyContext));
            partyMenuData->battlePartyCtx = battlePartyCtx;
            battlePartyCtx->party = Party_New(HEAP_ID_BATTLE);

            if ((BattleSystem_GetBattleType(partyMenuData->battleSys) & (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2)) ==
                    (BATTLE_TYPE_LINK | BATTLE_TYPE_2vs2) ||
                BattleSystem_GetBattleType(partyMenuData->battleSys) == BATTLE_TYPE_FRONTIER_WITH_AI_PARTNER) {
                if (BattleSystem_GetBattlerType(partyMenuData->battleSys, partyMenuData->battler) ==
                    BATTLER_TYPE_PLAYER_SIDE_SLOT_1) {
                    battler1 = partyMenuData->battler;
                    battler2 = BattleSystem_GetPartner(partyMenuData->battleSys, partyMenuData->battler);
                } else {
                    battler1 = BattleSystem_GetPartner(partyMenuData->battleSys, partyMenuData->battler);
                    battler2 = partyMenuData->battler;
                }

                monSrc = Pokemon_New(HEAP_ID_BATTLE);

                for (i = 0; i < MAX_PARTY_SIZE; i++) {
                    Party_AddPokemon(battlePartyCtx->party, monSrc);
                }

                fn_8016E0A0(monSrc);

                for (i = 0; i < BattleSystem_GetPartyCount(partyMenuData->battleSys, battler1); i++) {
                    monSrc = BattleSystem_GetPartyPokemon(partyMenuData->battleSys,
                                                          battler1,
                                                          partyMenuData->partyOrder[battler1][i]);
                    monDst = Party_GetPokemonBySlotIndex(battlePartyCtx->party, i * 2);
                    Pokemon_Copy(monSrc, monDst);
                    battlePartyCtx->pokemonPartySlots[i * 2] = partyMenuData->partyOrder[battler1][i];
                }

                for (i = 0; i < BattleSystem_GetPartyCount(partyMenuData->battleSys, battler2); i++) {
                    monSrc = BattleSystem_GetPartyPokemon(partyMenuData->battleSys,
                                                          battler2,
                                                          partyMenuData->partyOrder[battler2][i]);
                    monDst = Party_GetPokemonBySlotIndex(battlePartyCtx->party, i * 2 + 1);
                    Pokemon_Copy(monSrc, monDst);
                    battlePartyCtx->pokemonPartySlots[i * 2 + 1] = partyMenuData->partyOrder[battler2][i];
                }

                if (BattleSystem_GetBattlerType(partyMenuData->battleSys, partyMenuData->battler) ==
                    BATTLER_TYPE_PLAYER_SIDE_SLOT_2) {
                    battlePartyCtx->selectedPartyIndex = 1;
                } else {
                    battlePartyCtx->selectedPartyIndex = 0;
                }
            } else {
                if (BattleSystem_GetBattleType(partyMenuData->battleSys) & BATTLE_TYPE_DOUBLES &&
                    (BattleSystem_GetBattleType(partyMenuData->battleSys) & BATTLE_TYPE_2vs2) == FALSE) {
                    battler = partyMenuData->battler & 1;
                } else {
                    battler = partyMenuData->battler;
                }

                int battlerType = BattleSystem_GetBattlerType(partyMenuData->battleSys, partyMenuData->battler);
                battlePartyCtx->selectedPartyIndex =
                    battlerType == BATTLER_TYPE_PLAYER_SIDE_SLOT_2 || battlerType == BATTLER_TYPE_ENEMY_SIDE_SLOT_2;

                Party *party = BattleSystem_GetParty(partyMenuData->battleSys, partyMenuData->battler);

                for (i = 0; i < Party_GetCurrentCount(party); i++) {
                    monSrc = BattleSystem_GetPartyPokemon(partyMenuData->battleSys,
                                                          battler,
                                                          partyMenuData->partyOrder[battler][i]);
                    Party_AddPokemon(battlePartyCtx->party, monSrc);
                    battlePartyCtx->pokemonPartySlots[i] = partyMenuData->partyOrder[battler][i];
                }
            }

            battlePartyCtx->battleSys = partyMenuData->battleSys;
            battlePartyCtx->moveToLearn = partyMenuData->canSwitch;
            battlePartyCtx->doubleBattleFirstSelectedPartySlot = partyMenuData->doublesSelection;
            battlePartyCtx->selectedBattleBagItem = partyMenuData->selectedBattleBagItem;
            battlePartyCtx->battler = partyMenuData->battler;

            if ((partyMenuData->battlersSwitchingMask & FlagIndex(partyMenuData->battler)) == 0) {
                battlePartyCtx->playerPokemonPartySlot = partyMenuData->partySlots[partyMenuData->battler];
            } else {
                battlePartyCtx->playerPokemonPartySlot = MAX_PARTY_SIZE;
            }

            if (BattleSystem_GetBattleType(partyMenuData->battleSys) & BATTLE_TYPE_2vs2) {
                battlePartyCtx->partnerPokemonPartySlot = MAX_PARTY_SIZE;
            } else if ((partyMenuData->battlersSwitchingMask &
                        FlagIndex(BattleSystem_GetPartner(partyMenuData->battleSys, partyMenuData->battler))) == 0) {
                battlePartyCtx->partnerPokemonPartySlot =
                    partyMenuData->partySlots[BattleSystem_GetPartner(partyMenuData->battleSys,
                                                                      partyMenuData->battler)];
            } else {
                battlePartyCtx->partnerPokemonPartySlot = MAX_PARTY_SIZE;
            }

            fn_8016E330(4, partyMenuData->battler, 0xFF, battlePartyCtx);
            partyMenuData->state++;
            break;
        }
        case 1:
            if (fn_8016E430(partyMenuData->battler) != 0xFF) {
                fn_8016E2E4(9);
                break;
            }

            result = fn_8016E478(partyMenuData->battler);
            battlePartyCtx = partyMenuData->battlePartyCtx;

            if (result == 0xFF) {
                BattleController_EmitPartyMenuResult(partyMenuData->battleSys, partyMenuData->battler, 0xFF);
            } else {
                BattleController_EmitPartyMenuResult(partyMenuData->battleSys,
                                                     partyMenuData->battler,
                                                     battlePartyCtx->pokemonPartySlots[result] + 1);
            }

            BattleController_EmitClearCommand(partyMenuData->battleSys, partyMenuData->battler, partyMenuData->command);
            fn_8016E0A0(battlePartyCtx->party);
            fn_8016E0A0(battlePartyCtx);
            fn_8016E0A0(data);
            fn_803DEF3C(task);
            break;
    }
}

static void Task_TrainerShowPartyMenu(Unk8063D230 *task, void *data) {
    PartyMenuData *partyMenuData = (PartyMenuData *)data;
    u32 battleType = BattleSystem_GetBattleType(partyMenuData->battleSys);
    int battler = partyMenuData->battler;
    Pokemon *mon;
    int slot;
    Party *party;
    int partner;

    if (battleType & BATTLE_TYPE_TAG || battleType & BATTLE_TYPE_2vs2) {
        partner = battler;
    } else {
        partner = BattleSystem_GetPartner(partyMenuData->battleSys, battler);
    }

    slot = fn_803C93C4(partyMenuData->battleSys, battler, 2);

    if (fn_803C93C4(partyMenuData->battleSys, battler, 0) != 3 || slot == 0xFF) {
        slot = fn_8017CB14(partyMenuData->battleSys, battler);
    }

    if (battler >= 0 && battler < MAX_BATTLERS && slot >= 0 && slot < MAX_PARTY_SIZE) {
        if (Pokemon_GetValue(BattleSystem_GetPartyPokemon(partyMenuData->battleSys, battler, slot),
                             MON_DATA_HP,
                             NULL) == 0 ||
            partyMenuData->partySlots[battler] == slot || partyMenuData->partySlots[partner] == slot) {
            slot = 0xFF;
        }
    }

    if (slot == 0xFF) {
        slot = MAX_PARTY_SIZE;
    }

    if (slot == MAX_PARTY_SIZE) {
        party = BattleSystem_GetParty(partyMenuData->battleSys, partyMenuData->battler);

        for (slot = 0; slot < Party_GetCurrentCount(party); slot++) {
            mon = BattleSystem_GetPartyPokemon(partyMenuData->battleSys, partyMenuData->battler, slot);

            if (Pokemon_GetValue(mon, MON_DATA_HP, NULL) && partyMenuData->partySlots[battler] != slot &&
                partyMenuData->partySlots[partner] != slot) {
                break;
            }
        }
    }

    BattleController_EmitPartyMenuResult(partyMenuData->battleSys, partyMenuData->battler, slot + 1);
    BattleController_EmitClearCommand(partyMenuData->battleSys, partyMenuData->battler, partyMenuData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_PlayerShowYesNoMenu(Unk8063D230 *task, void *data) {
    YesNoMenuData *yesNoMenuData = (YesNoMenuData *)data;
    void *bgConfig = BattleSystem_GetBgConfig(yesNoMenuData->battleSys);
    void *btlSubscreen = fn_803ACA58(yesNoMenuData->battleSys);
    int partner;
    HealthBox *healthbox;
    BattlerData *battlerData = BattleSystem_GetBattlerData(yesNoMenuData->battleSys, yesNoMenuData->battler);
    partner = BattleSystem_GetPartner(yesNoMenuData->battleSys, yesNoMenuData->battler);

    if (partner != yesNoMenuData->battler) {
        healthbox = BattleSystem_GetHealthBox(yesNoMenuData->battleSys, partner);
    } else {
        healthbox = NULL;
    }

    switch (yesNoMenuData->state) {
        case 0:
            if (fn_803D9820(btlSubscreen) == FALSE) {
                break;
            }

            if (yesNoMenuData->promptMsg) {
                MessageLoader *msgLoader = BattleSystem_GetMessageLoader(yesNoMenuData->battleSys);
                BattleMessage battleMsg;

                if (yesNoMenuData->yesNoType == 5) {
                    battleMsg.tags = TAG_NICKNAME | 0x80;
                    battleMsg.params[0] = yesNoMenuData->nickname;
                } else {
                    battleMsg.tags = TAG_NONE;
                }

                battleMsg.id = yesNoMenuData->promptMsg;
                yesNoMenuData->msgIdx = BattleMessage_Print(yesNoMenuData->battleSys,
                                                            msgLoader,
                                                            &battleMsg,
                                                            BattleSystem_GetTextSpeed(yesNoMenuData->battleSys));
            }

            yesNoMenuData->state = 1;
            break;
        case 1:
            if (fn_803D97EC(yesNoMenuData->msgIdx) == FALSE || yesNoMenuData->promptMsg == 0) {
                GiveUpMoveData giveUpMoveData;

                fn_803D9838(btlSubscreen);

                giveUpMoveData.move = yesNoMenuData->move;

                switch (yesNoMenuData->yesNoType) {
                    case 0:
                    case 5: fn_803D9834(btlSubscreen, 13, 0, &giveUpMoveData); break;
                    case 1: fn_803D9834(btlSubscreen, 14, 0, &giveUpMoveData); break;
                    case 2: fn_803D9834(btlSubscreen, 15, 0, &giveUpMoveData); break;
                    case 3: fn_803D9834(btlSubscreen, 16, 0, &giveUpMoveData); break;
                    case 4: fn_803D9834(btlSubscreen, 17, 0, &giveUpMoveData); break;
                }

                yesNoMenuData->state = 2;
            }
            break;
        case 2:
            yesNoMenuData->input = fn_803D9828(btlSubscreen);

            if (yesNoMenuData->input != 0) {
                fn_803D97F8(7);
                yesNoMenuData->state = 3;
            }
            break;
        case 3:
            if (fn_803D9820(btlSubscreen) == TRUE) {
                fn_803D980C(yesNoMenuData->healthbox);
                fn_803D9850(battlerData);
                fn_803D9838(btlSubscreen);
                fn_803D9834(btlSubscreen, 0, 0, NULL);

                if (yesNoMenuData->input == 1) {
                    fn_803D9830(btlSubscreen, 0);
                }

                yesNoMenuData->state = 4;
            }
            break;
        case 4:
            if (fn_803D9818(btlSubscreen) == TRUE) {
                BattleController_EmitSelectedCommand(yesNoMenuData->battleSys,
                                                     yesNoMenuData->battler,
                                                     yesNoMenuData->input);
                BattleController_EmitClearCommand(yesNoMenuData->battleSys,
                                                  yesNoMenuData->battler,
                                                  yesNoMenuData->command);
                fn_8016E0A0(data);
                fn_803DEF3C(task);
            }
            break;
    }
}

static void Task_TrainerShowYesNoMenu(Unk8063D230 *task, void *data) {
    YesNoMenuData *yesNoMenuData = (YesNoMenuData *)data;

    BattleController_EmitClearCommand(yesNoMenuData->battleSys, yesNoMenuData->battler, yesNoMenuData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SetMoveAnimation(Unk8063D230 *task, void *data) {
    SetMoveAnimationData *setMoveAnimationData = (SetMoveAnimationData *)data;

    BattleController_EmitClearCommand(setMoveAnimationData->battleSys,
                                      setMoveAnimationData->battler,
                                      setMoveAnimationData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_FlickerBattler(Unk8063D230 *task, void *data) {
    FlickerBattlerData *flickerBattlerData = (FlickerBattlerData *)data;

    BattleController_EmitClearCommand(flickerBattlerData->battleSys,
                                      flickerBattlerData->battler,
                                      BATTLE_COMMAND_FLICKER_BATTLER);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_UpdateHPGauge(Unk8063D230 *task, void *data) {
    HealthBox *healthbox = (HealthBox *)data;

    BattleController_EmitClearCommand(healthbox->battleSys, healthbox->battler, healthbox->command);

    healthbox->task_10 = NULL;
    fn_803DEF3C(task);
}

static void Task_UpdateExpGauge(Unk8063D230 *task, void *data) {
    HealthBox *healthbox = (HealthBox *)data;

    BattleController_EmitClearCommand(healthbox->battleSys, healthbox->battler, healthbox->command);

    healthbox->task_10 = NULL;
    fn_803DEF3C(task);
}

static void Task_PlayFaintingSequence(Unk8063D230 *task, void *data) {
    FaintingSequenceData *faintingSequenceData = (FaintingSequenceData *)data;

    BattleController_EmitClearCommand(faintingSequenceData->battleSys,
                                      faintingSequenceData->battler,
                                      faintingSequenceData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_FadeOut(Unk8063D230 *task, void *data) {
    FadeOutData *fadeOutData = (FadeOutData *)data;

    BattleController_EmitClearCommand(fadeOutData->battleSys, fadeOutData->battler, fadeOutData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ToggleVanish(Unk8063D230 *task, void *data) {
    ToggleVanishData *toggleVanishData = (ToggleVanishData *)data;

    BattleController_EmitClearCommand(toggleVanishData->battleSys,
                                      toggleVanishData->battler,
                                      toggleVanishData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_PlayLevelUpAnimation(Unk8063D230 *task, void *data) {
    PlayLevelUpAnimationData *playLevelUpAnimationData = (PlayLevelUpAnimationData *)data;

    BattleController_EmitClearCommand(playLevelUpAnimationData->battleSys,
                                      playLevelUpAnimationData->battler,
                                      playLevelUpAnimationData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_WaitForBattleMessagePrint(Unk8063D230 *task, void *data) {
    BattleMessageWaitTask *waitTask = (BattleMessageWaitTask *)data;

    BattleController_EmitClearCommand(waitTask->battleSys, waitTask->battler, waitTask->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

// TODO The alert message steps of the DS code are replaced by calls not identified yet.
static void Task_WaitForAlertMessagePrint(Unk8063D230 *task, void *data) {
    AlertMsgData *alertMsgData = (AlertMsgData *)data;

    if (fn_8016E430(alertMsgData->battler) == 0xFF) {
        BattleController_EmitAlertMessageAck(alertMsgData->battleSys, alertMsgData->battler);
        BattleController_EmitClearCommand(alertMsgData->battleSys, alertMsgData->battler, alertMsgData->command);
        fn_8016E0A0(data);
        fn_803DEF3C(task);
    } else {
        fn_8016E2E4(12);
    }
}

static void SysTask_SetupUI(Unk8063D230 *task, void *data) {
    if (data != NULL) {
        fn_8016E0A0(data);
    }

    fn_803DEF3C(task);
}

static void Task_ForgetMove(Unk8063D230 *task, void *data) {}

static void Task_SetMosaic(Unk8063D230 *task, void *data) {
    SetMosaicData *setMosaicData = (SetMosaicData *)data;

    BattleController_EmitClearCommand(setMosaicData->battleSys, setMosaicData->battler, setMosaicData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_ShowPartyGauge(Unk8063D230 *task, void *data) {
    PartyGaugeTask *partyGaugeTask = (PartyGaugeTask *)data;

    BattleController_EmitClearCommand(partyGaugeTask->battleSys, partyGaugeTask->battler, partyGaugeTask->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_HidePartyGauge(Unk8063D230 *task, void *data) {
    PartyGaugeTask *partyGaugeTask = (PartyGaugeTask *)data;

    BattleController_EmitClearCommand(partyGaugeTask->battleSys, partyGaugeTask->battler, partyGaugeTask->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_SpriteToOAM(Unk8063D230 *task, void *data) {
    SpriteToOAMData *spriteToOAMData = (SpriteToOAMData *)data;

    BattleController_EmitClearCommand(spriteToOAMData->battleSys, spriteToOAMData->battler, spriteToOAMData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

static void Task_OAMToSprite(Unk8063D230 *task, void *data) {
    OAMToSpriteData *oamToSpriteData = (OAMToSpriteData *)data;

    BattleController_EmitClearCommand(oamToSpriteData->battleSys, oamToSpriteData->battler, oamToSpriteData->command);

    fn_8016E0A0(data);
    fn_803DEF3C(task);
}

void BattlerData_SetTaskFuncs(BattleSystem *battleSys, BattlerData *battlerData) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);

    if (battleType & (BATTLE_TYPE_UNK_15 | BATTLE_TYPE_UNK_16)) {
        battlerData->taskFuncs.setCommandSelection = Task_PlayerSetCommandSelection;
        battlerData->taskFuncs.showMoveSelectMenu = Task_PlayerShowMoveSelectMenu;
        battlerData->taskFuncs.showTargetSelectMenu = Task_PlayerShowTargetSelectMenu;
        battlerData->taskFuncs.showBagMenu = Task_PlayerShowBagMenu;
        battlerData->taskFuncs.showPartyMenu = Task_PlayerShowPartyMenu;
        battlerData->taskFuncs.showYesNoMenu = Task_PlayerShowYesNoMenu;
        battlerData->bootState = BATTLER_BOOT_STATE_NORMAL;
    } else if (battleType & BATTLE_TYPE_UNK_14) {
        if (battlerData->battlerType & BATTLER_THEM) {
            battlerData->taskFuncs.setCommandSelection = Task_TrainerSetCommandSelection;
            battlerData->taskFuncs.showMoveSelectMenu = Task_TrainerShowMoveSelectMenu;
            battlerData->taskFuncs.showTargetSelectMenu = Task_TrainerShowTargetSelectMenu;
            battlerData->taskFuncs.showBagMenu = Task_TrainerShowBagMenu;
            battlerData->taskFuncs.showPartyMenu = Task_TrainerShowPartyMenu;
            battlerData->taskFuncs.showYesNoMenu = Task_TrainerShowYesNoMenu;
            battlerData->bootState = BATTLER_BOOT_STATE_AI;
        } else {
            battlerData->taskFuncs.setCommandSelection = Task_PlayerSetCommandSelection;
            battlerData->taskFuncs.showMoveSelectMenu = Task_PlayerShowMoveSelectMenu;
            battlerData->taskFuncs.showTargetSelectMenu = Task_PlayerShowTargetSelectMenu;
            battlerData->taskFuncs.showBagMenu = Task_PlayerShowBagMenu;
            battlerData->taskFuncs.showPartyMenu = Task_PlayerShowPartyMenu;
            battlerData->taskFuncs.showYesNoMenu = Task_PlayerShowYesNoMenu;
            battlerData->bootState = BATTLER_BOOT_STATE_NORMAL;
        }
    } else if (battleType & BATTLE_TYPE_UNK_17) {
        battlerData->taskFuncs.setCommandSelection = Task_TrainerSetCommandSelection;
        battlerData->taskFuncs.showMoveSelectMenu = Task_TrainerShowMoveSelectMenu;
        battlerData->taskFuncs.showTargetSelectMenu = Task_TrainerShowTargetSelectMenu;
        battlerData->taskFuncs.showBagMenu = Task_TrainerShowBagMenu;
        battlerData->taskFuncs.showPartyMenu = Task_TrainerShowPartyMenu;
        battlerData->taskFuncs.showYesNoMenu = Task_TrainerShowYesNoMenu;
        battlerData->bootState = BATTLER_BOOT_STATE_AI;
    }
}

extern "C" {

u8 BattlerData_GetBattlerType(BattlerData *battlerData) {
    return battlerData->battlerType;
}

u8 BattlerData_GetBootState(BattlerData *battlerData) {
    return battlerData->bootState;
}

HealthBox *BattlerData_GetHealthBox(BattlerData *battlerData) {
    return &battlerData->healthbox;
}

// TODO Empty; battle_main calls it for link battles where pokeplatinum calls sub_0207A744.
void fn_803AB52C(BattleSystem *battleSys) {}

// TODO Empty; SendMessage calls it for link battles where pokeplatinum calls sub_0207A81C.
void fn_803AB530(BattleSystem *battleSys, int recipient, int battler, void *message, u8 size) {}
}
