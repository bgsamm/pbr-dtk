#include ".unsorted/8038F424.hpp"

extern "C" {

void fn_803AC820(u32 v) {
    lbl_806405C0 = v;
}

BattleSystem *fn_803AC828(void) {
    return (BattleSystem *)lbl_806405C0;
}

s32 fn_803AC830(void) {
    return 8;
}

u32 fn_803AC838(u8 *p) {
    return *(u32 *)(p + 0x4);
}

u32 BattleSystem_GetBattleType(BattleSystem *battleSys) {
    return battleSys->battleType;
}

BattleContext *BattleSystem_GetBattleContext(BattleSystem *battleSys) {
    return battleSys->battleCtx;
}

BattlerData *BattleSystem_GetBattlerData(BattleSystem *battleSys, int battler) {
    return battleSys->battlers[battler];
}

int BattleSystem_GetMaxBattlers(BattleSystem *battleSys) {
    return battleSys->maxBattlers;
}

Party *BattleSystem_GetParty(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattleSystem_GetBattlerType(battleSys, battler) & BATTLER_TYPE_SOLO_ENEMY))) {
        return battleSys->parties[battler];
    } else if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return battleSys->parties[battler & 1];
    } else {
        return battleSys->parties[battler];
    }
}

int BattleSystem_GetPartyCount(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattleSystem_GetBattlerType(battleSys, battler) & BATTLER_TYPE_SOLO_ENEMY))) {
        return Party_GetCurrentCount(battleSys->parties[battler]);
    } else if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return Party_GetCurrentCount(battleSys->parties[battler & 1]);
    } else {
        return Party_GetCurrentCount(battleSys->parties[battler]);
    }
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

// Unlike the other party getters, the game reads the battler type directly here.
Pokemon *BattleSystem_GetPartyPokemon(BattleSystem *battleSys, int battler, int slot) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattlerData_GetBattlerType(battleSys->battlers[battler]) & BATTLER_TYPE_SOLO_ENEMY))) {
        return Party_GetPokemonBySlotIndex(battleSys->parties[battler], slot);
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return Party_GetPokemonBySlotIndex(battleSys->parties[battler & 1], slot);
    }

    return Party_GetPokemonBySlotIndex(battleSys->parties[battler], slot);
}
}

#pragma pop

extern "C" {

void *fn_803ACA58(BattleSystem *battleSys) {
    return battleSys->unk164;
}

MessageLoader *BattleSystem_GetMessageLoader(BattleSystem *battleSys) {
    return battleSys->msgLoader;
}

MessageLoader *BattleSystem_GetAttackMessageLoader(BattleSystem *battleSys) {
    return battleSys->attackMsgLoader;
}

u8 *BattleSystem_GetServerMessage(BattleSystem *battleSys) {
    return battleSys->serverMessage;
}

u16 *BattleSystem_GetServerReadIndex(BattleSystem *battleSys) {
    return &battleSys->serverReadIndex;
}

u16 *BattleSystem_GetServerWriteIndex(BattleSystem *battleSys) {
    return &battleSys->serverWriteIndex;
}

u16 *BattleSystem_GetServerEndIndex(BattleSystem *battleSys) {
    return &battleSys->serverEndIndex;
}

Strbuf *BattleSystem_GetMsgBuffer(BattleSystem *battleSys) {
    return battleSys->msgBuffer;
}

u16 Battler_GetTrainerID(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattleSystem_GetBattlerType(battleSys, battler) & BATTLER_TYPE_SOLO_ENEMY))) {
        return battleSys->trainerIDs[battler];
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return battleSys->trainerIDs[battler & 1];
    }

    return battleSys->trainerIDs[battler];
}

Trainer *fn_803ACB30(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattlerData_GetBattlerType(battleSys->battlers[battler]) & BATTLER_TYPE_SOLO_ENEMY))) {
        return &battleSys->trainers[battler];
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return &battleSys->trainers[battler & 1];
    }

    return &battleSys->trainers[battler];
}

TrainerInfo *BattleSystem_GetTrainerInfo(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattlerData_GetBattlerType(battleSys->battlers[battler]) & BATTLER_TYPE_SOLO_ENEMY))) {
        return battleSys->trainerInfo[battler];
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return battleSys->trainerInfo[battler & 1];
    }

    return battleSys->trainerInfo[battler];
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

