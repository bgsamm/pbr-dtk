#include "ds/DSbridge.hpp"
#include "ds/battle/battle_system.hpp"

#include ".unsorted/80035CB0.hpp"
#include ".unsorted/803DEEA4.hpp"
#include "ds/field_battle_data_transfer.hpp"
#include "ds/overlay_manager.hpp"
#include "ds/pokemon.hpp"
#include "ds/strbuf.hpp"

#include <cstdarg>
#include <cstring>

#include "common.hpp"

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
void fn_8016E2DC();
void fn_8016E70C(Unk806405F4 *params);
void fn_8016ECC0(Unk806405F4 *params);
void fn_8016EEC8(Unk806405F4 *params);
void *fn_8016F0F4(void *archive, u32 narcId, u32 memberIndex, u32 *size);
void fn_8016FA4C(u32 command, Unk8048CDE8 *args);
void fn_8017CC8C(u32 battleType);
Unk80035CB0 *fn_80035D9C();
void fn_80035E60(Unk80035CB0 *config, u32 enable);
void fn_80035E70(Unk80035CB0 *config, u32 mode);
s32 fn_803AC830();
u32 fn_803AB534();

u16 fn_8038FD44(u8 **file, s32 item);
u8 fn_8038FD78(u8 **file, s32 item);
u8 fn_8038FDAC(u8 **file, s32 item);
u8 fn_8038FDE0(u8 **file, s32 item);
u8 fn_8038FE14(u8 **file, s32 item);
u8 fn_8038FE48(u8 **file, s32 item);
u8 fn_8038FE7C(u8 **file, s32 item);
u32 fn_8038FEB0(u8 **file, s32 item);
u32 fn_8038FEE8(u8 **file, s32 item);
u32 fn_8038FF20(u8 **file, s32 item);
u32 fn_8038FF58(u8 **file, s32 item);
u32 fn_8038FF90(u8 **file, s32 item);
u8 fn_8038FFC8(u8 **file, s32 item);
u8 fn_8038FFFC(u8 **file, s32 item);
u8 fn_80390030(u8 **file, s32 item);
u8 fn_80390064(u8 **file, s32 item);
u8 fn_80390098(u8 **file, s32 item, u32 index);

extern void *lbl_8063F1D8;
extern ItemData *gItemTable;
extern u32 gLCRNGState;
// TODO Counts the calls to LCRNG_Next; nothing decompiled reads it yet.
extern u32 lbl_806405E4;
extern Unk8063CE34 lbl_8063CE34;
extern Unk8048CE28 lbl_8048CE28;
extern Unk8048CDE8 lbl_8048CDE8;
}

/* lbl_80405B38 */ static const u16 sMailItemIDs[NUM_MAIL_ITEMS] = {
    137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148};

/* lbl_80405B50 */ static const u16 sBerryItemIDs[NUM_BERRY_ITEMS] = {
    149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170,
    171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192,
    193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212,
};

static BOOL fn_803D9CE4(ApplicationManager *appMan, s32 *state);
static BOOL fn_803D9CEC(ApplicationManager *appMan, s32 *state);
static BOOL fn_803D9D14(ApplicationManager *appMan, s32 *state);

/* lbl_80405BD0 */ static const ApplicationManagerTemplate sBattleAppTemplate = {
    fn_803D9CE4,
    fn_803D9CEC,
    fn_803D9D14,
    FS_OVERLAY_ID_NONE,
};

/* lbl_806405F0 */ static Unk806405F0 *sUnk806405F0;
/* lbl_806405F4 */ static Unk806405F4 *sUnk806405F4;
/* lbl_806405F8 */ static void *sUnk806405F8;

s32 Item_LoadParam(u16 item, ItemDataParam param, u32 heapId) {
    if (gItemTable == NULL) {
        return 0;
    }
    return Item_Get(&gItemTable[item], param);
}

