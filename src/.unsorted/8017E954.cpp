#include ".unsorted/8017E954.hpp"

#include "common.hpp"

extern "C" {

u8 fn_801817D8(void* p);
u8 fn_801817F8(void* p);
u8 fn_80181818(void* p);
u8 fn_80181838(void* p);
u8 fn_80180DA8(void* p);

void fn_801C673C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
int fn_801C66AC(void* p);
void fn_801C6650(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
u32 fn_801C42E8(void* p);
u32 fn_801C42A8(void* p);
void fn_801C4470(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);
u16 fn_801C4618(void* p);

void fn_8017F5C0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C673C(a1, a1, a2, a3, a4, a5, a6, a7); }
void fn_8017F6E0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C66AC((void*)a1); }
void fn_8017F6E8(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C6650(a1, a1, a2, a3, a4, a5, a6, a7); }
void fn_8017FE6C(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C42E8((void*)a1); }
void fn_8017FE74(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C42A8((void*)a1); }
void fn_80180050(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C4470(a1, a1, a2, a3, a4, a5, a6, a7); }
void fn_801817D0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801817D8((void*)a1); }
void fn_801817F0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801817F8((void*)a1); }
void fn_80181810(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80181818((void*)a1); }
void fn_80181830(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80181838((void*)a1); }
void fn_80181850(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_80180DA8((void*)a1); }
void fn_801818F0(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7) { fn_801C4618((void*)a1); }

}

#define F8(p, o) (*(u8*)((u8*)(p) + (o)))
#define F16(p, o) (*(u16*)((u8*)(p) + (o)))
#define F32(p, o) (*(u32*)((u8*)(p) + (o)))

