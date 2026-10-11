#include ".unsorted/8025DF80.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F998;
void fn_8025E370();

u32 fn_8025DFD0(void) { return lbl_8063F998; }
u32 fn_8025E0A8(u8 *p) { return *(u32 *)(p + 0x4); }
void fn_8025E120(void) {}
void fn_8025E154(void) {}
void fn_8025E188(void) {}
u32 fn_8025E304(u8 *p) { return *(u32 *)(p + 0x14); }
u32 fn_8025E30C(u8 *p) { return *(u32 *)(p + 0x8); }
u32 fn_8025E314(u8 *p) { return *(u32 *)(p + 0xc); }
u32 fn_8025E31C(u8 *p) { return *(u32 *)(p + 0x10); }
void fn_8025E324(void) { fn_8025E370(); }

}

#include "common.hpp"

extern "C" {

void fn_8025E474(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8025E4D0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8025DFC0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025E474(a1, a1, a2, a3, a4, a5, a6, a7); }
void fn_8025DFC8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025E4D0(a1, a1, a2, a3, a4, a5, a6, a7); }

}
