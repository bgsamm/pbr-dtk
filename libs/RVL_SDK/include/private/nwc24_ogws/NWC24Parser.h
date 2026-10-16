// From doldecomp/ogws (CC0), include/revolution/NWC24/NWC24Parser.h
#ifndef RVL_SDK_NWC24_PARSER_H
#define RVL_SDK_NWC24_PARSER_H
#include <private/nwc24_ogws/NWC24Types.h>

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

const char *NWC24GetMIMETypeStr(NWC24MIMEType type);
const char *NWC24GetCharsetStr(NWC24Charset charset);
const char *NWC24GetEncodingStr(NWC24Encoding encoding);

#ifdef __cplusplus
}
#endif
#endif
