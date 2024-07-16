#include "d_main.h"
#include "doomdef.h"
#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"

#include "./gpu.h"

static byte lpalette[256 * 3];

void I_InitGraphics(void)
{
	init_screen();
}

void I_ShutdownGraphics(void)
{
	end = true;
	cleanup();
}

void I_SetPalette(byte *palette)
{
	memcpy(lpalette, palette, sizeof(lpalette));
}

void I_UpdateNoBlit(void)
{
}

int dx[4] = {0, 0, 1, 1};
int dy[4] = {0, 1, 0, 1};

void I_FinishUpdate(void)
{
	int y, x;
	for (y = 0; y < SCREEN_HEIGHT; y += 2) {
		for (x = 0; x < SCREEN_WIDTH; x += 2) {
			uint32_t b = 0;
			uint32_t g = 0;
			uint32_t r = 0;

			for (int k = 0; k < 4; k++) {
				uint8_t col = ((uint8_t*)&screens[0][(y + dy[k]) * SCREENWIDTH])[x + dx[k]];
				b += lpalette[col * 3 + 2];
				g += lpalette[col * 3 + 1];
				r += lpalette[col * 3 + 0];

			}
			b /= 4;
			g /= 4;
			r /= 4;

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

#ifndef __riscv
void I_StartTic()
{
	if (end) {
		I_ShutdownGraphics();
	}

	poll_keyboard();
	if (!change_ack) {
		int rc = 0;

		switch (key_changed) {
		case LEFT:
			rc = KEY_LEFTARROW;
			break;
		case RIGHT:
			rc = KEY_RIGHTARROW;
			break;
		case UP:
			rc = KEY_UPARROW;
			break;
		case DOWN:
			rc = KEY_DOWNARROW;
			break;
		case SPACE:
			rc = ' ';
			break;
		case CTRL:
			rc = KEY_RCTRL;
			break;
		default:
			break;
		}

		event_t event;
		event.type = key_pressed ? ev_keydown : ev_keyup;
		event.data1 = rc;
		D_PostEvent(&event);

		change_ack = true;
		//printf("key event: %d %d\n", event.type, rc);
	}
}
#else
void I_StartTic()
{
	if (*end) {
		I_ShutdownGraphics();
	}

	poll_keyboard();
	if (!*change_ack) {
		int rc = 0;

		switch (*key_changed) {
		case LEFT:
			rc = KEY_LEFTARROW;
			break;
		case RIGHT:
			rc = KEY_RIGHTARROW;
			break;
		case UP:
			rc = KEY_UPARROW;
			break;
		case DOWN:
			rc = KEY_DOWNARROW;
			break;
		case SPACE:
			rc = ' ';
			break;
		case CTRL:
			rc = KEY_RCTRL;
			break;
		default:
			break;
		}

		event_t event;
		event.type = *key_pressed ? ev_keydown : ev_keyup;
		event.data1 = rc;
		D_PostEvent(&event);

		*change_ack = true;
		//printf("key event: %d %d\n", event.type, rc);
	}
}
#endif
