#include "global.hpp"

#include <revolution/os.h>

#include "gs/GSmath.hpp"

/* 
 * The way this initializes the seed to 1, and the LCG
 * inlined throughout the codebase, is equivalent to
 * sysdolphin's HSD_Rand - coincidence?
 */

struct GSrandState {
    /* 0x0 */ u32 mSeed;
    /* 0x4 */ bool _4;
    // TODO determine accurate struct size if possible
    u8 unk1 [0x8];

    GSrandState() {
        _4 = false;
        mSeed = 1;
    }
};
static GSrandState rand;

u32 *GSmath::getRandSeed() {
    return &rand.mSeed;
}

void GSmath::initRand() {
    OSTime time = OSGetTime();

    u32 *seed = getRandSeed();
    *seed = time;
}
