#include ".unsorted/8016EFCC.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F200;

u32 fn_8016FA3C(void) { return lbl_8063F200; }
void fn_8016FA44(u32 v) { lbl_8063F200 = v; }

}

#include "common.hpp"

extern "C" {

extern u8 lbl_8048CE68[];
void fn_8016E2B8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8016EFCC(u8 *p) { *(u32 *)(p + 0xa0) = 0x1; }
void fn_801700D0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8016E2B8((u32)lbl_8048CE68, a1, a2, a3, a4, a5, a6, a7); }

}
