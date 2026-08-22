from dataclasses import dataclass
from enum import IntEnum
from typing import Callable
from ppc import PpcInstr, PpcReg
from symval import SymbolicValue
from typealiases import ctype
from .state import VmState
import enum

type VmCallback[E: VmEvent] = Callable[[E, VmState], VmSignal]


class VmHaltException(Exception):
    pass


class VmSignal(IntEnum):
    # fmt: off
    CONTINUE  = enum.auto()
    STEP_OVER = enum.auto()
    HALT      = enum.auto()
    # fmt: on


@dataclass(frozen=True)
class VmEvent:
    thread_id: int
    pc: int
    instr: PpcInstr


@dataclass(frozen=True)
class VmPreExecuteEvent(VmEvent):
    pass


@dataclass(frozen=True)
class VmPostExecuteEvent(VmEvent):
    pass


@dataclass(frozen=True)
class VmReadRegEvent(VmEvent):
    reg: PpcReg
    value: SymbolicValue


@dataclass(frozen=True)
class VmWriteRegEvent(VmEvent):
    reg: PpcReg
    value: SymbolicValue


@dataclass(frozen=True)
class VmReadMemEvent(VmEvent):
    addr: SymbolicValue
    value: SymbolicValue
    dtype: ctype


@dataclass(frozen=True)
class VmWriteMemEvent(VmEvent):
    addr: SymbolicValue
    value: SymbolicValue
    dtype: ctype


@dataclass(frozen=True)
class VmForkEvent(VmEvent):
    parent_id: int
    child_id: int


@dataclass(frozen=True)
class VmCallEvent(VmEvent):
    target_addr: SymbolicValue


__all__ = [
    "VmCallback",
    "VmHaltException",
    "VmSignal",
    "VmEvent",
    "VmPreExecuteEvent",
    "VmPostExecuteEvent",
    "VmReadRegEvent",
    "VmWriteRegEvent",
    "VmReadMemEvent",
    "VmWriteMemEvent",
    "VmForkEvent",
    "VmCallEvent",
]
