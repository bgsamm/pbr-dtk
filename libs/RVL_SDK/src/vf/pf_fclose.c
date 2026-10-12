// Imported from doldecomp/ogws (CC0), src/revolution/VF/pf_fclose.c
#include <private/vf.h>

int VFipf2_fclose(struct PF_FILE *p_file) {
    s32 err;
    err = VFiPFAPI_convertReturnValue(VFiPFFILE_fclose(p_file));
    return err;
}
