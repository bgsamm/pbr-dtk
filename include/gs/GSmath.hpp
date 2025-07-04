#pragma once

#include <revolution/types.h>

#define PI 3.14159265f
#define DEG_TO_RAD (PI / 180f)

struct GSvec2 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;

    GSvec2(f32 x, f32 y) {
        this->x = x;
        this->y = y;
    }
};

struct GSvec3 {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;

    GSvec3(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct GSquat {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xc */ f32 w;
};

namespace GSmath {
    // GSrand
    u32 *getRandSeed();
    void initRand();
    // GStrig
    void initCosTable();
    f32 cos(f32 x);
    f32 sin(f32 x);
    // GSquat
    void rotateVec3ByQuat(GSvec3 *p, GSquat *r);
    // GSmathInit
    void init();
};
