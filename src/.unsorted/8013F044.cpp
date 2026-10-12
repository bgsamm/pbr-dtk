#include ".unsorted/8013F044.hpp"

#include ".unsorted/800559D4.hpp"
#include ".unsorted/80164E3C.hpp"
#include "gs/GScache.hpp"
#include "gs/GSfsys.hpp"
#include "gs/GSrender.hpp"

#include <string.h>

#include "common.hpp"

// Passed by value to fn_800E71B0.
// size: 0x20
struct Unk800E71B0 {
    /* 0x00 */ u32 _00[8];
};

// Filled by the layout query 6 and passed to fn_80059A3C or fn_800E71B0.
// size: 0x28
struct Unk80149630 {
    /* 0x00 */ Unk800E71B0 _00;
    /* 0x20 */ u32 _20[2];
};

// TODO Returns the 0x17C value of the current entry (inlined in fn_8014DCF4).
static inline int fn_8014DCF4Inline(void) {
    return lbl_8063D578->_17c[lbl_8063D578->_d49];
}

// TODO Replace with proper imports
extern "C" {
int fn_80253E8C(s16, int, int, void *);
int fn_80253EDC(s16, int, int, void *);
void fn_80253E10(s16, f32, int);
void fn_80253DB0(s16, int, int);
void fn_80253DF0(s16, int, int);
void fn_80253E4C(s16, int, void *);
void fn_8017714C(void *, void *, int);
int fn_80162A90(int);
void fn_80166D6C(void *, int, int, int, int, int);
void fn_80253EB4(s16, int, int, int);
int fn_8005A9F8(int);
u16 fn_80253DE0(s16);
u16 fn_80253DD0(s16);
void fn_80059A3C(int, void *);
void fn_80253CCC(u16);
void fn_80253F8C(int);
int fn_802502F4(int);
void fn_8015C308(int, int);
u16 fn_80250398(int, int, int);
void fn_80250134(int, int, int, int, int, u32);
void fn_8015C4F4(int, int);
void fn_8011F050();
void fn_800E7044();
void fn_8009FC9C();
void fn_802502D4(u16);
void fn_800598F8(int, int);
void fn_8000B170(int, int, f32);
void fn_801558F0(void *, void *);
f64 fn_8015F7A0();
u32 fn_80059A6C(int, int, int, int);
void fn_800E71B0(int, Unk800E71B0);
void fn_802504A0(int, int, int, GXColor, int, f32);
void fn_802503D8(int, void *);
int fn_80166FB0(int);
int fn_8016704C(int);
int fn_80167098(int);
s64 fn_80166FF4(int);
int fn_80166F64(int);
int fn_80166ED0(int);
u8 fn_800E5410(int);
u32 fn_801502A0(void *, int, int);
void fn_800599C8(int, int, int, int, int, int);
int fn_80163434();
void fn_80168B04(int);
int fn_80165354();
void fn_80168100(int, void *);
int fn_80168148(int, void *);
void fn_8005B294(s16, int, int);
void fn_8015CC78(int, int, int, int);
u32 fn_801670E4(int);
u32 *fn_8016722C(int);
void fn_80253F04(s16, int, int, int);
void fn_8012D530(int, void *, u8);
void fn_8012D640(int, void *, u8, int);
void fn_8005B328(s16, Unk8014FC0C *, int, int);
int fn_8005AC60(int, int);
Unk8015F6E0 *fn_8015F6E0();
Unk8011C974 *fn_8011C974();
Unk8015F690 *fn_8015F690();
s16 fn_80253C38(void *, void *, void *, void *, int, int, int, int);
int fn_80253F6C(int, void *, int);
void fn_80162FD4();
void fn_8016532C();
void fn_80162940(int, int, int);
}

extern const f32 lbl_8064144C;
extern const u16 lbl_80641470;
extern const u16 lbl_80641472;
extern const u16 lbl_80641474;
extern const u16 lbl_80641476;
extern const f32 lbl_80641414;
extern const f32 lbl_80641444;
extern const f64 lbl_80641430;
extern const f64 lbl_80641438;
extern u8 lbl_80487250[];
extern u8 lbl_80487278[];
extern const f32 lbl_80641450;
extern const f32 lbl_80641454;
extern u64 lbl_8041D468[];
extern u16 lbl_8041D438[];
extern u16 lbl_8041D450[];
extern u8 lbl_80486D28[];
extern const u8 lbl_80641478[];
extern const f32 lbl_80641440;
extern const f32 lbl_80641460;
extern const f32 lbl_80641464;
extern const f32 lbl_80641468;
extern const f32 lbl_8064146C;
extern int lbl_8041DC78[];
extern const f32 lbl_80641410;

// TODO Clears the layout slots and the global context of the screen.
void fn_8013F044() {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        lbl_8063D578->_000[i] = 0;
        lbl_8063D578->_080[i] = -1;
    }
    lbl_8063D578->_0c0 = -1;
    lbl_8063D578->_d43 = 1;
    lbl_8063D578->_d44 = 3;
    lbl_8063D578->_d45 = 2;
    lbl_8063D578->_d46 = 1;
    lbl_8063D578->_d47 = 1;
    lbl_8063D578->_d48 = 0;
    for (i = 0; i < 14; i++) {
        lbl_8063D578->_0d8[i] = 0;
        lbl_8063D578->_d4c[i] = 0;
    }
    lbl_8063D578->_d30 &= ~0x10000000;
    lbl_8063D578->_d41 = 0;
    lbl_8063D578->_d42 = 0;
    for (i = 0; i < 6; i++) {
        lbl_8063D578->_ebc[i] = lbl_80486D28 + i * 0xdc;
    }
    for (i = 0; i < 0x1e; i++) {
        memset(&lbl_8063D578->_470[i], 0, 0x44);
        lbl_8063D578->_ce0[i] = 0x2d;
    }
}