static inline s32 ItemPartyParam_Get(ItemPartyParam *partyParam, ItemDataParam param) {
    switch (param) {
        case ITEM_PARAM_HEAL_SLEEP:           return partyParam->healSleep;
        case ITEM_PARAM_HEAL_POISON:          return partyParam->healPoison;
        case ITEM_PARAM_HEAL_BURN:            return partyParam->healBurn;
        case ITEM_PARAM_HEAL_FREEZE:          return partyParam->healFreeze;
        case ITEM_PARAM_HEAL_PARALYSIS:       return partyParam->healParalysis;
        case ITEM_PARAM_HEAL_CONFUSION:       return partyParam->healConfusion;
        case ITEM_PARAM_HEAL_ATTRACT:         return partyParam->healAttract;
        case ITEM_PARAM_GUARD_SPEC:           return partyParam->guardSpec;
        case ITEM_PARAM_REVIVE:               return partyParam->revive;
        case ITEM_PARAM_REVIVE_ALL:           return partyParam->reviveAll;
        case ITEM_PARAM_LEVEL_UP:             return partyParam->levelUp;
        case ITEM_PARAM_EVOLVE:               return partyParam->evolve;
        case ITEM_PARAM_ATK_STAGES:           return partyParam->atkStages;
        case ITEM_PARAM_DEF_STAGES:           return partyParam->defStages;
        case ITEM_PARAM_SPATK_STAGES:         return partyParam->spatkStages;
        case ITEM_PARAM_SPDEF_STAGES:         return partyParam->spdefStages;
        case ITEM_PARAM_SPEED_STAGES:         return partyParam->speedStages;
        case ITEM_PARAM_ACC_STAGES:           return partyParam->accStages;
        case ITEM_PARAM_CRIT_STAGES:          return partyParam->critStages;
        case ITEM_PARAM_PP_UP:                return partyParam->ppUp;
        case ITEM_PARAM_PP_MAX:               return partyParam->ppMax;
        case ITEM_PARAM_PP_RESTORE:           return partyParam->ppRestore;
        case ITEM_PARAM_PP_RESTORE_ALL:       return partyParam->ppRestoreAll;
        case ITEM_PARAM_HP_RESTORE:           return partyParam->hpRestore;
        case ITEM_PARAM_GIVE_HP_EVS:          return partyParam->giveHPEVs;
        case ITEM_PARAM_GIVE_ATK_EVS:         return partyParam->giveAtkEVs;
        case ITEM_PARAM_GIVE_DEF_EVS:         return partyParam->giveDefEVs;
        case ITEM_PARAM_GIVE_SPEED_EVS:       return partyParam->giveSpeedEVs;
        case ITEM_PARAM_GIVE_SPATK_EVS:       return partyParam->giveSpAtkEVs;
        case ITEM_PARAM_GIVE_SPDEF_EVS:       return partyParam->giveSpDefEVs;
        case ITEM_PARAM_GIVE_FRIENDSHIP_LOW:  return partyParam->giveFriendshipLow;
        case ITEM_PARAM_GIVE_FRIENDSHIP_MED:  return partyParam->giveFriendshipMed;
        case ITEM_PARAM_GIVE_FRIENDSHIP_HIGH: return partyParam->giveFriendshipHigh;
        case ITEM_PARAM_HP_EVS:               return partyParam->hpEVs;
        case ITEM_PARAM_ATK_EVS:              return partyParam->atkEVs;
        case ITEM_PARAM_DEF_EVS:              return partyParam->defEVs;
        case ITEM_PARAM_SPEED_EVS:            return partyParam->speedEVs;
        case ITEM_PARAM_SPATK_EVS:            return partyParam->spatkEVs;
        case ITEM_PARAM_SPDEF_EVS:            return partyParam->spdefEVs;
        case ITEM_PARAM_HP_RESTORED:          return partyParam->hpRestored;
        case ITEM_PARAM_PP_RESTORED:          return partyParam->ppRestored;
        case ITEM_PARAM_FRIENDSHIP_LOW:       return partyParam->friendshipLow;
        case ITEM_PARAM_FRIENDSHIP_MED:       return partyParam->friendshipMed;
        case ITEM_PARAM_FRIENDSHIP_HIGH:      return partyParam->friendshipHigh;
    }
    return 0;
}

