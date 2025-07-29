#ifndef __MTX_H__
#define __MTX_H__

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    f32 x, y, z;
} Vec, *VecPtr;

typedef f32 Mtx[3][4];
typedef f32 (*MtxPtr)[4];

void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);

void PSVECScale(const Vec* src, Vec* dst, f32 scale);
f32 PSVECSquareMag(const Vec* v);

#ifdef __cplusplus
}
#endif

#endif // __MTX_H__
