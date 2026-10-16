// From doldecomp/ogws (CC0), include/revolution/NWC24/NWC24System.h
#ifndef RVL_SDK_NWC24_SYSTEM_H
#define RVL_SDK_NWC24_SYSTEM_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24EnableLedNotification(BOOL enable);
BOOL NWC24Shutdown(BOOL final, u32 event);

#ifdef __cplusplus
}
#endif
#endif
