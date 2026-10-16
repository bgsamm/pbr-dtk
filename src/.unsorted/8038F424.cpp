#include ".unsorted/8038F424.hpp"

extern "C" {

DataHdr **fn_8038F600(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8038F6A0(h, d);
    }
    return h;
}

DataHdr **fn_8038F640(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_8038F804((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
}

s32 fn_8038F6A0(DataHdr **h, DataHdr *d) {
    if (d == 0) {
        return -1;
    }
    if (*h != 0) {
        return -2;
    }
    if (d->ver != 4) {
        return -3;
    }
    if (d->relocated == 0) {
        d->off8 += (u32)d;
        d->off10 += (u32)d;
        d->relocs += (u32)d;
        u32 n = d->nrelocs;
        if (d->off20 != 0) {
            d->off20 += (u32)d;
        }
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

u8 *fn_8038F838(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u32 fn_8038F86C(u8 **h, s32 i) {
    u8 *p = fn_8038F838(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

DataHdr **fn_8038F8A0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8038F940(h, d);
    }
    return h;
}

DataHdr **fn_8038F8E0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_8038FAA4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

DataHdr **fn_8038FAD8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8038FB78(h, d);
    }
    return h;
}

DataHdr **fn_8038FB18(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_8038FCDC((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_8038FD10(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x28;
}

u16 fn_8038FD44(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_8038FD78(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x8);
    }
    return 0;
}

u8 fn_8038FDAC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x9);
    }
    return 0;
}

u8 fn_8038FDE0(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0xa);
    }
    return 0;
}

u8 fn_8038FE14(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0xb);
    }
    return 0;
}

u8 fn_8038FE48(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0xc);
    }
    return 0;
}

u8 fn_8038FE7C(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0xd);
    }
    return 0;
}

u32 fn_8038FEB0(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return (*(u16 *)(p + 0xe) >> 11) & 0x1f;
    }
    return 0;
}

u32 fn_8038FEE8(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return (*(u16 *)(p + 0xe) >> 10) & 0x1;
    }
    return 0;
}

u32 fn_8038FF20(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return (*(u16 *)(p + 0xe) >> 9) & 0x1;
    }
    return 0;
}

u32 fn_8038FF58(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return (*(u16 *)(p + 0xe) >> 5) & 0xf;
    }
    return 0;
}

u32 fn_8038FF90(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u16 *)(p + 0xe) & 0x1f;
    }
    return 0;
}

u8 fn_8038FFC8(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x10);
    }
    return 0;
}

u8 fn_8038FFFC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x11);
    }
    return 0;
}

u8 fn_80390030(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x12);
    }
    return 0;
}

u8 fn_80390064(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u8 *)(p + 0x13);
    }
    return 0;
}

u8 fn_80390098(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8038FD10(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x14) {
        return 0;
    }
    return ((u8 *)(p + 0x14))[j];
}

u16 fn_803900EC(u8 **h, s32 i) {
    u8 *p = fn_8038FD10(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

DataHdr **fn_80390120(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803901C0(h, d);
    }
    return h;
}

DataHdr **fn_80390160(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80390324((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80390358(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u16 fn_8039038C(u8 **h, s32 i) {
    u8 *p = fn_80390358(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u16 fn_803903C0(u8 **h, s32 i) {
    u8 *p = fn_80390358(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

DataHdr **fn_803903F4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80390494(h, d);
    }
    return h;
}

DataHdr **fn_80390434(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803905F8((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_8039062C(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x12;
}

u8 fn_80390660(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8039062C(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x12) {
        return 0;
    }
    return *(u8 *)(p + j * 1 + 0x0);
}

DataHdr **fn_803906B0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80390750(h, d);
    }
    return h;
}

DataHdr **fn_803906F0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803908B4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803908E8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x8;
}

u16 fn_8039091C(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) {
        return *(u16 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80390950(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) {
        return (*(u32 *)(p + 0x4) >> 1) & 0x7fff;
    }
    return 0;
}

u32 fn_80390988(u8 **h, s32 i) {
    u8 *p = fn_803908E8(h, i);
    if (p) {
        return *(u32 *)(p + 0x4) & 0x1;
    }
    return 0;
}

DataHdr **fn_803909C0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80390A60(h, d);
    }
    return h;
}

DataHdr **fn_80390A00(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80390BC4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80390BF8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x76;
}

u32 fn_80390C2C(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80390C48(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_80390C7C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6a);
    }
    return 0;
}

u8 fn_80390CB0(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6b);
    }
    return 0;
}

u8 fn_80390CE4(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6c);
    }
    return 0;
}

u8 fn_80390D18(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6d);
    }
    return 0;
}

