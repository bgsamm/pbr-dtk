#ifndef SC_H
#define SC_H

#ifdef __cplusplus
extern "C" {
#endif

#define SC_ASPECT_RATIO_4x3         0u
#define SC_ASPECT_RATIO_16x9        1u

#define SC_EURGB60_MODE_OFF           0u
#define SC_EURGB60_MODE_ON            1u

#define SC_PROGRESSIVE_MODE_OFF     0u
#define SC_PROGRESSIVE_MODE_ON      1u

u8 SCGetAspectRatio(void);
u8 SCGetEuRgb60Mode(void);
u8 SCGetProgressiveMode(void);

#ifdef __cplusplus
}
#endif

#endif // VI_H
