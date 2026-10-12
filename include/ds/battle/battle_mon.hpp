#pragma once

#include <revolution/types.h>
#include "ds/pokemon.hpp"

#define NUM_BOOSTABLE_STATS 8

// Parameters of BattleMon_Get, BattleMon_Set and BattleMon_AddVal
enum BattleMonParam {
    BATTLEMON_SPECIES = 0,
    BATTLEMON_ATTACK,
    BATTLEMON_DEFENSE,
    BATTLEMON_SPEED,
    BATTLEMON_SP_ATTACK,
    BATTLEMON_SP_DEFENSE,
    BATTLEMON_MOVE_1,
    BATTLEMON_MOVE_2,
    BATTLEMON_MOVE_3,
    BATTLEMON_MOVE_4,
    BATTLEMON_HP_IV,
    BATTLEMON_ATTACK_IV,
    BATTLEMON_DEFENSE_IV,
    BATTLEMON_SPEED_IV,
    BATTLEMON_SP_ATTACK_IV,
    BATTLEMON_SP_DEFENSE_IV,
    BATTLEMON_IS_EGG,
    BATTLEMON_HAS_NICKNAME,
    BATTLEMON_HP_STAGE,
    BATTLEMON_ATTACK_STAGE,
    BATTLEMON_DEFENSE_STAGE,
    BATTLEMON_SPEED_STAGE,
    BATTLEMON_SP_ATTACK_STAGE,
    BATTLEMON_SP_DEFENSE_STAGE,
    BATTLEMON_ACCURACY_STAGE,
    BATTLEMON_EVASION_STAGE,
    BATTLEMON_ABILITY,
    BATTLEMON_TYPE_1,
    BATTLEMON_TYPE_2,
    BATTLEMON_GENDER,
    BATTLEMON_IS_SHINY,
    BATTLEMON_CUR_PP_1,
    BATTLEMON_CUR_PP_2,
    BATTLEMON_CUR_PP_3,
    BATTLEMON_CUR_PP_4,
    BATTLEMON_PP_UPS_1,
    BATTLEMON_PP_UPS_2,
    BATTLEMON_PP_UPS_3,
    BATTLEMON_PP_UPS_4,
    BATTLEMON_MAX_PP_1,
    BATTLEMON_MAX_PP_2,
    BATTLEMON_MAX_PP_3,
    BATTLEMON_MAX_PP_4,
    BATTLEMON_LEVEL,
    BATTLEMON_FRIENDSHIP,
    BATTLEMON_NICKNAME,
    BATTLEMON_NICKNAME_STRING,
    BATTLEMON_CUR_HP,
    BATTLEMON_MAX_HP,
    BATTLEMON_OT_NAME,
    BATTLEMON_EXP,
    BATTLEMON_PERSONALITY,
    BATTLEMON_STATUS,
    BATTLEMON_VOLATILE_STATUS,
    BATTLEMON_OT_ID,
    BATTLEMON_HELD_ITEM,
    BATTLEMON_TIMES_DAMAGED,
    BATTLEMON_TRAINER_MESSAGE_FLAGS,
    BATTLEMON_OT_GENDER,
    BATTLEMON_MOVE_EFFECTS_MASK,
    BATTLEMON_MOVE_EFFECTS_TEMP,
    BATTLEMON_DISABLED_TURNS,
    BATTLEMON_ENCORED_TURNS,
    BATTLEMON_CHARGED_TURNS,
    BATTLEMON_TAUNTED_TURNS,
    BATTLEMON_SUCCESSFUL_PROTECT_TURNS,
    BATTLEMON_PERISH_SONG_TURNS,
    BATTLEMON_ROLLOUT_COUNT,
    BATTLEMON_FURY_CUTTER_COUNT,
    BATTLEMON_STOCKPILE_COUNT,
    BATTLEMON_STOCKPILE_DEF_BOOSTS,
    BATTLEMON_STOCKPILE_SPDEF_BOOSTS,
    BATTLEMON_TRUANT,
    BATTLEMON_FLASH_FIRE,
    BATTLEMON_LOCK_ON_TARGET,
    BATTLEMON_MIMICKED_MOVE_SLOT,
    BATTLEMON_BIND_TARGET,
    BATTLEMON_MEAN_LOOK_TARGET,
    BATTLEMON_LAST_RESORT_COUNT,
    BATTLEMON_MAGNET_RISE_TURNS,
    BATTLEMON_HEAL_BLOCK_TURNS,
    BATTLEMON_EMBARGO_TURNS,
    BATTLEMON_CAN_UNBURDEN,
    BATTLEMON_METRONOME_TURNS,
    BATTLEMON_MICLE_BERRY,
    BATTLEMON_CUSTAP_BERRY,
    BATTLEMON_QUICK_CLAW,
    BATTLEMON_RECHARGE_TURN_NUMBER,
    BATTLEMON_FAKE_OUT_TURN_NUMBER,
    BATTLEMON_SLOW_START_TURN_NUMBER,
    BATTLEMON_SUBSTITUTE_HP,
    BATTLEMON_TRANSFORMED_PERSONALITY,
    BATTLEMON_DISABLED_MOVE,
    BATTLEMON_ENCORED_MOVE,
    BATTLEMON_BINDING_MOVE,
    BATTLEMON_ITEM_HP_RECOVERY,
    BATTLEMON_SLOW_START_ANNOUNCED,
    BATTLEMON_SLOW_START_FINISHED,
    BATTLEMON_FORM_NUM,
    BATTLEMON_UNUSED_99,
    BATTLEMON_TEMP,
};