u8 fn_80390D4C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6e);
    }
    return 0;
}

u8 fn_80390D80(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x6f);
    }
    return 0;
}

u8 fn_80390DB4(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x70);
    }
    return 0;
}

u8 fn_80390DE8(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x71);
    }
    return 0;
}

u8 fn_80390E1C(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x72);
    }
    return 0;
}

u8 fn_80390E50(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x73);
    }
    return 0;
}

u16 fn_80390E84(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80390BF8(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x34) {
        return 0;
    }
    return ((u16 *)(p + 0x2))[j];
}

u8 fn_80390EDC(u8 **h, s32 i) {
    u8 *p = fn_80390BF8(h, i);
    if (p) {
        return *(u8 *)(p + 0x74);
    }
    return 0;
}

DataHdr **fn_80390F10(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80390FB0(h, d);
    }
    return h;
}

DataHdr **fn_80390F50(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80391114((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80391148(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x48;
}

u32 fn_8039117C(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80391198(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u16 *)(p + 0x14);
    }
    return 0;
}

u8 fn_803911CC(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u8 *)(p + 0x18);
    }
    return 0;
}

u32 fn_80391200(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u32 *)(p + 0x0) >> 29;
    }
    return 0;
}

u32 fn_80391238(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return (*(u32 *)(p + 0x0) >> 26) & 0x1;
    }
    return 0;
}

u8 fn_80391270(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80391148(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x19) {
        return 0;
    }
    return ((u8 *)(p + 0x19))[j];
}

u8 fn_803912C4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80391148(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x16) {
        return 0;
    }
    return ((u8 *)(p + 0x32))[j];
}

u32 fn_80391318(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_8039134C(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_80391380(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

f32 fn_803913B4(u8 **h, s32 i) {
    u8 *p = fn_80391148(h, i);
    if (p) {
        return *(f32 *)(p + 0x10);
    }
    return lbl_80642F08;
}

DataHdr **fn_803913E8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80391488(h, d);
    }
    return h;
}

DataHdr **fn_80391428(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803915EC((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

DataHdr **fn_80391620(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803916C0(h, d);
    }
    return h;
}

DataHdr **fn_80391660(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80391824((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80391858(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x34;
}

u8 fn_8039188C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x1e);
    }
    return 0;
}

u8 fn_803918C0(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x1f);
    }
    return 0;
}

u8 fn_803918F4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x20);
    }
    return 0;
}

u8 fn_80391928(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x21);
    }
    return 0;
}

u8 fn_8039195C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x22);
    }
    return 0;
}

u8 fn_80391990(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x23);
    }
    return 0;
}

u8 fn_803919C4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x24);
    }
    return 0;
}

u8 fn_803919F8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x25);
    }
    return 0;
}

u8 fn_80391A2C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x26);
    }
    return 0;
}

u8 fn_80391A60(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x27);
    }
    return 0;
}

u32 fn_80391A94(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 14) & 0x3;
    }
    return 0;
}

u32 fn_80391ACC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 12) & 0x3;
    }
    return 0;
}

u32 fn_80391B04(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 10) & 0x3;
    }
    return 0;
}

u32 fn_80391B3C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 8) & 0x3;
    }
    return 0;
}

u32 fn_80391B74(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 6) & 0x3;
    }
    return 0;
}

u32 fn_80391BAC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u16 *)(p + 0x28) >> 4) & 0x3;
    }
    return 0;
}

u16 fn_80391BE4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x10);
    }
    return 0;
}

u16 fn_80391C18(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x12);
    }
    return 0;
}

u8 fn_80391C4C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2a);
    }
    return 0;
}

u8 fn_80391C80(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2b);
    }
    return 0;
}

u8 fn_80391CB4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2c);
    }
    return 0;
}

u8 fn_80391CE8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2d);
    }
    return 0;
}

u8 fn_80391D1C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2e);
    }
    return 0;
}

u8 fn_80391D50(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x2f);
    }
    return 0;
}

