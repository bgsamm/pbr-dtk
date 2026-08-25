from argparse import ArgumentParser
from pathlib import Path
from decomp import AnalysisResult, DolAnalyzer, codegen
from dtk.splits import SplitMap
from dtk.symbols import SymbolMap
from rvl import Dol
import logging
import subprocess

DOL_PATH = Path("orig/RPBP01/sys/main.dol")
SPLITS_PATH = Path("config/RPBP01/splits.txt")
SYMBOLS_PATH = Path("config/RPBP01/symbols.txt")


def _integer_literal(string: str) -> int:
    return int(string, 0)


def _open_in_code(*paths: Path):
    subprocess.run(["code.cmd", *paths], check=True)


def exec_analyze(args):
    def gen_function_signature(result: AnalysisResult) -> str:
        return codegen.gen_function_signature(
            result.func_name, result.arguments, result.return_type, result.type_registry
        )

    address = args.address
    max_depth = args.depth
    breakpoint = args.breakpoint

    dol = Dol.from_file(DOL_PATH)
    symbol_map = SymbolMap.from_file(SYMBOLS_PATH)

    analyzer = DolAnalyzer(dol, symbol_map, breakpoints={breakpoint})
    result = analyzer.analyze_function(address, max_depth)

    outfile = Path(f"analysis_{address:X}.txt")
    if outfile.exists():
        response = input(f"The file {outfile} already exists; OK to overwrite? (y/N) ")
        if response.lower().strip() != "y":
            return

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


def exec_find_split(args):
    address = args.address

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
    parser_analyze.add_argument("address", type=_integer_literal)
    parser_analyze.add_argument("--breakpoint", type=_integer_literal)
    parser_analyze.add_argument("--depth", type=_integer_literal, default=0)
    parser_analyze.set_defaults(func=exec_analyze)

    parser_find_split = subparsers.add_parser("find-split")
    parser_find_split.add_argument("address", type=_integer_literal)
    parser_find_split.add_argument("-o", "--open", action="store_true")
    parser_find_split.set_defaults(func=exec_find_split)

    args = parser.parse_args()
    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
    args.func(args)


if __name__ == "__main__":
    main()
