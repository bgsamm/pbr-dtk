#include "ds/DSbridge.hpp"
#include ".unsorted/803D9EB4.hpp"

#include "common.hpp"

#include <string.h>

#pragma optimize_for_size on
#pragma dont_inline on

// Pokemon data code inherited from the Gen 4 DS games (BoxPokemon, species data,
// STRBUF string buffers, message loaders).

// Types

typedef struct BoxPokemon {
    u32 personality;
    u16 partyDecrypted : 1;
    u16 boxDecrypted : 1;
    u16 checksumFailed : 1;
    u16 unused : 13;
    u16 checksum;
    u8 data[0x80];
} BoxPokemon;

typedef struct HandleEntry {
    void *a;
    void *b;
} HandleEntry;

typedef struct MessageLoader {
    u16 type;
    u16 heapId;
    u16 narcId;
    u16 bankId;
    u32 bank;
} MessageLoader;

typedef void (*HandleCallback)(HandleEntry *e, void *arg);

extern "C" {

void *fn_8016DF70(u32 heapId, u32 size);
void fn_8016E0A0(void *p);
u32 fn_803DBF64(void *mon);
void fn_803DC598(void *mon, u32 move, u32 slot);
void fn_803DE824(void *party, s32 capacity);
void *fn_803DF5D0(u32 count, u32 len, u32 heapId);
void fn_803DFF20(u32 bank, u32 entry, void *buf);
Strbuf *fn_803DFFA8(u32 bank, u32 entry, u32 heapId);
u32 fn_803DAEFC(BoxPokemon *mon, u32 param, void *dest);
void fn_803DCD20(s32 idx, u16 *out);
void fn_803DEB48(u32 a, void *buf);
u32 fn_803DEAC4(void *buf, u32 b);
u8 fn_80392820(u8 *a, s32 idx, u8 i);
u16 fn_80392878(u8 *a, s32 idx, u8 i);
s32 fn_803DEC50(u16 *s);
void fn_803DEC24(u16 *dst, const u16 *src);
s8 fn_803DC958(u32 pv, s32 stat);

u16 fn_803E1C6C(u16 x);
u32 fn_803E19FC(u16 x);
u32 fn_803E1A10(u32 x);
u32 fn_803E0334(u16 *p, u32 size);
void SpeciesData_LoadSpecies(s32 species, void *out);
void Strbuf_CopyChars(Strbuf *buf, const u16 *src);
void fn_803DF750(void *a, u32 b, void *buf, u32 d);

u32 GetMonDataInternal(void *mon, u32 param, void *dest);
u32 fn_803DBB1C(s32 species, u32 a);
u8 fn_803DC12C(u32 id, u32 pv);
void *fn_803E0048(u32 type, u32 narcId, u32 bankId, u32 heapId);
void fn_803E00E0(MessageLoader *loader, u32 id, void *dest);
void fn_803E00D0(void *p);
void fn_803DF0D8(Strbuf *buf, s32 num, u32 maxDigits, s32 padding, s32 charset);

BOOL fn_803DCE54(u16 species, u32 form, u32 tm);
BOOL fn_803DD96C(BoxPokemon *mon);
u32 fn_803DBB90(BoxPokemon *mon);
void fn_803DB524(void *mon, u32 param, const void *value);
void fn_803DB678(BoxPokemon *mon, u32 param, void *value);
void fn_803DA8E0(void *mon);
BOOL fn_803DA2AC(BoxPokemon *mon, BOOL encrypt);
u32 fn_803DD188(u16 *p, u32 size);


u32 SpeciesData_GetValue(void *data, u32 param);
u32 SpeciesData_GetLevelAt(void *data, s32 species, u32 exp);
BOOL fn_803DA318(BoxPokemon *mon);
BOOL fn_803DA33C(BoxPokemon *mon, BOOL encrypt);
void fn_803DA258(void *mon);
void *fn_803E018C(void *loader, u32 entry);
s32 Pokemon_GetFormStatsIndex(s32 species, s32 form);

u8 fn_803DC04C(void *data, s32 species, u32 pv);
void Pokemon_LoadExperienceTableOf(s32 growthRate, u32 *table);
u32 fn_803DE72C(s32 growthRate, s32 level);
void *fn_803DFE28(u32 bank, u32 id);
void *fn_802502F4(void *a);
s32 fn_803E022C(const u16 *s, u32 n);
u32 Pokemon_GetSpeciesLevelAt(s32 species, u32 exp);

void fn_803E0160(void *loader, u32 entry, void *buf);
s32 fn_80176EB4(void *dest, void *src, u32 n);
void *fn_8016E008(u32 heapId, u32 size);
void fn_803DF31C(Strbuf *buf, const u16 *src, u32 len);
BOOL fn_803DFEAC(u32 a, u32 b, void **out, s32 *len);
extern const s8 lbl_80405C5D[25][5];

u32 fn_80392560(u8 *a, s32 growth, s32 level);
void fn_803E02B4(u16 *p, u32 size, u32 seed);
extern const char lbl_80474B9C[];

void *fn_803AC828(void);
void *fn_803AC868(void *a, u32 side);
u32 fn_803DE944(u8 *p);
u8 *fn_803DE94C(u8 *party, s32 idx);
u32 BoxPokemon_GetDataInternal(BoxPokemon *mon, s32 param, void *dest);
void Strbuf_Free(u8 *buf);
u32 fn_803E1E3C(u32 x);
extern const char lbl_804744C9[];

void *BoxPokemon_GetDataBlock(BoxPokemon *mon, u32 pv, u32 block);
void MessageLoader_GetSpeciesName(u32 species, u32 heapId, void *dest);
Strbuf *fn_803DEFD4(u32 size, u32 heapId);
u32 SpeciesData_GetFormValue(s32 species, s32 form, u32 param);

extern const char lbl_80474BBC[];
extern const char lbl_80474BDC[];

void fn_803DDAF8(BoxPokemon *mon, u32 param, void *value);
void Strbuf_Copy(Strbuf *dst, Strbuf *src);
extern const char lbl_80474E40[];
extern const char lbl_80474DF8[];

extern const char lbl_80474D71[];

void fn_803E0CAC(void *src, void *dst);
void fn_803DA474(void *mon, u32 species, u32 level, u32 a, u32 b, u32 c, u32 d, u32 e);
u32 fn_80392B38(u8 *a, u32 move);
u32 fn_80392B6C(u8 *a, u32 move);
u32 fn_80392BA0(u8 *a, u32 move);
u32 fn_80392BD4(u8 *a, u32 move);
u32 fn_80392C08(u8 *a, u32 move);
u32 fn_80392C3C(u8 *a, u32 move);
u32 fn_80392C70(u8 *a, u32 move);
u32 fn_80392CA4(u8 *a, u32 move);
u32 fn_80392CD8(u8 *a, u32 move);
u32 fn_80392D0C(u8 *a, u32 move);

void fn_803DF420(Strbuf *out, Strbuf *src);

void fn_803DC454(BoxPokemon *mon, u32 move);
u32 fn_803DD920(s32 n);
u8 fn_803DCA94(u8 *party, u8 mask);

void fn_803DE208(BoxPokemon *mon, u32 param, s32 value);
extern const char lbl_80474AF0[];

u32 fn_803DB93C(s32 species, u32 param);

void fn_80177080(u16 *dst, void *src, u32 n);
void fn_8017714C(u16 *dst, u16 *src, u32 n);

extern const s8 lbl_80405CDA[][3];

typedef struct DigitTables {
    u32 powersOfTen[10];
    u16 digitsJP[10];
    u16 digitsEN[10];
} DigitTables;

extern const DigitTables lbl_80405CF8;
extern const char lbl_80474D31[];

u32 fn_8039188C(u8 *a, s32 species);
u32 fn_803918C0(u8 *a, s32 species);
u32 fn_803918F4(u8 *a, s32 species);
u32 fn_80391928(u8 *a, s32 species);
u32 fn_8039195C(u8 *a, s32 species);
u32 fn_80391990(u8 *a, s32 species);
u32 fn_803919C4(u8 *a, s32 species);
u32 fn_803919F8(u8 *a, s32 species);
u32 fn_80391A2C(u8 *a, s32 species);
u32 fn_80391A60(u8 *a, s32 species);
u32 fn_80391A94(u8 *a, s32 species);
u32 fn_80391ACC(u8 *a, s32 species);
u32 fn_80391B04(u8 *a, s32 species);
u32 fn_80391B3C(u8 *a, s32 species);
u32 fn_80391B74(u8 *a, s32 species);
u32 fn_80391BAC(u8 *a, s32 species);
u32 fn_80391BE4(u8 *a, s32 species);
u32 fn_80391C18(u8 *a, s32 species);
u32 fn_80391C4C(u8 *a, s32 species);
u32 fn_80391C80(u8 *a, s32 species);
u32 fn_80391CB4(u8 *a, s32 species);
u32 fn_80391CE8(u8 *a, s32 species);
u32 fn_80391D1C(u8 *a, s32 species);
u32 fn_80391D50(u8 *a, s32 species);
u32 fn_80391D84(u8 *a, s32 species);
u32 fn_80391DB8(u8 *a, s32 species);
u32 fn_80391E20(u8 *a, s32 species);
u32 fn_80391E54(u8 *a, s32 species);
u32 fn_80391E8C(u8 *a, s32 species);
u32 fn_80391EC4(u8 *a, s32 species);
u32 fn_80391EF8(u8 *a, s32 species);
u32 fn_80391F2C(u8 *a, s32 species);
u32 fn_80391F60(u8 *a, s32 species);

void *fn_803E0588(void *mon, u32 pv, u32 block);
u64 fn_803E1A28(u64 x);

extern const char lbl_80474C38[];
extern const char lbl_80474E61[];

extern u8 lbl_80643008;
extern u8 lbl_80643009;

u16 fn_803DBD58(u32 nature, u16 value, u8 stat);

u32 Pokemon_GetArceusTypeOf(u32 item);

extern u8 lbl_8063CE34[];
extern u32 lbl_8063D098[101];
extern const char lbl_804744A8[];
extern const char lbl_80474D08[];
extern const char lbl_80474D56[];
extern const char lbl_80474D98[];


extern HandleEntry lbl_8063D230[16];


extern const s8 lbl_80405BE0[25][5];


void fn_803DAE24(BoxPokemon *dst, BoxPokemon *src);


}

extern "C" {

void fn_803DE81C(void *party) { fn_803DE824(party, 6); }

void fn_803DA258(void *mon) { memset(mon, 0, 0xa4); }

void Strbuf_Free(u8 *buf) {
    *(u32 *)(buf + 4) = 0xB6F8D2ED;
    fn_8016E0A0(buf);
}

void fn_803DC90C(BoxPokemon *src, BoxPokemon *dst) { fn_803DAE24(dst, src); }

u8 *fn_803DE94C(u8 *party, s32 idx) { return party + idx * 0xa4 + 8; }

BOOL fn_803DE99C(u32 memberIndex, void *dest) { return NARC_ReadWholeMemberByIndexPair(dest, 0x3a, memberIndex); }
BOOL fn_803DE9AC(u32 memberIndex, void *dest) { return NARC_ReadWholeMemberByIndexPair(dest, 0x3b, memberIndex); }

u32 fn_803DF540(u8 *p, s32 idx) { return *(u16 *)(p + idx * 2 + 6); }

void *fn_803DF5C0(u32 heapId) { return fn_803DF5D0(8, 0x20, heapId); }


void fn_803DA060(void *src, void *dst) { memcpy(dst, src, 0x20); }

u32 fn_803DFE0C(u8 *p, s32 idx) { return ((u32 *)(*(u8 **)(p + 8) + idx * 8))[1]; }

u32 fn_803E19FC(u16 x) { return (u16)(((x & 0xff) << 8) + ((x >> 8) & 0xff)); }
u16 fn_803E1C6C(u16 x) { return ((x & 0xff) << 8) + ((x >> 8) & 0xff); }

void fn_803DF048(u8 *p) {
    *(u16 *)(p + 2) = 0;
    *(u16 *)(p + 8) = 0xffff;
}

BOOL fn_803DF528(u8 *p) { return (*(u16 *)(p + 2) & 0xff00) == 0x100; }

u32 fn_803E1A10(u32 x) { return ((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x >> 24) & 0xff); }
u32 fn_803E1E3C(u32 x) { return ((x & 0xff) << 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8) | ((x >> 24) & 0xff); }

}

extern "C" {


s32 fn_803DA018(void) { return 0; }
void fn_803DA0BC(void) {}
u32 fn_803DA0C0(u8 *p) { return *(u32 *)(p + 0x10); }
u8 fn_803DA0C8(u8 *p) { return *(u8 *)(p + 0x18); }
u32 fn_803DA0F8(u8 *p) { return *(u32 *)(p + 0x14); }
u8 fn_803DA16C(u8 *p) { return *(u8 *)(p + 0x1c); }
s32 fn_803DA264(void) { return 164; }
void fn_803DB8C8(void *p) { fn_8016E0A0(p); }
u32 fn_803DBF60(void *mon) { return fn_803DBF64(mon); }
s32 fn_803DC160(void) { return 0; }
s32 fn_803DC168(void) { return 164; }
void fn_803DC19C(void) {}
void fn_803DC594(void *mon, u32 move, u32 slot) { fn_803DC598(mon, move, slot); }
s32 fn_803DE7D8(void) { return 992; }
u32 fn_803DE944(u8 *p) { return *(u32 *)(p + 0x4); }
s32 fn_803DE994(void) { return 0; }
}

void ApplicationManager_Free(ApplicationManager *appMan) { fn_8016E0A0(appMan); }
void *ApplicationManager_Data(ApplicationManager *appMan) { return appMan->data; }
void *ApplicationManager_Args(ApplicationManager *appMan) { return appMan->args; }
s32 fn_803DEE9C(ApplicationManager *appMan) { return appMan->procState; }
u32 Strbuf_Length(const Strbuf *str) { return str->size; }
const u16 *Strbuf_GetData(const Strbuf *str) { return str->data; }

extern "C" {
void fn_803DFCCC(void) {}
void fn_803DFD24(void) {}
void fn_803DFE20(void) {}
void fn_803DFE24(void) {}

}

