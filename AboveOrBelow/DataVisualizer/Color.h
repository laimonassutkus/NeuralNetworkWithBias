#pragma once

namespace visualizer
{
	struct Color
	{
		Uint8 alpha;
		Uint8 red;
		Uint8 green;
		Uint8 blue;

		Color(Uint8 a, Uint8 r, Uint8 g, Uint8 b) : alpha(a), red(r), green(g), blue(b)
		{
		}
	};
}