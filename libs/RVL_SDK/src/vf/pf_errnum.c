// Imported from doldecomp/ogws (CC0), src/revolution/VF/pf_errnum.c
#include <private/vf.h>

int VFipf2_errnum() {
    s32 err;
    err = VFiPFAPI_convertError(VFiPFVOL_errnum());
    return err;
}
