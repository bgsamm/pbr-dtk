#pragma once

#include "ds/battle/battle_system.hpp"
#include "ds/battle/battle_constants.hpp"

#include <revolution/types.h>

/*
 * Glue between the code inherited from the Gen 4 DS games and the Wii side of
 * the game: item data, NARC access, the LCRNG, stubbed DS hardware calls and
 * the start of the DS battle application.
 *
 * Names follow pret/pokeplatinum where the code is the same as on the DS.
 */

struct ApplicationManager;
struct BattleMessage;
struct BattleSystem;
struct FieldBattleDTO;
struct Pokemon;
struct Strbuf;

#define NUM_ITEMS 464
#define NUM_MAIL_ITEMS 12
#define NUM_BERRY_ITEMS 64
#define ITEM_PARTY_PARAM_SIZE 20

#define NARC_INDEX_ITEM_DATA 16


enum ItemDataParam {
    ITEM_PARAM_PRICE,
    ITEM_PARAM_HOLD_EFFECT,
    ITEM_PARAM_EFFECT_PARAM,
    ITEM_PARAM_PREVENT_TOSS,
    ITEM_PARAM_CAN_REGISTER,
    ITEM_PARAM_FIELD_POCKET,
    ITEM_PARAM_FIELD_USE_FUNC,
    ITEM_PARAM_BATTLE_USE_CATEGORY,
    ITEM_PARAM_PLUCK_EFFECT,
    ITEM_PARAM_FLING_EFFECT,
    ITEM_PARAM_FLING_POWER,
    ITEM_PARAM_NATURAL_GIFT_POWER,
    ITEM_PARAM_NATURAL_GIFT_TYPE,
    ITEM_PARAM_BATTLE_POCKET,
    ITEM_PARAM_PARTY_USE,
    ITEM_PARAM_HEAL_SLEEP,
    ITEM_PARAM_HEAL_POISON,
    ITEM_PARAM_HEAL_BURN,
    ITEM_PARAM_HEAL_FREEZE,
    ITEM_PARAM_HEAL_PARALYSIS,
    ITEM_PARAM_HEAL_CONFUSION,
    ITEM_PARAM_HEAL_ATTRACT,
    ITEM_PARAM_GUARD_SPEC,
    ITEM_PARAM_REVIVE,
    ITEM_PARAM_REVIVE_ALL,
    ITEM_PARAM_LEVEL_UP,
    ITEM_PARAM_EVOLVE,
    ITEM_PARAM_ATK_STAGES,
    ITEM_PARAM_DEF_STAGES,
    ITEM_PARAM_SPATK_STAGES,
    ITEM_PARAM_SPDEF_STAGES,
    ITEM_PARAM_SPEED_STAGES,
    ITEM_PARAM_ACC_STAGES,
    ITEM_PARAM_CRIT_STAGES,
    ITEM_PARAM_PP_UP,
    ITEM_PARAM_PP_MAX,
    ITEM_PARAM_PP_RESTORE,
    ITEM_PARAM_PP_RESTORE_ALL,
    ITEM_PARAM_HP_RESTORE,
    ITEM_PARAM_GIVE_HP_EVS,
    ITEM_PARAM_GIVE_ATK_EVS,
    ITEM_PARAM_GIVE_DEF_EVS,
    ITEM_PARAM_GIVE_SPEED_EVS,
    ITEM_PARAM_GIVE_SPATK_EVS,
    ITEM_PARAM_GIVE_SPDEF_EVS,
    ITEM_PARAM_GIVE_FRIENDSHIP_LOW,
    ITEM_PARAM_GIVE_FRIENDSHIP_MED,
    ITEM_PARAM_GIVE_FRIENDSHIP_HIGH,
    ITEM_PARAM_HP_EVS,
    ITEM_PARAM_ATK_EVS,
    ITEM_PARAM_DEF_EVS,
    ITEM_PARAM_SPEED_EVS,
    ITEM_PARAM_SPATK_EVS,
    ITEM_PARAM_SPDEF_EVS,
    ITEM_PARAM_HP_RESTORED,
    ITEM_PARAM_PP_RESTORED,
    ITEM_PARAM_FRIENDSHIP_LOW,
    ITEM_PARAM_FRIENDSHIP_MED,
    ITEM_PARAM_FRIENDSHIP_HIGH,
};

