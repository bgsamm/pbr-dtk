#pragma once

#include "decomp.h"

#include <revolution/types.h>

struct Strbuf;

#define NARC_INDEX_MSGDATA 0x1B
#define MESSAGE_BANK_SPECIES_NAMES 2

enum MessageLoaderMode {
    MESSAGE_LOADER_BANK_HANDLE,
    MESSAGE_LOADER_NARC_HANDLE,
};

// size: 0xC
struct MessageLoader {
    /* 0x0 */ u16 mode;
    /* 0x2 */ u16 heapID;
    /* 0x4 */ u16 narcID;
    /* 0x6 */ u16 bankID;
    /* 0x8 */ u32 bank;
};

u32 fn_803DFE28(u32 bankID, u32 entryID);
BOOL fn_803DFEAC(u32 bankID, u32 entryID, const u16 **text, s32 *length);
void fn_803DFF20(u32 bankID, u32 entryID, Strbuf *str);
Strbuf *fn_803DFFA8(u32 bankID, u32 entryID, u32 heapId);
MessageLoader *MessageLoader_Init(u32 mode, u32 narcID, u32 bankID, u32 heapId);
void MessageLoader_Free(MessageLoader *loader) NO_INLINE;
void MessageLoader_Get(const MessageLoader *loader, u32 entryID, u16 *dst);
void MessageLoader_GetString(const MessageLoader *loader, u32 entryID, Strbuf *str);
Strbuf *MessageLoader_GetNewString(const MessageLoader *loader, u32 entryID);
void MessageLoader_GetSpeciesName(u32 species, u32 heapId, u16 *dst);
s32 fn_803E022C(const u16 *text, u32 maxLength);
