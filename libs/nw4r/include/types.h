// From doldecomp/ogws (CC0), include/types.h
// Shim for the ogws nw4r headers: base types come from our SDK headers
#ifndef NW4R_SHIM_TYPES_H
#define NW4R_SHIM_TYPES_H

#ifdef __cplusplus
#include <cstdarg>
#include <cstddef>
#include <new>
#else
#include <stdarg.h>
#include <stddef.h>
#endif

#include <decomp/compat.h>
#include <decomp/decomp.h>
#include <decomp/lang.h>
#include <macros.h>
#include <revolution/types.h>

typedef int UNKWORD;
typedef void UNKTYPE;
typedef void (*funcptr_t)(void);

#endif
