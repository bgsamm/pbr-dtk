#ifndef VI_H
#define VI_H

#include <revolution/types.h>
#include <revolution/gx/GXStruct.h>
#include <revolution/vi/vitypes.h>

#ifdef __cplusplus
extern "C" {
#endif

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback);
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback);

void VIInit(void);
void VIWaitForRetrace(void);

void VIConfigure(const GXRenderModeObj* rm);

void VIFlush(void);
void VISetNextFrameBuffer(void *);
void VISetBlack(BOOL);

u32 VIGetNextField(void);
u32 VIGetTvFormat(void);
u32 VIGetScanMode(void);
u32 VIGetDTVStatus(void);
BOOL VIEnableDimming(BOOL enable);
VITimeToDIM VISetTimeToDimming(VITimeToDIM time);

#ifdef __cplusplus
}
#endif

#endif // VI_H
