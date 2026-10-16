// Imported from SMGCommunity/Petari (CC0), src/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c
#include "cmath"

double atan2(double y, double x) {
    return __ieee754_atan2(y, x);
}