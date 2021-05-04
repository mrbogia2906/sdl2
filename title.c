#include "title.h"

static void logic(void);
static void draw(void);
static void drawLogo(void);

static SDL_Texture *header;
static int reveal = 0;
static int timeout;

void initTitle(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);

	header = loadTexture("gfx/header1.png");

	timeout = FPS * 5;
}

static void logic(void)
{
	doBackground();

	doStarfield();

	if (reveal < SCREEN_HEIGHT)
	{
		reveal+=2;
	}

	if (app.keyboard[SDL_SCANCODE_LCTRL])
	{
		initStage();
	}
}

static void draw(void)
{
	drawBackground();

	drawStarfield();

	drawLogo();

	if (--timeout % 40 < 20)
	{
		drawText(470, 600, 255, 255, 255, "PRESS FIRE TO PLAY!");
	}
}

static void drawLogo(void)
{
	SDL_Rect r;

	r.x = 0;
	r.y = 0;

	SDL_QueryTexture(header, NULL, NULL, &r.w, &r.h);

	r.h = MIN(reveal, r.h);

	blitRect(header, &r, (SCREEN_WIDTH / 2) - (r.w / 2), 100);

}
