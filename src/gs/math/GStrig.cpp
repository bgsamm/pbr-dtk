#include "version.hpp"

#include <cmath>

#include "gs/GSmath.hpp"

#define COS_TBL_LEN (1 + 90 * 2)

/* lbl_80493330 */ f32 sCosTable[COS_TBL_LEN];

void GSmath::initCosTable() {
    for (int i = 0; i < COS_TBL_LEN; i++) {
        sCosTable[i] = ::cos(i * 0.5f * DEG_TO_RAD);
    }
}

f32 GSmath::cos(f32 x) {
    f32 sign = 1f;

    if (x > 180f) {
        sign = -1f;
        x = fmod(x, 180.);
    }

    if (x > 90f) {
        x = 180f - x;
    }

    // Does not match as a single line (uses fmadds)
    f32 temp = 2f * x;
    u32 tblIdx = 0.5f + temp;
    
    return sign * sCosTable[tblIdx];
}

f32 GSmath::sin(f32 x) {
    return cos(90f - x);
}
