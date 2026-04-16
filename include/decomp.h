#ifndef DECOMP_H
#define DECOMP_H

#define __CONCAT(x, y)          x ## y
#define   CONCAT(x, y)          __CONCAT(x, y)

#define ARRAY_LENGTH(x)              (sizeof(x) / sizeof(x[0]))

#define ROUNDUP(x, a)           (((x) + ((a) - 1)) & ~((a) - 1))
#define PTR_ROUNDUP(x, a)       ((void*)ROUNDUP((unsigned long)x, a))

#define ROUNDDOWN(x, a)         (((x)) & ~((a) - 1))
#define PTR_ROUNDDOWN(x, a)     ((void*)ROUNDDOWN((unsigned long)x, a))

#define MEM_CLEAR(x)            __memclr((x), sizeof(*(x)))

#ifdef __MWERKS__
#define ADDRESS(addr) : (addr)
#else
#define ADDRESS(addr)
#endif

/* Macros for Matching */

#ifndef NON_MATCHING

#define NO_INLINE   __attribute__((never_inline))

#define DECOMP_FORCE_ACTIVE(module, args...)        \
    void fake_function(int a, ...);                 \
    void CONCAT(FORCEACTIVE##module, __LINE__)();   \
    void CONCAT(FORCEACTIVE##module, __LINE__)() {  \
        fake_function(0, args);                     \
    }

#define DECOMP_FORCE_LITERAL(module, ...)                                   \
    void CONCAT(FORCELITERAL##module, __LINE__)();                          \
    void CONCAT(FORCELITERAL##module, __LINE__)() {                         \
        (__VA_ARGS__);                                                      \
    }

#define DECOMP_FORCE_DTOR(module, cls)                                   \
    void CONCAT(FORCEDTOR##module##cls, __LINE__)();                     \
    void CONCAT(FORCEDTOR##module##cls, __LINE__)() {                    \
        cls dummy;                                                       \
        dummy.~cls();                                                    \
    }

#else
#define NO_INLINE
#define DECOMP_FORCE_ACTIVE(module, args...)
#define DECOMP_FORCE_LITERAL(module, ...)
#define DECOMP_FORCE_DTOR(module, cls)
#endif // NON_MATCHING

#ifndef __MWERKS__

#define asm
#define register
#define __attribute__(x)
#define __declspec(x)

extern void         __sync();
extern unsigned int __cntlzw(unsigned int value);
extern void         __memclr(void* buffer, int len);
extern unsigned int __rlwimi(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern void*        __alloca(unsigned int blockSize);
extern int          __abs(int n);

#endif

typedef unsigned char   undefined;
typedef unsigned short  undefined2;
typedef unsigned long   undefined4;

#endif // DECOMP_H