// size: 0x14
struct ItemPartyParam {
    /* 0x0 */ u8 healSleep : 1;
    /* 0x0 */ u8 healPoison : 1;
    /* 0x0 */ u8 healBurn : 1;
    /* 0x0 */ u8 healFreeze : 1;
    /* 0x0 */ u8 healParalysis : 1;
    /* 0x0 */ u8 healConfusion : 1;
    /* 0x0 */ u8 healAttract : 1;
    /* 0x0 */ u8 guardSpec : 1;
    /* 0x1 */ u8 revive : 1;
    /* 0x1 */ u8 reviveAll : 1;
    /* 0x1 */ u8 levelUp : 1;
    /* 0x1 */ u8 evolve : 1;
    /* 0x1 */ u8 atkStages : 4;
    /* 0x2 */ u8 defStages : 4;
    /* 0x2 */ u8 spatkStages : 4;
    /* 0x3 */ u8 spdefStages : 4;
    /* 0x3 */ u8 speedStages : 4;
    /* 0x4 */ u8 accStages : 4;
    /* 0x4 */ u8 critStages : 2;
    /* 0x4 */ u8 ppUp : 1;
    /* 0x4 */ u8 ppMax : 1;
    /* 0x5 */ u8 ppRestore : 1;
    /* 0x5 */ u8 ppRestoreAll : 1;
    /* 0x5 */ u8 hpRestore : 1;
    /* 0x5 */ u8 giveHPEVs : 1;
    /* 0x5 */ u8 giveAtkEVs : 1;
    /* 0x5 */ u8 giveDefEVs : 1;
    /* 0x5 */ u8 giveSpeedEVs : 1;
    /* 0x5 */ u8 giveSpAtkEVs : 1;
    /* 0x6 */ u8 giveSpDefEVs : 1;
    /* 0x6 */ u8 giveFriendshipLow : 1;
    /* 0x6 */ u8 giveFriendshipMed : 1;
    /* 0x6 */ u8 giveFriendshipHigh : 1;
    /* 0x6 */ u8 unused : 4;
    /* 0x7 */ s8 hpEVs;
    /* 0x8 */ s8 atkEVs;
    /* 0x9 */ s8 defEVs;
    /* 0xA */ s8 speedEVs;
    /* 0xB */ s8 spatkEVs;
    /* 0xC */ s8 spdefEVs;
    /* 0xD */ u8 hpRestored;
    /* 0xE */ u8 ppRestored;
    /* 0xF */ s8 friendshipLow;
    /* 0x10 */ s8 friendshipMed;
    /* 0x11 */ s8 friendshipHigh;
    /* 0x12 */ u8 padding[2];
};

// size: 0x22
struct ItemData {
    /* 0x0 */ u16 price;
    /* 0x2 */ u8 holdEffect;
    /* 0x3 */ u8 effectParam;
    /* 0x4 */ u8 pluckEffect;
    /* 0x5 */ u8 flingEffect;
    /* 0x6 */ u8 flingPower;
    /* 0x7 */ u8 naturalGiftPower;
    /* 0x8 */ u16 naturalGiftType : 5;
    /* 0x8 */ u16 preventToss : 1;
    /* 0x8 */ u16 canRegister : 1;
    /* 0x8 */ u16 fieldPocket : 4;
    /* 0x8 */ u16 battlePocket : 5;
    /* 0xA */ u8 fieldUseFunc;
    /* 0xB */ u8 battleUseCategory;
    /* 0xC */ u8 partyUse;
    /* 0xD */ u8 padding_0D;
    /* 0xE */ union {
        ItemPartyParam partyUseParam;
        u8 partyUseParamBytes[ITEM_PARTY_PARAM_SIZE];
    };
};

// size: 0x4
struct BagItem {
    /* 0x0 */ u16 item;
    /* 0x2 */ u16 quantity;
};

// size: 0x774
struct Bag {
    /* 0x0 */ BagItem items[165];
    /* 0x294 */ BagItem keyItems[50];
    /* 0x35C */ BagItem tmHms[100];
    /* 0x4EC */ BagItem mail[12];
    /* 0x51C */ BagItem medicine[40];
    /* 0x5BC */ BagItem berries[64];
    /* 0x6BC */ BagItem pokeballs[15];
    /* 0x6F8 */ BagItem battleItems[30];
    /* 0x770 */ u32 registeredItem;
};

// TODO Allocated by fn_803D9BBC and freed by fn_803D9D7C, never read in this unit.
// size: 0x14
struct Unk806405F0 {
    /* 0x0 */ s32 _00;
    /* 0x4 */ s32 _04;
    /* 0x8 */ s32 _08;
    /* 0xC */ s32 _0C;
    /* 0x10 */ u8 unk10[0x4];
};

// TODO Holds what the Wii side passes to the DS battle application.
// size: 0x18
struct Unk806405F4 {
    /* 0x0 */ u32 battleType;
    /* 0x4 */ FieldBattleDTO *dto;
    /* 0x8 */ Pokemon *mon;
    /* 0xC */ u8 unkC[0x8];
    /* 0x14 */ ApplicationManager *appMan;
};

// TODO The message window owned by the Wii battle code.
// size: 0x40
struct Unk8048CE28 {
    /* 0x0 */ u8 unk0[0x4];
    /* 0x4 */ u32 pendingCommand;
    /* 0x8 */ u8 unk8[0x4];
    /* 0xC */ u32 _0C;
    /* 0x10 */ u8 unk10[0x4];
    /* 0x14 */ u32 _14;
    /* 0x18 */ u32 _18;
    /* 0x1C */ u32 _1C;
    /* 0x20 */ u32 _20;
    /* 0x24 */ u8 unk24[0x1C];
};

