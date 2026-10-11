#include ".unsorted/8038F424.hpp"

extern u32 lbl_806405C8;

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

void BattleMessage_Print(BattleSystem *battleSys, MessageLoader *msgLoader, BattleMessage *battleMsg) {
    BattleMessage message;

    fn_803ADEF0(&message, battleMsg);
    BattleMessage_CheckSide(battleSys, battleMsg, 0);
    BattleMessage_FillFormatBuffers(battleSys, battleMsg, msgLoader, 0);
    BattleMessage_Format(battleSys, msgLoader, battleMsg);
    fn_803D9A44(battleSys->msgBuffer, &message);
}
}

#pragma pop

extern "C" {

// TODO Copies a battle message; Platinum has no such function.
void fn_803ADEF0(BattleMessage *dst, BattleMessage *src) {
    *dst = *src;
}

// swapSides compares the side of the opposite battler. With BATTLE_TYPE_UNK_19, some messages are replaced
// (see fn_803AF3F0) and get the side as a parameter instead of a different message per side.
void BattleMessage_CheckSide(BattleSystem *battleSys, BattleMessage *battleMsg, int swapSides) {
    u32 battleType = BattleSystem_GetBattleType(battleSys);

    if (battleMsg->tags & TAG_GLOBAL_MESSAGE) {
        return;
    }

    if (battleMsg->tags & TAG_SIDE_LOCAL_MESSAGE) {
        if ((battleType & BATTLE_TYPE_UNK_19) && battleMsg->id == 0x120) {
            battleMsg->id = 0x5140;
            battleMsg->params[1] = battleMsg->params[0];

            if (BattleSystem_GetBattlerSide(battleSys, battleMsg->battler ^ swapSides)) {
                battleMsg->params[0] = TRUE;
            } else {
                battleMsg->params[0] = FALSE;
            }
        } else if (BattleSystem_GetBattlerSide(battleSys, battleMsg->battler ^ swapSides)) {
            battleMsg->id++;
        }

        return;
    }

    switch (battleMsg->tags & BATTLE_MESSAGE_TAGS) {
        case TAG_NONE:
        case TAG_MOVE:
        case TAG_STAT:
        case TAG_ITEM:
        case TAG_NUMBER:
        case TAG_NUMBERS:
        case TAG_TRNAME:
        case TAG_MOVE_MOVE:
        case TAG_ITEM_MOVE:
        case TAG_NUMBER_NUMBER:
        case TAG_TRNAME_TRNAME:
        case TAG_TRNAME_NICKNAME:
        case TAG_TRNAME_ITEM:
        case TAG_TRNAME_NUM:
        case TAG_TRCLASS_TRNAME:
        case TAG_TRNAME_NICKNAME_NICKNAME:
        case TAG_TRCLASS_TRNAME_NICKNAME:
        case TAG_TRCLASS_TRNAME_ITEM:
        case TAG_TRNAME_NICKNAME_TRNAME_NICKNAME:
        case TAG_TRCLASS_TRNAME_NICKNAME_NICKNAME:
        case TAG_TRCLASS_TRNAME_NICKNAME_TRNAME:
        case TAG_TRCLASS_TRNAME_TRCLASS_TRNAME:
        case TAG_TRCLASS_TRNAME_NICKNAME_TRCLASS_TRNAME_NICKNAME: break;

        case TAG_NONE_SIDE_CONSCIOUS:
            if (battleType & BATTLE_TYPE_UNK_19) {
                battleMsg->id = fn_803AF3F0(battleMsg->id);

                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[0] & 0xFF) ^ swapSides)) {
                    battleMsg->params[1] = TRUE;
                } else {
                    battleMsg->params[1] = FALSE;
                }
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[0] & 0xFF) ^ swapSides)) {
                battleMsg->id++;
            }
            break;

        case TAG_NICKNAME:
        case TAG_NICKNAME_MOVE:
        case TAG_NICKNAME_ABILITY:
        case TAG_NICKNAME_STAT:
        case TAG_NICKNAME_TYPE:
        case TAG_NICKNAME_POKE:
        case TAG_NICKNAME_ITEM:
        case TAG_NICKNAME_POFFIN:
        case TAG_NICKNAME_NUM:
        case TAG_NICKNAME_TRNAME:
        case TAG_NICKNAME_BOX:
        case TAG_NICKNAME_MOVE_MOVE:
        case TAG_NICKNAME_MOVE_NUMBER:
        case TAG_NICKNAME_ABILITY_MOVE:
        case TAG_NICKNAME_ABILITY_ITEM:
        case TAG_NICKNAME_ABILITY_STAT:
        case TAG_NICKNAME_ABILITY_TYPE:
        case TAG_NICKNAME_ABILITY_STATUS:
        case TAG_NICKNAME_ABILITY_NUMBER:
        case TAG_NICKNAME_ITEM_MOVE:
        case TAG_NICKNAME_ITEM_STAT:
        case TAG_NICKNAME_ITEM_STATUS:
        case TAG_NICKNAME_BOX_BOX:
            if ((battleType & BATTLE_TYPE_UNK_19) == FALSE) {
                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[0] & 0xFF) ^ swapSides)) {
                    battleMsg->id++;

                    if (battleType & BATTLE_TYPE_TRAINER) {
                        battleMsg->id++;
                    }
                }
            } else if (battleMsg->commandCode == 0x14) {
                battleMsg->id++;
            } else if (battleMsg->id != 0x260 && battleMsg->id != 0x264 && lbl_806405C8 == 0) {
                battleMsg->id++;
            }
            break;

        case TAG_MOVE_SIDE:
            if (battleType & BATTLE_TYPE_UNK_19) {
                battleMsg->id = fn_803AF3F0(battleMsg->id);

                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[1] & 0xFF) ^ swapSides)) {
                    battleMsg->params[2] = TRUE;
                } else {
                    battleMsg->params[2] = FALSE;
                }
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[1] & 0xFF) ^ swapSides)) {
                battleMsg->id++;
            }
            break;

        case TAG_MOVE_NICKNAME:
        case TAG_ABILITY_NICKNAME:
        case TAG_ITEM_NICKNAME_FLAVOR:
            if ((battleType & BATTLE_TYPE_UNK_19) == FALSE) {
                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[1] & 0xFF) ^ swapSides)) {
                    battleMsg->id++;

                    if (battleType & BATTLE_TYPE_TRAINER) {
                        battleMsg->id++;
                    }
                }
            } else {
                battleMsg->id++;
            }
            break;

        case TAG_NICKNAME_NICKNAME:
        case TAG_NICKNAME_NICKNAME_MOVE:
        case TAG_NICKNAME_NICKNAME_ABILITY:
        case TAG_NICKNAME_NICKNAME_ITEM:
            if (battleType & BATTLE_TYPE_UNK_19) {
                battleMsg->id++;
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[0] & 0xFF) ^ swapSides)) {
                battleMsg->id += 3;

                if (battleType & BATTLE_TYPE_TRAINER) {
                    battleMsg->id += 2;
                }

                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[1] & 0xFF) ^ swapSides)) {
                    battleMsg->id++;
                }
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[1] & 0xFF) ^ swapSides)) {
                battleMsg->id++;

                if (battleType & BATTLE_TYPE_TRAINER) {
                    battleMsg->id++;
                }
            }
            break;

        case TAG_NICKNAME_ABILITY_NICKNAME:
        case TAG_NICKNAME_ITEM_NICKNAME:
        case TAG_NICKNAME_ABILITY_NICKNAME_MOVE:
        case TAG_NICKNAME_ABILITY_NICKNAME_ABILITY:
        case TAG_NICKNAME_ABILITY_NICKNAME_STAT:
        case TAG_NICKNAME_ITEM_NICKNAME_ITEM:
            if (battleType & BATTLE_TYPE_UNK_19) {
                battleMsg->id++;
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[0] & 0xFF) ^ swapSides)) {
                battleMsg->id += 3;

                if (battleType & BATTLE_TYPE_TRAINER) {
                    battleMsg->id += 2;
                }

                if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[2] & 0xFF) ^ swapSides)) {
                    battleMsg->id++;
                }
            } else if (BattleSystem_GetBattlerSide(battleSys, (battleMsg->params[2] & 0xFF) ^ swapSides)) {
                battleMsg->id++;

                if (battleType & BATTLE_TYPE_TRAINER) {
                    battleMsg->id++;
                }
            }
            break;

        default: fn_803D989C(FALSE, "\x91\xb6\x8d\xdd\x82\xb5\x82\xc8\x82\xa2TAG\x82\xc5\x82\xb7\x81I\n"); break;
    }
}

