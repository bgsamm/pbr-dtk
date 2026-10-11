// Imported from doldecomp/ogws (CC0), src/revolution/AX/AX.c
#include <revolution/ax.h>
#include <revolution/os.h>

const char* __AXVersion =
    "<< RVL_SDK - AX \trelease build: Dec 18 2006 15:43:48 (0x4199_60831) >>";

static BOOL __init = FALSE;

void AXInit(void) {
    if (!__init) {
        OSRegisterVersion(__AXVersion);

        __AXInitVoiceStacks();
        __AXVPBInit();
        __AXSPBInit();
        __AXAuxInit();
        __AXClInit();
        __AXOutInit(0);

        __init = TRUE;
    }
}

// Not in the imported source: written from the original binary.
BOOL AXIsInit(void) {
    return __init;
}
