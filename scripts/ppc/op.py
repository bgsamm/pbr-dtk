from enum import Enum
from typealiases import *

_load_ops: dict[PpcOp, ctype]
_store_ops: dict[PpcOp, ctype]


class PpcOp(Enum):
    # fmt: off
    ADD        = 31, 266
    ADDO       = 31, 778
    ADDC       = 31, 10
    ADDCO      = 31, 522
    ADDE       = 31, 138
    ADDEO      = 31, 650
    ADDI       = 14
    ADDIC      = 12
    ADDIC_     = 13
    ADDIS      = 15
    ADDME      = 31, 234
    ADDMEO     = 31, 746
    ADDZE      = 31, 202
    ADDZEO     = 31, 714
    AND        = 31, 28
    ANDC       = 31, 60
    ANDI_      = 28
    ANDIS_     = 29
    B          = 18
    BC         = 16
    BCCTR      = 19, 528
    BCLR       = 19, 16
    CMP        = 31, 0
    CMPI       = 11
    CMPL       = 31, 32
    CMPLI      = 10
    CNTLZW     = 31, 26
    CRAND      = 19, 257
    CRANDC     = 19, 129
    CREQV      = 19, 289
    CRNAND     = 19, 225
    CRNOR      = 19, 33
    CROR       = 19, 449
    CRORC      = 19, 417
    CRXOR      = 19, 193
    DCBF       = 31, 86
    DCBI       = 31, 470
    DCBST      = 31, 54
    DCBT       = 31, 278
    DCBTST     = 31, 246
    DCBZ       = 31, 1014
    DCBZ_L     = 4, 1014
    DIVW       = 31, 491
    DIVWO      = 31, 1003
    DIVWU      = 31, 459
    DIVWUO     = 31, 971
    ECIWX      = 31, 310
    ECOWX      = 31, 438
    EIEIO      = 31, 854
    EQV        = 31, 284
    EXTSB      = 31, 954
    EXTSH      = 31, 922
    FABS       = 63, 264
    FADD       = 63, 21
    FADDS      = 59, 21
    FCMPO      = 63, 32
    FCMPU      = 63, 0
    FCTIW      = 63, 14
    FCTIWZ     = 63, 15
    FDIV       = 63, 18
    FDIVS      = 59, 18
    FMADD      = 63, 29
    FMADDS     = 59, 29
    FMR        = 63, 72
    FMSUB      = 63, 28
    FMSUBS     = 59, 28
    FMUL       = 63, 25
    FMULS      = 59, 25
    FNABS      = 63, 136
    FNEG       = 63, 40
    FNMADD     = 63, 31
    FNMADDS    = 59, 31
    FNMSUB     = 63, 30
    FNMSUBS    = 59, 30
    FRES       = 59, 24
    FRSP       = 63, 12
    FRSQRTE    = 63, 26
    FSEL       = 63, 23
    FSUB       = 63, 20
    FSUBS      = 59, 20
    ICBI       = 31, 982
    ISYNC      = 19, 150
    LBZ        = 34
    LBZU       = 35
    LBZUX      = 31, 119
    LBZX       = 31, 87
    LFD        = 50
    LFDU       = 51
    LFDUX      = 31, 631
    LFDX       = 31, 599
    LFS        = 48
    LFSU       = 49
    LFSUX      = 31, 567
    LFSX       = 31, 535
    LHA        = 42
    LHAU       = 43
    LHAUX      = 31, 375
    LHAX       = 31, 343
    LHBRX      = 31, 790
    LHZ        = 40
    LHZU       = 41
    LHZUX      = 31, 311
    LHZX       = 31, 279
    LMW        = 46
    LSWI       = 31, 597
    LSWX       = 31, 533
    LWARX      = 31, 20
    LWBRX      = 31, 534
    LWZ        = 32
    LWZU       = 33
    LWZUX      = 31, 55
    LWZX       = 31, 23
    MCRF       = 19, 0
    MCRFS      = 63, 64
    MCRXR      = 31, 512
    MFCR       = 31, 19
    MFFS       = 63, 583
    MFMSR      = 31, 83
    MFSPR      = 31, 339
    MFSR       = 31, 595
    MFSRIN     = 31, 659
    MFTB       = 31, 371
    MTCRF      = 31, 144
    MTFSB0     = 63, 70
    MTFSB1     = 63, 38
    MTFSF      = 63, 711
    MTFSFI     = 63, 134
    MTMSR      = 31, 146
    MTSPR      = 31, 467
    MTSR       = 31, 210
    MTSRIN     = 31, 242
    MULHW      = 31, 75
    MULHWU     = 31, 11
    MULLI      = 7
    MULLW      = 31, 235
    MULLWO     = 31, 747
    NAND       = 31, 476
    NEG        = 31, 104
    NEGO       = 31, 616
    NOR        = 31, 124
    OR         = 31, 444
    ORC        = 31, 412
    ORI        = 24
    ORIS       = 25
    PSQ_L      = 56
    PSQ_LU     = 57
    PSQ_LUX    = 4, 38
    PSQ_LX     = 4, 6
    PSQ_ST     = 60
    PSQ_STU    = 61
    PSQ_STUX   = 4, 39
    PSQ_STX    = 4, 7
    PS_ABS     = 4, 264
    PS_ADD     = 4, 21
    PS_CMPO0   = 4, 32
    PS_CMPO1   = 4, 96
    PS_CMPU0   = 4, 0
    PS_CMPU1   = 4, 64
    PS_DIV     = 4, 18
    PS_MADD    = 4, 29
    PS_MADDS0  = 4, 14
    PS_MADDS1  = 4, 15
    PS_MERGE00 = 4, 528
    PS_MERGE01 = 4, 560
    PS_MERGE10 = 4, 592
    PS_MERGE11 = 4, 624
    PS_MR      = 4, 72
    PS_MSUB    = 4, 28
    PS_MUL     = 4, 25
    PS_MULS0   = 4, 12
    PS_MULS1   = 4, 13
    PS_NABS    = 4, 136
    PS_NEG     = 4, 40
    PS_NMADD   = 4, 31
    PS_NMSUB   = 4, 30
    PS_RES     = 4, 24
    PS_RSQRTE  = 4, 26
    PS_SEL     = 4, 23
    PS_SUB     = 4, 20
    PS_SUM0    = 4, 10
    PS_SUM1    = 4, 11
    RFI        = 19, 50
    RLWIMI     = 20
    RLWINM     = 21
    RLWNM      = 23
    SC         = 17
    SLW        = 31, 24
    SRAW       = 31, 792
    SRAWI      = 31, 824
    SRW        = 31, 536
    STB        = 38
    STBU       = 39
    STBUX      = 31, 247
    STBX       = 31, 215
    STFD       = 54
    STFDU      = 55
    STFDUX     = 31, 759
    STFDX      = 31, 727
    STFIWX     = 31, 983
    STFS       = 52
    STFSU      = 53
    STFSUX     = 31, 695
    STFSX      = 31, 663
    STH        = 44
    STHBRX     = 31, 918
    STHU       = 45
    STHUX      = 31, 439
    STHX       = 31, 407
    STMW       = 47
    STSWI      = 31, 725
    STSWX      = 31, 661
    STW        = 36
    STWBRX     = 31, 662
    STWCX_     = 31, 150
    STWU       = 37
    STWUX      = 31, 183
    STWX       = 31, 151
    SUBF       = 31, 40
    SUBFO      = 31, 552
    SUBFC      = 31, 8
    SUBFCO     = 31, 520
    SUBFE      = 31, 136
    SUBFEO     = 31, 648
    SUBFIC     = 8
    SUBFME     = 31, 232
    SUBFMEO    = 31, 744
    SUBFZE     = 31, 200
    SUBFZEO    = 31, 712
    SYNC       = 31, 598
    TLBIE      = 31, 306
    TLBSYNC    = 31, 566
    TW         = 31, 4
    TWI        = 3
    XOR        = 31, 316
    XORI       = 26
    XORIS      = 27
    # fmt: on

    def __str__(self) -> str:
        return self.name.lower().replace("_", ".")

    @classmethod
    def is_load(cls, op: PpcOp) -> bool:
        return op in _load_ops

    @classmethod
    def is_store(cls, op: PpcOp) -> bool:
        return op in _store_ops


_load_ops = {
    PpcOp.LBZ: u8,
    PpcOp.LBZU: u8,
    PpcOp.LHA: s16,
    PpcOp.LHAU: s16,
    PpcOp.LHZ: u16,
    PpcOp.LHZU: u16,
    PpcOp.LWZ: u32,
    PpcOp.LWZU: u32,
}

_store_ops = {
    PpcOp.STB: u8,
    PpcOp.STBU: u8,
    PpcOp.STH: u16,
    PpcOp.STHU: u16,
    PpcOp.STW: u32,
    PpcOp.STWU: u32,
}


def get_load_store_type(op: PpcOp) -> ctype:
    if op in _load_ops:
        return _load_ops[op]
    if op in _store_ops:
        return _store_ops[op]
    raise TypeError(f"{op}")
