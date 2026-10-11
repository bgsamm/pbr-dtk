#include "ds/DSbridge.hpp"

#include "common.hpp"

#include <cstdarg>
#include <cstring>


// TODO Replace with proper imports once the callers' units are decompiled
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *heap);
void fn_8016E2DC();
void fn_8016E70C(DSSystem *system);
void fn_8016ECC0(DSSystem *system);
void fn_8016EEC8(DSSystem *system);
void *fn_8016F0F4(void *archive, u32 narcId, u32 memberId, u32 *size);
void fn_8016FA4C(void *window, MsgRequest *request);
void fn_8017CC8C(u32 flags);
void *fn_80035D9C();
void fn_80035E60(void *config, BOOL enable);
void fn_80035E70(void *config, u32 mode);
void *fn_803DA26C(u32 heapId);
void fn_803DEEA4();
void *fn_803DECFC(const void *template_, u32 *flags, u32 count);
void fn_803DED78(void *msgManager);
BattleMsgSource *fn_803DEDB0(void *msgManager);
BOOL fn_803DEDC0(void *msgManager);
s32 fn_803DEE9C(void *msgManager);
void fn_803DEF70();
const u16 *fn_803DF418(void *strbuf);
s32 fn_803DF274(void *strbuf);
u32 fn_803ACA60(BattleMsgSource *source);
u32 fn_803ACA68(BattleMsgSource *source);
void fn_803AF38C(BattleMsgSource *source, BattleMsg *msg, u32 param);
s32 fn_803AC830();
u32 fn_803AB534();

// Item data file reader (one getter per field)
u16 fn_8038FD44(void *file, u32 item);
u8 fn_8038FD78(void *file, u32 item);
u8 fn_8038FDAC(void *file, u32 item);
u8 fn_8038FDE0(void *file, u32 item);
u8 fn_8038FE14(void *file, u32 item);
u8 fn_8038FE48(void *file, u32 item);
u8 fn_8038FE7C(void *file, u32 item);
u8 fn_8038FEB0(void *file, u32 item);
u8 fn_8038FEE8(void *file, u32 item);
u8 fn_8038FF20(void *file, u32 item);
u8 fn_8038FF58(void *file, u32 item);
u8 fn_8038FF90(void *file, u32 item);
u8 fn_8038FFC8(void *file, u32 item);
u8 fn_8038FFFC(void *file, u32 item);
u8 fn_80390030(void *file, u32 item);
u8 fn_80390064(void *file, u32 item);
u8 fn_80390098(void *file, u32 item, s32 index);
}

// TODO Owned by units that are not decompiled yet
extern "C" {
extern void *lbl_8063F1D8;      // DS archive handle
extern u8 lbl_8063CE34[];       // item data file
extern MsgWindow lbl_8048CE28;  // message window
extern MsgRequest lbl_8048CDE8; // pending message request
}

/* lbl_80405B38 */ extern const u16 gMailItems[ITEM_MAIL_COUNT];
/* lbl_80405B50 */ extern const u16 gBerryItems[ITEM_BERRY_COUNT];
/* lbl_80405BD0 */ extern const u8 gDSMsgTemplate[];

/* lbl_806405D8 */ ItemData *gItemTable;
/* lbl_806405E0 */ u32 gDSRandSeed;
/* lbl_806405E4 */ u32 gDSRandCount;
/* lbl_806405F0 */ DSRandState *gDSRandState;
/* lbl_806405F4 */ DSSystem *gDSSystem;
/* lbl_806405F8 */ void *gDSUserData;

u32 Item_LoadParam(u16 item, u32 param, u32 heapId) {
    if (gItemTable == NULL) {
        return 0;
    }
    return ItemData_GetParam(&gItemTable[item], param);
}

