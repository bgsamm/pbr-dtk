#pragma once

#include <revolution/types.h>

/*
 * Glue between the battle code inherited from the Gen 4 DS games and the
 * Wii side of the game: item data, archive (NARC) access, random numbers,
 * stubbed DS hardware calls and the battle message queue.
 *
 * Like the rest of the DS-derived code, this unit is built with -O4,s and
 * -inline noauto (see configure.py).
 */

#define ITEM_COUNT 464
#define ITEM_MAIL_COUNT 12
#define ITEM_BERRY_COUNT 64
#define ITEM_PARTY_PARAM_COUNT 20

#define NARC_ITEM_DATA 16

enum ItemParam {
    ITEM_PARAM_PRICE = 0,
    ITEM_PARAM_HOLD_EFFECT = 1,
    ITEM_PARAM_HOLD_EFFECT_PARAM = 2,
    ITEM_PARAM_PREVENT_TOSS = 3,
    ITEM_PARAM_IS_SELECTABLE = 4,
    ITEM_PARAM_FIELD_POCKET = 5,
    ITEM_PARAM_FIELD_USE_FUNC = 6,
    ITEM_PARAM_BATTLE_USE_FUNC = 7,
    ITEM_PARAM_PLUCK_EFFECT = 8,
    ITEM_PARAM_FLING_EFFECT = 9,
    ITEM_PARAM_FLING_POWER = 10,
    ITEM_PARAM_NATURAL_GIFT_POWER = 11,
    ITEM_PARAM_NATURAL_GIFT_TYPE = 12,
    ITEM_PARAM_BATTLE_POCKET = 13,
    ITEM_PARAM_PARTY_USE = 14,

    ITEM_PARAM_SLP_HEAL = 15,
    ITEM_PARAM_PSN_HEAL,
    ITEM_PARAM_BRN_HEAL,
    ITEM_PARAM_FRZ_HEAL,
    ITEM_PARAM_PRZ_HEAL,
    ITEM_PARAM_CFS_HEAL,
    ITEM_PARAM_INFATUATION_HEAL,
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
    ITEM_PARAM_HP_EV_UP,
    ITEM_PARAM_ATK_EV_UP,
    ITEM_PARAM_DEF_EV_UP,
    ITEM_PARAM_SPEED_EV_UP,
    ITEM_PARAM_SPATK_EV_UP,
    ITEM_PARAM_SPDEF_EV_UP,
    ITEM_PARAM_FRIENDSHIP_LO,
    ITEM_PARAM_FRIENDSHIP_MED,
    ITEM_PARAM_FRIENDSHIP_HI,
    ITEM_PARAM_HP_EV,
    ITEM_PARAM_ATK_EV,
    ITEM_PARAM_DEF_EV,
    ITEM_PARAM_SPEED_EV,
    ITEM_PARAM_SPATK_EV,
    ITEM_PARAM_SPDEF_EV,
    ITEM_PARAM_HP_RESTORE_AMOUNT,
    ITEM_PARAM_PP_RESTORE_AMOUNT,
    ITEM_PARAM_FRIENDSHIP_LO_AMOUNT,
    ITEM_PARAM_FRIENDSHIP_MED_AMOUNT,
    ITEM_PARAM_FRIENDSHIP_HI_AMOUNT
};

// size: 0x14
struct ItemPartyParam {
    /* 0x0 */ u8 slpHeal : 1;
    u8 psnHeal : 1;
    u8 brnHeal : 1;
    u8 frzHeal : 1;
    u8 przHeal : 1;
    u8 cfsHeal : 1;
    u8 infatuationHeal : 1;
    u8 guardSpec : 1;
    /* 0x1 */ u8 revive : 1;
    u8 reviveAll : 1;
    u8 levelUp : 1;
    u8 evolve : 1;
    u8 atkStages : 4;
    /* 0x2 */ u8 defStages : 4;
    u8 spatkStages : 4;
    /* 0x3 */ u8 spdefStages : 4;
    u8 speedStages : 4;
    /* 0x4 */ u8 accStages : 4;
    u8 critStages : 2;
    u8 ppUp : 1;
    u8 ppMax : 1;
    /* 0x5 */ u8 ppRestore : 1;
    u8 ppRestoreAll : 1;
    u8 hpRestore : 1;
    u8 hpEvUp : 1;
    u8 atkEvUp : 1;
    u8 defEvUp : 1;
    u8 speedEvUp : 1;
    u8 spatkEvUp : 1;
    /* 0x6 */ u8 spdefEvUp : 1;
    u8 friendshipLo : 1;
    u8 friendshipMed : 1;
    u8 friendshipHi : 1;
    u8 unused : 4;
    /* 0x7 */ s8 hpEv;
    /* 0x8 */ s8 atkEv;
    /* 0x9 */ s8 defEv;
    /* 0xa */ s8 speedEv;
    /* 0xb */ s8 spatkEv;
    /* 0xc */ s8 spdefEv;
    /* 0xd */ u8 hpRestoreAmount;
    /* 0xe */ u8 ppRestoreAmount;
    /* 0xf */ s8 friendshipLoAmount;
    /* 0x10 */ s8 friendshipMedAmount;
    /* 0x11 */ s8 friendshipHiAmount;
    u8 unk1[0x2];
};

