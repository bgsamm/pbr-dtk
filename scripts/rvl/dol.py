from functools import cached_property
from byteio import BytesReader
from dtk import Symbol, SymbolMap
from .types import *
import enum
import logging

WII_MEM1_START = 0x8000_0000


class DolError(Exception):
    pass


class DolSectionType(enum.Enum):
    TEXT = enum.auto()
    DATA = enum.auto()


# TODO Merge with Symbol?
class DolSection:
    def __init__(self, type: DolSectionType, offset: int, address: int, size: int):
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
    _section_map: dict[str, DolSection | None]

    def __init__(self, data):
        super().__init__(data)

        self._section_map = {
            ".init": None,
            ".text": None,
            ".ctors": None,
            ".dtors": None,
        }
        self._symbol_map = SymbolMap()

        if not self._init_sections():
            raise DolError("Failed to initialize sections")

    @property
    def n_sections(self):
        return self._n_sections

    @property
    def n_text_sections(self):
        return self._n_text_sections

    @property
    def n_data_sections(self):
        return self._n_data_sections

    @property
    def sections(self):
        yield from self._sections

    @property
    def text_sections(self):
        yield from (
            section for section in self._sections if section.type == DolSectionType.TEXT
        )

    @property
    def data_sections(self):
        yield from (
            section for section in self._sections if section.type == DolSectionType.DATA
        )

    @cached_property
    def bss_address(self):
        return self.read(u32, self.BSS_ADDRESS_OFFSET)

    @cached_property
    def bss_size(self):
        return self.read(u32, self.BSS_SIZE_OFFSET)

    @cached_property
    def entry_point(self):
        return self.read(u32, self.ENTRY_POINT_OFFSET)

    @property
    def init_section(self) -> DolSection | None:
        return self._section_map[".init"]

    @property
    def text_section(self) -> DolSection | None:
        return self._section_map[".text"]

    @property
    def ctors_section(self) -> DolSection | None:
        return self._section_map[".ctors"]

    @property
    def dtors_section(self) -> DolSection | None:
        return self._section_map[".dtors"]

    def _init_sections(self) -> bool:
        section_offsets = self.read_many(u32, 0x0, n=self.MAX_SECTIONS)
        section_addresses = self.read_many(u32, 0x48, n=self.MAX_SECTIONS)
        section_sizes = self.read_many(u32, 0x90, n=self.MAX_SECTIONS)

        self._sections = []
        self._n_text_sections = 0
        self._n_data_sections = 0

        for i in range(Dol.MAX_SECTIONS):
            if (size := section_sizes[i]) == 0:
                continue

            if i < Dol.MAX_TEXT_SECTIONS:
                type = DolSectionType.TEXT
                self._n_text_sections += 1
            else:
                type = DolSectionType.DATA
                self._n_data_sections += 1

            offset = section_offsets[i]
            address = section_addresses[i]
            section = DolSection(type, offset, address, size)

            self._sections.append(section)

        self._n_sections = self._n_text_sections + self._n_data_sections

        self._section_map[".init"] = self.get_section_by_address(self.entry_point)

        # TODO Handle more than 2 text sections
        if self._n_text_sections == 2:
            self._section_map[".text"] = (
                self._sections[1]
                if self._sections[0] is self.init_section
                else self._sections[0]
            )

        if not self._try_find_rom_copy_info():
            logging.error("Failed to find _rom_copy_info")
            return False

        if not self._try_find_ctors_dtors():
            logging.error("Failed to find .ctors/.dtors")
            return False

        return True

    def _try_find_rom_copy_info(self):
        # TODO Something other than an assert?
        assert self.init_section is not None

        # + 1 for terminating null entry
        MAX_ROM_COPY_INFO_SIZE = (Dol.MAX_SECTIONS + 1) * 3 * 4
        MAX_BSS_INIT_INFO_SIZE = (Dol.MAX_DATA_SECTIONS + 1) * 2 * 4

        min_section_addr = min(section.address for section in self._sections)

        # 0x1c for max section padding
        offset = (
            self.init_section.end_offset
            - MAX_ROM_COPY_INFO_SIZE
            - MAX_BSS_INIT_INFO_SIZE
            - 0x1C
        )

        rom_copy_info_off = None
        while offset < self.init_section.end_offset:
            src, dst = self.read_many(u32, offset, n=2)

            if src == min_section_addr and dst == min_section_addr:
                rom_copy_info_off = offset
                break

            offset += 4

        if rom_copy_info_off is None:
            return False

        offset = rom_copy_info_off

        # Read table entries until the null entry is hit
        while offset < self.init_section.end_offset:
            src, dst, size = self.read_many(u32, offset, n=3)

            # Update now so equal to end if break is hit
            offset += 12  # = 3 * sizeof(uint)

            if src != dst:
                logging.error("Non-matching source/dest in _rom_copy_info")
                return False

            # Null entry hit
            if src == 0:
                if dst != 0 or size != 0:
                    logging.error("Unexpected null source address in _rom_copy_info")
                    return False
                break

            # Update section size
            section = self.get_section_by_address(src)

            if section is None or section.address != src:
                logging.error("Non-section address in _rom_copy_info")
                return False

            if section.real_size_known:
                logging.error("Repeated entry in _rom_copy_info")
                return False

            section.size = size
            section.real_size_known = True

        if any(not section.real_size_known for section in self._sections):
            logging.error("Section missing from _rom_copy_info")
            return False

        rom_copy_info_addr = self.offset_to_address(rom_copy_info_off)
        rom_copy_info_size = offset - rom_copy_info_off
        self.add_symbol("_rom_copy_info", rom_copy_info_addr, rom_copy_info_size)

        return True

    def _try_find_ctors_dtors(self):
        candidate_sections = []
        candidate_functions = []

        for section in self.data_sections:
            # TODO Make this work even with aligned sizes?
            assert section.real_size_known

            functions = []

            # Look for sections containing only valid addresses
            offset = section.offset
            while offset < section.end_offset:
                word = self.read(u32, offset)

                # Valid function addresses should be word-aligned
                if word % 4 != 0:
                    break

                if word == 0:
                    # 0 only valid as terminating null entry
                    # (Assumes real section size known from _rom_copy_info)
                    if offset == section.offset + section.size - 4:
                        candidate_sections.append(section)
                        candidate_functions.append(functions)
                    break

                if self.get_section_by_address(word) is None:
                    break

                functions.append(word)

                offset += 4

        if len(candidate_sections) < 2:
            logging.error("Unable to find .ctors/.dtors")
            return False

        if len(candidate_sections) > 2:
            logging.warning(
                "Found multiple candidates for .ctors/.dtors; using first 2"
            )

        # Assumes .ctors always comes before .dtors
        self._section_map[".ctors"] = candidate_sections[0]
        self._section_map[".dtors"] = candidate_sections[1]

        ctors, dtors = candidate_functions

        # ctors

        if len(ctors) < 1:
            logging.error("Invalid .ctors section; not enough entries")
            return False

        self.add_symbol("__init_cpp_exceptions", ctors[0], None)

        # TODO Something better?
        self.ctors = []
        for func_addr in ctors[1:]:
            symbol = self.add_symbol(f"fn_{func_addr:08x}", func_addr, None)
            self.ctors.append(symbol)

        # dtors

        if len(dtors) < 2:
            logging.error("Invalid .dtors section; not enough entries")
            return False

        self.add_symbol("__destroy_global_chain", dtors[0], None)
        self.add_symbol("__fini_cpp_exceptions", dtors[1], None)

        # TODO Something better?
        self.dtors = []
        for func_addr in dtors[2:]:
            symbol = self.add_symbol(f"fn_{func_addr:08x}", func_addr, None)
            self.dtors.append(symbol)

        return True

    def read(self, type: ctype, addr_or_off: int) -> int:
        offset = (
            addr_or_off
            if addr_or_off < WII_MEM1_START
            else self.address_to_offset(addr_or_off)
        )
        return super().read(type, offset)

    def read_many(self, type: ctype, addr_or_off: int, n: int) -> tuple[int, ...]:
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

    def add_symbol(self, name: str, address: int, size: int | None) -> Symbol:
        return self._symbol_map.add(name, address, size)

    def get_symbols_at(self, address: int) -> tuple[Symbol, ...]:
        return self._symbol_map.get_by_address(address)

    def get_symbols_named(self, name: str) -> tuple[Symbol, ...]:
        return self._symbol_map.get_by_name(name)

    def apply_symbol_map(self, symbol_map: SymbolMap):
        self._symbol_map.merge(symbol_map)