u8 fn_80391D84(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x30);
    }
    return 0;
}

u8 fn_80391DB8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x31);
    }
    return 0;
}

u16 fn_80391DEC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x16);
    }
    return 0;
}

u8 fn_80391E20(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x32);
    }
    return 0;
}

u32 fn_80391E54(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return (*(u8 *)(p + 0x33) >> 1) & 0x7f;
    }
    return 0;
}

u32 fn_80391E8C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u8 *)(p + 0x33) & 0x1;
    }
    return 0;
}

u32 fn_80391EC4(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80391EF8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80391F2C(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_80391F60(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u16 fn_80391F94(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x18);
    }
    return 0;
}

u16 fn_80391FC8(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x1a);
    }
    return 0;
}

u16 fn_80391FFC(u8 **h, s32 i) {
    u8 *p = fn_80391858(h, i);
    if (p) {
        return *(u16 *)(p + 0x1c);
    }
    return 0;
}

DataHdr **fn_80392030(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803920D0(h, d);
    }
    return h;
}

DataHdr **fn_80392070(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80392234((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80392268(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x2a;
}

u16 fn_8039229C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80392268(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x7) {
        return 0;
    }
    return *(u16 *)(p + j * 6 + 0x4);
}

DataHdr **fn_803922F4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80392394(h, d);
    }
    return h;
}

DataHdr **fn_80392334(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803924F8((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_8039252C(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x194;
}

u32 fn_80392560(u8 **h, s32 i, u32 j) {
    u8 *p = fn_8039252C(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x65) {
        return 0;
    }
    return *(u32 *)(p + j * 4 + 0x0);
}

DataHdr **fn_803925B4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80392654(h, d);
    }
    return h;
}

DataHdr **fn_803925F4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803927B8((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803927EC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x50;
}

u8 fn_80392820(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803927EC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x14) {
        return 0;
    }
    return *(u8 *)(p + j * 4 + 0x2);
}

u16 fn_80392878(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803927EC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x14) {
        return 0;
    }
    return *(u16 *)(p + j * 4 + 0x0);
}

DataHdr **fn_803928CC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8039296C(h, d);
    }
    return h;
}

DataHdr **fn_8039290C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80392AD0((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80392B04(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x18;
}

u16 fn_80392B38(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_80392B6C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0xe);
    }
    return 0;
}

u8 fn_80392BA0(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0xf);
    }
    return 0;
}

u8 fn_80392BD4(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x10);
    }
    return 0;
}

u8 fn_80392C08(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x11);
    }
    return 0;
}

u8 fn_80392C3C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x12);
    }
    return 0;
}

u8 fn_80392C70(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x13);
    }
    return 0;
}

u16 fn_80392CA4(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

u8 fn_80392CD8(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x14);
    }
    return 0;
}

u8 fn_80392D0C(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x15);
    }
    return 0;
}

u16 fn_80392D40(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u16 *)(p + 0x8);
    }
    return 0;
}

u16 fn_80392D74(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u16 *)(p + 0xa);
    }
    return 0;
}

u16 fn_80392DA8(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u16 *)(p + 0xc);
    }
    return 0;
}

u8 fn_80392DDC(u8 **h, s32 i) {
    u8 *p = fn_80392B04(h, i);
    if (p) {
        return *(u8 *)(p + 0x16);
    }
    return 0;
}

DataHdr **fn_80392E10(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80392E50(h, d);
    }
    return h;
}

u8 *fn_80392FB4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x8;
}

s16 fn_80392FE8(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) {
        return *(s16 *)(p + 0x0);
    }
    return 0;
}

s16 fn_8039301C(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) {
        return *(s16 *)(p + 0x2);
    }
    return 0;
}

u8 fn_80393050(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) {
        return *(u8 *)(p + 0x4);
    }
    return 0;
}

u8 fn_80393084(u8 **h, s32 i) {
    u8 *p = fn_80392FB4(h, i);
    if (p) {
        return *(u8 *)(p + 0x6);
    }
    return 0;
}

DataHdr **fn_803930B8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803930F8(h, d);
    }
    return h;
}

DataHdr **fn_8039325C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8039329C(h, d);
    }
    return h;
}

u8 *fn_80393400(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x38;
}

u8 fn_80393434(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(u8 *)(p + 0x34);
    }
    return 0;
}

f32 fn_80393468(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x0);
    }
    return lbl_80642F10;
}

