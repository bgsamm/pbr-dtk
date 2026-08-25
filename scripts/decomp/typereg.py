from typing import Iterator
from typealiases import *
from .typeinfo import *


class TypeRegistry:
    _type_map: list[TypeInfo | int]

    def __init__(self) -> None:
        self._type_map = []

    def __getitem__(self, node: int) -> TypeInfo:
        return self._get_type(node)

    def __iter__(self) -> Iterator[TypeInfo]:
        for value in self._type_map:
            if isinstance(value, TypeInfo):
                yield value

    def _find_root(self, node: int) -> int:
        # Find root
        root = node
        while True:
            parent = self._type_map[root]
            if isinstance(parent, TypeInfo):
                break
            root = parent

        if node != root:
            # Path compression
            curr = node
            while (parent := self._type_map[curr]) != root:
                self._type_map[curr] = root
                assert isinstance(parent, int)
                curr = parent

        return root

    def _get_type(self, node: int) -> TypeInfo:
        root = self._find_root(node)
        value = self._type_map[root]
        assert isinstance(value, TypeInfo)
        return value

    def _set_type(self, node: int, type: TypeInfo) -> None:
        root = self._find_root(node)
        self._type_map[root] = type

    def _attach(self, parent: int, child: int) -> int:
        parent_root = self._find_root(parent)
        child_root = self._find_root(child)
        self._type_map[child_root] = parent_root
        return parent_root

    def _numeric_union(self, left: NumericType, right: NumericType) -> NumericType:
        # Prefer wider floating-point type
        if left.is_float and right.is_float:
            return right if sizeof(right.dtype) > sizeof(left.dtype) else left
        # Prefer floating-point over integer type
        if left.is_float:
            return left
        if right.is_float:
            return right
        # Prefer narrower integer type
        return right if sizeof(right.dtype) < sizeof(left.dtype) else left

    def _pointer_union(self, left: PointerType, right: PointerType) -> PointerType:
        left.target = self.unify(left.target, right.target)
        return left

    def _struct_union(self, left: StructType, right: StructType) -> StructType:
        for offset, type_ref in right:
            self.add_struct_field(left, offset, type_ref)
        return left

    def _create_node(self, type: TypeInfo) -> int:
        id = len(self._type_map)
        self._type_map.append(type)
        return id

    def void(self) -> int:
        return self._create_node(VoidType())

    def numeric(self, dtype: ctype) -> int:
        return self._create_node(NumericType(dtype))

    def pointer(self, target: int) -> int:
        return self._create_node(PointerType(target))

    def struct(self, fields: dict[int, int]) -> int:
        return self._create_node(StructType(fields))

    def struct_pointer(self, fields: dict[int, int]) -> int:
        struct_ref = self.struct(fields)
        return self.pointer(struct_ref)

    def add_struct_field(self, struct: StructType, offset: int, field: int) -> None:
        # TODO Handle overlapping fields (union?)
        if old_field := struct.fields.get(offset):
            struct.fields[offset] = self.unify(old_field, field)
        else:
            struct.fields[offset] = field

    def are_unified(self, left: int, right: int) -> bool:
        return self._find_root(left) == self._find_root(right)

    def unify(self, left: int, right: int) -> int:
        if self.are_unified(left, right):
            return left

        left_type = self._get_type(left)
        right_type = self._get_type(right)

        match (left_type, right_type):
            # Same-type unions
            case (NumericType(), NumericType()):
                union = self._numeric_union(left_type, right_type)
                self._set_type(left, union)
                return self._attach(left, right)
            case (PointerType(), PointerType()):
                union = self._pointer_union(left_type, right_type)
                self._set_type(left, union)
                return self._attach(left, right)
            case (StructType(), StructType()):
                union = self._struct_union(left_type, right_type)
                self._set_type(left, union)
                return self._attach(left, right)
            # Struct w/ non-struct - assume non-struct is first field of struct
            case (StructType(), NumericType()) | (StructType(), PointerType()):
                self.add_struct_field(left_type, 0, right)
                # Do not attach!!!
                return left
            case (NumericType(), StructType()) | (PointerType(), StructType()):
                self.add_struct_field(right_type, 0, left)
                # Do not attach!!!
                return right
            # Pointer w/ numeric - prefer pointer
            # TODO Handle non-u32 NumericType differently (union?)
            case (PointerType(), NumericType()):
                assert right_type.dtype is u32
                return self._attach(left, right)
            case (NumericType(), PointerType()):
                assert left_type.dtype is u32
                return self._attach(right, left)
            # Void w/ any - prefer non-void
            case (_, VoidType()):
                return self._attach(left, right)
            case (VoidType(), _):
                return self._attach(right, left)
            # Unhandled combinations
            case _:
                raise TypeError()

    def sizeof(self, type: TypeInfo) -> int:
        match type:
            case NumericType():
                return sizeof(type.dtype)
            case PointerType():
                return sizeof(u32)
            case StructType():
                if len(type.fields) == 0:
                    return 0
                last_offset = max(type.fields)
                last_field_type = self._get_type(type.fields[last_offset])
                # TODO Account for struct alignment (max field size?)
                return last_offset + self.sizeof(last_field_type)
            # Intenionally raising error for VoidType
            case _:
                raise TypeError()
