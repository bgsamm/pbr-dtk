from bin import BytesReader
from functools import cached_property
import enum
import logging

class DolSection:
    def __init__(self, dol: DolReader, type, offset, address, size):
        self._dol = dol

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

class DolSymbol:
    def __init__(self, dol: DolReader, label, addr_or_off, size):
        self._dol = dol

        if addr_or_off < 0x8000_0000:
            self._offset = addr_or_off
            self._address = self._dol.offset_to_address(addr_or_off)
        else:
            self._address = addr_or_off
            self._offset = self._dol.address_to_offset(addr_or_off)

        self.label = label
        self.size = size
    
    def __str__(self):
        return self.label
    
    @property
    def offset(self):
        return self._offset
    
    @property
    def address(self):
        return self._address
    
    @cached_property
    def section(self):
        return self._dol.get_section_by_address(self.address)

class DolReader(BytesReader):
    HEADER_SIZE = 0x100
    MAX_TEXT_SECTIONS = 7
    MAX_DATA_SECTIONS = 11
    MAX_SECTIONS = MAX_TEXT_SECTIONS + MAX_DATA_SECTIONS # = 18

    _sections: list[DolSection | None]

    class SectionType(enum.Enum):
        TEXT = enum.auto()
        DATA = enum.auto()

    def __init__(self, data):
        super().__init__(data)

        self._section_map = {
            '.init': None,
            '.text': None,
            '.ctors': None,
            '.dtors': None
        }
        self._symbol_map = {}

        self._init_sections()
    
    @cached_property
    def n_sections(self):
        return self._n_sections
    
    @cached_property
    def n_text_sections(self):
        return self._n_text_sections
    
    @cached_property
    def n_data_sections(self):
        return self._n_data_sections
    
    @property
    def sections(self):
        return self._sections.copy()
    
    @property
    def text_sections(self):
        return [section for section in self._sections if section.type == self.SectionType.TEXT]
    
    @property
    def data_sections(self):
        return [section for section in self._sections if section.type == self.SectionType.DATA]
    
    @cached_property
    def bss_address(self):
        return self.read('uint', 0xD8)
    
    @cached_property
    def bss_size(self):
        return self.read('uint', 0xDC)
    
    @cached_property
    def entry_point(self):
        return self.read('uint', 0xE0)
    
    @property
    def init_section(self) -> DolSection | None:
        return self._section_map['.init']
    
    @property
    def text_section(self) -> DolSection | None:
        return self._section_map['.text']
    
    @property
    def ctors_section(self) -> DolSection | None:
        return self._section_map['.ctors']
    
    @property
    def dtors_section(self) -> DolSection | None:
        return self._section_map['.dtors']
    
    def offset_to_address(self, offset):
        if (section := self.get_section_by_offset(offset)) is None:
            return -1
        return offset - section.offset + section.address
    
    def address_to_offset(self, address):
        if (section := self.get_section_by_address(address)) is None:
            return -1
        return address - section.address + section.offset
    
    def get_section_by_offset(self, offset):
        for section in self._sections:
            if section.contains_offset(offset):
                return section
        return None

    def get_section_by_address(self, address):
        for section in self._sections:
            if section.contains_address(address):
                return section
        return None
    
    def _init_sections(self):
        ## Read section info from DOL header
        
        section_offsets = self.read('uint', 0x0, n=self.MAX_SECTIONS)
        section_addresses = self.read('uint', 0x48, n=self.MAX_SECTIONS)
        section_sizes = self.read('uint', 0x90, n=self.MAX_SECTIONS)

        self._sections = []

        self._n_text_sections = 0
        self._n_data_sections = 0

        for i in range(self.MAX_SECTIONS):
            if (size := section_sizes[i]) == 0:
                continue

            if i < self.MAX_TEXT_SECTIONS:
                type = self.SectionType.TEXT
                self._n_text_sections += 1
            else:
                type = self.SectionType.DATA
                self._n_data_sections += 1
            offset = section_offsets[i]
            address = section_addresses[i]

            self._sections.append(DolSection(self, type, offset, address, size))
        
        self._n_sections = self._n_text_sections + self._n_data_sections

        self._section_map['.init'] = self.get_section_by_address(self.entry_point)
        # TODO Handle more than 2 text sections?
        if self._n_text_sections == 2:
            if self._sections[0] is self.init_section:
                self._section_map['.text'] = self._sections[1]
            else:
                self._section_map['.text'] = self._sections[0]

        if not self._try_find_rom_copy_info():
            logging.error('Failed to find _rom_copy_info')
            return False

        if not self._try_find_ctors_dtors():
            logging.error('Failed to find .ctors/.dtors')
            return False
        
        return True

    # TODO Rewrite this to be a bit cleaner/more robust
    def _try_find_rom_copy_info(self):
        assert self.init_section is not None

        # + 1 for terminating null entry
        MAX_ROM_COPY_INFO_SIZE = (self.MAX_SECTIONS + 1) * 3 * 4
        MAX_BSS_INIT_INFO_SIZE = (self.MAX_DATA_SECTIONS + 1) * 2 * 4

        min_section_addr = min(section.address for section in self._sections)

        # 0x1c for max section padding
        offset = self.init_section.end_offset - MAX_ROM_COPY_INFO_SIZE - MAX_BSS_INIT_INFO_SIZE - 0x1c

        rom_copy_info_off = -1
        while offset < self.init_section.end_offset:
            src, dst = self.read('uint', offset, n=2)

            if src == min_section_addr and dst == min_section_addr:
                rom_copy_info_off = offset
                break

            offset += 4
        
        if rom_copy_info_off < 0:
            return False

        offset = rom_copy_info_off

        while offset < self.init_section.end_offset:
            src, dst, size = self.read('uint', offset, n=3)

            # Update now so equal to end if break is hit
            offset += 12 # = 3 * sizeof(uint)

            if src != dst:
                logging.error('Non-matching source/dest in _rom_copy_info')
                return False

            if src == 0:
                break

            # Update section sizes from _rom_copy_info
            section = self.get_section_by_address(src)

            if section is None or section.address != src:
                logging.error('Non-section address in _rom_copy_info')
                return False

            if section.real_size_known:
                logging.error('Repeated entry in _rom_copy_info')
                return False

            section.size = size
            section.real_size_known = True
        
        if any(not section.real_size_known for section in self._sections):
            logging.error('Section missing from _rom_copy_info')
            return False
        
        rom_copy_info_size = offset - rom_copy_info_off
        rom_copy_info = DolSymbol(self, '_rom_copy_info', rom_copy_info_off, rom_copy_info_size)
        self._symbol_map['_rom_copy_info'] = rom_copy_info

        return True
    
    # TODO Rewrite this to be a bit cleaner/more robust
    def _try_find_ctors_dtors(self):
        candidate_sections  = []
        candidate_functions = []

        for section in self.data_sections:
            # TODO Make this work even with aligned sizes
            assert section.real_size_known

            functions = []

            offset = section.offset
            while offset < section.end_offset:
                word = self.read('uint', offset)

                # Valid function addresses should be word-aligned
                if word % 4 != 0:
                    break

                if word == 0:
                    # 0 only valid as terminating null entry
                    # (Assumes real section size from _rom_copy_info)
                    if offset == section.offset + section.size - 4:
                        candidate_sections.append(section)
                        candidate_functions.append(functions)
                    break

                if self.get_section_by_address(word) is None:
                    break

                functions.append(word)
                
                offset += 4
        
        if len(candidate_sections) < 2:
            logging.error('Unable to find .ctors/.dtors')
            return False
        
        if len(candidate_sections) > 2:
            logging.warning('Found multiple candidates for .ctors/.dtors; using first 2')
        
        # Assumes .ctors always comes before .dtors
        self._section_map['.ctors'] = candidate_sections[0]
        self._section_map['.dtors'] = candidate_sections[1]

        # TODO Something better

        self.ctors = []
        for func_addr in candidate_functions[0][1:]:
            label = f'fn_{func_addr:08x}'
            symbol = DolSymbol(self, label, func_addr, None)
            self._symbol_map[label] = symbol
            self.ctors.append(symbol)

        self.dtors = []
        for func_addr in candidate_functions[1]:
            label = f'fn_{func_addr:08x}'
            symbol = DolSymbol(self, label, func_addr, None)
            self._symbol_map[label] = symbol
            self.dtors.append(symbol)

        return True
