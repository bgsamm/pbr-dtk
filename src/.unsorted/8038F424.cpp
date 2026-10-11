#include "ds/DSbridge.hpp"
#include ".unsorted/8038F424.hpp"

#include "common.hpp"

extern "C" {

extern u32 lbl_806405C0;
extern u8 *lbl_806405A0;

u8 fn_8039A3FC(void) { return *(u8 *)(lbl_806405A0 + 0x88); }
void fn_8039B278(u8 *p, u32 v) { *(u32 *)(p + 0x4) = v; }
void fn_8039B280(u8 *p, u8 v) { *(u8 *)(p + 0x24) = v; }
void fn_8039B288(u8 *p, u32 v) { *(u32 *)(p + 0x24) = v; }
u32 fn_803A3070(u8 *p) { return *(u32 *)(p + 0x2c); }
void fn_803A36A0(void) {}
void fn_803A36A4(void) {}
void fn_803A36A8(void) {}
void fn_803A36AC(void) {}
void fn_803A36B0(void) {}
void fn_803A36B4(void) {}
s32 fn_803A3D2C(void) { return 1; }
void fn_803A3D40(void) {}
u32 fn_803A3D64(u8 *p) { return *(u32 *)(p + 0x20); }
void fn_803A3D78(void) {}
void fn_803A3D7C(void) {}
void fn_803A3F94(u8 *p, u32 v) { *(u32 *)(p + 0x28) = v; }
u8 fn_803A416C(u8 *p) { return *(u8 *)(p + 0x24); }
void fn_803A4764(u8 *p, u32 v) { *(u32 *)(p + 0x2c) = v; }
u32 fn_803A49D8(u8 *p) { return *(u32 *)(p + 0x24); }
u32 fn_803A4C78(u8 *p) { return *(u32 *)(p + 0xc); }
s32 fn_803A4D54(void) { return 0; }
void fn_803A4D5C(u8 *p, u32 v) { *(u32 *)(p + 0x1c) = v; }
void fn_803A4D64(void) {}
s32 fn_803A4D94(void) { return 0; }
void fn_803A5414(void) {}
void fn_803A5418(u8 *p, f32 v) { *(f32 *)(p + 0x4) = v; }
void fn_803A576C(void) {}
void fn_803A61A8(void) {}
void fn_803AA430(void) {}
void fn_803AB1D0(void) {}
u8 fn_803AB514(u8 *p) { return *(u8 *)(p + 0x185); }
u8 fn_803AB51C(u8 *p) { return *(u8 *)(p + 0x186); }
u8 *fn_803AB524(u8 *p) { return p + 0x28; }
void fn_803AB52C(void) {}
void fn_803AB530(void) {}
void fn_803AC820(u32 v) { lbl_806405C0 = v; }
u32 fn_803AC828(void) { return lbl_806405C0; }
s32 fn_803AC830(void) { return 8; }
u32 fn_803AC838(u8 *p) { return *(u32 *)(p + 0x4); }
u32 fn_803AC840(u8 *p) { return *(u32 *)(p + 0x2c); }
u32 fn_803AC848(u8 *p) { return *(u32 *)(p + 0x30); }
u32 fn_803AC860(u8 *p) { return *(u32 *)(p + 0x44); }
u32 fn_803ACA58(u8 *p) { return *(u32 *)(p + 0x164); }
u32 fn_803ACA60(u8 *p) { return *(u32 *)(p + 0xc); }
u32 fn_803ACA68(u8 *p) { return *(u32 *)(p + 0x10); }
u8 *fn_803ACA70(u8 *p) { return p + 0x11ec; }
u8 *fn_803ACA78(u8 *p) { return p + 0x23b2; }
u8 *fn_803ACA80(u8 *p) { return p + 0x23b4; }
u8 *fn_803ACA88(u8 *p) { return p + 0x23b6; }
u32 fn_803ACA90(u8 *p) { return *(u32 *)(p + 0x18); }
u32 fn_803ACD30(u8 *p) { return *(u32 *)(p + 0x23cc); }
u32 fn_803ADB9C(u8 *p) { return *(u32 *)(p + 0x23d0); }
u8 fn_803ADBA4(u8 *p) { return *(u8 *)(p + 0x23c0); }
u32 fn_803ADBAC(u8 *p) { return *(u32 *)(p + 0x23d8); }
s32 fn_803ADBB4(u8 *a) { return 1; }
s32 fn_803ADBBC(void) { return 0; }
s32 fn_803ADBC4(void) { return 1; }
u32 fn_803ADCB0(u8 *p) { return *(u32 *)(p + 0x23f0); }
void fn_803ADCB8(u8 *p, u32 v) { *(u32 *)(p + 0x2404) = v; }
void fn_803ADCC0(u8 *p, u8 v) { *(u8 *)(p + 0x2408) = v; }
u8 fn_803ADCD8(u8 *p) { return *(u8 *)(p + 0x23e4); }
void fn_803ADCE0(u8 *p, u8 v) { *(u8 *)(p + 0x23e4) = v; }
void fn_803ADE5C(u8 *a, u32 b) {}
u32 fn_803AF43C(u8 *p) { return *(u32 *)(p + 0x23e0); }
void fn_803B6164(void) {}
void fn_803B6168(void) {}
void fn_803B8798(void) {}
void fn_803B8B50(void) {}
void fn_803B9294(void) {}
void fn_803B97BC(void) {}
s32 fn_803C59F0(void) { return 0; }
s32 fn_803C88E8(void) { return 1; }
s32 fn_803C90E0(void) { return 192; }
u8 *fn_803C9108(u8 *p) { return p + 0x184; }
s32 fn_803D6B68(void) { return 0; }

}

extern "C" {

u8 *fn_8038FD10(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x28;
}

u16 fn_8038F804(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u8 fn_8038FD78(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x8);
    return 0;
}

u32 fn_8038FEB0(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return (*(u16 *)(p + 0xe) >> 11) & 0x1f;
    return 0;
}

}
extern "C" {

extern const f32 lbl_80642F08;
extern const f32 lbl_80642F10;
extern const f32 lbl_80642F18;
extern const f32 lbl_80642F20;
u8 *fn_8038F838(u8 **h, s32 i);
u8 *fn_8038FD10(u8 **h, s32 i);
u8 *fn_80390358(u8 **h, s32 i);
u8 *fn_8039062C(u8 **h, s32 i);
u8 *fn_803908E8(u8 **h, s32 i);
u8 *fn_80390BF8(u8 **h, s32 i);
u8 *fn_80391148(u8 **h, s32 i);
u8 *fn_80391858(u8 **h, s32 i);
u8 *fn_80392268(u8 **h, s32 i);
u8 *fn_8039252C(u8 **h, s32 i);
u8 *fn_803927EC(u8 **h, s32 i);
u8 *fn_80392B04(u8 **h, s32 i);
u8 *fn_80392FB4(u8 **h, s32 i);
u8 *fn_80393400(u8 **h, s32 i);
u8 *fn_803938E4(u8 **h, s32 i);
u8 *fn_80393FEC(u8 **h, s32 i);
u8 *fn_80394270(u8 **h, s32 i);
u8 *fn_803944F4(u8 **h, s32 i);
u8 *fn_80394778(u8 **h, s32 i);
u8 *fn_803949FC(u8 **h, s32 i);
u8 *fn_80394C80(u8 **h, s32 i);
u8 *fn_80394F04(u8 **h, s32 i);
u8 *fn_803951C4(u8 **h, s32 i);
u8 *fn_80395A54(u8 **h, s32 i);
u8 *fn_80395DB0(u8 **h, s32 i);
u8 *fn_80396370(u8 **h, s32 i);
u8 *fn_80396668(u8 **h, s32 i);
u8 *fn_803969F8(u8 **h, s32 i);
u8 *fn_80396CCC(u8 **h, s32 i);
u8 *fn_803970D8(u8 **h, s32 i);
u8 *fn_80397580(u8 **h, s32 i);
u8 *fn_803978A8(u8 **h, s32 i);
u8 *fn_80397E44(u8 **h, s32 i);
u8 *fn_803985AC(u8 **h, s32 i);
u8 *fn_803988E8(u8 **h, s32 i);
u8 *fn_80398BD8(u8 **h, s32 i);
u8 *fn_80398F30(u8 **h, s32 i);
u8 *fn_803994F0(u8 **h, s32 i);
u8 *fn_803997E4(u8 **h, s32 i);
u8 *fn_80399C24(u8 **h, s32 i);
u8 *fn_80399EE0(u8 **h, s32 i);

u8 *fn_8038F838(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u8 *fn_80390358(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u8 *fn_8039062C(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x12;
}

u8 *fn_803908E8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x8;
}

u8 *fn_80390BF8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x76;
}

u8 *fn_80391148(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x48;
}

u8 *fn_80391858(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x34;
}

u8 *fn_80392268(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x2a;
}

u8 *fn_8039252C(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x194;
}

u8 *fn_803927EC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x50;
}

u8 *fn_80392B04(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x18;
}

u8 *fn_80392FB4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x8;
}

u8 *fn_80393400(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x38;
}

u8 *fn_803938E4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x46;
}

u8 *fn_80393FEC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_80394270(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_803944F4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_80394778(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_803949FC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_80394C80(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x14;
}

u8 *fn_80394F04(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xa;
}

u8 *fn_803951C4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x3c;
}

u8 *fn_80395A54(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x6;
}

u8 *fn_80395DB0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x54;
}

u8 *fn_80396370(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u8 *fn_80396668(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u8 *fn_803969F8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u8 *fn_80396CCC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x20;
}

u8 *fn_803970D8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x2c;
}

u8 *fn_80397580(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x6;
}

u8 *fn_803978A8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u8 *fn_80397E44(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x5c;
}

u8 *fn_803985AC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x10;
}

u8 *fn_803988E8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u8 *fn_80398BD8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u8 *fn_80398F30(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xba;
}

u8 *fn_803994F0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x2c;
}

u8 *fn_803997E4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x20;
}

u8 *fn_80399C24(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u8 *fn_80399EE0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) return 0;
    if (i < 0) return 0;
    return *(u8 **)(p + 0x10) + i * 0x1c;
}

u16 fn_8038FAA4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_8038FCDC(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80390324(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803905F8(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803908B4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80390BC4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80391114(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803915EC(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80391824(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80392234(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803924F8(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803927B8(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80392AD0(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80395190(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80395A20(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80395D7C(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_8039633C(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80396634(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803969C4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80396C98(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803970A4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_8039754C(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80397874(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80397E10(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80398578(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803988B4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80398BA4(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80398EFC(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803994BC(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_803997B0(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80399BF0(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u16 fn_80399EAC(u8 **h) {
    u8 *p = *h;
    u32 r = 0;
    if (p != 0) {
        r = *(u16 *)(p + 0x2c);
        if (r != 0) {
            r--;
            *(u16 *)(p + 0x2c) = r;
        }
        *h = 0;
    }
    return r;
}

u32 fn_8038F86C(u8 **h, s32 i) {
    u8 *p = fn_8038F838(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u16 fn_8038FD44(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_8038FDAC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x9);
    return 0;
}

u8 fn_8038FDE0(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0xa);
    return 0;
}

u8 fn_8038FE14(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0xb);
    return 0;
}

u8 fn_8038FE48(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0xc);
    return 0;
}

u8 fn_8038FE7C(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0xd);
    return 0;
}

u32 fn_8038FEE8(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return (*(u16 *)(p + 0xe) >> 10) & 0x1;
    return 0;
}

u32 fn_8038FF20(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return (*(u16 *)(p + 0xe) >> 9) & 0x1;
    return 0;
}

u32 fn_8038FF58(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return (*(u16 *)(p + 0xe) >> 5) & 0xf;
    return 0;
}

u32 fn_8038FF90(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u16 *)(p + 0xe) & 0x1f;
    return 0;
}

u8 fn_8038FFC8(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x10);
    return 0;
}

u8 fn_8038FFFC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x11);
    return 0;
}

u8 fn_80390030(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x12);
    return 0;
}

u8 fn_80390064(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u8 *)(p + 0x13);
    return 0;
}

u16 fn_803900EC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u16 fn_8039038C(u8 **h, s32 i) {
    u8 *p = fn_80390358(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u16 fn_803903C0(u8 **h, s32 i) {
    u8 *p = fn_80390358(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u16 fn_8039091C(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) return *(u16 *)(p + 0x4);
    return 0;
}

u32 fn_80390950(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) return (*(u32 *)(p + 0x4) >> 1) & 0x7fff;
    return 0;
}

u32 fn_80390988(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) return *(u32 *)(p + 0x4) & 0x1;
    return 0;
}

u16 fn_80390C48(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_80390C7C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6a);
    return 0;
}

u8 fn_80390CB0(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6b);
    return 0;
}

u8 fn_80390CE4(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6c);
    return 0;
}

u8 fn_80390D18(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6d);
    return 0;
}

u8 fn_80390D4C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6e);
    return 0;
}

u8 fn_80390D80(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x6f);
    return 0;
}

u8 fn_80390DB4(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x70);
    return 0;
}

u8 fn_80390DE8(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x71);
    return 0;
}

u8 fn_80390E1C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x72);
    return 0;
}

u8 fn_80390E50(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x73);
    return 0;
}

u8 fn_80390EDC(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) return *(u8 *)(p + 0x74);
    return 0;
}

u16 fn_80391198(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u16 *)(p + 0x14);
    return 0;
}

u8 fn_803911CC(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u8 *)(p + 0x18);
    return 0;
}

u32 fn_80391200(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u32 *)(p + 0x0) >> 29;
    return 0;
}

u32 fn_80391238(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return (*(u32 *)(p + 0x0) >> 26) & 0x1;
    return 0;
}

u32 fn_80391318(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_8039134C(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_80391380(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

f32 fn_803913B4(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) return *(f32 *)(p + 0x10);
    return lbl_80642F08;
}

u8 fn_8039188C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x1e);
    return 0;
}

u8 fn_803918C0(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x1f);
    return 0;
}

u8 fn_803918F4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x20);
    return 0;
}

u8 fn_80391928(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x21);
    return 0;
}

u8 fn_8039195C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x22);
    return 0;
}

u8 fn_80391990(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x23);
    return 0;
}

u8 fn_803919C4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x24);
    return 0;
}

u8 fn_803919F8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x25);
    return 0;
}

u8 fn_80391A2C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x26);
    return 0;
}

u8 fn_80391A60(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x27);
    return 0;
}

u32 fn_80391A94(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 14) & 0x3;
    return 0;
}

u32 fn_80391ACC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 12) & 0x3;
    return 0;
}

u32 fn_80391B04(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 10) & 0x3;
    return 0;
}

u32 fn_80391B3C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 8) & 0x3;
    return 0;
}

u32 fn_80391B74(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 6) & 0x3;
    return 0;
}

u32 fn_80391BAC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u16 *)(p + 0x28) >> 4) & 0x3;
    return 0;
}

u16 fn_80391BE4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x10);
    return 0;
}

u16 fn_80391C18(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x12);
    return 0;
}

u8 fn_80391C4C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2a);
    return 0;
}

u8 fn_80391C80(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2b);
    return 0;
}

u8 fn_80391CB4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2c);
    return 0;
}

u8 fn_80391CE8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2d);
    return 0;
}

u8 fn_80391D1C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2e);
    return 0;
}

u8 fn_80391D50(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x2f);
    return 0;
}

u8 fn_80391D84(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x30);
    return 0;
}

u8 fn_80391DB8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x31);
    return 0;
}

u16 fn_80391DEC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x16);
    return 0;
}

u8 fn_80391E20(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x32);
    return 0;
}

u32 fn_80391E54(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return (*(u8 *)(p + 0x33) >> 1) & 0x7f;
    return 0;
}

u32 fn_80391E8C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u8 *)(p + 0x33) & 0x1;
    return 0;
}

u32 fn_80391EC4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_80391EF8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80391F2C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_80391F60(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u16 fn_80391F94(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x18);
    return 0;
}

u16 fn_80391FC8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x1a);
    return 0;
}

u16 fn_80391FFC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) return *(u16 *)(p + 0x1c);
    return 0;
}

u16 fn_80392B38(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_80392B6C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0xe);
    return 0;
}

u8 fn_80392BA0(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0xf);
    return 0;
}

u8 fn_80392BD4(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x10);
    return 0;
}

u8 fn_80392C08(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x11);
    return 0;
}

u8 fn_80392C3C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x12);
    return 0;
}

u8 fn_80392C70(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x13);
    return 0;
}

u16 fn_80392CA4(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u8 fn_80392CD8(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x14);
    return 0;
}

u8 fn_80392D0C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x15);
    return 0;
}

u16 fn_80392D40(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u16 *)(p + 0x8);
    return 0;
}

u16 fn_80392D74(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u16 *)(p + 0xa);
    return 0;
}

u16 fn_80392DA8(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u16 *)(p + 0xc);
    return 0;
}

u8 fn_80392DDC(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) return *(u8 *)(p + 0x16);
    return 0;
}

s16 fn_80392FE8(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) return *(s16 *)(p + 0x0);
    return 0;
}

s16 fn_8039301C(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) return *(s16 *)(p + 0x2);
    return 0;
}

u8 fn_80393050(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) return *(u8 *)(p + 0x4);
    return 0;
}

u8 fn_80393084(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) return *(u8 *)(p + 0x6);
    return 0;
}

u8 fn_80393434(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(u8 *)(p + 0x34);
    return 0;
}

f32 fn_80393468(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x0);
    return lbl_80642F10;
}

f32 fn_8039349C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x4);
    return lbl_80642F10;
}

u8 fn_803934D0(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(u8 *)(p + 0x35);
    return 0;
}

f32 fn_80393504(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x8);
    return lbl_80642F10;
}

f32 fn_80393538(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0xc);
    return lbl_80642F10;
}

f32 fn_8039356C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x10);
    return lbl_80642F10;
}

f32 fn_803935A0(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x14);
    return lbl_80642F10;
}

f32 fn_803935D4(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x18);
    return lbl_80642F10;
}

f32 fn_80393608(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x1c);
    return lbl_80642F10;
}

f32 fn_8039363C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x20);
    return lbl_80642F10;
}

f32 fn_80393670(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x24);
    return lbl_80642F10;
}

f32 fn_803936A4(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x28);
    return lbl_80642F10;
}

f32 fn_803936D8(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x2c);
    return lbl_80642F10;
}

f32 fn_8039370C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) return *(f32 *)(p + 0x30);
    return lbl_80642F10;
}

u8 fn_80393918(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x2a);
    return 0;
}

s16 fn_8039394C(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(s16 *)(p + 0x0);
    return 0;
}

u8 fn_80393980(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x2b);
    return 0;
}

u8 fn_803939B4(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x2c);
    return 0;
}

u8 fn_80393A40(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x2d);
    return 0;
}

u8 fn_80393B20(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x32);
    return 0;
}

u8 fn_80393C00(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x37);
    return 0;
}

u8 fn_80393CE0(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x3c);
    return 0;
}

u8 fn_80393DC0(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) return *(u8 *)(p + 0x41);
    return 0;
}

u32 fn_803951F8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x2e) >> 4) & 0xf;
    return 0;
}

u32 fn_80395230(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x2f) >> 5) & 0x7;
    return 0;
}

u32 fn_80395268(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x2f) >> 2) & 0x7;
    return 0;
}

u32 fn_803952A0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x30) >> 5) & 0x7;
    return 0;
}

u32 fn_803952D8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x30) >> 2) & 0x7;
    return 0;
}

u32 fn_80395310(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x31) >> 5) & 0x7;
    return 0;
}

u32 fn_80395348(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x31) >> 4) & 0x1;
    return 0;
}

u32 fn_80395380(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x31) >> 3) & 0x1;
    return 0;
}

u32 fn_803953B8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x32) >> 3) & 0x1f;
    return 0;
}

u32 fn_803953F0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x32) >> 2) & 0x1;
    return 0;
}

u32 fn_80395428(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_8039545C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80395490(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x33) >> 3) & 0x1f;
    return 0;
}

u32 fn_803954C8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_803954FC(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u32 fn_80395530(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x34) >> 3) & 0x1f;
    return 0;
}

u32 fn_80395568(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x10);
    return 0;
}

u32 fn_8039559C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x14);
    return 0;
}

u32 fn_803955D0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x35) >> 3) & 0x1f;
    return 0;
}

u32 fn_80395608(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x18);
    return 0;
}

u32 fn_8039563C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x1c);
    return 0;
}

u32 fn_80395670(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x36) >> 3) & 0x1f;
    return 0;
}

u32 fn_803956A8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x20);
    return 0;
}

u32 fn_803956DC(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u32 *)(p + 0x24);
    return 0;
}

u32 fn_80395710(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x37) >> 3) & 0x1f;
    return 0;
}

u32 fn_80395748(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return (*(u8 *)(p + 0x38) >> 3) & 0x1f;
    return 0;
}

u16 fn_80395780(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u16 *)(p + 0x28);
    return 0;
}

u16 fn_803957B4(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u16 *)(p + 0x2a);
    return 0;
}

u16 fn_803957E8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) return *(u16 *)(p + 0x2c);
    return 0;
}

u16 fn_80395AA4(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u16 fn_80395AD8(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u16 fn_80395B0C(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) return *(u16 *)(p + 0x4);
    return 0;
}

u32 fn_80395E00(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return *(u32 *)(p + 0x0) >> 31;
    return 0;
}

u32 fn_80395E38(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return (*(u32 *)(p + 0x0) >> 28) & 0x7;
    return 0;
}

u32 fn_80395E70(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80395EA4(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_80395ED8(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u32 fn_80395F0C(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) return *(u32 *)(p + 0x10);
    return 0;
}

u16 fn_803963A4(u8 **h, s32 i) {
    u8 *p = fn_80396370(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_803966B8(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) return *(u8 *)(p + 0x8);
    return 0;
}

u32 fn_803966EC(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_80396720(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u8 fn_8039678C(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) return *(u8 *)(p + 0x9);
    return 0;
}

u16 fn_80396A2C(u8 **h, s32 i) {
    u8 *p = fn_803969F8(h, i);
    if (p) return *(u16 *)(p + 0x4);
    return 0;
}

u16 fn_80396A60(u8 **h, s32 i) {
    u8 *p = fn_803969F8(h, i);
    if (p) return *(u16 *)(p + 0x6);
    return 0;
}

u32 fn_80396D00(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_80396D34(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80396D68(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_80396D9C(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u32 fn_80396DD0(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x10);
    return 0;
}

u32 fn_80396E04(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x14);
    return 0;
}

u32 fn_80396E38(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x18);
    return 0;
}

u32 fn_80396E6C(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) return *(u32 *)(p + 0x1c);
    return 0;
}

u32 fn_8039710C(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_80397140(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80397174(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_803971A8(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u32 fn_803971DC(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x10);
    return 0;
}

u32 fn_80397210(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x14);
    return 0;
}

u32 fn_80397244(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x18);
    return 0;
}

u8 fn_80397278(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u8 *)(p + 0x28);
    return 0;
}

f32 fn_803972AC(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(f32 *)(p + 0x1c);
    return lbl_80642F18;
}

f32 fn_803972E0(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(f32 *)(p + 0x20);
    return lbl_80642F18;
}

u32 fn_80397314(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) return *(u32 *)(p + 0x24);
    return 0;
}

u16 fn_803975B4(u8 **h, s32 i) {
    u8 *p = fn_80397580(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_8039763C(u8 **h, s32 i) {
    u8 *p = fn_80397580(h, i);
    if (p) return *(u8 *)(p + 0x5);
    return 0;
}

u16 fn_803978DC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u16 fn_80397910(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u16 fn_80397944(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0x4);
    return 0;
}

u16 fn_80397978(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0x6);
    return 0;
}

u16 fn_803979AC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0x8);
    return 0;
}

u16 fn_803979E0(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0xa);
    return 0;
}

u32 fn_80397A14(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 15) & 0x1;
    return 0;
}

u32 fn_80397A4C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 14) & 0x1;
    return 0;
}

