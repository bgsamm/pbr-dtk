// Imported from SMGCommunity/Petari (CC0), src/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_sqrt.c
#include "cmath"

double sqrt(double x) {
    return __ieee754_sqrt(x);
}