int BattleSystem_GetBattlerOfType(BattleSystem *battleSys, int type) {
    int i;

    for (i = 0; i < battleSys->maxBattlers; i++) {
        if (type == BattlerData_GetBattlerType(battleSys->battlers[i])) {
            break;
        }
    }

    return i;
}
}

#pragma pop

extern "C" {

u8 BattleSystem_GetBattlerType(BattleSystem *battleSys, int battler) {
    return BattlerData_GetBattlerType(battleSys->battlers[battler]);
}

u8 BattleSystem_GetBattlerSide(BattleSystem *battleSys, int battler) {
    return BattlerData_GetBattlerType(battleSys->battlers[battler]) & 1;
}

int BattleSystem_GetTerrain(BattleSystem *battleSys) {
    if (battleSys->terrain > 12 || battleSys->terrain < 0) {
        return 12;
    }

    return battleSys->terrain;
}

int BattleSystem_GetMapHeader(BattleSystem *battleSys) {
    return battleSys->mapHeader;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

int BattleSystem_GetPartner(BattleSystem *battleSys, int battler) {
    int i;
    int maxBattlers = battleSys->maxBattlers;

    if ((battleSys->battleType & BATTLE_TYPE_DOUBLES) == FALSE) {
        return battler;
    }

    for (i = 0; i < maxBattlers; i++) {
        if (i != battler && (BattlerData_GetBattlerType(battleSys->battlers[i]) & 1) ==
                                (BattlerData_GetBattlerType(battleSys->battlers[battler]) & 1)) {
            break;
        }
    }

    return i;
}

// TODO Raw accesses: the pokeplatinum version does not match yet, the game inlines the getters and the
// side comparison is allocated differently.
int BattleSystem_GetEnemyInSlot(BattleSystem *battleSys, int battler, int slot) {
    u8 *p = (u8 *)battleSys;
    s32 i = (s32)battler;
    s32 m = (s32)slot;
    s32 n = *(s32 *)(p + 0x44);
    if (!(*(u32 *)(p + 0x2c) & 2)) {
        return i ^ 1;
    }
    u8 **pi = (u8 **)(p + i * 4);
    s32 j;
    for (j = 0; j < n; j++) {
        if (j != i) {
            u8 **pj = (u8 **)(p + j * 4);
            if (m == (BattlerData_GetBattlerType((BattlerData *)(pj[0x34 / 4])) & 2)) {
                u32 x = BattlerData_GetBattlerType((BattlerData *)(pi[0x34 / 4])) & 1;
                if ((u32)(BattlerData_GetBattlerType((BattlerData *)(pj[0x34 / 4])) & 1) != x) {
                    break;
                }
            }
        }
    }
    return j;
}
}

#pragma pop

extern "C" {

u32 BattleSystem_GetBattleStatusMask(BattleSystem *battleSys) {
    return battleSys->battleStatusMask;
}

u8 BattleSystem_IsInitialized(BattleSystem *battleSys) {
    return battleSys->battleInitialized;
}

int BattleSystem_GetNumSafariBalls(BattleSystem *battleSys) {
    return battleSys->safariBalls;
}

s32 fn_803ADBB4(u8 *a) {
    return 1;
}

s32 fn_803ADBBC(void) {
    return 0;
}

s32 fn_803ADBC4(void) {
    return 1;
}

void *BattleSystem_GetChatotCry(BattleSystem *battleSys, int battler) {
    if ((battleSys->battleType & BATTLE_TYPE_2vs2) ||
        ((battleSys->battleType & BATTLE_TYPE_TAG) &&
         (BattlerData_GetBattlerType(battleSys->battlers[battler]) & BATTLER_TYPE_SOLO_ENEMY))) {
        return battleSys->chatotCries[battler];
    }

    if (battleSys->battleType & BATTLE_TYPE_DOUBLES) {
        return battleSys->chatotCries[battler & 1];
    }

    return battleSys->chatotCries[battler];
}

void BattleSystem_GetBattleParticipantMask(BattleSystem *battleSys, int battler, int partySlot) {
    battleSys->battleParticipantMask[battler] |= FlagIndex(partySlot);
}

int BattleSystem_GetFieldWeather(BattleSystem *battleSys) {
    return battleSys->fieldWeather;
}

void BattleSystem_SetCommandSelectionFlags(BattleSystem *battleSys, u32 flags) {
    battleSys->commandSelectionFlags = flags;
}

void BattleSystem_SetUnread_2440(BattleSystem *battleSys, u8 value) {
    battleSys->unk2408 = value;
}

u8 *fn_803ADCC8(u8 *p, s32 i) {
    return fn_803AB524(*(u8 **)(p + i * 4 + 0x34));
}

u8 fn_803ADCD8(BattleSystem *battleSys) {
    return battleSys->resultMask;
}

void BattleSystem_SetResultMask(BattleSystem *battleSys, u8 resultMask) {
    battleSys->resultMask = resultMask;
}

void BattleSystem_SetRedHPSoundFlag(BattleSystem *battleSys, u8 flag) {
    battleSys->redHPSoundFlag = flag;
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void BattleSystem_SetBattlersByType(BattleSystem *battleSys, u8 *battlersByType) {
    for (int i = 0; i < battleSys->maxBattlers; i++) {
        battlersByType[BattlerData_GetBattlerType(battleSys->battlers[i])] = i;
    }
}

void BattleSystem_SetBattlerTypes(BattleSystem *battleSys, u8 *battlerTypes) {
    int i;

    for (i = 0; i < MAX_BATTLERS; i++) {
        battlerTypes[i] = 0xFF;
    }

    for (i = 0; i < battleSys->maxBattlers; i++) {
        battlerTypes[i] = BattlerData_GetBattlerType(battleSys->battlers[i]);
    }
}

u32 BattleSystem_CalcMoneyPenalty(Party *party, TrainerInfo *trainerInfo) {
    static const u8 badgeMul[] = {2, 4, 6, 9, 12, 16, 20, 25, 30};

    u8 badges = TrainerInfo_BadgeCount(trainerInfo);
    u32 penalty = Party_GetMaxLevel(party) * 4 * badgeMul[badges];
    u32 curMoney = TrainerInfo_Money(trainerInfo);

    if (penalty > curMoney) {
        penalty = curMoney;
    }

    return penalty;
}
}

#pragma pop

extern "C" {

void fn_803ADE5C(u8 *a, u32 b) {}

void fn_803ADE60(u8 *p, u32 a) {
    fn_803D97E4(*(u8 **)(p + 0x60), (u16)a);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803ADE6C(u8 *a, u8 *b, Rec24 *c) {
    Rec24 tmp;
    fn_803ADEF0(&tmp, c);
    fn_803ADF40(a, (u8 *)c, 0);
    fn_803AE378(a, (u8 *)c, b, 0);
    fn_803AF334(a, (u32)b, (u8 *)c);
    fn_803D9A44(*(Strbuf **)(a + 0x18), &tmp);
}
}

#pragma pop

extern "C" {

void fn_803ADEF0(Rec24 *d, Rec24 *s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
    d->f = s->f;
}

void fn_803AF334(u8 *p, u32 a, u8 *c) {
    void *s = MessageLoader_GetNewString((const MessageLoader *)a, *(u16 *)(c + 2));
    StringTemplate_Format((const StringTemplate *)(*(u32 *)(p + 0x14)),
                          (Strbuf *)(*(u32 *)(p + 0x18)),
                          (const Strbuf *)s);
    Strbuf_Free((Strbuf *)s);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

void fn_803AF38C(u8 *a, u8 *b, u8 *c) {
    fn_803ADF40(a, b, 1);
    fn_803AE378(a, b, c, 1);
    fn_803AF334(a, (u32)c, b);
}

u16 fn_803AF3F0(u32 v) {
    for (s32 i = 0; lbl_804732E8[i] != 0; i += 2) {
        if (v == lbl_804732E8[i]) {
            return lbl_804732E8[i + 1];
        }
    }
}
}

#pragma pop

extern "C" {

u32 fn_803AF43C(u8 *p) {
    return *(u32 *)(p + 0x23e0);
}
}
