from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
import logging


class SymbolError(Exception):
    pass


@dataclass(frozen=True)
class Symbol:
    name: str
    address: int
    size: int | None

    def __str__(self):
        return self.name

    @property
    def is_size_known(self) -> bool:
        return self.size is not None


class SymbolMap:
    _symbols: dict[tuple[int, str], Symbol]
    _name_lookup: defaultdict[str, list[Symbol]]
    _addr_lookup: defaultdict[int, list[Symbol]]

    def __init__(self):
        self._symbols = {}
        self._name_lookup = defaultdict(list)
        self._addr_lookup = defaultdict(list)

    def __iter__(self):
        for symbols in self._addr_lookup.values():
            yield from symbols

    def _replace(self, old_symbol: Symbol, new_symbol: Symbol):
        old_key = (old_symbol.address, old_symbol.name)
        self._symbols.pop(old_key)
        self._addr_lookup[old_symbol.address].remove(old_symbol)
        self._name_lookup[old_symbol.name].remove(old_symbol)

        new_key = (new_symbol.address, new_symbol.name)
        self._symbols[new_key] = new_symbol
        self._addr_lookup[new_symbol.address].append(new_symbol)
        self._name_lookup[new_symbol.name].append(new_symbol)

    def _add(self, symbol: Symbol):
        key = (symbol.address, symbol.name)

        old_symbol = self._symbols.get(key)
        if old_symbol:
            if symbol.is_size_known and old_symbol.size != symbol.size:
                if old_symbol.is_size_known:
                    logging.warning(
                        f"Size conflict for {symbol.name} at {symbol.address:#x}: "
                        + f"{old_symbol.size} (old) vs {symbol.size} (new); adopting new size"
                    )
                self._replace(old_symbol, symbol)
            return

        self._symbols[key] = symbol
        self._addr_lookup[symbol.address].append(symbol)
        self._name_lookup[symbol.name].append(symbol)

    def _create(self, name: str, address: int, size: int | None) -> Symbol:
        symbol = Symbol(name, address, size)
        self._add(symbol)
        return symbol

    def get_symbols_at(self, address: int) -> tuple[Symbol, ...]:
        return tuple(self._addr_lookup[address])

    def get_symbols_named(self, name: str) -> tuple[Symbol, ...]:
        return tuple(self._name_lookup[name])

    def require_symbol(self, name: str) -> Symbol:
        symbols = self.get_symbols_named(name)

        if len(symbols) == 0:
            raise SymbolError(f"No symbol named {name}")
        if len(symbols) > 1:
            raise SymbolError(f"Multiple symbols named {name}")

        return symbols[0]

    def add(self, name: str, address: int, size: int | None) -> Symbol:
        return self._create(name, address, size)

    def merge(self, other: SymbolMap):
        for symbol in other:
            self._add(symbol)

    @classmethod
    def from_file(cls, path: Path) -> SymbolMap:
        def parse_line(line: str):
            tokens = line.split()

            name = tokens[0]
            assert tokens[1] == "="
            addr = tokens[2]
            assert tokens[3] == "//"
            meta = tokens[4:]

            section, addr = addr.split(":")
            addr = int(addr[:-1], 16)

            meta = [token.split(":") for token in meta]
            meta = {e[0]: (True if len(e) == 1 else e[1]) for e in meta}

            if (size := meta.get("size")) is not None:
                assert isinstance(size, str)
                size = int(size, 16)

            return name, addr, size

        symbol_map = SymbolMap()

        with open(path, "r") as f:
            for line in f:
                name, addr, size = parse_line(line)
                symbol_map.add(name, addr, size)

        return symbol_map