// TODO Loads the layouts of the screen, registers their callbacks and picks the first state.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8013F31C() {
    lbl_8063D578->_d24 = fn_8015F6E0();
    lbl_8063D578->_d28 = fn_8011C974();
    lbl_8063D578->_efa = fn_8015F690()->_4c;
    GSfsys::loadFsys(0x404);
    GSfsys::loadFsys(0x405);
    lbl_8063D578->_000[0] = fn_80055D98(0x404, 0x23831a00);
    lbl_8063D578->_000[1] = fn_80055D98(0x404, 0x23841a00);
    lbl_8063D578->_000[2] = fn_80055D98(0x404, 0x23851a00);
    lbl_8063D578->_000[3] = fn_80055D98(0x404, 0x23861a00);
    lbl_8063D578->_000[4] = fn_80055D98(0x404, 0x23871a00);
    lbl_8063D578->_000[5] = fn_80055D98(0xe, 0x23881a00);
    lbl_8063D578->_000[6] = fn_80055D98(0xe, 0x23891a00);
    lbl_8063D578->_000[7] = fn_80055D98(0x404, 0x238a1a00);
    lbl_8063D578->_000[8] = fn_80055D98(0x404, 0x238b1a00);
    lbl_8063D578->_000[10] = fn_80055D98(0x404, 0x238c1a00);
    lbl_8063D578->_000[11] = fn_80055D98(0x404, 0x238d1a00);
    lbl_8063D578->_000[12] = fn_80055D98(0x404, 0x238e1a00);
    lbl_8063D578->_000[13] = fn_80055D98(0x404, 0x238f1a00);
    lbl_8063D578->_000[14] = fn_80055D98(0x404, 0x23901a00);
    lbl_8063D578->_000[15] = fn_80055D98(0x404, 0x23911a00);
    lbl_8063D578->_000[16] = fn_80055D98(0x404, 0x23921a00);
    lbl_8063D578->_000[17] = fn_80055D98(0x404, 0x23961a00);
    lbl_8063D578->_000[18] = fn_80055D98(0x404, 0x272d1a00);
    lbl_8063D578->_000[19] = fn_80055D98(0x404, 0x272d1a00);
    lbl_8063D578->_000[22] = fn_80055D98(0x404, 0x27bb1a00);
    lbl_8063D578->_000[23] = fn_80055D98(0x404, 0x27981a00);
    lbl_8063D578->_000[24] = fn_80055D98(0x404, 0x27991a00);
    lbl_8063D578->_000[25] = fn_80055D98(0xe, 0x44f1a00);
    lbl_8063D578->_000[26] = fn_80055D98(0x404, 0x27531a00);
    lbl_8063D578->_000[27] = fn_80055D98(0x404, 0x27331a00);
    lbl_8063D578->_000[28] = fn_80055D98(0xe, 0x4501a00);
    lbl_8063D578->_000[29] = fn_80055D98(0xe, 0x44f1a00);
    lbl_8063D578->_000[30] = fn_80055D98(0xe, 0x19a51a00);
    lbl_8063D578->_000[31] = fn_80055D98(0xe, 0x44e1a00);
    lbl_8063D578->_080[7] =
        fn_80253C38(lbl_8063D578->_000[7], 0, (void *)fn_80149C0C, (void *)fn_80149E18, -1, 0, 1, 0);
    lbl_8063D578->_080[30] =
        fn_80253C38(lbl_8063D578->_000[30], (void *)fn_8014E354, (void *)fn_8014E3C4, (void *)fn_8014E3F0, -1, 0, 1, 0);
    lbl_8063D578->_080[0] =
        fn_80253C38(lbl_8063D578->_000[0], 0, (void *)fn_80149348, (void *)fn_80149374, -1, 0, 1, 0);
    lbl_8063D578->_080[1] =
        fn_80253C38(lbl_8063D578->_000[1], 0, (void *)fn_801493A0, (void *)fn_80149488, -1, 0, 1, 0);
    lbl_8063D578->_080[2] =
        fn_80253C38(lbl_8063D578->_000[2], 0, (void *)fn_801495A8, (void *)fn_80149630, -1, 0, 1, 0);
    lbl_8063D578->_080[3] =
        fn_80253C38(lbl_8063D578->_000[3], 0, (void *)fn_80149744, (void *)fn_801497F0, -1, 0, 1, 0);
    lbl_8063D578->_080[4] =
        fn_80253C38(lbl_8063D578->_000[4], 0, (void *)fn_801498C0, (void *)fn_801498EC, -1, 0, 1, 0);
    lbl_8063D578->_080[5] =
        fn_80253C38(lbl_8063D578->_000[5], 0, (void *)fn_80149918, (void *)fn_80149944, -1, 0, 1, 0);
    lbl_8063D578->_080[8] =
        fn_80253C38(lbl_8063D578->_000[8], 0, (void *)fn_8014A1E8, (void *)fn_8014A2C0, -1, 0, 1, 0);
    lbl_8063D578->_080[10] =
        fn_80253C38(lbl_8063D578->_000[10], 0, (void *)fn_8014A510, (void *)fn_8014A71C, -1, 0, 1, 0);
    lbl_8063D578->_080[11] =
        fn_80253C38(lbl_8063D578->_000[11], 0, (void *)fn_8014AAA4, (void *)fn_8014AB70, -1, 0, 1, 0);
    lbl_8063D578->_080[12] =
        fn_80253C38(lbl_8063D578->_000[12], 0, (void *)fn_8014AC84, (void *)fn_8014AE08, -1, 0, 1, 0);
    lbl_8063D578->_080[13] =
        fn_80253C38(lbl_8063D578->_000[13], 0, (void *)fn_8014B41C, (void *)fn_8014B634, -1, 0, 1, 0);
    lbl_8063D578->_080[14] =
        fn_80253C38(lbl_8063D578->_000[14], 0, (void *)fn_8014BCA0, (void *)fn_8014BCCC, -1, 0, 1, 0);
    lbl_8063D578->_080[15] =
        fn_80253C38(lbl_8063D578->_000[15], 0, (void *)fn_8014BCF8, (void *)fn_8014BD24, -1, 0, 1, 0);
    lbl_8063D578->_080[16] =
        fn_80253C38(lbl_8063D578->_000[16], 0, (void *)fn_8014BD50, (void *)fn_8014BD7C, -1, 0, 1, 0);
    lbl_8063D578->_080[17] =
        fn_80253C38(lbl_8063D578->_000[17], (void *)fn_8014BDA8, (void *)fn_8014BDB8, (void *)fn_8014BEE4, -1, 0, 1, 0);
    lbl_8063D578->_080[18] =
        fn_80253C38(lbl_8063D578->_000[18], 0, (void *)fn_8014C074, (void *)fn_8014C078, -1, 0, 1, 0);
    lbl_8063D578->_080[19] =
        fn_80253C38(lbl_8063D578->_000[19], 0, (void *)fn_8014C2B8, (void *)fn_8014C34C, -1, 0, 1, 0);
    lbl_8063D578->_080[23] =
        fn_80253C38(lbl_8063D578->_000[23], (void *)fn_8014C598, (void *)fn_8014C6A0, (void *)fn_8014CD2C, -1, 0, 1, 0);
    lbl_8063D578->_080[24] =
        fn_80253C38(lbl_8063D578->_000[24], 0, (void *)fn_8014D148, (void *)fn_8014D370, -1, 0, 1, 0);
    lbl_8063D578->_080[22] =
        fn_80253C38(lbl_8063D578->_000[22], 0, (void *)fn_8014C3EC, (void *)fn_8014C50C, -1, 0, 1, 0);
    lbl_8063D578->_080[25] =
        fn_80253C38(lbl_8063D578->_000[25], 0, (void *)fn_8014D8EC, (void *)fn_8014D9E4, -1, 0, 1, 0);
    lbl_8063D578->_080[26] =
        fn_80253C38(lbl_8063D578->_000[26], 0, (void *)fn_8014DA84, (void *)fn_8014DC54, -1, 0, 1, 0);
    lbl_8063D578->_080[27] =
        fn_80253C38(lbl_8063D578->_000[27], 0, (void *)fn_8014DCF4, (void *)fn_8014E050, -1, 0, 1, 0);
    lbl_8063D578->_080[28] =
        fn_80253C38(lbl_8063D578->_000[28], 0, (void *)fn_8014E054, (void *)fn_8014E0E8, -1, 0, 1, 0);
    lbl_8063D578->_080[29] =
        fn_80253C38(lbl_8063D578->_000[29], 0, (void *)fn_8014E1EC, (void *)fn_8014E2B4, -1, 0, 1, 0);
    lbl_8063D578->_080[31] =
        fn_80253C38(lbl_8063D578->_000[31], (void *)fn_8014E6C0, (void *)fn_8014E730, (void *)fn_8014E79C, -1, 0, 1, 0);
    lbl_8063D578->_080[6] =
        fn_80253C38(lbl_8063D578->_000[6], 0, (void *)fn_80149970, (void *)fn_8014999C, -1, 0, 1, 0);
    fn_80253DF0(lbl_8063D578->_080[6], 9, 2);
    fn_80253E10(lbl_8063D578->_080[25], lbl_80641410, 4);
    lbl_8063D578->_0c0 = fn_80253F6C(0, (void *)fn_80149234, -1);
    GSfsys::fn_80249890(0x404);
    GScache::freeFsysCacheEntries(0x404);
    fn_800576B0();
    lbl_8063D578->_d30 &= ~0x200000;
    lbl_8063D578->_d30 &= ~0x100000;
    lbl_8063D578->_d30 &= ~0x80000;
    switch (fn_80162A90(0x25e)) {
        case 1:
            lbl_8063D578->_0c4 = 1;
            lbl_8063D578->_0c6 = 0;
            memset(lbl_8063D578->_d28->_c608[2], 0, 0x6ec);
            memset(lbl_8063D578->_d28->_c608[1], 0, 0x6ec);
            memset(lbl_8063D578->_d28->_c608[0], 0, 0x6ec);
            lbl_8063D578->_d30 &= ~0x10000000;
            fn_80162FD4();
            break;
        case 2: lbl_8063D578->_0c4 = 0xa6; break;
        case 5:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_0c4 = 0x18;
            } else {
                lbl_8063D578->_0c4 = 0x29;
            }
            break;
        case 6:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_0c4 = 0x22;
            } else {
                lbl_8063D578->_0c4 = 0x29;
            }
            break;
        case 7:
            lbl_8063D578->_0c4 = 0x22;
            lbl_8063D578->_0c6 = 5;
            lbl_8063D578->_dda = 0;
            break;
        case 8:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_d30 |= 0x8000;
                lbl_8063D578->_0c4 = 0x6c;
            } else {
                lbl_8063D578->_0c4 = 0x77;
            }
            break;
        case 9:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_0c4 = 0x70;
            } else {
                lbl_8063D578->_0c4 = 0x77;
            }
            break;
        case 10:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_0c4 = 0x5c;
            } else {
                lbl_8063D578->_0c4 = 0x81;
            }
            break;
        case 11:
            if (fn_80162A90(0x262) == 0) {
                lbl_8063D578->_0c4 = 0x7a;
            } else {
                lbl_8063D578->_0c4 = 0x81;
            }
            break;
        case 12:
            fn_8016532C();
            fn_8014F214();
            lbl_8063D578->_0c6 = 5;
            lbl_8063D578->_0c4 = 0x50;
            lbl_8063D578->_ddb = 0;
            lbl_8063D578->_dda = ((lbl_8063D578->_d30 >> 25) & 1) ? 2 : 0;
            break;
        case 13: break;
    }
    fn_800579FC(3);
    lbl_8063D578->_d30 &= ~0x80000000;
    fn_800562BC();
    fn_80162940(0x261, 4, 1);
    fn_800563EC(0xe, 0);
    lbl_8063D578->_d30 &= ~0x08000000;
}
#pragma dont_inline reset

// TODO Frees the layouts of the screen and its archive.
void fn_8013FFB8() {
    u32 i;
    for (i = 0; i < 0x20; i++) {
        if (lbl_8063D578->_000[(u16)i] != 0) {
            fn_80253CCC(lbl_8063D578->_080[(u16)i]);
            fn_80055E30(lbl_8063D578->_000[(u16)i]);
            (lbl_8063D578->_080[(u16)i]) = -1;
            lbl_8063D578->_000[(u16)i] = 0;
        }
    }
    fn_80253F8C(lbl_8063D578->_0c0);
    lbl_8063D578->_0c0 = -1;
    GSfsys::fn_80249890(0x405);
    GScache::freeFsysCacheEntries(0x405);
}

// TODO Updates the timed states 0xA4 and 0xA5 of the screen.
void fn_80149234() {
    Unk8063D578 *g;
    switch (lbl_8063D578->_0c4) {
        case 0xa4:
            fn_8000B170(0x222, 0, lbl_80641414);
            lbl_8063D578->_ef4 = &lbl_8063D578->_d28->_21f8[lbl_8063D578->_d4a * 0x8c];
            fn_801558F0(lbl_8063D578->_ef0, lbl_8063D578->_ef4);
            g = lbl_8063D578;
            g->_d38 = fn_8015F7A0();
            g->_0c4 = 0xa5;
            break;
        case 0xa5:
            fn_801558F0(lbl_8063D578->_ef0, lbl_8063D578->_ef4);
            g = lbl_8063D578;
            if (fn_8015F7A0() - g->_d38 >= lbl_80641430) {
                if (fn_8015F7A0() - g->_d38 >= lbl_80641438) {
                    g->_0c4 = 0x9d;
                }
                if (fn_80059A6C(0x80, 0, 0, 1) == 0x80000000) {
                    lbl_8063D578->_0c4 = 0x9d;
                }
            }
            break;
    }
}

// TODO First element callback of layout 0; reads the element id and does nothing else.
void fn_80149348(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 0; reads the element id and does nothing else.
void fn_80149374(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO First element callback of layout 1; sets the texts of its elements or dims them.
void fn_801493A0(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 1: {
            int id = 0;
            switch (lbl_8063D578->_0d4) {
                case 1: id = 0x50be; break;
                case 2: id = 0x50bf; break;
                case 3: id = 0x50c1; break;
            }
            fn_80253EB4(a, b, 2, id);
            break;
        }
        case 9:
        case 10:
        case 13:
        case 14: fn_80253EB4(a, b, 2, 0); break;
        case 16: fn_80253EB4(a, b, 2, 0x50c0); break;
    }
}

// TODO Second element callback of layout 1; draws the texts and icons of its elements.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_80149488(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 4:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 5:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(2, buf);
            break;
        case 6:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(3, buf);
            break;
        case 10: fn_8014FC0C(a, (Unk8014FC0C *)b, 0x50bc); break;
        case 14: fn_8014FC0C(a, (Unk8014FC0C *)b, 0x50bd); break;
        case 9:  fn_8014FC0C(a, (Unk8014FC0C *)b, 0x51de); break;
        case 13: fn_8014FC0C(a, (Unk8014FC0C *)b, 0x51de); break;
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 2; sets the texts of its elements or dims them.
void fn_801495A8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 5: fn_80253EB4(a, b, 2, 0x50c4); break;
        case 8: fn_80253EB4(a, b, 2, 0x50c5); break;
    }
}