extern "C" {

#pragma dont_inline on
#pragma optimize_for_size on

#pragma dont_inline off
static inline u16 inl_sel(u8 kind, u16 a, u16 c) {
    switch (kind) {
    case 1:
        return a;
    case 2:
        return c;
    default:
        return 0;
    }
}
#pragma dont_inline on

u8 fn_80182848(void* t, void* p, u32 v);

void fn_801C6780(u32 a, u32 b);
u32 fn_801C65B4(u32 a, u32 b);
void* fn_803AC848(void* p);
void* fn_803AC840(void* p);
void fn_801C3B64(void* p);
void* fn_801C3AA4(void* p);
void* fn_8017D100(void* p);
u32 fn_801C4184(void* p);
u32 fn_801C4150(void* p);
void* fn_8017D170(void* p, u32 a);
void* fn_8017E398(void* p);
u32 fn_801C1898(void* p);
u32 fn_801C4340(void* p);
int fn_8038F86C(void* p, u32 a);
u8 fn_801C18BC(void);
u8 fn_801C18E4(void);
u8 fn_801C190C(void);
u8 fn_801C1934(void);
u8 fn_801C195C(void);
u8 fn_801C1984(void);
u8 fn_801C19AC(void);
extern void* lbl_8063F24C;
extern u32 lbl_8048DFA8[];
extern u8 lbl_8063CE34[];

u32 fn_8017F740(void* t, void* p);
u8 fn_801803D8(void* t, void* p);
u16 fn_8017FE94(void* t, void* p);
int fn_8017FEE0(void* t, void* p);
int fn_80180058(void* t, void* p);
u8 fn_801802D0(void* t, void* p);
u8 fn_80180328(void* t, void* p);
u8 fn_80180380(void* t, void* p);
u16 fn_8018028C(void* p);
u8 fn_801818D8(void* p);

int fn_8017EA58(int x) { return x ^ 2; }
void fn_8017F624(void* t, u32 a, u32 b) { fn_801C6780(a, b); }
void fn_8017F630(void* t, u32 a, u32 b) { fn_801C65B4(a, b); }
u32 fn_8017EB68(void* p) { if (p == 0) return 0; return F32(p, 0x24); }
u16 fn_8017EB80(void* p) { if (p == 0) return 0; return F16(p, 0x0); }
u32 fn_8017EB98(void* p) { if (p == 0) return 0; return F32(p, 0x4); }
u32 fn_8017EBB0(void* p) { if (p == 0) return 0; return F32(p, 0x790); }
void* fn_8017F05C(void* p) { if (p == 0) return 0; return (void*)F32(p, 0x8); }
u16 fn_8017FE7C(void* p) { if (p == 0) return 0; return F16(p, 0x4); }
u32 fn_801800B8(void* p) { if (p == 0) return 0; return F32(p, 0x10); }
u8 fn_80180DA8(void* p) { if (p == 0) return 0; return F8(p, 0x7f0); }
u16 fn_80181380(void* t, void* p) { if (p == 0) return 0; return F16(p, 0x854); }
u16 fn_80181398(void* t, void* p) { if (p == 0) return 0; return F16(p, 0x852); }
u16 fn_801813B0(void* t, void* p) { if (p == 0) return 0; return F16(p, 0x850); }
u32 fn_80181700(void* p) { if (p == 0) return 0; return F32(p, 0x794); }
u8 fn_801817D8(void* p) { if (p == 0) return 0; return F8(p, 0x7ec); }
u8 fn_801817F8(void* p) { if (p == 0) return 0; return F8(p, 0x7ed); }
u8 fn_80181818(void* p) { if (p == 0) return 0; return F8(p, 0x7ee); }
u8 fn_80181838(void* p) { if (p == 0) return 0; return F8(p, 0x7ef); }
u8 fn_801818D8(void* p) { if (p == 0) return 0; return F8(p, 0x7f2); }
u32 fn_80181D7C(void* p) { if (p == 0) return 0; return F8(p, 0x864); }
u16 fn_80182988(void* p) { if (p == 0) return 0; return F16(p, 0x846); }
u8 fn_8018505C(void* p) { if (p == 0) return 0; return F8(p, 0xd); }
u8 fn_80185524(void* p, int i) { if (p == 0) return 0; return F8((u8*)p + i, 0x844); }

void fn_8017F224(void* p, u16 a, u16 b, u32 v) {
    if (p == 0) return;
    ((u32(*)[2])((u8*)p + 0x74))[a][b] = v;
}

#pragma dont_inline reset
static inline u8 inl_get7F1(void* p) { if (p == 0) return 0; return F8(p, 0x7f1); }
u8 fn_80181858(void* t, void* p) { void* q = p; return inl_get7F1(q); }
#pragma dont_inline on

void fn_8017EC50(u16* p) {
    for (u16 i = 0; i < 0x51; i++) p[i] = 0;
}

int fn_8017F244(int a, int b) {
    if (b > 0) {
        a += b;
        if (a > 200) a = 200;
        return a;
    } else if (b < 0) {
        int c = a + b;
        if (c < -200) return -200;
        return c;
    }
    return a;
}

int fn_8017F280(int a, int b, int c) {
    s16 t = (b * 100) / 100;
    s16 u = ((t - 50) * c) / 50;
    return fn_8017F244(a, u);
}

u32 fn_80180A4C(void* t, void* p) { return fn_801C42E8(fn_8017F05C(p)); }
u32 fn_80180A74(void* t, void* p) { return fn_801C42A8(fn_8017F05C(p)); }
u16 fn_80180A9C(void* t, void* p) { return fn_8017FE7C(fn_801C3AA4(fn_8017F05C(p))); }

void fn_8017EC1C(void* p) { fn_803AC848(p); fn_803AC840(p); }

int fn_801859A8(void* p) {
    if (p == 0) return 0;
    fn_801C3B64(p);
    return 1;
}

u32 fn_8017F740(void* t, void* p) {
    void* q = fn_801C3AA4(p);
    if (q == 0) return 0;
    return F16(q, 6);
}

u32 fn_8017F778(void* t, void* p) { fn_8017D100(lbl_8063F24C); return fn_801C4184(p); }

u8 fn_8017E9A0(u32 x) {
    u8 i;
    for (i = 0; i < 4; i++) {
        u32 v = lbl_8048DFA8[i];
        if (v == x) return i;
    }
    return 0;
}

u16 fn_80180250(void* t, void* p) { fn_8017D100(lbl_8063F24C); return fn_8018028C(fn_801C3AA4(p)); }
u32 fn_8018043C(void* t, void* p) { return fn_8017F740(t, fn_8017F05C(p)); }
u8 fn_80180A10(void* t, void* p) { return fn_801803D8(t, fn_8017F05C(p)); }
u16 fn_80180AC8(void* t, void* p) { return fn_8017FE94(t, fn_8017F05C(p)); }
int fn_80180B04(void* t, void* p) { return fn_8017FEE0(t, fn_8017F05C(p)); }
int fn_80180B9C(void* t, void* p) { return fn_80180058(t, fn_8017F05C(p)); }
u8 fn_80180C68(void* t, void* p) { return fn_801802D0(t, fn_8017F05C(p)); }
u8 fn_80180CA4(void* t, void* p) { return fn_80180328(t, fn_8017F05C(p)); }
u8 fn_80180CE0(void* t, void* p) { return fn_80180380(t, fn_8017F05C(p)); }

u32 fn_80180478(void* t, void* p) { void* q = fn_8017F05C(p); fn_8017D100(lbl_8063F24C); return fn_801C4150(q); }
u32 fn_801804B8(void* t, void* p) { void* q = fn_8017F05C(p); fn_8017D100(lbl_8063F24C); return fn_801C4184(q); }

u16 fn_8017F7B0(void* p, u32 a) {
    if (p == 0) return 0;
    void* q = fn_8017D170(p, a);
    if (q == 0) return 0;
    return F16(q, 0);
}
u8 fn_8017F7F4(void* p, u32 a) {
    if (p == 0) return 0;
    void* q = fn_8017D170(p, a);
    if (q == 0) return 0;
    return F8(q, 2);
}
u16 fn_8018028C(void* p) {
    if (p == 0) return 0;
    void* q = fn_8017E398(p);
    if (q == 0) return 0;
    return F16(q, 0xa);
}

u32 fn_80180C24(void* t, void* p) {
    if (fn_801C1898(t) == 1) return fn_801C4340(p);
    return 0;
}

int fn_8017F2A8(int a, u32 b, u32 c) { return fn_8017F244(a, fn_8038F86C(lbl_8063CE34 + 8, c)); }

int fn_80181990(void* t, void* p) { int a = fn_801817D8(p); return a >= fn_801C18BC(); }
int fn_801819D8(void* t, void* p) { int a = fn_801817F8(p); return a >= fn_801C18E4(); }
int fn_80181A20(void* t, void* p) { int a = fn_80181818(p); return a >= fn_801C190C(); }
int fn_80181A68(void* t, void* p) { int a = fn_80181838(p); return a >= fn_801C1934(); }
int fn_80181AB0(void* t, void* p) { int a = fn_80180DA8(p); return a >= fn_801C195C(); }
int fn_80181AF8(void* t, void* p) { int a = fn_801818D8(p); return a >= fn_801C1984(); }
int fn_80181B40(void* t, void* p) { int a = fn_801818D8(p); return a <= fn_801C19AC(); }

void* fn_8017D118(void* p);
u16 fn_8017F9F0(void* t, void* p, int b);
u32 fn_8017F838(void* t, void* p, u32 c);
u32 fn_801C47A0(void* p);
u8 fn_801C19D4(void);
u8 fn_801C19F8(void);
u32 fn_801C1874(void* p);
u32 fn_8039763C(void* p, void* q);
void fn_801BFAE0(void* p, void* f, void* s);
struct Unk81504;
int fn_801813C8(void* p, void* unused, Unk81504* s);
int fn_8017F280(int a, int b, int c);
int fn_803918C0(void* p, u16 a);
int fn_8039195C(void* p, u16 a);
int fn_80391928(void* p, u16 a);
u32 fn_801C4260(void* p);
int fn_8038FE7C(void* p, u16 a);
u8 fn_801C66F4(u32 c);
u32 fn_8017FF5C(void* t, void* p, s8 c, float f);
u8 fn_801C4858(void* p, u32 a, u32 b, u32 c);
u8 fn_801C1A1C(void* p);
u16 fn_8017E900(void);
struct Unk82A74;
void fn_80182A74(Unk82A74* p);
extern u8 lbl_8063F266;
extern u8 lbl_8048DFE0[];
u32 fn_801C2418(void* p);
u32 fn_801C2474(void* p);
u8 fn_801C66E0(void* p);
u8 fn_801C1A40(void);
void* fn_801C3AC8(void* p);
u32 fn_801C1730(void* p);
extern u16 lbl_80641688;
extern u16 lbl_8064168A;
extern u16 lbl_8064168C;
extern u16 lbl_8064168E;
extern u32 lbl_8048DFB8[];

u8 fn_8017E954(u32 x) {
    if (x == 0) return 0;
    u8 i;
    for (i = 0; i < 4; i++) {
        u32 v = lbl_8048DFB8[i];
        if (v == x) return i;
    }
    return 0;
}

u32 fn_8017FB0C(void* t, void* p, int b) {
    if (b == 0) return 0;
    return fn_8017F9F0(t, p, b) == b;
}

u16 fn_8017FE94(void* t, void* p) {
    void* q = fn_801C3AA4(p);
    if (q == 0) return 0;
    void* r = fn_8017E398(q);
    if (r == 0) return 0;
    return F16(r, 0);
}

u32 fn_80180554(void* t, void* p, u32 c) { return fn_8017F838(t, fn_8017F05C(p), c); }

int fn_80180BD8(void* t, void* p) {
    if (fn_801C1898(t) == 1) return fn_801C47A0(p) != 0;
    return 0;
}

int fn_801818F8(void* t, void* p) { u16 a = fn_801C4618(p); u8 b = fn_801C19D4(); return b <= a; }
int fn_80181944(void* t, void* p) { u16 a = fn_801C4618(p); u8 b = fn_801C19F8(); return b >= a; }

u32 fn_8017F6F0(void* t, void* p) {
    if (fn_801C1874(t) == 1) return fn_8039763C(lbl_8063CE34 + 0x58, p);
    return 0;
}

struct Unk81504 {
    u32 a;
    u32 res;
    int c;
    u32 d;
    void* t;
};

u32 fn_80181504(void* t, void* p, u32 a, u32 b, u32 c, u32 d) {
    Unk81504 s;
    void* tt = t;
    s.a = a;
    s.res = 0;
    s.c = c;
    s.d = d;
    s.t = tt;
    fn_801BFAE0(p, (void*)fn_801813C8, &s);
    return s.res;
}

#pragma dont_inline off
static inline void* inl_F05C(void* p) { if (p == 0) return 0; return (void*)F32(p, 0x8); }
u32 fn_8017EBC8(void* p) {
    if (p == 0) return 0;
    void* q = fn_8017D118(inl_F05C(p));
    if (q == 0) return 0;
    return F32(q, 0x10);
}
#pragma dont_inline on

int fn_8017F2F0(int a, int b, u32 c, u32 d) { return fn_8017F280(a, b, fn_8038F86C(lbl_8063CE34 + 8, d)); }

u8 fn_801802D0(void* t, void* p) { fn_8017D100(lbl_8063F24C); return fn_803918C0(lbl_8063CE34 + 0x10, fn_8017EB80(fn_801C3AA4(p))); }
u8 fn_80180328(void* t, void* p) { fn_8017D100(lbl_8063F24C); return fn_8039195C(lbl_8063CE34 + 0x10, fn_8017EB80(fn_801C3AA4(p))); }
u8 fn_80180380(void* t, void* p) { fn_8017D100(lbl_8063F24C); return fn_80391928(lbl_8063CE34 + 0x10, fn_8017EB80(fn_801C3AA4(p))); }

u8 fn_8017F5C8(void* t, void* p, u32 c) {
    u32 v = fn_801C4260(p);
    if (c == 0x16b) return fn_8038FE7C(lbl_8063CE34 + 0xc, v);
    return fn_801C66F4(c);
}

u16 fn_801804F8(void* t, void* p, u32 c) {
    void* q = fn_8017F05C(p);
    fn_8017D100(lbl_8063F24C);
    fn_801C3AA4(q);
    return fn_8017F7B0(fn_801C3AA4(q), c);
}

u32 fn_80180B40(void* t, void* p, s8 c, float f) { return fn_8017FF5C(t, fn_8017F05C(p), c, f); }

int fn_80180DC0(void* t, void* p, u32 m) {
    if (fn_801C1898(t) == 1) return (m & fn_8017EBC8(p)) != 0;
    return 0;
}
int fn_80180E1C(void* t, void* p, u32 m) {
    if (fn_801C1898(t) == 1) return (m & fn_8017EBB0(p)) != 0;
    return 0;
}

int fn_80180E78(void* t, void* p, u32 a) {
    fn_8017D100(lbl_8063F24C);
    return fn_801C4858(p, a, 0, 0) == 0;
}

u32 fn_80181B88(void* p) {
    u8 a = fn_801C1A1C(p);
    u16 b = fn_8017E900();
    return a < (b % 100);
}

void fn_80182AF4(void) {
    lbl_8063F266 = 0;
    for (u32 i = 0; i < 0x40; i++) fn_80182A74((Unk82A74*)(lbl_8048DFE0 + (u8)i * 0x2c));
}

u8 fn_8017F63C(void* t, void* p) {
    void* q = p;
    if (fn_801C2418(q) == 1) return 100;
    if (fn_801C2474(q) == 1) return 100;
    return fn_801C66E0(q);
}

int fn_8017F69C(void* t, void* p) {
    u8 a = fn_8017F63C(t, p);
    u8 b = fn_801C1A40();
    return a >= b;
}

int fn_80180058(void* t, void* p) {
    void* q = fn_801C3AA4(p);
    if (fn_801C1898(q) == 1) {
        if ((u8)fn_801800B8(q) != 0) {
            return 0;
        } else {
            return 1;
        }
    }
    return 1;
}

u16 fn_801800D0(void* t, void* p) {
    fn_8017D100(lbl_8063F24C);
    void* q = fn_801C3AC8(p);
    if (q == 0) return 0;
    void* r = fn_8017E398(q);
    if (r == 0) return 0;
    return F16(r, 2);
}
u16 fn_80180130(void* t, void* p) {
    fn_8017D100(lbl_8063F24C);
    void* q = fn_801C3AC8(p);
    if (q == 0) return 0;
    void* r = fn_8017E398(q);
    if (r == 0) return 0;
    return F16(r, 4);
}
u16 fn_80180190(void* t, void* p) {
    fn_8017D100(lbl_8063F24C);
    void* q = fn_801C3AC8(p);
    if (q == 0) return 0;
    void* r = fn_8017E398(q);
    if (r == 0) return 0;
    return F16(r, 6);
}
u16 fn_801801F0(void* t, void* p) {
    fn_8017D100(lbl_8063F24C);
    void* q = fn_801C3AC8(p);
    if (q == 0) return 0;
    void* r = fn_8017E398(q);
    if (r == 0) return 0;
    return F16(r, 8);
}

u8 fn_80181878(void* t, void* p) {
    void* q = p;
    u8 v = fn_801818D8(q);
    if ((fn_8017EBB0(q) & 0x20000000) && v > 6) v = 6;
    return v;
}

int fn_80181D94(u32 x) {
    u16 tbl[4];
    tbl[0] = lbl_80641688;
    tbl[1] = lbl_8064168A;
    tbl[2] = lbl_8064168C;
    tbl[3] = lbl_8064168E;
    for (u8 i = 0; i < 4; i++) {
        if (x == tbl[i]) return 1;
    }
    return 0;
}

u8 fn_801803D8(void* t, void* p) {
    fn_8017D100(lbl_8063F24C);
    void* q = fn_801C3AA4(p);
    if (fn_801C1730(q) == 1) {
        if (q == 0) return 0;
        return F8(q, 0x63);
    }
    return 0;
}

u16 fn_8017F8DC(void* t, void* p, u8 i);
u16 fn_801805A0(void* t, void* p, u8 i);
u32 fn_801C1754(void);
int fn_801C133C(void* t, void* p, void* r);
u8 fn_801C2F40(void* p, u8 i);
u32 fn_8017CE00(u32 a, u8 j);
u8 fn_801C1A88(void);
int fn_803C6154(u8 a, u32 b);
u16 fn_801810F4(void* t, void* p, u16* a, s16* b, u32 mode);
u8 fn_801C6664(u32 a, int b);
int fn_801C6A48(u16 v, u32 a, u32 c);

int fn_8017FC1C(void* t, void* p, u32 c) {
    if (c == fn_8017F8DC(t, p, 0) || c == fn_8017F8DC(t, p, 1)) return 1;
    return 0;
}
u32 fn_801807FC(void* t, void* p, u32 c) {
    if (c == fn_801805A0(t, p, 0) || c == fn_801805A0(t, p, 1)) return 1;
    return 0;
}

int fn_8018537C(void** arr, int lvl) {
    for (u8 i = 0; i < 8; i++) {
        void* e = arr[i];
        if (e != 0 && lvl >= fn_8017FE7C(fn_801C3AC8(e))) return 1;
    }
    return 0;
}

u16 fn_8017FC90(void* t, void* p, u16* out) {
    u16 n = 0;
    for (u8 i = 0; i < 2; i++) {
        u16 v = fn_8017F8DC(t, p, i);
        if (v != 9) out[n++] = v;
    }
    return n;
}

u16 fn_801805A0(void* t, void* p, u8 i) {
    void* r = fn_8017D100(lbl_8063F24C);
    if (fn_801C1754() == 1) {
        fn_801C133C(t, p, r);
        return (u8)fn_801C2F40(p, i);
    }
    return 9;
}

u16 fn_80180870(void* t, void* p, u16* out) {
    u16 n = 0;
    for (u8 i = 0; i < 2; i++) {
        u16 v = fn_801805A0(t, p, i);
        if (v != 9) out[n++] = v;
    }
    return n;
}

u8 fn_8017E9DC(u32 x) {
    u8 j, i;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            u32 v = fn_8017CE00(lbl_8048DFA8[i], j);
            if (v == x) return j;
        }
    }
    return 0;
}

