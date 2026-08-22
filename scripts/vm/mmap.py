from byteio import BytesWriter
from symval import SymbolicValue, SymOrInt
from typealiases import *
import symval


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

        def write(self, type: ctype, offset: int, value: SymOrInt):
            size = sizeof(type)

            value = symval.ensure_symbolic(value)

            if value.is_known:
                self._data.write(type, offset, value.value)
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

    def __init__(self, parent_pages: dict | None = None) -> None:
        self._page_table = dict(parent_pages) if parent_pages else {}
        self._owned_pages = set()

    def _resolve_address(self, addr: int) -> tuple[int, int]:
        phys = addr & 0x3FFF_FFFF
        if phys < 0x180_0000 or 0x1000_0000 <= phys < 0x1400_0000:
            return (phys >> self._PAGE_SHIFT), (phys & self._PAGE_MASK)
        raise ValueError(f"Invalid memory address: {addr}")

    def read(self, addr: int, type: ctype) -> SymbolicValue:
        page_idx, offset = self._resolve_address(addr)

        if not (page := self._page_table.get(page_idx)):
            return SymbolicValue.Unknown

        # TODO Handle cross-page (mis-aligned) reads
        return page.read(type, offset)

    def write(self, addr: int, value: SymOrInt, type: ctype) -> None:
        page_idx, offset = self._resolve_address(addr)

        if page_idx not in self._owned_pages:
            if page_idx in self._page_table:
                # Copy-on-write
                self._page_table[page_idx] = self._page_table[page_idx].copy()
            else:
                self._page_table[page_idx] = self.Page(self._PAGE_SIZE)
            self._owned_pages.add(page_idx)

        self._page_table[page_idx].write(type, offset, value)

    def copy(self) -> VmMemMap:
        return VmMemMap(self._page_table)

    def reset(self) -> None:
        self._page_table.clear()
        self._owned_pages.clear()


class VmMemView:
    def __init__(self, mmap: VmMemMap) -> None:
        self._mmap = mmap

    def __getitem__(self, address: int) -> SymbolicValue:
        return self._mmap.read(address, u8)

    def read(self, address: int, dtype: ctype) -> SymbolicValue:
        return self._mmap.read(address, dtype)
