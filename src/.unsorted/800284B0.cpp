#include ".unsorted/800284B0.hpp"

#include "common.hpp"

extern "C" {

void fn_80028554(Unk800284B0Value *value, u32 v) {
    value->_04.u = v;
    value->_00 = 1;
}

void fn_8002A294(void) {}
void fn_8002A298(void) {}
u32 fn_8002A2EC(Unk800284B0 *obj) {
    return obj->mFlags & 0x1;
}
u16 fn_8002A2F8(Unk800284B0 *obj) {
    return obj->_510;
}

void fn_8002A300(Unk800284B0 *obj, u16 a, u8 b, u16 c, u16 d, u32 e) {
    obj->_510 = a;
    obj->_512 = d;
    obj->_516 = b;
    obj->_514 = c;
    obj->_518 = e;
    obj->_50C = 1;
}

void fn_8002A320(Unk800284B0 *obj, u16 v) {
    obj->_50E = v;
}
u16 fn_8002A328(Unk800284B0 *obj) {
    return obj->_512;
}
u8 fn_8002A330(Unk800284B0 *obj) {
    return obj->_516;
}
u32 fn_8002A338(Unk800284B0 *obj) {
    return obj->_514 & 0xFF;
}
u32 fn_8002A344(Unk800284B0 *obj) {
    return obj->_518;
}

void fn_8002A34C(Unk800284B0Value *value, f32 v) {
    value->_04.f = v;
    value->_00 = 2;
}

void fn_8002A35C(Vec *dst, const Vec *src) {
    *dst = *src;
}

u32 fn_8002A3D8(Unk800284B0Value *value) {
    if (value->_00 == 4) {
        return value->_04.u;
    }
    return fn_800282E0(value);
}

void fn_8002A484(Unk800284B0 *obj, f32 v) {
    obj->_D80 = v;
}
void fn_8002A48C(Unk800284B0 *obj, f32 v) {
    obj->_D84 = v;
}
void fn_8002A494(Unk800284B0 *obj, u8 v) {
    obj->_D88 = v;
}
u16 fn_8002A49C(Unk800284B0 *obj) {
    return obj->_50E;
}
u32 fn_8002A51C(Unk800284B0 *obj) {
    return (obj->mFlags >> 12) & 0x1;
}
u32 fn_8002A528(Unk800284B0 *obj) {
    return (obj->mFlags >> 22) & 0x1;
}
u32 fn_8002A534(Unk800284B0 *obj) {
    return (obj->mFlags >> 13) & 0x1;
}
u32 fn_8002A540(Unk800284B0 *obj) {
    return (obj->mFlags >> 14) & 0x1;
}
u32 fn_8002A54C(Unk800284B0 *obj) {
    return (obj->mFlags >> 19) & 0x1;
}
u32 fn_8002A558(Unk800284B0 *obj) {
    return (obj->mFlags >> 20) & 0x1;
}
u32 fn_8002A564(Unk800284B0 *obj) {
    return (obj->mFlags >> 23) & 0x1;
}

u32 fn_8002A570(Unk800284B0Value *value) {
    if (value->_00 == 3) {
        return value->_04.u;
    }
    return fn_800283B0(value);
}

Vec *fn_8002A5C0(Unk800284B0 *obj) {
    return &obj->_DB4;
}

// TODO same inline Vec setter as fn_8002CABC
void fn_8002A5C8(Vec *v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

u32 fn_8002A7F8(Unk800284B0 *obj) {
    return (obj->mFlags >> 15) & 0x1;
}
Unk80024914 *fn_8002A804(void) {
    return lbl_8063E9B0;
}
void fn_8002A80C(Unk800284B0 *obj, u16 v) {
    obj->_50C = v;
}
u16 fn_8002A814(Unk800284B0 *obj) {
    return obj->_51C;
}
u8 fn_8002A81C(Unk800284B0 *obj) {
    return obj->_520;
}
void fn_8002A84C(void) {}

void fn_8002A850(GXColor *color, u8 r, u8 g, u8 b, u8 a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}
}
