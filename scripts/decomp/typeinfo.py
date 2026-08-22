from dataclasses import dataclass, field
from typing import Iterator
from typealiases import *


@dataclass
class TypeInfo:
    pass


@dataclass
class VoidType(TypeInfo):
    pass


@dataclass
class NumericType(TypeInfo):
    dtype: ctype

    @property
    def is_signed_integer(self) -> bool:
        return self.dtype in {s8, s16, s32, s64}

    @property
    def is_unsigned_integer(self) -> bool:
        return self.dtype in {u8, u16, u32, u64}

    @property
    def is_integer(self) -> bool:
        return self.is_signed_integer or self.is_unsigned_integer

    @property
    def is_float_single(self) -> bool:
        return self.dtype is f32

    @property
    def is_float_double(self) -> bool:
        return self.dtype is f64

    @property
    def is_float(self) -> bool:
        return self.is_float_single or self.is_float_double


@dataclass
class PointerType(TypeInfo):
    target: int


@dataclass
class StructType(TypeInfo):
    fields: dict[int, int] = field(default_factory=dict)
    name: str | None = None

    def __getitem__(self, offset: int) -> int:
        # TODO Handle unknown offsets gracefully?
        return self.fields[offset]

    def __iter__(self) -> Iterator[tuple[int, int]]:
        yield from sorted(self.fields.items())


__all__ = ["TypeInfo", "VoidType", "NumericType", "PointerType", "StructType"]
