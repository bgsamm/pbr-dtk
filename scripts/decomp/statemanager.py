from collections import defaultdict
from dataclasses import dataclass
from ppc import PpcInstr, PpcOp, PpcReg
from typealiases import f32, u32
from vm.event import *
from .common import *
from .typeinfo import *
from .typereg import TypeRegistry
import ppc


@dataclass
class InternalResult:
    type_registry: TypeRegistry
    found_args: dict[int, int]
    arg_graph: dict[int, set[int]]
    return_type: int
    subcalls: dict[int, InternalResult]


class ShadowState:
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

    def copy(self) -> ShadowState:
        new_state = ShadowState()
        new_state._reg_type_refs = self._reg_type_refs.copy()
        new_state._reg_access_flags = self._reg_access_flags.copy()
        new_state._reg_modify_flags = self._reg_modify_flags.copy()
        return new_state


class StateManager:
    _DEDICATED_REGISTERS = {PpcReg.GPR1, PpcReg.GPR2, PpcReg.GPR13}
    # TODO Handle 64-bit types properly, since one value is split across two registers
    # r3 used for integer/pointer returns
    # r4 used w/ r3 for 64-bit returns
    # f1 used for floating-point returns
    _RETURN_REGISTERS = {PpcReg.GPR3, PpcReg.GPR4, PpcReg.FPR1}

    _thread_map: dict[int, ShadowState]
    """A mapping from thread ID to shadow state"""

    found_args: dict[int, int]
    """A mapping from argument ID (e.g. PpcReg value) to type ID"""

    arg_graph: dict[int, set[int]]
    """A mapping from argument ID to known predecessors"""

    _modified_regs: set[PpcReg]

    def __init__(
        self,
        type_registry: TypeRegistry | None = None,
    ):
        self.type_registry = type_registry or TypeRegistry()

        self._thread_map = {}
        self.found_args = {}
        self.arg_graph = defaultdict(set)
        self.return_type = self.type_registry.void()

        self._modified_regs = set()

    def _is_argument_reg(self, reg: PpcReg) -> bool:
        return PpcReg.GPR3 <= reg <= PpcReg.GPR10 or PpcReg.FPR1 <= reg <= PpcReg.FPR8

    def _is_return_reg(self, reg: PpcReg) -> bool:
        return reg in self._RETURN_REGISTERS

    def _is_dedicated_reg(self, reg: PpcReg) -> bool:
        return reg in self._DEDICATED_REGISTERS

    def _ensure_reg_type(self, state: ShadowState, reg: PpcReg) -> int:
        type_ref = state.get_reg_type_ref(reg)

        if type_ref is None:
            type_ref = self.type_registry.void()
            state.set_reg_type_ref(reg, type_ref)

        return type_ref

    def _add_argument(self, shadow: ShadowState, arg_id: int, type_ref: int) -> None:
        # TODO Handle stack args
        assert arg_id in PpcReg

        arg_reg = PpcReg(arg_id)

        if arg_type_ref := self.found_args.get(arg_id):
            arg_type_ref = self.type_registry.unify(arg_type_ref, type_ref)
        else:
            arg_type_ref = self.found_args[arg_id] = type_ref

        # Ensure argument type is not void
        arg_type = self.type_registry[arg_type_ref]
        if isinstance(arg_type, VoidType):
            type_ref = self.type_registry.numeric(u32 if arg_reg.is_gpr() else f32)
            arg_type_ref = self.type_registry.unify(arg_type_ref, type_ref)

        # Ensure arg has entry in arg graph
        self.arg_graph.setdefault(arg_id, set())

        assert self._is_argument_reg(arg_reg)

        # Mark all preceding argument registers as arguments & add to predecessors
        start = PpcReg.GPR3 if arg_reg.is_gpr() else PpcReg.FPR1
        for reg in range(start, arg_reg):
            if reg not in self.found_args:
                type_ref = self._ensure_reg_type(shadow, PpcReg(reg))
                self._add_argument(shadow, reg, type_ref)
            self.arg_graph[arg_reg].add(reg)

    # TODO exec.py already parses the instruction fields; shouldn't have to reparse them

    def _handle_move(self, shadow: ShadowState, pc: int, instr: PpcInstr) -> None:
        src_reg = instr.gpr_field(6, 10)
        dst_reg = instr.gpr_field(11, 15)

        src_ref = self._ensure_reg_type(shadow, src_reg)
        shadow.set_reg_type_ref(dst_reg, src_ref)

    # def _handle_addi(self, shadow: ShadowState, pc: int, instr: PpcInstr) -> None:
    #     dst_reg = instr.gpr_field(6, 10)
    #     src_reg = instr.gpr_field(11, 15)
    #     value = instr.simm_field(16, 31)

    #     value_type_ref = self.type_registry.numeric(u32)

    #     if src_reg == PpcReg.GPR0:  # li
    #         shadow.set_reg_type_ref(dst_reg, value_type_ref)
    #         return

    #     src_type_ref = self._ensure_reg_type(shadow, src_reg)
    #     src_type = self.type_registry[src_type_ref]

    #     match src_type:
    #         case VoidType() | NumericType():
    #             src_type_ref = self.type_registry.unify(src_type_ref, value_type_ref)
    #         case PointerType():
    #             target_type = self.type_registry[src_type.target]
    #             if value <= 4:
    #                 # Assume simple data pointer
    #             else:
    #                 # Assume struct pointer
    #         case _:
    #             raise TypeError()

    #     shadow.set_reg_type_ref(dst_reg, src_type_ref)

    # TODO Refactor this function
    def _handle_load_store(self, shadow: ShadowState, pc: int, instr: PpcInstr) -> None:
        # TODO Properly handle store/load-with-update
        data_reg = instr.gpr_field(6, 10)
        base_reg = instr.gpr_field(11, 15)
        offset = instr.simm_field(16, 31)

        dtype = ppc.get_load_store_type(instr.op)
        data_type = self.type_registry.numeric(dtype)

        base_ref = self._ensure_reg_type(shadow, base_reg)
        if instr.is_load():
            shadow.set_reg_type_ref(data_reg, data_type)
            data_ref = data_type
        else:
            data_ref = self._ensure_reg_type(shadow, data_reg)

        data_ref = self.type_registry.unify(data_ref, data_type)

        # Base register for load/store -> struct or array
        if offset == 0:
            # Assume simple pointer if offset is 0
            type_ref = self.type_registry.pointer(data_type)
            base_ref = self.type_registry.unify(base_ref, type_ref)
        else:
            if offset < 0 and not self._is_dedicated_reg(base_reg):
                log_warning(f"Negative offset used with {base_reg}", pc)
            # Assume pointer-to-struct otherwise
            type_ref = self.type_registry.struct_pointer({offset: data_type})
            base_ref = self.type_registry.unify(base_ref, type_ref)

        base_type = self.type_registry[base_ref]

        assert isinstance(base_type, PointerType)

        target_type = self.type_registry[base_type.target]

        if isinstance(target_type, StructType):
            self.type_registry.add_struct_field(target_type, offset, data_ref)
        else:
            assert offset == 0
            base_type.target = self.type_registry.unify(base_type.target, data_ref)

    def _update_types(self, shadow: ShadowState, pc: int, instr: PpcInstr) -> bool:
        if instr.is_move():
            self._handle_move(shadow, pc, instr)
        # elif instr.op == PpcOp.ADDI:
        #     self._handle_addi(shadow, pc, instr)
        elif instr.is_load() or instr.is_store():
            self._handle_load_store(shadow, pc, instr)
        else:
            return False
        return True

    def init_thread(self, thread_id: int) -> None:
        start_state = self._thread_map[thread_id] = ShadowState()

        # Type all registers at the start so branches don't end up
        # creating separate types for the same register value
        for reg in PpcReg:
            if reg.is_gpr() or reg.is_fpr():
                self._ensure_reg_type(start_state, reg)

    def fork_thread(self, parent_id: int, child_id: int) -> None:
        parent_shadow = self._thread_map[parent_id]
        self._thread_map[child_id] = parent_shadow.copy()

    def register_read(self, thread_id: int, pc: int, reg: PpcReg) -> None:
        shadow = self._thread_map[thread_id]

        # Record argument after uninitialized read
        if not shadow.is_reg_modified(reg):
            if self._is_argument_reg(reg):
                if reg not in self.found_args:
                    log_debug(f"Unmodified read of {reg}; marking as argument", pc)
                type_ref = self._ensure_reg_type(shadow, reg)
                self._add_argument(shadow, reg, type_ref)
            elif (reg.is_gpr() or reg.is_fpr()) and reg.is_volatile():
                log_warning(
                    f"Unexpected unmodified read of {reg}; not an argument register",
                    pc,
                )

        shadow.mark_reg_accessed(reg)

    def register_write(self, thread_id: int, pc: int, reg: PpcReg) -> None:
        shadow = self._thread_map[thread_id]
        shadow.mark_reg_modified(reg)
        self._modified_regs.add(reg)

    def process_instruction(self, thread_id: int, pc: int, instr: PpcInstr) -> None:
        shadow = self._thread_map[thread_id]
        handled = self._update_types(shadow, pc, instr)
        if not handled:
            # Automatically reset modified register types for unhandled instructions
            for reg in self._modified_regs:
                shadow.set_reg_type_ref(reg, self.type_registry.void())
        self._modified_regs.clear()

    def apply_subanalysis_arguments(
        self, thread_id: int, result: InternalResult
    ) -> None:
        shadow = self._thread_map[thread_id]
        # Unify argument types
        for arg_id, sub_type_ref in result.found_args.items():
            # TODO Handle stack args
            assert arg_id in PpcReg

            reg = PpcReg(arg_id)

            type_ref = self._ensure_reg_type(shadow, reg)
            type_ref = self.type_registry.unify(type_ref, sub_type_ref)

            # Mark any unmodified input registers as arguments to outer call
            if not shadow.is_reg_modified(reg):
                self._add_argument(shadow, reg, type_ref)

        # TODO Add any modified-but-unaccessed input registers as arguments to inner call?

    def apply_subanalysis_return_type(
        self, thread_id: int, result: InternalResult
    ) -> None:
        shadow = self._thread_map[thread_id]
        # Since the subanalysis may not have identified a return type,
        # mark all possible return registers with return type
        for reg in self._RETURN_REGISTERS:
            shadow.set_reg_type_ref(reg, result.return_type)

    def apply_post_call_state(self, thread_id: int) -> None:
        shadow = self._thread_map[thread_id]
        for reg in PpcReg:
            # Mark volatile registers as modified but unaccessed after calls
            if reg.is_volatile():
                shadow.mark_reg_unaccessed(reg)
                shadow.mark_reg_modified(reg)
            # Reset return register types to void
            if self._is_return_reg(reg):
                shadow.set_reg_type_ref(reg, self.type_registry.void())

    def update_return_type(self, thread_id: int) -> None:
        shadow = self._thread_map[thread_id]

        def maybe_has_return_value(reg: PpcReg) -> bool:
            return shadow.is_reg_modified(reg) and not shadow.is_reg_accessed(reg)

        for reg in self._RETURN_REGISTERS:
            if maybe_has_return_value(reg):
                type_ref = self._ensure_reg_type(shadow, reg)
                self.return_type = self.type_registry.unify(self.return_type, type_ref)
