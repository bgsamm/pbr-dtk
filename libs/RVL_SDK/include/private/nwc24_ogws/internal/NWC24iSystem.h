// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iSystem.h
#ifndef RVL_SDK_NWC24_INTERNAL_SYSTEM_H
#define RVL_SDK_NWC24_INTERNAL_SYSTEM_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iPrepareShutdown(void);
NWC24Err NWC24iRequestShutdown(u32 event, NWC24Err *pResult);

#ifdef __cplusplus
}
#endif
#endif
