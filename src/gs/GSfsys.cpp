#include <version.hpp>

#include <cstdio>
#include <revolution/os.h>

#include "gs/GSfsys.hpp"
#include "gs/GStask.hpp"

extern u32 lbl_8063F600; // very possibly a singleton
extern u32 fn_801DC0C8(u32, bool); // DVD init?
extern u32 fn_801DC2D0(char *); // file open?
extern s32 fn_801DC3FC(u32, void *, u32, bool); // file read?
extern void fn_801DC6C4(u32); // file close?
extern u32 fn_801DC760(u32); // gets file size?
extern void fn_80224588(u32);
extern void fn_80244B48();
extern u32 fn_80244EDC(bool);
extern u32 fn_802458BC(bool, bool);
extern u32 fn_802459FC();
extern u32 fn_80245EE0(UnkStruct8 *, u32);

#define LIST_LEN 3
// 3 doubly linked lists
static UnkStruct4 *lbl_80497FA0[LIST_LEN];

/* lbl_8063F856 */ static bool isInitialized;
static u32 lbl_8063F858; // count for lbl_8063F870
static u32 lbl_8063F85C;
static u32 lbl_8063F860;
static u32 lbl_8063F864;
static u32 lbl_8063F868;
static UnkStruct3 *lbl_8063F86C;
static UnkStruct1 *lbl_8063F870;
static UnkStruct5 *lbl_8063F874;
static UnkStruct6 *lbl_8063F878;
static UnkStruct4 *lbl_8063F87C;
static UnkStruct4 *lbl_8063F880;
static u32 lbl_8063F884;
static u32 lbl_8063F888;

bool GSfsys::fn_80247288() {
    u32 size;
    u32 var1 = fn_801DC2D0("gsfsys.toc");
    if (var1 == 0) {
        return false;
    }

    size = (fn_801DC760(var1) + 0x1f) / 0x20 * 0x20;
    lbl_8063F86C = (UnkStruct3 *)fn_80247280(size);
    if (lbl_8063F86C == NULL) {
        return false;
    }

    s32 var2 = fn_801DC3FC(var1, lbl_8063F86C, size, false);
    if (var2 < 0) {
        fn_801DC6C4(var1);
        return false;
    }

    fn_801DC6C4(var1);
    UnkStruct2 *ptr = (UnkStruct2 *)((u8 *)lbl_8063F86C + lbl_8063F86C->mTableOffset);
    for (int i = 0; i < lbl_8063F86C->mCount; i++) {
        ptr->mName = (char *)((u8 *)lbl_8063F86C + (u32)ptr->mName);
        ptr->mFlags = 0;
        ptr++;
    }

    return true;
}

UnkStruct1 *GSfsys::fn_80247470(u32 fsysID, bool param2) {
    for (int i = 0; i < lbl_8063F858; i++) {
        // TODO should this really be a bool?
        if (param2 == true) {
            switch (lbl_8063F870[i].mState) {
                case FSYS_STATE_NEG_999:
                case FSYS_STATE_0:
                case FSYS_STATE_12:
                    continue;
            }
        }
        else if (lbl_8063F870[i].mState == FSYS_STATE_0) {
            continue;
        }

        if (lbl_8063F870[i].mID == fsysID) {
            return &lbl_8063F870[i];
        }
    }
    return NULL;
}

UnkStruct1 *GSfsys::fn_802474F4(int param1) {
    UnkStruct1 *var1 = NULL;

    int i = lbl_8063F85C;
    while (var1 == NULL) {
        switch (lbl_8063F870[i].mState) {
            case FSYS_STATE_12:
                if (param1 == 1) {
                    break;
                }
                // fallthrough
            case FSYS_STATE_NEG_999:
            case FSYS_STATE_0:
            case FSYS_STATE_1:
                var1 = &lbl_8063F870[i];
                if (var1->_20 != 0) {
                    fn_80244B48();
                }
                break;
        }

        i++;
        if (i >= lbl_8063F858) {
            i = 0;
        }

        if (i == lbl_8063F85C) {
            break;
        }
    }
    lbl_8063F85C = i;
    return var1;
}

UnkStruct1 *GSfsys::fn_802475C0() {
    UnkStruct1 *var1;

    var1 = fn_802474F4(1);
    if (var1 != NULL) {
        return var1;
    }

    var1 = fn_802474F4(0);
    if (var1 != NULL) {
        return var1;
    }

    return NULL;
}

