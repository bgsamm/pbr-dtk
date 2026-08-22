from collections import defaultdict
from dataclasses import dataclass
from graphlib import TopologicalSorter
from typing import Sequence
from dtk.symbols import Symbol, SymbolMap
from ppc import PpcInstr, PpcReg
from rvl import Dol
from symval import SymbolicValue
from typealiases import *
from vm import VmState, WiiVm
from vm.event import *
from .debugger import Debugger
from .typeinfo import *
from .typereg import TypeRegistry
import logging
import ppc

# TODO Decouple this module from Debugger?


class AnalysisError(Exception):
    pass


@dataclass
class _InternalResult:
    type_registry: TypeRegistry
    found_args: dict[int, int]
    arg_graph: dict[int, set[int]]
    return_type: int
    subcalls: dict[int, _InternalResult]


@dataclass(frozen=True)
class AnalysisResult:
    func_name: str
    type_registry: TypeRegistry
    arguments: Sequence[TypeInfo]
    return_type: TypeInfo
    structs: Sequence[StructType]
    subcalls: dict[int, AnalysisResult]


class _ShadowState:
    _reg_access_flags: dict[PpcReg, bool]
    _reg_modify_flags: dict[PpcReg, bool]
    _reg_type_refs: dict[PpcReg, int]

    def __init__(self) -> None:
        self._reg_access_flags = {reg: False for reg in PpcReg}
        self._reg_modify_flags = {reg: False for reg in PpcReg}
        self._reg_type_refs = {}

    def is_reg_accessed(self, reg: PpcReg) -> bool:
        return self._reg_access_flags[reg]

    def mark_reg_accessed(self, reg: PpcReg) -> None:
        self._reg_access_flags[reg] = True

    def mark_reg_unaccessed(self, reg: PpcReg) -> None:
        self._reg_access_flags[reg] = False

    def is_reg_modified(self, reg: PpcReg) -> bool:
        return self._reg_modify_flags[reg]

    def mark_reg_modified(self, reg: PpcReg) -> None:
        self._reg_modify_flags[reg] = True

    def mark_reg_unmodified(self, reg: PpcReg) -> None:
        self._reg_modify_flags[reg] = False

    def get_reg_type_ref(self, reg: PpcReg) -> int | None:
        return self._reg_type_refs.get(reg)

    def set_reg_type_ref(self, reg: PpcReg, type_ref: int) -> None:
        self._reg_type_refs[reg] = type_ref

    def copy(self) -> _ShadowState:
        new_state = _ShadowState()
        new_state._reg_type_refs = self._reg_type_refs.copy()
        new_state._reg_access_flags = self._reg_access_flags.copy()
        new_state._reg_modify_flags = self._reg_modify_flags.copy()
        return new_state


