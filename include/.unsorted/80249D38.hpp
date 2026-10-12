#pragma once

#include ".unsorted/8015AAF0.hpp"

#include <revolution/types.h>

struct Unk80249D38 {
    /* 0x00000 */ u8 unk00000[0xD54];
    /* 0x00D54 */ s16 _D54;
    /* 0x00D56 */ u8 unk00D56[0x16];
    /* 0x00D6C */ s16 _D6C[256]; // indexed by a byte
    /* 0x00F6C */ u8 unk00F6C[0x63FA0];
    /* 0x64F0C */ u8 unk64F0C[0x48];
    /* 0x64F54 */ u32 _64F54[8];
    /* 0x64F74 */ u8 unk64F74[0x20];
    /* 0x64F94 */ Unk8015AAF0 _64F94[8];
    // size: 0x654B4
};

/* lbl_80497FEC */ extern Unk80249D38 lbl_80497FEC;

extern "C" {
void fn_8024C440(Unk80249D38 *obj, Unk8015AAF0 *track);
void fn_8024FF4C(Unk80249D38 *obj, void *block);
void fn_8025032C(void *a);
void *fn_8025033C(u32 size);
void fn_80250388(Unk8015AAF0 *track);

// TODO Replace with proper imports (methods of the object above, not decompiled yet)
void fn_8024A464(Unk80249D38 *obj, u32 a);
void fn_8024A758(Unk80249D38 *obj, u32 a);
void fn_8024AB50(Unk80249D38 *obj, u32 a);
void fn_8024AE58(Unk80249D38 *obj, u32 a);
void fn_8024AFA4(Unk80249D38 *obj, u32 a);
void fn_8024B084(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024B11C(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024B364(Unk80249D38 *obj, u32 a, u32 b);
void fn_8024B9C4(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024BB74();
void fn_8024BC58(Unk80249D38 *obj);
void fn_8024C504(Unk80249D38 *obj, void *a);
void fn_8024F8C8(Unk80249D38 *obj, u32 a);
void fn_8024FA74(Unk80249D38 *obj, u32 a);
}
