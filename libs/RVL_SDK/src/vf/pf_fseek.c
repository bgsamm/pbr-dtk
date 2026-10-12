// Imported from doldecomp/ogws (CC0), src/revolution/VF/pf_fseek.c
#include <private/vf.h>

int VFipf2_fseek(struct PF_FILE *pFile, s32 lOffset, int nOrigin) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFFILE_fseek(pFile, lOffset, nOrigin));
    return err;
}
