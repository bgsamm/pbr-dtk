#include ".unsorted/8037F908.hpp"

#include "common.hpp"

extern "C" {

void fn_803828FC(void) {}
void fn_8038340C(u8 *p, u32 v) { *(u32 *)(p + 0x0) = v; }
u8 *fn_80383978(u8 *p) { return p + 0xd8; }
u8 *fn_80383980(u8 *p) { return p + 0xd8; }
u8 fn_80383988(u8 *p) { return *(u8 *)(p + 0x1d0); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_80640560;
extern u32 lbl_806404B0;
void fn_803841E4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_80384238(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_803839A4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80383864(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_803841E4(a0 + 0xd8, a1, a2, a3, a4, a5, a6, a7); }
void fn_8038386C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80384238(a0 + 0xd8, a1, a2, a3, a4, a5, a6, a7); }
BOOL fn_8038395C(u8 *p) { return *(u32 *)(p + 0x1c8) != 0; }
void fn_80383970(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_803839A4(*(u32 *)(a0 + 0x1c8), a1, a2, a3, a4, a5, a6, a7); }
u32 *fn_80383990(void) { return &lbl_80640560; }

}
