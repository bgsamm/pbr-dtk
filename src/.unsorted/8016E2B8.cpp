#include ".unsorted/8016E2B8.hpp"

#include "common.hpp"

extern "C" {

void fn_8016E2E4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8016E2DC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8016E2E4(0x1, a1, a2, a3, a4, a5, a6, a7); }

u32 fn_8016E430(u8 i) { return lbl_8063F1C8->_10[i]; }
void fn_8016E444(s32 i) { lbl_8063F1C8->_78[i] = 1; }

void fn_8016E458(s32 i) {
    lbl_8063F1C8->_7C[i] = 1;
    lbl_8063F1C8->_80[i] = 1;
}

u32 fn_8016E478(u8 i) { return lbl_8063F1C8->_00[i]; }

}
