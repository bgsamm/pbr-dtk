from typealiases import *
import struct

_fmt_map = {
    u8: "B",
    u16: "H",
    u32: "I",
    s8: "b",
    s16: "h",
    s32: "i",
    f32: "f",
    f64: "d",
}


# Note: assumes big-endian byte order
class BytesReader:
    def __init__(self, data):
        self._view = memoryview(data)

    def __len__(self):
        return len(self._view)

    def read(self, type: ctype, offset: int) -> int:
        return struct.unpack_from(f">{_fmt_map[type]}", self._view, offset)[0]

    def read_many(self, type: ctype, offset: int, n: int) -> tuple[int, ...]:
        return struct.unpack_from(f">{n}{_fmt_map[type]}", self._view, offset)

    def get_range(self, offset: int, size: int) -> memoryview:
        return self._view[offset : offset + size]

    @classmethod
    def from_file(cls, path):
        with open(path, "rb") as f:
            data = f.read()
        return cls(data)


class BytesWriter(BytesReader):
    def write(self, type: ctype, offset: int, value: int):
        struct.pack_into(f">{_fmt_map[type]}", self._view, offset, value)
