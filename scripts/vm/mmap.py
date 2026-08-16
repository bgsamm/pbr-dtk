from byteio import BytesWriter
from rvl.types import *
from .symval import SymbolicValue


class VmMemMap:
    _PAGE_SIZE = 4 * 1024
    _PAGE_MASK = _PAGE_SIZE - 1
    _PAGE_SHIFT = 12

    class Page:
        def __init__(self, size):
            self._data_bytes = bytearray(size)
            self._data = BytesWriter(self._data_bytes)
            self._state_bytes = bytearray(size)
            self._state = memoryview(self._state_bytes)

        def __getitem__(self, key: int) -> SymbolicValue:
            if isinstance(key, int):
                if self._state_bytes[key] == 1:
                    return SymbolicValue(self._data_bytes[key])
                return SymbolicValue.Unknown
            raise TypeError()

        def read(self, type: ctype, offset: int) -> SymbolicValue:
            size = sizeof(type)

            # TODO Handle partially known values?
            if self._state[offset : offset + size] == (b"\x01" * size):
                value = self._data.read(type, offset)
                return SymbolicValue(value)

            return SymbolicValue.Unknown

        def write(self, type: ctype, offset: int, sym: SymbolicValue):
            size = sizeof(type)

            if sym.is_known:
                self._data.write(type, offset, sym.value)
                state_mask = b"\x01" * size
            else:
                state_mask = b"\x00" * size

            self._state[offset : offset + size] = state_mask

        def copy(self) -> VmMemMap.Page:
            page = super().__new__(type(self))

            page._data_bytes = self._data_bytes[:]
            page._data = BytesWriter(page._data_bytes)
            page._state_bytes = self._state_bytes[:]
            page._state = memoryview(page._state_bytes)

            return page

    _page_table: dict[int, Page]
    _owned_pages: set[int]

    def __init__(self, parent_pages: dict | None = None):
        self._page_table = dict(parent_pages) if parent_pages else {}
        self._owned_pages = set()

    def _resolve_address(self, addr: int):
        phys = addr & 0x3FFF_FFFF
        if phys < 0x180_0000 or 0x1000_0000 <= phys < 0x1400_0000:
            return (phys >> self._PAGE_SHIFT), (phys & self._PAGE_MASK)
        raise ValueError(f"Invalid memory address: {addr}")

    def read(self, type: ctype, addr: int) -> SymbolicValue:
        page_idx, offset = self._resolve_address(addr)

        if not (page := self._page_table.get(page_idx)):
            return SymbolicValue.Unknown

        # TODO Handle cross-page (mis-aligned) reads
        return page.read(type, offset)

    def write(self, type: ctype, addr: int, sym: SymbolicValue):
        page_idx, offset = self._resolve_address(addr)

        if page_idx not in self._owned_pages:
            if page_idx in self._page_table:
                self._page_table[page_idx] = self._page_table[page_idx].copy()
            else:
                self._page_table[page_idx] = self.Page(self._PAGE_SIZE)
            self._owned_pages.add(page_idx)

        self._page_table[page_idx].write(type, offset, sym)

    def dump(self, addr: int, size: int):
        result = [SymbolicValue.Unknown for _ in range(size)]
        pos = 0

        while size > 0:
            page_idx, offset = self._resolve_address(addr)
            to_read = min(self._PAGE_SIZE - offset, size)

            if page := self._page_table.get(page_idx):
                for i in range(to_read):
                    result[pos + i] = page[offset + i]

            addr += to_read
            pos += to_read
            size -= to_read

        return result

    def clone(self) -> VmMemMap:
        return VmMemMap(self._page_table)

    def reset(self):
        self._page_table.clear()
        self._owned_pages.clear()
