#pragma once

#include "ds/battle/battle_system.hpp"

#define BATTLER_DATA_BUF_SIZE 256

enum BattleCommand {
    BATTLE_COMMAND_NONE,
    BATTLE_COMMAND_SETUP_UI,
    BATTLE_COMMAND_SET_ENCOUNTER,
    BATTLE_COMMAND_SHOW_ENCOUNTER,
    BATTLE_COMMAND_SHOW_POKEMON,
    BATTLE_COMMAND_RETURN_POKEMON,
    BATTLE_COMMAND_OPEN_CAPTURE_BALL,
    BATTLE_COMMAND_DELETE_POKEMON,
    BATTLE_COMMAND_SET_TRAINER_ENCOUNTER,
    BATTLE_COMMAND_THROW_TRAINER_BALL,
    BATTLE_COMMAND_SLIDE_TRAINER_OUT,
    BATTLE_COMMAND_SLIDE_TRAINER_IN,
    BATTLE_COMMAND_SLIDE_HEALTHBOX_IN,
    BATTLE_COMMAND_SLIDE_HEALTHBOX_OUT,
    BATTLE_COMMAND_SET_COMMAND_SELECTION,
    BATTLE_COMMAND_SHOW_MOVE_SELECT_MENU,
    BATTLE_COMMAND_SHOW_TARGET_SELECT_MENU,
    BATTLE_COMMAND_SHOW_BAG_MENU,
    BATTLE_COMMAND_SHOW_PARTY_MENU,
    BATTLE_COMMAND_SHOW_YES_NO_MENU,
    BATTLE_COMMAND_PRINT_ATTACK_MESSAGE,
    BATTLE_COMMAND_PRINT_MESSAGE,
    BATTLE_COMMAND_SET_MOVE_ANIMATION,
    BATTLE_COMMAND_FLICKER_BATTLER,
    BATTLE_COMMAND_UPDATE_HP_GAUGE,
    BATTLE_COMMAND_UPDATE_EXP_GAUGE,
    BATTLE_COMMAND_PLAY_FAINTING_SEQUENCE,
    BATTLE_COMMAND_PLAY_SOUND,
    BATTLE_COMMAND_FADE_OUT,
    BATTLE_COMMAND_TOGGLE_VANISH,
    BATTLE_COMMAND_SET_STATUS_ICON,
    BATTLE_COMMAND_PRINT_TRAINER_MESSAGE,
    BATTLE_COMMAND_PRINT_RECALL_MESSAGE,
    BATTLE_COMMAND_PRINT_SEND_OUT_MESSAGE,
    BATTLE_COMMAND_PRINT_BATTLE_START_MESSAGE,
    BATTLE_COMMAND_PRINT_LEAD_MON_MESSAGE,
    BATTLE_COMMAND_PLAY_LEVEL_UP_ANIMATION,
    BATTLE_COMMAND_SET_ALERT_MESSAGE,
    BATTLE_COMMAND_REFRESH_HP_GAUGE,
    BATTLE_COMMAND_UPDATE_PARTY_MON,
    BATTLE_COMMAND_SLIDE_IN_PANEL,
    BATTLE_COMMAND_STOP_GAUGE_ANIMATION,
    BATTLE_COMMAND_REFRESH_PARTY_STATUS,
    BATTLE_COMMAND_FORGET_MOVE,
    BATTLE_COMMAND_SET_MOSAIC,
    BATTLE_COMMAND_CHANGE_WEATHER_FORM,
    BATTLE_COMMAND_UPDATE_BG,
    BATTLE_COMMAND_CLEAR_TOUCH_SCREEN,
    BATTLE_COMMAND_SHOW_BATTLE_START_PARTY_GAUGE,
    BATTLE_COMMAND_HIDE_BATTLE_START_PARTY_GAUGE,
    BATTLE_COMMAND_SHOW_PARTY_GAUGE,
    BATTLE_COMMAND_HIDE_PARTY_GAUGE,
    BATTLE_COMMAND_LOAD_PARTY_GAUGE_GRAPHICS,
    BATTLE_COMMAND_FREE_PARTY_GAUGE_GRAPHICS,
    BATTLE_COMMAND_INCREMENT_RECORD,
    BATTLE_COMMAND_PRINT_LINK_WAIT_MESSAGE,
    BATTLE_COMMAND_RESTORE_SPRITE,
    BATTLE_COMMAND_SPRITE_TO_OAM,
    BATTLE_COMMAND_OAM_TO_SPRITE,
    BATTLE_COMMAND_PRINT_RESULT_MESSAGE,
    BATTLE_COMMAND_PRINT_ESCAPE_MESSAGE,
    BATTLE_COMMAND_PRINT_FORFEIT_MESSAGE,
    BATTLE_COMMAND_REFRESH_SPRITE,
    BATTLE_COMMAND_FLY_MOVE_HIT_SOUND_EFFECT,
    BATTLE_COMMAND_PLAY_MUSIC,
    BATTLE_COMMAND_SUBMIT_RESULT,
    BATTLE_COMMAND_CLEAR_MESSAGE_BOX,
};

