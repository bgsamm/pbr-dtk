#include ".unsorted/800477E8.hpp"

#include "common.hpp"

// TODO role: calls seven initialisation functions in turn
void fn_800477E8(void) {
    fn_8003E03C();
    fn_800401A0();
    fn_80033020();
    fn_800447E4();
    fn_80045550();
    fn_80035D58();
    fn_8004F37C();
}

// TODO role: sets the byte fn_800401F4 points to and notifies the object fn_80033088 returns
void fn_80047820(void) {
    Unk80040274 *q = fn_800401F4();
    if (q != NULL) {
        q->_0 = 1;
    }
    u8 *p = (u8 *)fn_80033088();
    if (p != NULL) {
        fn_80033488(p);
    }
}

// TODO role: clears the byte fn_800401F4 points to and notifies the object fn_80033088 returns
void fn_80047860(void) {
    Unk80040274 *q = fn_800401F4();
    if (q != NULL) {
        q->_0 = 0;
    }
    u8 *p = (u8 *)fn_80033088();
    if (p != NULL) {
        fn_80033494(p);
    }
}
