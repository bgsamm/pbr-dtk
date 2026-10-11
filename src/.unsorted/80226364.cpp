
// Fonctions simples (getters, stubs, tail calls)
#include "common.hpp"

extern "C" {

void fn_80227574();

void fn_8022756C(void) {}
void fn_80227570(void) {}
void fn_802275F8(void) { fn_80227574(); }
void fn_80227640(void) {}

}

#include "common.hpp"

extern "C" {

extern u32 lbl_8063F640;
void fn_80227620(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7);

void fn_80227644(void) { if (lbl_8063F640 != 0) { fn_80227620(lbl_8063F640, 0, 0, 0, 0, 0, 0, 0); } }

}
