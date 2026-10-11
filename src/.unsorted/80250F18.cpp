#include ".unsorted/80250F18.hpp"

#include "common.hpp"

extern "C" {

void fn_80253C08(u8 *p, u32 v) { *(u32 *)(p + 0x154) = v; }
void fn_80253D98(void) {}
void fn_80253D9C(void) {}

}

#include "common.hpp"

extern "C" {

extern u8 lbl_804FDAB0[];
void fn_80250FF8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80251AD4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80253BC8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80253B20(u8 *p, u32 x, u32 y) { *(u32 *)(p + 0x24) = x; *(u32 *)(p + 0x28) = y; }
void fn_80253BFC(u8 *p, u32 x, u32 y) { *(u32 *)(p + 0x14c) = x; *(u32 *)(p + 0x150) = y; }
void fn_80253C28(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80250FF8((u32)lbl_804FDAB0, a0, a2, a3, a4, a5, a6, a7); }
void fn_80253CBC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80251AD4((u32)lbl_804FDAB0, a0, a2, a3, a4, a5, a6, a7); }
void fn_80253F8C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80253BC8((u32)lbl_804FDAB0, a0, a2, a3, a4, a5, a6, a7); }

}
