#include ".unsorted/80250F18.hpp"

#include "common.hpp"

extern "C" {

void fn_80251AD4(Unk80250F18 *obj, u32 index) {
    if (index < obj->_00) {
        obj->_08[index]._06 = 2;
    }
}

void fn_80253B20(Unk80250F18 *obj, u32 x, u32 y) {
    obj->_24 = x;
    obj->_28 = y;
}

void fn_80253BC8(Unk80250F18 *obj, s32 index) {
    if (index < 0 || index >= 32) {
        return;
    }
    obj->_2C[index] = 0;
    obj->_AC[index] = 0;
    obj->_12C[index] = 0;
}

void fn_80253BFC(Unk80250F18 *obj, u32 x, u32 y) {
    obj->_14C = x;
    obj->_150 = y;
}

void fn_80253C08(Unk80250F18 *obj, u32 v) {
    obj->_154 = v;
}

void fn_80253C28(u16 count) {
    fn_80250FF8(&lbl_804FDAB0, count);
}

void fn_80253CBC(u32 index) {
    fn_80251AD4(&lbl_804FDAB0, index);
}

void fn_80253D98(void) {}
void fn_80253D9C(void) {}

void fn_80253F8C(s32 index) {
    fn_80253BC8(&lbl_804FDAB0, index);
}
}
