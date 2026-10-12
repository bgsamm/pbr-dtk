#pragma once

#include <revolution/mem.h>
#include <revolution/os.h>
#include <revolution/types.h>

struct GSthreadHandle;
struct Unk80035D9C;

// Bit view of the 0x2C word of an Unk8000CC84.
struct Unk8001914C {
    u32 b31_4 : 28;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
};

// The object returned by fn_80035D9C; the Unk8063E970 object keeps six of them.
// size: 0x974
struct Unk80035D9C {
    /* 0x000 */ u8 unk000[0x96C];
    /* 0x96C */ struct Unk8000EC58 *_96c;
    /* 0x970 */ u8 unk970[0x4];
};

// An entry of the Unk8063E970 object, cleared by fn_8000CC84.
// size: 0x58
struct Unk8000CC84 {
    /* 0x00 */ u32 _00;
    /* 0x04 */ Unk80035D9C *_04;
    /* 0x08 */ u8 _08;
    /* 0x09 */ u8 _09;
    /* 0x0A */ u8 _0a;
    /* 0x0B */ u8 _0b;
    /* 0x0C */ u8 _0c;
    /* 0x0D */ u8 _0d;
    /* 0x0E */ u8 unk0e[0x4];
    /* 0x12 */ u8 _12;
    /* 0x13 */ u8 _13;
    /* 0x14 */ u8 _14;
    /* 0x15 */ u8 _15;
    /* 0x16 */ u8 _16;
    /* 0x17 */ u8 _17;
    /* 0x18 */ u8 _18[5];
    /* 0x1D */ u8 _1d;
    /* 0x1E */ u8 unk1e[0x2];
    /* 0x20 */ u16 _20;
    /* 0x22 */ u8 unk22[0x2];
    /* 0x24 */ u8 _24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u16 _26;
    /* 0x28 */ u32 _28;
    /* 0x2C */ u32 _2c;
    /* 0x30 */ u8 _30;
    /* 0x31 */ u8 _31;
    /* 0x32 */ s16 _32[4];
    /* 0x3A */ u8 unk3a[0x2];
    /* 0x3C */ u32 _3c[4];
    /* 0x4C */ u8 _4c[4];
    /* 0x50 */ u32 _50;
    /* 0x54 */ int _54;
};

// size: 0x1C
struct Unk80019380 {
    /* 0x00 */ Unk80035D9C *_00;
    /* 0x04 */ u8 _04;
    /* 0x05 */ u8 _05;
    /* 0x06 */ u8 _06;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u16 _08[4];
    /* 0x10 */ u8 _10[8];
    /* 0x18 */ u8 _18[4];
};

// The 0x100-byte object passed to fn_802565C0, fn_80256850 and the other functions of that unit.
// size: 0x100
struct Unk80256850 {
    /* 0x00 */ int _00;
    /* 0x04 */ u8 unk04[0xFC];
};

// A request queued by fn_8000D818.
// size: 0xC
struct Unk8000D818 {
    /* 0x0 */ int _0;
    /* 0x4 */ void *_4;
    /* 0x8 */ int _8;
};

