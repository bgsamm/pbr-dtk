#include ".unsorted/80383D24.hpp"

#include "common.hpp"

extern "C" {

void fn_803843CC();
void fn_8038428C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_803836AC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80384BD0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80384BCC(void) {
    fn_803843CC();
}
void fn_80384BE0(void) {}
void fn_80384C28(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_8038428C(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7);
}
void fn_80384C30(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_803836AC(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7);
}
void fn_80384C38(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_80384BD0(a0 - 0x80, a1, a2, a3, a4, a5, a6, a7);
}
void fn_80384C48(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) {
    fn_803836AC(a0 - 0x80, a1, a2, a3, a4, a5, a6, a7);
}
}