u32 fn_80397A84(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 13) & 0x1;
    return 0;
}

u32 fn_80397ABC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 12) & 0x1;
    return 0;
}

u32 fn_80397AF4(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 11) & 0x1;
    return 0;
}

u32 fn_80397B2C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 10) & 0x1;
    return 0;
}

u32 fn_80397B64(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 9) & 0x1;
    return 0;
}

u32 fn_80397B9C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return (*(u16 *)(p + 0xc) >> 7) & 0x3;
    return 0;
}

u32 fn_80397BD4(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) return *(u16 *)(p + 0xc) & 0x7f;
    return 0;
}

u16 fn_80397E78(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u16 *)(p + 0x30);
    return 0;
}

u8 fn_80397EAC(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u8 *)(p + 0x4a);
    return 0;
}

u8 fn_80397FE0(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u8 *)(p + 0x4f);
    return 0;
}

u16 fn_80398068(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u16 *)(p + 0x3a);
    return 0;
}

u8 fn_8039809C(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u8 *)(p + 0x54);
    return 0;
}

u8 fn_80398284(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u8 *)(p + 0x55);
    return 0;
}

u8 fn_803982B8(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u8 *)(p + 0x56);
    return 0;
}

u16 fn_80398340(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) return *(u16 *)(p + 0x48);
    return 0;
}

u32 fn_803985E0(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_80398614(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80398648(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_8039867C(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u16 fn_80398938(u8 **h, s32 i) {
    u8 *p = fn_803988E8(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_8039896C(u8 **h, s32 i) {
    u8 *p = fn_803988E8(h, i);
    if (p) return *(u8 *)(p + 0x2);
    return 0;
}

u16 fn_80398C28(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u16 fn_80398C5C(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) return *(u16 *)(p + 0x4);
    return 0;
}

u16 fn_80398C90(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) return *(u16 *)(p + 0x6);
    return 0;
}

u16 fn_80398CC4(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) return *(u16 *)(p + 0x8);
    return 0;
}

u16 fn_80398F80(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) return *(u16 *)(p + 0x0);
    return 0;
}

u8 fn_80398FB4(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) return *(u8 *)(p + 0xb8);
    return 0;
}

u8 fn_80398FE8(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) return *(u8 *)(p + 0xb9);
    return 0;
}

u16 fn_8039901C(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) return *(u16 *)(p + 0x2);
    return 0;
}

u8 fn_80399578(u8 **h, s32 i) {
    u8 *p = fn_803994F0(h, i);
    if (p) return *(u8 *)(p + 0x2a);
    return 0;
}

u32 fn_80399818(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u32 fn_8039984C(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0x4);
    return 0;
}

u32 fn_80399880(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0x8);
    return 0;
}

u32 fn_803998B4(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0xc);
    return 0;
}

u32 fn_803998E8(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0x10);
    return 0;
}

u32 fn_8039991C(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u32 *)(p + 0x14);
    return 0;
}

u8 fn_80399950(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u8 *)(p + 0x1c);
    return 0;
}

u8 fn_80399984(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(u8 *)(p + 0x1d);
    return 0;
}

f32 fn_803999B8(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) return *(f32 *)(p + 0x18);
    return lbl_80642F20;
}

u8 fn_80399F30(u8 **h, s32 i) {
    u8 *p = fn_80399EE0(h, i);
    if (p) return *(u8 *)(p + 0x18);
    return 0;
}

}

struct DataHdr {
    u32 magic;
    u32 ver;
    u32 off8;
    u32 offC;
    u32 off10;
    u32 off14;
    u32 relocs;
    u32 nrelocs;
    u32 off20;
    u32 pad24;
    u32 pad28;
    u16 refcnt;
    u16 relocated;
};

static inline void RelocTbl(u32 *r, u32 n, u32 base) {
    while (n-- != 0) {
        u32 off = *r;
        r++;
        *(u32 *)(base + off) += base;
    }
}
static inline void RelocTbl2(u32 base, u32 *r, u32 n) {
    while (n-- != 0) {
        *(u32 *)(base + *r) += base;
        r++;
    }
}
static inline void RelocTbl3(u32 n, u32 *r, u32 base) {
    for (; n != 0; n--) {
        *(u32 *)(*r + base) += base;
        r++;
    }
}

