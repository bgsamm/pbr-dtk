// Imported from doldecomp/ogws (CC0), include/revolution/AI/ai_hardware.h; register indexes as macros, register array mapped to ours
#ifndef REVOLUTION_AI_HARDWARE_H
#define REVOLUTION_AI_HARDWARE_H

#include <revolution/types.h>
#include <private/hollywood.h>
#define AI_HW_REGS __AIRegs

#define AI_AICR 0
#define AI_AIVR 1
/* AI_AISCNT and AI_AIIT come from our register headers (byte offsets) */



// AICR - AI Control Register
#define AI_AICR_SAMPLERATE (1 << 6)
#define AI_AICR_SCRESET (1 << 5)
#define AI_AICR_AIINTVLD (1 << 4)
#define AI_AICR_AIINT (1 << 3)
#define AI_AICR_AIINTMSK (1 << 2)
#define AI_AICR_AFR (1 << 1)
#define AI_AICR_PSTAT (1 << 0)


#endif
