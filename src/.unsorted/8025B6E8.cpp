#include ".unsorted/8025B6E8.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F960;
void fn_8025BA00();
void fn_802F0760();
void fn_802F1BB8();

void fn_8025B6E8(void) { fn_8025BA00(); }
void fn_8025B9F8(void) { fn_802F0760(); }
void fn_8025B9FC(void) { fn_802F1BB8(); }
u32 fn_8025BD9C(void) { return lbl_8063F960; }

}

#include "common.hpp"

extern "C" {

extern u8 lbl_80424F60[];
extern u8 lbl_80425110[];
extern u8 lbl_80502548[];
void fn_802F0588(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8025DBA0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

u32 fn_8025B8F4(void) { return *(u32 *)(lbl_80424F60 + 0x38); }
void fn_8025B9EC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_802F0588((u32)lbl_80424F60, a1, a2, a3, a4, a5, a6, a7); }
u32 fn_8025CA88(void) { return *(u32 *)(lbl_80425110 + 0x8); }
u32 fn_8025CA98(void) { return *(u32 *)(lbl_80425110 + 0xc); }
u32 fn_8025CC94(void) { return *(u32 *)(lbl_80502548 + 0x4); }
void fn_8025D390(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025DBA0(a0 + 0x6030, a1, a2, a3, a4, a5, a6, a7); }

}
