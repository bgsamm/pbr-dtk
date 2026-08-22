from functools import cached_property
from mathutils import sign_ext
from typealiases import *
from .op import PpcOp
from .reg import PpcReg


class PpcInstr(int):
    BLR = 0x4E80_0020

    @cached_property
    def op(self) -> PpcOp:
        return self._get_op()

    @property
    def opcode(self) -> int:
        return (self >> 26) & 0x3F

    def _get_op(self) -> PpcOp:
        opcode = self.opcode

        # Integer instructions
        if opcode == 31:
            subop = self.field(21, 30)
            return PpcOp((opcode, subop))

        # Condition instructions
        if opcode == 19:
            subop = self.field(21, 30)
            return PpcOp((opcode, subop))

        # Floating-point single instructions
        if opcode == 59:
            subop = self.field(26, 30)
            return PpcOp((opcode, subop))

        # Floating-point double instructions
        if opcode == 63:
            subop = self.field(21, 30)
            if (opcode, subop) in PpcOp:
                return PpcOp((opcode, subop))
            subop = self.field(26, 30)
            return PpcOp((opcode, subop))

        # Paired single instructions
        if opcode == 4:
            subop = self.field(21, 30)
            if (opcode, subop) in PpcOp:
                return PpcOp((opcode, subop))
            subop = self.field(25, 30)
            if (opcode, subop) in PpcOp:
                return PpcOp((opcode, subop))
            subop = self.field(26, 30)
            return PpcOp((opcode, subop))

        # Immediate instructions
        return PpcOp(opcode)

    def bit(self, n: int) -> int:
        return (self >> (31 - n)) & 0x1

    def field(self, a: int, b: int) -> int:
        mask = (1 << (b - a + 1)) - 1
        return (self >> (31 - b)) & mask

    def gpr_field(self, a: int, b: int) -> PpcReg:
        return PpcReg.GPR(self.field(a, b))

    def uimm_field(self, a: int, b: int) -> int:
        return self.field(a, b)

    def simm_field(self, a: int, b: int) -> int:
        return sign_ext(self.field(a, b), (b - a + 1))

    def is_move(self, from_: PpcReg | None = None, to: PpcReg | None = None) -> bool:
        if not self.op == PpcOp.OR:
            return False
        S = self.gpr_field(6, 10)
        A = self.gpr_field(11, 15)
        B = self.gpr_field(16, 20)
        return (S == B) and (from_ in {None, S}) and (to in {None, A})

    def is_load(self) -> bool:
        return PpcOp.is_load(self.op)

    def is_store(self) -> bool:
        return PpcOp.is_store(self.op)

    def is_blr(self) -> bool:
        return self == self.BLR
