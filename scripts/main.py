from argparse import ArgumentParser
from pathlib import Path
from decomp import AnalysisResult, DolAnalyzer, callgraph, codegen
from dtk.splits import SplitMap
from dtk.symbols import SymbolMap
from rvl import Dol
import logging
import subprocess

DOL_PATH = Path("orig/RPBP01/sys/main.dol")
SPLITS_PATH = Path("config/RPBP01/splits.txt")
SYMBOLS_PATH = Path("config/RPBP01/symbols.txt")

OUTPUT_PATH = Path("analysis/")


def _hex_literal(string: str) -> int:
    return int(string, 16)


def _open_in_code(*paths: Path):
    subprocess.run(["code.cmd", *paths], check=True)


def _call_graphviz(infile: Path, outfile: Path):
    subprocess.run(["dot", "-Tpng", infile, "-o", outfile])


def _prompt_exists_ok(path: Path) -> bool:
    if path.exists():
        response = input(f"The file {path} already exists; OK to overwrite? (Y/n) ")
        if response.lower().strip() != "n":
            return True
        return False
    return True


def _parse_boundaries_file(path: Path) -> list[tuple[int, int]]:
    boundaries = []

    with open(path) as f:
        for line in f:
            if not line.startswith("#"):
                start, end = map(_hex_literal, line.split())
                boundaries.append((start, end))

    return boundaries


def exec_analyze(args):
    def gen_function_signature(result: AnalysisResult) -> str:
        return codegen.gen_function_signature(
            result.func_name, result.arguments, result.return_type, result.type_registry
        )

    func_addr: int = args.address
    max_depth: int = args.depth
    breakpoint: int | None = args.breakpoint

    dol = Dol.from_file(DOL_PATH)
    symbol_map = SymbolMap.from_file(SYMBOLS_PATH)

    breakpoints = {breakpoint} if breakpoint is not None else set()

    analyzer = DolAnalyzer(dol, symbol_map, breakpoints)
    result = analyzer.analyze_function(func_addr, max_depth)

    outfile = OUTPUT_PATH / f"analysis_{func_addr:X}.txt"
    if not _prompt_exists_ok(outfile):
        return

    # TODO Separate output generation from file writing
    with open(outfile, "w") as f:
        f.write("Proposed function signature:\n")
        f.write(f"    {gen_function_signature(result)}\n")
        f.write("\n")

        if len(result.subcalls) > 0:
            f.write("Identified subcalls:\n")
            for _, subresult in sorted(result.subcalls.items()):
                f.write(f"    {gen_function_signature(subresult)}\n")
            f.write("\n")

        if len(result.structs) > 0:
            f.write("Possible structs:\n\n")
            for struct in result.structs:
                f.write(f"{codegen.gen_struct(struct, result.type_registry)}\n")
            f.write("\n")

        print(f"Results have been written to {outfile}")


def exec_call_graph(args):
    func_addr: int = args.address
    max_depth: int = args.depth
    boundaries_file: Path | None = args.boundaries

    dol = Dol.from_file(DOL_PATH)
    symbol_map = SymbolMap.from_file(SYMBOLS_PATH)

    if boundaries_file:
        boundaries = _parse_boundaries_file(boundaries_file)
    else:
        boundaries = []

    function = symbol_map.require_symbol_at(func_addr)
    graph = callgraph.gen_call_graph(dol, function, symbol_map, max_depth, boundaries)

    # Every node is guaranteed to be a target of at least one call, except for the starting function
    nodes = {target for _, target in graph}
    nodes.add(function)

    splits = SplitMap.from_file(SPLITS_PATH)
    split = splits.find_split_by_address(func_addr)

    outfile = OUTPUT_PATH / f"callgraph_{func_addr:X}.dot"
    if not _prompt_exists_ok(outfile):
        return

    # TODO Separate output generation from file writing
    with open(outfile, "w") as f:
        f.write("digraph CallGraph {\n")
        f.write('  rankdir="LR"\n')
        if split:
            for func in sorted(nodes, key=lambda func: func.address):
                color = "blue" if split.contains_address(func.address) else "red"
                f.write(f'  "{func}" [color={color}]\n')
        for source, target in sorted(
            graph, key=lambda call: (call[0].address, call[1].address)
        ):
            f.write(f'  "{source}" -> "{target}"\n')
        f.write("}")

    print(f"Results have been written to {outfile}")

    infile = outfile
    outfile = OUTPUT_PATH / f"callgraph_{func_addr:X}.png"
    _call_graphviz(infile, outfile)

    print(f"Graph rendered to {outfile}")


def exec_find_split(args):
    address: int = args.address

    splits = SplitMap.from_file(SPLITS_PATH)
    split = splits.find_split_by_address(address)

    if split is None:
        print("No matching split found")
        return

    print(f"Split found: {split}")

    if args.open:
        src_path = Path(split.path)
        header_path = "include" / src_path.relative_to("src").with_suffix(".hpp")
        _open_in_code(src_path, header_path)


def main():
    parser = ArgumentParser(
        description="A suite of decompilation & binary analysis scripts"
    )
    parser.add_argument("--debug", action="store_true")
    subparsers = parser.add_subparsers(required=True)

    parser_analyze = subparsers.add_parser("analyze")
    parser_analyze.add_argument("address", type=_hex_literal)
    parser_analyze.add_argument("--breakpoint", type=_hex_literal)
    parser_analyze.add_argument("--depth", type=int, default=0)
    parser_analyze.set_defaults(func=exec_analyze)

    parser_call_graph = subparsers.add_parser("call-graph")
    parser_call_graph.add_argument("address", type=_hex_literal)
    parser_call_graph.add_argument("--depth", type=int, default=0)
    parser_call_graph.add_argument("--boundaries", type=Path)
    parser_call_graph.set_defaults(func=exec_call_graph)

    parser_find_split = subparsers.add_parser("find-split")
    parser_find_split.add_argument("address", type=_hex_literal)
    parser_find_split.add_argument("-o", "--open", action="store_true")
    parser_find_split.set_defaults(func=exec_find_split)

    args = parser.parse_args()
    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
    args.func(args)


if __name__ == "__main__":
    main()
