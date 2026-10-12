#pragma once

#include ".unsorted/803DEEA4.hpp"
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

// size: 0x18
struct BattlerDataSysTaskFuncs {
    /* 0x0 */ Unk8063D230Func setCommandSelection;
    /* 0x4 */ Unk8063D230Func showMoveSelectMenu;
    /* 0x8 */ Unk8063D230Func showTargetSelectMenu;
    /* 0xC */ Unk8063D230Func showBagMenu;
    /* 0x10 */ Unk8063D230Func showPartyMenu;
    /* 0x14 */ Unk8063D230Func showYesNoMenu;
};

// Only the fields used so far (pokeplatinum HealthBox).
// TODO Size unknown: BattlerData has room for 0x5C bytes.
struct HealthBox {
    /* 0x0 */ u8 state;
    /* 0x1 */ u8 unk1[0xB];
    /* 0xC */ BattleSystem *battleSys;
    /* 0x10 */ Unk8063D230 *task_10;
    /* 0x14 */ u8 unk14[0x4];
    /* 0x18 */ u8 battler;
    /* 0x19 */ u8 type;
    /* 0x1A */ u8 unk1A[0x2];
    /* 0x1C */ s32 curHP;
    /* 0x20 */ s32 maxHP;
    /* 0x24 */ s32 damage;
    /* 0x28 */ u8 unk28[0x14];
    /* 0x3C */ u8 level;
    /* 0x3D */ u8 unk3D[0x3];
    /* 0x40 */ u8 command;
    /* 0x41 */ u8 unk41[0x1B];
};

// Only the fields used so far (pokeplatinum BattlerData).
// size: 0x194
struct BattlerData {
    /* 0x0 */ BattlerDataSysTaskFuncs taskFuncs;
    /* 0x18 */ u8 unk18[0x8];
    // The DS sprite functions this is passed to are empty in this game.
    /* 0x20 */ u32 monSprite;
    /* 0x24 */ u8 unk24[0x4];
    /* 0x28 */ HealthBox healthbox;
    /* 0x84 */ u8 data[BATTLER_DATA_BUF_SIZE];
    /* 0x184 */ u8 battler;
    /* 0x185 */ u8 battlerType;
    /* 0x186 */ u8 bootState;
    /* 0x187 */ u8 unk187[0x9];
    /* 0x190 */ int isAlternateSprite;
};

// size: 0x2
struct BattlerInitData {
    /* 0x0 */ u8 battler;
    /* 0x1 */ u8 battlerType;
};

// Messages the battle controller writes into BattlerData::data (pokeplatinum message_defs.h).
// Only the fields read so far. Messages that are not read yet are only declared.

struct PartyGaugeData {
    /* 0x0 */ u8 command;
};

struct HealthBoxData {
    /* 0x0 */ u8 command;
};

struct MonEncounterMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u16 species;
    /* 0x4 */ u8 unk4[0x4];
    /* 0x8 */ int cryModulation;
};

struct MonShowMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u16 species;
};

struct MonReturnMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 yOffset;
};

struct OpenCaptureBallMessage {
    /* 0x0 */ u8 command;
};

struct TrainerEncounterMessage {
    /* 0x0 */ u8 command;
};

struct TrainerThrowBallMessage {
    /* 0x0 */ u8 command;
};

struct TrainerSlideInMessage {
    /* 0x0 */ u8 command;
};

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

struct MoveSelectMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u16 invalidMoves;
    /* 0x4 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0xC */ u8 ppCur[LEARNED_MOVES_MAX];
    /* 0x10 */ u8 ppMax[LEARNED_MOVES_MAX];
};

// pokeplatinum battle_subscreen.h
// size: 0x8
struct TargetMonData {
    /* 0x0 */ u8 partySlot;
    /* 0x1 */ u8 gender : 2;
    /* 0x1 */ u8 isPresent : 1;
    /* 0x1 */ u8 : 5;
    /* 0x2 */ u8 stockStatus;
    /* 0x3 */ u8 padding_03;
    /* 0x4 */ s16 curHP;
    /* 0x6 */ u16 maxHP;
};

