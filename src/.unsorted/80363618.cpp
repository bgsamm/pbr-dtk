#include ".unsorted/80363618.hpp"

#include "common.hpp"

extern "C" {

s32 fn_80363BC4(void) { return 32; }
s32 fn_80363BCC(void) { return 32; }
s32 fn_80363BD4(void) { return 4; }
s32 fn_80363BDC(void) { return 1; }
s32 fn_80363BE4(void) { return 0; }
s32 fn_80363BEC(void) { return 1; }
s32 fn_80363BF4(void) { return 1; }
s32 fn_80363BFC(void) { return 1; }
u32 fn_80363C04(u8 *p) { return *(u32 *)(p + 0x14); }
u32 fn_80363C0C(u8 *p) { return *(u32 *)(p + 0x18); }
u8 fn_80363C14(u8 *p) { return *(u8 *)(p + 0x6c); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_80640470;
extern u32 lbl_80640468;
void fn_80363574(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80363B58(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80363574(a0 + 0x14, a1, a2, a3, a4, a5, a6, a7); }
u32 *fn_80363C1C(void) { return &lbl_80640470; }

}
