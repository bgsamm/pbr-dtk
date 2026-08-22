from typing import Callable
from mathutils import rotate_l, create_mask, sign_ext
from symval import SymbolicValue, SymOrInt, SymOrNone
from typealiases import *
from .instr import PpcInstr
from .op import PpcOp
from .reg import PpcReg
from .state import PpcState
import logging

type _ExecFunction[T: PpcState] = Callable[[PpcInstr, T], tuple[T, ...]]

_op_lookup: dict[PpcOp, _ExecFunction]

_SPR_MAP = {1: PpcReg.XER, 8: PpcReg.LR, 9: PpcReg.CTR}


class ExecutionError(Exception):
    pass


def _log_invalid_instr(instr: PpcInstr, pc: SymOrInt, msg: str):
    logging.warning(f"Invalid instruction (0x{instr:08X}): {msg} (pc=0x{pc:08X})")


# TODO Make _read_xer w/ bit arg?
def _read_xer_so_bit(state: PpcState) -> SymbolicValue:
    return (state.read_reg(PpcReg.XER) >> 31) & 0x1


def _set_xer(state: PpcState, ov: SymOrNone = None, ca: SymOrNone = None) -> None:
    # TODO Verify whether ever need to specify so manually
    so = ov or None

    # TODO Something better?
    # Force ov/ca to 0 or 1 (if known)
    if ov and ov.is_known:
        ov = SymbolicValue(bool(ov.value))
    if ca and ca.is_known:
        ca = SymbolicValue(bool(ca.value))

    xer = state.read_reg(PpcReg.XER)
    _so = ((xer >> 31) & 0x1) if so is None else so
    _ov = ((xer >> 30) & 0x1) if ov is None else ov
    _ca = ((xer >> 29) & 0x1) if ca is None else ca

    xer = (xer & (0x1FFF_FFFF)) | (_so << 31) | (_ov << 30) | (_ca << 29)
    state.write_reg(PpcReg.XER, xer)


def _update_cr(state: PpcState, value: SymbolicValue, crf: int = 0) -> SymbolicValue:
    assert 0 <= crf <= 7

    value = sign_ext(value, 32)

    if value < 0:
        c = 0b100
    elif value > 0:
        c = 0b010
    elif value == 0:
        c = 0b001
    else:
        c = SymbolicValue.Unknown

    so = _read_xer_so_bit(state)
    cr = state.read_reg(PpcReg.CR)
    shift = (7 - crf) * 4

    result = (cr & ~(0b1111 << shift)) | (c << (shift + 1)) | (so << shift)
    return state.write_reg(PpcReg.CR, result)


def _decrement_ctr(state: PpcState) -> SymbolicValue:
    ctr = state.read_reg(PpcReg.CTR) - 1
    state.write_reg(PpcReg.CTR, ctr)
    return ctr


def _check_cr(state: PpcState, BO: int, BI: int) -> bool | None:
    cr_ignore = (BO >> 4) & 0x1
    if cr_ignore:
        return True

    cr = state.read_reg(PpcReg.CR)
    if cr.is_unknown:
        return None

    cr_bit = (cr >> (31 - BI)) & 0x1
    cr_bit_want = (BO >> 3) & 0x1
    return cr_bit == cr_bit_want


def _check_ctr(state: PpcState, BO: int) -> bool | None:
    ctr_ignore = (BO >> 2) & 0x1
    if ctr_ignore:
        return True

    ctr = _decrement_ctr(state)
    if ctr.is_unknown:
        return None

    ctr_want_zero = (BO >> 1) & 0x1
    return (ctr == 0) == ctr_want_zero


def _exec_load[T: PpcState](
    instr: PpcInstr, state: T, type: ctype, update: bool = False
) -> tuple[T, ...]:
    D = instr.field(6, 10)
    A = instr.field(11, 15)
    d = instr.field(16, 31)

    offset = sign_ext(d, 16)
    if A == 0:
        addr = SymbolicValue(offset)
    else:
        addr = state.read_reg(PpcReg.GPR(A)) + offset

    value = state.read_mem(addr, type)
    state.write_reg(PpcReg.GPR(D), value)

    if update:
        if A == 0:
            _log_invalid_instr(instr, state.pc, "A==0 in load-with-update")
        elif A == D:
            _log_invalid_instr(instr, state.pc, "A==D in load-with-update")
        state.write_reg(PpcReg.GPR(A), addr)

    return (state,)


