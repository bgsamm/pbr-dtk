#include ".unsorted/803839A4.hpp"

#include "common.hpp"

extern "C" {

void fn_803843CC();

void fn_80384BCC(void) { fn_803843CC(); }
void fn_80384BE0(void) {}
void fn_803852CC(void) {}
void fn_803852F4(void) {}
void fn_8038531C(void) {}
s32 fn_80385320(void) { return 255; }
void fn_80385328(void) {}
void fn_8038580C(void) {}
u32 fn_80385E04(u8 *p) { return *(u32 *)(p + 0x28); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_80640568;
void fn_8038428C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_803836AC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80384BD0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80384C28(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8038428C(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7); }
void fn_80384C30(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_803836AC(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7); }
void fn_80384C38(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80384BD0(a0 - 0x80, a1, a2, a3, a4, a5, a6, a7); }
void fn_80384C48(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_803836AC(a0 - 0x80, a1, a2, a3, a4, a5, a6, a7); }
void fn_803852C0(u8 *p) { *(u32 *)(p + 0x0) = -0x1; }
u32 *fn_80385E0C(void) { return &lbl_80640568; }
void fn_80385E14(void) { lbl_80640568 = 0x0; }

}
