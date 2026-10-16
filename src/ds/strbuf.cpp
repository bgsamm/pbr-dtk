#include "ds/strbuf.hpp"

#include "ds/DSbridge.hpp"

#include <cstring>

// TODO Replace with proper imports
extern "C" {
void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *ptr);
}

Strbuf *Strbuf_Init(u32 size, u32 heapId) {
    Strbuf *str = (Strbuf *)fn_8016DF70(heapId, size * sizeof(u16) + 10);
    if (str != NULL) {
        str->integrity = STRBUF_MAGIC_NUMBER;
        str->maxSize = size;
        str->size = 0;
        str->data[0] = CHAR_EOS;
    }
    return str;
}

void Strbuf_Free(Strbuf *str) {
    str->integrity = STRBUF_FREED_MAGIC_NUMBER;
    fn_8016E0A0(str);
}

void Strbuf_Clear(Strbuf *str) {
    str->size = 0;
    str->data[0] = CHAR_EOS;
}

void Strbuf_Copy(Strbuf *dst, const Strbuf *src) {
    if (dst->maxSize > src->size) {
        memcpy(dst->data, src->data, (src->size + 1) * sizeof(u16));
        dst->size = src->size;
    } else {
        fn_803D989C(0, "STRBUF overflow : dstsize=%d,  srclen=%d", dst->maxSize, src->size);
    }
}

void Strbuf_FormatInt(Strbuf *dst, s32 num, u32 maxDigits, s32 paddingMode, s32 charsetMode) {
    /* lbl_80405CF8 */ static const u32 sPowersOfTen[] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
    };
    static const u16 sDigitsJP[] = {
        0xA2,
        0xA3,
        0xA4,
        0xA5,
        0xA6,
        0xA7,
        0xA8,
        0xA9,
        0xAA,
        0xAB,
    };
    static const u16 sDigitsEN[] = {
        0x121,
        0x122,
        0x123,
        0x124,
        0x125,
        0x126,
        0x127,
        0x128,
        0x129,
        0x12A,
    };
    BOOL isNegative = (num < 0);
    if (dst->maxSize > maxDigits + isNegative) {
        const u16 *digits = sDigitsEN;
        if (charsetMode == CHARSET_MODE_JP) {
            digits = sDigitsJP;
        }
        u32 divisor;
        dst->size = 0;
        dst->data[0] = CHAR_EOS;
        if (isNegative) {
            u16 hyphen;
            num *= -1;
            hyphen = (charsetMode == CHARSET_MODE_JP) ? 0xF1 : 0x1BE;
            dst->data[dst->size++] = hyphen;
        }
        divisor = sPowersOfTen[maxDigits - 1];
        while (divisor != 0) {
            u32 digit = (u16)((u32)num / divisor);
            num -= divisor * digit;
            if (paddingMode == PADDING_MODE_ZEROES) {
                dst->data[dst->size++] = (digit < 10) ? digits[digit] : 0xE2;
            } else if (digit != 0 || divisor == 1) {
                paddingMode = PADDING_MODE_ZEROES;
                dst->data[dst->size++] = (digit < 10) ? digits[digit] : 0xE2;
            } else if (paddingMode == PADDING_MODE_NONE) {
                dst->data[dst->size++] = (charsetMode == CHARSET_MODE_JP) ? 0x1 : 0x1DE;
            }
            divisor /= 10;
        }
        dst->data[dst->size] = CHAR_EOS;
        return;
    }
    fn_803D989C(0, "STRBUF overflow: bufsize=%d, keta=%d", dst->maxSize, maxDigits);
}

u32 Strbuf_Length(const Strbuf *str) {
    return str->size;
}

void Strbuf_CopyChars(Strbuf *dst, const u16 *src) {
    dst->size = 0;
    while (*src != CHAR_EOS) {
        if (dst->size >= dst->maxSize - 1) {
            fn_803D989C(0, "STRBUF overflow: busize=%d");
            break;
        }
        dst->data[dst->size++] = *src++;
    }
    dst->data[dst->size] = CHAR_EOS;
}

void Strbuf_CopyNumChars(Strbuf *dst, const u16 *src, u32 num) {
    if (num <= dst->maxSize) {
        u32 i;
        memcpy(dst->data, src, num * sizeof(u16));
        for (i = 0; i < num; i++) {
            if (dst->data[i] == CHAR_EOS) {
                break;
            }
        }
        dst->size = i;
        if (i == num) {
            dst->data[num - 1] = CHAR_EOS;
        }
    } else {
        fn_803D989C(0, "STRBUF overflow: bufsize=%d, strlen=%d", dst->maxSize, num);
    }
}

void Strbuf_ToChars(const Strbuf *src, u16 *dst, u32 dstSize) {
    if (src->size + 1 <= dstSize) {
        memcpy(dst, src->data, (src->size + 1) * sizeof(u16));
    } else {
        fn_803D989C(0, "STRBUF overflow: strlen=%d, arysize=%d", src->size, dstSize);
    }
}

const u16 *Strbuf_GetData(const Strbuf *str) {
    return str->data;
}

void Strbuf_Concat(Strbuf *dst, const Strbuf *src) {
    if (dst->size + src->size + 1 <= dst->maxSize) {
        memcpy(dst->data + dst->size, src->data, (src->size + 1) * sizeof(u16));
        dst->size += src->size;
    } else {
        fn_803D989C(0, "STRBUF overflow: bufsize=%d, src_len=%d, dst_len=%d", dst->maxSize, src->size, dst->size);
    }
}

void Strbuf_AppendChar(Strbuf *dst, u16 c) {
    if (dst->size + 1 < dst->maxSize) {
        dst->data[dst->size++] = c;
        dst->data[dst->size] = CHAR_EOS;
    } else {
        fn_803D989C(0, "STRBUF overflow: busize=%d", dst->maxSize, dst->size);
    }
}