extern "C" {

s32 fn_8038F6A0(DataHdr **h, DataHdr *d) {
    if (d == 0) return -1;
    if (*h != 0) return -2;
    if (d->ver != 4) return -3;
    if (d->relocated == 0) {
        d->off8 += (u32)d;
        d->off10 += (u32)d;
        d->relocs += (u32)d;
        u32 n = d->nrelocs;
        if (d->off20 != 0) d->off20 += (u32)d;
        u32 *r = (u32 *)d->relocs;
        while (n-- != 0) {
            *(u32 *)(*r + (u32)d) += (u32)d;
            r++;
        }
        d->relocated = 1;
    }
    *h = d;
    d->refcnt++;
    return 0;
}

DataHdr **fn_8038F600(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8038F6A0(h, d);
    return h;
}

DataHdr **fn_8038F640(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_8038F804((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

}
extern "C" {

s32 fn_8038F940(DataHdr **h, DataHdr *d);
s32 fn_8038FB78(DataHdr **h, DataHdr *d);
s32 fn_803901C0(DataHdr **h, DataHdr *d);
s32 fn_80390494(DataHdr **h, DataHdr *d);
s32 fn_80390750(DataHdr **h, DataHdr *d);
s32 fn_80390A60(DataHdr **h, DataHdr *d);
s32 fn_80390FB0(DataHdr **h, DataHdr *d);
s32 fn_80391488(DataHdr **h, DataHdr *d);
s32 fn_803916C0(DataHdr **h, DataHdr *d);
s32 fn_803920D0(DataHdr **h, DataHdr *d);
s32 fn_80392394(DataHdr **h, DataHdr *d);
s32 fn_80392654(DataHdr **h, DataHdr *d);
s32 fn_8039296C(DataHdr **h, DataHdr *d);
s32 fn_80392E50(DataHdr **h, DataHdr *d);
s32 fn_803930F8(DataHdr **h, DataHdr *d);
s32 fn_8039329C(DataHdr **h, DataHdr *d);
s32 fn_80393780(DataHdr **h, DataHdr *d);
s32 fn_80393E88(DataHdr **h, DataHdr *d);
s32 fn_8039410C(DataHdr **h, DataHdr *d);
s32 fn_80394390(DataHdr **h, DataHdr *d);
s32 fn_80394614(DataHdr **h, DataHdr *d);
s32 fn_80394898(DataHdr **h, DataHdr *d);
s32 fn_80394B1C(DataHdr **h, DataHdr *d);
s32 fn_80394DA0(DataHdr **h, DataHdr *d);
s32 fn_8039502C(DataHdr **h, DataHdr *d);
s32 fn_803958BC(DataHdr **h, DataHdr *d);
s32 fn_80395C18(DataHdr **h, DataHdr *d);
s32 fn_803961D8(DataHdr **h, DataHdr *d);
s32 fn_803964D0(DataHdr **h, DataHdr *d);
s32 fn_80396860(DataHdr **h, DataHdr *d);
s32 fn_80396B34(DataHdr **h, DataHdr *d);
s32 fn_80396F40(DataHdr **h, DataHdr *d);
s32 fn_803973E8(DataHdr **h, DataHdr *d);
s32 fn_80397710(DataHdr **h, DataHdr *d);
s32 fn_80397CAC(DataHdr **h, DataHdr *d);
s32 fn_80398414(DataHdr **h, DataHdr *d);
s32 fn_80398750(DataHdr **h, DataHdr *d);
s32 fn_80398A40(DataHdr **h, DataHdr *d);
s32 fn_80398D98(DataHdr **h, DataHdr *d);
s32 fn_80399358(DataHdr **h, DataHdr *d);
s32 fn_8039964C(DataHdr **h, DataHdr *d);
s32 fn_80399A8C(DataHdr **h, DataHdr *d);
s32 fn_80399D48(DataHdr **h, DataHdr *d);
u16 fn_8038FAA4(u8 **h);
u16 fn_8038FCDC(u8 **h);
u16 fn_80390324(u8 **h);
u16 fn_803905F8(u8 **h);
u16 fn_803908B4(u8 **h);
u16 fn_80390BC4(u8 **h);
u16 fn_80391114(u8 **h);
u16 fn_803915EC(u8 **h);
u16 fn_80391824(u8 **h);
u16 fn_80392234(u8 **h);
u16 fn_803924F8(u8 **h);
u16 fn_803927B8(u8 **h);
u16 fn_80392AD0(u8 **h);
u16 fn_80395190(u8 **h);
u16 fn_80395A20(u8 **h);
u16 fn_80395D7C(u8 **h);
u16 fn_8039633C(u8 **h);
u16 fn_80396634(u8 **h);
u16 fn_803969C4(u8 **h);
u16 fn_80396C98(u8 **h);
u16 fn_803970A4(u8 **h);
u16 fn_8039754C(u8 **h);
u16 fn_80397874(u8 **h);
u16 fn_80397E10(u8 **h);
u16 fn_80398578(u8 **h);
u16 fn_803988B4(u8 **h);
u16 fn_80398BA4(u8 **h);
u16 fn_80398EFC(u8 **h);
u16 fn_803994BC(u8 **h);
u16 fn_803997B0(u8 **h);
u16 fn_80399BF0(u8 **h);
u16 fn_80399EAC(u8 **h);
u8 *fn_8038FD10(u8 **h, s32 i);
u8 *fn_80390BF8(u8 **h, s32 i);
u8 *fn_80391148(u8 **h, s32 i);
u8 *fn_803927EC(u8 **h, s32 i);
u8 *fn_803938E4(u8 **h, s32 i);
u8 *fn_80393FEC(u8 **h, s32 i);
u8 *fn_80394270(u8 **h, s32 i);
u8 *fn_803944F4(u8 **h, s32 i);
u8 *fn_80394778(u8 **h, s32 i);
u8 *fn_803949FC(u8 **h, s32 i);
u8 *fn_80394C80(u8 **h, s32 i);
u8 *fn_80395DB0(u8 **h, s32 i);
u8 *fn_80396370(u8 **h, s32 i);
u8 *fn_80397580(u8 **h, s32 i);
u8 *fn_80397E44(u8 **h, s32 i);
u8 *fn_80398F30(u8 **h, s32 i);

DataHdr **fn_8038F8A0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8038F940(h, d);
    return h;
}

DataHdr **fn_8038F8E0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_8038FAA4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_8038FAD8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8038FB78(h, d);
    return h;
}

DataHdr **fn_8038FB18(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_8038FCDC((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u8 fn_80390098(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8038FD10(h, i);
    if (p == 0) return 0;
    if (j >= 0x14) return 0;
    return ((u8 *)(p + 0x14))[j];
}

DataHdr **fn_80390120(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803901C0(h, d);
    return h;
}

DataHdr **fn_80390160(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80390324((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803903F4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80390494(h, d);
    return h;
}

DataHdr **fn_80390434(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803905F8((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803906B0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80390750(h, d);
    return h;
}

DataHdr **fn_803906F0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803908B4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803909C0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80390A60(h, d);
    return h;
}

DataHdr **fn_80390A00(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80390BC4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80390C2C(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u16 fn_80390E84(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80390BF8(h, i);
    if (p == 0) return 0;
    if (j >= 0x34) return 0;
    return ((u16 *)(p + 0x2))[j];
}

DataHdr **fn_80390F10(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80390FB0(h, d);
    return h;
}

DataHdr **fn_80390F50(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80391114((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_8039117C(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u8 fn_80391270(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80391148(h, i);
    if (p == 0) return 0;
    if (j >= 0x19) return 0;
    return ((u8 *)(p + 0x19))[j];
}

u8 fn_803912C4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80391148(h, i);
    if (p == 0) return 0;
    if (j >= 0x16) return 0;
    return ((u8 *)(p + 0x32))[j];
}

DataHdr **fn_803913E8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80391488(h, d);
    return h;
}

DataHdr **fn_80391428(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803915EC((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80391620(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803916C0(h, d);
    return h;
}

DataHdr **fn_80391660(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80391824((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80392030(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803920D0(h, d);
    return h;
}

DataHdr **fn_80392070(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80392234((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803922F4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80392394(h, d);
    return h;
}

DataHdr **fn_80392334(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803924F8((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803925B4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80392654(h, d);
    return h;
}

DataHdr **fn_803925F4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803927B8((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u8 fn_80392820(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803927EC(h, i);
    if (p == 0) return 0;
    if (j >= 0x14) return 0;
    return *(u8 *)(p + j * 4 + 0x2);
}

DataHdr **fn_803928CC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8039296C(h, d);
    return h;
}

DataHdr **fn_8039290C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80392AD0((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80392E10(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80392E50(h, d);
    return h;
}

DataHdr **fn_803930B8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803930F8(h, d);
    return h;
}

DataHdr **fn_8039325C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8039329C(h, d);
    return h;
}

DataHdr **fn_80393740(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80393780(h, d);
    return h;
}

s16 fn_803939E8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((s16 *)(p + 0x2))[j];
}

u8 fn_80393A74(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x2e))[j];
}

s16 fn_80393AC8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((s16 *)(p + 0xa))[j];
}

u8 fn_80393B54(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x33))[j];
}

s16 fn_80393BA8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((s16 *)(p + 0x12))[j];
}

u8 fn_80393C34(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x38))[j];
}

s16 fn_80393C88(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((s16 *)(p + 0x1a))[j];
}

u8 fn_80393D14(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x3d))[j];
}

s16 fn_80393D68(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((s16 *)(p + 0x22))[j];
}

u8 fn_80393DF4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x42))[j];
}

DataHdr **fn_80393E48(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80393E88(h, d);
    return h;
}

s16 fn_80394074(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80393FEC(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_803940CC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8039410C(h, d);
    return h;
}

s16 fn_803942F8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394270(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394350(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80394390(h, d);
    return h;
}

s16 fn_8039457C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803944F4(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_803945D4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80394614(h, d);
    return h;
}

s16 fn_80394800(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394778(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394858(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80394898(h, d);
    return h;
}

s16 fn_80394A84(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803949FC(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394ADC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80394B1C(h, d);
    return h;
}

s16 fn_80394D08(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394C80(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394D60(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80394DA0(h, d);
    return h;
}

DataHdr **fn_80394F8C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8039502C(h, d);
    return h;
}

DataHdr **fn_80394FCC(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80395190((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_8039581C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803958BC(h, d);
    return h;
}

DataHdr **fn_8039585C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80395A20((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80395A88(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

DataHdr **fn_80395B78(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80395C18(h, d);
    return h;
}

DataHdr **fn_80395BB8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80395D7C((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80395DE4(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u8 fn_80395F40(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x14) return 0;
    return ((u8 *)(p + 0x14))[j];
}

u8 fn_80395F94(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x28))[j];
}

u8 fn_80395FE8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x8) return 0;
    return ((u8 *)(p + 0x2c))[j];
}

u8 fn_8039603C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x14) return 0;
    return ((u8 *)(p + 0x34))[j];
}

u8 fn_80396090(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u8 *)(p + 0x48))[j];
}

u8 fn_803960E4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) return 0;
    if (j >= 0x8) return 0;
    return ((u8 *)(p + 0x4c))[j];
}

DataHdr **fn_80396138(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803961D8(h, d);
    return h;
}

DataHdr **fn_80396178(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_8039633C((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u16 fn_803963D8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80396370(h, i);
    if (p == 0) return 0;
    if (j >= 0x6) return 0;
    return ((u16 *)(p + 0x2))[j];
}

DataHdr **fn_80396430(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803964D0(h, d);
    return h;
}

DataHdr **fn_80396470(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80396634((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_8039669C(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

DataHdr **fn_803967C0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80396860(h, d);
    return h;
}

DataHdr **fn_80396800(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803969C4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80396A94(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80396B34(h, d);
    return h;
}

DataHdr **fn_80396AD4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80396C98((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80396EA0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80396F40(h, d);
    return h;
}

DataHdr **fn_80396EE0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803970A4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80397348(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_803973E8(h, d);
    return h;
}

DataHdr **fn_80397388(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_8039754C((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u8 fn_803975E8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397580(h, i);
    if (p == 0) return 0;
    if (j >= 0x3) return 0;
    return ((u8 *)(p + 0x2))[j];
}

DataHdr **fn_80397670(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80397710(h, d);
    return h;
}

DataHdr **fn_803976B0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80397874((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80397C0C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80397CAC(h, d);
    return h;
}

DataHdr **fn_80397C4C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80397E10((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u8 fn_80397EE0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return ((u8 *)(p + 0x4b))[j];
}

u16 fn_80397F34(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return ((u16 *)(p + 0x36))[j];
}

u8 fn_80397F8C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return ((u8 *)(p + 0x4d))[j];
}

u8 fn_80398014(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x3) return 0;
    return ((u8 *)(p + 0x51))[j];
}

u8 fn_803980D0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u8 *)(p + j * 16 + 0xc);
}

u32 fn_8039817C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 16 + 0x4);
}

u32 fn_803981D4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 16 + 0x8);
}

u32 fn_8039822C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u32 *)(p + 0x20))[j];
}

u8 fn_803982EC(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return ((u8 *)(p + 0x57))[j];
}

DataHdr **fn_80398374(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80398414(h, d);
    return h;
}

DataHdr **fn_803983B4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80398578((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803986B0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80398750(h, d);
    return h;
}

DataHdr **fn_803986F0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803988B4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_8039891C(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

DataHdr **fn_803989A0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80398A40(h, d);
    return h;
}

DataHdr **fn_803989E0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80398BA4((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80398C0C(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

DataHdr **fn_80398CF8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80398D98(h, d);
    return h;
}

DataHdr **fn_80398D38(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80398EFC((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80398F64(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

u16 fn_80399050(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x10) return 0;
    return ((u16 *)(p + 0x8))[j];
}

u16 fn_803990A8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x10) return 0;
    return ((u16 *)(p + 0x28))[j];
}

u16 fn_80399100(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x10) return 0;
    return ((u16 *)(p + 0x48))[j];
}

u16 fn_80399158(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x10) return 0;
    return ((u16 *)(p + 0x68))[j];
}

u16 fn_803991B0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x10) return 0;
    return ((u16 *)(p + 0x88))[j];
}

u16 fn_80399208(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u16 *)(p + 0xa8))[j];
}

u16 fn_80399260(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) return 0;
    if (j >= 0x4) return 0;
    return ((u16 *)(p + 0xb0))[j];
}

DataHdr **fn_803992B8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80399358(h, d);
    return h;
}

DataHdr **fn_803992F8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803994BC((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803995AC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_8039964C(h, d);
    return h;
}

DataHdr **fn_803995EC(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_803997B0((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_803999EC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80399A8C(h, d);
    return h;
}

DataHdr **fn_80399A2C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80399BF0((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

DataHdr **fn_80399CA8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) fn_80399D48(h, d);
    return h;
}

DataHdr **fn_80399CE8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) fn_80399EAC((u8 **)h);
        if (del > 0) ::operator delete(h);
    }
    return h;
}

u32 fn_80399F14(u8 **h) {
    u8 *p = *h;
    if (p) return *(u32 *)(p + 0x0);
    return 0;
}

}
extern "C" {

void fn_803B2570(u32 a, u32 b, u32 c);
void fn_8016E0A0(u8 *p);
void fn_803DEF3C(u8 *p);
void fn_803AF5F0(u8 *a, u32 b, u32 c, void *d, u32 e);
void *fn_8016DF70(u32 a, u32 b);
u32 fn_803DEF00(void *f, void *a, u32 b);
u32 fn_803D6E6C(u8 *b);
u32 fn_803D803C(u8 *a, u8 *b, u32 c);
void fn_803A742C(u8 *a, u8 *b, u8 *c);
void fn_803A74B8(u8 *a, u8 *b, u8 *c);
void fn_803A7524(u8 *a, u8 *b, u8 *c);
void fn_803A75A0(u8 *a, u8 *b, u8 *c);
void fn_803A7628(u8 *a, u8 *b, u8 *c);
void fn_803A7694(u8 *a, u8 *b, u8 *c);
void fn_803A7708(u8 *a, u8 *b, u8 *c);
void fn_803A7774(u8 *a, u8 *b);
void fn_803A77E4(u8 *a, u8 *b, u8 *c);
void fn_803A7858(u8 *a, u8 *b, u8 *c);
void fn_803A78CC(u8 *a, u8 *b);
void fn_803A7AB8(u8 *a, u8 *b, u8 *c);
void fn_803A7B88(u8 *a, u8 *b, u8 *c);
void fn_803A7C9C(u8 *a, u8 *b, u8 *c);
void fn_803A7DC8(u8 *a, u8 *b, u8 *c);
void fn_803A7EAC(u8 *a, u8 *b, u8 *c);
void fn_803A7F44(u8 *a, u8 *b, u8 *c);
void fn_803A8010(u8 *a, u8 *b, u8 *c);
void fn_803A80A8(u8 *a, u8 *b, u8 *c);
void fn_803A82EC(u8 *a, u8 *b, u8 *c);
void fn_803A83B4(u8 *a, u8 *b, u8 *c);
void fn_803A8444(u8 *a, u8 *b, u8 *c);
void fn_803A84C0(u8 *a, u8 *b, u8 *c);
void fn_803A84CC(u8 *a, u8 *b);
void fn_803A853C(u8 *a, u8 *b, u8 *c);
void fn_803A85A8(u8 *a, u8 *b, u8 *c);
void fn_803A85B4(u8 *a, u8 *b, u8 *c);
void fn_803A8620(u8 *a, u8 *b, u8 *c);
void fn_803A87D0(u8 *a, u8 *b, u8 *c);
void fn_803A8980(u8 *a, u8 *b);
void fn_803A8B14(u8 *a, u8 *b, u8 *c);
void fn_803A9068(u8 *a, u8 *b);
void fn_803A90D0(u8 *a, u8 *b, u8 *c);
void fn_803A9264(u8 *a, u8 *b, u8 *c);
void fn_803A9270(u8 *a, u8 *b, u8 *c);
void fn_803A92F4(u8 *a, u8 *b, u8 *c);
void fn_803A9360(u8 *a, u8 *b, u8 *c);
void fn_803A93CC(u8 *a, u8 *b, u8 *c);
void fn_803A9510(u8 *a, u8 *b);
void fn_803A951C(u8 *a, u8 *b, u8 *c);
void fn_803A9528(u8 *a, u8 *b);
void fn_803A9590(u8 *a, u8 *b);
void fn_803A95A4(u8 *a, u8 *b);
void fn_803A975C(u8 *a, u8 *b, u8 *c);
void fn_803A989C(u8 *a, u8 *b);
void fn_803A99A0(u8 *a, u8 *b, u8 *c);
void fn_803A99AC(u8 *a, u8 *b, u8 *c);
void fn_803A99B8(u8 *a, u8 *b, u8 *c);
void fn_803A9B14(u8 *a, u8 *b);
void fn_803A9BBC(u8 *a, u8 *b);
void fn_803AB018(u8 *a, u8 *b);
void fn_803AB0C0(u8 *a, u8 *b);
void fn_803AB1D4(u8 *a, u8 *b);
void fn_803AB228(u8 *a, u8 *b);
void fn_803AB27C(u8 *a, u8 *b);
void fn_803B1764(u8 *a, u8 *b, u32 c);
void fn_803B1798(u8 *a, u8 *b, u32 c);
void fn_803B2118(u8 *a, u8 *b, u32 c);
void fn_803B236C(u8 *a, u8 *b, u32 c);
void fn_803B2440(u8 *a, u8 *b, u32 c);
void fn_803BD39C(u8 *a, u8 *b, u32 c);
void fn_803BD3C4(u8 *a, u8 *b, u32 c);

s16 fn_80394020(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80393FEC(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_803942A4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394270(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_80394528(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803944F4(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_803947AC(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394778(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_80394A30(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803949FC(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_80394CB4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394C80(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

s16 fn_80394F38(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394F04(h, i);
    if (p == 0) return 0;
    if (j >= 0x5) return 0;
    return ((s16 *)p)[j];
}

void fn_803A61FC(u8 *a, u8 *b) {
    fn_803A742C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6234(u8 *a, u8 *b) {
    fn_803A74B8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A626C(u8 *a, u8 *b) {
    fn_803A7524(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A62A4(u8 *a, u8 *b) {
    fn_803A75A0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A62DC(u8 *a, u8 *b) {
    fn_803A7628(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6368(u8 *a, u8 *b) {
    fn_803A7694(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A63A0(u8 *a, u8 *b) {
    fn_803A7708(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A63D8(u8 *a, u8 *b) {
    fn_803A7774(a, b);
    b[0x84] = 0;
}

void fn_803A640C(u8 *a, u8 *b) {
    fn_803A77E4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6444(u8 *a, u8 *b) {
    fn_803A7858(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A647C(u8 *a, u8 *b) {
    fn_803A78CC(a, b);
    b[0x84] = 0;
}

void fn_803A6508(u8 *a, u8 *b) {
    fn_803A7AB8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6540(u8 *a, u8 *b) {
    fn_803A7B88(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6578(u8 *a, u8 *b) {
    fn_803A7C9C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A65B0(u8 *a, u8 *b) {
    fn_803A7DC8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A65E8(u8 *a, u8 *b) {
    fn_803A7EAC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6620(u8 *a, u8 *b) {
    fn_803A7F44(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6658(u8 *a, u8 *b) {
    fn_803A8010(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6690(u8 *a, u8 *b) {
    fn_803A80A8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6738(u8 *a, u8 *b) {
    fn_803A82EC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6770(u8 *a, u8 *b) {
    fn_803A83B4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A67A8(u8 *a, u8 *b) {
    fn_803A8444(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A67E0(u8 *a, u8 *b) {
    fn_803A84C0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6818(u8 *a, u8 *b) {
    fn_803A84CC(a, b);
    b[0x84] = 0;
}

void fn_803A684C(u8 *a, u8 *b) {
    fn_803A853C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6884(u8 *a, u8 *b) {
    fn_803A85A8(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A68BC(u8 *a, u8 *b) {
    fn_803A85B4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A68F4(u8 *a, u8 *b) {
    fn_803A8620(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A692C(u8 *a, u8 *b) {
    fn_803A87D0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6964(u8 *a, u8 *b) {
    fn_803A8980(a, b);
    b[0x84] = 0;
}

void fn_803A6998(u8 *a, u8 *b) {
    fn_803A8B14(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A69D0(u8 *a, u8 *b) {
    fn_803A9068(a, b);
    b[0x84] = 0;
}

void fn_803A6A04(u8 *a, u8 *b) {
    fn_803A90D0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6A3C(u8 *a, u8 *b) {
    fn_803A9264(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6D0C(u8 *a, u8 *b) {
    fn_803A9270(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6D44(u8 *a, u8 *b) {
    fn_803A92F4(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6E30(u8 *a, u8 *b) {
    fn_803A9360(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A6E68(u8 *a, u8 *b) {
    fn_803A93CC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A703C(u8 *a, u8 *b) {
    fn_803A9510(a, b);
    b[0x84] = 0;
}

void fn_803A7070(u8 *a, u8 *b) {
    fn_803A951C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A70A8(u8 *a, u8 *b) {
    fn_803A9528(a, b);
    b[0x84] = 0;
}

void fn_803A70DC(u8 *a, u8 *b) {
    fn_803A9590(a, b);
    b[0x84] = 0;
}

void fn_803A7110(u8 *a, u8 *b) {
    fn_803A95A4(a, b);
    b[0x84] = 0;
}

void fn_803A7144(u8 *a, u8 *b) {
    fn_803A975C(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A717C(u8 *a, u8 *b) {
    fn_803A989C(a, b);
    b[0x84] = 0;
}

void fn_803A71B0(u8 *a, u8 *b) {
    fn_803A99A0(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A71E8(u8 *a, u8 *b) {
    fn_803A99AC(a, b, b + 0x84);
    b[0x84] = 0;
}

void fn_803A7220(u8 *a, u8 *b) {
    fn_803A99B8(a, b, b + 0x84);
    b[0x84] = 0;
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A7628(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((void *)fn_803A9B14, m, 0);
}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A7708(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x1c);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((void *)fn_803A9BBC, m, 0);
}
#pragma pop

void fn_803A84C0(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A853C(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x68);
    *(u8 **)m = a;
    m[0x60] = c[0];
    m[0x61] = b[0x184];
    fn_803DEF00((void *)fn_803AB018, m, 0);
}
#pragma pop

void fn_803A85A8(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A85B4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x8);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((void *)fn_803AB0C0, m, 0);
}
#pragma pop

void fn_803A9264(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A92F4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x8] = c[0];
    m[0x9] = b[0x184];
    fn_803DEF00((void *)fn_803AB1D4, m, 0);
}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A9360(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((void *)fn_803AB228, m, 0);
}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A93CC(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((void *)fn_803AB27C, m, 0);
}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A9438(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((void *)fn_803AB228, m, 0);
}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A94A4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0x4] = c[0];
    m[0x5] = b[0x184];
    fn_803DEF00((void *)fn_803AB27C, m, 0);
}
#pragma pop

void fn_803A951C(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99A0(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99AC(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99B8(u8 *a, u8 *b, u8 *c) {
    fn_803B2570((u32)a, b[0x184], c[0]);
}

void fn_803A99C4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9A18(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9A6C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x89], b[0x88]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9AC0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9B14(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9B68(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x11], b[0x10]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9BBC(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9C10(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803A9C64(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AADCC(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AAE20(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x69], b[0x68]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AAF70(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x65], b[0x64]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AAFC4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB018(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x61], b[0x60]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB06C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB0C0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB1D4(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x9], b[0x8]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB228(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB27C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0x5], b[0x4]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB2D0(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AB324(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[0xd], b[0xc]);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}

void fn_803AF748(u8 *a, u32 b) {
    u32 v = 0x1000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803AFEB4(u8 *a, u32 b) {
    u32 v = 0x7000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803AFFAC(u8 *a, u32 b) {
    u32 v = 0xa000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B01CC(u8 *a, u32 b) {
    u32 v = 0xd000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1058(u8 *a, u32 b) {
    u32 v = 0x17000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1820(u8 *a, u32 b) {
    u32 v = 0x24000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1908(u8 *a, u32 b) {
    u32 v = 0x1000000;
    fn_803AF5F0(a, 0x0, b, &v, 4);
}

void fn_803B1BF0(u8 *a, u32 b) {
    u32 v = 0x28000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1C28(u8 *a, u32 b) {
    u32 v = 0x29000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1E18(u8 *a, u32 b) {
    u32 v = 0x2e000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B1E50(u8 *a, u32 b) {
    u32 v = 0x2f000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B21EC(u8 *a, u32 b) {
    u32 v = 0x39000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

void fn_803B2224(u8 *a, u32 b) {
    u32 v = 0x3a000000;
    fn_803AF5F0(a, 0x1, b, &v, 4);
}

s32 fn_803CDCB0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803BD39C(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CDD1C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803BD3C4(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CE648(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1764(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803CE6B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1798(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D5D84(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2118(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D6A14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B236C(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

s32 fn_803D6A80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2440(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}

}

extern "C" {

extern u8 *lbl_8063E80C;
extern const f32 lbl_80642FC4;
void fn_803A3078(u8 *p);
s32 fn_803BAA4C(u8 *p);
void fn_803A2E70(u8 *p, u32 a);
void fn_803A5F58(u8 *p, u32 a);
u32 fn_803A60BC(u8 *p, u32 a);
void fn_803AB190(u8 *a, u8 *b);
void fn_803D990C(u8 *p);
void *MEMAllocFromAllocator(void *a, u32 size);
void MEMFreeToAllocator(void *a, void *p);
void OSCancelAlarm(void *a);

void fn_8039A3F4(void) { fn_803A3078(lbl_806405A0); }
void fn_803A5D64(u8 *p) { OSCancelAlarm(p + 0x1a0); }
void fn_803D6B70(u8 *a, u8 *b) { fn_803BAA4C(b); }
void *fn_8039A068(u32 size) { return MEMAllocFromAllocator(lbl_8063E80C, size); }
void fn_8039A074(void *p) { MEMFreeToAllocator(lbl_8063E80C, p); }
void fn_8039A3E8(u32 a) { fn_803A2E70(lbl_806405A0, a); }
u8 fn_803A3D34(u8 *p, s32 i) { return p[i + 4]; }
void fn_803A3D6C(u8 *p, s32 i, u8 v) { p[i + 4] = v; }
u8 fn_803A4C6C(u8 *p) { return p[0xb7] & 1; }
void fn_803A9510(u8 *a, u8 *b) { fn_803B2570((u32)a, b[0x184], 0x37); }
void fn_803ADE60(u8 *p, u32 a) { fn_803D97E4(*(u8 **)(p + 0x60), (u16)a); }
void fn_803A53F4(u8 *p) {
    f32 f = lbl_80642FC4;
    *(f32 *)(p + 0x8) = f;
    *(f32 *)(p + 0xc) = f;
}
void fn_803A5404(u8 *p) { fn_803A5F58(*(u8 **)(p + 0x24), *(u32 *)p); }
void fn_803A5514(u8 *p) {
    p[0x42] = 0;
    p[0x43] = 0;
}
void fn_803A575C(u8 *p) { fn_803A60BC(*(u8 **)(p + 0x24), *(u32 *)p); }
u32 fn_803AC850(u8 *p, s32 i) { return *(u32 *)(p + i * 4 + 0x34); }
u8 fn_803ACCD4(u8 *p, s32 i) { return fn_803AB514(*(u8 **)(p + i * 4 + 0x34)); }
u8 *fn_803ADCC8(u8 *p, s32 i) { return fn_803AB524(*(u8 **)(p + i * 4 + 0x34)); }
struct BF_3_2_3 { u8 a : 3; u8 b : 2; u8 c : 3; };
void fn_803ADCE8(u8 *p, u32 v) { ((BF_3_2_3 *)(p + 0x23c3))->b = v; }
void fn_803BAC68(u8 *p) { (*(u32 *)(p + 0x3148))++; }
u8 fn_803C5A34(u8 *p, s32 i) { return p[i * 0x100 + 0x2300]; }
u8 *fn_803C90D0(u8 *p, s32 i) { return p + i * 0xc0 + 0x2d40; }
u8 *fn_803C90E8(u8 *p, u8 i) { return p + i * 8 + 0x1c4; }
u8 *fn_803C90F8(u8 *p, s32 i) { return p + i * 0xc0 + 0x2dc8; }
u8 *fn_803D915C(u8 *p, s32 i) { if (i == 0xff) p = *(u8 **)(p + 0x130); return p; }
u8 *fn_803D916C(u8 *p, s32 i) { if (i == 0xff) p = *(u8 **)(p + 0x130); return p; }
u8 *fn_803D91D4(u8 *p, s32 i) { if (i == 0xff) p = *(u8 **)(p + 0x130); return p; }
u8 *fn_803D91E4(u8 *p, s32 i) { if (i == 0xff) p = *(u8 **)(p + 0x130); return p; }
void fn_803A53E0(u8 *p) {
    *(u32 *)(p + 0x10) = 0;
    *(u32 *)(p + 0x14) = 0;
    *(u32 *)(p + 0x18) = 0;
}
void fn_803A7418(void) { fn_803DEF00((void *)fn_803AB190, 0, 0); }
void fn_803A9590(u8 *a, u8 *b) { fn_803DEF00((void *)fn_803AB324, a, 0); }
void fn_803B0D58(u8 *a, u32 b, void *c) { fn_803AF5F0(a, 0, b, c, 4); }
void fn_803B9734(u8 *a, u8 *b) {
    *(u32 *)(b + 0x8) = 0x2a;
    b[0x311f] = 1;
}
void fn_803BC450(u8 *p, u32 i) { *(u32 *)(p + ((i << 1) & 4) + 0xa4) = 0; }
u32 fn_803BF32C(u8 *p, s32 i) { return i | (p[i + 0x219c] << 8); }
void fn_803BA9D4(u8 *p, u32 a, u32 b) {
    *(u32 *)(p + 0xac) = a;
    *(u32 *)(p + 0xb0) = b;
    *(u32 *)(p + 0xb4) = 0;
    fn_803D990C(p + 0x2700);
}

}

struct VObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(u8 *a);
};
extern "C" {

extern u8 lbl_80472EF0[];
extern u8 lbl_806405B0[4];
extern u32 lbl_806405A8;
extern u8 lbl_80405AC1[];
struct U8Pair { u8 a; u8 b; };
extern U8Pair lbl_80405402[];
extern u16 lbl_80405ACE[];
extern void (*lbl_80405048[])(u8 *, u8 *);
extern s32 (*lbl_804056D8[])(u8 *, u8 *);
void fn_803BB744(u8 *p, u32 a, u32 b);
void fn_803A57D4(void *p);
void *OSGetAlarmUserData(void *a);
void fn_803B1AC4(u8 *a, u8 *b, s32 c);

void fn_803A36B8(u8 *p) {
    *(u32 *)(p + 0x20) = 0;
    *(u8 **)(p + 0x0) = lbl_80472EF0;
    *(u32 *)(p + 0x24) = 0;
}
void fn_803A58C8(s32 *p) {
    s32 i = *p;
    if (i < 4) lbl_806405B0[i] = 0;
}
u32 fn_803A6070(u8 *p, s32 i) { return *(u32 *)(p + i * 0x68 + 0x50) != 0; }
u32 fn_803A60BC(u8 *p, u32 i) { return *(u8 *)(p + i * 0x68 + 0x62) != 0; }
s32 fn_803ACD14(u8 *p) {
    s32 v = *(s32 *)(p + 0x23c4);
    if (v > 12 || v < 0) return 12;
    return v;
}
void fn_803BB728(u8 *p, s32 i, u32 a, u32 b) { fn_803BB744(p + i * 0xc0 + 0x2d40, a, b); }
s32 fn_803C3DD8(u8 *p, s32 i) { return *(u32 *)(p + i * 16 + 0x21a8) == 0x27; }
s32 fn_8039A3C8(void) {
    u8 *p = lbl_806405A0;
    if (*(s32 *)(p + 0x10) != 0x12) return -1;
    return *(s32 *)(p + 0xb0);
}
void fn_803A37FC(u8 *p) {
    f32 f;
    if (*(s32 *)(p + 0x18) == 1) f = *(f32 *)(p + 4);
    else f = *(f32 *)(p + 8);
    *(f32 *)(p + 0xc) = f;
}
void fn_803A3D44(u8 *p) {
    VObj *o = *(VObj **)(p + 4);
    if (o) o->v00();
}
void fn_803A44C0(u8 *o, u8 *b) {
    u8 *q = *(u8 **)(b + 0x10);
    lbl_806405A8 = 0;
    ((VObj *)o)->v18(q + 0x10);
}
void fn_803A5888(s32 i, s32 a) {
    if (a == 0 && i < 4) lbl_806405B0[i] = 1;
}
u8 fn_803A58A8(s32 *p) {
    s32 i = *p;
    if (i >= 4) return 0;
    return lbl_806405B0[i];
}
void fn_803B0F68(u8 *a, u8 *b, u8 *c) {
    c[0] = 0x15;
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), c, 0x24);
}
void fn_803C04A4(u8 *a, u8 *b) {
    *(u32 *)(b + 0x216c) = 0;
    *(u32 *)(b + 0x2150) = 1;
    *(u32 *)(b + 0x213c) &= ~0x100000;
}
s32 fn_803CC1C8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x178) == 0) (*(u32 *)(b + 0xb4))++;
    return 0;
}
s32 fn_803CC6E8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x178) == 0) (*(u32 *)(b + 0xb4))++;
    return 0;
}
u8 fn_803D4EE8(u32 i) {
    if (i > 12) return 0;
    return lbl_80405AC1[i];
}
u32 fn_803D6E6C(u8 *p) {
    u32 i = *(u32 *)(p + 0xb4);
    u32 r = *(u32 *)(p + i * 4 + 0x2700);
    *(u32 *)(p + 0xb4) = i + 1;
    return r;
}
void fn_8039DE00(void *a, void *b) { fn_803A57D4(OSGetAlarmUserData(a)); }
s32 fn_803C0B68(s32 a, s32 b) {
    s32 s;
    if (a == 0) return a;
    s = 1;
    if (a < 0) s = -1;
    a = a / b;
    if (a == 0) return s;
    return a;
}
u32 fn_803C5A44(u8 *p, s32 i) {
    u32 r = 0;
    if (*(u32 *)(p + i * 0x1c + 0x2e8) & 8) r = 1;
    return r;
}
u32 fn_803C6154(u8 i, u32 v) { return v * lbl_80405402[i].a / lbl_80405402[i].b; }
u16 fn_803D5004(u32 i) {
    if (i > 12) return 0;
    return lbl_80405ACE[(u8)i];
}
u8 *fn_803D90A0(u8 *p, s32 i) {
    switch (i) {
    case 1: p = *(u8 **)(p + 0x3044); break;
    case 0xff: p = *(u8 **)(p + 0x124); break;
    }
    return p;
}
void fn_803a6138(u8 *a, u8 *b) {
    u8 i = b[0x84];
    if (i) lbl_80405048[i](a, b);
}
void fn_803BD374(u8 *a, u8 *b, s32 c) {
    if (*(u16 *)(b + c * 0xc0 + 0x2db8) == 0) *(u16 *)(b + (u8)c * 2 + 0x394) = 0;
    fn_803B1AC4(a, b, c);
}
void fn_803BD39C(u8 *a, u8 *b, u32 c) {
    *(u32 *)(b + c * 0xc0 + 0x2db0) |= 0x1000;
    *(u32 *)(b + c * 4 + 0x304c) = *(u32 *)(b + 0x3044);
}
u32 fn_803C9158(void) { return *(u32 *)((u8 *)fn_803AC848((u8 *)fn_803AC828()) + 0x180); }
s32 fn_803C94CC(u8 *a, u8 *b) { return lbl_804056D8[*(u32 *)(b + *(u32 *)(b + 0xb4) * 4 + 0x2700)](a, b); }

}
extern "C" {

void fn_803B1420(u8 *a);
void fn_803B2008(u8 *a);
void fn_803B2040(u8 *a);
void fn_803B225C(u8 *a);
void fn_803B2294(u8 *a, u8 *b);
void fn_803B2334(u8 *a);

void fn_803B1420(u8 *a) {
    u32 v = 0x1c000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2008(u8 *a) {
    u32 v = 0x34000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2040(u8 *a) {
    u32 v = 0x35000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B225C(u8 *a) {
    u32 v = 0x3b000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2334(u8 *a) {
    u32 v = 0x3d000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

void fn_803B2538(u8 *a) {
    u32 v = 0x42000000;
    fn_803AF5F0(a, 1, 0, &v, 4);
}

s32 fn_803C94F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803AF748(a, 0);
    return 0;
}

s32 fn_803CBE50(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1420(a);
    return 0;
}

s32 fn_803CC1E8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    return 0;
}

s32 fn_803D59BC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1E18(a, 0);
    return 0;
}

s32 fn_803D5C98(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2008(a);
    return 0;
}

s32 fn_803D5CC8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2040(a);
    return 0;
}

s32 fn_803D6540(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B225C(a);
    return 0;
}

s32 fn_803D6570(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2294(a, b);
    return 0;
}

s32 fn_803D65A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B2334(a);
    return 0;
}

s32 fn_803D6BE0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    return 0;
}

}

struct VObj2 {
    virtual void v00();
    virtual void v01(u8 *a);
};

extern "C" {

extern const char *lbl_8063E808;
extern u8 lbl_8063CEC8[];
extern u8 *lbl_806405B8;
void OSRegisterVersion(const char *v);
void fn_8039B474(u8 *p);
void fn_803A357C(u8 *p);
void MEMDestroyFrmHeap(void *h);
u8 *fn_80362AEC(u8 *p, u16 x);
s32 fn_803B9BF0(u8 *p, u32 a, u32 b, u32 c);
void WPADControlMotor(s32 ch, u32 cmd);
s32 WPADControlSpeaker(s32 ch, u32 cmd, void *cb);
void fn_803A5D9C(s32 a, s32 b);
void fn_803A5E90(s32 a, s32 b);

void fn_8039A22C(void) {
    OSRegisterVersion(lbl_8063E808);
    fn_8039B474(lbl_806405A0);
}
void fn_803A3EA4(u8 *p) {
    p[0x18] = 0;
    p[0x4] = 0;
    p[0x5] = 0;
    p[0x6] = 0;
    p[0x7] = 0;
    p[0x8] = 0;
    p[0x9] = 0;
    p[0xa] = 0;
    p[0xb] = 0;
}
u32 fn_803A3F9C(u8 *p, u32 x) { return *(u32 *)(fn_80362AEC(p + 8, (u16)x) + 4); }
void fn_803A4D68(u8 *p, VObj2 *o) {
    *(VObj2 **)(p + 4) = o;
    if (o) o->v01(p);
}
void fn_803B8CD8(u8 *a, u8 *b) {
    if (*(u32 *)(b + 0x213c) & 0x0f000000) fn_803B9BF0(b, 0x21, 0x21, 0);
    else *(u32 *)(b + 8) = 0x22;
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803BAC78(u8 *p, s32 i) {
    for (s32 j = 0; j < 0x100; j++) p[i * 0x100 + j + 0x2300] = 0;
}
#pragma pop
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803C90A4(u8 *p, u8 i) {
    for (s32 j = 0; j < 4; j++) *(u16 *)(p + i * 8 + j * 2 + 0x370) = 0;
}
#pragma pop
s32 fn_803D4C24(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x08000000;
    return 0;
}
void fn_8039DEEC(s32 a, s32 b) {
    if (a == 1) lbl_806405A0[0x8a] = 1;
    void (*fp)(s32, s32) = *(void (**)(s32, s32))(lbl_806405A0 + 0x1bc);
    if (fp) fp(a, b);
}
void fn_803A4174(u8 *p, u32 m, f32 *v) {
    if (m & *(u32 *)(p + 0x1c)) {
        *(f32 *)(p + 0xc) = v[0];
        *(f32 *)(p + 0x10) = v[1];
        *(f32 *)(p + 0x14) = v[2];
        p[0x18] = 1;
    }
}
void fn_803A57D4(void *pv) {
    u8 *p = (u8 *)pv;
    s32 ch = *(s32 *)p;
    if (ch < 4 && p[0x1c]) {
        p[0x1c] = 0;
        WPADControlMotor(ch, 0);
    }
}
void fn_803A5B48(void) {
    u8 *p = lbl_806405B8;
    *(s32 *)(p + 0x58) = -1;
    *(u32 *)(p + 0x50) = 0;
    *(s32 *)(p + 0xc0) = -1;
    *(u32 *)(p + 0xb8) = 0;
    *(s32 *)(p + 0x128) = -1;
    *(u32 *)(p + 0x120) = 0;
    *(s32 *)(p + 0x190) = -1;
    *(u32 *)(p + 0x188) = 0;
}
void fn_803A5D6C(void *a, void *b) { WPADControlSpeaker((s32)OSGetAlarmUserData(a), 1, (void *)fn_803A5D9C); }
void fn_803A5E60(void *a, void *b) { WPADControlSpeaker((s32)OSGetAlarmUserData(a), 4, (void *)fn_803A5E90); }
u32 fn_803A608C(u8 *p, s32 i, s32 v) {
    u8 *q = p + i * 0x68;
    if (*(u32 *)(q + 0x50) != 0 && v == *(s32 *)(q + 0x58)) return 1;
    return 0;
}
u32 fn_803ACCE4(u8 *p, s32 i) { return fn_803AB514(*(u8 **)(p + i * 4 + 0x34)) & 1; }
void fn_8039A4EC(void) {
    fn_803A357C(lbl_806405A0);
    MEMDestroyFrmHeap(*(void **)(lbl_8063CEC8 + 4));
}
struct S8 { u8 a, b, c, d; s16 e; u16 f; };
void fn_803A7C68(S8 *d, S8 *s) { *d = *s; }
void fn_803B1764(u8 *a, u8 *b, u32 c) {
    u32 v = 0x22000000;
    fn_803AF5F0(a, 1, c, &v, 4);
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
s32 fn_803BE72C(u8 *p, u32 v) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (v == *(u16 *)(p + i * 2 + 0xc)) break;
    }
    return i;
}
#pragma pop

}

extern "C" {

extern u16 lbl_80473AB4[];

void fn_80395B40(u8 **h, s32 i, u16 v) {
    u8 *p = fn_80395A54(h, i);
    if (p) *(u16 *)(p + 4) = v;
}
void fn_80396754(u8 **h, s32 i, u32 v) {
    u8 *p = fn_80396668(h, i);
    if (p) *(u32 *)(p + 4) = v;
}
void fn_803A37C4(u8 *p, s32 m, f32 a, f32 b, f32 c) {
    *(s32 *)(p + 0x18) = m;
    *(f32 *)(p + 0x4) = a;
    *(f32 *)(p + 0x8) = b;
    *(f32 *)(p + 0x10) = c;
    *(u32 *)(p + 0x14) = 0;
    p[0x1c] = 0;
    *(f32 *)(p + 0xc) = (m == 1) ? (f64)a : (f64)b;
}
void fn_803B2CD4(u8 *p) {
    fn_8016E0A0(*(u8 **)(p + 0x2120));
    fn_8016E0A0(p);
}
u32 fn_803BFA40(u8 *p, s32 i) { return (u8)Item_IsMail(*(u16 *)(p + i * 0xc0 + 0x2db8)) == 0; }
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
s32 fn_803C06A4(u8 *a, u8 *b, s32 c) {
    s32 i;
    for (i = 0; i < 4; i++) {
        if (*(u16 *)(b + c * 0xc0 + i * 2 + 0x2d4c) == 0) return i;
    }
    return i;
}
u32 fn_803C06DC(u32 v) {
    for (u8 i = 0; i < 12; i++) {
        if (v == lbl_80473AB4[i]) return 1;
    }
    return 0;
}
void fn_803C9490(u8 *p, u16 *s) {
    if (p == 0) return;
    if (s == 0) {
    } else {
        for (s32 i = 0; i < 11; i++) {
            *(u16 *)(p + i * 2 + 0x36) = *s++;
        }
    }
}
#pragma pop
u32 fn_803C877C(u8 *p, u16 a, u32 b) { return ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), a), b); }
u8 *fn_803C9458(u8 *p, s32 i) { return (u8 *)fn_803AC848(p) + i * 6 + 0x312c; }
s32 fn_803D3DA8(u8 *a, u8 *b) {
    u32 idx = *(u32 *)(b + 0x6c);
    u8 *q;
    (*(u32 *)(b + 0xb4))++;
    q = b + idx * 0xc0;
    *(u32 *)(b + 0x2154) = *(u32 *)(q + 0x2d8c) * 0x78 / *(u32 *)(q + 0x2d90) + 1;
    return 0;
}
void fn_803D8004(u8 *a, u8 *b) {
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}
void fn_803A6BA4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}
void fn_803A6D7C(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}
void fn_803A7000(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}
void fn_803A6DB8(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x2e);
    b[0x84] = 0;
}
void fn_803A6DF4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x2f);
    b[0x84] = 0;
}
void fn_803A6F88(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x34);
    b[0x84] = 0;
}
void fn_803A6FC4(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x35);
    b[0x84] = 0;
}
void fn_803A73DC(u8 *a, u8 *b) {
    fn_803B2570((u32)a, b[0x184], 0x42);
    b[0x84] = 0;
}
struct Msg4 { u8 cmd; u8 a; u16 b; };
struct Msg4b { u8 cmd; u8 a; u8 b; u8 c; };
void fn_803B1570(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x1e;
    m.a = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803B15AC(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x1f;
    m.a = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803B24A8(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = 0x40;
    m.b = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803B13E0(u8 *a, u32 x, u32 c, u32 b) {
    Msg4 m;
    m.cmd = 0x1b;
    m.b = c;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803B1D18(u8 *a, u32 b, u32 c, u32 d) {
    Msg4b m;
    m.cmd = 0x2c;
    m.a = c;
    m.b = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803B2078(u8 *a, u32 b, u32 c, u32 d) {
    Msg4 m;
    m.cmd = 0x36;
    m.a = c;
    m.b = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}
void fn_803BD3C4(u8 *a, u8 *b, u32 c) {
    u8 *q = b + c * 0xc0;
    *(u32 *)(q + 0x2db0) &= ~0x1000;
    *(u32 *)(q + 0x2db0) &= ~0x300;
    *(u32 *)(q + 0x2dc0) &= 0xdffbff3f;
    *(u32 *)(q + 0x2dc8) &= ~0x1f800;
}
void fn_803C421C(u8 *p, s32 i) { ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(p + i * 0xc0 + 0x2db8)), 8); }
u32 fn_803C59F8(u8 *p, s32 i) {
    u32 r = 1;
    u32 v = *(u32 *)(p + i * 0xc0 + 0x2db0);
    if ((v & 0x400000) || (v & 0xc00) || (v & 0x70) || (v & 0x1000)) r = 0;
    return r;
}
u8 *fn_8039B238(u8 *p, s32 del) {
    if (p && del > 0) ::operator delete(p);
    return p;
}
u8 *fn_803A36D4(u8 *p, s32 del) {
    if (p && del > 0) ::operator delete(p);
    return p;
}
u8 *fn_803A4440(u8 *p, s32 del) {
    if (p && del > 0) ::operator delete(p);
    return p;
}
u8 *fn_803A4480(u8 *p, s32 del) {
    if (p && del > 0) ::operator delete(p);
    return p;
}
void fn_803AB190(u8 *a, u8 *b) {
    if (b) fn_8016E0A0(b);
    fn_803DEF3C(a);
}
u16 fn_803BF340(u8 *p, s32 i) {
    u16 r = 0;
    u8 *q = p + i * 16;
    if (*(u32 *)(q + 0x21b4) == 1) {
        s32 k = *(s32 *)(q + 0x21b0);
        if (k != 0) r = *(u16 *)(p + i * 0xc0 + k * 2 + 0x2d4a);
    }
    return r;
}
bool fn_803C9180(u32 m) { return (m & *(u32 *)((u8 *)fn_803AC848((u8 *)fn_803AC828()) + 0x180)) != 0; }

}

extern "C" {

extern u16 lbl_80405398[];
extern u16 lbl_8040543A[];
extern u8 lbl_8048CE28[];
extern u16 lbl_804732E8[];
extern u16 lbl_804053A4[];
extern u8 lbl_80643000[5];
void fn_8039BD7C(u8 *p, u32 a);
u16 fn_803C3D6C(u8 *p, s32 i);
u32 fn_803C8C48(u32 a, u32 b, u32 c, u32 d);
void fn_803CACF0(u8 *a, u8 *b);
u32 fn_803DD920(u32 a);
void fn_803B24E4(u8 *a);

s32 fn_8039A258(u32 a) {
    fn_8039BD7C(lbl_806405A0, a);
    u8 *p = lbl_806405A0;
    if (*(s32 *)(p + 0x10) != 0x12) return -1;
    return *(s32 *)(p + 0xb0);
}
void fn_803B6A64(u8 *a, u8 *b) {
    if (fn_803C94CC(a, b) == 1) {
        *(u32 *)(b + 0xb4) = 0;
        *(u32 *)(b + 0x8) = *(u32 *)(b + 0xc);
    }
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
u32 fn_803C0584(u8 *a, u8 *b, u32 c, s32 v) {
    u32 r = 0;
    if ((*(u32 *)(b + 0x180) & 0x7000) == 0) return r;
    for (s32 i = 0; i < 6; i++) {
        if (v == lbl_80405398[i]) return 1;
    }
    return r;
}
u32 fn_803C05C8(u8 *a, u8 *b, s32 c, s32 v) {
    if (((*(u32 *)(b + c * 0xc0 + 0x2dcc) >> 13) & 7) == 0) return 0;
    for (s32 i = 0; i < 14; i++) {
        if (v == lbl_804053A4[i]) return 1;
    }
    return 0;
}
#pragma pop
u32 fn_803C40BC(u8 *p, s32 i) { return ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)), 1); }
u32 fn_803C4194(u8 *p, s32 i) { return ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)), 0xb); }
u32 fn_803C41D8(u8 *p, s32 i) { return ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), fn_803C3D6C(p, i)), 0xc); }
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
s32 fn_803C8688(u32 v) {
    s32 i = 0;
    while (lbl_8040543A[i] != 0xffff) {
        if (v == lbl_8040543A[i]) break;
        i++;
    }
    return lbl_8040543A[i] == 0xffff;
}
#pragma pop
s32 fn_803CB100(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B0F68(a, b, b + 0xf4);
    *(u32 *)(lbl_8048CE28 + 4) = 10;
    return 0;
}
void fn_803a6160(u8 *a, u8 *b, s32 c) {
    if (c != 2) fn_803D9808(b + 0x28);
    fn_803D9850(b);
    fn_8016E0A0(b);
}
static inline u32 bswap32(u32 x) {
    u32 v = (x << 8) & 0xff0000;
    v |= x << 24;
    v |= (x >> 8) & 0xff00;
    v |= x >> 24;
    return v;
}
void fn_803B07B4(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}
void fn_803B08DC(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}
void fn_803B0AB8(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}
void fn_803B0E4C(u8 *a, u32 b, u32 x) {
    u32 v = bswap32(x);
    fn_803AF5F0(a, 0, b, &v, 4);
}
void fn_803B1C60(u8 *a, u8 *b, u32 c, u16 d) {
    Msg4 m;
    m.cmd = 0x2a;
    m.b = d;
    m.a = b[c * 0xc0 + 0x2d67];
    fn_803AF5F0(a, 1, c, &m, 4);
}
void fn_803B2DE0(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0);
    *(u32 *)(b + 8) = 0x15;
    *(u32 *)(b + 0xc) = 2;
}
void fn_803B7E98(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 1);
    *(u32 *)(b + 8) = 0x15;
    *(u32 *)(b + 0xc) = 0x1b;
}
u8 fn_803C9110(void) {
    u32 x = fn_803AC828();
    return fn_803C8C48(x, fn_803AC848((u8 *)x), 3, 0);
}
u8 fn_803C93C4(u8 *p, u8 i, s32 j) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 4;
    return q[j + 0x314c];
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
s32 fn_803CAF20(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803CACF0(a, b);
    *(s32 *)(b + 0x2144) *= -1;
    return 0;
}
#pragma pop
s32 fn_803CBACC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803D6E6C(b);
    *(u32 *)(b + 0xf0) = 0;
    return 0;
}
s32 fn_803CBED0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803BA9D4(b, 0x1f, *(u16 *)(b + *(u32 *)(b + 0x3044) * 16 + 0x3de));
    return 0;
}
void fn_803ADC64(u8 *p, s32 i, u32 v) { p[i + 0x23dc] |= fn_803DD920(v); }
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
u16 fn_803AF3F0(u32 v) {
    for (s32 i = 0; lbl_804732E8[i] != 0; i += 2) {
        if (v == lbl_804732E8[i]) return lbl_804732E8[i + 1];
    }
}
#pragma pop
void fn_803B96E8(u8 *a, u8 *b) {
    if (fn_803B9BF0(b, *(u32 *)(b + 8), *(u32 *)(b + 8), 1) != 1) *(u32 *)(b + 8) = 0x27;
}
s32 fn_803BA074(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0x10);
    *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
    *(u32 *)(b + 8) = 0x15;
    return 1;
}
u32 fn_803BF8E4(u32 v) {
    if (v == 0 || v == 0xd6 || v == 0x17f || v == 0x112 || v == 0x17e || (u16)(v - 0xffff0076 + 0x10000 - 0x10000) <= 1) return 1;
    return 0;
}
u32 fn_803C4258(u8 *p, s32 i) {
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) return 0;
    ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(q + 0x2db8)), 9);
}
u32 fn_803C42A4(u8 *p, s32 i) {
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) return 0;
    ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), *(u16 *)(q + 0x2db8)), 10);
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803C9378(u8 *p, u8 i, s32 j, u8 v) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 4;
    q[j + 0x314c] = v;
}
#pragma pop
u8 *fn_803C940C(u8 *p, u32 x, s32 i, s32 j) {
    u8 *q = (u8 *)fn_803AC848(p) + i * 0x1b0;
    return q + j * 0x48 + 0x315c;
}
s32 fn_803CD978(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D3D5C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 k = *(u32 *)(b + 0x64);
    u8 v = b[k * 0xc0 + *(u16 *)(b + k * 2 + 0x30bc) + 0x2d6c];
    if (v > 4) v = 4;
    *(u32 *)(b + 0x2154) = lbl_80643000[v];
    return 0;
}
s32 fn_803D5470(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (fn_803AC840(a) & 4) fn_803B24E4(a);
    return 0;
}

}
extern "C" {



u8 fn_80390660(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8039062C(h, i);
    if (p == 0) return 0;
    if (j >= 0x12) return 0;
    return *(u8 *)(p + j * 1 + 0x0);
}

u16 fn_8039229C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80392268(h, i);
    if (p == 0) return 0;
    if (j >= 0x7) return 0;
    return *(u16 *)(p + j * 6 + 0x4);
}

u32 fn_80392560(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8039252C(h, i);
    if (p == 0) return 0;
    if (j >= 0x65) return 0;
    return *(u32 *)(p + j * 4 + 0x0);
}

u16 fn_80392878(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803927EC(h, i);
    if (p == 0) return 0;
    if (j >= 0x14) return 0;
    return *(u16 *)(p + j * 4 + 0x0);
}

u32 fn_80398128(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 16 + 0x0);
}

u16 fn_80399524(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803994F0(h, i);
    if (p == 0) return 0;
    if (j >= 0x15) return 0;
    return *(u16 *)(p + j * 2 + 0x0);
}

u8 fn_80399C58(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399C24(h, i);
    if (p == 0) return 0;
    if (j >= 0xe) return 0;
    return *(u8 *)(p + j * 1 + 0x0);
}

u32 fn_80399F64(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 12 + 0x0);
}

u32 fn_80399FB8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 12 + 0x4);
}

u32 fn_8039A010(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) return 0;
    if (j >= 0x2) return 0;
    return *(u32 *)(p + j * 12 + 0x8);
}

}

extern "C" {

extern u32 lbl_80405AE8[];
extern u16 lbl_80405470[];
extern u16 lbl_8040547C[];
void fn_803BA9EC(u8 *p, u32 a, u32 b);
s32 fn_803BABF0(u8 *p);
void fn_803A7940(u8 *a, u8 *b, u8 *c);
void *fn_803E018C(u32 a, u16 b);
void fn_803DFD28(u32 a, u32 b, void *s);
void Strbuf_Free(void *s);
u32 fn_803BE8B0(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f, u32 g, u8 *h);
void WPADSetConnectCallback(s32 ch, void *cb);
void WPADSetExtensionCallback(s32 ch, void *cb);

void fn_803A61AC(u8 *a, u8 *b) {
    fn_803A7418();
    fn_803B2570((u32)a, b[0x184], 1);
    b[0x84] = 0;
}
struct Inner18 { u32 w[6]; };
struct Rec24 { u8 a; u8 b; u16 c; Inner18 d; u32 e; u32 f; };
void fn_803ADEF0(Rec24 *d, Rec24 *s) {
    d->a = s->a;
    d->b = s->b;
    d->c = s->c;
    d->d = s->d;
    d->e = s->e;
    d->f = s->f;
}
void fn_803B16B4(u8 *a, u8 *b, u32 c, u8 d) {
    Msg4 m;
    m.cmd = 0x20;
    m.a = d;
    s16 mx = *(s16 *)(b + 0x3122);
    m.b = (mx - *(s32 *)(b + 0x2e4c)) * 100 / mx;
    fn_803AF5F0(a, 1, c, &m, 4);
}
s32 fn_803CBE80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803BA9D4(b, 2, fn_803D6E6C(b));
    return 0;
}
s32 fn_803CD9C4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803BA9EC(b, 2, fn_803D6E6C(b));
    return 0;
}
s32 fn_803D5028(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x124) = lbl_80405ACE[fn_803ACD14(a)];
    return 0;
}
s32 fn_803D5078(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x2174) = lbl_80405AE8[fn_803ACD14(a)];
    return 0;
}
void fn_803A5208(s32 *p) {
    WPADSetConnectCallback(*p, *(void **)(p + 10));
    *(void **)(p + 10) = 0;
    WPADSetExtensionCallback(*p, *(void **)(p + 11));
    *(void **)(p + 11) = 0;
}
void fn_803A6314(u8 *a, u8 *b) {
    fn_803D9804(*(u32 *)(b + 0x20));
    fn_803B2570((u32)a, b[0x184], 7);
    b[0x84] = 0;
}
void fn_803A9CB8(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C(a);
}
void fn_803A9D0C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C(a);
}
void fn_803AAEC8(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C(a);
}
void fn_803AAF1C(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)(b + 0xc), b[0x18], b[0x40]);
    *(u32 *)(b + 0x10) = 0;
    fn_803DEF3C(a);
}
void fn_803AAE74(u8 *a, u8 *b) {
    fn_803B2570(*(u32 *)b, b[8], 0x17);
    fn_8016E0A0(b);
    fn_803DEF3C(a);
}
void fn_803AFEEC(u8 *p, u32 i) {
    Msg4 m;
    m.cmd = 8;
    m.b = p[i * 0x2c + 0xad];
    m.a = p[i + 0xa8];
    fn_803AF5F0(p, 1, i, &m, 4);
}
void fn_803B0F14(u8 *a, u8 *b) {
    Msg4 m;
    m.cmd = 0x14;
    m.a = b[*(u32 *)(b + 0x64) + 0x219c];
    m.b = *(u32 *)(b + 0x3044);
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), &m, 4);
}
struct Msg8 { u8 cmd; u32 v; };
void fn_803B24E4(u8 *a) {
    Msg8 m;
    m.cmd = 0x41;
    m.v = fn_803ADCD8(a);
    fn_803AF5F0(a, 1, 0, &m, 8);
}
s32 fn_803CAC9C(u8 *a, u8 *b) {
    if (fn_803BABF0(b)) (*(u32 *)(b + 0xb4))++;
    else fn_803BAC68(b);
    return 0;
}
s32 fn_803D3B28(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(s32 *)(b + 0x2154) = *(u32 *)(b + *(u32 *)(b + 0x6c) * 4 + 0x21f0) * 25 / *(u32 *)(b + *(u32 *)(b + 0x64) * 4 + 0x21f0) + 1;
    if (*(s32 *)(b + 0x2154) > 150) *(s32 *)(b + 0x2154) = 150;
    return 0;
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A64B0(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    fn_803ADCC0(a, b[0xad]);
    fn_803A7940(a, b, c);
    b[0x84] = 0;
}
u32 fn_803C86CC(u8 *p, u16 x) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (*(u16 *)(p + x * 16 + 0x3de) == *(u16 *)(p + lbl_80405470[i] * 16 + 0x3de)) break;
    }
    return i == 6;
}
u32 fn_803C8724(u8 *p, u16 x) {
    s32 i;
    for (i = 0; i < 6; i++) {
        if (*(u16 *)(p + x * 16 + 0x3de) == *(u16 *)(p + lbl_8040547C[i] * 16 + 0x3de)) break;
    }
    return i == 6;
}
#pragma pop
void fn_803AF334(u8 *p, u32 a, u8 *c) {
    void *s = fn_803E018C(a, *(u16 *)(c + 2));
    fn_803DFD28(*(u32 *)(p + 0x14), *(u32 *)(p + 0x18), s);
    Strbuf_Free(s);
}
void fn_803B2570(u32 a, u32 b, u32 c) {
    Msg4 m;
    m.cmd = c;
    m.a = fn_803D9848(a, b);
    fn_803AF5F0((u8 *)a, 2, b, &m, 4);
}
void fn_803B621C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0xe5);
    *(u32 *)(b + 0x64) = 0;
    *(u32 *)(b + 0x6c) = 1;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x27;
}
s32 fn_803D37FC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x2144) = fn_803BE8B0(a, b, *(u32 *)(b + 0x3044), *(u32 *)(b + 0x2160), *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), *(u32 *)(b + 0x2144), b + 0x216c);
    return 0;
}
u32 fn_803D917C(u8 *a, u8 *b, s32 c) {
    u32 r;
    switch (c) {
    case 0xff:
        return *(u32 *)(b + 0x12c);
    default:
        r = fn_803D803C(a, b, c);
        u8 *q = b + (u8)r;
        return q[0x390] = b[r * 0xc0 + 0x2d67];
    }
}

}

extern "C" {

void fn_803B6334(u8 *a, u8 *b, u32 c, u32 d, u32 e);
void fn_803B67D4(u8 *a, u8 *b, u32 c, u32 d, u32 e);
u32 fn_803DEAC4(u8 *p, u32 a);
void *memset(void *p, int c, unsigned long n);
void fn_803B2784(u8 *a, u32 b, void *c, u32 d, u8 *e);
void fn_803ADF40(u8 *a, u8 *b, u32 c);
void fn_803AE378(u8 *a, u8 *b, u8 *c, u32 d);
void fn_803B25C8(u8 *a, u8 *b, void *c, u32 d, u32 e, u32 f, u32 g, u32 h);
s32 fn_803BC520(u8 *a, u8 *b, u32 *c);
void fn_803D8444(u8 *b, void *c);
void fn_803D8520(u8 *a, u8 *b, void *c, u8 *d);

void fn_803A6BE0(u8 *a, u8 *b) {
    fn_803D980C(b + 0x28);
    fn_803D9850(b);
    fn_803B2570((u32)a, b[0x184], b[0x84]);
    b[0x84] = 0;
}
struct Msg8b { u8 cmd; u8 a; u16 b; u32 c; };
void fn_803AFFE4(u8 *p, u32 i, u32 v) {
    Msg8b m;
    m.cmd = 0xb;
    m.b = p[i * 0x2c + 0xad];
    m.a = p[i + 0xa8];
    m.c = v;
    fn_803AF5F0(p, 1, i, &m, 8);
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803B2D0C(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    fn_803B6334(a, b, c, d, e);
    fn_803B67D4(a, b, c, d, e);
}
#pragma pop
s32 fn_803D3018(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(u32 *)(b + 0x2154) == 0) {
        u8 *q = b + *(u32 *)(b + 0x64) * 0xc0;
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * *(u32 *)(q + 0x2d8c) / *(u32 *)(q + 0x2d90);
        if (*(u32 *)(b + 0x2154) == 0) *(u32 *)(b + 0x2154) = 1;
    }
    return 0;
}
s32 fn_803D3D00(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(u32 *)(b + *(u32 *)(b + 0x6c) * 16 + 0x21a8) == 0x27) {
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * 2;
    } else {
        *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
    }
    return 0;
}
s32 fn_803D583C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 v = fn_803D6E6C(b);
    *(u32 *)(b + 0x134) = fn_803DEAC4(b + *(u32 *)(b + 0x3044) * 16 + 0x3de, v);
    return 0;
}
u32 fn_803A54B4(s32 *p, s32 v) {
    if (fn_803A6070(*(u8 **)(p + 9), *p) == 0) return 0;
    return fn_803A608C(*(u8 **)(p + 9), *p, v);
}
u8 *fn_803A60D8(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x194);
    memset(m, 0, 0x194);
    m[0x184] = b[0];
    m[0x185] = b[1];
    return m;
}
void fn_803A828C(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xc);
    *(u8 **)m = a;
    m[8] = b[0x184];
    fn_803DEF00((void *)fn_803AAE74, m, 0);
}
void fn_803B1704(u8 *a, u8 *b, u32 c, u8 d) {
    Msg4 m;
    m.a = d;
    m.cmd = 0x21;
    u32 v = *(u32 *)(b + 0x2e4c);
    if (v == 0) m.b = 1000;
    else m.b = v * 1000 / *(u32 *)(b + 0x2e50);
    fn_803AF5F0(a, 1, c, &m, 4);
}
void fn_803B1E88(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x30, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}
void fn_803B1EE8(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x31, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}
void fn_803B1F48(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x32, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}
void fn_803B1FA8(u8 *a, u32 b) {
    u8 m[8];
    fn_803B2784(a, *(u32 *)(a + 0x30), m, 0x33, (u8 *)b);
    fn_803AF5F0(a, 1, b, m, 8);
}
void fn_803B20B8(u8 *a, u32 b) {
    u32 v = 0x37000000;
    if (fn_803AC840(a) & 4) fn_803AF5F0(a, 1, b, &v, 4);
}
void fn_803B6104(u8 *a, u8 *b) {
    *(u32 *)(b + 0x64) = b[*(u32 *)(b + 0xec) + 0x21e8];
    fn_803BA9D4(b, 2, 3);
    *(u32 *)(b + 0xb4) = 0;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x2a;
}
void fn_803BA9EC(u8 *p, u32 a, u32 b) {
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xbc) = *(u32 *)(p + 0xac);
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xcc) = *(u32 *)(p + 0xb0);
    *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xdc) = *(u32 *)(p + 0xb4);
    (*(u32 *)(p + 0xb8))++;
    *(u32 *)(p + 0xac) = a;
    *(u32 *)(p + 0xb0) = b;
    *(u32 *)(p + 0xb4) = 0;
    fn_803D990C(p + 0x2700);
}
struct BF_2700 { u32 pad0 : 20; u32 sel : 1; u32 who : 2; u32 rest : 9; };
s32 fn_803D25D4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u8 *q = b + (u8)fn_803ACCE4(a, *(u32 *)(b + 0x64)) * 8;
    ((BF_2700 *)(q + 0x1c4))->sel = 1;
    ((BF_2700 *)(q + 0x1c4))->who = *(u32 *)(b + 0x64);
    return 0;
}
void fn_803A5770(s32 *p) {
    if (*p < 4 && fn_803A6070(*(u8 **)(p + 9), *p) == 0 && ((u8 *)p)[0x44] != 0) {
        ((u8 *)p)[0x1c] = 1;
        WPADControlMotor(*p, 1);
    }
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803AF38C(u8 *a, u8 *b, u8 *c) {
    fn_803ADF40(a, b, 1);
    fn_803AE378(a, b, c, 1);
    fn_803AF334(a, (u32)c, b);
}
#pragma pop
void fn_803B1650(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 1, e, c, d, 0);
    fn_803AF5F0(a, 1, c, m, 0x58);
}
void fn_803B7D48(u8 *a, u8 *b) {
    u32 v;
    if (fn_803BC520(a, b, &v) == 1) {
        fn_803BA9D4(b, 2, v);
        *(u32 *)(b + 8) = 0x15;
        *(u32 *)(b + 0xc) = 0x19;
    } else {
        *(u32 *)(b + 8) = 0x19;
    }
}
struct BF_344 { u32 b0 : 1; u32 b1 : 1; u32 b2 : 1; u32 b3 : 1; u32 b4 : 1; u32 b5 : 1; u32 b6 : 1; u32 b7 : 1; u32 b8 : 1; u32 rest : 23; };
u32 fn_803BF1C4(u8 *p, s32 i) {
    BF_344 *f = (BF_344 *)(p + i * 4 + 0x344);
    if (f->b0 || f->b1 || f->b2 || f->b3 || f->b4 || f->b5 || f->b6 || f->b8 || f->b7) return 1;
    return 0;
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
s32 fn_803C8448(u8 *p, s32 v) {
    if (v != 0) {
        v *= 100 - (s32)DS_Rand() % 16;
        v /= 100;
        if (v == 0) v = 1;
    }
    return v;
}
#pragma pop
s32 fn_803CB144(u8 *a, u8 *b) {
    u8 buf[0x20];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, b + 0xf4);
    return 0;
}
s32 fn_803D43A8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (((*(u32 *)(b + *(u32 *)(b + 0x6c) * 64 + 0x1d4) >> 29) & 1) == 0) *(u32 *)(b + 0xb4) += n;
    return 0;
}
u32 fn_803D903C(u8 *a, u8 *b, s32 c) {
    u32 r = fn_803D803C(a, b, c);
    if (c == 0x16) return r | (b[r + 0x21a0] << 8);
    return r | (b[r + 0x219c] << 8);
}

}

struct VObj3 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
};
extern "C" {

u32 fn_803ACD38(u8 *a, s32 b);
u8 fn_803BFB18(u8 *a, s32 b);
u32 fn_803ACBCC(u8 *a, u32 b);
void fn_803DA100(u8 *a, u32 b);
u32 *fn_803D6E8C(u8 *a, u8 *b, u32 c);
void fn_803B0E94(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f, u32 g);
void fn_803B0D6C(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f);
u32 fn_803C1B4C(u8 *a, u8 *b, u32 c);
s32 WPADIsSpeakerEnabled(s32 ch);
extern u8 *lbl_8063D070[];

void fn_803A3E3C(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v01();
    }
}
void fn_803A41A4(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v02();
    }
}
void fn_803A420C(u8 *p) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj3 **)(fn_80362AEC(p + 8, i) + 4))->v04();
    }
}
void fn_803A9068(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xc);
    *(u8 **)m = a;
    m[8] = b[0x84];
    m[9] = b[0x184];
    fn_803DEF00((void *)fn_803AB06C, m, 0);
}
void fn_803A9528(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    *(u8 **)m = a;
    m[0xc] = b[0x84];
    m[0xd] = b[0x184];
    fn_803DEF00((void *)fn_803AB2D0, m, 0);
}
void fn_803A7774(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = b[0x84];
    m[9] = b[0x184];
    fn_803DEF00((void *)fn_803A9C10, m, 0);
}
void fn_803A84CC(u8 *a, u8 *b) {
    u8 *m = (u8 *)fn_8016DF70(5, 8);
    m[6] = 0;
    *(u8 **)m = a;
    m[4] = b[0x84];
    m[5] = b[0x184];
    fn_803DEF00((void *)fn_803AAFC4, m, 0);
}
#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
void fn_803A74B8(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xa4);
    m[0x88] = c[0];
    m[0x89] = b[0x184];
    *(u8 **)m = a;
    fn_803DEF00((void *)fn_803A9A18, m, 0);
}
#pragma pop
void fn_803B0F88(u8 *a, u8 *b, u32 c) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 0, 0, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), c);
    fn_803AF5F0(a, 1, *(u32 *)(b + 0x64), m, 0x58);
}
void fn_803B0FF0(u8 *a, u8 *b, u32 c, u32 d, u32 e) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 0, 0, d, e, c);
    fn_803AF5F0(a, 1, d, m, 0x58);
}
void fn_803B15E8(u8 *a, u8 *b, u32 c, u32 d) {
    u8 m[0x58];
    fn_803B25C8(a, b, m, 1, d, c, c, 0);
    fn_803AF5F0(a, 1, c, m, 0x58);
}
void fn_803B2440(u8 *a, u8 *b, u32 c) {
    Msg4 m;
    m.cmd = 0x3f;
    u32 f = *(u32 *)(b + 0x216c);
    if (f & 2) m.a = 2;
    else if (f & 4) m.a = 1;
    else m.a = 0;
    fn_803AF5F0(a, 1, c, &m, 4);
}
s32 fn_803C9F44(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803AFEB4(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
s32 fn_803D5AF8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1E88(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
s32 fn_803D5B60(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1EE8(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
s32 fn_803D5BC8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1F48(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
s32 fn_803D5C30(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B1FA8(a, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
s32 fn_803D6B78(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(lbl_8048CE28 + 0xc) = fn_803D803C(a, b, fn_803D6E6C(b));
    return 0;
}
s32 fn_803CE720(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B15AC(a, fn_803D803C(a, b, fn_803D6E6C(b)), *(u32 *)(b + 0x130));
    return 0;
}
s32 fn_803D6930(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u32 *)(b + 0x6c) = fn_803C1B4C(a, b, fn_803D803C(a, b, fn_803D6E6C(b)));
    return 0;
}
#pragma push
#pragma optimize_for_size on
s32 fn_803CAEB8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0x2144) = 1;
    } else {
        fn_803CACF0(a, b);
        *(s32 *)(b + 0x2144) = fn_803C8448(b, *(s32 *)(b + 0x2144)) * -1;
    }
    return 0;
}
#pragma pop
s32 fn_803CC0D8(u8 *a, u8 *b) {
    fn_803AC840(a);
    fn_803AC850(a, *(u32 *)(b + 0x74));
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0xb4) += n;
    return 0;
}
void fn_803A4FC0(void *al, void *ctx) {
    u8 *p = lbl_8063D070[(s32)OSGetAlarmUserData(al)];
    s32 ch = *(s32 *)p;
    if (WPADIsSpeakerEnabled(ch)) WPADControlSpeaker(ch, 3, 0);
    p[0x41] = 0;
}
s32 fn_803D1150(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 *r = fn_803D6E8C(a, b, fn_803D6E6C(b));
    *r = b[*(u32 *)(b + 0x3104) + 0x21ec];
    return 0;
}
s32 fn_803D5280(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B0E94(a, b, 0, 0, fn_803D6E6C(b), 0, 0);
    return 0;
}
s32 fn_803D5380(u8 *a, u8 *b) {
    fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    fn_803B0D6C(a, b, 0, 0, 0, 6);
    *(u32 *)(b + 0x78) = 0;
    return 0;
}
void fn_803A66C8(u8 *a, u8 *b) {
    if (fn_803D97FC(*(u32 *)(b + 0x20), 2) == 1) fn_803B2570((u32)a, b[0x184], 0x17);
    else fn_803A828C(a, b);
    b[0x84] = 0;
}
s32 fn_803BAA4C(u8 *p) {
    if (*(u32 *)(p + 0xb8) != 0) {
        (*(u32 *)(p + 0xb8))--;
        fn_803BA9D4(p, *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xbc), *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xcc));
        *(u32 *)(p + 0xb4) = *(u32 *)(p + *(u32 *)(p + 0xb8) * 4 + 0xdc);
        return 0;
    }
    return 1;
}
s32 fn_803CDA14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 *r = fn_803D6E8C(a, b, fn_803D6E6C(b));
    fn_803BA9EC(b, 2, *r);
    return 0;
}
s32 fn_803D2E38(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    if (*(u32 *)(q + 0x2dc0) & 0x1800) *(u32 *)(b + 0xb4) += n;
    else *(u32 *)(q + 0x2dc0) |= 0x1000;
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

extern u8 lbl_80405168[];
extern U8Pair lbl_80405A50[];
extern u8 lbl_8063CED8[];
u32 fn_803DA0D0(u8 *p);
u8 fn_803DC804(u8 *p);
u32 fn_803DA0F8(u8 *p);
u8 *fn_803AC868(u8 *p, u32 a);
void fn_803DC988(u8 *p);
void fn_803DCB44(u8 *p);
s32 fn_803C4DE8(u8 *a, u8 *b, u32 c);
s32 fn_803C1BF8(u8 *a, u8 *b, u8 *c);
s32 fn_803C3DF4(u8 *a, u8 *b, u8 *c);
s32 fn_803C88F0(u8 *a, u8 *b, u8 *c);
void fn_80379514(u32 a);
void fn_803A5524(u32 a);
void OSLockMutex(void *m);
void OSUnlockMutex(void *m);
void fn_803BA360(u8 *a, u8 *b, s32 c, u32 d);
s32 fn_803BD46C(u8 *a, u8 *b);
void fn_803C04C4(u8 *a, u8 *b);
void fn_8016D1C0(u32 a, u32 b);
u32 fn_803DD940(u32 a);
s32 fn_803BFE5C(u8 *a, u8 *b, u32 c, u32 d);
void fn_803ACE90(u8 *a, u32 b, u32 c, u32 d, u32 e);
s32 fn_8016E430(u32 a);
void fn_8016E2E4(u32 a);
s32 fn_803BACA4(u8 *a, u32 b, u32 c, u32 d);
void fn_803B1458(u8 *a, u32 b, u32 c);
s32 fn_803C0B8C(u8 *a, u8 *b);

void fn_803A6EA0(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    if ((u8)fn_803ACCE4(a, b[0x184])) fn_803A9438(a, b, c);
    else fn_803B2570((u32)a, b[0x184], 0x32);
    b[0x84] = 0;
}
void fn_803A6F14(u8 *a, u8 *b) {
    u8 *c = b + 0x84;
    if ((u8)fn_803ACCE4(a, b[0x184])) fn_803A94A4(a, b, c);
    else fn_803B2570((u32)a, b[0x184], 0x33);
    b[0x84] = 0;
}
void fn_803A7694(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x24);
    *(u8 **)m = a;
    m[0x10] = c[0];
    m[0x11] = b[0x184];
    m[0x12] = 0;
    fn_803DEF00((void *)fn_803A9B68, m, 0);
}
void fn_803A77E4(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = c[0];
    m[9] = b[0x184];
    fn_803DEF00((void *)fn_803A9C64, m, 0);
}
void fn_803A7524(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0xa4);
    m[0x8b] = 0;
    *(u8 **)m = a;
    m[0x88] = c[0];
    m[0x89] = b[0x184];
    *(u16 *)(m + 0x8e) = *(u16 *)(c + 2);
    fn_803DEF00((void *)fn_803A9A6C, m, 0);
}
void fn_803A8444(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x74);
    m[0x66] = 0;
    *(u8 **)m = a;
    m[0x64] = c[0];
    m[0x65] = b[0x184];
    *(u16 *)(m + 0x68) = *(u16 *)(c + 2);
    fn_803DEF00((void *)fn_803AAF70, m, 0);
}
void fn_803A7858(u8 *a, u8 *b, u8 *c) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    q[0x18] = b[0x184];
    q[0x40] = c[0];
    fn_803DEF00((void *)fn_803A9CB8, q, 1000);
}
void fn_803A78CC(u8 *a, u8 *b) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    q[0x18] = b[0x184];
    q[0x40] = b[0x84];
    *(u32 *)(q + 0x10) = fn_803DEF00((void *)fn_803A9D0C, q, 1000);
}
u32 fn_803ADDE8(u8 *a, u8 *b) {
    u32 i = (u8)fn_803DA0D0(b);
    u32 v = lbl_80405168[i] * (fn_803DC804(a) * 4);
    u32 mx = fn_803DA0F8(b);
    if (v > mx) v = mx;
    return v;
}
s32 fn_803CE560(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B16B4(a, b, r, b[r + 0x219c]);
    return 0;
}
s32 fn_803CE5D4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B1704(a, b, r, b[r + 0x219c]);
    return 0;
}
u8 fn_803D01BC(s32 a, s32 b) {
    s32 i;
    s32 v = fn_803D9878(a, b, 0x40);
    for (i = 0; i < 6; i++) {
        if (v <= lbl_80405A50[i].a) break;
    }
    return lbl_80405A50[i].b;
}
s32 fn_803D520C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803C4DE8(a, b, *(u32 *)(b + 0x64)) != 1) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D5DF0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803C1BF8(a, b, b + 0x138) == 0) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D64CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803C3DF4(a, b, b + 0x138) == 0) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D69A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803C88F0(a, b, b + 0x138) == 0) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D225C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803BFE5C(a, b, *(u32 *)(b + 0x64), 0)) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D6458(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u16 *q = (u16 *)(b + *(u32 *)(b + 0x64) * 2 + 0x3124);
    if (*q) {
        *(u32 *)(b + 0x128) = *q;
        *q = 0;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
void fn_803B2D68(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) fn_803BA360(a, b, i, b[i + 0x219c]);
    *(u16 *)(b + 0x3122) = *(u32 *)(b + 0x2e4c);
    *(u32 *)(b + 8) = 1;
}
void fn_803B2E28(u8 *a, u8 *b) {
    if (fn_803BD46C(a, b)) {
        fn_803BA9D4(b, 2, 0x29);
        *(u32 *)(b + 8) = 0x15;
        *(u32 *)(b + 0xc) = 3;
    } else {
        *(u32 *)(b + 8) = 3;
    }
    fn_803C04C4(a, b);
}
s32 fn_803CD4E0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 y;
    s32 x;
    x = fn_803D6E6C(b);
    y = fn_803D6E6C(b);
    *(u32 *)(b + 0x134) = y + (s32)DS_Rand() % (x + 1);
    return 0;
}
s32 fn_803CD2F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B1458(a, fn_803D803C(a, b, x), y);
    return 0;
}
s32 fn_803CDD88(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B1570(a, fn_803D803C(a, b, x), y);
    return 0;
}
s32 fn_803CDE04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B15AC(a, fn_803D803C(a, b, x), y);
    return 0;
}
s32 fn_803D6AEC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B24A8(a, fn_803D803C(a, b, x), y);
    return 0;
}
s32 fn_803CD270(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    *(u32 *)(b + fn_803D803C(a, b, x) * 4 + 0x218c) |= y;
    return 0;
}
s32 fn_803CF3B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, x);
    *r = fn_803C0B68(*r, y);
    return 0;
}
void fn_803C8BC8(u8 *a, s32 b, s32 c) {
    if (fn_803BFB18(a, c) == 0x2e && c != 0xff) {
        u8 *q = a + b * 0xc0;
        q += *(u16 *)(a + b * 2 + 0x30bc);
        if (q[0x2d6c]) q[0x2d6c]--;
    }
}

}
#pragma pop