int fn_8017FEE0(void* t, void* p) {
    u16 a = fn_8017FE7C(fn_801C3AA4(p));
    u16 b = fn_8017FE94(t, p);
    u8 c = fn_801C1A88();
    return (a * 100) / b <= c;
}

struct Unk82A74 {
    u32 a[2];
    u32 b[2];
    u16 c[2];
    u8 d[2];
    u8 e[2];
    u8 f[2];
    u8 g;
    u16 h[2][2];
    u8 k[2];
    u8 m;
    u16 n;
};

void fn_80182A74(Unk82A74* p) {
    if (p == 0) return;
    for (u8 i = 0; i < 2; i++) {
        for (u8 j = 0; j < 2; j++) {
            p->a[i] = 0;
            p->b[i] = 0;
            p->c[i] = 0;
            p->d[i] = 0;
            p->e[i] = 0;
            p->f[i] = 0;
            p->g = 0;
            p->h[i][j] = 0;
            p->k[j] = 0;
        }
    }
}

int fn_80180D1C(void* t, void* p, void* q) {
    int a = fn_8018028C(fn_801C3AC8(p));
    int b = fn_8018028C(fn_801C3AC8(q));
    u8 c = fn_80180DA8(p);
    u8 d = fn_80180DA8(q);
    return fn_803C6154(c, a) - fn_803C6154(d, b);
}

int fn_801812F0(void* t, void* p, u32 key, s16* out) {
    u16 keys[28];
    s16 vals[28];
    u16 n = ((u16(*)(void*, void*, u16*, s16*))fn_801810F4)(t, p, keys, vals);
    for (u16 i = 0; i < n; i++) {
        if (key == keys[i]) {
            if (out != 0) *out = vals[i];
            return 1;
        }
    }
    return 0;
}

u8 fn_801851A0(u32 a, int b) {
    u8 r = fn_801C6664(a, b);
    if (a == 0x137) {
        switch (b) {
        case 1: r = 10; break;
        case 2: r = 11; break;
        case 3: r = 5; break;
        case 5: r = 0; break;
        case 4: r = 15; break;
        }
    }
    return r;
}

int fn_8017FDD8(void* t, void* p, u32 c) {
    u8 i;
    int sum;
    u16 prev;
    prev = 9;
    sum = 0;
    for (i = 0; i < 2; i++) {
        u16 v = fn_8017F8DC(t, p, i);
        if (v != 9) {
            if (prev == v) break;
            prev = v;
            sum += fn_801C6A48(v, 0, c);
        }
    }
    return sum;
}