// size: 0x22
struct ItemData {
    /* 0x0 */ u16 price;
    /* 0x2 */ u8 holdEffect;
    /* 0x3 */ u8 holdEffectParam;
    /* 0x4 */ u8 pluckEffect;
    /* 0x5 */ u8 flingEffect;
    /* 0x6 */ u8 flingPower;
    /* 0x7 */ u8 naturalGiftPower;
    /* 0x8 */ u16 naturalGiftType : 5;
    u16 preventToss : 1;
    u16 isSelectable : 1;
    u16 fieldPocket : 4;
    u16 battlePocket : 5;
    /* 0xa */ u8 fieldUseFunc;
    /* 0xb */ u8 battleUseFunc;
    /* 0xc */ u8 partyUse;
    /* 0xd */ u8 padding;
    /* 0xe */ union {
        ItemPartyParam partyUseParam;
        u8 partyUseParamRaw[ITEM_PARTY_PARAM_COUNT];
    };
};

// size: 0x14
struct DSRandState {
    /* 0x0 */ s32 mSeedA;
    /* 0x4 */ s32 mCountA;
    /* 0x8 */ s32 mSeedB;
    /* 0xc */ s32 mCountB;
    u8 unk1[0x4];
};

// size: 0x18
struct DSSystem {
    /* 0x0 */ u32 mFlags;
    /* 0x4 */ u32 *mFlagsOut;
    /* 0x8 */ void *mHeap;
    u8 unk1[0x8];
    /* 0x14 */ void *mMsgManager;
};

// size: 0x40
struct MsgWindow {
    u8 unk1[0x4];
    /* 0x4 */ void *mPending;
    u8 unk2[0x4];
    /* 0xc */ u32 mColor;
    u8 unk3[0x8];
    /* 0x18 */ u32 mFont;
    u8 unk4[0x24];
};

// size: 0x40
struct MsgRequest {
    /* 0x0 */ const u16 *mText;
    /* 0x4 */ u32 mSize;
    /* 0x8 */ u32 mFlags;
    /* 0xc */ void *mParam;
    /* 0x10 */ u32 mColor;
    /* 0x14 */ u32 mFont;
    u8 unk1[0x28];
};

// Battle message as sent by the DS battle code
struct BattleMsg {
    /* 0x0 */ u8 mType;
};

// size: 0x1c (only the fields used here)
struct BattleMsgSource {
    u8 unk1[0x18];
    /* 0x18 */ void *mStrbuf;
};

u32 Item_LoadParam(u16 item, u32 param, u32 heapId);
s32 ItemData_GetParam(ItemData *item, u32 param);
BOOL Item_IsMail(u16 item);
BOOL Item_IsBerry(u16 item);
ItemData *Item_LoadTable(u32 heapId);
ItemData *ItemTable_GetEntry(ItemData *table, u16 index);

u16 DS_Rand();

void DSRand_Create();
DSSystem *DSSystem_Create();

void Narc_ReadFromMember(void *dst, u32 narcId, u32 memberId, u32 offset, u32 size);
void *Narc_AllocReadFromMember(u32 narcId, u32 memberId, u32 heapId, u32 offset, u32 size);

void *DSSystem_GetUserData();
void DSSystem_SetUserData(void *data);
u32 DSSystem_Init();
void DSSystem_Exit();
void *DSSystem_GetMsgManager();

// Stubbed DS calls (names unknown)
BOOL fn_803D97E4(void *, u16);
s32 fn_803D97FC(u32, u32);
void fn_803D9804(u32);
void fn_803D9808(void *);
void fn_803D980C(void *);
void fn_803D9844(u32);
u8 fn_803D9848(u32, u32);
void fn_803D9850(void *);
u8 fn_803D9878(s16 value, s16 max, s32 scale);
void fn_803D989C(BOOL cond, const char *fmt, ...);
void *fn_803D9778(u32 heapId);
s32 fn_803D9A44(void *strbuf, void *param);
