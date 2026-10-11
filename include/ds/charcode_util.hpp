#pragma once

#include "ds/charcode.hpp"

void CharCode_Copy(u16 *dst, const u16 *src);
s32 CharCode_Length(const u16 *str);
BOOL CharCode_Compare(const u16 *str1, const u16 *str2);
BOOL CharCode_CompareNumChars(const u16 *str1, const u16 *str2, u32 num);
