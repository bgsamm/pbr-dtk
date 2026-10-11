#pragma once

#include <revolution/types.h>

struct BoxPokemon;
struct PCBoxes;
struct Strbuf;
struct Trainer;

// size: 0x4
struct StringTemplateArgHeader {
    /* 0x0 */ u8 data[4];
};

// size: 0x8
struct StringTemplateArg {
    /* 0x0 */ StringTemplateArgHeader header;
    /* 0x4 */ Strbuf *string;
};

// size: 0x10
struct StringTemplate {
    /* 0x0 */ u32 maxArgs;
    /* 0x4 */ u32 heapID;
    /* 0x8 */ StringTemplateArg *args;
    /* 0xC */ Strbuf *templateBuffer;
};

StringTemplate *StringTemplate_Default(u32 heapId);
StringTemplate *StringTemplate_New(u32 maxArgs, u32 maxLen, u32 heapId);
void StringTemplate_Free(StringTemplate *strTemplate);
void SetStringTemplateArg(StringTemplate *strTemplate,
                          u32 idx,
                          const Strbuf *argVal,
                          const StringTemplateArgHeader *header);
void StringTemplate_SetSpeciesName(StringTemplate *strTemplate, u32 idx, BoxPokemon *boxMon);
void StringTemplate_SetNickname(StringTemplate *strTemplate, u32 idx, BoxPokemon *boxMon);
void StringTemplate_SetNumber(
    StringTemplate *strTemplate, u32 idx, s32 num, u32 maxDigits, s32 paddingMode, s32 charsetMode);
void StringTemplate_SetMoveName(StringTemplate *strTemplate, u32 idx, u32 move);
void StringTemplate_SetAbilityName(StringTemplate *strTemplate, u32 idx, u32 ability);
void StringTemplate_SetItemName(StringTemplate *strTemplate, u32 idx, u32 item);
void StringTemplate_SetPokemonTypeName(StringTemplate *strTemplate, u32 idx, u32 type);
void StringTemplate_SetPokemonStatName(StringTemplate *strTemplate, u32 idx, u32 stat);
void StringTemplate_SetStatusConditionName(StringTemplate *strTemplate, u32 idx, u32 status);
void StringTemplate_SetFlavorName(StringTemplate *strTemplate, u32 idx, u32 flavor);
void StringTemplate_SetTrainerClassNameBattle(StringTemplate *strTemplate, u32 idx, Trainer *trainer);
void StringTemplate_SetTrainerNameBattle(StringTemplate *strTemplate, u32 idx, Trainer *trainer);
void StringTemplate_SetPCBoxName(StringTemplate *strTemplate, u32 idx, const PCBoxes *pcBoxes, u32 boxIdx);
void StringTemplate_Format(const StringTemplate *strTemplate, Strbuf *dst, const Strbuf *src);
Strbuf *fn_803DFE0C(const StringTemplate *strTemplate, u32 idx);
void fn_803DFE20();
void fn_803DFE24();
