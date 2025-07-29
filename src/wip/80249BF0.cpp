#include "global.hpp"

#include "gs/GSmem.hpp"
#include "wip/80249BF0.hpp"

extern MEMHeapHandle lbl_8063E8E8;

struct UnkStruct1 {
    /* 0x0 */ UnkStruct1 *mNext;
    u8 unk1[0x8];
};

static UnkStruct1 *lbl_8063F8C0;
static UnkStruct1 *lbl_8063F8C4;

void GSunk::fn_80249BF0(u32 param1) {
    if (lbl_8063F8C0 != NULL) {
        GSmem::freeToHeap(lbl_8063E8E8, lbl_8063F8C0);
    }

    u32 count = (param1 + sizeof(UnkStruct1) - 1) / sizeof(UnkStruct1);
    lbl_8063F8C0 = (UnkStruct1 *)GSmem::allocFromHeap(lbl_8063E8E8, count * sizeof(UnkStruct1));
    lbl_8063F8C4 = lbl_8063F8C0;

    UnkStruct1 *var1 = lbl_8063F8C4;
    for (u32 i = 0; i < count - 1; i++) {
        var1->mNext = var1 + 1;
        var1++;
    }
    var1->mNext = NULL;
}

UnkStruct1 *GSunk::fn_80249CF8() {
    UnkStruct1 *var1 = lbl_8063F8C4;
    lbl_8063F8C4 = var1->mNext;
    return var1;
}

void GSunk::fn_80249D08(UnkStruct1 *param1) {
    param1->mNext = lbl_8063F8C4;
    lbl_8063F8C4 = param1;
}
