// Imported from SMGCommunity/Petari (CC0), src/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c
#include "cmath"

double fmod(double x, double y) {
    return __ieee754_fmod(x, y);
}