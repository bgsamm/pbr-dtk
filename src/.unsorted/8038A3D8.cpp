#include ".unsorted/8038A3D8.hpp"

#include "common.hpp"

extern "C" {

u32 fn_8038BF30(u8 *p) { return *(u32 *)(p + 0x40); }
u16 fn_8038D9E0(u8 *p) { return *(u16 *)(*(u8 **)(p + 0xc) + 0x8); }
s32 fn_8038E330(void) { return 0; }

}

#include "common.hpp"

extern "C" {

extern u8 lbl_8044E580[];
void fn_8038E2AC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8038D2C4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8038E2AC(a0 + 0x4, a1, a2, a3, a4, a5, a6, a7); }
void fn_8038E320(u8 *p) { *(u8 **)(p + 0x0) = lbl_8044E580; }

}
