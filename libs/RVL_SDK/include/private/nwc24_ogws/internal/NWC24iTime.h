// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iTime.h
#ifndef RVL_SDK_NWC24_INTERNAL_TIME_H
#define RVL_SDK_NWC24_INTERNAL_TIME_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

NWC24Err NWC24iGetUniversalTime(s64 *pTime);
NWC24Err NWC24iGetTimeDifference(s64 *pTimeDiff);
NWC24Err NWC24iSetRtcCounter(u32 rtc, u32 flags);
NWC24Err NWC24iSynchronizeRtcCounter(BOOL forceSave);

#ifdef __cplusplus
}
#endif
#endif
