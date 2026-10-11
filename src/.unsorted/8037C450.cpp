#include ".unsorted/8037C450.hpp"

#include "common.hpp"

extern "C" {

void fn_8037E5A8();
void fn_8037E948();

void fn_8037F298(void) {}
void fn_8037F580(void) { fn_8037E5A8(); }
void fn_8037F584(void) { fn_8037E948(); }
u8 fn_8037F598(u8 *p) { return *(u8 *)(p + 0xbf); }
u8 fn_8037F5A0(u8 *p) { return *(u8 *)(p + 0xba); }
u8 fn_8037F5A8(u8 *p) { return *(u8 *)(p + 0xb9); }
u8 *fn_8037F8DC(u8 *p) { return p + 0xd8; }
u8 *fn_8037F8E4(u8 *p) { return p + 0xd8; }
u8 fn_8037F8EC(u8 *p) { return *(u8 *)(p + 0x193); }

}

#include "common.hpp"

extern "C" {

extern u32 lbl_80640548;
extern u32 lbl_806404B0;
void fn_8037F588(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037D464(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8037F908(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8037F5B0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8037F588(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7); }
void fn_8037F5C8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8037D464(a0 - 0x74, a1, a2, a3, a4, a5, a6, a7); }
BOOL fn_8037F8C0(u8 *p) { return *(u32 *)(p + 0x938) != 0; }
void fn_8037F8D4(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8037F908(*(u32 *)(a0 + 0x938), a1, a2, a3, a4, a5, a6, a7); }
u32 *fn_8037F8F4(void) { return &lbl_80640548; }

}
