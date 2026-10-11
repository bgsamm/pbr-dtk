#include ".unsorted/8000ADC0.hpp"

#include "common.hpp"
#include "gs/GSthread.hpp"
#include <string.h>

#pragma optimize_for_size on
#pragma dont_inline on

extern "C" {

extern f32 lbl_8063D318;
extern f32 lbl_8063D31C;
extern f32 lbl_8063D324;
extern u32 lbl_8063E970;
extern u8 lbl_8063D328;

u8 fn_8000B2C8(void) { return lbl_8063D328; }
f32 fn_8000B848(void) { return lbl_8063D318; }
f32 fn_8000B850(void) { return lbl_8063D31C; }
f32 fn_8000B858(void) { return lbl_8063D324; }
u32 fn_8000C7E8(void) { return lbl_8063E970; }
void fn_8000D810(u8 *p, u8 v) { *(u8 *)(p + 0x0) = v; }

}


extern "C" void *fn_802544D0(void);
extern "C" void fn_802549D0(void);
void fn_8000AE8C() {
    fn_802544D0(); fn_802549D0();
}

extern "C" {

void *fn_802544D0(void);
void fn_802549D0(void);
int fn_80255890(void *);
f32 fn_8039349C(void *, void *);
int fn_8039301C(void *, void *);
int fn_80392FE8(void *, void *);
void fn_802556A8(void *, int, void *);
void fn_802554A0(void *, int, void *);
u32 fn_802557AC(void *, int);
int fn_802557E0(void *, int);
void fn_80255520(void *, int, f32);
u32 fn_80255738(void *, int);
void fn_80255710(void *, int);
int fn_802553B8(void *, int, int);
int fn_80393084(void *, void *);
void fn_8000C52C(const char *, ...);
void fn_80020EB8(void *, int);
void fn_8000EAE0(void *, u8, u16);
void fn_8002062C(void *);
void fn_8001FCAC(void *);
int fn_80035D9C(void);
int fn_80035ED8(int);
int fn_803AC828(void);
void *fn_803AC848(void);
void fn_8000D1B8(void *);
void fn_8000CD70(void *);
void fn_8000B914(int, void *);

extern void *lbl_8063E958;
extern void *lbl_8063E954;
extern f32 lbl_8063D320;
extern void *lbl_8063E95C;
extern void *lbl_8063E960;
extern void *lbl_8063E964;
extern char lbl_804084E6[];
extern char lbl_80408D04[];
extern char lbl_80408D3C[];
extern char lbl_80408D7D[];
extern char lbl_80408DBE[];
extern char lbl_80409170[];

f32 fn_8000BC20(void *x) { return fn_8039349C(lbl_8063E958, x); }
int fn_8000BCA4(void *x) { return fn_8039301C(lbl_8063E954, x); }
int fn_8000BC2C(void) { return fn_80255890(fn_802544D0()); }
void fn_8000CBD4(u32 *p) { p[0] = 0; p[1] = 0; p[2] = 0; }
u32 fn_8000FF40(u32 *p) {
    *p = *p * 0x343FD + 0x269EC3;
    return *p >> 16;
}
int fn_80019090(u8 *p, u32 v) {
    u8 a = p[0x1d];
    int r = 0;
    if (((a + v) & 1) == 0) {
        if (a != v) r = 1;
    }
    return r;
}

struct Bits2C {
    u32 pad : 28;
    u32 b3 : 1;
    u32 b2 : 1;
    u32 b1 : 1;
    u32 b0 : 1;
};
struct Bits2C4 {
    u32 pad : 28;
    u32 f : 4;
};
int fn_8001914C(u8 *p) {
    Bits2C *b = (Bits2C *)(p + 0x2c);
    return b->b1 + b->b0 + b->b3 + b->b2;
}
#pragma push
#pragma optimize_for_size off
int fn_8001D1E0(u8 *p, int n) {
    Bits2C4 *b = (Bits2C4 *)(p + 0x2c);
    return (*(u32 *)(p + 0x2c) & ((1 << n) & 0xF)) != 0;
}
#pragma pop
void fn_8001FC94(u8 *p) {
    if (p[0x9D5E]) fn_8002062C(p);
    else fn_8001FCAC(p);
}
void fn_80021DD0(void *p, u32 x) { fn_8000EAE0(p, (x >> 16) & 3, x & 0xFFFF); }

void fn_8000B500(void *x) { fn_802556A8(fn_802544D0(), 1, x); }
void fn_8000B538(void *x) { fn_802556A8(fn_802544D0(), 0, x); }
void fn_8000B570(void *x) { fn_802554A0(fn_802544D0(), 2, x); }
void fn_8000B5D0(void *x) { fn_802554A0(fn_802544D0(), 0, x); }
void fn_8000B608(void *x) { fn_802554A0(fn_802544D0(), 1, x); }
void fn_8000B640(void *x) { fn_802554A0(fn_802544D0(), 3, x); }
void fn_8000B678(void *x) { fn_802554A0(fn_802544D0(), 4, x); }
void fn_8000B6B0(void *x) { fn_802554A0(fn_802544D0(), 5, x); }
void fn_8000B6E8(void *x) { fn_802554A0(fn_802544D0(), 6, x); }
u32 fn_8000B5A8(void) { return fn_802557AC(fn_802544D0(), 2); }
u32 fn_8000B720(void) { return fn_802557AC(fn_802544D0(), 3); }
int fn_8000BC50(void) { return fn_802557E0(fn_802544D0(), 3); }
int fn_8000BC78(void *x) { return (s16)fn_80392FE8(lbl_8063E954, x); }

void fn_8000B748(f32 f) { lbl_8063D318 = f; fn_80255520(fn_802544D0(), 2, f); }
void fn_8000B7D0(f32 f) { lbl_8063D320 = f; fn_80255520(fn_802544D0(), 3, f); }
void fn_8000B80C(f32 f) { lbl_8063D324 = f; fn_80255520(fn_802544D0(), 5, f); }
void fn_8000B784(f32 f) {
    lbl_8063D31C = f;
    fn_80255520(fn_802544D0(), 0, f);
    fn_80255520(fn_802544D0(), 1, f);
}

void *fn_8000D780(void **p, OSMutex *m) {
    *p = m;
    OSLockMutex(m);
    return p;
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_8000EEBC(u8 *p) {
    u32 last = *(u32 *)(p + 0x2684);
    int i;
    for (i = 4; i > 0; i--) *(u32 *)(p + 0x2674 + i * 4) = *(u32 *)(p + 0x2670 + i * 4);
    *(u32 *)(p + 0x2674) = last;
    memset(p + 0x2688, 0, 0x4e);
}
#pragma pop

u8 fn_80017CE8(u8 *p) {
    u8 v = p[0x17];
    if (v >= 1 && v <= 4) return p[0x18 + v];
    return 0xff;
}
int fn_8001A544(u8 *p) { return p[0x12] != 0 || p[0x18] != 0; }

void fn_800210CC(u8 *p, int n) {
    int c = *(int *)(p + 0x1170);
    if (c <= 0) {
        fn_8000C52C(lbl_804084E6);
        return;
    }
    if (n + 1 == c) fn_80020EB8(p, n);
}

void fn_80022B60(void) { fn_8000C52C(lbl_80408D04, fn_80035ED8(fn_80035D9C())); }
void fn_80022B98(void) { fn_8000C52C(lbl_80408D3C, fn_80035ED8(fn_80035D9C())); }
void fn_80022BD0(void) { fn_8000C52C(lbl_80408D7D, fn_80035ED8(fn_80035D9C())); }
void fn_80022C08(void) { fn_8000C52C(lbl_80408DBE, fn_80035ED8(fn_80035D9C())); }
void fn_80023DF0(void) { fn_8000C52C(lbl_80409170, fn_80035ED8(fn_80035D9C())); }

bool fn_80024178(u8 *p, int bit, int idx) {
    u8 *buf = *(u8 **)(p + 0x2674 + idx * 4);
    return !!(buf[bit >> 3] & (1 << (bit & 7)));
}
void fn_800241A8(u8 *p, int bit, int idx) {
    u8 *buf = *(u8 **)(p + 0x2674 + idx * 4);
    buf[bit >> 3] |= (1 << (bit & 7));
}

bool fn_8000D230(void *) {
    if (fn_803AC828() == 0) return 0;
    return fn_803AC848() != 0;
}

void fn_8000C52C(const char *fmt, ...) {}

void *fn_8000CBE8(void *p, int del) { if (p && del > 0) operator delete(p); return p; }
void *fn_8000CCF0(void *p, int del) { if (p && del > 0) operator delete(p); return p; }
void *fn_8000CD30(void *p, int del) { if (p && del > 0) operator delete(p); return p; }

int fn_8000B2D0(void *x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    return fn_802553B8(fn_802544D0(), v, 0) >= 0;
}
u32 fn_8000B42C(void *x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    return fn_80255738(fn_802544D0(), v);
}
void fn_8000B4C0(void *x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    fn_80255710(fn_802544D0(), v);
}

int fn_8000AFE0(void *x) {
    if (lbl_8063D328 == 0) {
        switch ((u8)fn_80393084(lbl_8063E954, x)) {
        case 0x14:
            return 0;
        }
    }
    return 1;
}

void fn_8000B8C4(void) {
    fn_8000B914(1, lbl_8063E95C);
    fn_8000B914(2, lbl_8063E960);
    fn_8000B914(4, lbl_8063E964);
    lbl_8063E95C = 0;
    lbl_8063E960 = 0;
    lbl_8063E964 = 0;
}

void fn_8000BD2C(void) {
    while (1) {
        u8 *p = (u8 *)lbl_8063E970;
        if (p[0] == 1 && *(int *)(p + 4) != 0) {
            fn_8000D1B8(p);
            fn_8000CD70((void *)lbl_8063E970);
        }
        GSthreadManager::sInstance->sleepCurrentThread();
    }
}

}

extern "C" {

void fn_80255350(void *, int, void *);
void fn_8025643C(void *, int, int, void *, int);
void fn_80015234(void *, int);
void fn_80020BF8(void *);
u32 fn_8000FECC(u32);
void fn_8000E06C(void *);
void fn_8000D818(void *, int, void *, int);
int fn_8000B170(int, int, f32);
bool fn_8000D230(void *);

extern void *lbl_8063EA68;
extern f32 lbl_80640698;
extern char lbl_80407AE4[];
extern char lbl_804088F0[];
extern char lbl_8040933C[];

void fn_8000B46C(void *x, void *y) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    fn_80255350(fn_802544D0(), v, y);
}

void fn_8000B860(void) {
    fn_8025643C(fn_802544D0(), 0, 0xfa, &lbl_8063E95C, 0);
    fn_8025643C(fn_802544D0(), 1, 0xfa, &lbl_8063E960, 0);
    fn_8025643C(fn_802544D0(), 2, 0xfa, &lbl_8063E964, 0);
}

#pragma push
#pragma dont_inline on
void *fn_8000CC28(void *p, int del) {
    if (p) {
        fn_8000CC28(lbl_8063EA68, 1);
        if (del > 0) operator delete(p);
    }
    return p;
}
#pragma pop

void *fn_8000D7B8(OSMutex **p, int del) {
    if (p) {
        OSUnlockMutex(*p);
        if (del > 0) operator delete(p);
    }
    return p;
}

#pragma push
#pragma dont_inline on
u32 fn_8000D734(u8 *p) {
    OSMutex *l;
    u32 r;
    fn_8000D780((void **)&l, (OSMutex *)(p + 0x9DC4));
    r = *(u32 *)(p + 8);
    fn_8000D7B8(&l, -1);
    return r;
}
#pragma pop

void fn_8000DE70(u8 *p) {
    if (*(int *)(p + 0x1070) != 0 || *(int *)(p + 0x1170) != 0) {
        fn_80015234(p, 0);
        fn_80020BF8(p);
    }
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
u32 fn_80014E88(void *p, u32 a, u32 b, u32 c) {
    u32 r = fn_8000FECC(100);
    if (r < 0x21) return a;
    if (r < 0x42) c = b;
    return c;
}
#pragma pop

u8 fn_80019170(u8 *p, u8 idx) {
    if (*(u32 *)(p + 0x3c + idx * 4) & 0x200000) return 0;
    u8 v = (p + idx)[0x4c];
    if (v < 1 || v > 0x7b) {
        fn_8000C52C(lbl_80407AE4);
        return 0;
    }
    return v;
}

void fn_80021D78(u8 *p) {
    if (*(int *)(p + 0x4c) < *(int *)(p + 0x50)) {
        fn_8000C52C(lbl_804088F0);
        *(int *)(p + 0x4c) = *(int *)(p + 0x50);
    }
    fn_8000E06C(p);
}

void fn_80021DE0(u8 *p, void *x) {
    fn_8000D818(p, 7, x, 0);
    while ((int)fn_8000D734(p) > 0) GSthreadManager::sInstance->sleepCurrentThread();
}

int fn_800248A0(u32 n) {
    if (n < 1 || n > 0x1ed) {
        if (n != 0x259) fn_8000C52C(lbl_8040933C, n);
        return 0;
    }
    return fn_8000B170(n + 0x2f, 0, lbl_80640698);
}

}


struct BattleEnt {
    /* 0x00 */ u32 idx;
    /* 0x04 */ u8 *ptr;
    /* 0x08 */ u8 _08[0xE];
    /* 0x16 */ u8 _16;
    /* 0x17 */ u8 _17;
    /* 0x18 */ u8 _18;
    /* 0x19 */ u8 _19[4];
    /* 0x1D */ u8 slot;
    /* 0x1E */ u8 _1E[0x2];
    /* 0x20 */ u16 _20;
    /* 0x22 */ u8 _22[0x6];
    /* 0x28 */ u32 _28_pad : 31;
    /* 0x28 */ u32 _28_flag : 1;
    /* 0x2C */ u8 _2C[0x4];
    /* 0x30 */ u8 _30;
    /* 0x31 */ u8 _31;
    /* 0x32 */ s16 _32[4];
    /* 0x3A */ u8 _3A[0x1A];
    /* 0x54 */ int _54;
};

struct BattleSub1C {
    u32 _00;
    u8 _04[0x18];
};

struct BattleObj {
    /* 0x0000 */ u8 active;
    /* 0x0001 */ u8 pad0[0x9A53];
    /* 0x9A54 */ int entCount;
    /* 0x9A58 */ BattleEnt ents[4];
    /* 0x9BB8 */ BattleEnt *prev[4];
    /* 0x9BC8 */ int entCount2;
    /* 0x9BCC */ BattleEnt ents2[4];
    /* 0x9D2C */ BattleEnt *slots[4];
    /* 0x9D3C */ BattleSub1C subA[2];
    /* 0x9D74 */ BattleSub1C subB[2];
    /* 0x9DAC */ u8 _9DAC;
    /* 0x9DAD */ u8 _9DAD;
    /* 0x9DAE */ u8 _9DAE;
    /* 0x9DAF */ u8 _9DAF;
    /* 0x9DB0 */ u8 _9DB0;
    /* 0x9DB1 */ u8 _9DB1;
    /* 0x9DB2 */ u8 _9DB2;
    /* 0x9DB3 */ u8 _9DB3;
    /* 0x9DB4 */ u8 _9DB4;
    /* 0x9DB5 */ u8 _9DB5;
    /* 0x9DB6 */ u8 _9DB6;
    /* 0x9DB7 */ u8 _9DB7;
    /* 0x9DB8 */ u8 _9DB8[4];
    /* 0x9DBC */ u8 depth2;
    /* 0x9DBD */ u8 depth1;
    /* 0x9DBE */ u8 pad3[2];
    /* 0x9DC0 */ GSthreadHandle *thread;
    /* 0x9DC4 */ OSMutex mutex;
    /* 0x9DDC */ u32 _9DDC;
    /* 0x9DE0 */ u32 _9DE0;
    /* 0x9DE4 */ OSMutex mutex2;
};
typedef void (BattleObj::*BattleHandler)(void *);

extern "C" {

int fn_80393434(void *, void *);
int fn_803C8C48(int, void *, int, int);
u32 fn_8000DFC4(void *, int, u8, int, int);

extern BattleHandler lbl_804086FC[];
extern BattleHandler lbl_80408914[];

int fn_8000BBB4(void *x) {
    switch ((u8)fn_80393434(lbl_8063E958, x)) {
    case 0xf:
        return 0;
    case 0x10:
        return 1;
    case 0x11:
        return 2;
    }
    return 0;
}

void fn_8000CC84(u8 *p) {
    *(u32 *)(p + 0x0) = 0;
    *(u32 *)(p + 0x4) = 0;
    p[0x8] = 0xff;
    p[0x9] = 0;
    p[0xa] = 0;
    p[0xb] = 0;
    p[0xc] = 0;
    p[0xd] = 0;
    p[0x12] = 0;
    p[0x13] = 0;
    p[0x14] = 0;
    p[0x15] = 0;
    p[0x16] = 0;
    p[0x17] = 0;
    p[0x18] = 0;
    p[0x1d] = 0xff;
    *(u16 *)(p + 0x20) = 0;
    p[0x24] = 0;
    *(u16 *)(p + 0x26) = 0;
    *(u32 *)(p + 0x28) = 0;
    *(u32 *)(p + 0x2c) = 0;
    p[0x30] = 0;
    *(u32 *)(p + 0x50) = 0;
    *(u32 *)(p + 0x54) = 0;
}

u16 fn_8000EA70(void *p, int x) {
    int a = fn_803AC828();
    void *b = fn_803AC848();
    return fn_8000DFC4(p, x, fn_803C8C48(a, b, 2, x), 5, 0);
}
u16 fn_8001370C(void *p, int x) {
    int a = fn_803AC828();
    void *b = fn_803AC848();
    return fn_8000DFC4(p, x, fn_803C8C48(a, b, 2, x), 0xa2, 0);
}
u16 fn_8001377C(void *p, int x) {
    int a = fn_803AC828();
    void *b = fn_803AC848();
    return fn_8000DFC4(p, x, fn_803C8C48(a, b, 2, x), 0xa3, 0);
}

void fn_80019310(u8 *p) {
    *(u32 *)(p + 0x0) = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    memset(p + 0x8, 0, 8);
    memset(p + 0x10, 0, 8);
    memset(p + 0x18, 0, 4);
}

void fn_800217CC(BattleObj *p, int idx, void *arg) {
    if (p->active) {
        p->depth1++;
        (p->*lbl_804086FC[idx])(arg);
        p->depth1--;
    }
}
void fn_80021EC4(BattleObj *p, int idx, void *arg) {
    if (p->active) {
        p->depth2++;
        (p->*lbl_80408914[idx])(arg);
        p->depth2--;
    }
}

}


namespace GSmath {
u32 *getRandSeed();
}

extern "C" {

int fn_802552AC(void *, int, void *);
void fn_8000B030(int, void *, void *, f32);
void fn_8000D8AC(void *);
int fn_80035E38(void);
void fn_8000E2C8(void *);
void fn_8000E4A0(void *);

extern f32 lbl_80640678;
extern char lbl_80409278[];

int fn_8000B3B4(void *x, void *y) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    int r = fn_802552AC(fn_802544D0(), v, y);
    if (r < 0) return 0;
    fn_8000B030(r, x, y, lbl_80640678);
    return 1;
}

void fn_8000D1B8(void *pv) {
    u8 *p = (u8 *)pv;
    fn_8000D8AC(p);
    if (fn_80035D9C()) {
        int r = fn_80035E38();
        *(int *)(p + 0x40) = r;
        if (*(int *)(p + 4) == 2) {
            switch (r) {
            case 4:
                if (fn_8000D230(p) == 1) {
                    fn_8000E2C8(p);
                    fn_8000E4A0(p);
                }
                break;
            }
        }
    }
}

#pragma push
#pragma optimize_for_size off
u32 fn_8000FECC(u32 n) {
    u32 *seed = GSmath::getRandSeed();
    u32 lo, hi;
    if (n != 0) {
        lo = (u16)fn_8000FF40(seed);
        hi = fn_8000FF40(seed);
        return ((hi << 16) | lo) % n;
    }
    return 0;
}
#pragma pop

u32 fn_8000FE58(void *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25) return a;
    if (r < 50) return b;
    if (r < 75) d = c;
    return d;
}
u32 fn_80012908(void *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25) return a;
    if (r < 50) return b;
    if (r < 75) d = c;
    return d;
}

