from dataclasses import dataclass, field
from dtk.symbols import SymbolMap
from rvl import Dol
from rvl.types import *
from vm import (
    SymbolicValue,
    SymOrInt,
    VmInstr,
    VmOp,
    VmOpType,
    VmReg,
    VmThread,
    WiiVm
)
from .typeinfo import (
    TypeInfo,
    NumericType,
    PointerType,
    StructType
)
import logging

type RegStateDict = dict[VmReg, SymOrInt]

@dataclass
class AnalysisResult:
    found_structs: list[StructType] = field(default_factory=list)
    parameters: list[TypeInfo] = field(default_factory=list)

class DolAnalyzer:
    def __init__(self, dol: Dol, symbol_map: SymbolMap):
        self._dol = dol
        self._dol.apply_symbol_map(symbol_map)
        self._vm = WiiVm(dol)

        r1, r2, r13 = self._find_init_reg_state()
        self._base_state = { VmReg.GPR1: r1, VmReg.GPR2: r2, VmReg.GPR13: r13,
                             VmReg.CR: 0, VmReg.XER: 0 }

        self._save_rest_subs = self._find_save_rest_subs()

    def _find_save_rest_subs(self) -> set[int]:
        save_rest_subs = set()

        for name in { 'savegpr', 'restgpr', 'savefpr', 'restfpr' }:
            for i in range(14, 31 + 1):
                sym_name = f'_{name}_{i}'
                syms = self._dol.get_symbols_named(sym_name)

                if len(syms) == 0:
                    logging.warning(f'Could not find {sym_name}!')
                    continue

                if len(syms) > 1:
                    logging.warning(f'Multiple symbols named {sym_name}! Using first')

                save_rest_subs.add(syms[0].address)

        return save_rest_subs

    def _find_init_reg_state(self):
        r1 = r2 = r13 = SymbolicValue.Unknown

        def thread_callback(thread: VmThread, op: VmOp):
            nonlocal r1, r2, r13

            instr = thread.get_current_instruction()

            if instr.is_blr():
                r1 = thread.read_reg(VmReg.GPR1)
                r2 = thread.read_reg(VmReg.GPR2)
                r13 = thread.read_reg(VmReg.GPR13)
                return VmThread.HALT

            return VmThread.CONTINUE

        symbols = self._dol.get_symbols_named('__init_registers')

        if len(symbols) == 0:
            logging.warning('No symbol for __init_registers')
        else:
            __init_registers = symbols[0]

            # self._vm.set_breakpoint(0x80006304)
            self._vm.run(entry_point=__init_registers.address,
                         callback=thread_callback)

        if r1.is_unknown or r2.is_unknown or r13.is_unknown:
            logging.warning('Failed to determine initial state of one or more registers')

        return r1, r2, r13

    def analyze_function(self, address: int) -> AnalysisResult:
        def is_arg_reg(reg):
            return VmReg.GPR3 <= reg <= VmReg.GPR10 or VmReg.FPR1 <= reg <= VmReg.FPR8
    
        args: dict[VmReg, TypeInfo] = {}
        uninited_regs = set(reg for reg in VmReg if is_arg_reg(reg))
    
        def ensure_args_up_to(arg_reg: VmReg):
            if arg_reg.is_gpr():
                for reg in range(VmReg.GPR3, arg_reg + 1):
                    args.setdefault(VmReg(reg), NumericType(u32))
            elif arg_reg.is_fpr():
                for reg in range(VmReg.FPR1, arg_reg + 1):
                    args.setdefault(VmReg(reg), NumericType(f32))
    
        def update_arg_type(op_reg: VmReg, arg_reg: VmReg, instr: VmInstr):
            ensure_args_up_to(arg_reg)
    
            if instr.is_load() or instr.is_store():
                data_reg = instr.gpr_field(6, 10)
                base_reg = instr.gpr_field(11, 15)
                offset = instr.simm_field(16, 31)
                dtype = VmInstr.loadstore_type(instr)
    
                # Base register for load/store -> probable struct
                if op_reg == base_reg:
                    type_info = args[arg_reg]
                    if not isinstance(type_info, StructType):
                        type_info = args[arg_reg] = StructType()
                    type_info.add_field(offset, dtype)
    
                if op_reg == data_reg:
                    # TODO Something more robust
                    if isinstance(args[arg_reg], NumericType):
                        args[arg_reg] = NumericType(dtype)
    
        def thread_callback(thread: VmThread, op: VmOp):
            if thread.is_at_seen_address():
                return VmThread.HALT
    
            # Clear uninitialized registers after calls
            if op.type == VmOpType.CALL and op.addr not in self._save_rest_subs:
                uninited_regs.clear()
    
            # Remove from uninitialized registers after write
            if op.type == VmOpType.WRITE_REG and op.reg in uninited_regs:
                uninited_regs.remove(op.reg)
    
            # Tag as argument after uninitialized read
            if op.type == VmOpType.READ_REG and op.reg in uninited_regs:
                logging.debug(hex(thread.get_pc().value), op.reg.name)
                thread.tag_register(op.reg, op.reg)
    
            # Only care about reads from tagged registers
            if op.type != VmOpType.READ_REG:
                return VmThread.CONTINUE
    
            # Tag == original argument register
            tag = thread.get_register_tag(op.reg)
    
            if tag == VmThread.NULL_TAG:
                return VmThread.CONTINUE
    
            update_arg_type(op.reg, VmReg(tag), thread.get_current_instruction())
    
            return VmThread.CONTINUE
    
        # self._vm.set_breakpoint(address)
        self._vm.run(entry_point=address,
                     callback=thread_callback,
                     init_state=self._base_state,
                     step_into_calls=self._save_rest_subs)
    
        result = AnalysisResult()

        for _, type_info in sorted(args.items()):
            if isinstance(type_info, StructType):
                result.found_structs.append(type_info)
                type_info = PointerType(type_info)
            result.parameters.append(type_info)
    
        return result