extern "C" {

u32 fn_803DD920(s32 n) {
    u32 r = 1;
    for (s32 i = 0; i < n; i++) {
        r <<= 1;
    }
    return r;
}

typedef struct MsgHeader {
    u16 magic;
    u16 unk2;
    u16 count;
    u16 data[1];
} MsgHeader;

u16 *fn_803DF508(MsgHeader *p) {
    if (p->magic == 0xfffe) {
        u16 *r = (u16 *)p;
        r += 3;
        r += p->count;
        return r;
    }
    return (u16 *)p;
}

BOOL fn_803DA318(BoxPokemon *mon) {
    BOOL ret = FALSE;
    if (!mon->boxDecrypted) {
        ret = TRUE;
        mon->boxDecrypted = TRUE;
    }
    return ret;
}

s32 fn_803DA0D0(u8 *p) {
    u32 v = p[0x1a];
    s32 c = 0;
    while (v != 0) {
        if (v & 1) {
            c++;
        }
        v >>= 1;
    }
    return c;
}

u32 fn_803DA144(u8 *p, u32 n) {
    if (*(u32 *)(p + 0x14) < n) {
        *(u32 *)(p + 0x14) = 0;
    } else {
        *(u32 *)(p + 0x14) -= n;
    }
    return *(u32 *)(p + 0x14);
}

s32 fn_803DEC50(u16 *s) {
    s32 n = 0;
    while (s[n] != 0xffff) {
        n++;
    }
    return n;
}

u8 fn_803DC170(u32 pv) {
    return (((pv & 0x3000000) >> 18) | ((pv & 0x30000) >> 12) | ((pv & 0x300) >> 6) | (pv & 0x3)) % 28;
}

s32 fn_803DD940(u32 x) {
    s32 i;
    u32 mask;
    for (mask = 1, i = 0; i < 32; i++) {
        if (x & mask) {
            break;
        }
        mask <<= 1;
    }
    return i;
}

void fn_803DEC24(u16 *dst, const u16 *src) {
    while (*src != 0xffff) {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = 0xffff;
}

void fn_803E0160(void *loader, u32 entry, void *buf) {
    u16 *p = (u16 *)loader;
    switch (p[0]) {
    case 0:
        fn_803DFF20(*(u32 *)(p + 4), entry, buf);
        break;
    case 1:
        fn_803DFF20(p[3], entry, buf);
        break;
    }
}

s8 fn_803DC958(u32 pv, s32 stat) {
    u8 nature = pv % 25;
    return lbl_80405BE0[nature][stat];
}

u32 fn_803DD188(u16 *p, u32 size) {
    u32 sum = 0;
    for (u32 i = 0; i < size / 2; i++) {
        sum += p[i];
    }
    return sum;
}

}

extern "C" {

u8 fn_803DC12C(u32 id, u32 pv) {
    return (((pv & 0xffff) ^ (pv >> 16)) ^ ((id >> 16) ^ (id & 0xffff))) < 8;
}

s32 Pokemon_GetFormStatsIndex(s32 species, s32 form) {
    switch (species) {
    case 386:
        if (form != 0 && form <= 3) {
            species = 0x1ef + form;
        }
        break;
    case 413:
        if (form != 0 && form <= 2) {
            species = 0x1f2 + form;
        }
        break;
    }
    return species;
}

void fn_803DCDBC(s32 species, s32 form, u16 *out) {
    fn_803DCD20(Pokemon_GetFormStatsIndex(species, form), out);
}

BOOL fn_803DEC78(const u16 *a, const u16 *b) {
    while (*a == *b) {
        if (*a == 0xffff) {
            return FALSE;
        }
        a++;
        b++;
    }
    return TRUE;
}

void fn_803DED7C(u8 *p, u32 size, u32 heapId) {
    *(void **)(p + 0x1c) = fn_8016DF70(heapId, size);
}

void fn_803DEF3C(void *p) {
    HandleEntry *e = lbl_8063D230;
    for (s32 i = 0; i < 16; i++, e++) {
        if (e == p) {
            e->a = NULL;
            e->b = NULL;
            return;
        }
    }
}

typedef struct PokemonRaw {
    u32 w[0xa4 / 4];
} PokemonRaw;

typedef struct Party {
    s32 capacity;
    s32 count;
    PokemonRaw mons[6];
} Party;

#pragma dont_inline off
void fn_803DE95C(Party *src, Party *dst) { *dst = *src; }
#pragma dont_inline reset

s8 fn_803DC91C(void *mon, s32 stat) { return fn_803DC958(fn_803DAEFC((BoxPokemon *)mon, 0, NULL), stat); }

Party *fn_803DE7E0(u32 heapId) {
    Party *p = (Party *)fn_8016DF70(heapId, 0x3e0);
    fn_803DE824(p, 6);
    return p;
}

u32 fn_803DEA24(u32 a, u32 b) {
    u8 buf[16];
    fn_803DEB48(a, buf);
    return fn_803DEAC4(buf, b);
}

HandleEntry *fn_803DEF00(void *a, void *b) {
    HandleEntry *e = lbl_8063D230;
    for (s32 i = 0; i < 16; i++, e++) {
        if (e->a == NULL) {
            e->a = a;
            e->b = b;
            return e;
        }
    }
    return NULL;
}

void fn_803DCD20(s32 idx, u16 *out) {
    for (u8 i = 0; i < 20; i++) {
        u8 a = fn_80392820(lbl_8063CE34 + 0x48, idx, i);
        u16 b = fn_80392878(lbl_8063CE34 + 0x48, idx, i);
        if (b != 0) {
            out[i] = b | (a << 9);
        } else {
            out[i] = 0xffff;
        }
    }
}

void *fn_803DA020(u32 heapId) {
    void *p = fn_8016DF70(heapId, 0x20);
    memset(p, 0, 0x20);
    return p;
}

}

Pokemon *Pokemon_New(u32 heapId) {
    Pokemon *mon = (Pokemon *)fn_8016DF70(heapId, 0xa4);
    memset(mon, 0, 0xa4);
    return mon;
}

extern "C" {

#pragma dont_inline off
void fn_803DAE24(BoxPokemon *dst, BoxPokemon *src) { *dst = *src; }
#pragma dont_inline reset

void fn_803DF3D8(Strbuf *buf, u16 *dst, u32 dstSize) {
    if (buf->size + 1 <= dstSize) {
        memcpy(dst, buf->data, (buf->size + 1) * 2);
    } else {
        fn_803D989C(0, lbl_80474D98, buf->size, dstSize);
    }
}

void *fn_803E018C(void *loader, u32 entry) {
    u16 *p = (u16 *)loader;
    switch (p[0]) {
    case 0:
        return (void *)fn_803DFFA8(*(u32 *)(p + 4), entry, p[1]);
    case 1:
        return (void *)fn_803DFFA8(p[3], entry, p[1]);
    }
    return 0;
}

u32 fn_803DA100(u8 *p, u32 n) {
    if (n > 999999) {
        *(u32 *)(p + 0x14) = 999999;
    } else {
        *(u32 *)(p + 0x14) += n;
    }
    if (*(u32 *)(p + 0x14) > 999999) {
        *(u32 *)(p + 0x14) = 999999;
    }
    return *(u32 *)(p + 0x14);
}

void fn_803DA074(u16 *dst, u16 *src) {
    fn_803DEC50(src);
    fn_803DEC24(dst, src);
}

}

extern "C" {

void fn_803E1A78(u16 *src, u16 *dst) {
    dst[0] = fn_803E1C6C(src[0]);
    dst[1] = fn_803E1C6C(src[1]);
}

void *fn_803DB730(s32 species, u32 heapId) {
    void *p = fn_8016DF70(heapId, 0x2c);
    SpeciesData_LoadSpecies(species, p);
    return p;
}

BOOL fn_803DECAC(const u16 *a, const u16 *b, u32 n) {
    while (*a == *b) {
        if (n == 0) {
            return FALSE;
        }
        if (*a == 0xffff && *b == 0xffff) {
            return FALSE;
        }
        n--;
        a++;
        b++;
    }
    return TRUE;
}

BOOL fn_803E1848(u8 *p) {
    return (u16)fn_803E19FC(fn_803E0334((u16 *)(p + 8), 0x80)) == *(u16 *)(p + 6);
}

u64 fn_803E1A28(u64 x) {
    u32 lo = fn_803E1A10(x & 0xffffffff);
    u32 hi = fn_803E1A10((x >> 32) & 0xffffffff);
    return ((u64)lo << 32) | hi;
}

typedef struct BoxRaw {
    u32 w[0x88 / 4];
} BoxRaw;

typedef struct PartyRaw {
    u32 w[0x1c / 4];
} PartyRaw;

typedef struct PokemonCopy {
    BoxRaw box;
    PartyRaw party;
} PokemonCopy;

#pragma dont_inline off
void fn_803DC8B8(PokemonCopy *src, PokemonCopy *dst) {
    dst->box = src->box;
    dst->party = src->party;
}
#pragma dont_inline reset

#pragma dont_inline off
void fn_803DE8F0(PokemonCopy *dst, PokemonCopy *src) { *dst = *src; }
#pragma dont_inline reset

void fn_803DF4B4(Strbuf *buf, u16 c) {
    if (buf->size + 1 < buf->maxSize) {
        buf->data[buf->size++] = c;
        buf->data[buf->size] = 0xffff;
    } else {
        fn_803D989C(0, lbl_80474D56, buf->maxSize, buf->size);
    }
}

void fn_803DFCD0(u8 *a, u32 b, u8 *c) {
    Strbuf_CopyChars(*(Strbuf **)(a + 0xc), (u16 *)(c + 0x14));
    fn_803DF750(a, b, *(void **)(a + 0xc), 0);
}

}

extern "C" {

u32 fn_803DBAC4(void *mon) {
    u32 a = GetMonDataInternal(mon, 0xa0, NULL);
    return fn_803DBB1C(GetMonDataInternal(mon, 5, NULL), a);
}

void fn_803DF894(u8 *a, u32 b, void *mon) {
    fn_803DAEFC((BoxPokemon *)mon, 0x76, *(void **)(a + 0xc));
    fn_803DF750(a, b, *(void **)(a + 0xc), 0);
}

u8 fn_803DC0D0(void *mon) {
    u32 id = fn_803DAEFC((BoxPokemon *)mon, 7, NULL);
    return fn_803DC12C(id, fn_803DAEFC((BoxPokemon *)mon, 0, NULL));
}

}

void fn_803DEEA4() {
    for (s32 i = 0; i < 16; i++) {
        memset(&lbl_8063D230[i], 0, sizeof(HandleEntry));
    }
}

extern "C" {

#pragma dont_inline on
void MessageLoader_GetSpeciesName(u32 species, u32 heapId, void *dest) {
    void *loader = fn_803E0048(1, 0x1b, 2, heapId);
    fn_803E00E0((MessageLoader *)loader, species, dest);
    fn_803E00D0(loader);
}
#pragma dont_inline reset

typedef struct PartyFull {
    s32 capacity;
    s32 count;
    PokemonCopy mons[6];
} PartyFull;

BOOL fn_803DE890(PartyFull *party, PokemonCopy *mon) {
    if (party->count >= party->capacity) {
        return FALSE;
    }
    fn_803DE8F0(&party->mons[party->count], mon);
    party->count++;
    return TRUE;
}

void fn_803DF8EC(u8 *a, u32 b, u32 c, u32 d, u32 e, u32 f) {
    fn_803DF0D8(*(Strbuf **)(a + 0xc), c, d, e, f);
    fn_803DF750(a, b, *(void **)(a + 0xc), 0);
}

u8 MoveTable_CalcMaxPP(u32 move, u8 ppUps) {
    u8 buf[16];
    u8 pp;
    if (ppUps > 3) {
        ppUps = 3;
    }
    fn_803DEB48(move, buf);
    pp = fn_803DEAC4(buf, 5);
    return pp + (ppUps * pp * 20) / 100;
}

}

extern "C" {

BOOL fn_803DCDF0(void *mon, u32 tm) {
    u16 a = fn_803DAEFC((BoxPokemon *)mon, 0xad, NULL);
    return fn_803DCE54(a, fn_803DAEFC((BoxPokemon *)mon, 0x70, NULL), tm);
}

}

void fn_803DEF70() {
    HandleEntry *e = lbl_8063D230;
    for (s32 i = 0; i < 16; i++, e++) {
        if (e->a != NULL) {
            ((HandleCallback)e->a)(e, e->b);
        }
    }
}

extern "C" {

Strbuf *fn_803DEFD4(u32 size, u32 heapId) {
    Strbuf *buf = (Strbuf *)fn_8016DF70(heapId, size * 2 + 10);
    if (buf != NULL) {
        buf->integrity = 0xB6F8D2EC;
        buf->maxSize = size;
        buf->size = 0;
        buf->data[0] = 0xffff;
    }
    return buf;
}

u32 fn_803E0334(u16 *p, u32 size) {
    u32 i;
    u32 sum = 0;
    for (i = 0; i < size / 2; i++) {
        sum += fn_803E19FC(p[i]);
    }
    return sum;
}

void fn_803DA878(void *mon) {
    BOOL dec = fn_803DD96C((BoxPokemon *)mon);
    u32 level = fn_803DBB90((BoxPokemon *)mon);
    fn_803DB524(mon, 0xa0, &level);
    fn_803DA8E0(mon);
    fn_803DA2AC((BoxPokemon *)mon, dec);
}

void fn_803DE9BC(u8 *dest) {
    NARC_ReadFromMemberByIndexPair(dest, 10, 0, 0, 0x1d40);
    for (s32 i = 0; i < 0x1d4; i++) {
        fn_803DEB48(i, dest + i * 16);
    }
}

BOOL fn_803DA2AC(BoxPokemon *mon, BOOL encrypt) {
    BOOL ret = FALSE;
    if (mon->partyDecrypted == TRUE && encrypt == TRUE) {
        ret = TRUE;
        mon->partyDecrypted = FALSE;
        mon->boxDecrypted = FALSE;
        mon->checksum = fn_803DD188((u16 *)mon->data, 0x80);
    }
    return ret;
}

}

extern "C" {

BOOL fn_803DA33C(BoxPokemon *mon, BOOL encrypt) {
    BOOL ret = FALSE;
    if (mon->boxDecrypted == TRUE && encrypt == TRUE) {
        ret = TRUE;
        mon->boxDecrypted = FALSE;
        mon->checksum = fn_803DD188((u16 *)mon->data, 0x80);
    }
    return ret;
}

u32 fn_803DB93C(s32 species, u32 param) {
    void *data = fn_8016DF70(0, 0x2c);
    u32 ret;
    SpeciesData_LoadSpecies(species, data);
    ret = SpeciesData_GetValue(data, param);
    fn_8016E0A0(data);
    return ret;
}

u8 fn_803DBCEC(BoxPokemon *mon) {
    BOOL dec = fn_803DA318(mon);
    u32 pv = fn_803DAEFC((BoxPokemon *)mon, 0, NULL);
    fn_803DA33C(mon, dec);
    return pv % 25;
}

#pragma dont_inline on
void fn_803DE824(void *p, s32 capacity) {
    memset(p, 0, sizeof(PartyFull));
    ((PartyFull *)p)->capacity = capacity;
    ((PartyFull *)p)->count = 0;
    for (s32 i = 0; i < 6; i++) {
        fn_803DA258(&((PartyFull *)p)->mons[i]);
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void *MessageUtil_SpeciesName(u32 species, u32 heapId) {
    void *loader = fn_803E0048(1, 0x1b, 2, heapId);
    void *buf;
    if (loader != NULL) {
        buf = fn_803E018C(loader, species);
        fn_803E00D0(loader);
        return buf;
    }
    return NULL;
}
#pragma dont_inline reset

u32 Pokemon_GetSpeciesLevelAt(s32 species, u32 exp) {
    void *data = fn_8016DF70(0, 0x2c);
    u32 ret;
    SpeciesData_LoadSpecies(species, data);
    ret = SpeciesData_GetLevelAt(data, species, exp);
    fn_8016E0A0(data);
    return ret;
}

u32 SpeciesData_GetFormValue(s32 species, s32 form, u32 param) {
    void *data;
    u32 ret;
    species = Pokemon_GetFormStatsIndex(species, form);
    data = fn_8016DF70(0, 0x2c);
    SpeciesData_LoadSpecies(species, data);
    ret = SpeciesData_GetValue(data, param);
    fn_8016E0A0(data);
    return ret;
}

}

extern "C" {

u8 fn_803DBFDC(s32 species, u32 x) {
    void *data = fn_8016DF70(0, 0x2c);
    u8 ret;
    SpeciesData_LoadSpecies(species, data);
    ret = fn_803DC04C(data, species, x);
    fn_8016E0A0(data);
    return ret;
}

BOOL fn_803DD96C(BoxPokemon *mon) {
    BOOL ret = FALSE;
    if (!mon->partyDecrypted) {
        ret = TRUE;
        fn_803D989C(mon->boxDecrypted == FALSE, lbl_804744A8);
        mon->partyDecrypted = TRUE;
        mon->boxDecrypted = TRUE;
    }
    return ret;
}

u32 SpeciesData_GetLevelAt(void *data, s32 species, u32 exp) {
    s32 i;
    Pokemon_LoadExperienceTableOf(SpeciesData_GetValue(data, 0x15), lbl_8063D098);
    for (i = 1; i < 101; i++) {
        if (lbl_8063D098[i] > exp) {
            break;
        }
    }
    return i - 1;
}

u32 fn_803DBB1C(s32 species, u32 exp) {
    void *data = fn_8016DF70(0, 0x2c);
    u32 growth;
    SpeciesData_LoadSpecies(species, data);
    growth = SpeciesData_GetValue(data, 0x15);
    fn_8016E0A0(data);
    return fn_803DE72C(growth, exp);
}

BOOL fn_803DFEAC(u32 a, u32 b, void **out, s32 *len) {
    void *p = fn_803DFE28(a, b);
    if (p == NULL) {
        return FALSE;
    }
    *out = fn_802502F4(p);
    if (*out == NULL) {
        return FALSE;
    }
    *len = fn_803E022C((const u16 *)*out, 0xff) + 1;
    return TRUE;
}

void Strbuf_Copy(Strbuf *dst, Strbuf *src) {
    if (dst->maxSize > src->size) {
        memcpy(dst->data, src->data, (src->size + 1) * 2);
        dst->size = src->size;
    } else {
        fn_803D989C(0, lbl_80474D08, dst->maxSize, src->size);
    }
}

u32 fn_803DBB90(BoxPokemon *mon) {
    u32 species;
    u32 exp;
    BOOL dec;
    dec = fn_803DA318(mon);
    species = fn_803DAEFC((BoxPokemon *)mon, 5, NULL);
    exp = fn_803DAEFC((BoxPokemon *)mon, 8, NULL);
    fn_803DA33C(mon, dec);
    return Pokemon_GetSpeciesLevelAt((u16)species, exp);
}

}

// Lets the template copy be inlined.
#pragma dont_inline off
ApplicationManager *ApplicationManager_New(const ApplicationManagerTemplate *appTemplate, void *args, u32 heapId) {
    ApplicationManager *appMan = (ApplicationManager *)fn_8016DF70(heapId, sizeof(ApplicationManager));
    appMan->appTemplate = *appTemplate;
    appMan->execState = 0;
    appMan->procState = 0;
    appMan->args = args;
    appMan->data = NULL;
    appMan->parent = NULL;
    appMan->child = NULL;
    return appMan;
}
#pragma dont_inline reset


extern "C" {

#define DEFINE_MSG_FORMAT(name, bank)                                  \
    void name(u8 *a, u32 b, u32 entry) {                               \
        void *loader = fn_803E0048(1, 0x1b, bank, *(u32 *)(a + 4));    \
        if (loader != NULL) {                                          \
            fn_803E0160(loader, entry, *(void **)(a + 0xc));           \
            fn_803DF750(a, b, *(void **)(a + 0xc), 0);                 \
            fn_803E00D0(loader);                                       \
        }                                                              \
    }

DEFINE_MSG_FORMAT(fn_803DF94C, 3)
DEFINE_MSG_FORMAT(fn_803DF9CC, 4)
DEFINE_MSG_FORMAT(fn_803DFA4C, 5)
DEFINE_MSG_FORMAT(fn_803DFACC, 10)
DEFINE_MSG_FORMAT(fn_803DFB4C, 8)
DEFINE_MSG_FORMAT(fn_803DFBCC, 7)
DEFINE_MSG_FORMAT(fn_803DFC4C, 9)

void fn_803E00E0(MessageLoader *loader, u32 id, void *dest) {
    switch (loader->type) {
    case 0:
        fn_80176EB4(dest, fn_802502F4(fn_803DFE28(loader->bank, id)), 0xff);
        break;
    case 1:
        fn_80176EB4(dest, fn_802502F4(fn_803DFE28(loader->bankId, id)), 0xff);
        break;
    }
}

void fn_803E02B4(u16 *p, u32 size, u32 seed) {
    u32 i;
    for (i = 0; i < size / 2; i++) {
        u32 v = fn_803E19FC(p[i]);
        seed = seed * 0x41C64E6D + 0x6073;
        p[i] = fn_803E19FC(v ^ (seed >> 16));
    }
}

}

extern "C" {

u16 fn_803DBD58(u32 nature, u16 value, u8 stat) {
    if (stat < 1 || stat > 5) {
        return value;
    }
    switch (lbl_80405C5D[nature][stat - 1]) {
    case 1:
        value = value * 110;
        value = value / 100;
        break;
    case -1:
        value = (u16)(value * 90) / 100;
        break;
    }
    return value;
}

u8 fn_803DC04C(void *data, s32 species, u32 pv) {
    u8 ratio = SpeciesData_GetValue(data, 0x12);
    switch (ratio) {
    case 0:
        return 0;
    case 0xfe:
        return 1;
    case 0xff:
        return 2;
    }
    return (u32)ratio > (u32)(u8)pv;
}

typedef struct MoveTable {
    u16 effect;
    u8 cls;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 effectChance;
    u16 range;
    s8 priority;
    u8 flags;
    u8 contestEffect;
    u8 contestType;
    u8 pad[2];
} MoveTable;

u32 fn_803DEAC4(void *buf, u32 param) {
    MoveTable *move = (MoveTable *)buf;
    u32 ret;
    switch (param) {
    case 0:
        ret = move->effect;
        break;
    case 1:
        ret = move->cls;
        break;
    case 2:
        ret = move->power;
        break;
    case 3:
        ret = move->type;
        break;
    case 4:
        ret = move->accuracy;
        break;
    case 5:
        ret = move->pp;
        break;
    case 6:
        ret = move->effectChance;
        break;
    case 7:
        ret = move->range;
        break;
    case 8:
        ret = move->priority;
        break;
    case 9:
        ret = move->flags;
        break;
    case 10:
        ret = move->contestEffect;
        break;
    case 11:
        ret = move->contestType;
        break;
    }
    return ret;
}

void *fn_803DFE28(u32 bank, u32 id) {
    switch (bank) {
    case 2:
        return (void *)(id + 0xa);
    case 3:
        return (void *)(id + 0x1fa);
    case 4:
        return (void *)(id + 0xbae);
    case 5:
        return (void *)(id + 0x7c7);
    case 0:
        return (void *)(id > 0x4eb ? id : id + 0x24da);
    case 1:
        return (void *)(id + 0x1f5e);
    case 7:
        return (void *)(id + 0x418);
    case 8:
        return (void *)(id + 0x3008);
    case 9:
        return (void *)(id + 0x5051);
    case 10:
        return (void *)(id + 0xca6);
    }
    return NULL;
}

void fn_803DFF20(u32 bank, u32 entry, void *strbuf) {
    void *str;
    s32 len;
    if (fn_803DFEAC(bank, entry, &str, &len)) {
        u16 *buf;
        len *= 2;
        buf = (u16 *)fn_8016E008(0, len * 2);
        len = fn_80176EB4(buf, str, len);
        fn_803DF31C((Strbuf *)strbuf, buf, len);
        fn_8016E0A0(buf);
    }
}

}

extern "C" {

void *fn_803E0048(u32 type, u32 narcId, u32 bankId, u32 heapId) {
    MessageLoader *l = (MessageLoader *)fn_8016E008(heapId, sizeof(MessageLoader));
    if (l != NULL) {
        if (type == 0) {
            l->bank = bankId;
            if (bankId == 0) {
                fn_8016E0A0(l);
                return NULL;
            }
        } else {
            l->bank = 0;
        }
        l->type = type;
        l->narcId = narcId;
        l->bankId = bankId;
        l->heapId = heapId;
    }
    return l;
}

s32 fn_803E022C(const u16 *s, u32 n) {
    u16 prev;
    s32 i;
    if (s == NULL) {
        return 0;
    }
    prev = *s;
    for (i = 0; i < n; i++, s++) {
        if (i != 0) {
            if ((prev != 0xffff && *s == 0) || (prev == 0xffff && *s == 0xffff)) {
                return i;
            }
        } else if (*s == 0) {
            return 0;
        }
        prev = *s;
    }
    return n;
}

typedef struct BoxPokemonRaw {
    u32 personality;
    u16 flags;
    u16 checksum;
    u16 data[0x40];
} BoxPokemonRaw;

typedef union BoxFlagsLE {
    u16 raw;
    struct {
        u16 unused : 13;
        u16 checksumFailed : 1;
        u16 boxDecrypted : 1;
        u16 partyDecrypted : 1;
    } bits;
} BoxFlagsLE;

typedef struct BoxPokemonLE {
    u32 personality;
    BoxFlagsLE flags;
    u16 checksum;
    u16 data[0x40];
} BoxPokemonLE;

BOOL fn_803E0500(BoxPokemonRaw *mon) {
    BoxPokemonLE tmp;
    BOOL ret = FALSE;
    u32 seed;
    tmp.flags.raw = fn_803E19FC(mon->flags);
    if (!tmp.flags.bits.boxDecrypted) {
        ret = TRUE;
        tmp.flags.bits.boxDecrypted = TRUE;
        mon->flags = fn_803E19FC(tmp.flags.raw);
        fn_803E1A10(mon->personality);
        seed = fn_803E19FC(mon->checksum);
        fn_803E02B4(mon->data, 0x80, (u16)seed);
    }
    return ret;
}

void Pokemon_LoadExperienceTableOf(s32 growthRate, u32 *table) {
    fn_803D989C(growthRate < 8, lbl_80474B9C);
    for (s32 i = 0; i < 101; i++) {
        table[i] = fn_80392560(lbl_8063CE34 + 0x1c, growthRate, i);
    }
}

void fn_803DF808(u8 *a, u32 b, void *mon) {
    void *loader = fn_803E0048(1, 0x1b, 2, *(u32 *)(a + 4));
    fn_803E0160(loader, fn_803DAEFC((BoxPokemon *)mon, 5, NULL), *(void **)(a + 0xc));
    fn_803DF750(a, b, *(void **)(a + 0xc), 0);
    fn_803E00D0(loader);
}

}

extern "C" {

u32 fn_803DAE64(u32 side, s32 slot, u32 param, void *dest) {
    u8 *party;
    if (side > 3) {
        return 0;
    }
    if ((u32)slot >= 6) {
        return 0;
    }
    party = (u8 *)fn_803AC868(fn_803AC828(), side);
    if (slot >= (s32)fn_803DE944(party)) {
        return 0;
    }
    return GetMonDataInternal(fn_803DE94C(party, slot), param, dest);
}

#define BOX mon

u32 fn_803DAEFC(BoxPokemon *mon, u32 param, void *dest) {
    if (!BOX->boxDecrypted) {
        u32 cs = fn_803DD188((u16 *)BOX->data, 0x80);
        if ((u16)cs != BOX->checksum) {
            fn_803D989C((u16)cs == BOX->checksum, lbl_804744C9);
            BOX->checksumFailed = TRUE;
        }
    }
    return BoxPokemon_GetDataInternal(BOX, param, dest);
}

#undef BOX

typedef struct TemplateAttr {
    u8 b[4];
} TemplateAttr;

typedef struct TemplateEntry {
    TemplateAttr attr;
    u8 *buf;
} TemplateEntry;

typedef struct StringTemplate {
    u32 count;
    u32 heapId;
    TemplateEntry *entries;
    u8 *buf;
} StringTemplate;

void fn_803DF6B4(StringTemplate *t) {
    if (t->entries != NULL) {
        for (u32 i = 0; i < t->count; i++) {
            if (t->entries[i].buf == NULL) {
                break;
            }
            Strbuf_Free(t->entries[i].buf);
        }
        fn_8016E0A0(t->entries);
    }
    if (t->buf != NULL) {
        Strbuf_Free(t->buf);
    }
    t->count = 0;
    fn_8016E0A0(t);
}

typedef struct SwapRecord {
    u16 h[8];
    u32 w10;
    u32 w14;
    u8 b18;
    u8 b19;
    u8 b1a;
    u8 b1b;
    u8 b1c;
} SwapRecord;

void fn_803E1DA0(SwapRecord *src, SwapRecord *dst) {
    for (s32 i = 0; i < 8; i++) {
        dst->h[i] = ((src->h[i] & 0xff) << 8) + ((src->h[i] >> 8) & 0xff);
    }
    dst->w10 = fn_803E1E3C(src->w10);
    dst->w14 = fn_803E1E3C(src->w14);
    dst->b18 = src->b18;
    dst->b19 = src->b19;
    dst->b1a = src->b1a;
    dst->b1b = src->b1b;
    dst->b1c = src->b1c;
}

}

extern "C" {

void Strbuf_CopyChars(Strbuf *buf, const u16 *src) {
    buf->size = 0;
    while (*src != 0xffff) {
        if (buf->size >= buf->maxSize - 1) {
            fn_803D989C(0, lbl_80474D56);
            break;
        }
        buf->data[buf->size++] = *src++;
    }
    buf->data[buf->size] = 0xffff;
}

Strbuf *fn_803DFFA8(u32 bank, u32 entry, u32 heapId) {
    void *str;
    s32 len;
    Strbuf *ret = NULL;
    if (fn_803DFEAC(bank, entry, &str, &len)) {
        u16 *buf;
        len *= 2;
        buf = (u16 *)fn_8016E008(heapId, len * 2);
        len = fn_80176EB4(buf, str, len);
        ret = fn_803DEFD4(len, heapId);
        if (ret != NULL) {
            fn_803DF31C(ret, buf, len);
        }
        fn_8016E0A0(buf);
    }
    return ret;
}

void fn_803E195C(BoxPokemon *mon, BOOL force) {
    u16 *a;
    u32 *b;
    void *c;
    fn_803DA318(mon);
    a = (u16 *)BoxPokemon_GetDataBlock(mon, mon->personality, 0);
    b = (u32 *)BoxPokemon_GetDataBlock(mon, mon->personality, 1);
    c = BoxPokemon_GetDataBlock(mon, mon->personality, 2);
    if (force || (b[4] & 1)) {
        b[4] &= ~1;
        MessageLoader_GetSpeciesName(a[0], 0, c);
    }
}

u16 fn_803DC3AC(BoxPokemon *mon, u16 move) {
    s32 i;
    u16 ret;
    BOOL dec;
    ret = 0xffff;
    dec = fn_803DA318(mon);
    for (i = 0; i < 4; i++) {
        u16 m = fn_803DAEFC(mon, 0x36 + i, NULL);
        if (m == 0) {
            fn_803DC598(mon, move, (u8)i);
            ret = move;
            break;
        }
        if (m == move) {
            ret = 0xfffe;
            break;
        }
    }
    fn_803DA33C(mon, dec);
    return ret;
}

BOOL fn_803DCE54(u16 species, u32 form, u32 tm) {
    u32 mask;
    u32 param;
    if (species == 0x1ee) {
        return FALSE;
    }
    if (tm < 32) {
        mask = 1 << tm;
        param = 0x1d;
    } else if (tm < 64) {
        mask = 1 << (tm - 32);
        param = 0x1e;
    } else if (tm < 96) {
        mask = 1 << (tm - 64);
        param = 0x1f;
    } else {
        mask = 1 << (tm - 96);
        param = 0x20;
    }
    return (SpeciesData_GetFormValue(species, form, param) & mask) != 0;
}

}

extern "C" {

u32 Pokemon_GetArceusTypeOf(u32 item) {
    switch (item) {
    case 125:
        return 10;
    case 126:
        return 11;
    case 127:
        return 13;
    case 128:
        return 12;
    case 129:
        return 15;
    case 130:
        return 1;
    case 131:
        return 3;
    case 132:
        return 4;
    case 133:
        return 2;
    case 134:
        return 14;
    case 135:
        return 6;
    case 136:
        return 5;
    case 137:
        return 7;
    case 138:
        return 16;
    case 139:
        return 17;
    case 140:
        return 8;
    }
    return 0;
}

u32 fn_803DE72C(s32 growthRate, s32 level) {
    u32 *table;
    u32 ret;
    fn_803D989C(growthRate < 8, lbl_80474BBC);
    fn_803D989C(level <= 101, lbl_80474BDC);
    table = (u32 *)fn_8016DF70(0, 101 * sizeof(u32));
    Pokemon_LoadExperienceTableOf(growthRate, table);
    ret = table[level];
    fn_8016E0A0(table);
    return ret;
}

u8 fn_803DCA94(u8 *party, u8 mask) {
    s32 i = 0;
    s32 bit = 1;
    u8 ret = 0;
    if (mask != 0) {
        do {
            if (mask & 1) {
                if (GetMonDataInternal(fn_803DE94C(party, i), 0x99, NULL)) {
                    ret |= bit;
                }
            }
            bit <<= 1;
            i++;
        } while ((mask >>= 1) != 0);
    } else if (GetMonDataInternal(fn_803DE94C(party, 0), 0x99, NULL)) {
        ret = 1;
    }
    return ret;
}

u8 fn_803DC804(u8 *party) {
    s32 count = fn_803DE944(party);
    u8 max = 1;
    s32 i;
    u8 *mon;
    for (i = 0; i < count; i++) {
        mon = fn_803DE94C(party, i);
        if (GetMonDataInternal(mon, 5, NULL) && !GetMonDataInternal(mon, 0x4c, NULL)) {
            u8 level = GetMonDataInternal(mon, 0xa0, NULL);
            if (level > max) {
                max = level;
            }
        }
    }
    return max;
}

}

extern "C" {

typedef struct PokemonDS {
    u32 personality;
    BoxFlagsLE flags;
    u16 checksum;
    u16 data[0x40];
    u16 party[0x32];
} PokemonDS;

BOOL fn_803E0398(PokemonDS *mon, BOOL encrypt) {
    BoxPokemonLE tmp;
    BOOL ret = FALSE;
    u32 cs;
    tmp.flags.raw = fn_803E19FC(mon->flags.raw);
    if (tmp.flags.bits.partyDecrypted == TRUE && encrypt == TRUE) {
        ret = TRUE;
        tmp.flags.bits.partyDecrypted = FALSE;
        tmp.flags.bits.boxDecrypted = FALSE;
        mon->flags.raw = fn_803E19FC(tmp.flags.raw);
        fn_803E02B4(mon->party, 0x64, fn_803E1A10(mon->personality));
        cs = fn_803E0334(mon->data, 0x80);
        fn_803E02B4(mon->data, 0x80, (u16)cs);
        mon->checksum = fn_803E19FC((u16)cs);
    }
    return ret;
}

BOOL fn_803E044C(PokemonDS *mon) {
    BoxPokemonLE tmp;
    BOOL ret = FALSE;
    u32 seed;
    tmp.flags.raw = fn_803E19FC(mon->flags.raw);
    if (!tmp.flags.bits.partyDecrypted) {
        ret = TRUE;
        fn_803D989C(tmp.flags.bits.boxDecrypted == FALSE, lbl_80474E40);
        tmp.flags.bits.partyDecrypted = TRUE;
        tmp.flags.bits.boxDecrypted = TRUE;
        mon->flags.raw = fn_803E19FC(tmp.flags.raw);
        fn_803E02B4(mon->party, 0x64, fn_803E1A10(mon->personality));
        seed = fn_803E19FC(mon->checksum);
        fn_803E02B4(mon->data, 0x80, (u16)seed);
    }
    return ret;
}

void fn_803DB678(BoxPokemon *mon, u32 param, void *value) {
    if (!mon->boxDecrypted) {
        u32 cs = fn_803DD188((u16 *)mon->data, 0x80);
        if ((u16)cs != mon->checksum) {
            fn_803D989C((u16)cs == mon->checksum, lbl_804744C9);
            mon->checksumFailed = TRUE;
            return;
        }
    }
    fn_803DDAF8(mon, param, value);
    if (!mon->boxDecrypted) {
        mon->checksum = fn_803DD188((u16 *)mon->data, 0x80);
    }
}

#define TPL ((StringTemplate *)a)

#pragma dont_inline off
void fn_803DF750(void *a, u32 idx, void *buf, u32 attr) {
    fn_803D989C(idx < TPL->count, lbl_80474DF8, idx, TPL->count);
    if (idx < TPL->count) {
        if (attr != 0) {
            TPL->entries[idx].attr = *(TemplateAttr *)attr;
        }
        Strbuf_Copy((Strbuf *)TPL->entries[idx].buf, (Strbuf *)buf);
    }
}
#pragma dont_inline reset


#undef TPL

}

extern "C" {

void fn_803DF31C(Strbuf *buf, const u16 *src, u32 len) {
    if (len <= buf->maxSize) {
        u32 i;
        memcpy(buf->data, src, len * 2);
        for (i = 0; i < len; i++) {
            if (buf->data[i] == 0xffff) {
                break;
            }
        }
        buf->size = i;
        if (i == len) {
            buf->data[len - 1] = 0xffff;
        }
    } else {
        fn_803D989C(0, lbl_80474D71, buf->maxSize, len);
    }
}

void fn_803DC748(BoxPokemon *src, BoxPokemon *dst) {
    u32 zero = 0;
    u8 mail[4];
    fn_803DAE24(dst, src);
    if (dst->boxDecrypted) {
        dst->partyDecrypted = TRUE;
    }
    fn_803DB524(dst, 0x9f, &zero);
    fn_803DB524(dst, 0xa2, &zero);
    fn_803DB524(dst, 0xa3, &zero);
    fn_803DB524(dst, 0xa1, &zero);
    memset(mail, 0, sizeof(mail));
    fn_803DB524(dst, 0xaa, mail);
    fn_803DA878(dst);
}

typedef struct PartyDS {
    u32 capacity;
    u32 count;
    PokemonDS mons[6];
} PartyDS;

u32 fn_803E1898(PartyDS *party) {
    PokemonDS *mon;
    u32 capacity;
    u32 count;
    u32 ok;
    u32 i;
    BOOL dec;
    capacity = fn_803E1A10(party->capacity);
    count = fn_803E1A10(party->count);
    ok = 0;
    if (capacity > 6) {
        capacity = 6;
    }
    if (count > 6) {
        count = 6;
    }
    if (count > capacity) {
        count = capacity;
    }
    for (i = 0; i < count; i++) {
        mon = &party->mons[i];
        dec = fn_803E044C(mon);
        if (fn_803E1848((u8 *)mon)) {
            ok++;
        }
        fn_803E0398(mon, dec);
    }
    return ok;
}

}

extern "C" {

void fn_803E1054(u8 *src, u8 *dst) {
    fn_803E0CAC(src, dst);
    *(u32 *)(dst + 0x88) = fn_803E1A10(*(u32 *)(src + 0x88));
    dst[0x8c] = src[0x8c];
    dst[0x8d] = src[0x8d];
    *(u16 *)(dst + 0x8e) = fn_803E19FC(*(u16 *)(src + 0x8e));
    *(u16 *)(dst + 0x90) = fn_803E19FC(*(u16 *)(src + 0x90));
    *(u16 *)(dst + 0x92) = fn_803E19FC(*(u16 *)(src + 0x92));
    *(u16 *)(dst + 0x94) = fn_803E19FC(*(u16 *)(src + 0x94));
    *(u16 *)(dst + 0x96) = fn_803E19FC(*(u16 *)(src + 0x96));
    *(u16 *)(dst + 0x98) = fn_803E19FC(*(u16 *)(src + 0x98));
    *(u16 *)(dst + 0x9a) = fn_803E19FC(*(u16 *)(src + 0x9a));
    memset(dst + 0x9c, 0, 4);
    memset(dst + 0xa0, 0, 4);
}

void fn_803DA3A8(void *mon, u32 species, u32 level, u32 a, u32 b, u32 c, u32 d, u32 e) {
    u32 zero;
    u8 mail[4];
    memset(mon, 0, 0xa4);
    fn_803DA474(mon, species, level, a, b, c, d, e);
    fn_803DB524(mon, 0xa0, &level);
    zero = 0;
    fn_803DB524(mon, 0xa1, &zero);
    memset(mail, 0, sizeof(mail));
    fn_803DB524(mon, 0xaa, mail);
    fn_803DA878(mon);
}

void fn_803DEB48(u32 move, void *buf) {
    MoveTable *out = (MoveTable *)buf;
    out->effect = fn_80392B38(lbl_8063CE34 + 0x18, move);
    out->cls = fn_80392B6C(lbl_8063CE34 + 0x18, move);
    out->power = fn_80392BA0(lbl_8063CE34 + 0x18, move);
    out->type = fn_80392BD4(lbl_8063CE34 + 0x18, move);
    out->accuracy = fn_80392C08(lbl_8063CE34 + 0x18, move);
    out->pp = fn_80392C3C(lbl_8063CE34 + 0x18, move);
    out->effectChance = fn_80392C70(lbl_8063CE34 + 0x18, move);
    out->range = fn_80392CA4(lbl_8063CE34 + 0x18, move);
    out->priority = fn_80392CD8(lbl_8063CE34 + 0x18, move);
    out->flags = fn_80392D0C(lbl_8063CE34 + 0x18, move);
}

}


BOOL ApplicationManager_Exec(ApplicationManager *appMan) {
    switch (appMan->execState) {
        case 0:
            appMan->execState = 1;
        case 1:
            if (appMan->appTemplate.init(appMan, &appMan->procState) == TRUE) {
                appMan->execState = 2;
                appMan->procState = 0;
            }
            break;
        case 2:
            if (appMan->appTemplate.main(appMan, &appMan->procState) == TRUE) {
                appMan->execState = 3;
                appMan->procState = 0;
            }
            break;
        case 3:
            if (appMan->appTemplate.exit(appMan, &appMan->procState) == TRUE) {
                return TRUE;
            }
            break;
    }
    return FALSE;
}

extern "C" {


FieldBattleDTO *fn_803DA174(u32 heapId, u32 battleType, u32 b, u32 c, u32 d) {
    FieldBattleDTO *dto = (FieldBattleDTO *)fn_8016DF70(heapId, sizeof(FieldBattleDTO));
    s32 i;
    memset(dto, 0, sizeof(FieldBattleDTO));
    dto->battleType = battleType;
    dto->_16C = 0;
    dto->_14 = 0;
    dto->_130 = 0;
    dto->_134 = d;
    dto->_174 = c;
    dto->_140 = 0;
    dto->_154 = b;
    for (i = 0; i < 4; i++) {
        dto->parties[i] = fn_803DE7E0(heapId);
    }
    for (i = 0; i < 4; i++) {
        dto->trainerInfo[i] = fn_803DA020(heapId);
    }
    dto->bag = Bag_New(heapId);
    dto->_F0 = 0;
    dto->_EC = 0;
    return dto;
}

void *fn_803DF5D0(u32 count, u32 len, u32 heapId) {
    u32 i;
    StringTemplate *t = (StringTemplate *)fn_8016E008(heapId, sizeof(StringTemplate));
    if (t != NULL) {
        t->count = count;
        t->heapId = heapId;
        t->buf = (u8 *)fn_803DEFD4(len, heapId);
        if (t->buf != NULL) {
            t->entries = (TemplateEntry *)fn_8016E008(heapId, count * sizeof(TemplateEntry));
            if (t->entries != NULL) {
                for (i = 0; i < count; i++) {
                    t->entries[i].buf = (u8 *)fn_803DEFD4(len, heapId);
                    if (t->entries[i].buf == NULL) {
                        break;
                    }
                }
                if (i == count) {
                    return t;
                }
            }
        }
    }
    return NULL;
}

void fn_803DFD28(StringTemplate *t, Strbuf *out, u8 *fmt) {
    u16 *src = (u16 *)Strbuf_GetData((Strbuf *)fmt);
    fn_803DF048((u8 *)out);
    while (*src != 0xffff) {
        if (*src == 0xfffe) {
            if (fn_803DF528((u8 *)src)) {
                u32 idx = fn_803DF540((u8 *)src, 0);
                fn_803DF420(out, (Strbuf *)t->entries[idx].buf);
                src = fn_803DF508((MsgHeader *)src);
            } else {
                u16 *start = src;
                src = fn_803DF508((MsgHeader *)src);
                while (start < src) {
                    fn_803DF4B4(out, *start++);
                }
            }
        } else {
            fn_803DF4B4(out, *src++);
        }
    }
}

}

extern "C" {

typedef struct Pokemon {
    BoxPokemon box;
    u32 status;
    u8 level;
    u8 unk8D;
    u16 hp;
    u16 maxHp;
    u16 attack;
    u16 defense;
    u16 speed;
    u16 spAttack;
    u16 spDefense;
    u8 unk9C[8];
} Pokemon;

#define MON ((Pokemon *)mon)

u32 GetMonDataInternal(void *mon, u32 param, void *dest) {
    if (!MON->box.partyDecrypted) {
        u32 cs = fn_803DD188((u16 *)MON->box.data, 0x80);
        if ((u16)cs != MON->box.checksum) {
            fn_803D989C((u16)cs == MON->box.checksum, lbl_804744C9);
            MON->box.checksumFailed = TRUE;
        }
    }
    switch (param) {
    case 0x9f:
        return MON->status;
    case 0xa0:
        return MON->level;
    case 0xa1:
        return MON->unk8D;
    case 0xa2:
        return MON->hp;
    case 0xa3:
        return MON->maxHp;
    case 0xa4:
        return MON->attack;
    case 0xa5:
        return MON->defense;
    case 0xa6:
        return MON->speed;
    case 0xa7:
        return MON->spAttack;
    case 0xa8:
        return MON->spDefense;
    case 0xa9:
        return TRUE;
    case 0xaa:
        return TRUE;
    }
    return BoxPokemon_GetDataInternal(&MON->box, param, dest);
}

#undef MON

void fn_803DC2B4(BoxPokemon *mon) {
    u16 species;
    u8 level;
    BOOL dec;
    u32 form;
    u16 *table;
    s32 i;
    table = (u16 *)fn_8016DF70(0, 0x2c);
    dec = fn_803DA318(mon);
    species = fn_803DAEFC(mon, 5, NULL);
    form = fn_803DAEFC(mon, 0x70, NULL);
    level = fn_803DBB90(mon);
    fn_803DCD20(Pokemon_GetFormStatsIndex(species, form), table);
    for (i = 0; table[i] != 0xffff; i++) {
        u32 move;
        if ((table[i] & 0xfe00) > (level << 9)) {
            break;
        }
        move = table[i] & 0x1ff;
        if (fn_803DC3AC(mon, move) == 0xffff) {
            fn_803DC454(mon, move);
        }
    }
    fn_8016E0A0(table);
    fn_803DA33C(mon, dec);
}

void fn_803DC988(u8 *party) {
    s32 count = fn_803DE944(party);
    u8 *mon;
    s32 slot;
    u16 r = LCRNG_Next();
    if (r == 0x4000 || r == 0x8000 || r == 0xc000) {
        do {
            slot = LCRNG_Next() % count;
            mon = fn_803DE94C(party, slot);
        } while (!GetMonDataInternal(mon, 5, NULL) || GetMonDataInternal(mon, 0x4c, NULL));
        if (!fn_803DCA94(party, fn_803DD920(slot))) {
            u8 strain;
            u32 val;
            do {
                strain = LCRNG_Next();
            } while ((strain & 7) == 0);
            if (strain & 0xf0) {
                strain &= 7;
            }
            strain |= strain << 4;
            strain &= 0xf3;
            strain++;
            val = strain;
            fn_803DB524(mon, 0x99, &val);
        }
    }
}

}

extern "C" {

void fn_803DE0FC(Pokemon *mon, u32 param, s32 value) {
    if (!mon->box.partyDecrypted) {
        u32 cs = fn_803DD188((u16 *)mon->box.data, 0x80);
        if ((u16)cs != mon->box.checksum) {
            fn_803D989C((u16)cs == mon->box.checksum, lbl_804744C9);
            return;
        }
    }
    switch (param) {
    case 0xa2:
        if (mon->hp + value > mon->maxHp) {
            mon->hp = mon->maxHp;
        } else {
            mon->hp = mon->hp + value;
        }
        break;
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
        fn_803D989C(0, lbl_80474AF0);
        break;
    default:
        fn_803DE208(&mon->box, param, value);
        break;
    }
    if (!mon->box.partyDecrypted) {
        mon->box.checksum = fn_803DD188((u16 *)mon->box.data, 0x80);
    }
}

#pragma dont_inline off
static inline u32 SpeciesGetValueInline(s32 species, u32 param) {
    void *data = fn_8016DF70(0, 0x2c);
    u32 ret;
    SpeciesData_LoadSpecies(species, data);
    ret = SpeciesData_GetValue(data, param);
    fn_8016E0A0(data);
    return ret;
}

static inline u32 SpeciesGetExpAtInline(s32 species, u32 level) {
    void *data = fn_8016DF70(0, 0x2c);
    u32 growth;
    SpeciesData_LoadSpecies(species, data);
    growth = SpeciesData_GetValue(data, 0x15);
    fn_8016E0A0(data);
    return fn_803DE72C(growth, level);
}

BOOL fn_803DC1A0(void *mon) {
    u32 exp;
    u32 level;
    u32 growth;
    u16 species;
    u8 nextLevel;
    species = GetMonDataInternal(mon, 5, NULL);
    nextLevel = GetMonDataInternal(mon, 0xa0, NULL) + 1;
    exp = GetMonDataInternal(mon, 8, NULL);
    growth = SpeciesGetValueInline(species, 0x15);
    {
        u32 maxExp = fn_803DE72C(growth, 100);
        if (exp > maxExp) {
            exp = maxExp;
            fn_803DB524(mon, 8, &exp);
        }
    }
    if (nextLevel > 100) {
        return FALSE;
    }
    if (exp >= fn_803DE72C(growth, nextLevel)) {
        level = nextLevel;
        fn_803DB524(mon, 0xa0, &level);
        return TRUE;
    }
    return FALSE;
}

u8 fn_803DB9A8(void *mon) {
    u16 species;
    u8 level;
    BOOL dec;
    u32 cur;
    dec = fn_803DD96C((BoxPokemon *)mon);
    species = GetMonDataInternal(mon, 5, NULL);
    level = GetMonDataInternal(mon, 0xa0, NULL);
    cur = SpeciesGetExpAtInline(species, level);
    u32 next = SpeciesGetExpAtInline(species, level + 1);
    u32 exp = GetMonDataInternal(mon, 8, NULL);
    fn_803DA2AC((BoxPokemon *)mon, dec);
    return ((exp - cur) * 100) / (next - cur);
}
#pragma dont_inline reset

}

extern "C" {

void fn_803DCB44(u8 *party) {
    u8 pokerus;
    s32 count = fn_803DE944(party);
    u8 *other;
    u8 *mon;
    s32 i;
    u32 prev;
    u32 next;
    if ((LCRNG_Next() % 3) == 0) {
        for (i = 0; i < count; i++) {
            mon = fn_803DE94C(party, i);
            if (GetMonDataInternal(mon, 5, NULL)) {
                pokerus = GetMonDataInternal(mon, 0x99, NULL);
                if (pokerus & 0xf) {
                    if (i != 0) {
                        other = fn_803DE94C(party, i - 1);
                        if (!(GetMonDataInternal(other, 0x99, NULL) & 0xf0)) {
                            prev = pokerus;
                            fn_803DB524(other, 0x99, &prev);
                        }
                    }
                    if (i < count - 1) {
                        other = fn_803DE94C(party, i + 1);
                        if (!(GetMonDataInternal(other, 0x99, NULL) & 0xf0)) {
                            next = pokerus;
                            fn_803DB524(other, 0x99, &next);
                            i++;
                        }
                    }
                }
            }
        }
    }
}

u16 fn_803DC614(void *mon, u32 *idx, u16 *move) {
    u16 *table;
    u16 ret;
    u16 species;
    u32 form;
    u8 level;
    ret = 0;
    table = (u16 *)fn_8016DF70(0, 0x2c);
    species = GetMonDataInternal(mon, 5, NULL);
    form = GetMonDataInternal(mon, 0x70, NULL);
    level = GetMonDataInternal(mon, 0xa0, NULL);
    fn_803DCD20(Pokemon_GetFormStatsIndex(species, form), table);
    if (table[*idx] == 0xffff) {
        fn_8016E0A0(table);
        return 0;
    }
    while ((level << 9) != (table[*idx] & 0xfe00)) {
        (*idx)++;
        if (table[*idx] == 0xffff) {
            fn_8016E0A0(table);
            return 0;
        }
    }
    if ((level << 9) == (table[*idx] & 0xfe00)) {
        *move = table[*idx] & 0x1ff;
        (*idx)++;
        ret = fn_803DC3AC((BoxPokemon *)mon, *move);
    }
    fn_8016E0A0(table);
    return ret;
}

typedef struct PCBoxesDS {
    u32 currentBox;
    BoxPokemonRaw mons[18][30];
    u16 names[18][20];
} PCBoxesDS;

typedef struct PCBoxes {
    BoxPokemon mons[18][30];
    u16 names[18][20];
} PCBoxes;

void fn_803E1C80(PCBoxesDS *src, PCBoxes *dst) {
    s32 i;
    s32 j;
    u16 name[0x20];
    u16 tmp[0x20];
    for (i = 0; i < 18; i++) {
        for (j = 0; j < 30; j++) {
            BoxPokemonRaw *s = &src->mons[i][j];
            BoxPokemon *d = &dst->mons[i][j];
            BOOL ok;
            fn_803E0500(s);
            ok = fn_803E1848((u8 *)s);
            fn_803E0CAC(s, d);
            if (!ok) {
                d->checksumFailed = TRUE;
                fn_80177080(name, BoxPokemon_GetDataBlock(d, d->personality, 2), 11);
                fn_8017714C(tmp, name, 0x40);
            }
        }
        for (j = 0; j < 20; j++) {
            u16 v = src->names[i][j];
            dst->names[i][j] = ((v & 0xff) << 8) + ((v >> 8) & 0xff);
        }
    }
}

}

extern "C" {

typedef struct SpeciesData {
    u8 baseHp;
    u8 baseAttack;
    u8 baseDefense;
    u8 baseSpeed;
    u8 baseSpAttack;
    u8 baseSpDefense;
    u8 type1;
    u8 type2;
    u8 catchRate;
    u8 baseExp;
    u16 evHp : 2;
    u16 evAttack : 2;
    u16 evDefense : 2;
    u16 evSpeed : 2;
    u16 evSpAttack : 2;
    u16 evSpDefense : 2;
    u16 evPad : 4;
    u16 item1;
    u16 item2;
    u8 gender;
    u8 eggCycles;
    u8 friendship;
    u8 growthRate;
    u8 eggGroup1;
    u8 eggGroup2;
    u8 ability1;
    u8 ability2;
    u8 safariFleeRate;
    u8 color : 7;
    u8 flipSprite : 1;
    u8 pad1A[2];
    u32 tmLearnset[4];
} SpeciesData;

u32 SpeciesData_GetValue(void *data, u32 param) {
    SpeciesData *d = (SpeciesData *)data;
    u32 ret;
    switch (param) {
    case 0:
        ret = d->baseHp;
        break;
    case 1:
        ret = d->baseAttack;
        break;
    case 2:
        ret = d->baseDefense;
        break;
    case 3:
        ret = d->baseSpeed;
        break;
    case 4:
        ret = d->baseSpAttack;
        break;
    case 5:
        ret = d->baseSpDefense;
        break;
    case 6:
        ret = d->type1;
        break;
    case 7:
        ret = d->type2;
        break;
    case 8:
        ret = d->catchRate;
        break;
    case 9:
        ret = d->baseExp;
        break;
    case 10:
        ret = d->evHp;
        break;
    case 11:
        ret = d->evAttack;
        break;
    case 12:
        ret = d->evDefense;
        break;
    case 13:
        ret = d->evSpeed;
        break;
    case 14:
        ret = d->evSpAttack;
        break;
    case 15:
        ret = d->evSpDefense;
        break;
    case 16:
        ret = d->item1;
        break;
    case 17:
        ret = d->item2;
        break;
    case 18:
        ret = d->gender;
        break;
    case 19:
        ret = d->eggCycles;
        break;
    case 20:
        ret = d->friendship;
        break;
    case 21:
        ret = d->growthRate;
        break;
    case 22:
        ret = d->eggGroup1;
        break;
    case 23:
        ret = d->eggGroup2;
        break;
    case 24:
        ret = d->ability1;
        break;
    case 25:
        ret = d->ability2;
        break;
    case 26:
        ret = d->safariFleeRate;
        break;
    case 27:
        ret = d->color;
        break;
    case 28:
        ret = d->flipSprite;
        break;
    case 29:
        ret = d->tmLearnset[0];
        break;
    case 30:
        ret = d->tmLearnset[1];
        break;
    case 31:
        ret = d->tmLearnset[2];
        break;
    case 32:
        ret = d->tmLearnset[3];
        break;
    }
    return ret;
}

void fn_803DC454(BoxPokemon *mon, u32 move) {
    u16 moves[4];
    u8 pp[4];
    u8 ppUps[4];
    u32 v;
    BOOL dec;
    s32 i;
    dec = fn_803DA318(mon);
    for (i = 0; i < 3; i++) {
        moves[i] = fn_803DAEFC(mon, 0x37 + i, NULL);
        pp[i] = fn_803DAEFC(mon, 0x3b + i, NULL);
        ppUps[i] = fn_803DAEFC(mon, 0x3f + i, NULL);
    }
    moves[3] = move;
    pp[3] = fn_803DEA24(move, 5);
    ppUps[3] = 0;
    for (i = 0; i < 4; i++) {
        v = moves[i];
        fn_803DB678(mon, 0x36 + i, &v);
        v = pp[i];
        fn_803DB678(mon, 0x3a + i, &v);
        v = ppUps[i];
        fn_803DB678(mon, 0x3e + i, &v);
    }
    fn_803DA33C(mon, dec);
}

typedef struct PartyWii {
    s32 capacity;
    s32 count;
    Pokemon mons[6];
} PartyWii;

void fn_803E111C(PartyDS *src, PartyWii *dst) {
    s32 i;
    u16 name[0x20];
    u16 tmp[0x20];
    dst->capacity = fn_803E1A10(src->capacity);
    dst->count = fn_803E1A10(src->count);
    if (dst->count <= 6) {
        for (i = dst->count; i < 6; i++) {
            memset(&src->mons[i], 0, sizeof(PokemonDS));
        }
    }
    for (i = 0; i < 6; i++) {
        PokemonDS *s = &src->mons[i];
        BOOL dec = fn_803E044C(s);
        BOOL ok = fn_803E1848((u8 *)s);
        fn_803E1054((u8 *)s, (u8 *)&dst->mons[i]);
        if (!ok) {
            dst->mons[i].box.checksumFailed = TRUE;
            fn_80177080(name, BoxPokemon_GetDataBlock(&dst->mons[i].box, dst->mons[i].box.personality, 2), 11);
            fn_8017714C(tmp, name, 0x40);
        }
        fn_803E0398(s, dec);
    }
}

}

extern "C" {

#define MON ((Pokemon *)mon)

void fn_803DB524(void *mon, u32 param, const void *value) {
    if (!MON->box.partyDecrypted) {
        u32 cs = fn_803DD188((u16 *)MON->box.data, 0x80);
        if ((u16)cs != MON->box.checksum) {
            fn_803D989C((u16)cs == MON->box.checksum, lbl_804744C9);
            MON->box.checksumFailed = TRUE;
            return;
        }
    }
    switch (param) {
    case 0x9f:
        MON->status = *(const u32 *)value;
        break;
    case 0xa0:
        MON->level = ((const u8 *)value)[3];
        break;
    case 0xa1:
        MON->unk8D = ((const u8 *)value)[3];
        break;
    case 0xa2:
        MON->hp = ((const u16 *)value)[1];
        break;
    case 0xa3:
        MON->maxHp = ((const u16 *)value)[1];
        break;
    case 0xa4:
        MON->attack = ((const u16 *)value)[1];
        break;
    case 0xa5:
        MON->defense = ((const u16 *)value)[1];
        break;
    case 0xa6:
        MON->speed = ((const u16 *)value)[1];
        break;
    case 0xa7:
        MON->spAttack = ((const u16 *)value)[1];
        break;
    case 0xa8:
        MON->spDefense = ((const u16 *)value)[1];
        break;
    case 0xa9:
    case 0xaa:
        break;
    default:
        fn_803DDAF8(&MON->box, param, (void *)value);
        break;
    }
    if (!MON->box.partyDecrypted) {
        MON->box.checksum = fn_803DD188((u16 *)MON->box.data, 0x80);
    }
}

#undef MON

u32 fn_803D9EB4(s32 a, s32 b) {
    switch (a) {
    case 0:
        {
            BOOL f = (b == 4 || b == 5);
            u32 ret = 8;
            if (f) {
                ret = 9;
            }
            return ret;
        }
    case 1:
    case 2:
    case 0x10:
        {
            BOOL f = (b == 4 || b == 5);
            u32 ret = 4;
            if (f) {
                ret = 6;
            }
            return ret;
        }
    case 4:
    case 0x80:
        return 1;
    case 8:
        {
            BOOL f = (b == 4 || b == 5);
            u32 ret = 2;
            if (f) {
                ret = 7;
            }
            return ret;
        }
    case 0x100:
        {
            BOOL f = (b == 4 || b == 5);
            u32 ret = 6;
            if (f) {
                ret = 4;
            }
            return ret;
        }
    case 0x40:
        return 3;
    case 0x200:
        return 10;
    case 0x20:
        return 5;
    case 0x400:
        return 11;
    }
    return 0;
}

}

extern "C" {

void fn_803DBDDC(void *mon, u32 event, u32 location) {
    u16 species;
    s16 friendship;
    u8 idx;
    u8 effect;
    s8 delta;
    s32 v;
    if (event == 5) {
        if (LCRNG_Next() & 1) {
            return;
        }
    }
    species = GetMonDataInternal(mon, 0xad, NULL);
    if (species == 0 || species == 0x1ee) {
        return;
    }
    effect = Item_LoadParam(GetMonDataInternal(mon, 6, NULL), ITEM_PARAM_HOLD_EFFECT, 0);
    idx = 0;
    friendship = GetMonDataInternal(mon, 9, NULL);
    if (friendship >= 100) {
        idx = 1;
    }
    if (friendship >= 200) {
        idx++;
    }
    delta = lbl_80405CDA[event][idx];
    if (delta > 0 && GetMonDataInternal(mon, 0x9a, NULL) == 11) {
        delta++;
    }
    if (delta > 0 && GetMonDataInternal(mon, 0x97, NULL) == location) {
        delta++;
    }
    if (delta > 0 && effect == 0x34) {
        delta = delta * 150 / 100;
    }
    friendship += delta;
    if (friendship < 0) {
        friendship = 0;
    }
    if (friendship > 255) {
        friendship = 255;
    }
    v = friendship;
    fn_803DB524(mon, 9, &v);
}

void fn_803E1244(Pokemon *src, PokemonDS *dst, u32 heapId);

#pragma dont_inline off
static inline BOOL BoxPokemon_IsEmptyInline(BoxPokemon *box) {
    u16 *a;
    u16 *c;
    if (box->personality != 0 || box->checksum != 0) {
        return FALSE;
    }
    a = (u16 *)BoxPokemon_GetDataBlock(box, box->personality, 0);
    BoxPokemon_GetDataBlock(box, box->personality, 1);
    c = (u16 *)BoxPokemon_GetDataBlock(box, box->personality, 2);
    BoxPokemon_GetDataBlock(box, box->personality, 3);
    if (a[0] != 0 || *(u32 *)(a + 2) != 0) {
        return FALSE;
    }
    return c[0] == 0;
}

void fn_803E16E0(PartyWii *src, PartyDS *dst, u32 heapId) {
    s32 i;
    dst->capacity = fn_803E1A10(src->capacity);
    dst->count = fn_803E1A10(src->count);
    for (i = 0; i < 6; i++) {
        BOOL dec;
        Pokemon *m;
        m = &src->mons[i];
        dec = fn_803DD96C(&m->box);
        fn_803E1244(m, &dst->mons[i], heapId);
        fn_803DA2AC(&m->box, dec);
    }
    for (i = 0; i < 6; i++) {
        if (BoxPokemon_IsEmptyInline(&src->mons[i].box)) {
            break;
        }
    }
    dst->count = fn_803E1A10(i);
}
#pragma dont_inline reset

}

extern "C" {

void fn_803DF0D8(Strbuf *buf, s32 num, u32 maxDigits, s32 padding, s32 charset) {
    const DigitTables *tables = &lbl_80405CF8;
    const u32 *pow = tables->powersOfTen;
    BOOL isNegative = (num < 0);
    if (buf->maxSize > maxDigits + isNegative) {
        const u16 *digits = tables->digitsEN;
        if (charset == 3) {
            digits = tables->digitsJP;
        }
        u32 divisor;
        buf->size = 0;
        buf->data[0] = 0xffff;
        if (isNegative) {
            u16 hyphen;
            num *= -1;
            hyphen = (charset == 3) ? 0xf1 : 0x1be;
            buf->data[buf->size++] = hyphen;
        }
        divisor = pow[maxDigits - 1];
        while (divisor != 0) {
            u32 digit = (u16)((u32)num / divisor);
            num -= divisor * digit;
            if (padding == 2) {
                buf->data[buf->size++] = (digit < 10) ? digits[digit] : 0xe2;
            } else if (digit != 0 || divisor == 1) {
                padding = 2;
                buf->data[buf->size++] = (digit < 10) ? digits[digit] : 0xe2;
            } else if (padding == 0) {
                buf->data[buf->size++] = (charset == 3) ? 0x1 : 0x1de;
            }
            divisor /= 10;
        }
        buf->data[buf->size] = 0xffff;
        return;
    }
    fn_803D989C(0, lbl_80474D31, buf->maxSize, maxDigits);
}

typedef struct SwapPair {
    u16 a;
    u16 b;
} SwapPair;

typedef struct SwapBlock {
    SwapPair a[0xa5];
    SwapPair b[0x32];
    SwapPair c[0x64];
    SwapPair d[0xc];
    SwapPair e[0x28];
    SwapPair f[0x40];
    SwapPair g[0xf];
    SwapPair h[0x1e];
    u32 last;
} SwapBlock;

void fn_803E1AC4(SwapBlock *src, SwapBlock *dst) {
    s32 i;
    u32 x;
    for (i = 0; i < 0xa5; i++) {
        fn_803E1A78(&src->a[i].a, &dst->a[i].a);
    }
    for (i = 0; i < 0x32; i++) {
        fn_803E1A78(&src->b[i].a, &dst->b[i].a);
    }
    for (i = 0; i < 0x64; i++) {
        fn_803E1A78(&src->c[i].a, &dst->c[i].a);
    }
    for (i = 0; i < 0xc; i++) {
        fn_803E1A78(&src->d[i].a, &dst->d[i].a);
    }
    for (i = 0; i < 0x28; i++) {
        fn_803E1A78(&src->e[i].a, &dst->e[i].a);
    }
    for (i = 0; i < 0x40; i++) {
        fn_803E1A78(&src->f[i].a, &dst->f[i].a);
    }
    for (i = 0; i < 0xf; i++) {
        fn_803E1A78(&src->g[i].a, &dst->g[i].a);
    }
    for (i = 0; i < 0x1e; i++) {
        fn_803E1A78(&src->h[i].a, &dst->h[i].a);
    }
    x = src->last;
    dst->last = (x << 24) | ((x << 8) & 0xff0000) | ((x >> 8) & 0xff00) | (x >> 24);
}

}

extern "C" {

void SpeciesData_LoadSpecies(s32 species, void *out) {
    SpeciesData *d = (SpeciesData *)out;
    d->baseHp = fn_8039188C(lbl_8063CE34 + 0x10, species);
    d->baseAttack = fn_803918C0(lbl_8063CE34 + 0x10, species);
    d->baseDefense = fn_803918F4(lbl_8063CE34 + 0x10, species);
    d->baseSpeed = fn_80391928(lbl_8063CE34 + 0x10, species);
    d->baseSpAttack = fn_8039195C(lbl_8063CE34 + 0x10, species);
    d->baseSpDefense = fn_80391990(lbl_8063CE34 + 0x10, species);
    d->type1 = fn_803919C4(lbl_8063CE34 + 0x10, species);
    d->type2 = fn_803919F8(lbl_8063CE34 + 0x10, species);
    d->catchRate = fn_80391A2C(lbl_8063CE34 + 0x10, species);
    d->baseExp = fn_80391A60(lbl_8063CE34 + 0x10, species);
    d->evHp = fn_80391A94(lbl_8063CE34 + 0x10, species);
    d->evAttack = fn_80391ACC(lbl_8063CE34 + 0x10, species);
    d->evDefense = fn_80391B04(lbl_8063CE34 + 0x10, species);
    d->evSpeed = fn_80391B3C(lbl_8063CE34 + 0x10, species);
    d->evSpAttack = fn_80391B74(lbl_8063CE34 + 0x10, species);
    d->evSpDefense = fn_80391BAC(lbl_8063CE34 + 0x10, species);
    d->item1 = fn_80391BE4(lbl_8063CE34 + 0x10, species);
    d->item2 = fn_80391C18(lbl_8063CE34 + 0x10, species);
    d->gender = fn_80391C4C(lbl_8063CE34 + 0x10, species);
    d->eggCycles = fn_80391C80(lbl_8063CE34 + 0x10, species);
    d->friendship = fn_80391CB4(lbl_8063CE34 + 0x10, species);
    d->growthRate = fn_80391CE8(lbl_8063CE34 + 0x10, species);
    d->eggGroup1 = fn_80391D1C(lbl_8063CE34 + 0x10, species);
    d->eggGroup2 = fn_80391D50(lbl_8063CE34 + 0x10, species);
    d->ability1 = fn_80391D84(lbl_8063CE34 + 0x10, species);
    d->ability2 = fn_80391DB8(lbl_8063CE34 + 0x10, species);
    d->safariFleeRate = fn_80391E20(lbl_8063CE34 + 0x10, species);
    d->color = fn_80391E54(lbl_8063CE34 + 0x10, species);
    d->flipSprite = fn_80391E8C(lbl_8063CE34 + 0x10, species);
    d->tmLearnset[0] = fn_80391EC4(lbl_8063CE34 + 0x10, species);
    d->tmLearnset[1] = fn_80391EF8(lbl_8063CE34 + 0x10, species);
    d->tmLearnset[2] = fn_80391F2C(lbl_8063CE34 + 0x10, species);
    d->tmLearnset[3] = fn_80391F60(lbl_8063CE34 + 0x10, species);
}

}

extern "C" {

typedef struct BlockA {
    u16 species;
    u16 item;
    u32 otId;
    u32 exp;
    u8 b[16];
    u32 ribbons;
} BlockA;

typedef union IVsLE {
    u32 raw;
    struct {
        u32 hasNickname : 1;
        u32 isEgg : 1;
        u32 spDefIV : 5;
        u32 spAtkIV : 5;
        u32 speedIV : 5;
        u32 defIV : 5;
        u32 atkIV : 5;
        u32 hpIV : 5;
    } bits;
} IVsLE;

typedef struct IVsBE {
    u32 hpIV : 5;
    u32 atkIV : 5;
    u32 defIV : 5;
    u32 speedIV : 5;
    u32 spAtkIV : 5;
    u32 spDefIV : 5;
    u32 isEgg : 1;
    u32 hasNickname : 1;
} IVsBE;

typedef struct FormLE {
    u8 form : 5;
    u8 gender : 2;
    u8 fateful : 1;
} FormLE;

typedef struct FormBE {
    u8 fateful : 1;
    u8 gender : 2;
    u8 form : 5;
} FormBE;

typedef struct BlockBDS {
    u16 moves[4];
    u8 pp[4];
    u8 ppUps[4];
    u32 ivs;
    u32 ribbons;
    FormLE form;
    u8 b19;
    u16 h1a;
    u32 w1c;
} BlockBDS;

typedef struct BlockBLE {
    u16 moves[4];
    u8 pp[4];
    u8 ppUps[4];
    IVsLE ivs;
    u32 ribbons;
    FormLE form;
    u8 b19;
    u16 h1a;
    u32 w1c;
} BlockBLE;

typedef struct BlockBWii {
    u16 moves[4];
    u8 pp[4];
    u8 ppUps[4];
    IVsBE ivs;
    u32 ribbons;
    FormBE form;
    u8 b19;
    u16 h1a;
    u32 w1c;
} BlockBWii;

typedef struct BlockC {
    u16 nickname[11];
    u8 b16;
    u8 b17;
    u64 ribbons;
} BlockC;

typedef struct MetLE {
    u8 otGender : 1;
    u8 metLevel : 7;
} MetLE;

typedef struct MetBE {
    u8 metLevel : 7;
    u8 otGender : 1;
} MetBE;

typedef struct BlockDDS {
    u16 otName[8];
    u8 b10[6];
    u16 h16;
    u16 h18;
    u8 b1a;
    u8 b1b;
    MetLE met;
    u8 b1d;
    u16 h1e;
} BlockDDS;

typedef struct BlockDWii {
    u16 otName[8];
    u8 b10[6];
    u16 h16;
    u16 h18;
    u8 b1a;
    u8 b1b;
    MetBE met;
    u8 b1d;
    u16 h1e;
} BlockDWii;

void fn_803E0CAC(void *srcp, void *dstp) {
    BoxPokemonRaw *src = (BoxPokemonRaw *)srcp;
    BoxPokemon *dst = (BoxPokemon *)dstp;
    BoxPokemonLE tmpBox;
    BlockBLE tmpB;
    BlockA *sa;
    BlockBDS *sb;
    BlockC *sc;
    BlockDDS *sd;
    BlockA *da;
    BlockBWii *db;
    BlockC *dc;
    BlockDWii *dd;
    s32 i;

    dst->personality = fn_803E1A10(src->personality);
    tmpBox.flags.raw = fn_803E19FC(src->flags);
    dst->checksumFailed = tmpBox.flags.bits.checksumFailed;
    dst->boxDecrypted = tmpBox.flags.bits.boxDecrypted;
    dst->partyDecrypted = tmpBox.flags.bits.partyDecrypted;
    dst->checksum = fn_803E19FC(src->checksum);

    sa = (BlockA *)fn_803E0588(src, fn_803E1A10(src->personality), 0);
    sb = (BlockBDS *)fn_803E0588(src, fn_803E1A10(src->personality), 1);
    sc = (BlockC *)fn_803E0588(src, fn_803E1A10(src->personality), 2);
    sd = (BlockDDS *)fn_803E0588(src, fn_803E1A10(src->personality), 3);
    da = (BlockA *)BoxPokemon_GetDataBlock(dst, dst->personality, 0);
    db = (BlockBWii *)BoxPokemon_GetDataBlock(dst, dst->personality, 1);
    dc = (BlockC *)BoxPokemon_GetDataBlock(dst, dst->personality, 2);
    dd = (BlockDWii *)BoxPokemon_GetDataBlock(dst, dst->personality, 3);

    da->species = fn_803E19FC(sa->species);
    da->item = fn_803E19FC(sa->item);
    da->otId = fn_803E1A10(sa->otId);
    da->exp = fn_803E1A10(sa->exp);
    da->b[0] = sa->b[0];
    da->b[1] = sa->b[1];
    da->b[2] = sa->b[2];
    da->b[3] = sa->b[3];
    da->b[4] = sa->b[4];
    da->b[5] = sa->b[5];
    da->b[6] = sa->b[6];
    da->b[7] = sa->b[7];
    da->b[8] = sa->b[8];
    da->b[9] = sa->b[9];
    da->b[10] = sa->b[10];
    da->b[11] = sa->b[11];
    da->b[12] = sa->b[12];
    da->b[13] = sa->b[13];
    da->b[14] = sa->b[14];
    da->b[15] = sa->b[15];
    da->ribbons = fn_803E1A10(sa->ribbons);

    for (i = 0; i < 4; i++) {
        db->moves[i] = fn_803E19FC(sb->moves[i]);
        db->pp[i] = sb->pp[i];
        db->ppUps[i] = sb->ppUps[i];
    }
    tmpB.ivs.raw = fn_803E1A10(sb->ivs);
    db->ivs.hasNickname = tmpB.ivs.bits.hasNickname;
    db->ivs.isEgg = tmpB.ivs.bits.isEgg;
    db->ivs.spDefIV = tmpB.ivs.bits.spDefIV;
    db->ivs.spAtkIV = tmpB.ivs.bits.spAtkIV;
    db->ivs.speedIV = tmpB.ivs.bits.speedIV;
    db->ivs.defIV = tmpB.ivs.bits.defIV;
    db->ivs.atkIV = tmpB.ivs.bits.atkIV;
    db->ivs.hpIV = tmpB.ivs.bits.hpIV;
    db->ribbons = fn_803E1A10(sb->ribbons);
    db->form.form = sb->form.form;
    db->form.gender = sb->form.gender;
    db->form.fateful = sb->form.fateful;
    db->b19 = sb->b19;
    db->h1a = fn_803E19FC(sb->h1a);
    db->w1c = (u16)fn_803E19FC(sb->w1c);

    for (i = 0; i < 11; i++) {
        dc->nickname[i] = fn_803E19FC(sc->nickname[i]);
    }
    dc->b16 = sc->b16;
    dc->b17 = sc->b17;
    dc->ribbons = fn_803E1A28(sc->ribbons);

    for (i = 0; i < 8; i++) {
        dd->otName[i] = fn_803E19FC(sd->otName[i]);
    }
    dd->b10[0] = sd->b10[0];
    dd->b10[1] = sd->b10[1];
    dd->b10[2] = sd->b10[2];
    dd->b10[3] = sd->b10[3];
    dd->b10[4] = sd->b10[4];
    dd->b10[5] = sd->b10[5];
    dd->h16 = fn_803E19FC(sd->h16);
    dd->h18 = fn_803E19FC(sd->h18);
    dd->b1a = sd->b1a;
    dd->b1b = sd->b1b;
    dd->met.otGender = sd->met.otGender;
    dd->met.metLevel = sd->met.metLevel;
    dd->b1d = sd->b1d;
    dd->h1e = fn_803E19FC(sd->h1e);
}

}

extern "C" {

void fn_803E1244(Pokemon *src, PokemonDS *dst, u32 encrypt) {
    BlockA *da;
    BlockBLE *db;
    BlockC *dc;
    BlockDDS *dd;
    BlockA *sa;
    BlockBWii *sb;
    BlockC *sc;
    BlockDWii *sd;
    s32 i;

    dst->personality = fn_803E1A10(src->box.personality);
    dst->flags.raw = 0;
    dst->flags.bits.checksumFailed = src->box.checksumFailed;
    dst->flags.bits.boxDecrypted = src->box.boxDecrypted;
    dst->flags.bits.partyDecrypted = src->box.partyDecrypted;
    dst->flags.raw = fn_803E19FC(dst->flags.raw);
    dst->checksum = fn_803E19FC(src->box.checksum);

    da = (BlockA *)fn_803E0588(dst, fn_803E1A10(dst->personality), 0);
    db = (BlockBLE *)fn_803E0588(dst, fn_803E1A10(dst->personality), 1);
    dc = (BlockC *)fn_803E0588(dst, fn_803E1A10(dst->personality), 2);
    dd = (BlockDDS *)fn_803E0588(dst, fn_803E1A10(dst->personality), 3);
    sa = (BlockA *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, 0);
    sb = (BlockBWii *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, 1);
    sc = (BlockC *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, 2);
    sd = (BlockDWii *)BoxPokemon_GetDataBlock(&src->box, src->box.personality, 3);

    da->species = fn_803E19FC(sa->species);
    da->item = fn_803E19FC(sa->item);
    da->otId = fn_803E1A10(sa->otId);
    da->exp = fn_803E1A10(sa->exp);
    da->b[0] = sa->b[0];
    da->b[1] = sa->b[1];
    da->b[2] = sa->b[2];
    da->b[3] = sa->b[3];
    da->b[4] = sa->b[4];
    da->b[5] = sa->b[5];
    da->b[6] = sa->b[6];
    da->b[7] = sa->b[7];
    da->b[8] = sa->b[8];
    da->b[9] = sa->b[9];
    da->b[10] = sa->b[10];
    da->b[11] = sa->b[11];
    da->b[12] = sa->b[12];
    da->b[13] = sa->b[13];
    da->b[14] = sa->b[14];
    da->b[15] = sa->b[15];
    da->ribbons = fn_803E1A10(sa->ribbons);

    for (i = 0; i < 4; i++) {
        db->moves[i] = fn_803E19FC(sb->moves[i]);
        db->pp[i] = sb->pp[i];
        db->ppUps[i] = sb->ppUps[i];
    }
    db->ivs.bits.hasNickname = sb->ivs.hasNickname;
    db->ivs.bits.isEgg = sb->ivs.isEgg;
    db->ivs.bits.spDefIV = sb->ivs.spDefIV;
    db->ivs.bits.spAtkIV = sb->ivs.spAtkIV;
    db->ivs.bits.speedIV = sb->ivs.speedIV;
    db->ivs.bits.defIV = sb->ivs.defIV;
    db->ivs.bits.atkIV = sb->ivs.atkIV;
    db->ivs.bits.hpIV = sb->ivs.hpIV;
    db->ivs.raw = fn_803E1A10(db->ivs.raw);
    db->ribbons = fn_803E1A10(sb->ribbons);
    db->form.form = sb->form.form;
    db->form.gender = sb->form.gender;
    db->form.fateful = sb->form.fateful;
    db->b19 = sb->b19;
    db->h1a = fn_803E19FC(sb->h1a);
    db->w1c = (u16)fn_803E19FC(sb->w1c);

    for (i = 0; i < 11; i++) {
        dc->nickname[i] = fn_803E19FC(sc->nickname[i]);
    }
    dc->b16 = sc->b16;
    dc->b17 = sc->b17;
    dc->ribbons = fn_803E1A28(sc->ribbons);

    for (i = 0; i < 8; i++) {
        dd->otName[i] = fn_803E19FC(sd->otName[i]);
    }
    dd->b10[0] = sd->b10[0];
    dd->b10[1] = sd->b10[1];
    dd->b10[2] = sd->b10[2];
    dd->b10[3] = sd->b10[3];
    dd->b10[4] = sd->b10[4];
    dd->b10[5] = sd->b10[5];
    dd->h16 = fn_803E19FC(sd->h16);
    dd->h18 = fn_803E19FC(sd->h18);
    dd->b1a = sd->b1a;
    dd->b1b = sd->b1b;
    dd->met.otGender = sd->met.otGender;
    dd->met.metLevel = sd->met.metLevel;
    dd->b1d = sd->b1d;
    dd->h1e = fn_803E19FC(sd->h1e);

    *(u32 *)((u8 *)dst + 0x88) = fn_803E1A10(src->status);
    *((u8 *)dst + 0x8c) = src->level;
    *((u8 *)dst + 0x8d) = src->unk8D;
    *(u16 *)((u8 *)dst + 0x8e) = fn_803E19FC(src->hp);
    *(u16 *)((u8 *)dst + 0x90) = fn_803E19FC(src->maxHp);
    *(u16 *)((u8 *)dst + 0x92) = fn_803E19FC(src->attack);
    *(u16 *)((u8 *)dst + 0x94) = fn_803E19FC(src->defense);
    *(u16 *)((u8 *)dst + 0x96) = fn_803E19FC(src->speed);
    *(u16 *)((u8 *)dst + 0x98) = fn_803E19FC(src->spAttack);
    *(u16 *)((u8 *)dst + 0x9a) = fn_803E19FC(src->spDefense);
    memset((u8 *)dst + 0x9c, 0, 0x38);
    memset((u8 *)dst + 0xd4, 0, 0x18);
    if (encrypt) {
        fn_803E0398(dst, TRUE);
    }
}

}

extern "C" {

void *BoxPokemon_GetDataBlock(BoxPokemon *mon, u32 personality, u32 blockId) {
    u8 *block;
    u8 *blocks;
    personality = (personality & 0x3e000) >> 13;
    fn_803D989C(personality <= 31, lbl_80474C38);
    switch (personality) {
    case 0:
    case 24:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 1:
    case 25:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 2:
    case 26:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 3:
    case 27:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 4:
    case 28:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 5:
    case 29:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 6:
    case 30:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 7:
    case 31:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 8:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 9:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 10:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 11:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 12:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 13:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 14:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 15:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 16:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 17:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 18:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 19:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 20:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 21:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 22:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 23:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    }
    return block;
}

void *fn_803E0588(void *monp, u32 personality, u32 blockId) {
    BoxPokemonRaw *mon = (BoxPokemonRaw *)monp;
    u8 *block;
    u8 *blocks;
    personality = (personality & 0x3e000) >> 13;
    fn_803D989C(personality <= 31, lbl_80474E61);
    switch (personality) {
    case 0:
    case 24:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 1:
    case 25:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 2:
    case 26:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 3:
    case 27:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 4:
    case 28:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 5:
    case 29:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 0 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 6:
    case 30:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 7:
    case 31:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 8:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 9:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 10:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 11:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 0 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 12:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 13:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 14:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 3 * 0x20;
            break;
        }
        break;
    case 15:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 2 * 0x20;
            break;
        }
        break;
    case 16:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 17:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 0 * 0x20;
            break;
        case 3:
            block = blocks + 1 * 0x20;
            break;
        }
        break;
    case 18:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 19:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 1 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 20:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 3 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 21:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 1 * 0x20;
            break;
        case 2:
            block = blocks + 2 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 22:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 2 * 0x20;
            break;
        case 1:
            block = blocks + 3 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    case 23:
        blocks = (u8 *)mon->data;
        switch (blockId) {
        case 0:
            block = blocks + 3 * 0x20;
            break;
        case 1:
            block = blocks + 2 * 0x20;
            break;
        case 2:
            block = blocks + 1 * 0x20;
            break;
        case 3:
            block = blocks + 0 * 0x20;
            break;
        }
        break;
    }
    return block;
}

}

