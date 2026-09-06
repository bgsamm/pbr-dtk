#pragma once

// TODO(samm) Remove; needed so cmath sees __abs
#include "decomp.h"

#include <cmath>
#include <revolution/types.h>

#define EPSILON 0.00001f

// TODO(samm) Unify these ensure_nonzero funcs?

static inline f32 ensure_nonzero(f32 x) {
    if (x < EPSILON && x > -EPSILON) {
        x = (x < 0.f) ? -EPSILON : EPSILON;
    }
    return x;
}

static inline void ensure_nonzero_inplace(f32 *ptr) {
    f32 x = *ptr;
    if (x < EPSILON && x > -EPSILON) {
        *ptr = (x < 0.f) ? -EPSILON : EPSILON;
    }
}

#define SAFE_SQRT(x) (((x) <= 0.f) ? 0.f : sqrtf((x)))

static inline f32 safe_sqrt(f32 x) {
    return (x <= 0.f) ? 0.f : sqrtf(x);
}

#define SAFE_POW(x, y) ((x) > EPSILON ? powf((x), (y)) : ((x) < -EPSILON ? -powf(-(x), (y)) : 0.f))

static inline f32 abs(f32 x) {
    return (x > 0.f) ? x : -x;
}
