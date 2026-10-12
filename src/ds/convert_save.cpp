#include "ds/convert_save.hpp"

#include "ds/DSbridge.hpp"
#include "ds/trainer_info.hpp"

// TODO Replace with proper imports
extern "C" {
void fn_80177080(u16 *dst, const void *src, u32 length);
void fn_8017714C(u16 *dst, u16 *src, u32 size);
}

static u16 Swap16(u16 value);
static u32 Swap32(u32 value);

// Same as Swap16, but inlined where it is called.
static inline u16 Swap16Inline(u16 value) {
    return ((value & 0xFF) << 8) + ((value >> 8) & 0xFF);
}

void BagItem_FromDS(const BagItem *src, BagItem *dst) {
    dst->item = Swap16(src->item);
    dst->quantity = Swap16(src->quantity);
}

void Bag_FromDS(const Bag *src, Bag *dst) {
    s32 i;
    u32 registeredItem;
    for (i = 0; i < 165; i++) {
        BagItem_FromDS(&src->items[i], &dst->items[i]);
    }
    for (i = 0; i < 50; i++) {
        BagItem_FromDS(&src->keyItems[i], &dst->keyItems[i]);
    }
    for (i = 0; i < 100; i++) {
        BagItem_FromDS(&src->tmHms[i], &dst->tmHms[i]);
    }
    for (i = 0; i < 12; i++) {
        BagItem_FromDS(&src->mail[i], &dst->mail[i]);
    }
    for (i = 0; i < 40; i++) {
        BagItem_FromDS(&src->medicine[i], &dst->medicine[i]);
    }
    for (i = 0; i < 64; i++) {
        BagItem_FromDS(&src->berries[i], &dst->berries[i]);
    }
    for (i = 0; i < 15; i++) {
        BagItem_FromDS(&src->pokeballs[i], &dst->pokeballs[i]);
    }
    for (i = 0; i < 30; i++) {
        BagItem_FromDS(&src->battleItems[i], &dst->battleItems[i]);
    }
    registeredItem = src->registeredItem;
    dst->registeredItem = (registeredItem << 24) | ((registeredItem << 8) & 0xFF0000) |
                          ((registeredItem >> 8) & 0xFF00) | (registeredItem >> 24);
}

static u16 Swap16(u16 value) {
    return ((value & 0xFF) << 8) + ((value >> 8) & 0xFF);
}

void PCStorage_FromDS(DSPCStorage *src, PCStorage *dst) {
    s32 box;
    s32 i;
    u16 nickname[32];
    u16 unused[32];
    for (box = 0; box < MAX_PC_BOXES; box++) {
        for (i = 0; i < MAX_MONS_PER_BOX; i++) {
            DSBoxPokemon *srcMon = &src->boxes[box][i];
            BoxPokemon *dstMon = &dst->boxes[box][i];
            BOOL checksumValid;
            DSBoxPokemon_EnterDecryptionContext(srcMon);
            checksumValid = DSBoxPokemon_IsChecksumValid(srcMon);
            BoxPokemon_FromDS(srcMon, dstMon);
            if (!checksumValid) {
                dstMon->checksumFailed = TRUE;
                fn_80177080(nickname,
                            BoxPokemon_GetDataBlock(dstMon, dstMon->personality, DATA_BLOCK_C),
                            MON_NAME_LEN + 1);
                fn_8017714C(unused, nickname, 0x40);
            }
        }
        for (i = 0; i < PC_BOX_NAME_LEN; i++) {
            dst->names[box][i] = Swap16Inline(src->names[box][i]);
        }
    }
}

void TrainerInfo_FromDS(TrainerInfo *src, TrainerInfo *dst) {
    for (s32 i = 0; i < 8; i++) {
        dst->name[i] = ((src->name[i] & 0xFF) << 8) + ((src->name[i] >> 8) & 0xFF);
    }
    dst->id = Swap32(src->id);
    dst->money = Swap32(src->money);
    dst->gender = src->gender;
    dst->language = src->language;
    dst->badgeMask = src->badgeMask;
    dst->appearance = src->appearance;
    dst->gameCode = src->gameCode;
}

static u32 Swap32(u32 value) {
    return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000) >> 8) | ((value >> 24) & 0xFF);
}