// TODO Second element callback of layout 2; draws the texts and icons of its elements.
void fn_80149630(s16 a, int b) {
    int v;
    Unk80149630 buf;
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 1:
            fn_80253EDC(a, b, 6, &buf);
            fn_80059A3C(1, &buf);
            break;
        case 2:
            fn_80253EDC(a, b, 6, &buf);
            fn_80059A3C(2, &buf);
            break;
        case 4:
            fn_80253EDC(a, b, 6, &buf);
            fn_800E71B0(0, buf._00);
            break;
    }
}

// TODO First element callback of layout 3; sets the texts of its elements or dims them.
void fn_80149744(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 5: fn_80253EB4(a, b, 2, 0x50e8); break;
        case 7: fn_80253EB4(a, b, 2, 0x50e9); break;
        case 9: fn_80253EB4(a, b, 2, 0x50ea); break;
    }
}

// TODO Second element callback of layout 3; draws the texts and icons of its elements.
void fn_801497F0(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 2:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(2, buf);
            break;
        case 3:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(3, buf);
            break;
    }
}

// TODO First element callback of layout 4; reads the element id and does nothing else.
void fn_801498C0(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 4; reads the element id and does nothing else.
void fn_801498EC(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO First element callback of layout 5; reads the element id and does nothing else.
void fn_80149918(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 5; reads the element id and does nothing else.
void fn_80149944(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO First element callback of layout 6; reads the element id and does nothing else.
void fn_80149970(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO First element callback of layout 7; sets the texts of its elements or dims them.
void fn_80149C0C(s16 a, u8 *b) {
    int v;
    u16 idx = 0xffff;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 15:
            if (lbl_8063D578->_0fc < 2) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 20:
            if (lbl_8063D578->_0fc < 3) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 25:
            if (lbl_8063D578->_0fc < 4) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 9:  idx = lbl_8063D578->_0f8 - 1; break;
        case 14: idx = lbl_8063D578->_0f8; break;
        case 19: idx = lbl_8063D578->_0f8 + 1; break;
        case 24: idx = lbl_8063D578->_0f8 + 2; break;
        case 29: idx = lbl_8063D578->_0f8 + 3; break;
    }
    if (idx < lbl_8063D578->_0fc) {
        if (lbl_8063D578->_c68[idx] != 4) {
            fn_80253EB4(a, (int)b, 1, 0);
        }
    } else if (idx < 4) {
        fn_80253EB4(a, (int)b, 1, 0);
    }
    Unk8063D578 *g = lbl_8063D578;
    if (g->_0f8 != g->_0fa && g->_100 == fn_80253DE0(a)) {
        lbl_8063D578->_0f8 = lbl_8063D578->_0fa;
    }
}

// TODO Second element callback of layout 7; draws the texts and icons of its elements.
void fn_80149E18(s16 a, Unk8014FC0C *b) {
    u32 color;
    int x;
    int y;
    s16 w;
    s16 h;
    u16 idxA = 0xffff;
    u16 idxB = idxA;
    u16 idxC = idxA;
    int flag = 0;
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    x = buf[0];
    y = buf[4];
    w = buf[1] - buf[0];
    h = buf[6] - buf[4];
    color = b->_11 | 0xFFFFFF00;
    switch ((u32)v) {
        case 1:  fn_80059A3C(1, buf); break;
        case 2:  fn_80059A3C(2, buf); break;
        case 3:  fn_80059A3C(3, buf); break;
        case 4:  fn_80059A3C(4, buf); break;
        case 7:  idxA = lbl_8063D578->_0f8 - 1; break;
        case 12: idxA = lbl_8063D578->_0f8; break;
        case 17: idxA = lbl_8063D578->_0f8 + 1; break;
        case 22: idxA = lbl_8063D578->_0f8 + 2; break;
        case 27: idxA = lbl_8063D578->_0f8 + 3; break;
        case 6:
            flag = 1;
            idxB = lbl_8063D578->_0f8 - 1;
            break;
        case 11:
            flag = 1;
            idxB = lbl_8063D578->_0f8;
            break;
        case 16:
            flag = 1;
            idxB = lbl_8063D578->_0f8 + 1;
            break;
        case 21:
            flag = 1;
            idxB = lbl_8063D578->_0f8 + 2;
            break;
        case 26:
            flag = 1;
            idxB = lbl_8063D578->_0f8 + 3;
            break;
        case 8:  idxC = lbl_8063D578->_0f8 - 1; break;
        case 13: idxC = lbl_8063D578->_0f8; break;
        case 18: idxC = lbl_8063D578->_0f8 + 1; break;
        case 23: idxC = lbl_8063D578->_0f8 + 2; break;
        case 28: idxC = lbl_8063D578->_0f8 + 3; break;
    }
    if (idxA < (lbl_8063D578->_0fc)) {
        if (lbl_8063D578->_104[idxA] == 0) {
            fn_80250134(0x50f0, x, y, w, h, color);
        } else {
            fn_8015C308(0xe, lbl_8063D578->_17c[idxA]);
            fn_80250134(0x50d2, x, y, w, h, color);
        }
    }
    if (flag && idxB >= lbl_8063D578->_0fc) {
        fn_80253F04(a, (int)b, 2, 0);
    }
    if (idxC < (lbl_8063D578->_0fc)) {
        switch (lbl_8063D578->_c68[idxC]) {
            case 0: fn_80250134(0x51a1, x, y, w, h, color); break;
            case 1: fn_80250134(0x50ac, x, y, w, h, color); break;
            case 2:
            case 3: fn_80250134(0x50af, x, y, w, h, color); break;
            case 4: fn_80250134(0x50ad, x, y, w, h, color); break;
            case 5: fn_80250134(0x50ae, x, y, w, h, color); break;
        }
    }
}

// TODO First element callback of layout 8; sets the texts of its elements or dims them.
void fn_8014A1E8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 10:
            if (((lbl_8063D578->_d30 >> 25) & 1)) {
                fn_80253EB4(a, b, 2, 0x51a2);
            } else {
                fn_80253EB4(a, b, 2, 0x51a3);
            }
            break;
        case 5:
            if (((lbl_8063D578->_d30 >> 25) & 1)) {
                fn_80253EB4(a, b, 2, 0x50d1);
            } else {
                fn_80253EB4(a, b, 2, 0x50d0);
            }
            break;
    }
}

// TODO Second element callback of layout 8; draws the texts and icons of its elements.
void fn_8014A2C0(s16 a, Unk8014FC0C *b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    u32 color;
    int x = buf[0];
    int y = buf[4];
    s16 w = buf[1] - buf[0];
    s16 h = buf[6] - buf[4];
    color = b->_11 | 0xFFFFFF00;
    switch ((u32)v) {
        case 1:
            fn_8015C308(8, lbl_8063D578->_0fc);
            fn_80250134(0x3ed, x, y, w, h, color);
            break;
        case 3: fn_80059A3C(5, buf); break;
        case 9:
            fn_8015C308(0xe, (int)lbl_8063D578->_d24->_00010);
            fn_80250134(0x50da, x, y, w, h, color);
            break;
        case 6:
            if (lbl_8063D578->_d21 != 1) {
                int id = 0;
                switch (lbl_8063D578->_d1c) {
                    case 0: id = 0x50b1; break;
                    case 1: id = 0x50b0; break;
                    case 4: id = 0x50b2; break;
                }
                if (id != 0) {
                    fn_8015C308(0xe, lbl_8063D578->_17c[lbl_8063D578->_d20]);
                    fn_8015C308(0x10, fn_802502F4(id));
                    fn_80250134(0x50dc, x + lbl_8063D578->_d22, y, w, h, color);
                }
                if (!GSrender::sInstance->_unkCondition1()) {
                    lbl_8063D578->_d22 -= 3;
                }
                if (lbl_8063D578->_d22 < -0x352) {
                    lbl_8063D578->_d22 = 0x352;
                    lbl_8063D578->_d21++;
                }
            }
            break;
    }
}

// TODO First element callback of layout 10; sets the texts of its elements or dims them.
void fn_8014A510(s16 a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 3:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] == 4) {
                fn_80253EB4(a, (int)b, 2, 0x50df);
            }
            break;
        case 8:
            fn_80253EB4(a, (int)b, 2, 0x50de);
            switch (lbl_8063D578->_c68[lbl_8063D578->_d49]) {
                case 0: fn_80253EB4(a, (int)b, 2, 0x51a1); break;
                case 1: fn_80253EB4(a, (int)b, 2, 0x50ac); break;
                case 2:
                case 3: fn_80253EB4(a, (int)b, 2, 0x50af); break;
                case 4: fn_80253EB4(a, (int)b, 2, 0x50ad); break;
                case 5: fn_80253EB4(a, (int)b, 2, 0x50ae); break;
            }
            break;
        case 6:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] == 4) {
                if (lbl_8063D578->_470[lbl_8063D578->_d49]._08 == 2) {
                    fn_80253EB4(a, (int)b, 2, 0x50b3);
                } else {
                    fn_80253EB4(a, (int)b, 2, 0x50b4);
                }
            }
            break;
        case 11:
        case 13:
        case 14:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] != 4) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
    }
}