// finds fsys entry in toc
UnkStruct2 *GSfsys::fn_802477F4(u32 fsysID) {
    u32 count = lbl_8063F86C->mCount;
    // TODO better understand the derivation of this pointer
    UnkStruct2 *ptr = (UnkStruct2 *)((u8 *)lbl_8063F86C + lbl_8063F86C->mTableOffset);
    for (int i = 0; i < count; i++, ptr++) {
        if (ptr->mID == fsysID) {
            return ptr;
        }
    }
    return NULL;
}

void GSfsys::fn_80247834(UnkStruct1 *param1, FsysState param2) {
    BOOL intEnabled = OSDisableInterrupts();
    param1->_18 = param2;
    OSRestoreInterrupts(intEnabled);
}

void GSfsys::fn_80247874(UnkStruct1 *param1, u32 param2) {
    BOOL intEnabled = OSDisableInterrupts();
    param1->_40 = param2;
    OSRestoreInterrupts(intEnabled);
}

bool GSfsys::fn_802478B4(UnkStruct1 *param1, char *param2) {
    UnkStruct2 *var1 = fn_802477F4(param1->mID);
    if (var1 == NULL) {
        return false;
    }

    sprintf(param2, "%s.fsys", var1->mName);
    return true;
}

bool GSfsys::fn_8024790C(UnkStruct1 *param1) {
    char var1[0x80];
    fn_802478B4(param1, var1);
    param1->_C = fn_801DC2D0(var1);
    if (param1->_C == 0) {
        fn_80249B58(param1, FSYS_STATE_NEG_998);
        return false;
    }

    if (param1->_1c->_8 == 0) {
        fn_80249B58(param1, FSYS_STATE_3);
    }
    else {
        fn_80249B58(param1, FSYS_STATE_5);
    }
    return true;
}

void GSfsys::fn_80247EA8(u32 fsysID, u32 param2) {
    UnkStruct2 *var1 = fn_802477F4(fsysID);
    if (var1 != NULL) {
        var1->mFlags &= ~param2;
    }
}

// void GSfsys::fn_802482B4(u32 param1, u32 param2) {
//     UnkStruct6 *var1, *next;
//     UnkStruct7 *var3;
//     UnkStruct8 *var4;
//     u32 var5, var6;
    
//     var1 = lbl_8063F878;
//     while (var1 != NULL) {
//         next = var1->mNext;
//         if (var1->_9 == 1) {
//             var3 = var1->_10;
//             var4 = var1->_C;
//             var5 = fn_80247C5C(var4, var3->_0);
//             if (var5 != 0) {
//                 var6 = fn_80245EE0(var4, var5 - 1);
//             }
//             else {
//                 var6 = 0;
//             }
//             var5 = fn_80247C5C(var4, var4->_8);
//             if (var5 == 0xffff) {
                
//             }
//         }
//         var1 = next;
//     }
// };

bool GSfsys::fn_80248B4C(bool param1, bool param2, bool param3) {
    if (isInitialized == true) {
        return false;
    }

    lbl_8063F85C = 0;
    lbl_8063F864 = 0;
    lbl_80497FA0[0] = NULL;
    lbl_80497FA0[1] = NULL;
    lbl_80497FA0[2] = NULL;
    lbl_8063F880 = NULL;

    if (fn_80244EDC(param1) == 0) {
        return false;
    }

    if (fn_802458BC(param2, param3) == 0) {
        return false;
    }

    lbl_8063F858 = 4;
    lbl_8063F860 = 32;
    lbl_8063F868 = 24;
    
    lbl_8063F870 = (UnkStruct1 *)fn_80247280(sizeof(UnkStruct1) * lbl_8063F858);
    if (lbl_8063F870 == NULL) {
        return false;
    }

    lbl_8063F874 = (UnkStruct5 *)fn_80247280(sizeof(UnkStruct5) * lbl_8063F860);
    if (lbl_8063F874 == NULL) {
        return false;
    }

    lbl_8063F87C = (UnkStruct4 *)fn_80247280(sizeof(UnkStruct4) * lbl_8063F868);
    if (lbl_8063F87C == NULL) {
        return false;
    }

    for (int i = 0; i < lbl_8063F858; i++) {
        lbl_8063F870[i].mState = FSYS_STATE_0;
        lbl_8063F870[i]._18 = FSYS_STATE_FFFF;
        lbl_8063F870[i]._20 = 0;
        lbl_8063F870[i]._2e = false;
    }

    for (int i = 0; i < lbl_8063F860; i++) {
        lbl_8063F874[i]._8 = false;
    }

    for (int i = 0; i < lbl_8063F868; i++) {
        lbl_8063F87C[i].mID = 0;
    }

    if (!fn_80247288()) {
        return false;
    }

    lbl_8063F884 = GStask::createTask(TASK_TYPE_1, 254, 0, fn_802482B4);
    GStask::setTaskName(lbl_8063F884, "GSfsysDaemonForeground");

    lbl_8063F888 = GStask::createTask(TASK_TYPE_1, 2, 0, fn_80248A54);
    GStask::setTaskName(lbl_8063F888, "GSfsysDaemonBackground");

    isInitialized = true;

    return true;
}

