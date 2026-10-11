#include ".unsorted/8019BEC4.hpp"

#include "common.hpp"

extern "C" {

// external prototypes
s32 fn_801C256C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_8019D8E4(s32 a, s32 b, s32 c, s32 d) { if (b == 0) return 0; return fn_801C256C(a, b, c, d, 0, 0, 0); }
s32 fn_801C297C(s32, s32, s32, s32, s32, s32, s32);
s32 fn_80180A74(s32, s32);
s32 fn_80180AC8(s32, s32);
s32 fn_80180A9C(s32, s32);
u32 fn_80180B40(s32, s32, f32, s32);
s32 fn_80181718(s32, s32, s32);
s32 fn_8017D118(s32);
s32 fn_8017FE7C(s32);
s32 fn_801A0C34(s32, s32, s32, s32, s32);
s32 fn_80180478(s32, s32);
s32 fn_803C06DC(s32);
s32 fn_80392CA4(s32, s32);
s32 fn_80392BA0(s32, s32);
s32 fn_80392CD8(s32, s32);
s32 fn_80185FB4(s32);
s32 fn_80180B9C(s32, s32);
u32 fn_80180C24(s32, s32);
s32 fn_801800B8(s32);
s32 fn_801C116C(s32, void*);
s32 fn_801C2B04(s32, void*, s32, s32);
s32 fn_801C03A0(void*, s32, void*, s32, s32);
s32 fn_801C5E08(void*, s32);
extern u8 lbl_8063CE34[];
extern const f32 lbl_806416C0;
extern void* lbl_8063F24C;
extern void* lbl_8063F248;

// ---- setters with null check ----
void fn_801C2F30(u8* p, u16 v) { if (p) *(s16*)(p + 0x846) = v; }
void fn_801C68F0(u8* p, u16 v) { if (p) *(s16*)(p + 0x2) = v; }
void fn_801C6900(u8* p, u16 v) { if (p) *(s16*)(p + 0x4) = v; }
void fn_801C6910(u8* p, u16 v) { if (p) *(s16*)(p + 0x6) = v; }
void fn_801C6960(u8* p, u16 v) { if (p) *(s16*)(p + 0x18) = v; }
void fn_801C6970(u8* p, u16 v) { if (p) *(s16*)(p + 0x1a) = v; }
void fn_801C68E0(u8* p, s8 v) { if (p) *(u8*)(p + 0x0) = v; }
void fn_801C6920(u8* p, u8 v) { if (p) *(u8*)(p + 0xc) = v; }
void fn_801C6930(u8* p, u8 v) { if (p) *(u8*)(p + 0xd) = v; }
void fn_801C6980(u8* p, u8 v) { if (p) *(u8*)(p + 0x1c) = v; }
void fn_801C6990(u8* p, u8 v) { if (p) *(u8*)(p + 0x1d) = v; }
void fn_801C6940(u8* p, s32 v) { if (p) *(s32*)(p + 0x10) = v; }
void fn_801C6950(u8* p, s32 v) { if (p) *(s32*)(p + 0x14) = v; }
void fn_801C2F5C(u8* p, s32 i, u8 v) { if (p) p[i + 0x844] = v; }

// ---- getters with null check ----
u8 fn_8019C6D0(u8* p) { if (p == 0) return 0; return p[0x84d]; }
u8* fn_8019DE78(u8* p) { if (p == 0) return 0; return p + 0x79c; }
u8 fn_801ABF54(u8* p) { if (p == 0) return 0; return p[0xd]; }
u16 fn_801C0A64(u8* p) { if (p == 0) return 0; return *(u16*)(p + 0x0); }
u16 fn_801C5F28(u8* p) { if (p == 0) return 0; return *(u16*)(p + 0x2); }
u16 fn_801C6898(u8* p) { if (p == 0) return 0; return *(u16*)(p + 0x2); }
u16 fn_801C68B0(u8* p) { if (p == 0) return 0; return *(u16*)(p + 0x6); }
u16 fn_801C68C8(u8* p) { if (p == 0) return 0; return *(u16*)(p + 0x18); }
s32 fn_801A854C(u8* p) { if (p == 0) return 0; return *(s32*)(*(u8**)(p + 0x798) + 0xc); }
u16 fn_801AC4CC(u8* p) { if (p == 0) return 0; return *(u16*)(*(u8**)(p + 0x798) + 0x24); }
u16 fn_801AC4E8(u8* p) { if (p == 0) return 0; return *(u16*)(*(u8**)(p + 0x798) + 0x20); }
u8 fn_801C0860(s32 dummy) { u8* p = (u8*)lbl_8063F24C; if (p == 0) return 0; return p[0xe]; }
u8 fn_801C2F40(u8* p, s32 i) { if (p == 0) return 0; return p[i + 0x844]; }
u32 fn_8019E89C(u8* p) { if (p == 0) return 0; return (*(u32*)(*(u8**)(p + 0x798) + 0x0) >> 8) & 7; }
u32 fn_801AAB28(u8* p) { if (p == 0) return 0; return *(u32*)(*(u8**)(p + 0x798) + 0x4) >> 30; }
u32 fn_801B0EF0(u8* p) { if (p == 0) return 0; return *(u32*)(*(u8**)(p + 0x8) + 0x4) >> 30; }
u32 fn_801B0F10(u8* p) { if (p == 0) return 0; return (*(u32*)(*(u8**)(p + 0x8) + 0x4) >> 28) & 3; }
u32 fn_801B37E4(u8* p) { if (p == 0) return 0; return (*(u32*)(*(u8**)(p + 0x798) + 0x0) >> 19) & 3; }
u32 fn_801B70B8(u8* p) { if (p == 0) return 0; return (*(u32*)(*(u8**)(p + 0x798) + 0x4) >> 16) & 7; }
u32 fn_801B8C44(u8* p) { if (p == 0) return 0; return (*(u32*)(*(u8**)(p + 0x798) + 0x0) >> 21) & 7; }
u32 fn_801C0A4C(u8* p, u32 m) { return (*(u32*)(p + 4) & m) != 0; }
s32 fn_801C083C(s32 dummy) { u8* p = (u8*)lbl_8063F24C; if (p == 0) return 0; return ((*(u32*)(p + 8) >> 3) & 1) + 1; }
s32 fn_801C087C(s32 dummy) { u8* p = (u8*)lbl_8063F24C; if (p == 0) return 0; return ((*(u32*)(p + 8) >> 1) & 1) + 1; }

// ---- small wrappers ----
void fn_8019DF30(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 10); }
void fn_8019DF5C(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 20); }
void fn_8019DF88(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 30); }
void fn_8019E1F0(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 40); }
void fn_8019E2D8(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 70); }
void fn_8019FA00(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 10); }
void fn_8019FA2C(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 20); }
void fn_8019FA58(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 30); }
void fn_8019FCE4(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 40); }
void fn_8019FDE4(s32 a, s32 b, u8* c) { fn_801C6960(fn_8019DE78(c), 70); }
u8 fn_8019DCF0(s32 a, s32 b) { return fn_80180A74(a, b); }
u8 fn_8019DD14(s32 a, s32 b) { return fn_80180A74(a, b); }
u8 fn_8019F7A4(s32 a, s32 b) { return fn_80180A74(a, b); }
u8 fn_8019F7C8(s32 a, s32 b) { return fn_80180A74(a, b); }
s32 fn_8019DA78(s32 a, s32 b) { return -((u16)fn_80180AC8(a, b) >> 1); }
s32 fn_8019E7DC(s32 a, s32 b) { return -((u16)fn_80180AC8(a, b) >> 1); }
s32 fn_8019F3E8(s32 a, s32 b) { return -((u16)fn_80180AC8(a, b) >> 1); }
s32 fn_801A02B0(s32 a, s32 b) { return -((u16)fn_80180AC8(a, b) >> 1); }
s32 fn_8019DAB8(s32 a, s32 b) { return -(u16)fn_80180AC8(a, b); }
s32 fn_8019F458(s32 a, s32 b) { return -(u16)fn_80180AC8(a, b); }
s32 fn_801A19F4(s32 a, s32 b) { return fn_80180B40(a, b, lbl_806416C0, 0) != 1; }
s32 fn_801A3940(s32 a, s32 b) { return fn_80180B40(a, b, lbl_806416C0, 0) != 1; }
s32 fn_801A3C1C(s32 a, s32 b) { return fn_80180B40(a, b, lbl_806416C0, 0) != 1; }
s32 fn_801A5264(s32 a, s32 b) { return fn_80180B40(a, b, lbl_806416C0, 0) != 1; }
s32 fn_801A3578(s32 a) { return (u8)fn_80181718(a, 0, 1) != 3; }
s32 fn_801A3A34(s32 a) { return (u8)fn_80181718(a, 0, 1) != 2; }
s32 fn_801A3A70(s32 a) { return (u8)fn_80181718(a, 0, 1) != 1; }
s32 fn_801A3EAC(s32 a) { return (u8)fn_80181718(a, 0, 1) != 4; }
s32 fn_8019F524(s32 a, s32 b, s32 c, s32 d) { return fn_801C297C(a, c, b, d, 0, 0, 0) * 2; }
s32 fn_8019F6F8(s32 a, s32 b, s32 c, s32 d) { return fn_801C297C(a, c, b, d, 0, 0, 0) * 2; }
s32 fn_8019FE38(s32 a, s32 b, s32 c, s32 d) { return fn_801C297C(a, c, b, d, 0, 0, 0) * 2; }
u16 fn_8019DAE0(s32 a, s32 b, s32 c, s32 d) { return fn_80180A9C(a, d); }
u16 fn_8019DDD4(s32 a, s32 b, s32 c, s32 d) { return fn_80180A9C(a, d); }
u16 fn_8019F480(s32 a, s32 b, s32 c, s32 d) { return fn_8017FE7C(fn_8017D118(d)); }
u16 fn_8019F890(s32 a, s32 b, s32 c, s32 d) { return fn_8017FE7C(fn_8017D118(d)); }
s32 fn_8019DB9C(s32 a, s32 b, s32 c, s32 d) { return fn_8019D8E4(a, c, b, d) * 2; }
s32 fn_8019DC80(s32 a, s32 b, s32 c, s32 d) { return fn_8019D8E4(a, c, b, d) * 2; }
s32 fn_801A349C(s32 a, s32 b, s32 c, s32 d) { return fn_801A0C34(a, b, c, d, 0) != 0; }
s32 fn_801A3BA4(s32 a, s32 b, s32 c, s32 d) { return fn_801A0C34(a, b, c, d, 0) != 0; }
s32 fn_801A544C(s32 a, s32 b) { return (u16)fn_80180478(a, b) != 0; }
s32 fn_801C6750(s32 a) { return (u8)fn_803C06DC(a) != 0; }
u16 fn_801C66AC(s32 a) { return fn_80392CA4((s32)(lbl_8063CE34 + 0x18), a); }
u8 fn_801C66F4(s32 a) { return fn_80392BA0((s32)(lbl_8063CE34 + 0x18), a); }
s8 fn_801C6678(s32 a) { return fn_80392CD8((s32)(lbl_8063CE34 + 0x18), a); }
s32 fn_801A19C4(s32 a) { return fn_80185FB4(a) != 0; }
s32 fn_801A547C(s32 a, s32 b) { return fn_80180B9C(a, b) != 1; }
void fn_801BF200(u32* p) { p[0] = 0; p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0; p[6] = 0; p[7] = 0; }
u32 fn_801C61E8(u8* p, u32 m) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x10); return (m & v) != 0; }
s32 fn_801C2DB8(u32 x) { if (x == 0xa5 || x == 0xe3 || x == 0x77 || x == 0xffff) return 1; return 0; }
s32 fn_801C2D80(u32 x) { if (x == 0xa5 || x == 0xa6 || x == 0xffff || x == 0 || x == 0x1d4) return 1; return 0; }
u8* fn_801C0A7C(u8* p, u32 i) { if (p == 0) return 0; if (i >= 2) return 0; return p + i * 0x4a9c + 0xc; }
s32 fn_801A387C(s32 a) { s16 t = 0; return fn_801C116C(a, &t) != 0; }
void fn_801C5608(u8* p) { if (p) *(s32*)(p + 0x10) = 0; if (p) *(s32*)(p + 0x10) = 0; }
void fn_801C6474(u8* p) { fn_801C6920(p, 1); fn_801C6930(p, 1); }
#pragma push
#pragma dont_inline on
s32 fn_801ADF78(s32 a) { u8 buf[0x28]; fn_801C03A0(lbl_8063F248, a, buf, 0, 1); return 0; }
#pragma pop

// ---- global option block at lbl_8048CD90 ----
struct Unk8048CD90 {
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, b10:1, b11:1, b12:1, b13:1, b14:1, b15:1, b16:1, b17:1, b18:1, b19:1, b20:1, b21:1, b22:1, b23:1, b24:1, b25:1, b26:1, b27:1, b28:1, b29:1, b30:1, b31:1;
    u8 n4h:4, n4l:4;
    u8 n5h:4, n5l:4;
    u8 n6h:4, n6l:4;
    u8 n7h:4, n7l:4;
    u8 n8h:4, n8l:4;
    u8 pad9;
    u8 nah:4, nal:4;
    u8 padb;
    u8 c0c, c0d, c0e, c0f, c10, c11, c12, c13;
    u8 a14[2];
    u8 a16[2];
    u16 a18[2];
    u8 a1c[2];
    u8 c1e;
};
extern Unk8048CD90 lbl_8048CD90;
inline s32 isCD90(void) { if (*(u32*)&lbl_8048CD90 & 0x80000000) return 1; return 0; }
u32 fn_801C16A0(void) { if (!isCD90()) return 1; return lbl_8048CD90.b31 != 0; }
u32 fn_801C16C4(void) { if (!isCD90()) return 0; return lbl_8048CD90.b30; }
u32 fn_801C16E8(void) { if (!isCD90()) return 1; return lbl_8048CD90.b29; }
u32 fn_801C170C(void) { if (!isCD90()) return 0; return lbl_8048CD90.b28; }
u32 fn_801C1730(void) { if (!isCD90()) return 0; return lbl_8048CD90.b27; }
u32 fn_801C1754(void) { if (!isCD90()) return 0; return lbl_8048CD90.b26; }
u32 fn_801C1778(void) { if (!isCD90()) return 0; return lbl_8048CD90.b25; }
u32 fn_801C179C(void) { if (!isCD90()) return 0; return lbl_8048CD90.b24; }
u32 fn_801C17C0(void) { if (!isCD90()) return 1; return lbl_8048CD90.b23; }
u32 fn_801C17E4(void) { if (!isCD90()) return 1; return lbl_8048CD90.b22; }
u32 fn_801C1808(void) { if (!isCD90()) return 0; return lbl_8048CD90.b21; }
u32 fn_801C182C(void) { if (!isCD90()) return 0; return lbl_8048CD90.b20; }
u32 fn_801C1850(void) { if (!isCD90()) return 0; return lbl_8048CD90.b19; }
u32 fn_801C1874(void) { if (!isCD90()) return 0; return lbl_8048CD90.b18; }
u32 fn_801C1898(void) { if (!isCD90()) return 0; return lbl_8048CD90.b17; }
u8 fn_801C18BC(void) { if (!isCD90()) return 12; return lbl_8048CD90.n4l; }
u8 fn_801C18E4(void) { if (!isCD90()) return 0; return lbl_8048CD90.n5l; }
u8 fn_801C190C(void) { if (!isCD90()) return 12; return lbl_8048CD90.n6l; }
u8 fn_801C1934(void) { if (!isCD90()) return 12; return lbl_8048CD90.n7l; }
u8 fn_801C195C(void) { if (!isCD90()) return 12; return lbl_8048CD90.n8l; }
u8 fn_801C1984(void) { if (!isCD90()) return 12; return lbl_8048CD90.nal; }
u8 fn_801C19AC(void) { if (!isCD90()) return 0; return lbl_8048CD90.nah; }
u8 fn_801C19D4(void) { if (!isCD90()) return 12; return lbl_8048CD90.c0c; }
u8 fn_801C19F8(void) { if (!isCD90()) return 0; return lbl_8048CD90.c0d; }
u8 fn_801C1A1C(void) { if (!isCD90()) return 0; return lbl_8048CD90.c0e; }
u8 fn_801C1A40(void) { if (!isCD90()) return 0; return lbl_8048CD90.c0f; }
u8 fn_801C1A64(void) { if (!isCD90()) return 0; return lbl_8048CD90.c10; }
u8 fn_801C1A88(void) { if (!isCD90()) return 0; return lbl_8048CD90.c11; }
u8 fn_801C1AAC(void) { if (!isCD90()) return 0; return lbl_8048CD90.c12; }
u8 fn_801C1B78(void) { if (!isCD90()) return 0; return lbl_8048CD90.c1e; }
u8 fn_801C1AD0(s32 i) { if (!isCD90()) return 0; return lbl_8048CD90.a14[i]; }
u8 fn_801C1AF8(s32 i) { if (!isCD90()) return 0; return lbl_8048CD90.a16[i]; }
u8 fn_801C1B50(s32 i) { if (!isCD90()) return 0; return lbl_8048CD90.a1c[i]; }
u8 fn_801C1B20(u8 i) { if (!isCD90()) return 0; return lbl_8048CD90.a18[i]; }