static inline void BattleMessage_SetNumberDigits(BattleSystem *battleSys, u32 idx, int num, int digits) {
    if (digits) {
        StringTemplate_SetNumber(battleSys->strFormatter, idx, num, digits, PADDING_MODE_NONE, 2);
    } else {
        StringTemplate_SetNumber(battleSys->strFormatter, idx, num, 5, PADDING_MODE_NONE, 2);
    }
}

// The numbers use charset mode 2. With BATTLE_TYPE_UNK_19, some messages get an extra argument from
// fn_803AF0D8.
void BattleMessage_FillFormatBuffers(BattleSystem *battleSys,
                                     BattleMessage *battleMsg,
                                     MessageLoader *msgLoader,
                                     int swapSides) {
    Pokemon *mon;

    if (battleMsg->id == 0x5140) {
        fn_803AF0D8(battleSys, 0, battleMsg->params[0], msgLoader, battleMsg->id);
        StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
        return;
    }

    switch (battleMsg->tags & BATTLE_MESSAGE_TAGS) {
        case TAG_NONE: break;

        case TAG_NONE_SIDE_CONSCIOUS:
            if (battleSys->battleType & BATTLE_TYPE_UNK_19) {
                fn_803AF0D8(battleSys, 0, battleMsg->params[1], msgLoader, battleMsg->id);
            }
            break;

        case TAG_NICKNAME: BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides); break;

        case TAG_MOVE:     StringTemplate_SetMoveName(battleSys->strFormatter, 0, battleMsg->params[0]); break;

        case TAG_MOVE_SIDE:
            if (battleSys->battleType & BATTLE_TYPE_UNK_19) {
                fn_803AF0D8(battleSys, 0, battleMsg->params[2], msgLoader, battleMsg->id);
                StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[0]);
            } else {
                StringTemplate_SetMoveName(battleSys->strFormatter, 0, battleMsg->params[0]);
            }
            break;

        case TAG_STAT: StringTemplate_SetPokemonStatName(battleSys->strFormatter, 0, battleMsg->params[0]); break;

        case TAG_ITEM: StringTemplate_SetItemName(battleSys->strFormatter, 0, battleMsg->params[0]); break;

        case TAG_NUMBER:
            StringTemplate_SetNumber(battleSys->strFormatter, 0, battleMsg->params[0], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_NUMBERS: BattleMessage_SetNumberDigits(battleSys, 0, battleMsg->params[0], battleMsg->digits); break;

        case TAG_TRNAME:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            break;

        case TAG_NICKNAME_NICKNAME:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            break;

        case TAG_NICKNAME_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NICKNAME_ABILITY:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NICKNAME_STAT:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetPokemonStatName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NICKNAME_TYPE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetPokemonTypeName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NICKNAME_POKE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            mon = BattleSystem_GetPartyPokemon(battleSys,
                                               (battleMsg->params[1] & 0xFF) ^ swapSides,
                                               (battleMsg->params[1] & 0xFF00) >> 8);
            StringTemplate_SetSpeciesName(battleSys->strFormatter, 1, &mon->box);
            break;

        case TAG_NICKNAME_ITEM:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NICKNAME_POFFIN: BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides); break;

        case TAG_NICKNAME_NUM:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetNumber(battleSys->strFormatter, 1, battleMsg->params[1], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_NICKNAME_TRNAME:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            break;

        case TAG_NICKNAME_BOX:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetPCBoxName(battleSys->strFormatter, 1, battleSys->pcBoxes, battleMsg->params[1]);
            break;

        case TAG_MOVE_NICKNAME:
            StringTemplate_SetMoveName(battleSys->strFormatter, 0, battleMsg->params[0]);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            break;

        case TAG_MOVE_MOVE:
            StringTemplate_SetMoveName(battleSys->strFormatter, 0, battleMsg->params[0]);
            StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_ABILITY_NICKNAME:
            StringTemplate_SetAbilityName(battleSys->strFormatter, 0, battleMsg->params[0]);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            break;

        case TAG_ITEM_MOVE:
            StringTemplate_SetItemName(battleSys->strFormatter, 0, battleMsg->params[0]);
            StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_NUMBER_NUMBER:
            StringTemplate_SetNumber(battleSys->strFormatter, 0, battleMsg->params[0], 5, PADDING_MODE_SPACES, 2);
            StringTemplate_SetNumber(battleSys->strFormatter, 1, battleMsg->params[1], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_TRNAME_TRNAME:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            break;

        case TAG_TRNAME_NICKNAME:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            break;

        case TAG_TRNAME_ITEM:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            break;

        case TAG_TRNAME_NUM:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetNumber(battleSys->strFormatter, 1, battleMsg->params[1], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_TRCLASS_TRNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            break;

        case TAG_NICKNAME_NICKNAME_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            StringTemplate_SetMoveName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_NICKNAME_ABILITY:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_NICKNAME_ITEM:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_MOVE_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetMoveName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_MOVE_NUMBER:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetMoveName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetNumber(battleSys->strFormatter, 2, battleMsg->params[2], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_NICKNAME_ABILITY_NICKNAME:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            break;

        case TAG_NICKNAME_ABILITY_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetMoveName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_ITEM:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetItemName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_STAT:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetPokemonStatName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_TYPE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetPokemonTypeName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_STATUS:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetStatusConditionName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_NUMBER:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetNumber(battleSys->strFormatter, 2, battleMsg->params[2], 5, PADDING_MODE_SPACES, 2);
            break;

        case TAG_NICKNAME_ITEM_NICKNAME:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            break;

        case TAG_NICKNAME_ITEM_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetMoveName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ITEM_STAT:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetPokemonStatName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ITEM_STATUS:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            StringTemplate_SetStatusConditionName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_BOX_BOX:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetPCBoxName(battleSys->strFormatter, 1, battleSys->pcBoxes, battleMsg->params[1]);
            StringTemplate_SetPCBoxName(battleSys->strFormatter, 2, battleSys->pcBoxes, battleMsg->params[2]);
            break;

        case TAG_ITEM_NICKNAME_FLAVOR:
            StringTemplate_SetItemName(battleSys->strFormatter, 0, battleMsg->params[0]);
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            StringTemplate_SetFlavorName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_TRNAME_NICKNAME_NICKNAME:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            break;

        case TAG_TRCLASS_TRNAME_NICKNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            break;

        case TAG_TRCLASS_TRNAME_ITEM:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            StringTemplate_SetItemName(battleSys->strFormatter, 2, battleMsg->params[2]);
            break;

        case TAG_NICKNAME_ABILITY_NICKNAME_MOVE:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetMoveName(battleSys->strFormatter, 3, battleMsg->params[3]);
            break;

        case TAG_NICKNAME_ABILITY_NICKNAME_ABILITY:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 3, battleMsg->params[3]);
            break;

        case TAG_NICKNAME_ABILITY_NICKNAME_STAT:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetAbilityName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetPokemonStatName(battleSys->strFormatter, 3, battleMsg->params[3]);
            break;

        case TAG_NICKNAME_ITEM_NICKNAME_ITEM:
            BattleMessage_SetNickname(battleSys, 0, battleMsg->params[0], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 1, battleMsg->params[1]);
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetItemName(battleSys->strFormatter, 3, battleMsg->params[3]);
            break;

        case TAG_TRNAME_NICKNAME_TRNAME_NICKNAME:
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                0,
                                                fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 1, battleMsg->params[1], swapSides);
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                2,
                                                fn_803ACB30(battleSys, battleMsg->params[2] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 3, battleMsg->params[3], swapSides);
            break;

        case TAG_TRCLASS_TRNAME_NICKNAME_NICKNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            BattleMessage_SetNickname(battleSys, 3, battleMsg->params[3], swapSides);
            break;

        case TAG_TRCLASS_TRNAME_NICKNAME_TRNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                3,
                                                fn_803ACB30(battleSys, battleMsg->params[3] ^ swapSides));
            break;

        case TAG_TRCLASS_TRNAME_TRCLASS_TRNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     2,
                                                     fn_803ACB30(battleSys, battleMsg->params[2] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                3,
                                                fn_803ACB30(battleSys, battleMsg->params[3] ^ swapSides));
            break;

        case TAG_TRCLASS_TRNAME_NICKNAME_TRCLASS_TRNAME_NICKNAME:
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     0,
                                                     fn_803ACB30(battleSys, battleMsg->params[0] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                1,
                                                fn_803ACB30(battleSys, battleMsg->params[1] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 2, battleMsg->params[2], swapSides);
            StringTemplate_SetTrainerClassNameBattle(battleSys->strFormatter,
                                                     3,
                                                     fn_803ACB30(battleSys, battleMsg->params[3] ^ swapSides));
            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter,
                                                4,
                                                fn_803ACB30(battleSys, battleMsg->params[4] ^ swapSides));
            BattleMessage_SetNickname(battleSys, 5, battleMsg->params[5], swapSides);
            break;

        default: fn_803D989C(FALSE, "\x91\xb6\x8d\xdd\x82\xb5\x82\xc8\x82\xa2TAG\x82\xc5\x82\xb7\x81I\n"); break;
    }
}

