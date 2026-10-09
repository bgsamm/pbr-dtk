#pragma once

#include <revolution.h>

class GSrenderPass {
private:
    /* 0x0 */ u32 _0;

    // TODO(samm) Verify
    static GSrenderPass *sActiveRenderPass;

public:
    // TODO(samm) Name
    u32 get_0() const {
        return _0;
    }

    static GSrenderPass *getActiveRenderPass() {
        return sActiveRenderPass;
    }
};