u8 *fn_8001929C(u8 *p) {
    *(u32 *)(p + 0x0) = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    memset(p + 0x8, 0, 8);
    memset(p + 0x10, 0, 8);
    memset(p + 0x18, 0, 4);
    return p;
}

int fn_80024688(BattleObj *p) {
    if (*(int *)((u8 *)p + 0x50) == 0 && p->_9DB4 != 0) {
        fn_8000C52C(lbl_80409278, p->_9DB5, p->_9DB4);
        if (p->_9DB5 < p->_9DB4) return 0;
    }
    return 1;
}

}


extern "C" {

u8 *fn_80045590(void);
void *fn_8000C7F0(void *);
void fn_80024924(void);
void fn_80024A34(void);
void fn_80024BCC(void);
void fn_80024D80(void);
int fn_80023E28(void *, int, void *);
int fn_8001515C(void *, int, void *);
int fn_80024AEC(void *);
int fn_80024A70(void *, u32);

extern char lbl_8040848E[];

int fn_8000BCB0(int idx) {
    u8 *s = *(u8 **)(fn_80045590() + idx * 0x44 + 0x10);
    switch (*(u16 *)(s + 0x51c)) {
    case 1:
    case 2:
    case 3:
    case 7:
        return 0;
    case 4:
    case 5:
    case 6:
    case 8:
        return 1;
    }
    return 0;
}

void fn_8000C764(void) {
    BattleObj *p = (BattleObj *)operator new(0x9DFC);
    if (p) p = (BattleObj *)fn_8000C7F0(p);
    lbl_8063E970 = (u32)p;
    p->thread = GSthreadManager::sInstance->createThread(0x136, (void *(*)(void *))fn_8000BD2C, 0, 0x4000, 8, 1);
    fn_80024924();
    fn_80024A34();
    fn_80024BCC();
    fn_80024D80();
}

bool fn_800150E0(void *p, int n, void *x) {
    if (n <= 0 || n >= 0x26a) return 0;
    return !fn_80023E28(p, n, x) ? false : fn_8001515C(p, n, x) != 0;
}

void fn_80020E34(u8 *p) {
    int i;
    if (*(int *)(p + 0x1170)) {
        for (i = 0; i < *(int *)(p + 0x1170); i++) {
            if (!(*(u32 *)(p + 0x1264) & (1 << i))) fn_80020EB8(p, i);
        }
        fn_8000C52C(lbl_8040848E);
    }
}

int fn_800241D4(void *p, void *x) {
    u32 i;
    u8 n = fn_80024AEC(x);
    for (i = 0; i < n; i++) {
        switch ((s16)fn_80024A70(x, i)) {
        case 0x145d:
        case 0x145e:
        case 0x145f:
        case 0x1460:
        case 0x1461:
            return 1;
        }
    }
    return 0;
}

int fn_80024254(BattleObj *bp, u8 k) {
    u8 *p = (u8 *)bp;
    int n;
    u8 mask;
    u8 i;
    if (*(u16 *)(p + 0x2890 + k * 2) == 0) return 1;
    n = *(int *)(p + 0x28dc);
    mask = 1 << k;
    for (i = 0; i < n; i++) {
        if ((p[0x9A6E + i * 0x58] & mask) || (p[0x9A70 + i * 0x58] & mask)) return 1;
    }
    return 0;
}

}


extern "C" {

u32 fn_80255834(void *, int);
int fn_80035EA8(int);
void fn_8000EC58(void *, int);
int fn_8016FA3C(void);
u8 *fn_8011C974(void);
int fn_8005F198(void);

extern char lbl_804087B6[];
extern char lbl_804087EB[];
extern char lbl_8040662D[];

int fn_8000B31C(void *x) {
    s16 v = fn_80392FE8(lbl_8063E954, x);
    int r = fn_802553B8(fn_802544D0(), v, 0);
    int i;
    if (r < 0) return 0;
    for (i = 0; i < 0x78; i++) {
        if (fn_80255834(fn_802544D0(), r) == 1) return 1;
        GSthreadManager::sInstance->sleepCurrentThread();
    }
    return 0;
}

void fn_8000D818(void *pv, int a, void *b, int c) {
    u8 *p = (u8 *)pv;
    OSMutex *l;
    int n;
    fn_8000D780((void **)&l, (OSMutex *)(p + 0x9DC4));
    n = *(int *)(p + 8);
    if (n >= 4) {
        fn_8000D7B8(&l, -1);
        return;
    }
    *(int *)(p + 0xc + n * 0xc) = a;
    *(void **)(p + 0x10 + n * 0xc) = b;
    *(int *)(p + 0x14 + n * 0xc) = c;
    *(int *)(p + 8) = *(int *)(p + 8) + 1;
    fn_8000D7B8(&l, -1);
}

int fn_800190B4(void *p) {
    u8 i;
    u8 n = ((u8 *)lbl_8063E970)[0x3e];
    for (i = 0; i < n; i++) {
        switch (fn_80019170((u8 *)p, i)) {
        case 0xd:
        case 0x4c:
            return 1;
        case 0:
            return 1;
        }
    }
    return 0;
}

void fn_800218E8(u8 *p) {
    int i;
    if (*(int *)(p + 0x54) < 4) {
        for (i = 0; i < 0x1e; i++) {
            if (*(int *)(p + 0x54) >= 4) break;
            GSthreadManager::sInstance->sleepCurrentThread();
        }
        fn_8000C52C(lbl_804087B6, i + 1);
        if (i == 0x1e) fn_8000C52C(lbl_804087EB);
    }
}

void fn_80021974(BattleObj *bp) {
    u8 *p = (u8 *)bp;
    int x = fn_80035D9C();
    if (fn_80035EA8(x) == 0x1000) {
        fn_8000EC58(p, x);
    } else if (fn_80035EA8(x) == 0x1001) {
        fn_8000EC58(p, x);
    } else if (*(int *)(p + 0x4c) != fn_8016FA3C()) {
        *(int *)(p + 0x54) = 1;
        bp->_9DE0 = bp->_9DDC;
    }
}

void fn_80021E34(u8 *p, u32 x) {
    if (fn_8011C974()[0x1b] == 1) {
        int r = fn_8005F198();
        if ((u8)r != 0 && (u8)r != 2 && (u8)r != 0xff) fn_8000C52C(lbl_8040662D, (u8)r);
        if ((u8)r <= 3 && (u8)r == 0) *(u32 *)(p + 0x48) = (u16)x;
    }
}

}