s32 Item_Get(ItemData *itemData, ItemDataParam param) {
    switch (param) {
        case ITEM_PARAM_PRICE:               return itemData->price;
        case ITEM_PARAM_HOLD_EFFECT:         return itemData->holdEffect;
        case ITEM_PARAM_EFFECT_PARAM:        return itemData->effectParam;
        case ITEM_PARAM_PREVENT_TOSS:        return itemData->preventToss;
        case ITEM_PARAM_CAN_REGISTER:        return itemData->canRegister;
        case ITEM_PARAM_FIELD_POCKET:        return itemData->fieldPocket;
        case ITEM_PARAM_FIELD_USE_FUNC:      return itemData->fieldUseFunc;
        case ITEM_PARAM_BATTLE_USE_CATEGORY: return itemData->battleUseCategory;
        case ITEM_PARAM_PLUCK_EFFECT:        return itemData->pluckEffect;
        case ITEM_PARAM_FLING_EFFECT:        return itemData->flingEffect;
        case ITEM_PARAM_FLING_POWER:         return itemData->flingPower;
        case ITEM_PARAM_NATURAL_GIFT_POWER:  return itemData->naturalGiftPower;
        case ITEM_PARAM_NATURAL_GIFT_TYPE:   return itemData->naturalGiftType;
        case ITEM_PARAM_BATTLE_POCKET:       return itemData->battlePocket;
        case ITEM_PARAM_PARTY_USE:           return itemData->partyUse;
        default:
            switch (itemData->partyUse) {
                case 0: return itemData->partyUseParamBytes[0];
                case 1: return ItemPartyParam_Get(&itemData->partyUseParam, param);
            }
    }
    return 0;
}

