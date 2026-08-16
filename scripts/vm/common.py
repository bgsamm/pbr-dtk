from typing import overload
from .symval import SymbolicValue

type SymOrInt = SymbolicValue | int


@overload
def sign_ext(simm: int, bits: int) -> int: ...
@overload
def sign_ext(simm: SymbolicValue, bits: int) -> SymbolicValue: ...
def sign_ext(simm: SymOrInt, bits: int):
    sign_bit = 1 << (bits - 1)
    return (simm ^ sign_bit) - sign_bit


__all__ = ["SymOrInt", "sign_ext"]