extern "C" {

#pragma dont_inline off
void fn_803DA474(void *mon, u32 species, u32 level, u32 ivs, u32 hasPersonality, u32 personality, u32 otIdSource, u32 otId) {
    u32 value;
    u32 iv;
    u32 tmp;
    BOOL dec;
    memset(mon, 0, sizeof(BoxPokemon));
    dec = fn_803DA318((BoxPokemon *)mon);
    if (!hasPersonality) {
        personality = LCRNG_Next() | (LCRNG_Next() << 16);
    }
    fn_803DB678((BoxPokemon *)mon, 0, &personality);
    if ((s32)otIdSource == 2) {
        do {
            otId = LCRNG_Next() | (LCRNG_Next() << 16);
        } while ((((personality & 0xffff) ^ (personality >> 16)) ^ ((otId >> 16) ^ (otId & 0xffff))) < 8);
    } else if ((s32)otIdSource != 1) {
        otId = 0;
    }
    fn_803DB678((BoxPokemon *)mon, 7, &otId);
    tmp = lbl_80643009;
    fn_803DB678((BoxPokemon *)mon, 0xc, &tmp);
    fn_803DB678((BoxPokemon *)mon, 5, &species);
    fn_803DB678((BoxPokemon *)mon, 0xb2, NULL);
    value = fn_803DBB1C(species, level);
    fn_803DB678((BoxPokemon *)mon, 8, &value);
    value = SpeciesGetValueInline(species, 0x14);
    fn_803DB678((BoxPokemon *)mon, 9, &value);
    fn_803DB678((BoxPokemon *)mon, 0x9b, &level);
    tmp = lbl_80643008;
    fn_803DB678((BoxPokemon *)mon, 0x79, &tmp);
    value = 4;
    fn_803DB678((BoxPokemon *)mon, 0x9a, &value);
    if ((s32)ivs < 32) {
        fn_803DB678((BoxPokemon *)mon, 0x46, &ivs);
        fn_803DB678((BoxPokemon *)mon, 0x47, &ivs);
        fn_803DB678((BoxPokemon *)mon, 0x48, &ivs);
        fn_803DB678((BoxPokemon *)mon, 0x49, &ivs);
        fn_803DB678((BoxPokemon *)mon, 0x4a, &ivs);
        fn_803DB678((BoxPokemon *)mon, 0x4b, &ivs);
    } else {
        value = LCRNG_Next();
        iv = value & 0x1f;
        fn_803DB678((BoxPokemon *)mon, 0x46, &iv);
        iv = (value & 0x3e0) >> 5;
        fn_803DB678((BoxPokemon *)mon, 0x47, &iv);
        iv = (value & 0x7c00) >> 10;
        fn_803DB678((BoxPokemon *)mon, 0x48, &iv);
        value = LCRNG_Next();
        iv = value & 0x1f;
        fn_803DB678((BoxPokemon *)mon, 0x49, &iv);
        iv = (value & 0x3e0) >> 5;
        fn_803DB678((BoxPokemon *)mon, 0x4a, &iv);
        iv = (value & 0x7c00) >> 10;
        fn_803DB678((BoxPokemon *)mon, 0x4b, &iv);
    }
    value = SpeciesGetValueInline(species, 0x18);
    iv = SpeciesGetValueInline(species, 0x19);
    if (iv != 0) {
        if (personality & 1) {
            fn_803DB678((BoxPokemon *)mon, 0xa, &iv);
        } else {
            fn_803DB678((BoxPokemon *)mon, 0xa, &value);
        }
    } else {
        fn_803DB678((BoxPokemon *)mon, 0xa, &value);
    }
    value = (u8)fn_803DBF64(mon);
    fn_803DB678((BoxPokemon *)mon, 0x6f, &value);
    fn_803DC2B4((BoxPokemon *)mon);
    fn_803DA33C((BoxPokemon *)mon, dec);
}
#pragma dont_inline reset

}