// TODO Second element callback of layout 10; draws the texts and icons of its elements.
void fn_8014A71C(s16 a, Unk8014FC0C *b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    fn_80253EDC(a, (int)b, 6, buf);
    u32 color;
    int x = buf[0];
    int y = buf[4];
    s16 w = buf[1] - buf[0];
    s16 h = buf[6] - buf[4];
    color = b->_11 | 0xFFFFFF00;
    switch ((u32)v) {
        case 12:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] != 4) {
                color = b->_11 | 0x7f7f7f00;
            }
            fn_80250134(0x50e3, x, y, w, h, color);
            break;
        case 15:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] != 4) {
                color = b->_11 | 0x7f7f7f00;
            }
            fn_80250134(0x50e4, x, y, w, h, color);
            break;
        case 1:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] != 4) {
                buf[7] = lbl_80641440;
                buf[6] = lbl_80641440;
                buf[5] = lbl_80641440;
                buf[4] = lbl_80641440;
                buf[3] = lbl_80641440;
                buf[2] = lbl_80641440;
                buf[1] = lbl_80641440;
                buf[0] = lbl_80641440;
            }
            fn_80059A3C(1, buf);
            break;
        case 2:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] != 4) {
                buf[7] = lbl_80641440;
                buf[6] = lbl_80641440;
                buf[5] = lbl_80641440;
                buf[4] = lbl_80641440;
                buf[3] = lbl_80641440;
                buf[2] = lbl_80641440;
                buf[1] = lbl_80641440;
                buf[0] = lbl_80641440;
            }
            fn_80059A3C(2, buf);
            break;
        case 4:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] == 4) {
                int id;
                memset(lbl_8063D578->_efe, 0, 0x28);
                switch (lbl_8063D578->_470[lbl_8063D578->_d49]._1a) {
                    case 0: id = 0x3069; break;
                    case 1: id = 0x306a; break;
                    case 2: id = 0x306b; break;
                    default:
                        fn_8015C308(0xf, (int)lbl_8063D578->_470[lbl_8063D578->_d49]._1c);
                        id = 0x3f9;
                        break;
                }
                fn_802503D8(id, lbl_8063D578->_efe);
                fn_8015C308(0xe, (int)(lbl_8063D578->_efe));
                fn_80250134(0x50dd, x, y, w, h, color);
            }
            break;
        case 5:
            if (lbl_8063D578->_c68[lbl_8063D578->_d49] == 4) {
                int saved = lbl_8063D578->_d28->_0010;
                lbl_8063D578->_d28->_0010 = lbl_8063D578->_470[lbl_8063D578->_d49]._04;
                fn_8014F164();
                fn_80250134(0x50dd, x, y, w, h, color);
                lbl_8063D578->_d28->_0010 = saved;
            }
            break;
        case 7:
            if (lbl_8063D578->_104[lbl_8063D578->_d49] == 0) {
                fn_80250134(0x50f0, x, y, w, h, color);
            } else {
                fn_8015C308(0xe, lbl_8063D578->_17c[lbl_8063D578->_d49]);
                fn_80250134(0x50dd, x, y, w, h, color);
            }
            break;
    }
}

// TODO First element callback of layout 11; sets the texts of its elements or dims them.
void fn_8014AAA4(s16 a, int b) {
    u32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (lbl_8063D578->_d40) {
        case 1:
            if (v == 7) {
                fn_80253EB4(a, b, 2, 0x510c);
                break;
            }
        case 0:
            switch (v) {
                case 3: fn_80253EB4(a, b, 2, 0x510a); break;
                case 9: fn_80253EB4(a, b, 2, 0x50ab); break;
            }
            break;
    }
}

// TODO Second element callback of layout 11; draws the texts and icons of its elements.
void fn_8014AB70(int a, Unk8014FC0C *b) {
    u32 v;
    fn_80253EDC(a, (int)b, 3, &v);
    switch (lbl_8063D578->_d40) {
        case 0:
            if (v == 5) {
                Unk8063D578 *g = lbl_8063D578;
                GXColor col;
                u16 arr[15];
                col.r = 0xff;
                col.g = 0xff;
                col.b = 0xff;
                col.a = b->_11;
                for (int i = 0; i < 4; i++) {
                    arr[i] = g->_0d8[i];
                    arr[i + 5] = g->_0d8[i + 4];
                    arr[i + 10] = g->_0d8[i + 8];
                }
                arr[4] = 0x2d;
                arr[9] = 0x2d;
                arr[14] = 0;
                fn_8015C308(0xe, (int)arr);
                fn_802504A0(0x510b, 0x140, 0xe6, col, 0x84, lbl_80641444);
            }
            break;
    }
}

// TODO First element callback of layout 12; sets the texts of its elements or dims them.
void fn_8014AC84(s16 a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 9:  fn_80253EB4(a, (int)b, 2, 0x50fb); break;
        case 10: fn_80253EB4(a, (int)b, 2, 0x50fc); break;
        case 12: fn_80253EB4(a, (int)b, 2, 0x50fd); break;
        case 14: fn_80253EB4(a, (int)b, 2, 0x50fe); break;
        case 16: fn_80253EB4(a, (int)b, 2, 0x50ff); break;
        case 18: fn_80253EB4(a, (int)b, 2, 0x5100); break;
        case 20: fn_80253EB4(a, (int)b, 2, 0x5101); break;
        case 6:
            if (lbl_8063D578->_d48 == 0) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 7:
            if (lbl_8063D578->_d48 == lbl_8063D578->_0fc - 1) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
    }
}

// TODO First element callback of layout 13; sets the texts of its elements or dims them.
void fn_8014B41C(s16 a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 4: fn_80253EB4(a, (int)b, 2, 0x50e7); break;
        case 2: fn_80253EB4(a, (int)b, 1, 0); break;
        case 9:
            if (lbl_8063D578->_0fc < 1) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 13:
            if (lbl_8063D578->_0fc < 2) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 17:
            if (lbl_8063D578->_0fc < 3) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 21:
            if (lbl_8063D578->_0fc < 4) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 25:
            if (lbl_8063D578->_0fc < 5) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 29:
            if (lbl_8063D578->_0fc < 6) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
    }
    Unk8063D578 *g = lbl_8063D578;
    if (g->_0f8 != g->_0fa && g->_100 == fn_80253DE0(a)) {
        lbl_8063D578->_0f8 = lbl_8063D578->_0fa;
    }
}

// TODO Second element callback of layout 13; draws the texts and icons of its elements.
// TODO Does not match yet (same size; the rectangle values get other registers).
void fn_8014B634(s16 a, Unk8014FC0C *b) {
    u16 idxA = 0xffff;
    u16 idxB = idxA;
    u16 idxC = idxA;
    u32 v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
        case 2: {
            u32 color;
            int x;
            int y;
            s16 w;
            s16 h;
            fn_80253EDC(a, (int)b, 6, buf);
            x = buf[0];
            y = buf[4];
            w = buf[1] - buf[0];
            h = buf[6] - buf[4];
            color = b->_11 | 0xFFFFFF00;
            if (lbl_8063D578->_0fc != 0) {
                fn_8015C308(0x1b, lbl_8063D578->_0f8 + lbl_8063D578->_102);
            } else {
                fn_8015C308(0x1b, 0);
            }
            fn_8015C308(0x1c, lbl_8063D578->_0fc);
            fn_80250134(0x43e3, x, y, w, h, color);
            break;
        }
        case 33:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 34:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(2, buf);
            break;
        case 35:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(3, buf);
            break;
        case 36:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(4, buf);
            break;
        case 37:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(5, buf);
            break;
        case 38:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(6, buf);
            break;
        case 6:  idxA = lbl_8063D578->_0f8 - 1; break;
        case 10: idxA = lbl_8063D578->_0f8; break;
        case 14: idxA = lbl_8063D578->_0f8 + 1; break;
        case 18: idxA = lbl_8063D578->_0f8 + 2; break;
        case 22: idxA = lbl_8063D578->_0f8 + 3; break;
        case 26: idxA = lbl_8063D578->_0f8 + 4; break;
        case 30: idxA = lbl_8063D578->_0f8 + 5; break;
        case 7:  idxB = lbl_8063D578->_0f8 - 1; break;
        case 11: idxB = lbl_8063D578->_0f8; break;
        case 15: idxB = lbl_8063D578->_0f8 + 1; break;
        case 19: idxB = lbl_8063D578->_0f8 + 2; break;
        case 23: idxB = lbl_8063D578->_0f8 + 3; break;
        case 27: idxB = lbl_8063D578->_0f8 + 4; break;
        case 31: idxB = lbl_8063D578->_0f8 + 5; break;
        case 8:  idxC = lbl_8063D578->_0f8 - 1; break;
        case 12: idxC = lbl_8063D578->_0f8; break;
        case 16: idxC = lbl_8063D578->_0f8 + 1; break;
        case 20: idxC = lbl_8063D578->_0f8 + 2; break;
        case 24: idxC = lbl_8063D578->_0f8 + 3; break;
        case 28: idxC = lbl_8063D578->_0f8 + 4; break;
        case 32: idxC = lbl_8063D578->_0f8 + 5; break;
    }
    if (idxA < (lbl_8063D578->_0fc)) {
        u32 color;
        int x;
        int y;
        s16 w;
        s16 h;
        color = b->_11 | 0xFFFFFF00;
        if (lbl_8063D578->_104[idxA] == 0) {
            color = b->_11 | 0xffcf5f00;
        }
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        fn_8015CC78(idxA + 1, 2, 0xe, 1);
        fn_80250134(0x50ec, x, y, w, h, color);
        fn_80250134(0x50ed, x + 0x26, y, w, h, color);
    }
    if (idxB < (lbl_8063D578->_0fc)) {
        int x;
        int y;
        s16 w;
        s16 h;
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        u8 c = b->_11;
        if (lbl_8063D578->_104[idxB] == 0) {
            fn_80250134(0x50f0, x, y, w, h, c | 0xffcf5f00);
        } else {
            fn_8015C308(0xe, lbl_8063D578->_17c[idxB]);
            fn_80250134(0x50ee, x, y, w, h, c | 0xFFFFFF00);
        }
    }
    if (idxC < (lbl_8063D578->_0fc)) {
        u32 color;
        int x;
        int y;
        s16 w;
        s16 h;
        fn_80253EDC(a, (int)b, 6, buf);
        x = buf[0];
        y = buf[4];
        w = buf[1] - buf[0];
        h = buf[6] - buf[4];
        u8 c = b->_11;
        if (lbl_8063D578->_104[idxC] == 0) {
            fn_80250134(0x50f8, x, y, w, h, c | 0xffcf5f00);
        } else {
            color = c | 0xFFFFFF00;
            if (lbl_8063D578->_1f4[idxC] == 0) {
                fn_80250134(0x50f9, x, y, w, h, color);
            } else {
                fn_8015C308(0x18, lbl_8063D578->_1f4[idxC]);
                fn_80250134(0x50ef, x, y, w, h, color);
            }
        }
    }
}