s32 fn_801C5E08(void*, s32);
u32 fn_80180C24(s32, s32);
s32 fn_801C5FC8(u8*);
s32 fn_801C6188(u8*);
s32 fn_801C6068(u8*, s32);
s32 fn_801C60E8(u8*, s32);
s32 fn_801C090C(u8*);
s32 fn_801C0E2C(u8*);
s32 fn_801C3620(u8*);
s32 fn_801C37C4(u8*);
s32 fn_801C6728(s32);
s32 fn_8038FD78(u8*, u16);
s32 fn_8038FDAC(u8*, u16);
s32 fn_8038FE7C(u8*, u16);
s32 fn_80185D28(s32, s32, s32, s32, s32, s32, s32);
s32 fn_801C05F0(s32, s32, void*, s32, s32);
s32 fn_803975B4(u8*, s32);
s32 fn_80392B38(s32, s32);
s32 fn_801BFAE0(s32, void*, void*, s32);
void fn_801BFC94();
extern u32 lbl_804225D8[];
extern u32 lbl_804218D8[];
extern u32 lbl_80421D2C[];
extern u32 lbl_80422180[];

inline u8* inl_3AA4(u8* p) { if (p == 0) return 0; return p + 4; }
u8* fn_801C3AA4(u8* p) { if (p == 0) return 0; return inl_3AA4(p); }
inline u16 inl_1B9C(u8* p) { if (p == 0) return 0; return *(u16*)p; }
u16 fn_801C1B9C(u8* p) { if (p == 0) return 0; return inl_1B9C(p); }
inline u8* inl_ptr8(u8* p) { u8* r; if (p == 0) r = 0; else r = *(u8**)(p + 8); return r; }
u8* fn_801C3AC8(u8* p) { u8* r; if (p == 0) return 0; r = fn_801C3AA4(inl_ptr8(p)); return r; }
u16 fn_801C4150(u8* p);
u8 fn_801C4184(u8* p);
u16 fn_801C41F0(u8* p);
u16 fn_801C42E8(u8* p);
s32 fn_801C45CC(u8* p);
u16 fn_801C4260(u8* p) { return fn_801C4150(inl_ptr8(p)); }
u8 fn_801C4278(u8* p) { return fn_801C4184(inl_ptr8(p)); }
u16 fn_801C4290(u8* p) { return fn_801C41F0(inl_ptr8(p)); }
u16 fn_801C4328(u8* p) { return fn_801C42E8(inl_ptr8(p)); }
s32 fn_801C4600(u8* p) { return fn_801C45CC(inl_ptr8(p)); }
s32 fn_801C5E98(u8* p) { s32 v; if (p == 0) return 2; if (p == 0) v = 0; else v = *(s32*)(p + 0x24); return fn_801C5E08(p, v); }
u16 fn_801C4150(u8* p) { u8* q = fn_801C3AA4(p); if (q == 0) return 0; return fn_801C5F28(q); }
s32 fn_801C4340(u8* p) { u8* q = fn_801C3AC8(p); if (q == 0) return 0; return fn_801C5FC8(q); }
s32 fn_801C4470(u8* p) { u8* q = fn_801C3AC8(p); if (q == 0) return 0; return fn_801C6188(q); }
s32 fn_801C45CC(u8* p) { u8* q = fn_801C3AA4(p); if (q == 0) return 0; return fn_801C5E98(q); }
s32 fn_801C4374(u8* p, s32 b) { u8* q = fn_801C3AC8(p); if (q == 0) return 0; return fn_801C6068(q, b); }
s32 fn_801C43B8(u8* p, s32 b) { u8* q = fn_801C3AC8(p); if (q == 0) return 0; return fn_801C60E8(q, b); }
inline u8 inl_lbz_d(u8* p) { if (p == 0) return 0; return p[0xd]; }
u8 fn_801C42A8(u8* p) { u8* q = fn_801C3AA4(p); if (q == 0) return 0; return inl_lbz_d(q); }
u16 fn_801C42E8(u8* p) { u8* q = fn_801C3AA4(p); if (q == 0) return 0; return inl_1B9C(q); }
s32 fn_801A1EB8(s32 a, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x790); if (v & 0x100000) return 0; return 1; }
s32 fn_801A46F0(s32 a, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x400) return 0; return 1; }
s32 fn_801A4B38(s32 a, s32 b, s32 c, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x4000) return 0; return 1; }
s32 fn_801A4C94(s32 a, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x10000) return 0; return 1; }
s32 fn_801A5024(s32 a, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x20000) return 0; return 1; }
s32 fn_801A5420(s32 a, s32 b, s32 c, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x4000000) return 0; return 1; }
s32 fn_801A54B0(s32 a, s32 b, s32 c, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x2000000) return 0; return 1; }
s32 fn_801A57A0(s32 a, u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); if (v & 0x1000000) return 0; return 1; }
s32 fn_801A529C(void) { u8* p = (u8*)lbl_8063F248; u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0); if (v & 0x7000) return 0; return 1; }
s32 fn_801C20F0(void) { u8* p = (u8*)lbl_8063F24C; u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 8); if (v & 2) return 2; return 1; }
s32 fn_801A57CC(s32 a, u8* p) { u8 v; if (p == 0) v = 0; else v = (*(u32*)(*(u8**)(p + 0x798) + 4) >> 16) & 7; if (v) return 0; return 1; }
u32 fn_801C3FD4(u32 a, u8* q) { u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v == a) return 1; return 0; }
s32 fn_801A4B0C(s32 a, s32 b) { return fn_80180C24(a, b) == 1; }
s32 fn_801AA548(s32 p) { if (p == 0) return 0; return fn_801800B8(fn_8017D118(p)); }
inline u8* inl_1BC0(u8* p, u8 i) { if (p == 0) return 0; return p + i * 0x774 + 0x28c; }
u8* fn_801C1BC0(u8* p, u32 i) { if (p == 0) return 0; if (i >= 6) return 0; return inl_1BC0(p, i); }
inline u8* inl_1C00(u8* p, u8 i) { if (p == 0) return 0; return p + i * 0x8cc + 0x2f44; }
u8* fn_801C1C00(u8* p, u32 i) { if (p == 0) return 0; if (i >= 2) return 0; return inl_1C00(p, i); }
u8* fn_801C08C8(u8* p, u32 i) { if (p == 0 && (p = (u8*)lbl_8063F248) == 0) return 0; if (i >= 2) return 0; return p + i * 0x9544 + 0xc; }
u8* fn_801BF47C(u8* a, u32 b) { u8* r = fn_801C08C8(a, b); if (fn_801C090C(r) == 0) return 0; return r; }
u8* fn_801C0978(u8* a, u32 b) { u8* r = fn_801C0A7C(a, b); if (fn_801C0E2C(r) == 0) return 0; return r; }
u8* fn_801C0F38(u8* a, u32 b) { u8* r = fn_801C1BC0(a, b); if (fn_801C3620(r) == 0) return 0; return r; }
u8* fn_801C0F7C(u8* a, u32 b) { u8* r = fn_801C1C00(a, b); if (fn_801C37C4(r) == 0) return 0; return r; }
s32 fn_801C2474(s32 a) { u16 v = fn_801C6728(a); if (v == 0x11 || v == 0x4e) return 1; return 0; }
s32 fn_801C2D3C(u16 x) { if (x == 0 || x == 0x1d4 || x == 0xd6 || x == 0x112 || x == 0x76 || x == 0x77) return 1; return 0; }
s32 fn_801C3AF0(u8* p) { u8* q; if (p == 0) return -1; if (p == 0) q = 0; else q = *(u8**)(p + 4); if (q == 0) return -1; if (q == 0) return 0; return q[0x70]; }
u8 fn_801C5F40(u8* p) { u16 v = fn_801C5F28(p); if (v == 0) return 0; return fn_8038FD78(lbl_8063CE34 + 0xc, v); }
u8 fn_801C5F84(u8* p) { u16 v = fn_801C5F28(p); if (v == 0) return 0; return fn_8038FDAC(lbl_8063CE34 + 0xc, v); }
s32 fn_801A5328(s32 a, s32 b) { s32 v = fn_80180478(a, b); return (u8)fn_8038FE7C(lbl_8063CE34 + 0xc, v) != 0; }
s32 fn_801A3BD8(s32 a, s32 b, s32 c, s32 d) { return fn_80185D28(a, b, d, c, 0x10, 2, 0x41) != 0; }
s32 fn_801A52E0(s32 a) { u8 buf[0x68]; return (u16)fn_801C05F0(0, a, buf, 1, 1) != 0; }
u32 fn_801C6798(s32 a) { return lbl_804225D8[(u16)fn_803975B4(lbl_8063CE34 + 0x58, a)]; }
u32 fn_801C67D8(s32 a) { return lbl_804218D8[(u16)fn_80392B38((s32)(lbl_8063CE34 + 0x18), a)]; }
s32 fn_801BFDDC(s32 a, s32 b, s32 c, s32 d, s32 e) { s32 s[4]; s[0] = b; s[1] = 0; s[2] = d; s[3] = e; fn_801BFAE0(a, (void*)fn_801BFC94, s, c); return s[1]; }
u16 fn_801C614C(u8* p, s32 d) { s32 v; if (p == 0) return 0; if (d == 0) return 0; if (p == 0) v = 0; else v = *(u16*)(p + 4); return v / d; }
u8 fn_801C08A0(s32 dummy) { u8* p = (u8*)lbl_8063F24C; u32 v; if (p == 0) v = 0; else v = ((*(u32*)(p + 8) >> 1) & 1) + 1; return v; }

s32 fn_8017F244(s32, s32);
u8* fn_801C0AAC(s32, void*);
s32 fn_80180A4C(s32, s32);
u32 fn_80180BD8(s32, u8*);
s32 fn_803900EC(u8*, s32);
s32 fn_80181700(s32);
s32 fn_8017EBC8(s32);
s32 fn_801BF5D8(s32, u8*);
s32 fn_801BF4C0(s32, s32);
u32 fn_801C06CC(s32, s32, s32, s32, s32, s32);
void fn_801BF2F0(s32, u32*, s32, s32, s32);
s32 fn_80391F94(u8*, s32);
u8 fn_80392C3C(s32, s32);
s32 fn_801C0168(u8*, s32, u32*);
s32 fn_801BFC40(void);
void fn_801BFE24();
extern const f32 lbl_806416D8;
extern const f32 lbl_806416C4;

s32 fn_801A1C34(s32 a, s32 b) { u8* q = fn_801C0AAC(2, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 2) return 0; return 1; }
s32 fn_801A1E6C(s32 a, s32 b) { u8* q = fn_801C0AAC(2, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 0x40) return 0; return 1; }
s32 fn_801A2150(s32 a, s32 b) { u8* q = fn_801C0AAC(2, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 1) return 0; return 1; }
s32 fn_801A3824(s32 a, s32 b) { u8* q = fn_801C0AAC(2, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 8) return 0; return 1; }
s32 fn_801A54F0(s32 a, s32 b) { u8* q = fn_801C0AAC(2, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 0x7000) return 0; return 1; }
s32 fn_801A59E0(s32 a, s32 b) { u8* q = fn_801C0AAC(3, (void*)b); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 0x80) return 0; return 1; }
s32 fn_801A3B3C(s32 a, s32 b, s32 c, s32 d) { u8* q = fn_801C0AAC(2, (void*)d); u32 v; if (q == 0) v = 0; else v = *(u32*)(q + 4); if (v & 0x10) return 0; return 1; }
u8* fn_801C0DD0(s32 a, s32 b) { u8* q = fn_801C0AAC(4, 0); u8* r; if (q == 0) return 0; r = fn_801C0AAC(a, q); if (r == 0) return 0; return r; }
u8* fn_801C395C(u8* p, s32 b, s32 c) { u8* q; if (p == 0) q = 0; else q = p + 0x7bc; return fn_801C0DD0(fn_801C68B0(q), c); }
s32 fn_801B61A0(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; if ((u16)fn_80180A4C(a, d) == 0xd5) r = fn_8017F244(0, 10); return r; }
s32 fn_801AF9A0(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; if (fn_80180B40(a, d, lbl_806416D8, 1) == 1) r = fn_8017F244(0, 10); return r; }
#pragma push
#pragma dont_inline on
s32 fn_801A5BD8(s32 a) { s32 r = 0; if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(0, 30); return r; }
#pragma pop
s32 fn_801C0228(s32 a, s32 b, s32 c) { s32 s[3]; s[0] = b; s[1] = c; s[2] = 0; fn_801BFAE0(a, (void*)fn_801C0168, s, 0); return s[2] != 0; }
u16 fn_801BFC48(s32 a, s32 b, s32 c, s32 d) { s32 s[4]; s[0] = b; s[1] = 0; s[2] = c; s[3] = d; fn_801BFAE0(a, (void*)fn_801BFC40, s, 0); return s[1]; }
u16 fn_801BFF68(s32 a, s32 b, s32 c, s32 d) { s32 s[4]; s[0] = c; s[1] = 0; s[2] = b; s[3] = d; fn_801BFAE0(a, (void*)fn_801BFE24, s, 0); return s[1]; }
s32 fn_801A208C(s32 a, s32 b, s32 c, u8* d) { u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if ((v & 0x200000) || fn_80180BD8(a, d) == 1) return 0; return 1; }
#pragma push
#pragma optimize_for_size on
s32 fn_801C2DE8(u16 x) { if ((u16)fn_803900EC(lbl_8063CE34 + 0xc, x) == 0) return 0; return x < 0x1d0; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019F7FC(s32 a, s32 b, s32 c, s32 d) { u16 s = fn_80180A9C(a, b); u16 t = fn_8017FE7C(fn_8017D118(d)); return t - (s + t) / 2; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019DD48(s32 a, s32 b, s32 c, s32 d) { u16 s = fn_80180A9C(a, b); u16 t = fn_80180A9C(a, d); return t - (s + t) / 2; }
#pragma pop
s32 fn_8019E4B4(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_80181700(d) & 0x40) r *= 2; return r; }
s32 fn_8019E510(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_80181700(d) & 0x80) r *= 2; return r; }
s32 fn_8019E618(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_80181700(d) & 0x40) r *= 2; return r; }
s32 fn_8019E674(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_80181700(d) & 0x100) r *= 2; return r; }
s32 fn_8019E9D0(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_8017EBC8(d) & 0x40) r *= 2; return r; }
s32 fn_8019EEB4(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_8017EBC8(d) & 7) r *= 2; return r; }
#pragma push
#pragma optimize_for_size on
s32 fn_8019E96C(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if (fn_80180C24(a, b) == 1) r *= 2; return r; }
#pragma pop
s32 fn_801A257C(s32 a, u8* b) { u32 v; if (b == 0) v = 0; else v = *(u32*)(b + 0x790); if (v & 0x1000000) return 0; return fn_80180B40(a, (s32)b, lbl_806416C4, -1) != 1; }
#pragma push
#pragma optimize_for_size on
s32 fn_801BF694(s32 a, u8* p) { u8* q; if (p == 0) return 0; if (p == 0) q = 0; else q = *(u8**)(p + 4); if (q == 0) return 0; if (fn_801BF5D8(a, q) == 0) return 0; }
#pragma pop
s32 fn_801C2418(s32 a) { s32 s = fn_801C6728(a); if ((u8)fn_801BF4C0(0, 1) == 2 && (u16)s == 0x98) return 1; return 0; }
s32 fn_801A3EE8(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0); u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x80000000) return 0; return r != 0; }
s32 fn_801A2A94(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0xffff); u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x1000000) return 0; return r != 0; }
s32 fn_801A2C08(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0xffff); u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x1000000) return 0; return r != 0; }
s32 fn_801A3160(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0xfffe); u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x4000000) return 0; return r != 0; }
void fn_801C0278(s32 a, s32 b, s32 c, s32 d, u32* e) { fn_801BF200(e); fn_801BF2F0(a, e, b, c, d); }
s32 fn_801C2CDC(s32 a) { u16 v = fn_801C6728(a); if (v == 0x91 || v == 0x27 || v == 0x4b || v == 0x97 || v == 0x9b || v == 0x1a) return 1; return 0; }
#pragma push
#pragma optimize_for_size on
s32 fn_801C6210(s32 a, u16 x) { if (x == 0) return 0; if ((u16)fn_80391F94(lbl_8063CE34 + 0x10, x) == 0) return 0; return x < 0x1ef; }
#pragma pop
s32 fn_801C5A60(u8* p) { u16 v; if (p == 0) return 0; if (p == 0) v = 0; else v = *(u16*)p; if (v == 0) return 0; return fn_801C6210(0, v) != 0; }
s32 fn_801A3E48(s32 a, u8* b) { u8 v; if (b == 0) v = 0; else v = (*(u32*)(*(u8**)(b + 0x798)) >> 8) & 7; if (v == 0) return 0; return fn_80180B40(a, (s32)b, lbl_806416C0, 0) != 1; }
s32 fn_801ABEF0(void) { u8 v = fn_801ABF54((u8*)lbl_8063F24C); if (v == 8 || v == 6 || v == 2 || v == 3) return fn_8017F244(0, 20); return fn_8017F244(0, 10); }
s32 fn_801C2994(s32 x) { switch (x) { case 0x10: return 1; case 0x20: return 2; case 0x90: return -1; case 0xa0: return -2; } return 0; }
u8 fn_801C6650(s32 a) { return fn_80392C3C((s32)(lbl_8063CE34 + 0x18), a); }
u8 fn_801C655C(s32 a, s32 b) { u8 r = fn_801C6650(a); return r + b * r * 20 / 100; }

