// Imported from SMGCommunity/Petari (CC0), src/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_pow.c
#include "cmath"

double pow(double x, double y) {
    return __ieee754_pow(x, y);
}