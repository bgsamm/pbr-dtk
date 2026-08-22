from ppc import PpcReg
from symval import SymbolicValue
from typealiases import str_to_type
from vm import VmState, WiiVm
from vm.event import VmCallback, VmPreExecuteEvent, VmSignal
import logging
import re


class Debugger:
    _DEFAULT_MEM_DUMP_SIZE = 0x80

    _breakpoints: set[int]
    _mem_watch: int | None
    _existing_callback: VmCallback[VmPreExecuteEvent] | None

    def __init__(self, vm: WiiVm) -> None:
        self._vm = vm
        self._breakpoints = set()
        self._mem_watch = None
        self._in_breakpoint = False

        self._existing_callback = self._vm.register_callback(
            VmPreExecuteEvent, self._on_pre_execute
        )

    def _print_regs(self, state: VmState, include_fprs: bool = True) -> None:
        def print_reg(name: str, value: SymbolicValue, width: int):
            print(f"{name.rjust(3)}: {value:0{width}X}", end=" ")

        def print_spr(reg: PpcReg, value: SymbolicValue):
            print_reg(reg.name.lower(), value, 8)

        def print_gpr(i: int, value: SymbolicValue):
            print_reg(f"r{i}", value, 8)

        def print_fpr(i: int, value: SymbolicValue):
            print_reg(f"f{i}", value, 16)

        for reg in PpcReg:
            value = state.read_reg(reg)
            if reg.is_gpr():
                i = reg - PpcReg.GPR0
                if i % 8 == 0:
                    print()
                print_gpr(i, value)
            elif reg.is_fpr():
                if include_fprs:
                    i = reg - PpcReg.FPR0
                    if i % 4 == 0:
                        print()
                    print_fpr(i, value)
            else:
                print_spr(reg, value)

        print()

    def _print_mem(self, state: VmState, address: int, size: int, row_len: int = 16):
        # TODO Allow unaligned addresses/sizes?
        address = (address // row_len) * row_len
        size = ((size + row_len - 1) // row_len) * row_len

        print(" " * 9 + " ".join(f"{x:02X}" for x in range(row_len)))

        for addr in range(address, address + size):
            if addr % row_len == 0:
                print(f"{addr:08X}", end=" ")

            value = state.memory[addr]
            print(f"{value:02X}", end=" ")

            if addr % row_len == row_len - 1:
                print()

    def _exec_command(self, state: VmState, *args: str):
        def normalize_reg_name(name):
            if match := re.match(r"([rf])(\d+)", name):
                pre, num = match.groups()
                name = ("gpr" if pre == "r" else "fpr") + num
            return name.upper()

        match args:
            case ["c"]:
                self._in_breakpoint = False
            case ["q" | "quit" | "exit"]:
                exit()
            case ["bp", "clear"]:
                self.clear_breakpoints()
            case ["bp", "clear", addr]:
                self.clear_breakpoint(int(addr, 0))
            case ["bp", "set", addr]:
                self.set_breakpoint(int(addr, 0))
            case ["mem", "dump", addr]:
                self._print_mem(state, int(addr, 0), self._DEFAULT_MEM_DUMP_SIZE)
            case ["mem", "dump", addr, size]:
                self._print_mem(state, int(addr, 0), int(size, 0))
            case ["mem", "set", addr, value, dtype]:
                dtype = str_to_type(dtype)
                state.write_mem(int(addr, 0), int(value, 0), dtype)
            case ["mem", "watch", addr]:
                self.set_mem_watch(int(addr, 0))
            case ["reg", "set", reg, value]:
                reg = PpcReg[normalize_reg_name(reg)]
                state.write_reg(reg, int(value, 0))
                self._print_regs(state, include_fprs=False)
            case ["threads"]:
                print(self._vm.thread_count)
            case _:
                logging.error("Invalid command")

    def _do_breakpoint(self, state: VmState) -> None:
        self._print_regs(state, include_fprs=False)

        if self._mem_watch:
            self._print_mem(state, self._mem_watch, self._DEFAULT_MEM_DUMP_SIZE)

        while self._in_breakpoint:
            args = input(">> ").lower().split()

            if len(args) == 0:
                return

            try:
                self._exec_command(state, *args)
            except Exception as e:
                logging.error(e)

    def _on_pre_execute(self, event: VmPreExecuteEvent, state: VmState) -> VmSignal:
        self._in_breakpoint |= event.pc in self._breakpoints

        if self._in_breakpoint:
            self._do_breakpoint(state)

        if self._existing_callback:
            return self._existing_callback(event, state)

        return VmSignal.CONTINUE

    def set_breakpoint(self, address: int):
        self._breakpoints.add(address)

    def clear_breakpoint(self, address: int):
        if address in self._breakpoints:
            self._breakpoints.remove(address)

    def clear_breakpoints(self):
        self._breakpoints.clear()

    def set_mem_watch(self, address: int):
        self._mem_watch = address
