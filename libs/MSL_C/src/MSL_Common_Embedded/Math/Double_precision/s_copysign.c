// Imported from SMGCommunity/Petari (CC0), src/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c
double copysign(double x, double y) {
    *(int*)&x = (*(int*)&x) & 0x7FFFFFFF | (*(int*)&y) & 0x80000000;
    return x;
}