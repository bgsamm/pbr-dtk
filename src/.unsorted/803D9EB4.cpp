#include ".unsorted/803D9EB4.hpp"

// TODO Maps a battle type (one flag per type) to an index; the second argument selects variants for 4 and 5.
u32 fn_803D9EB4(u32 battleType, s32 variant) {
    switch (battleType) {
        case 0: {
            BOOL alt = (variant == 4 || variant == 5);
            u32 index = 8;
            if (alt) {
                index = 9;
            }
            return index;
        }
        case 1:
        case 2:
        case 0x10: {
            BOOL alt = (variant == 4 || variant == 5);
            u32 index = 4;
            if (alt) {
                index = 6;
            }
            return index;
        }
        case 4:
        case 0x80: return 1;
        case 8:    {
            BOOL alt = (variant == 4 || variant == 5);
            u32 index = 2;
            if (alt) {
                index = 7;
            }
            return index;
        }
        case 0x100: {
            BOOL alt = (variant == 4 || variant == 5);
            u32 index = 6;
            if (alt) {
                index = 4;
            }
            return index;
        }
        case 0x40:  return 3;
        case 0x200: return 10;
        case 0x20:  return 5;
        case 0x400: return 11;
    }
    return 0;
}
