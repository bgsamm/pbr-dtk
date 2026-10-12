#pragma once

#include "ds/battle/battle_context.hpp"
#include "ds/trainer_data.hpp"

struct BattlerData;
struct HealthBox;
struct Party;
struct Pokemon;
struct Strbuf;
struct TrainerInfo;
struct MessageLoader;
struct PCBoxes;
struct StringTemplate;

// Only the fields used so far (pokeplatinum BattleSystem; the layout is the same up to 0xAC).
// size: unknown
struct BattleSystem {
    /* 0x0 */ u8 unk0[0x4];
    /* 0x4 */ void *bgConfig;
    /* 0x8 */ u8 unk8[0x4];
    /* 0xC */ MessageLoader *msgLoader;
    /* 0x10 */ MessageLoader *attackMsgLoader;
    /* 0x14 */ StringTemplate *strFormatter;
    /* 0x18 */ Strbuf *msgBuffer;
    /* 0x1C */ u8 unk1C[0x10];
    /* 0x2C */ u32 battleType;
    /* 0x30 */ BattleContext *battleCtx;
    /* 0x34 */ BattlerData *battlers[MAX_BATTLERS];
    /* 0x44 */ int maxBattlers;
    /* 0x48 */ TrainerInfo *trainerInfo[MAX_BATTLERS];
    /* 0x58 */ u8 unk58[0x4];
    /* 0x5C */ void *bagCursor;
    /* 0x60 */ void *pokedex;
    /* 0x64 */ PCBoxes *pcBoxes;
    /* 0x68 */ Party *parties[MAX_BATTLERS];
    /* 0x78 */ void *chatotCries[MAX_BATTLERS];
    /* 0x88 */ u8 unk88[0x10];
    /* 0x98 */ u32 poketch;
    /* 0x9C */ u32 captureAttempt;
    /* 0xA0 */ u16 trainerIDs[MAX_BATTLERS];
    /* 0xA8 */ u8 unwritten[MAX_BATTLERS];
    /* 0xAC */ Trainer trainers[MAX_BATTLERS];
    /* 0x15C */ u8 unk15C[0x8];
    /* 0x164 */ void *unk164;
    /* 0x168 */ u8 unk168[0x14];
    /* 0x17C */ u32 options;
    /* 0x180 */ u32 palPad;
    /* 0x184 */ u8 unk184[0x5C];
    /* 0x1E0 */ u32 records;
    /* 0x1E4 */ u8 unk1E4[0x1008];
    /* 0x11EC */ u8 serverMessage[0x11C6];
    /* 0x23B2 */ u16 serverReadIndex;
    /* 0x23B4 */ u16 serverWriteIndex;
    /* 0x23B6 */ u16 serverEndIndex;
    /* 0x23B8 */ u8 unk23B8[0x8];
    /* 0x23C0 */ u8 battleInitialized;
    /* 0x23C1 */ u8 renderMode;
    /* 0x23C2 */ u8 commandIsEndWait;
    /* 0x23C3 */ u8 pendingBlendReset : 1;
    /* 0x23C3 */ u8 pendingBattleVRAMSetup : 1;
    /* 0x23C3 */ u8 pendingSubMenuVRAMSetup : 1;
    /* 0x23C3 */ u8 redHPSoundFlag : 2;
    /* 0x23C3 */ u8 redHPSoundEffectDelay : 3;
    /* 0x23C4 */ int terrain;
    /* 0x23C8 */ int background;
    /* 0x23CC */ int mapHeader;
    /* 0x23D0 */ u32 battleStatusMask;
    /* 0x23D4 */ int time;
    /* 0x23D8 */ int safariBalls;
    /* 0x23DC */ u8 battleParticipantMask[MAX_BATTLERS];
    /* 0x23E0 */ u32 rulesetMask;
    /* 0x23E4 */ u8 resultMask;
    /* 0x23E5 */ u8 unk23E5[0x3];
    /* 0x23E8 */ u32 mapEvolutionMethod;
    /* 0x23EC */ u32 visitedContestHall;
    /* 0x23F0 */ int fieldWeather;
    /* 0x23F4 */ u32 metBebe;
    /* 0x23F8 */ u8 unk23F8[0xC];
    /* 0x2404 */ u32 commandSelectionFlags;
    /* 0x2408 */ u8 unk2408;
};