extern "C" {

void fn_803D71CC(u8 *a, u8 *b);
void fn_8017CED8(u8 *a);
s32 WPADGetInfoAsync(s32 ch, void *info, void *cb);
extern u8 lbl_8063CEF0[];
extern u8 lbl_8063CFB0[];
void fn_8037A9EC(u8 *p);
extern u8 lbl_80405248[];

u16 fn_803C3D6C(u8 *p, s32 i) {
    if ((u8)fn_803BFB18(p, i) == 0x67) return 0;
    u8 *q = p + i * 0xc0;
    if ((*(u32 *)(q + 0x2dcc) >> 10) & 7) return 0;
    return *(u16 *)(q + 0x2db8);
}
s32 fn_803A5804(s32 *p, void *info) {
    if (*p >= 4) return -2;
    if (fn_803A6070(*(u8 **)(p + 9), *p) != 0 || ((u8 *)p)[0x1c] != 0) return -2;
    return WPADGetInfoAsync(*p, info, (void *)fn_803A5888);
}
s32 fn_803D50C8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 r = fn_803C4194(b, *(u32 *)(b + 0x64));
    if (r) {
        *(u32 *)(b + 0x2154) = r;
        *(u32 *)(b + 0x2160) = fn_803C41D8(b, *(u32 *)(b + 0x64));
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
s32 fn_803D53EC(u8 *a, u8 *b) {
    u8 v = fn_803C5A34(b, 0);
    if (v) {
        (*(u32 *)(b + 0xb4))++;
        u32 n = fn_803D6E6C(b);
        if (v == 0xff) *(u32 *)(b + 0xb4) += n;
        else b[0x21a0] = v - 1;
    }
    return 0;
}
s32 fn_803CC140(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    *(u8 **)(b + 0x178) = (u8 *)fn_8016DF70(5, 0x50);
    **(u8 ***)(b + 0x178) = a;
    *(u8 **)(*(u8 **)(b + 0x178) + 4) = b;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x20) = 0;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x40) = 0;
    fn_803DEF00((void *)fn_803D71CC, *(u8 **)(b + 0x178), 0);
    return 0;
}
s32 fn_803D440C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    if (*(u32 *)(q + 0x2dac) != 0 || (*(u32 *)(q + 0x2db0) & 0x1000000) ||
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dac) == 0) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
u8 *fn_803A50E8(u8 *p, s32 del) {
    if (p) {
        OSCancelAlarm(lbl_8063CEF0 + *(s32 *)p * 0x30);
        OSCancelAlarm(lbl_8063CFB0 + *(s32 *)p * 0x30);
        if (p + 0x20) fn_8037A9EC(p + 0x20);
        if (del > 0) ::operator delete(p);
    }
    return p;
}
s32 fn_803D63CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    *(u16 *)(b + r * 2 + 0x3124) = *(u16 *)(b + r * 0xc0 + 0x2db8);
    *(u16 *)(b + r * 0xc0 + 0x2db8) = 0;
    fn_803BD374(a, b, r);
    return 0;
}
#pragma push
#pragma optimize_for_size on
void fn_803B2F20(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) {
        b[i] = 0;
        *(u32 *)(b + i * 0xc0 + 0x2dc4) = *(u32 *)(b + i * 0xc0 + 0x2dc0);
    }
    fn_8017CED8(a);
    fn_8016E2E4(0xf);
    fn_803ADCB8(a, 0);
    *(u32 *)(b + 8) = 5;
}
#pragma pop

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

