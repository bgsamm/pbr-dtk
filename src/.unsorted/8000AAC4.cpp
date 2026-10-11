#include ".unsorted/8000AAC4.hpp"

extern "C" {

/* lbl_80405F60 */ extern const u8 lbl_80405F60[];

void fn_8000AAC4(Unk8000AAC4 *obj, Unk8000AAC4Sub *sub) { obj->_04 = sub; }
u8 fn_8000AACC(Unk8000AAC4 *obj) { return obj->_04->_05; }
u32 fn_8000AAD8(Unk8000AAC4 *obj) { return obj->_04->_08; }
u32 fn_8000AAE4(Unk8000AAC4 *obj) { return obj->_04->_08; }
u16 fn_8000AAF0(Unk8000AAC4 *obj) { return obj->_04->_06; }
BOOL fn_8000AAFC(Unk8000AAC4 *obj) { return obj->_04->_10 < 0; }
u32 fn_8000AB0C(Unk8000AAC4 *obj) { return obj->_04->_0C; }
u8 fn_8000AB18(Unk8000AAC4 *obj) { return obj->_04->_02; }
u16 fn_8000AB24(Unk8000AAC4 *obj) { return obj->_04->_00; }
u8 fn_8000AB30(Unk8000AAC4 *obj) { return obj->_04->_03; }
void fn_8000AC34(Unk8000AAC4 *obj) { obj->_00 = lbl_80405F60; }

}