static inline s32 ItemPartyParam_Get(ItemPartyParam *param, u32 which) {
    switch (which) {
        case ITEM_PARAM_SLP_HEAL:             return param->slpHeal;
        case ITEM_PARAM_PSN_HEAL:             return param->psnHeal;
        case ITEM_PARAM_BRN_HEAL:             return param->brnHeal;
        case ITEM_PARAM_FRZ_HEAL:             return param->frzHeal;
        case ITEM_PARAM_PRZ_HEAL:             return param->przHeal;
        case ITEM_PARAM_CFS_HEAL:             return param->cfsHeal;
        case ITEM_PARAM_INFATUATION_HEAL:     return param->infatuationHeal;
        case ITEM_PARAM_GUARD_SPEC:           return param->guardSpec;
        case ITEM_PARAM_REVIVE:               return param->revive;
        case ITEM_PARAM_REVIVE_ALL:           return param->reviveAll;
        case ITEM_PARAM_LEVEL_UP:             return param->levelUp;
        case ITEM_PARAM_EVOLVE:               return param->evolve;
        case ITEM_PARAM_ATK_STAGES:           return param->atkStages;
        case ITEM_PARAM_DEF_STAGES:           return param->defStages;
        case ITEM_PARAM_SPATK_STAGES:         return param->spatkStages;
        case ITEM_PARAM_SPDEF_STAGES:         return param->spdefStages;
        case ITEM_PARAM_SPEED_STAGES:         return param->speedStages;
        case ITEM_PARAM_ACC_STAGES:           return param->accStages;
        case ITEM_PARAM_CRIT_STAGES:          return param->critStages;
        case ITEM_PARAM_PP_UP:                return param->ppUp;
        case ITEM_PARAM_PP_MAX:               return param->ppMax;
        case ITEM_PARAM_PP_RESTORE:           return param->ppRestore;
        case ITEM_PARAM_PP_RESTORE_ALL:       return param->ppRestoreAll;
        case ITEM_PARAM_HP_RESTORE:           return param->hpRestore;
        case ITEM_PARAM_HP_EV_UP:             return param->hpEvUp;
        case ITEM_PARAM_ATK_EV_UP:            return param->atkEvUp;
        case ITEM_PARAM_DEF_EV_UP:            return param->defEvUp;
        case ITEM_PARAM_SPEED_EV_UP:          return param->speedEvUp;
        case ITEM_PARAM_SPATK_EV_UP:          return param->spatkEvUp;
        case ITEM_PARAM_SPDEF_EV_UP:          return param->spdefEvUp;
        case ITEM_PARAM_FRIENDSHIP_LO:        return param->friendshipLo;
        case ITEM_PARAM_FRIENDSHIP_MED:       return param->friendshipMed;
        case ITEM_PARAM_FRIENDSHIP_HI:        return param->friendshipHi;
        case ITEM_PARAM_HP_EV:                return param->hpEv;
        case ITEM_PARAM_ATK_EV:               return param->atkEv;
        case ITEM_PARAM_DEF_EV:               return param->defEv;
        case ITEM_PARAM_SPEED_EV:             return param->speedEv;
        case ITEM_PARAM_SPATK_EV:             return param->spatkEv;
        case ITEM_PARAM_SPDEF_EV:             return param->spdefEv;
        case ITEM_PARAM_HP_RESTORE_AMOUNT:    return param->hpRestoreAmount;
        case ITEM_PARAM_PP_RESTORE_AMOUNT:    return param->ppRestoreAmount;
        case ITEM_PARAM_FRIENDSHIP_LO_AMOUNT: return param->friendshipLoAmount;
        case ITEM_PARAM_FRIENDSHIP_MED_AMOUNT: return param->friendshipMedAmount;
        case ITEM_PARAM_FRIENDSHIP_HI_AMOUNT: return param->friendshipHiAmount;
    }
    return 0;
}

