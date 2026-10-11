#pragma once

#include "ds/battle/battle_constants.hpp"
#include "ds/battle/battle_mon.hpp"
#include "ds/move_table.hpp"

struct ItemData;

/*
 * Battle state of the server side, ported from the Gen 4 DS games. The layout
 * follows the Platinum one up to 0x3148; this game has one more move in the
 * move table (so everything after it is 0x10 further) and its own data after
 * linkBattleTimeout.
 */

#define MAX_LINK_BATTLERS 4
#define MAX_BATTLERS_PER_SIDE 2
#define NUM_BATTLE_SIDES 2
#define MAX_OPPONENTS 2
#define MAX_TRAINER_ITEMS 4
#define MAX_BATTLE_ACTIONS 4
#define MOVE_TABLE_SIZE 468

#define BATTLE_IO_QUEUE_SIZE 16
#define BATTLE_IO_BUFFER_SIZE 256
#define BATTLE_SCRIPT_SIZE_MAX 400
#define BATTLE_SCRIPT_STACK_MAX 4

// size: 0x24
struct BattleMessage {
    /* 0x0 */ u8 commandCode;
    /* 0x1 */ u8 tags;
    /* 0x2 */ u16 id;
    /* 0x4 */ s32 params[6];
    /* 0x1C */ s32 digits;
    /* 0x20 */ s32 battler;
};

// size: 0x38
struct FieldConditions {
    /* 0x0 */ u32 weatherTurns;
    /* 0x4 */ u8 futureSightTurns[MAX_BATTLERS];
    /* 0x8 */ u8 wishTurns[MAX_BATTLERS];
    /* 0xC */ u16 futureSightMove[MAX_BATTLERS];
    /* 0x14 */ s32 futureSightAttacker[MAX_BATTLERS];
    /* 0x24 */ s32 futureSightDamage[MAX_BATTLERS];
    /* 0x34 */ u8 wishTarget[MAX_BATTLERS];
};

// size: 0x8
struct SideConditions {
    /* 0x0 */ u32 reflectUser : 2;
    u32 reflectTurns : 3;
    u32 lightScreenUser : 2;
    u32 lightScreenTurns : 3;
    u32 mistUser : 2;
    u32 mistTurns : 3;
    u32 safeguardUser : 2;
    u32 safeguardTurns : 3;
    u32 followMe : 1;
    u32 followMeUser : 2;
    u32 knockedOffItemsMask : 6;
    u32 _0_29 : 3;

    /* 0x4 */ u32 spikesLayers : 2;
    u32 toxicSpikesLayers : 2;
    u32 _4_4 : 28;
};

// size: 0x40
struct TurnFlags {
    /* 0x0 */ u32 struggling : 1;
    u32 ppDecremented : 1;
    u32 protecting : 1;
    u32 helpingHand : 1;
    u32 magicCoat : 1;
    u32 snatching : 1;
    u32 roosting : 1;
    u32 fleeing : 2;
    u32 enduring : 1;
    u32 _0_10 : 22;

    /* 0x4 */ s32 physicalDamageTakenFrom[MAX_BATTLERS];
    /* 0x14 */ s32 physicalDamageLastAttacker;
    /* 0x18 */ s32 physicalDamageAttackerMask;
    /* 0x1C */ s32 specialDamageTakenFrom[MAX_BATTLERS];
    /* 0x2C */ s32 specialDamageLastAttacker;
    /* 0x30 */ s32 specialDamageAttackerMask;
    /* 0x34 */ s32 lastDamageTaken;
    /* 0x38 */ s32 lastAttacker;
    /* 0x3C */ s32 assuranceDamageMask;
};

// size: 0x1C
struct SelfTurnFlags {
    /* 0x0 */ u32 skipPressureCheck : 1;
    u32 lightningRodActivated : 1;
    u32 stormDrainActivated : 1;
    u32 moldBreakerActivated : 1;
    u32 trickRoomActivated : 1;
    u32 focusItemActivated : 1;
    u32 repeatedMoveCount : 3;
    u32 _0_9 : 23;

    /* 0x4 */ s32 physicalDamageTaken;
    /* 0x8 */ s32 physicalDamageLastAttacker;
    /* 0xC */ s32 specialDamageTaken;
    /* 0x10 */ s32 specialDamageLastAttacker;
    /* 0x14 */ s32 statusFlags;
    /* 0x18 */ s32 shellBellDamageDealt;
};