// TODO Defined in unit 803A60D8, which is not decompiled yet
extern "C" {
void *BattleSystem_GetBgConfig(BattleSystem *battleSys);
u32 BattleSystem_GetBattleType(BattleSystem *battleSys);
BattleContext *BattleSystem_GetBattleContext(BattleSystem *battleSys);
BattlerData *BattleSystem_GetBattlerData(BattleSystem *battleSys, int battler);
int BattleSystem_GetMaxBattlers(BattleSystem *battleSys);
Pokemon *BattleSystem_GetPartyPokemon(BattleSystem *battleSys, int battler, int partySlot);
u8 BattleSystem_GetBattlerSide(BattleSystem *battleSys, int battler);
u8 BattlerData_GetBattlerType(BattlerData *battlerData);
Party *BattleSystem_GetParty(BattleSystem *battleSys, int battler);
int BattleSystem_GetPartyCount(BattleSystem *battleSys, int battler);
u8 BattleSystem_GetBattlerType(BattleSystem *battleSys, int battler);
int BattleSystem_GetPartner(BattleSystem *battleSys, int battler);
int BattleSystem_GetEnemyInSlot(BattleSystem *battleSys, int battler, int slot);
u16 Battler_GetTrainerID(BattleSystem *battleSys, int battler);
int BattleSystem_GetFieldWeather(BattleSystem *battleSys);
TrainerInfo *BattleSystem_GetTrainerInfo(BattleSystem *battleSys, int battler);
u8 fn_803ADCD8(BattleSystem *battleSys); // BattleSystem_GetResultMask
void BattleSystem_SetResultMask(BattleSystem *battleSys, u8 resultMask);
HealthBox *BattleSystem_GetHealthBox(BattleSystem *battleSys, int battler);
BOOL BattleSystem_UseBagItem(BattleSystem *battleSys, int battler, int partySlot, int moveSlot, int item);
u8 BattleMessage_Print(BattleSystem *battleSys, MessageLoader *msgLoader, BattleMessage *battleMsg, int renderDelay);
void fn_803ADEF0(BattleMessage *dst, BattleMessage *src);
void BattleMessage_CheckSide(BattleSystem *battleSys, BattleMessage *battleMsg, int swapSides);
void BattleMessage_FillFormatBuffers(BattleSystem *battleSys,
                                     BattleMessage *battleMsg,
                                     MessageLoader *msgLoader,
                                     int swapSides);
void BattleMessage_Format(BattleSystem *battleSys, MessageLoader *msgLoader, BattleMessage *battleMsg);
void fn_803AF38C(BattleSystem *battleSys, BattleMessage *battleMsg, MessageLoader *msgLoader);
void fn_803AF0D8(BattleSystem *battleSys, u32 idx, int offset, MessageLoader *msgLoader, u32 msgID);
void BattleMessage_SetNickname(BattleSystem *battleSys, u32 idx, int nicknameTag, int swapSides);
Trainer *fn_803ACB30(BattleSystem *battleSys, int battler);
int BattleSystem_GetBattlerOfType(BattleSystem *battleSys, int type);
void *BattleSystem_GetChatotCry(BattleSystem *battleSys, int battler);
void BattleSystem_GetBattleParticipantMask(BattleSystem *battleSys, int battler, int partySlot);
void BattleSystem_SetBattlersByType(BattleSystem *battleSys, u8 *battlersByType);
void BattleSystem_SetBattlerTypes(BattleSystem *battleSys, u8 *battlerTypes);
u32 BattleSystem_CalcMoneyPenalty(Party *party, TrainerInfo *trainerInfo);
void *fn_803ACA58(BattleSystem *battleSys);
MessageLoader *BattleSystem_GetMessageLoader(BattleSystem *battleSys);
MessageLoader *BattleSystem_GetAttackMessageLoader(BattleSystem *battleSys);
u8 *BattleSystem_GetServerMessage(BattleSystem *battleSys);
u16 *BattleSystem_GetServerReadIndex(BattleSystem *battleSys);
u16 *BattleSystem_GetServerWriteIndex(BattleSystem *battleSys);
u16 *BattleSystem_GetServerEndIndex(BattleSystem *battleSys);
Strbuf *BattleSystem_GetMsgBuffer(BattleSystem *battleSys);
int BattleSystem_GetTerrain(BattleSystem *battleSys);
int BattleSystem_GetMapHeader(BattleSystem *battleSys);
u32 BattleSystem_GetBattleStatusMask(BattleSystem *battleSys);
u8 BattleSystem_IsInitialized(BattleSystem *battleSys);
int BattleSystem_GetNumSafariBalls(BattleSystem *battleSys);
BOOL BattleSystem_HasCaughtSpecies(BattleSystem *battleSys, int species);
u8 BattleSystem_GetTextSpeed(BattleSystem *battleSys);
int BattleSystem_GetBattleStyle(BattleSystem *battleSys);
// TODO probably BattleSystem_GetRulesetMask (pret)
u32 fn_803AF43C(BattleSystem *battleSys);
void BattleSystem_SetCommandSelectionFlags(BattleSystem *battleSys, u32 flags);
void BattleSystem_SetUnread_2440(BattleSystem *battleSys, u8 value);
void BattleSystem_SetRedHPSoundFlag(BattleSystem *battleSys, u8 flag);
}

// TODO Set by BattleDisplay_SetAlertMessage while it prints for some battle types; BattleMessage_CheckSide then
// keeps the message as it is.
extern u32 lbl_806405C8;
