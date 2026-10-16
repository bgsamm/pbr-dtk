#include ".unsorted/80228B0C.hpp"

#include ".unsorted/80226364.hpp"

#include "common.hpp"

extern "C" {

u32 fn_80228B84(Unk80226364_00 *obj) {
    return obj->_14;
}

// TODO role: sets the flag pair at 0x10/0x11 (three states, read back by fn_80228BF8)
void fn_80228BC0(Unk80226364_00 *obj) {
    obj->_10 = 1;
    obj->_11 = 0;
}

void fn_80228BD4(Unk80226364_00 *obj) {
    obj->_10 = 0;
    obj->_11 = 1;
}

void fn_80228BE8(Unk80226364_00 *obj) {
    obj->_10 = 0;
    obj->_11 = 0;
}

u32 fn_80228BF8(Unk80226364_00 *obj) {
    if (obj->_10 != 0) {
        return 1;
    }
    u32 result = 3;
    if (obj->_11 != 0) {
        result = 2;
    }
    return result;
}

// TODO role: stores a value at 0x04 and the same value plus 0x5001 at 0x00
void fn_80228C24(Unk80226364_00 *obj, u32 value) {
    obj->_04 = value;
    obj->_00 = value + 0x5001;
}

// TODO role: stores a value at 0x00 and, when a thread handle is attached, its id (value plus 0x2000)
void fn_80228C34(Unk80226364_00 *obj, u32 value) {
    obj->_00 = value;
    if (obj->_1C != NULL) {
        obj->_1C->mID = value + 0x2000;
    }
}

void fn_80228C50(Unk80226364_00 *obj, u32 x, u32 y) {
    obj->_08 = x;
    obj->_0C = y;
}

// TODO role: suspends the attached thread
void fn_80228C5C(Unk80226364_00 *obj) {
    if (obj->_1C != NULL) {
        obj->_1C->suspendThread();
    }
}

// TODO role: resumes the attached thread
void fn_80228C70(Unk80226364_00 *obj) {
    if (obj->_1C != NULL) {
        obj->_1C->resumeThread();
    }
}

void fn_80228FBC(void) {}

// TODO role: act on the current element of an array of records (indexed by the second member)
u32 fn_80228FC0(Unk80226364_04 *inner) {
    return fn_80228BF8(&inner->_00[inner->_04]);
}

void fn_80228FD4(Unk80226364_04 *inner, u32 value) {
    inner->_00[inner->_04]._220 = value;
}

void fn_80228FEC(Unk80226364_04 *inner, u32 x, u32 y) {
    fn_80228C50(&inner->_00[inner->_04], x, y);
}
}
