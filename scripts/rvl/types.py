from ctypes import (
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
    sizeof
)
import ctypes

type ctype = type[ctypes._CData]

C_TYPE_LOOKUP = {
    'u8'  : u8,
    'u16' : u16,
    'u32' : u32,
    'u64' : u64,
    's8'  : s8,
    's16' : s16,
    's32' : s32,
    's64' : s64,
    'f32' : f32,
    'f64' : f64
}

C_TYPE_RLOOKUP = {
    u8  : 'u8',
    u16 : 'u16',
    u32 : 'u32',
    u64 : 'u64',
    s8  : 's8',
    s16 : 's16',
    s32 : 's32',
    s64 : 's64',
    f32 : 'f32',
    f64 : 'f64'
}
