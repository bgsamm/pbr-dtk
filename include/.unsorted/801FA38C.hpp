#pragma once

#include <revolution.h>

class _UnkClass801FA38C {
private:
    static _UnkClass801FA38C *sInstance;

private:
    void fn_801FAFE0(f32 deltaTime);

public:
    static void update(f32 deltaTime) {
        if (sInstance) {
            sInstance->fn_801FAFE0(deltaTime);
        }
    }

    static _UnkClass801FA38C *getInstance() {
        return sInstance;
    }
};
