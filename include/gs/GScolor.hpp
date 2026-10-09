#pragma once

#include <revolution.h>

struct GScolor : public GXColor {
    GScolor() {}

    GScolor(u8 r, u8 g, u8 b, u8 a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    GScolor &operator=(const GScolor &other) {
        *reinterpret_cast<u32 *>(this) = other;
        return *this;
    }

    operator u32() const {
        return *reinterpret_cast<const u32 *>(this);
    }
};
