from enum import IntEnum
import enum


class VmReg(IntEnum):
    NULL = 0
    # SPRs
    PC = enum.auto()
    LR = enum.auto()
    CTR = enum.auto()
    CR = enum.auto()
    XER = enum.auto()
    # GPRs
    GPR0 = enum.auto()
    GPR1 = enum.auto()
    GPR2 = enum.auto()
    GPR3 = enum.auto()
    GPR4 = enum.auto()
    GPR5 = enum.auto()
    GPR6 = enum.auto()
    GPR7 = enum.auto()
    GPR8 = enum.auto()
    GPR9 = enum.auto()
    GPR10 = enum.auto()
    GPR11 = enum.auto()
    GPR12 = enum.auto()
    GPR13 = enum.auto()
    GPR14 = enum.auto()
    GPR15 = enum.auto()
    GPR16 = enum.auto()
    GPR17 = enum.auto()
    GPR18 = enum.auto()
    GPR19 = enum.auto()
    GPR20 = enum.auto()
    GPR21 = enum.auto()
    GPR22 = enum.auto()
    GPR23 = enum.auto()
    GPR24 = enum.auto()
    GPR25 = enum.auto()
    GPR26 = enum.auto()
    GPR27 = enum.auto()
    GPR28 = enum.auto()
    GPR29 = enum.auto()
    GPR30 = enum.auto()
    GPR31 = enum.auto()
    # FPRS
    FPR0 = enum.auto()
    FPR1 = enum.auto()
    FPR2 = enum.auto()
    FPR3 = enum.auto()
    FPR4 = enum.auto()
    FPR5 = enum.auto()
    FPR6 = enum.auto()
    FPR7 = enum.auto()
    FPR8 = enum.auto()
    FPR9 = enum.auto()
    FPR10 = enum.auto()
    FPR11 = enum.auto()
    FPR12 = enum.auto()
    FPR13 = enum.auto()
    FPR14 = enum.auto()
    FPR15 = enum.auto()
    FPR16 = enum.auto()
    FPR17 = enum.auto()
    FPR18 = enum.auto()
    FPR19 = enum.auto()
    FPR20 = enum.auto()
    FPR21 = enum.auto()
    FPR22 = enum.auto()
    FPR23 = enum.auto()
    FPR24 = enum.auto()
    FPR25 = enum.auto()
    FPR26 = enum.auto()
    FPR27 = enum.auto()
    FPR28 = enum.auto()
    FPR29 = enum.auto()
    FPR30 = enum.auto()
    FPR31 = enum.auto()

    def is_gpr(self) -> bool:
        return VmReg.GPR0 <= self <= VmReg.GPR31

    def is_fpr(self) -> bool:
        return VmReg.FPR0 <= self <= VmReg.FPR31

    @classmethod
    def GPR(cls, i: int) -> VmReg:
        return VmReg(VmReg.GPR0 + i)

    @classmethod
    def FPR(cls, i: int) -> VmReg:
        return VmReg(VmReg.FPR0 + i)
