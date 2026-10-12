#include ".unsorted/80250F18.hpp"

#include "common.hpp"

extern "C" {

// TODO role: sets byte 6 of element i of the array at 0x08, when i is below the count at 0x00
void fn_80251AD4(Unk80250F18 *obj, u32 index) {
    if (index < obj->_00) {
        obj->_08[index]._06 = 2;
    }
}

// TODO role: when element i of the table at 0x04 has a count above the argument, stores the argument and 1 in element i
// of the table at 0x08, then the last argument
void fn_80253A74(Unk80250F18 *obj, s32 index, u32 value, u32 extra) {
    if (obj->_04[index]._0E <= value) {
        return;
    }
    obj->_08[index]._10 = value;
    obj->_08[index]._12 = 1;
    obj->_08[index]._1E = extra;
}

// TODO role: reads member 0x12 of an element of the table at 0x08, or 0 when the index is out of range
u16 fn_80253ABC(Unk80250F18 *obj, s16 index) {
    if (index < 0 || index >= obj->_00) {
        return 0;
    }
    return obj->_08[index]._12;
}

// TODO role: reads member 0x10 of an element of the table at 0x08, or 0xFFFF when the index is out of range
u16 fn_80253AEC(Unk80250F18 *obj, s16 index) {
    if (index < 0 || index >= obj->_00) {
        return 0xFFFF;
    }
    return obj->_08[index]._10;
}

void fn_80253B20(Unk80250F18 *obj, u32 x, u32 y) {
    obj->_24 = x;
    obj->_28 = y;
}

// TODO role: stores two values in a free entry of the tables at 0x2C/0xAC (index -1) or in the given entry; returns the
// entry, -1 when full, -2 for an unused entry, -3 for a bad index
s32 fn_80253B2C(Unk80250F18 *obj, u32 x, u32 y, s32 index) {
    if (index == -1) {
        for (s32 i = 0; i < 32; i++) {
            if (obj->_12C[i] == 0) {
                obj->_2C[i] = x;
                obj->_AC[i] = y;
                obj->_12C[i] = 1;
                return i;
            }
        }
        return -1;
    }
    if (index < 0 || index >= 32) {
        return -3;
    }
    if (obj->_12C[index] != 0) {
        obj->_2C[index] = x;
        obj->_AC[index] = y;
        return index;
    }
    return -2;
}

// TODO role: clears entry i of three parallel tables of 32 entries
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

// TODO role: stores the callback at 0x154
void fn_80253C08(Unk80250F18 *obj, Unk80250F18Callback callback) {
    obj->_154 = callback;
}

// TODO role: calls that callback with the object when it is set
void fn_80253C10(Unk80250F18 *obj) {
    if (obj->_154 != NULL) {
        obj->_154(obj);
    }
}

// TODO role: the wrappers below call methods of the global object lbl_804FDAB0
void fn_80253C28(u16 count) {
    fn_80250FF8(&lbl_804FDAB0, count);
}

void fn_80253CBC(u32 index) {
    fn_80251AD4(&lbl_804FDAB0, index);
}

void fn_80253CCC(s32 a) {
    fn_80251AF8(&lbl_804FDAB0, a);
}

void fn_80253D98(void) {}
void fn_80253D9C(void) {}

void fn_80253DA0(Unk80250F18Callback callback) {
    fn_80253C08(&lbl_804FDAB0, callback);
}

void fn_80253DB0(u32 a, u32 b, u32 c) {
    fn_80253A74(&lbl_804FDAB0, a, b, c);
}

void fn_80253DD0(s16 a) {
    fn_80253ABC(&lbl_804FDAB0, a);
}

void fn_80253DE0(s16 a) {
    fn_80253AEC(&lbl_804FDAB0, a);
}

void fn_80253DF0(u32 a, u32 b, u32 c) {
    fn_80254260(&lbl_804FDAB0, a, b, c);
}

void fn_80253E4C(u32 a, u32 b, u32 c) {
    fn_80254334(&lbl_804FDAB0, a, b, c);
}

void fn_80253E6C(u32 a, u32 b, u32 c) {
    fn_80254334(&lbl_804FDAB0, a, b, c);
}

void fn_80253F54(u32 x, u32 y) {
    fn_80253B20(&lbl_804FDAB0, x, y);
}

void fn_80253F6C(u32 a, u32 b, u32 c) {
    fn_80253B2C(&lbl_804FDAB0, a, b, c);
}

void fn_80253F8C(s32 index) {
    fn_80253BC8(&lbl_804FDAB0, index);
}

void fn_80253F9C(u32 x, u32 y) {
    fn_80253BFC(&lbl_804FDAB0, x, y);
}
}
