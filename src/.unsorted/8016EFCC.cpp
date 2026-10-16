#include ".unsorted/8016EFCC.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F1E8;
extern u32 lbl_8063F1EC;
extern u32 lbl_8063F1F0;
extern u32 lbl_8063F1F4;
extern u32 lbl_8063F1FC;
extern u32 lbl_8063F200;
extern u8 lbl_8048CE68[];
void fn_8016E2B8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8016EFCC(u8 *p) {
    *(u32 *)(p + 0xa0) = 0x1;
}

u32 fn_8016F3FC(u32 *out) {
    *out = lbl_8063F1F4;
    return lbl_8063F1E8;
}

u32 fn_8016F40C(u32 *out) {
    *out = lbl_8063F1FC;
    return lbl_8063F1F0;
}

u32 fn_8016F628(u32 offset) {
    return lbl_8063F1EC + offset;
}
void fn_8016FA30(void) {
    lbl_8063F200 = 0;
}
u32 fn_8016FA3C(void) {
    return lbl_8063F200;
}
void fn_8016FA44(u32 v) {
    lbl_8063F200 = v;
}
void fn_801700D0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8016E2B8((u32)lbl_8048CE68, a1, a2, a3, a4, a5, a6, a7);
}
}
