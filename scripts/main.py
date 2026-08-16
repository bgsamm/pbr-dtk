from argparse import ArgumentParser
from pathlib import Path
from decomp import DolAnalyzer
from dtk import SplitMap, SymbolMap
from rvl import Dol
import os
import subprocess

DOL_PATH = Path('orig/RPBP01/sys/main.dol')
SPLITS_PATH = Path('config/RPBP01/splits.txt')
SYMBOLS_PATH = Path('config/RPBP01/symbols.txt')

def integer_literal(string: str) -> int:
    return int(string, 0)

def open_in_code(*paths: Path):
    subprocess.run(['code.cmd', *paths], check=True)

def exec_analyze(args):
    address = args.address

    dol = Dol.from_file(DOL_PATH)
    symbol_map = SymbolMap.from_file(SYMBOLS_PATH)

    try:
        analyzer = DolAnalyzer(dol, symbol_map)
        result = analyzer.analyze_function(address)
    except RuntimeError:
        return

    if len(result.found_structs) > 0:
        print('Found the following structs:')
        for i, struct_info in enumerate(result.found_structs):
            struct_info.name = f'Struct_{i}'
            print(struct_info.to_c())

    symbols = symbol_map.get_by_address(address)
    if len(symbols) == 0:
        func_name = f'fn_{address:X}'
    else:
        func_name = symbols[0]

    print('Proposed function signature:')
    param_list = ', '.join(f'{type_info} arg{i}' for i, type_info in enumerate(result.parameters))
    print(f'void {func_name}({param_list})')

def exec_find_split(args):
    address = args.address

    splits = SplitMap.from_file(SPLITS_PATH)
    split = splits.find_split_by_address(address)

    if split is None:
        print('No matching split found')
        return

    print(f'Split found: {split}')

    if args.open:
        src_path = Path(split.path)
        header_path = 'include' / src_path.relative_to('src').with_suffix('.hpp')
        open_in_code(src_path, header_path)

def main():
    parser = ArgumentParser(description="A suite of decompilation & binary analysis scripts")
    subparsers = parser.add_subparsers(required=True)

    parser_analyze = subparsers.add_parser('analyze')
    parser_analyze.add_argument('address', type=integer_literal)
    parser_analyze.set_defaults(func=exec_analyze)

    parser_find_split = subparsers.add_parser('find-split')
    parser_find_split.add_argument('address', type=integer_literal)
    parser_find_split.add_argument('-o', '--open', action='store_true')
    parser_find_split.set_defaults(func=exec_find_split)

    args = parser.parse_args()
    args.func(args)

if __name__ == '__main__':
    main()
