#ifndef REVOLUTION_OS_ERROR_H
#define REVOLUTION_OS_ERROR_H

#include <revolution/types.h>

#include <revolution/os/OSContext.h>
#include <revolution/os/OSException.h>

#include <revolution/gx/GXStruct.h>

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OS_ERROR_MAX 15

typedef u16 OSError;
typedef void (*OSErrorHandler)(OSError, OSContext*, ...);

OSErrorHandler OSSetErrorHandler(OSError error, OSErrorHandler handler);

void OSReport(const char* msg, ...);
void OSVReport(const char* msg, va_list list);

void OSPanic(const char* file, int line, const char* msg, ...);

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)
#define OSAssertMsg(exp, msg)                                                                                                                  \
    if (!(exp))                                                                                                                                      \
    OSHalt(msg)
#define OSAssertVMsg(exp, ...)                                                                                                                 \
    if (!(exp))                                                                                                                                      \
    OSPanic(__FILE__, __LINE__, __VA_ARGS__)

void OSRegisterVersion(const char* version);

void OSFatal(GXColor front, GXColor back, const char* msg);

#ifdef __cplusplus
}
#endif

#endif  // REVOLUTION_OS_ERROR_H
