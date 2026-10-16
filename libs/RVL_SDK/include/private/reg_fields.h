// Imported from koopthekoopa/wii-ipl (CC0), libs/RVL_SDK/include/private/reg_fields.h
#ifndef PRIVATE_REGISTER_FIELDS_H
#define PRIVATE_REGISTER_FIELDS_H

// gx.h carries the older GX-specific variants of these macros
#undef GET_REG_FIELD
#undef SET_REG_FIELD
#undef OLD_SET_REG_FIELD

#define GET_REG_FIELD(reg, size, shift)                                                                                                              \
    ((u32)((reg) & (((1 << (size)) - 1) << (shift))) >> (shift)) /* implementation that matches debug RVL_SDK */
#define OLD_GET_REG_FIELD(reg, size, shift) (((reg) >> (shift)) & ((1 << (size)) - 1)) /* original dolsdk2004 implementation */

#define SET_REG_FIELD(line, reg, size, shift, val)                                                                                                   \
    do {                                                                                                                                             \
        (reg) = ((u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift)));                                                    \
    } while (0)

#define OLD_SET_REG_FIELD(line, reg, size, shift, val)                                                                                               \
    do {                                                                                                                                             \
        (reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift));                                                          \
    } while (0)

#endif  // PRIVATE_REGISTER_FIELDS_H
