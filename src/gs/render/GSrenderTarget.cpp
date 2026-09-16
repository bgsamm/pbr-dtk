#include "gs/render/GSrenderTarget.hpp"

#include "version.hpp"

GSrenderTarget *GSrenderTarget::sHead;
GSrenderTarget *GSrenderTarget::sTail;

GSrenderTarget::GSrenderTarget(s32 id, u8 arg1, u8 arg2, u32 arg3)
    : mId(id), _4(arg1), _5(arg2), _6(), _8(arg3), _c(), _10(), _14(), mNext() {
    registerTarget(this);
}

GSrenderTarget::~GSrenderTarget() {
    fn_8023B2F0();
    unregisterTarget(this);
}

GSrenderTarget *GSrenderTarget::findTarget(s32 id) {
    GSrenderTarget *module = sHead;
    while (module) {
        if (module->mId == id) {
            return module;
        }
        module = module->mNext;
    }
    return NULL;
}

void GSrenderTarget::registerTarget(GSrenderTarget *target) {
    if (!sHead) {
        sHead = target;
    }

    if (sTail) {
        sTail->mNext = target;
    }

    sTail = target;
}

void GSrenderTarget::unregisterTarget(GSrenderTarget *target) {
    if (target == sHead) {
        sHead = target->mNext;

        if (sTail == target) {
            sTail = NULL;
        }
    } else {
        GSrenderTarget *prev = sHead;
        while (prev) {
            if (prev->mNext == target) {
                break;
            }
            prev = prev->mNext;
        }

        prev->mNext = target->mNext;

        if (sTail == target) {
            sTail = target->mNext;
        }
    }

    target->mNext = NULL;
}

void GSrenderTarget::fn_8023B59C() {}
