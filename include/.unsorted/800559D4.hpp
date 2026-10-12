#pragma once

#include ".unsorted/80032FE8.hpp"
#include "decomp.h"
#include "ds/pokemon.hpp"

class GSscene;

struct Unk8063D4A0Bits {
    u32 b31 : 1;
    u32 b30 : 1;
    u32 b29 : 1;
    u32 b28 : 1;
    u32 b27 : 1;
    u32 b26 : 1;
    u32 b25_24 : 2;
    u32 b23 : 1;
    u32 b22 : 1;
    u32 b21 : 1;
    u32 b20 : 1;
    u32 b19 : 1;
    u32 b18_15 : 4;
    u32 b14_12 : 3;
    u32 b11 : 1;
    u32 b10 : 1;
    u32 b9 : 1;
    u32 b8 : 1;
    u32 b7 : 1;
    u32 b6 : 1;
    u32 b5 : 1;
    u32 b4 : 1;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
};

// size: 0x10B0
struct Unk8063D4A0 {
    /* 0x0000 */ u64 _0000;
    /* 0x0008 */ Unk8063D4A0Bits _0008;
    /* 0x000C */ union {
        Unk8063D4A0Bits _000c;
        u32 _000c_word;
    };
    /* 0x0010 */ u32 _0010;
    /* 0x0014 */ u32 *_0014;
    /* 0x0018 */ u32 _0018;
    /* 0x001C */ void *_001c;
    /* 0x0020 */ void *_0020;
    /* 0x0024 */ void *_0024;
    /* 0x0028 */ GSscene *_0028;
    /* 0x002C */ GSscene *_002c;
    /* 0x0030 */ GSscene *_0030;
    /* 0x0034 */ u16 _0034;
    /* 0x0036 */ u16 _0036;
    /* 0x0038 */ u32 _0038;
    /* 0x003C */ u16 _003c[64][32];
    /* 0x103C */ u16 _103c;
    /* 0x1040 */ void *_1040;
    /* 0x1044 */ s16 _1044;
    /* 0x1048 */ void *_1048;
    /* 0x104C */ s16 _104c;
    /* 0x1050 */ void *_1050;
    /* 0x1054 */ s16 _1054;
    /* 0x1058 */ u32 _1058;
    /* 0x105C */ f32 _105c[8];
    /* 0x107C */ u32 _107c;
    /* 0x1080 */ u8 _1080;
    /* 0x1081 */ u8 _1081;
    /* 0x1084 */ u32 _1084;
    /* 0x1088 */ f32 _1088;
    /* 0x108C */ f32 _108c;
    /* 0x1090 */ f32 _1090;
    /* 0x1094 */ f32 _1094;
    /* 0x1098 */ f32 _1098;
    /* 0x109C */ f32 _109c;
    /* 0x10A0 */ u64 _10a0;
    /* 0x10A8 */ u8 _10a8;
};

extern Unk8063D4A0 *lbl_8063D4A0;

// size: 0x58
struct Unk80056630 {
    /* 0x00 */ u8 unk00[0x11];
    /* 0x11 */ u8 _11;
    /* 0x12 */ u8 unk12[0x36];
    /* 0x48 */ f32 _48;
    /* 0x4C */ f32 _4c;
    /* 0x50 */ f32 _50;
    /* 0x54 */ f32 _54;
};

// size: unknown
struct Unk800570E8 {
    /* 0x0 */ u16 _0;
    /* 0x2 */ u16 _2;
    /* 0x4 */ u16 _4;
    /* 0x6 */ u16 _6;
    /* 0x8 */ u32 _8;
    /* 0xC */ u16 _c[1];
};

// size: 0x1C
struct Unk80058EA0 {
    /* 0x0 */ u8 unk0[0x4];
    /* 0x4 */ u16 _4[12];
};

// size: 0x20
struct Unk80058FD4 {
    /* 0x00 */ f32 _00[4];
    /* 0x10 */ f32 _10[4];
};

