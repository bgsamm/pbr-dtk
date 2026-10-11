// Imported from SMGCommunity/Petari (CC0), src/MetroTRK/gamedev/cust_connection/utils/gc/MWCriticalSection_gc.c
/**
 * MWCriticalSection_gc.c
 * Description:
 */

#include "utils/gc/MWCriticalSection_gc.h"

extern BOOL OSRestoreInterrupts(unsigned int);
extern unsigned int OSDisableInterrupts();

extern void MWInitializeCriticalSection(unsigned int*) {}

extern void MWEnterCriticalSection(unsigned int* section) {
    *section = OSDisableInterrupts();
}

extern void MWExitCriticalSection(unsigned int* section) {
    OSRestoreInterrupts(*section);
}
