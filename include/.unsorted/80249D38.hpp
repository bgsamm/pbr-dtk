#pragma once

#include ".unsorted/8015AAF0.hpp"

#include <revolution/types.h>

struct Unk80249D38_D38 {
    /* 0x0 */ u16 _00;
    /* 0x2 */ u16 _02;
    // size: 0x4
};

struct Unk80249D38 {
    /* 0x00000 */ u8 unk00000[8];
    /* 0x00008 */ u8 _08;
    /* 0x00009 */ u8 unk00009[3];
    /* 0x0000C */ u32 _0C[256][2];
    /* 0x0080C */ u8 unk0080C[0x400];
    /* 0x00C0C */ u8 _C0C[256];
    /* 0x00D0C */ u8 unk00D0C[0x28];
    /* 0x00D34 */ u32 _D34;
    /* 0x00D38 */ Unk80249D38_D38 *_D38;
    /* 0x00D3C */ u8 unk00D3C[0x18];
    /* 0x00D54 */ s16 _D54;
    /* 0x00D56 */ u8 unk00D56[0x16];
    /* 0x00D6C */ s16 _D6C[10];
    /* 0x00D80 */ u16 _D80[10]; // indexed like _D6C
    /* 0x00D94 */ u8 unk00D94[0x64030];
    /* 0x64DC4 */ void (*_64DC4)(u32 id, void *data);
    /* 0x64DC8 */ u32 (*_64DC8)(u32 id);
    /* 0x64DCC */ u8 unk64DCC[0x140];
    /* 0x64F0C */ u8 unk64F0C[0x28];
    /* 0x64F34 */ u32 *_64F34[8];
    /* 0x64F54 */ u32 _64F54[8];
    /* 0x64F74 */ u32 _64F74[8];
    /* 0x64F94 */ Unk8015AAF0 _64F94[8];
    // size: 0x654B4
};

/* lbl_80497FEC */ extern Unk80249D38 lbl_80497FEC;

extern "C" {
s32 fn_8024AEC0(Unk80249D38 *obj);
void *fn_8024AFFC(Unk80249D38 *obj, u32 index);
u32 fn_8024B084(Unk80249D38 *obj, u32 key, u8 flag, u8 c);
u32 fn_8024B11C(Unk80249D38 *obj, void *table, u8 flag, u8 c);
u32 fn_8024B180(Unk80249D38 *obj, Unk8015AAF0 *track, u8 a, s16 b, u8 c, u8 d, u32 e, u32 f, u32 g, u8 h);
s16 fn_8024B364(Unk80249D38 *obj, u32 key, s16 *out);
BOOL fn_8024BB74(Unk80249D38 *obj, u32 value);
void fn_8024BEA4(Unk80249D38 *obj, Unk8015AAF0 *track);
void fn_8024C42C(Unk80249D38 *obj, u32 index);
void fn_8024C430(Unk80249D38 *obj, u32 index);
void fn_8024C434(Unk80249D38 *obj, u32 index);
void fn_8024C438(Unk80249D38 *obj, u32 index);
void fn_8024C43C(Unk80249D38 *obj, u32 index);
void fn_8024C440(Unk80249D38 *obj, Unk8015AAF0 *track);
void fn_8024FA74(Unk80249D38 *obj, Unk8015AAF0 *track);
void fn_8024FC4C(Unk80249D38 *obj);
void fn_8024FF4C(Unk80249D38 *obj, void *block);
void fn_8024FF60(Unk80249D38 *obj, const u16 *src, u16 *dst);
void fn_8025032C(Unk8015AAF0 *track);
void *fn_8025033C(u32 size);
void fn_80250388(Unk8015AAF0 *track);
s16 fn_802503D8(u32 key, s16 *out);

// TODO Replace with proper imports (methods of the object above, not decompiled yet)
void fn_8024A464(Unk80249D38 *obj, u32 a);
void fn_8024A758(Unk80249D38 *obj, u32 a);
void fn_8024AB50(Unk80249D38 *obj, u32 a);
void fn_8024AFA4(Unk80249D38 *obj, u32 a);
void fn_8024B9C4(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024BED0(Unk80249D38 *obj, u32 index);
void fn_8024C19C(Unk80249D38 *obj, u32 index);
void fn_8024C504(Unk80249D38 *obj, Unk8015AAF0 *track);
void fn_8024F8C8(Unk80249D38 *obj, u32 a);
}
