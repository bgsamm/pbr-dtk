#include ".unsorted/80363E84.hpp"

#include "common.hpp"

extern "C" {

u8 fn_80363FFC(u8 *p) {
    return *(u8 *)(*(u8 **)(p + 0x14) + 0x15);
}
u8 fn_80364008(u8 *p) {
    return *(u8 *)(*(u8 **)(p + 0x14) + 0x14);
}
u8 fn_80364014(u8 *p) {
    return *(u8 *)(*(u8 **)(p + 0x14) + 0x16);
}
s32 fn_80364078(void) {
    return 2;
}
u8 fn_80364358(u8 *p) {
    return *(u8 *)(*(u8 **)(p + 0x14) + 0x7);
}
}

#include "common.hpp"

extern "C" {

void fn_80363FF0(u8 *p, u32 x, u32 y) {
    *(u32 *)(p + 0x10) = x;
    *(u32 *)(p + 0x14) = y;
}
}
