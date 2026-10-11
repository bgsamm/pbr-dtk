#include ".unsorted/800284B0.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063E9B0;

void fn_8002A294(void) {}
void fn_8002A298(void) {}
u16 fn_8002A2F8(u8 *p) { return *(u16 *)(p + 0x510); }
void fn_8002A320(u8 *p, u16 v) { *(u16 *)(p + 0x50e) = v; }
u16 fn_8002A328(u8 *p) { return *(u16 *)(p + 0x512); }
u8 fn_8002A330(u8 *p) { return *(u8 *)(p + 0x516); }
u32 fn_8002A344(u8 *p) { return *(u32 *)(p + 0x518); }
void fn_8002A484(u8 *p, f32 v) { *(f32 *)(p + 0xd80) = v; }
void fn_8002A48C(u8 *p, f32 v) { *(f32 *)(p + 0xd84) = v; }
void fn_8002A494(u8 *p, u8 v) { *(u8 *)(p + 0xd88) = v; }
u16 fn_8002A49C(u8 *p) { return *(u16 *)(p + 0x50e); }
u8 *fn_8002A5C0(u8 *p) { return p + 0xdb4; }
u32 fn_8002A804(void) { return lbl_8063E9B0; }
void fn_8002A80C(u8 *p, u16 v) { *(u16 *)(p + 0x50c) = v; }
u16 fn_8002A814(u8 *p) { return *(u16 *)(p + 0x51c); }
u8 fn_8002A81C(u8 *p) { return *(u8 *)(p + 0x520); }
void fn_8002A84C(void) {}

}

#include "common.hpp"

extern "C" {



u32 fn_8002A2EC(u8 *p) { return *(u32 *)(p + 0x0) & 0x1; }
u32 fn_8002A338(u8 *p) { return *(u16 *)(p + 0x514) & 0xff; }
u32 fn_8002A51C(u8 *p) { return (*(u32 *)(p + 0x0) >> 12) & 0x1; }
u32 fn_8002A528(u8 *p) { return (*(u32 *)(p + 0x0) >> 22) & 0x1; }
u32 fn_8002A534(u8 *p) { return (*(u32 *)(p + 0x0) >> 13) & 0x1; }
u32 fn_8002A540(u8 *p) { return (*(u32 *)(p + 0x0) >> 14) & 0x1; }
u32 fn_8002A54C(u8 *p) { return (*(u32 *)(p + 0x0) >> 19) & 0x1; }
u32 fn_8002A558(u8 *p) { return (*(u32 *)(p + 0x0) >> 20) & 0x1; }
u32 fn_8002A564(u8 *p) { return (*(u32 *)(p + 0x0) >> 23) & 0x1; }
u32 fn_8002A7F8(u8 *p) { return (*(u32 *)(p + 0x0) >> 15) & 0x1; }

}
