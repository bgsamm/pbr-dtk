#pragma once

#include ".unsorted/8011C974.hpp"

#include <revolution/types.h>

struct Unk80058EA0;

// size: 0x44
struct Unk8014F2CC {
    /* 0x00 */ u32 _00;
    /* 0x04 */ u32 _04;
    /* 0x08 */ s32 _08;
    /* 0x0C */ u8 _0c[0xE];
    /* 0x1A */ u16 _1a;
    /* 0x1C */ u16 _1c[20];
};

// A drawn element of a layout, passed to the layout callbacks.
// size: unknown
struct Unk8014FC0C {
    /* 0x00 */ u8 unk00[0x11];
    /* 0x11 */ u8 _11;
    /* 0x12 */ u8 unk12[0x26];
    /* 0x38 */ f32 _38;
    /* 0x3C */ f32 _3c;
    /* 0x40 */ f32 _40;
    /* 0x44 */ f32 _44;
    /* 0x48 */ f32 _48;
    /* 0x4C */ f32 _4c;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
};

// Object returned by fn_8015F690.
// size: unknown
struct Unk8015F690 {
    /* 0x00 */ u8 unk00[0x4C];
    /* 0x4C */ s32 _4c;
};

// Object returned by fn_8015F6E0.
// size: unknown
struct Unk8015F6E0 {
    /* 0x00000 */ u8 unk00000[0x10];
    /* 0x00010 */ u8 _00010[0x660D2];
    /* 0x660E2 */ u8 _660e2[0x48];
};

// size: unknown
struct Unk8063D578 {
    /* 0x000 */ void *_000[32];
    /* 0x080 */ s16 _080[32];
    /* 0x0C0 */ s32 _0c0;
    /* 0x0C4 */ u16 _0c4;
    /* 0x0C6 */ u16 _0c6;
    /* 0x0C8 */ u8 unk0c8[0x8];
    /* 0x0D0 */ u16 _0d0;
    /* 0x0D4 */ s32 _0d4;
    /* 0x0D8 */ u16 _0d8[14];
    /* 0x0F4 */ u8 unk0f4[0x4];
    /* 0x0F8 */ u16 _0f8;
    /* 0x0FA */ u16 _0fa;
    /* 0x0FC */ u16 _0fc;
    /* 0x0FE */ u16 _0fe;
    /* 0x100 */ u16 _100;
    /* 0x102 */ u16 _102;
    /* 0x104 */ s32 _104[30];
    /* 0x17C */ s32 _17c[30];
    /* 0x1F4 */ s32 _1f4[31];
    /* 0x270 */ s64 _270[30];
    /* 0x360 */ s32 _360[30];
    /* 0x3D8 */ u8 _3d8[32];
    /* 0x3F8 */ s32 _3f8[30];
    /* 0x470 */ Unk8014F2CC _470[30];
    /* 0xC68 */ u32 _c68[30];
    /* 0xCE0 */ u16 _ce0[30];
    /* 0xD1C */ u32 _d1c;
    /* 0xD20 */ u8 _d20;
    /* 0xD21 */ u8 _d21;
    /* 0xD22 */ s16 _d22;
    /* 0xD24 */ Unk8015F6E0 *_d24;
    /* 0xD28 */ Unk8011C974 *_d28;
    /* 0xD2C */ u8 unkd2c[0x4];
    /* 0xD30 */ u32 _d30;
    /* 0xD34 */ u8 unkd34[0x4];
    /* 0xD38 */ f64 _d38;
    /* 0xD40 */ u8 _d40;
    /* 0xD41 */ u8 _d41;
    /* 0xD42 */ u8 _d42;
    /* 0xD43 */ u8 _d43;
    /* 0xD44 */ u8 _d44;
    /* 0xD45 */ u8 _d45;
    /* 0xD46 */ u8 _d46;
    /* 0xD47 */ u8 _d47;
    /* 0xD48 */ u8 _d48;
    /* 0xD49 */ u8 _d49;
    /* 0xD4A */ u8 _d4a;
    /* 0xD4C */ u16 _d4c[16];
    /* 0xD6C */ u16 _d6c;
    /* 0xD6E */ u8 unkd6e[0x12];
    /* 0xD80 */ u16 _d80;
    /* 0xD82 */ u16 _d82;
    /* 0xD84 */ u8 unkd84[0x4];
    /* 0xD88 */ Unk8014F2CC _d88;
    /* 0xDCC */ u8 _dcc[0xE];
    /* 0xDDA */ u8 _dda;
    /* 0xDDB */ u8 _ddb;
    /* 0xDDC */ u8 unkddc[0x14];
    /* 0xDF0 */ u8 _df0;
    /* 0xDF1 */ u8 _df1[12];
    /* 0xDFD */ u8 _dfd[12];
    /* 0xE09 */ u8 _e09[0x80];
    /* 0xE89 */ u8 unke89[0x3];
    /* 0xE8C */ s32 _e8c[12];
    /* 0xEBC */ u8 *_ebc[8];
    /* 0xEDC */ u8 _edc[6];
    /* 0xEE2 */ u8 _ee2[6];
    /* 0xEE8 */ s32 _ee8[2];
    /* 0xEF0 */ void *_ef0;
    /* 0xEF4 */ u8 *_ef4;
    /* 0xEF8 */ u8 unkef8[0x2];
    /* 0xEFA */ u8 _efa;
    /* 0xEFB */ u8 unkefb[0x2];
    /* 0xEFD */ u8 _efd;
    /* 0xEFE */ u8 _efe[0x28];
};

