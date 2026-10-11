#include "ds/charcode_util.hpp"

void CharCode_Copy(u16 *dst, const u16 *src) {
    while (*src != CHAR_EOS) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = CHAR_EOS;
}

s32 CharCode_Length(const u16 *str) {
    s32 len = 0;
    while (str[len] != CHAR_EOS) {
        len++;
    }
    return len;
}

// Returns FALSE when the strings are equal.
BOOL CharCode_Compare(const u16 *str1, const u16 *str2) {
    while (*str1 == *str2) {
        if (*str1 == CHAR_EOS) {
            return FALSE;
        }
        str1++;
        str2++;
    }
    return TRUE;
}

BOOL CharCode_CompareNumChars(const u16 *str1, const u16 *str2, u32 num) {
    while (*str1 == *str2) {
        if (num == 0) {
            return FALSE;
        }
        if (*str1 == CHAR_EOS && *str2 == CHAR_EOS) {
            return FALSE;
        }
        num--;
        str1++;
        str2++;
    }
    return TRUE;
}
