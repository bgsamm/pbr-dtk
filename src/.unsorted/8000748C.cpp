#include ".unsorted/8000748C.hpp"

#include "common.hpp"

extern "C" {



void fn_800077C0(u8 *p) { *(u8 *)(p + 0x6) = 0x1; }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_8063E918;
void fn_8000764C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_800074C0(void) { if (lbl_8063E918 != 0) { fn_8000764C(lbl_8063E918, 0, 0, 0, 0, 0, 0, 0); } }

}
