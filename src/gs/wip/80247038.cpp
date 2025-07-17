#include "version.hpp"

extern void fn_801DB4FC(u32, void *);
extern void fn_801DB548(u32, void *);

class UnkClass1 {
public:
    /* 0x0 */ s32 mCapacity;
    /* 0x4 */ void **mItems;

    UnkClass1(u32 param1);
    ~UnkClass1();

    bool fn_802470E8();
    bool fn_80247110(void *param1);
    void **fn_80247180();
    void fn_80247188(u32 param1);
    void fn_802471F4(u32 param1);
};

UnkClass1::UnkClass1(u32 capacity) {
    mCapacity = capacity;
    // TODO verify array type
    mItems = new void *[capacity + 1];

    if (mItems != NULL) {
        mItems[0] = NULL;
    }
}

UnkClass1::~UnkClass1() {
    if (mItems != NULL) {
        delete[] mItems;
    }
}

// empty
bool UnkClass1::fn_802470E8() {
    // Does not match as a single `if`
    if (mItems != NULL) {
        if (mItems[0] != NULL) {
            return false;
        }
    }
    return true;
}

// push_back
bool UnkClass1::fn_80247110(void *param1) {
    for (s32 i = 0; i < mCapacity; i++) {
        if (param1 == mItems[i]) {
            return true;
        }

        if (mItems[i] == NULL) {
            mItems[i] = param1;
            mItems[++i] = NULL;
            return true;
        }
    }
    return false;
}

void **UnkClass1::fn_80247180() {
    return mItems;
}

void UnkClass1::fn_80247188(u32 param1) {
    if (mItems == NULL) {
        return;
    }

    for (u32 i = 0; mItems[i] != NULL; i++) {
        fn_801DB4FC(param1, mItems[i]);
    }
}

void UnkClass1::fn_802471F4(u32 param1) {
    if (mItems == NULL) {
        return;
    }

    for (u32 i = 0; mItems[i] != NULL; i++) {
        fn_801DB548(param1, mItems[i]);
    }
}
