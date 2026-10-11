#include ".unsorted/802674CC.hpp"

#include "common.hpp"

extern "C" {

u8 *fn_802674CC(u8 *p) { return p + 0xf00; }
s32 fn_802674D4(void) { return 3368; }
u8 *fn_802674DC(u8 *p) { return p + 0xf00; }
s32 fn_80267504(void) { return 30; }
s32 fn_8026750C(void) { return 360; }
u32 fn_80267688(u8 *p) { return *(u32 *)(p + 0x1c2c); }

}

#include "common.hpp"

extern "C" {



void fn_802676A8(u8 *p) { *(u32 *)(p + 0x1c2c) = 0x0; }

}
