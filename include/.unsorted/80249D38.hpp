#pragma once

#include <revolution/types.h>

struct Unk80249D38 {
    /* 0x00000 */ u8 unk00000[0xD54];
    /* 0x00D54 */ s16 _D54;
    /* 0x00D56 */ u8 unk00D56[0xF304];
    // size: 0x1005A
};

/* lbl_80497FEC */ extern Unk80249D38 lbl_80497FEC;

extern "C" {
// TODO Replace with proper imports (methods of the object above, not decompiled yet)
void fn_8024A464(Unk80249D38 *obj, u32 a);
void fn_8024A758(Unk80249D38 *obj, u32 a);
void fn_8024AB50(Unk80249D38 *obj, u32 a);
void fn_8024AE58(Unk80249D38 *obj, u32 a);
void fn_8024AFA4(Unk80249D38 *obj, u32 a);
void fn_8024B3D4(Unk80249D38 *obj);
void fn_8024B440(Unk80249D38 *obj, u32 a);
void fn_8024BB74();
void fn_8024BC58(Unk80249D38 *obj);
void fn_8024C440(Unk80249D38 *obj, u32 a);
void fn_8024C504(Unk80249D38 *obj, u32 a);
void fn_8024F8C8(Unk80249D38 *obj, u32 a);
void fn_8024FA74(Unk80249D38 *obj, u32 a);
}
