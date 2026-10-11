#include ".unsorted/80024914.hpp"

#include "common.hpp"

extern "C" {

void fn_80025360(u8 *p, u32 v) { *(u32 *)(p + 0xc) = v; }
u32 fn_80025368(u8 *p) { return *(u32 *)(p + 0xc); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_8063E9B0;
void fn_80025024(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80024E40(void) { if (lbl_8063E9B0 != 0) { fn_80025024(lbl_8063E9B0, 0, 0, 0, 0, 0, 0, 0); } }

}
