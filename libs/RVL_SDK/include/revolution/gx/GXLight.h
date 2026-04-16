#ifndef REVOLUTION_GX_LIGHTING_H
#define REVOLUTION_GX_LIGHTING_H

#include <revolution/gx/GXEnum.h>
#include <revolution/gx/GXStruct.h>
#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

///////////// LIGHT FUNCTIONS //////////////
// Init functions.
extern void GXInitLightAttn(GXLightObj* obj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
extern void GXInitLightAttnA(GXLightObj* obj, f32 a0, f32 a1, f32 a2);
extern void GXInitLightAttnK(GXLightObj* obj, f32 k0, f32 k1, f32 k2);

extern void GXInitLightSpot(GXLightObj* obj, f32 cutoff, GXSpotFn spotFunc);
extern void GXInitLightDistAttn(GXLightObj* obj, f32 refDist, f32 refBrightness, GXDistAttnFn distFunc);

extern void GXInitLightPos(GXLightObj* obj, f32 x, f32 y, f32 z);
extern void GXInitLightDir(GXLightObj* obj, f32 nX, f32 nY, f32 nZ);
extern void GXInitSpecularDir(GXLightObj* obj, f32 nX, f32 nY, f32 nZ);
extern void GXInitSpecularDirHA(GXLightObj* obj, f32 nX, f32 nY, f32 nZ, f32 hX, f32 hY, f32 hZ);
extern void GXInitLightColor(GXLightObj* obj, GXColor color);

// Load functions.
extern void GXLoadLightObjImm(const GXLightObj* obj, GXLightID light);
extern void GXLoadLightObjIndx(u32 objIndex, GXLightID light);

// Set functions.
extern void GXSetChanAmbColor(GXChannelID channel, GXColor color);
extern void GXSetChanMatColor(GXChannelID channel, GXColor color);
extern void GXSetNumChans(u8 count);
extern void GXSetChanCtrl(GXChannelID channel, GXBool doEnable, GXColorSrc ambSrc, GXColorSrc matSrc, u32 mask, GXDiffuseFn diffFunc,
                          GXAttnFn attnFunc);
						  
// Get functions.
extern void GXGetLightPos(const GXLightObj* obj, f32* x, f32* y, f32* z);
extern void GXGetLightDir(const GXLightObj* obj, f32* nX, f32* nY, f32* nZ);

extern void GXGetLightAttnA(GXLightObj* obj, f32* a0, f32* a1, f32* a2);
extern void GXGetLightAttnK(GXLightObj* obj, f32* k0, f32* k1, f32* k2);

extern void GXGetLightColor(GXLightObj* obj, GXColor* color);

////////////////////////////////////////////

/////////////// LIGHT MACROS ///////////////
#define GXInitLightPosVec(obj, vec) (GXInitLightPos((obj), *(f32*)(vec), *((f32*)(vec) + 1), *((f32*)(vec) + 2)))

#define GXInitLightDirVec(obj, vec) (GXInitLightDir((obj), *(f32*)(vec), *((f32*)(vec) + 1), *((f32*)(vec) + 2)))

#define GXInitSpecularDirVec(obj, vec) (GXInitSpecularDir((obj), *(f32*)(vec), *((f32*)(vec) + 1), *((f32*)(vec) + 2)))

#define GXInitLightShininess(obj, shine) (GXInitLightAttn((obj), 0.0f, 0.0f, 1.0f, (shine) / 2.0f, 0.0f, 1.0f - (shine) / 2.0f))

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_GX_LIGHTING_H
