#ifndef GX_H
#define GX_H

#include <revolution/types.h>
#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>
#include <revolution/gx/GXvert.h>
#include <revolution/vi.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GXBreakPtCallback)(void);
typedef void (*GXDrawDoneCallback)(void);
typedef void (*GXDrawSyncCallback)(u16 token);

typedef GXTexRegion *(* GXTexRegionCallback)(const GXTexObj *t_obj, GXTexMapID id);
typedef GXTlutRegion *(* GXTlutRegionCallback)(u32 tlut_name);

void GXSetCPUFifo(const GXFifoObj* fifo);
void GXSetGPFifo(const GXFifoObj* fifo);
void GXGetGPStatus(GXBool* overhi, GXBool* underlow, GXBool* readIdle, GXBool* cmdIdle, GXBool* brkpt);
GXBreakPtCallback GXSetBreakPtCallback(GXBreakPtCallback cb);
void GXDisableBreakPt(void);

void GXSetVtxDescv(const GXVtxDescList* attr_list);
void GXClearVtxDesc(void);
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
void GXSetArray(GXAttr attr, const void* base_ptr, u8 stride);
void GXInvalidateVtxCache(void);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 postmtx);
void GXSetNumTexGens(u8 nTexGens);
void GXSetMisc(GXMiscToken token, u32 value);
void GXFlush(void);
void GXAbortFrame(void);
void GXSetDrawDone(void);
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb);
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb);
void GXSetLineWidth(u8 width, GXTexOffset tex_offsets);
void GXSetPointSize(u8 size, GXTexOffset tex_offsets);
void GXEnableTexOffsets(GXTexCoordID coord, GXBool line_enable, GXBool point_enable);
void GXSetCullMode(GXCullMode mode);
void GXSetCoPlanar(GXBool enable);
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

void GXInitLightAttn(GXLightObj* lt_obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
void GXInitLightSpot(GXLightObj* lt_obj, f32 cutoff, GXSpotFn spot_func);
void GXInitLightDistAttn(GXLightObj*  lt_obj, f32 ref_distance, f32 ref_brightness, GXDistAttnFn dist_func);
void GXInitLightPos(GXLightObj* lt_obj, f32 x, f32 y, f32 z);
void GXInitLightDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz);
void GXInitSpecularDir(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz);
void GXInitSpecularDirHA(GXLightObj* lt_obj, f32 nx, f32 ny, f32 nz, f32 hx, f32 hy, f32 hz);
void GXInitLightColor(GXLightObj* lt_obj, GXColor color);
void GXLoadLightObjImm(const GXLightObj* lt_obj, GXLightID light);
void GXSetChanAmbColor(GXChannelID chan, GXColor amb_color);
void GXSetChanMatColor(GXChannelID chan, GXColor mat_color);
void GXSetNumChans(u8 nChans);
void GXSetChanCtrl(GXChannelID chan, GXBool enable, GXColorSrc amb_src, GXColorSrc mat_src, GXLightID light_mask, GXDiffuseFn diff_fn, GXAttnFn attn_fn);

GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback f);
GXTlutRegionCallback GXSetTlutRegionCallback(GXTlutRegionCallback f);

void GXSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexFormat format, GXIndTexBiasSel bias_sel, GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s, GXIndTexWrap wrap_t, GXBool add_prev, GXBool utc_lod, GXIndTexAlphaSel alpha_sel);
void GXSetIndTexCoordScale(GXIndTexStageID ind_stage, GXIndTexScale scale_s, GXIndTexScale scale_t);
void GXSetIndTexOrder(GXIndTexStageID ind_stage, GXTexCoordID tex_coord, GXTexMapID tex_map);
void GXSetNumIndStages(u8 nstages);
void GXSetTevDirect(GXTevStageID tev_stage);
void GXSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXBool signed_offsets, GXBool replace_mode, GXIndTexMtxID matrix_sel);
void GXSetTevIndTile(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u16 tilesize_s, u16 tilesize_t, u16 tilespacing_s, u16 tilespacing_t, GXIndTexFormat format, GXIndTexMtxID matrix_sel, GXIndTexBiasSel bias_sel, GXIndTexAlphaSel alpha_sel);
void GXSetTevIndBumpST(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel);
void GXSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel);
void GXSetTevIndRepeat(GXTevStageID tev_stage);

void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg);
void GXSetTevColor(GXTevRegID id, GXColor color);
void GXSetTevColorS10(GXTevRegID id, GXColorS10 color);
void GXSetTevKColor(GXTevKColorID id, GXColor color);
void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel);
void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel);
void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel);
void GXSetTevSwapModeTable(GXTevSwapSel id, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias);
void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color);
void GXSetNumTevStages(u8 nStages);

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color);
void GXSetFogColor(GXColor color);
void GXInitFogAdjTable(GXFogAdjTable* table, u16 width, f32 projmtx[4][4]);
void GXSetFogRangeAdj(GXBool enable, u16 center, GXFogAdjTable* table);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetColorUpdate(GXBool update_enable);
void GXSetAlphaUpdate(GXBool update_enable);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void GXSetZCompLoc(GXBool before_tex);
void GXSetPixelFmt(GXPixelFmt pix_fmt, GXZFmt16 z_fmt);
void GXSetDither(GXBool dither);
void GXSetDstAlpha(GXBool enable, u8 alpha);
void GXSetFieldMode(GXBool field_mode, GXBool half_aspect_ratio);

void GXSetProjectionv(const f32* ptr);
void GXSetViewportJitter(f32 xOrig, f32 yOrig, f32 wd, f32 ht, f32 nearZ, f32 farZ, u32 field);
void GXSetViewport(f32 xOrig, f32 yOrig, f32 wd, f32 ht, f32 nearZ, f32 farZ);
void GXSetScissor(u32 xOrig, u32 yOrig, u32 wd, u32 ht);
void GXSetScissorBoxOffset(s32 xoffset, s32 yoffset);
void GXSetClipMode(GXClipMode mode);

#define GXInitLightShininess(lobj, shininess) \
    (GXInitLightAttn(lobj, 0.0F, 0.0F, 1.0F,  \
                    (shininess)/2.0F, 0.0F,   \
                    1.0F-(shininess)/2.0F ))

#ifdef __cplusplus
}
#endif

#endif // GX_H
