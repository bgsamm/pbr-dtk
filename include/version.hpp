#pragma once

#include <revolution/types.h>

#define VERSION(maj, min, rev) ((maj << 24) | (min << 8) | (rev))

/* NOTE(samm)
 * This struct shows up everywhere, but always goes unused.
 * That it represents a version is entirely speculative.
 * (Credit to @Max Power for the idea)
 */
struct Version {
    /* 0x0 */ u8 mMajor;
    /* 0x2 */ u16 mMinor;
    /* 0x6 */ u8 mRevision;

    Version(u8 major, u16 minor, u8 revision) {
        mMajor = major;
        mMinor = minor;
        mRevision = revision;
    }

    bool operator<(s32 version) const {
        return VERSION(mMajor, mMinor, mRevision) < version;
    }
};
