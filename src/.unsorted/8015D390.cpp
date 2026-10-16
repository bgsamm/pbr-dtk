#include ".unsorted/8015D390.hpp"

#include "common.hpp"

extern "C" {

extern u8 lbl_8063F018;

u8 fn_8015E62C(void) {
    return lbl_8063F018;
}
}

#include "common.hpp"

extern "C" {

extern u8 lbl_80488300[];

u32 fn_8015F660(void) {
    return *(u32 *)(lbl_80488300 + 0x18);
}
}
