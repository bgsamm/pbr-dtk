#include ".unsorted/80226364.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F644;

void fn_802265D4(u32, u32 v) {
    lbl_8063F644 = v;
}

u32 fn_80226868(Unk80226364 *obj) {
    return obj->_04->_00[obj->_04->_04]._00;
}
u8 fn_802268D8(Unk80226364 *obj) {
    return obj->_04->_00[obj->_04->_04]._10;
}
u8 fn_802268F4(Unk80226364 *obj) {
    return obj->_04->_00[obj->_04->_04]._11;
}
void fn_80226910(Unk80226364 *obj) {
    fn_80228B84(&obj->_04->_00[obj->_04->_04]);
}

void fn_80227558(Unk80227558 *flags) {
    flags->_30 = 1;
    flags->_34 = 2;
}

void fn_8022756C(void) {}
void fn_80227570(void) {}
void fn_802275F8(void) {
    fn_80227574();
}

void fn_80227620(Unk80226364 *obj) {
    Unk80226364_00 *elem = &obj->_04->_00[obj->_04->_04];
    if (elem != NULL) {
        fn_80228CF8(elem);
    }
}

void fn_80227640(Unk80226364 *) {}

void fn_80227644(void) {
    if (lbl_8063F640 != NULL) {
        fn_80227620(lbl_8063F640);
    }
}

void fn_80227658(void) {
    if (lbl_8063F640 != NULL) {
        fn_80227640(lbl_8063F640);
    }
}
}
