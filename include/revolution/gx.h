#ifndef GX_H
#define GX_H

#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>
#include <revolution/vi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXBreakPtCallback)(void);
typedef void (*GXDrawDoneCallback)(void);

void GXSetCPUFifo(const GXFifoObj* fifo);
void GXSetGPFifo(const GXFifoObj* fifo);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
void GXDisableBreakPt(void);

void GXSetMisc(GXMiscToken token, u32 value);
void GXFlush(void);
void GXSetDrawDone(void);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback);
void GXSetDispCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetDispCopyDst(u16 wd, u16 ht);
void GXSetDispCopyFrame2Field(GXCopyMode mode);
void GXSetCopyClamp(GXFBClamp clamp);
u16 GXGetNumXfbLines(u16 efbHeight, f32 yscale);
f32 GXGetYScaleFactor(u16 efbHeight, u16 xfbHeight);
u32 GXSetDispCopyYScale(f32 yscale);
void GXSetCopyClear(GXColor clear_clr, u32 clear_z);
void GXSetCopyFilter(GXBool aa, const u8 sample_pattern[12][2], GXBool vf, const u8 vfilter[7]);
void GXSetDispCopyGamma(GXGamma gamma);
void GXCopyDisp(void* dest, GXBool clear);

void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio);
void GXSetViewportJitter(f32 xOrig, f32 yOrig, f32 wd, f32 ht, f32 nearZ, f32 farZ, u32 field);
void GXSetViewport(f32 xOrig, f32 yOrig, f32 wd, f32 ht, f32 nearZ, f32 farZ);
void GXSetScissor(u32 xOrig, u32 yOrig, u32 wd, u32 ht);
void GXSetScissorBoxOffset(s32 xoffset, s32 yoffset);

#ifdef __cplusplus
}
#endif

#endif // GX_H