extern "C" {

int fn_80254E70(void *, int, int, int, int);
u32 fn_803DAE64(u32, u8, int, int);
int fn_8000BD6C(void *, u32);
void fn_8000C04C(void *, u32);
int fn_8000AFE0(void *);

extern char lbl_804061BA[];
extern char lbl_804062B4[];
extern char lbl_804093EB[];
extern char lbl_804093CD[];

int fn_8000B170(int a, int b, f32 f) {
    s16 v;
    int r;
    if (!fn_8000AFE0((void *)a)) return 0;
    v = fn_80392FE8(lbl_8063E954, (void *)a);
    r = fn_80254E70(fn_802544D0(), v, b, 0, 0);
    if (r < 0) return 0;
    fn_8000B030(r, (void *)a, (void *)b, f);
    return 1;
}

void fn_8000D68C(u8 *p) {
    if (p[0]) {
        fn_8000C52C(lbl_804061BA, lbl_804062B4);
        fn_8000D818(p, 8, 0, 0);
        while ((int)fn_8000D734(p) > 0) GSthreadManager::sInstance->sleepCurrentThread();
        fn_8000EEBC(p);
        *(int *)(p + 0x4) = 0;
        *(int *)(p + 0x4c) = 0;
        *(int *)(p + 0x50) = 0;
        *(int *)(p + 0x1068) = 0;
        memset(p + 0x2890, 0, 8);
    }
}

u32 fn_8000DFC4(void *pv, int a, u8 b, int c, int d) {
    u8 *p = (u8 *)pv;
    u8 m;
    if (b >= 7) fn_8000C52C(lbl_804093EB);
    m = p[0x3f];
    if (m == 4) return fn_803DAE64(a, b, c, d);
    if (m != 2) fn_8000C52C(lbl_804093CD, m);
    return fn_803DAE64(a & 1, b, c, d);
}

void fn_8000EBAC(u8 *p, u32 v) {
    u32 old = *(u32 *)(p + 0x28c4);
    if ((old & 0x80ff) != (v & 0x80ff) && *(int *)(p + 0x50) >= 2) {
        if ((old & 3) && !(v & 3)) {
            p[0x3c] |= 4;
        } else if ((old & 0xC0) && !(v & 0xC0)) {
            p[0x3c] |= 0x20;
        } else if ((old & 0xC) && !(v & 0xC)) {
            p[0x3c] |= 8;
        } else if ((old & 0x30) && !(v & 0x30)) {
            p[0x3c] |= 0x10;
        }
    }
    *(u32 *)(p + 0x28c8) = *(u32 *)(p + 0x28c4);
    *(u32 *)(p + 0x28c4) = v;
}

u32 fn_80017B08(void *p, u32 a, u32 b) {
    u32 r = fn_8000FECC(100);
    if (r < 50 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (!fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (r < 50) b = a;
    return b;
}

}


extern "C" {

int fn_80393050(void *, void *);
int fn_802550F8(void *, int, int, int, int);
int fn_80036554(int, int, int, int);

extern int lbl_8063E978;
extern char lbl_80408750[];
extern char lbl_80408786[];
extern char lbl_804089BC[];
extern char lbl_804089EA[];
extern char lbl_8063D335[3];
extern char lbl_8063D330[5];
extern char lbl_804092D6[];

int fn_8000B210(int a, int b, f32 f) {
    s16 v;
    int r;
    if (!fn_8000AFE0((void *)a)) return 0;
    v = fn_80392FE8(lbl_8063E954, (void *)a);
    fn_80393050(lbl_8063E954, (void *)a);
    fn_80393084(lbl_8063E954, (void *)a);
    r = fn_802550F8(fn_802544D0(), v, b, 0, 0);
    if (r < 0) return 0;
    fn_8000B030(r, (void *)a, (void *)b, f);
    return 1;
}

void fn_8002183C(u8 *p) {
    int i;
    if (*(int *)(p + 0x4c) != fn_8016FA3C() || *(int *)(p + 0x54) < 2) {
        for (i = 0; i < 0x1e; i++) {
            if (*(int *)(p + 0x4c) == fn_8016FA3C() && *(int *)(p + 0x54) >= 2) break;
            GSthreadManager::sInstance->sleepCurrentThread();
        }
        fn_8000C52C(lbl_80408750, i + 1);
        if (i == 0x1e) fn_8000C52C(lbl_80408786);
    }
}

void fn_80021F34(BattleObj *bp, int k) {
    u8 *p = (u8 *)bp;
    fn_8000C52C(lbl_804089BC, k);
    switch (k) {
    case 1:
        if (bp->_9DAE == 0) {
            fn_8000D818(p, 4, 0, 0);
            fn_8000C52C(lbl_804089EA, !(u8)fn_8000BCB0(0) ? lbl_8063D330 : lbl_8063D335);
        }
        bp->_9DAE++;
        break;
    case 0:
        break;
    }
}

int fn_80024700(void) {
    int x = fn_80035D9C();
    lbl_8063E978 = 0;
    if (fn_80035EA8(x) == 0x2d) {
        int k = fn_80035ED8(x);
        if (k >= 0 && k <= 3) {
            int n = fn_80036554(x, k, 0, 0);
            if (n >= 1 && n <= 0x1ed) {
                lbl_8063E978 = n + 0x2f;
                if ((u32)fn_8000B31C((void *)(n + 0x2f)) == 1) return 1;
            }
        }
    }
    fn_8000C52C(lbl_804092D6);
    return 0;
}

}


struct Word3 {
    u32 a, b, c;
};

extern "C" {

void fn_80254460(void *, void *, int, Word3 *, int);
void *fn_803930B8(void *, void *);
void *fn_80392E10(void *, void *);
void *fn_8039325C(void *, void *);
void fn_8000EDB0(void *);
void fn_80016640(void *, int, int, u32);
void fn_800195A8(void *);
int fn_80016EE0(void *, u8);
void fn_8001A56C(void *, u8);

extern Word3 lbl_803FB738;
extern void *lbl_8063E950;
extern u8 lbl_8044E9B8[];
extern u8 lbl_8044EA30[];
extern u8 lbl_80458D98[];
extern char lbl_80407C3D[];

void fn_8000ADC0(void *a, void *b) {
    Word3 buf = lbl_803FB738;
    void *m;
    fn_80254460(a, b, 3, &buf, 0);
    m = operator new(4);
    if (m) m = fn_803930B8(m, lbl_8044E9B8);
    lbl_8063E950 = m;
    m = operator new(4);
    if (m) m = fn_80392E10(m, lbl_8044EA30);
    lbl_8063E954 = m;
    m = operator new(4);
    if (m) m = fn_8039325C(m, lbl_80458D98);
    lbl_8063E958 = m;
    fn_8000B914(1, 0);
    fn_8000B914(2, 0);
    fn_8000B914(4, 0);
}

void fn_80016580(BattleObj *bp) {
    u8 *p = (u8 *)bp;
    bp->_9DAF = 0xff;
    bp->_9DB0 = 0;
    bp->_9DB1 = 0;
    bp->_9DB2 = 0;
    *(u16 *)(p + 0x281c) = 0;
    if (*(int *)(p + 0x4c) >= 2 && p[0x281f] == 0 && p[0x2820] == 0) {
        p[0x281e]++;
    } else {
        p[0x281e] = 0;
    }
    p[0x2820] = 0;
    p[0x281f] = 0;
    p[0x2822] = 0;
    p[0x2821] = 0;
    fn_8000EDB0(p);
    fn_80016640(p, 0, 1, bp->_9DE0);
    fn_800195A8(p);
}

int fn_800191D4(u8 *p, int v) {
    switch (*(int *)(*(u8 **)(*(u8 **)(p + 4) + 0x96c) + 0xc)) {
    case 0x78:
        return v == 0x36b;
    case 0x3f:
    case 0x4f:
        return v == 0x36e;
    case 0x55:
        return v == 0x371;
    case 0x65:
        return v == 0x374;
    case 0x2f:
        return v == 0x377;
    case 0x9c:
        return v == 0x37a;
    }
    return 0;
}

void fn_8001FBDC(BattleObj *bp, u8 start) {
    u8 i;
    for (i = start; i < bp->entCount; i++) {
        if ((u32)fn_8001A544((u8 *)&bp->ents[i]) == 1) {
            if ((u32)fn_80016EE0(bp, i) != 1) fn_8000C52C(lbl_80407C3D);
        } else if (bp->ents[i]._28_flag == 1) {
            fn_8001A56C(bp, i);
        }
    }
}

}


extern "C" {

u8 fn_80036E6C(int, u8, int);
u8 fn_80036E94(int, u8, int);
u8 fn_80024B50(int, int);
int fn_80023AB0(void *, u16, u32, u8, u16, int);
int fn_80023BC0(void *, void *, void *, u8, u16, int);

extern char lbl_804066A5[];

void fn_8000EAE0(void *pv, u8 k, u16 v) {
    u8 *p = (u8 *)pv;
    int x;
    if (v != 0) {
        x = fn_80035D9C();
        if (v != fn_80036554(x, k, 0, 0)) fn_8000C52C(lbl_804066A5);
        *(u16 *)(p + 0x2890 + k * 2) = v;
        (p + k)[0x2898] = fn_80036E6C(x, k, 0);
        (p + k)[0x289c] = fn_80036E94(x, k, 0);
        *(u32 *)(p + 0x28a0 + k * 4) = 0;
        p[0x28b0 + k] = 0;
        p[0x28b4 + k] = 0;
        p[0x28b8 + k] = 0;
        p[0x28bc + k] = 0;
    }
}

int fn_8001515C(void *p, int n, void *outv) {
    int *out = (int *)outv;
    u32 r;
    u8 c;
    int i;
    u8 cnt;
    u32 sum;
    if (n <= 0 || n >= 0x26a) return 0;
    *out = -1;
    r = fn_8000FECC(100);
    c = fn_80024B50(n, 0);
    if (c) return r < c;
    {
        cnt = fn_80024AEC((void *)n);
        sum = 0;
        for (i = 1; i < cnt; i++) {
            u8 w = fn_80024B50(n, i);
            if (w) {
                sum += w;
                if (r < sum) {
                    *out = i;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int fn_800239DC(void *p, int x, u8 *s, void *y) {
    u8 a = fn_80035ED8(x);
    u16 b = fn_80035EA8(x);
    int r = 0;
    if (*(u16 *)(s + 4)) r = fn_80023AB0(p, *(u16 *)(s + 4), (u32)y, a, b, x);
    if (!r && *(void **)(s + 0xc)) r = fn_80023BC0(p, *(void **)(s + 0xc), y, a, b, x);
    if (!r && *(void **)(s + 0x10)) r = fn_80023BC0(p, *(void **)(s + 0x10), y, a, b, x);
    return r;
}

}


extern "C" {

u32 fn_80009838(void);
u32 fn_80256E24(void *);

extern const f32 lbl_80640690;
extern const f32 lbl_80640688;
extern f32 lbl_8063D988;
extern char lbl_804072A2[];
extern char lbl_8040803A[];
extern char lbl_80405FC0[];

u32 fn_80017D10(void *p, u32 a, u32 b, u32 c) {
    u32 r = fn_8000FECC(100);
    if (r < 33 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (r < 66 && !fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (!fn_8000BD6C(p, c)) {
        fn_8000C04C(p, c);
        return c;
    }
    if (r < 33) return a;
    if (r < 66) c = b;
    return c;
}

int fn_8001EBF4(void *p, int k) {
    int r = 0;
    switch (k) {
    case 0xdf:
        r = 0x17f;
        break;
    case 0xe8:
        r = 0x180;
        break;
    case 0xe2:
        r = 0x181;
        break;
    case 0xe5:
        r = 0x182;
        break;
    case 0xd3:
        r = 0x183;
        break;
    case 0xdc:
        r = 0x184;
        break;
    case 0xd9:
        r = 0x185;
        break;
    case 0x43a:
        r = 0x186;
        break;
    case 0xd6:
        r = 0x187;
        break;
    default:
        fn_8000C52C(lbl_8040803A, k);
        break;
    }
    return r;
}

void fn_80020D44(u8 *p) {
    int i;
    if (*(int *)(p + 0x1170) != 0) {
        if (p[0x2669] < *(int *)(p + 0x1170)) {
            i = 0;
            while (fn_80256E24(p + 0x1268 + p[0x2669] * 0x100) == 1) {
                if (fn_80009838() != 1) {
                    if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                        fn_8000C52C(lbl_804072A2);
                        break;
                    }
                }
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
        fn_80020BF8(p);
    }
}

int fn_800247AC(u32 n) {
    char *str = lbl_80405FC0;
    int r;
    fn_8000C52C(str + 0x333e, fn_80035ED8(fn_80035D9C()));
    if (n < 1 || n > 0x1ed) {
        if (n != 0x259) fn_8000C52C(str + 0x337c, n);
        return 0;
    }
    if (lbl_8063E978 == 0) {
        fn_8000C52C(str + 0x33b9);
        return 0;
    }
    r = 0;
    if (lbl_8063E978 == n + 0x2f) {
        if (fn_8000B42C((void *)lbl_8063E978) == 1) {
            r = fn_8000B3B4((void *)lbl_8063E978, 0);
        } else {
            fn_8000C52C(str + 0x33dd);
            fn_8000B46C((void *)lbl_8063E978, 0);
        }
    }
    lbl_8063E978 = 0;
    return r;
}

}


extern "C" {

extern char lbl_80408A04[];
extern char lbl_80408890[];

void fn_8000DEC4(BattleObj *bp) {
    u8 *p = (u8 *)bp;
    u32 found;
    u8 i;
    u32 j;
    if (p[0x3f] == 2 || p[0x3f] == 4) {
        found = 0;
        memset(bp->_9DB8, 0, 4);
        for (i = 0; i < p[0x3f]; i++) {
            for (j = 0; j < 6; j++) {
                u16 v = fn_8000DFC4(p, i, j, 5, 0);
                if (v != 0 && v != 0xffff) {
                    bp->_9DB8[i]++;
                    if ((u8)fn_8000DFC4(p, i, j, 0x9f, 0)) found = 1;
                }
            }
        }
        if (found == 1) p[0x3c] |= 2;
    }
}

int fn_8001EF1C(void *p, int a, int b) {
    char *str = lbl_80405FC0;
    int r = 0;
    switch (a) {
    case 0x66:
        switch (b) {
        case 0x153:
        case 0x15b:
        case 0x15d:
            r = 0x1a1;
            break;
        default:
            fn_8000C52C(str + 0x209d, b);
            break;
        }
        break;
    case 0x67:
        switch (b) {
        case 0x142:
        case 0x1c7:
            r = 0x1a1;
            break;
        default:
            fn_8000C52C(str + 0x209d, b);
            break;
        }
        break;
    case 0x68:
        fn_8000C52C(str + 0x20e3, b);
        break;
    case 0x69:
        fn_8000C52C(str + 0x20e3, b);
        break;
    default:
        r = 0;
        fn_8000C52C(str + 0x2106);
        break;
    }
    return r;
}

void fn_80021FE8(u8 *p) {
    fn_8000C52C(lbl_80408A04, fn_80035ED8(fn_80035D9C()), fn_80035EA8(fn_80035D9C()));
    if (*(int *)(p + 0x1170) > 0) {
        int q = fn_80035D9C();
        if (q) {
            s8 i;
            for (i = p[0x2668] + 1; i < *(int *)(p + 0x1170); i++) {
                if (p[0x123c + i] == 0x1f && p[0x11d8 + i] == fn_80035ED8(q) &&
                    *(u16 *)(p + 0x11ec + i * 2) == fn_80035EA8(q)) {
                    fn_8000C52C(lbl_80408890);
                    p[0x2668] = i;
                }
            }
        }
    }
}

}


extern "C" {

void fn_8000EDB0(void *pv) {
    BattleObj *bp = (BattleObj *)pv;
    u8 *p = (u8 *)bp;
    int i;
    bp->entCount2 = bp->entCount;
    memcpy(bp->ents2, bp->ents, bp->entCount * sizeof(BattleEnt));
    *(int *)(p + 0x6198) = *(int *)(p + 0x28dc);
    memcpy(p + 0x619c, p + 0x28e0, *(int *)(p + 0x28dc) * 0x974);
    memset(bp->slots, 0, sizeof(bp->slots));
    for (i = 0; i < bp->entCount2; i++) {
        bp->ents2[i].ptr = p + 0x619c + bp->ents2[i].idx * 0x974;
        bp->slots[bp->ents2[i].slot] = &bp->ents2[i];
    }
    memcpy(bp->subB, bp->subA, sizeof(bp->subA));
    bp->subB[0]._00 = 0;
    bp->subB[1]._00 = 0;
    bp->entCount = 0;
    *(int *)(p + 0x28dc) = 0;
    fn_80019310((u8 *)&bp->subA[0]);
    fn_80019310((u8 *)&bp->subA[1]);
}

}


struct Out8 {
    u16 a;
    u16 b;
    u8 c;
    u8 d;
    u8 e;
    u8 pad;
};

extern "C" {

u16 fn_80391FFC(void *, u16);
u8 fn_80391200(void *, u16);
u8 fn_803919C4(void *, u16);
u8 fn_803919F8(void *, u16);
int fn_8039394C(void *, int);
int fn_80393918(void *, int);

extern u8 lbl_8063CE34[];
extern void *lbl_8063E988;
extern char lbl_80407304[];

void fn_800137EC(u8 *p, Out8 *out) {
    u16 v;
    int aa;
    u8 i;
    u8 n;
    Out8 *o;
    n = p[0x3e];
    for (i = 0; i < n; i++) {
        o = &out[i];
        v = fn_8000EA70(p, i);
        if (v == 0 || v == 0xffff) {
            o->a = 0;
            o->b = 0;
            continue;
        }
        o->a = v;
        aa = fn_803AC828();
        o->b = fn_8000DFC4(p, i, fn_803C8C48(aa, fn_803AC848(), 2, i), 0x9f, 0);
        o->c = fn_80391200(lbl_8063CE34, fn_80391FFC(lbl_8063CE34 + 0x10, v));
        o->d = fn_803919C4(lbl_8063CE34 + 0x10, v);
        o->e = fn_803919F8(lbl_8063CE34 + 0x10, v);
    }
}

void fn_8001585C(void *p, int n, int *outA, int *outB, u32 *cnt, u32 max) {
    u32 i;
    u8 c;
    if (!fn_80023E28(p, n, outA)) return;
    {
        int a = fn_8039394C(lbl_8063E988, n);
        fn_8000C52C(lbl_80407304, (s8)fn_80393918(lbl_8063E988, n), (s16)a);
    }
    c = fn_80024AEC((void *)n);
    if (*cnt + c > max) return;
    for (i = 0; i < c; i++) {
        s16 id = fn_80024A70((void *)n, i);
        outA[*cnt] = fn_8000BC78((void *)id);
        outB[*cnt] = (s16)fn_8000BCA4((void *)id);
        (*cnt)++;
    }
    fn_800241A8((u8 *)p, n, 0);
}

}


struct MsgSlot {
    u8 data[0x100];
};

struct MsgObj {
    u8 pad0[0x1170];
    int count;
    int ids[0x14];
    u8 arrF[0x14];
    u8 arrA[0x14];
    u16 arrB[0x14];
    s16 arrD[0x14];
    u8 arrC[0x14];
    u8 arrE[0x14];
    u32 mask;
    MsgSlot slots[0x14];
    s8 cur;
};

extern "C" {

int fn_80010078(void *, int *, int *, int *, int);
void fn_802565C0(void *, int, int, int, int, int);
void fn_80256850(void *, int, int, int);
int fn_80254A30(void *, int, int, int);

extern char lbl_80408AB9[];

int fn_8000FF64(u8 *p, void *x) {
    u8 *q = fn_8011C974();
    u8 m = p[0x3d];
    int t = q[0x18];
    int a, b, c;
    if ((m == 0 && t == 5) || (m == 1 && t == 3)) return 1;
    a = 0;
    b = 0;
    c = 0;
    fn_80010078(p, &a, &b, &c, (int)x);
    m = p[0x3d];
    if ((m == 0 && (a == 3 || b == 3)) || (m == 1 && (a == 2 || b == 2))) return 1;
    if (m == 0 && c == 2 && (a == 2 || b == 2)) return 1;
    return 0;
}

void fn_80015740(u8 *p, int n, int *ids) {
    int i;
    s16 v;
    int skip;
    fn_802565C0(p + 0x1070, n, 0, 0, -1, 0);
    for (i = 0; i < n; i++) {
        fn_80256850(p + 0x1070, i, fn_8000BC78((void *)ids[i]), 0);
        v = fn_8000BCA4((void *)ids[i]);
        switch (v) {
        case 0:
        case 1:
        case 0x657:
        case 0xac0:
        case 0x1116:
        case 0x157f:
            skip = 1;
            break;
        default:
            skip = 0;
            break;
        }
        if (!skip && v != -1) {
            fn_80254A30(fn_802544D0(), v, 1, 0xC000);
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
        }
    }
}

int fn_80023AB0(void *pv, u16 k, u32 y, u8 a, u16 b, int x) {
    u8 *p = (u8 *)pv;
    MsgObj *m = (MsgObj *)pv;
    u32 t = 0;
    s8 i;
    switch (k) {
    case 0:
        break;
    case 0x8e:
        if (y == 1) t = 0x38;
        break;
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
        if (y == 0) t = 0x37;
        else if (y == 1) t = 0x38;
        break;
    }
    if (t) {
        for (i = p[0x2668] + 1; i < *(int *)(p + 0x1170); i++) {
            if (t == m->arrC[i] && a == m->arrA[i] && b == *(u16 *)((u8 *)m->arrB + i * 2)) {
                fn_8000C52C(lbl_80408AB9);
                p[0x2668] = i;
            }
        }
    }
    return t != 0;
}

}


extern "C" {

void fn_8000E88C(u8 *);
u32 fn_803C9158(void);
void fn_80015E7C(void *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *, u8 *);

extern char lbl_80406534[];

void fn_8000E06C(void *pv) {
    BattleObj *bp = (BattleObj *)pv;
    u8 *p = (u8 *)pv;
    if (*(int *)(p + 0x50) > *(int *)(p + 0x4c)) return;
    *(int *)(p + 0x50) = *(int *)(p + 0x4c) + 1;
    bp->_9DAF = 0xff;
    bp->_9DB2 = 0;
    *(u16 *)(p + 0x106c) = 0;
    p[0x106e] = 0;
    p[0x106f] = 0xff;
    *(int *)(p + 0x44) = 0;
    *(int *)(p + 0x48) = 0;
    fn_8000E88C(p);
    fn_8000EBAC(p, fn_803C9158());
    *(u32 *)(p + 0x28c0) = fn_803C9158();
    *(u16 *)(p + 0x28cc) = 0;
    p[0x28ce] = 0;
    p[0x28cf] = 0;
    *(int *)(p + 0x28d4) = 0;
    *(int *)(p + 0x28d8) = 0;
    p[0x285e] = p[0x285c];
    p[0x285f] = p[0x285d];
    fn_80015E7C(p, p + 0x285c, p + 0x285d, p + 0x2824, p + 0x282c, p + 0x2834, p + 0x2844, p + 0x284c);
    *(int *)(p + 0x2670) = *(int *)(p + 0x266c);
    bp->_9DAD = bp->_9DAC;
    bp->_9DAC = 0;
    fn_8000C52C(lbl_80406534, fn_8000BC2C(), fn_8000BC50());
    if (bp->_9DB7) bp->_9DB7--;
}

}


extern "C" {

int fn_8000EEF4(void *, int *, int *, void *);
void fn_80015608(u8 *, int, int *, int *);
u32 fn_802568BC(void *);

extern int lbl_8063E980;
extern char lbl_80406312[];
extern char lbl_8040639E[];

void fn_8000AEB0(int k) {
    switch (k) {
    case 1:
        lbl_8063E980 = 1;
        break;
    case 2:
        lbl_8063E980 = 3;
        break;
    case 3:
        lbl_8063E980 = 2;
        break;
    case 4:
        lbl_8063E980 = 4;
        break;
    default:
        lbl_8063E980 = 0;
        break;
    }
    fn_80254A30(fn_802544D0(), 0, 0, 0);
    switch (lbl_8063E980) {
    case 1:
        fn_80254A30(fn_802544D0(), 0xac0, 0, 0);
        break;
    case 3:
        fn_80254A30(fn_802544D0(), 0x1116, 0, 0);
        break;
    case 2:
        fn_80254A30(fn_802544D0(), 0x657, 0, 0);
        break;
    case 4:
        fn_80254A30(fn_802544D0(), 0x157f, 0, 0);
        break;
    default:
        fn_80254A30(fn_802544D0(), 1, 0, 0);
        break;
    }
}

struct Pair2 {
    int x;
    int y;
};

#pragma push
#pragma optimize_for_size off
void fn_8000E194(u8 *p, void *x) {
    int a[8];
    int b[8];
    int i;
    int r;
    fn_80015234(p, 0);
    fn_80020D44(p);
    GSthreadManager::sInstance->sleepCurrentThread();
    fn_8000CD70(p);
    for (i = 0; i < 8; i++) a[i] = 0;
    for (i = 0; i < 8; i++) b[i] = 0;
    r = fn_8000EEF4(p, a, b, x);
    fn_80015608(p, r, a, b);
    if (*(int *)(p + 0x1070) > 0) {
        if (fn_80009838() == 1) {
            fn_8000C52C(lbl_80406312);
            fn_80015234(p, 0);
        } else {
            fn_802568BC(p + 0x1070);
            if (fn_80009838() == 1) {
                fn_8000C52C(lbl_8040639E);
                fn_80015234(p, 5);
            }
        }
    }
    *(int *)(p + 0x44) = 0;
    *(int *)(p + 0x48) = 0;
    p[0x5c] = 0;
    *(int *)(p + 0x4) = 3;
}
#pragma pop

u32 fn_80017BB4(void *p, u32 a, u32 b, u32 c, u32 d) {
    u32 r = fn_8000FECC(100);
    if (r < 25 && !fn_8000BD6C(p, a)) {
        fn_8000C04C(p, a);
        return a;
    }
    if (r < 50 && !fn_8000BD6C(p, b)) {
        fn_8000C04C(p, b);
        return b;
    }
    if (r < 75 && !fn_8000BD6C(p, c)) {
        fn_8000C04C(p, c);
        return c;
    }
    if (!fn_8000BD6C(p, d)) {
        fn_8000C04C(p, d);
        return d;
    }
    if (r < 25) return a;
    if (r < 50) return b;
    if (r < 75) d = c;
    return d;
}

}


extern "C" {

f32 fn_80393468(void *, u8);
int fn_803934D0(void *, u8);
void fn_80255684(void *, int, f32);
void fn_8025565C(void *, int, int, f32);
void fn_80255628(void *, int, int, f32);
int fn_80015968(void *, int, int, int, int *, int *);

extern const f32 lbl_8064067C;
extern char lbl_804072BB[];

void fn_8000B030(int h, void *a, void *b, f32 f) {
    int d;
    int c;
    u8 idx;
    f32 v;
    idx = fn_80393050(lbl_8063E954, a);
    v = fn_80393468(lbl_8063E958, idx);
    if ((f32)__fabs(v - lbl_80640678) > lbl_8064067C) fn_80255684(fn_802544D0(), h, v);
    c = fn_803934D0(lbl_8063E958, idx);
    d = fn_80393434(lbl_8063E958, (void *)idx);
    v = fn_8039349C(lbl_8063E958, (void *)idx);
    if ((u8)c && (u8)d != 0xff && v > lbl_8064067C) {
        int sel = fn_8000BBB4((void *)idx);
        fn_8025565C(fn_802544D0(), h, sel, v);
    }
    if ((f32)__fabs(lbl_80640678 - f) > lbl_8064067C) fn_80255628(fn_802544D0(), h, (int)b, f);
}

void fn_80015608(u8 *p, int n, int *ids, int *xs) {
    int buf[16];
    int l1;
    int l2;
    int cnt;
    int j;
    int i;
    u8 m;
    s16 id;
    if (!n) return;
    if (*(int *)(p + 0x1070)) {
        if (fn_80256E24(p + 0x1070) == 1) {
            fn_8000C52C(lbl_804072BB);
        } else {
            fn_80015234(p, 0);
            fn_8000C52C(lbl_804072BB);
        }
    }
    cnt = 0;
    for (i = 0; i < n; i++) {
        m = fn_80024AEC((void *)ids[i]);
        for (j = 0; j < m; j++) {
            int v;
            id = fn_80024A70((void *)ids[i], j);
            v = fn_8000BC78((void *)id);
            if (v < 0x4a38) {
                buf[cnt] = id;
            } else {
                buf[cnt] = fn_80015968(p, v, xs[i], 0, &l1, &l2);
            }
            cnt++;
        }
    }
    fn_80015740(p, cnt, buf);
}

}


extern "C" {

u32 fn_80254B80(void *, int);
u32 fn_80254B24(void *, int);
u32 fn_80254C18(void *, int);
int fn_80035F68(void *);
u32 fn_80256890(void *, int);
void fn_802567E8(void *);
void fn_80254AD0(void *, int);

extern char lbl_80408422[];
extern char lbl_8040844A[];

void fn_8000D26C(BattleObj *bp) {
    u8 *p = (u8 *)bp;
    char *str = lbl_80405FC0;
    if (p[0]) {
        fn_8000C52C(str + 0x1fa, str + 0x1eb);
        if (fn_80254B80(fn_802544D0(), 1) > 0x100 || fn_80254B80(fn_802544D0(), 2) > 0x100) {
            fn_8000C52C(str + 0x20e, fn_80254B80(fn_802544D0(), 1), fn_80254B80(fn_802544D0(), 2));
        }
        bp->_9DAE = 0;
        p[0x3c] = 0;
        *(int *)(p + 0x44) = 0;
        *(int *)(p + 0x48) = 0;
        p[0x5c] = 0;
        *(int *)(p + 0x4) = 1;
        fn_8000C52C(str + 0x23f, fn_80254B80(fn_802544D0(), 1) >> 10, fn_80254C18(fn_802544D0(), 1) >> 10,
                    fn_80254B24(fn_802544D0(), 1) >> 10);
        fn_8000C52C(str + 0x286, fn_80254B80(fn_802544D0(), 2) >> 10, fn_80254C18(fn_802544D0(), 2) >> 10,
                    fn_80254B24(fn_802544D0(), 2) >> 10);
    }
}

void fn_8000EC58(void *pv, int qi) {
    u8 *p = (u8 *)pv;
    u8 *q = (u8 *)qi;
    int n = fn_80035F68(q);
    int i;
    for (i = 0; i < n; i++) {
        u32 x;
        switch (*(u16 *)(*(u8 **)(q + 0x96c) + i * 0x1c + 4)) {
        case 0x13:
            x = *(u32 *)(p + 0x28c0);
            if (!(x & 3)) *(u32 *)(p + 0x28c0) = (x & 0xFFFF7F00) | 2;
            break;
        case 0x14:
            x = *(u32 *)(p + 0x28c0);
            if (!(x & 0xC0)) *(u32 *)(p + 0x28c0) = (x & 0xFFFF7F00) | 0x80;
            break;
        case 0x15:
            x = *(u32 *)(p + 0x28c0);
            if (!(x & 0xC)) *(u32 *)(p + 0x28c0) = (x & 0xFFFF7F00) | 8;
            break;
        case 0x16:
            x = *(u32 *)(p + 0x28c0);
            if (!(x & 0x30)) *(u32 *)(p + 0x28c0) = (x & 0xFFFF7F00) | 0x20;
            break;
        case 0x12:
            *(u32 *)(p + 0x28c0) |= 0x8000;
            break;
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
            *(u32 *)(p + 0x28c0) &= 0xFFFF7F00;
            break;
        case 0x78:
            *(u32 *)(p + 0x28c0) &= ~0x8000;
            break;
        }
    }
}

void fn_80020BF8(void *pv) {
    u8 *p = (u8 *)pv;
    u32 r;
    int i;
    if (*(int *)(p + 0x1070) > 0) {
        u32 v = fn_80256890(p + 0x1070, 0);
        if (v >= 0x76b && v <= 0x110b) {
            u32 d = v - 0x76b;
            r = d % 5;
            fn_8000C52C(lbl_80408422, d / 5 + 1, r + 1);
            if (r == 2) fn_80015234(p, 0);
        }
    }
    if (p[0x2669] < *(int *)(p + 0x1170)) {
        int a = fn_8039394C(lbl_8063E988, *(int *)(p + 0x1174 + p[0x2669] * 4));
        s8 b = fn_80393918(lbl_8063E988, *(int *)(p + 0x1174 + p[0x2669] * 4));
        fn_8000C52C(lbl_8040844A, p[0x2669], b, (s16)a, *(int *)(p + 0x1174 + p[0x2669] * 4));
    }
    for (i = 0; i < 0x14; i++) fn_802567E8(p + 0x1268 + i * 0x100);
    fn_80254AD0(fn_802544D0(), 2);
    *(int *)(p + 0x1170) = 0;
    *(int *)(p + 0x1264) = 0;
    *(s8 *)(p + 0x2668) = -1;
    p[0x2669] = 0;
    *(int *)(p + 0x266c) = 0;
}

}


extern "C" {

void fn_80256BC0(void *, int);

extern char lbl_804067D4[];
extern char lbl_804067F7[];
extern char lbl_80407494[];
extern char lbl_804074C2[];
extern const f32 lbl_806406A0;

void fn_80015234(void *pv, int mode) {
    u8 *p = (u8 *)pv;
    int i;
    if (*(int *)(p + 0x1070) != 0) {
        if (mode > 0) {
            fn_80256BC0(p + 0x1070, mode);
            i = 0;
            while (fn_8000B720() == 1) {
                if (fn_80009838() != 1) {
                    if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                        fn_8000C52C(lbl_804072A2);
                        break;
                    }
                }
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
        i = 0;
        while (fn_80256E24(p + 0x1070) == 1) {
            if (fn_80009838() != 1) {
                if (!(i++ < (int)(lbl_80640688 + lbl_80640690 * lbl_8063D988))) {
                    fn_8000C52C(lbl_804072A2);
                    break;
                }
            }
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
        }
        fn_802567E8(p + 0x1070);
        *(u16 *)(p + 0x106c) = 0;
        p[0x106f] = 0xff;
        fn_80254AD0(fn_802544D0(), 1);
    }
}

int fn_80010078(void *p, int *a, int *b, int *c, int k) {
    u8 *q = fn_8011C974();
    u8 n = q[0x18];
    int i;
    for (i = 0; i < n - 1; i++) {
        if (i >= 10) {
            fn_8000C52C(lbl_804067D4, n);
            break;
        }
        switch (q[0x80 + i]) {
        case 0:
            (*a)++;
            break;
        case 1:
            (*b)++;
            break;
        case 2:
            (*c)++;
            break;
        default:
            fn_8000C52C(lbl_804067F7, i + 1, q[0x80 + i]);
            break;
        }
    }
    switch (k) {
    case 0:
        (*a)++;
        break;
    case 1:
        (*b)++;
        break;
    case 2:
        (*c)++;
        break;
    default:
        fn_8000C52C(lbl_804067F7, n, k);
        break;
    }
    if (*a == *b) return 2;
    return *a <= *b;
}

void fn_80015D38(u8 *p) {
    if (*(int *)(p + 0x58) == 0 && p[0x281f] + p[0x2820] > 0) {
        *(int *)(p + 0x58) = 1;
        fn_8000C52C(lbl_80407494);
    }
    if (*(int *)(p + 0x58) <= 1 && *(int *)(p + 0x4c) >= 3) {
        if (p[0x3d] == 0) {
            if (p[0x285c] == 1 || p[0x285d] == 1) {
                *(int *)(p + 0x58) = 2;
                fn_8000C52C(lbl_804074C2);
            }
        } else {
            f32 x = *(u16 *)(p + 0x2844) + *(u16 *)(p + 0x2848);
            f32 y = *(u16 *)(p + 0x2846) + *(u16 *)(p + 0x284a);
            if ((p[0x285c] <= 2 && x < lbl_806406A0) || (p[0x285d] <= 2 && y < lbl_806406A0)) {
                *(int *)(p + 0x58) = 2;
                fn_8000C52C(lbl_804074C2);
            }
        }
    }
}

}


extern "C" {

extern char lbl_80406820[];
extern char lbl_80406844[];

int fn_80010968(void *p, int *a, int *b, int *c, int k) {
    u8 *q = fn_8011C974();
    u16 n = *(u16 *)(q + 0x16);
    int i;
    for (i = 0; i < n - 1; i++) {
        if (i >= 100) {
            fn_8000C52C(lbl_80406820, n);
            break;
        }
        switch (q[0x1c + i]) {
        case 0:
            (*a)++;
            break;
        case 1:
            (*b)++;
            break;
        case 2:
            (*c)++;
            break;
        default:
            fn_8000C52C(lbl_80406844, n, q[0x1c + i]);
            break;
        }
    }
    switch (k) {
    case 0:
        (*a)++;
        break;
    case 1:
        (*b)++;
        break;
    case 2:
        (*c)++;
        break;
    default:
        fn_8000C52C(lbl_80406844, n, q[0x1c + i]);
        break;
    }
    if (*a == *b) return 2;
    return *a <= *b;
}

}


extern "C" {

int fn_80162A90(u32);

int fn_8000C378(void) {
    u8 *q = fn_8011C974();
    u32 id = 0xFFFFFFFF;
    switch (*(int *)(q + 0x10)) {
    case 1000:
        if (q[0x14] == 0) id = 0x23;
        else id = 0x1b1;
        break;
    case 1001:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x24;
        else id = 0x1b2;
        break;
    case 1002:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x25;
        else id = 0x1b3;
        break;
    case 1003:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x26;
        else id = 0x1b4;
        break;
    case 1004:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x27;
        else id = 0x1b5;
        break;
    case 1005:
        if (q[0x14] == 6) {
            if (*(u16 *)(q + 0x9a) == 1) id = 0x28;
            else id = 0x1b6;
        } else {
            id = 0x1b7;
        }
        break;
    case 1006:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x29;
        else id = 0x1b8;
        break;
    case 1007:
        if (q[0x14] == 10) {
            if (*(u16 *)(q + 0x9a) == 1) id = 0x2a;
            else id = 0x1b9;
        } else {
            id = 0x1ba;
        }
        break;
    case 1008:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x2b;
        else id = 0x1bb;
        break;
    case 1009:
        id = !fn_80162A90(0x39) ? 0x2c : 0x1bc;
        break;
    }
    if (id == 0xFFFFFFFF) {
        fn_8000C52C(lbl_80405FC0);
        return 0;
    }
    return fn_80162A90(id);
}

}


extern "C" {

u32 fn_803BACA4(void *, u8, int, int);

void fn_8000E88C(u8 *p) {
    u8 i;
    u8 n;
    memset(p + 0x2890, 0, 8);
    memset(p + 0x2898, 0, 4);
    memset(p + 0x289c, 0, 4);
    memset(p + 0x28a0, 0, 0x10);
    memset(p + 0x28b0, 0, 4);
    memset(p + 0x28b4, 0, 4);
    memset(p + 0x28b8, 0, 4);
    memset(p + 0x28bc, 0, 4);
    n = p[0x3e];
    for (i = 0; i < n; i++) {
        int aa;
        int v;
        *(u16 *)(p + 0x2890 + i * 2) = fn_8000EA70(p, i);
        aa = fn_803AC828();
        v = fn_803C8C48(aa, fn_803AC848(), 2, i);
        p[0x2898 + i] = v;
        if ((u8)v <= 5) {
            u32 t;
            fn_803AC828();
            p[0x289c + i] = fn_803BACA4(fn_803AC848(), i, 0x1a, 0);
            fn_803AC828();
            *(u32 *)(p + 0x28a0 + i * 4) = fn_803BACA4(fn_803AC848(), i, 0x3b, 0);
            fn_803AC828();
            p[0x28b0 + i] = fn_803BACA4(fn_803AC848(), i, 0x43, 0);
            fn_803AC828();
            t = fn_803BACA4(fn_803AC848(), i, 0x35, 0);
            p[0x28b4 + i] = (t >> 10) & 3;
            p[0x28b8 + i] = (t >> 4) & 7;
            fn_803AC828();
            p[0x28bc + i] = fn_803BACA4(fn_803AC848(), i, 0x42, 0);
        } else {
            p[0x289c + i] = 0;
            *(u32 *)(p + 0x28a0 + i * 4) = 0;
            p[0x28b0 + i] = 0;
            p[0x28b4 + i] = 0;
            p[0x28b8 + i] = 0;
            p[0x28bc + i] = 0;
        }
    }
}

}


extern "C" {

void fn_8000E2C8(void *pv) {
    u8 *p = (u8 *)pv;
    BattleObj *bp = (BattleObj *)pv;
    char *str = lbl_80405FC0;
    switch (*(int *)(p + 0x54)) {
    case 1: {
        int t = fn_8016FA3C();
        if (*(int *)(p + 0x4c) < t) {
            fn_8000C52C(str + 0x5a5, t);
            *(u16 *)(p + 0x106c) = 0;
            p[0x106e] = 1;
            p[0x106f] = 0xff;
            *(int *)(p + 0x4c) = t;
            bp->_9DB6 = 0;
            if (*(int *)(p + 0x1170) > 0 && p[0x2669] < *(int *)(p + 0x1170) &&
                fn_80256E24(p + 0x1268 + p[0x2669] * 0x100) == 1) {
                int a;
                s8 b;
                bp->_9DB6 = 1;
                a = fn_8039394C(lbl_8063E988, *(int *)(p + 0x1174 + p[0x2669] * 4));
                b = fn_80393918(lbl_8063E988, *(int *)(p + 0x1174 + p[0x2669] * 4));
                fn_8000C52C(str + 0x5d1, p[0x2669], b, (s16)a, *(int *)(p + 0x1174 + p[0x2669] * 4));
            }
            fn_80020D44(p);
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(p);
            fn_80016580(bp);
            *(int *)(p + 0x54) = 2;
            if (*(int *)(p + 0x1170) == 0) fn_8000C52C(str + 0x618);
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (*(int *)(p + 0x1170) > 0) {
            fn_80020E34(p);
            *(int *)(p + 0x54) = 4;
            if (*(int *)(p + 0x1170) > 0 && p[0x123c] == 0x1d && *(s8 *)(p + 0x2668) < 0) p[0x2668] = 0;
        } else {
            fn_8000C52C(str + 0x639);
            *(int *)(p + 0x54) = 4;
        }
        break;
    }
}

}


extern "C" {

extern char lbl_8040601C[];

int fn_8000C57C(void) {
    u8 *q = fn_8011C974();
    u32 id = 0xFFFFFFFF;
    switch (*(int *)(q + 0x10)) {
    case 1000:
        if (q[0x14] == 0) id = 0x19;
        else id = 0x251;
        break;
    case 1001:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x1a;
        else id = 0x252;
        break;
    case 1002:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x1b;
        else id = 0x253;
        break;
    case 1003:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x1c;
        else id = 0x254;
        break;
    case 1004:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x1d;
        else id = 0x255;
        break;
    case 1005:
        if (q[0x14] == 6) {
            if (*(u16 *)(q + 0x9a) == 1) id = 0x1e;
            else id = 0x256;
        } else {
            id = 0x257;
        }
        break;
    case 1006:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x1f;
        else id = 0x258;
        break;
    case 1007:
        if (q[0x14] == 10) {
            if (*(u16 *)(q + 0x9a) == 1) id = 0x20;
            else id = 0x259;
        } else {
            id = 0x25a;
        }
        break;
    case 1008:
        if (*(u16 *)(q + 0x9a) == 1) id = 0x21;
        else id = 0x25b;
        break;
    case 1009:
        if (fn_80162A90(0x39) == 0) id = 0x22;
        else id = (q[0x145] < (u32)fn_80162A90(0x249)) ? 0x25c : 0;
        break;
    }
    if (id == 0) return 0;
    if (id == 0xFFFFFFFF) {
        fn_8000C52C(lbl_8040601C);
        return 0;
    }
    return fn_80162A90(id);
}

}


extern "C" {

void fn_800213D0(void *, int, int, int *, int *);

extern char lbl_804084BD[];

void fn_80020EB8(void *pv, int k) {
    MsgObj *m = (MsgObj *)pv;
    int buf1[4];
    int buf2[4];
    u8 n;
    int i;
    n = fn_80024AEC((void *)m->ids[k]);
    for (i = 0; i < n; i++) {
        s16 id = fn_80024A70((void *)m->ids[k], i);
        buf1[i] = fn_8000BC78((void *)id);
        buf2[i] = (s16)fn_8000BCA4((void *)id);
        if (buf1[i] >= 0x4a38) fn_800213D0(m, buf1[i], m->arrD[k], &buf1[i], &buf2[i]);
    }
    if (*(int *)&m->slots[k]) fn_8000C52C(lbl_804084BD);
    fn_802565C0(&m->slots[k], n, 0, 0, -1, 0);
    for (i = 0; i < n; i++) {
        int v;
        int skip;
        fn_80256850(&m->slots[k], i, buf1[i], 0);
        v = buf2[i];
        switch (v) {
        case 0:
        case 1:
        case 0x657:
        case 0xac0:
        case 0x1116:
        case 0x157f:
            skip = 1;
            break;
        default:
            skip = 0;
            break;
        }
        if (!skip && v != -1) {
            if (fn_80254A30(fn_802544D0(), v, 2, 0xC000) == 0) {
                fn_802567E8(&m->slots[k]);
                break;
            }
            GSthreadManager::sInstance->sleepCurrentThread();
            fn_8000CD70(m);
        }
    }
    m->mask |= 1 << k;
}

}


extern "C" {

void fn_800153A8(u8 *, int, int, int, int);

void fn_80014EE8(u8 *p, int k, u32 flag) {
    char *str = lbl_80405FC0;
    int id;
    int out;
    if (*(int *)(p + 0x4c) == 0) {
        if (flag == 1) {
            if (k == 0 || k == 1) {
                id = 0x70;
            } else {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            }
        } else {
            if (k == 0 || k == 1) {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            } else {
                id = fn_8000FECC(100) < 50 ? 0x70 : 0x71;
            }
        }
    } else {
        if (k == 0 || k == 1) {
            id = fn_8000FE58(p, 0x56, 0x57, 0x58, 0x59);
        } else {
            id = fn_80014E88(p, 0x56, 0x58, 0x59);
        }
    }
    out = -1;
    if (!fn_800150E0(p, id, &out)) id = 0;
    if (id) {
        fn_800153A8(p, id, out, k, 0);
        if (fn_80009838() == 1) {
            fn_8000C52C(str + 0x352);
            fn_80015234(p, 0);
        } else {
            if (fn_802568BC(p + 0x1070) == 1) {
                fn_8000C52C(str + 0x1250, id);
            } else {
                fn_8000C52C(str + 0x128b, id);
            }
            if (fn_80009838() == 1) {
                fn_8000C52C(str + 0x3de);
                fn_80015234(p, 5);
            }
            fn_800241A8(p, id, 0);
        }
    } else {
        fn_8000C52C(str + 0x12bd);
    }
    *(u16 *)(p + 0x2810) = id;
}

}


struct ChoiceIn {
    u8 b0;
    u8 pad[0xb];
    int c[2];
};

extern "C" {

int fn_800210FC(MsgObj *, int, u8, u8, u16, s16, u8, u32);

extern char lbl_804082E1[];
extern char lbl_804082B2[];

int fn_8001FA9C(BattleObj *bp, int idx, ChoiceIn *s) {
    u16 w;
    u8 b;
    BattleEnt *e;
    int i;
    e = &bp->ents[idx];
    w = e->_20;
    b = e->slot;
    if (w != 0x104) return 0;
    for (i = 0; i < 2; i++) {
        switch (s->c[i]) {
        case 0x9c:
            if (s->b0 <= 3) {
                switch (w) {
                case 0xcf:
                case 0x104:
                    if ((u32)fn_800210FC((MsgObj *)bp, fn_8000FECC(100) < 50 ? 0x196 : 0x198, idx, b, w, e->_32[s->b0], 0xff, 1) == 1)
                        return 1;
                    break;
                default:
                    fn_8000C52C(lbl_804082E1, w);
                    break;
                }
            } else {
                fn_8000C52C(lbl_804082B2);
            }
            break;
        case 0:
            break;
        }
    }
    return 0;
}

}


extern "C" {

int fn_80035E58(int);

extern char lbl_80409258[];

void fn_80024480(BattleObj *bp, int x) {
    u8 *p = (u8 *)bp;
    u8 c0, c1, c2, c3, c4;
    u8 n;
    u8 i;
    if (*(int *)(p + 0x50) > 0) return;
    if (bp->_9DB5 < 4) bp->_9DB5++;
    if (bp->_9DB3 == 1) return;
    fn_8000C52C(lbl_80409258);
    bp->_9DB3 = 1;
    c0 = 0;
    c1 = 0;
    c2 = 0;
    c3 = 0;
    c4 = 0;
    n = !fn_80035E58(x) ? 2 : 4;
    for (i = 0; i < n; i++) {
        switch (fn_8000EA70(p, i)) {
        case 0x17e:
            if (i) {
                bp->_9DB4 = 0;
                return;
            }
            c0++;
            break;
        case 0x17f:
            if (i) {
                bp->_9DB4 = 0;
                return;
            }
            c1++;
            break;
        case 0x1cb:
        case 0x1cc:
            c3++;
            break;
        case 0xf8:
        case 0x1c1:
        case 0x1c2:
            c2++;
            break;
        case 0x89:
        case 0xe9:
        case 0x118:
        case 0x119:
        case 0x11a:
            c4++;
            break;
        }
    }
    {
        u8 sum = c0 + c1 + c3 + c2;
        if (sum == 0 || c4 != 0 || c0 >= 2 || c1 >= 2 || c3 >= 2 || c2 >= 2) {
            bp->_9DB4 = 0;
            return;
        }
        bp->_9DB4 = sum;
    }
}

}


struct Sub1C {
    u8 *q;
    u8 k;
    u8 n;
    u8 cnt;
    u8 bits;
    u16 h[4];
    u8 a[8];
    u8 b[4];
};

struct Ev1C {
    u8 slot;
    u8 _01[3];
    u16 type;
    u8 _06[6];
    u32 _0c;
    u8 _10[4];
    u16 _14;
    u16 _16;
    u8 _18[4];
};

extern "C" {

void fn_80019380(Sub1C *out, u8 k, u8 *q) {
    u32 f = *(u32 *)((u8 *)lbl_8063E970 + 0x28c0);
    u8 i;
    out->q = q;
    out->k = k;
    out->n = fn_80035F68(q);
    out->cnt = 0;
    out->bits = 0;
    memset(out->h, 0, 8);
    for (i = 0; i < out->n; i++) {
        Ev1C *e = (Ev1C *)(*(u8 **)(q + 0x96c) + i * 0x1c);
        switch (e->type) {
        case 0x64:
            out->cnt++;
            out->bits |= 1 << e->slot;
            break;
        case 2:
            if (e->_14 > e->_16 && e->slot <= 3) out->h[e->slot] |= 1;
            break;
        case 3:
            if (e->_14 > e->_16 && e->slot <= 3) out->h[e->slot] |= 2;
            break;
        case 0x68:
            if (e->_0c == 0x26e && e->slot <= 3) out->h[e->slot] |= 4;
            break;
        case 0x12:
            f = 0x8000;
            break;
        case 0x13:
            f = 2;
            break;
        case 0x14:
            f = 0x80;
            break;
        case 0x15:
            f = 8;
            break;
        case 0x16:
            f = 0x20;
            break;
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
        case 0x78:
            f = 0;
            break;
        }
    }
    memcpy(out->a, (u8 *)lbl_8063E970 + 0x2890, 8);
    memcpy(out->b, (u8 *)lbl_8063E970 + 0x2898, 4);
    *(u32 *)((u8 *)lbl_8063E970 + 0x28c0) = f;
}

}


extern "C" {

f32 fn_80393504(void *, int);
f32 fn_80393538(void *, int);
f32 fn_8039356C(void *, int);
f32 fn_803935A0(void *, int);
f32 fn_803935D4(void *, int);
f32 fn_80393608(void *, int);
f32 fn_8039363C(void *, int);
f32 fn_80393670(void *, int);
f32 fn_803936A4(void *, int);
f32 fn_803936D8(void *, int);
f32 fn_8039370C(void *, int);
void fn_802563D8(void *, int, void *, int);
void fn_80255C6C(void *, int, f32, f32, f32, f32, f32, f32);
void fn_80255DF0(void *, int, f32, f32, f32, f32, f32, f32);
void fn_80255F74(void *, int, f32, f32, f32, f32, f32);
void fn_80256264(void *, int, f32, f32, f32);
void fn_802560F0(void *, int, f32, f32, f32);

void fn_8000B914(int idx, void *y) {
    int t = ((int (*)(void *, int))fn_803934D0)(lbl_8063E958, idx);
    int sel;
    f32 x0, x1, x2, x3, x4;
    f32 a;
    if (!(u8)t) return;
    sel = fn_8000BBB4((void *)idx);
    if (y) {
        fn_802563D8(fn_802544D0(), sel, y, 0);
        return;
    }
    a = fn_80393504(lbl_8063E958, idx);
    switch ((u8)t) {
    case 8:
        x4 = fn_80393538(lbl_8063E958, idx);
        x3 = fn_8039356C(lbl_8063E958, idx);
        x2 = fn_803935A0(lbl_8063E958, idx);
        x1 = fn_803935D4(lbl_8063E958, idx);
        x0 = fn_80393608(lbl_8063E958, idx);
        fn_80255C6C(fn_802544D0(), sel, x4, x3, x2, x1, x0, a);
        break;
    case 9:
        x0 = fn_80393538(lbl_8063E958, idx);
        x1 = fn_8039356C(lbl_8063E958, idx);
        x2 = fn_803935A0(lbl_8063E958, idx);
        x3 = fn_803935D4(lbl_8063E958, idx);
        x4 = fn_80393608(lbl_8063E958, idx);
        fn_80255DF0(fn_802544D0(), sel, x0, x1, x2, x3, x4, a);
        break;
    case 10:
        x0 = fn_80393538(lbl_8063E958, idx);
        x1 = fn_8039356C(lbl_8063E958, idx);
        x2 = fn_803935A0(lbl_8063E958, idx);
        x3 = fn_803935D4(lbl_8063E958, idx);
        fn_80255F74(fn_802544D0(), sel, x0, x1, x2, x3, a);
        break;
    case 11:
        x4 = fn_8039363C(lbl_8063E958, idx);
        x3 = fn_80393670(lbl_8063E958, idx);
        fn_80256264(fn_802544D0(), sel, x4, x3, a);
        break;
    case 12:
        a = fn_803936A4(lbl_8063E958, idx);
        x4 = fn_803936D8(lbl_8063E958, idx);
        x3 = fn_8039370C(lbl_8063E958, idx);
        fn_802560F0(fn_802544D0(), sel, a, x4, x3);
        break;
    }
}

}


extern "C" {

void fn_800153A8(u8 *p, int n, int sel, int x, int y) {
    int buf1[4];
    int buf2[4];
    u8 m;
    int cnt;
    int i;
    if (n <= 0 || n >= 0x26a) return;
    {
        if (*(int *)(p + 0x1070)) {
            if (fn_80256E24(p + 0x1070) == 1) {
                fn_8000C52C(lbl_804072BB);
            } else {
                fn_80015234(p, 0);
                fn_8000C52C(lbl_804072BB);
            }
        }
        m = fn_80024AEC((void *)n);
        buf1[0] = 0;
        buf1[1] = 0;
        buf1[2] = 0;
        buf1[3] = 0;
        buf2[0] = 0;
        buf2[1] = 0;
        buf2[2] = 0;
        buf2[3] = 0;
        cnt = 0;
        for (i = 0; i < m; i++) {
            s16 id = fn_80024A70((void *)n, i);
            int v;
            if (i > 0 && sel != -1 && fn_80024B50(n, i) && i != sel) continue;
            v = fn_8000BC78((void *)id);
            if (v < 0x4a38) {
                buf1[cnt] = v;
                buf2[cnt] = (s16)fn_8000BCA4((void *)id);
            } else {
                fn_80015968(p, v, x, y, &buf1[cnt], &buf2[cnt]);
            }
            cnt++;
        }
        fn_802565C0(p + 0x1070, cnt, 0, 0, -1, 0);
        for (i = 0; i < cnt; i++) {
            int v;
            int skip;
            fn_80256850(p + 0x1070, i, buf1[i], 0);
            v = buf2[i];
            switch (v) {
            case 0:
            case 1:
            case 0x657:
            case 0xac0:
            case 0x1116:
            case 0x157f:
                skip = 1;
                break;
            default:
                skip = 0;
                break;
            }
            if (!skip && v != -1) {
                fn_80254A30(fn_802544D0(), v, 1, 0xC000);
                GSthreadManager::sInstance->sleepCurrentThread();
                fn_8000CD70(p);
            }
        }
    }
}

}


extern "C" {

int fn_8001ECE4(void *p, int a, int b) {
    char *str = lbl_80405FC0;
    int r = 0;
    switch (a) {
    case 0x66:
        switch (b) {
        case 0xe:
        case 0x60:
        case 0x9f:
        case 0xbb:
        case 0xe8:
        case 0x135:
        case 0x150:
            r = 0x1a7;
            break;
        case 0x4a:
        case 0x126:
        case 0x1a1:
        case 0x1c3:
            r = 0x1a8;
            break;
        case 0x16f:
            r = 0x1a1;
            break;
        default:
            fn_8000C52C(str + 0x209d, b);
            break;
        }
        break;
    case 0x67:
        switch (b) {
        case 0x6a:
        case 0x6e:
        case 0x6f:
        case 0x70:
        case 0x97:
        case 0xd3:
        case 0x14e:
            r = 0x1a9;
            break;
        case 0x68:
            r = 0x1a5;
            break;
        case 0x85:
            r = 0x1aa;
            break;
        case 0x16f:
            r = 0x1a1;
            break;
        case 0x69:
        default:
            fn_8000C52C(str + 0x20bf, b);
            break;
        }
        break;
    case 0x68:
        switch (b) {
        case 0x61:
        case 0x16f:
        case 0x18d:
            r = 0x1a4;
            break;
        default:
            fn_8000C52C(str + 0x20e3, b);
            break;
        }
        break;
    case 0x69:
        switch (b) {
        case 0x16f:
            r = 0x1a6;
            break;
        default:
            fn_8000C52C(str + 0x20e3, b);
            break;
        }
        break;
    default:
        r = 0;
        fn_8000C52C(str + 0x2106);
        break;
    }
    return r;
}

}


extern "C" {

void fn_80023790(MsgObj *m, int unused, Ev1C *e, u8 slot) {
    char *str = lbl_80405FC0;
    u8 *mi;
    s8 i;
    for (i = m->cur + 1; i < m->count; i++) {
        if (m->arrB[i] != 0x1001) continue;
        mi = (u8 *)m + i;
        switch (mi[0x123c]) {
        case 0x22:
            if (slot == mi[0x1250]) {
                if (e->_14 > e->_16 && e->slot == mi[0x11d8]) {
                    fn_8000C52C(str + 0x30b0);
                    m->cur = i;
                } else {
                    fn_8000C52C(str + 0x30eb);
                }
            }
            break;
        case 0x20:
            if (slot == mi[0x1250]) {
                switch (e->type) {
                case 0xa:
                case 0xe:
                case 0x89:
                    if (e->slot == mi[0x11d8]) {
                        fn_8000C52C(str + 0x30b0, i);
                        m->cur = i;
                    } else {
                        fn_8000C52C(str + 0x311f);
                    }
                    break;
                }
            }
            break;
        case 0x1e:
            if (slot == mi[0x1250]) {
                int j;
                for (j = 0; j < 2; j++) {
                    switch (((int *)((u8 *)e + 0xc))[j]) {
                    case 0x2f:
                    case 0x131:
                    case 0x152:
                    case 0x26e:
                        if (e->slot == mi[0x11d8]) {
                            fn_8000C52C(str + 0x3023, i);
                            m->cur = i;
                        } else {
                            fn_8000C52C(str + 0x311f);
                        }
                        break;
                    case 0:
                        break;
                    }
                }
            }
            break;
        case 0x34:
            if (slot == mi[0x1250] && e->type == 0x86) {
                fn_8000C52C(str + 0x2f4f);
                m->cur = i;
            }
            break;
        case 0x35:
            if (e->type == 0x87) {
                fn_8000C52C(str + 0x2f4f);
                m->cur = i;
            }
            break;
        }
    }
}

}


extern "C" {

extern char lbl_804068E0[];

int fn_80011290(void *p, int *cnt, int *out, int unused, int k) {
    u8 *q = fn_8011C974();
    int lv = fn_80162A90(0x38);
    fn_8000C52C(lbl_804068E0, *(u16 *)(q + 0x16), lv, k);
    switch (k) {
    case 0: {
        u16 t = *(u16 *)(q + 0x16);
        if (lv >= 5 && t == lv + 1) {
            out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x206 : 0x207;
            (*cnt)++;
        } else {
            switch (t) {
            case 10:
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x200 : 0x201;
                (*cnt)++;
                break;
            case 0x32:
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x202 : 0x203;
                (*cnt)++;
                break;
            case 0x64:
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x204 : 0x205;
                (*cnt)++;
                break;
            }
        }
        break;
    }
    case 1:
    case 2: {
        int t = *(u16 *)(q + 0x16) - 1;
        if (lv >= 5 && t > lv) {
            if (t >= 100) {
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23b : 0x23c;
                (*cnt)++;
            } else {
                out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23d : 0x23e;
                (*cnt)++;
            }
        } else if (t >= 8) {
            out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x23f : 0x240;
            (*cnt)++;
        } else {
            out[*cnt] = !(u8)fn_8000BCB0(0) ? 0x241 : 0x242;
            (*cnt)++;
        }
        break;
    }
    }
    return *cnt;
}

}


extern "C" {

u8 *fn_8016F3FC(int *);
int fn_800242D0(void *, u8, u32);

extern char lbl_804088C5[];

void fn_80021BA8(BattleObj *bp, int hdr) {
    u8 *p = (u8 *)bp;
    int len;
    OSMutex *l;
    u8 *data;
    int off;
    if (*(int *)(p + 0x50) > fn_8016FA3C()) return;
    data = fn_8016F3FC(&len);
    if (len == 0) return;
    fn_8000D780((void **)&l, &bp->mutex2);
    bp->_9DDC++;
    p[0x5d] = hdr >> 28;
    *(int *)(p + 0x60) = hdr & 0x0FFFFFFF;
    off = *(int *)(p + 0x64) - 4;
    *(int *)(p + 0x64) = len;
    memcpy(p + 0x68, data, len + 2);
    if (*(int *)(p + 0x54) == 4) {
        if ((u32)len >= (u32)(off + 8) && data[off] == 0x15) {
            fn_8000D818(p, 5, (void *)off, bp->_9DDC);
            fn_800218E8(p);
        } else if (data[0] == 0x18) {
            int r = fn_800242D0(p, 4, 0);
            if (r > 0) {
                u8 sl = data[1];
                int r2;
                if (sl <= 3) {
                    *(u16 *)(p + 0x2890 + sl * 2) = 0;
                    (p + sl)[0x2898] = 0xff;
                    (p + sl)[0x289c] = 0;
                    *(u32 *)(p + 0x28a0 + sl * 4) = 0;
                    (p + sl)[0x28b0] = 0;
                    (p + sl)[0x28b4] = 0;
                    (p + sl)[0x28b8] = 0;
                    (p + sl)[0x28bc] = 0;
                }
                r2 = fn_800242D0(p, 3, 0);
                if ((u32)r2 == (u32)(r + 4)) {
                    fn_8000D818(p, 6, (void *)r2, bp->_9DDC);
                    fn_800218E8(p);
                }
            }
        }
    } else if (*(int *)(p + 0x54) == 3) {
        fn_8000C52C(lbl_804088C5);
    }
    fn_8000D7B8(&l, -1);
}

}


extern "C" {

struct PktObj {
    u8 pad[0x68];
    u8 data[1];
};

int fn_800242D0(void *pv, u8 key, u32 start) {
    u8 *p = (u8 *)pv;
    char *str;
    u32 total;
    u32 pos;
    u8 *end;
    u8 *cur;
    total = *(u32 *)(p + 0x64);
    str = lbl_80405FC0;
    cur = p + start + 0x68;
    end = p + total + 0x68;
    pos = start;
    while (cur < end) {
        u8 t = *cur;
        int sz;
        if (key == t) return pos;
        sz = 0;
        switch (t) {
        case 1:
            sz = 4;
            break;
        case 2:
            sz = 4;
            break;
        case 3:
            sz = 4;
            break;
        case 4:
            sz = 4;
            break;
        case 5:
            sz = 4;
            break;
        case 6:
            sz = 4;
            break;
        case 7:
            sz = 8;
            break;
        case 8:
            sz = 8;
            break;
        case 9:
            sz = 8;
            break;
        case 10:
            sz = 8;
            break;
        case 11:
            sz = 4;
            break;
        case 12:
            sz = 8;
            break;
        case 13:
            sz = 8;
            break;
        case 14:
            sz = 8;
            break;
        case 15:
            sz = 4;
            break;
        case 16:
            sz = 8;
            break;
        case 17:
            sz = 8;
            break;
        case 18:
            sz = 8;
            break;
        case 19:
            sz = 4;
            break;
        case 20:
            sz = 4;
            break;
        case 21:
            sz = 4;
            break;
        case 22:
            sz = 4;
            break;
        case 23:
            sz = 4;
            break;
        case 24:
            sz = 4;
            break;
        case 25:
            sz = 4;
            break;
        case 26:
            sz = 4;
            break;
        case 30:
            sz = 4;
            break;
        default:
            fn_8000C52C(str + 0x31ea, t);
            fn_8000C52C(str + 0x1640, start, pos);
            fn_8000C52C(str + 0x165d, total);
            cur = end;
            break;
        }
        cur += sz;
        pos += sz;
    }
    return -1;
}

}


extern "C" {

int fn_80035E68(int);

void fn_8000D3C4(BattleObj *bp) {
    u8 *p = (u8 *)bp;
    char *str = lbl_80405FC0;
    if (p[0]) {
        int x;
        fn_8000C52C(str + 0x1fa, str + 0x2cd);
        x = fn_80035D9C();
        if (x) {
            int v = fn_80035E58(x);
            p[0x3d] = v;
            p[0x3e] = !(u8)v ? 2 : 4;
            p[0x3f] = fn_80035E68(x) == 2 ? 2 : 4;
        } else {
            fn_8000C52C(str + 0x2d9);
        }
        *(int *)(p + 0x40) = 0;
        *(int *)(p + 0x44) = 0;
        *(int *)(p + 0x48) = 0;
        *(int *)(p + 0x4c) = 0;
        *(int *)(p + 0x50) = 0;
        *(int *)(p + 0x54) = 0;
        *(int *)(p + 0x58) = 0;
        *(int *)(p + 0x1068) = 0;
        *(u16 *)(p + 0x106c) = 0;
        p[0x106e] = 0;
        p[0x106f] = 0xff;
        *(u16 *)(p + 0x280e) = 0;
        *(u16 *)(p + 0x2810) = 0;
        *(u16 *)(p + 0x2812) = 0;
        *(u16 *)(p + 0x281c) = 0;
        p[0x285d] = 0;
        p[0x285c] = 0;
        p[0x285f] = 0;
        p[0x285e] = 0;
        p[0x281e] = 0;
        p[0x2820] = 0;
        p[0x281f] = 0;
        p[0x2822] = 0;
        p[0x2821] = 0;
        memset(p + 0x2824, 0, 8);
        memset(p + 0x282c, 0, 8);
        memset(p + 0x2834, 0, 0x10);
        memset(p + 0x2844, 0, 8);
        memset(p + 0x284c, 0, 0x10);
        memset(p + 0x285c, 0, 2);
        memset(p + 0x285e, 0, 2);
        memset(p + 0x2860, 0, 0x18);
        memset(p + 0x2878, 0, 0x18);
        memset(p + 0x2890, 0, 8);
        memset(p + 0x2898, 0, 4);
        memset(p + 0x289c, 0, 4);
        memset(p + 0x28a0, 0, 0x10);
        memset(p + 0x28b0, 0, 4);
        memset(p + 0x28b4, 0, 4);
        memset(p + 0x28b8, 0, 4);
        memset(p + 0x28bc, 0, 4);
        *(u32 *)(p + 0x28c0) = 0;
        *(u32 *)(p + 0x28c4) = 0;
        *(u32 *)(p + 0x28c8) = 0;
        *(u16 *)(p + 0x28cc) = 0;
        p[0x28ce] = 0;
        p[0x28cf] = 0;
        p[0x28d0] = 0;
        bp->_9DAF = 0xff;
        bp->_9DB0 = 0;
        bp->_9DB1 = 0;
        bp->_9DB2 = 0;
        bp->_9DB3 = 0;
        bp->_9DB4 = 0;
        bp->_9DB5 = 0;
        bp->_9DB6 = 0;
        bp->_9DB7 = 0;
        *(int *)(p + 0x4) = 2;
        *(int *)(p + 0x28dc) = 0;
        *(int *)(p + 0x6198) = 0;
        bp->entCount = 0;
        bp->entCount2 = 0;
        fn_80019310((u8 *)&bp->subA[0]);
        fn_80019310((u8 *)&bp->subA[1]);
        memset(bp->prev, 0, 0x10);
        memset(bp->slots, 0, 0x10);
        bp->_9DAC = 0;
        bp->_9DAD = 0;
    }
}

}


extern "C" {

int fn_8000BD6C(void *pv, u32 k) {
    switch (k) {
    case 0x79:
    case 0xf2:
    case 0xf3:
    case 0xf5:
    case 0xf6:
    case 0x173:
    case 0x1b8:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x1) != 0;
    case 0xf7:
    case 0xf8:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x1001) != 0;
    case 0xf1:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x2001) != 0;
    case 0x77:
    case 0x78:
    case 0x1b7:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x2) != 0;
    case 0xf9:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x1004) != 0;
    case 0x7b:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x200000) != 0;
    case 0x7a:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x400000) != 0;
    case 0x74:
    case 0x75:
    case 0x1b9:
    case 0x1ba:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x10) != 0;
    case 0xea:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x20) != 0;
    case 0x104:
    case 0x105:
    case 0x106:
    case 0x107:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x820) != 0;
    case 0xec:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x40) != 0;
    case 0x122:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100040) != 0;
    case 0xed:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x80) != 0;
    case 0x124:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100080) != 0;
    case 0x123:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100000) != 0;
    case 0xee:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100) != 0;
    case 0x126:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100100) != 0;
    case 0xef:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x201) != 0;
    case 0x125:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x100201) != 0;
    case 0xeb:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x400) != 0;
    case 0xf0:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x2000) != 0;
    case 0x100:
    case 0x155:
    case 0x15a:
    case 0x15f:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x10000) != 0;
    case 0x101:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x20000) != 0;
    case 0x102:
    case 0x103:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x40000) != 0;
    case 0x85:
        return (*(u32 *)((u8 *)pv + 0x266c) & 0x80000) != 0;
    case 0x76:
    case 0xf4:
        break;
    }
    return 0;
}

}


