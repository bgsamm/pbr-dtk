from typing import Iterable
from typealiases import type_to_str
from .typeinfo import *
from .typereg import TypeRegistry


def _to_type_str(type: TypeInfo, registry: TypeRegistry) -> str:
    match type:
        case VoidType():
            return "void"
        case NumericType():
            return type_to_str(type.dtype)
        case PointerType():
            target_type = registry[type.target]
            return _to_type_str(target_type, registry) + "*"
        case StructType():
            return type.name or "UnkStruct"
        case _:
            raise TypeError()


def _build_struct(struct: StructType, registry: TypeRegistry) -> str:
    TAB = "    "

    def align(offset: int, n: int) -> int:
        return (offset + n - 1) // n * n

    def pre_comment(offset: int, pad: int) -> str:
        # + 2 accounts for 0x prefix
        return f"/* {offset:#0{pad + 2}x} */"

    def field_name(offset: int, pad: int) -> str:
        return f"_{offset:0{pad}x}"

    def make_field(offset: int, info: TypeInfo, pad: int) -> str:
        type = _to_type_str(info, registry)
        return f"{TAB}{pre_comment(offset, pad)} {type} {field_name(offset, pad)};\n"

    def make_dummy(offset: int, size: int, pad: int) -> str:
        return f"{TAB}{pre_comment(offset, pad)} u8 _pad{field_name(offset, pad)}[{size}];\n"

    if struct.name:
        s = f"struct {struct.name} {{\n"
    else:
        s = "struct {{\n"

    if len(struct.fields) > 0:
        min_offset = min(struct.fields)
        max_offset = max(struct.fields)
        pad = len(f"{max_offset:x}")

        fields = sorted(struct.fields.items(), reverse=True)

        offset = min(min_offset, 0)
        while offset <= max_offset:
            assert len(fields) > 0

            field_off, field_var = fields[-1]
            field_type = registry[field_var]
            field_size = registry.sizeof(field_type)

            if offset == field_off:
                s += make_field(field_off, field_type, pad)
                offset += field_size
                fields.pop()
            else:
                offset = align(offset, field_size)
                if offset != field_off:
                    s += make_dummy(offset, field_off - offset, pad)
                    offset = field_off

    s += "}"

    return s


def gen_function_signature(
    name: str,
    arguments: Iterable[TypeInfo],
    return_type: TypeInfo,
    registry: TypeRegistry,
) -> str:
    arg_strs = []
    for i, arg in enumerate(arguments):
        type_str = _to_type_str(arg, registry)
        arg_strs.append(f"{type_str} arg{i}")

    type_str = _to_type_str(return_type, registry)
    return f"{type_str} {name}({', '.join(arg_strs)})"


def gen_struct(struct: StructType, registry: TypeRegistry) -> str:
    return _build_struct(struct, registry) + ";\n"
