#include "d_main.h"
#include "doomdef.h"
#include "doomstat.h"
#include "i_system.h"
#include "m_argv.h"
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

void I_FinishUpdate(void)
{
	static int lasttic;
	int tics;
	int i;

	static uint32_t *bmdata;
	int y, x;
	for (y = 0; y < SCREENHEIGHT; y++) {
		const uint8_t *screenline = &screens[0][y * SCREENWIDTH];
		int xt2 = 0;
		for (x = 0; x < SCREEN_WIDTH; x++) {
			int col = screenline[x];
			int lx, ly;
			uint32_t rgb = (lpalette[col * 3 + 0] << 0) | (lpalette[col * 3 + 1] << 8) | (lpalette[col * 3 + 2] << 16) | 0xff000000;
			write_screen(x, SCREENHEIGHT - 1 - y, rgb);
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

void I_StartTic ()
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
		printf("key event: %d %d\n", event.type, rc);
	}
}