extern "C" {

void fn_8000C04C(void *pv, u32 k) {
    switch (k) {
    case 0x79:
    case 0xf2:
    case 0xf3:
    case 0xf5:
    case 0xf6:
    case 0x173:
    case 0x1b8:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x1;
        break;
    case 0xf7:
    case 0xf8:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x1001;
        break;
    case 0xf1:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x2001;
        break;
    case 0x77:
    case 0x78:
    case 0x1b7:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x2;
        break;
    case 0xf9:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x1004;
        break;
    case 0x7b:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x200000;
        break;
    case 0x7a:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x400000;
        break;
    case 0x74:
    case 0x75:
    case 0x1b9:
    case 0x1ba:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x10;
        break;
    case 0xea:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x20;
        break;
    case 0x104:
    case 0x105:
    case 0x106:
    case 0x107:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x820;
        break;
    case 0xec:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x40;
        break;
    case 0x122:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100040;
        break;
    case 0xed:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x80;
        break;
    case 0x124:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100080;
        break;
    case 0x123:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100000;
        break;
    case 0xee:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100;
        break;
    case 0x126:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100100;
        break;
    case 0xef:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x201;
        break;
    case 0x125:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x100201;
        break;
    case 0xeb:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x400;
        break;
    case 0x108:
    case 0x109:
    case 0x110:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x800;
        break;
    case 0x127:
    case 0x128:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x1000;
        break;
    case 0xf0:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x2000;
        break;
    case 0x100:
    case 0x155:
    case 0x15a:
    case 0x15f:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x10000;
        break;
    case 0x101:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x20000;
        break;
    case 0x102:
    case 0x103:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x40000;
        break;
    case 0x85:
        *(u32 *)((u8 *)pv + 0x266c) |= 0x80000;
        break;
    case 0x76:
    case 0xf4:
        break;
    }
}

}


