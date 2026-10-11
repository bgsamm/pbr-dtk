#include ".unsorted/80168798.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F108;
extern u32 lbl_8063F114;
extern u32 lbl_8063F118;
extern u32 lbl_8063F11C;
void fn_80168B48();
void fn_801691D8();

void fn_801687C8(u32 v) { lbl_8063F108 = v; }
u32 fn_801687D0(void) { return lbl_8063F108; }
u32 fn_801689A0(void) { return lbl_8063F114; }
void fn_80168AF4(u32 v) { lbl_8063F118 = v; }
u32 fn_80168AFC(void) { return lbl_8063F118; }
void fn_80168B04(u32 v) { lbl_8063F11C = v; }
u32 fn_80168B0C(void) { return lbl_8063F11C; }
void fn_80168B58(void) { fn_80168B48(); }
void fn_80168B5C(void) { fn_80168B48(); }
void fn_80168B60(void) { fn_801691D8(); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F10C;
extern u32 lbl_8063F110;
void fn_80164C04(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80163DC4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80168798(void) { lbl_8063F10C = 0x1; }
void fn_801687A4(void) { lbl_8063F10C = 0x0; }
void fn_801687B0(void) { lbl_8063F110 = 0x1; }
void fn_801687BC(void) { lbl_8063F110 = 0x0; }
void fn_801687D8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80164C04(0x0, a1, a2, a3, a4, a5, a6, a7); }
void fn_80168818(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80163DC4(0x1, a1, a2, a3, a4, a5, a6, a7); }

}