// The object created by fn_8000C764 and kept in lbl_8063E970.
// size: 0x9DFC
struct Unk8063E970 {
    /* 0x0000 */ u8 _0000;
    /* 0x0001 */ u8 unk0001[0x3];
    /* 0x0004 */ int _0004;
    /* 0x0008 */ int _0008;
    /* 0x000C */ Unk8000D818 _000c[4];
    /* 0x003C */ u8 _003c;
    /* 0x003D */ u8 _003d;
    /* 0x003E */ u8 _003e;
    /* 0x003F */ u8 _003f;
    /* 0x0040 */ int _0040;
    /* 0x0044 */ int _0044;
    /* 0x0048 */ int _0048;
    /* 0x004C */ int _004c;
    /* 0x0050 */ int _0050;
    /* 0x0054 */ int _0054;
    /* 0x0058 */ int _0058;
    /* 0x005C */ u8 _005c;
    /* 0x005D */ u8 _005d;
    /* 0x005E */ u8 unk005e[0x2];
    /* 0x0060 */ int _0060;
    /* 0x0064 */ int _0064;
    /* 0x0068 */ u8 _0068[0x1000];
    /* 0x1068 */ int _1068;
    /* 0x106C */ u16 _106c;
    /* 0x106E */ u8 _106e;
    /* 0x106F */ u8 _106f;
    /* 0x1070 */ Unk80256850 _1070;
    /* 0x1170 */ int _1170;
    /* 0x1174 */ int _1174[20];
    /* 0x11C4 */ u8 _11c4[20];
    /* 0x11D8 */ u8 _11d8[20];
    /* 0x11EC */ u16 _11ec[20];
    /* 0x1214 */ s16 _1214[20];
    /* 0x123C */ u8 _123c[20];
    /* 0x1250 */ u8 _1250[20];
    /* 0x1264 */ u32 _1264;
    /* 0x1268 */ Unk80256850 _1268[20];
    /* 0x2668 */ s8 _2668;
    /* 0x2669 */ u8 _2669;
    /* 0x266A */ u8 unk266a[0x2];
    /* 0x266C */ u32 _266c;
    /* 0x2670 */ int _2670;
    /* 0x2674 */ u8 *_2674[5];
    /* 0x2688 */ u8 _2688[5][0x4E];
    /* 0x280E */ s16 _280e;
    /* 0x2810 */ s16 _2810;
    /* 0x2812 */ s16 _2812;
    /* 0x2814 */ u8 unk2814[0x8];
    /* 0x281C */ u16 _281c;
    /* 0x281E */ u8 _281e;
    /* 0x281F */ u8 _281f;
    /* 0x2820 */ u8 _2820;
    /* 0x2821 */ u8 _2821;
    /* 0x2822 */ u8 _2822;
    /* 0x2823 */ u8 unk2823;
    /* 0x2824 */ u8 _2824[8];
    /* 0x282C */ u8 _282c[8];
    /* 0x2834 */ u8 _2834[0x10];
    /* 0x2844 */ u16 _2844[4];
    /* 0x284C */ u8 _284c[0x10];
    /* 0x285C */ u8 _285c[2];
    /* 0x285E */ u8 _285e[2];
    /* 0x2860 */ u8 _2860[4][6];
    /* 0x2878 */ u8 _2878[4][6];
    /* 0x2890 */ u16 _2890[4];
    /* 0x2898 */ u8 _2898[4];
    /* 0x289C */ u8 _289c[4];
    /* 0x28A0 */ u32 _28a0[4];
    /* 0x28B0 */ u8 _28b0[4];
    /* 0x28B4 */ u8 _28b4[4];
    /* 0x28B8 */ u8 _28b8[4];
    /* 0x28BC */ u8 _28bc[4];
    /* 0x28C0 */ u32 _28c0;
    /* 0x28C4 */ u32 _28c4;
    /* 0x28C8 */ u32 _28c8;
    /* 0x28CC */ u16 _28cc;
    /* 0x28CE */ u8 _28ce;
    /* 0x28CF */ u8 _28cf;
    /* 0x28D0 */ u8 _28d0;
    /* 0x28D1 */ u8 unk28d1[0x3];
    /* 0x28D4 */ int _28d4[2];
    /* 0x28DC */ int _28dc;
    /* 0x28E0 */ Unk80035D9C _28e0[6];
    /* 0x6198 */ int _6198;
    /* 0x619C */ Unk80035D9C _619c[6];
    /* 0x9A54 */ int _9a54;
    /* 0x9A58 */ Unk8000CC84 _9a58[4];
    /* 0x9BB8 */ Unk8000CC84 *_9bb8[4];
    /* 0x9BC8 */ int _9bc8;
    /* 0x9BCC */ Unk8000CC84 _9bcc[4];
    /* 0x9D2C */ Unk8000CC84 *_9d2c[4];
    /* 0x9D3C */ Unk80019380 _9d3c[2];
    /* 0x9D74 */ Unk80019380 _9d74[2];
    /* 0x9DAC */ u8 _9dac;
    /* 0x9DAD */ u8 _9dad;
    /* 0x9DAE */ u8 _9dae;
    /* 0x9DAF */ u8 _9daf;
    /* 0x9DB0 */ u8 _9db0;
    /* 0x9DB1 */ u8 _9db1;
    /* 0x9DB2 */ u8 _9db2;
    /* 0x9DB3 */ u8 _9db3;
    /* 0x9DB4 */ u8 _9db4;
    /* 0x9DB5 */ u8 _9db5;
    /* 0x9DB6 */ u8 _9db6;
    /* 0x9DB7 */ u8 _9db7;
    /* 0x9DB8 */ u8 _9db8[4];
    /* 0x9DBC */ u8 _9dbc;
    /* 0x9DBD */ u8 _9dbd;
    /* 0x9DBE */ u8 unk9dbe[2];
    /* 0x9DC0 */ GSthreadHandle *_9dc0;
    /* 0x9DC4 */ OSMutex _9dc4;
    /* 0x9DDC */ u32 _9ddc;
    /* 0x9DE0 */ u32 _9de0;
    /* 0x9DE4 */ OSMutex _9de4;
};

