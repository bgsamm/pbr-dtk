#pragma once

#include <revolution/types.h>

struct Unk80249D38 {
    /* 0x00000 */ u8 unk00000[0xD54];
    /* 0x00D54 */ s16 _D54;
    /* 0x00D56 */ u8 unk00D56[0xF304];
    // size: 0x1005A
};

struct Unk8024F9B8 {
    /* 0x00 */ u8 unk00[0x1E];
    /* 0x1E */ s16 _1E;
    /* 0x20 */ s16 _20;
    /* 0x22 */ u8 unk22[0x12];
    /* 0x34 */ s32 _34;
    /* 0x38 */ u8 unk38[0x2C];
    /* 0x64 */ u8 _64;
    // size: unknown
};

/* lbl_80497FEC */ extern Unk80249D38 lbl_80497FEC;

extern "C" {
void fn_8025032C(void *a);
void *fn_8025033C(u32 size);
void fn_80250388(void *a);

// TODO Replace with proper imports (methods of the object above, not decompiled yet)
void fn_8024A464(Unk80249D38 *obj, u32 a);
void fn_8024A758(Unk80249D38 *obj, u32 a);
void fn_8024AB50(Unk80249D38 *obj, u32 a);
void fn_8024AE58(Unk80249D38 *obj, u32 a);
void fn_8024AFA4(Unk80249D38 *obj, u32 a);
void fn_8024B084(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024B11C(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024B364(Unk80249D38 *obj, u32 a, u32 b);
void fn_8024B3D4(Unk80249D38 *obj);
void fn_8024B440(Unk80249D38 *obj, u32 a);
void fn_8024B9C4(Unk80249D38 *obj, u32 a, u32 b, u32 c);
void fn_8024BB74();
void fn_8024BC58(Unk80249D38 *obj);
void fn_8024C440(Unk80249D38 *obj, void *a);
void fn_8024C504(Unk80249D38 *obj, void *a);
void fn_8024F8C8(Unk80249D38 *obj, u32 a);
void fn_8024F970(Unk80249D38 *obj, u32 a, u32 b);
void fn_8024FA74(Unk80249D38 *obj, u32 a);
}
