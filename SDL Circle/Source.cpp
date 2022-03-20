#include<SDL.h>
#include<iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 900, win_height = 700;

void deInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		deInit(1);
	}

	win = SDL_CreateWindow("Rain", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("Couldn't creat window! Error: %s", SDL_GetError());
		system("pause");
		deInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't creat renderer! Error: %s", SDL_GetError());
		system("pause");
		deInit(1);
	}
}

void mathCoordsToScreen(double x, double y, double scale, int centerx, int centery, int &sx, int &sy)
{
	sx = round(centerx + x * scale);
	sy = round(centery + y * scale);
}

double findY(double x, double x0, double y0, double rad)
{
	return sqrt(rad * rad - (x - x0) * (x - x0)) + y0;
}

void drawFilledCircleM1()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);

	double x1, y1, x2, y2, scale = 2.0;
	int sx1, sy1, sx2, sy2;

	x1 = -100; x2 = 100;
	y1 = y2 = 0;
	
	mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
	mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);
	SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);

	y1 = -100; y2 = 100;
	x1 = x2 = 0;
	
	mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
	mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);
	SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

	for (int rad = 100; rad >= 0; rad -= 1)
	{
		for (x1 = -100; x1 < 101; x1 += 0.0375)
		{
			y1 = findY(x1, 0, 0, rad);
			mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
			SDL_RenderDrawPoint(ren, sx1, sy1);

			y1 = -y1;
			mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
			SDL_RenderDrawPoint(ren, sx1, sy1);
		}
	}
}

void drawFilledCircleM2()
{
	SDL_Rect r = { 0, 0, 3, 3 };

	double scale = 2, x1, y1, x2, y2;
	int sx1, sy1, sx2, sy2;

	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);

	x1 = -100; x2 = 100;
	y1 = y2 = 0;

	mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
	mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);

	SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);

	y1 = -100; y2 = 100;
	x1 = x2 = 0;

	mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
	mathCoordsToScreen(x2, y2, scale, win_width / 2, win_height / 2, sx2, sy2);

	SDL_RenderDrawLine(ren, sx1, sy1, sx2, sy2);

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);

	double rad = M_PI / 180.0;

	for (int i = 100; i >= 0; i--)
	{
		for (double alpha = 0; alpha <= 360; alpha += 0.5)
		{
			x1 = i * cos(alpha * rad);
			y1 = i * sin(alpha * rad);

			mathCoordsToScreen(x1, y1, scale, win_width / 2, win_height / 2, sx1, sy1);
			r.x = sx1 - 1;
			r.y = sy1 - 1;
			SDL_RenderFillRect(ren, &r);
		}
	}

	SDL_RenderPresent(ren);
}

void drawFilledCircleM3()
{

}

int main(int argc, char* argv[])
{
	init();

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);

	drawFilledCircleM2();

	SDL_Delay(2500);

	deInit(0);
	return 0;
}