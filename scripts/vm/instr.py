from rvl.types import *
from .common import sign_ext
from .reg import VmReg

class VmInstr(int):
    _ls_type_map = {
        # lwz/lwzu
        0x20: u32, 0x21: u32,
        # lbz/lbzu
        0x22: u8,  0x23: u8,
        # stw/stwu
        0x24: u32, 0x25: u32,
        # stb/stbu
        0x26: u8,  0x27: u8,
        # lhz/lhzu
        0x28: u16, 0x29: u16,
        # lha/lhau
        0x2a: s16, 0x2b: s16,
        # sth/sthu
        0x2c: u16, 0x2d: u16
    }

    @property
    def opcode(self) -> int:
        return (self >> 26) & 0x3f

    @property
    def subop(self) -> int:
        return (self >> 1) & 0x3ff

    def bit(self, n: int) -> int:
        return (self >> (31 - n)) & 0x1

    def field(self, a: int, b: int) -> int:
        mask = (1 << (b - a + 1)) - 1
        return (self >> (31 - b)) & mask

    # TODO Use in exec functions
    def gpr_field(self, a: int, b: int) -> VmReg:
        return VmReg.GPR(self.field(a, b))

    # TODO Use in exec functions
    def simm_field(self, a: int, b: int) -> int:
        return sign_ext(self.field(a, b), (b - a + 1))

    def is_or(self) -> bool:
        return self.opcode == 31 and self.subop == 444

    def is_move(self, from_: VmReg = VmReg.NULL, to: VmReg = VmReg.NULL) -> bool:
        if not self.is_or():
            return False
        S = self.field(6, 10)
        A = self.field(11, 15)
        B = self.field(16, 20)
        return S == B and from_ in (VmReg.NULL, S) and to in (VmReg.NULL, A)

    def is_load(self) -> bool:
        return 32 <= self.opcode <= 35 or 40 <= self.opcode <= 43

    def is_store(self) -> bool:
        return 36 <= self.opcode <= 39 or 44 <= self.opcode <= 45

    def is_blr(self) -> bool:
        return self == 0x4E80_0020

    @classmethod
    def loadstore_type(cls, instr: VmInstr) -> ctype:
        if not (instr.is_load() or instr.is_store()):
            raise TypeError('Not a load/store instruction')
        return cls._ls_type_map[instr.opcode]
