#include ".unsorted/80367FAC.hpp"

#include "common.hpp"

extern "C" {

u32 fn_80368B0C(u8 *p) {
    return *(u32 *)(p + 0x4);
}
u32 fn_80368C58(u8 *p) {
    return *(u32 *)(p + 0x0);
}
u8 fn_8036D718(u8 *p) {
    return *(u8 *)(p + 0x67);
}
void fn_8036DF0C(u8 *p, f32 v) {
    *(f32 *)(p + 0x98) = v;
}
void fn_8036DF14(u8 *p, f32 v) {
    *(f32 *)(p + 0x90) = v;
}
void fn_8036DF1C(u8 *p, f32 v) {
    *(f32 *)(p + 0x94) = v;
}
}

#include "common.hpp"

extern "C" {

extern u32 lbl_806404B0;
void fn_8037A9EC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

BOOL fn_8036E0CC(u8 *p) {
    return *(u32 *)(p + 0x8) != 0;
}
BOOL fn_8036E0E0(u8 *p) {
    return *(u32 *)(p + 0xc) != 0;
}
void fn_8036E0F4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037A9EC(*(u32 *)(a0 + 0x8), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8036E0FC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037A9EC(*(u32 *)(a0 + 0xc), a1, a2, a3, a4, a5, a6, a7);
}
u32 *fn_8036E184(void) {
    return &lbl_806404B0;
}
void fn_8036E18C(void) {
    lbl_806404B0 = 0x0;
}
}
