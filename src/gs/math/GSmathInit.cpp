#include "gs/GSmath.hpp"

#include <revolution/os.h>

#include "common.hpp"

void GSmath::init() {
    OSInitFastCast();
    OSSetGQR6(OS_GQR_TYPE_S16, 6);
    OSSetGQR7(OS_GQR_TYPE_U16, 6);
    initRand();
    initCosTable();
}
