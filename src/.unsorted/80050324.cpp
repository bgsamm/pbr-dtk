#include ".unsorted/80050324.hpp"

#include "common.hpp"

extern "C" {

void fn_800520B0(void) {}
void fn_8005376C(void) {}
void fn_80054154(void) {}
void fn_80054490(void) {}
void fn_80054494(void) {}
u32 fn_800547F4(u8 *p) { return *(u32 *)(p + 0x38); }
u32 fn_8005498C(u8 *p) { return *(u32 *)(p + 0x40); }
u32 fn_80055278(u8 *p) { return *(u32 *)(p + 0x3c); }
s32 fn_80055474(void) { return 0; }

}

#include "common.hpp"

extern "C" {

extern u8 lbl_8040AEA4[];

void fn_80050388(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }
void fn_800505C0(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }
void fn_80050BE0(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }
void fn_80052060(u8 *p) { *(u8 **)(p + 0x0) = lbl_8040AEA4; }

}
