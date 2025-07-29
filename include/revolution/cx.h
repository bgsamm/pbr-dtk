#ifndef __CX_H__
#define __CX_H__

#ifdef __cplusplus
extern "C" {
#endif

u32 CXGetUncompressedSize(const void *srcp);
void CXUncompressLZ(const void* srcp, void* destp);

#ifdef __cplusplus
}
#endif

#endif  // __CX_H__
