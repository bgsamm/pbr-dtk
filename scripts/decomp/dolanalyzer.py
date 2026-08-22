from dataclasses import dataclass
from graphlib import TopologicalSorter
from typing import Sequence
from dtk.symbols import Symbol, SymbolMap
from ppc import PpcReg
from rvl import Dol
from symval import SymbolicValue
from typealiases import *
from vm import VmState, WiiVm
from vm.event import *
from .funcanalyzer import AnalysisError, FunctionAnalyzer, InternalResult
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
        analyzer = FunctionAnalyzer(
            self._dol,
            address,
            self._base_state,
            self._save_rest_subs,
            max_depth,
            self._breakpoints,
        )
        internal_result = analyzer.analyze()
        return self._build_result(address, internal_result)