// TODO First element callback of layout 14; reads the element id and does nothing else.
void fn_8014BCA0(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 14; reads the element id and does nothing else.
void fn_8014BCCC(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO First element callback of layout 15; reads the element id and does nothing else.
void fn_8014BCF8(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 15; reads the element id and does nothing else.
void fn_8014BD24(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO First element callback of layout 16; reads the element id and does nothing else.
void fn_8014BD50(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 16; reads the element id and does nothing else.
void fn_8014BD7C(s16 a, int b) {
    u8 buf[8];
    fn_80253EDC(a, b, 3, buf);
}

// TODO Update callback of layout 17.
void fn_8014BDA8(s16 a) {
    fn_80253E10(a, lbl_8064144C, 4);
}

// TODO First element callback of layout 17; sets the texts of its elements or dims them.
void fn_8014BDB8(s16 a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 3:
            b[2] >>= 2;
            b[3] >>= 2;
            b[4] >>= 2;
            break;
        case 4: fn_80253EB4(a, (int)b, 2, 0x3141); break;
        case 5: fn_80253EB4(a, (int)b, 2, 0x2a34); break;
        case 7: fn_80253EB4(a, (int)b, 2, 0x2a32); break;
        case 8:
            if (lbl_8063D578->_d45 == 1) {
                fn_80253EB4(a, (int)b, 2, 0x4636);
            } else {
                fn_80253EB4(a, (int)b, 2, 0x4637);
            }
            break;
        case 11: fn_80253EB4(a, (int)b, 2, 0x2a36); break;
    }
}

// TODO Second element callback of layout 17; draws the texts and icons of its elements.
void fn_8014BEE4(s16 a, Unk8014FC0C *b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
        case 1:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(2, buf);
            break;
        case 2:
            fn_80253EDC(a, (int)b, 6, buf);
            fn_80059A3C(3, buf);
            break;
        case 14: {
            int id = 0;
            fn_80253EDC(a, (int)b, 6, buf);
            int x = buf[0] - lbl_80641450;
            int y = buf[4] - lbl_80641454;
            s16 w = buf[1] - buf[0];
            s16 h = buf[6] - buf[4];
            u32 color = b->_11 | 0xFFFFFF00;
            switch (lbl_8063D578->_0d4) {
                case 1:    id = 0x521b; break;
                case 2:    id = 0x2a38; break;
                case 3:    id = 0x521c; break;
                case 0x63: id = 0x2a57; break;
            }
            if (id != 0) {
                fn_80250134(id, x, y, w, h, color);
            }
            break;
        }
    }
}

// TODO First element callback of layout 18; does nothing.
void fn_8014C074() {}

// TODO First element callback of layout 19; sets the texts of its elements or dims them.
void fn_8014C2B8(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 3: fn_80253EB4(a, b, 2, 0x2a40); break;
        case 4: break;
        case 5: fn_80253EB4(a, b, 2, 0x2a41); break;
    }
}

// TODO Second element callback of layout 19; draws the texts and icons of its elements.
void fn_8014C34C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(2, buf);
            break;
    }
}

// TODO First element callback of layout 22; sets the texts of its elements or dims them.
void fn_8014C3EC(s16 a, u8 *b) {
    u8 *tmp;
    int v;
    u8 *p;
    int id = 0;
    fn_80253E8C(a, (int)b, 3, &v);
    fn_80253E8C(a, (int)b, 5, &tmp);
    p = tmp;
    switch (v) {
        case 6:
            id = 0x4646;
            *(u8 **)p = lbl_80487250;
            break;
        case 8:
            id = 0x4647;
            *(u8 **)p = lbl_80487278;
            break;
        case 4: fn_80253EB4(a, (int)b, 2, 0x5237); break;
    }
    if (id != 0) {
        fn_802503D8(id, *(void **)p);
        p[4] = b[2];
        p[5] = b[3];
        p[6] = b[4];
        p[7] = b[5];
        p[9] = 0x84;
        fn_80253EB4(a, (int)b, 2, -2);
    }
}

// TODO Second element callback of layout 22; draws the texts and icons of its elements.
void fn_8014C50C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    fn_80253EDC(a, b, 6, buf);
    switch (v) {
        case 1: fn_80059A3C(0x3d, buf); break;
        case 2: fn_80059A3C(0x3e, buf); break;
    }
}

// TODO Update callback of layout 23.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014C598(s16 a) {
    int v;
    fn_80253E4C(a, 8, &v);
    if (v != 0 && fn_80253DD0(a) == 3) {
        switch (fn_80253DE0(a)) {
            case 6:  fn_80253DB0(a, 0, 0); break;
            case 7:  fn_80253DB0(a, 1, 0); break;
            case 8:  fn_80253DB0(a, 2, 0); break;
            case 9:  fn_80253DB0(a, 3, 0); break;
            case 10: fn_80253DB0(a, 4, 0); break;
            case 11: fn_80253DB0(a, 5, 0); break;
        }
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 23; sets the names and the order numbers of the selected entries.
void fn_8014C6A0(s16 a, int b) {
    u32 v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 2: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[0]]); break;
        case 3: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[1]]); break;
        case 4: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[2]]); break;
        case 5: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[3]]); break;
        case 6: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[4]]); break;
        case 7: fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_edc[5]]); break;
        case 45:
            if (lbl_8063D578->_df1[0] == 0 || lbl_8063D578->_df1[0] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 46:
            if (lbl_8063D578->_df1[1] == 0 || lbl_8063D578->_df1[1] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 47:
            if (lbl_8063D578->_df1[2] == 0 || lbl_8063D578->_df1[2] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 48:
            if (lbl_8063D578->_df1[3] == 0 || lbl_8063D578->_df1[3] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 49:
            if (lbl_8063D578->_df1[4] == 0 || lbl_8063D578->_df1[4] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 50:
            if (lbl_8063D578->_df1[5] == 0 || lbl_8063D578->_df1[5] == 7) {
                fn_80253EB4(a, b, 1, 0);
            }
            break;
        case 57: {
            int id = 0;
            switch (lbl_8063D578->_df1[6]) {
                case 0:
                case 1:
                    switch (lbl_8063D578->_df1[lbl_8063D578->_d4a]) {
                        case 0:  id = 0x2a68; break;
                        case 7:  id = 0; break;
                        default: id = 0x2a69; break;
                    }
                    break;
            }
            fn_80253EB4(a, b, 2, id);
            break;
        }
        case 58:
            switch (lbl_8063D578->_df1[6]) {
                case 0:
                case 1:
                    switch (lbl_8063D578->_efa) {
                        case 0: fn_80253EB4(a, b, 1, fn_8005A9F8(0x3d)); break;
                        case 1: fn_80253EB4(a, b, 1, fn_8005A9F8(0x3e)); break;
                        case 2: fn_80253EB4(a, b, 1, fn_8005A9F8(0x3c)); break;
                    }
                    break;
            }
            break;
        case 59:
            if (lbl_8063D578->_df1[6] == 1) {
                fn_80253EB4(a, b, 2, 0x2a6b);
            }
            break;
        case 60:
            if (lbl_8063D578->_df1[6] == 1) {
                switch (lbl_8063D578->_efa) {
                    case 0:  fn_80253EB4(a, b, 1, fn_8005A9F8(0x3e)); break;
                    case 1:  fn_80253EB4(a, b, 1, fn_8005A9F8(0x3d)); break;
                    default: fn_80253EB4(a, b, 1, fn_8005A9F8(0x3b)); break;
                }
            }
            break;
        case 12: {
            u8 c = lbl_8063D578->_df1[0];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 18: {
            u8 c = lbl_8063D578->_df1[1];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 24: {
            u8 c = lbl_8063D578->_df1[2];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 30: {
            u8 c = lbl_8063D578->_df1[3];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 36: {
            u8 c = lbl_8063D578->_df1[4];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 42: {
            u8 c = lbl_8063D578->_df1[5];
            if (c != 0 && c != 7) {
                fn_80253EB4(a, b, 1, fn_8005AC60(0x405, lbl_8041DC78[c - 1]));
            }
            break;
        }
        case 14: fn_8005B294(a, b, lbl_8063D578->_e8c[0]); break;
        case 20: fn_8005B294(a, b, lbl_8063D578->_e8c[1]); break;
        case 26: fn_8005B294(a, b, lbl_8063D578->_e8c[2]); break;
        case 32: fn_8005B294(a, b, lbl_8063D578->_e8c[3]); break;
        case 38: fn_8005B294(a, b, lbl_8063D578->_e8c[4]); break;
        case 44: fn_8005B294(a, b, lbl_8063D578->_e8c[5]); break;
    }
}

// TODO Second element callback of layout 23; moves and draws the entries and their icons.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014CD2C(s16 a, Unk8014FC0C *b) {
    u8 c;
    u32 color;
    int x;
    int y;
    s16 w;
    s16 h;
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
        case 14:
        case 20:
        case 26:
        case 32:
        case 38:
        case 44:
            b->_38 -= lbl_80641460;
            b->_44 -= lbl_80641460;
            b->_3c -= lbl_80641464;
            b->_40 -= lbl_80641464;
            b->_48 += lbl_80641468;
            b->_4c += lbl_80641468;
            break;
    }
    fn_80253EDC(a, (int)b, 6, buf);
    x = buf[0];
    y = buf[4];
    w = buf[1] - buf[0];
    h = buf[6] - buf[4];
    c = b->_11;
    color = c | 0xFFFFFF00;
    if (fn_8014E980(0x16)) {
        switch (v) {
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 56: return;
        }
    }
    switch (v) {
        case 57:
            b->_38 += lbl_8064146C;
            b->_3c += lbl_8064146C;
            b->_40 += lbl_8064146C;
            b->_44 += lbl_8064146C;
            break;
        case 8:
            fn_8015C308(0xf, (int)lbl_8063D578->_ebc[6]);
            fn_80250134(0x3f9, x, y, w, h, color);
            break;
        case 10: fn_8012D530(lbl_8063D578->_e8c[0], buf, c); break;
        case 16: fn_8012D530(lbl_8063D578->_e8c[1], buf, c); break;
        case 22: fn_8012D530(lbl_8063D578->_e8c[2], buf, c); break;
        case 28: fn_8012D530(lbl_8063D578->_e8c[3], buf, c); break;
        case 34: fn_8012D530(lbl_8063D578->_e8c[4], buf, c); break;
        case 40: fn_8012D530(lbl_8063D578->_e8c[5], buf, c); break;
        case 11: fn_8012D640(lbl_8063D578->_e8c[0], buf, c, 1); break;
        case 17: fn_8012D640(lbl_8063D578->_e8c[1], buf, c, 1); break;
        case 23: fn_8012D640(lbl_8063D578->_e8c[2], buf, c, 1); break;
        case 29: fn_8012D640(lbl_8063D578->_e8c[3], buf, c, 1); break;
        case 35: fn_8012D640(lbl_8063D578->_e8c[4], buf, c, 1); break;
        case 41: fn_8012D640(lbl_8063D578->_e8c[5], buf, c, 1); break;
        case 13: fn_8005B328(a, b, lbl_8063D578->_e8c[0], 0); break;
        case 19: fn_8005B328(a, b, lbl_8063D578->_e8c[1], 0); break;
        case 25: fn_8005B328(a, b, lbl_8063D578->_e8c[2], 0); break;
        case 31: fn_8005B328(a, b, lbl_8063D578->_e8c[3], 0); break;
        case 37: fn_8005B328(a, b, lbl_8063D578->_e8c[4], 0); break;
        case 43: fn_8005B328(a, b, lbl_8063D578->_e8c[5], 0); break;
        case 51: fn_80059A3C(0x33, buf); break;
        case 52: fn_80059A3C(0x34, buf); break;
        case 53: fn_80059A3C(0x35, buf); break;
        case 54: fn_80059A3C(0x36, buf); break;
        case 55: fn_80059A3C(0x37, buf); break;
        case 56: fn_80059A3C(0x38, buf); break;
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 24; sets the texts of its elements or dims them.
void fn_8014D148(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 2:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[0]]); break;
        case 3:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[1]]); break;
        case 4:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[2]]); break;
        case 5:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[3]]); break;
        case 6:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[4]]); break;
        case 7:  fn_80253EB4(a, b, 1, lbl_8063D578->_ee8[lbl_8063D578->_ee2[5]]); break;
        case 45:
        case 46:
        case 47:
        case 48:
        case 49:
        case 50: fn_80253EB4(a, b, 1, 0); break;
        case 57: fn_80253EB4(a, b, 2, 0); break;
        case 61: fn_80253EB4(a, b, 2, 0); break;
        case 14: fn_8005B294(a, b, lbl_8063D578->_e8c[6]); break;
        case 20: fn_8005B294(a, b, lbl_8063D578->_e8c[7]); break;
        case 26: fn_8005B294(a, b, lbl_8063D578->_e8c[8]); break;
        case 32: fn_8005B294(a, b, lbl_8063D578->_e8c[9]); break;
        case 38: fn_8005B294(a, b, lbl_8063D578->_e8c[10]); break;
        case 44: fn_8005B294(a, b, lbl_8063D578->_e8c[11]); break;
    }
}

