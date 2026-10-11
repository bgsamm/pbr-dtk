#include ".unsorted/800B9E10.hpp"

#include "common.hpp"

extern "C" {

Unk800B9E10 *fn_800BA550(void) { return lbl_8063EED8; }

void fn_800BA558(u16 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_0A = lbl_8063EED8->_08;
    lbl_8063EED8->_08 = v;
}

u16 fn_800BA578(void) {
    if (lbl_8063EED8 != NULL) {
        return lbl_8063EED8->_08;
    }
    return 0xFFFF;
}

u16 fn_800BA598(void) {
    if (lbl_8063EED8 != NULL) {
        return lbl_8063EED8->_0A;
    }
    return 0xFFFF;
}

void fn_800BA5B8(u16 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_0C = v;
}

u16 fn_800BA5CC(void) {
    if (lbl_8063EED8 != NULL) {
        return lbl_8063EED8->_0C;
    }
    return 0xFFFF;
}

void fn_800BA5EC(s32 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_10 = v;
}

s32 fn_800BA600(void) {
    if (lbl_8063EED8 != NULL) {
        return lbl_8063EED8->_10;
    }
    return -1;
}

void fn_800BA970(u16 i, u16 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_14[i] = v;
}

void fn_800BA9B0(u16 i, u32 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_54[i] = v;
}

void fn_800BA9F0(u16 i, u32 v) {
    if (lbl_8063EED8 == NULL) {
        return;
    }
    lbl_8063EED8->_28C[i] = v;
}

u8 fn_800BB9D4(s32 v) { return v / 6; }

void fn_800C5940(void) {}
void fn_800C5944(void) {}

}
