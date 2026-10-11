#include ".unsorted/800447E4.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EAA8;

u32 fn_80044848(void) { return lbl_8063EAA8; }
void fn_80044A98(void) {}
void fn_80044AA8(void) {}

}

#include "common.hpp"

extern "C" {



void fn_80044A8C(u8 *p, u32 x, u8 y) { *(u32 *)(p + 0x4) = x; *(u8 *)(p + 0x1) = y; }

}
