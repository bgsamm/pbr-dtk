#ifndef RVL_SDK_MTX_QUAT_H
#define RVL_SDK_MTX_QUAT_H

#include <revolution/mtx/GeoTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO(samm) Debug versions
#define QUATInverse PSQUATInverse
#define QUATMultiply PSQUATMultiply
#define QUATNormalize PSQUATNormalize
#define QUATMtx C_QUATMtx
#define QUATSlerp C_QUATSlerp
#define QUATSquad C_QUATSquad
#define QUATRotAxisRad C_QUATRotAxisRad

void PSQUATInverse(const Quaternion *, Quaternion *);
void PSQUATMultiply(const Quaternion *, const Quaternion *, Quaternion *);
void PSQUATNormalize(const Quaternion *, Quaternion *);
void C_QUATMtx(Quaternion *, const Mtx);
void C_QUATSlerp(const Quaternion *, const Quaternion *, Quaternion *, f32);
void C_QUATSquad(const Quaternion *, const Quaternion *, const Quaternion *, const Quaternion *, Quaternion *, f32);

void C_QUATRotAxisRad(Quaternion *, const Vec *, f32);

#ifdef __cplusplus
}
#endif
#endif
