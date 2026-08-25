from collections import defaultdict
from dataclasses import dataclass
from graphlib import TopologicalSorter
from typing import Sequence
from dtk.symbols import Symbol, SymbolMap
from ppc import PpcReg
from rvl import Dol
from typealiases import *
from vm import VmState, WiiVm
from vm.event import *
from .common import *
from .debugger import Debugger
from .statemanager import AnalysisError, InternalResult, StateManager
from .typeinfo import *
from .typereg import TypeRegistry
import logging

# TODO Decouple this module from Debugger?


@dataclass(frozen=True)
class AnalysisResult:
    func_name: str
    type_registry: TypeRegistry
    arguments: Sequence[TypeInfo]
    return_type: TypeInfo
    structs: Sequence[StructType]
    subcalls: dict[int, AnalysisResult]


class _FunctionAnalyzer:
    # TODO Make customizable?
    _MAX_LOOP_ITERS = 10

    _breakpoints: set[int]
    _save_rest_subs: set[Symbol]

    _seen_addresses: dict[int, set[int]]
    """A mapping from addresses to a set of previous state hashes"""

    _thread_trace: dict[int, list[int]]
    """A mapping from thread ID to addresses visited by that thread"""

    _subanalysis_result: InternalResult

    def __init__(
        self,
        dol: Dol,
        entry_point: int,
        symbol_map: SymbolMap,
        save_rest_subs: set[Symbol],
        max_depth: int = 0,
        breakpoints: set[int] | None = None,
        type_registry: TypeRegistry | None = None,
    ):
        self._dol = dol
        self._func_addr = entry_point
        self._symbol_map = symbol_map
        self._max_depth = max_depth
        self._breakpoints = breakpoints or set()

        self._save_rest_subs = save_rest_subs

        self._state_manager = StateManager(type_registry)
        self._subcalls = {}
        self._thread_trace = defaultdict(list)
        self._seen_addresses = defaultdict(set)

        # TODO Something more extensible
        self._base_state = VmState(
            {
                PpcReg.GPR1: 0x80653050,
                PpcReg.GPR2: 0x80648600,
                PpcReg.GPR13: 0x806452C0,
                PpcReg.CR: 0,
                PpcReg.XER: 0,
            }
        )

        self._func_size = self._get_func_size()

        self._did_call = False
        self._did_tail_call = False

    def _get_func_size(self) -> int:
        func_addr = self._func_addr
        symbols = self._symbol_map.get_symbols_at(func_addr)

        sizes = [symbol.size for symbol in symbols if symbol.size]

        if not sizes:
            raise AnalysisError(f"No symbol w/ known size at {func_addr:#x}")

        if any(size != sizes[0] for size in sizes):
            raise AnalysisError(f"Inconsistent symbols sizes for {func_addr:#x}")

        return sizes[0]

    def _update_address_record(self, address: int, state: VmState) -> None:
        self._seen_addresses[address].add(hash(state))

    def _is_local_address(self, address: int) -> bool:
        return self._func_addr <= address < self._func_addr + self._func_size

    def _is_save_rest_sub(self, address: int) -> bool:
        for sub in self._save_rest_subs:
            assert sub.size
            if sub.address <= address < sub.address + sub.size:
                return True
        return False

    def _create_dummy_subanalysis_result(self) -> InternalResult:
        return InternalResult(
            self._state_manager.type_registry,
            {},
            {},
            self._state_manager.type_registry.void(),
            {},
        )

    def _analyze_subcall(self, address: int) -> InternalResult:
        if address in self._subcalls:
            result = self._subcalls[address]
        else:
            subanalyzer = _FunctionAnalyzer(
                self._dol,
                address,
                self._symbol_map,
                self._save_rest_subs,
                self._max_depth - 1,
                self._breakpoints,
                self._state_manager.type_registry,
            )
            result = self._subcalls[address] = subanalyzer.analyze()

        return result

    def _on_pre_execute(self, event: VmPreExecuteEvent, state: VmState) -> VmSignal:
        curr_addr = event.pc
        thread_id = event.thread_id

        hashes = self._seen_addresses[curr_addr]

        if hash(state) in hashes:
            log_debug(f"Halting thread {thread_id} - repeated state", curr_addr)
            return VmSignal.HALT

        if event.instr.is_blr():
            log_debug(f"Halting thread {thread_id} - encountered return", curr_addr)
            self._state_manager.update_return_type(thread_id)
            return VmSignal.HALT

        self._update_address_record(curr_addr, state)
        self._thread_trace[thread_id].append(curr_addr)

        return VmSignal.CONTINUE

    def _on_post_execute(self, event: VmPostExecuteEvent, state: VmState) -> VmSignal:
        self._state_manager.process_instruction(event.thread_id, event.pc, event.instr)

        if self._did_call:
            subresult = self._subanalysis_result
            self._state_manager.apply_subanalysis_arguments(event.thread_id, subresult)
            self._state_manager.apply_post_call_state(event.thread_id)
            self._state_manager.apply_subanalysis_return_type(
                event.thread_id, subresult
            )
            self._did_call = False

        if self._did_tail_call:
            self._did_tail_call = False
            return VmSignal.HALT

        return VmSignal.CONTINUE

    def _on_read_reg(self, event: VmReadRegEvent, state: VmState) -> VmSignal:
        self._state_manager.register_read(event.thread_id, event.pc, event.reg)
        return VmSignal.CONTINUE

    def _on_write_reg(self, event: VmWriteRegEvent, state: VmState) -> VmSignal:
        self._state_manager.register_write(event.thread_id, event.pc, event.reg)
        return VmSignal.CONTINUE

    def _on_fork(self, event: VmForkEvent, state: VmState) -> VmSignal:
        parent_id = event.parent_id
        child_id = event.child_id

        self._state_manager.fork_thread(parent_id, child_id)
        self._thread_trace[child_id] = self._thread_trace[parent_id].copy()

        return VmSignal.CONTINUE

    def _on_branch(self, event: VmBranchEvent, state: VmState) -> VmSignal:
        assert not event.link

        thread_id = event.thread_id
        curr_addr = event.pc
        target_addr = event.target_addr.value

        hashes = self._seen_addresses[target_addr]
        if target_addr <= curr_addr and len(hashes) >= self._MAX_LOOP_ITERS:
            log_debug(
                f"Halting thread {thread_id} - potential infinite loop", curr_addr
            )
            return VmSignal.HALT

        return VmSignal.CONTINUE

    def _on_call(self, event: VmBranchEvent, state: VmState) -> VmSignal:
        target_addr = event.target_addr.value

        # Step over save/restore sub-routines; not relevant for analysis
        if self._is_save_rest_sub(target_addr):
            return VmSignal.STEP_OVER

        if not event.link:
            assert not self._is_local_address(target_addr)
            log_debug("Treating branch to out-of-function address as call", event.pc)
            self._did_tail_call = True

        if self._max_depth > 0:
            self._subanalysis_result = self._analyze_subcall(target_addr)
        else:
            self._subanalysis_result = self._create_dummy_subanalysis_result()
        self._did_call = True

        # TODO Centralize with tail call handling?
        return VmSignal.STEP_OVER

    def _on_branch_or_call(self, event: VmBranchEvent, state: VmState) -> VmSignal:
        if event.target_addr.is_unknown:
            return VmSignal.STEP_OVER if event.link else VmSignal.HALT

        target_addr = event.target_addr.value

        if not event.link and self._is_local_address(target_addr):
            return self._on_branch(event, state)

        return self._on_call(event, state)

    def _register_callbacks(self, vm: WiiVm) -> None:
        vm.register_callback(VmPreExecuteEvent, self._on_pre_execute)
        vm.register_callback(VmPostExecuteEvent, self._on_post_execute)
        vm.register_callback(VmReadRegEvent, self._on_read_reg)
        vm.register_callback(VmWriteRegEvent, self._on_write_reg)
        vm.register_callback(VmForkEvent, self._on_fork)
        vm.register_callback(VmBranchEvent, self._on_branch_or_call)

    def _attach_debugger(self, vm: WiiVm) -> None:
        debugger = Debugger(vm)
        for breakpoint in self._breakpoints:
            debugger.set_breakpoint(breakpoint)

    def _do_coverage_check(self) -> None:
        func_start = self._func_addr
        func_end = func_start + self._func_size
        for address in range(func_start, func_end, 4):
            if address not in self._seen_addresses:
                logging.warning(f"Address unreached by analysis: {address:#x}")

    def analyze(self) -> InternalResult:
        vm = WiiVm(self._dol)

        self._register_callbacks(vm)

        if len(self._breakpoints) > 0:
            self._attach_debugger(vm)

        # TODO Make explicit somewhere the fact 0 is the starting thread's ID?
        self._state_manager.init_thread(0)

        vm.run(self._func_addr, self._base_state)

        self._do_coverage_check()

        result = InternalResult(
            self._state_manager.type_registry,
            self._state_manager.found_args,
            self._state_manager.arg_graph,
            self._state_manager.return_type,
            self._subcalls,
        )

        return result