f32 fn_8039349C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x4);
    }
    return lbl_80642F10;
}

u8 fn_803934D0(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(u8 *)(p + 0x35);
    }
    return 0;
}

f32 fn_80393504(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x8);
    }
    return lbl_80642F10;
}

f32 fn_80393538(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0xc);
    }
    return lbl_80642F10;
}

f32 fn_8039356C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x10);
    }
    return lbl_80642F10;
}

f32 fn_803935A0(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x14);
    }
    return lbl_80642F10;
}

f32 fn_803935D4(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x18);
    }
    return lbl_80642F10;
}

f32 fn_80393608(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x1c);
    }
    return lbl_80642F10;
}

f32 fn_8039363C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x20);
    }
    return lbl_80642F10;
}

f32 fn_80393670(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x24);
    }
    return lbl_80642F10;
}

f32 fn_803936A4(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x28);
    }
    return lbl_80642F10;
}

f32 fn_803936D8(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x2c);
    }
    return lbl_80642F10;
}

f32 fn_8039370C(u8 **h, s32 i) {
    u8 *p = fn_80393400(h, i);
    if (p) {
        return *(f32 *)(p + 0x30);
    }
    return lbl_80642F10;
}

DataHdr **fn_80393740(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80393780(h, d);
    }
    return h;
}

u8 *fn_803938E4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x46;
}

u8 fn_80393918(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x2a);
    }
    return 0;
}

s16 fn_8039394C(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(s16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_80393980(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x2b);
    }
    return 0;
}

u8 fn_803939B4(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x2c);
    }
    return 0;
}

s16 fn_803939E8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((s16 *)(p + 0x2))[j];
}

u8 fn_80393A40(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x2d);
    }
    return 0;
}

u8 fn_80393A74(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x2e))[j];
}

s16 fn_80393AC8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

u8 fn_80393B20(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x32);
    }
    return 0;
}

u8 fn_80393B54(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x33))[j];
}

s16 fn_80393BA8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((s16 *)(p + 0x12))[j];
}

u8 fn_80393C00(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x37);
    }
    return 0;
}

u8 fn_80393C34(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x38))[j];
}

s16 fn_80393C88(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((s16 *)(p + 0x1a))[j];
}

u8 fn_80393CE0(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x3c);
    }
    return 0;
}

u8 fn_80393D14(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x3d))[j];
}

s16 fn_80393D68(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((s16 *)(p + 0x22))[j];
}

u8 fn_80393DC0(u8 **h, s32 i) {
    u8 *p = fn_803938E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x41);
    }
    return 0;
}

u8 fn_80393DF4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803938E4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x42))[j];
}

DataHdr **fn_80393E48(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80393E88(h, d);
    }
    return h;
}

u8 *fn_80393FEC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_80394020(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80393FEC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_80394074(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80393FEC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_803940CC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8039410C(h, d);
    }
    return h;
}

u8 *fn_80394270(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_803942A4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394270(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_803942F8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394270(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394350(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80394390(h, d);
    }
    return h;
}

u8 *fn_803944F4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_80394528(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803944F4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_8039457C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803944F4(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_803945D4(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80394614(h, d);
    }
    return h;
}

u8 *fn_80394778(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_803947AC(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394778(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_80394800(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394778(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394858(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80394898(h, d);
    }
    return h;
}

u8 *fn_803949FC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_80394A30(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803949FC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_80394A84(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803949FC(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394ADC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80394B1C(h, d);
    }
    return h;
}

u8 *fn_80394C80(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x14;
}

s16 fn_80394CB4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394C80(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

s16 fn_80394D08(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394C80(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)(p + 0xa))[j];
}

DataHdr **fn_80394D60(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80394DA0(h, d);
    }
    return h;
}

u8 *fn_80394F04(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xa;
}

s16 fn_80394F38(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80394F04(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x5) {
        return 0;
    }
    return ((s16 *)p)[j];
}

DataHdr **fn_80394F8C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8039502C(h, d);
    }
    return h;
}

DataHdr **fn_80394FCC(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80395190((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803951C4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x3c;
}

u32 fn_803951F8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x2e) >> 4) & 0xf;
    }
    return 0;
}

u32 fn_80395230(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x2f) >> 5) & 0x7;
    }
    return 0;
}