// TODO First element callback of layout 25; sets the texts of its elements or dims them.
void fn_8014D8EC(int a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 2:
            if (lbl_8063D578->_0f8 == 0) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 3: {
            u16 tbl[4] = {lbl_80641470, lbl_80641472, lbl_80641474, lbl_80641476};
            if (lbl_8063D578->_0f8 + tbl[(lbl_8063D578->_d30 >> 23) & 3] >= lbl_8063D578->_0fc) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        }
    }
}

// TODO Second element callback of layout 25; draws the texts and icons of its elements.
void fn_8014D9E4(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(7, buf);
            break;
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(8, buf);
            break;
    }
}

// TODO First element callback of layout 26; sets the texts of its elements or dims them.
void fn_8014DA84(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 5:
            switch (lbl_8063D578->_d41) {
                case 2: fn_80253EB4(a, b, 2, 0x50c2); break;
                case 1: fn_80253EB4(a, b, 2, 0x50bb); break;
                case 3:
                case 4: fn_80253EB4(a, b, 2, 0x50e5); break;
            }
            break;
        case 8:
            switch (lbl_8063D578->_d41) {
                case 1:
                case 2:
                case 3:
                case 4: fn_80253EB4(a, b, 2, 0x50a9); break;
            }
            break;
        case 10:
            switch (lbl_8063D578->_d41) {
                case 1:
                case 2:
                case 3:
                case 4: fn_80253EB4(a, b, 2, 0x50aa); break;
            }
            break;
        case 3:
            switch (lbl_8063D578->_d41) {
                case 2: fn_80253EB4(a, b, 2, 0x516d); break;
                case 1: fn_80253EB4(a, b, 2, 0x5186); break;
                case 3: fn_80253EB4(a, b, 2, 0x50e6); break;
                case 4: fn_80253EB4(a, b, 2, 0x5253); break;
            }
            break;
    }
}

// TODO Second element callback of layout 26; draws the texts and icons of its elements.
void fn_8014DC54(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 2:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(2, buf);
            break;
    }
}

// TODO First element callback of layout 27; sets the texts of its elements or dims them.
void fn_8014DCF4(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    if (lbl_8063D578->_d42 == 11 && ((lbl_8063D578->_d30 >> 22) & 1)) {
        switch (v) {
            case 2:
            case 3: return;
        }
    }
    switch (v) {
        case 3:
            switch (lbl_8063D578->_d42) {
                case 2:
                case 3:
                case 4:
                case 5:  fn_80253EB4(a, b, 2, 0x50c6); break;
                case 1:  fn_80253EB4(a, b, 2, 0x50bb); break;
                case 6:
                case 8:
                case 9:  fn_80253EB4(a, b, 2, 0x50cd); break;
                case 11: fn_80253EB4(a, b, 2, 0x50e5); break;
                case 10: fn_80253EB4(a, b, 2, 0x50e5); break;
            }
            break;
        case 5:
            switch (lbl_8063D578->_d42) {
                case 2: fn_80253EB4(a, b, 2, 0x50c7); break;
                case 3:
                    fn_8014F164();
                    fn_80253EB4(a, b, 2, 0x50c9);
                    break;
                case 4: fn_80253EB4(a, b, 2, 0x50cc); break;
                case 5: fn_80253EB4(a, b, 2, 0x50ca); break;
                case 1: fn_80253EB4(a, b, 2, 0x518c); break;
                case 6: fn_80253EB4(a, b, 2, 0x520c); break;
                case 9:
                    fn_8015C308(0xe, fn_8014DCF4Inline());
                    fn_80253EB4(a, b, 2, 0x50ba);
                    break;
                case 8:
                    fn_8015C308(0xe, (int)lbl_8063D578->_d28->_4ecc);
                    fn_80253EB4(a, b, 2, 0x50b9);
                    break;
                case 11:
                    if (lbl_8063D578->_d80 == 0x50ba) {
                        fn_8015C308(0xe, fn_8014DCF4Inline());
                    }
                    fn_80253EB4(a, b, 2, lbl_8063D578->_d80);
                    break;
                case 10: fn_80253EB4(a, b, 2, 0x5129); break;
            }
            break;
        case 7:
            switch (lbl_8063D578->_d42) {
                case 2:  fn_80253EB4(a, b, 2, 0x50c8); break;
                case 4:
                case 5:
                case 9:  fn_80253EB4(a, b, 2, 0x516e); break;
                case 11: fn_80253EB4(a, b, 2, lbl_8063D578->_d82); break;
                case 10: fn_80253EB4(a, b, 2, 0x50ab); break;
            }
            break;
        case 6:
            switch (lbl_8063D578->_d42) {
                case 1:
                case 3:
                case 6:
                case 8: fn_80253EB4(a, b, 1, 0); break;
            }
            break;
    }
}

// TODO Second element callback of layout 27; does nothing.
void fn_8014E050() {}

// TODO First element callback of layout 28; sets the texts of its elements or dims them.
void fn_8014E054(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 3: fn_80253EB4(a, b, 2, 0x50a9); break;
        case 4: break;
        case 5: fn_80253EB4(a, b, 2, 0x50aa); break;
    }
}

// TODO Second element callback of layout 28; draws the texts and icons of its elements.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E0E8(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(1, buf);
            break;
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(2, buf);
            break;
    }
    if (lbl_8063D578->_0c4 == 0x49 && fn_80253DD0(lbl_8063D578->_080[0x1c]) == 3) {
        if (lbl_8063D578->_efd == 0) {
            fn_8014E80C(0);
            fn_8014E94C(0x1c, 5);
            lbl_8063D578->_0c4 = 0x4a;
        } else {
            fn_8015C4F4(3, 0x5533);
        }
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 29; sets the texts of its elements or dims them.
void fn_8014E1EC(int a, u8 *b) {
    int v;
    fn_80253E8C(a, (int)b, 3, &v);
    switch (v) {
        case 2:
            if (lbl_8063D578->_0f8 == 0) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
        case 3:
            if (lbl_8063D578->_0f8 + 6 >= lbl_8063D578->_0fc) {
                b[2] >>= 2;
                b[3] >>= 2;
                b[4] >>= 2;
            }
            break;
    }
}

// TODO Second element callback of layout 29; draws the texts and icons of its elements.
void fn_8014E2B4(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(7, buf);
            break;
        case 1:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(8, buf);
            break;
    }
}

// TODO Update callback of layout 30.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E354(s16 a) {
    if (fn_8014E980(0x1e) && fn_80253DE0(a) == 1 && fn_80253DD0(a) == 3) {
        fn_80253DF0(a, 8, 0);
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 30; reads the element id and does nothing else.
void fn_8014E3C4(s16 a, int b) {
    u8 buf[8];
    fn_80253E8C(a, b, 3, buf);
}

// TODO Second element callback of layout 30; draws the texts and icons of its elements.
void fn_8014E3F0(s16 a, Unk8014FC0C *b) {
    int v;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 3, &v);
    switch (v) {
        case 0:
            switch (lbl_8063D578->_0d0) {
                case 5:
                case 10:
                    b->_50 += b->_50 - b->_4c;
                    b->_54 += b->_54 - b->_4c;
                    break;
            }
            break;
        case 1: {
            u16 id1 = lbl_8041D438[lbl_8063D578->_0d0];
            u16 id2 = lbl_8041D450[lbl_8063D578->_0d0];
            switch (lbl_8063D578->_0d0) {
                case 10:
                    fn_8015CC78(lbl_8063D578->_d48 + 1, 2, 0xe, 1);
                    if (lbl_8063D578->_104[lbl_8063D578->_d48] == 0) {
                        fn_8015C308(0xf, fn_802502F4(0x50f0));
                    } else {
                        fn_8015C308(0xf, lbl_8063D578->_17c[lbl_8063D578->_d48]);
                    }
                    break;
                case 3:
                    switch (lbl_8063D578->_0d4) {
                        case 1:    id2 = 0x2a3d; break;
                        case 2:    id2 = 0x2a3e; break;
                        case 0x63: id2 = 0x2a57; break;
                    }
                    break;
                case 4:
                    switch (lbl_8063D578->_0d4) {
                        case 1: id2 = 0x2a44; break;
                        case 2: id2 = 0x2a45; break;
                    }
                    break;
                case 11: {
                    Unk8011C974 *p = lbl_8063D578->_d28;
                    u16 k = p->_0090;
                    if (k != 0 && k != 7) {
                        fn_8015C308(0x17, k);
                    } else {
                        if (k == 7) {
                            if (p->_0008 == 1) {
                                fn_8015C308(0x17, 4);
                            } else {
                                fn_8015C308(0x17, 3);
                            }
                        }
                        if (lbl_8063D578->_d28->_0090 == 0) {
                            id1 = 0xe9e;
                        }
                    }
                    break;
                }
            }
            if (id1 != 0) {
                fn_80253EDC(a, (int)b, 6, buf);
                s16 w = buf[1] - buf[0];
                s16 h = buf[6] - buf[4];
                fn_80250134(id1, buf[0], buf[4], w, h, b->_11 | 0xFFFFFF00);
            }
            if (id2 != 0xffff) {
                fn_8015C4F4(2, id2);
            }
            break;
        }
    }
}

