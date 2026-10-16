#include "ds/move_table.hpp"

#include "ds/DSbridge.hpp"

// TODO Replace with proper imports
extern "C" {
extern Unk8063CE34 lbl_8063CE34;
u16 fn_80392B38(u8 **file, s32 move);
u8 fn_80392B6C(u8 **file, s32 move);
u8 fn_80392BA0(u8 **file, s32 move);
u8 fn_80392BD4(u8 **file, s32 move);
u8 fn_80392C08(u8 **file, s32 move);
u8 fn_80392C3C(u8 **file, s32 move);
u8 fn_80392C70(u8 **file, s32 move);
u16 fn_80392CA4(u8 **file, s32 move);
u8 fn_80392CD8(u8 **file, s32 move);
u8 fn_80392D0C(u8 **file, s32 move);
}

// The file is read, then every entry is filled again from the move data file.
void MoveTable_Load(MoveTable *moveTable) {
    NARC_ReadFromMemberByIndexPair(moveTable, NARC_INDEX_MOVE_TABLE, 0, 0, MAX_MOVES * sizeof(MoveTable));
    for (s32 i = 0; i < MAX_MOVES; i++) {
        MoveTable_LoadEntry(i, &moveTable[i]);
    }
}

u32 MoveTable_LoadParam(u32 move, u32 param) {
    MoveTable entry;
    MoveTable_LoadEntry(move, &entry);
    return MoveTable_Get(&entry, param);
}

u8 MoveTable_CalcMaxPP(u32 move, u8 ppUps) {
    MoveTable entry;
    u8 pp;
    if (ppUps > 3) {
        ppUps = 3;
    }
    MoveTable_LoadEntry(move, &entry);
    pp = MoveTable_Get(&entry, MOVEATTRIBUTE_PP);
    return pp + (ppUps * pp * 20) / 100;
}

u32 MoveTable_Get(MoveTable *entry, u32 param) {
    u32 result;
    switch (param) {
        case MOVEATTRIBUTE_EFFECT:         result = entry->effect; break;
        case MOVEATTRIBUTE_CLASS:          result = entry->moveClass; break;
        case MOVEATTRIBUTE_POWER:          result = entry->power; break;
        case MOVEATTRIBUTE_TYPE:           result = entry->type; break;
        case MOVEATTRIBUTE_ACCURACY:       result = entry->accuracy; break;
        case MOVEATTRIBUTE_PP:             result = entry->pp; break;
        case MOVEATTRIBUTE_EFFECT_CHANCE:  result = entry->effectChance; break;
        case MOVEATTRIBUTE_RANGE:          result = entry->range; break;
        case MOVEATTRIBUTE_PRIORITY:       result = entry->priority; break;
        case MOVEATTRIBUTE_FLAGS:          result = entry->flags; break;
        case MOVEATTRIBUTE_CONTEST_EFFECT: result = entry->contestEffect; break;
        case MOVEATTRIBUTE_CONTEST_TYPE:   result = entry->contestType; break;
    }
    return result;
}

void MoveTable_LoadEntry(u32 move, MoveTable *entry) {
    entry->effect = fn_80392B38(&lbl_8063CE34.moveData, move);
    entry->moveClass = fn_80392B6C(&lbl_8063CE34.moveData, move);
    entry->power = fn_80392BA0(&lbl_8063CE34.moveData, move);
    entry->type = fn_80392BD4(&lbl_8063CE34.moveData, move);
    entry->accuracy = fn_80392C08(&lbl_8063CE34.moveData, move);
    entry->pp = fn_80392C3C(&lbl_8063CE34.moveData, move);
    entry->effectChance = fn_80392C70(&lbl_8063CE34.moveData, move);
    entry->range = fn_80392CA4(&lbl_8063CE34.moveData, move);
    entry->priority = fn_80392CD8(&lbl_8063CE34.moveData, move);
    entry->flags = fn_80392D0C(&lbl_8063CE34.moveData, move);
}