void fn_803A9270(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x10);
    m[0xa] = 0;
    *(u8 **)m = a;
    m[8] = c[0];
    m[9] = b[0x184];
    *(u16 *)(m + 0xc) = *(u16 *)(c + 2);
    m[0xe] = c[1];
    fn_803DEF00((void *)fn_803AB1D0, m, 0);
}
void fn_803A75A0(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x74);
    *(u8 **)m = a;
    m[0x68] = c[0];
    m[0x69] = b[0x184];
    *(u8 **)(m + 4) = b;
    *(u32 *)(m + 8) = *(u32 *)(b + 0x20);
    m[0x6b] = 0;
    m[0x6c] = c[1];
    fn_803DEF00((void *)fn_803A9AC0, m, 0);
}
void fn_803A742C(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x2c);
    m[0x12] = 0;
    *(u8 **)m = a;
    m[0x10] = c[0];
    m[0x11] = b[0x184];
    *(u16 *)(m + 0x16) = *(u16 *)(c + 2);
    *(u32 *)(m + 0x18) = *(u32 *)(c + 8);
    *(u32 *)(m + 0x1c) = b[0x185];
    fn_803DEF00((void *)fn_803A99C4, m, 0);
}
void fn_803ADD64(u8 *p, u8 *out) {
    u8 *o;
    s32 i;
    for (i = 0; i < 4; i++) out[i] = 0xff;
    o = out;
    for (i = 0; i < *(s32 *)(p + 0x44); i++) {
        *o = fn_803AB514(*(u8 **)(p + i * 4 + 0x34));
        o++;
    }
}
void fn_803ADE6C(u8 *a, u8 *b, Rec24 *c) {
    Rec24 tmp;
    fn_803ADEF0(&tmp, c);
    fn_803ADF40(a, (u8 *)c, 0);
    fn_803AE378(a, (u8 *)c, b, 0);
    fn_803AF334(a, (u32)b, (u8 *)c);
    fn_803D9A44((void *)*(u32 *)(a + 0x18), &tmp);
}
void fn_803B1798(u8 *a, u8 *b, u32 c) {
    u8 m[8];
    m[0] = 0x23;
    u8 *q = m;
    for (s32 i = 0; i < (s32)fn_803AC860(a); i++) {
        q[i + 4] = b[i + 0x219c];
    }
    fn_803AF5F0(a, 1, c, m, 8);
}
s32 fn_803D4C50(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (fn_803C3DD8(b, fn_803D803C(a, b, x)) == 1) *(u32 *)(b + 0xb4) += y;
    return 0;
}
s32 fn_803D5898(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    fn_803B1D18(a, fn_803D803C(a, b, x), y, z);
    return 0;
}
s32 fn_803D5CF8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    fn_803B2078(a, fn_803D803C(a, b, x), y, z);
    return 0;
}
u32 fn_803BF7E8(u32 i, u8 *x, u8 *y, u8 *z) {
    u32 r = 1;
    if (i >= 0x70) {
        i = (u32)(u16)DS_Rand() % 0x70;
        r = 0;
    }
    u8 t0 = lbl_80405248[i * 3];
    u8 t1 = lbl_80405248[i * 3 + 1];
    *x = t0;
    u8 t2 = lbl_80405248[i * 3 + 2];
    *y = t1;
    *z = t2;
    return r;
}

}
#pragma pop