u32 fn_80395268(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x2f) >> 2) & 0x7;
    }
    return 0;
}

u32 fn_803952A0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x30) >> 5) & 0x7;
    }
    return 0;
}

u32 fn_803952D8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x30) >> 2) & 0x7;
    }
    return 0;
}

u32 fn_80395310(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x31) >> 5) & 0x7;
    }
    return 0;
}

u32 fn_80395348(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x31) >> 4) & 0x1;
    }
    return 0;
}

u32 fn_80395380(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x31) >> 3) & 0x1;
    }
    return 0;
}

u32 fn_803953B8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x32) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_803953F0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x32) >> 2) & 0x1;
    }
    return 0;
}

u32 fn_80395428(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_8039545C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80395490(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x33) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_803954C8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_803954FC(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u32 fn_80395530(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x34) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_80395568(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x10);
    }
    return 0;
}

u32 fn_8039559C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x14);
    }
    return 0;
}

u32 fn_803955D0(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x35) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_80395608(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x18);
    }
    return 0;
}

u32 fn_8039563C(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x1c);
    }
    return 0;
}

u32 fn_80395670(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x36) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_803956A8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x20);
    }
    return 0;
}

u32 fn_803956DC(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u32 *)(p + 0x24);
    }
    return 0;
}

u32 fn_80395710(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x37) >> 3) & 0x1f;
    }
    return 0;
}

u32 fn_80395748(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return (*(u8 *)(p + 0x38) >> 3) & 0x1f;
    }
    return 0;
}

u16 fn_80395780(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u16 *)(p + 0x28);
    }
    return 0;
}

u16 fn_803957B4(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u16 *)(p + 0x2a);
    }
    return 0;
}

u16 fn_803957E8(u8 **h, s32 i) {
    u8 *p = fn_803951C4(h, i);
    if (p) {
        return *(u16 *)(p + 0x2c);
    }
    return 0;
}

DataHdr **fn_8039581C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803958BC(h, d);
    }
    return h;
}

DataHdr **fn_8039585C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80395A20((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80395A54(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x6;
}

u32 fn_80395A88(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80395AA4(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80395AD8(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

u16 fn_80395B0C(u8 **h, s32 i) {
    u8 *p = fn_80395A54(h, i);
    if (p) {
        return *(u16 *)(p + 0x4);
    }
    return 0;
}

void fn_80395B40(u8 **h, s32 i, u16 v) {
    u8 *p = fn_80395A54(h, i);
    if (p) {
        *(u16 *)(p + 4) = v;
    }
}

DataHdr **fn_80395B78(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80395C18(h, d);
    }
    return h;
}

DataHdr **fn_80395BB8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80395D7C((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80395DB0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x54;
}

u32 fn_80395DE4(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80395E00(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return *(u32 *)(p + 0x0) >> 31;
    }
    return 0;
}

u32 fn_80395E38(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return (*(u32 *)(p + 0x0) >> 28) & 0x7;
    }
    return 0;
}

u32 fn_80395E70(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80395EA4(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_80395ED8(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u32 fn_80395F0C(u8 **h, s32 i) {
    u8 *p = fn_80395DB0(h, i);
    if (p) {
        return *(u32 *)(p + 0x10);
    }
    return 0;
}

u8 fn_80395F40(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x14) {
        return 0;
    }
    return ((u8 *)(p + 0x14))[j];
}

u8 fn_80395F94(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x28))[j];
}

u8 fn_80395FE8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x8) {
        return 0;
    }
    return ((u8 *)(p + 0x2c))[j];
}

u8 fn_8039603C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x14) {
        return 0;
    }
    return ((u8 *)(p + 0x34))[j];
}

u8 fn_80396090(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u8 *)(p + 0x48))[j];
}

u8 fn_803960E4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80395DB0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x8) {
        return 0;
    }
    return ((u8 *)(p + 0x4c))[j];
}

DataHdr **fn_80396138(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803961D8(h, d);
    }
    return h;
}

