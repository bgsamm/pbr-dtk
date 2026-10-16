#pragma once

#include "ds/charcode.hpp"

#define STRBUF_MAGIC_NUMBER 0xB6F8D2EC
#define STRBUF_FREED_MAGIC_NUMBER 0xB6F8D2ED

// size: 0x8 header, then maxSize characters
struct Strbuf {
    /* 0x0 */ u16 maxSize;
    /* 0x2 */ u16 size;
    /* 0x4 */ u32 integrity;
    /* 0x8 */ u16 data[1];
};

enum PaddingMode {
    PADDING_MODE_NONE,
    PADDING_MODE_SPACES,
    PADDING_MODE_ZEROES,
};

// Value the game passes to get full-width digits
#define CHARSET_MODE_JP 3

Strbuf *Strbuf_Init(u32 size, u32 heapId);
void Strbuf_Free(Strbuf *str);
void Strbuf_Clear(Strbuf *str);
void Strbuf_Copy(Strbuf *dst, const Strbuf *src);
void Strbuf_FormatInt(Strbuf *dst, s32 num, u32 maxDigits, s32 paddingMode, s32 charsetMode);
u32 Strbuf_Length(const Strbuf *str);
void Strbuf_CopyChars(Strbuf *dst, const u16 *src);
void Strbuf_CopyNumChars(Strbuf *dst, const u16 *src, u32 num);
void Strbuf_ToChars(const Strbuf *src, u16 *dst, u32 dstSize);
const u16 *Strbuf_GetData(const Strbuf *str);
void Strbuf_Concat(Strbuf *dst, const Strbuf *src);
void Strbuf_AppendChar(Strbuf *dst, u16 c);
