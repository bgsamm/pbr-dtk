#ifndef OS_H
#define OS_H

#include <revolution/types.h>

#include <revolution/os/OSFastCast.h>
#include <revolution/os/OSThread.h>

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

typedef void (*OSIdleFunction)(void*);
typedef void (*OSResetCallback)(void);
typedef void (*OSPowerCallback)(void);

void* OSGetMEM1ArenaHi(void);
void* OSGetMEM2ArenaHi(void);
void* OSGetMEM1ArenaLo(void);
void* OSGetMEM2ArenaLo(void);
void OSSetMEM1ArenaLo(void* newLo);
void OSSetMEM2ArenaLo(void* newLo);
void DCInvalidateRange(void* startAddr, u32 nBytes);
void DCFlushRange(void* startAddr, u32 nBytes);

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL enabled);

OSThread* OSSetIdleFunction(OSIdleFunction idleFunction, void* param, void* stack, u32 stackSize);

OSTime OSGetTime(void);

OSResetCallback OSSetResetCallback(OSResetCallback callback);
OSPowerCallback OSSetPowerCallback(OSPowerCallback callback);


#ifdef __cplusplus
}
#endif

#endif // OS_H