class DolAnalyzer:
    def __init__(
        self, dol: Dol, symbol_map: SymbolMap, breakpoints: set[int] | None = None
    ) -> None:
        self._dol = dol
        self._symbol_map = symbol_map
        self._breakpoints = breakpoints

        self._save_rest_subs = self._find_save_rest_subs()

    def _find_save_rest_subs(self) -> set[Symbol]:
        addresses: set[Symbol] = set()

        for name in {"__save_fpr", "__restore_fpr", "__save_gpr", "__restore_gpr"}:
            symbol = self._symbol_map.require_symbol(name)
            addresses.add(symbol)

        return addresses

    def _get_func_name(self, address: int) -> str:
        symbols = self._symbol_map.get_symbols_at(address)

        if len(symbols) == 0:
            logging.warning(f"No symbol exists at 0x{address:08X}; using default name")
            return f"fn_{address:08x}"

        if len(symbols) > 1:
            logging.warning(f"Multiple symbols exist at 0x{address:08X}; using first")

        return symbols[0].name

    def _build_result(
        self, address: int, internal_result: InternalResult
    ) -> AnalysisResult:
        def flatten_args(
            found_args: dict[int, int],
            arg_graph: dict[int, set[int]],
            registry: TypeRegistry,
        ) -> list[TypeInfo]:
            arguments: list[TypeInfo] = []
            sorter = TopologicalSorter(arg_graph)

            for arg_id in sorter.static_order():
                assert arg_id in found_args
                type_info = registry[found_args[arg_id]]
                arguments.append(type_info)

            return arguments

        def is_pseudo_struct(struct: StructType) -> bool:
            # TODO Something more robust
            return min(struct.fields) < 0

        def collect_structs(registry: TypeRegistry) -> list[StructType]:
            structs: list[StructType] = []

            i = 0
            for type in registry:
                if isinstance(type, StructType):
                    if not is_pseudo_struct(type):
                        type.name = f"UnkStruct_{i}"
                        structs.append(type)
                        i += 1

            return structs

        def build_subresults(
            subresults: dict[int, InternalResult],
        ) -> dict[int, AnalysisResult]:
            built = {
                addr: self._build_result(addr, subresult)
                for addr, subresult in subresults.items()
            }
            return built

        type_registry = internal_result.type_registry
        found_args = internal_result.found_args
        arg_graph = internal_result.arg_graph
        return_type_ref = internal_result.return_type
        subresults = internal_result.subcalls

        func_name = self._get_func_name(address)
        arguments = flatten_args(found_args, arg_graph, type_registry)
        return_type = type_registry[return_type_ref]
        structs = collect_structs(type_registry)
        subcalls = build_subresults(subresults)

        return AnalysisResult(
            func_name, type_registry, arguments, return_type, structs, subcalls
        )

    def analyze_function(self, address: int, max_depth: int = 0) -> AnalysisResult:
        func_analyzer = _FunctionAnalyzer(
            self._dol,
            address,
            self._symbol_map,
            self._save_rest_subs,
            max_depth,
            self._breakpoints,
        )
        internal_result = func_analyzer.analyze()
        return self._build_result(address, internal_result)

    # TODO Make use of this on an as-needed basis (move elsewhere?)
    # def _find_init_reg_state(self):
    #     r1 = r2 = r13 = SymbolicValue.Unknown

    #     def on_pre_execute(event: VmEvent, state: VmState) -> VmSignal:
    #         nonlocal r1, r2, r13

    #         if event.instr.is_blr():
    #             r1 = state.read_reg(PpcReg.GPR1)
    #             r2 = state.read_reg(PpcReg.GPR2)
    #             r13 = state.read_reg(PpcReg.GPR13)
    #             return VmSignal.HALT

    #         return VmSignal.CONTINUE

    #     __init_registers = self._require_symbol("__init_registers")

    #     vm = WiiVm(self._dol)
    #     vm.register_callback(VmPreExecuteEvent, on_pre_execute)
    #     vm.run(__init_registers.address)

    #     if r1.is_unknown or r2.is_unknown or r13.is_unknown:
    #         logging.warning(
    #             "Failed to determine initial state of one or more registers"
    #         )

    #     return r1, r2, r13