class _FunctionAnalyzer:
    _DEDICATED_REGISTERS = {PpcReg.GPR1, PpcReg.GPR2, PpcReg.GPR13}
    # TODO Handle 64-bit types properly, since one value is split across two registers
    # r3 used for integer/pointer returns
    # r4 used w/ r3 for 64-bit returns
    # f1 used for floating-point returns
    _RETURN_REGISTERS = {PpcReg.GPR3, PpcReg.GPR4, PpcReg.FPR1}

    _seen_addresses: set[int]

    _subcalls: dict[int, _InternalResult]

    _thread_map: dict[int, _ShadowState]
    """A mapping from thread ID to shadow state"""

    _thread_trace: dict[int, list[int]]
    """A mapping from thread ID to addresses visited by that thread"""

    _found_args: dict[int, int]
    """A mapping from argument ID (e.g. PpcReg value) to type ID"""

    _arg_graph: dict[int, set[int]]
    """A mapping from argument ID to known predecessors"""

    _pseudo_structs: set[int]
    """A collection of type IDs for pseudo-structs, like the stack"""

    _modified_regs: set[PpcReg]
    _subanalysis_result: _InternalResult | None

    def __init__(
        self,
        dol: Dol,
        func_address: int,
        init_state: VmState,
        save_rest_subs: set[Symbol],
        max_depth: int = 0,
        breakpoints: set[int] | None = None,
        type_registry: TypeRegistry | None = None,
    ):
        self._dol = dol
        self._func_address = func_address
        self._init_state = init_state
        self._save_rest_subs = save_rest_subs
        self._max_depth = max_depth
        self._breakpoints = breakpoints or set()

        self._type_registry = type_registry or TypeRegistry()

        self._seen_addresses = set()
        self._subcalls = {}
        self._thread_map = defaultdict(_ShadowState)
        self._thread_trace = defaultdict(list)
        self._found_args = {}
        self._arg_graph = defaultdict(set)
        self._return_type = self._create_void_type()
        self._pseudo_structs = set()

        self._modified_regs = set()
        self._did_call = False
        self._subanalysis_result = None

    def _make_log_message(self, msg: str, pc: int) -> str:
        return f"{msg} (pc=0x{pc:X})"

    def _log_debug(self, msg: str, pc: int) -> None:
        message = self._make_log_message(msg, pc)
        logging.debug(message)

    def _log_info(self, msg: str, pc: int) -> None:
        message = self._make_log_message(msg, pc)
        logging.info(message)

    def _log_warning(self, msg: str, pc: int) -> None:
        message = self._make_log_message(msg, pc)
        logging.warning(message)

    def _log_error(self, msg: str, pc: int) -> None:
        message = self._make_log_message(msg, pc)
        logging.error(message)

    def _is_argument_reg(self, reg: PpcReg) -> bool:
        return PpcReg.GPR3 <= reg <= PpcReg.GPR10 or PpcReg.FPR1 <= reg <= PpcReg.FPR8

    def _is_dedicated_reg(self, reg: PpcReg) -> bool:
        return reg in self._DEDICATED_REGISTERS

    def _in_save_rest_sub(self, addr: int) -> bool:
        for sub in self._save_rest_subs:
            assert sub.size is not None
            if sub.address <= addr < sub.address + sub.size:
                return True
        return False

    def _create_void_type(self) -> int:
        return self._type_registry.add(VoidType())

    def _create_numeric_type(self, dtype: ctype) -> int:
        return self._type_registry.add(NumericType(dtype))

    def _create_pointer_type(self, target: int) -> int:
        return self._type_registry.add(PointerType(target))

    def _create_struct_type(self, fields: dict[int, int]) -> int:
        return self._type_registry.add(StructType(fields))

    def _ensure_reg_type(self, state: _ShadowState, reg: PpcReg) -> int:
        type_ref = state.get_reg_type_ref(reg)

        if type_ref is None:
            type_ref = self._create_void_type()
            state.set_reg_type_ref(reg, type_ref)

        return type_ref

    def _add_argument(self, shadow: _ShadowState, arg_id: int, type_ref: int) -> None:
        # TODO Handle stack args
        assert arg_id in PpcReg

        arg_reg = PpcReg(arg_id)

        if arg_type_ref := self._found_args.get(arg_id):
            arg_type_ref = self._type_registry.unify(arg_type_ref, type_ref)
        else:
            arg_type_ref = self._found_args[arg_id] = type_ref

        # Ensure argument type is not void
        arg_type = self._type_registry[arg_type_ref]
        if isinstance(arg_type, VoidType):
            type_ref = self._create_numeric_type(u32 if arg_reg.is_gpr() else f32)
            arg_type_ref = self._type_registry.unify(arg_type_ref, type_ref)

        # Ensure arg has entry in arg graph
        self._arg_graph.setdefault(arg_id, set())

        assert self._is_argument_reg(arg_reg)

        # Mark all preceding argument registers as arguments & add to predecessors
        start = PpcReg.GPR3 if arg_reg.is_gpr() else PpcReg.FPR1
        for reg in range(start, arg_reg):
            if reg not in self._found_args:
                type_ref = self._ensure_reg_type(shadow, PpcReg(reg))
                self._add_argument(shadow, reg, type_ref)
            self._arg_graph[arg_reg].add(reg)

    def _update_types(self, shadow: _ShadowState, pc: int, instr: PpcInstr) -> bool:
        # TODO Refactor this function
        if instr.is_move():
            src_reg = instr.gpr_field(6, 10)
            dst_reg = instr.gpr_field(11, 15)

            src_ref = self._ensure_reg_type(shadow, src_reg)
            shadow.set_reg_type_ref(dst_reg, src_ref)
            return True
        elif instr.is_load() or instr.is_store():
            # TODO Properly handle store/load-with-update
            data_reg = instr.gpr_field(6, 10)
            base_reg = instr.gpr_field(11, 15)
            offset = instr.simm_field(16, 31)

            dtype = ppc.get_load_store_type(instr.op)
            data_type = self._create_numeric_type(dtype)

            base_ref = self._ensure_reg_type(shadow, base_reg)
            if instr.is_load():
                shadow.set_reg_type_ref(data_reg, data_type)
                data_ref = data_type
            else:
                data_ref = self._ensure_reg_type(shadow, data_reg)

            data_ref = self._type_registry.unify(data_ref, data_type)

            # Base register for load/store -> struct or array
            if offset == 0:
                # Assume simple pointer if offset is 0
                pointer_ref = self._create_pointer_type(data_type)
                base_ref = self._type_registry.unify(base_ref, pointer_ref)
            else:
                if offset < 0 and not self._is_dedicated_reg(base_reg):
                    # TODO Some way to avoid this special case?
                    if not self._in_save_rest_sub(pc):
                        self._log_warning(f"Negative offset used with {base_reg}", pc)
                # Assume pointer-to-struct otherwise
                struct_ref = self._create_struct_type({offset: data_type})
                pointer_ref = self._create_pointer_type(struct_ref)
                base_ref = self._type_registry.unify(base_ref, pointer_ref)

            base_type = self._type_registry[base_ref]

            if not isinstance(base_type, PointerType):
                message = self._make_log_message(
                    "Base register of load/store is not a pointer type after unifying",
                    pc,
                )
                raise AnalysisError(message)

            target_type = self._type_registry[base_type.target]

            if isinstance(target_type, StructType):
                self._type_registry.add_struct_field(target_type, offset, data_ref)
            else:
                assert offset == 0
                base_type.target = self._type_registry.unify(base_type.target, data_ref)

            return True
        return False

    def _update_return_type(self, shadow: _ShadowState) -> None:
        def maybe_has_return_value(reg: PpcReg) -> bool:
            return shadow.is_reg_modified(reg) and not shadow.is_reg_accessed(reg)

        for reg in self._RETURN_REGISTERS:
            if maybe_has_return_value(reg):
                type_ref = self._ensure_reg_type(shadow, reg)
                self._return_type = self._type_registry.unify(
                    self._return_type, type_ref
                )

    def _apply_subanalysis_result(
        self, shadow: _ShadowState, result: _InternalResult
    ) -> None:
        # Unify argument types
        for arg_id, sub_type_ref in result.found_args.items():
            # TODO Handle stack args
            assert arg_id in PpcReg

            reg = PpcReg(arg_id)

            type_ref = self._ensure_reg_type(shadow, reg)
            type_ref = self._type_registry.unify(type_ref, sub_type_ref)

            # Mark any unmodified input registers as arguments to outer call
            if not shadow.is_reg_modified(reg):
                self._add_argument(shadow, reg, type_ref)

        # TODO Add any modified-but-unaccessed input registers as arguments to inner call?

        # Since the subanalysis may not have identified a return type,
        # mark all possible return registers with return type
        for reg in self._RETURN_REGISTERS:
            shadow.set_reg_type_ref(reg, result.return_type)

    def _handle_post_call(self, shadow: _ShadowState) -> None:
        if self._subanalysis_result:
            # Apply subanalysis result, if any
            self._apply_subanalysis_result(shadow, self._subanalysis_result)
            self._subanalysis_result = None
        else:
            # Otherwise, reset the types of return registers to void
            for reg in self._RETURN_REGISTERS:
                shadow.set_reg_type_ref(reg, self._create_void_type())

        for reg in PpcReg:
            # Mark volatile registers as modified but unaccessed after calls
            if reg.is_volatile():
                shadow.mark_reg_unaccessed(reg)
                shadow.mark_reg_modified(reg)

    def _analyze_subcall(self, address: int) -> _InternalResult:
        if address in self._subcalls:
            result = self._subcalls[address]
        else:
            subanalyzer = _FunctionAnalyzer(
                self._dol,
                address,
                self._init_state,
                self._save_rest_subs,
                self._max_depth - 1,
                self._breakpoints,
                self._type_registry,
            )
            result = self._subcalls[address] = subanalyzer.analyze()

        return result

    def _on_pre_execute(self, event: VmPreExecuteEvent, state: VmState) -> VmSignal:
        curr_addr = event.pc
        thread_id = event.thread_id

        if curr_addr in self._seen_addresses:
            return VmSignal.HALT

        shadow_state = self._thread_map[thread_id]

        if event.instr.is_blr() and not self._in_save_rest_sub(curr_addr):
            self._update_return_type(shadow_state)
            return VmSignal.HALT

        self._seen_addresses.add(curr_addr)
        self._thread_trace[thread_id].append(curr_addr)

        return VmSignal.CONTINUE

    def _on_post_execute(self, event: VmPostExecuteEvent, state: VmState) -> VmSignal:
        shadow_state = self._thread_map[event.thread_id]

        handled = self._update_types(shadow_state, event.pc, event.instr)
        if not handled:
            # Automatically reset modified register types for unhandled instructions
            for reg in self._modified_regs:
                shadow_state.set_reg_type_ref(reg, self._create_void_type())
        self._modified_regs.clear()

        if self._did_call:
            self._handle_post_call(shadow_state)
            self._did_call = False

        return VmSignal.CONTINUE

    def _on_read_reg(self, event: VmReadRegEvent, state: VmState) -> VmSignal:
        reg = event.reg
        shadow = self._thread_map[event.thread_id]

        # Record argument after uninitialized read
        if not shadow.is_reg_modified(reg):
            if self._is_argument_reg(reg):
                self._log_debug(
                    f"Unmodified read of {reg}; marking as argument", event.pc
                )
                type_ref = self._ensure_reg_type(shadow, reg)
                self._add_argument(shadow, reg, type_ref)
            elif (reg.is_gpr() or reg.is_fpr()) and reg.is_volatile():
                self._log_warning(
                    f"Unexpected unmodified read of {reg}; not an argument register",
                    event.pc,
                )

        shadow.mark_reg_accessed(reg)

        return VmSignal.CONTINUE

    def _on_write_reg(self, event: VmWriteRegEvent, state: VmState) -> VmSignal:
        shadow = self._thread_map[event.thread_id]
        shadow.mark_reg_modified(event.reg)
        self._modified_regs.add(event.reg)
        return VmSignal.CONTINUE

    def _on_fork(self, event: VmForkEvent, state: VmState) -> VmSignal:
        parent_id = event.parent_id
        child_id = event.child_id

        parent_shadow = self._thread_map[parent_id]
        self._thread_map[child_id] = parent_shadow.copy()
        self._thread_trace[child_id] = self._thread_trace[parent_id].copy()

        return VmSignal.CONTINUE

    def _on_call(self, event: VmCallEvent, state: VmState) -> VmSignal:
        if not event.target_addr.is_known:
            return VmSignal.STEP_OVER

        target_addr = event.target_addr.value

        if self._in_save_rest_sub(target_addr):
            # Don't treat save/restore subroutines as calls
            return VmSignal.CONTINUE

        if self._max_depth > 0:
            self._subanalysis_result = self._analyze_subcall(target_addr)
        self._did_call = True

        return VmSignal.STEP_OVER

    def _register_callbacks(self, vm: WiiVm) -> None:
        vm.register_callback(VmPreExecuteEvent, self._on_pre_execute)
        vm.register_callback(VmPostExecuteEvent, self._on_post_execute)
        vm.register_callback(VmReadRegEvent, self._on_read_reg)
        vm.register_callback(VmWriteRegEvent, self._on_write_reg)
        vm.register_callback(VmForkEvent, self._on_fork)
        vm.register_callback(VmCallEvent, self._on_call)

    def _attach_debugger(self, vm: WiiVm) -> None:
        debugger = Debugger(vm)
        for breakpoint in self._breakpoints:
            debugger.set_breakpoint(breakpoint)

    def analyze(self) -> _InternalResult:
        # Initialize shadow state for starting thread
        # TODO Make explicit somewhere the fact 0 is the starting thread's ID?
        start_state = self._thread_map[0] = _ShadowState()

        # Type all registers at the start so branches don't end up
        # creating separate types for the same register value
        for reg in PpcReg:
            if reg.is_gpr() or reg.is_fpr():
                type_ref = self._ensure_reg_type(start_state, reg)
                if self._is_dedicated_reg(reg):
                    self._pseudo_structs.add(type_ref)

        vm = WiiVm(self._dol)

        self._register_callbacks(vm)

        if len(self._breakpoints) > 0:
            self._attach_debugger(vm)

        vm.run(self._func_address, self._init_state)

        result = _InternalResult(
            self._type_registry,
            self._found_args,
            self._arg_graph,
            self._return_type,
            self._subcalls,
        )

        return result


