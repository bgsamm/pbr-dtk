from functools import cached_property
from typing import Mapping, Self
from ppc import PpcReg
from symval import SymbolicValue, SymOrInt
from typealiases import *
from .mmap import VmMemMap, VmMemView
import symval


class VmState:
    _regs: dict[PpcReg, SymbolicValue]
    _mmap: VmMemMap

    # TODO Support specifying initial memory state
    def __init__(self, init_state: Mapping[PpcReg, SymOrInt] | None = None) -> None:
        # TODO VmRegMap?
        self._regs = {reg: SymbolicValue.Unknown for reg in PpcReg}
        self._mmap = VmMemMap()

        if init_state:
            for reg, value in init_state.items():
                if isinstance(value, int):
                    value = SymbolicValue(value)
                self._regs[reg] = value

    def __hash__(self) -> int:
        # TODO Incorporate mmap
        return hash(tuple(sorted(self._regs.items())))

    @property
    def pc(self) -> SymbolicValue:
        return self.read_reg(PpcReg.PC)

    @pc.setter
    def pc(self, value: SymOrInt) -> None:
        self.write_reg(PpcReg.PC, value)

    @cached_property
    def memory(self) -> VmMemView:
        return VmMemView(self._mmap)

    def read_reg(self, reg: PpcReg) -> SymbolicValue:
        # TODO Revisit this (floating-point registers)
        value = self._regs[reg].cast(u32)
        return value

    def write_reg(self, reg: PpcReg, value: SymOrInt) -> SymbolicValue:
        value = symval.ensure_symbolic(value)

        # TODO Revisit this (floating-point registers)
        value = self._regs[reg] = value.cast(u32)
        return value

    def read_mem(self, addr: SymOrInt, dtype: ctype) -> SymbolicValue:
        addr = symval.ensure_symbolic(addr)

        if addr.is_known:
            address = addr.value
            value = self._mmap.read(address, dtype)
        else:
            value = SymbolicValue.Unknown
        return value

    def write_mem(self, addr: SymOrInt, value: SymOrInt, dtype: ctype) -> SymbolicValue:
        addr = symval.ensure_symbolic(addr)
        value = symval.ensure_symbolic(value)

        # Ensure value is in range for dtype
        value = value.cast(dtype)
        if addr.is_known:
            address = addr.value
            self._mmap.write(address, value, dtype)
        return value

    def reset_mem(self) -> None:
        # TODO Avoid resetting stack?
        self._mmap.reset()

    def branch(self, target_addr: SymOrInt, link: bool) -> None:
        if link:
            self.write_reg(PpcReg.LR, self.pc + 4)
        self.pc = target_addr

    def fork(self) -> Self:
        # TODO Avoid __new__
        new_state = object.__new__(self.__class__)

        new_state._regs = self._regs.copy()
        new_state._mmap = self._mmap.copy()

        return new_state
