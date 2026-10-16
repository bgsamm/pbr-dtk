// Imported from doldecomp/ogws (CC0), src/revolution/VF/pf_fread.c
#include <private/vf.h>

u32 VFipf2_fread(void *p_buf, u32 size, u32 count, struct PF_FILE *p_file) {
    u32 count_read;
    VFiPFFILE_fread(p_buf, size, count, p_file, &count_read);
    return count_read;
}