u8 fn_801C5AC0(void* p, u32 c);
u8 fn_801C1AAC(void);
extern void* lbl_8063F248;
u32 fn_801BF4C0(void* p, u32 a);
void* fn_803AC828(void);
void* fn_801C0AAC(u32 a, u32 k);
int fn_803BACA4(void* r, u32 idx, u32 a, u32 b);
void fn_801C2040(void* r, u32 k, u16 v);
u16 fn_801C69A0(u8 c, u16* buf, u16 n);
struct Unk421000 {
    int a;
    u16 b;
};
extern Unk421000 lbl_80421000[];

u32 fn_8017F838(void* t, void* p, u32 c) {
    fn_8017D100(lbl_8063F24C);
    fn_801C3AA4(p);
    u8 a = fn_8017F7F4(fn_801C3AA4(p), c);
    fn_8017D100(lbl_8063F24C);
    fn_801C3AA4(p);
    u8 b = fn_801C5AC0(fn_801C3AA4(p), c);
    u8 m = fn_801C1AAC();
    return (a * 100) / b <= m;
}

u32 fn_80181718(void* t, void* p, u32 flag) {
    if (p == 0) p = lbl_8063F248;
    u32 r = fn_801BF4C0(p, 0);
    if (flag == 1) {
        if (fn_80181504(t, p, 0xd, 0, 0, 0)) return 0;
        if (fn_80181504(t, p, 0x4c, 0, 0, 0)) return 0;
    }
    return r;
}

u16 fn_8017FD08(void* t, void* p, u32 c, int d) {
    u16 buf[2];
    if (c == 9) return 0x3f;
    if (fn_8017FB0C(t, p, 0x1a) == 1 && c == 4) return 0x43;
    u16 n = fn_8017FC90(t, p, buf);
    if (n == 0) return 0x3f;
    u32 r = fn_801C69A0(c, buf, n);
    if (fn_8017FB0C(t, p, 0x19) == 1 && r != 0x41 && d > 0) return 0x43;
    return r;
}

void fn_8017FB58(int x, u8 idx) {
    u16 v;
    void* q;
    u32 k;
    u16 i;
    void* r;
    r = fn_803AC848(fn_803AC828());
    if (idx <= 3) {
        k = lbl_8048DFB8[idx];
        q = fn_801C0AAC(0x1e, k);
        for (i = 0; i < 0x38; i++) {
            if (x == lbl_80421000[i].a) {
                v = lbl_80421000[i].b;
                if (v == fn_803BACA4(r, idx, 0x1a, 0)) fn_801C2040(q, k, v);
            }
        }
    }
}

int fn_80391D84(void* p, u16 a);
int fn_80391DB8(void* p, u16 a);
u8 fn_801C1E04(void* q, void* p);
void fn_801C1F90(void* q, void* p, u32 a);
void* fn_801C2120(void* p, void* r, void* x, void* f, u32 a, u32 b, int c);
void fn_8019C6C8(void);
void fn_801C3CF8(void* p, void* q, s8 d);

void fn_801829A0(void* p, void* q) {
    u16 m;
    u8 a;
    u8 b;
    void* d;
    if (p != 0 && q != 0) {
        d = fn_8017D118(fn_8017F05C(p));
        a = fn_80391D84(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
        b = fn_80391DB8(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
        m = fn_80182988(p);
        if (fn_801C1E04(q, p) == 0) {
            if (b == 0 || a == b) {
                fn_801C1F90(q, p, 1);
                fn_801C2040(q, (u32)p, m);
            }
        }
    }
}

int fn_801858D0(void* p, void* q, void* r, int d) {
    void* x = fn_8017D100(lbl_8063F24C);
    if (p == 0) return 0;
    if (q == 0) return 0;
    if (r == 0) return 0;
    if (d < 0) return 0;
    void* n = fn_801C2120(p, r, x, (void*)fn_8019C6C8, 1, 0, -1);
    if (n != 0) q = n;
    if (q == 0) return 0;
    fn_801C3CF8(p, q, d);
    return 1;
}

u32 fn_80183638(void* t, u32 a) {
    switch (fn_801C66AC(t)) {
    case 0:
    case 0x200:
        return a;
    case 4:
    case 8:
        return 2;
    case 1:
    case 0x40:
    case 0x80:
    case 0x400:
        return 3;
    case 0x10:
    case 0x20:
    case 0x100:
        return 4;
    case 2:
        return 5;
    }
    return 0;
}

int fn_801859DC(Unk82A74* d, Unk82A74* s) {
    if (d == 0 || s == 0) return 0;
    for (u8 i = 0; i < 2; i++) {
        for (u8 j = 0; j < 2; j++) {
            d->a[i] = s->a[i];
            d->b[i] = s->b[i];
            d->c[i] = s->c[i];
            d->d[i] = s->d[i];
            d->e[i] = s->e[i];
            d->f[i] = s->f[i];
            d->g = s->g;
            d->h[i][j] = s->h[i][j];
            d->k[j] = s->k[j];
        }
    }
    return 1;
}

u8 fn_803C93C4(void* p, u8 idx, u32 a);

void fn_80184014(void* t, Unk82A74* s) {
    u8 idx;
    u8 i;
    void* x;
    void* a;
    void* b;
    u16 c;
    u8 d;
    x = fn_8017D100(lbl_8063F24C);
    for (i = 0; i < 2; i++) {
        a = (void*)s->a[i];
        c = s->c[i];
        d = s->d[i];
        b = (void*)s->b[i];
        if (a != 0 && b != 0) {
            idx = fn_8017E954((u32)a);
            if (fn_803C93C4(fn_803AC828(), idx, 0) == 0xff) {
                void* n = fn_801C2120(a, (void*)c, x, (void*)fn_8019C6C8, 1, 0, -1);
                if (n != 0) b = n;
                if (b == 0) return;
                fn_801C3CF8(a, b, d);
            }
        }
    }
}

u32 fn_801BF6F0(u32 a, u32 b, u32 c, u32 d);

u32 fn_80185540(u32* s, u32 c) {
    if (s[0] == 0 && s[1] == 0) {
    } else if (s[0] != 0 && s[1] != 0) {
        if (fn_801BF6F0(0, s[0], c, 1) == 1 && fn_801BF6F0(0, s[1], c, 1) == 1) return 1;
    } else if (s[0] != 0) {
        if (fn_801BF6F0(0, s[0], c, 1) == 1) return 1;
    } else if (s[1] != 0) {
        if (fn_801BF6F0(0, s[1], c, 1) == 1) return 1;
    }
    return 0;
}

u8 fn_8017EA60(u32 x) {
    u8 i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            u32 v = fn_8017CE00(lbl_8048DFA8[i], j);
            if (v == x) return i;
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            void* d = fn_8017D118((void*)fn_8017CE00(lbl_8048DFA8[i], j));
            if (fn_8017EB68(d) == fn_8017EB68(fn_8017D118((void*)x)) || fn_8017EB80(d) == fn_8017EB80(fn_8017D118((void*)x))) return i;
        }
    }
    return 0;
}

struct Unk8273C {
    u8 pad0[2];
    u8 cnt;
    u8 pad3;
    u16 h[4];
    u16 arr[0x1c];
};
void fn_803C92C8(void* p, u8 idx);
u8 fn_803C91C0(u8 a, u8 b);
Unk8273C* fn_803C940C(void* p, u32 z, u8 a, u8 c);

void fn_8018273C(u8 idx, u32 unused, u16 v) {
    fn_803C92C8(fn_803AC840(fn_803AC828()), idx);
    u8 a = fn_8017E9A0((u32)fn_801C0AAC(0x1e, lbl_8048DFB8[idx]));
    u8 b = fn_8017E9DC((u32)fn_8017F05C((void*)lbl_8048DFB8[idx]));
    u8 c = fn_803C91C0(a, b);
    Unk8273C* r = fn_803C940C(fn_803AC828(), 0, a, c);
    u8 i;
    for (i = 0; i < 4; i++) {
        if (v == r->h[i]) break;
        if (r->h[i] == 0) {
            r->h[i] = v;
            r->cnt++;
            break;
        }
    }
    if (r->cnt >= 4) {
        for (i = 0; i < 0x1c; i++) r->arr[i] = 0;
    }
}

