#include ".unsorted/80044F28.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EAB8;

u8 fn_80044FB0(u8 *p) {
    return *(u8 *)(p + 0x3f);
}
u32 fn_80045590(void) {
    return lbl_8063EAB8;
}
}

#include "common.hpp"

extern "C" {

void fn_800470B4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8004746C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_800470B4(a0, 0x0, a2, a3, a4, a5, a6, a7);
}
}