extern "C" {

void fn_803C605C(u8 *a, u8 *b, s32 i, u32 c);
s32 fn_803C01A0(u8 *a, u8 *b, u32 c);
void fn_8017C9E0(u32 a, u32 b);

s32 fn_803BF758(u8 *p, s32 i) {
    switch (*(u16 *)(p + i * 16 + 0x3de)) {
    case 0x1a:
    case 0x27:
    case 0x4b:
    case 0x91:
    case 0x97:
    case 0x9b:
    case 0xff:
    case 0x100:
    case 0x107:
    case 0x110:
        return 1;
    }
    return 0;
}
u32 fn_803C9010(u8 *p, s32 i) {
    switch (*(u16 *)(p + i * 16 + 0x3de)) {
    case 0x1a:
    case 0x27:
    case 0x4b:
    case 0x91:
    case 0x97:
    case 0x9b:
    case 0xff:
    case 0x100:
    case 0x107:
    case 0x111:
        return *(u32 *)(p + 0x213c) & 0x200;
    }
    return 1;
}
s32 fn_803CAFE0(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x30];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    fn_803B0F68(a, b, out);
    if (*(u32 *)(lbl_8048CE28 + 4) == 0) *(u32 *)(lbl_8048CE28 + 4) = 10;
    return 0;
}
s32 fn_803CB070(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x30];
    (*(u32 *)(b + 0xb4))++;
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    out[1] |= 0x80;
    fn_803B0F68(a, b, out);
    *(u32 *)(lbl_8048CE28 + 4) = 10;
    return 0;
}
#pragma push
#pragma optimize_for_size on
s32 fn_803CC5B4(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    u32 m = fn_803D6E6C(b);
    for (s32 i = 0; i < n; i++) {
        if (*(u32 *)(b + i * 4 + 0x13c) & 1) {
            *(u32 *)(b + 0x78) = i;
            *(u32 *)(b + 0xb4) += m;
            break;
        }
    }
    return 0;
}
#pragma pop
s32 fn_803D3F04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803BF8E4((u16)*(u32 *)(b + 0x3048)) == 0 && *(u32 *)(b + 0x3048) != 0 && fn_803C8688((u16)*(u32 *)(b + 0x3048)) == 1) {
        *(u32 *)(b + 0x124) = *(u32 *)(b + 0x3048);
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
u32 fn_803C4100(u8 *p, s32 i, s32 c) {
    u16 v;
    switch (c) {
    case 0:
        v = fn_803C3D6C(p, i);
        break;
    case 2:
        if ((*(u32 *)(p + i * 0xc0 + 0x2dcc) >> 10) & 7) return 0;
    case 1:
        v = *(u16 *)(p + i * 0xc0 + 0x2db8);
        break;
    }
    ItemData_GetParam((ItemData *)ItemTable_GetEntry((ItemData *)*(u8 **)(p + 0x2120), v), 2);
}
void fn_803A9E68(u8 *a, u8 *m) {
    fn_8017C9E0(*(u32 *)m, m[9]);
    fn_803AC848(*(u8 **)m);
    s32 v = fn_803C93C4(*(u8 **)m, m[9], 0);
    if (v == 0xff) v = 1;
    fn_803B07B4(*(u8 **)m, m[9], v);
    fn_803B2570(*(u32 *)m, m[9], m[8]);
    fn_8016E0A0(m);
    fn_803DEF3C(a);
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D11BC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, x);
    if (*r < (u32)fn_803AC860(a)) *(u32 *)(b + 0xb4) += y;
    return 0;
}
s32 fn_803D5A68(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (fn_803C01A0(a, b, fn_803D803C(a, b, x))) *(u32 *)(b + 0xb4) += y;
    return 0;
}
void fn_803C5FCC(u8 *a, u8 *b) {
    for (s32 i = 0; i < (s32)fn_803AC860(a); i++) {
        for (s32 j = 0; j < 6; j++) b[i * 6 + j + 0x312c] = j;
        fn_803C605C(a, b, i, b[i + 0x219c]);
    }
}
u32 fn_803BF9AC(u8 *a, u8 *b, s32 i) {
    u8 *q;
    u32 r;
    u32 k;
    r = 0;
    k = (u8)fn_803ACCE4(a, i);
    q = b + i * 0xc0;
    if (*(u16 *)(q + 0x2db8) != 0 &&
        (((*(u32 *)(b + k * 8 + 0x1c4) >> 3) & 0x3f) & fn_803DD920(b[i + 0x219c])) == 0 &&
        (u8)Item_IsMail(*(u16 *)(q + 0x2db8)) == 0) {
        r = 1;
    }
    return r;
}

}
#pragma pop

extern "C" {

extern void (*lbl_80405178[])(u8 *, u8 *);
extern u8 lbl_8048CDE8[];
void fn_803B1D58(u8 *a, u32 b);
void fn_8016FA4C(u32 a, void *b);

static inline s32 SelIdx(u8 *p, s32 i) {
    return i;
}

#define SEL_GETTER(name, T, EXPR)                                                         \
    T name(u8 *p, u32 i) {                                                                \
        if ((*(u32 *)(p + 0x2c) & 8) ||                                                   \
            ((*(u32 *)(p + 0x2c) & 0x10) && (fn_803AB514(*(u8 **)(p + i * 4 + 0x34)) & 1))) \
            return EXPR(i);                                                               \
        if (*(u32 *)(p + 0x2c) & 2) return EXPR(i & 1);                                   \
        return EXPR(i);                                                                   \
    }

#define E_68(k) (*(u32 *)(p + (k) * 4 + 0x68))
#define E_A0(k) (*(u16 *)(p + (k) * 2 + 0xa0))
#define E_48(k) (*(u32 *)(p + (k) * 4 + 0x48))
#define E_78(k) (*(u32 *)(p + (k) * 4 + 0x78))
#define E_AC(k) (p + (k) * 0x2c + 0xac)

SEL_GETTER(fn_803AC868, u8 *, (u8 *)E_68)
SEL_GETTER(fn_803ACA98, u16, E_A0)
SEL_GETTER(fn_803ACBCC, u32, E_48)
SEL_GETTER(fn_803ADBCC, u32, E_78)
SEL_GETTER(fn_803ACB30, u8 *, E_AC)

s32 fn_803B2C3C(u8 *a, u8 *b) {
    if (b[0x311f] == 0 && fn_803ADCD8(a) != 0 && !(fn_803ADCD8(a) & 0x40)) *(u32 *)(b + 8) = 0x29;
    lbl_80405178[*(u32 *)(b + 8)](a, b);
    return *(u32 *)(b + 8) == 0x2b;
}
s32 fn_803D5924(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803B1D58(a, r);
    *(u32 *)lbl_8048CDE8 = r;
    *(u32 *)(lbl_8048CDE8 + 4) = ((*(u8 **)(a + 0x30))[r * 0xc0 + 0x2d66] >> 3) & 0x1f;
    fn_8016FA4C(0x16, lbl_8048CDE8);
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D52EC(u8 *a, u8 *b) {
    u8 v = fn_803C5A34(b, 0);
    if (v) {
        (*(u32 *)(b + 0xb4))++;
        u32 x = fn_803D6E6C(b);
        u32 y = fn_803D6E6C(b);
        if (v == 0xff) *(u32 *)(b + 0xb4) += y;
        else *(u32 *)(b + 0xb4) += x;
    }
    return 0;
}
s32 fn_803D4494(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 k = fn_803C06A4(a, b, *(u32 *)(b + 0x64));
    if (((*(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc) >> 19) & 7) < (u32)(k - 1) || k < 2) *(u32 *)(b + 0xb4) += n;
    return 0;
}
void fn_803A7EAC(u8 *a, u8 *b, u8 *c) {
    u8 *m = (u8 *)fn_8016DF70(5, 0x1c);
    m[0xe] = 0;
    *(u8 **)m = a;
    m[0xc] = c[0];
    m[0xd] = b[0x184];
    *(u8 **)(m + 4) = b + 0x28;
    *(u32 *)(m + 0x10) = *(u16 *)(c + 2);
    m[0xf] = c[1];
    *(u16 *)(m + 0x18) = *(u32 *)(c + 4);
    *(u32 *)(m + 0x14) = *(u32 *)(c + 8);
    fn_803DEF00(*(void **)(b + 0x14), m, 0);
}

}
#pragma pop

extern "C" {

void fn_803B0F14(u8 *a, u8 *b);

void fn_803AFF40(u8 *a, u32 b, u32 c) {
    Msg4 m;
    m.a = c;
    m.cmd = 9;
    u32 k = fn_803ACD38(a, b);
    m.b = (*(u8 **)(a + 0x30))[k + 0x219c];
    fn_803AF5F0(a, 1, b, &m, 4);
}
s32 fn_803CED18(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 v = *(s32 *)(b + 0x14c) * *(s32 *)(b + 0x2168);
    *(s32 *)(b + 0x130) = v;
    if (v > 0xffff) *(s32 *)(b + 0x130) = 0xffff;
    fn_803DA100((u8 *)fn_803ACBCC(a, 0), *(u32 *)(b + 0x130));
    return 0;
}
void fn_803A4274(u8 *p, u8 *arg) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        (*(VObj **)(fn_80362AEC(p + 8, i) + 4))->v18(arg);
    }
}
u8 *fn_803A476C(u8 *p, u32 key) {
    for (u32 i = 0; i < *(u16 *)(p + 0x10); i++) {
        u8 *e = fn_80362AEC(p + 0x18, i);
        if (*(u32 *)e == key) return *(u8 **)(e + 4);
    }
    return 0;
}
void fn_803B608C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 9);
    u32 v = b[*(u32 *)(b + 0xec) + 0x21e8];
    *(u32 *)(b + 0x64) = v;
    *(u32 *)(b + 0x78) = v;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x28;
    *(u32 *)(b + 0x138) = 0;
    *(u32 *)(b + 0x216c) |= 0x80000000;
    fn_8016D1C0(2, 0);
}
void fn_803B8F64(u8 *a, u8 *b) {
    u32 v = *(u32 *)(b + 0x213c) & 0xf0000000;
    if (v) {
        *(u32 *)(b + 0x74) = fn_803DD940(v >> 28);
        *(u32 *)(b + 0x213c) &= 0x0fffffff;
        fn_803BA9D4(b, 2, 0x115);
        *(u32 *)(b + 0x8) = 0x15;
        *(u32 *)(b + 0xc) = 0x24;
    } else {
        *(u32 *)(b + 0x8) = 0x24;
    }
}
s32 fn_803CAF68(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (!(*(u32 *)(b + 0x213c) & 1)) {
        fn_803B0F14(a, b);
        *(u32 *)(lbl_8048CE28 + 4) = 7;
        *(u32 *)(lbl_8048CE28 + 0xc) = *(u32 *)(b + 0x64);
    }
    *(u32 *)(b + 0x213c) |= 1;
    *(u32 *)(b + 0x2140) |= 4;
    return 0;
}
s32 fn_803D59F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    fn_803ACE90(a, r, b[r + 0x219c], 0, *(u32 *)(b + 0x128));
    return 0;
}
s32 fn_803D28DC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x64);
    if (q[0x18c]) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        q[0x18c] = 2;
        u8 *r = b + *(u32 *)(b + 0x64);
        r[0x1b8] = r[0x219c];
    }
    return 0;
}
void fn_803B2EA0(u8 *a, u8 *b) {
    s32 r = fn_803C0B8C(a, b);
    if (r) {
        fn_803BA9D4(b, 2, r);
        *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
        *(u32 *)(b + 8) = 0x15;
    } else {
        fn_803C04C4(a, b);
        *(u32 *)(b + 8) = 4;
        fn_8016E2E4(8);
    }
}
void fn_803AB114(u8 *a, u8 *m) {
    if (fn_8016E430(m[5]) == 0xff) {
        fn_803B1908(*(u8 **)m, m[5]);
        fn_803B2570(*(u32 *)m, m[5], m[4]);
        fn_8016E0A0(m);
        fn_803DEF3C(a);
    } else {
        fn_8016E2E4(0xc);
    }
}
struct BF_2DC8 { u32 hi : 18; u32 k : 3; u32 lo : 11; };
s32 fn_803D1788(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    BF_2DC8 *f = (BF_2DC8 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dc8);
    if (f->k < 5) f->k++;
    *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
    for (u32 i = 1; i < ((BF_2DC8 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dc8))->k; i++) {
        *(u32 *)(b + 0x2154) *= 2;
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

void fn_803ADCF8(u8 *p, u8 *out) {
    for (s32 i = 0; i < *(s32 *)(p + 0x44); i++) {
        out[(u8)fn_803AB514(*(u8 **)(p + i * 4 + 0x34))] = i;
    }
}
s32 fn_803C87B4(u8 *a, u32 x, s32 v) {
    s32 n = fn_803AC860(a);
    s32 i;
    for (i = 0; i < n; i++) {
        if (v == (u8)fn_803ACCE4(a, i)) break;
    }
    return i;
}
u8 fn_803C91C0(u32 i, s32 j) {
    u32 x = fn_803AC828();
    u8 *base = (u8 *)fn_803AC848((u8 *)x);
    if (fn_803AC840((u8 *)x) & 2) i &= 1;
    u8 *q = base + (u8)i * 6;
    return q[j + 0x312c];
}
s32 fn_803CA838(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    for (s32 i = 0; i < n; i++) fn_803B1BF0(a, i);
    return 0;
}
s32 fn_803ACC64(u8 *p, s32 v) {
    s32 i;
    for (i = 0; i < *(s32 *)(p + 0x44); i++) {
        if (v == (u8)fn_803AB514(*(u8 **)(p + i * 4 + 0x34))) break;
    }
    return i;
}
void fn_803B1CA8(u8 *a, u32 b, u32 c, u32 d) {
    fn_803BAC78((u8 *)fn_803AC848(a), b);
    Msg4 m;
    m.b = c;
    m.cmd = 0x2b;
    m.a = d;
    fn_803AF5F0(a, 1, b, &m, 4);
}
u32 fn_803C02EC(u8 *a, s32 i) {
    u32 r = 0;
    if ((u8)fn_803BFB18(a, i) == 0x36 && (*(u32 *)(a + 0x150) & 1) != ((*(u32 *)(a + i * 0xc0 + 0x2dc8) >> 1) & 1)) r = 1;
    return r;
}
u32 fn_803C0434(u8 *a, u8 *b, u32 m) {
    u32 r = 0;
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n; i++) {
        if (m & *(u32 *)(b + i * 0xc0 + 0x2dc0)) {
            r = 1;
            break;
        }
    }
    return r;
}
s32 fn_803D3F98(u8 *a, u8 *b) {
    s32 i;
    s32 s = 0;
    (*(u32 *)(b + 0xb4))++;
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    for (i = 0; i < 8; i++) {
        s8 v = q[i + 0x2d58];
        if (v > 6) s = s + v - 6;
    }
    *(s32 *)(b + 0x2154) = s * 20 + 60;
    if (*(s32 *)(b + 0x2154) > 200) *(s32 *)(b + 0x2154) = 200;
    return 0;
}
void fn_803B9748(u8 *a, u8 *b) {
    u32 f = fn_803AC840(a) & 4;
    if (!f) {
        u8 *x = fn_803AC868(a, 0);
        fn_803DC988(x);
        fn_803DCB44(x);
    }
    if (f) fn_803D9844(0);
    *(u32 *)(b + 8) = 0x2b;
}
s32 fn_803BABF0(u8 *p) {
    s32 i;
    s32 j;
    s32 k;
    s32 s = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 16; k++) s += p[i * 0x40 + j * 0x10 + k + 0x2200];
    if (s == 0) *(u32 *)(p + 0x3148) = 0;
    return s == 0;
}
s32 fn_803D1F84(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    for (s32 i = 0; i < 8; i++) b[*(u32 *)(b + 0x64) * 0xc0 + i + 0x2d58] = b[*(u32 *)(b + 0x6c) * 0xc0 + i + 0x2d58];
    *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) |= *(u32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2db0) & 0x100000;
    return 0;
}
void fn_803B0E94(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f, u32 g) {
    fn_803BAC78(b, c);
    struct { u8 cmd; u8 e; u16 d; u32 f; u32 g; } m;
    m.d = d;
    m.cmd = 0x13;
    m.e = e;
    m.f = f;
    m.g = g;
    fn_803AF5F0(a, 1, c, &m, 0xc);
}
s32 fn_803CBB14(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    fn_803B13E0(a, (u32)b, y, fn_803D803C(a, b, x));
    return 0;
}
u32 fn_803BF930(u8 *a, u32 mv, u32 c) {
    u32 r = 0;
    if (mv == 0xae && (fn_803BACA4(a, c, 0x1b, 0) == 7 || fn_803BACA4(a, c, 0x1c, 0) == 7)) r = 1;
    return r;
}
s32 fn_803CDC28(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 n = fn_803AC860(a);
    s32 j;
    s32 i;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 8; j++) b[i * 0xc0 + j + 0x2d58] = 6;
        *(u32 *)(b + i * 0xc0 + 0x2db0) &= ~0x100000;
    }
    return 0;
}
void fn_803A83B4(u8 *a, u8 *b, u8 *c) {
    u8 *q = b + 0x28;
    memset(q, 0, 1);
    *(u8 **)(q + 0xc) = a;
    u8 f = b[0x185];
    u8 cv = c[0];
    u8 bv = b[0x184];
    q[0x40] = cv;
    q[0x18] = bv;
    if (f == 0) *(u32 *)(q + 0x10) = fn_803DEF00((void *)fn_803AAF1C, q, 1000);
    else fn_803B2570((u32)a, bv, cv);
}

}
#pragma pop

