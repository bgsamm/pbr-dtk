#include "global.hpp"

#include <cmath>
#include <revolution/gx.h>
#include <revolution/mtx.h>

#include "gs/GSrender.hpp"

GSlight::GSlight() {
    mColor.r = 255;
    mColor.g = 255;
    mColor.b = 255;
    mColor.a = 255;

    mPosition.x = 0f;
    mPosition.y = 0f;
    mPosition.z = 0f;

    GXInitLightColor(&mLightObj, mColor);
    GXInitLightPos(&mLightObj, 0f, 0f, 0f);

    mType = GS_LIGHT_POINT;
    _1 = 0;
    _0 = (1 << 0);
    mIndex = 0;
}

void GSlight::initPointLight(
    GXColor color,
    Vec position,
    GXDistAttnFn distAttnFn,
    f32 refDistance,
    f32 refBrightness
) {
    _1 = 0;
    _0 = 0;
    mType = GS_LIGHT_POINT;

    mColor.r = color.r;
    mColor.g = color.g;
    mColor.b = color.b;
    mColor.a = color.a;
    _1 |= (1 << 0);

    mDistAttnFn = distAttnFn;
    mRefDistance = refDistance;
    mRefBrightness = refBrightness;
    _1 |= (1 << 4);

    if (mSpotFn != GX_SP_OFF) {
        mSpotFn = GX_SP_OFF;
        mCutoff = 90f;
        _1 |= (1 << 5);
    }

    mPosition.x = position.x;
    mPosition.y = position.y;
    mPosition.z = position.z;
    _1 |= (1 << 1);
    _0 |= (1 << 0);
}

void GSlight::initSpotLight(
    GXColor color,
    Vec position,
    Vec direction,
    GXDistAttnFn distAttnFn,
    f32 refDistance,
    f32 refBrightness,
    GXSpotFn spotFn,
    f32 cutoff
) {
    _1 = 0;
    _0 = 0;
    mType = GS_LIGHT_SPOT;

    mColor.r = color.r;
    mColor.g = color.g;
    mColor.b = color.b;
    mColor.a = color.a;
    _1 |= (1 << 0);

    mPosition.x = position.x;
    mPosition.y = position.y;
    mPosition.z = position.z;
    _1 |= (1 << 1);
    _0 |= (1 << 0);

    mDirection.x = direction.x;
    mDirection.y = direction.y;
    mDirection.z = direction.z;
    _1 |= (1 << 2);
    _0 |= (1 << 1);

    mDistAttnFn = distAttnFn;
    mRefDistance = refDistance;
    mRefBrightness = refBrightness;
    _1 |= (1 << 4);

    mSpotFn = spotFn;
    mCutoff = cutoff;
    _1 |= (1 << 5);
}

void GSlight::initSpecLight(GXColor color, Vec direction, f32 shininess) {
    _1 = 0;
    _0 = 0;
    mType = GS_LIGHT_SPEC;

    mColor.r = color.r;
    mColor.g = color.g;
    mColor.b = color.b;
    mColor.a = color.a;
    _1 |= (1 << 0);

    mDirection.x = direction.x;
    mDirection.y = direction.y;
    mDirection.z = direction.z;
    _1 |= (1 << 2);
    _0 |= (1 << 1);

    mShininess = shininess;
    _1 |= (1 << 7);
}

void GSlight::load(u8 index, GSlightStruct1 *param2) {
    if ((_1 & (1 << 0)) != 0) {
        GXInitLightColor(&mLightObj, mColor);
    }

    Vec pos;
    pos.x = mPosition.x;
    pos.y = mPosition.y;
    pos.z = mPosition.z;

    Vec dir;
    dir.x = mDirection.x;
    dir.y = mDirection.y;
    dir.z = mDirection.z;

    if (param2 != NULL) {
        MtxPtr mtx1 = param2->_1d4;
        MtxPtr mtx2 = param2->_234;
        if ((_0 & (1 << 1)) != 0) {
            PSMTXMultVec(mtx2, &dir, &dir);
            f32 sqMag = PSVECSquareMag(&dir);
            if (sqMag > EPSILON) {
                f32 mag = safe_sqrt(sqMag);
                PSVECScale(&dir, &dir, 1f / ensure_nonzero(mag));
            }
            _1 |= (1 << 2);
            _1 &= ~(1 << 6);
        }

        if ((_0 & (1 << 0)) != 0) {
            PSMTXMultVec(mtx1, &pos, &pos);
            _1 |= (1 << 1);
        }
    }

    switch (mType) {
    case GS_LIGHT_SPEC:
        if ((_1 & (1 << 6)) != 0) {
            GXInitSpecularDirHA(
                &mLightObj,
                dir.x,
                dir.y,
                dir.z,
                mHalfAngle.x,
                mHalfAngle.y,
                mHalfAngle.z
            );
        }
        else if ((_1 & (1 << 2)) != 0) {
            GXInitSpecularDir(&mLightObj, dir.x, dir.y, dir.z);
        }

        if ((_1 & (1 << 7)) != 0) {
            GXInitLightShininess(&mLightObj, mShininess);
        }
        else if ((_1 & (1 << 3)) != 0) {
            GXInitLightAttn(
                &mLightObj,
                mAngleAtten0,
                mAngleAtten1,
                mAngleAtten2,
                mDistAtten0,
                mDistAtten1,
                mDistAtten2
            );
        }
        break;
    
    case GS_LIGHT_SPOT:
        if ((_1 & (1 << 1)) != 0) {
            GXInitLightPos(&mLightObj, pos.x, pos.y, pos.z);
        }

        if ((_1 & (1 << 2)) != 0) {
            GXInitLightDir(&mLightObj, dir.x, dir.y, dir.z);
        }
        
        if ((_1 & (1 << 3)) != 0) {
            GXInitLightAttn(
                &mLightObj,
                mAngleAtten0,
                mAngleAtten1,
                mAngleAtten2,
                mDistAtten0,
                mDistAtten1,
                mDistAtten2
            );
        }
        else {
            if ((_1 & (1 << 4)) != 0) {
                GXInitLightDistAttn(
                    &mLightObj,
                    mRefDistance,
                    mRefBrightness,
                    mDistAttnFn
                );
            }

            if ((_1 & (1 << 5)) != 0) {
                GXInitLightSpot(&mLightObj, mCutoff, mSpotFn);
            }
        }
        break;
    
    case GS_LIGHT_POINT:
        if ((_1 & (1 << 1)) != 0) {
            GXInitLightPos(&mLightObj, pos.x, pos.y, pos.z);
        }

        if ((_1 & (1 << 4)) != 0) {
            GXInitLightDistAttn(
                &mLightObj,
                mRefDistance,
                mRefBrightness,
                mDistAttnFn
            );
        }

        // Why would a point light use GXInitLightSpot?
        if ((_1 & (1 << 5)) != 0) {
            GXInitLightSpot(&mLightObj, mCutoff, mSpotFn);
        }
        break;
    }

    _1 = 0;
    mIndex = index;
    GXLoadLightObjImm(&mLightObj, (GXLightID)(1 << index));
}
