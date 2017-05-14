#include <iostream>
#include <SDL.h>
#include <math.h>

#define _USE_MATH_DEFINES

unsigned
window_width = 640,
window_height = 480,
padding = 20;

struct Point
{
	double x;
	double y;

	Point(): x(0), y(0) { }
	Point(double _x, double _y): x(_x), y(_y) { }

	Point& operator +(const Point& o)
	{
		x = x + o.x;
		y = y + o.y;

		return *this;
	}
};

struct Color
{
	Uint8 alpha;
	Uint8 red;
	Uint8 green;
	Uint8 blue;

	Color(Uint8 a, Uint8 r, Uint8 g, Uint8 b): alpha(a), red(r), green(g), blue(b)
	{
	}
};

void SDL_RenderCircle(SDL_Renderer *renderer, const Point & center, float radius);
void draw_circle(SDL_Renderer *renderer, Point center, int radius, Color color);

int wWinMain(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, window_width, window_height, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_bool done = SDL_FALSE;

	while (!done) {
		SDL_Event event;

		SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
		
		// Draw OY axis
		SDL_RenderDrawLine(renderer, padding, padding, padding, window_height - padding);

		// Draw OX axis
		SDL_RenderDrawLine(renderer, padding, window_height - padding, window_width - padding, window_height - padding);

		SDL_RenderCircle(renderer, Point(100, 100), 100);

		draw_circle(renderer, Point(100, 100), 100, Color(0, 0, 0, 0));

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				done = SDL_TRUE;
			}
		}
	}

	SDL_Quit();

	return 0;
}

void SDL_RenderCircle(SDL_Renderer *renderer, const Point & center, float radius)
{
	int sides = 2 * M_PI * radius / 2;

	float d_a = 2 * M_PI / sides,
		angle = d_a;

	Point start, end;
	end.x = radius;
	end.y = 0.0f;
	end = end + center;
	for (int i = 0; i != sides; i++)
	{
		start = end;
		end.x = cos(angle) * radius;
		end.y = sin(angle) * radius;
		end = end + center;
		angle += d_a;
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
}

void draw_circle(SDL_Renderer *renderer, Point center, int radius, Color color)
{
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy*dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
			}
		}
	}
}