extern "C" {

s32 fn_803BF380(u8 *a, u8 *b, u32 c, u32 d, u32 e);
u32 fn_803DE944(u8 *p);
extern u8 lbl_80473058[];

#define E_68F(k) fn_803DE944(*(u8 **)(p + (k) * 4 + 0x68))
SEL_GETTER(fn_803AC900, u32, E_68F)

u8 fn_803C922C(s32 i, s32 j) {
    u32 fl = fn_803AC840((u8 *)fn_803AC828());
    if (fl & 8) {
        if (j > 0) return 0xff;
        return i;
    }
    if (fl & 2) {
        if (j > 1) return 0xff;
        if (i > 1) return 0xff;
        return i + j * 2;
    }
    if (j > 0) return 0xff;
    return i;
}
u8 *fn_803A5C30(u8 *p, s32 del) {
    if (p) {
        *(u8 **)(p + 0x1f0) = lbl_80473058;
        lbl_806405B8 = 0;
        p[0x1ec] = 0;
        OSCancelAlarm(p + 0x1a0);
        u8 *q = p;
        for (s32 i = 0; i < 4; i++) {
            OSCancelAlarm(q);
            q += 0x68;
        }
        if (del > 0) ::operator delete(p);
    }
    return p;
}
s32 fn_803BA0C0(u8 *a, u8 *b) {
    s32 r = 0;
    u32 v = *(u32 *)(b + 0x216c);
    if (v) {
        if (b[0x217d] != 0) {
            if (*(s32 *)(b + 0x74) != 0xff || b[0x217c] == 1 || (v & 0x4000)) r = 1;
        } else {
            r = 1;
        }
    }
    if (r == 1) {
        fn_803BA9D4(b, 2, 0x15);
        *(u32 *)(b + 0xc) = *(u32 *)(b + 8);
        *(u32 *)(b + 8) = 0x15;
    }
    return r;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

void fn_803B2294(u8 *a, u8 *b) {
    Msg4 m;
    m.cmd = 0x3c;
    m.a = 0;
    for (s32 i = 0; i < (s32)fn_803AC860(a); i++) {
        if (*(u32 *)(b + i * 16 + 0x21a8) == 0x10) m.a |= fn_803DD920(i);
    }
    fn_803AF5F0(a, 1, 0, &m, 4);
}
s32 fn_803D6894(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803BF380(a, b, 8, 0, 0xd) || fn_803BF380(a, b, 8, 0, 0x4c)) *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803CC648(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    *(u8 **)(b + 0x178) = (u8 *)fn_8016DF70(5, 0x50);
    **(u8 ***)(b + 0x178) = a;
    *(u8 **)(*(u8 **)(b + 0x178) + 4) = b;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x20) = 0;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x1c) = n;
    *(u32 *)(*(u8 **)(b + 0x178) + 0x24) = *(u32 *)(b + 0x128);
    fn_803DEF00((void *)fn_803D8004, *(u8 **)(b + 0x178), 0);
    return 0;
}
s32 fn_803D4DA8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 *r = fn_803D6E8C(a, b, y);
    *r = fn_803C877C(b, fn_803C3D6C(b, fn_803D803C(a, b, x)), 1);
    return 0;
}
s32 fn_803D67F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    if ((*(u32 *)(b + r * 0xc0 + 0x2db0) & 0x1000000) || (*(u32 *)(b + r * 0x1c + 0x2e8) & 8)) *(u32 *)(b + 0xb4) += y;
    return 0;
}

}
#pragma pop

extern "C" {

u32 fn_803C84AC(u8 *b, u32 c, u32 d, u32 e, u32 f);

s32 fn_803CC028(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if ((fn_803AC840(a) & 0x400) || (fn_803ADB9C(a) & 1)) {
        *(u32 *)(b + 0x2150) = 1;
    } else if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0x2150) = 1;
    } else {
        *(u32 *)(b + 0x2150) = fn_803C84AC(b, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), *(u32 *)(b + 0x214c), fn_803C8C48((u32)a, (u32)b, 0, *(u32 *)(b + 0x6c)));
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803CF434(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    s32 *r1 = (s32 *)fn_803D6E8C(a, b, x);
    s32 *r2 = (s32 *)fn_803D6E8C(a, b, y);
    s32 s = 1;
    if (*r1 < 0) s = -1;
    if ((*r1 = *r1 / *r2) == 0) *r1 = s;
    return 0;
}
void fn_803B3E70(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    fn_803C04C4(a, b);
    if (*(s32 *)(b + 0xec) == n) {
        *(u32 *)(b + 0xec) = 0;
        *(u32 *)(b + 8) = 9;
        fn_8016FA4C(0x15, 0);
        fn_8016E2E4(10);
    } else {
        u8 *q = b + *(u32 *)(b + 0xec);
        *(u32 *)(b + 8) = *(u32 *)(b + q[0x21e8] * 16 + 0x21a8);
        *(u32 *)lbl_8048CDE8 = q[0x21e8];
        fn_8016FA4C(3, lbl_8048CDE8);
    }
}
void fn_803B616C(u8 *a, u8 *b) {
    fn_803BA9D4(b, 2, 0xe4);
    *(u32 *)(b + 0x64) = 0;
    *(u32 *)(b + 0x6c) = 1;
    *(u32 *)(b + 0x8) = 0x15;
    *(u32 *)(b + 0xc) = 0x27;
    *(s32 *)(b + 0x138) = (s32)DS_Rand() % 10;
    if (b[0x311d]) b[0x311d]--;
    if (*(u32 *)(b + 0x138)) {
        *(u32 *)(b + 0x130) = 1;
        if (b[0x311c]) b[0x311c]--;
    }
}
s32 fn_803CB1A8(u8 *a, u8 *b) {
    u8 buf[0x20];
    u8 out[0x24];
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    fn_803D8444(b, buf);
    fn_803D8520(a, b, buf, out);
    out[1] |= 0x40;
    *(u32 *)(out + 0x20) = fn_803D803C(a, b, n);
    fn_803B0F68(a, b, out);
    *(u32 *)(lbl_8048CE28 + 4) = 10;
    return 0;
}

}
#pragma pop

extern "C" {

u8 *fn_803DE94C(u8 *p, u32 v);
u8 fn_803BBB80(u8 *a, u8 *b, u32 c, u32 d, u32 e);

s32 fn_803D091C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 q = fn_803C0B68(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90), 4);
    u8 *p = b + *(u32 *)(b + 0x64) * 0xc0;
    if (*(s32 *)(p + 0x2d8c) <= q) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(s32 *)(b + 0x215c) = -q;
        *(s32 *)(p + 0x2de0) = q;
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) &= ~0xe000;
    }
    return 0;
}
s32 fn_803D19A0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 r = (u8)DS_Rand();
    if (r < 0x66) *(u32 *)(b + 0x2154) = 40;
    else if (r < 0xb2) *(u32 *)(b + 0x2154) = 80;
    else if (r < 0xcc) *(u32 *)(b + 0x2154) = 120;
    else {
        *(s32 *)(b + 0x215c) = fn_803C0B68(*(s32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d90), 4);
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

u8 *fn_803AC9A4(u8 *p, u32 i, u32 v) {
    if ((*(u32 *)(p + 0x2c) & 8) ||
        ((*(u32 *)(p + 0x2c) & 0x10) && (fn_803AB514(*(u8 **)(p + i * 4 + 0x34)) & 1))) {
        return fn_803DE94C(*(u8 **)(p + i * 4 + 0x68), v);
    }
    if (*(u32 *)(p + 0x2c) & 2) {
        return fn_803DE94C(*(u8 **)(p + (i & 1) * 4 + 0x68), v);
    }
    return fn_803DE94C(*(u8 **)(p + i * 4 + 0x68), v);
}
u32 fn_803ACD38(u8 *p, s32 i) {
    u32 x;
    s32 n = *(s32 *)(p + 0x44);
    if (!(*(u32 *)(p + 0x2c) & 2)) return i;
    u8 **pi = (u8 **)(p + i * 4);
    s32 j;
    for (j = 0; j < n; j++) {
        if (j != i) {
            x = fn_803AB514(pi[0x34 / 4]) & 1;
            if ((u32)(fn_803AB514(*(u8 **)(p + j * 4 + 0x34)) & 1) == x) break;
        }
    }
    return j;
}
s32 fn_803ACDD8(u8 *p, s32 i, s32 m) {
    s32 n = *(s32 *)(p + 0x44);
    if (!(*(u32 *)(p + 0x2c) & 2)) return i ^ 1;
    u8 **pi = (u8 **)(p + i * 4);
    s32 j;
    for (j = 0; j < n; j++) {
        if (j != i) {
            u8 **pj = (u8 **)(p + j * 4);
            if (m == (fn_803AB514(pj[0x34 / 4]) & 2)) {
                u32 x = fn_803AB514(pi[0x34 / 4]) & 1;
                if ((u32)(fn_803AB514(pj[0x34 / 4]) & 1) != x) break;
            }
        }
    }
    return j;
}
s32 fn_803BFB90(u8 *a, s32 b, s32 c, s32 d) {
    u32 r = 0;
    if ((u8)fn_803BFB18(a, b) != 0x68) {
        if (d == (u8)fn_803BFB18(a, c)) r = 1;
    } else {
        if (d == (u8)fn_803BFB18(a, c)) {
            u32 *q = (u32 *)(a + b * 0x1c + 0x2d4);
            if (!((*q >> 28) & 1)) {
                *q |= 0x10000000;
                *(u32 *)(a + 0x213c) |= 0x800000;
            }
        }
    }
    return r;
}
s32 fn_803CF6A4(u8 *a, u8 *b) {
    u16 v;
    s32 i;
    (*(u32 *)(b + 0xb4))++;
    do {
        do {
            v = (s32)DS_Rand() % 0x1d3 + 1;
            for (i = 0; i < 4; i++) {
                if (v == *(u16 *)(b + *(u32 *)(b + 0x64) * 0xc0 + i * 2 + 0x2d4c)) break;
            }
        } while (i != 4);
    } while (fn_803C8688(v) == 0);
    *(u32 *)(b + 0x124) = v;
    return 0;
}
s32 fn_803CC708(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (b[0x217d] == 0) {
        if (x == 0) {
            if ((u8)fn_803BFB18(b, *(u32 *)(b + 0x64)) == 0x5c) {
                x = 5;
            } else {
                x = DS_Rand() & 3;
                if (x < 2) x += 2;
                else x = (DS_Rand() & 3) + 2;
            }
        }
        b[0x217c] = x;
        b[0x217d] = x;
        *(u32 *)(b + 0x2188) = y;
    }
    return 0;
}
struct BF_1C4 { u32 a : 10; u32 y : 2; u32 x : 3; u32 rest : 17; };
s32 fn_803CEFFC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)fn_803ACCE4(a, *(u32 *)(b + 0x64));
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 0x40) {
        *(u32 *)(b + 0xb4) += n;
        *(u32 *)(b + 0x216c) |= 0x40;
    } else {
        *q |= 0x40;
        BF_1C4 *f = (BF_1C4 *)(b + k * 8 + 0x1c4);
        f->x = 5;
        f->y = *(u32 *)(b + 0x64);
    }
    return 0;
}
void fn_803C04C4(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    s32 i;
    for (i = 0; i < n; i++) b[i + 0x21ec] = i;
    for (i = 0; i < n - 1; i++) {
        for (s32 j = i + 1; j < n; j++) {
            u8 x = b[i + 0x21ec];
            u8 y = b[j + 0x21ec];
            if (fn_803BBB80(a, b, x, y, 1)) {
                b[i + 0x21ec] = y;
                b[j + 0x21ec] = x;
            }
        }
    }
}

}
#pragma pop

extern "C" {

s32 fn_803BFCEC(u8 *a, u8 *b, u32 c);
s32 fn_803C44DC(u8 *a, u8 *b, u32 c);
void fn_803B12A4(u8 *a, u8 *b, u32 c);
void fn_803BDD44(u8 *a, u8 *b, u32 c);
u32 fn_803DA0C0(u8 *p);
u32 fn_803DA0C8(u8 *p);
u8 *fn_803DA0BC(u8 *p);
u32 GetMonDataInternal(u8 *mon, u32 id, void *buf);
s32 fn_803DECAC(u8 *a, void *b, u32 c);

s32 fn_803B6274(u8 *a, u8 *b) {
    s32 r = 0;
    if ((*(s32 *)(b + 0x6c) == 0xff && fn_803BF758(b, *(u32 *)(b + 0x3044)) == 0) ||
        (*(s32 *)(b + 0x6c) == 0xff && fn_803BF758(b, *(u32 *)(b + 0x3044)) == 1 &&
         ((*(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2db0) & 0x1000) || (*(u32 *)(b + 0x213c) & 0x200)))) {
        fn_803BA9D4(b, 2, 0x119);
        *(u32 *)(b + 0xc) = 0x26;
        r = 1;
        *(u32 *)(b + 8) = 0x15;
    }
    return r;
}
s32 fn_803D180C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 y = *(u32 *)(b + 0x118);
    u8 *px = b + *(u32 *)(b + 0x94) * 0xc0;
    u32 kx = (px[0x2dbe] >> 4) & 0xf;
    u32 ky = (b[y * 0xc0 + 0x2dbe] >> 4) & 0xf;
    if (ky == kx || (*(u32 *)(px + 0x2db0) & 0xf0000) || ky == 2 || kx == 2) {
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + *(u32 *)(b + 0x94) * 0xc0 + 0x2db0) |= fn_803DD920(y) << 16;
    }
    return 0;
}
s32 fn_803D2C80(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 o = *(u32 *)(b + 0x64) * 64;
    if ((*(u32 *)(b + o + *(u32 *)(b + 0x6c) * 4 + 0x1d8) != 0 && (*(u32 *)(b + o + 0x1ec) & fn_803DD920(*(u32 *)(b + 0x6c)))) ||
        (*(u32 *)(b + o + *(u32 *)(b + 0x6c) * 4 + 0x1f0) != 0 && (*(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x204) & fn_803DD920(*(u32 *)(b + 0x6c))))) {
        *(u32 *)(b + 0x2158) = 20;
    } else {
        *(u32 *)(b + 0x2158) = 10;
    }
    return 0;
}
s32 fn_803CBA04(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    fn_803B12A4(a, b, *(u32 *)(b + 0x74));
    *(u32 *)(b + 0x213c) &= (fn_803DD920(*(u32 *)(b + 0x74)) << 24) ^ 0xffffffff;
    *(u32 *)(b + 0x2140) |= fn_803DD920(*(u32 *)(b + 0x74)) << 28;
    *(u32 *)(b + *(u32 *)(b + 0x74) * 16 + 0x21a8) = 0x27;
    fn_803BDD44(a, b, *(u32 *)(b + 0x74));
    fn_8016E2E4(2);
    *(u32 *)lbl_8048CDE8 = *(u32 *)(b + 0x74);
    fn_8016FA4C(0xf, lbl_8048CDE8);
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D1B7C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    s32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    x = fn_803D803C(a, b, x);
    if (fn_803BFCEC(a, b, x) == 0) *(u32 *)(b + 0xb4) += z;
    else if (y == 1) *(u32 *)(b + x * 4 + 0x13c) |= 1;
    return 0;
}
s32 fn_803D48F8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 r1 = fn_803D803C(a, b, x);
    u32 k = (u8)fn_803ACCE4(a, fn_803D803C(a, b, y));
    if ((u8)fn_803ACCE4(a, r1) == k) *(u32 *)(b + 0xb4) += z;
    return 0;
}
s32 fn_803D514C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    if (*(u16 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2db8) != 0 && fn_803BFB90(b, *(u32 *)(b + 0x64), *(u32 *)(b + 0x6c), 0x3c) == 1) {
        *(u32 *)(b + 0xb4) += x;
    } else if (fn_803C44DC(a, b, *(u32 *)(b + 0x6c)) != 1) {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}
s32 fn_803D2AB4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 i;
    s32 c = 0;
    for (i = 0; i < (s32)fn_803AC860(a); i++) {
        if (*(u32 *)(b + i * 0xc0 + 0x2d8c)) c++;
    }
    if (*(u32 *)(b + 0xec) == c - 1) *(u32 *)(b + 0xb4) += n;
    else *(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) |= 0x8000000;
    return 0;
}
u32 fn_803C5A68(u8 *a, u8 *mon) {
    u16 buf[8];
    u8 *x = (u8 *)fn_803ACBCC(a, 0);
    u32 v1 = fn_803DA0C0(x);
    u32 v2 = fn_803DA0C8(x);
    u8 *v3 = fn_803DA0BC(x);
    GetMonDataInternal(mon, 0x8f, buf);
    if (v1 == GetMonDataInternal(mon, 7, 0) && v2 == GetMonDataInternal(mon, 0x9c, 0) && fn_803DECAC(v3, buf, 7) == 0) return 1;
    return 0;
}

}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D333C(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 i;
    s32 c = 0;
    for (i = 0; i < (s32)fn_803AC860(a); i++) {
        if (*(u32 *)(b + i * 0xc0 + 0x2d8c)) c++;
    }
    if (*(u32 *)(b + 0xec) == c - 1) *(u32 *)(b + 0xb4) += n;
    else *(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) |= 0x4000000;
    return 0;
}
s32 fn_803D4CDC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 w = fn_803D6E6C(b);
    u32 x = fn_803D6E6C(b);
    s32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    if (w == 0) {
        if (y == (s32)fn_803C40BC(b, r)) *(u32 *)(b + 0xb4) += z;
    } else {
        if (y != (s32)fn_803C40BC(b, r)) *(u32 *)(b + 0xb4) += z;
    }
    return 0;
}
struct BF_1C8 { u32 t : 2; u32 u : 2; u32 rest : 28; };
s32 fn_803D0EC8(u8 *a, u8 *b) {
    u32 k;
    BF_1C8 *f;
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    k = (u8)fn_803ACCE4(a, *(u32 *)(b + 0x64)) ^ 1;
    f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    if (f->t == 3) {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x80000000;
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + k * 4 + 0x1bc) |= 4;
        f->t++;
    }
    return 0;
}
s32 fn_803D4528(u8 *a, u8 *b) {
    u32 k;
    BF_1C8 *f;
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    k = (u8)fn_803ACCE4(a, *(u32 *)(b + 0x64)) ^ 1;
    f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    if (f->u == 2) {
        *(u32 *)(b + *(u32 *)(b + 0x64) * 0x1c + 0x2d4) |= 0x80000000;
        *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + k * 4 + 0x1bc) |= 0x400;
        f->u++;
    }
    return 0;
}
void fn_803BD840(u8 *a, u8 *b) {
    for (s32 i = 0; i < 4; i++) {
        *(u16 *)(b + i * 2 + 0x306c) = 0xff;
        b[i + 0x21a0] = 6;
        *(u16 *)(b + i * 2 + 0x310c) = DS_Rand();
    }
    *(u32 *)(b + 0x2168) = 1;
    *(u32 *)(b + 0x174) = 1;
    if (!(fn_803AC840(a) & 2)) {
        b[0x3108] |= fn_803DD920(2);
        b[0x3108] |= fn_803DD920(3);
    }
    b[0x311c] = 6;
    b[0x311d] = 6;
}
void fn_803C8820(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    for (s32 i = 0; i < n - 1; i++) {
        for (s32 j = i + 1; j < n; j++) {
            u8 x = b[i + 0x21e8];
            u8 y = b[j + 0x21e8];
            u32 kx = *(u32 *)(b + x * 16 + 0x21b4);
            if (kx == *(u32 *)(b + y * 16 + 0x21b4) && fn_803BBB80(a, b, x, y, kx - 1 != 0)) {
                b[i + 0x21e8] = y;
                b[j + 0x21e8] = x;
            }
        }
    }
}
s32 fn_803D0F94(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 t = *(u32 *)(b + (u8)fn_803ACCE4(a, r) * 8 + 0x1c8) >> 30;
    u8 *q;
    if (t && *(u32 *)((q = b + r * 0xc0) + 0x2d8c)) {
        *(s32 *)(b + 0x215c) = (5 - t) * 2;
        s32 m = *(s32 *)(q + 0x2d90);
        m *= -1;
        *(s32 *)(b + 0x215c) = fn_803C0B68(m, *(s32 *)(b + 0x215c));
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

}
#pragma pop

extern "C" {

s32 fn_803D4008(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    u32 m = *(u16 *)(q + 0x2dec);
    if (m != 0 && m == *(u16 *)(q + *(u16 *)(q + 0x2dee) * 2 + 0x2d4c)) {
    } else {
        m = (u16)fn_803BF340(b, *(u32 *)(b + 0x6c));
    }
    if (*(u32 *)(b + *(u32 *)(b + 0x6c) * 16 + 0x21a8) == 0x27 ||
        (b[m * 16 + 0x3e1] == 0 && !(*(u32 *)(b + *(u32 *)(b + 0x6c) * 64 + 0x1d4) >> 31))) {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803CDE80(u8 *a, u8 *b, u32 c);
void fn_803DA144(u8 *a, u32 b);

s32 fn_803D5660(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u16 v;
    if ((u8)fn_803BFB18(b, *(u32 *)(b + 0x64)) == 0x20) v = b[*(u32 *)(b + 0x3044) * 16 + 0x3e5] * 2;
    else v = b[*(u32 *)(b + 0x3044) * 16 + 0x3e5];
    if ((s32)DS_Rand() % 100 < v && *(u32 *)(b + *(u32 *)(b + 0x94) * 0xc0 + 0x2d8c) != 0) return 0;
    *(u32 *)(b + 0xb4) += n;
    return 0;
}
s32 fn_803D62F0(u8 *a, u8 *b) {
    s32 buf[7];
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 cnt = 0;
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    for (s32 i = 1; i < 8; i++) {
        if ((s8)q[i + 0x2d58] < 12) {
            buf[cnt] = i - 1;
            cnt++;
        }
    }
    if (cnt) *(u32 *)(b + 0x2170) = (buf[(s32)DS_Rand() % cnt] + 0x27) | 0x80000000;
    else *(u32 *)(b + 0xb4) += n;
    return 0;
}
struct BF_1C4b { u32 a : 15; u32 y : 2; u32 x : 3; u32 rest : 12; };
s32 fn_803D18CC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)fn_803ACCE4(a, *(u32 *)(b + 0x64));
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 8) {
        *(u32 *)(b + 0xb4) += n;
        *(u32 *)(b + 0x216c) |= 0x40;
    } else {
        *q |= 8;
        BF_1C4b *f = (BF_1C4b *)(b + k * 8 + 0x1c4);
        f->x = 5;
        f->y = *(u32 *)(b + 0x64);
        b[0xf5] = 1;
        *(u32 *)(b + 0xf8) = *(u32 *)(b + 0x64);
        *(u16 *)(b + 0xf6) = 0xc6;
    }
    return 0;
}
u32 fn_803C035C(u8 *a, u8 *b, s32 c, s32 mv) {
    u32 r = 0;
    s32 n = fn_803AC860(a);
    u32 k = (u8)fn_803ACCE4(a, c);
    for (s32 i = 0; i < n; i++) {
        if (k != (u8)fn_803ACCE4(a, i) && (*(u32 *)(b + i * 0xc0 + 0x2dc0) & 0x2000)) {
            s32 j;
            for (j = 0; j < 4; j++) {
                if (mv == *(u16 *)(b + i * 0xc0 + j * 2 + 0x2d4c)) break;
            }
            if (j != 4) r = 1;
        }
    }
    return r;
}
s32 fn_803CE014(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 v;
    if (a[0x23e4] == 1) {
        v = fn_803CDE80(a, b, 1);
        if ((*(u32 *)(a + 0x2c) & 0x10) || *(u32 *)(a + 0x2c) == 0x4b) v += fn_803CDE80(a, b, 3);
        fn_803DA100((u8 *)fn_803ACBCC(a, 0), v);
    } else {
        v = fn_803ADDE8(*(u8 **)(a + 0x68), *(u8 **)(a + 0x48));
        fn_803DA144((u8 *)fn_803ACBCC(a, 0), v);
    }
    if (v) *(s32 *)(b + 0x130) = v;
    else *(s32 *)(b + 0x130) = 0;
    return 0;
}

}
#pragma pop