extern Unk8063E970 *lbl_8063E970;

typedef void (Unk8063E970::*Unk800217CC)(void *);

// The value copied from lbl_803FB738.
// size: 0xC
struct Unk8000ADC0 {
    /* 0x0 */ u32 _0;
    /* 0x4 */ u32 _4;
    /* 0x8 */ u32 _8;
};

// size: 0x8
struct Unk800137EC {
    /* 0x0 */ u16 _0;
    /* 0x2 */ u16 _2;
    /* 0x4 */ u8 _4;
    /* 0x5 */ u8 _5;
    /* 0x6 */ u8 _6;
    /* 0x7 */ u8 unk7;
};

// An entry of the table at 0x96C of an Unk80035D9C.
// size: 0x1C
struct Unk8000EC58 {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 unk01[3];
    /* 0x04 */ u16 _04;
    /* 0x06 */ u8 unk06[6];
    /* 0x0C */ int _0c[2];
    /* 0x14 */ u16 _14;
    /* 0x16 */ u16 _16;
    /* 0x18 */ u8 unk18[4];
};

// The object reached through an entry of the table returned by fn_80045590.
// size: unknown
struct Unk8000BCB0 {
    /* 0x000 */ u8 unk000[0x51C];
    /* 0x51C */ u16 _51c;
};

// An entry of the table returned by fn_80045590.
// size: 0x44
struct Unk80045590 {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ Unk8000BCB0 *_10;
    /* 0x14 */ u8 unk14[0x30];
};

// size: unknown
struct Unk800239DC {
    /* 0x00 */ u8 unk00[0x4];
    /* 0x04 */ u16 _04;
    /* 0x06 */ u8 unk06[0x6];
    /* 0x0C */ void *_0c;
    /* 0x10 */ void *_10;
};

// size: unknown
struct Unk8001FA9C {
    /* 0x00 */ u8 _00;
    /* 0x01 */ u8 unk01[0xB];
    /* 0x0C */ int _0c[2];
};

// Bit view of the message passed to fn_800220F0.
struct Unk800220F0 {
    u32 b31_28 : 4;
    u32 b27_24 : 4;
    u32 b23_16 : 8;
    u32 b15_0 : 16;
};

