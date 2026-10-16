#pragma once

#include "ds/battle/battle_io_command.hpp"

void BattleDisplay_InitTaskSetupUI(void);
void BattleDisplay_InitTaskSetEncounter(BattleSystem *battleSys,
                                        BattlerData *battlerData,
                                        MonEncounterMessage *message);
void BattleDisplay_InitTaskShowEncounter(BattleSystem *battleSys, BattlerData *battlerData, MonShowMessage *message);
void BattleDisplay_InitTaskShowPokemon(BattleSystem *battleSys, BattlerData *battlerData, MonShowMessage *message);
void BattleDisplay_InitTaskReturnPokemon(BattleSystem *battleSys, BattlerData *battlerData, MonReturnMessage *message);
void BattleDisplay_InitTaskOpenCaptureBall(BattleSystem *battleSys,
                                           BattlerData *battlerData,
                                           OpenCaptureBallMessage *message);
void BattleDisplay_InitTaskSetTrainerEncounter(BattleSystem *battleSys,
                                               BattlerData *battlerData,
                                               TrainerEncounterMessage *message);
void BattleDisplay_InitTaskThrowTrainerBall(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            TrainerThrowBallMessage *message);
void BattleDisplay_InitTaskSlideTrainerOut(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_InitTaskSlideTrainerIn(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          TrainerSlideInMessage *message);
void BattleDisplay_InitTaskSlideHealthBoxIn(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            HealthBoxData *healthboxData);
void BattleDisplay_InitTaskSlideHealthBoxOut(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_InitTaskSetCommandSelection(BattleSystem *battleSys,
                                               BattlerData *battlerData,
                                               CommandSetMessage *message);
void BattleDisplay_InitTaskShowMoveSelectMenu(BattleSystem *battleSys,
                                              BattlerData *battlerData,
                                              MoveSelectMenuMessage *message);
void BattleDisplay_InitTaskShowTargetSelectMenu(BattleSystem *battleSys,
                                                BattlerData *battlerData,
                                                TargetSelectMenuMessage *message);
void BattleDisplay_InitTaskShowBagMenu(BattleSystem *battleSys, BattlerData *battlerData, BagMenuMessage *message);
void BattleDisplay_InitTaskShowPartyMenu(BattleSystem *battleSys, BattlerData *battlerData, PartyMenuMessage *message);
void BattleDisplay_InitTaskShowYesNoMenu(BattleSystem *battleSys, BattlerData *battlerData, YesNoMenuMessage *message);
void BattleDisplay_PrintAttackMessage(BattleSystem *battleSys, BattlerData *battlerData, AttackMsgMessage *message);
void BattleDisplay_PrintMessage(BattleSystem *battleSys, BattlerData *battlerData, BattleMessage *battleMsg);
void BattleDisplay_InitTaskSetMoveAnimation(BattleSystem *battleSys,
                                            BattlerData *battlerData,
                                            MoveAnimation *animation);
void BattleDisplay_InitTaskFlickerBattler(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_InitTaskUpdateHPGauge(BattleSystem *battleSys,
                                         BattlerData *battlerData,
                                         HPGaugeUpdateMessage *message);
void BattleDisplay_InitTaskUpdateExpGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          ExpGaugeUpdateMessage *message);
void BattleDisplay_InitTaskPlayFaintingSequence(BattleSystem *battleSys,
                                                BattlerData *battlerData,
                                                FaintingSequenceMessage *message);
void BattleDisplay_PlaySound(BattleSystem *battleSys, BattlerData *battlerData, PlaySoundMessage *message);
void BattleDisplay_InitTaskFadeOut(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_InitTaskToggleVanish(BattleSystem *battleSys,
                                        BattlerData *battlerData,
                                        ToggleVanishMessage *message);
void BattleDisplay_SetStatusIcon(BattleSystem *battleSys, BattlerData *battlerData, SetStatusIconMessage *message);
void BattleDisplay_PrintTrainerMessage(BattleSystem *battleSys, BattlerData *battlerData, TrainerMsgMessage *message);
void BattleDisplay_PrintRecallMessage(BattleSystem *battleSys, BattlerData *battlerData, RecallMsgMessage *message);
void BattleDisplay_PrintSendOutMessage(BattleSystem *battleSys, BattlerData *battlerData, SendOutMsgMessage *message);
void BattleDisplay_PrintBattleStartMessage(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_PrintLeadMonMessage(BattleSystem *battleSys, BattlerData *battlerData, LeadMonMsgMessage *message);
void BattleDisplay_InitTaskPlayLevelUpAnimation(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_SetAlertMessage(BattleSystem *battleSys, BattlerData *battlerData, AlertMsgMessage *message);
void BattleDisplay_RefreshHPGauge(BattleSystem *battleSys, BattlerData *battlerData, RefreshHPGaugeMessage *message);
void BattleDisplay_InitTaskForgetMove(BattleSystem *battleSys, BattlerData *battlerData, ForgetMoveMessage *message);
void BattleDisplay_InitTaskSetMosaic(BattleSystem *battleSys, BattlerData *battlerData, MosaicSetMessage *message);
void BattleDisplay_InitTaskShowBattleStartPartyGauge(BattleSystem *battleSys,
                                                     BattlerData *battlerData,
                                                     PartyGaugeData *partyGauge);
void BattleDisplay_InitTaskHideBattleStartPartyGauge(BattleSystem *battleSys,
                                                     BattlerData *battlerData,
                                                     PartyGaugeData *partyGauge);
void BattleDisplay_InitTaskShowPartyGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          PartyGaugeData *partyGauge);
void BattleDisplay_InitTaskHidePartyGauge(BattleSystem *battleSys,
                                          BattlerData *battlerData,
                                          PartyGaugeData *partyGauge);
void BattleDisplay_PrintLinkWaitMessage(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_RestoreSprite(BattleSystem *battleSys, BattlerData *battlerData, MoveAnimation *animation);
void BattleDisplay_InitTaskSpriteToOAM(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_InitTaskOAMToSprite(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_PrintResultMessage(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_PrintEscapeMessage(BattleSystem *battleSys, BattlerData *battlerData, EscapeMsgMessage *message);
void BattleDisplay_PrintForfeitMessage(BattleSystem *battleSys, BattlerData *battlerData);
void BattleDisplay_RefreshSprite(BattleSystem *battleSys, BattlerData *battlerData, MoveAnimation *animation);
void BattleDisplay_FlyMoveHitSoundEffect(BattleSystem *battleSys,
                                         BattlerData *battlerData,
                                         MoveHitSoundMessage *message);
void BattleDisplay_PlayMusic(BattleSystem *battleSys, BattlerData *battlerData, MusicPlayMessage *message);

void BattlerData_SetTaskFuncs(BattleSystem *battleSys, BattlerData *battlerData);

extern "C" {
u8 BattlerData_GetBootState(BattlerData *battlerData);
HealthBox *BattlerData_GetHealthBox(BattlerData *battlerData);
void fn_803AB52C(BattleSystem *battleSys);
void fn_803AB530(BattleSystem *battleSys, int recipient, int battler, void *message, u8 size);
}