DataHdr **fn_80396178(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_8039633C((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80396370(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u16 fn_803963A4(u8 **h, s32 i) {
    u8 *p = fn_80396370(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u16 fn_803963D8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80396370(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x6) {
        return 0;
    }
    return ((u16 *)(p + 0x2))[j];
}

DataHdr **fn_80396430(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803964D0(h, d);
    }
    return h;
}

DataHdr **fn_80396470(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80396634((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80396668(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u32 fn_8039669C(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u8 fn_803966B8(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) {
        return *(u8 *)(p + 0x8);
    }
    return 0;
}

u32 fn_803966EC(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80396720(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

void fn_80396754(u8 **h, s32 i, u32 v) {
    u8 *p = fn_80396668(h, i);
    if (p) {
        *(u32 *)(p + 4) = v;
    }
}

u8 fn_8039678C(u8 **h, s32 i) {
    u8 *p = fn_80396668(h, i);
    if (p) {
        return *(u8 *)(p + 0x9);
    }
    return 0;
}

DataHdr **fn_803967C0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80396860(h, d);
    }
    return h;
}

DataHdr **fn_80396800(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803969C4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803969F8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u16 fn_80396A2C(u8 **h, s32 i) {
    u8 *p = fn_803969F8(h, i);
    if (p) {
        return *(u16 *)(p + 0x4);
    }
    return 0;
}

u16 fn_80396A60(u8 **h, s32 i) {
    u8 *p = fn_803969F8(h, i);
    if (p) {
        return *(u16 *)(p + 0x6);
    }
    return 0;
}

DataHdr **fn_80396A94(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80396B34(h, d);
    }
    return h;
}

DataHdr **fn_80396AD4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80396C98((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80396CCC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x20;
}

u32 fn_80396D00(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80396D34(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80396D68(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_80396D9C(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u32 fn_80396DD0(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x10);
    }
    return 0;
}

u32 fn_80396E04(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x14);
    }
    return 0;
}

u32 fn_80396E38(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x18);
    }
    return 0;
}

u32 fn_80396E6C(u8 **h, s32 i) {
    u8 *p = fn_80396CCC(h, i);
    if (p) {
        return *(u32 *)(p + 0x1c);
    }
    return 0;
}

DataHdr **fn_80396EA0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80396F40(h, d);
    }
    return h;
}

DataHdr **fn_80396EE0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803970A4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803970D8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x2c;
}

u32 fn_8039710C(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80397140(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80397174(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_803971A8(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u32 fn_803971DC(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x10);
    }
    return 0;
}

u32 fn_80397210(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x14);
    }
    return 0;
}

u32 fn_80397244(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x18);
    }
    return 0;
}

u8 fn_80397278(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u8 *)(p + 0x28);
    }
    return 0;
}

f32 fn_803972AC(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(f32 *)(p + 0x1c);
    }
    return lbl_80642F18;
}

f32 fn_803972E0(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(f32 *)(p + 0x20);
    }
    return lbl_80642F18;
}

u32 fn_80397314(u8 **h, s32 i) {
    u8 *p = fn_803970D8(h, i);
    if (p) {
        return *(u32 *)(p + 0x24);
    }
    return 0;
}

DataHdr **fn_80397348(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_803973E8(h, d);
    }
    return h;
}

DataHdr **fn_80397388(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_8039754C((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80397580(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x6;
}

u16 fn_803975B4(u8 **h, s32 i) {
    u8 *p = fn_80397580(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_803975E8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397580(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x3) {
        return 0;
    }
    return ((u8 *)(p + 0x2))[j];
}

u8 fn_8039763C(u8 **h, s32 i) {
    u8 *p = fn_80397580(h, i);
    if (p) {
        return *(u8 *)(p + 0x5);
    }
    return 0;
}

DataHdr **fn_80397670(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80397710(h, d);
    }
    return h;
}

DataHdr **fn_803976B0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80397874((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803978A8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u16 fn_803978DC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80397910(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

u16 fn_80397944(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0x4);
    }
    return 0;
}

u16 fn_80397978(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0x6);
    }
    return 0;
}

u16 fn_803979AC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0x8);
    }
    return 0;
}

u16 fn_803979E0(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0xa);
    }
    return 0;
}

u32 fn_80397A14(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 15) & 0x1;
    }
    return 0;
}

u32 fn_80397A4C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 14) & 0x1;
    }
    return 0;
}

u32 fn_80397A84(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 13) & 0x1;
    }
    return 0;
}

u32 fn_80397ABC(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 12) & 0x1;
    }
    return 0;
}

u32 fn_80397AF4(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 11) & 0x1;
    }
    return 0;
}

u32 fn_80397B2C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 10) & 0x1;
    }
    return 0;
}

