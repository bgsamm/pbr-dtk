#include ".unsorted/801E0A54.hpp"

#define FIX_ADDRESS(obj, member, base) \
    do { \
    if ((base) != 0 && (obj)->member != 0 && (obj)->member < 0x80000000) { \
        (obj)->member += (base); \
    } \
    } while (0)

struct Sdr {
    /* 0x00 */ u8 _00[8];
    /* 0x08 */ u32 _08;
    /* 0x0c */ u32 _0c;
    /* 0x10 */ u32 _10;
    /* 0x14 */ u32 _14;
    /* 0x18 */ u16 _18;
    /* 0x1a */ u16 _1a;
    /* 0x1c */ u16 _1c;
    /* 0x1e */ u16 _1e;
    /* 0x20 */ u8 _20[4];
    /* 0x24 */ u32 _24;
    /* 0x28 */ u32 _28;
};

void fn_801E34DC(Sdr *sdr, u32 base) {
    FIX_ADDRESS(sdr, _08, base);
    FIX_ADDRESS(sdr, _0c, base);
    FIX_ADDRESS(sdr, _10, base);
    FIX_ADDRESS(sdr, _14, base);
    FIX_ADDRESS(sdr, _24, base);
    FIX_ADDRESS(sdr, _28, base);

    u16 var1 = sdr->_1a;

    for (u32 i = 0; i < var1; i++) {
        
    }
}