def _exec_store[T: PpcState](
    instr: PpcInstr, state: T, type: ctype, update: bool = False
) -> tuple[T, ...]:
    S = instr.field(6, 10)
    A = instr.field(11, 15)
    d = instr.field(16, 31)

    offset = sign_ext(d, 16)
    if A == 0:
        addr = SymbolicValue(offset)
    else:
        addr = state.read_reg(PpcReg.GPR(A)) + offset

    value = state.read_reg(PpcReg.GPR(S))
    state.write_mem(addr, value, type)

    if update:
        if A == 0:
            _log_invalid_instr(instr, state.pc, "A==0 in store-with-update")
        state.write_reg(PpcReg.GPR(A), addr)

    return (state,)


def _resolve_branch[T: PpcState](
    state: T,
    target_addr: SymOrInt,
    ctr_ok: bool | None,
    cond_ok: bool | None,
    link: bool,
) -> tuple[T, ...]:
    if ctr_ok is None or cond_ok is None:
        branch = state.fork()
        branch.branch(target_addr, link)
        return (state, branch)
    if ctr_ok and cond_ok:
        state.branch(target_addr, link)
        return (state,)
    return (state,)


def _exec_add[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    B = instr.gpr_field(16, 20)
    OE = instr.bit(21)
    Rc = instr.bit(31)

    rA = state.read_reg(A)
    rB = state.read_reg(B)
    sum = rA + rB

    if OE == 1:
        if sum.is_known:
            overflow = SymbolicValue(sum > 0xFFFF_FFFF)
        else:
            overflow = SymbolicValue.Unknown
        _set_xer(state, ov=overflow)

    # Sign extend for CR test
    result = sum.cast(s32)

    if Rc == 1:
        _update_cr(state, result)

    state.write_reg(D, result)

    return (state,)


def _exec_addi[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.field(11, 15)  # Do not read directly as GPR!
    SIMM = instr.simm_field(16, 31) & 0xFFFF_FFFF

    if A == 0:
        value = SymbolicValue(SIMM)
    else:
        value = state.read_reg(PpcReg.GPR(A)) + SIMM

    state.write_reg(D, value)

    return (state,)


def _exec_addis[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.field(11, 15)  # Do not read directly as GPR!
    SIMM = instr.simm_field(16, 31) & 0xFFFF_FFFF

    SIMM <<= 16

    if A == 0:
        value = SymbolicValue(SIMM)
    else:
        value = state.read_reg(PpcReg.GPR(A)) + SIMM

    state.write_reg(D, value)

    return (state,)


def _exec_b[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    LI = instr.field(6, 29)
    AA = instr.bit(30)
    LK = instr.bit(31)

    offset = sign_ext(LI << 2, 26)
    if AA == 1:
        target_addr = SymbolicValue(offset)
    else:
        target_addr = state.pc + offset

    state.branch(target_addr, LK == 1)

    return (state,)


def _exec_bc[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    BO = instr.field(6, 10)
    BI = instr.field(11, 15)
    BD = instr.field(16, 29)
    AA = instr.bit(30)
    LK = instr.bit(31)

    ctr_ok = _check_ctr(state, BO)
    cond_ok = _check_cr(state, BO, BI)

    offset = sign_ext(BD << 2, 16)
    if AA == 1:
        target_addr = SymbolicValue(offset)
    else:
        target_addr = state.pc + offset

    return _resolve_branch(state, target_addr, ctr_ok, cond_ok, LK == 1)


def _exec_bcctr[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    BO = instr.field(6, 10)
    BI = instr.field(11, 15)
    LK = instr.bit(31)

    if (BO & 0b00100) == 0:
        _log_invalid_instr(instr, state.pc, "decrement-and-test in bcctr")

    ctr_ok = _check_ctr(state, BO)
    cond_ok = _check_cr(state, BO, BI)

    target_addr = state.read_reg(PpcReg.CTR) & 0xFFFF_FFFC

    return _resolve_branch(state, target_addr, ctr_ok, cond_ok, LK == 1)


def _exec_bclr[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    BO = instr.field(6, 10)
    BI = instr.field(11, 15)
    LK = instr.bit(31)

    ctr_ok = _check_ctr(state, BO)
    cond_ok = _check_cr(state, BO, BI)

    target_addr = state.read_reg(PpcReg.LR) & 0xFFFF_FFFC

    return _resolve_branch(state, target_addr, ctr_ok, cond_ok, LK == 1)


def _exec_cmp[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.field(6, 8)
    L = instr.bit(10)
    A = instr.gpr_field(11, 15)
    B = instr.gpr_field(16, 20)

    if L == 1:
        _log_invalid_instr(instr, state.pc, "L==1 in cmp instruction")

    rA = state.read_reg(A)
    rB = state.read_reg(B)

    rA = rA.cast(s32)
    rB = rB.cast(s32)

    _update_cr(state, rA - rB, D)

    return (state,)


def _exec_cmpi[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 8)
    L = instr.bit(10)
    A = instr.gpr_field(11, 15)
    SIMM = instr.simm_field(16, 31)

    if L == 1:
        _log_invalid_instr(instr, state.pc, "L==1 in cmpi instruction")

    rA = state.read_reg(A)
    rA = rA.cast(s32)

    _update_cr(state, rA - SIMM, D)

    return (state,)


def _exec_cmpl[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.field(6, 8)
    L = instr.bit(10)
    A = instr.gpr_field(11, 15)
    B = instr.gpr_field(16, 20)

    if L == 1:
        _log_invalid_instr(instr, state.pc, "L==1 in cmpl instruction")

    rA = state.read_reg(A)
    rB = state.read_reg(B)

    _update_cr(state, rA - rB, D)

    return (state,)


def _exec_cmpli[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 8)
    L = instr.bit(10)
    A = instr.gpr_field(11, 15)
    UIMM = instr.uimm_field(16, 31)

    if L == 1:
        _log_invalid_instr(instr, state.pc, "L==1 in cmpli instruction")

    rA = state.read_reg(A)

    _update_cr(state, rA - UIMM, D)

    return (state,)


def _exec_lbz[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u8)


def _exec_lbzu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u8, True)


def _exec_lha[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, s16)


def _exec_lhau[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, s16, True)


def _exec_lhz[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u16)


def _exec_lhzu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u16, True)


def _exec_lwz[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u32)


def _exec_lwzu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_load(instr, state, u32, True)


def _exec_mfspr[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    spr1 = instr.field(11, 15)
    spr2 = instr.field(16, 20)
    SPR = (spr2 << 0x5) + spr1

    spr = _SPR_MAP.get(SPR)
    if not spr:
        msg = "invalid SPR in mfspr instruction"
        _log_invalid_instr(instr, state.pc, msg)
        raise ExecutionError(msg)

    value = state.read_reg(spr)
    state.write_reg(D, value)

    return (state,)


def _exec_mtspr[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    spr1 = instr.field(11, 15)
    spr2 = instr.field(16, 20)
    SPR = (spr2 << 0x5) + spr1

    spr = _SPR_MAP.get(SPR)
    if not spr:
        msg = "invalid SPR in mtspr instruction"
        _log_invalid_instr(instr, state.pc, msg)
        raise ExecutionError(msg)

    value = state.read_reg(S)
    state.write_reg(spr, value)

    return (state,)


def _exec_mullw[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    B = instr.gpr_field(16, 20)
    OE = instr.bit(21)
    Rc = instr.bit(31)

    rA = state.read_reg(A)
    rB = state.read_reg(B)

    product = rA * rB
    result = product & 0xFFFF_FFFF

    if OE == 1:
        if product.is_known:
            overflow = SymbolicValue(product > 0xFFFF_FFFF)
        else:
            overflow = SymbolicValue.Unknown
        _set_xer(state, ov=overflow)

    if Rc == 1:
        _update_cr(state, result)

    state.write_reg(D, result)

    return (state,)


def _exec_neg[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    OE = instr.bit(21)
    Rc = instr.bit(31)

    rA = state.read_reg(A)
    result = (~rA & 0xFFFF_FFFF) + 1

    if OE == 1:
        if rA.is_known:
            overflow = SymbolicValue(rA == 0x8000_0000)
        else:
            overflow = SymbolicValue.Unknown
        _set_xer(state, ov=overflow)

    if Rc == 1:
        _update_cr(state, result)

    state.write_reg(D, result)

    return (state,)


def _exec_or[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    B = instr.gpr_field(16, 20)
    Rc = instr.bit(31)

    rS = state.read_reg(S)
    rB = state.read_reg(B)

    result = rS | rB
    state.write_reg(A, result)

    if Rc == 1:
        _update_cr(state, result)

    return (state,)


def _exec_ori[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    UIMM = instr.uimm_field(16, 31)

    rS = state.read_reg(S)

    result = rS | UIMM
    state.write_reg(A, result)

    return (state,)


def _exec_oris[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    UIMM = instr.uimm_field(16, 31)

    rS = state.read_reg(S)

    result = rS | (UIMM << 16)
    state.write_reg(A, result)

    return (state,)


def _exec_rlwimi[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    SH = instr.field(16, 20)
    MB = instr.field(21, 25)
    ME = instr.field(26, 30)
    Rc = instr.bit(31)

    rS = state.read_reg(S)
    rA = state.read_reg(A)

    r = rotate_l(rS, SH)
    m = create_mask(MB, ME)

    result = (r & m) | (rA & ~m)
    state.write_reg(A, result)

    if Rc == 1:
        _update_cr(state, result)

    return (state,)


def _exec_rlwinm[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    SH = instr.field(16, 20)
    MB = instr.field(21, 25)
    ME = instr.field(26, 30)
    Rc = instr.bit(31)

    rS = state.read_reg(S)

    r = rotate_l(rS, SH)
    m = create_mask(MB, ME)

    result = r & m
    state.write_reg(A, result)

    if Rc == 1:
        _update_cr(state, result)

    return (state,)


def _exec_srawi[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    S = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    SH = instr.field(16, 20)
    Rc = instr.bit(31)

    rS = state.read_reg(S)

    r = rotate_l(rS, 32 - SH)
    m = create_mask(SH, 31)
    sign_bit = (rS >> 31) & 0x1

    result = (r & m) | (sign_ext(sign_bit, 1) & ~m)
    carry = sign_bit & ((r & ~m) != 0)

    state.write_reg(A, result)
    _set_xer(state, ca=carry)

    if Rc == 1:
        _update_cr(state, result)

    return (state,)


def _exec_stb[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u8)


def _exec_stbu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u8, True)


def _exec_sth[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u16)


def _exec_sthu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u16, True)


def _exec_stw[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u32)


def _exec_stwu[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    return _exec_store(instr, state, u32, True)


def _exec_subfic[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    D = instr.gpr_field(6, 10)
    A = instr.gpr_field(11, 15)
    SIMM = instr.simm_field(16, 31) & 0xFFFF_FFFF

    rA = state.read_reg(A)

    value = SIMM + (~rA & 0xFFFF_FFFF) + 1
    carry = (value >> 32) & 1

    _set_xer(state, ca=carry)
    state.write_reg(D, value)

    return (state,)


def _not_implemented[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    raise NotImplementedError(f"{instr.op} has not been implemented (pc={state.pc:#x})")


def execute[T: PpcState](instr: PpcInstr, state: T) -> tuple[T, ...]:
    exec_func = _op_lookup[instr.op]
    branches = exec_func(instr, state)
    return branches


_op_lookup = {
    # fmt: off
    PpcOp.ADD        : _exec_add,
    PpcOp.ADDO       : _exec_add,
    PpcOp.ADDC       : _not_implemented,
    PpcOp.ADDCO      : _not_implemented,
    PpcOp.ADDE       : _not_implemented,
    PpcOp.ADDEO      : _not_implemented,
    PpcOp.ADDI       : _exec_addi,
    PpcOp.ADDIC      : _not_implemented,
    PpcOp.ADDIC_     : _not_implemented,
    PpcOp.ADDIS      : _exec_addis,
    PpcOp.ADDME      : _not_implemented,
    PpcOp.ADDMEO     : _not_implemented,
    PpcOp.ADDZE      : _not_implemented,
    PpcOp.ADDZEO     : _not_implemented,
    PpcOp.AND        : _not_implemented,
    PpcOp.ANDC       : _not_implemented,
    PpcOp.ANDI_      : _not_implemented,
    PpcOp.ANDIS_     : _not_implemented,
    PpcOp.B          : _exec_b,
    PpcOp.BC         : _exec_bc,
    PpcOp.BCCTR      : _exec_bcctr,
    PpcOp.BCLR       : _exec_bclr,
    PpcOp.CMP        : _exec_cmp,
    PpcOp.CMPI       : _exec_cmpi,
    PpcOp.CMPL       : _exec_cmpl,
    PpcOp.CMPLI      : _exec_cmpli,
    PpcOp.CNTLZW     : _not_implemented,
    PpcOp.CRAND      : _not_implemented,
    PpcOp.CRANDC     : _not_implemented,
    PpcOp.CREQV      : _not_implemented,
    PpcOp.CRNAND     : _not_implemented,
    PpcOp.CRNOR      : _not_implemented,
    PpcOp.CROR       : _not_implemented,
    PpcOp.CRORC      : _not_implemented,
    PpcOp.CRXOR      : _not_implemented,
    PpcOp.DCBF       : _not_implemented,
    PpcOp.DCBI       : _not_implemented,
    PpcOp.DCBST      : _not_implemented,
    PpcOp.DCBT       : _not_implemented,
    PpcOp.DCBTST     : _not_implemented,
    PpcOp.DCBZ       : _not_implemented,
    PpcOp.DCBZ_L     : _not_implemented,
    PpcOp.DIVW       : _not_implemented,
    PpcOp.DIVWO      : _not_implemented,
    PpcOp.DIVWU      : _not_implemented,
    PpcOp.DIVWUO     : _not_implemented,
    PpcOp.ECIWX      : _not_implemented,
    PpcOp.ECOWX      : _not_implemented,
    PpcOp.EIEIO      : _not_implemented,
    PpcOp.EQV        : _not_implemented,
    PpcOp.EXTSB      : _not_implemented,
    PpcOp.EXTSH      : _not_implemented,
    PpcOp.FABS       : _not_implemented,
    PpcOp.FADD       : _not_implemented,
    PpcOp.FADDS      : _not_implemented,
    PpcOp.FCMPO      : _not_implemented,
    PpcOp.FCMPU      : _not_implemented,
    PpcOp.FCTIW      : _not_implemented,
    PpcOp.FCTIWZ     : _not_implemented,
    PpcOp.FDIV       : _not_implemented,
    PpcOp.FDIVS      : _not_implemented,
    PpcOp.FMADD      : _not_implemented,
    PpcOp.FMADDS     : _not_implemented,
    PpcOp.FMR        : _not_implemented,
    PpcOp.FMSUB      : _not_implemented,
    PpcOp.FMSUBS     : _not_implemented,
    PpcOp.FMUL       : _not_implemented,
    PpcOp.FMULS      : _not_implemented,
    PpcOp.FNABS      : _not_implemented,
    PpcOp.FNEG       : _not_implemented,
    PpcOp.FNMADD     : _not_implemented,
    PpcOp.FNMADDS    : _not_implemented,
    PpcOp.FNMSUB     : _not_implemented,
    PpcOp.FNMSUBS    : _not_implemented,
    PpcOp.FRES       : _not_implemented,
    PpcOp.FRSP       : _not_implemented,
    PpcOp.FRSQRTE    : _not_implemented,
    PpcOp.FSEL       : _not_implemented,
    PpcOp.FSUB       : _not_implemented,
    PpcOp.FSUBS      : _not_implemented,
    PpcOp.ICBI       : _not_implemented,
    PpcOp.ISYNC      : _not_implemented,
    PpcOp.LBZ        : _exec_lbz,
    PpcOp.LBZU       : _exec_lbzu,
    PpcOp.LBZUX      : _not_implemented,
    PpcOp.LBZX       : _not_implemented,
    PpcOp.LFD        : _not_implemented,
    PpcOp.LFDU       : _not_implemented,
    PpcOp.LFDUX      : _not_implemented,
    PpcOp.LFDX       : _not_implemented,
    PpcOp.LFS        : _not_implemented,
    PpcOp.LFSU       : _not_implemented,
    PpcOp.LFSUX      : _not_implemented,
    PpcOp.LFSX       : _not_implemented,
    PpcOp.LHA        : _exec_lha,
    PpcOp.LHAU       : _exec_lhau,
    PpcOp.LHAUX      : _not_implemented,
    PpcOp.LHAX       : _not_implemented,
    PpcOp.LHBRX      : _not_implemented,
    PpcOp.LHZ        : _exec_lhz,
    PpcOp.LHZU       : _exec_lhzu,
    PpcOp.LHZUX      : _not_implemented,
    PpcOp.LHZX       : _not_implemented,
    PpcOp.LMW        : _not_implemented,
    PpcOp.LSWI       : _not_implemented,
    PpcOp.LSWX       : _not_implemented,
    PpcOp.LWARX      : _not_implemented,
    PpcOp.LWBRX      : _not_implemented,
    PpcOp.LWZ        : _exec_lwz,
    PpcOp.LWZU       : _exec_lwzu,
    PpcOp.LWZUX      : _not_implemented,
    PpcOp.LWZX       : _not_implemented,
    PpcOp.MCRF       : _not_implemented,
    PpcOp.MCRFS      : _not_implemented,
    PpcOp.MCRXR      : _not_implemented,
    PpcOp.MFCR       : _not_implemented,
    PpcOp.MFFS       : _not_implemented,
    PpcOp.MFMSR      : _not_implemented,
    PpcOp.MFSPR      : _exec_mfspr,
    PpcOp.MFSR       : _not_implemented,
    PpcOp.MFSRIN     : _not_implemented,
    PpcOp.MFTB       : _not_implemented,
    PpcOp.MTCRF      : _not_implemented,
    PpcOp.MTFSB0     : _not_implemented,
    PpcOp.MTFSB1     : _not_implemented,
    PpcOp.MTFSF      : _not_implemented,
    PpcOp.MTFSFI     : _not_implemented,
    PpcOp.MTMSR      : _not_implemented,
    PpcOp.MTSPR      : _exec_mtspr,
    PpcOp.MTSR       : _not_implemented,
    PpcOp.MTSRIN     : _not_implemented,
    PpcOp.MULHW      : _not_implemented,
    PpcOp.MULHWU     : _not_implemented,
    PpcOp.MULLI      : _not_implemented,
    PpcOp.MULLW      : _exec_mullw,
    PpcOp.MULLWO     : _exec_mullw,
    PpcOp.NAND       : _not_implemented,
    PpcOp.NEG        : _exec_neg,
    PpcOp.NEGO       : _exec_neg,
    PpcOp.NOR        : _not_implemented,
    PpcOp.OR         : _exec_or,
    PpcOp.ORC        : _not_implemented,
    PpcOp.ORI        : _exec_ori,
    PpcOp.ORIS       : _exec_oris,
    PpcOp.PSQ_L      : _not_implemented,
    PpcOp.PSQ_LU     : _not_implemented,
    PpcOp.PSQ_LUX    : _not_implemented,
    PpcOp.PSQ_LX     : _not_implemented,
    PpcOp.PSQ_ST     : _not_implemented,
    PpcOp.PSQ_STU    : _not_implemented,
    PpcOp.PSQ_STUX   : _not_implemented,
    PpcOp.PSQ_STX    : _not_implemented,
    PpcOp.PS_ABS     : _not_implemented,
    PpcOp.PS_ADD     : _not_implemented,
    PpcOp.PS_CMPO0   : _not_implemented,
    PpcOp.PS_CMPO1   : _not_implemented,
    PpcOp.PS_CMPU0   : _not_implemented,
    PpcOp.PS_CMPU1   : _not_implemented,
    PpcOp.PS_DIV     : _not_implemented,
    PpcOp.PS_MADD    : _not_implemented,
    PpcOp.PS_MADDS0  : _not_implemented,
    PpcOp.PS_MADDS1  : _not_implemented,
    PpcOp.PS_MERGE00 : _not_implemented,
    PpcOp.PS_MERGE01 : _not_implemented,
    PpcOp.PS_MERGE10 : _not_implemented,
    PpcOp.PS_MERGE11 : _not_implemented,
    PpcOp.PS_MR      : _not_implemented,
    PpcOp.PS_MSUB    : _not_implemented,
    PpcOp.PS_MUL     : _not_implemented,
    PpcOp.PS_MULS0   : _not_implemented,
    PpcOp.PS_MULS1   : _not_implemented,
    PpcOp.PS_NABS    : _not_implemented,
    PpcOp.PS_NEG     : _not_implemented,
    PpcOp.PS_NMADD   : _not_implemented,
    PpcOp.PS_NMSUB   : _not_implemented,
    PpcOp.PS_RES     : _not_implemented,
    PpcOp.PS_RSQRTE  : _not_implemented,
    PpcOp.PS_SEL     : _not_implemented,
    PpcOp.PS_SUB     : _not_implemented,
    PpcOp.PS_SUM0    : _not_implemented,
    PpcOp.PS_SUM1    : _not_implemented,
    PpcOp.RFI        : _not_implemented,
    PpcOp.RLWIMI     : _exec_rlwimi,
    PpcOp.RLWINM     : _exec_rlwinm,
    PpcOp.RLWNM      : _not_implemented,
    PpcOp.SC         : _not_implemented,
    PpcOp.SLW        : _not_implemented,
    PpcOp.SRAW       : _not_implemented,
    PpcOp.SRAWI      : _exec_srawi,
    PpcOp.SRW        : _not_implemented,
    PpcOp.STB        : _exec_stb,
    PpcOp.STBU       : _exec_stbu,
    PpcOp.STBUX      : _not_implemented,
    PpcOp.STBX       : _not_implemented,
    PpcOp.STFD       : _not_implemented,
    PpcOp.STFDU      : _not_implemented,
    PpcOp.STFDUX     : _not_implemented,
    PpcOp.STFDX      : _not_implemented,
    PpcOp.STFIWX     : _not_implemented,
    PpcOp.STFS       : _not_implemented,
    PpcOp.STFSU      : _not_implemented,
    PpcOp.STFSUX     : _not_implemented,
    PpcOp.STFSX      : _not_implemented,
    PpcOp.STH        : _exec_sth,
    PpcOp.STHBRX     : _not_implemented,
    PpcOp.STHU       : _exec_sthu,
    PpcOp.STHUX      : _not_implemented,
    PpcOp.STHX       : _not_implemented,
    PpcOp.STMW       : _not_implemented,
    PpcOp.STSWI      : _not_implemented,
    PpcOp.STSWX      : _not_implemented,
    PpcOp.STW        : _exec_stw,
    PpcOp.STWBRX     : _not_implemented,
    PpcOp.STWCX_     : _not_implemented,
    PpcOp.STWU       : _exec_stwu,
    PpcOp.STWUX      : _not_implemented,
    PpcOp.STWX       : _not_implemented,
    PpcOp.SUBF       : _not_implemented,
    PpcOp.SUBFO      : _not_implemented,
    PpcOp.SUBFC      : _not_implemented,
    PpcOp.SUBFCO     : _not_implemented,
    PpcOp.SUBFE      : _not_implemented,
    PpcOp.SUBFEO     : _not_implemented,
    PpcOp.SUBFIC     : _exec_subfic,
    PpcOp.SUBFME     : _not_implemented,
    PpcOp.SUBFMEO    : _not_implemented,
    PpcOp.SUBFZE     : _not_implemented,
    PpcOp.SUBFZEO    : _not_implemented,
    PpcOp.SYNC       : _not_implemented,
    PpcOp.TLBIE      : _not_implemented,
    PpcOp.TLBSYNC    : _not_implemented,
    PpcOp.TW         : _not_implemented,
    PpcOp.TWI        : _not_implemented,
    PpcOp.XOR        : _not_implemented,
    PpcOp.XORI       : _not_implemented,
    PpcOp.XORIS      : _not_implemented,
}
