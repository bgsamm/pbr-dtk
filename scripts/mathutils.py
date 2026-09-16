# TODO(samm) Make 32-bit nature clear in name?
def rotate_l(x, y):
    return ((x << y) | (x >> (32 - y))) & 0xFFFF_FFFF


# TODO(samm) Make 32-bit nature clear in name?
def create_mask(x, y):
    a, b = (x, y) if x <= y else (y + 1, x - 1)
    bitmask = ((1 << (b - a + 1)) - 1) << (31 - b)
    if x > y:
        bitmask = ~bitmask
    return bitmask & 0xFFFF_FFFF


def sign_ext(simm, bits):
    sign_bit = 1 << (bits - 1)
    mask = (1 << bits) - 1
    return ((simm & mask) ^ sign_bit) - sign_bit
