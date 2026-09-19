#pragma once

#include <revolution.h>

struct GSanimTrackData;
struct GSkeyframe;
struct GSquat;
struct GSvec2;
struct GSvec3;

namespace GSmath {

void animInterpolateS8(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
void animInterpolateU8(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
void animInterpolateS16(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
void animInterpolateU16(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
void animInterpolateQuat(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
f32 fn_80221B2C(f32 cursor, GSanimTrackData *track, u32 arg2);
GSvec2 fn_80221F8C(f32 cursor, GSanimTrackData *track, u32 arg2);
void animInterpolateVec3(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4);
void animSampleVec3(GSvec3 *dst, f32 cursor, GSanimTrackData *track, u32 arg2);
void animSampleQuat(GSquat *dst, f32 cursor, GSanimTrackData *track, u32 arg2);
s8 animSampleS8(f32 cursor, GSanimTrackData *track, u32 arg2);
u8 animSampleU8(f32 cursor, GSanimTrackData *track, u32 arg2);
s16 animSampleS16(f32 cursor, GSanimTrackData *track, u32 arg2);
u16 animSampleU16(f32 cursor, GSanimTrackData *track, u32 arg2);

} // namespace GSmath
