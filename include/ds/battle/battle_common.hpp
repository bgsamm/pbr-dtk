#pragma once

#include "ds/battle/battle_constants.hpp"

#include <revolution/types.h>

// size: 0x2
struct Fraction {
    /* 0x0 */ u8 numerator;
    /* 0x1 */ u8 denominator;
};

// Shorthands used throughout the battle code, as in pret/pokeplatinum.
// They expect battleSys and battleCtx in scope.

#define ATTACKING_MON (battleCtx->battleMons[battleCtx->attacker])
#define ATTACKER_TURN_FLAGS (battleCtx->turnFlags[battleCtx->attacker])
#define DEFENDING_MON (battleCtx->battleMons[battleCtx->defender])
#define ATTACKER_SELF_TURN_FLAGS (battleCtx->selfTurnFlags[battleCtx->attacker])
#define DEFENDER_TURN_FLAGS (battleCtx->turnFlags[battleCtx->defender])
#define DEFENDER_SELF_TURN_FLAGS (battleCtx->selfTurnFlags[battleCtx->defender])
#define FOLLOW_ME_MON(side) (battleCtx->battleMons[battleCtx->sideConditions[side].followMeUser])
#define CURRENT_MOVE_DATA (battleCtx->aiContext.moveTable[battleCtx->moveCur])
#define MOVE_DATA(move) (battleCtx->aiContext.moveTable[move])
#define ITEM_DATA(item, param) (Item_Get(ItemTable_Index(battleCtx->aiContext.itemTable, (item)), (param)))

#define LOAD_SUBSEQ(script) (BattleSystem_LoadScript(battleCtx, NARC_BATTLE_SUB_SEQ, script))

#define NO_CLOUD_NINE                                                                                                  \
    (BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALIVE_BATTLERS, 0, ABILITY_CLOUD_NINE) == FALSE &&          \
     BattleSystem_CountAbility(battleSys, battleCtx, COUNT_ALIVE_BATTLERS, 0, ABILITY_AIR_LOCK) == FALSE)
#define WEATHER_IS_RAIN (battleCtx->fieldConditionsMask & FIELD_CONDITION_RAINING)
#define WEATHER_IS_SAND (battleCtx->fieldConditionsMask & FIELD_CONDITION_SANDSTORM)
#define WEATHER_IS_SUN (battleCtx->fieldConditionsMask & FIELD_CONDITION_SUNNY)
#define WEATHER_IS_HAIL (battleCtx->fieldConditionsMask & FIELD_CONDITION_HAILING)

#define MON_IS_IDENTIFIED(battler)                                                                                     \
    ((battleCtx->battleMons[battler].statusVolatile & VOLATILE_CONDITION_FORESIGHT) ||                                 \
     (battleCtx->battleMons[battler].moveEffectsMask & MOVE_EFFECT_MIRACLE_EYE))
#define MON_IS_UPROARING(battler)                                                                                      \
    (battleCtx->fieldConditionsMask & (FlagIndex(battler) << FIELD_CONDITION_UPROAR_SHIFT))
#define MON_IS_LOCKED_ONTO(attacker, defender)                                                                         \
    ((battleCtx->battleMons[defender].moveEffectsMask & MOVE_EFFECT_LOCK_ON) &&                                        \
     battleCtx->battleMons[defender].moveEffectsData.lockOnTarget == attacker)

#define MON_HAS_TYPE(mon, type)                                                                                        \
    (BattleMon_Get(battleCtx, mon, BATTLEMON_TYPE_1, NULL) == type ||                                                  \
     BattleMon_Get(battleCtx, mon, BATTLEMON_TYPE_2, NULL) == type)
#define MON_IS_NOT_TYPE(mon, type)                                                                                     \
    (BattleMon_Get(battleCtx, mon, BATTLEMON_TYPE_1, NULL) != type &&                                                  \
     BattleMon_Get(battleCtx, mon, BATTLEMON_TYPE_2, NULL) != type)

#define FLAG_NEGATE(flag) ((flag) ^ 0xFFFFFFFF)

#define BATTLER_US 0
#define BATTLER_THEM 1

// Damage of a typeless hit of the given power from the attacker on itself
#define CALC_SELF_HIT(move, power)                                                                                     \
    (BattleSystem_CalcMoveDamage(battleSys,                                                                            \
                                 battleCtx,                                                                            \
                                 move,                                                                                 \
                                 0,                                                                                    \
                                 0,                                                                                    \
                                 power,                                                                                \
                                 0,                                                                                    \
                                 battleCtx->attacker,                                                                  \
                                 battleCtx->attacker,                                                                  \
                                 1))