// size: 0x38
struct MoveEffectsData {
    /* 0x0 */ u32 disabledTurns : 3;
    u32 encoredTurns : 3;
    u32 chargedTurns : 2;
    u32 tauntedTurns : 3;
    u32 protectSuccessTurns : 2;
    u32 perishSongTurns : 2;
    u32 rolloutCount : 3;
    u32 furyCutterCount : 3;
    u32 stockpileCount : 3;
    u32 stockpileDefBoosts : 3;
    u32 stockpileSpDefBoosts : 3;
    u32 truant : 1;
    u32 flashFire : 1;

    /* 0x4 */ u32 lockOnTarget : 2;
    u32 mimickedMoveSlot : 4;
    u32 bindTarget : 2;
    u32 meanLookTarget : 2;
    u32 lastResortCount : 3;
    u32 magnetRiseTurns : 3;
    u32 healBlockTurns : 3;
    u32 embargoTurns : 3;
    u32 canUnburden : 1;
    u32 metronomeTurns : 4;
    u32 micleBerry : 1;
    u32 custapBerry : 1;
    u32 quickClaw : 1;
    u32 meFirst : 1;
    u32 _4_31 : 1;

    /* 0x8 */ s32 rechargeTurnNumber;
    /* 0xC */ s32 fakeOutTurnNumber;
    /* 0x10 */ s32 slowStartTurnNumber;
    /* 0x14 */ s32 meFirstTurnNumber;
    /* 0x18 */ s32 substituteHP;
    /* 0x1C */ u32 transformedPID;
    /* 0x20 */ u16 disabledMove;
    /* 0x22 */ u16 bindingMove;
    /* 0x24 */ u16 encoredMove;
    /* 0x26 */ u16 encoredMoveSlot;
    /* 0x28 */ u16 lastResortMoves[4];
    /* 0x30 */ u16 choiceLockedMove;
    /* 0x32 */ u16 transformedGender;
    /* 0x34 */ s32 itemHPRecovery;
};

// size: 0xC0
struct BattleMon {
    /* 0x0 */ u16 species;
    /* 0x2 */ u16 attack;
    /* 0x4 */ u16 defense;
    /* 0x6 */ u16 speed;
    /* 0x8 */ u16 spAttack;
    /* 0xA */ u16 spDefense;
    /* 0xC */ u16 moves[LEARNED_MOVES_MAX];

    /* 0x14 */ u32 hpIV : 5;
    u32 attackIV : 5;
    u32 defenseIV : 5;
    u32 speedIV : 5;
    u32 spAttackIV : 5;
    u32 spDefenseIV : 5;
    u32 isEgg : 1;
    u32 hasNickname : 1;

    /* 0x18 */ s8 statBoosts[NUM_BOOSTABLE_STATS];
    /* 0x20 */ s32 weight;
    /* 0x24 */ u8 type1;
    /* 0x25 */ u8 type2;
    /* 0x26 */ u8 formNum : 5;
    u8 isShiny : 1;
    u8 _26_6 : 2;
    /* 0x27 */ u8 ability;

    /* 0x28 */ u32 weatherAbilityAnnounced : 1;
    u32 intimidateAnnounced : 1;
    u32 traceAnnounced : 1;
    u32 downloadAnnounced : 1;
    u32 anticipationAnnounced : 1;
    u32 forewarnAnnounced : 1;
    u32 slowStartAnnounced : 1;
    u32 slowStartFinished : 1;
    u32 friskAnnounced : 1;
    u32 moldBreakerAnnounced : 1;
    u32 pressureAnnounced : 1;
    u32 _28_11 : 21;

    /* 0x2C */ u8 ppCur[LEARNED_MOVES_MAX];
    /* 0x30 */ u8 ppUps[LEARNED_MOVES_MAX];
    /* 0x34 */ u8 level;
    /* 0x35 */ u8 friendship;
    /* 0x36 */ u16 nickname[MON_NAME_LEN + 1];
    /* 0x4C */ int curHP;
    /* 0x50 */ u32 maxHP;
    /* 0x54 */ u16 OTName[TRAINER_NAME_LEN + 1];
    /* 0x64 */ u32 exp;
    /* 0x68 */ u32 personality;
    /* 0x6C */ u32 status;
    /* 0x70 */ u32 statusVolatile;
    /* 0x74 */ u32 OTId;
    /* 0x78 */ u16 heldItem;
    /* 0x7A */ u8 _7A[0x2];
    /* 0x7C */ u8 timesDamaged;
    /* 0x7D */ u8 trainerMessageFlags;
    /* 0x7E */ u8 gender : 4;
    u8 OTGender : 4;
    /* 0x7F */ u8 capturedBall;
    /* 0x80 */ u32 moveEffectsMask;
    /* 0x84 */ u32 moveEffectsTemp;
    /* 0x88 */ MoveEffectsData moveEffectsData;
};
