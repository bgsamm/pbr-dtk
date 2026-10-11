#include ".unsorted/801166F8.hpp"

#include "common.hpp"

extern "C" {

void fn_80116708(void) {}
void fn_80116DC4(void) {}
void fn_8011838C(void) {}

}

#include "common.hpp"

extern "C" {

extern u8 lbl_8041B894[];

void fn_801166F8(u8 *p) { *(u8 **)(p + 0x0) = lbl_8041B894; }

}
