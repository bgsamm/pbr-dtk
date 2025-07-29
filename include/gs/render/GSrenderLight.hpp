#pragma once

#include <revolution/types.h>

enum GSlightType {
    GS_LIGHT_SPEC,
    GS_LIGHT_SPOT,
    GS_LIGHT_POINT
};

struct GSlightStruct1 {
    u8 _0[0x1d4];
    /* 0x1d4 */ Mtx _1d4;
    u8 _204[0x30];
    /* 0x234 */ Mtx _234;
};

// size: 0x80
class GSlight {
public:
    /* 0x0 */ u8 _0;
    /* 0x1 */ u8 _1;
    /* 0x4 */ GSlightType mType;
    /* 0x8 */ GXColor mColor;
    /* 0xc */ Vec mPosition;
    /* 0x18 */ Vec mDirection;
    union {
        /* 0x24 */ Vec mHalfAngle;
        struct {
            /* 0x24 */ f32 mAngleAtten0;
            /* 0x28 */ f32 mAngleAtten1;
            /* 0x2c */ f32 mAngleAtten2;
        };
        struct {
            /* 0x24 */ GXDistAttnFn mDistAttnFn;
            /* 0x28 */ f32 mRefDistance;
            /* 0x2c */ f32 mRefBrightness;
        };
    };
    union {
        /* 0x30 */ f32 mShininess;
        struct {
            /* 0x30 */ f32 mDistAtten0;
            /* 0x34 */ f32 mDistAtten1;
            /* 0x38 */ f32 mDistAtten2;
        };
        struct {
            /* 0x30 */ GXSpotFn mSpotFn;
            /* 0x34 */ f32 mCutoff;
        };
    };
    /* 0x3c */ GXLightObj mLightObj;
    /* 0x7c */ u8 mIndex;

    GSlight();

    void initPointLight(GXColor color, Vec position, GXDistAttnFn distAttnFn, f32 refDistance, f32 refBrightness);
    void initSpotLight(GXColor color, Vec position, Vec direction, GXDistAttnFn distAttnFn, f32 refDistance, f32 refBrightness, GXSpotFn spotFn, f32 cutoff);
    void initSpecLight(GXColor color, Vec direction, f32 shininess);
    void load(u8 index, GSlightStruct1 *param2);
};
