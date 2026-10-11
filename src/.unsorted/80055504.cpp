#include ".unsorted/80055504.hpp"

#include "common.hpp"

extern "C" {

void fn_8005555C(void) {}
void fn_800557E0(void) {}

}

#include "common.hpp"

extern "C" {

extern u8 lbl_8040AF00[];
void fn_80009808(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8005550C(u8 *p) { *(u8 **)(p + 0x0) = lbl_8040AF00; }
void fn_80055560(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80009808(0x1, a1, a2, a3, a4, a5, a6, a7); }

}
