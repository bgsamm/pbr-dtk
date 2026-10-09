#pragma once

#include "gs/GSrender.hpp"

#include <revolution.h>

// Size: 0x148
class _UnkClass8023C09C {
private:
    /* 0x000 */ u8 _pad_[0x148];

public:
    _UnkClass8023C09C(void *arg0);
    ~_UnkClass8023C09C();

    void fn_8023C2E8();
};

bool fn_8023CAA8(GSvertexFormat *vtxFmt, u32 arg1);
