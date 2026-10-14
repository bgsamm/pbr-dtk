#include ".unsorted/80375340.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_806404E0;

u8 *fn_80375340(u8 *p) { return p + 0xd8; }
u8 *fn_80375348(u8 *p) { return p + 0xd8; }
u8 fn_80375350(u8 *p) { return *(u8 *)(p + 0x221); }
u32 *fn_80375358(void) { return &lbl_806404E0; }
void fn_803753A4(u8 *p, u8 v) { *(u8 *)(p + 0x4) = v; }

}