// size: 0x4
struct MoveFailFlags {
    /* 0x0 */ u32 paralyzed : 1;
    u32 noEffect : 1;
    u32 imprisoned : 1;
    u32 infatuated : 1;
    u32 disabled : 1;
    u32 taunted : 1;
    u32 flinched : 1;
    u32 confused : 1;
    u32 gravity : 1;
    u32 healBlocked : 1;
    u32 _0_10 : 22;
};

// size: 0x1DE0
struct AIContext {
    /* 0x0 */ u8 evalStep;
    /* 0x1 */ u8 moveSlot;
    /* 0x2 */ u16 move;
    /* 0x4 */ s8 moveScore[LEARNED_MOVES_MAX];
    /* 0x8 */ s32 calcTemp;
    /* 0xC */ u32 thinkingMask;
    /* 0x10 */ u8 stateFlags;
    /* 0x11 */ u8 thinkingBitShift;
    /* 0x12 */ u8 _12[0x6];
    /* 0x18 */ u8 moveDamageRolls[LEARNED_MOVES_MAX];
    /* 0x1C */ u16 battlerMoves[MAX_BATTLERS][LEARNED_MOVES_MAX];
    /* 0x3C */ u8 battlerAbilities[MAX_BATTLERS];
    /* 0x40 */ u16 battlerHeldItems[MAX_BATTLERS];
    /* 0x48 */ u16 trainerItems[MAX_OPPONENTS][MAX_TRAINER_ITEMS];
    /* 0x58 */ u32 scriptStackPointer[8];
    /* 0x78 */ u8 scriptStackSize;
    /* 0x79 */ u8 trainerItemCounts[MAX_BATTLERS_PER_SIDE];
    /* 0x7B */ u8 attacker;
    /* 0x7C */ u8 defender;
    /* 0x7D */ u8 usedItemType[MAX_BATTLERS_PER_SIDE];
    /* 0x7F */ u8 usedItemCondition[MAX_BATTLERS_PER_SIDE];
    /* 0x82 */ u16 usedItem[MAX_BATTLERS_PER_SIDE];
    /* 0x86 */ u8 selectedTarget[MAX_BATTLERS];
    /* 0x8A */ MoveTable moveTable[MOVE_TABLE_SIZE];
    /* 0x1DCC */ ItemData *itemTable;
    /* 0x1DD0 */ u8 _1DD0[0x10];
};

// Per party member data added by this game, read by the game code
// size: 0x48
struct Unk803C940C {
    /* 0x0 */ u8 unk0[0x48];
};

// size: 0x4C5C
struct BattleContext {
    /* 0x0 */ u8 curCommandState[MAX_BATTLERS];
    /* 0x4 */ u8 nextCommandState[MAX_BATTLERS];
    /* 0x8 */ s32 command;
    /* 0xC */ s32 commandNext;

    /* 0x10 */ s32 fieldConditionCheckState;
    /* 0x14 */ s32 fieldConditionCheckTemp;
    /* 0x18 */ s32 monConditionCheckState;
    /* 0x1C */ s32 monConditionCheckTemp;
    /* 0x20 */ s32 sideConditionCheckState;
    /* 0x24 */ s32 sideConditionCheckTemp;
    /* 0x28 */ s32 turnStartCheckState;
    /* 0x2C */ s32 turnStartCheckTemp;
    /* 0x30 */ s32 afterMoveHitCheckState;
    /* 0x34 */ s32 afterMoveHitCheckTemp;
    /* 0x38 */ s32 afterMoveMessageType;
    /* 0x3C */ s32 afterMoveMessageState;
    /* 0x40 */ s32 afterMoveEffectState;
    /* 0x44 */ s32 afterMoveEffectTemp;
    /* 0x48 */ s32 beforeMoveCheckState;
    /* 0x4C */ s32 tryMoveCheckState;
    /* 0x50 */ s32 statusCheckState;
    /* 0x54 */ s32 abilityCheckState;
    /* 0x58 */ s32 switchInCheckState;
    /* 0x5C */ s32 vanishedCheckTemp;
    /* 0x60 */ u8 _60[0x4];

