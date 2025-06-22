#ifndef GXENUM_H
#define GXENUM_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 GXBool;

#define GX_TRUE ((GXBool)1)
#define GX_FALSE ((GXBool)0)
#define GX_ENABLE ((GXBool)1)
#define GX_DISABLE ((GXBool)0)

#define GX_MAX_Z24 0xffffff

typedef enum _GXPixelFmt {
  GX_PF_RGB8_Z24,
  GX_PF_RGBA6_Z24,
  GX_PF_RGB565_Z16,
  GX_PF_Z24,
  GX_PF_Y8,
  GX_PF_U8,
  GX_PF_V8,
  GX_PF_YUV420
} GXPixelFmt;

typedef enum _GXZFmt16 {
  GX_ZC_LINEAR,
  GX_ZC_NEAR,
  GX_ZC_MID,
  GX_ZC_FAR
} GXZFmt16;

typedef enum _GXGamma {
    GX_GM_1_0,
    GX_GM_1_7,
    GX_GM_2_2
} GXGamma;

typedef enum _GXFBClamp {
  GX_CLAMP_NONE,
  GX_CLAMP_TOP,
  GX_CLAMP_BOTTOM
} GXFBClamp;

typedef enum _GXCopyMode {
  GX_COPY_PROGRESSIVE = 0,
  GX_COPY_INTLC_EVEN = 2,
  GX_COPY_INTLC_ODD = 3
} GXCopyMode;

typedef enum _GXMiscToken{
    GX_MT_XF_FLUSH           = 1,
    GX_MT_DL_SAVE_CONTEXT    = 2,
    GX_MT_ABORT_WAIT_COPYOUT = 3, 
    GX_MT_NULL               = 0
} GXMiscToken;

typedef enum _GXXFFlushVal {
    GX_XF_FLUSH_NONE  = 0,
    GX_XF_FLUSH_SAFE  = 8
} GXXFFlushVal;


#ifdef __cplusplus
}
#endif

#endif // GXENUM_H
