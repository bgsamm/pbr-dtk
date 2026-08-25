from dtk.symbols import Symbol, SymbolMap
from mathutils import sign_ext
from ppc import PpcInstr, PpcOp
from rvl import Dol
from typealiases import u32
import bisect

# TODO Centralize save/rest sub filtering
_SAVE_REST_SUBS = {
    f"_{op}{type}_{i}"
    for op in ["save", "rest"]
    for type in ["gpr", "fpr"]
    for i in range(14, 31 + 1)
}


def _get_branch_target(instr: PpcInstr, curr_addr: int) -> int:
    # TODO Move instruction parsing into ppc
    LI = instr.field(6, 29)
    AA = instr.bit(30)

    offset = sign_ext(LI << 2, 26)

    if AA == 1:
        target_addr = offset
    else:
        target_addr = curr_addr + offset

    return target_addr


def _is_at_boundary(boundaries: list[tuple[int, int]], address: int) -> bool:
    for start, end in boundaries:
        if start <= address < end:
            return True
    return False


def gen_call_graph(
    dol: Dol,
    function: Symbol,
    symbol_map: SymbolMap,
    depth: int = 0,
    boundaries: list[tuple[int, int]] | None = None,
) -> set[tuple[Symbol, Symbol]]:
    graph: set[tuple[Symbol, Symbol]] = set()

    assert function.size

    func_start = function.address
    func_end = function.address + function.size

    for address in range(func_start, func_end, 4):
        instr = PpcInstr(dol.read(address, u32))

        if instr.op != PpcOp.B:
            continue

        target_addr = _get_branch_target(instr, address)
        if func_start <= target_addr < func_end:
            continue

        target_function = symbol_map.require_symbol_at(target_addr)
        if target_function.name in _SAVE_REST_SUBS:
            continue

        graph.add((function, target_function))

        if boundaries and _is_at_boundary(boundaries, target_addr):
            continue

        if depth > 0:
            subresult = gen_call_graph(
                dol, target_function, symbol_map, depth - 1, boundaries
            )
            graph.update(subresult)

    return graph