s32 ItemData_GetParam(ItemData *item, u32 param) {
    switch (param) {
        case ITEM_PARAM_PRICE:              return item->price;
        case ITEM_PARAM_HOLD_EFFECT:        return item->holdEffect;
        case ITEM_PARAM_HOLD_EFFECT_PARAM:  return item->holdEffectParam;
        case ITEM_PARAM_PREVENT_TOSS:       return item->preventToss;
        case ITEM_PARAM_IS_SELECTABLE:      return item->isSelectable;
        case ITEM_PARAM_FIELD_POCKET:       return item->fieldPocket;
        case ITEM_PARAM_FIELD_USE_FUNC:     return item->fieldUseFunc;
        case ITEM_PARAM_BATTLE_USE_FUNC:    return item->battleUseFunc;
        case ITEM_PARAM_PLUCK_EFFECT:       return item->pluckEffect;
        case ITEM_PARAM_FLING_EFFECT:       return item->flingEffect;
        case ITEM_PARAM_FLING_POWER:        return item->flingPower;
        case ITEM_PARAM_NATURAL_GIFT_POWER: return item->naturalGiftPower;
        case ITEM_PARAM_NATURAL_GIFT_TYPE:  return item->naturalGiftType;
        case ITEM_PARAM_BATTLE_POCKET:      return item->battlePocket;
        case ITEM_PARAM_PARTY_USE:          return item->partyUse;
        default:
            switch (item->partyUse) {
                case 0: return item->partyUseParamRaw[0];
                case 1: return ItemPartyParam_Get(&item->partyUseParam, param);
            }
    }
    return 0;
}

