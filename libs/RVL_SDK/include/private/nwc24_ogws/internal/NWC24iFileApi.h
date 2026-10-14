// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iFileApi.h
#ifndef RVL_SDK_NWC24_INTERNAL_FILE_API_H
#define RVL_SDK_NWC24_INTERNAL_FILE_API_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_VF_DRIVE "@24"

NWC24Err NWC24iFOpenNand(NWC24File *pFile, const char *pPath, u32 mode);
NWC24Err NWC24iFOpenVF(NWC24File *pFile, const char *pPath, u32 mode);

NWC24Err NWC24iFCloseNand(NWC24File *pFile) NO_INLINE;
NWC24Err NWC24iFCloseVF(NWC24File *pFile);

#ifdef __cplusplus
}
#endif
#endif
