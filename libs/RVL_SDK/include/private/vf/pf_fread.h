// From doldecomp/ogws (CC0), include/revolution/VF/pf_fread.h
#ifndef RVL_SDK_VF_PF_FREAD_H
#define RVL_SDK_VF_PF_FREAD_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 VFipf2_fread(void* p_buf, u32 size, u32 count, struct PF_FILE* p_file);

#ifdef __cplusplus
}
#endif
#endif
