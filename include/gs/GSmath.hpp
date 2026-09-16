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

    GSvec3 operator+(const GSvec3 &other) const {
        GSvec3 result;
        VECAdd(this, &other, &result);
        return result;
    }

    GSvec3 operator*(f32 scale) const {
        GSvec3 result;
        VECScale(this, &result, scale);
        return result;
    }

    GSvec3 cross(const GSvec3 *other) const {
        GSvec3 result;
        VECCrossProduct(this, other, &result);
        return result;
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

struct GSmatrix {
private:
    Mtx mMatrix;

public:
    operator Mtx &() {
        return mMatrix;
    }

    operator const Mtx &() const {
        return mMatrix;
    }

    GSvec3 operator*(const GSvec3 &vec) const {
        GSvec3 result;
        MTXMultVec(mMatrix, &vec, &result);
        return result;
    }
};

// TODO(samm) Name? Move? Vec vs. GSvec3?
struct GSboundingBox {
    /* 0x00 */ GSvec3 mMin;
    /* 0x0C */ GSvec3 mMax;
    /* 0x18 */ GSmatrix *mTransform;

    GSboundingBox(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1) : mMin(x0, y0, z0), mMax(x1, y1, z1), mTransform() {}
};

namespace GSmath {

extern GSvec3 sXAxis;
extern GSvec3 sYAxis;
extern GSvec3 sZAxis;

// GSboundingBox.cpp
void calcBoundingBoxCenter(GSvec3 *dst, const GSboundingBox *aabb);
void expandBoundingBox(GSboundingBox *dst, const GSboundingBox *src);

// GSeuler.cpp
void eulerToQuat(GSquat *quat, GSvec3 *euler);

// GSrand.cpp
u32 *getRandSeed();
void initRand();

// GStrig.cpp
void initCosTable();
f32 cos(f32 x);
f32 sin(f32 x);

// GSquat.cpp
void rotateVec3ByQuat(GSvec3 *p, GSquat *r);

// GSmathInit.cpp
void init();

}; // namespace GSmath
