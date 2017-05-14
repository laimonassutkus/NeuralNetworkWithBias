#include <iostream>
#include <SDL.h>
#include <math.h>
#include <memory>

#define _USE_MATH_DEFINES

unsigned
window_width = 640,
window_height = 480,
padding = 20;

float point_size = 10;

enum DrawType
{
	FILLED,
	HOLLOW
};

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

void SDL_RenderCircle(SDL_Renderer *renderer, Point center, float radius, Color color);
void SDL_RenderFilledCircle(SDL_Renderer *renderer, Point center, float radius, Color color);
void PlacePoint(DrawType type, Point point);

void HandleUserEvent(SDL_Renderer* renderer, SDL_Event event)
{
	void *mode = event.user.data1;
	void *data = event.user.data2;
	if (mode != nullptr && data != nullptr)
	{
		switch (*static_cast<DrawType *>(mode))
		{
		case FILLED:
			SDL_RenderFilledCircle(renderer, *static_cast<Point *>(data), 100, Color(100, 100, 100, 100));
			break;
		case HOLLOW:
			SDL_RenderCircle(renderer, *static_cast<Point *>(data), 100, Color(100, 100, 100, 100));
			break;
		default:
			break;
		}
					
	}
}

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

		// Test
		PlacePoint(FILLED, Point(200, 200));

		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT)
				done = SDL_TRUE;
			else if (event.type == SDL_USEREVENT)
				HandleUserEvent(renderer, event);
		}
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}

void SDL_RenderCircle(SDL_Renderer *renderer, Point center, float radius, Color color)
{
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);

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

void SDL_RenderFilledCircle(SDL_Renderer *renderer, Point center, float radius, Color color)
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

void PlacePoint(DrawType type, Point point)
{
	SDL_Event userEvent;
	SDL_memset(&userEvent, 0, sizeof(userEvent)); 
	userEvent.type = SDL_USEREVENT;
	userEvent.user.code = 12345;
	userEvent.user.data1 = malloc(sizeof(type));
	userEvent.user.data2 = malloc(sizeof(point));
	memcpy(userEvent.user.data1, static_cast<void *>(&type), sizeof(type));
	memcpy(userEvent.user.data2, static_cast<void *>(&point), sizeof(point));
	SDL_PushEvent(&userEvent);
}
