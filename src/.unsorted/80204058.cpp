#include ".unsorted/80204058.hpp"

#include "common.hpp"
#include "gs/GShierarchyModule.hpp"

extern "C" {

extern u32 lbl_8063F494;

void fn_802054E0(u32 v) { lbl_8063F494 = v; }

GSrenderLight **fn_802054E8(u8 *count) {
    *count = GShierarchyModule::lbl_8063F46D;
    return GShierarchyModule::lbl_804920B0;
}

void fn_80205914(u8 *p, u32 v) {
    p[0] = v >> 24;
    p[1] = v >> 16;
    p[2] = v >> 8;
    p[3] = v;
}

}
