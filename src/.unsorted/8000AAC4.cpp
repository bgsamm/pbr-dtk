#include ".unsorted/8000AAC4.hpp"

#include "common.hpp"

extern "C" {

void fn_8000AAC4(u8 *p, u32 v) { *(u32 *)(p + 0x4) = v; }
u8 fn_8000AACC(u8 *p) { return *(u8 *)(*(u8 **)(p + 0x4) + 0x5); }
u32 fn_8000AAD8(u8 *p) { return *(u32 *)(*(u8 **)(p + 0x4) + 0x8); }
u32 fn_8000AAE4(u8 *p) { return *(u32 *)(*(u8 **)(p + 0x4) + 0x8); }
u16 fn_8000AAF0(u8 *p) { return *(u16 *)(*(u8 **)(p + 0x4) + 0x6); }
u32 fn_8000AB0C(u8 *p) { return *(u32 *)(*(u8 **)(p + 0x4) + 0xc); }
u8 fn_8000AB18(u8 *p) { return *(u8 *)(*(u8 **)(p + 0x4) + 0x2); }
u16 fn_8000AB24(u8 *p) { return *(u16 *)(*(u8 **)(p + 0x4) + 0x0); }
u8 fn_8000AB30(u8 *p) { return *(u8 *)(*(u8 **)(p + 0x4) + 0x3); }

}

#include "common.hpp"

extern "C" {

extern u8 lbl_80405F60[];

void fn_8000AC34(u8 *p) { *(u8 **)(p + 0x0) = lbl_80405F60; }

}
