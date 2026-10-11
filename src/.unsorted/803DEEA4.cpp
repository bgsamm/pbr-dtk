#include ".unsorted/803DEEA4.hpp"

#include <cstring>

/* lbl_8063D230 */ static Unk8063D230 sUnk8063D230[UNK_8063D230_COUNT];
// TODO Clears the 16 callback slots, which take the place of the DS task system.

void fn_803DEEA4() {
    for (s32 i = 0; i < UNK_8063D230_COUNT; i++) {
        memset(&sUnk8063D230[i], 0, sizeof(Unk8063D230));
    }
}
// TODO Puts a callback and its argument in the first free slot; the priority is ignored.

Unk8063D230 *fn_803DEF00(Unk8063D230Func func, void *arg, u32 priority) {
    Unk8063D230 *entry = sUnk8063D230;
    for (s32 i = 0; i < UNK_8063D230_COUNT; i++, entry++) {
        if (entry->func == NULL) {
            entry->func = func;
            entry->arg = arg;
            return entry;
        }
    }
    return NULL;
}
// TODO Frees the slot of a callback.

void fn_803DEF3C(Unk8063D230 *entry) {
    Unk8063D230 *slot = sUnk8063D230;
    for (s32 i = 0; i < UNK_8063D230_COUNT; i++, slot++) {
        if (slot == entry) {
            slot->func = NULL;
            slot->arg = NULL;
            return;
        }
    }
}
// TODO Runs every callback; fn_803D9E08 calls it once per frame.

void fn_803DEF70() {
    Unk8063D230 *entry = sUnk8063D230;
    for (s32 i = 0; i < UNK_8063D230_COUNT; i++, entry++) {
        if (entry->func != NULL) {
            entry->func(entry, entry->arg);
        }
    }
}
