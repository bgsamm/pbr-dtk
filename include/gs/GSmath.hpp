#pragma once

#include <revolution.h>

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

struct GSvec3 : public Vec {
    GSvec3() {}

    GSvec3(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    GSvec3 &operator=(const Vec &vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        return *this;
    }

    void set(f32 x, f32 y, f32 z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct GSquat : public Quaternion {
    GSquat() {}

    GSquat(f32 x, f32 y, f32 z, f32 w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    GSquat(const GSquat &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    GSquat &operator=(const Quaternion &quat) {
        x = quat.x;
        y = quat.y;
        z = quat.z;
        w = quat.w;
        return *this;
    }

    void set(f32 x, f32 y, f32 z, f32 w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};

namespace GSmath {
// GSeuler
void eulerToQuat(GSquat *quat, GSvec3 *euler);
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
}; // namespace GSmath