extern "C" {

s32 fn_803D1DFC(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if ((*(u32 *)(b + 0x180) & 0x80ff) == 0 || fn_803BF380(a, b, 8, 0, 0xd) || fn_803BF380(a, b, 8, 0, 0x4c)) {
        *(u32 *)(b + 0x215c) = *(u32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90) >> 1;
    } else if (*(u32 *)(b + 0x180) & 0x30) {
        *(s32 *)(b + 0x215c) = fn_803C0B68(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90) * 20, 30);
    } else {
        *(s32 *)(b + 0x215c) = fn_803C0B68(*(s32 *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2d90), 4);
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D2168(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 w0 = fn_803D6E6C(b);
    u32 x0 = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 z = fn_803D6E6C(b);
    u32 w = fn_803D803C(a, b, w0);
    u32 x = fn_803D803C(a, b, x0);
    fn_803B2D0C(a, b, w, x, (u32)fn_803D90A0(b, y));
    if (*(u32 *)(b + 0x216c) & 0x1fd849) {
        *(u32 *)(b + 0xb4) += z;
        *(u32 *)lbl_8048CDE8 = x;
        fn_8016FA4C(0xb, lbl_8048CDE8);
    }
    return 0;
}
s32 fn_803D4F08(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if ((u8)fn_803BFB18(b, *(u32 *)(b + 0x64)) == 0x79) {
        *(u32 *)(b + 0xb4) += n;
        return 0;
    }
    s32 t = lbl_80405AC1[fn_803ACD14(a)];
    if (t != fn_803BACA4(b, *(u32 *)(b + 0x64), 0x1b, 0) && t != fn_803BACA4(b, *(u32 *)(b + 0x64), 0x1c, 0)) {
        b[*(u32 *)(b + 0x64) * 0xc0 + 0x2d64] = t;
        b[*(u32 *)(b + 0x64) * 0xc0 + 0x2d65] = t;
        *(s32 *)(b + 0x130) = t;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
s32 fn_803D1064(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 cnt = fn_803AC860(a);
    *(s32 *)(b + 0x134) = cnt;
    s32 k = 0;
    for (s32 i = 0; i < cnt; i++) {
        u8 *q = b + i * 0xc0;
        if ((*(u32 *)(q + 0x2dc0) & 0x20) || *(u32 *)(q + 0x2d8c) == 0 || fn_803BFB90(b, *(u32 *)(b + 0x64), i, 0x2b) == 1) {
            k++;
        } else {
            *(u32 *)(q + 0x2dc0) |= 0x20;
            *(u32 *)(q + 0x2dc8) |= 0x60000;
        }
    }
    if (k == cnt) *(u32 *)(b + 0xb4) += n;
    return 0;
}
struct BF_1C4c { u32 a : 2; u32 x : 3; u32 b : 2; u32 y : 3; u32 rest : 22; };
s32 fn_803D2D44(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 k = (u8)fn_803ACCE4(a, *(u32 *)(b + 0x6c));
    *(u32 *)(lbl_8048CE28 + 0x20) = 0;
    u32 *q = (u32 *)(b + k * 4 + 0x1bc);
    if (*q & 1) *(u32 *)(lbl_8048CE28 + 0x20) |= 1;
    if (*q & 2) *(u32 *)(lbl_8048CE28 + 0x20) |= 2;
    if ((*q & 1) || (*q & 2)) {
        *q &= ~3;
        BF_1C4c *f = (BF_1C4c *)(b + k * 8 + 0x1c4);
        f->x = 0;
        f->y = 0;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}
#pragma pop

extern "C" {

s32 fn_803D34C8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (fn_803BF380(a, b, 8, 0, 0xd) == 0 && fn_803BF380(a, b, 8, 0, 0x4c) == 0) {
        u32 fl = *(u32 *)(b + 0x180);
        if (fl & 0x80ff) {
            *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1] * 2;
            if (fl & 3) *(u32 *)(b + 0x2160) = 11;
            if (*(u32 *)(b + 0x180) & 0xc) *(u32 *)(b + 0x2160) = 5;
            if (*(u32 *)(b + 0x180) & 0x30) *(u32 *)(b + 0x2160) = 10;
            if (*(u32 *)(b + 0x180) & 0xc0) *(u32 *)(b + 0x2160) = 15;
        } else {
            *(u32 *)(b + 0x2154) = b[*(u32 *)(b + 0x3044) * 16 + 0x3e1];
        }
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803DA018(u32 a);
s32 fn_803C268C(u8 *b, u32 c, u32 d);

s32 fn_803D5E64(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    s32 c = fn_803D6E6C(b);
    s32 i;
    switch (c) {
    case 3:
        for (i = 0; i < n; i++) {
            if (!(((u8 *)fn_803AC850(a, i))[0x185] & 1)) fn_803B21EC(a, i);
        }
        break;
    case 4:
        for (i = 0; i < n; i++) {
            if (((u8 *)fn_803AC850(a, i))[0x185] & 1) fn_803B21EC(a, i);
        }
        break;
    default:
        fn_803B21EC(a, fn_803D803C(a, b, c));
        break;
    }
    return 0;
}
s32 fn_803D5F64(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    s32 c = fn_803D6E6C(b);
    s32 i;
    switch (c) {
    case 3:
        for (i = 0; i < n; i++) {
            if (!(((u8 *)fn_803AC850(a, i))[0x185] & 1)) fn_803B2224(a, i);
        }
        break;
    case 4:
        for (i = 0; i < n; i++) {
            if (((u8 *)fn_803AC850(a, i))[0x185] & 1) fn_803B2224(a, i);
        }
        break;
    default:
        fn_803B2224(a, fn_803D803C(a, b, c));
        break;
    }
    return 0;
}
s32 fn_803D5738(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u8 *q = b + *(u32 *)(b + 0x64) * 0xc0;
    if (*(u16 *)(q + 0x2d40) == 0x1b9 && *(u32 *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d8c) && !(*(u32 *)(q + 0x2db0) & 0x200000)) {
        s32 p;
        switch (fn_803DA018(fn_803ADBCC(a, *(u32 *)(b + 0x64)))) {
        case 0:
        default:
            p = 0;
            break;
        case 1:
            p = 10;
            break;
        case 2:
            p = 30;
            break;
        }
        if ((s32)DS_Rand() % 100 > p) *(u32 *)(b + 0xb4) += n;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}
s32 fn_803D66F0(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 o = r * 0xc0;
    if (*(u32 *)(b + o + 0x2d8c) && b[r + 0x219c] != 6) {
        u8 *m = fn_803AC9A4(a, r, b[r + 0x219c]);
        u32 v1 = GetMonDataInternal(m, 10, 0);
        u32 v2 = GetMonDataInternal(m, 0x9f, 0);
        if ((b + o)[0x2d67] != 0x1e && fn_803C268C(b, v1, v2) == 0) *(u32 *)(b + 0xb4) += y;
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}
s32 fn_803D2634(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    if (fn_803AC840(a) & 2) {
        u32 r = fn_803D803C(a, b, 0x10);
        if (!(b[0x3108] & fn_803DD920(r)) && *(u32 *)(b + r * 16 + 0x21a8) != 0x27 && *(u32 *)(b + r * 0xc0 + 0x2d8c) &&
            !((*(u32 *)(b + *(u32 *)(b + 0x64) * 64 + 0x1d4) >> 28) & 1) && !((*(u32 *)(b + r * 64 + 0x1d4) >> 28) & 1)) {
            *(u32 *)(b + 0x118) = r;
            *(u32 *)(b + r * 64 + 0x1d4) |= 0x10000000;
        } else {
            *(u32 *)(b + 0xb4) += n;
        }
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

void fn_803BD8FC(u8 *a, u8 *b, s32 c);

s32 fn_803CC4B0(u8 *a, u8 *b) {
    u8 *q;
    s32 i;
    (*(u32 *)(b + 0xb4))++;
    switch (fn_803D6E6C(b)) {
    case 1:
        i = *(u32 *)(b + 0x64);
        break;
    case 6:
        i = *(u32 *)(b + 0x78);
        break;
    case 0x12:
        i = *(u32 *)(b + 0x6c);
        break;
    }
    *(u32 *)(b + i * 4 + 0x13c) &= ~1;
    b[0x3108] &= fn_803DD920(i) ^ 0xffffffff;
    q = b + i;
    u8 v = q[0x21a0];
    q[0x219c] = v;
    q[0x21a0] = 6;
    fn_803BA360(a, b, i, v);
    fn_803C605C(a, b, i, q[0x219c]);
    *(u16 *)(b + 0x3122) = *(u32 *)(b + 0x2e4c);
    fn_803BD8FC(a, b, i);
    return 0;
}
s32 fn_803D65D0(u8 *a, u8 *b) {
    u32 r;
    s32 hit = 0;
    (*(u32 *)(b + 0xb4))++;
    r = fn_803D803C(a, b, fn_803D6E6C(b));
    s32 ab = fn_803C40BC(b, r);
    s32 v = fn_803C4100(b, r, 0);
    if (ab == 0x40 && (s32)DS_Rand() % 100 < v) hit = 1;
    if (ab == 0x66 && *(u32 *)(b + r * 0xc0 + 0x2d8c) == *(u32 *)(b + r * 0xc0 + 0x2d90)) hit = 1;
    if (hit) {
        s32 hp = *(s32 *)(b + r * 0xc0 + 0x2d8c);
        if (*(s32 *)(b + 0x215c) + hp <= 0) {
            *(s32 *)(b + 0x215c) = -(hp - 1);
            *(u32 *)(b + 0x216c) |= 0x100;
            *(u32 *)(lbl_8048CE28 + 0x1c) = 1;
        }
    }
    return 0;
}
s32 fn_803D45F4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u32 r = fn_803D803C(a, b, x);
    u32 k = (u8)fn_803ACCE4(a, r);
    BF_1C8 *f = (BF_1C8 *)(b + k * 8 + 0x1c8);
    u32 t = f->u;
    if (t) {
        *(u32 *)(b + 0x134) = t;
        *(u32 *)(b + 0x88) = 6;
        *(u32 *)(b + 0x94) = r;
        if (fn_803BACA4(b, *(u32 *)(b + 0x78), 0x1b, 0) == 3 || fn_803BACA4(b, *(u32 *)(b + 0x78), 0x1c, 0) == 3) {
            *(u32 *)(b + k * 4 + 0x1bc) &= ~0x400;
            f->u = 0;
            *(u32 *)(b + 0x134) = 0;
        }
    } else {
        *(u32 *)(b + 0xb4) += y;
    }
    return 0;
}

}
#pragma pop

extern "C" {

void fn_803AF780(u8 *a, u32 b);
u32 fn_803BC964(u8 *a, u8 *b, u32 c, u32 d, u32 e, u32 f);
void fn_803BCE18(u8 *a, u8 *b, u32 c, u32 d);

s32 fn_803CB5B4(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 r = fn_803D803C(a, b, fn_803D6E6C(b));
    u8 *q = b + r * 0xc0;
    s32 d = *(s32 *)(b + 0x215c);
    s32 hp = *(s32 *)(q + 0x2d8c);
    if (d + hp <= 0) *(s32 *)(b + 0x2148) = -hp;
    else *(s32 *)(b + 0x2148) = d;
    if (*(s32 *)(b + 0x2148) < 0) *(s32 *)(b + r * 4 + 0x164) -= *(s32 *)(b + 0x2148);
    s32 nh = *(s32 *)(q + 0x2d8c) + *(s32 *)(b + 0x215c);
    *(s32 *)(q + 0x2d8c) = nh;
    if (nh < 0) *(s32 *)(q + 0x2d8c) = 0;
    else if ((u32)nh > *(u32 *)(b + r * 0xc0 + 0x2d90)) *(u32 *)(q + 0x2d8c) = *(u32 *)(b + r * 0xc0 + 0x2d90);
    fn_803BD374(a, b, r);
    return 0;
}
s32 fn_803CBF18(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 n = fn_803D6E6C(b);
    *(u32 *)(b + 0x3044) = *(u32 *)(b + 0x124);
    struct BF_213C { u32 hi : 17; u32 f14 : 1; u32 mid : 13; u32 f0 : 1; };
    ((BF_213C *)(b + 0x213c))->f0 = 0;
    ((BF_213C *)(b + 0x213c))->f14 = 0;
    if (n == 0) {
        *(u32 *)(b + 0x6c) = fn_803BC964(a, b, *(u32 *)(b + 0x64), (u16)*(u32 *)(b + 0x3044), 1, 0);
        fn_803BCE18(a, b, *(u32 *)(b + 0x64), (u16)*(u32 *)(b + 0x124));
        *(u32 *)(b + *(u32 *)(b + 0x64) * 16 + 0x21ac) = *(u32 *)(b + 0x6c);
    }
    if (*(s32 *)(b + 0x6c) == 0xff) {
        *(u32 *)(b + 0xc) = 0x26;
        fn_803BA9D4(b, 2, 0x119);
    } else {
        fn_803BA9D4(b, 1, *(u32 *)(b + 0x3044));
    }
    *(u32 *)lbl_8048CDE8 = *(u32 *)(b + 0x64);
    *(u32 *)(lbl_8048CDE8 + 4) = *(u32 *)(b + 0x3044);
    fn_8016FA4C(0x19, lbl_8048CDE8);
    return 0;
}
struct BF_2DC8b { u32 t : 3; u32 rest : 29; };
s32 fn_803CF758(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    s32 j = fn_803BE72C(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2d40, *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c));
    u8 *q = b + *(u32 *)(b + 0x6c) * 0xc0;
    u16 m;
    if (*(u16 *)(q + 0x2de8) == 0 && j != 4 && q[j + 0x2d6c] != 0 && (m = *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c)) != 0) {
        *(u32 *)(b + 0x124) = m;
        *(u16 *)(q + 0x2de8) = m;
        ((BF_2DC8b *)(b + *(u32 *)(b + 0x6c) * 0xc0 + 0x2dc8))->t = (s32)DS_Rand() % 4 + 3;
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803C9528(u8 *a, u8 *b) {
    s32 n = fn_803AC860(a);
    (*(u32 *)(b + 0xb4))++;
    s32 i;
    switch (fn_803D6E6C(b)) {
    case 0:
    default:
        for (i = 0; i < n; i++) {
            fn_803AF780(a, i);
            fn_803ADE5C(a, i);
        }
        break;
    case 3:
        break;
    case 4:
        for (i = 0; i < n; i++) {
            if (((u8 *)fn_803AC850(a, i))[0x185] & 1) {
                fn_803AF780(a, i);
                fn_803ADE5C(a, i);
            }
        }
        break;
    }
    return 0;
}

}
#pragma pop

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803D1A58(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    if (b[0x3120] == 0) {
        u8 v = (s32)DS_Rand() % 100;
        b[0x3120] = v;
        if (v < 5) {
            *(u32 *)(b + 0x2154) = 10;
            b[0x3120] = 4;
        } else if (v < 15) {
            *(u32 *)(b + 0x2154) = 30;
            b[0x3120] = 5;
        } else if (v < 35) {
            *(u32 *)(b + 0x2154) = 50;
            b[0x3120] = 6;
        } else if (v < 65) {
            *(u32 *)(b + 0x2154) = 70;
            b[0x3120] = 7;
        } else if (v < 85) {
            *(u32 *)(b + 0x2154) = 90;
            b[0x3120] = 8;
        } else if (v < 95) {
            *(u32 *)(b + 0x2154) = 110;
            b[0x3120] = 9;
        } else {
            *(u32 *)(b + 0x2154) = 150;
            b[0x3120] = 10;
        }
    }
    *(u32 *)(b + 0x130) = b[0x3120];
    return 0;
}
s32 fn_803CB438(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    s32 w = fn_803D6E6C(b);
    u32 x = fn_803D6E6C(b);
    u32 y = fn_803D6E6C(b);
    u16 m;
    if (w == 0xff) m = *(u32 *)(b + 0x124);
    else m = *(u32 *)(b + 0x3044);
    u32 rx = fn_803D803C(a, b, x);
    u32 ry = fn_803D803C(a, b, y);
    if ((!(*(u32 *)(b + 0x213c) & 0x4000) && fn_803ADBB4(a) == 1) || m == 0x90) {
        *(u32 *)(b + 0x213c) |= 0x4000;
        fn_803B0FF0(a, b, m, rx, ry);
        *(u32 *)lbl_8048CDE8 = ry;
        *(u32 *)(lbl_8048CDE8 + 4) = rx;
        *(u32 *)(lbl_8048CDE8 + 8) = m;
        fn_8016FA4C(0x10, lbl_8048CDE8);
    }
    return 0;
}
s32 fn_803D02D8(u8 *a, u8 *b) {
    (*(u32 *)(b + 0xb4))++;
    u32 n = fn_803D6E6C(b);
    u32 i6c = *(u32 *)(b + 0x6c);
    u16 mv = *(u16 *)(b + i6c * 2 + 0x307c);
    if (mv) {
        s32 j = fn_803BE72C(b + i6c * 0xc0 + 0x2d40, mv);
        u8 pp;
        if (j == 4 || (pp = b[*(u32 *)(b + 0x6c) * 0xc0 + j + 0x2d6c]) == 0) {
            *(u32 *)(b + 0xb4) += n;
        } else {
            s32 d = 4;
            if (pp < 4) d = pp;
            *(u32 *)(b + 0x124) = *(u16 *)(b + *(u32 *)(b + 0x6c) * 2 + 0x307c);
            *(s32 *)(b + 0x130) = d;
            b[*(u32 *)(b + 0x6c) * 0xc0 + j + 0x2d6c] -= d;
            fn_803BD374(a, b, *(u32 *)(b + 0x6c));
        }
    } else {
        *(u32 *)(b + 0xb4) += n;
    }
    return 0;
}

}
#pragma pop

extern "C" {

struct BF_2DCC { u32 hi : 23; u32 k : 4; u32 lo : 5; };
void fn_803C5828(u8 *a, u8 *b) {
    if (fn_803C40BC(b, *(u32 *)(b + 0x64)) == 0x68) {
        u32 i = *(u32 *)(b + 0x64);
        u8 *q = b + i * 0xc0;
        u32 v = *(u32 *)(q + 0x2db0);
        if (!(v & 0xc00) && !(v & 0x70) && !(*(u32 *)(b + 0x213c) & 0x200) && !(v & 0x1000)) {
            if (*(u32 *)(b + 0x3040) == *(u16 *)(b + i * 2 + 0x30dc)) {
                BF_2DCC *f = (BF_2DCC *)(q + 0x2dcc);
                if (f->k < 10) f->k++;
            } else {
                ((BF_2DCC *)(q + 0x2dcc))->k = 0;
                *(u16 *)(b + *(u32 *)(b + 0x64) * 2 + 0x30dc) = *(u32 *)(b + 0x3040);
            }
        }
    } else {
        ((BF_2DCC *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc))->k = 0;
    }
}
void fn_803C590C(u8 *a, u8 *b) {
    if (fn_803C40BC(b, *(u32 *)(b + 0x64)) == 0x68) {
        if (*(u32 *)(b + 0x216c) & 0x801fda49) {
            u32 i = *(u32 *)(b + 0x64);
            if (*(u32 *)(b + 0x3040) == *(u16 *)(b + i * 2 + 0x30dc)) {
                u8 *q = b + i * 0xc0;
                BF_2DCC *f = (BF_2DCC *)(q + 0x2dcc);
                u32 k = f->k;
                if (k && !((*(u32 *)(b + i * 0x1c + 0x2d4) >> 23) & 7)) {
                    u32 v = *(u32 *)(q + 0x2db0);
                    if (!(v & 0xc00) && !(v & 0x70) && !(*(u32 *)(b + 0x213c) & 0x200) && !(v & 0x1000)) f->k = k - 1;
                }
            }
        }
    } else {
        ((BF_2DCC *)(b + *(u32 *)(b + 0x64) * 0xc0 + 0x2dcc))->k = 0;
    }
}

}

#pragma push
#pragma optimize_for_size on
#pragma dont_inline on
extern "C" {

s32 fn_803C8F1C(u8 *b, u32 x, s32 m, s32 v, s32 f, u32 *p) {
    u32 fl = *(u32 *)(b + 0x213c);
    if (!(fl & 0x800) && !(fl & 0x8000) && v != 0) v = fn_803C0B68(v * m, 10);
    switch (m) {
    case 0:
        *p = (*p | 8) & ~6;
        break;
    case 5:
        if (f) {
            if (*p & 2) *p &= ~2;
            else *p |= 4;
        }
        break;
    case 0x14:
        if (f) {
            if (*p & 4) *p &= ~4;
            else *p |= 2;
        }
        break;
    }
    return v;
}

}
#pragma pop
