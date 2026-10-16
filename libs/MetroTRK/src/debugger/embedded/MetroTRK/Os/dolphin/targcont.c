// Imported from SMGCommunity/Petari (CC0), src/MetroTRK/debugger/embedded/MetroTRK/Os/dolphin/targcont.c
/**
 * targcont.c
 * Description:
 */

#include "Os/dolphin/targcont.h"

DSError TRKTargetContinue(void) {
    TRKTargetSetStopped(0);
    UnreserveEXI2Port();
    TRKSwapAndGo();
    ReserveEXI2Port();
    return 0;
}
