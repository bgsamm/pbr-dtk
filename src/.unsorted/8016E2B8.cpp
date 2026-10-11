#include ".unsorted/8016E2B8.hpp"

#include "common.hpp"

extern "C" {

/* lbl_8048CDD8 */ extern s32 lbl_8048CDD8[4];
extern s32 lbl_8063F1CC;

void fn_8016E2DC(void) { fn_8016E2E4(1); }

// TODO name: appends a value to a small list unless it is already there
void fn_8016E2E4(u32 value) {
    s32 i;
    for (i = 0; i < lbl_8063F1CC; i++) {
        if (lbl_8048CDD8[i] == (s32)value) {
            return;
        }
    }
    lbl_8048CDD8[lbl_8063F1CC++] = value;
}

s32 fn_8016E430(u8 i) { return lbl_8063F1C8->_10[i]; }
void fn_8016E444(s32 i) { lbl_8063F1C8->_78[i] = 1; }

void fn_8016E458(s32 i) {
    lbl_8063F1C8->_7C[i] = 1;
    lbl_8063F1C8->_80[i] = 1;
}

u32 fn_8016E478(u8 i) { return lbl_8063F1C8->_00[i]; }

}