// Copies one of the messages 0x5141 + offset (0x552A + offset for some messages in mode 1) into a format
// argument.
// TODO fn_803D9BAC returns a mode that DSbridge stores as a pointer.
void fn_803AF0D8(BattleSystem *battleSys, u32 idx, int offset, MessageLoader *msgLoader, u32 msgID) {
    int base = 0x5141;

    if ((int)fn_803D9BAC() == 1 && (msgID == 0x5131 || msgID == 0x5132 || msgID == 0x5133 || msgID == 0x5134 ||
                                    msgID == 0x513A || msgID == 0x513C || msgID == 0x5140)) {
        base = 0x552A;
    }

    Strbuf *string = MessageLoader_GetNewString(msgLoader, base + offset);

    Strbuf_Copy(fn_803DFE0C(battleSys->strFormatter, idx), string);
    Strbuf_Free(string);
}

// With BATTLE_TYPE_UNK_19, the nickname is joined with the trainer name by message 0x5143, in an order that
// depends on the mode returned by fn_803D9BAC.
void BattleMessage_SetNickname(BattleSystem *battleSys, u32 idx, int nicknameTag, int swapSides) {
    Pokemon *mon;
    Strbuf *separator;
    Strbuf *arg;
    u8 battler;

    if ((battleSys->battleType & BATTLE_TYPE_UNK_19) && lbl_806405C8 == 0) {
        if (fn_803D9BAC() == NULL || (int)fn_803D9BAC() == 5) {
            battler = nicknameTag & 0xFF;

            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter, idx, fn_803ACB30(battleSys, battler));

            separator = MessageLoader_GetNewString(battleSys->msgLoader, 0x5143);
            arg = fn_803DFE0C(battleSys->strFormatter, idx);

            Strbuf_Concat(arg, separator);
            Strbuf_Free(separator);

            mon = BattleSystem_GetPartyPokemon(battleSys, battler, (nicknameTag & 0xFF00) >> 8);

            StringTemplate_SetNickname(battleSys->strFormatter, 6, &mon->box);
            Strbuf_Concat(arg, fn_803DFE0C(battleSys->strFormatter, 6));
        } else {
            battler = nicknameTag & 0xFF;
            mon = BattleSystem_GetPartyPokemon(battleSys, battler, (nicknameTag & 0xFF00) >> 8);

            StringTemplate_SetNickname(battleSys->strFormatter, idx, &mon->box);

            separator = MessageLoader_GetNewString(battleSys->msgLoader, 0x5143);
            arg = fn_803DFE0C(battleSys->strFormatter, idx);

            Strbuf_Concat(arg, separator);
            Strbuf_Free(separator);

            StringTemplate_SetTrainerNameBattle(battleSys->strFormatter, 6, fn_803ACB30(battleSys, battler));
            Strbuf_Concat(arg, fn_803DFE0C(battleSys->strFormatter, 6));
        }
    } else {
        mon = BattleSystem_GetPartyPokemon(battleSys, (nicknameTag & 0xFF) ^ swapSides, (nicknameTag & 0xFF00) >> 8);

        StringTemplate_SetNickname(battleSys->strFormatter, idx, &mon->box);
    }
}

