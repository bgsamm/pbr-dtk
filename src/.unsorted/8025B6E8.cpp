#include ".unsorted/8025B6E8.hpp"

#include "common.hpp"

extern "C" {

/* lbl_80424F60 */ extern Unk80424F60 lbl_80424F60;
/* lbl_80425110 */ extern Unk80425110 lbl_80425110;
/* lbl_80502548 */ extern u32 lbl_80502548[];
extern u32 lbl_8063F958;
extern u32 lbl_8063F95C;
extern u32 lbl_8063F960;
extern u32 lbl_8063F968;

void fn_8025BA00();
void fn_802F0760();
void fn_802F1BB8();
void fn_802F0588(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
void fn_8025DBA0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_8025B6E8(void) { fn_8025BA00(); }

s32 fn_8025B720(u32 v) {
    lbl_8063F95C = v;
    return 0;
}

s32 fn_8025B7F0(u32 v) {
    lbl_8063F958 = v;
    return 0;
}

void fn_8025B8B4(u32 v) { lbl_80424F60._28 = v; }
void fn_8025B8C4(u32 v) { lbl_80424F60._2C = v; }
void fn_8025B8D4(u32 v) { lbl_80424F60._10 = v; }
void fn_8025B8E4(u32 v) { lbl_80424F60._14 = v; }
u32 fn_8025B8F4(void) { return lbl_80424F60._38; }
void fn_8025B948(u32 v) { lbl_80424F60._24 = v; }
void fn_8025B958(u32 v) { lbl_80424F60._20 = v; }
void fn_8025B9DC(u32 v) { lbl_80424F60._18 = v; }
void fn_8025B9EC(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_802F0588((u32)&lbl_80424F60, a1, a2, a3, a4, a5, a6, a7); }
void fn_8025B9F8(void) { fn_802F0760(); }
void fn_8025B9FC(void) { fn_802F1BB8(); }
u32 fn_8025BD9C(void) { return lbl_8063F960; }

void fn_8025BF04(u32 seed) { lbl_8063F968 = (seed << 16) | seed; }

u8 fn_8025BF14(void) {
    u32 next = lbl_8063F968 * 0x45 + 0x1111;
    lbl_8063F968 = next & 0x7FFFFFFF;
    return next >> 16;
}

u32 fn_8025CA88(void) { return lbl_80425110._08; }
u32 fn_8025CA98(void) { return lbl_80425110._0C; }
void fn_8025CC38(void) { lbl_80502548[0] = 0; }
u32 fn_8025CC94(void) { return lbl_80502548[1]; }

void fn_8025CEF8(Unk8025CEF8 *obj) {
    obj->_6050 = 0;
    obj->_6054 = 0;
    obj->_6058 = 0;
}

void fn_8025D390(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_8025DBA0(a0 + 0x6030, a1, a2, a3, a4, a5, a6, a7); }

}
