#include ".unsorted/80249D38.hpp"

#include "gs/GSmem.hpp"

#include "common.hpp"

extern "C" {

extern f32 lbl_8063F8D8;

void fn_8024B4B0(void) {
    fn_8024BB74();
}

void fn_8024C42C(void) {}
void fn_8024C430(void) {}
void fn_8024C434(void) {}
void fn_8024C438(void) {}
void fn_8024C43C(void) {}

// TODO role: 8-bit field stored shifted by 5 at 0xD54, with its getter
void fn_8024F958(Unk80249D38 *obj, u8 v) {
    obj->_D54 = v << 5;
}

u8 fn_8024F964(Unk80249D38 *obj) {
    return (obj->_D54 >> 5) & 0xFF;
}

// TODO role: setters on a second record (0x34 as a signed byte; 0x64, 0x1E and 0x20 reset)
void fn_8024F9B8(Unk80249D38 *, Unk8024F9B8 *arg, s32 value) {
    arg->_34 = (s8)value;
}

void fn_8024FA5C(Unk80249D38 *, Unk8024F9B8 *arg) {
    arg->_64 = 0;
    arg->_1E = -1;
    arg->_20 = -1;
}

// TODO role: allocates from the second game heap, size rounded up to a multiple of 32
void *fn_8024FF3C(Unk80249D38 *, u32 size) {
    return GSmem::allocFromHeap(gUnkHeap2, (size + 0x1F) & ~0x1F);
}

// TODO role: frees a block of that heap when it is not null
void fn_8024FF4C(Unk80249D38 *, void *block) {
    if (block != NULL) {
        GSmem::freeToHeap(gUnkHeap2, block);
    }
}

// TODO role: the wrappers below call methods of the global object lbl_80497FEC
void fn_8025004C(u32 a) {
    fn_8024A464(&lbl_80497FEC, a);
}

void fn_8025005C(u32 a) {
    fn_8024A758(&lbl_80497FEC, a);
}

void fn_8025006C(u32 a) {
    fn_8024AE58(&lbl_80497FEC, a);
}

void fn_8025007C(u32 a) {
    fn_8024AB50(&lbl_80497FEC, a);
}

void fn_8025008C(u32 a) {
    fn_8024AFA4(&lbl_80497FEC, a);
}

void fn_802502BC(void) {
    fn_8024BC58(&lbl_80497FEC);
}

void fn_802502C8(void) {
    fn_8024B3D4(&lbl_80497FEC);
}

void fn_802502D4(u32 a) {
    fn_8024B440(&lbl_80497FEC, a);
}

void fn_8025032C(void *a) {
    fn_8024C504(&lbl_80497FEC, a);
}

// TODO role: allocates from the object above, or returns null for a size of 0
void *fn_8025033C(u32 size) {
    if (size == 0) {
        return NULL;
    }
    return fn_8024FF3C(&lbl_80497FEC, size);
}

void fn_80250360(void *block) {
    fn_8024FF4C(&lbl_80497FEC, block);
}

void fn_80250370(u32 a, u32 b) {
    fn_8024F970(&lbl_80497FEC, a, b);
}

void fn_80250388(void *a) {
    fn_8024C440(&lbl_80497FEC, a);
}

void fn_80250398(u32 a, u32 b, u32 c) {
    fn_8024B084(&lbl_80497FEC, a, b, c);
}

void fn_802503B8(u32 a, u32 b, u32 c) {
    fn_8024B11C(&lbl_80497FEC, a, b, c);
}

void fn_802503D8(u32 a, u32 b) {
    fn_8024B364(&lbl_80497FEC, a, b);
}

void fn_802503F0(u32 a) {
    fn_8024FA74(&lbl_80497FEC, a);
}

void fn_80250400(u32 a, u32 b, u32 c) {
    fn_8024B9C4(&lbl_80497FEC, a, b, c);
}

void fn_80250644(u32 a) {
    fn_8024F8C8(&lbl_80497FEC, a);
}

void fn_80250654(u8 v) {
    fn_8024F958(&lbl_80497FEC, v);
}

u8 fn_80250664(void) {
    return fn_8024F964(&lbl_80497FEC);
}

// TODO role: sets a float global; the next function sets it to 0.59
void fn_80250ECC(f32 v) {
    lbl_8063F8D8 = v;
}

void fn_80250ED4(void) {
    lbl_8063F8D8 = 0.59f;
}
}
