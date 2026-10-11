#include ".unsorted/80249D38.hpp"

#include "common.hpp"
#include "gs/GSmem.hpp"

extern "C" {

void fn_8024B4B0(void) { fn_8024BB74(); }
void fn_8024C42C(void) {}
void fn_8024C430(void) {}
void fn_8024C434(void) {}
void fn_8024C438(void) {}
void fn_8024C43C(void) {}

void fn_8024F958(Unk80249D38 *obj, u8 v) { obj->_D54 = v << 5; }
u8 fn_8024F964(Unk80249D38 *obj) { return (obj->_D54 >> 5) & 0xFF; }

void fn_8024FF4C(Unk80249D38 *, void *block) {
    if (block != NULL) {
        GSmem::freeToHeap(gUnkHeap2, block);
    }
}

void fn_8025004C(u32 a) { fn_8024A464(&lbl_80497FEC, a); }
void fn_8025005C(u32 a) { fn_8024A758(&lbl_80497FEC, a); }
void fn_8025006C(u32 a) { fn_8024AE58(&lbl_80497FEC, a); }
void fn_8025007C(u32 a) { fn_8024AB50(&lbl_80497FEC, a); }
void fn_8025008C(u32 a) { fn_8024AFA4(&lbl_80497FEC, a); }
void fn_802502BC(void) { fn_8024BC58(&lbl_80497FEC); }
void fn_802502C8(void) { fn_8024B3D4(&lbl_80497FEC); }
void fn_802502D4(u32 a) { fn_8024B440(&lbl_80497FEC, a); }
void fn_8025032C(u32 a) { fn_8024C504(&lbl_80497FEC, a); }
void fn_80250360(void *block) { fn_8024FF4C(&lbl_80497FEC, block); }
void fn_80250388(u32 a) { fn_8024C440(&lbl_80497FEC, a); }
void fn_802503F0(u32 a) { fn_8024FA74(&lbl_80497FEC, a); }
void fn_80250644(u32 a) { fn_8024F8C8(&lbl_80497FEC, a); }
void fn_80250654(u8 v) { fn_8024F958(&lbl_80497FEC, v); }
u8 fn_80250664(void) { return fn_8024F964(&lbl_80497FEC); }

}