int fn_803919C4(void* p, u16 a);
int fn_803919F8(void* p, u16 a);

u16 fn_8017F8DC(void* t, void* p, u8 i) {
    void* x = fn_8017D100(lbl_8063F24C);
    u16 sp = fn_8017EB80(fn_801C3AA4(p));
    if (fn_801C1754() == 1) {
        if (fn_801C133C(t, p, x) == 0) {
            if (i == 0) return (u8)fn_803919C4(lbl_8063CE34 + 0x10, sp);
            if (i == 1) return (u8)fn_803919F8(lbl_8063CE34 + 0x10, sp);
        } else {
            if (i == 0) return (u8)fn_803919C4(lbl_8063CE34 + 0x10, sp);
            if (i == 1) return (u8)fn_803919F8(lbl_8063CE34 + 0x10, sp);
        }
        return 9;
    }
    return 9;
}

u8 fn_80182624(void* t, u32 x, u16* out, u8 n) {
    fn_8017E9A0((u32)t);
    fn_8017E954(x);
    u8 a = fn_8017E9A0((u32)fn_801C0AAC(0x1e, x));
    u8 b = fn_8017E9DC((u32)fn_8017F05C((void*)x));
    u8 c = fn_803C91C0(a, b);
    Unk8273C* r = fn_803C940C(fn_803AC828(), 0, a, c);
    if (n < 4) {
        u16 v = r->h[n];
        *out = v;
        if (v == 0) return 0;
        if (v > 0x1d4) return 0;
        return 2;
    } else if (n >= 4 && n < 0x20) {
        u16 v = r->arr[(u8)(n - 4)];
        *out = v;
        if (v == 0) return 0;
        return v <= 0x1d4;
    }
    return 0;
}

int fn_8017F348(int* arr, u16 n, u32 mode) {
    u32 idx[16];
    u16 i;
    int best = -200;
    u16 cnt = 0;
    u16 k;
    for (i = 0; i < 16; i++) idx[i] = -1;
    for (i = 0; i < n; i++) {
        if (best < arr[i]) best = arr[i];
    }
    for (i = 0; i < n; i++) {
        if (best <= arr[i]) idx[cnt++] = i;
        if (cnt >= 16) break;
    }
    if (cnt == 0) return -1;
    if (cnt == 1) k = 0;
    else if (mode == 1) k = fn_8017E900() % cnt;
    else k = 0;
    return idx[k];
}

u32 fn_801C1778(void);
void* fn_801BF5D8(u32 a, void* p);
u16 fn_801C1EB0(void* t, void* p);
int fn_80399578(void* p, u16 a);
u16 fn_801C59C4(void* q);

#pragma dont_inline off
u16 fn_8017F9F0(void* t, void* p, int unused) {
    void* q;
    u16 a;
    u16 c;
    fn_8017D100(lbl_8063F24C);
    q = fn_801C3AA4(p);
    a = (u8)fn_80391D84(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(fn_8017D118(p)));
    c = (u8)fn_80391DB8(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(fn_8017D118(p)));
    if (fn_801C1778() == 1) {
        if (fn_801BF5D8(0, p) != t) {
            u16 r = fn_801C1EB0(t, p);
            if (r != 0) return r;
            return inl_sel(fn_80399578(lbl_8063CE34 + 0x74, (u16)fn_8017EB80(fn_8017D118(p))), a, c);
        }
        return fn_801C59C4(q);
    }
    return 0;
}
#pragma dont_inline on

u16 fn_801C03A0(void* a, void* p, void** buf, u32 b, u32 c);
u16 fn_80399524(void* p, u16 a, u16 j);

void fn_8017EF38(void* p) {
    void* buf[8];
    u16 n;
    u8 a;
    u16 sp;
    u8 c;
    Unk8273C* r;
    u8 b;
    u16 v;
    u16 i;
    void* e;
    u32 j;
    n = fn_801C03A0(lbl_8063F248, p, buf, 0, 1);
    for (i = 0; i < n; i++) {
        e = buf[i];
        if (e == 0) continue;
        fn_801829A0(e, p);
        a = fn_8017E9A0((u32)fn_801C0AAC(0x1e, (u32)e));
        b = fn_8017E9DC((u32)fn_8017F05C(e));
        c = fn_803C91C0(a, b);
        r = fn_803C940C(fn_803AC828(), 0, a, c);
        sp = fn_8017EB80(fn_801C3AC8(e));
        for (j = 0; j < 0x1c; j++) {
            v = fn_80399524(lbl_8063CE34 + 0x74, sp, j);
            r->arr[(u8)j] = v;
            if (v != 0) r->pad3 = n;
        }
    }
}

u32 fn_80180618(void* t, void* p, u32 b);

u16 fn_801808E8(void* t, void* p, u32 c, int d) {
    u16 buf[4];
    if (c == 9) return 0x3f;
    if (fn_80180618(t, p, 0x1a) == 1 && c == 4) return 0x43;
    u16 n = fn_80180870(t, p, buf);
    if (n == 0) return 0x3f;
    u32 r = fn_801C69A0(c, buf, n);
    if (c <= 1 && (fn_8017EBB0(p) & 0x20000000)) {
        for (u16 i = 0; i < n; i++) {
            if (buf[i] != 9 && buf[i] == 7) r = 0x3f;
        }
    }
    if (fn_80180618(t, p, 0x19) == 1 && r != 0x41 && d > 0) return 0x43;
    return r;
}

int fn_801824F8(void* t, void* p, u32 v) {
    void* x = fn_8017D100(lbl_8063F24C);
    fn_8017E954((u32)p);
    fn_8017E9A0((u32)t);
    u8 a = fn_8017E9A0((u32)fn_801C0AAC(0x1e, (u32)p));
    u8 b = fn_8017E9DC((u32)fn_8017F05C(p));
    u8 c = fn_803C91C0(a, b);
    Unk8273C* r = fn_803C940C(fn_803AC828(), 0, a, c);
    if (t == 0) return 0;
    if (p == 0) return 0;
    if (v == 0) return 0;
    void* q = fn_8017F05C(p);
    fn_8017D118(q);
    if (fn_801C133C(t, q, x) == 0) {
        for (u8 i = 0; i < 0x1c; i++) {
            if (v == r->arr[i]) return 1;
        }
    }
    return 0;
}

s16 fn_801848F4(void* t, void* p, u32 a, s8 f, u32 b, int c, int d);

u32 fn_80185074(void* t, void* p, u32* arr, int n, void* e, s8 f) {
    u8 buf[64];
    u8 i;
    s16 best;
    void* x;
    u8 cnt;
    x = fn_8017D100(lbl_8063F24C);
    switch (fn_801C66AC(e)) {
    case 0:
        best = -0xff;
        for (i = 0; i < n; i++) {
            s16 sc = fn_801848F4(t, p, arr[i], f, 0, -1, -1);
            if (best < sc) {
                buf[0] = i;
                best = sc;
                cnt = 1;
            } else if (best == sc && best > -0xff) {
                buf[cnt++] = i;
            }
        }
        return arr[buf[(u16)fn_8017E900() % cnt]];
    default:
        return (u32)fn_801C2120(p, e, x, 0, 1, 1, -1);
    }
}

int fn_803BF874(u32 v, u8 a, u8 b);

u8 fn_801853F0(void* p, void* q, u32 v) {
    u8 a[2];
    u8 b[2];
    if (p == 0) return 0;
    if (q == 0) return 0;
    for (u8 i = 0; i < 2; i++) {
        a[i] = fn_80185524(p, i);
        b[i] = fn_80185524(q, i);
    }
    if (b[0] == v || b[1] == v) {
        switch ((u16)fn_803BF874(v, a[0], a[1])) {
        case 0:
            return 0x43;
        case 10:
        case 20:
            return 0x42;
        case 0x28:
            return 0x3f;
        case 0x50:
        case 0xa0:
            return 0x41;
        default:
            return 0x3f;
        }
    }
    return 0;
}

void* fn_801C38C0(void* p);

