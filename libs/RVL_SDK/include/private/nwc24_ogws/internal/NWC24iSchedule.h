// From doldecomp/ogws (CC0), include/revolution/NWC24/internal/NWC24iSchedule.h
#ifndef RVL_SDK_NWC24_INTERNAL_SCHEDULE_H
#define RVL_SDK_NWC24_INTERNAL_SCHEDULE_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define NWC24i_SCHEDULER_DEVICE "/dev/net/kd/request"

NWC24Err NWC24iRequestGenerateUserId(u64 *pId, u32 *arg1);
NWC24Err NWC24iTrySuspendForOpenLib(void);
NWC24Err NWC24iResumeForCloseLib(void);

#ifdef __cplusplus
}
#endif
#endif