// TODO Update callback of layout 31.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E6C0(s16 a) {
    if (fn_8014E980(0x1f) && fn_80253DE0(a) == 3 && fn_80253DD0(a) == 3) {
        fn_80253DF0(a, 8, 0);
    }
}
#pragma dont_inline reset

// TODO First element callback of layout 31; sets the texts of its elements or dims them.
void fn_8014E730(s16 a, int b) {
    int v;
    fn_80253E8C(a, b, 3, &v);
    switch (v) {
        case 1: fn_80253EB4(a, b, 1, fn_8005A9F8(0x1a)); break;
    }
}

// TODO Second element callback of layout 31; draws the texts and icons of its elements.
void fn_8014E79C(s16 a, int b) {
    int v;
    u8 buf[0x28];
    fn_80253EDC(a, b, 3, &v);
    switch (v) {
        case 0:
            fn_80253EDC(a, b, 6, buf);
            fn_80059A3C(0x63, buf);
            break;
    }
}

// TODO Switches layout slot 30 on when a is not 0, off otherwise.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E80C(int a) {
    if (a) {
        if (fn_8014E980(0x1e)) {
            if (fn_80253DE0(lbl_8063D578->_080[0x1e]) == 1) {
                fn_8014E964(0x1e, 1);
                fn_8014E94C(0x1e, 2);
            }
        } else {
            fn_8014E964(0x1e, 1);
            fn_8014E94C(0x1e, 2);
        }
    } else {
        if (fn_8014E980(0x1e)) {
            fn_8014E94C(0x1e, 1);
        }
    }
}
#pragma dont_inline reset

// TODO Switches layout slot 31 on when a is not 0, off otherwise.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E8AC(int a) {
    if (a) {
        if (fn_8014E980(0x1f)) {
            if (fn_80253DE0(lbl_8063D578->_080[0x1f]) == 3) {
                fn_8014E964(0x1f, 1);
                fn_8014E94C(0x1f, 4);
            }
        } else {
            fn_8014E964(0x1f, 1);
            fn_8014E94C(0x1f, 4);
        }
    } else {
        if (fn_8014E980(0x1f)) {
            fn_8014E94C(0x1f, 3);
        }
    }
}
#pragma dont_inline reset

// TODO Calls fn_80253DB0 with b on layout slot i.
void fn_8014E94C(u16 i, int b) {
    fn_80253DB0(lbl_8063D578->_080[i], b, 0);
}

// TODO Sets property 8 of layout slot i to b.
void fn_8014E964(u16 i, int b) {
    fn_80253DF0(lbl_8063D578->_080[i], 8, b);
}

// TODO Returns whether property 8 of layout slot i is 1.
int fn_8014E980(u16 i) {
    int v;
    fn_80253E4C(lbl_8063D578->_080[i], 8, &v);
    return v == 1;
}

// TODO Clears property 8 of the layout slots and runs the actions flagged in 0xD30.
// The callees are not inlined in the original.
#pragma dont_inline on
void fn_8014E9C8() {
    u32 i;
    for (i = 0; i < 0x14; i++) {
        fn_8014E964((u8)i, 0);
    }
    for (i = 0x16; i < 0x20; i++) {
        fn_8014E964((u8)i, 0);
    }
    if ((lbl_8063D578->_d30 >> 21) & 1) {
        lbl_8063D578->_d30 &= ~0x200000;
        lbl_8063D578->_d30 &= ~0x8000000;
        fn_8011F050();
    }
    if ((lbl_8063D578->_d30 >> 20) & 1) {
        lbl_8063D578->_d30 &= ~0x100000;
        fn_800E7044();
    }
    if ((lbl_8063D578->_d30 >> 19) & 1) {
        lbl_8063D578->_d30 &= ~0x80000;
        fn_8009FC9C();
        memcpy(lbl_8063D578->_d28->_008a, lbl_8063D578->_dcc, 0xe);
    }
    fn_80056330();
    if (lbl_8063D578->_d6c != 0) {
        fn_802502D4(lbl_8063D578->_d6c);
        lbl_8063D578->_d6c = 0;
    }
    fn_800598F8(0, 0);
}
#pragma dont_inline reset

// TODO Fills the entry tables from the 30 entries that fn_80166FB0 accepts.
void fn_8014EAD0() {
    u16 count = 0;
    int i;
    for (i = 0; i < 0x1e; i++) {
        if (fn_80166FB0(i)) {
            lbl_8063D578->_17c[count] = fn_8016704C(i);
            lbl_8063D578->_104[count] = fn_80167098(i);
            lbl_8063D578->_270[count] = fn_80166FF4(i);
            lbl_8063D578->_1f4[count] = fn_80166F64(i);
            lbl_8063D578->_360[count] = fn_80166ED0(i);
            lbl_8063D578->_3d8[count] = fn_800E5410(lbl_8063D578->_104[count]);
            lbl_8063D578->_3f8[count] = i;
            count++;
        }
    }
    lbl_8063D578->_0f8 = lbl_8063D578->_d48;
    lbl_8063D578->_0fa = lbl_8063D578->_d48;
    lbl_8063D578->_0f8 = 0;
    lbl_8063D578->_0fa = 0;
    lbl_8063D578->_0fc = count;
}

// TODO Refreshes the entry tables from fn_80166FB0 and picks the entry that changed.
void fn_8014EBFC(int flag) {
    u16 count = 0;
    if (!((lbl_8063D578->_d30 >> 26) & 1)) {
        for (int i = 0; i < 0x1e; i++) {
            if (fn_80166FB0(i)) {
                lbl_8063D578->_17c[0] = fn_8016704C(i);
                lbl_8063D578->_104[0] = fn_80167098(i);
                lbl_8063D578->_270[0] = fn_80166FF4(i);
                lbl_8063D578->_1f4[0] = fn_80166F64(i);
                lbl_8063D578->_360[0] = fn_80166ED0(i);
                lbl_8063D578->_3d8[0] = fn_800E5410(lbl_8063D578->_104[0]);
                lbl_8063D578->_c68[0] = 0;
                memset(lbl_8063D578->_470, 0, 0x44);
            }
        }
        lbl_8063D578->_0fc = 0;
        return;
    }
    u8 sel = 0xff;
    for (int i = 0; i < 0x1e; i++) {
        if (fn_80166FB0(i)) {
            int skip = 0;
            switch (fn_801670E4(i)) {
                case 0:
                    if (lbl_8063D578->_c68[count] != fn_801670E4(i)) {
                        sel = count;
                    }
                    break;
                case 1:
                    if (lbl_8063D578->_c68[count] == 0) {
                        sel = count;
                    }
                    break;
                case 4:
                    if (lbl_8063D578->_c68[count] != fn_801670E4(i)) {
                        u32 *p = fn_8016722C(i);
                        u32 first = lbl_8063D578->_470[count]._00;
                        if (*p == first) {
                            skip = 1;
                        } else if (first == 0 && lbl_8063D578->_ce0[count] != 0) {
                            lbl_8063D578->_ce0[count]--;
                            skip = 1;
                        } else {
                            sel = count;
                        }
                    }
                    break;
            }
            if (skip) {
                count++;
                continue;
            }
            lbl_8063D578->_c68[count] = fn_801670E4(i);
            lbl_8063D578->_17c[count] = fn_8016704C(i);
            lbl_8063D578->_104[count] = fn_80167098(i);
            lbl_8063D578->_270[count] = fn_80166FF4(i);
            lbl_8063D578->_1f4[count] = fn_80166F64(i);
            lbl_8063D578->_360[count] = fn_80166ED0(i);
            lbl_8063D578->_3d8[count] = fn_800E5410(lbl_8063D578->_104[count]);
            lbl_8063D578->_3f8[count] = i;
            if (lbl_8063D578->_c68[count] == 4) {
                memcpy(&lbl_8063D578->_470[count], fn_8016722C(i), 0x44);
            }
            count++;
        }
    }
    if (flag) {
        if (sel != 0xff) {
            lbl_8063D578->_d20 = sel;
            lbl_8063D578->_d21 = 0;
            lbl_8063D578->_d22 = 0x352;
            lbl_8063D578->_d1c = lbl_8063D578->_c68[sel];
            fn_8000B170(0x25f, 0, lbl_80641414);
        }
    } else {
        lbl_8063D578->_d21 = 1;
    }
    lbl_8063D578->_0fc = count;
}

// TODO Writes the 12 digits of a 64-bit number as text; returns 0 when it is 0.
int fn_8014EF80() {
    u64 val = fn_80164F58();
    if (val != 0) {
        for (u16 i = 0; i < 12; i++) {
            lbl_8063D578->_0d8[i] = val % lbl_8041D468[i] / lbl_8041D468[i + 1] + 0x30;
        }
        return 1;
    }
    lbl_8063D578->_0d8[0] = 0;
    return 0;
}

