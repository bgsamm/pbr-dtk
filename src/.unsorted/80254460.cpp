#include ".unsorted/80254460.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F908;

u32 fn_802544D0(void) { return lbl_8063F908; }
s32 fn_80256520(void) { return 1; }

}

#include "common.hpp"

extern "C" {

void fn_80377024(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_802558FC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80377024(*(u32 *)(a0 + 0x0), a1, a2, a3, a4, a5, a6, a7); }
void fn_80256E34(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }
void fn_80256E80(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }

}
