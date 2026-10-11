#include "ds/string_template.hpp"

#include "ds/DSbridge.hpp"
#include "ds/charcode.hpp"
#include "ds/message.hpp"
#include "ds/pokemon.hpp"
#include "ds/strbuf.hpp"
#include "ds/trainer_data.hpp"

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
void *fn_8016E008(u32 heapId, u32 size);
}

StringTemplate *StringTemplate_Default(u32 heapId) {
    return StringTemplate_New(8, 32, heapId);
}

StringTemplate *StringTemplate_New(u32 maxArgs, u32 maxLen, u32 heapId) {
    u32 i;
    StringTemplate *strTemplate = (StringTemplate *)fn_8016E008(heapId, sizeof(StringTemplate));
    if (strTemplate != NULL) {
        strTemplate->maxArgs = maxArgs;
        strTemplate->heapID = heapId;
        strTemplate->templateBuffer = Strbuf_Init(maxLen, heapId);
        if (strTemplate->templateBuffer != NULL) {
            strTemplate->args = (StringTemplateArg *)fn_8016E008(heapId, maxArgs * sizeof(StringTemplateArg));
            if (strTemplate->args != NULL) {
                for (i = 0; i < maxArgs; i++) {
                    strTemplate->args[i].string = Strbuf_Init(maxLen, heapId);
                    if (strTemplate->args[i].string == NULL) {
                        break;
                    }
                }
                if (i == maxArgs) {
                    return strTemplate;
                }
            }
        }
    }
    return NULL;
}

void StringTemplate_Free(StringTemplate *strTemplate) {
    if (strTemplate->args != NULL) {
        for (u32 i = 0; i < strTemplate->maxArgs; i++) {
            if (strTemplate->args[i].string == NULL) {
                break;
            }
            Strbuf_Free(strTemplate->args[i].string);
        }
        fn_8016E0A0(strTemplate->args);
    }
    if (strTemplate->templateBuffer != NULL) {
        Strbuf_Free(strTemplate->templateBuffer);
    }
    strTemplate->maxArgs = 0;
    fn_8016E0A0(strTemplate);
}

void SetStringTemplateArg(StringTemplate *strTemplate,
                          u32 idx,
                          const Strbuf *argVal,
                          const StringTemplateArgHeader *header) {
    fn_803D989C(idx < strTemplate->maxArgs, "bufID=%d, wordmax=%d", idx, strTemplate->maxArgs);
    if (idx < strTemplate->maxArgs) {
        if (header != NULL) {
            strTemplate->args[idx].header = *header;
        }
        Strbuf_Copy(strTemplate->args[idx].string, argVal);
    }
}

void StringTemplate_SetSpeciesName(StringTemplate *strTemplate, u32 idx, BoxPokemon *boxMon) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE,
                                               NARC_INDEX_MSGDATA,
                                               MESSAGE_BANK_SPECIES_NAMES,
                                               strTemplate->heapID);
    MessageLoader_GetString(loader, BoxPokemon_GetValue(boxMon, MON_DATA_SPECIES, NULL), strTemplate->templateBuffer);
    SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
    MessageLoader_Free(loader);
}

void StringTemplate_SetNickname(StringTemplate *strTemplate, u32 idx, BoxPokemon *boxMon) {
    BoxPokemon_GetValue(boxMon, MON_DATA_NICKNAME_STRING, strTemplate->templateBuffer);
    SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
}

void StringTemplate_SetNumber(
    StringTemplate *strTemplate, u32 idx, s32 num, u32 maxDigits, s32 paddingMode, s32 charsetMode) {
    Strbuf_FormatInt(strTemplate->templateBuffer, num, maxDigits, paddingMode, charsetMode);
    SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
}

// Sets argument idx to the name of the given move (message bank 3).
void StringTemplate_SetMoveName(StringTemplate *strTemplate, u32 idx, u32 move) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 3, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, move, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given ability (message bank 4).
void StringTemplate_SetAbilityName(StringTemplate *strTemplate, u32 idx, u32 ability) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 4, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, ability, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given item (message bank 5).
void StringTemplate_SetItemName(StringTemplate *strTemplate, u32 idx, u32 item) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 5, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, item, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given type (message bank 10).
void StringTemplate_SetPokemonTypeName(StringTemplate *strTemplate, u32 idx, u32 type) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 10, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, type, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given stat (message bank 8).
void StringTemplate_SetPokemonStatName(StringTemplate *strTemplate, u32 idx, u32 stat) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 8, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, stat, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given status condition (message bank 7).
void StringTemplate_SetStatusConditionName(StringTemplate *strTemplate, u32 idx, u32 status) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 7, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, status, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Sets argument idx to the name of the given flavor (message bank 9).
void StringTemplate_SetFlavorName(StringTemplate *strTemplate, u32 idx, u32 flavor) {
    MessageLoader *loader = MessageLoader_Init(MESSAGE_LOADER_NARC_HANDLE, NARC_INDEX_MSGDATA, 9, strTemplate->heapID);
    if (loader != NULL) {
        MessageLoader_GetString(loader, flavor, strTemplate->templateBuffer);
        SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
        MessageLoader_Free(loader);
    }
}

// Empty in this game.
void StringTemplate_SetTrainerClassNameBattle(StringTemplate *strTemplate, u32 idx, Trainer *trainer) {}

void StringTemplate_SetTrainerNameBattle(StringTemplate *strTemplate, u32 idx, Trainer *trainer) {
    Strbuf_CopyChars(strTemplate->templateBuffer, trainer->name);
    SetStringTemplateArg(strTemplate, idx, strTemplate->templateBuffer, NULL);
}

// Empty in this game.
void StringTemplate_SetPCBoxName(StringTemplate *strTemplate, u32 idx, const PCBoxes *pcBoxes, u32 boxIdx) {}

void StringTemplate_Format(const StringTemplate *strTemplate, Strbuf *dst, const Strbuf *src) {
    const u16 *srcChars = Strbuf_GetData(src);
    Strbuf_Clear(dst);
    while (*srcChars != CHAR_EOS) {
        if (*srcChars == CHAR_FORMAT_ARG) {
            if (CharCode_IsFormatArg(srcChars)) {
                u32 idx = CharCode_FormatArgParam(srcChars, 0);
                Strbuf_Concat(dst, strTemplate->args[idx].string);
                srcChars = CharCode_SkipFormatArg(srcChars);
            } else {
                const u16 *formatArg = srcChars;
                srcChars = CharCode_SkipFormatArg(srcChars);
                while (formatArg < srcChars) {
                    Strbuf_AppendChar(dst, *formatArg++);
                }
            }
        } else {
            Strbuf_AppendChar(dst, *srcChars++);
        }
    }
}
// TODO Returns the string of argument idx.

Strbuf *fn_803DFE0C(const StringTemplate *strTemplate, u32 idx) {
    return strTemplate->args[idx].string;
}
// TODO Empty.

void fn_803DFE20() {}
// TODO Empty.

void fn_803DFE24() {}
