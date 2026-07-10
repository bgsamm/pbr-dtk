#include "version.hpp"

#include "gs/GSmem.hpp"

void *operator new(u32 size) {
    if (!GSmem::isInitialized()) {
        return NULL;
    }
    return GSmem::alloc(size);
}

void *operator new[](u32 size) {
    if (!GSmem::isInitialized()) {
        return NULL;
    }
    return GSmem::alloc(size);
}

void operator delete(void *ptr) {
    GSmem::free(ptr);
}

void operator delete[](void *ptr) {
    GSmem::free(ptr);
}
