#pragma once

namespace visualizer
{
	struct Point
	{
		double x;
		double y;

		Point() : x(0), y(0) { }
		Point(double _x, double _y) : x(_x), y(_y) { }

		Point& operator +(const Point& o)
		{
			x = x + o.x;
			y = y + o.y;

			return *this;
		}
	};
}