void BattleMessage_Format(BattleSystem *battleSys, MessageLoader *msgLoader, BattleMessage *battleMsg) {
    Strbuf *string = MessageLoader_GetNewString(msgLoader, battleMsg->id);

    StringTemplate_Format(battleSys->strFormatter, battleSys->msgBuffer, string);
    Strbuf_Free(string);
}
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

// TODO Formats a message into the message buffer without printing it (called by DSbridge).
void fn_803AF38C(BattleSystem *battleSys, BattleMessage *battleMsg, MessageLoader *msgLoader) {
    BattleMessage_CheckSide(battleSys, battleMsg, 1);
    BattleMessage_FillFormatBuffers(battleSys, battleMsg, msgLoader, 1);
    BattleMessage_Format(battleSys, msgLoader, battleMsg);
}

// TODO Maps a message to the one used with BATTLE_TYPE_UNK_19, from a table of pairs.
u16 fn_803AF3F0(u32 v) {
    int i = 0;

    while (lbl_804732E8[i] != 0) {
        if (v == lbl_804732E8[i]) {
            return lbl_804732E8[i + 1];
        }
        i += 2;
    }
}
}

#pragma pop

extern "C" {

u32 fn_803AF43C(u8 *p) {
    return *(u32 *)(p + 0x23e0);
}
}
