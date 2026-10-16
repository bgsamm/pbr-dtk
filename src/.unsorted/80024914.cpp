#include ".unsorted/80024914.hpp"

#include "common.hpp"

extern "C" {

void fn_80024E40(void) {
    if (lbl_8063E9B0 != NULL) {
        fn_80025024(lbl_8063E9B0);
    }
}

void fn_80025360(Unk80024914 *obj, u32 v) {
    obj->_0C = v;
}
u32 fn_80025368(Unk80024914 *obj) {
    return obj->_0C;
}
}
