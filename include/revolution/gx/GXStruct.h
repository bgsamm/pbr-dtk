#ifndef GXSTRUCT_H
#define GXSTRUCT_H

#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/vi/vitypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _GXColor {
    u8 r, g, b, a;
} GXColor;

typedef struct _GXRenderModeObj {
    /* 0x0 */ VITVMode viTVmode;
    /* 0x4 */ u16 fbWidth;
    /* 0x6 */ u16 efbHeight;
    /* 0x8 */ u16 xfbHeight;
    /* 0xA */ u16 viXOrigin;
    /* 0xC */ u16 viYOrigin;
    /* 0xE */ u16 viWidth;
    /* 0x10 */ u16 viHeight;
    /* 0x14 */ VIXFBMode xFBmode;
    /* 0x18 */ u8 field_rendering;
    /* 0x19 */ GXBool aa;
    /* 0x1A */ u8 sample_pattern[12][2];
    /* 0x32 */ u8 vfilter[7];
} GXRenderModeObj;

typedef struct _GXFifoObj {
    u8* base;
    u8* top;
    u32 size;
    u32 hiWatermark;
    u32 loWatermark;
    void* rdPtr;
    void* wrPtr;
    s32 count;
    GXBool wrap;
    GXBool bind_cpu;
    GXBool bind_gp;
} GXFifoObj;

#ifdef __cplusplus
}
#endif

#endif // GXSTRUCT_H
