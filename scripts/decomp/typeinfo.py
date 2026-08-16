from rvl.types import *


class TypeInfo:
    def __init__(self):
        pass


class NumericType(TypeInfo):
    def __init__(self, dtype: ctype):
        super().__init__()
        self._type = dtype

    def __str__(self) -> str:
        return C_TYPE_RLOOKUP[self._type]


class PointerType(TypeInfo):
    def __init__(self, target: TypeInfo):
        super().__init__()
        self._target = target

    def __str__(self) -> str:
        return f"{self._target}*"

    @property
    def target(self):
        return self._target


class StructType(TypeInfo):
    def __init__(self, name: str = "MyStruct"):
        super().__init__()
        self.name = name
        self._fields = {}

    def __str__(self) -> str:
        return self.name

    # TODO Something far more robust
    def add_field(self, offset: int, dtype: ctype):
        self._fields[offset] = dtype

    def to_c(self) -> str:
        def align(offset, n):
            return (offset + n - 1) // n * n

        def pre_comment(offset, pad):
            return f"/* 0x{offset:0{pad}x} */"

        def field_name(offset, pad):
            return f"_{offset:0{pad}x}"

        def make_field(offset, dtype, pad):
            type_name = C_TYPE_RLOOKUP[dtype]
            return f"    {pre_comment(offset, pad)} {type_name} {field_name(offset, pad)};\n"

        def make_dummy(offset, size, pad):
            return f"    {pre_comment(offset, pad)} u8 {field_name(offset, pad)}[{size}];\n"

        src_code = f"struct {self.name} {{\n"

        if len(self._fields) > 0:
            max_offset = max(self._fields)
            pad = len(f"{max_offset:x}")

            fields = sorted(self._fields.items(), reverse=True)

            offset = 0
            while offset <= max_offset:
                assert len(fields) > 0

                field_off, field_type = fields[-1]
                if offset == field_off:
                    src_code += make_field(field_off, field_type, pad)
                    offset += sizeof(field_type)
                    fields.pop()
                else:
                    offset = align(offset, sizeof(field_type))
                    if offset != field_off:
                        src_code += make_dummy(offset, field_off - offset, pad)
                        offset = field_off

        src_code += "};\n"

        return src_code
