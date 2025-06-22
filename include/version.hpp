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
