// From doldecomp/ogws (CC0), include/revolution/NWC24/NWC24Schedule.h
#ifndef RVL_SDK_NWC24_SCHEDULE_H
#define RVL_SDK_NWC24_SCHEDULE_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

s32 NWC24SuspendScheduler(void);
s32 NWC24ResumeScheduler(void);

#ifdef __cplusplus
}
#endif
#endif
