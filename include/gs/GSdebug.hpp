#pragma once

#include <revolution/types.h>

enum GSregionOverride {
    REGION_OVERRIDE_DEFAULT = 0,
    REGION_OVERRIDE_USA     = 1,
    REGION_OVERRIDE_PAL     = 2
};

namespace GSdebug {
    GSregionOverride getRegionOverride();
};
