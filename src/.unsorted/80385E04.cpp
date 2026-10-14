#include ".unsorted/80385E04.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_80640568;

u32 fn_80385E04(u8 *p) { return *(u32 *)(p + 0x28); }
u32 *fn_80385E0C(void) { return &lbl_80640568; }
void fn_80385E14(void) { lbl_80640568 = 0x0; }

}