class DolAnalyzer:
    _breakpoints: set[int]
    _save_rest_subs: set[Symbol]

    def __init__(
        self, dol: Dol, symbol_map: SymbolMap, breakpoints: set[int] | None = None
    ):
        self._dol = dol
        self._symbol_map = symbol_map
        self._breakpoints = breakpoints or set()

        r1, r2, r13 = self._find_init_reg_state()
        self._base_state = VmState(
            {
                PpcReg.GPR1: r1,
                PpcReg.GPR2: r2,
                PpcReg.GPR13: r13,
                PpcReg.CR: 0,
                PpcReg.XER: 0,
            }
        )

        self._save_rest_subs = self._find_save_rest_subs()

    def _require_symbol(self, name: str) -> Symbol:
        symbols = self._symbol_map.get_by_name(name)

        if len(symbols) == 0:
            raise AnalysisError(f"No symbol named {name}")
        if len(symbols) > 1:
            raise AnalysisError(f"Multiple symbols named {name}")

        return symbols[0]

    def _find_save_rest_subs(self) -> set[Symbol]:
        addresses: set[Symbol] = set()

        for name in {"__save_fpr", "__restore_fpr", "__save_gpr", "__restore_gpr"}:
            symbol = self._require_symbol(name)
            addresses.add(symbol)

        return addresses

    def _find_init_reg_state(self):
        r1 = r2 = r13 = SymbolicValue.Unknown

        def on_pre_execute(event: VmEvent, state: VmState) -> VmSignal:
            nonlocal r1, r2, r13

            if event.instr.is_blr():
                r1 = state.read_reg(PpcReg.GPR1)
                r2 = state.read_reg(PpcReg.GPR2)
                r13 = state.read_reg(PpcReg.GPR13)
                return VmSignal.HALT

            return VmSignal.CONTINUE

        __init_registers = self._require_symbol("__init_registers")

        vm = WiiVm(self._dol)
        vm.register_callback(VmPreExecuteEvent, on_pre_execute)
        vm.run(__init_registers.address)

        if r1.is_unknown or r2.is_unknown or r13.is_unknown:
            logging.warning(
                "Failed to determine initial state of one or more registers"
            )

        return r1, r2, r13

    def _get_func_name(self, address: int) -> str:
        symbols = self._symbol_map.get_by_address(address)

        if len(symbols) == 0:
            logging.warning(f"No symbol exists at 0x{address:08X}; using default name")
            return f"fn_{address:08x}"

        if len(symbols) > 1:
            logging.warning(f"Multiple symbols exist at 0x{address:08X}; using first")

        return symbols[0].name

    def _build_result(
        self, address: int, internal_result: _InternalResult
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
            subresults: dict[int, _InternalResult],
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
        analyzer = _FunctionAnalyzer(
            self._dol,
            address,
            self._base_state,
            self._save_rest_subs,
            max_depth,
            self._breakpoints,
        )
        internal_result = analyzer.analyze()
        return self._build_result(address, internal_result)