    /* 0x64 */ s32 attacker;
    /* 0x68 */ s32 attackerTemp;
    /* 0x6C */ s32 defender;
    /* 0x70 */ s32 defenderTemp;
    /* 0x74 */ s32 faintedMon;
    /* 0x78 */ s32 switchedMon;
    /* 0x7C */ s32 switchedMonTemp;
    /* 0x80 */ s32 abilityMon;
    /* 0x84 */ s32 magicCoatMon;
    /* 0x88 */ s32 sideEffectType;
    /* 0x8C */ s32 sideEffectParam;
    /* 0x90 */ s32 sideEffectFlags;
    /* 0x94 */ s32 sideEffectMon;
    /* 0x98 */ s32 lastBattlerId;
    /* 0x9C */ s32 gainedExp;
    /* 0xA0 */ s32 sharedExp;
    /* 0xA4 */ u32 sideGetExpMask[NUM_BATTLE_SIDES];

    /* 0xAC */ u32 scriptNarc;
    /* 0xB0 */ u32 scriptFile;
    /* 0xB4 */ u32 scriptCursor;
    /* 0xB8 */ u32 scriptStackPointer;
    /* 0xBC */ u32 scriptStackNarc[BATTLE_SCRIPT_STACK_MAX];
    /* 0xCC */ u32 scriptStackFile[BATTLE_SCRIPT_STACK_MAX];
    /* 0xDC */ u32 scriptStackCursor[BATTLE_SCRIPT_STACK_MAX];

    /* 0xEC */ s32 turnOrderCounter;
    /* 0xF0 */ s32 waitCounter;
    /* 0xF4 */ BattleMessage msgBuffer;
    /* 0x118 */ s32 msgBattlerTemp;
    /* 0x11C */ s32 msgAttacker;
    /* 0x120 */ s32 msgDefender;
    /* 0x124 */ s32 msgMoveTemp;
    /* 0x128 */ s32 msgItemTemp;
    /* 0x12C */ s32 msgAbilityTemp;
    /* 0x130 */ s32 msgTemp;
    /* 0x134 */ s32 calcTemp;
    /* 0x138 */ s32 scriptTemp;

    /* 0x13C */ u32 battlerStatusFlags[MAX_BATTLERS];
    /* 0x14C */ u32 payDayCount;
    /* 0x150 */ s32 totalTurns;
    /* 0x154 */ s32 totalFainted[MAX_BATTLERS];
    /* 0x164 */ s32 totalDamage[MAX_BATTLERS];
    /* 0x174 */ s32 meFirstTurnOrder;
    /* 0x178 */ void *taskData;
    /* 0x17C */ void *tmpData;

    /* 0x180 */ u32 fieldConditionsMask;
    /* 0x184 */ FieldConditions fieldConditions;
    /* 0x1BC */ u32 sideConditionsMask[NUM_BATTLE_SIDES];
    /* 0x1C4 */ SideConditions sideConditions[NUM_BATTLE_SIDES];
    /* 0x1D4 */ TurnFlags turnFlags[MAX_BATTLERS];
    /* 0x2D4 */ SelfTurnFlags selfTurnFlags[MAX_BATTLERS];
    /* 0x344 */ MoveFailFlags moveFailFlags[MAX_BATTLERS];
    /* 0x354 */ AIContext aiContext;
    /* 0x2134 */ u32 *aiScriptTemp;
    /* 0x2138 */ u32 aiScriptCursor;

    /* 0x213C */ u32 battleStatusMask;
    /* 0x2140 */ u32 battleStatusMask2;
    /* 0x2144 */ s32 damage;
    /* 0x2148 */ s32 hitDamage;
    /* 0x214C */ s32 criticalBoosts;
    /* 0x2150 */ s32 criticalMul;
    /* 0x2154 */ s32 movePower;
    /* 0x2158 */ s32 powerMul;
    /* 0x215C */ s32 hpCalcTemp;
    /* 0x2160 */ s32 moveType;
    /* 0x2164 */ s32 moveEffectChance;
    /* 0x2168 */ s32 prizeMoneyMul;
    /* 0x216C */ u32 moveStatusFlags;
    /* 0x2170 */ u32 sideEffectDirectFlags;
    /* 0x2174 */ u32 sideEffectIndirectFlags;
    /* 0x2178 */ u32 sideEffectAbilityFlags;
    /* 0x217C */ u8 multiHitCounter;
    /* 0x217D */ u8 multiHitNumHits;
    /* 0x217E */ u8 battlerCounter;
    /* 0x217F */ u8 beatUpCounter;
    /* 0x2180 */ BOOL multiHitLoop;
    /* 0x2184 */ u32 multiHitCheckFlags;
    /* 0x2188 */ u32 multiHitAccuracyCheck;
    /* 0x218C */ u32 clearVolatileStatus[MAX_BATTLERS];

