#pragma once

#include "ds/battle/battle_context.hpp"

struct BattlerData;
struct Party;
struct Pokemon;
struct Strbuf;
struct TrainerInfo;

// Only the fields used so far (pokeplatinum BattleSystem).
// size: unknown
struct BattleSystem {
    /* 0x0 */ u8 unk0[0x18];
    /* 0x18 */ Strbuf *msgBuffer;
    /* 0x1C */ u8 unk1C[0x10];
    /* 0x2C */ u32 battleType;
    /* 0x30 */ BattleContext *battleCtx;
    /* 0x34 */ BattlerData *battlers[MAX_BATTLERS];
    /* 0x44 */ int maxBattlers;
    /* 0x48 */ TrainerInfo *trainerInfo[MAX_BATTLERS];
};

// TODO Defined in unit 803A60D8, which is not decompiled yet
extern "C" {
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
}
