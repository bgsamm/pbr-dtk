from rvl import Dol
from rvl.types import *
from .common import SymOrInt
from .reg import VmReg
from .thread import VmCallback, VmThread
import logging
import re

class WiiVm:
    _DEFAULT_MEM_DUMP_SIZE = 0x80

    _threads: list[VmThread]
    _breakpoints: set[int]
    _mem_watch: int | None

    # TODO Do I really want to be passing a DOL in?
    def __init__(self, dol: Dol):
        self._dol = dol
        self._threads = []
        self._active_thread = None
        self._breakpoints = set()
        self._mem_watch = None
        self._in_breakpoint = False
        self._should_exit = False

    @property
    def active_thread(self) -> VmThread | None:
        return self._active_thread

    def _exec_command(self, *args: str):
        def normalize_reg_name(name):
            if (match:= re.match(r'([rf])(\d+)', name)):
                pre, num = match.groups()
                name = ('gpr' if pre == 'r' else 'fpr') + num
            return name.upper()

        assert self._active_thread

        match args:
            case ['c']:
                self._in_breakpoint = False
            case ['q']:
                self._should_exit = True
            case ['bp', 'clear', 'all']:
                self.clear_breakpoints()
            case ['bp', 'clear', addr]:
                self.clear_breakpoint(int(addr, 0))
            case ['bp', 'set', addr]:
                self.set_breakpoint(int(addr, 0))
            case ['mem', 'dump', addr]:
                self._active_thread.print_mem(int(addr, 0), self._DEFAULT_MEM_DUMP_SIZE)
            case ['mem', 'dump', addr, size]:
                self._active_thread.print_mem(int(addr, 0), int(size, 0))
            case ['mem', 'set', addr, value, dtype]:
                dtype = C_TYPE_LOOKUP.get(dtype)
                if not dtype:
                    logging.error('Invalid type')
                    return
                self._active_thread.write_mem(dtype, int(addr, 0), int(value, 0))
            case ['mem', 'watch', addr]:
                self.set_mem_watch(int(addr, 0))
            case ['reg', 'set', reg, value]:
                reg = VmReg[normalize_reg_name(reg)]
                self._active_thread.write_reg(reg, int(value, 0))
                self._active_thread.print_regs(include_fprs=False)
            case ['reg', 'tag', reg]:
                reg = VmReg[normalize_reg_name(reg)]
                tag = self._active_thread.get_register_tag(reg)
                print(f'{reg.name}: {tag}')
            case ['reg', 'tag', reg, tag]:
                reg = VmReg[normalize_reg_name(reg)]
                self._active_thread.tag_register(reg, int(tag, 0))
            case ['threads']:
                print(len(self._threads))
            case _:
                logging.error('Invalid command')

    def _do_breakpoint(self):
        assert self._active_thread

        self._active_thread.print_regs(include_fprs=False)

        if self._mem_watch:
            self._active_thread.print_mem(self._mem_watch, self._DEFAULT_MEM_DUMP_SIZE)

        while self._in_breakpoint:
            args = input('>> ').lower().split()

            if len(args) == 0:
                return

            try:
                self._exec_command(*args)
            except Exception as e:
                logging.error(e)

            if self._should_exit:
                return

    def set_breakpoint(self, address: int):
        self._breakpoints.add(address)

    def clear_breakpoint(self, address: int):
        if address in self._breakpoints:
            self._breakpoints.remove(address)

    def clear_breakpoints(self):
        self._breakpoints.clear()

    def set_mem_watch(self, address: int):
        self._mem_watch = address

    def run(self,
            entry_point: int | None = None,
            callback: VmCallback | None = None,
            init_state: dict[VmReg, SymOrInt] | None = None,
            reg_tags: dict[VmReg, int] | None = None,
            step_into_calls: bool | set[int] = False):
        self._threads.clear()

        if entry_point is None:
            entry_point = self._dol.entry_point

        start_thread = VmThread(self._dol,
                                init_state=init_state,
                                reg_tags=reg_tags,
                                step_into_calls=step_into_calls)
        start_thread.set_callback(callback)
        start_thread.set_pc(entry_point)

        self._threads.append(start_thread)

        while len(self._threads) > 0:
            thread = self._active_thread = self._threads[0]

            if thread.should_terminate():
                # TODO Avoid popping from front of list?
                self._threads.pop(0)
                logging.debug(f'Thread finished. Total threads remaining: {len(self._threads)}')
                continue

            self._in_breakpoint |= (thread.get_pc() in self._breakpoints)

            if self._in_breakpoint:
                # TODO Better handle breakpoints & multiple threads?
                self._do_breakpoint()

            if self._should_exit:
                return

            # None on error
            if (branches := thread.step()) is None:
                # TODO Custom exception?
                raise RuntimeError()

            # TODO Something better?
            self._threads = list(branches) + self._threads[1:]
