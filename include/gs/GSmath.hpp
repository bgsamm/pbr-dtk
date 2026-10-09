#pragma once

#include <cmath>
#include <revolution.h>

#define EPSILON 0.00001f

#define FLOAT_EQUAL(x, y) ((x) - (y) < EPSILON && (x) - (y) > -EPSILON)

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

static inline f32 u8tof32(u8 arg) {
    f32 ret;
    OSu8tof32(&arg, &ret);
    return ret;
}

static inline u8 f32tou8(f32 arg) {
    u8 ret;
    OSf32tou8(&arg, &ret);
    return ret;
}

#define PI 3.14159265f
#define DEG_TO_RAD (PI / 180f)

struct GSvec2 : Vec2 {
    GSvec2() {}

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

    GSvec3(const GSvec3 &other) {
        x = other.x;
        y = other.y;
        z = other.z;
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
    void normalize() {
        VECNormalize(this, this);
    }

    GSvec3 operator-() const {
        return GSvec3(-x, -y, -z);
    }

    GSvec3 operator+(const GSvec3 &other) const {
        GSvec3 result;
        VECAdd(this, &other, &result);
        return result;
    }

    GSvec3 operator-(const GSvec3 &other) const {
        GSvec3 result;
        VECSubtract(this, &other, &result);
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
    GSmatrix() {}

    GSmatrix(
        f32 x00, f32 x01, f32 x02, f32 x03, f32 x10, f32 x11, f32 x12, f32 x13, f32 x20, f32 x21, f32 x22, f32 x23) {
        mMatrix[0][0] = x00;
        mMatrix[0][1] = x01;
        mMatrix[0][2] = x02;
        mMatrix[0][3] = x03;
        mMatrix[1][0] = x10;
        mMatrix[1][1] = x11;
        mMatrix[1][2] = x12;
        mMatrix[1][3] = x13;
        mMatrix[2][0] = x20;
        mMatrix[2][1] = x21;
        mMatrix[2][2] = x22;
        mMatrix[2][3] = x23;
    }

    GSmatrix(const GSmatrix &other) {
        MTXCopy(other, mMatrix);
    }

    operator Mtx &() {
        return mMatrix;
    }

    operator const Mtx &() const {
        return mMatrix;
    }

    f32 operator()(u32 x, u32 y) const {
        return mMatrix[x][y];
    }

    f32 &operator()(u32 x, u32 y) {
        return mMatrix[x][y];
    }

    GSmatrix &operator=(const GSmatrix &other) {
        MTXCopy(other, *this);
        return *this;
    }

    GSmatrix operator*(const GSmatrix &other) const {
        GSmatrix result;
        MTXConcat(mMatrix, other, result);
        return result;
    }

    GSvec3 operator*(const GSvec3 &vec) const {
        GSvec3 result;
        MTXMultVec(mMatrix, &vec, &result);
        return result;
    }

    GSmatrix invXpose() const {
        GSmatrix result;
        MTXInvXpose(mMatrix, result);
        return result;
    }

    void scale(GSvec3 vec) {
        MTXScaleApply(mMatrix, mMatrix, vec.x, vec.y, vec.z);
    }
};

// TODO(samm) Name? Move? Vec vs. GSvec3?
struct GSboundingBox {
    /* 0x00 */ GSvec3 mMin;
    /* 0x0C */ GSvec3 mMax;
    /* 0x18 */ GSmatrix *mTransform;

    GSboundingBox() : mMin(EPSILON, EPSILON, EPSILON), mMax(-EPSILON, -EPSILON, -EPSILON), mTransform() {}
    GSboundingBox(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1) : mMin(x0, y0, z0), mMax(x1, y1, z1), mTransform() {}
};

namespace GSmath {

extern GSvec3 sXAxis;
extern GSvec3 sYAxis;
extern GSvec3 sZAxis;

// GSboundingBox.cpp
void calcBoundingBoxCenter(GSvec3 *dst, const GSboundingBox *aabb);
void expandBoundingBox(GSboundingBox *dst, const GSboundingBox *src);
u32 fn_80220B18(GSboundingBox *arg0);

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
