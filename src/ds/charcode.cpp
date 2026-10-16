#include "ds/charcode.hpp"

// A format argument is CHAR_FORMAT_ARG, a type, a parameter count, then the parameters.
const u16 *CharCode_SkipFormatArg(const u16 *str) {
    if (*str == CHAR_FORMAT_ARG) {
        const u16 *next = str;
        next += 3;
        next += str[2];
        return next;
    }
    return str;
}

BOOL CharCode_IsFormatArg(const u16 *str) {
    return (str[1] & 0xFF00) == 0x100;
}

u32 CharCode_FormatArgParam(const u16 *str, u32 paramIndex) {
    return str[paramIndex + 3];
}
