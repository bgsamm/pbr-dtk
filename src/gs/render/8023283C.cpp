#include "gs/render/8023283C.hpp"

#include "gs/GSmem.hpp"

#include <revolution.h>

#include "common.hpp"

GSdisplayList::GSdisplayList() : mFlags(), _2(), mDisplayList(), mDisplayListSize(), mVertexFormat() {}

GSdisplayList::~GSdisplayList() {
    fn_802328AC();
}

void GSdisplayList::fn_802328AC() {
    if ((mFlags & (1 << 0))) {
        if (mDisplayList && (mFlags & (1 << 3))) {
            GSmem::free(mDisplayList);
        }
        mFlags &= ~(1 << 0);
    }
}

void GSdisplayList::call() {
    flush();
    GXCallDisplayList(mDisplayList, mDisplayListSize);
}

void GSdisplayList::flush() {
    if ((mFlags & (1 << 1))) {
        DCStoreRange(mDisplayList, mDisplayListSize);
        mFlags &= ~(1 << 1);
    }
}