extern "C" {

#pragma dont_inline off
static inline u8 Pokemon_GetNatureInline(BoxPokemon *mon) {
    BOOL dec = fn_803DA318(mon);
    u32 pv = fn_803DAEFC(mon, 0, NULL);
    fn_803DA33C(mon, dec);
    return pv % 25;
}

void fn_803DA8E0(void *mon) {
    BOOL dec = fn_803DD96C((BoxPokemon *)mon);
    s32 level = GetMonDataInternal(mon, 0xa0, NULL);
    s32 maxHp = GetMonDataInternal(mon, 0xa3, NULL);
    s32 hp = GetMonDataInternal(mon, 0xa2, NULL);
    s32 hpIV = GetMonDataInternal(mon, 0x46, NULL);
    s32 hpEV = GetMonDataInternal(mon, 0xd, NULL);
    s32 atkIV = GetMonDataInternal(mon, 0x47, NULL);
    s32 atkEV = GetMonDataInternal(mon, 0xe, NULL);
    s32 defIV = GetMonDataInternal(mon, 0x48, NULL);
    s32 defEV = GetMonDataInternal(mon, 0xf, NULL);
    s32 speIV = GetMonDataInternal(mon, 0x49, NULL);
    s32 speEV = GetMonDataInternal(mon, 0x10, NULL);
    s32 spaIV = GetMonDataInternal(mon, 0x4a, NULL);
    s32 spaEV = GetMonDataInternal(mon, 0x11, NULL);
    s32 spdIV = GetMonDataInternal(mon, 0x4b, NULL);
    s32 spdEV = GetMonDataInternal(mon, 0x12, NULL);
    s32 form = GetMonDataInternal(mon, 0x70, NULL);
    s32 species = GetMonDataInternal(mon, 5, NULL);
    s32 newMaxHp;
    s32 newAtk;
    s32 newDef;
    s32 newSpe;
    s32 newSpa;
    s32 newSpd;
    SpeciesData *data = (SpeciesData *)fn_8016DF70(0, sizeof(SpeciesData));
    SpeciesData_LoadSpecies(Pokemon_GetFormStatsIndex(species, form), data);
    if (species == 292) {
        newMaxHp = 1;
    } else {
        newMaxHp = ((2 * data->baseHp + hpIV + hpEV / 4) * level / 100) + level + 10;
    }
    fn_803DB524(mon, 0xa3, &newMaxHp);
    newAtk = ((2 * data->baseAttack + atkIV + atkEV / 4) * level / 100) + 5;
    newAtk = fn_803DBD58(Pokemon_GetNatureInline((BoxPokemon *)mon), newAtk, 1);
    fn_803DB524(mon, 0xa4, &newAtk);
    newDef = ((2 * data->baseDefense + defIV + defEV / 4) * level / 100) + 5;
    newDef = fn_803DBD58(Pokemon_GetNatureInline((BoxPokemon *)mon), newDef, 2);
    fn_803DB524(mon, 0xa5, &newDef);
    newSpe = ((2 * data->baseSpeed + speIV + speEV / 4) * level / 100) + 5;
    newSpe = fn_803DBD58(Pokemon_GetNatureInline((BoxPokemon *)mon), newSpe, 3);
    fn_803DB524(mon, 0xa6, &newSpe);
    newSpa = ((2 * data->baseSpAttack + spaIV + spaEV / 4) * level / 100) + 5;
    newSpa = fn_803DBD58(Pokemon_GetNatureInline((BoxPokemon *)mon), newSpa, 4);
    fn_803DB524(mon, 0xa7, &newSpa);
    newSpd = ((2 * data->baseSpDefense + spdIV + spdEV / 4) * level / 100) + 5;
    newSpd = fn_803DBD58(Pokemon_GetNatureInline((BoxPokemon *)mon), newSpd, 5);
    fn_803DB524(mon, 0xa8, &newSpd);
    fn_8016E0A0(data);
    if (hp != 0 || maxHp == 0) {
        if (species == 292) {
            hp = 1;
        } else if (hp == 0) {
            hp = newMaxHp;
        } else {
            hp += newMaxHp - maxHp;
        }
    }
    if (hp != 0) {
        fn_803DB524(mon, 0xa2, &hp);
    }
    fn_803DA2AC((BoxPokemon *)mon, dec);
}
#pragma dont_inline reset

}

