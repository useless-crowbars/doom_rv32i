#ifndef I_VIDEO_PAJSERI
#define I_VIDEO_PAJSERI

#include "doomtype.h"

extern byte* gpu;

#ifdef __riscv
extern byte* lpalette;
#else
extern byte lpalette[];
#endif

#endif