void fn_8000ADC0(char *a, MEMHeapHandle b);
void fn_8000AE8C();
void fn_8000AEB0(u8 k);
int fn_8000AFE0(int x);
void fn_8000B030(int h, int a, int b, f32 f);
int fn_8000B170(int a, int b, f32 f);
int fn_8000B210(int a, int b, f32 f);
u8 fn_8000B2C8();
int fn_8000B2D0(int x);
int fn_8000B31C(int x);
int fn_8000B3B4(int x, int y);
u32 fn_8000B42C(int x);
void fn_8000B46C(int x, int y);
int fn_8000B4C0(int x);
void fn_8000B500(int x);
void fn_8000B538(int x);
void fn_8000B570(int x);
u32 fn_8000B5A8();
void fn_8000B5D0(int x);
void fn_8000B608(int x);
void fn_8000B640(int x);
void fn_8000B678(int x);
void fn_8000B6B0(int x);
void fn_8000B6E8(int x);
u32 fn_8000B720();
void fn_8000B748(f32 f);
void fn_8000B784(f32 f);
void fn_8000B7D0(f32 f);
void fn_8000B80C(f32 f);
f32 fn_8000B848();
f32 fn_8000B850();
f32 fn_8000B858();
void fn_8000B860();
void fn_8000B8C4();
void fn_8000B914(int idx, void *y);
int fn_8000BBB4(int x);
f32 fn_8000BC20(int x);
int fn_8000BC2C();
int fn_8000BC50();
int fn_8000BC78(int x);
int fn_8000BCA4(int x);
int fn_8000BCB0(int idx);
void fn_8000BD2C();
int fn_8000BD6C(Unk8063E970 *p, u32 k);
void fn_8000C04C(Unk8063E970 *p, u32 k);
int fn_8000C378();
void fn_8000C52C(const char *fmt, ...);
int fn_8000C57C();
void fn_8000C764();
Unk8063E970 *fn_8000C7E8();
void *fn_8000C7F0(void *);
void fn_8000CBD4(u32 *p);
void *fn_8000CBE8(void *p, int del);
void *fn_8000CC28(void *p, int del);
void fn_8000CC84(Unk8000CC84 *p);
void *fn_8000CCF0(void *p, int del);
void *fn_8000CD30(void *p, int del);
void fn_8000CD70(void *);
void fn_8000D1B8(Unk8063E970 *p);
bool fn_8000D230(void *);
void fn_8000D26C(Unk8063E970 *bp);
void fn_8000D3C4(Unk8063E970 *bp);
void fn_8000D68C(Unk8063E970 *p);
u32 fn_8000D734(Unk8063E970 *p);
void *fn_8000D780(void **p, OSMutex *m);
void *fn_8000D7B8(OSMutex **p, int del);
void fn_8000D810(Unk8063E970 *p, u8 v);
void fn_8000D818(Unk8063E970 *p, int a, void *b, int c);
void fn_8000D8AC(void *);
void fn_8000DE70(Unk8063E970 *p);
void fn_8000DEC4(Unk8063E970 *bp);
u32 fn_8000DFC4(Unk8063E970 *p, int a, u8 b, int c, int d);
void fn_8000E06C(Unk8063E970 *p);
void fn_8000E194(Unk8063E970 *p, void *x);
void fn_8000E2C8(Unk8063E970 *p);
void fn_8000E4A0(void *);
void fn_8000E88C(Unk8063E970 *p);
u16 fn_8000EA70(Unk8063E970 *p, int x);
void fn_8000EAE0(Unk8063E970 *p, u8 k, u16 v);
void fn_8000EBAC(Unk8063E970 *p, u32 v);
void fn_8000EC58(Unk8063E970 *p, Unk80035D9C *q);
void fn_8000EDB0(Unk8063E970 *bp);
void fn_8000EEBC(Unk8063E970 *p);
int fn_8000EEF4(void *, int *, int *, void *);
u32 fn_8000FE58(void *p, u32 a, u32 b, u32 c, u32 d);
u32 fn_8000FECC(u32 n);
u32 fn_8000FF40(u32 *p);
int fn_8000FF64(Unk8063E970 *p, void *x);
int fn_80010078(void *p, int *a, int *b, int *c, int k);
int fn_80010968(void *p, int *a, int *b, int *c, int k);
int fn_80011290(void *p, int *cnt, int *out, int unused, int k);
u32 fn_80012908(void *p, u32 a, u32 b, u32 c, u32 d);
u16 fn_8001370C(Unk8063E970 *p, int x);
u16 fn_8001377C(Unk8063E970 *p, int x);
void fn_800137EC(Unk8063E970 *p, Unk800137EC *out);
u32 fn_80014E88(void *p, u32 a, u32 b, u32 c);
void fn_80014EE8(Unk8063E970 *p, int k, u32 flag);
bool fn_800150E0(Unk8063E970 *p, int n, void *x);
int fn_8001515C(void *p, int n, void *x);
void fn_80015234(Unk8063E970 *p, int x);
void fn_800153A8(Unk8063E970 *p, int n, int c, int x, int y);
void fn_80015608(Unk8063E970 *p, int n, int *a, int *b);
void fn_80015740(Unk8063E970 *p, int n, int *a);
void fn_8001585C(Unk8063E970 *p, int n, int *a, int *b, u32 *cnt, u32 max);
int fn_80015968(void *, int, int, int, int *, int *);
void fn_80015D38(Unk8063E970 *p);
void fn_80015E7C(void *, u8 *, u8 *, u8 *, u8 *, u8 *, u16 *, u8 *);
void fn_80016580(Unk8063E970 *bp);
void fn_80016640(void *, int, int, u32);
int fn_80016EE0(void *, u8);
u32 fn_80017B08(Unk8063E970 *p, u32 a, u32 b);
u32 fn_80017BB4(Unk8063E970 *p, u32 a, u32 b, u32 c, u32 d);
u8 fn_80017CE8(Unk8000CC84 *p);
u32 fn_80017D10(Unk8063E970 *p, u32 a, u32 b, u32 c);
int fn_80019090(Unk8000CC84 *p, u32 v);
int fn_800190B4(Unk8000CC84 *p);
int fn_8001914C(Unk8000CC84 *p);
u8 fn_80019170(Unk8000CC84 *p, u8 idx);
int fn_800191D4(Unk8000CC84 *p, int v);
Unk80019380 *fn_8001929C(Unk80019380 *p);
void fn_80019310(Unk80019380 *p);
void fn_80019380(Unk80019380 *out, u8 k, Unk80035D9C *q);
void fn_800195A8(void *);
int fn_8001A544(Unk8000CC84 *p);
void fn_8001A56C(void *, u8);
int fn_8001D1E0(Unk8000CC84 *p, int n);
int fn_8001EBF4(void *p, int k);
int fn_8001ECE4(void *p, int a, int b);
int fn_8001EF1C(void *p, int a, int b);
int fn_8001FA9C(Unk8063E970 *bp, int idx, Unk8001FA9C *s);
void fn_8001FBDC(Unk8063E970 *bp, u8 start);
void fn_8001FC94(Unk8063E970 *p);
void fn_8001FCAC(void *);
void fn_8002062C(void *);
void fn_80020BF8(Unk8063E970 *p);
void fn_80020D44(Unk8063E970 *p);
void fn_80020E34(Unk8063E970 *p);
void fn_80020EB8(Unk8063E970 *p, int k);
void fn_800210CC(Unk8063E970 *p, int n);
int fn_800210FC(Unk8063E970 *m, int id, u8 a, u8 b, u16 w, s16 v, u8 e, u32 flag);
void fn_800213D0(void *, int, int, int *, int *);
void fn_800217CC(Unk8063E970 *p, int idx, void *arg);
void fn_8002183C(Unk8063E970 *p);
void fn_800218E8(Unk8063E970 *p);
void fn_80021974(Unk8063E970 *bp);
void fn_80021BA8(Unk8063E970 *bp, int x);
void fn_80021D78(Unk8063E970 *p);
void fn_80021DD0(Unk8063E970 *p, u32 x);
void fn_80021DE0(Unk8063E970 *p, void *x);
void fn_80021E34(Unk8063E970 *p, u32 x);
void fn_80021EC4(Unk8063E970 *p, int idx, void *arg);
void fn_80021F34(Unk8063E970 *bp, int k);
void fn_80021FE8(Unk8063E970 *p);
void fn_800220F0(Unk8063E970 *p, u32 m);
void fn_80022B60();
void fn_80022B98();
void fn_80022BD0();
void fn_80022C08();
void fn_80023790(Unk8063E970 *m, int unused, Unk8000EC58 *e, u8 c);
int fn_800239DC(Unk8063E970 *p, Unk80035D9C *x, Unk800239DC *s, void *y);
int fn_80023AB0(Unk8063E970 *p, u16 k, u32 y, u8 a, u16 b, Unk80035D9C *x);
int fn_80023BC0(void *, void *, void *, u8, u16, Unk80035D9C *);
void fn_80023DF0();
int fn_80023E28(Unk8063E970 *p, int id, void *unused);
bool fn_80024178(Unk8063E970 *p, int bit, int idx);
void fn_800241A8(Unk8063E970 *p, int bit, int idx);
int fn_800241D4(void *p, int x);
int fn_80024254(Unk8063E970 *bp, u8 k);
int fn_800242D0(Unk8063E970 *p, u8 k, u32 start);
void fn_80024480(Unk8063E970 *bp, Unk80035D9C *x);
int fn_80024688(Unk8063E970 *p);
int fn_80024700();
int fn_800247AC(u32 n);
int fn_800248A0(u32 n);