// TODO Arguments of the battle commands sent to fn_8016FA4C; the layout depends on the command.
// size: 0x40
union Unk8048CDE8 {
    // A message to show (see fn_803D9A44)
    struct {
        /* 0x0 */ const u16 *text;
        /* 0x4 */ u32 size;
        /* 0x8 */ u32 _08;
        /* 0xC */ void *param;
        /* 0x10 */ u32 _10;
        /* 0x14 */ u32 _14;
    } message;
    // Other commands: a battler index and integers
    /* 0x0 */ u32 args[0x10];
};

// TODO Table of the game data files; each field is a handle read by the getters in 8038F424.
// size: 0x84
struct Unk8063CE34 {
    /* 0x0 */ u8 unk0[0xC];
    /* 0xC */ u8 *itemData;
    /* 0x10 */ u8 *speciesData;
    /* 0x14 */ u8 unk14[0x4];
    /* 0x18 */ u8 *moveData;
    /* 0x1C */ u8 *expData;
    /* 0x20 */ u8 unk20[0x28];
    /* 0x48 */ u8 *levelUpMoveData;
    /* 0x4C */ u8 unk4C[0x38];
};

s32 Item_LoadParam(u16 item, ItemDataParam param, u32 heapId);
s32 Item_Get(ItemData *itemData, ItemDataParam param);
u8 Item_IsMail(u16 item);
u8 Item_IsBerry(u16 item);
ItemData *ItemTable_Load(u32 heapId);
ItemData *ItemTable_Index(ItemData *itemTable, u16 index);
Bag *Bag_New(u32 heapId);
u16 LCRNG_Next();

// Stubs of DS hardware and system calls
BOOL fn_803D97E4(void *, u16);
// TODO probably Text_IsPrinterActive (pret). The printer id is an int here: battle_script passes a word without
// truncating it.
BOOL fn_803D97EC(int printerID);
void fn_803D97F4();
// TODO probably Sound_PlayEffect (pret). It returns nothing here: the stub is a single blr.
void fn_803D97F8(int seqID);
s32 fn_803D97FC(u32, u32);
void fn_803D9804(u32);
void fn_803D9808(void *);
void fn_803D980C(void *);
// TODO probably HealthBox_Type (pret)
u8 fn_803D9810(int battlerType, u32 battleType);
// TODO probably useless_0226BCD0 (pret), the end of the subscreen transition
BOOL fn_803D9818(void *btlSubscreen);
// TODO probably BattleSubscreen_IsReady (pret)
BOOL fn_803D9820(void *btlSubscreen);
// TODO probably BattleSystem_MenuInput (pret)
int fn_803D9828(void *btlSubscreen);
// TODO probably ov16_Dummy3 (pret)
void fn_803D9830(void *btlSubscreen, int param1);
// TODO probably BattleSubscreen_SetupBackground (pret), without the NARC arguments
void fn_803D9834(void *btlSubscreen, int menuConfigIndex, int forceRedraw, void *battleDisplayData);
// TODO probably BattleSubscreen_HideBallSprites (pret)
void fn_803D9838(void *btlSubscreen);
// TODO probably the link position of a network id (pret BattleSystem_GetLinkPlayerPositionForBattler)
int fn_803D983C(int netId);
void fn_803D9844(u32);
// TODO probably CommSys_CurNetId (pret)
u16 fn_803D9848();
void fn_803D9850(void *);
void fn_803D9854(int);
void fn_803D9858(int, int);
BOOL fn_803D985C();
BOOL fn_803D9864(int);
void fn_803D986C(int);
BOOL fn_803D9870();

u8 App_PixelCount(s16 cur, s16 max, s32 maxPixels);
void fn_803D989C(BOOL cond, const char *fmt, ...);
BOOL NARC_ReadWholeMemberByIndexPair(void *dest, u32 narcId, u32 memberIndex);
void NARC_ReadFromMemberByIndexPair(void *dest, u32 narcId, u32 memberIndex, u32 offset, u32 bytesToRead);
void *NARC_AllocAndReadFromMemberByIndexPair(u32 narcId, u32 memberIndex, u32 heapId, u32 offset, u32 bytesToRead);
u8 fn_803D9A44(Strbuf *str, void *param);
const u16 *fn_803D9AEC(BattleMessage *battleMsg, u32 *size);
void *fn_803D9BAC();
void fn_803D9BB4(void *data);
void fn_803D9BBC();
Unk806405F4 *fn_803D9C18();
u32 fn_803D9D1C();
void fn_803D9D7C();
BOOL fn_803D9E08();
ApplicationManager *fn_803D9E48();
BOOL fn_803D9E54();