u32 fn_80397B64(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 9) & 0x1;
    }
    return 0;
}

u32 fn_80397B9C(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return (*(u16 *)(p + 0xc) >> 7) & 0x3;
    }
    return 0;
}

u32 fn_80397BD4(u8 **h, s32 i) {
    u8 *p = fn_803978A8(h, i);
    if (p) {
        return *(u16 *)(p + 0xc) & 0x7f;
    }
    return 0;
}

DataHdr **fn_80397C0C(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80397CAC(h, d);
    }
    return h;
}

DataHdr **fn_80397C4C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80397E10((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80397E44(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x5c;
}

u16 fn_80397E78(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u16 *)(p + 0x30);
    }
    return 0;
}

u8 fn_80397EAC(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u8 *)(p + 0x4a);
    }
    return 0;
}

u8 fn_80397EE0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return ((u8 *)(p + 0x4b))[j];
}

u16 fn_80397F34(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return ((u16 *)(p + 0x36))[j];
}

u8 fn_80397F8C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return ((u8 *)(p + 0x4d))[j];
}

u8 fn_80397FE0(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u8 *)(p + 0x4f);
    }
    return 0;
}

u8 fn_80398014(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x3) {
        return 0;
    }
    return ((u8 *)(p + 0x51))[j];
}

u16 fn_80398068(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u16 *)(p + 0x3a);
    }
    return 0;
}

u8 fn_8039809C(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u8 *)(p + 0x54);
    }
    return 0;
}

u8 fn_803980D0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u8 *)(p + j * 16 + 0xc);
}

u32 fn_80398128(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 16 + 0x0);
}

u32 fn_8039817C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 16 + 0x4);
}

u32 fn_803981D4(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 16 + 0x8);
}

u32 fn_8039822C(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u32 *)(p + 0x20))[j];
}

u8 fn_80398284(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u8 *)(p + 0x55);
    }
    return 0;
}

u8 fn_803982B8(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u8 *)(p + 0x56);
    }
    return 0;
}

u8 fn_803982EC(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80397E44(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return ((u8 *)(p + 0x57))[j];
}

u16 fn_80398340(u8 **h, s32 i) {
    u8 *p = fn_80397E44(h, i);
    if (p) {
        return *(u16 *)(p + 0x48);
    }
    return 0;
}

DataHdr **fn_80398374(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80398414(h, d);
    }
    return h;
}

DataHdr **fn_803983B4(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80398578((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803985AC(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x10;
}

u32 fn_803985E0(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_80398614(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80398648(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_8039867C(u8 **h, s32 i) {
    u8 *p = fn_803985AC(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

DataHdr **fn_803986B0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80398750(h, d);
    }
    return h;
}

DataHdr **fn_803986F0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803988B4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803988E8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x4;
}

u32 fn_8039891C(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80398938(u8 **h, s32 i) {
    u8 *p = fn_803988E8(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_8039896C(u8 **h, s32 i) {
    u8 *p = fn_803988E8(h, i);
    if (p) {
        return *(u8 *)(p + 0x2);
    }
    return 0;
}

DataHdr **fn_803989A0(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80398A40(h, d);
    }
    return h;
}

DataHdr **fn_803989E0(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80398BA4((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80398BD8(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xc;
}

u32 fn_80398C0C(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80398C28(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80398C5C(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) {
        return *(u16 *)(p + 0x4);
    }
    return 0;
}

u16 fn_80398C90(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) {
        return *(u16 *)(p + 0x6);
    }
    return 0;
}

u16 fn_80398CC4(u8 **h, s32 i) {
    u8 *p = fn_80398BD8(h, i);
    if (p) {
        return *(u16 *)(p + 0x8);
    }
    return 0;
}

DataHdr **fn_80398CF8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80398D98(h, d);
    }
    return h;
}

DataHdr **fn_80398D38(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80398EFC((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80398F30(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xba;
}

u32 fn_80398F64(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u16 fn_80398F80(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) {
        return *(u16 *)(p + 0x0);
    }
    return 0;
}

u8 fn_80398FB4(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) {
        return *(u8 *)(p + 0xb8);
    }
    return 0;
}

u8 fn_80398FE8(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) {
        return *(u8 *)(p + 0xb9);
    }
    return 0;
}

u16 fn_8039901C(u8 **h, s32 i) {
    u8 *p = fn_80398F30(h, i);
    if (p) {
        return *(u16 *)(p + 0x2);
    }
    return 0;
}

u16 fn_80399050(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x10) {
        return 0;
    }
    return ((u16 *)(p + 0x8))[j];
}

u16 fn_803990A8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x10) {
        return 0;
    }
    return ((u16 *)(p + 0x28))[j];
}

u16 fn_80399100(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x10) {
        return 0;
    }
    return ((u16 *)(p + 0x48))[j];
}

u16 fn_80399158(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x10) {
        return 0;
    }
    return ((u16 *)(p + 0x68))[j];
}

u16 fn_803991B0(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x10) {
        return 0;
    }
    return ((u16 *)(p + 0x88))[j];
}

u16 fn_80399208(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u16 *)(p + 0xa8))[j];
}

u16 fn_80399260(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80398F30(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x4) {
        return 0;
    }
    return ((u16 *)(p + 0xb0))[j];
}

DataHdr **fn_803992B8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80399358(h, d);
    }
    return h;
}

