import struct

# Note: assumes big-endian byte order
class BytesReader:
    _fmt_map = {
        'uchar'  : 'B',
        'ushort' : 'H',
        'uint'   : 'I',
        'char'   : 'b',
        'short'  : 'h',
        'int'    : 'i',
        'float'  : 'f',
        'double' : 'd',
    }

    def __init__(self, data):
        self._view = memoryview(data)

    def __len__(self):
        return len(self._view)

    def read(self, type: str, offset: int, n: int = 1) -> int:
        fmt = self._fmt_map[type]
        result = struct.unpack_from(f'>{n}{fmt}', self._view, offset)
        if n == 1:
            return result[0]
        return result

    def get_range(self, offset: int, size: int) -> memoryview:
        return self._view[offset:offset + size]
    
    @classmethod
    def from_file(cls, path):
        with open(path, 'rb') as f:
            data = f.read()
        return cls(data)
