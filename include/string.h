#ifndef STRING_H
#define STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

void *memcpy(void *, const void *, unsigned long);
void *memset(void *dest, int c, size_t n);

#ifdef __cplusplus
}
#endif

#endif // STRING_H
