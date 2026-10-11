#include ".unsorted/8004E9F0.hpp"

#include "common.hpp"

extern "C" {

u8 fn_8004EE68(u8 *p) { return *(u8 *)(p + 0x0); }

}

#include "common.hpp"

extern "C" {

void fn_80050BE0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8004ECD8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80050BE0(a0 + 0x14, a1, a2, a3, a4, a5, a6, a7); }

}