extern "C" {

u8 fn_803939B4(void *, int);

extern char lbl_80408508[];

int fn_800210FC(MsgObj *m, int id, u8 a, u8 slot, u16 w, s16 v, u8 e, u32 flag) {
    BattleObj *bp = (BattleObj *)m;
    int local;
    if (id == 0) return 0;
    if (id >= 0x26a) return 0;
    if (m->count >= 20) return 0;
    if (*(int *)((u8 *)m + 0x1070) && (u32)fn_800241D4(m, (void *)id) == 1) return 0;
    if (flag == 1) {
        if ((id >= 0x72 && id <= 0x9c) || (id >= 0x9d && id <= 0xb4)) {
            int c = m->count;
            if (c >= 1) {
                switch (id) {
                case 0x73:
                case 0x7c:
                case 0x7d:
                case 0x81:
                case 0x93: {
                    int i;
                    for (i = 0; i < c - 1; i++) {
                        if (id == m->ids[i]) {
                            if (id != 0x73) {
                                int s1 = fn_8039394C(lbl_8063E988, id);
                                fn_8000C52C(lbl_80408508, (s8)fn_80393918(lbl_8063E988, id), (s16)s1, id);
                            }
                            return 0;
                        }
                    }
                    break;
                }
                }
            }
        } else {
            int c;
            if (!((int (*)(void *, int))fn_80023E28)(m, id)) return 0;
            if (!fn_8001515C(m, id, &local)) return 0;
            c = m->count;
            if (c >= 1 && id == m->ids[c - 1]) return 0;
            if (slot <= 3) {
                BattleEnt *x = bp->slots[slot];
                BattleEnt *y = bp->prev[slot];
                if (x && y && x->_54 == id && x->_30 == y->_30 && x->_30 <= 5) return 0;
            }
        }
    }
    m->ids[m->count] = id;
    m->arrF[m->count] = a;
    m->arrA[m->count] = slot;
    m->arrB[m->count] = w;
    m->arrD[m->count] = v;
    m->arrC[m->count] = fn_803939B4(lbl_8063E988, id);
    m->arrE[m->count] = e;
    m->count++;
    if (a < 4) bp->ents[a]._54 = id;
    return 1;
}

}