// TODO Sets text argument 0xE from the 0x10 field of the 0xD28 object.
void fn_8014F164() {
    int id;
    switch (lbl_8063D578->_d28->_0010) {
        case 1000: id = 0x29c6; break;
        case 1001: id = 0x29c7; break;
        case 1002: id = 0x29c8; break;
        case 1003: id = 0x29c9; break;
        case 1004: id = 0x29ca; break;
        case 1005: id = 0x29cb; break;
        case 1006: id = 0x29cc; break;
        case 1007: id = 0x29cd; break;
        case 1008: id = 0x29ce; break;
        case 1009: id = 0x29cf; break;
        default:   id = 0x29d0; break;
    }
    fn_8015C308(0xe, fn_802502F4(id));
}

// TODO Calls fn_80166D6C with mode 1 on the buffer of the 0xD24 object.
void fn_8014F214() {
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(lbl_8063D578->_d24->_00010, 1, b, a, 0, 0);
}

// TODO Calls fn_80166D6C with mode 5 on the buffer of the 0xD24 object.
void fn_8014F270() {
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(lbl_8063D578->_d24->_00010, 5, b, a, 0, 0);
}

// TODO Copies the 0x1C text of the entry into a local buffer.
void fn_8014F2CC(u32 a, Unk8014F2CC *b) {
    u8 buf[0x80];
    fn_8017714C(buf, b->_1c, 0x80);
}

// TODO Builds the entry at 0xD88 from the 0xD28 object and sends it; returns 1 on success.
// The callees are not inlined in the original.
#pragma dont_inline on
int fn_8014F2F8() {
    int id;
    memcpy(&lbl_8063D578->_d88._0c[0], lbl_8063D578->_d28->_008a, 0xe);
    lbl_8063D578->_d88._04 = lbl_8063D578->_d28->_0010;
    lbl_8063D578->_d88._08 = lbl_8063D578->_d28->_0008;
    lbl_8063D578->_d88._1a = lbl_8063D578->_d28->_0004 >> 28;
    switch (lbl_8063D578->_d28->_0004 >> 28) {
        case 0: id = 0x5531; break;
        case 1: id = 0x5532; break;
        case 2: id = 0x5532; break;
        default:
            fn_8015C308(0xf, (int)(lbl_8063D578->_d24->_660e2 + ((lbl_8063D578->_d28->_0004 >> 28) - 3) * 0x18));
            id = 0x3f9;
            break;
    }
    fn_802503D8(id, lbl_8063D578->_d88._1c);
    lbl_8063D578->_d88._00 = fn_80163434();
    if (lbl_8063D578->_d88._00 == 0) {
        (lbl_8063D578->_d88._00)++;
    }
    fn_80168B04(lbl_8063D578->_d88._00);
    int a = fn_80162A90(0xd);
    int b = fn_80162A90(0x3a);
    fn_80166D6C(lbl_8063D578->_d24->_00010, 4, b, a, (int)(&lbl_8063D578->_d88._00), 0x44);
    fn_8014F2CC(lbl_8063D578->_d88._00, &lbl_8063D578->_d88);
    if (fn_80165354() < 0) {
        fn_8014F214();
        return 0;
    }
    lbl_8063D578->_d30 |= 0x02000000;
    return 1;
}
#pragma dont_inline reset

// TODO Clears the selection tables.
void fn_8014F488() {
    lbl_8063D578->_df1[0] = 0;
    lbl_8063D578->_dfd[0] = 0;
    lbl_8063D578->_edc[0] = 0;
    lbl_8063D578->_ee2[0] = 0;
    lbl_8063D578->_df1[1] = 0;
    lbl_8063D578->_dfd[1] = 0;
    lbl_8063D578->_edc[1] = 0;
    lbl_8063D578->_ee2[1] = 0;
    lbl_8063D578->_df1[2] = 0;
    lbl_8063D578->_dfd[2] = 0;
    lbl_8063D578->_edc[2] = 0;
    lbl_8063D578->_ee2[2] = 0;
    lbl_8063D578->_df1[3] = 0;
    lbl_8063D578->_dfd[3] = 0;
    lbl_8063D578->_edc[3] = 0;
    lbl_8063D578->_ee2[3] = 0;
    lbl_8063D578->_df1[4] = 0;
    lbl_8063D578->_dfd[4] = 0;
    lbl_8063D578->_edc[4] = 0;
    lbl_8063D578->_ee2[4] = 0;
    lbl_8063D578->_df1[5] = 0;
    lbl_8063D578->_dfd[5] = 0;
    lbl_8063D578->_edc[5] = 0;
    lbl_8063D578->_ee2[5] = 0;
    lbl_8063D578->_df1[6] = 0;
    lbl_8063D578->_dfd[6] = 0;
    lbl_8063D578->_df1[7] = 0;
    lbl_8063D578->_dfd[7] = 0;
    memset(lbl_8063D578->_e09, 0, 0x80);
    fn_8014F748(0);
}

// TODO Reads the selection tables back and counts the selected entries.
void fn_8014F5A4() {
    Unk8063D578 *g = lbl_8063D578;
    if (g->_df0 == 0) {
        fn_80168100(0, g->_df1);
        lbl_8063D578->_df0 = 1;
    }
    if (fn_80168148(0, lbl_8063D578->_dfd)) {
        u8 count = 0;
        u32 i;
        for (i = 0; i < 6; i++) {
            u8 c = lbl_8063D578->_dfd[i];
            if (c != 0 && c != 7) {
                count++;
            }
        }
        for (u8 j = 0; j < 6; j++) {
            if (j < count) {
                g->_ee2[j] = 1;
            } else {
                g->_ee2[j] = 0;
            }
        }
    }
}

// TODO Marks the entries that cannot be selected, from the mask returned by fn_801502A0.
void fn_8014F748(int x) {
    u32 m;
    if (lbl_8063D578->_df1[6] == 3) {
        return;
    }
    for (int i = 0; i < 6; i++) {
        if (lbl_8063D578->_df1[i] == 7) {
            lbl_8063D578->_df1[i] = 0;
        }
    }
    m = fn_801502A0(lbl_8063D578->_d28->_1ffc, x, 0xff);
    if (m & 0x04000000) {
        lbl_8063D578->_df1[0] = 7;
    }
    if (m & 0x08000000) {
        lbl_8063D578->_df1[1] = 7;
    }
    if (m & 0x10000000) {
        lbl_8063D578->_df1[2] = 7;
    }
    if (m & 0x20000000) {
        lbl_8063D578->_df1[3] = 7;
    }
    if (m & 0x40000000) {
        lbl_8063D578->_df1[4] = 7;
    }
    if (m & 0x80000000) {
        lbl_8063D578->_df1[5] = 7;
    }
    if (m & 0x400) {
        Unk8063D578 *g = lbl_8063D578;
        if (g->_d28->_0090 == 0) {
            g->_df1[6] = 1;
        } else {
            g->_df1[6] = 2;
        }
    } else {
        lbl_8063D578->_df1[6] = 0;
    }
}

// TODO Selects or unselects entry slot and renumbers the others; returns 1 when it changed.
// TODO Does not match yet (0x348 bytes instead of 0x344).
int fn_8014F8BC(int slot, int b) {
    int ret = 0;
    u8 cur = *(lbl_8063D578->_df1 + slot);
    if (cur != 0 && cur != 7) {
        *(lbl_8063D578->_df1 + slot) = 0;
        ret = 1;
        for (u8 i = 0; i < 6; i++) {
            u8 c = lbl_8063D578->_df1[i];
            if (c != 0 && c != 7 && c >= cur) {
                lbl_8063D578->_df1[i] = c - 1;
            }
        }
        if (b) {
            fn_8000B170(0x21f, 0, lbl_80641414);
        }
    } else if (cur == 0) {
        u8 n = 1;
        for (int k = 0; k < 6; k++) {
            u8 c = lbl_8063D578->_df1[k];
            if (c != 0 && c != 7) {
                n++;
            }
        }
        *(lbl_8063D578->_df1 + slot) = n;
        ret = 1;
        if (b) {
            fn_8000B170(0x21f, 0, lbl_80641414);
        }
    }
    u8 cnt = 0;
    u8 mask = 0;
    for (u8 i = 0; i < 6; i++) {
        u8 c = lbl_8063D578->_df1[i];
        if (c != 0 && c != 7) {
            cnt++;
            mask |= lbl_80641478[i];
        }
    }
    for (u8 i = 0; i < 6; i++) {
        if (i < cnt) {
            lbl_8063D578->_edc[i] = 1;
        } else {
            lbl_8063D578->_edc[i] = 0;
        }
    }
    fn_8014F748(mask);
    lbl_8063D578->_df0 = 0;
    return ret;
}

// TODO Clears the byte at 0x6E5 and calls fn_80058CBC.
void fn_8014FC00(Unk80058EA0 *p) {
    p->_6e5 = 0;
    fn_80058CBC(p);
}

// TODO Draws text c centred in the rectangle of element b.
// TODO Does not match yet (0xEC bytes instead of 0xF0).
void fn_8014FC0C(int a, Unk8014FC0C *b, int c) {
    u32 color = b->_11 | 0xFFFFFF00;
    f32 buf[8];
    fn_80253EDC(a, (int)b, 6, buf);
    s16 w = fn_80250398(c, 1, 0);
    s16 width = buf[1] - buf[0];
    s16 height = buf[6] - buf[4];
    fn_80250134(c, buf[0] + (width - w) / 2, buf[4], width, height, color);
}

// TODO Sets the links between six buttons through fn_800599C8.
void fn_8014FCFC() {
    if (lbl_8063D578->_c68[lbl_8063D578->_d49] == 4) {
        fn_800599C8(1, 0, 0, 2, 5, 0);
        fn_800599C8(2, 0, 1, 7, 5, 0);
        fn_800599C8(5, 1, 0, 0x63, 0, 0);
        fn_800599C8(7, 0, 2, 0, 8, 0);
        fn_800599C8(8, 7, 2, 0, 0x63, 0);
        fn_800599C8(0x63, 8, 5, 0, 0, 0);
    } else {
        fn_800599C8(1, 0, 0, 0, 0, 0);
        fn_800599C8(2, 0, 0, 0, 0, 0);
        fn_800599C8(5, 0, 0, 0x63, 0, 0);
        fn_800599C8(7, 0, 0, 0, 8, 0);
        fn_800599C8(8, 7, 0, 0, 0x63, 0);
        fn_800599C8(0x63, 8, 5, 0, 0, 0);
    }
}
