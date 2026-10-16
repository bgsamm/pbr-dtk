#include ".unsorted/80165534.hpp"

#include "common.hpp"

extern "C" {

u8 *fn_80166AAC(u8 *p) {
    return p + 0x2;
}
u32 fn_80166AB4(u8 *p) {
    return *(u32 *)(p + 0x854);
}
u32 fn_80166ABC(u8 *p) {
    return *(u32 *)(p + 0x84c);
}
u32 fn_80166AC4(u8 *p) {
    return *(u32 *)(p + 0x858);
}
u32 fn_80166ACC(u8 *p) {
    return *(u32 *)(p + 0x85c);
}
void fn_80166C14(u8 *p, u32 v) {
    *(u32 *)(p + 0x1968) = v;
}
u32 fn_80166C1C(u8 *p) {
    return *(u32 *)(p + 0x1968);
}
void fn_80166D3C(u8 *p, u32 v) {
    *(u32 *)(p + 0x860) = v;
}
u32 fn_80166D44(u8 *p) {
    return *(u32 *)(p + 0x860);
}
}

#include "common.hpp"

extern "C" {

void fn_80166AA0(u8 *p) {
    *(u32 *)(p + 0x864) = 0x1;
}
BOOL fn_80166AF0(u8 *p) {
    return *(u32 *)(p + 0x1884) != 0;
}
}
