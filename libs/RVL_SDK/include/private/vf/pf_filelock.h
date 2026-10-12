// From doldecomp/ogws (CC0), include/revolution/VF/pf_filelock.h
#ifndef RVL_SDK_VF_PF_FILELOCK_H
#define RVL_SDK_VF_PF_FILELOCK_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void VFiPF_InitLockFile();
s32 VFiPF_UnLockFile(struct PF_FILE* p_file);

#ifdef __cplusplus
}
#endif
#endif