int GSfsys::fn_80248DC0(u32 fsysID) {
    if (!isInitialized) {
        return -2;
    }

    UnkStruct2 *var1 = fn_802477F4(fsysID);
    if (var1 == NULL) {
        return -1;
    }
    else if ((var1->mFlags & 1) != 0) {
        return 0;
    }

    UnkStruct1 *var2 = fn_80247470(fsysID, false);
    if (var2 == NULL) {
        return -1;
    }

    switch (var2->mState) {
        case FSYS_STATE_12:
            return 0;
        
        case FSYS_STATE_1:
            return -1;
        
        case FSYS_STATE_NEG_999:
            return -2;
        
        default:
            return 1;
    }
}

void GSfsys::fn_80248E84(u32 fsysID) {
    fn_80247EA8(fsysID, true);

    UnkStruct1 *var1 = fn_80247470(fsysID, false);
    if (var1 != NULL) {
        var1->mState = FSYS_STATE_1;
    }
}

bool GSfsys::fn_80248ED0(
    u32 fsysID,
    u32 param2,
    u32 param3,
    bool param4,
    u32 param5,
    u32 param6,
    u32 param7,
    u32 param8
) {
    UnkStruct1 *var1;

    BOOL intEnabled = OSDisableInterrupts();
    fn_80248E84(fsysID);
    var1 = fn_80247470(fsysID, false);
    if (var1 == NULL) {
        var1 = fn_802475C0();
        if (var1 == NULL) {
            OSRestoreInterrupts(intEnabled);
            return false;
        }
        var1->_20 = 0;
        var1->_3c = fn_802459FC();
    }

    var1->mID = fsysID;
    var1->_8 = param2;
    var1->_C = 0;
    var1->_10 = param3;
    var1->mState = FSYS_STATE_2;
    var1->_18 = FSYS_STATE_FFFF;
    var1->_24 = 0;
    var1->_28 = 0;
    var1->_2c = false;
    var1->_2d = param4;
    var1->_30 = param5;
    var1->_34 = param6;
    var1->_38 = param7;
    var1->_40 = param8;
    var1->_44 = param8;

    var1->_1c = fn_802477F4(fsysID);
    fn_8024790C(var1);
    OSRestoreInterrupts(intEnabled);

    return true;
}

UnkStruct4 *GSfsys::fn_80248FE0(
    int param1,
    u32 fsysID,
    u32 param3,
    bool param4,
    bool param5,
    bool param6,
    bool param7,
    int param8
) {
    UnkStruct4 *var1 = NULL;
    for (int i = 0; i < lbl_8063F868; i++) {
        if (lbl_8063F87C[i].mID == 0) {
            var1 = &lbl_8063F87C[i];
            var1->mPrev = NULL;
            var1->mNext = NULL;
            var1->_8 = param1;
            var1->mID = fsysID;
            var1->_10 = param3;
            var1->_14 = param5;
            var1->_18 = param6;
            var1->_1c = param7;
            var1->_24 = param4;
            var1->_25 = false;
            var1->_20 = param8;
            break;
        }
    }
    return var1;
}

UnkStruct4 *GSfsys::fn_80249074(u32 fsysID, u32 param2) {
    UnkStruct4 *var1;
    for (int i = 0; i < LIST_LEN; i++) {
        var1 = lbl_80497FA0[i];
        while (var1 != NULL) {
            if (var1->mID == fsysID) {
                return var1;
            }
            var1 = var1->mNext;
        }
    }
    return NULL;
}

// inserts node into doubly linked list
bool GSfsys::fn_802490F8(UnkStruct4 *param1, int index) {
    bool result;

    if (lbl_80497FA0[index] == NULL) {
        lbl_80497FA0[index] = param1;
        result = true;
    }
    else {
        UnkStruct4 *var1 = lbl_80497FA0[index];
        while (var1->mNext != NULL) {
            var1 = var1->mNext;
        }

        var1->mNext = param1;
        param1->mPrev = var1;
        result = false;
    }

    return result;
}

