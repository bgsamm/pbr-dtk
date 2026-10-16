#include ".unsorted/80220DC4.hpp"

#include "gs/GSmath.hpp"
#include "gs/GSsceneData.hpp"

#include "common.hpp"

#define GS_INTERP_NONE 0
#define GS_INTERP_LINEAR 1
#define GS_INTERP_CUBIC 2

#define GET_BYTE(track, idx) (((s8 *)(track)->mValues)[idx])
#define GET_SHORT(track, idx) (((s16 *)(track)->mValues)[idx])
#define GET_USHORT(track, idx) (((u16 *)(track)->mValues)[idx])
#define GET_VEC3(track, idx) (((GSvec3 *)(track)->mValues)[idx])
#define GET_QUAT(track, idx) (((GSquat *)(track)->mValues)[idx])

#define GET_FLOAT_CONTROL(track, idx) (((f32 *)(track)->mControls)[idx])
#define GET_VEC3_CONTROL(track, idx) (((GSvec3 *)(track)->mControls)[idx])

namespace GSmath {

void animInterpolateS8(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    s8 *values;
    u16 idx;
    f32 t, t2, t3;
    f32 b, c, h00, h01, h10, h11;
    f32 p0, p1;

    idx = kf1->mValueIdx;

    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR:
            values = (s8 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            track->mCachedByte = (s8)(((1.0f - t) * p0 + t * p1) * (f32)(1 << arg4));
            break;

        case GS_INTERP_CUBIC:
            values = (s8 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            t2 = t * t;
            t3 = t2 * t;
            h11 = t3 - t2;    /*  t^3 - t^2            */
            b = t2 + t2 - t3; /*  2t^2 - t^3           */
            c = h11 - t2;
            h01 = b - h11;    /*  3t^2 - 2t^3          */
            h10 = t + c;      /*  t^3 - 2t^2 + t       */
            h00 = 1.0f - h01; /*  2t^3 - 3t^2 + 1      */

            track->mCachedByte = (s8)((h00 * p0 + h01 * p1 + h10 * ((f32 *)track->mControls)[kf1->mControlIdxR] +
                                       h11 * ((f32 *)track->mControls)[kf2->mControlIdxL]) *
                                      (f32)(1 << arg4));
            break;

        case GS_INTERP_NONE:
        default:             track->mCachedByte = ((s8 *)track->mValues)[idx]; break;
    }
}

void animInterpolateU8(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    u8 *values;
    u16 idx;
    f32 t, t2, t3;
    f32 b, c, h00, h01, h10, h11;
    f32 p0, p1;

    idx = kf1->mValueIdx;

    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR:
            values = (u8 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            track->mCachedByte = (u8)(((1.0f - t) * p0 + t * p1) * (f32)(1 << arg4));
            break;

        case GS_INTERP_CUBIC:
            values = (u8 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            t2 = t * t;
            t3 = t2 * t;
            h11 = t3 - t2;    /*  t^3 - t^2            */
            b = t2 + t2 - t3; /*  2t^2 - t^3           */
            c = h11 - t2;
            h01 = b - h11;    /*  3t^2 - 2t^3          */
            h10 = t + c;      /*  t^3 - 2t^2 + t       */
            h00 = 1.0f - h01; /*  2t^3 - 3t^2 + 1      */

            track->mCachedByte = (u8)((h00 * p0 + h01 * p1 + h10 * ((f32 *)track->mControls)[kf1->mControlIdxR] +
                                       h11 * ((f32 *)track->mControls)[kf2->mControlIdxL]) *
                                      (f32)(1 << arg4));
            break;

        case GS_INTERP_NONE:
        default:             track->mCachedByte = ((u8 *)track->mValues)[idx]; break;
    }
}

void animInterpolateS16(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    s16 *values;
    u16 idx;
    f32 t, t2, t3;
    f32 b, c, h00, h01, h10, h11;
    f32 p0, p1;

    idx = kf1->mValueIdx;

    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR:
            values = (s16 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            track->mCachedShort = (s16)(((1.0f - t) * p0 + t * p1) * (f32)(1 << arg4));
            break;

        case GS_INTERP_CUBIC:
            values = (s16 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            t2 = t * t;
            t3 = t2 * t;
            h11 = t3 - t2;    /*  t^3 - t^2            */
            b = t2 + t2 - t3; /*  2t^2 - t^3           */
            c = h11 - t2;
            h01 = b - h11;    /*  3t^2 - 2t^3          */
            h10 = t + c;      /*  t^3 - 2t^2 + t       */
            h00 = 1.0f - h01; /*  2t^3 - 3t^2 + 1      */

            track->mCachedShort = (s16)((h00 * p0 + h01 * p1 + h10 * ((f32 *)track->mControls)[kf1->mControlIdxR] +
                                         h11 * ((f32 *)track->mControls)[kf2->mControlIdxL]) *
                                        (f32)(1 << arg4));
            break;

        case GS_INTERP_NONE:
        default:             track->mCachedShort = ((s16 *)track->mValues)[idx]; break;
    }
}

void animInterpolateU16(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    u16 *values;
    u16 idx;
    f32 t, t2, t3;
    f32 b, c, h00, h01, h10, h11;
    f32 p0, p1;

    idx = kf1->mValueIdx;

    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR:
            values = (u16 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            track->mCachedShort = (u16)(((1.0f - t) * p0 + t * p1) * (f32)(1 << arg4));
            break;

        case GS_INTERP_CUBIC:
            values = (u16 *)track->mValues;
            t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            p0 = (f32)values[idx] / (f32)(1 << arg4);
            p1 = (f32)values[kf2->mValueIdx] / (f32)(1 << arg4);

            t2 = t * t;
            t3 = t2 * t;
            h11 = t3 - t2;    /*  t^3 - t^2            */
            b = t2 + t2 - t3; /*  2t^2 - t^3           */
            c = h11 - t2;
            h01 = b - h11;    /*  3t^2 - 2t^3          */
            h10 = t + c;      /*  t^3 - 2t^2 + t       */
            h00 = 1.0f - h01; /*  2t^3 - 3t^2 + 1      */

            track->mCachedShort = (s16)((h00 * p0 + h01 * p1 + h10 * ((f32 *)track->mControls)[kf1->mControlIdxR] +
                                         h11 * ((f32 *)track->mControls)[kf2->mControlIdxL]) *
                                        (f32)(1 << arg4));
            break;

        case GS_INTERP_NONE:
        default:             track->mCachedShort = ((s16 *)track->mValues)[idx]; break;
    }
}

void animInterpolateQuat(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    u16 valueIdx = kf1->mValueIdx;
    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR: {
            f32 t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);
            GSquat result;
            QUATSlerp(&GET_QUAT(track, valueIdx), &GET_QUAT(track, kf2->mValueIdx), &result, t);
            track->mCachedQuat = result;
        } break;
        case GS_INTERP_CUBIC: {
            f32 t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);
            GSquat result;
            QUATSquad(
                // NOTE(samm) The args appear to be in the wrong order (control values should be in the middle)
                &GET_QUAT(track, valueIdx),
                &GET_QUAT(track, kf2->mValueIdx),
                &GET_QUAT(track, kf1->mControlIdxR),
                &GET_QUAT(track, kf2->mControlIdxL),
                &result,
                t);
            track->mCachedQuat = result;
        } break;
        case GS_INTERP_NONE:
        default:             track->mCachedQuat = GET_QUAT(track, valueIdx); break;
    }
}

void animInterpolateVec3(f32 cursor, GSanimTrackData *track, GSkeyframe *kf1, GSkeyframe *kf2, u32 arg4) {
    u16 valueIdx = kf1->mValueIdx;
    switch (kf1->mInterpType) {
        case GS_INTERP_LINEAR: {
            f32 t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            GSvec3 a;
            VECScale(&GET_VEC3(track, valueIdx), &a, 1.f - t);
            track->mCachedVec3 = a;

            GSvec3 b;
            VECScale(&GET_VEC3(track, kf2->mValueIdx), &b, t);

            VECAdd(&track->mCachedVec3, &b, &track->mCachedVec3);
        } break;
        case GS_INTERP_CUBIC: {
            f32 t = (cursor - kf1->mTime) / (kf2->mTime - kf1->mTime);

            // TODO(samm) Clean up & fix regswap
            f32 tsquared = t * t;
            f32 tcubed = tsquared * t;
            f32 h_11 = tcubed - tsquared;
            f32 h_01 = tsquared + tsquared - tcubed - h_11;
            f32 h_10 = h_11 - tsquared + t;
            f32 h_00 = 1.f - h_01;

            GSvec3 a;
            VECScale(&GET_VEC3(track, valueIdx), &a, h_00);
            track->mCachedVec3 = a;

            GSvec3 b;
            VECScale(&GET_VEC3(track, kf2->mValueIdx), &b, h_01);
            VECAdd(&track->mCachedVec3, &b, &track->mCachedVec3);

            GSvec3 c;
            VECScale(&GET_VEC3_CONTROL(track, kf1->mControlIdxR), &c, h_10);
            VECAdd(&track->mCachedVec3, &c, &track->mCachedVec3);

            GSvec3 d;
            VECScale(&GET_VEC3_CONTROL(track, kf2->mControlIdxL), &d, h_11);
            VECAdd(&track->mCachedVec3, &d, &track->mCachedVec3);
        } break;
        case GS_INTERP_NONE:
        default:             track->mCachedVec3 = GET_VEC3(track, valueIdx); break;
    }
}

void animSampleVec3(GSvec3 *dst, f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            *dst = track->mCachedVec3;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedVec3 = GET_VEC3(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedVec3 = GET_VEC3(track, track->mValueCount - 1);
            } else {
                track->mCachedVec3 = GET_VEC3(track, index);
            }

            *dst = track->mCachedVec3;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            *dst = GET_VEC3(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            *dst = GET_VEC3(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            *dst = track->mCachedVec3;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateVec3(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            *dst = track->mCachedVec3;
        }
    }
}

void animSampleQuat(GSquat *dst, f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            *dst = track->mCachedQuat;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedQuat = GET_QUAT(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedQuat = GET_QUAT(track, track->mValueCount - 1);
            } else {
                track->mCachedQuat = GET_QUAT(track, index);
            }

            *dst = track->mCachedQuat;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            *dst = GET_QUAT(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            *dst = GET_QUAT(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            *dst = track->mCachedQuat;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateQuat(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            *dst = track->mCachedQuat;
        }
    }
}

s8 animSampleS8(f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            return track->mCachedByte;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedByte = GET_BYTE(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedByte = GET_BYTE(track, track->mValueCount - 1);
            } else {
                track->mCachedByte = GET_BYTE(track, index);
            }

            return track->mCachedByte;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            return GET_BYTE(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            return GET_BYTE(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            return track->mCachedByte;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateS8(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            return track->mCachedByte;
        }
    }
}

u8 animSampleU8(f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            return track->mCachedByte;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedByte = GET_BYTE(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedByte = GET_BYTE(track, track->mValueCount - 1);
            } else {
                track->mCachedByte = GET_BYTE(track, index);
            }

            return track->mCachedByte;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            return GET_BYTE(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            return GET_BYTE(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            return track->mCachedByte;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateU8(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            return track->mCachedByte;
        }
    }
}

s16 animSampleS16(f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            return track->mCachedShort;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedShort = GET_SHORT(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedShort = GET_SHORT(track, track->mValueCount - 1);
            } else {
                track->mCachedShort = GET_SHORT(track, index);
            }

            return track->mCachedShort;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            return GET_SHORT(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            return GET_SHORT(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            return track->mCachedShort;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateS16(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            return track->mCachedShort;
        }
    }
}

u16 animSampleU16(f32 cursor, GSanimTrackData *track, u32 arg2) {
    if (!track->mKeyframes) {
        if (track->mCachedTime == cursor) {
            return track->mCachedUShort;
        } else {
            s32 index = 0.5f + cursor * (s32)(u8)track->mCachedIndex;
            if (index <= 0) {
                track->mCachedUShort = GET_SHORT(track, 0);
            } else if (index >= track->mValueCount) {
                track->mCachedUShort = GET_SHORT(track, track->mValueCount - 1);
            } else {
                track->mCachedUShort = GET_SHORT(track, index);
            }

            return track->mCachedUShort;
        }
    } else {
        if (cursor <= 0.f && !track->mKeyframes[0].mInterpType) {
            return GET_SHORT(track, track->mKeyframes[0].mValueIdx);
        } else if (cursor >= track->mDuration) {
            return GET_SHORT(track, track->mKeyframes[track->mKeyframCount - 1].mValueIdx);
        } else if (FLOAT_EQUAL(cursor, track->mCachedTime)) {
            return track->mCachedUShort;
        } else {
            if (track->mCachedIndex > 0 && cursor < track->mKeyframes[track->mCachedIndex].mTime) {
                track->mCachedIndex = 0;
            }

            GSkeyframe *kf1 = &track->mKeyframes[track->mCachedIndex];
            GSkeyframe *kf2 = kf1 + 1;
            if (kf2->mTime < cursor) {
                while (kf2->mTime < cursor) {
                    track->mCachedIndex++;
                    kf2++;
                }
                kf1 = kf2 - 1;
            }

            animInterpolateU16(cursor, track, kf1, kf2, arg2);
            track->mCachedTime = cursor;
            return track->mCachedUShort;
        }
    }
}

} // namespace GSmath
