#include ".unsorted/8004F37C.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EB10;

void fn_8004F418(void) {}
u32 fn_8004F41C(void) {
    return lbl_8063EB10;
}
u32 fn_8004F4C4(u8 *p) {
    return *(u32 *)(p + 0x4);
}
}

#include "common.hpp"

extern "C" {

void fn_8004F900(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8004F4CC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8004F900(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
}
