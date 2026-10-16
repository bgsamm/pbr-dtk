#ifndef REVOLUTION_MTX_H
#define REVOLUTION_MTX_H

#include <revolution/mtx/GeoTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// Mtx

void PSMTXIdentity(Mtx m);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
u32 PSMTXInverse(const Mtx src, Mtx inv);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXQuat(Mtx, const Quaternion *);

void C_MTXIdentity(Mtx m);
void C_MTXCopy(const Mtx src, Mtx dst);
void C_MTXConcat(const Mtx a, const Mtx b, Mtx ab);
u32 C_MTXInverse(const Mtx src, Mtx inv);
u32 C_MTXInvXpose(const Mtx src, Mtx invX);
void C_MTXRotRad(Mtx m, char axis, f32 rad);
void C_MTXRotTrig(Mtx m, char axis, f32 sinA, f32 cosA);
void C_MTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void C_MTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
void C_MTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void C_MTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void C_MTXQuat(Mtx, const Quaternion *);

#ifdef DEBUG
#define MTXIdentity C_MTXIdentity
#define MTXCopy C_MTXCopy
#define MTXConcat C_MTXConcat
#define MTXInverse C_MTXInverse
#define MTXInvXpose C_MTXInvXpose
#define MTXRotRad C_MTXRotRad
#define MTXRotTrig C_MTXRotTrig
#define MTXTrans C_MTXTrans
#define MTXTransApply C_MTXTransApply
#define MTXScale C_MTXScale
#define MTXScaleApply C_MTXScaleApply
#define MTXQuat C_MTXQuat
#else
#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXInverse PSMTXInverse
#define MTXInvXpose PSMTXInvXpose
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXQuat PSMTXQuat
#endif // DEBUG

void MTXLookAt(Mtx m, const Point3d *camPos, const Vec *camUp, const Point3d *target);
void MTXLightFrustum(Mtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void MTXLightOrtho(Mtx, f32, f32, f32, f32, f32, f32, f32, f32);
void MTXLightPerspective(Mtx, f32, f32, f32, f32, f32, f32);

// MtxVec

void PSMTXMultVec(const Mtx m, const Vec *src, Vec *dst);
void PSMTXMultVecSR(const Mtx m, const Vec *src, Vec *dst);

void C_MTXMultVec(const Mtx m, const Vec *src, Vec *dst);
void C_MTXMultVecSR(const Mtx m, const Vec *src, Vec *dst);

#ifdef DEBUG
#define MTXMultVec C_MTXMultVec
#define MTXMultVecSR C_MTXMultVecSR
#else
#define MTXMultVec PSMTXMultVec
#define MTXMultVecSR PSMTXMultVecSR
#endif // DEBUG

// Mtx44

void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f);
void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

#define MTXFrustum C_MTXFrustum
#define MTXPerspective C_MTXPerspective
#define MTXOrtho C_MTXOrtho

// Vec

void PSVECAdd(const Vec *a, const Vec *b, Vec *ab);
void PSVECCrossProduct(const Vec *a, const Vec *b, Vec *axb);
void PSVECNormalize(const Vec *src, Vec *dst);
void PSVECScale(const Vec *src, Vec *dst, f32 scale);
f32 PSVECSquareMag(Vec *vec);
void PSVECSubtract(const Vec *a, const Vec *b, Vec *ab);

void C_VECAdd(const Vec *a, const Vec *b, Vec *ab);
void C_VECCrossProduct(const Vec *a, const Vec *b, Vec *axb);
void C_VECNormalize(const Vec *src, Vec *dst);
void C_VECScale(const Vec *src, Vec *dst, f32 scale);
f32 C_VECSquareMag(Vec *vec);
void C_VECSubtract(const Vec *a, const Vec *b, Vec *ab);

#ifdef DEBUG
#define VECAdd C_VECAdd
#define VECCrossProduct C_VECCrossProduct
#define VECNormalize C_VECNormalize
#define VECScale C_VECScale
#define VECSquareMag C_VECSquareMag
#define VECSubtract C_VECSubtract
#else
#define VECAdd PSVECAdd
#define VECCrossProduct PSVECCrossProduct
#define VECNormalize PSVECNormalize
#define VECScale PSVECScale
#define VECSquareMag PSVECSquareMag
#define VECSubtract PSVECSubtract
#endif // DEBUG

// From doldecomp/ogws (CC0), include/revolution/MTX/*.h
void PSMTXConcatArray(const Mtx, const Mtx, Mtx, u32);
void PSMTXTranspose(const Mtx, Mtx);
void PSMTXRotAxisRad(Mtx, const Vec*, f32);
void C_MTXLookAt(Mtx, const Vec*, const Vec*, const Vec*);
void C_MTXLightFrustum(Mtx, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void C_MTXLightPerspective(Mtx, f32, f32, f32, f32, f32, f32);
void C_MTXLightOrtho(Mtx, f32, f32, f32, f32, f32, f32, f32, f32);
void PSQUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* prod);
void PSQUATNormalize(const Quaternion* in, Quaternion* out);
void C_QUATMtx(Quaternion* quat, const Mtx mtx);
void C_QUATSlerp(const Quaternion* a, const Quaternion* b, Quaternion* out,
                 f32 t);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);

#ifdef __cplusplus
}
#endif

#endif // REVOLUTION_MTX_H
