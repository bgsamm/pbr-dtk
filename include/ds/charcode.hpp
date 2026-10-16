#pragma once

#include <revolution/types.h>

#define CHAR_EOS 0xFFFF
#define CHAR_FORMAT_ARG 0xFFFE

const u16 *CharCode_SkipFormatArg(const u16 *str);
BOOL CharCode_IsFormatArg(const u16 *str);
u32 CharCode_FormatArgParam(const u16 *str, u32 paramIndex);
