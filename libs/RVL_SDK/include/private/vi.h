#ifndef PRIVATE_VI_H
#define PRIVATE_VI_H

#include <revolution/vi.h>
#include <private/vi/i2c.h>
#include <private/vi/vi3in1.h>
#include <revolution/vi/vi3in1.h>

#ifdef __cplusplus
extern "C" {
#endif

void __VISetRGBModeImm();


void __VIInit(VITVMode mode);
void __VIInit3in1(VITVMode mode);

BOOL __VIResetRFIdle();

#ifdef __cplusplus
}
#endif

#endif  // PRIVATE_VI_H
