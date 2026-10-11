#include "ds/battle/battle_io_command.hpp"

#include "ds/DSbridge.hpp"
#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_controller.hpp"
#include "ds/constants/abilities.hpp"
#include "ds/constants/moves.hpp"
#include "ds/party.hpp"
#include "ds/pokemon.hpp"

#include <string.h>

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
// BattleDisplay_InitTaskSetupUI
void fn_803A7418(void);
// BattleDisplay_InitTaskSetEncounter
void fn_803A742C(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowEncounter
void fn_803A74B8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowPokemon
void fn_803A7524(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskReturnPokemon
void fn_803A75A0(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskOpenCaptureBall
void fn_803A7628(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSetTrainerEncounter
void fn_803A7694(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskThrowTrainerBall
void fn_803A7708(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSlideTrainerOut
void fn_803A7774(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_InitTaskSlideTrainerIn
void fn_803A77E4(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSlideHealthBoxIn
void fn_803A7858(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSlideHealthBoxOut
void fn_803A78CC(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_InitTaskSetCommandSelection
void fn_803A7940(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowMoveSelectMenu
void fn_803A7AB8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowTargetSelectMenu
void fn_803A7B88(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowBagMenu
void fn_803A7C9C(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowPartyMenu
void fn_803A7DC8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowYesNoMenu
void fn_803A7EAC(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintAttackMessage
void fn_803A7F44(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintMessage
void fn_803A8010(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSetMoveAnimation
void fn_803A80A8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskFlickerBattler
void fn_803A828C(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_InitTaskUpdateHPGauge
void fn_803A82EC(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskUpdateExpGauge
void fn_803A83B4(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskPlayFaintingSequence
void fn_803A8444(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PlaySound
void fn_803A84C0(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskFadeOut
void fn_803A84CC(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_InitTaskToggleVanish
void fn_803A853C(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_SetStatusIcon
void fn_803A85A8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintTrainerMessage
void fn_803A85B4(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintRecallMessage
void fn_803A8620(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintSendOutMessage
void fn_803A87D0(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintBattleStartMessage
void fn_803A8980(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_PrintLeadMonMessage
void fn_803A8B14(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskPlayLevelUpAnimation
void fn_803A9068(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_SetAlertMessage
void fn_803A90D0(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_RefreshHPGauge
void fn_803A9264(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskForgetMove
void fn_803A9270(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSetMosaic
void fn_803A92F4(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowBattleStartPartyGauge
void fn_803A9360(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskHideBattleStartPartyGauge
void fn_803A93CC(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskShowPartyGauge
void fn_803A9438(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskHidePartyGauge
void fn_803A94A4(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintLinkWaitMessage
void fn_803A9510(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_RestoreSprite
void fn_803A951C(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_InitTaskSpriteToOAM
void fn_803A9528(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_InitTaskOAMToSprite
void fn_803A9590(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_PrintResultMessage
void fn_803A95A4(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_PrintEscapeMessage
void fn_803A975C(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PrintForfeitMessage
void fn_803A989C(BattleSystem *battleSys, BattlerData *battlerData);
// BattleDisplay_RefreshSprite
void fn_803A99A0(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_FlyMoveHitSoundEffect
void fn_803A99AC(BattleSystem *battleSys, BattlerData *battlerData, void *message);
// BattleDisplay_PlayMusic
void fn_803A99B8(BattleSystem *battleSys, BattlerData *battlerData, void *message);
}

static void BtlIOCmd_None(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetupUI(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetEncounter(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowEncounter(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowPokemon(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ReturnPokemon(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_OpenCaptureBall(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_DeletePokemon(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetTrainerEncounter(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ThrowTrainerBall(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SlideTrainerOut(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SlideTrainerIn(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SlideHealthBoxIn(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SlideHealthBoxOut(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetCommandSelection(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowMoveSelectMenu(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowTargetSelectMenu(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowBagMenu(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowPartyMenu(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowYesNoMenu(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintAttackMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintBattleMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetMoveAnimation(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_FlickerBattler(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_UpdateHPGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_UpdateExpGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PlayFaintingSequence(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PlaySound(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_FadeOut(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ToggleVanish(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetStatusIcon(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintTrainerMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintRecallMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintSendOutMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintBattleStartMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintLeadMonMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PlayLevelUpAnimation(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetAlertMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_RefreshHPGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_UpdatePartyMon(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SlideInPanel(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_StopGaugeAnimation(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_RefreshPartyStatus(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ForgetMove(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SetMosaic(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ChangeWeatherForm(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_UpdateBg(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ClearTouchScreen(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowBattleStartPartyGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_HideBattleStartPartyGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ShowPartyGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_HidePartyGauge(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_LoadPartyGaugeGraphics(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_FreePartyGaugeGraphics(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_IncrementRecord(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintLinkWaitMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_RestoreSprite(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SpriteToOAM(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_OAMToSprite(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintResultMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintEscapeMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PrintForfeitMessage(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_RefreshSprite(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_FlyMoveHitSoundEffect(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_PlayMusic(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_SubmitResult(BattleSystem *battleSys, BattlerData *battlerData);
static void BtlIOCmd_ClearMessageBox(BattleSystem *battleSys, BattlerData *battlerData);

static inline void ZeroDataBuffer(BattlerData *battlerData) {
    battlerData->data[0] = 0;
}

BattlerData *BattlerData_New(BattleSystem *battleSys, BattlerInitData *battlerInitData) {
    BattlerData *battlerData = (BattlerData *)fn_8016DF70(HEAP_ID_BATTLE, sizeof(BattlerData));

    memset(battlerData, 0, sizeof(BattlerData));
    battlerData->battler = battlerInitData->battler;
    battlerData->battlerType = battlerInitData->battlerType;

    return battlerData;
}

static void (*const sBattleCommands[])(BattleSystem *battleSys, BattlerData *battlerData) = {
    BtlIOCmd_None,
    BtlIOCmd_SetupUI,
    BtlIOCmd_SetEncounter,
    BtlIOCmd_ShowEncounter,
    BtlIOCmd_ShowPokemon,
    BtlIOCmd_ReturnPokemon,
    BtlIOCmd_OpenCaptureBall,
    BtlIOCmd_DeletePokemon,
    BtlIOCmd_SetTrainerEncounter,
    BtlIOCmd_ThrowTrainerBall,
    BtlIOCmd_SlideTrainerOut,
    BtlIOCmd_SlideTrainerIn,
    BtlIOCmd_SlideHealthBoxIn,
    BtlIOCmd_SlideHealthBoxOut,
    BtlIOCmd_SetCommandSelection,
    BtlIOCmd_ShowMoveSelectMenu,
    BtlIOCmd_ShowTargetSelectMenu,
    BtlIOCmd_ShowBagMenu,
    BtlIOCmd_ShowPartyMenu,
    BtlIOCmd_ShowYesNoMenu,
    BtlIOCmd_PrintAttackMessage,
    BtlIOCmd_PrintBattleMessage,
    BtlIOCmd_SetMoveAnimation,
    BtlIOCmd_FlickerBattler,
    BtlIOCmd_UpdateHPGauge,
    BtlIOCmd_UpdateExpGauge,
    BtlIOCmd_PlayFaintingSequence,
    BtlIOCmd_PlaySound,
    BtlIOCmd_FadeOut,
    BtlIOCmd_ToggleVanish,
    BtlIOCmd_SetStatusIcon,
    BtlIOCmd_PrintTrainerMessage,
    BtlIOCmd_PrintRecallMessage,
    BtlIOCmd_PrintSendOutMessage,
    BtlIOCmd_PrintBattleStartMessage,
    BtlIOCmd_PrintLeadMonMessage,
    BtlIOCmd_PlayLevelUpAnimation,
    BtlIOCmd_SetAlertMessage,
    BtlIOCmd_RefreshHPGauge,
    BtlIOCmd_UpdatePartyMon,
    BtlIOCmd_SlideInPanel,
    BtlIOCmd_StopGaugeAnimation,
    BtlIOCmd_RefreshPartyStatus,
    BtlIOCmd_ForgetMove,
    BtlIOCmd_SetMosaic,
    BtlIOCmd_ChangeWeatherForm,
    BtlIOCmd_UpdateBg,
    BtlIOCmd_ClearTouchScreen,
    BtlIOCmd_ShowBattleStartPartyGauge,
    BtlIOCmd_HideBattleStartPartyGauge,
    BtlIOCmd_ShowPartyGauge,
    BtlIOCmd_HidePartyGauge,
    BtlIOCmd_LoadPartyGaugeGraphics,
    BtlIOCmd_FreePartyGaugeGraphics,
    BtlIOCmd_IncrementRecord,
    BtlIOCmd_PrintLinkWaitMessage,
    BtlIOCmd_RestoreSprite,
    BtlIOCmd_SpriteToOAM,
    BtlIOCmd_OAMToSprite,
    BtlIOCmd_PrintResultMessage,
    BtlIOCmd_PrintEscapeMessage,
    BtlIOCmd_PrintForfeitMessage,
    BtlIOCmd_RefreshSprite,
    BtlIOCmd_FlyMoveHitSoundEffect,
    BtlIOCmd_PlayMusic,
    BtlIOCmd_SubmitResult,
    BtlIOCmd_ClearMessageBox,
    NULL,
};

void BattleSystem_ExecuteBattlerCommand(BattleSystem *battleSys, BattlerData *battlerData) {
    if (battlerData->data[0]) {
        sBattleCommands[battlerData->data[0]](battleSys, battlerData);
    }
}

void BattlerData_Delete(BattleSystem *battleSys, BattlerData *battlerData, int renderMode) {
    if (renderMode != 2) {
        fn_803D9808(battlerData->healthbox);
    }

    fn_803D9850(battlerData);
    fn_8016E0A0(battlerData);
}

static void BtlIOCmd_None(BattleSystem *battleSys, BattlerData *battlerData) {
    return;
}

static void BtlIOCmd_SetupUI(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7418();
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_SETUP_UI);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetEncounter(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A742C(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowEncounter(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A74B8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowPokemon(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7524(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ReturnPokemon(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A75A0(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_OpenCaptureBall(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7628(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_DeletePokemon(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803D9804(battlerData->monSprite);
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_DELETE_POKEMON);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetTrainerEncounter(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7694(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ThrowTrainerBall(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7708(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SlideTrainerOut(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7774(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SlideTrainerIn(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A77E4(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SlideHealthBoxIn(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7858(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SlideHealthBoxOut(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A78CC(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetCommandSelection(BattleSystem *battleSys, BattlerData *battlerData) {
    CommandSetMessage *message = (CommandSetMessage *)&battlerData->data[0];

    BattleSystem_SetUnread_2440(battleSys, message->switchingOrCanPickCommandMask);
    fn_803A7940(battleSys, battlerData, message);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowMoveSelectMenu(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7AB8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowTargetSelectMenu(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7B88(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowBagMenu(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7C9C(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowPartyMenu(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7DC8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowYesNoMenu(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7EAC(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintAttackMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A7F44(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintBattleMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A8010(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetMoveAnimation(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A80A8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_FlickerBattler(BattleSystem *battleSys, BattlerData *battlerData) {
    if (fn_803D97FC(battlerData->monSprite, MON_SPRITE_HIDE) == TRUE) {
        BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_FLICKER_BATTLER);
    } else {
        fn_803A828C(battleSys, battlerData);
    }

    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_UpdateHPGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A82EC(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_UpdateExpGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A83B4(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PlayFaintingSequence(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A8444(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PlaySound(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A84C0(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_FadeOut(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A84CC(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ToggleVanish(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A853C(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetStatusIcon(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A85A8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintTrainerMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A85B4(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintRecallMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A8620(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintSendOutMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A87D0(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintBattleStartMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A8980(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintLeadMonMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A8B14(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PlayLevelUpAnimation(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9068(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetAlertMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A90D0(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_RefreshHPGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9264(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_UpdatePartyMon(BattleSystem *battleSys, BattlerData *battlerData) {
    UpdatePartyMonMessage *message = (UpdatePartyMonMessage *)&battlerData->data[0];
    int i;
    Pokemon *mon = BattleSystem_GetPartyPokemon(battleSys, battlerData->battler, message->partySlot);

    if ((message->statusVolatile & VOLATILE_CONDITION_TRANSFORM) == FALSE) {
        for (i = 0; i < LEARNED_MOVES_MAX; i++) {
            if ((message->mimickedMoveSlot & FlagIndex(i)) == FALSE) {
                u32 move = message->moves[i];
                u32 pp = message->ppCur[i];

                Pokemon_SetValue(mon, MON_DATA_MOVE1 + i, &move);
                Pokemon_SetValue(mon, MON_DATA_MOVE1_PP + i, &pp);
            }
        }
    }

    if ((message->knockedOffItemsMask & FlagIndex(message->partySlot)) == FALSE) {
        u32 heldItem = message->heldItem;

        Pokemon_SetValue(mon, MON_DATA_HELD_ITEM, &heldItem);
    }

    u32 curHP = message->curHP;

    Pokemon_SetValue(mon, MON_DATA_HP, &curHP);
    Pokemon_SetValue(mon, MON_DATA_STATUS, &message->status);

    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SlideInPanel(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, battlerData->data[0]);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_StopGaugeAnimation(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803D980C(battlerData->healthbox);
    fn_803D9850(battlerData);
    BattleController_EmitClearCommand(battleSys, battlerData->battler, battlerData->data[0]);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_RefreshPartyStatus(BattleSystem *battleSys, BattlerData *battlerData) {
    RefreshPartyStatusMessage *message = (RefreshPartyStatusMessage *)&battlerData->data[0];
    Pokemon *mon;
    int i, partyCount, ability;
    u32 clearedStatus = 0;
    partyCount = BattleSystem_GetPartyCount(battleSys, battlerData->battler);

    for (i = 0; i < partyCount; i++) {
        mon = BattleSystem_GetPartyPokemon(battleSys, battlerData->battler, i);

        if (message->ability == ABILITY_MOLD_BREAKER) {
            ability = ABILITY_NONE;
        } else {
            ability = Pokemon_GetValue(mon, MON_DATA_ABILITY, NULL);
        }

        if (message->move != MOVE_HEAL_BELL || (message->move == MOVE_HEAL_BELL && ability != ABILITY_SOUNDPROOF)) {
            Pokemon_SetValue(mon, MON_DATA_STATUS, &clearedStatus);
        }
    }

    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ForgetMove(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9270(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SetMosaic(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A92F4(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ChangeWeatherForm(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, battlerData->data[0]);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_UpdateBg(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_UPDATE_BG);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ClearTouchScreen(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_CLEAR_TOUCH_SCREEN);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowBattleStartPartyGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9360(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_HideBattleStartPartyGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A93CC(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ShowPartyGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    PartyGaugeData *data = (PartyGaugeData *)&battlerData->data[0];

    if (BattleSystem_GetBattlerSide(battleSys, battlerData->battler)) {
        fn_803A9438(battleSys, battlerData, data);
    } else {
        BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_SHOW_PARTY_GAUGE);
    }

    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_HidePartyGauge(BattleSystem *battleSys, BattlerData *battlerData) {
    PartyGaugeData *data = (PartyGaugeData *)&battlerData->data[0];

    if (BattleSystem_GetBattlerSide(battleSys, battlerData->battler)) {
        fn_803A94A4(battleSys, battlerData, data);
    } else {
        BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_HIDE_PARTY_GAUGE);
    }

    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_LoadPartyGaugeGraphics(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_LOAD_PARTY_GAUGE_GRAPHICS);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_FreePartyGaugeGraphics(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_FREE_PARTY_GAUGE_GRAPHICS);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_IncrementRecord(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, battlerData->data[0]);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintLinkWaitMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9510(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_RestoreSprite(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A951C(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SpriteToOAM(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9528(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_OAMToSprite(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A9590(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintResultMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A95A4(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintEscapeMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A975C(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PrintForfeitMessage(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A989C(battleSys, battlerData);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_RefreshSprite(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A99A0(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_FlyMoveHitSoundEffect(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A99AC(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_PlayMusic(BattleSystem *battleSys, BattlerData *battlerData) {
    fn_803A99B8(battleSys, battlerData, battlerData->data);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_SubmitResult(BattleSystem *battleSys, BattlerData *battlerData) {
    ResultSubmitMessage *message = (ResultSubmitMessage *)&battlerData->data[0];
    Party *party;
    Pokemon *mon;
    int slot;
    int battler;
    int playerHP = 0;
    int enemyHP = 0;

    if (BattleSystem_GetBattleType(battleSys) & BATTLE_TYPE_FRONTIER) {
        BattleSystem_SetResultMask(battleSys, message->resultMask);
    } else {
        for (battler = 0; battler < BattleSystem_GetMaxBattlers(battleSys); battler++) {
            party = BattleSystem_GetParty(battleSys, battler);

            for (slot = 0; slot < Party_GetCurrentCount(party); slot++) {
                mon = Party_GetPokemonBySlotIndex(party, slot);

                if (Pokemon_GetValue(mon, MON_DATA_SPECIES, NULL) &&
                    Pokemon_GetValue(mon, MON_DATA_IS_EGG, NULL) == FALSE) {
                    if (BattleSystem_GetBattlerSide(battleSys, battler)) {
                        enemyHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                    } else {
                        playerHP += Pokemon_GetValue(mon, MON_DATA_HP, NULL);
                    }
                }
            }
        }

        if (playerHP == 0 && enemyHP == 0) {
            BattleSystem_SetResultMask(battleSys, BATTLE_RESULT_DRAW);
        } else if (playerHP == 0) {
            BattleSystem_SetResultMask(battleSys, BATTLE_RESULT_LOSE);
        } else {
            BattleSystem_SetResultMask(battleSys, BATTLE_RESULT_WIN);
        }
    }

    BattleController_EmitClearCommand(battleSys, battlerData->battler, message->command);
    ZeroDataBuffer(battlerData);
}

static void BtlIOCmd_ClearMessageBox(BattleSystem *battleSys, BattlerData *battlerData) {
    BattleController_EmitClearCommand(battleSys, battlerData->battler, BATTLE_COMMAND_CLEAR_MESSAGE_BOX);
    ZeroDataBuffer(battlerData);
}
