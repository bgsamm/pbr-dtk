#include ".unsorted/8016A25C.hpp"

#include "common.hpp"

extern "C" {

/* lbl_8041F820 */ extern u8 lbl_8041F820[];
extern u8 lbl_8063F1C0;
extern u8 lbl_8063F1C4[4];

u8 fn_8016CE10(u32, Unk8016A25C *obj) {
    return lbl_8041F820[obj->_08];
}
void fn_8016D1C0(u8 v) {
    lbl_8063F1C0 = v;
}
void fn_8016D1C8(u32 i, u8 v) {
    lbl_8063F1C4[i] = v;
}
}
