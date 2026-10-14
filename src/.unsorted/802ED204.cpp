#include ".unsorted/802ED204.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063DEC0;
extern u32 lbl_8063DECC;
extern u32 lbl_8064020C;
extern u32 lbl_80640288;
extern u8 lbl_80445BB0[];
extern u8 lbl_8057AAB8[];
void fn_802ED628();
void fn_802F7FC0();

u8 *fn_802EDD5C(void) { return lbl_80445BB0; }
s32 fn_802EDE48(void) { return 0; }
void fn_802F3264(void) {}
u32 fn_802F4CF8(void) { return lbl_8064020C; }
u32 fn_802F5190(void) { return lbl_8063DEC0; }
void fn_802F5198(void) { fn_802ED628(); }
u8 *fn_802F5A44(void) { return lbl_8057AAB8; }
u32 fn_802F5A50(void) { return lbl_8063DECC; }
void fn_802F6D6C(void) {}
void fn_802F6D78(void) {}
void fn_802F7C00(u8 *p, u32 v) { *(u32 *)(p + 0x7d8) = v; }
void fn_802F7C08(u8 *p, u32 v) { *(u32 *)(p + 0x7d4) = v; }
u32 fn_802F7C10(u8 *p) { return *(u32 *)(p + 0x7d4); }
void fn_802F83F0(void) { fn_802F7FC0(); }
void fn_802F8440(void) {}
u32 fn_802FAA68(u8 *p) { return *(u32 *)(p + 0x348); }
void fn_802FFED0(void) {}
u8 *fn_802FFED4(u8 *p) { return p + 0x800; }
u8 *fn_802FFEDC(u8 *p) { return p + 0x808; }
u8 *fn_802FFEE4(u8 *p) { return p + 0x840; }
u8 *fn_802FFEEC(u8 *p) { return p + 0x80c; }
u32 fn_803047CC(void) { return lbl_80640288; }
s32 fn_8030483C(void) { return 0; }
void fn_802F83F4(u8 *p) { *(u32 *)(p + 0x18) = 0x0; }
void fn_802F8CB4(u8 *p) { *(u32 *)(p + 0x0) = 0x0; }
void fn_802FAA50(u8 *p) { *(u32 *)(p + 0x348) = 0x0; }
void fn_802FAA5C(u8 *p) { *(u32 *)(p + 0x348) = 0x1; }

}
