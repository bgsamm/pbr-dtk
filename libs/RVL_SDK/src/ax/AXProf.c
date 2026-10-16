// Imported from doldecomp/ogws (CC0), src/revolution/AX/AXProf.c
#include <revolution/ax.h>
#include <private/ax.h>

static BOOL __AXProfileInitialized = FALSE;
static AXPROFILE* __AXProfile;
static u32 __AXMaxProfiles;
static u32 __AXCurrentProfile;

AXPROFILE* __AXGetCurrentProfile(void) {
    if (__AXProfileInitialized) {
        AXPROFILE* prof = &__AXProfile[__AXCurrentProfile];

        __AXCurrentProfile++;
        __AXCurrentProfile %= __AXMaxProfiles;

        return prof;
    }

    return NULL;
}
