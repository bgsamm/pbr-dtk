#include ".unsorted/801697AC.hpp"

#include "common.hpp"

extern "C" {

void fn_80169884(void) {}
void fn_80169E88(void) {}
void fn_8016A088(void) {}
}

#include "common.hpp"

extern "C" {

extern u8 lbl_8041F7A0[];
extern u8 lbl_8063F156;

void fn_80169834(u8 *p) {
    *(u8 **)(p + 0x0) = lbl_8041F7A0;
}
void fn_801698B4(void) {
    lbl_8063F156 = 0x1;
}
}
