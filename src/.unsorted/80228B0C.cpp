#include ".unsorted/80228B0C.hpp"

#include "common.hpp"

extern "C" {

u32 fn_80228B84(u8 *p) { return *(u32 *)(p + 0x14); }
void fn_80228FBC(void) {}

}

#include "common.hpp"

extern "C" {



void fn_80228C50(u8 *p, u32 x, u32 y) { *(u32 *)(p + 0x8) = x; *(u32 *)(p + 0xc) = y; }

}
