#include ".unsorted/8006E554.hpp"

#include "common.hpp"

extern "C" {

void fn_80058E34();
void fn_8007C3E0();
void fn_801577C4();

BOOL fn_800728C4(void) {
    return lbl_8063D4D0->_00 == 3;
}
BOOL fn_80072908(void) {
    return lbl_8063D4D0->_04 == 2;
}
BOOL fn_80072944(void) {
    return lbl_8063D4D0->_14 == 2;
}
BOOL fn_80072CD8(void) {
    return lbl_8063D4D0->_08 == 2;
}
void fn_80073EA0(u32 i) {
    lbl_8063D4D0->_420[i] = -1;
}

void fn_800745D8(void) {}
void fn_800753F4(void) {}
void fn_8007B9F4(void) {}
void fn_8007BA80(void) {}
void fn_8007C290(void) {}
void fn_8007C3DC(void) {
    fn_8007C3E0();
}
void fn_8007C6D0(void) {
    fn_801577C4();
}
void fn_8007C80C(void) {
    fn_80058E34();
}
}