// Only the fields used so far (pokeplatinum BattlerData).
// size: 0x194
struct BattlerData {
    /* 0x0 */ u8 unk0[0x20];
    // The DS sprite functions this is passed to are empty in this game.
    /* 0x20 */ u32 monSprite;
    /* 0x24 */ u8 unk24[0x4];
    // TODO Size unknown: the next known field is at 0x84.
    /* 0x28 */ u8 healthbox[0x5C];
    /* 0x84 */ u8 data[BATTLER_DATA_BUF_SIZE];
    /* 0x184 */ u8 battler;
    /* 0x185 */ u8 battlerType;
    /* 0x186 */ u8 bootState;
    /* 0x187 */ u8 unk187[0xD];
};

// size: 0x2
struct BattlerInitData {
    /* 0x0 */ u8 battler;
    /* 0x1 */ u8 battlerType;
};

// Messages the battle controller writes into BattlerData::data (pokeplatinum message_defs.h).
// Only the fields read so far.

struct CommandSetMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u8 expPercents[MAX_PARTY_SIZE];
    /* 0x8 */ u8 ballStatus[2][MAX_PARTY_SIZE];
    /* 0x14 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x1C */ u8 curPP[LEARNED_MOVES_MAX];
    /* 0x20 */ u8 maxPP[LEARNED_MOVES_MAX];
    /* 0x24 */ s16 curHP;
    /* 0x26 */ u16 maxHP;
    /* 0x28 */ u8 ballStatusBattler;
    /* 0x29 */ u8 switchingOrCanPickCommandMask;
};

struct UpdatePartyMonMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot : 4;
    /* 0x1 */ u8 mimickedMoveSlot : 4;
    /* 0x2 */ s16 curHP;
    /* 0x4 */ u32 status;
    /* 0x8 */ u32 knockedOffItemsMask;
    /* 0xC */ u16 heldItem;
    /* 0xE */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x16 */ u8 ppCur[LEARNED_MOVES_MAX];
    /* 0x1A */ u8 padding_1A[2];
    /* 0x1C */ u32 statusVolatile;
};

// size: 0x4
struct RefreshPartyStatusMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 ability;
    /* 0x2 */ u16 move;
};

// Contents not read here.
struct PartyGaugeData;

struct ResultSubmitMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01;
    /* 0x2 */ u16 recordedInputCount;
    /* 0x4 */ u32 resultMask;
};

BattlerData *BattlerData_New(BattleSystem *battleSys, BattlerInitData *battlerInitData);
void BattleSystem_ExecuteBattlerCommand(BattleSystem *battleSys, BattlerData *battlerData);
void BattlerData_Delete(BattleSystem *battleSys, BattlerData *battlerData, int renderMode);
