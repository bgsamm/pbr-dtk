#include "ds/message.hpp"

#include "ds/charcode.hpp"
#include "ds/strbuf.hpp"

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
const u16 *fn_802502F4(u32 textID);
s32 fn_80176EB4(u16 *dst, const u16 *src, u32 maxLength);
void *fn_8016E008(u32 heapId, u32 size);
}
// TODO Index of an entry of a message bank in the game's text table; 0 for an unknown bank.

u32 fn_803DFE28(u32 bankID, u32 entryID) {
    switch (bankID) {
        case 2:  return entryID + 0xA;
        case 3:  return entryID + 0x1FA;
        case 4:  return entryID + 0xBAE;
        case 5:  return entryID + 0x7C7;
        case 0:  return entryID <= 0x4EB ? entryID + 0x24DA : entryID;
        case 1:  return entryID + 0x1F5E;
        case 7:  return entryID + 0x418;
        case 8:  return entryID + 0x3008;
        case 9:  return entryID + 0x5051;
        case 10: return entryID + 0xCA6;
    }
    return 0;
}
// TODO Gets the text and length of a bank entry; FALSE when it does not exist.

BOOL fn_803DFEAC(u32 bankID, u32 entryID, const u16 **text, s32 *length) {
    u32 textID = fn_803DFE28(bankID, entryID);
    if (textID == 0) {
        return FALSE;
    }
    *text = fn_802502F4(textID);
    if (*text == NULL) {
        return FALSE;
    }
    *length = fn_803E022C(*text, 0xFF) + 1;
    return TRUE;
}
// TODO Copies a bank entry into str.

void fn_803DFF20(u32 bankID, u32 entryID, Strbuf *str) {
    const u16 *text;
    s32 length;
    if (fn_803DFEAC(bankID, entryID, &text, &length)) {
        u16 *chars;
        length *= 2;
        chars = (u16 *)fn_8016E008(0, length * sizeof(u16));
        length = fn_80176EB4(chars, text, length);
        Strbuf_CopyNumChars(str, chars, length);
        fn_8016E0A0(chars);
    }
}
// TODO Returns a new Strbuf holding a bank entry.

Strbuf *fn_803DFFA8(u32 bankID, u32 entryID, u32 heapId) {
    const u16 *text;
    s32 length;
    Strbuf *str = NULL;
    if (fn_803DFEAC(bankID, entryID, &text, &length)) {
        u16 *chars;
        length *= 2;
        chars = (u16 *)fn_8016E008(heapId, length * sizeof(u16));
        length = fn_80176EB4(chars, text, length);
        str = Strbuf_Init(length, heapId);
        if (str != NULL) {
            Strbuf_CopyNumChars(str, chars, length);
        }
        fn_8016E0A0(chars);
    }
    return str;
}

MessageLoader *MessageLoader_Init(u32 mode, u32 narcID, u32 bankID, u32 heapId) {
    MessageLoader *loader = (MessageLoader *)fn_8016E008(heapId, sizeof(MessageLoader));
    if (loader != NULL) {
        if (mode == MESSAGE_LOADER_BANK_HANDLE) {
            loader->bank = bankID;
            if (bankID == 0) {
                fn_8016E0A0(loader);
                return NULL;
            }
        } else {
            loader->bank = 0;
        }
        loader->mode = mode;
        loader->narcID = narcID;
        loader->bankID = bankID;
        loader->heapID = heapId;
    }
    return loader;
}

void MessageLoader_Free(MessageLoader *loader) {
    if (loader != NULL) {
        fn_8016E0A0(loader);
    }
}

void MessageLoader_Get(const MessageLoader *loader, u32 entryID, u16 *dst) {
    switch (loader->mode) {
        case MESSAGE_LOADER_BANK_HANDLE: fn_80176EB4(dst, fn_802502F4(fn_803DFE28(loader->bank, entryID)), 0xFF); break;
        case MESSAGE_LOADER_NARC_HANDLE:
            fn_80176EB4(dst, fn_802502F4(fn_803DFE28(loader->bankID, entryID)), 0xFF);
            break;
    }
}

void MessageLoader_GetString(const MessageLoader *loader, u32 entryID, Strbuf *str) {
    switch (loader->mode) {
        case MESSAGE_LOADER_BANK_HANDLE: fn_803DFF20(loader->bank, entryID, str); break;
        case MESSAGE_LOADER_NARC_HANDLE: fn_803DFF20(loader->bankID, entryID, str); break;
    }
}

Strbuf *MessageLoader_GetNewString(const MessageLoader *loader, u32 entryID) {
    switch (loader->mode) {
        case MESSAGE_LOADER_BANK_HANDLE: return fn_803DFFA8(loader->bank, entryID, loader->heapID);
        case MESSAGE_LOADER_NARC_HANDLE: return fn_803DFFA8(loader->bankID, entryID, loader->heapID);
    }
    return NULL;
}

void MessageLoader_GetSpeciesName(u32 species, u32 heapId, u16 *dst) {
    MessageLoader *loader =
        MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, MESSAGE_BANK_SPECIES_NAMES, heapId);
    MessageLoader_Get(loader, species, dst);
    MessageLoader_Free(loader);
}
// TODO Length of a text, stopping at a 0 or at two terminators in a row.

s32 fn_803E022C(const u16 *text, u32 maxLength) {
    u16 previous;
    s32 i;
    if (text == NULL) {
        return 0;
    }
    previous = *text;
    for (i = 0; i < maxLength; i++, text++) {
        if (i != 0) {
            if ((previous != CHAR_EOS && *text == 0) || (previous == CHAR_EOS && *text == CHAR_EOS)) {
                return i;
            }
        } else if (*text == 0) {
            return 0;
        }
        previous = *text;
    }
    return maxLength;
}
