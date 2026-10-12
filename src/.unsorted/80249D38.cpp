#include ".unsorted/80249D38.hpp"

#include "gs/GSmem.hpp"

#include <string.h>

#include "common.hpp"

extern "C" {

/* lbl_803FD8C8 */ extern s16 lbl_803FD8C8[10];
extern f32 lbl_8063F8D8;
extern u8 lbl_8063F8CE;
extern u8 lbl_8063F8D6;
extern u8 lbl_8063D9B8;
extern s16 *lbl_8063F8D0;
extern s16 lbl_8063F8D4;

// TODO role: registers a blob in the first free entry of the three tables at 0x64F34, 0x64F54 and 0x64F74; returns the
// entry or -1
s32 fn_8024AE58(Unk80249D38 *obj, u32 *blob) {
    s32 i = fn_8024AEC0(obj);
    if (i == -1) {
        return -1;
    }
    obj->_64F34[i] = blob;
    obj->_64F54[i] = blob[2];
    obj->_64F74[i] = blob[3];
    return i;
}

// TODO role: index of the first free entry of the table at 0x64F54, or -1
s32 fn_8024AEC0(Unk80249D38 *obj) {
    for (s32 i = 0; i < 8; i++) {
        if (obj->_64F54[i] == 0) {
            return i;
        }
    }
    return -1;
}

// TODO role: pointer into the blob of the loaded table whose key matches entry `index` (1-based) of the list at 0xD38,
// or null
void *fn_8024AFFC(Unk80249D38 *obj, u32 index) {
    if (index < 1 || index > obj->_D34) {
        return NULL;
    }
    u16 key = obj->_D38[index - 1]._00;
    u16 sub = obj->_D38[index - 1]._02;
    for (s32 i = 0; i < 8; i++) {
        if (obj->_64F54[i] == key) {
            u32 *base = obj->_64F34[i];
            return (u8 *)base + base[sub + 3];
        }
    }
    return NULL;
}

// TODO role: looks a table up by key and initialises a track from it; returns 0 when the key is unknown
u32 fn_8024B084(Unk80249D38 *obj, u32 key, u8 flag, u8 c) {
    Unk8015AAF0 track;
    track._00 = fn_8024AFFC(obj, key);
    if (track._00 == NULL) {
        return 0;
    }
    track._04 = key;
    return fn_8024B180(obj, &track, 0, 0, c, 1, 0, 0, 0, flag);
}

// TODO role: same as fn_8024B084 with the table given directly
u32 fn_8024B11C(Unk80249D38 *obj, void *table, u8 flag, u8 c) {
    Unk8015AAF0 track;
    track._00 = table;
    if (table == NULL) {
        return 0;
    }
    track._04 = -1;
    return fn_8024B180(obj, &track, 0, 0, c, 1, 0, 0, 0, flag);
}

// TODO role: initialises a track from the arguments and sets it up through fn_8024C504 and fn_8024C440; returns two of
// its members packed in one word
u32 fn_8024B180(Unk80249D38 *obj, Unk8015AAF0 *track, u8 a, s16 b, u8 c, u8 d, u32 e, u32 f, u32 g, u8 h) {
    track->_18 = a;
    track->_26 = b;
    track->_28 = c;
    track->_59 = d;
    track->_08 = 0;
    track->_0C = 0;
    track->_10 = 0;
    track->_12 = 0;
    track->_14 = 0;
    track->_19 = 0;
    track->_1A = 0;
    track->_1E = -1;
    track->_20 = -1;
    track->_22 = -1;
    track->_24 = -1;
    track->_1C = 0;
    track->_1B = 0;
    switch (obj->_64F74[0]) {
        case 0x4A504A50: // 'JPJP'
            track->_44 = 0;
            break;
        case 0x46524652: // 'FRFR'
        case 0x47524752: // 'GRGR'
        case 0x49544954: // 'ITIT'
        case 0x53505350: // 'SPSP'
        case 0x5553554B: // 'USUK'
            track->_44 = 1;
            break;
    }
    track->_40 = -1;
    track->_34 = e;
    track->_38 = f;
    track->_3C = g;
    track->_5A = 0;
    track->_5C = 0;
    track->_60 = 0;
    track->_64 = 1;
    for (s32 i = 0; i < 8; i++) {
        track->_68[i] = NULL;
    }
    fn_8024C504(obj, track);
    fn_8024C440(obj, track);
    if (h != 0) {
        track->_60 = (track->_60 + track->_26) + track->_3C;
    } else {
        track->_60 = obj->_D80[track->_18] + (track->_60 + track->_3C);
    }
    return (track->_60 << 16) | track->_5C;
}

// TODO role: runs fn_8024B084 with the globals at 0x8063F8CE to 0x8063F8D4 set up, then clears the output; returns the
// incremented counter
s16 fn_8024B364(Unk80249D38 *obj, u32 key, s16 *out) {
    lbl_8063F8D0 = out;
    lbl_8063F8CE = 1;
    lbl_8063F8D4 = 0;
    fn_8024B084(obj, key, 1, 0);
    if (lbl_8063F8D0 != NULL) {
        *lbl_8063F8D0 = 0;
    }
    s16 count = lbl_8063F8D4 + 1;
    lbl_8063F8D0 = NULL;
    lbl_8063F8D4 = count;
    lbl_8063F8CE = 0;
    return count;
}

// TODO role: clears the member at 0x04 of each of the eight tracks and releases their children
void fn_8024B3D4(Unk80249D38 *obj) {
    for (s32 i = 0; i < 8; i++) {
        obj->_64F94[i]._04 = 0;
        fn_8024C440(obj, &obj->_64F94[i]);
    }
}

// TODO role: finds the track whose member at 0x04 equals the argument, clears it and releases its children; returns 1
// when found
u32 fn_8024B440(Unk80249D38 *obj, u32 value) {
    for (s32 i = 0; i < 8; i++) {
        if (obj->_64F94[i]._04 == value) {
            obj->_64F94[i]._04 = 0;
            fn_8024C440(obj, &obj->_64F94[i]);
            return 1;
        }
    }
    return 0;
}

// TODO role: forwards to fn_8024BB74
BOOL fn_8024B4B0(Unk80249D38 *obj, u32 value) {
    return fn_8024BB74(obj, value);
}

// TODO role: 1 when one of the eight tracks has the argument in its member at 0x04
BOOL fn_8024BB74(Unk80249D38 *obj, u32 value) {
    for (s32 i = 0; i < 8; i++) {
        if (obj->_64F94[i]._04 == value) {
            return TRUE;
        }
    }
    return FALSE;
}

// TODO role: updates the eight tracks, then clears the buffer selected by the member at 0x08 and flips it
void fn_8024BC58(Unk80249D38 *obj) {
    if (lbl_8063F8D6 == 0) {
        return;
    }
    if (lbl_8063D9B8 != 0) {
        if (obj->_64DC8 != 0) {
            fn_8024FC4C(obj);
        }
        lbl_8063D9B8 = 0;
    }
    for (u32 i = 0; i < 8; i++) {
        if (obj->_64F94[i]._04 == 0) {
            continue;
        }
        Unk8015AAF0 *track = &obj->_64F94[i];
        switch (obj->_64F94[i]._98) {
            case 1:  fn_8024C19C(obj, i); break;
            case 2:  fn_8024C42C(obj, i); break;
            case 3:  fn_8024C430(obj, i); break;
            case 4:  fn_8024C434(obj, i); break;
            case 5:  fn_8024C438(obj, i); break;
            case 6:  fn_8024C43C(obj, i); break;
            default: fn_8024BED0(obj, i); break;
        }
        fn_8024BEA4(obj, track);
        fn_8024C504(obj, track);
        if (obj->_64F94[i]._64 == 0) {
            obj->_64F94[i]._04 = 0;
            fn_8024C440(obj, track);
        }
    }
    for (s32 j = 0; j < 256; j++) {
        if (obj->_C0C[j] == 0) {
            obj->_0C[j][obj->_08] = 0;
        }
    }
    memset(obj->_C0C, 0, 256);
    obj->_08 ^= 1;
}

// TODO role: empty handlers selected by the type byte of a track in fn_8024BC58
void fn_8024C42C(Unk80249D38 *, u32) {}
void fn_8024C430(Unk80249D38 *, u32) {}
void fn_8024C434(Unk80249D38 *, u32) {}
void fn_8024C438(Unk80249D38 *, u32) {}
void fn_8024C43C(Unk80249D38 *, u32) {}

// TODO role: frees the eight child tracks of a track, recursively
void fn_8024C440(Unk80249D38 *obj, Unk8015AAF0 *track) {
    for (s32 i = 0; i < 8; i++) {
        if (track->_68[i] != NULL) {
            fn_8024C440(obj, track->_68[i]);
            fn_8024FF4C(obj, track->_68[i]);
            track->_68[i] = NULL;
        }
    }
}

// TODO role: 8-bit field stored shifted by 5 at 0xD54, with its getter
void fn_8024F958(Unk80249D38 *obj, u8 v) {
    obj->_D54 = v << 5;
}

u8 fn_8024F964(Unk80249D38 *obj) {
    return (obj->_D54 >> 5) & 0xFF;
}

// TODO role: stores the index in the track and, when its member at 0x26 is 0, loads it from a table chosen by the
// member at 0x28
void fn_8024F970(Unk80249D38 *obj, Unk8015AAF0 *track, u8 index) {
    track->_18 = index;
    if (track->_26 != 0) {
        return;
    }
    if (track->_28 != 0) {
        track->_26 = lbl_803FD8C8[index];
    } else {
        track->_26 = obj->_D6C[index];
    }
}

// TODO role: setters on a second record (0x34 as a signed byte; 0x64, 0x1E and 0x20 reset)
void fn_8024F9B8(Unk80249D38 *, Unk8015AAF0 *arg, s32 value) {
    arg->_34 = (s8)value;
}

void fn_8024FA5C(Unk80249D38 *, Unk8015AAF0 *arg) {
    arg->_64 = 0;
    arg->_1E = -1;
    arg->_20 = -1;
}

// TODO role: allocates from the second game heap, size rounded up to a multiple of 32
void *fn_8024FF3C(Unk80249D38 *, u32 size) {
    return GSmem::allocFromHeap(gUnkHeap2, (size + 0x1F) & ~0x1F);
}

// TODO role: frees a block of that heap when it is not null
void fn_8024FF4C(Unk80249D38 *, void *block) {
    if (block != NULL) {
        GSmem::freeToHeap(gUnkHeap2, block);
    }
}

// TODO role: the wrappers below call methods of the global object lbl_80497FEC
void fn_8025004C(u32 a) {
    fn_8024A464(&lbl_80497FEC, a);
}

void fn_8025005C(u32 a) {
    fn_8024A758(&lbl_80497FEC, a);
}

void fn_8025006C(u32 *blob) {
    fn_8024AE58(&lbl_80497FEC, blob);
}

void fn_8025007C(u32 a) {
    fn_8024AB50(&lbl_80497FEC, a);
}

void fn_8025008C(u32 a) {
    fn_8024AFA4(&lbl_80497FEC, a);
}

void fn_802502BC(void) {
    fn_8024BC58(&lbl_80497FEC);
}

void fn_802502C8(void) {
    fn_8024B3D4(&lbl_80497FEC);
}

u32 fn_802502D4(u32 value) {
    return fn_8024B440(&lbl_80497FEC, value);
}

BOOL fn_802502E4(u32 value) {
    return fn_8024B4B0(&lbl_80497FEC, value);
}

void fn_8025032C(Unk8015AAF0 *track) {
    fn_8024C504(&lbl_80497FEC, track);
}

// TODO role: allocates from the object above, or returns null for a size of 0
void *fn_8025033C(u32 size) {
    if (size == 0) {
        return NULL;
    }
    return fn_8024FF3C(&lbl_80497FEC, size);
}

void fn_80250360(void *block) {
    fn_8024FF4C(&lbl_80497FEC, block);
}

void fn_80250370(Unk8015AAF0 *track, u8 index) {
    fn_8024F970(&lbl_80497FEC, track, index);
}

void fn_80250388(Unk8015AAF0 *track) {
    fn_8024C440(&lbl_80497FEC, track);
}

u32 fn_80250398(u32 key, u8 flag, u8 c) {
    return fn_8024B084(&lbl_80497FEC, key, flag, c);
}

u32 fn_802503B8(void *table, u8 flag, u8 c) {
    return fn_8024B11C(&lbl_80497FEC, table, flag, c);
}

s16 fn_802503D8(u32 key, s16 *out) {
    return fn_8024B364(&lbl_80497FEC, key, out);
}

void fn_802503F0(u32 a) {
    fn_8024FA74(&lbl_80497FEC, a);
}

void fn_80250400(u32 a, u32 b, u32 c) {
    fn_8024B9C4(&lbl_80497FEC, a, b, c);
}

void fn_80250644(u32 a) {
    fn_8024F8C8(&lbl_80497FEC, a);
}

void fn_80250654(u8 v) {
    fn_8024F958(&lbl_80497FEC, v);
}

u8 fn_80250664(void) {
    return fn_8024F964(&lbl_80497FEC);
}

// TODO role: sets a float global; the next function sets it to 0.59
void fn_80250ECC(f32 v) {
    lbl_8063F8D8 = v;
}

void fn_80250ED4(void) {
    lbl_8063F8D8 = 0.59f;
}
}
