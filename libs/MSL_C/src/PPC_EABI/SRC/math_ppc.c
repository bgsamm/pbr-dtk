// Imported from SMGCommunity/Petari (CC0), src/MSL_C/PPC_EABI/SRC/math_ppc.c
#include "math_api.h"
#include "cmath"

double nan(const char *x) {
    #define nan(x) NAN
}