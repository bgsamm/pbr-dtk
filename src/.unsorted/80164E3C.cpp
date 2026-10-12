#include ".unsorted/80164E3C.hpp"

#include ".unsorted/8025DF80.hpp"
#include ".unsorted/802674CC.hpp"

#include <string.h>

#include "common.hpp"

/* lbl_8063F0A0 */ s32 lbl_8063F0A0;

// TODO role: copies the buffer from fn_8015F704 into the one fn_802674CC returns, then calls fn_802676A8
void fn_80164E3C(void) {
    void *source = fn_8015F704();
    void *dest = fn_802674CC(fn_8025E31C(fn_8025DFD0()));
    u32 size = fn_802674D4(fn_8025E31C(fn_8025DFD0()));
    memcpy(dest, source, size);
    fn_802676A8(fn_8025E31C(fn_8025DFD0()));
}

// TODO role: copies the buffer the other way when fn_80267688 allows it; returns 1 when it did something
s32 fn_80164EA8(void) {
    if (fn_80267688(fn_8025E31C(fn_8025DFD0())) == 0) {
        if (lbl_8063F0A0 != 0) {
            lbl_8063F0A0 = 0;
            return 1;
        }
        return 0;
    }
    void *dest = fn_8015F704();
    void *source = fn_802674CC(fn_8025E31C(fn_8025DFD0()));
    u32 size = fn_802674D4(fn_8025E31C(fn_8025DFD0()));
    memcpy(dest, source, size);
    fn_802676A8(fn_8025E31C(fn_8025DFD0()));
    lbl_8063F0A0 = 0;
    return 1;
}

// TODO role: forwards to fn_802677F8
u64 fn_80164F58(void) {
    return fn_802677F8(fn_8025E31C(fn_8025DFD0()));
}