int fn_801813C8(void* p, void* unused, Unk81504* s) {
    void* m;
    void* q;
    u32 d = s->d;
    void* t = s->t;
    if (fn_801C38C0(p) == 0) return 1;
    if (d == 0) m = 0;
    else if (s->c == 1) m = fn_801C0AAC(2, d);
    else if (s->c == 2) m = fn_801C0AAC(3, d);
    else m = 0;
    q = fn_801C0AAC(2, (u32)p);
    if ((s->c == 1 || s->c == 2) && m == 0) return 1;
    if (s->c == 0) {
        if (d != 0 && d == (u32)p) return 1;
    } else if (s->c == 1 || s->c == 2) {
        if (m != q) return 1;
    } else {
        return 1;
    }
    if (fn_80180618(t, p, (u16)s->a) == 1) {
        s->res = (u32)p;
        return 0;
    }
    return 1;
}


#pragma dont_inline off
u8 fn_80182848(void* t, void* p, u32 v) {
    void* d;
    u16 c;
    void* x;
    u16 a;
    x = fn_8017D100(lbl_8063F24C);
    if (p == 0) return 0;
    if (t == 0) return 0;
    d = fn_8017D118(fn_8017F05C(p));
    a = (u8)fn_80391D84(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
    c = (u8)fn_80391DB8(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
    fn_80182988(p);
    a = inl_sel(fn_80399578(lbl_8063CE34 + 0x74, (u16)fn_8017EB80(d)), a, c);
    if (((u32(*)(void*, void*, u32))fn_80180618)(t, p, v) == 1) return 2;
    if (fn_801C133C(t, p, x) == 0 && a == v) return 1;
    return 0;
}
#pragma dont_inline on


u32 fn_801C4374(void* p, u32 a);

u8 fn_80185230(void* p) {
    void* t = fn_801BF5D8(0, fn_8017F05C(p));
    if (fn_801C4374(p, 3) == 1) {
        if (fn_80182848(t, p, 0x42) == 2 || fn_80182848(t, p, 0x44) == 2 || fn_80182848(t, p, 0x41) == 2 || fn_80182848(t, p, 0x43) == 2) return 2;
        if (fn_80182848(t, p, 0x42) == 1 || fn_80182848(t, p, 0x44) == 1 || fn_80182848(t, p, 0x41) == 1 || fn_80182848(t, p, 0x43) == 1) return 1;
    }
    return 0;
}

int fn_8038FEB0(void* p, u16 a);
void fn_801C6270(void* q, u32 a, u8* buf);

u8 fn_8017F464(void* t, u32 c, void* p) {
    u32 w = fn_80181718(t, 0, 1);
    u8 v = fn_8038FEB0(lbl_8063CE34 + 0xc, ((u16(*)(void*))fn_801C4260)(p));
    if (fn_801C1754() == 1) {
        if (fn_80180618(t, p, 0x60) == 1) return 0;
        if (c == 0xa5 || c == 0xf8 || c == 0x161) return 9;
        if (c == 0xed) {
            u8 buf[8];
            fn_801C6270(fn_801C3AC8(p), 0, buf);
            return buf[0];
        }
        if (c == 0x137) {
            int r;
            u8 ww = w;
            if (ww == 2) r = 11;
            else if (ww == 3) r = 5;
            else if (ww == 1) r = 10;
            else r = (ww == 4) ? 15 : 0;
            return r;
        }
        if (c == 0x16b) {
            if (v > 0x11) return 9;
            return v;
        }
        return ((u8(*)(u32))fn_801C6664)(c);
    }
    return 9;
}

void* fn_801BF694(void* a, void* p);

void** fn_80181BE4(void* t, void** arr, u16* cnt) {
    u8 i;
    u16 n = *cnt;
    if (arr == 0) return 0;
    for (i = 0; i < n; i++) {
        if (arr[i] == 0) continue;
        if ((fn_8017EBB0(arr[i]) & 0x400000) || (fn_8017EBB0(arr[i]) & 0x1000)) {
            arr[i] = 0;
            (*cnt)--;
            continue;
        }
        if ((fn_8017EBC8(arr[i]) & 7) || (fn_8017EBC8(arr[i]) & 0x20)) {
            arr[i] = 0;
            (*cnt)--;
            continue;
        }
        if (fn_801BF694(lbl_8063F248, arr[i]) != t) {
            arr[i] = 0;
            (*cnt)--;
            continue;
        }
        if (fn_80182848(t, arr[i], 0x36) == 2 && fn_80181D7C(arr[i]) == 1) {
            arr[i] = 0;
            (*cnt)--;
        }
    }
    for (i = 0; i < n; i++) {
        if (arr[i] == 0 && i + 1 < n && arr[i + 1] != 0) {
            arr[i] = arr[i + 1];
            arr[i + 1] = 0;
        }
    }
    return arr;
}

int fn_801C5B50(void* d, u8 i);

u8 fn_80182350(void* t, void* p, u32 v) {
    Unk8273C* r;
    void* q;
    void* d;
    void* x;
    u8 a;
    u8 b;
    u8 c;
    u8 i;
    x = fn_8017D100(lbl_8063F24C);
    fn_8017E954((u32)p);
    fn_8017E9A0((u32)t);
    a = fn_8017E9A0((u32)fn_801C0AAC(0x1e, (u32)p));
    b = fn_8017E9DC((u32)fn_8017F05C(p));
    c = fn_803C91C0(a, b);
    r = fn_803C940C(fn_803AC828(), 0, a, c);
    if (t == 0) return 0;
    if (p == 0) return 0;
    if (v == 0) return 0;
    q = fn_8017F05C(p);
    d = fn_8017D118(q);
    if (fn_801C133C(t, q, x) == 0) {
        for (i = 0; i < 4; i++) {
            if (v == r->h[i]) return 2;
        }
        for (i = 0; i < 0x1c; i++) {
            if (v == r->arr[i]) return 1;
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (fn_801C5B50(d, i) != 0 && v == fn_8017F7B0(d, i)) return 2;
        }
    }
    return 0;
}

int fn_801C37C4(void* q);

u8 fn_80181554(void* t, void* p, void* q, u32* out) {
    u8 f1 = 0;
    u8 f2 = 0;
    if (fn_801C37C4(q) == 0) return 0;
    u32 a = fn_80181504(t, p, 0x17, 0, 2, (u32)q);
    u32 b = fn_80181504(t, p, 0x47, 0, 2, (u32)q);
    u32 c = fn_80181504(t, p, 0x2a, 0, 0, (u32)q);
    if (fn_801807FC(t, q, 2) == 1 || fn_80180618(t, q, 0x1a) == 1) f1 = 1;
    if (fn_801807FC(t, q, 8) == 1) f2 = 1;
    if ((fn_8017EBB0(q) & 0x04000000) || (fn_8017EBB0(q) & 0xe000) || (fn_80181700(q) & 0x400)) return 1;
    if (a != 0) {
        if (out != 0) *out = a;
        return 2;
    }
    if (b != 0 && f1 == 0) {
        if (out != 0) *out = b;
        return 2;
    }
    if (c != 0 && f2 == 1) {
        if (out != 0) *out = c;
        return 2;
    }
    return 0;
}

u8 fn_80182D00(void* t, void* p, void* q);

#pragma dont_inline off
static inline u8 inl_adj(u8 kind, u8 acc) {
    switch (kind) {
    case 0:
        acc = 0;
        break;
    case 1:
    case 2:
        acc = acc * 50 / 100;
        break;
    case 3:
        acc = acc * 75 / 100;
        break;
    }
    return acc;
}

u8 fn_80182B50(void* t, void* p, void** arr, void* q) {
    u16 buf[2];
    u32 sp;
    u8 acc;
    u8 i;
    void* d;
    u8 cnt;
    cnt = 0;
    if (p == 0) return 0;
    if (t == 0) return 0;
    if (q == 0) return 0;
    d = fn_8017D118(fn_8017F05C(p));
    acc = fn_801C66E0(q);
    if (acc == 0) acc = 100;
    sp = fn_8018028C(d);
    for (i = 0; i < 2; i++) {
        if (arr[i] != 0) buf[i] = fn_8018028C(fn_8017D118(fn_8017F05C(arr[i])));
        else buf[i] = 0;
        if (sp < buf[i]) cnt++;
    }
    if (cnt == 1) acc = acc * 75 / 100;
    else if (cnt == 2) acc = acc * 50 / 100;
    acc = inl_adj(fn_80182D00(t, p, q), acc);
    return acc;
}
#pragma dont_inline on

u16 fn_801C05F0(void* a, void* p, void** buf, u32 b, u32 c);
u32 fn_801C43B8(void* f, u32 a);
int fn_8019C4E8(void* p, void* f, u16 mv, void* e, u32 z);

void fn_8017F074(void* p) {
    void* list1[8];
    u16 moves[28];
    void* list2[24];
    u16 n1;
    void* f;
    void* e;
    u16 i;
    u16 j;
    u16 k;
    int score;
    u32 tot;
    u16 mv;
    u16 n2;
    u16 nm;
    u16 idx;
    n1 = fn_801C03A0(lbl_8063F248, p, list1, 0, 1);
    n2 = fn_801C05F0(lbl_8063F248, p, list2, 1, 1);
    for (i = 0; i < n2; i++) {
        e = list2[i];
        if (e == 0) continue;
        for (j = 0; j < n1; j++) {
            f = list1[j];
            if (f == 0) continue;
            nm = ((u16(*)(void*, void*, u16*, s16*, u32))fn_801810F4)(p, f, moves, 0, 0);
            tot = (u16)fn_801C43B8(f, 1);
            for (k = 0; k < nm; k++) {
                score = 0;
                mv = moves[k];
                if (mv == 0 || mv == 0x1d4) continue;
                if (fn_8017F464(p, mv, f) == 9) continue;
                if (fn_801C65B4(mv, 1) == 1) score = fn_8019C4E8(p, f, mv, e, 0);
                idx = j + k;
                fn_8017F224(e, idx, 0, score * 100 / tot);
                fn_8017F224(e, idx, 1, mv);
            }
        }
    }
}

u8 fn_801C2E3C(void* p);

#pragma dont_inline off
static inline u32 inl_flags(void* p) {
    if (p == 0) return 0;
    return *(u32*)p;
}

u32 fn_80180618(void* t, void* p, u32 v) {
    u32 type;
    u16 c;
    u16 a;
    void* d;
    void* q;
    void* x;
    void* r;
    if (v == 0) return 0;
    r = fn_803AC848(fn_803AC828());
    x = fn_8017D100(lbl_8063F24C);
    q = fn_8017F05C(p);
    d = fn_801C3AC8(p);
    a = (u8)fn_80391D84(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
    c = (u8)fn_80391DB8(lbl_8063CE34 + 0x10, (u16)fn_8017EB80(d));
    if (fn_801C1778() == 1) {
        if (fn_801C133C(t, p, x) == 0) {
            u16 rr = fn_801C1EB0(t, q);
            if (rr != 0) type = (u8)rr;
            else type = (u8)inl_sel(fn_80399578(lbl_8063CE34 + 0x74, (u16)fn_8017EB80(d)), a, c);
        } else {
            type = (u8)fn_801C2E3C(p);
        }
    } else {
        type = 0;
        goto done;
    }
    if (type == 0x1a) {
        if ((inl_flags(lbl_8063F248) & 0x7000) || (fn_803BACA4(r, fn_8017E954((u32)p), 0x3b, 0) & 0x400)) type = 0;
    }
    if ((fn_803BACA4(r, fn_8017E954((u32)p), 0x3b, 0) & 0x200000) && type != 0x79) type = 0;
done:
    if (v != type) return 0;
    return 1;
}
#pragma dont_inline on

u16 fn_801C1C40(void* t, void* p, u8 j);

u16 fn_801810F4(void* t, void* p, u16* keys, s16* vals, u32 mode) {
    u16 n;
    u16 mv;
    u32 j;
    void* x;
    u16 i;
    x = fn_8017D100(lbl_8063F24C);
    fn_8017F05C(p);
    if (p == 0) return 0;
    if (fn_801C133C(t, p, x) == 0) {
        n = 0;
        for (i = 0; i < 0x1c; i++) {
            if (keys != 0) keys[i] = 0;
            if (vals != 0) vals[i] = -1;
        }
        for (j = 0; j < 4; j++) {
            mv = fn_801C1C40(t, p, j);
            if (mv == 0 || mv == 0x1d4 || mv == 0x1d4) continue;
            if (mode == 1 && fn_80180E78(t, p, (u8)j) == 0) continue;
            if (keys != 0) keys[n] = mv;
            if (vals != 0) vals[n] = j;
            n++;
        }
    } else {
        n = 0;
        for (i = 0; i < 4; i++) {
            if (keys != 0) keys[i] = 0;
            if (vals != 0) vals[i] = -1;
        }
        for (j = 0; j < 4; j++) {
            mv = fn_801804F8(t, p, (u8)j);
            if (mv == 0 || mv == 0x1d4 || mv == 0x1d4) continue;
            if (mode == 1 && fn_80180E78(t, p, (u8)j) == 0) continue;
            if (keys != 0) keys[n] = mv;
            if (vals != 0) vals[n] = j;
            n++;
        }
    }
    return n;
}

u16 fn_801C1D10(void* t, void* p, u8 j);

u16 fn_80180ED4(void* t, void* p, u16* keys, s16* vals, u32 mode) {
    u16 n;
    u16 mv;
    u32 j;
    u16 i;
    void* x = fn_8017D100(lbl_8063F24C);
    if (p == 0) return 0;
    if (fn_801C133C(t, p, x) == 0) {
        n = 0;
        for (i = 0; i < 0x1c; i++) {
            if (keys != 0) keys[i] = 0;
            if (vals != 0) vals[i] = -1;
        }
        for (j = 0; j < 0x1c; j++) {
            mv = fn_801C1D10(t, p, j);
            if (mv == 0 || mv == 0x1d4 || mv == 0x1d4) continue;
            if (mode == 1) {
                fn_8017D100(lbl_8063F24C);
                fn_801C3AA4(p);
                if (fn_8017F7F4(fn_801C3AA4(p), (u8)j) == 0) continue;
            }
            if (keys != 0) keys[n] = mv;
            if (vals != 0) vals[n] = j;
            n++;
        }
    } else {
        n = 0;
        for (i = 0; i < 4; i++) {
            if (keys != 0) keys[i] = 0;
            if (vals != 0) vals[i] = -1;
        }
        for (j = 0; j < 4; j++) {
            fn_8017D100(lbl_8063F24C);
            fn_801C3AA4(p);
            mv = fn_8017F7B0(fn_801C3AA4(p), (u8)j);
            if (mv == 0 || mv == 0x1d4 || mv == 0x1d4) continue;
            if (mode == 1) {
                fn_8017D100(lbl_8063F24C);
                fn_801C3AA4(p);
                if (fn_8017F7F4(fn_801C3AA4(p), (u8)j) == 0) continue;
            }
            if (keys != 0) keys[n] = mv;
            if (vals != 0) vals[n] = j;
            n++;
        }
    }
    return n;
}

u32 fn_801846D4(void* t, void* p, void* q, u32 mv) {
    u32 buf[8];
    if (t == 0) return 0;
    if (p == 0) return 0;
    if (q == 0) return 0;
    if (mv == 0) return 0;
    void* a = fn_8017F05C(p);
    void* b = fn_8017F05C(q);
    fn_8017D118(a);
    fn_8017D118(b);
    u8 ty0 = fn_801C2F40(q, 0);
    u8 ty1 = fn_801C2F40(q, 1);
    u8 mt = fn_8017F464(t, mv, p);
    fn_801C03A0(lbl_8063F248, t, (void**)buf, 1, 1);
    if (((u32(*)(void))fn_801C1898)() == 1) {
        if (!(fn_80181700(q) & 0x18) && mv != 0xc3 && fn_80185540(buf, (u32)q) != 1) {
            if ((fn_80181700(q) & 0x40) && (mv != 0x57 || mv != 0x147 || mv != 0x10 || mv != 0xef)) return 0;
            if (fn_80181700(q) & 0x80) {
                if (mv != 0x59 || mv != 0xde) return 0;
                if (((u16(*)(void*, void*))fn_8017F9F0)(t, b) == 0x1a) return 0;
                if (ty0 == 2 || ty1 == 2) return 0;
            }
            if ((fn_80181700(q) & 0x40000) && (mv != 0xfa || mv != 0x39)) return 0;
        }
    }
    if (fn_801C1754() == 1 && fn_803BF874(mt, ty0, ty1) == 0) return 0;
    return 1;
}

u8 fn_801833DC(void* t, void* p, u32 m1, u32 m2, u32 lvl) {
    u32 buf[8];
    if (p == 0) return 0;
    void* a = fn_8017F05C(p);
    void* d = fn_8017D118(a);
    u8 ty0 = fn_801C2F40(p, 0);
    u8 ty1 = fn_801C2F40(p, 1);
    u8 t1 = ((u8(*)(u32))fn_801C6664)(m1);
    u8 t2 = ((u8(*)(u32))fn_801C6664)(m2);
    fn_801C03A0(lbl_8063F248, t, (void**)buf, 1, 1);
    if (fn_801C1754() == 1 && fn_803BF874(t1, ty0, ty1) == 0 && fn_803BF874(t2, ty0, ty1) == 0) return 1;
    if (((u32(*)(void))fn_801C1898)() == 1) {
        if (!(fn_80181700(p) & 0x18) && m1 != 0xc3 && m2 != 0xc3 && fn_80185540(buf, (u32)p) != 1) {
            if ((fn_80181700(p) & 0x40) && m1 != 0x57 && m1 != 0x147 && m1 != 0x10 && m1 != 0xef && m2 != 0x57 && m2 != 0x147 && m2 != 0x10 && m2 != 0xef) return 2;
            if (fn_80181700(p) & 0x80) {
                if (m1 != 0x59 && m1 != 0xde && m2 != 0x59 && m2 != 0xde) return 2;
                if (((u16(*)(void*, void*))fn_8017F9F0)(t, a) == 0x1a) return 2;
                if (ty0 == 2 || ty1 == 2) return 2;
            }
            if ((fn_80181700(p) & 0x40000) && m1 != 0xfa && m1 != 0x39 && m2 != 0xfa && m2 != 0x39) return 2;
        }
    }
    u16 sp = fn_8017FE7C(d);
    return (sp <= lvl) ? 3 : 0;
}

#pragma dont_inline off
void fn_8018563C(void* t, Unk82A74* arr, u8* count, u32 mv, u32 mode) {
    int sp[2];
    int eff[2];
    u8 lv[2];
    s8 k;
    Unk82A74* e;
    s8 i;
    s8 j;
    u8 found;
    for (i = 0; i < *count; i++) {
        e = &arr[i];
        found = 0;
        for (j = 0; j < 2; j++) {
            sp[j] = fn_8018028C(fn_801C3AC8((void*)e->a[j]));
            u8 l = fn_80180DA8((void*)e->a[j]);
            lv[j] = l;
            if (lv[j] != 6) eff[j] = fn_803C6154(lv[j], sp[j]);
            else eff[j] = sp[j];
        }
        if (mode == 1) {
            if (mv == e->c[0] && eff[0] < eff[1]) found = 1;
            else if (mv == e->c[1] && eff[0] > eff[1]) found = 1;
        } else {
            if (mv == e->c[0] && eff[0] > eff[1]) found = 1;
            else if (mv == e->c[1] && eff[0] < eff[1]) found = 1;
        }
        if (found == 1) {
            fn_80182A74(e);
            i--;
            (*count)--;
            for (k = 0; k < *count; k++) {
                arr[k] = arr[k + 1];
                fn_801859DC(&arr[k], &arr[k + 1]);
            }
        }
    }
    for (i = *count; i < 0x40; i++) fn_80182A74(&arr[i]);
}
#pragma dont_inline on

void fn_80184108(void* t, Unk82A74* out, u8* count, u8 k0, int v0, u8 k1, int v1) {
    u8 kinds[2];
    int vals[2];
    u8 c0;
    u8 c1;
    int v;
    Unk82A74* e;
    u8 i;
    u8 j;
    u8 n;
    kinds[0] = k0;
    kinds[1] = k1;
    vals[0] = v0;
    vals[1] = v1;
    n = *count;
    for (i = 0; i < 0x40; i++) {
        e = (Unk82A74*)(lbl_8048DFE0 + i * 0x2c);
        c0 = 0;
        c1 = 0;
        for (j = 0; j < 2; j++) {
            switch (kinds[j]) {
            case 0:
                c0++;
                c1++;
                break;
            case 1: {
                int v = vals[j];
                if (v == 0) break;
                if (e->c[0] == v) {
                    if (j == 0) c0++;
                    if (j == 1) c1++;
                }
                if (e->c[1] == v) {
                    if (j == 0) c1++;
                    if (j == 1) c0++;
                }
                break;
            }
            case 2: {
                v = vals[j];
                if (v == 0) break;
                if (fn_801C65B4(e->c[0], (u8)v) == 1) {
                    if (j == 0) c0++;
                    if (j == 1) c1++;
                }
                if (fn_801C65B4(e->c[1], (u8)v) == 1) {
                    if (j == 0) c1++;
                    if (j == 1) c0++;
                }
                break;
            }
            case 3: {
                v = vals[j];
                if (v == -1) break;
                if (v == fn_8017F464(t, e->c[0], (void*)e->a[0])) {
                    if (j == 0) c0++;
                    if (j == 1) c1++;
                }
                if (v == fn_8017F464(t, e->c[1], (void*)e->a[1])) {
                    if (j == 0) c1++;
                    if (j == 1) c0++;
                }
                break;
            }
            }
        }
        if (c0 == 2 || c1 == 2) {
            fn_801859DC(&out[n], e);
            n++;
        }
    }
    *count = n;
}

u8 fn_801C20F0(void);
void* fn_801C0F7C(void* p, u8 i);
void fn_801C39A8(void* e, u32 a);
void fn_80187348(void* p, void* q);
void fn_80183720(void* p, void** list, u8 n);
void* fn_801C12B0(void* p, u8 i);
void fn_801861E0(void* p, void* e, void* q);
void fn_80181DF4(void* p, u32 a);
u8 fn_801BFFB4(void* a, void* e, u32 b);
void fn_8019BE08(void* p, void* e, void* q);
void fn_801862C4(void* p, void** list, u8 m, void* q);
u8 fn_801C4D0C(void* e, u32 a);
void fn_801BF868(void* a, void** list, u32 n, u32 b);
void fn_8019C6E8(void* p, void* e, void* q);

void fn_8017EC74(void* p, void* q) {
    u16 cnt;
    void* list[8];
    int n;
    u8 m;
    u8 i;
    void* e;
    fn_8017EF38(p);
    fn_8017F074(p);
    n = fn_801C20F0();
    for (i = 0; i < n; i++) {
        e = fn_801C0F7C(p, i);
        if (e != 0) fn_801C39A8(e, 0);
    }
    fn_80187348(p, q);
    cnt = fn_801C03A0(lbl_8063F248, p, list, 1, 1);
    fn_80183720(p, fn_80181BE4(p, list, &cnt), cnt);
    for (i = 0; i < n; i++) {
        e = fn_801C12B0(p, i);
        if (e != 0) fn_801861E0(p, e, q);
    }
    fn_80181DF4(p, 0);
    if (fn_80181B88(p) == 1) {
        for (i = 0; i < n; i++) {
            e = fn_801C12B0(p, i);
            if (e != 0 && fn_801BFFB4(lbl_8063F248, e, 0) == 0) fn_8019BE08(p, e, q);
        }
    }
    for (i = 0; i < 8; i++) list[i] = 0;
    m = 0;
    for (i = 0; i < n; i++) {
        e = fn_801C12B0(p, i);
        if (e != 0) list[m++] = e;
    }
    if (m != 0) fn_801862C4(p, list, m, q);
    for (i = 0; i < 8; i++) list[i] = 0;
    m = 0;
    for (i = 0; i < n; i++) {
        e = fn_801C12B0(p, i);
        if (e != 0 && fn_801C4D0C(e, 1) == 0) list[m++] = e;
    }
    if (m != 0) {
        fn_801BF868(lbl_8063F248, list, 8, 0);
        for (i = 0; i < m; i++) {
            if (list[i] != 0) fn_8019C6E8(p, list[i], q);
        }
    }
}

#pragma optimize_for_size reset
#pragma dont_inline reset
}
