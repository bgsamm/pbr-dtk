// Imported from SMGCommunity/Petari (CC0), src/MSL_C/math_sun.c
#include "cmath"

#pragma exceptions on

double scalbn(double x, int n) {
    double man;
    int exponent;

    man = frexp(x, &exponent);
    exponent += n;
    return ldexp(man, exponent);
}
