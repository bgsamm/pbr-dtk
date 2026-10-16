#ifndef REVOLUTION_VI_FUNCTIONS_H
#define REVOLUTION_VI_FUNCTIONS_H

#include <revolution/gx/GXStruct.h>
#include <revolution/vi/vitypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VIPadFrameBufferWidth(width) ((u16)(((u16)(width) + 15) & ~15))

void VIInit(void);
void VIWaitForRetrace(void);

void VIConfigure(const GXRenderModeObj* rm);
void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height);

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb);
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb);

#define VI_DTV_COMPONENT (1 << 0)

void VIFlush(void);
void VISetNextFrameBuffer(void* fb);

void VISetBlack(BOOL setBlack);

BOOL VIResetDimmingCount(void);
BOOL VIEnableDimming(BOOL enableDim);
VITimeToDIM VISetTimeToDimming(VITimeToDIM time);

u32 VIGetRetraceCount(void);
u32 VIGetNextField(void);
u32 VIGetDTVStatus(void);
u32 VIGetScanMode(void);

u32 VIGetTvFormat(void);

u32 VIGetCurrentLine(void);

void* VIGetCurrentFrameBuffer(void);

void VISetNextRightFrameBuffer(void* fb);
void VISet3D(BOOL threeD);
void* VIGetNextFrameBuffer();
s32 VIGetVSyncTimingTest();
void VISetVSyncTimingTest();
s32 VIGetDimmingCount();
s32 VIGetDVDStopMotorCount();
BOOL VIEnableDVDStopMotor(BOOL flag);
#define VI_I2C_TYPE_REVERSE 0
#define VI_I2C_TYPE_NORMAL 1
s32 VIGetI2CType();

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_VI_FUNCTIONS_H
