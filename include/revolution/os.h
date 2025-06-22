#ifndef OS_H
#define OS_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef s64 OSTime;

#ifdef __MWERKS__
u32 __OSBusClock : (0x8000 << 16 | 0x00F8);
#else
u32 __OSBusClock = 0x800000F8;
#endif

#define OS_BUS_CLOCK        __OSBusClock
#define OS_TIMER_CLOCK      (OS_BUS_CLOCK/4)

typedef struct OSThread OSThread;
typedef void (*OSIdleFunction)(void*);

void DCFlushRange(void* startAddr, u32 nBytes);

OSTime OSGetTime(void);

OSThread* OSSetIdleFunction(OSIdleFunction idleFunction, void* param, void* stack, u32 stackSize);

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL);

#ifdef __cplusplus
}
#endif

#endif // OS_H