    /* 0x219C */ u8 selectedPartySlot[MAX_BATTLERS];
    /* 0x21A0 */ u8 switchedPartySlot[MAX_BATTLERS];
    /* 0x21A4 */ u8 aiSwitchedPartySlot[MAX_BATTLERS];
    /* 0x21A8 */ u32 battlerActions[MAX_BATTLERS][MAX_BATTLE_ACTIONS];
    /* 0x21E8 */ u8 battlerActionOrder[MAX_BATTLERS];
    /* 0x21EC */ u8 monSpeedOrder[MAX_BATTLERS];
    /* 0x21F0 */ u32 monSpeedValues[MAX_BATTLERS];

    /* 0x2200 */ u8 ioQueue[MAX_LINK_BATTLERS][MAX_BATTLERS][BATTLE_IO_QUEUE_SIZE];
    /* 0x2300 */ u8 ioBuffer[MAX_BATTLERS][BATTLE_IO_BUFFER_SIZE];
    /* 0x2700 */ s32 battleScript[BATTLE_SCRIPT_SIZE_MAX];
    /* 0x2D40 */ BattleMon battleMons[MAX_BATTLERS];

    /* 0x3040 */ u32 moveTemp;
    /* 0x3044 */ u32 moveCur;
    /* 0x3048 */ u32 movePrev;
    /* 0x304C */ u32 moveLockedInto[MAX_BATTLERS];
    /* 0x305C */ u16 moveProtect[MAX_BATTLERS];
    /* 0x3064 */ u16 moveHit[MAX_BATTLERS];
    /* 0x306C */ u16 moveHitBattler[MAX_BATTLERS];
    /* 0x3074 */ u16 moveHitType[MAX_BATTLERS];
    /* 0x307C */ u16 movePrevByBattler[MAX_BATTLERS];
    /* 0x3084 */ u16 moveCopied[MAX_BATTLERS];
    /* 0x308C */ u16 moveCopiedHit[MAX_BATTLERS][MAX_BATTLERS];
    /* 0x30AC */ u16 moveSketched[MAX_BATTLERS];
    /* 0x30B4 */ u16 moveSelected[MAX_BATTLERS];
    /* 0x30BC */ u16 moveSlot[MAX_BATTLERS];
    /* 0x30C4 */ u16 conversion2Move[MAX_BATTLERS];
    /* 0x30CC */ u16 conversion2Battler[MAX_BATTLERS];
    /* 0x30D4 */ u16 conversion2Type[MAX_BATTLERS];
    /* 0x30DC */ u16 metronomeMove[MAX_BATTLERS];
    /* 0x30E4 */ s32 storedDamage[MAX_BATTLERS];
    /* 0x30F4 */ s32 lastHitByBattler[MAX_BATTLERS];
    /* 0x3104 */ s32 battlerSpeedTemp;
    /* 0x3108 */ u8 battlersSwitchingMask;
    /* 0x3109 */ u8 levelUpMons;
    /* 0x310A */ u8 _310A[0x2];
    /* 0x310C */ u16 speedRand[MAX_BATTLERS];
    /* 0x3114 */ s32 flingTemp;
    /* 0x3118 */ s32 flingScript;
    /* 0x311C */ u8 safariCatchStage;
    /* 0x311D */ u8 safariEscapeCount;
    /* 0x311E */ u8 runAttempts;
    /* 0x311F */ u8 battleEndFlag;
    /* 0x3120 */ u8 magnitude;
    /* 0x3121 */ u8 fieldWeatherChecked;
    /* 0x3122 */ s16 hpTemp;
    /* 0x3124 */ u16 recycleItem[MAX_BATTLERS];
    /* 0x312C */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x3144 */ BOOL expJinglePlayed;
    /* 0x3148 */ s32 linkBattleTimeout;
    /* 0x314C */ u8 unk314C[MAX_BATTLERS][4];
    /* 0x315C */ Unk803C940C unk315C[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x381C */ u8 _381C[0x1440];
};
