#include ".unsorted/802B4CC0.hpp"

#include "common.hpp"

extern "C" {

extern u8 lbl_806401B8;
void fn_802B4D10();
void fn_802B9D34();
void fn_802C7CB0();
extern u8 lbl_80568B78[];
extern u8 lbl_8056BC40[];
void fn_802C66B8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
extern u8 lbl_805686D8[];

s32 fn_802B9574(void) {
    return 0;
}
u32 fn_802BA534(u8 *p) {
    return *(u32 *)(p + 0x0);
}
void fn_802BB0A0(void) {}
void fn_802BB0A4(void) {}
void fn_802BB0A8(void) {}
void fn_802BB0AC(void) {}
s32 fn_802BB154(void) {
    return 2;
}
void fn_802BB1C4(void) {}
void fn_802BB1F4(void) {
    fn_802B4D10();
}
s32 fn_802BC6F0(void) {
    return 0;
}
void fn_802BDAC4(u8 v) {
    lbl_806401B8 = v;
}
void fn_802BF1F4(void) {
    fn_802C7CB0();
}
s32 fn_802BF4B0(void) {
    return 11;
}
void fn_802BFFD8(void) {}
void fn_802C72F4(void) {}
void fn_802C8244(void) {}
void fn_802CA4B0(void) {
    fn_802B9D34();
}
void fn_802D63F8(void) {}
void fn_802DD798(void) {}
void fn_802DF894(void) {}
void fn_802BDF6C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_802C66B8(a0 + 0x8, a1, a2, a3, a4, a5, a6, a7);
}
u8 fn_802C4394(void) {
    return *(u8 *)(lbl_80568B78 + 0x27bf);
}
u8 fn_802C78FC(void) {
    return *(u8 *)(lbl_80568B78 + 0x1848);
}
u8 fn_802D9D80(void) {
    return *(u8 *)(lbl_8056BC40 + 0x1);
}
void fn_802BD634(u32 v) {
    *(u32 *)(lbl_805686D8 + 0x80) = v;
}
void fn_802BD644(u32 v) {
    *(u32 *)(lbl_805686D8 + 0x88) = v;
}
void fn_802BD654(u32 v) {
    *(u32 *)(lbl_805686D8 + 0x84) = v;
}
}
