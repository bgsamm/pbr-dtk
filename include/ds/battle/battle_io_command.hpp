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

// Messages between the battle controller and the battlers (pokeplatinum message_defs.h).

// size: 0x4
struct BattleItemUse {
    /* 0x0 */ u16 item;
    /* 0x2 */ u8 category;
    /* 0x3 */ u8 target;
};

// size: 0x8
struct PartyGaugeData {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01;
    /* 0x2 */ u8 status[MAX_PARTY_SIZE];
};

// size: 0x18
struct HealthBoxData {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 level;
    /* 0x2 */ s16 curHP;
    /* 0x4 */ u16 maxHP;
    /* 0x6 */ u8 selectedPartySlot;
    /* 0x7 */ u8 status : 5;
    /* 0x7 */ u8 gender : 2;
    /* 0x7 */ u8 speciesCaught : 1;
    /* 0x8 */ u32 expFromLastLevel;
    /* 0xC */ u32 expToNextLevel;
    /* 0x10 */ int numSafariBalls;
    /* 0x14 */ u8 delay;
};

// size: 0x4
struct BattleMessageInfo {
    /* 0x0 */ u8 recipient;
    /* 0x1 */ u8 battler;
    /* 0x2 */ u16 size;
};

// size: 0x3C
struct MonEncounterMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 gender : 2;
    /* 0x1 */ u8 isShiny : 1;
    /* 0x1 */ u8 formNum : 5;
    /* 0x2 */ u16 species;
    /* 0x4 */ u32 personality;
    /* 0x8 */ int cryModulation;
    /* 0xC */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x14 */ u16 curPP[LEARNED_MOVES_MAX];
    /* 0x1C */ u16 maxPP[LEARNED_MOVES_MAX];
    /* 0x24 */ u16 nickname[MON_NAME_LEN + 1];
    /* 0x3A */ u8 padding_3A[2];
};

// size: 0x74
struct MonShowMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 gender : 2;
    /* 0x1 */ u8 isShiny : 1;
    /* 0x1 */ u8 formNum : 5;
    /* 0x2 */ u16 species;
    /* 0x4 */ u32 personality;
    /* 0x8 */ int cryModulation;
    /* 0xC */ int selectedPartySlot;
    /* 0x10 */ int capturedBall;
    /* 0x14 */ int isQuickSendOut;
    /* 0x18 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x20 */ u16 curPP[LEARNED_MOVES_MAX];
    /* 0x28 */ u16 maxPP[LEARNED_MOVES_MAX];
    /* 0x30 */ u16 nickname[MON_NAME_LEN + 1];
    /* 0x46 */ u8 padding_46[2];
    /* 0x48 */ int partnerPartySlot;
    /* 0x4C */ int isSubstitute;
    /* 0x50 */ u16 battleMonSpecies[MAX_BATTLERS];
    /* 0x58 */ u8 battleMonGenders[MAX_BATTLERS];
    /* 0x5C */ u8 battleMonIsShiny[MAX_BATTLERS];
    /* 0x60 */ u8 battleMonFormNums[MAX_BATTLERS];
    /* 0x64 */ u32 battleMonPersonalities[MAX_BATTLERS];
};

// size: 0x2C
struct MonReturnMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 yOffset;
    /* 0x2 */ u16 capturedBall;
    /* 0x4 */ int isSubstitute;
    /* 0x8 */ u16 battleMonSpecies[MAX_BATTLERS];
    /* 0x10 */ u8 battleMonGenders[MAX_BATTLERS];
    /* 0x14 */ u8 battleMonIsShiny[MAX_BATTLERS];
    /* 0x18 */ u8 battleMonFormNums[MAX_BATTLERS];
    /* 0x1C */ u32 battleMonPersonalities[MAX_BATTLERS];
};

// size: 0x4
struct OpenCaptureBallMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 yOffset;
    /* 0x2 */ u16 ball;
};

// size: 0x4
struct TrainerEncounterMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unread;
    /* 0x2 */ u16 trainerType;
};

// size: 0x4
struct TrainerThrowBallMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 ballTypeIn;
    /* 0x2 */ u16 selectedPartySlot;
};

// size: 0x8
struct TrainerSlideInMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unread;
    /* 0x2 */ u16 trainerType;
    /* 0x4 */ int posIn;
};

// size: 0x2C
struct CommandSetMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u8 expPercents[MAX_PARTY_SIZE];
    /* 0x8 */ u8 ballStatus[PARTY_GAUGE_COUNT][MAX_PARTY_SIZE];
    /* 0x14 */ u16 moves[LEARNED_MOVES_MAX];
    /* 0x1C */ u8 curPP[LEARNED_MOVES_MAX];
    /* 0x20 */ u8 maxPP[LEARNED_MOVES_MAX];
    /* 0x24 */ s16 curHP;
    /* 0x26 */ u16 maxHP;
    /* 0x28 */ u8 ballStatusBattler;
    /* 0x29 */ u8 switchingOrCanPickCommandMask;
    /* 0x2A */ u16 padding_2A;
};

// size: 0x14
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

// size: 0x24
struct TargetSelectMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 shouldHidePanel;
    /* 0x2 */ u16 range;
    /* 0x4 */ TargetMonData targetMon[MAX_BATTLERS];
};

// size: 0x24
struct BagMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 hasTwoOpponents;
    /* 0x2 */ u8 semiInvulnerable;
    /* 0x3 */ u8 substitute;
    /* 0x4 */ u8 partySlots[MAX_BATTLERS];
    /* 0x8 */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x20 */ u8 embargoTurns[MAX_BATTLERS];
};

