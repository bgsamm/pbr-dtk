// Imported from SMGCommunity/Petari (CC0), src/MetroTRK/debugger/embedded/MetroTRK/Portable/string_TRK.c
#include <size_t.h>
#include "trk.h"


size_t TRK_strlen(const s8* str) {
    size_t len = 0xFFFFFFFF;

    u8* p = (u8*)(str - 1);

    do

        len++;

    while (*++p);

    return len;
}