void fn_800559D4();
void fn_80055D94();
void *fn_80055D98(u32 a, u32 b) NO_INLINE;
void *fn_80055E1C(u32 size);
void fn_80055E30(void *p);
f32 fn_80055E3C() NO_INLINE;
void fn_80055EB4(int x) NO_INLINE;
void fn_80055EC8();
void *fn_80055EDC(void *arg);
void *fn_8005606C(void *arg);
void *fn_80056120(void *arg);
void fn_800561B0() NO_INLINE;
void fn_800561E8();
void fn_80056230();
void fn_80056274();
void fn_800562BC();
void fn_800562D0();
void fn_800562E4();
BOOL fn_800562F8();
void fn_80056330();
void fn_80056344();
void fn_80056358(int a, int b, int c, int d, int e);
void fn_800563CC(int x);
void fn_800563E0(u8 x);
void fn_800563EC(void *p, int x);
void fn_80056458(int x);
void fn_800564AC(u32 x);
void fn_800564B8(u8 a, u32 b);
void fn_800564CC();
void fn_8005650C() NO_INLINE;
void fn_80056528();
void fn_8005654C();
void fn_800565BC(s16 a, int b);
void fn_80056630(s16 a, Unk80056630 *o);
void fn_800568C0(s16 a);
int fn_8005694C(int a, int b);
void fn_80056978();
u16 *fn_8005697C(BoxPokemon *p);
u16 *fn_800569EC(Pokemon *p);
u8 fn_80056A5C(BoxPokemon *p);
u8 fn_80056B18(Pokemon *p);
int fn_80056BD4(BoxPokemon *p);
int fn_80056C4C(Pokemon *p);
void *fn_80056CC4(BoxPokemon *p);
void *fn_80056D78(Pokemon *p);
BOOL fn_80056E2C(BoxPokemon *p);
BOOL fn_80056E84(Pokemon *p);
BOOL fn_80056EDC(BoxPokemon *p);
void fn_80056F34(int a, int b);
int fn_80056F68(BoxPokemon *p, int b);
void fn_800570E8(BoxPokemon *p, Unk800570E8 *q);
void fn_80057208(Pokemon *p);
void fn_8005732C(BoxPokemon *p);
void fn_80057450(BoxPokemon *p);
void fn_800574DC(s16 a, int b, BoxPokemon *c);
void fn_80057558();
u32 fn_8005755C();
u32 fn_8005756C();
void *fn_8005757C(void *arg);
void fn_80057688();
u32 fn_8005769C();
void fn_800576AC() NO_INLINE;
void fn_800576B0();
void fn_800578BC();
void fn_800579FC(int mode);
void fn_80057FB4(int mode);
void fn_80058178();
void fn_800583A4();
void fn_800583B8();
void fn_800583CC();
void fn_800583E0();
void fn_800583F4();
void fn_80058408();
void fn_8005841C();
u32 fn_80058480();
u32 fn_80058490();
u32 fn_800584A0();
u32 fn_800584B0();
void fn_800584C0();
void fn_800584D4();
void fn_800584E8();
void fn_80058580();
BOOL fn_80058610();
BOOL fn_80058660();
int fn_800586B0();
int fn_80058714();
void fn_80058778(int x);
u8 fn_80058B10(bool x);
u8 fn_80058BA4();
u16 fn_80058BCC(u32 x);
u16 fn_80058BFC(int a, int b, int c);
void fn_80058CBC(Unk80058EA0 *p);
void fn_80058E34(u16 *p);
void fn_80058EA0(Unk80058EA0 *p);
void fn_80058FD4(u8 c, int mode);
void fn_80059208();
u32 fn_8005923C();
bool fn_8005924C();
void fn_8005925C(u32 x);
void *fn_80059288(void *arg);
void fn_80059414();
f32 fn_800597C4();
bool fn_8005983C(int i);
void fn_80059884(int i);
