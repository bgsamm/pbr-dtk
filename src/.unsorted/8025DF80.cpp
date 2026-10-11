#include ".unsorted/8025DF80.hpp"
#include ".unsorted/8025E348.hpp"

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

void fn_8025DFC0(u32, u32 a) { fn_8025E474(a); }
void fn_8025DFC8(u32, void *block) { fn_8025E4D0(block); }

}
