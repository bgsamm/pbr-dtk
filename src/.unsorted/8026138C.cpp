#include ".unsorted/8026138C.hpp"

#include "common.hpp"

extern "C" {

void fn_802F1CD4();

s32 fn_8026138C(void) { return 200; }
s32 fn_80261394(void) { return 5; }
s32 fn_8026139C(void) { return 1; }
void fn_802615A0(u8 *p, u32 v) { *(u32 *)(p + 0x1000) = v; }
u32 fn_802615A8(u8 *p) { return *(u32 *)(p + 0xfc4); }
s32 fn_802624C4(void) { return 0; }
void fn_80262548(u8 *p, u32 v) { *(u32 *)(p + 0x1004) = v; }
u32 fn_802625C8(u8 *p) { return *(u32 *)(p + 0xfac); }
void fn_802625E0(void) { fn_802F1CD4(); }
u32 fn_80262790(u8 *p) { return *(u32 *)(p + 0xfe4); }
u32 fn_8026283C(u8 *p) { return *(u32 *)(p + 0xf04); }
s32 fn_80262844(void) { return 0; }

}

#include "common.hpp"

extern "C" {

void fn_8025E6C0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

BOOL fn_802615B0(u8 *p) { return *(u32 *)(p + 0xfac) != 0; }
void fn_80262734(u8 *p, u32 x, u32 y) { *(u32 *)(p + 0xff0) = x; *(u32 *)(p + 0xfec) = y; }
void fn_80262740(u8 *p) { *(u32 *)(p + 0xfe4) = 0x1; }
void fn_80262798(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025E6C0(*(u32 *)(a0 + 0xfec), a1, a2, a3, a4, a5, a6, a7); }

}
