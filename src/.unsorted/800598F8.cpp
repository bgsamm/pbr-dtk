#include ".unsorted/800598F8.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063EB98;
extern u8 lbl_8063EBAC;

void fn_800599C0(u8 v) {
    lbl_8063EBAC = v;
}
void fn_8005A438(u32 v) {
    lbl_8063EB98 = v;
}
void fn_8005A44C(void) {}
}

#include "common.hpp"

extern "C" {

extern u8 lbl_8063EBA4;

void fn_8005A440(void) {
    lbl_8063EBA4 = 0x1;
}
}
