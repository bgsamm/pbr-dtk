#include ".unsorted/80007940.hpp"

#include "gs/GSfsys.hpp"

#include "common.hpp"

extern "C" {

void fn_80007B14(void) {}
s32 fn_800081A0(void) {
    return 1;
}
s32 fn_80009218(void) {
    return 1;
}

bool fn_80009640(void) {
    return GSfsys::fn_802499E4();
}
bool fn_80009644(u32 fsysId) {
    return GSfsys::fn_802499EC(fsysId);
}
void *fn_80009648(u32 fsysId, u32 fileId, u32 size) {
    return GSfsys::fn_80249A28(fsysId, fileId, size);
}
void *fn_8000964C(u32 fsysId, u32 fileId, u32 size) {
    return GSfsys::fn_80249A44(fsysId, fileId, size);
}
}
