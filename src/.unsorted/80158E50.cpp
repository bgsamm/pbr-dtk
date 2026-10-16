#include ".unsorted/80158E50.hpp"

#include ".unsorted/80249D38.hpp"

#include "common.hpp"

extern "C" {

/* lbl_8048773C */ extern Unk8048773C lbl_8048773C;
extern u32 lbl_8063EFF0;

// TODO role: same copy as fn_8015A98C into a local state, then fn_8025032C and fn_80250388 on it when a third argument
// is given; two members come back
void fn_8015A840(Unk80158E50 *, Unk8015AAF0 *src, void *member) {
    Unk8015AAF0 tmp;
    tmp._1C = 0;
    tmp._08 = src->_2C;
    tmp._0C = src->_30;
    tmp._10 = src->_10;
    tmp._12 = src->_12;
    tmp._14 = src->_14;
    tmp._5C = src->_5C;
    tmp._60 = src->_60;
    tmp._18 = src->_18;
    tmp._19 = src->_19;
    tmp._1A = src->_1A;
    tmp._1E = src->_1E;
    tmp._20 = src->_20;
    tmp._22 = src->_22;
    tmp._24 = src->_24;
    tmp._1B = src->_1B;
    tmp._26 = src->_26;
    tmp._40 = src->_40;
    tmp._34 = src->_34;
    tmp._38 = src->_38;
    tmp._3C = src->_3C;
    tmp._5A = src->_5A;
    tmp._59 = src->_59;
    tmp._64 = 1;
    tmp._44 = src->_44;
    for (int i = 0; i < 8; i++) {
        tmp._68[i] = NULL;
    }
    tmp._00 = member;
    if (member != NULL) {
        fn_8025032C(&tmp);
        fn_80250388(&tmp);
    }
    src->_2C = tmp._2C;
    src->_30 = tmp._30;
    src->_5C = tmp._5C;
    src->_60 = tmp._60;
}

// TODO role: copies the state in the second argument into a new slot, resets the slot's own eight slots and attaches
// the third argument
void fn_8015A98C(Unk80158E50 *, Unk8015AAF0 *src, Unk8015AAF0 *dst, void *member) {
    dst->_08 = src->_2C;
    dst->_0C = src->_30;
    dst->_10 = src->_10;
    dst->_12 = src->_12;
    dst->_14 = src->_14;
    dst->_18 = src->_18;
    dst->_19 = src->_19;
    dst->_1A = src->_1A;
    dst->_1E = src->_1E;
    dst->_20 = src->_20;
    dst->_22 = src->_22;
    dst->_24 = src->_24;
    dst->_1C = 1;
    dst->_1B = src->_1B;
    dst->_26 = src->_26;
    dst->_40 = src->_40;
    dst->_34 = src->_34;
    dst->_38 = src->_38;
    dst->_3C = src->_3C;
    dst->_5A = src->_5A;
    dst->_59 = src->_59;
    dst->_64 = 1;
    dst->_44 = src->_44;
    for (int i = 0; i < 8; i++) {
        dst->_68[i] = NULL;
    }
    dst->_00 = member;
}

// TODO role: copies two members of the slot back into the first argument; returns 1 once the slot has reached its end
// state
u32 fn_8015AA6C(Unk80158E50 *, Unk8015AAF0 *arg, Unk8015AAF0 *slot) {
    if (slot->_00 != NULL) {
        fn_8025032C(slot);
    }
    arg->_2C = slot->_2C;
    arg->_30 = slot->_30;
    if (slot->_1E == -1 && slot->_20 == -1) {
        slot->_64 = 1;
        return 1;
    }
    return 0;
}

// TODO role: advances through the 8 slots of the second argument; each new slot is allocated and filled by fn_8015A98C
u32 fn_8015AAF0(Unk80158E50 *obj, Unk8015AAF0 *arg, void *member) {
    if (member == NULL) {
        return 1;
    }
    if (arg->_1E == -1) {
        fn_8015A840(obj, arg, member);
        return 1;
    }
    if (arg->_68[arg->_88] == NULL) {
        arg->_68[arg->_88] = (Unk8015AAF0 *)fn_8025033C(sizeof(Unk8015AAF0));
        fn_8015A98C(obj, arg, arg->_68[arg->_88], member);
    }
    u32 result = fn_8015AA6C(obj, arg, arg->_68[arg->_88]);
    if (result == 1) {
        arg->_88++;
    }
    return result;
}

// TODO roles not established: each wrapper forwards one member of the object to fn_8015AAF0 or fn_8015ABD8
u32 fn_8015B65C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_00);
}
u32 fn_8015B664(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 0);
}
u32 fn_8015B670(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 7);
}
u32 fn_8015B67C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 1);
}
u32 fn_8015B688(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 8);
}
u32 fn_8015B694(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 2);
}
u32 fn_8015B6A0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 9);
}
u32 fn_8015B6AC(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 3);
}
u32 fn_8015B6B8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_10, 10);
}
u32 fn_8015B6C4(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 0);
}
u32 fn_8015B6D0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 7);
}
u32 fn_8015B6DC(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 1);
}
u32 fn_8015B6E8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 8);
}
u32 fn_8015B6F4(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 2);
}
u32 fn_8015B700(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 9);
}
u32 fn_8015B70C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 3);
}
u32 fn_8015B718(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_14, 10);
}
u32 fn_8015B724(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 0);
}
u32 fn_8015B730(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 7);
}
u32 fn_8015B73C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 1);
}
u32 fn_8015B748(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 8);
}
u32 fn_8015B754(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 2);
}
u32 fn_8015B760(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 9);
}
u32 fn_8015B76C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 3);
}
u32 fn_8015B778(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_18, 10);
}
u32 fn_8015B784(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 0);
}
u32 fn_8015B790(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 7);
}
u32 fn_8015B79C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 1);
}
u32 fn_8015B7A8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 8);
}
u32 fn_8015B7B4(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 2);
}
u32 fn_8015B7C0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 9);
}
u32 fn_8015B7CC(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 3);
}
u32 fn_8015B7D8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1C, 10);
}
void fn_8015B7E4(void) {}
void fn_8015B7E8(void) {}
void fn_8015B7EC(void) {}
void fn_8015BB14(void) {}
void fn_8015BB18(void) {}
u32 fn_8015BB1C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_28, 4);
}
u32 fn_8015BB28(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_28, 11);
}
u32 fn_8015BB34(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_2C, 4);
}
u32 fn_8015BB40(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_2C, 11);
}
u32 fn_8015BB4C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_30);
}
u32 fn_8015BB54(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_34);
}
u32 fn_8015BB5C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_38);
}
u32 fn_8015BB64(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_3C, 5);
}
u32 fn_8015BB70(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_3C, 12);
}
void fn_8015BB7C(void) {}
u32 fn_8015BB80(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_44);
}
u32 fn_8015BB88(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_48);
}
u32 fn_8015BB90(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_4C);
}
void fn_8015BB98(void) {}
u32 fn_8015BBE8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_5C);
}
u32 fn_8015BBF0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_60);
}
u32 fn_8015BBF8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_64);
}
u32 fn_8015BC00(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_68);
}
u32 fn_8015BC08(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_6C);
}
u32 fn_8015BC10(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_70);
}
u32 fn_8015BC18(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_74);
}
u32 fn_8015BC20(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_78);
}
u32 fn_8015BC28(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_7C);
}
u32 fn_8015BC30(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_80);
}
u32 fn_8015BC38(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_84);
}
u32 fn_8015BC40(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_88);
}
u32 fn_8015BC48(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_8C);
}
u32 fn_8015BC50(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_90);
}
void fn_8015BC58(void) {}
u32 fn_8015BCA8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_94);
}
u32 fn_8015BCB0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_98);
}
u32 fn_8015BCB8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_9C);
}
u32 fn_8015BCC0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_A0);
}
u32 fn_8015BCC8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_A4);
}
u32 fn_8015BCD0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_A8);
}
u32 fn_8015BCD8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_AC);
}
u32 fn_8015BCE0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_B0);
}
u32 fn_8015BCE8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_B4);
}
u32 fn_8015BCF0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_B8);
}
u32 fn_8015BCF8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_BC);
}
u32 fn_8015BD00(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_C0);
}
u32 fn_8015BD08(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_C4);
}
u32 fn_8015BD10(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_C8);
}
u32 fn_8015BD18(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_CC);
}
u32 fn_8015BD20(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_D0);
}
u32 fn_8015BD28(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_D4);
}
u32 fn_8015BD30(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_D8);
}
u32 fn_8015BD38(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_DC);
}
u32 fn_8015BD40(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_E0);
}
u32 fn_8015BD48(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_E4);
}
u32 fn_8015BD50(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_E8);
}
u32 fn_8015BD58(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_EC);
}
u32 fn_8015BD60(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_F0);
}
u32 fn_8015BD68(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_F4);
}
u32 fn_8015BD70(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_F8);
}
u32 fn_8015BD78(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_FC);
}
u32 fn_8015BD80(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_100);
}
u32 fn_8015BD88(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_104);
}
u32 fn_8015BD90(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_108);
}
u32 fn_8015BD98(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_10C);
}
u32 fn_8015BDA0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_110);
}
u32 fn_8015BDA8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_114);
}
u32 fn_8015BDB0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_118);
}
u32 fn_8015BDB8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_11C);
}
u32 fn_8015BDC0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_120);
}
u32 fn_8015BDC8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_124);
}
u32 fn_8015BDD0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_128);
}
u32 fn_8015BDD8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_12C);
}
u32 fn_8015BDE0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_130);
}
u32 fn_8015BDE8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_134);
}
u32 fn_8015BDF0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_138);
}
u32 fn_8015BDF8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_13C);
}
u32 fn_8015BE00(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_140);
}
u32 fn_8015BE08(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_144);
}
u32 fn_8015BE10(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_148);
}
u32 fn_8015BE18(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_14C);
}
u32 fn_8015BE20(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_150);
}
u32 fn_8015BE28(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_154);
}
u32 fn_8015BE30(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_158);
}
u32 fn_8015BE38(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_15C);
}
u32 fn_8015BE40(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_160);
}
u32 fn_8015BE48(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_164);
}
u32 fn_8015BE50(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_168);
}
u32 fn_8015BE58(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_16C);
}
u32 fn_8015BE60(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_170);
}
u32 fn_8015BE68(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_174);
}
u32 fn_8015BE70(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_178);
}
u32 fn_8015BE78(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_17C);
}
u32 fn_8015BE80(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_180);
}
u32 fn_8015BE88(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_184);
}
u32 fn_8015BE90(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_198, 1);
}
u32 fn_8015BE9C(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_198, 8);
}
u32 fn_8015BEA8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_19C, 1);
}
u32 fn_8015BEB4(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_19C, 8);
}
u32 fn_8015BEC0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1A0, 4);
}
u32 fn_8015BECC(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015ABD8(obj, arg, obj->_1A0, 11);
}
u32 fn_8015BED8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_188);
}
u32 fn_8015BEE0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_18C);
}
u32 fn_8015BEE8(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_190);
}
u32 fn_8015BEF0(Unk80158E50 *obj, Unk8015AAF0 *arg) {
    return fn_8015AAF0(obj, arg, obj->_194);
}
void fn_8015C0A0(void) {}
void fn_8015D340(u8 v) {
    lbl_8048773C._1B8 = v;
}
void fn_8015D350(u32 v) {
    lbl_8063EFF0 = v;
}
}
