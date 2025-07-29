#include "global.hpp"

#include "gs/GSdebug.hpp"

/*
 * My best guess is that this is some leftover debug functionality for
 * overriding the disk's region. gRegionOverride never gets set or
 * referenced anywhere else. getRegionOverride() is only referenced
 * once, in GSfile::init().
 */

static GSregionOverride gRegionOverride;

GSregionOverride GSdebug::getRegionOverride() {
    return gRegionOverride;
} 
