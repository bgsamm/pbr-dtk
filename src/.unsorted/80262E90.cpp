#include ".unsorted/80262E90.hpp"

#include "common.hpp"

extern "C" {

void fn_802F1CD4();

s32 fn_80262E90(void) {
    return 200;
}
s32 fn_80262E98(void) {
    return 5;
}
s32 fn_80262EA0(void) {
    return 1;
}
s32 fn_80262EB0(void) {
    return 0;
}
void fn_80262F50(void) {
    fn_802F1CD4();
}
u32 fn_80262F54(u8 *p) {
    return *(u32 *)(p + 0xf0c);
}
s32 fn_80262F84(void) {
    return 0;
}
s32 fn_80262F8C(void) {
    return 0;
}
u32 fn_80263048(u8 *p) {
    return *(u32 *)(p + 0xf00);
}
u32 fn_802631FC(u8 *p) {
    return *(u32 *)(p + 0xf30);
}
s32 fn_802638FC(void) {
    return 0;
}
s32 fn_80263904(void) {
    return 0;
}
s32 fn_8026390C(void) {
    return -1;
}
s32 fn_80263914(void) {
    return -1;
}
}

#include "common.hpp"

extern "C" {

void fn_8025E518(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80262EA8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8025E518(*(u32 *)(a0 + 0xf40), a1, a2, a3, a4, a5, a6, a7);
}
BOOL fn_80262F5C(u8 *p) {
    return *(u32 *)(p + 0xf00) != 0;
}
void fn_802631AC(u8 *p, u32 x, u32 y) {
    *(u32 *)(p + 0xf3c) = x;
    *(u32 *)(p + 0xf40) = y;
}
void fn_802631B8(u8 *p) {
    *(u32 *)(p + 0xf30) = 0x1;
}
}