DataHdr **fn_803992F8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803994BC((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803994F0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x2c;
}

u16 fn_80399524(u8 **h, s32 i, u32 j) {
    u8 *p = fn_803994F0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x15) {
        return 0;
    }
    return *(u16 *)(p + j * 2 + 0x0);
}

u8 fn_80399578(u8 **h, s32 i) {
    u8 *p = fn_803994F0(h, i);
    if (p) {
        return *(u8 *)(p + 0x2a);
    }
    return 0;
}

DataHdr **fn_803995AC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_8039964C(h, d);
    }
    return h;
}

DataHdr **fn_803995EC(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_803997B0((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_803997E4(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x20;
}

u32 fn_80399818(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u32 fn_8039984C(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0x4);
    }
    return 0;
}

u32 fn_80399880(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0x8);
    }
    return 0;
}

u32 fn_803998B4(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0xc);
    }
    return 0;
}

u32 fn_803998E8(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0x10);
    }
    return 0;
}

u32 fn_8039991C(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u32 *)(p + 0x14);
    }
    return 0;
}

u8 fn_80399950(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x1c);
    }
    return 0;
}

u8 fn_80399984(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(u8 *)(p + 0x1d);
    }
    return 0;
}

f32 fn_803999B8(u8 **h, s32 i) {
    u8 *p = fn_803997E4(h, i);
    if (p) {
        return *(f32 *)(p + 0x18);
    }
    return lbl_80642F20;
}

DataHdr **fn_803999EC(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80399A8C(h, d);
    }
    return h;
}

DataHdr **fn_80399A2C(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80399BF0((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80399C24(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0xe;
}

u8 fn_80399C58(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399C24(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0xe) {
        return 0;
    }
    return *(u8 *)(p + j * 1 + 0x0);
}

DataHdr **fn_80399CA8(DataHdr **h, DataHdr *d) {
    *h = 0;
    if (d) {
        fn_80399D48(h, d);
    }
    return h;
}

DataHdr **fn_80399CE8(DataHdr **h, s32 del) {
    if (h) {
        if (*h) {
            fn_80399EAC((u8 **)h);
        }
        if (del > 0) {
            ::operator delete(h);
        }
    }
    return h;
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

u8 *fn_80399EE0(u8 **h, s32 i) {
    u8 *p = *h;
    if (p == 0) {
        return 0;
    }
    if (i < 0) {
        return 0;
    }
    return *(u8 **)(p + 0x10) + i * 0x1c;
}

u32 fn_80399F14(u8 **h) {
    u8 *p = *h;
    if (p) {
        return *(u32 *)(p + 0x0);
    }
    return 0;
}

u8 fn_80399F30(u8 **h, s32 i) {
    u8 *p = fn_80399EE0(h, i);
    if (p) {
        return *(u8 *)(p + 0x18);
    }
    return 0;
}

u32 fn_80399F64(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 12 + 0x0);
}

u32 fn_80399FB8(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 12 + 0x4);
}

u32 fn_8039A010(u8 **h, s32 i, u32 j) {
    u8 *p = fn_80399EE0(h, i);
    if (p == 0) {
        return 0;
    }
    if (j >= 0x2) {
        return 0;
    }
    return *(u32 *)(p + j * 12 + 0x8);
}
}