// removes node from doubly linked list
void GSfsys::fn_80249144(UnkStruct4 *param1) {
    if (param1->mPrev != NULL) {
        param1->mPrev->mNext = param1->mNext;
    }

    if (param1->mNext != NULL) {
        param1->mNext->mPrev = param1->mPrev;
    }

    for (int i = 0; i < LIST_LEN; i++) {
        if (param1 == lbl_80497FA0[i]) {
            lbl_80497FA0[i] = param1->mNext;
            break;
        }
    }

    param1->mID = NULL;
}

bool GSfsys::fn_802491BC(UnkStruct4 *param1) {
    if (!param1->_25) {
        param1->_25 = true;
        switch (param1->_8) {
            case 5:
                fn_80249664(param1->mID);
                return false;
            
            default:
                fn_80249144(param1);
                return true;
            
            case 1:
            case 2:
            case 3:
            case 4:
                fn_80248ED0(param1->mID, param1->_10, param1->_8, param1->_24, param1->_14, param1->_18, param1->_1c, param1->_20);
                return false;
        }
    }
    else if (fn_80248DC0(param1->mID) <= 0) {
        fn_80249144(param1);
        return true;
    }
    return false;
}

void GSfsys::fn_80249280() {
    if (lbl_8063F880 != NULL) {
        if (fn_802491BC(lbl_8063F880) == 0) {
            return;
        }
        lbl_8063F880 = NULL;
    }

    UnkStruct4 *var2, *next;
    for (int i = 0; i < LIST_LEN; i++) {
        var2 = lbl_80497FA0[i];
        while (var2 != NULL) {
            next = var2->mNext;
            if (fn_802491BC(var2) == 0) {
                lbl_8063F880 = var2;
                return;
            }
            var2 = next;
        }
    }
}

bool GSfsys::fn_80249328(int param1, u32 fsysID, u32 param3, bool param4, bool param5, bool param6, bool param7, int param8, int param9) {
    if (!isInitialized) {
        return false;
    }

    // Was this supposed to test param1 for both?
    if (param1 < 0 || param8 >= 6) {
        return false;
    }

    if (param8 < 0 || param8 >= LIST_LEN) {
        return false;
    }
    
    UnkStruct4 *var1 = fn_80249074(fsysID, param3);
    if (var1 != NULL && !var1->_25 && (param1 == 2 || param1 == 3)) {
        fn_80249144(var1);
    }

    UnkStruct4 *var2 = fn_80248FE0(param1, fsysID, param3, param4, param5, param6, param7, param9);
    if (var2 == NULL) {
        return false;
    }

    if (fn_802490F8(var2, param8) == true) {
        fn_80249280();
    }

    return true;
}

bool GSfsys::fn_80249438(u32 fsysID) {
    return fn_80249328(true, fsysID, 0xffff, false, false, false, false, true, false);
}

bool GSfsys::fn_80249548(u32 fsysID, bool param2) {
    if (!isInitialized) {
        return false;
    }

    while (true) {
        int var1 = fn_80248DC0(fsysID);
        if (var1 == 0) {
            return true;
        }
        else if (var1 == -1) {
            if (param2 == true) {
                return true;
            }
        }
        else if (var1 <= -2) {
            return false;
        }
        fn_80224588(lbl_8063F600);
    }
}

// loads fsys
bool GSfsys::fn_802495DC(u32 fsysID) {
    if (!isInitialized) {
        return false;
    }

    UnkStruct1 *var1 = fn_80247470(fsysID, true);
    if (var1 != NULL && var1->_10 == 2) {
        fn_802496DC(fsysID);
    }

    do {
        if (fn_80249438(fsysID) == true) {
            break;
        }
        fn_80224588(lbl_8063F600);
    } while (true);

    return fn_80249548(fsysID, false);
}

bool GSfsys::fn_80249664(u32 fsysID) {
    if (!isInitialized) {
        return false;
    }

    if (fn_80248DC0(fsysID) <= 0) {
        return false;
    }

    UnkStruct1 *var1 = fn_80247470(fsysID, true);
    if (var1 == NULL) {
        return false;
    }

    var1->_2c = true;
    return true;
}

bool GSfsys::fn_802496DC(u32 fsysID) {
    if (fn_80249664(fsysID) == false) {
        return false;
    }

    return fn_80249548(fsysID, false);
}

void GSfsys::fn_802499B0(u32 param1, bool param2, bool param3, bool param4) {
    fn_801DC0C8(param1, false);
    // were params 2 - 4 supposed to be passed here?
    fn_80248B4C(false, false, false);
}

void GSfsys::fn_80249B58(UnkStruct1 *param1, FsysState param2) {
    fn_80247834(param1, param2);
}
