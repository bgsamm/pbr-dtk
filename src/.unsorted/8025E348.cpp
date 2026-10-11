#include ".unsorted/8025E348.hpp"

#include "common.hpp"
#include "gs/GSmem.hpp"

extern "C" {

/* lbl_8063F9B0 */ extern MEMHeapHandle lbl_8063F9B0;

void fn_8025E40C(MEMHeapHandle heap) { lbl_8063F9B0 = heap; }

void fn_8025E474(u32 a) { fn_8025E414(a, 0x20); }

void fn_8025E4D0(void *block) {
    if (block != NULL) {
        GSmem::freeToHeap(lbl_8063F9B0, block);
    }
}

}
