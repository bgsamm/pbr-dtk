#ifndef STDDEF_H
#define STDDEF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
typedef unsigned long size_t;
#else
typedef unsigned int size_t;
#endif

#ifdef __cplusplus
}
#endif

#endif // STDDEF_H
