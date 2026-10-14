#include ".unsorted/80228970.hpp"

#include "common.hpp"

/* lbl_8063F658 */ u32 lbl_8063F658;

// TODO role: 1 when the upper half of a is 0x0596, else 2
s32 fn_80228970(u32 a) {
    s32 result = 2;
    if ((a & 0xFFFF0000) == 0x05960000) {
        result = 1;
    }
    return result;
}

// TODO role: builds four (1, value) pairs from the last four arguments and passes them to fn_8022A6A4
u32 fn_8022898C(u32 a, u32 b, u32 c, u32 d, u32 e) {
    u32 p;
    if (fn_80228970(a) == 1) {
        p = lbl_8063F640->_20;
    } else {
        p = fn_80226910(lbl_8063F640);
    }
    if (p == 0) {
        return 0;
    }
    Unk8022898C x[4];
    x[0]._00 = 1;
    x[0]._04 = b;
    x[1]._00 = 1;
    x[1]._04 = c;
    x[2]._00 = 1;
    x[2]._04 = d;
    x[3]._00 = 1;
    x[3]._04 = e;
    u32 result = fn_8022A6A4(p, a, x, 4, 0);
    lbl_8063F658 = fn_8022CFB8(p, result);
    return result;
}

// TODO role: checks the result of fn_80226910, its _940 field and fn_8022D02C, then forwards to fn_8022898C
u32 fn_80228A54(u32 a, u32 b, u32 c, u32 d, u32 e) {
    Unk80228A54 *p = (Unk80228A54 *)fn_80226910(lbl_8063F640);
    if (p == NULL) {
        return 0;
    }
    if (p->_940 == 0) {
        return 0;
    }
    u32 x = fn_8022D02C(p, a);
    if (x == 0) {
        return 0;
    }
    return fn_8022898C(x, b, c, d, e);
}