extern "C" {

u8 fn_80393980(void *, int);

int fn_80023E28(void *pv, int id, void *unused) {
    int r;
    u8 t;
    if (id <= 0 || id >= 0x26a) return 0;
    t = fn_80393980(lbl_8063E988, id);
    r = 0;
    switch (t) {
    case 0:
        r = 1;
        break;
    case 0x3b:
        if ((u32)fn_80024178((u8 *)pv, id, 0) == 1) r = 0;
        else r = 1;
        break;
    case 0x3c:
        if ((u32)fn_80024178((u8 *)pv, id, 0) == 1 || (u32)fn_80024178((u8 *)pv, id, 1) == 1) r = 0;
        else r = 1;
        break;
    case 0x3d:
        if ((u32)fn_80024178((u8 *)pv, id, 0) == 1 || (u32)fn_80024178((u8 *)pv, id, 1) == 1 || (u32)fn_80024178((u8 *)pv, id, 2) == 1) r = 0;
        else r = 1;
        break;
    case 0x3e:
        if ((u32)fn_80024178((u8 *)pv, id, 0) == 1 || (u32)fn_80024178((u8 *)pv, id, 1) == 1 || (u32)fn_80024178((u8 *)pv, id, 2) == 1 || (u32)fn_80024178((u8 *)pv, id, 3) == 1) r = 0;
        else r = 1;
        break;
    case 0x3f:
        if ((u32)fn_80024178((u8 *)pv, id, 0) == 1 || (u32)fn_80024178((u8 *)pv, id, 1) == 1 || (u32)fn_80024178((u8 *)pv, id, 2) == 1 || (u32)fn_80024178((u8 *)pv, id, 3) == 1 || (u32)fn_80024178((u8 *)pv, id, 4) == 1) r = 0;
        else r = 1;
        break;
    case 0x40: {
        int c = *(int *)((u8 *)pv + 0x1170);
        r = 1;
        if (c >= 1 && id >= 0xea && id <= 0x1ba) {
            int i;
            for (i = 0; i < c; i++) {
                if (id == *(int *)((u8 *)pv + 0x1174 + i * 4)) {
                    r = 0;
                    break;
                }
            }
        }
        break;
    }
    case 0x41:
        if (id == *(s16 *)((u8 *)pv + 0x280e) || id == *(s16 *)((u8 *)pv + 0x2810) || id == *(s16 *)((u8 *)pv + 0x2812)) {
            r = 0;
        } else {
            r = 1;
            switch (id) {
            case 0x1cd:
            case 0x1ce:
            case 0x1cf:
                switch (*(s16 *)((u8 *)pv + 0x2812)) {
                case 0x1cd:
                case 0x1ce:
                case 0x1cf:
                    r = 0;
                    break;
                }
                break;
            case 0x1d0:
            case 0x1d1:
                switch (*(s16 *)((u8 *)pv + 0x2812)) {
                case 0x1d0:
                case 0x1d1:
                    r = 0;
                    break;
                }
                break;
            }
        }
        break;
    case 0x42:
        r = 1;
        break;
    }
    return r;
}

}


