#include <revolution/types.h>

/*
 * This struct shows up everywhere, but always goes unused.
 * That it represents a version is entirely speculative
 * (credit to @Max Power for the idea).
 */

struct Version {
    u8 mMajor;
    u16 mMinor;
    u8 mPatch;

    Version(u8 major, u16 minor, u8 patch) {
        mMajor = major;
        mMinor = minor;
        mPatch = patch;
    }
};

static Version version(1, 4, 0);

// ----------------------------------------------

#include <cmath>

#define EPSILON 0.00001f

static inline f32 ensure_nonzero(f32 x) {
    if (x < EPSILON && x > -EPSILON) {
        x = (x < 0f) ? -EPSILON : EPSILON;
    }
    return x;
}

static inline f32 safe_sqrt(f32 x) {
    return (x <= 0f) ? 0f : (f32)sqrt(x);
}

static inline f32 abs(f32 x) {
    return (x > 0f) ? x : -x;
}