extern Unk8063D578 *lbl_8063D578;

void fn_8013F044();
void fn_8013F31C();
void fn_8013FFB8();
void fn_80149234();
void fn_80149348(s16 a, int b);
void fn_80149374(s16 a, int b);
void fn_801493A0(s16 a, int b);
void fn_80149488(s16 a, int b);
void fn_801495A8(s16 a, int b);
void fn_80149630(s16 a, int b);
void fn_80149744(s16 a, int b);
void fn_801497F0(s16 a, int b);
void fn_801498C0(s16 a, int b);
void fn_801498EC(s16 a, int b);
void fn_80149918(s16 a, int b);
void fn_80149944(s16 a, int b);
void fn_80149970(s16 a, int b);
void fn_8014999C();
void fn_80149C0C(s16 a, u8 *b);
void fn_80149E18(s16 a, Unk8014FC0C *b);
void fn_8014A1E8(s16 a, int b);
void fn_8014A2C0(s16 a, Unk8014FC0C *b);
void fn_8014A510(s16 a, u8 *b);
void fn_8014A71C(s16 a, Unk8014FC0C *b);
void fn_8014AAA4(s16 a, int b);
void fn_8014AB70(int a, Unk8014FC0C *b);
void fn_8014AC84(s16 a, u8 *b);
void fn_8014AE08();
void fn_8014B41C(s16 a, u8 *b);
void fn_8014B634(s16 a, Unk8014FC0C *b);
void fn_8014BCA0(s16 a, int b);
void fn_8014BCCC(s16 a, int b);
void fn_8014BCF8(s16 a, int b);
void fn_8014BD24(s16 a, int b);
void fn_8014BD50(s16 a, int b);
void fn_8014BD7C(s16 a, int b);
void fn_8014BDA8(s16 a);
void fn_8014BDB8(s16 a, u8 *b);
void fn_8014BEE4(s16 a, Unk8014FC0C *b);
void fn_8014C074();
void fn_8014C078();
void fn_8014C2B8(s16 a, int b);
void fn_8014C34C(s16 a, int b);
void fn_8014C3EC(s16 a, u8 *b);
void fn_8014C50C(s16 a, int b);
void fn_8014C598(s16 a);
void fn_8014C6A0(s16 a, int b);
void fn_8014CD2C(s16 a, Unk8014FC0C *b);
void fn_8014D148(s16 a, int b);
void fn_8014D370();
void fn_8014D8EC(int a, u8 *b);
void fn_8014D9E4(s16 a, int b);
void fn_8014DA84(s16 a, int b);
void fn_8014DC54(s16 a, int b);
void fn_8014DCF4(s16 a, int b);
void fn_8014E050();
void fn_8014E054(s16 a, int b);
void fn_8014E0E8(s16 a, int b);
void fn_8014E1EC(int a, u8 *b);
void fn_8014E2B4(s16 a, int b);
void fn_8014E354(s16 a);
void fn_8014E3C4(s16 a, int b);
void fn_8014E3F0(s16 a, Unk8014FC0C *b);
void fn_8014E6C0(s16 a);
void fn_8014E730(s16 a, int b);
void fn_8014E79C(s16 a, int b);
void fn_8014E80C(int a);
void fn_8014E8AC(int a);
void fn_8014E94C(u16 i, int b);
void fn_8014E964(u16 i, int b);
int fn_8014E980(u16 i);
void fn_8014E9C8();
void fn_8014EAD0();
void fn_8014EBFC(int flag);
int fn_8014EF80();
void fn_8014F164();
void fn_8014F214();
void fn_8014F270();
void fn_8014F2CC(u32 a, Unk8014F2CC *b);
int fn_8014F2F8();
void fn_8014F488();
void fn_8014F5A4();
void fn_8014F748(int x);
int fn_8014F8BC(int slot, int b);
void fn_8014FC00(Unk80058EA0 *p);
void fn_8014FC0C(int a, Unk8014FC0C *b, int c);
void fn_8014FCFC();
