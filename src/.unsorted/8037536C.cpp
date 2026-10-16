#include ".unsorted/8037536C.hpp"

#include "common.hpp"

extern "C" {

void fn_803753A4(u8 *p, u8 v) {
    *(u8 *)(p + 0x4) = v;
}
void fn_80377004(u8 *p, u32 v) {
    *(u32 *)(p + 0x4) = v;
}
u32 fn_8037AF94(u8 *p) {
    return *(u32 *)(p + 0x30);
}
u8 fn_8037AF9C(u8 *p) {
    return *(u8 *)(p + 0x2c);
}
void fn_8037BE70(u8 *p, u16 v) {
    *(u16 *)(p + 0x26) = v;
}
}

#include "common.hpp"

extern "C" {

void fn_80376F68(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80376F00(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377E30(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377E70(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377EB0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037765C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037774C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037786C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377918(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377964(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377AAC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377DAC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377A00(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377B64(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377C74(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377EF4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80377FF4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037703C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80379B54(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80378CBC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80370194(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80370330(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80375670(u8 *p) {
    *(u8 *)(p + 0x5) = 0x1;
}
void fn_80376F7C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80376F68(a0 - 0x4, a1, a2, a3, a4, a5, a6, a7);
}
void fn_80376F84(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80376F00(a0 - 0x4, a1, a2, a3, a4, a5, a6, a7);
}
BOOL fn_80376FF0(u8 *p) {
    return *(u32 *)(p + 0x4) != 0;
}
void fn_80377024(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377E30(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037702C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377E70(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377034(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377EB0(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037704C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037765C(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377054(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037774C(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037705C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037786C(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377064(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377918(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037706C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377964(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377074(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377AAC(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037707C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377DAC(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377084(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377A00(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037708C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377B64(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_80377094(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377C74(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037709C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377EF4(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_803770A4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80377FF4(*(u32 *)(a0 + 0x4), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037A8AC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8037703C(*(u32 *)(a0 + 0x10), a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037A914(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80379B54(a0 - 0xc, a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037A91C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80378CBC(a0 - 0xc, a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037AAF4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80370194(a0 + 0x1c, a1, a2, a3, a4, a5, a6, a7);
}
void fn_8037AAFC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80370330(a0 + 0x1c, a1, a2, a3, a4, a5, a6, a7);
}
}
