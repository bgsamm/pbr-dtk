from typing import Iterator, Mapping, Self
from ppc import PpcInstr, PpcReg
from rvl import Dol
from symval import SymbolicValue, SymOrInt
from typealiases import *
from .event import *
from .state import VmState
import logging
import ppc


# TODO Cleaner handling of halting
# (Originally, was using an exception, but this lead to branches getting dropped)
class VmThread:
    halted: bool

    _id_generator: Iterator[int]
    _callbacks: dict[type[VmEvent], VmCallback]

    def __init__(
        self,
        dol: Dol,
        init_state: VmState,
        id_generator: Iterator[int],
        callbacks: Mapping[type[VmEvent], VmCallback] | None = None,
    ):
        self._id = next(id_generator)
        self._id_generator = id_generator

        self._dol = dol
        self._state = init_state.fork()

        if callbacks:
            self._callbacks = {ev: cb for ev, cb in callbacks.items()}
        else:
            self._callbacks = {}

        self._did_branch = False
        self.halted = False

    @property
    def id(self) -> int:
        return self._id

    @property
    def pc(self) -> SymbolicValue:
        return self._state.pc

    @pc.setter
    def pc(self, value: SymOrInt) -> None:
        self._state.pc = value

    def _read_instruction(self) -> PpcInstr:
        assert self.pc.is_known
        raw_instr = self._dol.read(u32, self.pc.value)
        return PpcInstr(raw_instr)

    def _do_callback(self, event_class: type[VmEvent], **kwargs) -> VmSignal:
        if self.halted:
            return VmSignal.HALT

        if not (callback := self._callbacks.get(event_class)):
            return VmSignal.CONTINUE

        addr = self._current_address
        instr = self._current_instruction
        event = event_class(self.id, addr, instr, **kwargs)

        signal = callback(event, self._state)
        if signal == VmSignal.HALT:
            self.halted = True

        return signal

    # TODO Revisit this
    def _set_post_call_state(self):
        for reg in PpcReg:
            if reg.is_volatile():
                self._state.write_reg(reg, SymbolicValue.Unknown)
        self._state.reset_mem()

    def peek_reg(self, reg: PpcReg) -> SymbolicValue:
        return self._state.read_reg(reg)

    def poke_reg(self, reg: PpcReg, value: int) -> SymbolicValue:
        return self._state.write_reg(reg, value)

    def peek_mem(self, addr: int, dtype: ctype) -> SymbolicValue:
        return self._state.read_mem(addr, dtype)

    def poke_mem(self, addr: int, value: int, dtype: ctype) -> SymbolicValue:
        return self._state.write_mem(addr, value, dtype)

    def read_reg(self, reg: PpcReg) -> SymbolicValue:
        value = self._state.read_reg(reg)
        self._do_callback(VmReadRegEvent, reg=reg, value=value)
        return value

    def write_reg(self, reg: PpcReg, value: SymOrInt) -> SymbolicValue:
        value = self._state.write_reg(reg, value)
        self._do_callback(VmWriteRegEvent, reg=reg, value=value)
        return value

    def read_mem(self, addr: SymOrInt, dtype: ctype) -> SymbolicValue:
        value = self._state.read_mem(addr, dtype)
        self._do_callback(VmReadMemEvent, addr=addr, value=value, dtype=dtype)
        return value

    def write_mem(self, addr: SymOrInt, value: SymOrInt, dtype: ctype) -> SymbolicValue:
        value = self._state.write_mem(addr, value, dtype)
        self._do_callback(VmWriteMemEvent, addr=addr, value=value, dtype=dtype)
        return value

    def reset_mem(self) -> None:
        self._state.reset_mem()

    def fork(self) -> Self:
        logging.debug(f"Forking thread {self.id} (pc={self.pc:X})")

        new_thread = self.__class__(
            self._dol, self._state, self._id_generator, self._callbacks
        )
        # TODO Revisit this
        new_thread._current_address = self._current_address
        new_thread._current_instruction = self._current_instruction

        self._do_callback(VmForkEvent, parent_id=self.id, child_id=new_thread.id)
        return new_thread

    def branch(self, target_addr: SymOrInt, link: bool) -> None:
        signal = self._do_callback(VmBranchEvent, target_addr=target_addr, link=link)

        if link:
            self.write_reg(PpcReg.LR, self.pc + 4)

        if link and signal == VmSignal.STEP_OVER:
            logging.debug(f"Stepping over call to 0x{target_addr:X} at 0x{self.pc:X}")
            self._set_post_call_state()
            self.pc += 4
        else:
            self.pc = target_addr

        self._did_branch = True

    def step(self) -> tuple[VmThread, ...]:
        if self.pc.is_unknown:
            last_addr = self._current_address
            logging.warning(
                f"PC is unknown for thread {self.id}; halting thread (last known pc: {last_addr:#x})"
            )
            self.halted = True
            return (self,)

        self._current_address = self.pc.value
        self._current_instruction = self._read_instruction()

        self._did_branch = False

        self._do_callback(VmPreExecuteEvent)

        instr = self._current_instruction
        branches = ppc.execute(instr, self)

        for branch in branches:
            branch._do_callback(VmPostExecuteEvent)

        if not self._did_branch:
            self.pc += 4

        return branches
