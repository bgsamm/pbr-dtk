#include ".unsorted/802609E0.hpp"

#include "common.hpp"

extern "C" {

void fn_802609F0(u8 *p, u8 v) { *(u8 *)(p + 0x6) = v; }
u8 fn_802609F8(u8 *p) { return *(u8 *)(p + 0x6); }

}

#include "common.hpp"

extern "C" {



u32 fn_80260A10(u8 *p) { return *(u8 *)(p + 0x7) & 0x1; }

}
