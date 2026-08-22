from typing import Callable, overload
from typealiases import ctype, cast
import operator
import re

type _OpFunc = Callable[[int, int], int]
type _CompFunc = Callable[[int, int], bool]

type SymOrInt = SymbolicValue | int
type SymOrNone = SymbolicValue | None


class SymbolicValue:
    Unknown: SymbolicValue

    def __init__(self, value: int):
        self._value = value

    @property
    def value(self) -> int:
        return self._value

    @property
    def is_known(self) -> bool:
        return self is not SymbolicValue.Unknown

    @property
    def is_unknown(self) -> bool:
        return self is SymbolicValue.Unknown

    def _process_operand(self, other: SymOrInt) -> SymbolicValue:
        if isinstance(other, SymbolicValue):
            return other
        if isinstance(other, int):
            return SymbolicValue(other)
        return NotImplemented

    def _apply_op(self, other: SymOrInt, op_func: _OpFunc) -> SymbolicValue:
        if (other := self._process_operand(other)) is NotImplemented:
            return NotImplemented
        if self.is_unknown or other.is_unknown:
            return SymbolicValue.Unknown
        return SymbolicValue(op_func(self._value, other._value))

    def _apply_rop(self, other: SymOrInt, op_func: _OpFunc) -> SymbolicValue:
        if (other := self._process_operand(other)) is NotImplemented:
            return NotImplemented
        if self.is_unknown or other.is_unknown:
            return SymbolicValue.Unknown
        return SymbolicValue(op_func(other._value, self._value))

    def _apply_comp(
        self, other: SymOrInt, comp_func: _CompFunc, on_unknown: bool = False
    ) -> bool:
        if (other := self._process_operand(other)) is NotImplemented:
            return NotImplemented
        if self.is_unknown or other.is_unknown:
            return on_unknown
        return comp_func(self._value, other._value)

    def __invert__(self) -> SymbolicValue:
        if self.is_unknown:
            return SymbolicValue.Unknown
        return SymbolicValue(~self._value)

    def __neg__(self):
        if self.is_unknown:
            return SymbolicValue.Unknown
        return SymbolicValue(-self.value)

    def __add__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.add)

    def __sub__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.sub)

    def __mul__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.mul)

    def __and__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.and_)

    def __or__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.or_)

    def __xor__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.xor)

    def __lshift__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.lshift)

    def __rshift__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_op(other, operator.rshift)

    def __radd__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.add)

    def __rsub__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.sub)

    def __rand__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.and_)

    def __ror__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.or_)

    def __rxor__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.xor)

    def __rlshift__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.lshift)

    def __rrshift__(self, other: SymOrInt) -> SymbolicValue:
        return self._apply_rop(other, operator.rshift)

    def __eq__(self, other: SymOrInt) -> bool:
        return self._apply_comp(other, operator.eq)

    def __ne__(self, other: SymOrInt) -> bool:
        # Following NaN convention, i.e. every value (incl. NaN) is != NaN
        return self._apply_comp(other, operator.ne, on_unknown=True)

    def __lt__(self, other: SymOrInt) -> bool:
        return self._apply_comp(other, operator.lt)

    def __le__(self, other: SymOrInt) -> bool:
        return self._apply_comp(other, operator.le)

    def __gt__(self, other: SymOrInt) -> bool:
        return self._apply_comp(other, operator.gt)

    def __ge__(self, other: SymOrInt) -> bool:
        return self._apply_comp(other, operator.ge)

    def __format__(self, format_spec: str) -> str:
        def sub_qmarks(match: re.Match[str]) -> str:
            prefix = match.group(1)
            digits = match.group(2)
            return (prefix or "") + ("?" * len(digits))

        result = format(self._value, format_spec)
        if self.is_unknown:
            result = re.sub(r"(0[boxX])?([0-9a-fA-F]+)", sub_qmarks, result)
        return result

    def __hash__(self) -> int:
        if self.is_unknown:
            return hash(SymbolicValue.Unknown)
        return hash(self._value)

    def __repr__(self) -> str:
        if self.is_unknown:
            return "SymbolicValue.Unknown"
        return f"SymbolicValue({self._value})"

    def __str__(self) -> str:
        if self.is_unknown:
            return "?"
        return str(self._value)

    def cast(self, dtype: ctype) -> SymbolicValue:
        if self.is_unknown:
            return SymbolicValue.Unknown
        return SymbolicValue(cast(self.value, dtype))


class _UnknownSymbolicValue(SymbolicValue):
    def __init__(self):
        super().__init__(0)

    @property
    def value(self) -> int:
        raise TypeError()


SymbolicValue.Unknown = _UnknownSymbolicValue()


def ensure_symbolic(value: SymOrInt) -> SymbolicValue:
    if isinstance(value, int):
        return SymbolicValue(value)
    return value