extern "C" {

void *MessageUtil_SpeciesName(u32 species, u32 heapId);
u8 MoveTable_CalcMaxPP(u32 move, u8 ppUps);

u32 BoxPokemon_GetDataInternal(BoxPokemon *mon, s32 param, void *dest) {
    u32 result = 0;
    BlockA *a = (BlockA *)BoxPokemon_GetDataBlock(mon, mon->personality, 0);
    BlockBWii *b = (BlockBWii *)BoxPokemon_GetDataBlock(mon, mon->personality, 1);
    BlockC *c = (BlockC *)BoxPokemon_GetDataBlock(mon, mon->personality, 2);
    BlockDWii *d = (BlockDWii *)BoxPokemon_GetDataBlock(mon, mon->personality, 3);

    switch (param) {
    default:
    case 0x73:
    case 0x75:
    case 0x9f:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
        result = 0;
        break;
    case 0x0:
        result = mon->personality;
        break;
    case 0x1:
        result = mon->partyDecrypted;
        break;
    case 0x2:
        result = mon->boxDecrypted;
        break;
    case 0x3:
        result = mon->checksumFailed;
        break;
    case 0x4:
        result = mon->checksum;
        break;
    case 0xab:
        result = (a->species != 0);
        break;
    case 0xac:
        result = mon->checksumFailed;
        if (!result) {
            result = b->ivs.isEgg;
        }
        break;
    case 0xad:
        result = a->species;
        if (result == 0) {
            break;
        }
        if (b->ivs.isEgg || mon->checksumFailed) {
            result = 0x1ee;
        }
        break;
    case 0xa0:
        result = Pokemon_GetSpeciesLevelAt(a->species, a->exp);
        break;
    case 0x5:
        if (mon->checksumFailed) {
            result = 0x1ee;
        } else {
            result = a->species;
        }
        break;
    case 0x6:
        result = a->item;
        break;
    case 0x7:
        result = a->otId;
        break;
    case 0x8:
        result = a->exp;
        break;
    case 0x9:
        result = a->b[0];
        break;
    case 0xa:
        result = a->b[1];
        break;
    case 0xb:
        result = a->b[2];
        break;
    case 0xc:
        result = a->b[3];
        break;
    case 0xd:
        result = a->b[4];
        break;
    case 0xe:
        result = a->b[5];
        break;
    case 0xf:
        result = a->b[6];
        break;
    case 0x10:
        result = a->b[7];
        break;
    case 0x11:
        result = a->b[8];
        break;
    case 0x12:
        result = a->b[9];
        break;
    case 0x13:
        result = a->b[10];
        break;
    case 0x14:
        result = a->b[11];
        break;
    case 0x15:
        result = a->b[12];
        break;
    case 0x16:
        result = a->b[13];
        break;
    case 0x17:
        result = a->b[14];
        break;
    case 0x18:
        result = a->b[15];
        break;
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x1f:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2c:
    case 0x2d:
    case 0x2e:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    {
        u64 bit = (u64)1 << (param - 0x19);
        result = (a->ribbons & bit) != 0;
    } break;
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
        result = *(u16 *)((u8 *)b->moves + (param - 0x36) * 2);
        break;
    case 0x3a:
    case 0x3b:
    case 0x3c:
    case 0x3d:
        result = *(param + (u8 *)b - 0x32);
        break;
    case 0x3e:
    case 0x3f:
    case 0x40:
    case 0x41:
        result = *(param + (u8 *)b - 0x32);
        break;
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
        result = MoveTable_CalcMaxPP(*(u16 *)((u8 *)b->moves + (param - 0x42) * 2), *(param + (u8 *)b - 0x36));
        break;
    case 0x46:
        result = b->ivs.hpIV;
        break;
    case 0x47:
        result = b->ivs.atkIV;
        break;
    case 0x48:
        result = b->ivs.defIV;
        break;
    case 0x49:
        result = b->ivs.speedIV;
        break;
    case 0x4a:
        result = b->ivs.spAtkIV;
        break;
    case 0x4b:
        result = b->ivs.spDefIV;
        break;
    case 0x4c:
        result = mon->checksumFailed;
        if (!result) {
            result = b->ivs.isEgg;
        }
        break;
    case 0x4d:
        result = b->ivs.hasNickname;
        break;
    case 0x4e:
    case 0x4f:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x5e:
    case 0x5f:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
    case 0x6c:
    case 0x6d:
    {
        u64 bit = (u64)1 << (param - 0x4e);
        result = (b->ribbons & bit) != 0;
    } break;
    case 0x6e:
        result = b->form.fateful;
        break;
    case 0x6f:
        result = b->form.gender;
        break;
    case 0x70:
        result = b->form.form;
        break;
    case 0x71:
        result = b->b19;
        break;
    case 0x72:
        result = b->h1a;
        break;
    case 0x74:
        if (mon->checksumFailed) {
            MessageLoader_GetSpeciesName(0x1ef, 0, dest);
        } else {
            u16 *out = (u16 *)dest;
            for (result = 0; result < 10; result++) {
                out[result] = c->nickname[result];
            }
            out[result] = 0xffff;
        }
        break;
    case 0x77:
        result = b->ivs.hasNickname;
    case 0x76:
        if (mon->checksumFailed) {
            void *buf = MessageUtil_SpeciesName(0x1ef, 0);
            Strbuf_Copy((Strbuf *)dest, (Strbuf *)buf);
            Strbuf_Free((u8 *)buf);
        } else {
            Strbuf_CopyChars((Strbuf *)dest, c->nickname);
        }
        break;
    case 0x78:
        result = c->b16;
        break;
    case 0x79:
        result = c->b17;
        break;
    case 0x7a:
    case 0x7b:
    case 0x7c:
    case 0x7d:
    case 0x7e:
    case 0x7f:
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    {
        u64 bit = (u64)1 << (param - 0x7a);
        result = (c->ribbons & bit) != 0;
    } break;
    case 0x8f: {
        u16 *out = (u16 *)dest;
        for (result = 0; result < 7; result++) {
            out[result] = d->otName[result];
        }
        out[result] = 0xffff;
    } break;
    case 0x90:
        Strbuf_CopyChars((Strbuf *)dest, d->otName);
        break;
    case 0x91:
        result = d->b10[0];
        break;
    case 0x92:
        result = d->b10[1];
        break;
    case 0x93:
        result = d->b10[2];
        break;
    case 0x94:
        result = d->b10[3];
        break;
    case 0x95:
        result = d->b10[4];
        break;
    case 0x96:
        result = d->b10[5];
        break;
    case 0x97:
        result = d->h16;
        break;
    case 0x98:
        result = d->h18;
        break;
    case 0x99:
        result = d->b1a;
        break;
    case 0x9a:
        result = d->b1b;
        break;
    case 0x9b:
        result = d->met.metLevel;
        break;
    case 0x9c:
        result = d->met.otGender;
        break;
    case 0x9d:
        result = d->b1d;
        break;
    case 0x9e:
        result = d->h1e;
        break;
    case 0xae:
        result = (b->ivs.hpIV << 0) | (b->ivs.atkIV << 5) | (b->ivs.defIV << 10) | (b->ivs.speedIV << 15) | (b->ivs.spAtkIV << 20) | (b->ivs.spDefIV << 25);
        break;
    case 0xaf:
        if ((a->species == 0x1d || a->species == 0x20) && !b->ivs.hasNickname) {
            result = FALSE;
        } else {
            result = TRUE;
        }
        break;
    case 0xb0:
    case 0xb1:
        if (a->species == 0x1ed && a->b[1] == 0x79) {
            result = (u8)Pokemon_GetArceusTypeOf((u16)Item_LoadParam(a->item, ITEM_PARAM_HOLD_EFFECT, 0));
        } else {
            result = SpeciesData_GetFormValue(a->species, b->form.form, param - 0xaa);
        }
        break;
    case 0xb2:
        MessageLoader_GetSpeciesName(a->species, 0, dest);
        break;
    }
    return result;
}

}

// Late definitions (kept at the end so they are not inlined into earlier callers)
extern "C" {

void fn_803E00D0(void *p) {
    if (p != NULL) {
        fn_8016E0A0(p);
    }
}

}

#pragma dont_inline off
