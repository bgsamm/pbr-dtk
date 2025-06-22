#include <version.hpp>

#include "gs/GSmem.hpp"

void *operator new(u32 size) {
    if (!GSmem::isInitialized()) {
        return NULL;
    }
    return GSmem::allocFromDefaultHeap(size);
}

void *operator new[](u32 size) {
    if (!GSmem::isInitialized()) {
        return NULL;
    }
    return GSmem::allocFromDefaultHeap(size);
}

void operator delete(void *ptr) {
    GSmem::freeDefaultHeapBlock(ptr);
}

void operator delete[](void *ptr) {
    GSmem::freeDefaultHeapBlock(ptr);
}
