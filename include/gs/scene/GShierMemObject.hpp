#pragma once

#include "gs/GSmem.hpp"

// NOTE(samm) Name known from RTTI
class GShierMemObject {
public:
    inline void *operator new(u32 size) {
        if (!GSmem::isInitialized()) {
            return NULL;
        }
        return GSmem::allocFromHeap(gGameHeap, size);
    }

    inline void operator delete(void *ptr) {
        GSmem::freeToHeap(gGameHeap, ptr);
    }
};