struct TargetSelectMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 shouldHidePanel;
    /* 0x2 */ u16 range;
    /* 0x4 */ TargetMonData targetMon[MAX_BATTLERS];
};
struct BagMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 hasTwoOpponents;
    /* 0x2 */ u8 semiInvulnerable;
    /* 0x3 */ u8 substitute;
    /* 0x4 */ u8 partySlots[MAX_BATTLERS];
    /* 0x8 */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x20 */ u8 embargoTurns[MAX_BATTLERS];
};

struct PartyMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 battler;
    /* 0x2 */ u8 listMode;
    /* 0x3 */ u8 doublesSelection;
    /* 0x4 */ u8 selectedPartySlot[MAX_BATTLERS];
    /* 0x8 */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x20 */ int canSwitch;
    /* 0x24 */ u8 battlersSwitchingMask;
};

struct YesNoMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 yesNoType;
    /* 0x2 */ u16 promptMsg;
    /* 0x4 */ int move;
    /* 0x8 */ int nickname;
};

struct AttackMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u16 move;
};
struct HPGaugeUpdateMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 level;
    /* 0x2 */ s16 curHP;
    /* 0x4 */ u16 maxHP;
    /* 0x6 */ u8 padding_06;
    /* 0x7 */ u8 gender;
    /* 0x8 */ int hpCalcTemp;
};

struct ExpGaugeUpdateMessage {
    /* 0x0 */ u8 command;
};

struct FaintingSequenceMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u16 species;
};

struct PlaySoundMessage {
    /* 0x0 */ u8 command;
};

struct ToggleVanishMessage {
    /* 0x0 */ u8 command;
};

struct SetStatusIconMessage {
    /* 0x0 */ u8 command;
};

struct TrainerMsgMessage {
    /* 0x0 */ u8 command;
};

struct RecallMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u16 hpPercent;
};

struct SendOutMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    // Out of 1000.
    /* 0x2 */ u16 hpPercent;
};
struct LeadMonMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01[3];
    /* 0x4 */ u8 partySlot[MAX_BATTLERS];
};
struct AlertMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01[3];
    /* 0x4 */ BattleMessage msg;
};

struct RefreshHPGaugeMessage {
    /* 0x0 */ u8 command;
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

struct ForgetMoveMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 slot;
    /* 0x2 */ u16 move;
};

struct MosaicSetMessage {
    /* 0x0 */ u8 command;
};

struct EscapeMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 escaperBitmask;
};

struct MoveHitSoundMessage {
    /* 0x0 */ u8 command;
};

struct MusicPlayMessage {
    /* 0x0 */ u8 command;
};

struct ResultSubmitMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01;
    /* 0x2 */ u16 recordedInputCount;
    /* 0x4 */ u32 resultMask;
};

// pokeplatinum struct_defs/move_animation.h
// size: 0x58
struct MoveAnimation {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u16 move;
    /* 0x4 */ s32 damage;
    /* 0x8 */ u16 power;
    /* 0xA */ u16 effectChance;
    /* 0xC */ u16 friendship;
    /* 0xE */ u16 isSubstitute : 1;
    /* 0xE */ u16 isTransformed : 1;
    /* 0xE */ u16 : 14;
    /* 0x10 */ u32 fieldConditions;
    /* 0x14 */ u16 attacker;
    /* 0x16 */ u16 defender;
    /* 0x18 */ u16 species[MAX_BATTLERS];
    /* 0x20 */ u8 genders[MAX_BATTLERS];
    /* 0x24 */ u8 isShiny[MAX_BATTLERS];
    /* 0x28 */ u8 formNums[MAX_BATTLERS];
    /* 0x2C */ u32 personalities[MAX_BATTLERS];
    /* 0x3C */ u32 moveEffectMasks[MAX_BATTLERS];
    /* 0x4C */ int animMode;
    /* 0x50 */ int secondaryAnimID;
    /* 0x54 */ int terrain;
};

BattlerData *BattlerData_New(BattleSystem *battleSys, BattlerInitData *battlerInitData);
void BattleSystem_ExecuteBattlerCommand(BattleSystem *battleSys, BattlerData *battlerData);
void BattlerData_Delete(BattleSystem *battleSys, BattlerData *battlerData, int renderMode);
