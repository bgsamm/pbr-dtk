#include "common.hpp"
#include "gs/GSmath.hpp"

#include <revolution/os.h>


void GSmath::init() {
    OSInitFastCast();
    OSSetGQR6(OS_GQR_S16, OS_GQR_SCALE_64);
    OSSetGQR7(OS_GQR_U16, OS_GQR_SCALE_64);
    initRand();
    initCosTable();
}