BOOL Item_IsMail(u16 item) {
    for (int i = 0; i < ITEM_MAIL_COUNT; i++) {
        if (item == gMailItems[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL Item_IsBerry(u16 item) {
    for (int i = 0; i < ITEM_BERRY_COUNT; i++) {
        if (item == gBerryItems[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

ItemData *Item_LoadTable(u32 heapId) {
    ItemData *item;
    s32 i;
    s32 j;
    ItemData *table = (ItemData *)Narc_AllocReadFromMember(NARC_ITEM_DATA, 0, heapId, 0, ITEM_COUNT * sizeof(ItemData));
    gItemTable = table;

    for (i = 0; i < ITEM_COUNT; i++) {
        item = &table[i];
        item->price = fn_8038FD44(lbl_8063CE34 + 0xC, i);
        item->holdEffect = fn_8038FD78(lbl_8063CE34 + 0xC, i);
        item->holdEffectParam = fn_8038FDAC(lbl_8063CE34 + 0xC, i);
        item->pluckEffect = fn_8038FDE0(lbl_8063CE34 + 0xC, i);
        item->flingEffect = fn_8038FE14(lbl_8063CE34 + 0xC, i);
        item->flingPower = fn_8038FE48(lbl_8063CE34 + 0xC, i);
        item->naturalGiftPower = fn_8038FE7C(lbl_8063CE34 + 0xC, i);
        item->naturalGiftType = fn_8038FEB0(lbl_8063CE34 + 0xC, i);
        item->preventToss = fn_8038FEE8(lbl_8063CE34 + 0xC, i);
        item->isSelectable = fn_8038FF20(lbl_8063CE34 + 0xC, i);
        item->fieldPocket = fn_8038FF58(lbl_8063CE34 + 0xC, i);
        item->battlePocket = fn_8038FF90(lbl_8063CE34 + 0xC, i);
        item->fieldUseFunc = fn_8038FFC8(lbl_8063CE34 + 0xC, i);
        item->battleUseFunc = fn_8038FFFC(lbl_8063CE34 + 0xC, i);
        item->partyUse = fn_80390030(lbl_8063CE34 + 0xC, i);
        item->padding = fn_80390064(lbl_8063CE34 + 0xC, i);

        for (j = 0; j < ITEM_PARTY_PARAM_COUNT; j++) {
            item->partyUseParamRaw[j] = fn_80390098(lbl_8063CE34 + 0xC, i, j);
        }
    }

    return table;
}

ItemData *ItemTable_GetEntry(ItemData *table, u16 index) {
    return &table[index];
}

// TODO name: allocates and clears a 0x774-byte work area
void *fn_803D9778(u32 heapId) {
    void *work = fn_8016DF70(heapId, 0x774);
    memset(work, 0, 0x774);
    return work;
}

// TODO 98%: register allocation differs on the seed/count loads
u16 DS_Rand() {
    u32 seed = gDSRandSeed * 0x41C64E6D;
    gDSRandCount++;
    gDSRandSeed = seed + 0x6073;
    return gDSRandSeed >> 16;
}

// DS hardware and system calls stubbed out on the Wii
BOOL fn_803D97E4(void *, u16) { return TRUE; }
BOOL fn_803D97EC() { return FALSE; }
void fn_803D97F4() {}
void fn_803D97F8() {}
s32 fn_803D97FC(u32, u32) { return FALSE; }
void fn_803D9804(u32) {}
void fn_803D9808(void *) {}
void fn_803D980C(void *) {}
BOOL fn_803D9810() { return FALSE; }
BOOL fn_803D9818() { return TRUE; }
BOOL fn_803D9820() { return TRUE; }
BOOL fn_803D9828() { return FALSE; }
void fn_803D9830() {}
void fn_803D9834() {}
void fn_803D9838() {}
BOOL fn_803D983C() { return FALSE; }
void fn_803D9844(u32) {}
u8 fn_803D9848(u32, u32) { return FALSE; }
void fn_803D9850(void *) {}
void fn_803D9854() {}
void fn_803D9858() {}
BOOL fn_803D985C() { return FALSE; }
BOOL fn_803D9864() { return TRUE; }
void fn_803D986C() {}
BOOL fn_803D9870() { return FALSE; }

// Scales value / max to a 0..scale range, never rounding a non-zero value down to 0
u8 fn_803D9878(s16 value, s16 max, s32 scale) {
    u8 result = value * scale / max;
    if (result == 0 && value > 0) {
        result = 1;
    }
    return result;
}

// Debug print, compiled out
void fn_803D989C(BOOL cond, const char *fmt, ...) {
    if (!cond) {
        va_list args;
        va_start(args, fmt);
    }
}

// TODO Callers disagree on the signature; kept under its address name
extern "C" BOOL fn_803D990C(void *dst, u32 narcId, u32 memberId) {
    u32 size;
    void *src = fn_8016F0F4(lbl_8063F1D8, narcId, memberId, &size);
    if (src == NULL) {
        return TRUE;
    }
    memcpy(dst, src, size);
    return FALSE;
}

void Narc_ReadFromMember(void *dst, u32 narcId, u32 memberId, u32 offset, u32 size) {
    u32 memberSize;
    u8 *src = (u8 *)fn_8016F0F4(lbl_8063F1D8, narcId, memberId, &memberSize);
    if (src != NULL) {
        memcpy(dst, src + offset, size);
    }
}

void *Narc_AllocReadFromMember(u32 narcId, u32 memberId, u32 heapId, u32 offset, u32 size) {
    void *dst = fn_8016DF70(heapId, size);
    u32 memberSize;
    u8 *src = (u8 *)fn_8016F0F4(lbl_8063F1D8, narcId, memberId, &memberSize);
    if (src != NULL) {
        memcpy(dst, src + offset, size);
    }
    return dst;
}

// Queues a string for the message window
s32 fn_803D9A44(void *strbuf, void *param) {
    fn_8016E2DC();
    if (lbl_8048CE28.mPending != NULL) {
        lbl_8048CDE8.mText = fn_803DF418(strbuf);
        lbl_8048CDE8.mSize = (fn_803DF274(strbuf) + 1) * sizeof(u16);
        lbl_8048CDE8.mFlags = 0;
        lbl_8048CDE8.mParam = param;
        lbl_8048CDE8.mColor = lbl_8048CE28.mColor;
        lbl_8048CDE8.mFont = lbl_8048CE28.mFont;
        fn_8016FA4C(lbl_8048CE28.mPending, &lbl_8048CDE8);
        lbl_8048CE28.mPending = NULL;
        lbl_8048CE28.mColor = 0xFF;
    }
    return 0;
}

// Builds the text of a battle message, returns it and its size in bytes
#pragma dont_inline on
const u16 *fn_803D9AEC(BattleMsg *msg, u32 *size) {
    const u16 *text;
    u32 param;
    BattleMsgSource *source;

    source = fn_803DEDB0(DSSystem_GetMsgManager());
    switch (msg->mType) {
        case 0x14:
            param = fn_803ACA68(source);
            break;
        case 0x15:
        case 0x25:
            param = fn_803ACA60(source);
            break;
        default:
            param = fn_803ACA60(source);
            break;
    }
    fn_803AF38C(source, msg, param);

    text = fn_803DF418(source->mStrbuf);
    *size = (fn_803DF274(source->mStrbuf) + 1) * sizeof(u16);
    return text;
}
#pragma dont_inline reset

void *DSSystem_GetUserData() {
    return gDSUserData;
}

void DSSystem_SetUserData(void *data) {
    gDSUserData = data;
}

void DSRand_Create() {
    gDSRandState = new DSRandState;
    memset(gDSRandState, 0, sizeof(DSRandState));
    gDSRandState->mSeedA = -1;
    gDSRandState->mCountA = 0;
    gDSRandState->mSeedB = -1;
    gDSRandState->mCountB = 0;
}

DSSystem *DSSystem_Create() {
    gDSSystem = new DSSystem;
    memset(gDSSystem, 0, sizeof(DSSystem));
    gDSSystem->mHeap = fn_803DA26C(0);
    fn_8016E70C(gDSSystem);

    void *config = fn_80035D9C();
    if (gDSSystem->mFlags & 2) {
        fn_80035E60(config, TRUE);
    } else {
        fn_80035E60(config, FALSE);
    }
    if (gDSSystem->mFlags & 8) {
        fn_80035E70(config, 3);
    } else {
        fn_80035E70(config, 2);
    }

    fn_8016ECC0(gDSSystem);
    fn_8016EEC8(gDSSystem);
    fn_8017CC8C(gDSSystem->mFlags);
    return gDSSystem;
}

BOOL fn_803D9CE4() {
    return TRUE;
}

BOOL fn_803D9CEC() {
    return fn_803AB534() != 0;
}

BOOL fn_803D9D14() {
    return TRUE;
}

u32 DSSystem_Init() {
    DSRand_Create();
    fn_803DEEA4();
    DSSystem_Create();
    *gDSSystem->mFlagsOut = gDSSystem->mFlags;
    gDSSystem->mMsgManager = fn_803DECFC(gDSMsgTemplate, gDSSystem->mFlagsOut, 0x1B);
    return gDSSystem->mFlags;
}

void DSSystem_Exit() {
    if (gDSSystem->mMsgManager != NULL) {
        fn_803DED78(gDSSystem->mMsgManager);
        gDSSystem->mMsgManager = NULL;
    }
    if (gDSSystem->mHeap != NULL) {
        fn_8016E0A0(gDSSystem->mHeap);
        gDSSystem->mHeap = NULL;
    }
    if (gDSRandState != NULL) {
        delete gDSRandState;
        gDSRandState = NULL;
    }
    if (gDSSystem != NULL) {
        delete gDSSystem;
        gDSSystem = NULL;
    }
}

BOOL fn_803D9E08() {
    if (fn_803DEDC0(gDSSystem->mMsgManager)) {
        return TRUE;
    }
    fn_803DEF70();
    return FALSE;
}

void *DSSystem_GetMsgManager() {
    return gDSSystem->mMsgManager;
}

// TODO 88%: the signed comparison operands come out swapped
BOOL fn_803D9E54() {
    s32 a = fn_803DEE9C(gDSSystem->mMsgManager);
    s32 b = fn_803AC830();
    return b > a;
}