// size: 0x28
struct PartyMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 battler;
    /* 0x2 */ u8 listMode;
    /* 0x3 */ u8 doublesSelection;
    /* 0x4 */ u8 selectedPartySlot[MAX_BATTLERS];
    /* 0x8 */ u8 partyOrder[MAX_BATTLERS][MAX_PARTY_SIZE];
    /* 0x20 */ int canSwitch;
    /* 0x24 */ u8 battlersSwitchingMask;
    /* 0x25 */ u8 padding_25[3];
};

// size: 0xC
struct YesNoMenuMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 yesNoType;
    /* 0x2 */ u16 promptMsg;
    /* 0x4 */ int move;
    /* 0x8 */ int nickname;
};

// size: 0x4
struct AttackMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u16 move;
};

// size: 0x14
struct HPGaugeUpdateMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 level;
    /* 0x2 */ s16 curHP;
    /* 0x4 */ u16 maxHP;
    /* 0x6 */ u8 padding_06;
    /* 0x7 */ u8 gender;
    /* 0x8 */ int hpCalcTemp;
    /* 0xC */ u32 exp;
    /* 0x10 */ u32 expToNextLevel;
};

// size: 0x10
struct ExpGaugeUpdateMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01[3];
    /* 0x4 */ u32 curExp;
    /* 0x8 */ u32 gainedExp;
    /* 0xC */ u32 expToNextLevel;
};

// size: 0x30
struct FaintingSequenceMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 gender;
    /* 0x2 */ u16 species;
    /* 0x4 */ u32 personality;
    /* 0x8 */ u8 form;
    /* 0x9 */ u8 isSubstitute;
    /* 0xA */ u8 isTransformed;
    /* 0xB */ u8 unk_0B;
    /* 0xC */ u16 monSpecies[MAX_BATTLERS];
    /* 0x14 */ u8 monGenders[MAX_BATTLERS];
    /* 0x18 */ u8 monShiny[MAX_BATTLERS];
    /* 0x1C */ u8 monFormNums[MAX_BATTLERS];
    /* 0x20 */ u32 monPersonalities[MAX_BATTLERS];
};

// size: 0x4
struct PlaySoundMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u16 sdatID;
};

// size: 0x28
struct ToggleVanishMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 toggle;
    /* 0x2 */ u8 isSubstitute;
    /* 0x3 */ u8 padding_03;
    /* 0x4 */ u16 species[MAX_BATTLERS];
    /* 0xC */ u8 gender[MAX_BATTLERS];
    /* 0x10 */ u8 isShiny[MAX_BATTLERS];
    /* 0x14 */ u8 formNum[MAX_BATTLERS];
    /* 0x18 */ u32 personality[MAX_BATTLERS];
};

// size: 0x4
struct SetStatusIconMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 status;
    /* 0x2 */ u16 padding_02;
};

// size: 0x4
struct TrainerMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 msg;
    /* 0x2 */ u16 padding_02;
};

// size: 0x4
struct RecallMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    /* 0x2 */ u16 hpPercent;
};

// size: 0x4
struct SendOutMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 partySlot;
    // Out of 1000.
    /* 0x2 */ u16 hpPercent;
};

// size: 0x8
struct LeadMonMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01[3];
    /* 0x4 */ u8 partySlot[MAX_BATTLERS];
};

// size: 0x28
struct AlertMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01[3];
    /* 0x4 */ BattleMessage msg;
};

// size: 0x14
struct RefreshHPGaugeMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 level;
    /* 0x2 */ s16 curHP;
    /* 0x4 */ u16 maxHP;
    /* 0x6 */ u8 partySlot;
    /* 0x7 */ u8 status : 5;
    /* 0x7 */ u8 gender : 2;
    /* 0x7 */ u8 caughtSpecies : 1;
    /* 0x8 */ u32 curExp;
    /* 0xC */ u32 maxExp;
    /* 0x10 */ int numSafariBalls;
};

// No form, ability or update flags in this game (as in Diamond and Pearl).
// size: 0x20
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

// size: 0x4
struct ForgetMoveMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 slot;
    /* 0x2 */ u16 move;
};

// size: 0x4
struct MosaicSetMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 intensity;
    /* 0x2 */ u8 wait;
    /* 0x3 */ u8 padding_03;
};

// size: 0xC
struct MonChangeFormMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 formNum;
    /* 0x2 */ u16 species;
    /* 0x4 */ u8 gender;
    /* 0x5 */ u8 isShiny;
    /* 0x6 */ u8 padding_06[2];
    /* 0x8 */ u32 personality;
};

// size: 0x4
struct RecordIncrementMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 battlerType;
    /* 0x2 */ u16 record;
};

// No recorded inputs in this game.
// size: 0x4
struct EscapeMsgMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 escaperBitmask;
    /* 0x2 */ u16 padding_02;
};

// size: 0x4
struct MoveHitSoundMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 effectiveness;
    /* 0x2 */ u8 padding_02[2];
};

// size: 0x4
struct MusicPlayMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01;
    /* 0x2 */ u16 bgmID;
};

// No recorded inputs in this game.
// size: 0x8
struct ResultSubmitMessage {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 padding_01;
    /* 0x2 */ u16 recordedInputCount;
    /* 0x4 */ u32 resultMask;
};

// size: 0x4
struct CommandClearMsg {
    /* 0x0 */ u8 command;
    /* 0x1 */ u8 netID;
    /* 0x2 */ u16 padding_02;
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