extern "C" {

extern char lbl_80408A51[];

struct MsgArr {
    u8 pad[0x2860];
    u8 a[4][6];
    u8 b[4][6];
};

struct MsgBits {
    u32 side : 4;
    u32 a : 4;
    u32 kind : 8;
    u32 val : 16;
};

void fn_800220F0(u8 *p, u32 msg) {
    u32 side = ((MsgBits *)&msg)->side;
    u32 a = (msg >> 24) & 0xF;
    u32 kind = (msg >> 16) & 0xFF;
    u32 val = msg & 0xFFFF;
    fn_8000C52C(lbl_80408A51, msg >> 28, a, kind, val);
    switch (kind) {
    case 2:
        if (*(int *)(p + 0x1070) == 0) {
            int s = side & 1;
            int ev = 0;
            switch (++*(int *)(p + 0x28d4 + s * 4)) {
            case 1:
                if (*(int *)(p + 0x28d4 + !s * 4) == 0) ev = !*(int *)(p + 0x4c) ? 0xb6 : 0xb7;
                else ev = 0xba;
                break;
            case 2:
                ev = 0xb9;
                break;
            }
            if (ev) fn_8000D818(p, 2, (void *)ev, s);
        }
        break;
    case 3:
        p[0x28d0] = 1;
        if (p[0x28cf] != 0xff) p[0x28cf]++;
        if (*(int *)(p + 0x1070) == 0) {
            int flag = 0;
            if (p[0x28cf] == 1) {
                int x = fn_80035D9C();
                u8 r;
                if (!x) return;
                r = ((u8(*)(int, u32, int))fn_80036E6C)(x, a, 0);
                if (r <= 5) {
                    if (((MsgArr *)p)->a[side][r] & 0xF8) {
                        flag = 1;
                    } else if (((MsgArr *)p)->b[side][r] < 0x21 && ((MsgArr *)p)->b[side][r] != 0) {
                        flag = 1;
                    }
                }
            }
            fn_8000D818(p, 3, (void *)val, flag);
        }
        break;
    }
}

}

#pragma optimize_for_size off
#pragma dont_inline off
