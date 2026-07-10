from dol import DolReader
from pathlib import Path
import os
import re

DOL_PATH = Path('orig/RPBP01/sys/main.dol')
SYMBOLS_PATH = Path('config/RPBP01/symbols.txt')
SPLITS_PATH = Path('config/RPBP01/splits.txt')
ROOT_INC_DIR = Path('include')
ROOT_SRC_DIR = Path('src')
AUTO_SPLIT_DIR = Path('.unsorted')

def read_symbol_file(path):
    def parse_line(line):
        tokens = line.split()
        
        name = tokens[0]
        assert tokens[1] == '='
        addr = tokens[2]
        assert tokens[3] == '//'
        meta = tokens[4:]

        section, addr = addr.split(':')
        addr = int(addr[:-1], 16)

        meta = [token.split(':') for token in meta]
        meta = {e[0]:(True if len(e) == 1 else e[1]) for e in meta}
        if 'size' in meta:
            meta['size'] = int(meta['size'], 16)

        return name, section, addr, meta
    
    symbol_map = {}
    with open(path, 'r') as f:
        for line in f:
            name, section, addr, meta = parse_line(line)
            symbol_map[addr] = {'name': name, 'section': section, 'addr': addr, **meta}

    return symbol_map

def read_splits_file(path):
    def commit_split(split):
        if split is not None and split['name'] != 'Sections':
            assert '.text' in split
            splits_map[split['.text'][0]] = split

    splits_map = {}
    with open(path, 'r') as f:
        cur_split = None

        for line in f:
            if (match := re.match(r'([._0-9A-Za-z/]+):', line)) is not None:
                commit_split(cur_split)
                cur_split = {'name': match.groups()[0]}
            elif 'start' in line:
                tokens = line.split()
                assert len(tokens) >= 3

                section = tokens[0]
                start = tokens[1]
                end = tokens[2]

                assert start.startswith('start:')
                assert end.startswith('end:')

                start = int(start[len('start:'):], 16)
                end = int(end[len('end:'):], 16)

                assert start < end

                cur_split[section] = (start, end)
    commit_split(cur_split)

    return splits_map

def fix_splits(splits_to_fix, ref_splits):
    pos_a = pos_b = 0

    while pos_a < len(splits_to_fix) and pos_b < len(ref_splits):
        start_a, end_a = splits_to_fix[pos_a]
        start_b, end_b = ref_splits[pos_b]

        if end_b <= start_a:
            pos_b += 1
        elif end_a <= start_b:
            pos_a += 1
        else:
            if start_a == start_b:
                if end_a != end_b:
                    print(f'Non-matching splits! {start_a:x}-{end_a:x} vs. {start_b:x}-{end_b:x}')
                if end_a > end_b:
                    splits_to_fix[pos_a] = (end_b, end_a)
                else:
                    splits_to_fix.pop(pos_a)
            else:
                print(f'Overlapping splits! {start_a:x}-{end_a:x} vs. {start_b:x}-{end_b:x}')
                if start_a < start_b and end_a <= end_b:
                    splits_to_fix[pos_a] = (start_a, start_b)
                elif start_a > start_b and end_a > end_b:
                    splits_to_fix[pos_a] = (end_b, end_a)
                elif start_a < start_b and end_a > end_b:
                    splits_to_fix[pos_a] = (start_a, start_b)
                    splits_to_fix.insert(pos_a + 1, (end_b, end_a))
                else:
                    splits_to_fix.pop(pos_a)

            ## For just finding overlaps w/o fixing them
            # if end_a < end_b:
            #     pos_a += 1
            # elif end_b < end_a:
            #     pos_b += 1
            # else:
            #     pos_a += 1
            #     pos_b += 1

def touch_file(path):
    with open(path, 'w'):
        pass

if __name__ == '__main__':
    symbol_map = read_symbol_file(SYMBOLS_PATH)
    split_map = read_splits_file(SPLITS_PATH)

    existing_splits = [split['.text'] for split in split_map.values()]
    existing_splits.sort(key=lambda split: split[0])
    
    dol = DolReader.from_file(DOL_PATH)

    section = dol.get_section_by_address(dol.ctors[0].address)
    last_addr = section.address

    split_candidates = []
    for ctor in dol.ctors:
        assert ctor.address in symbol_map

        sym = symbol_map[ctor.address]
        next_addr = ctor.address + sym['size']
        
        assert section.contains_address(next_addr)
        assert next_addr > last_addr

        split_candidates.append((last_addr, next_addr))
        last_addr = next_addr

    split_candidates.sort(key=lambda split: split[0])

    os.makedirs(ROOT_INC_DIR / AUTO_SPLIT_DIR, exist_ok=True)
    os.makedirs(ROOT_SRC_DIR / AUTO_SPLIT_DIR, exist_ok=True)

    fix_splits(split_candidates, existing_splits)

    with open(SPLITS_PATH, 'a') as splits_file:
        splits_file.write(f'\n')

        for start, end in split_candidates:
            assert start < end
            assert start not in split_map

            inc_path = ROOT_INC_DIR / AUTO_SPLIT_DIR / f'{start:X}.hpp'
            src_path = ROOT_SRC_DIR / AUTO_SPLIT_DIR / f'{start:X}.cpp'

            rel_inc_path = inc_path.relative_to(ROOT_INC_DIR)
            rel_src_path = src_path.relative_to(ROOT_SRC_DIR)

            splits_file.write(f'{src_path.as_posix()}:\n')
            splits_file.write(f'\t.text       start:0x{start:X} end:0x{end:X}\n')
            splits_file.write(f'\n')

            print(f'Object(NonMatching, "{rel_src_path.as_posix()}"),')

            with open(inc_path, 'w') as inc:
                inc.write('#pragma once\n\n#include "common.hpp"\n')
            with open(src_path, 'w') as src:
                src.write(f'#include "{rel_inc_path.as_posix()}"\n')
