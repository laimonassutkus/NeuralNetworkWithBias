#include "paint.h"
#include <iostream>
#include "WindowInfo.h"

namespace visualizer
{
	using std::vector;
	using std::tuple;

	typedef vector<tuple<double, double, bool>> points;

	static const unsigned winH = 480;
	static const unsigned winW = 640;
	static const unsigned winP = 20;


	const WindowInfo windowInfo(winW, winH, winP);
	float point_size = 5;

	points pointContainer;


	int run()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, windowInfo.window_width, windowInfo.window_height, SDL_WINDOW_SHOWN);
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
			SDL_RenderDrawLine(renderer, windowInfo.padding, windowInfo.padding, 
				windowInfo.padding, windowInfo.window_height - windowInfo.padding);

			// Draw OX axis
			SDL_RenderDrawLine(renderer, windowInfo.padding, windowInfo.window_height - windowInfo.padding, 
				windowInfo.window_width - windowInfo.padding, windowInfo.window_height - windowInfo.padding);

			for (auto point : pointContainer)
			{
				bool isAbove = std::get<2>(point);
				Point coordinates = Point(std::get<0>(point), std::get<1>(point));

				if (isAbove)
					SDL_RenderCircle(renderer, coordinates, point_size, Color(100, 0, 0, 0));
				else
					SDL_RenderFilledCircle(renderer, coordinates, point_size, Color(100, 255, 0, 0));
			}

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					done = SDL_TRUE;
				else if (event.type == SDL_USEREVENT)
					HandleUserEvent(event);
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

	void AddPoint(Point point, bool isAbove)
	{
		auto t = std::make_tuple(point.x, point.y, isAbove);

		SDL_Event userEvent;
		SDL_memset(&userEvent, 0, sizeof(userEvent));
		userEvent.type = SDL_USEREVENT;
		userEvent.user.code = 0;
		userEvent.user.data1 = malloc(sizeof(t));
		memcpy(userEvent.user.data1, static_cast<void *>(&t), sizeof(t));
		SDL_PushEvent(&userEvent);
	}

	void HandleUserEvent(SDL_Event event)
	{
		void *data = event.user.data1;
		if (data != nullptr)
		{
			auto p = static_cast<tuple<double, double, bool>*>(data);
			pointContainer.push_back(*p);
		}
	}

	WindowInfo GetWindowInfo()
	{
		return WindowInfo(winW, winH, winP);
	}
}
