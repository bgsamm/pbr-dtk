#include ".unsorted/80167994.hpp"

#include "common.hpp"

// TODO role: if fn_80164C2C finds something for the first argument, passes it to fn_80166C3C with the second
void fn_80167994(void *a, u32 b) {
    void *found = fn_80164C2C(a);
    if (found != NULL) {
        fn_80166C3C(found, b);
    }
}

// TODO role: empty function
void fn_801679D0(void) {}

// TODO role: empty function
void fn_801679D4(void) {}
