#include ".unsorted/8000748C.hpp"

#include "common.hpp"

extern "C" {

/* lbl_8063E918 */ extern Unk8000748C *lbl_8063E918;

void fn_800074C0(void) {
    if (lbl_8063E918 != NULL) {
        fn_8000764C(lbl_8063E918);
    }
}

void fn_800074D4(void) {
    if (lbl_8063E918 != NULL) {
        fn_800077C0(lbl_8063E918);
    }
}

void fn_800074E8(void) {
    if (lbl_8063E918 != NULL) {
        lbl_8063E918->_00 = 1;
    }
}

void fn_80007564(u8 v) {
    if (lbl_8063E918 != NULL) {
        lbl_8063E918->_01 = v;
    }
}

u32 fn_80007578(u32 v) {
    u32 old = 0;
    if (lbl_8063E918 != NULL) {
        old = lbl_8063E918->_10;
        lbl_8063E918->_10 = v;
    }
    return old;
}

void fn_800077C0(Unk8000748C *obj) {
    obj->_06 = 1;
}
}