void fn_801C6270(u8*, u16*, u8*);
s32 fn_8018043C(s32, s32);
s32 fn_803D01BC(u16, u16);
s32 fn_80391DEC(u8*, u16);
s32 fn_803D3400(u16);
void fn_801C5508(u8*, u16);
s32 fn_801817D0(s32, s32);
s32 fn_8017E954(s32);
s32 fn_80185C5C(s32, s32, s32, s32);
s32 fn_8019BEC4(s32, s32, u32, s32);
s32 fn_803D5004(u8);
s32 fn_803AC828(void);
s32 fn_803ADCD8(s32);
u32 fn_801C45C8(u8*, s32);
extern const f32 lbl_806416C8;

void fn_8019E3E8(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); u8 l; u16 h; fn_801C6270(fn_801C3AC8(c), &h, &l); fn_801C6960(q, h); fn_801C6970(q, l); }
void fn_8019FF38(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); u8 l; u16 h; fn_801C6270(fn_801C3AC8(c), &h, &l); fn_801C6960(q, h); fn_801C6970(q, l); }
#pragma push
#pragma optimize_for_size on
void fn_8019E164(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v; fn_801C68C8(q); v = fn_8018043C(a, (s32)c); fn_801C6960(q, (u16)v * 10 / 25); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019FC58(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v; fn_801C68C8(q); v = fn_8018043C(a, (s32)c); fn_801C6960(q, (u16)v * 10 / 25); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019E23C(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v; fn_801C68C8(q); v = fn_8018043C(a, (s32)c); fn_801C6960(q, (255 - (u16)v) * 10 / 25); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019FD30(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v; fn_801C68C8(q); v = fn_8018043C(a, (s32)c); fn_801C6960(q, (255 - (u16)v) * 10 / 25); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019DDFC(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 s = fn_80180A9C(a, (s32)c); s32 t = fn_80180AC8(a, (s32)c); s32 r = fn_803D01BC(s, t); fn_801C6960(q, r); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019F8BC(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 s = fn_80180A9C(a, (s32)c); s32 t = fn_80180AC8(a, (s32)c); s32 r = fn_803D01BC(s, t); fn_801C6960(q, r); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019EC90(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v = fn_80180A4C(a, (s32)c); s32 r = fn_803D3400(fn_80391DEC(lbl_8063CE34 + 0x10, v)); fn_801C6960(q, r); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_801A0784(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 v = fn_80180A4C(a, (s32)c); s32 r = fn_803D3400(fn_80391DEC(lbl_8063CE34 + 0x10, v)); fn_801C6960(q, r); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019EB54(s32 a, s32 b, s32 c, s32 d) { s32 s = (u16)fn_80180A9C(a, b); s32 t = (u16)fn_80180A9C(a, d); return (t <= s) ? 0 : t - s; }
#pragma pop
s32 fn_8019D910(s32 a, s32 b, u32 c, s32 d);
s32 fn_8019DB30(s32 a, s32 b, u32 c, s32 d);
s32 fn_801A43D8(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0); u8 v; if (d == 0) v = 0; else v = (*(u32*)(*(u8**)(d + 0x798)) >> 21) & 7; if (v) return 0; return r != 0; }
void fn_801C55A0(u8* p, u32 n) { u16 i; if (p) { for (i = 0; i < n; i++) fn_801C5508(p, i); } }
#pragma push
#pragma optimize_for_size on
s32 fn_8019DEB8(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_80180A9C(a, d); s32 r = fn_8019D8E4(a, c, b, d); if ((u16)s <= r) r = (u16)s - 1; return r; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A0438(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_801C297C(a, c, b, d, 0, 0, 0); if (fn_80180C24(a, b) == 1) r *= 2; return r; }
#pragma pop
s32 fn_801A3AB8(s32 a, s32 b) { if ((u8)fn_801817D0(a, b) >= 12 || fn_80180B40(a, b, lbl_806416C8, -1) != 0) return 0; return 1; }
s32 fn_801A464C(s32 a, s32 b) { u8 v = fn_8017E954(b); u8* p; u8 w; if (v > 3) return 0; p = (u8*)lbl_8063F248; if (p == 0) w = 0; else w = *(*(u8**)(p + 4) + v + 8); if (w) return 0; return 1; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B2280(s32 a, s32 b, u32 c, s32 d) { u16 s = fn_80185C5C(a, b, c, d); if (s != c && s != 0) return fn_8019BEC4(a, b, s, d); return 0; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABF6C(s32 a, s32 b, u32 c, s32 d) { u16 s = fn_803D5004(fn_801ABF54((u8*)lbl_8063F24C)); if (s != c) return fn_8019BEC4(a, b, s, d); return 0; }
#pragma pop
#pragma pop
s32 fn_801C090C(u8* p) { if (p == 0) return 0; if ((u8)fn_803ADCD8(fn_803AC828()) == 1) return 0; return fn_801C0A64(p) != 0; }
s32 fn_801C0E2C(u8* p) { if (p == 0) return 0; if ((u8)fn_803ADCD8(fn_803AC828()) == 1) return 0; return fn_801C1B9C(p) != 0; }
s32 fn_801C2F70(u8* p, u32 x) { if (x == fn_801C2F40(p, 0) || x == fn_801C2F40(p, 1)) return 1; return 0; }
u8 fn_801C4184(u8* p) { u8* q = fn_801C3AA4(p); if (q == 0) return 0; if (fn_801C45C8(p, 0x3d) == 1) return 0; return fn_801C5F40(q); }
s32 fn_801C44A4(u8* p) { u8* q; if (fn_801C37C4(p) == 0) return 1; q = fn_801C3AC8(p); if (q == 0) return 1; if (q == 0) return 0; return *(u16*)(q + 4) == 0; }
void fn_8019E0B4(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); u16 v = fn_801C68C8(q); u32 w; if (c == 0) w = 0; else w = *(u32*)(c + 0x790); if (w & 0x40000000) v *= 2; fn_801C6960(q, v); }
void fn_8019FB9C(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); u16 v = fn_801C68C8(q); u32 w; if (c == 0) w = 0; else w = *(u32*)(c + 0x790); if (w & 0x40000000) v *= 2; fn_801C6960(q, v); }
s32 fn_801A064C(s32 a, s32 b, s32 c, s32 d) { s32 s = (u16)fn_80180A9C(a, b); s32 t = (u16)fn_8017FE7C(fn_8017D118(d)); return (t <= s) ? 0 : t - s; }

s32 fn_8017F464(s32, s32, s32);
s32 fn_8017F5C8(s32, s32, s32);
u32 fn_801808E8(s32, s32, u16, s16);
void fn_801810F4(s32, s32, void*, s32, s32);
u32 fn_801A5A54(s32, u32, s32, s32);
s32 fn_801A5B34(s32, s32, u32, s32);
u32 fn_801C38C0(u8*);
s32 fn_803C93C4(s32, u8, s32);

s32 fn_801A3418(s32 a, s32 b) { u8* q = fn_801C0AAC(3, (void*)b); s16 v = 0; if (fn_801C0A4C(q, 4) == 1) { u8 w; if (q == 0) w = 0; else w = *(u32*)(*(u8**)(q + 8) + 4) >> 30; v = w; } if (v >= 3) return 0; return 1; }
s32 fn_801A5718(s32 a, s32 b) { u8* q = fn_801C0AAC(3, (void*)b); s16 v = 0; if (fn_801C0A4C(q, 0x400) == 1) { u8 w; if (q == 0) w = 0; else w = (*(u32*)(*(u8**)(q + 8) + 4) >> 28) & 3; v = w; } if (v >= 2) return 0; return 1; }
#pragma push
#pragma optimize_for_size on
s32 fn_801A38B4(s32 a, s32 b, s32 c, s32 d) { u8 v = fn_8017F464(a, c, b); s32 w = fn_8017F5C8(a, b, c); s32 r = fn_801808E8(a, d, v, w); return (u32)((0x43 - r) | (r - 0x43)) >> 31; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801A4A88(s32 a, u8* b) { u8 buf2[0x20]; u8 buf1[0x40]; u32 v; fn_801810F4(a, (s32)b, buf1, 0, 0); fn_801C03A0(lbl_8063F248, a, buf2, 0, 1); if (b == 0) v = 0; else v = *(u32*)(b + 0x794); if (v & 0x2000) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B1318(s32 a, u32* b, u32 c, s32 d, s32 e) { u16 i; for (i = 0; i < c; i++) { if (fn_801A5A54(a, b[i], d, e) == 1) return 1; } return 0; }
#pragma pop
#pragma pop
typedef s32 (*Fn8019BEC4)(s32, s32, u32, s32);
#pragma push
#pragma optimize_for_size on
s32 fn_8019BEC4(s32 a, s32 b, u32 c, s32 d) { Fn8019BEC4 f; if (fn_801C1808() == 1) { f = (Fn8019BEC4)fn_801C6798(c); if (f == 0) f = fn_801A5B34; } else { return 0; } return f(a, b, c, d); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019E8BC(s32 a, s32 b) { u8 r = 1; s16 sh; s16 dv; s32 x; if ((u8)fn_8019E89C((u8*)b)) r = fn_8019E89C((u8*)b); sh = 3 - r; if (sh < 0) sh = 0; dv = 1 << sh; x = fn_80180AC8(a, b); return -((u16)x / dv); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A0388(s32 a, s32 b) { u8 r = 1; s16 sh; s16 dv; if ((u8)fn_8019E89C((u8*)b)) r = fn_8019E89C((u8*)b); sh = 3 - r; if (sh < 0) sh = 0; dv = 1 << sh; return -((u16)fn_80180AC8(a, b) / dv); }
#pragma pop
s32 fn_801A2ED4(s32 a) { u8* p = (u8*)lbl_8063F24C; u32 f; u8 buf[0x60]; s32 n; if (p == 0) f = 0; else f = *(u32*)(p + 8); n = fn_801C05F0(0, a, buf, 1, 1); if (f & 2) { if ((u16)n <= 2) return 0; } else { if ((u16)n <= 1) return 0; } return 1; }
s32 fn_801C37C4(u8* p) { u8* q; if (p == 0) return 0; if ((u8)fn_803ADCD8(fn_803AC828()) == 1) return 0; if (p == 0) q = 0; else q = *(u8**)(p + 8); if (q == 0) return 0; return fn_801C3620(q) != 0; }
#pragma push
#pragma dont_inline on
s32 fn_801AC504(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; if (fn_8017EBC8(d) & 0x40) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return r; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801B71FC(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; if (fn_8017EBC8(d) & 7) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return r; }
#pragma pop
u8* fn_801C12B0(u8* a, u32 b) { u8* q = fn_801C0F7C(a, b); s32 v; if (q == 0) return 0; if (fn_801C38C0(q) == 0) return 0; v = fn_8017E954((s32)q); if ((u8)fn_803C93C4(fn_803AC828(), (u8)v, 0) != 0xff) return 0; return q; }

void fn_801C02D8();
u32 fn_801C3E94(u32, s32, s32);
s32 fn_801C15A8(u8*, s32, s32);
s32 fn_801804B8(s32, s32);
s32 fn_80181878(s32, s32);
s32 fn_80181858(s32, s32);
s32 fn_801B0F30(s32, s32);

#pragma push
#pragma optimize_for_size on
s32 fn_8019DFB4(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_801C256C(a, c, b, d, 0, (s32)fn_8019DF30, 0); r += fn_801C256C(a, c, b, d, 0, (s32)fn_8019DF5C, 0); return r + fn_801C256C(a, c, b, d, 0, (s32)fn_8019DF88, 0); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019FA84(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_801C297C(a, c, b, d, 0, (s32)fn_8019FA00, 0); r += fn_801C297C(a, c, b, d, 0, (s32)fn_8019FA2C, 0); return r + fn_801C297C(a, c, b, d, 0, (s32)fn_8019FA58, 0); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801C03A0(void* a, s32 b, void* c, s32 d, s32 e) { s32 s[5]; fn_801BF200((u32*)c); s[0] = b; s[1] = (s32)c; s[2] = 0; s[3] = d; s[4] = e; fn_801BFAE0((s32)a, (void*)fn_801C02D8, s, 0); return (u16)s[2]; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A0304(s32 a, s32 b, s32 c, s32 d) { s16 r = 1; if ((u8)fn_8019E89C((u8*)b)) r = (u8)fn_8019E89C((u8*)b); return r * fn_801C297C(a, c, b, d, 0, 0, 0); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019EBB8(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 s = fn_80180A9C(a, (s32)c); s32 t = fn_80180AC8(a, (s32)c); s32 h = fn_801C68C8(q); u16 v = (u16)h * (u16)s / (u16)t; if (v == 0) v = 1; fn_801C6960(q, v); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_801A06AC(s32 a, s32 b, u8* c) { u8* q = fn_8019DE78(c); s32 s = fn_80180A9C(a, (s32)c); s32 t = fn_80180AC8(a, (s32)c); s32 h = fn_801C68C8(q); u16 v = (u16)h * (u16)s / (u16)t; if (v == 0) v = 1; fn_801C6960(q, v); }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
u32 fn_801C06CC(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) { u32 buf[8]; s32 n = fn_801C03A0((void*)a, b, buf, c, d); u16 i; for (i = 0; i < (u16)n; i++) { if (fn_801C3E94(buf[i], e, f) == 1) return 1; } return 0; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
u16 fn_801C09BC(u8* a, u32 n, s32 c, s32 d) { u8* q; u16 i; u16 sum = 0; for (i = 0; i < n; i++) { q = fn_801C0A7C(a, i); if (fn_801C0E2C(q)) sum += fn_801C15A8(q, c, d); } return sum; }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_8019ED4C(s32 a, s32 b, u8* c) { s32 v = fn_80181718(a, 0, 1); u8* q = fn_8019DE78(c); u16 x; if ((u8)v == 2) x = 11; else if ((u8)v == 3) x = 5; else if ((u8)v == 1) x = 10; else if ((u8)v == 4) x = 15; else x = 0; fn_801C6970(q, x); }
#pragma pop
#pragma push
#pragma optimize_for_size on
void fn_801A08A0(s32 a, s32 b, u8* c) { s32 v = fn_80181718(a, 0, 1); u8* q = fn_8019DE78(c); u16 x; if ((u8)v == 2) x = 11; else if ((u8)v == 3) x = 5; else if ((u8)v == 1) x = 10; else x = ((u8)v == 4) ? 15 : 0; fn_801C6970(q, x); }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801B7DA0(s32 a, s32 b) { s32 r = 0; if ((u16)fn_801804B8(a, b) == 0x30) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return fn_8017F244(r, 0); }
#pragma pop
#pragma push
#pragma optimize_for_size on
u16 fn_801C121C(s32 a, u32* out) { u16 n = 0; s16 k; out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0; out[4] = 0; out[5] = 0; k = 0; for (;;) { u32 r = fn_801C116C(a, &k); if (r == 0) break; out[n++] = r; k++; } return n; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019E348(s32 a, s32 b) { u8 v = fn_80181718(a, 0, 1); s32 x; if (v == 0) x = (u16)fn_80180AC8(a, b) >> 1; else if (v == 1) x = (u16)fn_80180AC8(a, b) * 20 / 30; else x = (u16)fn_80180AC8(a, b) >> 2; return -x; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019FE98(s32 a, s32 b) { u8 v = fn_80181718(a, 0, 1); s32 x; if (v == 0) x = (u16)fn_80180AC8(a, b) >> 1; else if (v == 1) x = (u16)fn_80180AC8(a, b) * 20 / 30; else x = (u16)fn_80180AC8(a, b) >> 2; return -x; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A61EC(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; u8 v = fn_80181878(a, d); u8 w; if (v > 6) r = fn_8017F244(0, (v - 6) * 5); w = fn_80181858(a, b); if (w < 6) r = fn_8017F244(r, (6 - w) * 5); return fn_8017F244(r, -5); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801B27BC(s32 a, s32 b) { s32 r = 0; if (fn_8017EBC8(b) & 7) { if ((s8)fn_801B0F30(a, b) == 0) r = fn_8017F244(0, 100); if ((s8)fn_801B0F30(a, b) == 1) r = fn_8017F244(r, -10); } return r; }
#pragma pop

u32 fn_80180618(s32, u32, s32);
s32 fn_801824F8(s32, u32, s32);
s32 fn_801817F0(s32, s32);
s32 fn_801860C4(s32);
s32 fn_803BF874(s32, u8, u8);
u32 fn_80180E1C(s32, s32, s32);
s32 fn_801C2984(s32, s32, u8*, s32, u16, u8);
s32 fn_801C298C(s32, s32, u8*, s32, u16, u8);

s32 fn_801C5FC8(u8* p) { if (p == 0) return 0; if (fn_801C61E8(p, 8) == 1) return 1; if (fn_801C61E8(p, 0x40) == 1) return 1; if (fn_801C61E8(p, 0x10) == 1) return 1; return fn_801C61E8(p, 0x80) == 1; }
s32 fn_801A49E4(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_801A0C34(a, b, c, d, 0xffff); if (fn_80180618(a, b, 0x19) == 1) return 0; if (fn_80180618(a, d, 0x19) == 1) return 0; return r != 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A5B34(s32 a, s32 b, u32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(0, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABC34(s32 a, s32 b) { s32 r = fn_8017F244(0, 4); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)fn_801817F0(a, b) >= 12) r = fn_8017F244(r, -4); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A66E4(s32 a, s32 b) { s32 r = fn_8017F244(0, 5); if ((u16)fn_801804B8(a, b) == 0x62) r = fn_8017F244(r, 20); r = fn_8017F244(r, -5); if ((u8)fn_801817F0(a, b) >= 12) r = fn_8017F244(r, -5); return r; }
#pragma pop
inline u8 inl_4618(u8* p, s32 i) { if (p == 0) return 0; return p[0x7ec + i]; }
s32 fn_801C4618(u8* p) { s32 s = inl_4618(p, 0); s += inl_4618(p, 1); s += inl_4618(p, 2); s += inl_4618(p, 3); s += inl_4618(p, 4); s += inl_4618(p, 5); return s + inl_4618(p, 6); }
s32 fn_801C69A0(s32 a, u16* b) { switch (fn_803BF874(a, b[0], b[1])) { case 0: return 0x43; case 0x28: return 0x3f; case 0x3c: case 0x50: case 0xa0: return 0x41; case 10: case 20: return 0x42; } return 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_8019E56C(s32 a, s32 b, s32 c, s32 d) { s32 r; u16 w = fn_8017F5C8(a, b, c); u8 v = fn_8017F464(a, c, b); r = fn_801C298C(b, d, fn_801C0AAC(2, (void*)d), c, w, v); if (fn_80180E1C(a, b, 50) == 1) r = r * 15 / 10; return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A0090(s32 a, s32 b, s32 c, s32 d) { u16 w = fn_8017F5C8(a, b, c); u8 v = fn_8017F464(a, c, b); s32 r = fn_801C2984(b, d, fn_801C0AAC(2, (void*)d), c, w, v); if (fn_80180E1C(a, b, 50) == 1) r = r * 15 / 10; return r; }
#pragma pop
#pragma pop
s32 fn_801A34CC(s32 a) { u8* p = (u8*)lbl_8063F24C; u32 f; u8 buf[0x60]; s32 n; if (p == 0) f = 0; else f = *(u32*)(p + 8); n = fn_801C05F0(0, a, buf, 1, 1); if (f & 2) { if ((u16)n <= 2) return 0; } else { if ((u16)n <= 1) return 0; } if ((u16)fn_801860C4(a) == 0) return 0; return 1; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B61F0(s32 a, s32 b) { s32 r = 0; u8* q = fn_801C0AAC(3, (void*)b); if (fn_801C0A4C(q, 2) != 0 || fn_801C0A4C(q, 1) != 0) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return r; }
#pragma pop
#pragma pop
u8* fn_801C0FC0(u8* a, u8* b) { u32 i; if (a == 0) return 0; if (b == 0) return 0; for (i = 0; i < 2; i++) { u8* q = fn_801C0F7C(a, (u16)i); if (q != 0 && fn_801C3FD4((u32)b, q) == 1) return q; } return 0; }
#pragma push
#pragma dont_inline on
void fn_801C64B0(u8* p) { if (p) { fn_801C68E0(p, -1); fn_801C68F0(p, 0); fn_801C6900(p, 0); fn_801C6910(p, 0); fn_801C6474(p); fn_801C6940(p, 0); fn_801C6950(p, 0); fn_801C6960(p, 0); fn_801C6970(p, 9); fn_801C6980(p, 0); fn_801C6990(p, 0); } }
#pragma pop

s32 fn_803AC848(s32);
s32 fn_803C8C48(s32, s32, s32, u8);
u32 fn_801807FC(s32, s32, s32);
s32 fn_8017E9A0(u8*);
s32 fn_8017E9DC(u8*);
s32 fn_803C91C0(u8, u8);
u8* fn_803C940C(s32, s32, u8, u8);
s32 fn_8018E388(void*);
s32 fn_801C106C(u8*, u8*);
extern u8* lbl_8048DFB8[];

#pragma push
#pragma optimize_for_size on
s32 fn_801A3C54(s32 a, u8* b, s32 c, s32 d) { s32 w; s32 x; s32 y; x = fn_803AC828(); y = fn_803AC848(fn_803AC828()); if (b == 0) w = 0; else w = *(s32*)(*(u8**)(b + 0x798) + 0xc); if (w != fn_803C8C48(x, y, 3, fn_8017E954((s32)b))) return 0; s32 r = fn_801807FC(a, d, 7); return (u32)((1 - r) | (r - 1)) >> 31; }
#pragma pop
s32 fn_801A31C4(s32 a, s32 b, s32 c, u8* d) { u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x1000000) return 0; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x8000000) return 0; if (d == 0) v = 0; else { u8* q = inl_3AA4(inl_ptr8(d)); if (q == 0) v = 0; else v = *(u32*)(q + 0x10); } if ((v & 7) == 0) return 0; return 1; }
u8 fn_801C1E04(s32 a, s32 b) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return 0; idx = (u8)fn_8017E954(b); x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); return fn_803C940C(fn_803AC828(), 0, x, z)[0x44]; }
void fn_801C1F90(s32 a, s32 b, u8 c) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return; idx = (u8)fn_8017E954(b); x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); fn_803C940C(fn_803AC828(), 0, x, z)[0x44] = c; }
void fn_801C2040(s32 a, s32 b, u16 c) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return; idx = (u8)fn_8017E954(b); x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); *(u16*)(fn_803C940C(fn_803AC828(), 0, x, z) + 0x46) = c; }
#pragma push
#pragma dont_inline on
s32 fn_801C3620(u8* p) { u8* q; if (p == 0) return 0; if ((u8)fn_803ADCD8(fn_803AC828()) == 1) return 0; if (p == 0) q = 0; else q = *(u8**)p; if (q == 0) return 0; if (fn_801C5A60(q) == 0) return 0; q = fn_801C3AA4(p); if (q == 0) return 0; return fn_801C5A60(q) != 0; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801B7288(s32 a, s32 b) { s32 r = 0; if ((u16)fn_801804B8(a, b) == 0x30) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_8018E388(lbl_8063F248) & 0x70000) r = fn_8017F244(r, 10); return fn_8017F244(r, 0); }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801AB8F8(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; if (fn_80180E1C(a, d, 0x3d) == 0 && (u16)fn_80180478(a, d) != 0) r = fn_8017F244(0, 10); if (fn_80180618(a, d, 0x3c) == 1 || fn_80180618(a, d, 0x79) == 1) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801C116C(s32 a, void* kk) { u16* k = (u16*)kk; u8* q; if (a == 0) return 0; if (k == 0) return 0; while (*k < 6) { q = fn_801C1BC0((u8*)a, *k); if ((u8)fn_801C106C((u8*)a, q) == 0) break; (*k)++; } if (*k >= 6) return 0; return (s32)q; }
#pragma pop

s32 fn_801C5BFC(u8*, u32);
extern const u32 lbl_803FC6B0[4];
typedef void (*Fn801C0420)(u8*, u32, s32);

#pragma push
#pragma dont_inline on
s32 fn_801A4440(s32 a, s32 b) { u8* q = fn_801C0AAC(14, (void*)b); if (q == 0) return 0; if (((u16(*)(s32))fn_801C08A0)(0) < 2 || fn_801C38C0(q) != 1 || fn_80180E1C(a, b, 50) != 0 || fn_80180E1C(a, (s32)q, 50) != 0) return 0; return 1; }
#pragma pop
s32 fn_801A2784(s32 a, s32 b, s32 c, u8* d) { s32 r = fn_801A0C34(a, b, c, (s32)d, 0); u32 v; if (d == 0) v = 0; else v = *(u32*)(d + 0x794); if (v & 4) return 0; if (fn_801807FC(a, (s32)d, 12) == 1) return 0; if (d == 0) v = 0; else v = *(u32*)(d + 0x790); if (v & 0x1000000) return 0; return r != 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801BF5D8(s32 a, u8* b) { u32 i; u32 j; u32 k; for (i = 0; i < 2; i++) { u8* p = fn_801C08C8((u8*)a, (u16)i); if (p) { for (j = 0; j < 2; j++) { u8* q = fn_801C0A7C(p, (u16)j); if (q) { for (k = 0; k < 6; k++) { u8* r = fn_801C1BC0(q, (u16)k); if (r && b == r) return (s32)q; } } } } } return 0; }
#pragma pop
#pragma pop
inline u32 inl_790(u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x790); return v; }
inline u32 inl_794(u8* p) { u32 v; if (p == 0) v = 0; else v = *(u32*)(p + 0x794); return v; }
#pragma push
#pragma optimize_for_size on
u32 fn_801C47A0(u8* p) { u32 t0 = lbl_803FC6B0[0]; u32 t1 = lbl_803FC6B0[1]; u32 t2 = lbl_803FC6B0[2]; u32 t3 = lbl_803FC6B0[3]; if (p == 0) return 0; if (t0 & inl_794(p)) return t0; if (t1 & inl_794(p)) return t1; if (t2 & inl_794(p)) return t2; if (t3 & inl_794(p)) return t3; return 0; }
#pragma pop
s32 fn_801C4510(u8* a, u8* b) { u32 i; u32 j; u32 k; if (a == 0) return 0; if (b == 0) return 0; for (k = 0; k < 4; k++) { if (lbl_8048DFB8[k] == a) i = k; if (lbl_8048DFB8[k] == b) j = k; } if (i == j || (s32)(i ^ 2) == (s32)j) return 1; return 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
void fn_801C0420(u8* a, Fn801C0420 fn, s32 c, s32 unused) { u8* p = (u8*)lbl_8063F24C; u32 f; u32 n; u32 i; if (p == 0) f = 0; else f = *(u32*)(p + 8); n = (u8)fn_801C083C(0); for (i = 0; i < 2; i++) { u8* q = fn_801BF47C(a, (u16)i); if (q) { u16 j; for (j = 0; j < n; j++) { u8* e = fn_801C0978(q, j); if (e) fn(e, f, c); } } } }
#pragma pop
#pragma pop
struct Bf16 { u16 hi:8; u16 b8:1; u16 lo:7; };
inline u32 inl_5CC4a(u8* p) { if (p == 0) return 0; return ((Bf16*)(p + 0x16))->b8 != 0; }
inline u32 inl_5CC4b(u8* p) { if (p == 0) return 0; return *(u16*)(p + 4) == 0; }
s32 fn_801C5CC4(u8* p) { if (fn_801C5A60(p) == 0) return 0; if (inl_1B9C(p) == 0x19c) return 0; if (inl_5CC4a(p) == 1) return 0; if (inl_5CC4b(p) == 1) return 0; return 1; }
s32 fn_801C0168(u8* p, s32 b, u32* s) { u16 w = s[1]; u8* v = (u8*)s[0]; if (fn_801C38C0(p) == 0) return 1; if (fn_801C4510(p, v) == 0) { if (inl_794(p) & 0x2000) { if ((s8)fn_801C5BFC(fn_801C3AC8(p), w) >= 0) { s[2] = 1; return 0; } } } return 1; }

s32 fn_80181830(s32, s32);
s32 fn_80181810(s32, s32);
s32 fn_80181850(s32, s32);
s32 fn_8017F5C0(s32, s32);
s32 fn_80181554(s32, s32, s32, s32);
s32 fn_8017EBB0(s32);
u32 fn_801818F8(s32, s32);
u32 fn_80185B6C(s32, s32);
u32 fn_8017FB0C(s32, u32, s32);
s32 fn_80180058(s32, u32);
#pragma push
#pragma optimize_for_size on
s32 fn_801A4E84(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_801817F0(a, b); s32 t = fn_80181830(a, b); if ((u8)s >= 12 && (u8)t >= 12) return 0; if (fn_80185D28(a, b, d, c, 0x10, 2, 0x41) == 0 && fn_80185D28(a, b, d, c, 0x10, 5, 0x41) == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A4F54(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_801817D0(a, b); s32 t = fn_801817F0(a, b); if ((u8)s >= 12 && (u8)t >= 12) return 0; if (fn_80185D28(a, b, d, c, 0x10, 1, 0x41) == 0 && fn_80185D28(a, b, d, c, 0x10, 2, 0x41) == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A5050(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_80181810(a, b); s32 t = fn_80181830(a, b); if ((u8)s >= 12 && (u8)t >= 12) return 0; if (fn_80185D28(a, b, d, c, 0x10, 4, 0x41) == 0 && fn_80185D28(a, b, d, c, 0x10, 5, 0x41) == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A511C(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_801817D0(a, b); s32 t = fn_80181850(a, b); if ((u8)s >= 12 && (u8)t >= 12) return 0; if (fn_80185D28(a, b, d, c, 0x10, 1, 0x41) == 0 && fn_80185D28(a, b, d, c, 0x10, 3, 0x41) == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABA9C(s32 a, s32 b) { s32 r = 0; u8 v; if ((u16)fn_801804B8(a, b) == 0x30) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); r = fn_8017F244(r, -5); v = fn_801817D0(a, b); if (v < 6) r = fn_8017F244(r, (6 - v) * -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABB68(s32 a, s32 b) { s32 r = 0; u8 v; if ((u16)fn_801804B8(a, b) == 0x30) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); r = fn_8017F244(r, -5); v = fn_80181810(a, b); if (v < 6) r = fn_8017F244(r, (6 - v) * -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABCD8(s32 a, s32 b, s32 c) { s32 r = fn_8017F244(0, (u8)fn_8017F5C0(a, c) / 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)fn_801817D0(a, b) >= 12) r = fn_8017F244(r, (u8)fn_8017F5C0(a, c) / -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801AEC80(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 v = fn_80181554(a, 0, d, 0); if (!(fn_8017EBB0(d) & 0x8000000)) r = fn_8017F244(0, 20); if ((u32)(fn_8017EBC8(d) & 7) >= 3) r = fn_8017F244(r, 10); if ((u8)v == 0) r = fn_8017F244(r, -5); if ((u32)(fn_8017EBC8(d) & 7) <= 2) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B57A8(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_801818F8(a, b) == 1) r = fn_8017F244(0, 30); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
u16 fn_801C1C40(s32 a, s32 b, u32 c) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return 0; if (c >= 4) return 0; idx = (u8)fn_8017E954(b); x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); return *(u16*)(fn_803C940C(fn_803AC828(), 0, x, z) + (u8)c * 2 + 4); }
s32 fn_801A1C84(s32 a, u8* b) { u32 v; if (b == 0) v = 0; else { u8* q = inl_3AA4(inl_ptr8(b)); if (q == 0) v = 0; else v = *(u32*)(q + 0x10); } if (v & 7) return 0; if (fn_80185B6C(a, (s32)b) == 1) return 0; return fn_80180B40(a, (s32)b, lbl_806416C0, 0) != 1; }
#pragma push
#pragma optimize_for_size on
s32 fn_801A3088(s32 a, s32 b, u32 c) { u32 buf[0x18]; s32 n = fn_801C05F0(0, a, buf, 1, 1); s32 found = 0; u16 i; for (i = 0; i < (u16)n; i++) { if (buf[i] != 0) { if (c == 0xd7 && fn_8017FB0C(a, buf[i], 0x2b) == 1) continue; if (fn_80180058(a, buf[i]) == 0) { found = 1; break; } } } if (found == 0) return 0; return 1; }
#pragma pop

s32 fn_80180D1C(s32, s32, s32);
s32 fn_8038FDE0(u8*, u16);
u32 fn_80185C18(s32);
void fn_801C04E4();
s32 fn_80181878(s32, s32);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AC6B4(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_80180B40(a, b, lbl_806416D8, -1) == 1) r = fn_8017F244(0, 30); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
#pragma push
#pragma optimize_for_size on
s32 fn_801B696C(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(0, 10); break; } } if (fn_801C06CC(0, a, 1, 1, 0xd5, d) == 1) r = fn_8017F244(r, -100); return r; }
#pragma pop
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B7E34(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; fn_801C03A0(lbl_8063F248, a, buf, 0, 1); if (fn_80180D1C(a, d, b) > 0) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_80180D1C(a, b, d) > 0) r = fn_8017F244(r, -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801BDB48(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 v = fn_80180478(a, d); if (fn_80180618(a, d, 0x52) == 1) r = fn_8017F244(0, 5); if ((u8)fn_8038FDE0(lbl_8063CE34 + 0xc, v)) r = fn_8017F244(r, 20); if (fn_80180618(a, d, 0x3c) == 1 || fn_80180618(a, d, 0x79) == 1) r = fn_8017F244(r, -5); return r; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801C05F0(s32 a, s32 b, void* cc, s32 d, s32 e) { u32* c = (u32*)cc; s32 s[6]; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; c[4] = 0; c[5] = 0; c[6] = 0; c[7] = 0; c[8] = 0; c[9] = 0; c[10] = 0; c[11] = 0; c[12] = 0; c[13] = 0; c[14] = 0; c[15] = 0; c[16] = 0; c[17] = 0; c[18] = 0; c[19] = 0; c[20] = 0; c[21] = 0; c[22] = 0; c[23] = 0; s[0] = b; s[1] = d; s[2] = 0; s[3] = (s32)c; s[4] = fn_801C0860(0); s[5] = e; fn_801C0420((u8*)a, (Fn801C0420)fn_801C04E4, (s32)s, 0); return (u16)s[2]; }
#pragma pop
#pragma push
#pragma optimize_for_size on
u32 fn_801A5A54(s32 a, u32 b, s32 lo, s32 hi) { u8 v[7]; u32 i; v[0] = fn_801817D0(a, b); v[1] = fn_801817F0(a, b); v[2] = fn_80181810(a, b); v[3] = fn_80181830(a, b); v[4] = fn_80181850(a, b); v[5] = fn_80181858(a, b); v[6] = fn_80181878(a, b); for (i = 0; i < 7; i++) { if (v[(u8)i] >= (u32)lo && v[(u8)i] <= (u32)hi) return 1; } return 0; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A13F0(s32 a, s32 b, s32 c, s32 d) { u8 buf[0x60]; u8 v = fn_8017F464(a, c, b); if ((u16)fn_801C05F0(0, a, buf, 1, 1) <= 1) return 0; if (fn_80185C18(a) == 1) return 0; s32 w = fn_8017F5C8(a, b, c); if (fn_801808E8(a, d, v, w) == 0x43) return 0;  s32 r = fn_801A0C34(a, b, c, d, 0); return (u32)(-r | r) >> 31; }
#pragma pop
#pragma pop

s32 fn_801800D0(s32, s32);
s32 fn_80180190(s32, s32);
s32 fn_80180130(s32, s32);
s32 fn_801801F0(s32, s32);
s32 fn_80181380(s32, s32);
u32 fn_8017F630(s32, u16, s32);
s32 fn_801C384C(u8*);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AB9AC(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; u8 v; if ((u16)fn_801804B8(a, b) == 0x30) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); r = fn_8017F244(r, -5); if (fn_8017EBC8(d) & 0x20) r = fn_8017F244(r, -30); v = fn_80181810(a, b); if (v < 6) r = fn_8017F244(r, (6 - v) * -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AB724(s32 a, s32 b) { s32 r = 0; s32 v = fn_80181718(a, 0, 1); if ((u8)v == 1) r = fn_8017F244(0, 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u16)fn_801804B8(a, b) == 0x62) r = fn_8017F244(r, 20); if ((u8)(v + 0xfe) <= 2) r = fn_8017F244(r, -30); if ((u8)v == 0) r = fn_8017F244(r, -15); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ABFDC(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 v = fn_80181718(a, 0, 1); if ((u8)(v + 0xff) <= 1) r = fn_8017F244(0, 20); if ((u8)v == 4) r = fn_8017F244(r, 15); if ((u8)v == 3) r = fn_8017F244(r, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)v == 1 && (fn_8017EBC8(d) & 0x20)) r = fn_8017F244(r, -50); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A4CC4(s32 a, s32 b, s32 c, s32 d) { u8 v = fn_80181718(a, 0, 1); s32 r; u16 x; s32 w; if (v == 2) x = 11; else if (v == 3) x = 5; else if (v == 1) x = 10; else if (v == 4) x = 15; else x = 0; r = fn_801A0C34(a, b, c, d, 0); w = fn_8017F5C8(a, b, c); if (fn_801808E8(a, d, x, w) == 0x43) r = 0; if (r == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B1944(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 y; s32 x; s32 n; u16 i; x = fn_803AC828(); y = fn_803AC848(fn_803AC828()); n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); if (fn_803C8C48(x, y, 0x10, fn_8017E954(b)) != 0) r = fn_8017F244(0, 20); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B75C0(s32 a, s32 b, s32 c, s32 d) { u32 buf[10]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x78) == 1 || (u8)fn_801824F8(a, buf[i], 0x99) == 1) { r = fn_8017F244(0, 30); break; } } if ((u16)fn_80181380(a, d) == 0xb6 || (u16)fn_80181380(a, d) == 0xc5) r = fn_8017F244(r, -30); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A1D50(s32 a, s32 b, s32 c, s32 d) { s32 r; u8 v; s32 s = fn_80180A74(a, b); s32 t = fn_80180A74(a, d); s32 w; v = fn_8017F464(a, c, b); r = fn_801A0C34(a, b, c, d, 0xffff); w = fn_8017F5C8(a, b, c); if (fn_801808E8(a, d, v, w) == 0x43) r = 0; if (fn_80180618(a, d, 5) == 1) r = 0; if ((u8)s < (u8)t) r = 0; if (r == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A60EC(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 w0 = fn_801800D0(0, d); s32 w1 = fn_80180190(0, d); s32 w2 = fn_80180130(0, d); s32 w3 = fn_801801F0(0, d); u16 m = fn_80181380(a, d); if (m != 0 && m != 0xffff && m != 0x1d4 && m != 0x1d4 && fn_8017F630(a, m, 1) == 1) r = fn_8017F244(0, 20); if ((u16)w0 + (u16)w1 > (u16)w2 + (u16)w3) r = fn_8017F244(r, 10); return fn_8017F244(r, -5); }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801C106C(u8* a, u8* b) { s32 x = fn_803AC828(); u32 i; if (fn_801C384C(b) == 0) return 1; if (fn_801C0FC0(a, b) != 0) return 2; for (i = 0; i < 4; i++) { if ((u8)i != 0 && (u8)i != 2 && (u8)fn_803C93C4(x, i, 0) == 3) { s32 y = fn_803C93C4(x, i, 2); s32 e = fn_8017E9DC(b); if ((u8)y == (u8)fn_803C91C0(i, e)) return 1; } } return 0; }
#pragma pop

s32 fn_8019C308(s32, s32, s32, s32, s32);
#pragma push
#pragma optimize_for_size on
s32 fn_801ABE1C(s32 a, s32 b, s32 c, s32 d) { s32 r = fn_8017F244(0, 10); if (fn_80180618(a, b, 0x63) == 1 || fn_80180618(a, d, 0x63) == 1) r = fn_8017F244(r, 100); if ((u16)fn_801804B8(a, b) == 0x33) r = fn_8017F244(r, 10); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B629C(s32 a, s32 b, s32 c, s32 d) { s32 r; s32 t; s32 x; fn_80180A9C(a, b); t = fn_80180AC8(a, b); x = fn_8019C308(a, b, c, d, 1) / 2 * 100 / (u16)t; if (x > 100) x = 100; r = fn_8017F244(0, x / 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A4DBC(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_801817D0(a, d); s32 t = fn_801817F0(a, d); if ((u8)s == 0 && (u8)t == 0) return 0; if (fn_80185D28(a, b, d, c, 0x90, 1, 1) == 0 && fn_80185D28(a, b, d, c, 0x90, 2, 1) == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A6898(s32 a, s32 b) { s32 r = 0; s32 v; if (fn_80180618(a, b, 0x14) == 1) r = fn_8017F244(0, 20); v = fn_801804B8(a, b); if ((u16)(v + 0xfff6) <= 1) r = fn_8017F244(r, 20); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); return fn_8017F244(r, -10); }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A678C(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_80180A9C(a, b); s32 r; s32 x = fn_8019C308(a, b, c, d, 1); r = fn_8017F244(0, x / 2 * 100 / (u16)s / 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u16)fn_801804B8(a, b) == 0x7b) r = fn_8017F244(r, 5); if (fn_80180618(a, d, 0x40) == 1) r = fn_8017F244(r, -50); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B78E4(s32 a, s32 b) { u32 buf2[8]; u32 buf1[8]; s32 r = 0; s32 n; u16 i; fn_801C03A0(lbl_8063F248, a, buf1, 1, 1); n = fn_801C03A0(lbl_8063F248, a, buf2, 0, 1); if (fn_801818F8(a, b) == 0) r = fn_8017F244(0, 20); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf2[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_801818F8(a, b) == 1) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma pop

s32 fn_8017E900(void);
s32 fn_8017FE6C(s32, u32);
s32 fn_8017FE74(s32, u32);
s32 fn_801C24B4(s32, u16, u8, u16, u8);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B21B8(s32 a) { u32 buf[8]; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 r = fn_8017F244(0, (u16)fn_8017E900() % 21); u16 i; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801BCB1C(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; fn_801C03A0(lbl_8063F248, a, buf, 0, 1); if (fn_80180618(a, b, 0x5c) == 1) r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, 5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A18E8(s32 a, s32 b, s32 c, u8* d) { u32 buf[8]; s32 r; s32 q; u32 f; q = fn_801BF694(0, d); if (fn_80180618(a, (s32)d, 0x15) == 1) return 0; if (d == 0) f = 0; else f = *(u32*)(d + 0x794); if (f & 0x400) return 0; r = fn_801A0C34(a, b, c, (s32)d, 0); if ((u16)fn_801C121C(q, buf) == 0) r = 0; if (r == 0) return 0; return 1; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A3D70(s32 a, u8* b, s32 c, s32 d) { s32 r; u8 v; u8 x; s32 w; v = fn_8017F464(a, c, (s32)b); r = fn_801A0C34(a, (s32)b, c, d, 0); if (b == 0) x = 0; else x = (*(u32*)(*(u8**)(b + 0x798)) >> 8) & 7; if (x == 0) r = 0; w = fn_8017F5C8(a, (s32)b, c); if (fn_801808E8(a, d, v, w) == 0x43) r = 0; if (r == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A2AF8(s32 a, u8* b, s32 c, s32 d) { s32 r; u8 v; u32 m; s32 w; v = fn_8017F464(a, c, (s32)b); if (b == 0) m = 0; else { u8* q = inl_3AA4(inl_ptr8(b)); if (q == 0) m = 0; else m = *(u32*)(q + 0x10); } if ((m & 7) == 0) return 0; r = fn_801A0C34(a, (s32)b, c, d, 0); w = fn_8017F5C8(a, (s32)b, c); if (fn_801808E8(a, d, v, w) == 0x43) r = 0; if (r == 0) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AB820(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 s = fn_80180478(a, b); s32 t = fn_80180478(a, d); u32 ok = 1; if ((u16)s != 0 || (u16)t == 0xd0 || (u16)t == 0 || fn_801C2DE8((u16)t) == 0) ok = 0; if (ok == 1) r = fn_8017F244(0, 10); if (fn_80180618(a, d, 0x3c) == 1 || fn_80180618(a, d, 0x79) == 1) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A01B4(s32 a, s32 b, s32 c, s32 d) { u32 buf[0x18]; s32 sum = 0; s32 n = fn_801C05F0(0, a, buf, 1, 1); u16 i; for (i = 0; i < (u16)n; i++) { s32 x = fn_8017FE6C(a, buf[i]); s32 y = fn_8017FE74(a, buf[i]); s32 z = fn_8017FE6C(a, d); s32 w = fn_8017FE74(a, d); sum += fn_801C24B4(c, x, y, z, w); } return sum; }
#pragma pop
#pragma pop

u32 fn_80185D20(s32, s32, s32);
s32 fn_801A1040(s32, s32, s32);
s32 fn_80181398(s32, s32);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ADB90(s32 a) { u32 buf2[0x18]; u32 buf1[8]; s32 r = 0; s32 n1 = fn_801C03A0(lbl_8063F248, a, buf1, 0, 1); s32 n2 = fn_801C05F0(0, a, buf2, 1, 1); u16 i; for (i = 0; i < (u16)n2; i++) { if (fn_80180058(a, buf2[i]) == 0) r = fn_8017F244(r, 10); } for (i = 0; i < (u16)n1; i++) { if ((u8)fn_801824F8(a, buf1[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A4210(s32 a, s32 b, s32 c, u8* d) { s32 s = fn_801817D0(a, (s32)d); s32 t = fn_80181810(a, (s32)d); u32 f; if (fn_80185D20(a, (s32)d, c) == 1) return 0; if ((u8)s == 0 && (u8)t == 0) return 0; if (fn_80185D28(a, b, (s32)d, c, 0xa0, 1, 1) == 0 && fn_80185D28(a, b, (s32)d, c, 0xa0, 4, 1) == 0) return 0; if (d == 0) f = 0; else f = *(u32*)(d + 0x790); if (f & 0x1000000) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF3BC(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 x = fn_80180130(a, d); s32 y = fn_801801F0(a, d); u16 i; if ((u16)x < (u16)y) r = fn_8017F244(0, 10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if ((u8)fn_80181830(a, d) <= 4) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF4CC(s32 a, s32 b, s32 c, s32 d) { u32 buf[10]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(0, 10); break; } } if ((u8)fn_80181858(a, d) <= 4) r = fn_8017F244(r, -20); if (fn_80180618(a, b, 0x63) == 1 || fn_80180618(a, d, 0x63) == 1) r = fn_8017F244(r, -50); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A1EE8(s32 a, s32 b, s32 c, u8* d) { u8* q = fn_801C0AAC(2, d); s32 r; u32 f; if (fn_80180618(a, (s32)d, 0x14) == 1) return 0; if (d == 0) f = 0; else f = *(u32*)(d + 0x790); if (f & 0x1000000) return 0; if (d == 0) f = 0; else f = *(u32*)(d + 0x790); if (f & 7) return 0; if (fn_801A1040(a, (s32)d, 7) == 0) return 0; r = fn_801A0C34(a, b, c, (s32)d, 0); if (fn_801C0A4C(q, 8) == 1) return 0; return r != 0; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A2848(s32 a, u8* b, s32 c, u8* d) { u8 b40[0x40]; u8 b8[0x38]; s32 w; s32 y; s32 x; s32 m; s32 r; u16 v; x = fn_803AC828(); y = fn_803AC848(fn_803AC828()); fn_801810F4(a, (s32)d, b40, (s32)b8, 0); m = fn_80181398(a, (s32)d); r = fn_801A0C34(a, (s32)b, c, (s32)d, 0); if (b == 0) w = 0; else w = *(s32*)(*(u8**)(b + 0x798) + 0xc); if (w != fn_803C8C48(x, y, 3, fn_8017E954((s32)b)) && (u16)m == 0) return 0; if (d == 0) v = 0; else v = *(u16*)(*(u8**)(d + 0x798) + 0x20); if (v != 0) return 0; return (u32)(-r | r) >> 31; }
#pragma pop
#pragma push
#pragma dont_inline on
s32 fn_801A44F8(s32 a, s32 b, s32 c, s32 d) { s32 s = fn_80180478(a, b); s32 t = fn_80180478(a, d); if (((u16)s == 0 && (u16)t == 0) || (u16)s == 0xd0 || (u16)t == 0xd0 || ((u16)s != 0 && fn_801C2DE8(s) == 0) || ((u16)t != 0 && fn_801C2DE8(t) == 0)) return 0; if (fn_80180618(a, d, 0x3c) == 1) return 0; return 1; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A48FC(s32 a, s32 b, s32 c, s32 d) { s32 r; u8 v = fn_8017F464(a, c, b); s32 s = fn_80180A9C(a, b); s32 w; if ((u16)fn_80180A9C(a, d) <= (u16)s) return 0; r = fn_801A0C34(a, b, c, d, 0); w = fn_8017F5C8(a, b, c); if (fn_801808E8(a, d, v, w) == 0x43) r = 0; if (r == 0) return 0; return 1; }
#pragma pop

extern u16 lbl_80421808[];
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ADFB0(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_801807FC(a, d, 7) == 1) r = fn_8017F244(0, 30); if ((u8)fn_80181878(a, d) >= 8) r = fn_8017F244(r, 20); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_8017EBB0(d) & 0x20000000) r = fn_8017F244(r, -30); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AC590(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 v = fn_80181718(a, 0, 1); s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if ((u8)v == 1) r = fn_8017F244(0, 10); if (fn_80180B40(a, b, lbl_806416D8, -1) == 1) r = fn_8017F244(r, 30); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if ((u8)(v + 0xfe) <= 2) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B6370(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; u32 k; for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(0, 10); break; } } for (k = 0; k < 5; k++) { if (fn_801C06CC(0, a, 1, 1, lbl_80421808[(u16)k], d) == 1) { r = fn_8017F244(r, -100); break; } } if (fn_80180618(a, d, 0x4d) == 1) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A36FC(s32 a, u8* b, s32 c, u8* d) { s32 s = fn_801C4600(b); s32 t = fn_801C4600(d); s32 r = fn_801A0C34(a, (s32)b, c, (s32)d, 0); if (fn_80180618(a, (s32)d, 0xc) == 1) r = 0; if (fn_801A1040(a, (s32)d, 0xf0000) == 0) return 0; if ((u8)s == (u8)t || fn_80180BD8(a, d) == 1 || (inl_790(d) & 0xf0000) || (u8)s == 2 || (u8)t == 2) r = 0; if (r == 0) return 0; return 1; }
#pragma pop

extern const f32 lbl_806416E0;
extern const f32 lbl_806416E4;
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B70D8(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n; u16 i; fn_801C0AAC(14, (void*)b); n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); if (fn_801807FC(a, d, 0x11) == 1) r = fn_8017F244(0, 30); if ((u8)fn_80181878(a, d) >= 8) r = fn_8017F244(r, 20); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_80181700(d) & 0x400000) r = fn_8017F244(r, -30); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_801A14DC(s32 a, s32 b, s32 c, u8* d) { s32 r; u8 v; u32 m; s32 w; v = fn_8017F464(a, c, b); if (inl_790(d) & 0x1000000) return 0; if (d == 0) m = 0; else { u8* q = inl_3AA4(inl_ptr8(d)); if (q == 0) m = 0; else m = *(u32*)(q + 0x10); } if ((m & 7) == 0) return 0; r = fn_801A0C34(a, b, c, (s32)d, 0); w = fn_8017F5C8(a, b, c);  if (fn_801808E8(a, (s32)d, v, w) == 0x43) return 0; return r != 0; }
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF164(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 x; s32 y; u16 i; fn_801800D0(a, d); fn_80180190(a, d); x = fn_801800D0(a, d); y = fn_80180190(a, d); if ((u16)x > (u16)y) r = fn_8017F244(0, 10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if ((u8)fn_801817D0(a, d) <= 4) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B7494(s32 a, s32 b) { u8 buf[0x60]; s32 r = 0; u8 n = fn_801C05F0(0, a, buf, 1, 1); if (fn_80180B40(a, b, lbl_806416E0, -1) == 1) r = fn_8017F244(0, 30); else if (fn_80180B40(a, b, lbl_806416E4, -1) == 1) r = fn_8017F244(0, 20); else if (fn_80180B40(a, b, lbl_806416D8, -1) == 1) r = fn_8017F244(0, 10); if (((u8)fn_801C087C(0) == 2 && n <= 2) || ((u8)fn_801C087C(0) == 1 && n <= 1)) r = fn_8017F244(r, -150); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A5C38(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 x; u8 v; fn_801C03A0(lbl_8063F248, a, buf, 0, 1); x = ((u8)fn_80181878(a, d) - 6) * 5; if (x > 0) r = fn_8017F244(0, x); v = fn_80181858(a, b); if (v < 6) r = fn_8017F244(r, (6 - v) * 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_80180618(a, b, 0x63) == 1 || fn_80180618(a, d, 0x63) == 1) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma pop

s32 fn_801BF228(u32* p, u32 v) { if (p[0] == 0) { p[0] = v; return 0; } if (p[1] == 0) { p[1] = v; return 1; } if (p[2] == 0) { p[2] = v; return 2; } if (p[3] == 0) { p[3] = v; return 3; } if (p[4] == 0) { p[4] = v; return 4; } if (p[5] == 0) { p[5] = v; return 5; } if (p[6] == 0) { p[6] = v; return 6; } if (p[7] == 0) { p[7] = v; return 7; } return -1; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801BF040(s32 a) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(0, 30); for (i = 0; i < (u16)n; i++) { if (fn_80180618(a, buf[i], 0x12) == 1) r = fn_8017F244(r, -20); } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801BF114(s32 a) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(0, 30); for (i = 0; i < (u16)n; i++) { if (fn_80180618(a, buf[i], 0xb) == 1 || fn_80180618(a, buf[i], 0x57) == 1) r = fn_8017F244(r, -20); } return r; }
#pragma pop
#pragma pop
void fn_801C3218(u8* p) { if (p) p[0x881] = 0; if (p) p[0x882] = 0; if (p) p[0x883] = 0; if (p) p[0x884] = 0; if (p) p[0x885] = 0; if (p) p[0x886] = 0; if (p) p[0x887] = 0; if (p) p[0x888] = 0; if (p) *(u32*)(p + 0x88c) = 0; if (p) *(u16*)(p + 0x890) = 0; if (p) *(u16*)(p + 0x892) = 0; if (p) *(u16*)(p + 0x894) = 0; if (p) *(u16*)(p + 0x896) = 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_8019E6EC(s32 a, s32 b, s32 c, s32 d) { u32 buf[0x18]; s32 sum = 0; s32 n = fn_801C05F0(0, a, buf, 1, 1); u16 i; for (i = 0; i < (u16)n; i++) { s32 x = fn_8017FE6C(a, buf[i]); s32 y = fn_8017FE74(a, buf[i]); s32 z = fn_80180A4C(a, d); s32 w = fn_80180A74(a, d); sum += fn_801C24B4(c, x, y, z, w); } return sum; }
#pragma pop
#pragma pop

s32 fn_8017EA60(s32);
s32 fn_803C922C(u8, u8);
u16 fn_801C1D10(s32 a, s32 b, u32 c) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return 0; x = fn_8017EA60(b); y = fn_8017E9DC((u8*)b); idx = fn_803C922C(x, y); if ((u8)idx == 0xff) return 0; idx = (u8)idx; x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); return *(u16*)(fn_803C940C(fn_803AC828(), 0, x, z) + (u8)c * 2 + 0xc); }
u16 fn_801C1EB0(s32 a, s32 b) { u32 idx; s32 x; s32 y; s32 z; u8* p; if (a == 0) return 0; x = fn_8017EA60(b); y = fn_8017E9DC((u8*)b); idx = fn_803C922C(x, y); if ((u8)idx == 0xff) return 0; idx = (u8)idx; x = fn_8017E9A0(fn_801C0AAC(30, lbl_8048DFB8[idx])); p = lbl_8048DFB8[idx]; y = fn_8017E9DC(inl_ptr8(p)); z = fn_803C91C0(x, y); return *(u16*)(fn_803C940C(fn_803AC828(), 0, x, z) + 0x46); }

void fn_801C3104(u8* p) { if (p) *(u16*)(p + 0x86c) = 0; if (p) *(u16*)(p + 0x86e) = 0; if (p) *(u16*)(p + 0x870) = 0; if (p) *(u16*)(p + 0x872) = 0; if (p) p[0x874] = 0; if (p) p[0x875] = 0; if (p) p[0x876] = 0; if (p) p[0x877] = 0; if (p) p[0x878] = 0; if (p) p[0x879] = 0; if (p) p[0x87a] = 0; if (p) p[0x87b] = 0; if (p) p[0x87c] = 0; if (p) p[0x87d] = 0; if (p) p[0x87e] = 0; if (p) p[0x87f] = 0; if (p) p[0x880] = 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801BEC5C(s32 a) { u32 buf2[8]; u32 buf1[8]; s32 r = 0; s32 n1 = fn_801C03A0(lbl_8063F248, a, buf1, 1, 1); s32 n2 = fn_801C03A0(lbl_8063F248, a, buf2, 0, 1); u16 i; for (i = 0; i < (u16)n1; i++) { if (fn_80180618(a, buf1[i], 0x2b) == 1) r = fn_8017F244(r, 10); } for (i = 0; i < (u16)n2; i++) { if (fn_80180618(a, buf2[i], 0x2b) == 1) r = fn_8017F244(r, -10); } return r; }
#pragma pop
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AAD20(s32 a, s32 b, s32 c, s32 d) { u32 buf[0x18]; s32 n = fn_801C05F0(0, a, buf, 1, 1); s32 t = (u8)fn_8017F5C0(a, c); s32 r = fn_8017F244(0, t / 2);  u16 i; for (i = 0; i < (u16)n; i++) { if (fn_801AA548(buf[i]) & 7) { r = fn_8017F244(r, -2); break; } } if (fn_80180B9C(a, d) == 0 || fn_80180618(a, d, 0xf) == 1 || fn_80180618(a, d, 0x48) == 1 || fn_80180618(a, d, 0x13) == 1) r = fn_8017F244(r, -2); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF28C(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 x = fn_80180130(a, d); s32 y = fn_801801F0(a, d); u8 i; if ((u16)x > (u16)y) r = fn_8017F244(0, 10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_8017EBB0(d) & 7) r = fn_8017F244(r, 5); if ((u8)fn_801817F0(a, d) <= 4) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B0238(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_80180B40(a, b, lbl_806416E0, -1) == 1) r = fn_8017F244(0, 30); else if (fn_80180B40(a, b, lbl_806416E4, -1) == 1) r = fn_8017F244(0, 20); else if (fn_80180B40(a, b, lbl_806416D8, -1) == 1) r = fn_8017F244(0, 10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop

s32 fn_80180050(s32, s32);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF020(s32 a, s32 b, s32 c, s32 d) { u32 buf2[8]; u32 buf1[8]; s32 r = 0; u32 found = 0; s32 n1 = fn_801C03A0(lbl_8063F248, a, buf1, 0, 1); s32 n2 = fn_801C03A0(lbl_8063F248, a, buf2, 1, 1); u16 i; for (i = 0; i < (u16)n2; i++) { if (fn_80180D1C(a, d, buf2[i]) > 0) { found = 1; break; } } if (found == 1) r = fn_8017F244(0, 10); for (i = 0; i < (u16)n1; i++) { if ((u8)fn_801824F8(a, buf1[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_8018E388(lbl_8063F248) & 0x70000) r = fn_8017F244(r, -40); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AED4C(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 s = fn_80180050(a, b); s32 t = fn_80180050(a, d); u16 i; if (s * 3 <= t) r = fn_8017F244(0, 20); else if (s * 2 <= t) r = fn_8017F244(0, 10); if (t * 3 <= s) r = fn_8017F244(r, -20); else if (t * 2 <= s) r = fn_8017F244(r, -10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B733C(s32 a, s32 b, s32 c, s32 d) { s32 r = 0; s32 v = fn_80181718(a, 0, 1); u8 w; if (fn_80180D1C(a, d, b) > 0) r = fn_8017F244(0, 10); if ((fn_80180618(a, d, 0x22) == 1 && (u8)v == 1) || (fn_80180618(a, d, 0x21) == 1 && (u8)v == 2)) r = fn_8017F244(r, 10); w = fn_80181850(a, b); if (w < 6) r = fn_8017F244(r, (6 - w) * 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_80180D1C(a, b, d) > 0) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801B15E0(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; if (fn_801A5A54(a, d, 8, 9) == 1) r = fn_8017F244(0, 0); if (fn_801A5A54(a, d, 10, 12) == 1) r = fn_8017F244(r, 0); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if (fn_801A5A54(a, d, 3, 4) == 1) r = fn_8017F244(r, -10); if (fn_801A5A54(a, d, 0, 2) == 1) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
s32 fn_801A47A4(s32 a, s32 b, s32 c, u8* d) { s32 r; if (fn_80180618(a, (u32)d, 0x48) == 1) return 0; if (fn_80180618(a, (u32)d, 0xf) == 1) return 0; if (inl_790(d) & 0x1000000) return 0; if (fn_801C0A4C(fn_801C0AAC(2, d), 8) == 1) return 0; r = fn_801A0C34(a, b, c, (s32)d, 0); if (fn_80185B6C(a, (s32)d) == 1) return 0; if (inl_794(d) & 0x1800) return 0; if (fn_80180B9C(a, (s32)d) == 0) return 0; return r != 0; }
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801ADE20(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 i; fn_80181380(a, d); for (i = 0; i < (u16)n; i++) { s32 x = fn_801800D0(a, buf[i]); s32 y = fn_80180190(a, buf[i]); if ((u16)x < (u16)y) { r = fn_8017F244(0, 5); break; } } for (i = 0; i < (u16)n; i++) { s32 w0 = fn_801800D0(0, buf[i]); s32 w1 = fn_80180190(0, buf[i]); s32 w2 = fn_80180130(0, buf[i]); s32 w3 = fn_801801F0(0, buf[i]); if ((u16)w0 + (u16)w1 > (u16)w2 + (u16)w3) r = fn_8017F244(r, 5); } return r; }
#pragma pop
#pragma pop

s32 fn_8017EB98(u8*);
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A97C4(s32 a, s32 b, s32 c, s32 d) { s32 r; u8* q = fn_801C0AAC(3, (void*)b); r = fn_8017F244(0, (u8)fn_8017F5C0(a, c) / 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if (fn_8017EBB0(d) & 7) r = fn_8017F244(r, -5); if (fn_80180618(a, d, 0x13) == 1 || fn_80180618(a, d, 0x14) == 1 || fn_80180618(a, d, 0x4d) == 1) r = fn_8017F244(r, -5); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -5); if (fn_8017EB98(q) & 8) r = fn_8017F244(r, -5); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A8568(s32 a, s32 b, s32 c, s32 d) { s32 r; u8* q = fn_801C0AAC(3, (void*)b); r = fn_8017F244(0, 2); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)fn_801817D0(a, d) == 0) r = fn_8017F244(r, -2); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -2); if (fn_80180618(a, d, 0x1d) == 1 || fn_80180618(a, d, 0x13) == 1 || fn_80180618(a, d, 0x49) == 1 || fn_80180618(a, d, 0x34) == 1) r = fn_8017F244(r, -2); if (fn_8017EB98(q) & 0x40) r = fn_8017F244(r, -2); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A9040(s32 a, s32 b, s32 c, s32 d) { s32 r; u8* q = fn_801C0AAC(3, (void*)b); r = fn_8017F244(0, (u8)fn_8017F5C0(a, c) / 5); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)fn_80181830(a, d) == 0) r = fn_8017F244(r, -5); if (fn_80180618(a, d, 0x1d) == 1 || fn_80180618(a, d, 0x13) == 1 || fn_80180618(a, d, 0x49) == 1) r = fn_8017F244(r, -5); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -5); if (fn_8017EB98(q) & 0x40) r = fn_8017F244(r, -5); return r; }
#pragma pop
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A8EFC(s32 a, s32 b, s32 c, s32 d) { s32 r; u8* q = fn_801C0AAC(3, (void*)b); r = fn_8017F244(0, 10); if (fn_801C06CC(0, a, 1, 1, 0x10e, 0) == 1) r = fn_8017F244(r, 30); if ((u8)fn_80181810(a, d) == 0) r = fn_8017F244(r, -10); if (fn_80180618(a, d, 0x1d) == 1 || fn_80180618(a, d, 0x13) == 1 || fn_80180618(a, d, 0x49) == 1) r = fn_8017F244(r, -10); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -10); if (fn_8017EB98(q) & 0x40) r = fn_8017F244(r, -10); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AF834(s32 a, s32 b, s32 c, s32 d) { u32 buf[8]; s32 r = 0; s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); s32 w0 = fn_801800D0(a, d); s32 w1 = fn_80180190(a, d); s32 w2 = fn_80180130(a, d); s32 w3 = fn_801801F0(a, d); u16 i; if ((u16)w0 > (u16)w1) r = fn_8017F244(0, 10); if ((u16)w2 > (u16)w3) r = fn_8017F244(r, 10); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } if ((u8)fn_801817D0(a, d) <= 4 && (u8)fn_801817F0(a, d) <= 4) r = fn_8017F244(r, -20); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801A83D8(s32 a, u8* b, s32 c, s32 d) { s32 r = 0; s32 x = fn_803AC828(); s32 y = fn_803AC848(fn_803AC828()); s32 z = fn_803C8C48(x, y, 3, fn_8017E954((s32)b)); if (fn_801A854C(b) == z) r = fn_8017F244(0, 150); if (fn_80180618(a, d, 0x27) == 1 || fn_80180618(a, d, 0x13) == 1) r = fn_8017F244(r, -150); if (fn_8017EBB0(d) & 0x1000000) r = fn_8017F244(r, -150); if (fn_80180618(a, d, 0x50) == 1) r = fn_8017F244(r, -40); if ((u32)(fn_8017EBC8(d) & 7) >= 2) r = fn_8017F244(r, -200); if (fn_801C06CC(0, a, 1, 1, 0xfc, 0) == 1) r = fn_8017F244(r, -200); return r; }
#pragma pop
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma push
#pragma dont_inline on
s32 fn_801AC78C(s32 a, s32 b) { u32 buf[8]; s32 r = 0; s32 v = fn_80181718(a, 0, 0); s32 n = fn_801C03A0(lbl_8063F248, a, buf, 0, 1); u16 m; u16 i; m = fn_801804B8(a, b); if (m == 5 || m == 0xb) r = fn_8017F244(0, 20); if (fn_80180B40(a, b, lbl_806416D8, -1) == 1) r = fn_8017F244(r, 30); if (fn_80180B9C(a, b) == 0) r = fn_8017F244(r, 5); if (fn_80180618(a, b, 0x5d) == 1 && (v & 2)) r = fn_8017F244(r, 20); for (i = 0; i < (u16)n; i++) { if ((u8)fn_801824F8(a, buf[i], 0x185) == 1) { r = fn_8017F244(r, 10); break; } } return fn_8017F244(r, -20); }
#pragma pop
#pragma pop

void fn_801A13DC(void);
void fn_801A13E4(void);
s32 fn_801A16AC(s32, s32, s32, s32, s32, s32, s32);
void fn_801A19C0(void);
void fn_801A1E50(void);
s32 fn_801A3410(void);
void fn_801A3818(void);
void fn_801A3874(void);
void fn_801A3B34(void);
s32 fn_80392BD4(s32, s32);
s32 fn_80392C08(s32, s32);
s32 fn_80392C70(s32, s32);
s32 fn_803975E8(s32, s32, s32);
s32 fn_80399C58(s32, s32, s32);
s32 fn_8019D984(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019D9A0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019D9B0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DA24(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DB08(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DB18(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DC6C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DDA4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019DE90(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019DDFC, 0); }
s32 fn_8019E124(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E0B4, 0); }
s32 fn_8019E14C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019E1D0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E164, 0); }
s32 fn_8019E21C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E1F0, 0); }
s32 fn_8019E2AC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E23C, 0); }
s32 fn_8019E304(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E2D8, 0); }
s32 fn_8019E32C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019E450(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019E3E8, 0); }
s32 fn_8019E4A4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019E6D0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019E7C4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019E80C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EB28(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EB38(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EC48(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019EBB8, 0); }
s32 fn_8019ED0C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C256C(p0, p2, p1, p3, 0, (s32)&fn_8019EC90, 0); }
s32 fn_8019EF10(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF20(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF38(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF48(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF58(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF68(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF88(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EF98(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EFA8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EFB8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EFC8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EFE0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019EFF8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F010(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F058(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F068(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F080(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F0B0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F0C0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F0D0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F0E0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F0F0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F110(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F128(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F138(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F160(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F170(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F180(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F198(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F1A8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F1B8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F1C8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F1D8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F1E8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_8019D8E4(p0, p2, p1, p3); }
s32 fn_8019F200(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F224(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F240(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F25C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F278(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F294(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F2B0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F2CC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F310(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F364(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F3CC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F418(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F43C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F4AC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F4C8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F4EC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F508(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F560(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F58C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F618(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F634(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F650(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F66C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F688(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F6A4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F6C0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F6DC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F734(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F758(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F854(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019F938(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019F8BC, 0); }
s32 fn_8019F9E4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FB30(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FC0C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FB9C, 0); }
s32 fn_8019FC34(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FCC4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FC58, 0); }
s32 fn_8019FD10(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FCE4, 0); }
s32 fn_8019FDA0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FD30, 0); }
s32 fn_8019FDC8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FE10(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FDE4, 0); }
s32 fn_8019FE74(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FFA0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_8019FF38, 0); }
s32 fn_8019FFD0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_8019FFEC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0008(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A003C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0058(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0074(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A013C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0158(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0174(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0190(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A028C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A02E0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A04A4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A04C0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A05C4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A05F0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A060C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0630(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A073C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_801A06AC, 0); }
s32 fn_801A0800(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, (s32)&fn_801A0784, 0); }
s32 fn_801A0820(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A083C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0860(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0884(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A09B0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A09DC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A0A00(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801C297C(p0, p2, p1, p3, 0, 0, 0); }
s32 fn_801A17D8(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 16, 1, 65); }
s32 fn_801A17F4(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 16, 2, 65); }
s32 fn_801A1810(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 16, 4, 65); }
s32 fn_801A182C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 16, 7, 65); }
s32 fn_801A184C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 144, 1, 1); }
s32 fn_801A1868(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 144, 2, 1); }
s32 fn_801A1884(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 144, 3, 1); }
s32 fn_801A18A0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 144, 6, 1); }
s32 fn_801A18BC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 144, 7, 1); }
void fn_801A18E0(void) { fn_801A1E50(); }
void fn_801A1E64(void) { fn_801A19C0(); }
s32 fn_801A2000(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 32, 1, 65); }
s32 fn_801A201C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 32, 2, 65); }
s32 fn_801A2038(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 32, 3, 65); }
s32 fn_801A2054(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 32, 4, 65); }
s32 fn_801A2070(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 32, 5, 65); }
s32 fn_801A20E0(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 160, 1, 1); }
s32 fn_801A20FC(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 160, 2, 1); }
s32 fn_801A2118(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 160, 3, 1); }
s32 fn_801A2134(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 160, 5, 1); }
void fn_801A256C(void) { fn_801A1E50(); }
void fn_801A2574(void) { fn_801A19C0(); }
s32 fn_801A326C(s32 p0, s32 p1, s32 p2, s32 p3) { return fn_801A16AC(p0, p1, p3, p2, 16, 7, 65); }
s32 fn_801A35B4(void) { return fn_801A3410(); }
void fn_801A3820(void) { fn_801A3818(); }
void fn_801A3878(void) { fn_801A3874(); }
void fn_801A3B30(void) { fn_801A1E50(); }
void fn_801A3B38(void) { fn_801A3874(); }
void fn_801A3B90(void) { fn_801A3B34(); }
void fn_801A3B94(void) { fn_801A1E50(); }
void fn_801A4C90(void) { fn_801A13E4(); }
void fn_801A5020(void) { fn_801A13DC(); }
s32 fn_801A60E0(void) { return fn_8017F244(0, 5); }
s32 fn_801AE8B4(void) { return fn_8017F244(0, 0); }
s32 fn_801C1688(s32 p0, s32 p1) { return fn_80399C58((s32)((u8*)&lbl_8063CE34+124), p0, p1); }
s32 fn_801C6664(s32 p0) { return fn_80392BD4((s32)((u8*)&lbl_8063CE34+24), p0); }
s32 fn_801C66E0(s32 p0) { return fn_80392C08((s32)((u8*)&lbl_8063CE34+24), p0); }
s32 fn_801C6728(s32 p0) { return fn_80392B38((s32)((u8*)&lbl_8063CE34+24), p0); }
s32 fn_801C673C(s32 p0) { return fn_80392C70((s32)((u8*)&lbl_8063CE34+24), p0); }
s32 fn_801C6780(s32 p0, s32 p1) { return fn_803975E8((s32)((u8*)&lbl_8063CE34+88), p0, p1); }

}

#pragma push
#pragma dont_inline on

extern "C" {

void fn_801A11C0();
void fn_801C3B34();
void fn_801C54D0();

s32 fn_8019C6C8(void) { return 0; }
s32 fn_8019D908(void) { return 0; }
s32 fn_8019D978(void) { return 0; }
void fn_8019D980(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019D994(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019D998(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019D99C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019D9C0(void) { return 0; }
s32 fn_8019D9C8(void) { return 0; }
s32 fn_8019D9D0(void) { return 0; }
s32 fn_8019D9D8(void) { return 0; }
s32 fn_8019D9E0(void) { return 0; }
void fn_8019D9E8(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019D9EC(void) { return 0; }
s32 fn_8019D9F4(void) { return 0; }
s32 fn_8019D9FC(void) { return 0; }
s32 fn_8019DA04(void) { return 0; }
s32 fn_8019DA0C(void) { return 0; }
s32 fn_8019DA14(void) { return 0; }
s32 fn_8019DA1C(void) { return 0; }
s32 fn_8019DA34(void) { return 0; }
s32 fn_8019DA6C(void) { return 0; }
void fn_8019DA74(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DAA0(void) { return 0; }
void fn_8019DAA8(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DAAC(void) { return 0; }
void fn_8019DAB4(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DB28(void) { return 40; }
void fn_8019DB98(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DBCC(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DBD0(void) { return 0; }
s32 fn_8019DBD8(void) { return 0; }
void fn_8019DBE0(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DBE4(void) { return 0; }
s32 fn_8019DBEC(void) { return 0; }
s32 fn_8019DBF4(void) { return 0; }
s32 fn_8019DBFC(void) { return 0; }
s32 fn_8019DC04(void) { return 0; }
s32 fn_8019DC0C(void) { return 0; }
s32 fn_8019DC14(void) { return 0; }
s32 fn_8019DC1C(void) { return 0; }
s32 fn_8019DC24(void) { return 0; }
s32 fn_8019DC2C(void) { return 0; }
s32 fn_8019DC34(void) { return 0; }
s32 fn_8019DC3C(void) { return 0; }
s32 fn_8019DC44(void) { return 0; }
s32 fn_8019DC4C(void) { return 0; }
void fn_8019DC54(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC58(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC5C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC60(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC64(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC68(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DC7C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019DCB0(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DCB4(void) { return 0; }
void fn_8019DCBC(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019DCC0(void) { return 0; }
s32 fn_8019DCC8(void) { return 0; }
s32 fn_8019DCD0(void) { return 0; }
s32 fn_8019DCD8(void) { return 0; }
s32 fn_8019DCE0(void) { return 0; }
s32 fn_8019DCE8(void) { return 0; }
s32 fn_8019DD38(void) { return 0; }
s32 fn_8019DD40(void) { return 0; }
s32 fn_8019DDB4(void) { return 0; }
s32 fn_8019DDBC(void) { return 0; }
s32 fn_8019DDC4(void) { return 0; }
s32 fn_8019DDCC(void) { return 0; }
s32 fn_8019DEB0(void) { return 5; }
s32 fn_8019DF24(void) { return 0; }
void fn_8019DF2C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019E060(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019E064(void) { return 0; }
s32 fn_8019E06C(void) { return 0; }
s32 fn_8019E074(void) { return 0; }
s32 fn_8019E07C(void) { return 0; }
s32 fn_8019E084(void) { return 0; }
s32 fn_8019E08C(void) { return 0; }
s32 fn_8019E094(void) { return 0; }
s32 fn_8019E09C(void) { return 0; }
s32 fn_8019E0A4(void) { return 0; }
s32 fn_8019E0AC(void) { return 0; }
s32 fn_8019E144(void) { return 0; }
s32 fn_8019E15C(void) { return 0; }
s32 fn_8019E2CC(void) { return 0; }
void fn_8019E2D4(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019E324(void) { return 0; }
void fn_8019E33C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019E340(void) { return 20; }
void fn_8019E3E0(s32 p0, s32 p1) { fn_8019E348(p0, p1); }
void fn_8019E3E4(s32 p0, s32 p1) { fn_8019E348(p0, p1); }
s32 fn_8019E470(void) { return 0; }
s32 fn_8019E478(void) { return 0; }
void fn_8019E480(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019E484(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019E488(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019E48C(void) { return 0; }
s32 fn_8019E494(void) { return 0; }
s32 fn_8019E49C(void) { return 0; }
void fn_8019E6E0(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019E6E4(void) { return 0; }
s32 fn_8019E7D4(void) { return 0; }
s32 fn_8019E804(void) { return 0; }
s32 fn_8019E81C(void) { return 0; }
s32 fn_8019E944(void) { return 0; }
s32 fn_8019E94C(void) { return 0; }
s32 fn_8019E954(void) { return 0; }
s32 fn_8019E95C(void) { return 0; }
s32 fn_8019E964(void) { return 0; }
void fn_8019E9CC(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EA2C(void) { return 0; }
s32 fn_8019EAD4(void) { return 0; }
s32 fn_8019EADC(void) { return 0; }
s32 fn_8019EAE4(void) { return 0; }
s32 fn_8019EAEC(void) { return 0; }
s32 fn_8019EAF4(void) { return 0; }
s32 fn_8019EAFC(void) { return 0; }
s32 fn_8019EB04(void) { return 0; }
s32 fn_8019EB0C(void) { return 0; }
void fn_8019EB14(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EB18(void) { return 0; }
s32 fn_8019EB20(void) { return 0; }
s32 fn_8019EB48(void) { return 0; }
void fn_8019EB50(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EC68(void) { return 0; }
s32 fn_8019EC70(void) { return 0; }
s32 fn_8019EC78(void) { return 0; }
s32 fn_8019EC80(void) { return 0; }
s32 fn_8019EC88(void) { return 0; }
void fn_8019ED2C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019ED30(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019ED34(void) { return 0; }
void fn_8019ED3C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019ED40(void) { return 0; }
void fn_8019ED48(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
void fn_8019EE5C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EE60(void) { return 0; }
s32 fn_8019EE68(void) { return 0; }
void fn_8019EE70(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EE74(void) { return 0; }
void fn_8019EE7C(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EE80(void) { return 0; }
s32 fn_8019EE88(void) { return 0; }
s32 fn_8019EE90(void) { return 0; }
s32 fn_8019EE98(void) { return 0; }
s32 fn_8019EEA0(void) { return 0; }
s32 fn_8019EEA8(void) { return 0; }
void fn_8019EEB0(s32 p0, s32 p1, s32 p2, s32 p3) { fn_8019D910(p0, p1, p2, p3); }
s32 fn_8019EF30(void) { return 0; }
s32 fn_8019EF78(void) { return 0; }
s32 fn_8019EF80(void) { return 0; }
s32 fn_8019EFD8(void) { return 0; }
s32 fn_8019EFF0(void) { return 0; }
s32 fn_8019F008(void) { return 0; }
s32 fn_8019F020(void) { return 0; }
s32 fn_8019F028(void) { return 0; }
s32 fn_8019F030(void) { return 0; }
s32 fn_8019F038(void) { return 0; }
s32 fn_8019F040(void) { return 0; }
s32 fn_8019F048(void) { return 0; }
s32 fn_8019F050(void) { return 0; }
s32 fn_8019F078(void) { return 0; }
s32 fn_8019F090(void) { return 0; }
s32 fn_8019F098(void) { return 0; }
s32 fn_8019F0A0(void) { return 0; }
s32 fn_8019F0A8(void) { return 0; }
s32 fn_8019F100(void) { return 0; }
s32 fn_8019F108(void) { return 0; }
s32 fn_8019F120(void) { return 0; }
s32 fn_8019F148(void) { return 0; }
s32 fn_8019F150(void) { return 0; }
s32 fn_8019F158(void) { return 0; }
s32 fn_8019F190(void) { return 0; }
s32 fn_8019F1F8(void) { return 0; }
s32 fn_8019F21C(void) { return 0; }
s32 fn_8019F2E8(void) { return 0; }
s32 fn_8019F2F0(void) { return 0; }
s32 fn_8019F2F8(void) { return 0; }
s32 fn_8019F300(void) { return 0; }
s32 fn_8019F308(void) { return 0; }
s32 fn_8019F32C(void) { return 0; }
s32 fn_8019F334(void) { return 0; }
s32 fn_8019F33C(void) { return 0; }
s32 fn_8019F344(void) { return 0; }
s32 fn_8019F34C(void) { return 0; }
s32 fn_8019F354(void) { return 0; }
s32 fn_8019F35C(void) { return 0; }
s32 fn_8019F380(void) { return 0; }
s32 fn_8019F3C4(void) { return 0; }
s32 fn_8019F410(void) { return 0; }
s32 fn_8019F434(void) { return 0; }
s32 fn_8019F4E4(void) { return 40; }
s32 fn_8019F57C(void) { return 0; }
s32 fn_8019F584(void) { return 0; }
s32 fn_8019F5A8(void) { return 0; }
s32 fn_8019F5B0(void) { return 0; }
s32 fn_8019F5B8(void) { return 0; }
s32 fn_8019F5C0(void) { return 0; }
s32 fn_8019F5C8(void) { return 0; }
s32 fn_8019F5D0(void) { return 0; }
s32 fn_8019F5D8(void) { return 0; }
s32 fn_8019F5E0(void) { return 0; }
s32 fn_8019F5E8(void) { return 0; }
s32 fn_8019F5F0(void) { return 0; }
s32 fn_8019F5F8(void) { return 0; }
s32 fn_8019F600(void) { return 0; }
s32 fn_8019F608(void) { return 0; }
s32 fn_8019F610(void) { return 0; }
s32 fn_8019F750(void) { return 0; }
s32 fn_8019F774(void) { return 0; }
s32 fn_8019F77C(void) { return 0; }
s32 fn_8019F784(void) { return 0; }
s32 fn_8019F78C(void) { return 0; }
s32 fn_8019F794(void) { return 0; }
s32 fn_8019F79C(void) { return 0; }
s32 fn_8019F7EC(void) { return 0; }
s32 fn_8019F7F4(void) { return 0; }
s32 fn_8019F870(void) { return 0; }
s32 fn_8019F878(void) { return 0; }
s32 fn_8019F880(void) { return 0; }
s32 fn_8019F888(void) { return 0; }
s32 fn_8019F958(void) { return 5; }
s32 fn_8019F9DC(void) { return 0; }
s32 fn_8019FB4C(void) { return 0; }
s32 fn_8019FB54(void) { return 0; }
s32 fn_8019FB5C(void) { return 0; }
s32 fn_8019FB64(void) { return 0; }
s32 fn_8019FB6C(void) { return 0; }
s32 fn_8019FB74(void) { return 0; }
s32 fn_8019FB7C(void) { return 0; }
s32 fn_8019FB84(void) { return 0; }
s32 fn_8019FB8C(void) { return 0; }
s32 fn_8019FB94(void) { return 0; }
s32 fn_8019FC2C(void) { return 0; }
s32 fn_8019FC50(void) { return 0; }
s32 fn_8019FDC0(void) { return 0; }
s32 fn_8019FE30(void) { return 0; }
s32 fn_8019FE90(void) { return 20; }
void fn_8019FF30(s32 p0, s32 p1) { fn_8019FE98(p0, p1); }
void fn_8019FF34(s32 p0, s32 p1) { fn_8019FE98(p0, p1); }
s32 fn_8019FFC0(void) { return 0; }
s32 fn_8019FFC8(void) { return 0; }
s32 fn_801A0024(void) { return 0; }
s32 fn_801A002C(void) { return 0; }
s32 fn_801A0034(void) { return 0; }
s32 fn_801A01AC(void) { return 0; }
s32 fn_801A02A8(void) { return 0; }
s32 fn_801A02D8(void) { return 0; }
s32 fn_801A02FC(void) { return 0; }
s32 fn_801A0410(void) { return 0; }
s32 fn_801A0418(void) { return 0; }
s32 fn_801A0420(void) { return 0; }
s32 fn_801A0428(void) { return 0; }
s32 fn_801A0430(void) { return 0; }
s32 fn_801A04DC(void) { return 0; }
s32 fn_801A0584(void) { return 0; }
s32 fn_801A058C(void) { return 0; }
s32 fn_801A0594(void) { return 0; }
s32 fn_801A059C(void) { return 0; }
s32 fn_801A05A4(void) { return 0; }
s32 fn_801A05AC(void) { return 0; }
s32 fn_801A05B4(void) { return 0; }
s32 fn_801A05BC(void) { return 0; }
s32 fn_801A05E0(void) { return 0; }
s32 fn_801A05E8(void) { return 0; }
s32 fn_801A0628(void) { return 0; }
s32 fn_801A075C(void) { return 0; }
s32 fn_801A0764(void) { return 0; }
s32 fn_801A076C(void) { return 0; }
s32 fn_801A0774(void) { return 0; }
s32 fn_801A077C(void) { return 0; }
s32 fn_801A0858(void) { return 0; }
s32 fn_801A087C(void) { return 0; }
s32 fn_801A09CC(void) { return 0; }
s32 fn_801A09D4(void) { return 0; }
s32 fn_801A09F8(void) { return 0; }
s32 fn_801A0A1C(void) { return 0; }
s32 fn_801A0A24(void) { return 0; }
s32 fn_801A0A2C(void) { return 0; }
s32 fn_801A0A34(void) { return 0; }
s32 fn_801A0A3C(void) { return 0; }
s32 fn_801A0A44(void) { return 0; }
s32 fn_801A0A4C(void) { return 0; }
s32 fn_801A0A54(void) { return 0; }
s32 fn_801A0A5C(void) { return 0; }
s32 fn_801A0A64(void) { return 0; }
s32 fn_801A0A6C(void) { return 0; }
s32 fn_801A0A74(void) { return 0; }
s32 fn_801A0A7C(void) { return 0; }
s32 fn_801A0A84(void) { return 0; }
s32 fn_801A0A8C(void) { return 0; }
s32 fn_801A0A94(void) { return 0; }
s32 fn_801A0A9C(void) { return 0; }
s32 fn_801A0AA4(void) { return 0; }
s32 fn_801A0AAC(void) { return 0; }
s32 fn_801A0AB4(void) { return 0; }
s32 fn_801A0ABC(void) { return 0; }
s32 fn_801A0AC4(void) { return 0; }
s32 fn_801A0ACC(void) { return 0; }
s32 fn_801A0AD4(void) { return 0; }
s32 fn_801A0ADC(void) { return 0; }
s32 fn_801A0AE4(void) { return 0; }
s32 fn_801A0AEC(void) { return 0; }
s32 fn_801A0AF4(void) { return 0; }
s32 fn_801A0AFC(void) { return 0; }
s32 fn_801A0B04(void) { return 0; }
s32 fn_801A0B0C(void) { return 0; }
s32 fn_801A0B14(void) { return 0; }
s32 fn_801A0B1C(void) { return 0; }
s32 fn_801A0B24(void) { return 0; }
s32 fn_801A0B2C(void) { return 0; }
s32 fn_801A0B34(void) { return 0; }
s32 fn_801A0B3C(void) { return 0; }
s32 fn_801A0B44(void) { return 0; }
s32 fn_801A0B4C(void) { return 0; }
s32 fn_801A0B54(void) { return 0; }
s32 fn_801A0B5C(void) { return 0; }
s32 fn_801A0B64(void) { return 0; }
s32 fn_801A0B6C(void) { return 0; }
s32 fn_801A0B74(void) { return 0; }
s32 fn_801A0B7C(void) { return 0; }
s32 fn_801A0B84(void) { return 0; }
s32 fn_801A0B8C(void) { return 0; }
s32 fn_801A0B94(void) { return 0; }
s32 fn_801A0B9C(void) { return 0; }
s32 fn_801A0BA4(void) { return 0; }
s32 fn_801A0BAC(void) { return 0; }
s32 fn_801A0BB4(void) { return 0; }
s32 fn_801A0BBC(void) { return 0; }
s32 fn_801A0BC4(void) { return 0; }
s32 fn_801A0BCC(void) { return 0; }
s32 fn_801A0BD4(void) { return 0; }
s32 fn_801A0BDC(void) { return 0; }
s32 fn_801A0BE4(void) { return 0; }
s32 fn_801A0BEC(void) { return 0; }
s32 fn_801A0BF4(void) { return 0; }
s32 fn_801A0BFC(void) { return 0; }
s32 fn_801A0C04(void) { return 0; }
s32 fn_801A0C0C(void) { return 0; }
s32 fn_801A0C14(void) { return 0; }
s32 fn_801A0C1C(void) { return 0; }
s32 fn_801A0C24(void) { return 0; }
s32 fn_801A0C2C(void) { return 0; }
s32 fn_801A11B8(void) { return 1; }
void fn_801A13DC(void) { fn_801A11C0(); }
void fn_801A13E0(void) { fn_801A11C0(); }
void fn_801A13E4(void) { fn_801A11C0(); }
void fn_801A13E8(void) { fn_801A11C0(); }
void fn_801A13EC(void) { fn_801A11C0(); }
void fn_801A1848(void) { fn_801A11C0(); }
s32 fn_801A18D8(void) { return 1; }
void fn_801A18E4(void) { fn_801A11C0(); }
void fn_801A19C0(void) { fn_801A11C0(); }
void fn_801A19F0(void) { fn_801A11C0(); }
void fn_801A1C30(void) { fn_801A11C0(); }
void fn_801A1C80(void) { fn_801A11C0(); }
void fn_801A1E50(void) { fn_801A11C0(); }
void fn_801A1E54(void) { fn_801A11C0(); }
void fn_801A1E58(void) { fn_801A11C0(); }
void fn_801A1E5C(void) { fn_801A11C0(); }
void fn_801A1E60(void) { fn_801A11C0(); }
void fn_801A1E68(void) { fn_801A11C0(); }
void fn_801A1EE4(void) { fn_801A11C0(); }
void fn_801A2554(void) { fn_801A11C0(); }
void fn_801A2558(void) { fn_801A11C0(); }
void fn_801A255C(void) { fn_801A11C0(); }
void fn_801A2560(void) { fn_801A11C0(); }
void fn_801A2564(void) { fn_801A11C0(); }
void fn_801A2568(void) { fn_801A11C0(); }
void fn_801A2570(void) { fn_801A11C0(); }
void fn_801A2578(void) { fn_801A11C0(); }
void fn_801A25D8(void) { fn_801A11C0(); }
void fn_801A25DC(void) { fn_801A11C0(); }
s32 fn_801A277C(void) { return 1; }
s32 fn_801A2840(void) { return 1; }
void fn_801A295C(void) { fn_801A11C0(); }
void fn_801A2960(void) { fn_801A11C0(); }
void fn_801A2964(void) { fn_801A11C0(); }
s32 fn_801A2C00(void) { return 1; }
void fn_801A2F5C(void) { fn_801A11C0(); }
void fn_801A3084(void) { fn_801A11C0(); }
void fn_801A3154(void) { fn_801A11C0(); }
void fn_801A3158(void) { fn_801A11C0(); }
void fn_801A315C(void) { fn_801A11C0(); }
s32 fn_801A3410(void) { return 1; }
void fn_801A35B8(void) { fn_801A11C0(); }
void fn_801A36F8(void) { fn_801A11C0(); }
void fn_801A3818(void) { fn_801A11C0(); }
void fn_801A381C(void) { fn_801A11C0(); }
void fn_801A3870(void) { fn_801A11C0(); }
void fn_801A3874(void) { fn_801A11C0(); }
void fn_801A3938(void) { fn_801A11C0(); }
void fn_801A393C(void) { fn_801A11C0(); }
void fn_801A3978(s32 p0, s32 p1) { fn_801A3940(p0, p1); }
void fn_801A397C(s32 p0, s32 p1) { fn_801A3940(p0, p1); }
void fn_801A3980(s32 p0, s32 p1) { fn_801A3940(p0, p1); }
void fn_801A3AAC(void) { fn_801A11C0(); }
void fn_801A3AB0(void) { fn_801A11C0(); }
void fn_801A3AB4(void) { fn_801A11C0(); }
s32 fn_801A3B24(void) { return 1; }
void fn_801A3B2C(void) { fn_801A11C0(); }
void fn_801A3B34(void) { fn_801A11C0(); }
void fn_801A3B8C(void) { fn_801A11C0(); }
void fn_801A3B98(void) { fn_801A11C0(); }
s32 fn_801A3B9C(void) { return 0; }
void fn_801A3BD4(void) { fn_801A11C0(); }
void fn_801A3D04(void) { fn_801A11C0(); }
void fn_801A4320(void) { fn_801A11C0(); }
void fn_801A4324(void) { fn_801A11C0(); }
void fn_801A4328(void) { fn_801A11C0(); }
s32 fn_801A432C(void) { return 1; }
s32 fn_801A43D0(void) { return 1; }
void fn_801A471C(void) { fn_801A11C0(); }
s32 fn_801A4720(void) { return 1; }
void fn_801A479C(void) { fn_801A11C0(); }
void fn_801A47A0(void) { fn_801A11C0(); }
void fn_801A48F8(void) { fn_801A11C0(); }
void fn_801A49E0(void) { fn_801A11C0(); }
s32 fn_801A4B64(void) { return 1; }
void fn_801A4B6C(void) { fn_801A11C0(); }
void fn_801A4B70(void) { fn_801A11C0(); }
void fn_801A4B74(void) { fn_801A11C0(); }
void fn_801A4CC0(void) { fn_801A11C0(); }
void fn_801A4DB8(void) { fn_801A11C0(); }
void fn_801A4F50(void) { fn_801A11C0(); }
s32 fn_801A52CC(void) { return 1; }
void fn_801A52D4(void) { fn_801A11C0(); }
void fn_801A52D8(void) { fn_801A11C0(); }
void fn_801A52DC(void) { fn_801A11C0(); }
void fn_801A5324(void) { fn_801A11C0(); }
void fn_801A5370(void) { fn_801A11C0(); }
void fn_801A5374(void) { fn_801A11C0(); }
void fn_801A5408(void) { fn_801A11C0(); }
void fn_801A540C(void) { fn_801A11C0(); }
void fn_801A5410(void) { fn_801A11C0(); }
void fn_801A5414(void) { fn_801A11C0(); }
void fn_801A5418(void) { fn_801A11C0(); }
void fn_801A541C(void) { fn_801A11C0(); }
void fn_801A54AC(void) { fn_801A11C0(); }
void fn_801A54DC(void) { fn_801A11C0(); }
s32 fn_801A54E0(void) { return 1; }
s32 fn_801A54E8(void) { return 1; }
void fn_801A553C(void) { fn_801A11C0(); }
s32 fn_801A55E4(void) { return 1; }
s32 fn_801A55EC(void) { return 1; }
void fn_801A55F4(void) { fn_801A11C0(); }
void fn_801A5714(void) { fn_801A11C0(); }
void fn_801A579C(void) { fn_801A11C0(); }
void fn_801A5800(void) { fn_801A11C0(); }
void fn_801A5804(void) { fn_801A11C0(); }
void fn_801A5808(void) { fn_801A11C0(); }
void fn_801A580C(void) { fn_801A11C0(); }
void fn_801A5810(void) { fn_801A11C0(); }
void fn_801A5814(void) { fn_801A11C0(); }
void fn_801A5818(void) { fn_801A11C0(); }
void fn_801A581C(void) { fn_801A11C0(); }
void fn_801A5820(void) { fn_801A11C0(); }
void fn_801A5824(void) { fn_801A11C0(); }
void fn_801A5828(void) { fn_801A11C0(); }
void fn_801A582C(void) { fn_801A11C0(); }
void fn_801A5A2C(void) { fn_801A11C0(); }
void fn_801A5A30(void) { fn_801A11C0(); }
void fn_801A5A34(void) { fn_801A11C0(); }
void fn_801A5A38(void) { fn_801A11C0(); }
void fn_801A5A3C(void) { fn_801A11C0(); }
void fn_801A5A40(void) { fn_801A11C0(); }
void fn_801A5A44(void) { fn_801A11C0(); }
void fn_801A5A48(void) { fn_801A11C0(); }
void fn_801A5A4C(void) { fn_801A11C0(); }
void fn_801A5A50(void) { fn_801A11C0(); }
s32 fn_801BFC40(void) { return 1; }
s32 fn_801C297C(s32, s32, s32, s32, s32, s32, s32) { return 0; }
s32 fn_801C2984(s32, s32, u8*, s32, u16, u8) { return 0; }
s32 fn_801C298C(s32, s32, u8*, s32, u16, u8) { return 0; }
void fn_801C3AEC(void) {}
void fn_801C3B60(void) { fn_801C3B34(); }
u32 fn_801C45C8(u8* p, s32 x) {}
s32 fn_801C54C8(void) { return 1; }
void fn_801C5504(void) { fn_801C54D0(); }
void fn_801C5B4C(void) {}
void fn_801C5EBC(void) {}

}
#pragma pop

extern "C" {
// Placed late to avoid inlining
#pragma push
#pragma optimize_for_size on
s32 fn_8019D910(s32 a, s32 b, u32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if ((fn_80181700(d) & 0x40000) && c == 0x39) r *= 2; return r; }
#pragma pop
#pragma push
#pragma optimize_for_size on
s32 fn_8019DB30(s32 a, s32 b, u32 c, s32 d) { s32 r = fn_8019D8E4(a, c, b, d); if ((fn_80181700(d) & 0x40000) && c == 0xfa) r *= 2; return r; }
#pragma pop

}
