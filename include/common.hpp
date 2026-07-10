#pragma once

#include <revolution/types.h>

#include <cmath>

#define EPSILON 0.00001f

static inline f32 ensure_nonzero(f32 x) {
    if (x < EPSILON && x > -EPSILON) {
        x = (x < 0.f) ? -EPSILON : EPSILON;
    }
    return x;
}

static inline f32 safe_sqrt(f32 x) {
    return (x <= 0.f) ? 0.f : (f32)sqrt(x);
}

static inline f32 abs(f32 x) {
    return (x > 0.f) ? x : -x;
}
