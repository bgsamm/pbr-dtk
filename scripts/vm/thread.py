from dataclasses import dataclass
from enum import IntEnum
from typing import Callable
from rvl import Dol
from rvl.types import *
from .common import *
from .instr import VmInstr
from .mmap import VmMemMap
from .reg import VmReg
from .symval import SymbolicValue
import logging

type VmCallback = Callable[["VmThread", "VmOp"], bool]


def _dummy_callback(thread: "VmThread", op: "VmOp") -> bool:
    return VmThread.CONTINUE


class VmOpType(IntEnum):
    UNKNOWN = 0
    READ_REG = 1
    WRITE_REG = 2
    READ_MEM = 3
    WRITE_MEM = 4
    CALL = 5


@dataclass(frozen=True)
class VmOp:
    type: VmOpType
    reg: VmReg = VmReg.NULL
    addr: SymbolicValue = SymbolicValue.Unknown
    value: SymbolicValue = SymbolicValue.Unknown
    dtype: ctype | None = None


class VmThread:
    type InstructionCallback = Callable[
        [VmThread, VmInstr], None | tuple[VmThread, ...]
    ]

    CONTINUE = False
    HALT = True

    NULL_TAG = 0

    _op_lookup: dict[int, InstructionCallback]
    _subop_lookup: dict[int, InstructionCallback]

    _mmap: VmMemMap
    _callback: VmCallback
    _global_seen_addrs: set[int]
    _local_seen_addrs: set[int]

    # TODO Do I really want to be passing a DOL in?
    def __init__(
        self,
        dol: Dol,
        init_state: dict[VmReg, SymOrInt] | None = None,
        reg_tags: dict[VmReg, int] | None = None,
        step_into_calls: bool | set[int] = False,
    ):
        self._dol = dol
        self._regs = [SymbolicValue.Unknown for _ in range(max(VmReg) + 1)]
        self._reg_tags = [self.NULL_TAG] * len(self._regs)
        self._mmap = VmMemMap()
        self._callback = _dummy_callback
        self._step_into_calls = step_into_calls
        self._global_seen_addrs = set()
        self._local_seen_addrs = set()
        self._terminate = False

        if init_state:
            for reg, value in init_state.items():
                if isinstance(value, int):
                    value = SymbolicValue(value)
                self._regs[reg] = value

        if reg_tags:
            for reg, tag in reg_tags.items():
                self._reg_tags[reg] = tag

    @property
    def _pc(self) -> SymbolicValue:
        return self._regs[VmReg.PC]

    @property
    def _lr(self) -> SymbolicValue:
        return self._regs[VmReg.LR]

    @property
    def _ctr(self) -> SymbolicValue:
        return self._regs[VmReg.CTR]

    @property
    def _cr(self) -> SymbolicValue:
        return self._regs[VmReg.CR]

    def _log_invalid_instr(self, instr: int, msg: str):
        logging.warning(f"Invalid instruction: 0x{instr:08x} ({msg})")

    def _log_unhandled_op(self, op: int):
        logging.error(f"Unhandled opcode: 0x{op:02x} (PC=0x{self._pc.value:08x})")

    def _log_unhandled_subop(self, op: int, subop: int):
        logging.error(
            f"Unhandled 0x{op:02x} sub-op: 0x{subop:02x} (PC=0x{self._pc.value:08x})"
        )

    def _do_callback(self, op: VmOp):
        self._terminate |= self._callback(self, op)

    def _op_read_pc(self):
        return self._op_read_reg(VmReg.PC)

    def _op_inc_pc(self):
        # Intentionally omitting pc read op
        self._op_write_reg(VmReg.PC, self._pc + 4)

    def _op_read_xer_so_bit(self) -> SymbolicValue:
        return (self._op_read_reg(VmReg.XER) >> 31) & 0x1

    def _op_set_xer(
        self, so: bool | None = None, ov: bool | None = None, ca: bool | None = None
    ):
        xer = self._op_read_reg(VmReg.XER)
        _so = ((xer >> 31) & 0x1) if so is None else int(so)
        _ov = ((xer >> 30) & 0x1) if ov is None else int(ov)
        _ca = ((xer >> 29) & 0x1) if ca is None else int(ca)
        self._op_write_reg(
            VmReg.XER, (xer & (0x1FFF_FFFF)) | (_so << 31) | (_ov << 30) | (_ca << 29)
        )

    def _op_update_cr(self, value: SymbolicValue, crf: int = 0):
        assert 0 <= crf <= 7

        if value < 0:
            c = 0b100
        elif value > 0:
            c = 0b010
        elif value == 0:
            c = 0b001
        else:
            c = SymbolicValue.Unknown

        so = self._op_read_xer_so_bit()
        cr = self._op_read_reg(VmReg.CR)
        shift = (7 - crf) * 4
        result = (cr & ~(0b1111 << shift)) | (c << (shift + 1)) | (so << shift)
        self._op_write_reg(VmReg.CR, result)

    def _op_read_reg(self, reg: VmReg) -> SymbolicValue:
        value = self._regs[reg]
        self._do_callback(VmOp(VmOpType.READ_REG, reg=reg, value=value))
        return value

    def _op_write_reg(self, reg: VmReg, value: SymbolicValue, tag: int = NULL_TAG):
        # TODO Revisit this (floating-point registers?)
        # Enforce 32-bit register width
        value &= 0xFFFF_FFFF
        self._do_callback(VmOp(VmOpType.WRITE_REG, reg=reg, value=value))
        self._regs[reg] = value & 0xFFFF_FFFF
        self._reg_tags[reg] = tag

    def _op_read_mem(self, type: ctype, addr: SymbolicValue) -> SymbolicValue:
        value = (
            self._mmap.read(type, addr.value)
            if addr.is_known
            else SymbolicValue.Unknown
        )
        self._do_callback(VmOp(VmOpType.READ_MEM, addr=addr, value=value, dtype=type))
        return value

    def _op_write_mem(self, type: ctype, addr: SymbolicValue, sym: SymbolicValue):
        # Enforce type widths
        sym &= (1 << (sizeof(type) * 8)) - 1
        self._do_callback(VmOp(VmOpType.WRITE_MEM, addr=addr, value=sym, dtype=type))
        if addr.is_known:
            self._mmap.write(type, addr.value, sym)

    def _op_call(self, target_addr: SymbolicValue, step_over: bool = False):
        self._do_callback(VmOp(VmOpType.CALL, addr=target_addr))
        self._op_write_reg(VmReg.LR, self._op_read_pc() + 4)
        if step_over:
            self._set_post_call_state()
            self._op_inc_pc()
        else:
            self._op_write_reg(VmReg.PC, target_addr)

    def _should_step_over_call(self, addr: SymbolicValue) -> bool:
        if isinstance(self._step_into_calls, set):
            return addr not in self._step_into_calls
        return not self._step_into_calls

    def _set_post_call_state(self):
        for reg in range(len(self._regs)):
            # Special registers that (should) remain unaffected
            if reg in {VmReg.PC, VmReg.LR, VmReg.GPR1, VmReg.GPR2, VmReg.GPR13}:
                continue
            # Callee-saved registers
            if VmReg.GPR14 <= reg <= VmReg.GPR31 or VmReg.FPR14 <= reg <= VmReg.FPR31:
                continue
            self._regs[reg] = SymbolicValue.Unknown
            self._reg_tags[reg] = VmThread.NULL_TAG
        # TODO Avoid resetting stack
        self._mmap.reset()

    def _exec_add(self, instr: VmInstr):
        # < Generated by Gemini
        def check_overflow(a, b, res):
            ov = (a ^ res) & (b ^ res) & (1 << 31)
            return bool(ov)

        # >

        D = instr.gpr_field(6, 10)
        A = instr.gpr_field(11, 15)
        B = instr.gpr_field(16, 20)
        OE = instr.bit(21)
        Rc = instr.bit(31)

        rA = self._op_read_reg(A) & 0xFFFF_FFFF
        rB = self._op_read_reg(B) & 0xFFFF_FFFF
        sum = (rA + rB) & 0xFFFF_FFFF

        if OE == 1:
            overflow = check_overflow(rA, rB, sum)
            # SO is sticky - does not get cleared automatically
            self._op_set_xer(so=(overflow or None), ov=overflow)

        sum = sign_ext(sum, 32)

        if Rc == 1:
            self._op_update_cr(sum)

        self._op_write_reg(D, sum)

        self._op_inc_pc()

        return (self,)

    def _exec_addi(self, instr: VmInstr):
        op = instr.opcode

        D = instr.field(6, 10)
        A = instr.field(11, 15)
        SIMM = instr.field(16, 31)

        if op == 0xE:  # addi
            value = sign_ext(SIMM, 16)
        elif op == 0xF:  # addis
            value = SIMM << 16
        else:
            self._log_unhandled_op(op)
            return None

        if A == 0:
            self._op_write_reg(VmReg.GPR(D), SymbolicValue(value))
        else:
            self._op_write_reg(VmReg.GPR(D), self._op_read_reg(VmReg.GPR(A)) + value)

        self._op_inc_pc()

        return (self,)

    def _exec_b(self, instr: VmInstr):
        LI = instr.field(6, 29)
        AA = instr.bit(30)
        LK = instr.bit(31)

        offset = sign_ext(LI << 2, 26)

        if AA == 0:
            target_addr = self._op_read_pc() + offset
        else:
            target_addr = SymbolicValue(offset)

        if LK == 1:
            self._op_call(
                target_addr, step_over=self._should_step_over_call(target_addr)
            )
        else:
            self._op_write_reg(VmReg.PC, target_addr)

        return (self,)

    def _exec_bc(self, instr: VmInstr):
        op = instr.opcode
        subop = instr.subop

        # Common
        BO = instr.field(6, 10)
        BI = instr.field(11, 15)
        # For bc
        BD = instr.field(16, 29)
        AA = instr.bit(30)
        # Common
        LK = instr.bit(31)

        if (BO & 0b00100) == 0:
            if op == 0x13 and subop == 528:
                self._log_invalid_instr(instr, "decrement-and-test in bcctr")
            self._op_write_reg(VmReg.CTR, self._op_read_reg(VmReg.CTR) - 1)

            ctr = self._op_read_reg(VmReg.CTR)
            if ctr.is_known:
                ctr_ok = (ctr == 0) == ((BO & 0b00010) != 0)
            else:
                ctr_ok = None
        else:
            ctr_ok = True

        if (BO & 0b10000) == 0:
            cr = self._op_read_reg(VmReg.CR)
            if cr.is_known:
                cond_ok = (((cr >> (31 - BI)) & 0x1) != 0) == ((BO & 0b01000) != 0)
            else:
                cond_ok = None
        else:
            cond_ok = True

        offset = sign_ext(BD << 2, 16)

        if op == 0x10:  # bc
            if AA == 0:
                target_addr = self._op_read_pc() + offset
            else:
                target_addr = SymbolicValue(offset)
        elif op == 0x13:  # bcctr/bclr
            if subop == 528:  # bcctr
                reg = VmReg.CTR
            elif subop == 16:  # bclr
                reg = VmReg.LR
            else:
                self._log_unhandled_subop(op, subop)
                return None

            target_addr = self._op_read_reg(reg) & 0xFFFF_FFFC
        else:
            self._log_unhandled_op(op)
            return None

        branch = self.clone()
        if LK == 1:
            branch._op_call(
                target_addr, step_over=self._should_step_over_call(target_addr)
            )
        else:
            branch._op_write_reg(VmReg.PC, target_addr)

        self._op_inc_pc()

        # Branch result unknown
        if ctr_ok is None or cond_ok is None:
            return (self, branch)
        # Branch taken
        if ctr_ok and cond_ok:
            return (branch,)
        # Branch not taken
        return (self,)

    def _exec_compare(self, instr: VmInstr):
        op = instr.opcode
        subop = instr.subop

        D = instr.field(6, 8)
        L = instr.bit(10)
        A = instr.gpr_field(11, 15)
        # cmp/cmpl
        B = instr.gpr_field(16, 20)
        # cmpi
        SIMM = instr.field(16, 31)

        if L == 1:
            self._log_invalid_instr(instr, "L==1 in compare instruction")

        rA = self._op_read_reg(A)

        if op == 11:  # cmpi
            value = sign_ext(SIMM, 16)
            rA = sign_ext(rA, 32)
        elif op == 31:
            rB = self._op_read_reg(B)
            if subop == 0:  # cmpw
                value = sign_ext(rB, 32)
                rA = sign_ext(rA, 32)
            elif subop == 32:  # cmpl
                value = rB & 0xFFFF_FFFF
                rA &= 0xFFFF_FFFF
            else:
                self._log_unhandled_subop(op, subop)
                return None

        self._op_update_cr(rA - value, D)

        self._op_inc_pc()

        return (self,)

    def _exec_loadstore(self, instr: VmInstr):
        def with_update(op: int):
            return op % 2 == 1

        op = instr.opcode

        S = D = instr.gpr_field(6, 10)
        A = instr.field(11, 15)
        d = instr.field(16, 31)

        offset = sign_ext(d, 16)

        if A == 0:
            if with_update(op):
                self._log_invalid_instr(instr, "rA==0 in load/store-with-update")
            addr = SymbolicValue(offset)
        else:
            if A == D and instr.is_load() and with_update(op):
                self._log_invalid_instr(instr, "rA==rD in load-with-update")
            addr = self._op_read_reg(VmReg.GPR(A)) + offset

        if instr.is_store():
            dtype = VmInstr.loadstore_type(instr)
            value = self._op_read_reg(S)
            self._op_write_mem(dtype, addr, value)
        elif instr.is_load():
            dtype = VmInstr.loadstore_type(instr)
            value = self._op_read_mem(dtype, addr)
            self._op_write_reg(D, value)
        else:
            self._log_unhandled_op(op)
            return None

        if with_update(op):
            self._op_write_reg(VmReg.GPR(A), addr)

        self._op_inc_pc()

        return (self,)

    def _exec_mfspr(self, instr: VmInstr):
        op = instr.opcode
        subop = instr.subop

        D = S = instr.gpr_field(6, 10)
        spr1 = instr.field(11, 15)
        spr2 = instr.field(16, 20)
        SPR = (spr2 << 0x5) + spr1

        spr_map = {1: VmReg.XER, 8: VmReg.LR, 9: VmReg.CTR}

        if not (spr := spr_map.get(SPR)):
            self._log_invalid_instr(op, "Invalid SPR in mfspr/mtspr instruction")
            return None

        if subop == 339:
            self._op_write_reg(D, self._op_read_reg(spr))
        elif subop == 467:
            self._op_write_reg(spr, self._op_read_reg(S))
        else:
            self._log_unhandled_subop(op, subop)
            return None

        self._op_inc_pc()

        return (self,)

    def _exec_neg(self, instr: VmInstr):
        D = instr.gpr_field(6, 10)
        A = instr.gpr_field(11, 15)
        OE = instr.bit(21)
        Rc = instr.bit(31)

        rA = self._op_read_reg(A) & 0xFFFF_FFFF

        if OE == 1:
            overflow = rA == 0x8000_0000
            self._op_set_xer(so=(overflow or None), ov=overflow)

        result = sign_ext((~rA + 1) & 0xFFFF_FFFF, 32)

        if Rc == 1:
            self._op_update_cr(result)

        self._op_write_reg(D, result)

        self._op_inc_pc()

        return (self,)

    def _exec_or(self, instr: VmInstr):
        S = instr.gpr_field(6, 10)
        A = instr.gpr_field(11, 15)
        B = instr.gpr_field(16, 20)
        Rc = instr.bit(31)

        result = self._op_read_reg(S) | self._op_read_reg(B)

        # Taint propagation on mr (rS == rB)
        tag = self._reg_tags[S] if S == B else self.NULL_TAG
        self._op_write_reg(A, result, tag)

        if Rc == 1:
            self._op_update_cr(result)

        self._op_inc_pc()

        return (self,)

    def _exec_ori(self, instr: VmInstr):
        op = instr.opcode

        S = instr.gpr_field(6, 10)
        A = instr.gpr_field(11, 15)
        UIMM = instr.field(16, 31)

        rS = self._op_read_reg(S)

        if op == 0x18:  # ori
            value = rS | UIMM
        elif op == 0x19:  # oris
            value = rS | (UIMM << 16)
        else:
            self._log_unhandled_op(op)
            return None

        self._op_write_reg(A, value)

        self._op_inc_pc()

        return (self,)

    def _exec_rlwinm(self, instr: VmInstr):
        def rotl(x, y):
            return ((x << y) | (x >> (32 - y))) & 0xFFFF_FFFF

        def mask(x, y):
            a, b = (x, y) if x <= y else (y + 1, x - 1)
            bitmask = ((1 << (b - a + 1)) - 1) << (31 - b)
            if x > y:
                bitmask = ~bitmask
            return bitmask & 0xFFFF_FFFF

        S = instr.gpr_field(6, 10)
        A = instr.gpr_field(11, 15)
        SH = instr.field(16, 20)
        MB = instr.field(21, 25)
        ME = instr.field(26, 30)
        Rc = instr.bit(31)

        rS = self._op_read_reg(S)
        result = rotl(rS, SH) & mask(MB, ME)

        self._op_write_reg(A, result)

        if Rc == 1:
            self._op_update_cr(result)

        self._op_inc_pc()

        return (self,)

    def _dispatch_op_1f(self, instr: VmInstr):
        op = instr.opcode
        subop = instr.subop

        exec_func = self._subop_lookup.get(subop)
        if exec_func is None:
            self._log_unhandled_subop(op, subop)
            return None

        return exec_func(self, instr)

    _op_lookup = {
        11: _exec_compare,
        14: _exec_addi,
        15: _exec_addi,
        16: _exec_bc,
        18: _exec_b,
        19: _exec_bc,
        21: _exec_rlwinm,
        24: _exec_ori,
        25: _exec_ori,
        31: _dispatch_op_1f,
        32: _exec_loadstore,
        33: _exec_loadstore,
        34: _exec_loadstore,
        35: _exec_loadstore,
        36: _exec_loadstore,
        37: _exec_loadstore,
        38: _exec_loadstore,
        39: _exec_loadstore,
        40: _exec_loadstore,
        41: _exec_loadstore,
        42: _exec_loadstore,
        43: _exec_loadstore,
        44: _exec_loadstore,
        45: _exec_loadstore,
    }

    _subop_lookup = {
        0: _exec_compare,
        32: _exec_compare,
        104: _exec_neg,
        266: _exec_add,
        339: _exec_mfspr,
        444: _exec_or,
        467: _exec_mfspr,
    }

    def should_terminate(self):
        return self._pc.is_unknown or self._terminate

    def is_at_seen_address(self, local_only=False):
        return self._pc.is_known and (
            self._pc.value in self._local_seen_addrs
            or (not local_only and self._pc.value in self._global_seen_addrs)
        )

    def set_callback(self, callback: VmCallback | None):
        self._callback = callback or _dummy_callback

    def tag_register(self, reg: VmReg, tag: int):
        self._reg_tags[reg] = tag

    def get_register_tag(self, reg: VmReg) -> int:
        return self._reg_tags[reg]

    def get_pc(self) -> SymbolicValue:
        return self.read_reg(VmReg.PC)

    def set_pc(self, value: SymOrInt):
        self.write_reg(VmReg.PC, value)

    def read_reg(self, reg: VmReg) -> SymbolicValue:
        return self._regs[reg]

    def write_reg(self, reg: VmReg, value: SymOrInt):
        if isinstance(value, int):
            value = SymbolicValue(value)
        self._regs[reg] = value

    def read_mem(self, dtype: ctype, addr: int) -> SymbolicValue:
        return self._mmap.read(dtype, addr)

    def write_mem(self, dtype: ctype, addr: int, value: SymOrInt):
        if isinstance(value, int):
            value = SymbolicValue(value)
        self._mmap.write(dtype, addr, value)

    def get_current_instruction(self) -> VmInstr:
        assert self._pc.is_known
        return VmInstr(self._dol.read(u32, self._pc.value))

    def reset_state(self):
        self._terminate = False

        for i in range(len(self._regs)):
            self._regs[i] = SymbolicValue.Unknown

        self._mmap.reset()

    def step(self):
        assert self._pc.is_known
        starting_pc = self._pc.value

        instr = self.get_current_instruction()
        op = instr.opcode

        exec_func = self._op_lookup.get(op)
        if exec_func is None:
            self._log_unhandled_op(op)
            return None

        branches = exec_func(self, instr)

        self._global_seen_addrs.add(starting_pc)
        self._local_seen_addrs.add(starting_pc)

        return branches

    def clone(self) -> VmThread:
        new_thread = VmThread(self._dol, step_into_calls=self._step_into_calls)
        new_thread.set_callback(self._callback)

        new_thread._regs = self._regs[:]
        new_thread._mmap = self._mmap.clone()

        new_thread._reg_tags = self._reg_tags[:]
        new_thread._global_seen_addrs = self._global_seen_addrs
        new_thread._local_seen_addrs = self._local_seen_addrs.copy()

        return new_thread

    def print_regs(self, include_fprs: bool = True):
        def print_reg(name: str, sym: SymbolicValue, width: int):
            # TODO Simplify once SymbolicValue.__format__ is working
            val_str = format(sym, f"0{width}x") if sym.is_known else ("?" * width)
            print(f"{name.rjust(3)}: {val_str}", end=" ")

        def print_spr(i: int, reg: SymbolicValue):
            print_reg(VmReg(i).name.lower(), reg, 8)

        def print_gpr(i: int, reg: SymbolicValue):
            print_reg(f"r{i}", reg, 8)

        def print_fpr(i: int, reg: SymbolicValue):
            print_reg(f"f{i}", reg, 16)

        for reg, value in enumerate(self._regs):
            reg = VmReg(reg)

            if reg == VmReg.NULL:
                continue

            if reg.is_gpr():
                i = reg - VmReg.GPR0
                if i % 8 == 0:
                    print()
                print_gpr(i, value)
            elif reg.is_fpr():
                if include_fprs:
                    i = reg - VmReg.FPR0
                    if i % 4 == 0:
                        print()
                    print_fpr(i, value)
            else:
                print_spr(reg, value)

        print()

    def print_mem(self, addr: int, size: int, row_len: int = 16):
        addr = (addr // row_len) * row_len
        size = ((size + row_len - 1) // row_len) * row_len

        print(" " * 9 + " ".join(f"{x:02X}" for x in range(row_len)))

        data = self._mmap.dump(addr, size)
        for i, sym in enumerate(data):
            if i % row_len == 0:
                print(f"{addr + i:08X}", end=" ")

            # TODO Simplify once SymbolicValue.__format__ is working
            print(f"{sym:02X}" if sym.is_known else "??", end=" ")

            if i % row_len == row_len - 1:
                print()
