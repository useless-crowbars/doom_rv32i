#include "d_main.h"
#include "doomdef.h"
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"

#include "./gpu.h"

#ifdef __riscv
static byte* lpalette = (byte*) 0x10032000;
#else
static byte lpalette[256 * 3];
#endif

void I_InitGraphics(void)
{
	init_screen();
}

void I_ShutdownGraphics(void)
{
	cleanup();
}

void I_SetPalette(byte *palette)
{
	memcpy(lpalette, palette, 256 * 3 * sizeof(byte));
}

void I_UpdateNoBlit(void)
{
}

__attribute__((section(".critical")))
void I_FinishUpdate(void)
{
	int y, x;
	for (y = 0; y < SCREEN_HEIGHT; y += 2) {
		for (x = 0; x < SCREEN_WIDTH; x += 2) {
			uint8_t col = ((uint8_t*)&screens[0][y * SCREENWIDTH])[x];
			uint32_t b = lpalette[col * 3 + 2];
			uint32_t g = lpalette[col * 3 + 1];
			uint32_t r = lpalette[col * 3 + 0];

			uint32_t bgr = 0xff000000 | (b << 16) | (g << 8) | r;

			write_screen(x / 2, y / 2, bgr);
		}
	}

	update_screen();
}
void I_ReadScreen(byte *scr)
{
	memcpy(scr, screens[0], SCREENWIDTH * SCREENHEIGHT);
}

void I_StartFrame()
{
}

#define KEY_ADDR 0x30000000UL
#define ESC 0x80
#define SPACE 0x40
#define D 0x20
#define S 0x10
#define A 0x08
#define W 0x04
#define SHIFT 0x02
#define CTRL 0x01

uint8_t kb_status = 0;

void I_StartTic()
{
	poll_keyboard();
	volatile uint8_t* keyboard = (uint8_t*)KEY_ADDR;
	uint8_t key = *keyboard;
	if (ESC & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_PAUSE;
		D_PostEvent(&event);
		kb_status |= ESC;
	} else if (kb_status & ESC) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_PAUSE;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~ESC;
	}

	if (SPACE & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = ' ';
		D_PostEvent(&event);
		kb_status |= SPACE;
	} else if (kb_status & SPACE) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = ' ';
		D_PostEvent(&event);
		kb_status &= (uint8_t)~SPACE;
	}

	if (D & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_RIGHTARROW;
		D_PostEvent(&event);
		kb_status |= D;
	} else if (kb_status & D) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_RIGHTARROW;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~D;
	}

	if (S & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_DOWNARROW;
		D_PostEvent(&event);
		kb_status |= S;
	} else if (kb_status & S) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_DOWNARROW;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~S;
	}

	if (A & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_LEFTARROW;
		D_PostEvent(&event);
		kb_status |= A;
	} else if (kb_status & A) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_LEFTARROW;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~A;
	}

	if (W & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_UPARROW;
		D_PostEvent(&event);
		kb_status |= W;
	} else if (kb_status & W) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_UPARROW;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~W;
	}

	if (SHIFT & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_PAUSE;
		D_PostEvent(&event);
		kb_status |= SHIFT;
	} else if (kb_status & SHIFT) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_PAUSE;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~SHIFT;
	}

	if (CTRL & key) {
		event_t event;
		event.type = ev_keydown;
		event.data1 = KEY_RCTRL;
		D_PostEvent(&event);
		kb_status |= CTRL;
	} else if (kb_status & CTRL) {
		event_t event;
		event.type = ev_keyup;
		event.data1 = KEY_RCTRL;
		D_PostEvent(&event);
		kb_status &= (uint8_t)~CTRL;
	}
	
}
