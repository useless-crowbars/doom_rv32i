#ifndef I_VIDEO_PAJSERI
#define I_VIDEO_PAJSERI

#include "doomtype.h"

#define LPALETTE (byte*)0x10031c00

#define BUFFER_SWITCH 0x50000008

#define GPU_ADDR1 0x20000000
#define GPU_ADDR2 0x20004000

#define FRAMEBUFFER ((*((byte*)BUFFER_SWITCH)) ? ((byte*)GPU_ADDR2) : ((byte*)GPU_ADDR1))

#endif
