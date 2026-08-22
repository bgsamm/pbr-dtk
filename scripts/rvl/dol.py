from functools import cached_property
from typing import Iterator
from byteio import BytesReader
from typealiases import *
import enum

WII_MEM1_START = 0x8000_0000


class _SectionType(enum.Enum):
    TEXT = enum.auto()
    DATA = enum.auto()


class DolSection:
    def __init__(self, type: _SectionType, offset: int, address: int, size: int):
        self.type = type
        self.offset = offset
        self.address = address
        self.size = size
        self.real_size_known = False

    @property
    def end_offset(self) -> int:
        return self.offset + self.size

    @property
    def end_address(self) -> int:
        return self.address + self.size

    def contains_offset(self, offset):
        return offset >= self.offset and offset < self.end_offset

    def contains_address(self, address):
        return address >= self.address and address < self.end_address


class Dol(BytesReader):
    HEADER_SIZE = 0x100
    BSS_ADDRESS_OFFSET = 0xD8
    BSS_SIZE_OFFSET = 0xDC
    ENTRY_POINT_OFFSET = 0xE0

    MAX_TEXT_SECTIONS = 7
    MAX_DATA_SECTIONS = 11
    MAX_SECTIONS = MAX_TEXT_SECTIONS + MAX_DATA_SECTIONS  # = 18

    _sections: list[DolSection]

    def __init__(self, data) -> None:
        super().__init__(data)
        self._init_sections()

    @property
    def n_sections(self) -> int:
        return self._n_sections

    @property
    def n_text_sections(self) -> int:
        return self._n_text_sections

    @property
    def n_data_sections(self) -> int:
        return self._n_data_sections

    @property
    def sections(self) -> Iterator[DolSection]:
        yield from self._sections

    @property
    def text_sections(self) -> Iterator[DolSection]:
        yield from (
            section for section in self._sections if section.type == _SectionType.TEXT
        )

    @property
    def data_sections(self) -> Iterator[DolSection]:
        yield from (
            section for section in self._sections if section.type == _SectionType.DATA
        )

    @cached_property
    def bss_address(self) -> int:
        return self.read(self.BSS_ADDRESS_OFFSET, u32)

    @cached_property
    def bss_size(self) -> int:
        return self.read(self.BSS_SIZE_OFFSET, u32)

    @cached_property
    def entry_point(self) -> int:
        return self.read(self.ENTRY_POINT_OFFSET, u32)

    def _init_sections(self) -> None:
        section_offsets = self.read_many(0x0, u32, self.MAX_SECTIONS)
        section_addresses = self.read_many(0x48, u32, self.MAX_SECTIONS)
        section_sizes = self.read_many(0x90, u32, self.MAX_SECTIONS)

        self._sections = []
        self._n_text_sections = 0
        self._n_data_sections = 0

        for i in range(Dol.MAX_SECTIONS):
            if (size := section_sizes[i]) == 0:
                continue

            if i < Dol.MAX_TEXT_SECTIONS:
                type = _SectionType.TEXT
                self._n_text_sections += 1
            else:
                type = _SectionType.DATA
                self._n_data_sections += 1

            offset = section_offsets[i]
            address = section_addresses[i]
            section = DolSection(type, offset, address, size)

            self._sections.append(section)

        self._n_sections = self._n_text_sections + self._n_data_sections

    def read(self, addr_or_off: int, type: ctype) -> int:
        offset = (
            addr_or_off
            if addr_or_off < WII_MEM1_START
            else self.address_to_offset(addr_or_off)
        )
        return super().read(type, offset)

    def read_many(self, addr_or_off: int, type: ctype, n: int) -> tuple[int, ...]:
        offset = (
            addr_or_off
            if addr_or_off < WII_MEM1_START
            else self.address_to_offset(addr_or_off)
        )
        return super().read_many(type, offset, n)

    def offset_to_address(self, offset: int) -> int:
        if (section := self.get_section_by_offset(offset)) is None:
            raise ValueError("Invalid offset")
        return offset - section.offset + section.address

    def address_to_offset(self, address: int) -> int:
        if (section := self.get_section_by_address(address)) is None:
            raise ValueError("Invalid address")
        return address - section.address + section.offset

    def get_section_by_offset(self, offset: int) -> DolSection | None:
        for section in self._sections:
            if section.contains_offset(offset):
                return section
        return None

    def get_section_by_address(self, address: int) -> DolSection | None:
        for section in self._sections:
            if section.contains_address(address):
                return section
        return None
