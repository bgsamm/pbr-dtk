// From doldecomp/ogws (CC0), include/revolution/NWC24/NWC24Utils.h
#ifndef RVL_SDK_NWC24_UTILS_H
#define RVL_SDK_NWC24_UTILS_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void NWC24Data_Init(NWC24Data *pData);
void NWC24Data_SetDataP(NWC24Data *pData, const void *pPtr, u32 size);
void NWC24Date_Init(NWC24Date *pDate);

#ifdef __cplusplus
}
#endif
#endif
