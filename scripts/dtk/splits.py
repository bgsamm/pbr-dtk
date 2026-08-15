from pathlib import Path
import logging
import re

class Split:
    _sections: dict[str, tuple[int, int]]

    def __init__(self, path: str):
        self._path = path
        self._sections = {}

    def __str__(self) -> str:
        return self._path

    @property
    def path(self):
        return self._path

    # TODO Handle existing section?
    def add_section(self, section: str, start: int, end: int):
        self._sections[section] = (start, end)

    def contains_address(self, address: int) -> bool:
        for start, end in self._sections.values():
            if start <= address < end:
                return True
        return False

class SplitMap:
    _splits: dict[str, Split]

    def __init__(self):
        self._splits = {}

    def add_split(self, path: str) -> Split:
        split = self._splits[path] = Split(path)
        return split

    def find_split_by_address(self, address: int) -> Split | None:
        # TODO Something better than linear search
        for split in self._splits.values():
            if split.contains_address(address):
                return split
        return None

    @classmethod
    def from_file(cls, path: Path) -> SplitMap:
        def parse_line(line: str):
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

            return section, start, end

        split_map = SplitMap()

        with open(path, 'r') as f:
            active_split = None

            for line in f:
                # Try to match a file path
                match = re.match(r'([._0-9A-Za-z/]+):', line)

                if match is not None:
                    split_path = match.groups()[0]
                    active_split = split_map.add_split(split_path)
                elif 'start' in line:
                    if active_split is None:
                        logging.warning('Unexpected split information; ignoring')
                        continue
                    section, start, end = parse_line(line)
                    active_split.add_section(section, start, end)

        return split_map
