#pragma once

#include "ds/battle/battle_context.hpp"
#include "ds/battle/battle_system.hpp"

BattleContext *BattleContext_New(BattleSystem *battleSys);
BOOL BattleContext_Main(BattleSystem *battleSys, BattleContext *battleCtx);
void BattleContext_Free(BattleContext *battleCtx);
void BattleControllerPlayer_CheckMoveHit(
    BattleSystem *battleSys, BattleContext *battleCtx, int attacker, int defender, int move);
