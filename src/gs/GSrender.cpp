#include <version.hpp>
#include <string.h>

#include "gs/GSrender.hpp"

void fn_8023234C();
void fn_80232394();

static void *lbl_804245BC[0x10]; // dummy

static GSrender *lbl_8063F698;

GSrender::GSrender(UnkStruct1 *param1)
    : GSvideo(param1->mNumBuffers, param1->mEfbHeight, param1->mVidFmt) {
    _d8 = lbl_804245BC;
    _1638 = 0;
    _16e8 = 0;
    _16ec = 0;
    _16f0 = 0;
    _16f4 = 0;
    _16f8 = 1;
    _16f9 = 1;
    _16fa = 0;
    _16fb = 0;
    _16fc = 0;
    _16fd = 0;
    _16fe = 0;
    _1700 = 0;
    _1704 = 0;
    _1708 = 0;
    _1709 = 0;
    _170a = 0;
    _170b = 0;
    _170c = 0;
    _1710 = 0;
    _1714 = 0;
    _1718 = 0;
    _1719 = 1;
    _171a = 0;
    _171b = 0;
    _171c = 0;
    _1720 = 0;
    _1724 = 0;
    _1728 = 0;
    _172c = 0;
    _1730 = 0;
    _1734 = 0;
    _1738 = 0x90;
    _173c = 0;
    memset(&_163c, 0, sizeof(_163c));
    _1638 = &_dc;
    _16e8 = new UnkClass5(param1->_C);
    fn_8023255C(param1->_8, param1->_10);
    lbl_8063F698 = this;
    fn_80239E58();
    GXSetDrawDoneCallback(fn_80232394);
    GXSetBreakPtCallback(fn_8023234C);
    GXSetMisc(GX_MT_XF_FLUSH, GX_XF_FLUSH_SAFE);
    fn_8023B704();
    fn_80237798(4);
    fn_80235204(0, 0f, 0f, 640f, 480f);
    fn_80235178(0, 0, 0, 0x280, 0x1e0);
    fn_8024041C();
    fn_8023F45C();
    fn_802327E8();
    _1719 = 0;
    _16f9 = 0;
}
