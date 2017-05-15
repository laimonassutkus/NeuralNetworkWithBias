#pragma once

#include "SDL2/include/SDL.h"
#include <vector>
#include <tuple>

#include "Point.h"
#include "Color.h"
#include "WindowInfo.h"

#define _USE_MATH_DEFINES

namespace visualizer
{
	void SDL_RenderCircle(SDL_Renderer *renderer, Point center, float radius, Color color);
	void SDL_RenderFilledCircle(SDL_Renderer *renderer, Point center, float radius, Color color);
	void AddPoint(Point point, bool isAbove);
	void HandleUserEvent(SDL_Event event);
	WindowInfo GetWindowInfo();
	int run();
}