u8 Item_IsMail(u16 item) {
    for (int i = 0; i < NUM_MAIL_ITEMS; i++) {
        if (item == sMailItemIDs[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

u8 Item_IsBerry(u16 item) {
    for (int i = 0; i < NUM_BERRY_ITEMS; i++) {
        if (item == sBerryItemIDs[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

// Unlike the DS version, the table is filled from the item data file field by field.
ItemData *ItemTable_Load(u32 heapId) {
    ItemData *itemData;
    s32 i;
    s32 j;
    ItemData *itemTable = (ItemData *)
        NARC_AllocAndReadFromMemberByIndexPair(NARC_INDEX_ITEM_DATA, 0, heapId, 0, NUM_ITEMS * sizeof(ItemData));
    gItemTable = itemTable;

    for (i = 0; i < NUM_ITEMS; i++) {
        itemData = &itemTable[i];
        itemData->price = fn_8038FD44(&lbl_8063CE34.itemData, i);
        itemData->holdEffect = fn_8038FD78(&lbl_8063CE34.itemData, i);
        itemData->effectParam = fn_8038FDAC(&lbl_8063CE34.itemData, i);
        itemData->pluckEffect = fn_8038FDE0(&lbl_8063CE34.itemData, i);
        itemData->flingEffect = fn_8038FE14(&lbl_8063CE34.itemData, i);
        itemData->flingPower = fn_8038FE48(&lbl_8063CE34.itemData, i);
        itemData->naturalGiftPower = fn_8038FE7C(&lbl_8063CE34.itemData, i);
        itemData->naturalGiftType = fn_8038FEB0(&lbl_8063CE34.itemData, i);
        itemData->preventToss = fn_8038FEE8(&lbl_8063CE34.itemData, i);
        itemData->canRegister = fn_8038FF20(&lbl_8063CE34.itemData, i);
        itemData->fieldPocket = fn_8038FF58(&lbl_8063CE34.itemData, i);
        itemData->battlePocket = fn_8038FF90(&lbl_8063CE34.itemData, i);
        itemData->fieldUseFunc = fn_8038FFC8(&lbl_8063CE34.itemData, i);
        itemData->battleUseCategory = fn_8038FFFC(&lbl_8063CE34.itemData, i);
        itemData->partyUse = fn_80390030(&lbl_8063CE34.itemData, i);
        itemData->padding_0D = fn_80390064(&lbl_8063CE34.itemData, i);

        for (j = 0; j < ITEM_PARTY_PARAM_SIZE; j++) {
            itemData->partyUseParamBytes[j] = fn_80390098(&lbl_8063CE34.itemData, i, j);
        }
    }

    return itemTable;
}

ItemData *ItemTable_Index(ItemData *itemTable, u16 index) {
    return &itemTable[index];
}

Bag *Bag_New(u32 heapId) {
    Bag *bag = (Bag *)fn_8016DF70(heapId, sizeof(Bag));
    memset(bag, 0, sizeof(Bag));
    return bag;
}

u16 LCRNG_Next() {
    gLCRNGState = gLCRNGState * 1103515245 + 24691;
    lbl_806405E4++;
    return gLCRNGState >> 16;
}

BOOL fn_803D97E4(void *, u16) {
    return TRUE;
}

BOOL fn_803D97EC(int printerID) {
    return FALSE;
}

void fn_803D97F4() {}

void fn_803D97F8(int seqID) {}

s32 fn_803D97FC(u32, u32) {
    return FALSE;
}

void fn_803D9804(u32) {}

void fn_803D9808(void *) {}

void fn_803D980C(void *) {}

u8 fn_803D9810(int battlerType, u32 battleType) {
    return FALSE;
}

BOOL fn_803D9818(void *btlSubscreen) {
    return TRUE;
}

BOOL fn_803D9820(void *btlSubscreen) {
    return TRUE;
}

int fn_803D9828(void *btlSubscreen) {
    return FALSE;
}

void fn_803D9830(void *btlSubscreen, int param1) {}

void fn_803D9834(void *btlSubscreen, int menuConfigIndex, int forceRedraw, void *battleDisplayData) {}

void fn_803D9838(void *btlSubscreen) {}

int fn_803D983C(int netId) {
    return FALSE;
}

void fn_803D9844(u32) {}

u16 fn_803D9848() {
    return FALSE;
}

void fn_803D9850(void *) {}

// TODO probably Overlay_UnloadByID (pret)
void fn_803D9854(int) {}

void fn_803D9858() {}

BOOL fn_803D985C() {
    return FALSE;
}

BOOL fn_803D9864() {
    return TRUE;
}

void fn_803D986C() {}

BOOL fn_803D9870() {
    return FALSE;
}

u8 App_PixelCount(s16 cur, s16 max, s32 maxPixels) {
    u8 pixels = cur * maxPixels / max;
    if (pixels == 0 && cur > 0) {
        pixels = 1;
    }
    return pixels;
}

// TODO Assertion with a printf-style message, compiled out in this build.
void fn_803D989C(BOOL cond, const char *fmt, ...) {
    if (!cond) {
        va_list args;
        va_start(args, fmt);
    }
}

// Returns TRUE when the member could not be read.
BOOL NARC_ReadWholeMemberByIndexPair(void *dest, u32 narcId, u32 memberIndex) {
    u32 size;
    void *src = fn_8016F0F4(lbl_8063F1D8, narcId, memberIndex, &size);
    if (src == NULL) {
        return TRUE;
    }
    memcpy(dest, src, size);
    return FALSE;
}

void NARC_ReadFromMemberByIndexPair(void *dest, u32 narcId, u32 memberIndex, u32 offset, u32 bytesToRead) {
    u32 size;
    u8 *src = (u8 *)fn_8016F0F4(lbl_8063F1D8, narcId, memberIndex, &size);
    if (src != NULL) {
        memcpy(dest, src + offset, bytesToRead);
    }
}

void *NARC_AllocAndReadFromMemberByIndexPair(u32 narcId, u32 memberIndex, u32 heapId, u32 offset, u32 bytesToRead) {
    void *dest = fn_8016DF70(heapId, bytesToRead);
    u32 size;
    u8 *src = (u8 *)fn_8016F0F4(lbl_8063F1D8, narcId, memberIndex, &size);
    if (src != NULL) {
        memcpy(dest, src + offset, bytesToRead);
    }
    return dest;
}

// TODO Sends a string to the Wii message window when a command is pending.
u8 fn_803D9A44(Strbuf *str, void *param) {
    fn_8016E2DC();
    if (lbl_8048CE28.pendingCommand != 0) {
        lbl_8048CDE8.message.text = Strbuf_GetData(str);
        lbl_8048CDE8.message.size = (Strbuf_Length(str) + 1) * sizeof(u16);
        lbl_8048CDE8.message._08 = 0;
        lbl_8048CDE8.message.param = param;
        lbl_8048CDE8.message._10 = lbl_8048CE28._0C;
        lbl_8048CDE8.message._14 = lbl_8048CE28._18;
        fn_8016FA4C(lbl_8048CE28.pendingCommand, &lbl_8048CDE8);
        lbl_8048CE28.pendingCommand = 0;
        lbl_8048CE28._0C = 0xFF;
    }
    return 0;
}

// TODO Formats a battle message into the battle system's buffer and returns its text and size in bytes.
// The call to fn_803D9E48 below is not inlined in the original.
#pragma dont_inline on
const u16 *fn_803D9AEC(BattleMessage *battleMsg, u32 *size) {
    const u16 *text;
    MessageLoader *msgLoader;
    BattleSystem *battleSys;

    battleSys = (BattleSystem *)ApplicationManager_Data(fn_803D9E48());
    switch (battleMsg->commandCode) {
        case 0x14: msgLoader = BattleSystem_GetAttackMessageLoader(battleSys); break;
        case 0x15:
        case 0x25: msgLoader = BattleSystem_GetMessageLoader(battleSys); break;
        default:   msgLoader = BattleSystem_GetMessageLoader(battleSys); break;
    }
    fn_803AF38C(battleSys, battleMsg, msgLoader);

    text = Strbuf_GetData(battleSys->msgBuffer);
    *size = (Strbuf_Length(battleSys->msgBuffer) + 1) * sizeof(u16);
    return text;
}
#pragma dont_inline reset

// TODO Accessors of a pointer set by the Wii battle code.
void *fn_803D9BAC() {
    return sUnk806405F8;
}

void fn_803D9BB4(void *data) {
    sUnk806405F8 = data;
}

void fn_803D9BBC() {
    sUnk806405F0 = new Unk806405F0;
    memset(sUnk806405F0, 0, sizeof(Unk806405F0));
    sUnk806405F0->_00 = -1;
    sUnk806405F0->_04 = 0;
    sUnk806405F0->_08 = -1;
    sUnk806405F0->_0C = 0;
}

// TODO Allocates the parameters of the DS battle and lets the Wii side fill them.
Unk806405F4 *fn_803D9C18() {
    sUnk806405F4 = new Unk806405F4;
    memset(sUnk806405F4, 0, sizeof(Unk806405F4));
    sUnk806405F4->mon = Pokemon_New(0);
    fn_8016E70C(sUnk806405F4);

    Unk80035CB0 *config = fn_80035D9C();
    if (sUnk806405F4->battleType & BATTLE_TYPE_DOUBLES) {
        fn_80035E60(config, TRUE);
    } else {
        fn_80035E60(config, FALSE);
    }
    if (sUnk806405F4->battleType & BATTLE_TYPE_2vs2) {
        fn_80035E70(config, 3);
    } else {
        fn_80035E70(config, 2);
    }

    fn_8016ECC0(sUnk806405F4);
    fn_8016EEC8(sUnk806405F4);
    fn_8017CC8C(sUnk806405F4->battleType);
    return sUnk806405F4;
}

static BOOL fn_803D9CE4(ApplicationManager *appMan, s32 *state) {
    return TRUE;
}

static BOOL fn_803D9CEC(ApplicationManager *appMan, s32 *state) {
    return fn_803AB534() != 0;
}

static BOOL fn_803D9D14(ApplicationManager *appMan, s32 *state) {
    return TRUE;
}

// TODO Starts the DS battle application; returns the battle type.
u32 fn_803D9D1C() {
    fn_803D9BBC();
    fn_803DEEA4();
    fn_803D9C18();
    sUnk806405F4->dto->battleType = sUnk806405F4->battleType;
    sUnk806405F4->appMan = ApplicationManager_New(&sBattleAppTemplate, sUnk806405F4->dto, 0x1B);
    return sUnk806405F4->battleType;
}

void fn_803D9D7C() {
    if (sUnk806405F4->appMan != NULL) {
        ApplicationManager_Free(sUnk806405F4->appMan);
        sUnk806405F4->appMan = NULL;
    }
    if (sUnk806405F4->mon != NULL) {
        fn_8016E0A0(sUnk806405F4->mon);
        sUnk806405F4->mon = NULL;
    }
    if (sUnk806405F0 != NULL) {
        delete sUnk806405F0;
        sUnk806405F0 = NULL;
    }
    if (sUnk806405F4 != NULL) {
        delete sUnk806405F4;
        sUnk806405F4 = NULL;
    }
}

// TODO Runs one frame of the DS battle application; returns TRUE once it has exited.
BOOL fn_803D9E08() {
    if (ApplicationManager_Exec(sUnk806405F4->appMan)) {
        return TRUE;
    }
    fn_803DEF70();
    return FALSE;
}

ApplicationManager *fn_803D9E48() {
    return sUnk806405F4->appMan;
}

BOOL fn_803D9E54() {
    s32 procState = fn_803DEE9C(sUnk806405F4->appMan);
    s32 limit = fn_803AC830();
    return procState > limit;
}
