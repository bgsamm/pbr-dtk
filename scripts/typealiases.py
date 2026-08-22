from ctypes import (
    _SimpleCData,
    c_int8 as s8,
    c_int16 as s16,
    c_int32 as s32,
    c_int64 as s64,
    c_uint8 as u8,
    c_uint16 as u16,
    c_uint32 as u32,
    c_uint64 as u64,
    c_float as f32,
    c_double as f64,
    sizeof,
)
from typing import overload

type ctype = type[_SimpleCData]

_STR_TO_TYPE = {
    "u8": u8,
    "u16": u16,
    "u32": u32,
    "u64": u64,
    "s8": s8,
    "s16": s16,
    "s32": s32,
    "s64": s64,
    "f32": f32,
    "f64": f64,
}

_TYPE_TO_STR = {
    u8: "u8",
    u16: "u16",
    u32: "u32",
    u64: "u64",
    s8: "s8",
    s16: "s16",
    s32: "s32",
    s64: "s64",
    f32: "f32",
    f64: "f64",
}


def str_to_type(name: str) -> ctype:
    return _STR_TO_TYPE[name]


def type_to_str(dtype: ctype) -> str:
    return _TYPE_TO_STR[dtype]


@overload
def cast(value: int, dtype: ctype) -> int: ...
@overload
def cast(value: float, dtype: ctype) -> float: ...
def cast(value: int | float, dtype: ctype) -> int | float:
    return dtype(value).value


__all__ = [
    "s8",
    "s16",
    "s32",
    "s64",
    "u8",
    "u16",
    "u32",
    "u64",
    "f32",
    "f64",
    "ctype",
    "str_to_type",
    "type_to_str",
    "cast",
    "sizeof",
]
