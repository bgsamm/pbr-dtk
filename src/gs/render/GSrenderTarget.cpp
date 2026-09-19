#include "gs/render/GSrenderTarget.hpp"

#include "common.hpp"

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

void GSrenderTarget::fn_8023B3B8(u32 arg0) {
    u8 targetId = (arg0 >> 16) & 0xff;
    if (targetId != mId) {
        return;
    }

    s32 _unk1 = (arg0 >> 8) & 0xff;
    if (!_unk1) {
        return;
    }

    u8 _unk2 = arg0 & 0xff;
    if (!_unk2) {
        return;
    }

    _UnkRenderTargetStruct_1 *_unk3 = _10;
    while (_unk3) {
        if (_unk1 == _unk3->_0->_0 && _unk2 == _unk3->_4->_4) {
            _unk3->_8++;
            return;
        }
        _unk3 = _unk3->mNext;
    }
}

void GSrenderTarget::fn_8023B59C() {}
