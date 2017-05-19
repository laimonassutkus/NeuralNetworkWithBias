#pragma once
#include <vector>
#include <tuple>
#include <ctime>
#include <cmath>
#include "Writer.h"
#include "../DataVisualizer/paint.h"

#define PATH "./Data.txt"

using std::vector;
using std::tuple;
using std::exception;
using std::make_tuple;

inline double SinFunction(double x);
inline double LinearFunction(double x);
inline double QuadricFunction(double x);
inline SDL_Point *GeneratePointsForFunction(double(*getY)(double));
inline void GenerateDataForFunction(vector<tuple<double, double, bool>> &data, double(*GetPositionIsAbove)(double));

const WindowInfo winInfo = visualizer::GetWindowInfo();
const int AREA_X = winInfo.window_width - 2 * winInfo.padding;
const int AREA_Y = winInfo.window_height - 2 * winInfo.padding;
const int NUM_OF_POINTS = 10000;

inline int GenerateTrainData(int mode, const std::vector<unsigned int> &topology)
{
	Writer writer(PATH);
	vector<tuple<double, double, bool>> data;
	srand(static_cast<int>(time(nullptr)));

	switch (mode)
	{
	case 1:
		GenerateDataForFunction(data, LinearFunction); break;
	case 2:
		GenerateDataForFunction(data, SinFunction); break;
	case 3:
		GenerateDataForFunction(data, QuadricFunction); break;
	default:
		throw exception("Wrong selection of generating method.");
	}

	writer.ResetFile();
	writer.WriteValues(data);

	return 0;
}

inline SDL_Point *GeneratePoints(int mode)
{
	switch (mode)
	{
	case 1:
		return GeneratePointsForFunction(LinearFunction);
	case 2:
		return GeneratePointsForFunction(SinFunction);
	case 3:
		return GeneratePointsForFunction(QuadricFunction);
	default: ;
		return nullptr;
	}
}

inline double QuadricFunction(double x)
{
	auto a = std::pow(x, 2) / 250 - 2.5 * x + 500;
	return a;
}

inline double SinFunction(double x)
{
	return std::sin(x) * 10;
}

inline double LinearFunction(double x)
{
	return x / 2;
}

inline SDL_Point *GeneratePointsForFunction(double(*getY)(double))
{
	SDL_Point *points = static_cast<SDL_Point *>(malloc(sizeof(SDL_Point) * winInfo.window_width));
	for (auto i = 0; i < winInfo.window_width; ++i)
	{
		points[i].x = i + winInfo.padding;
		points[i].y = getY(i) + winInfo.padding;
	}
	return points;
}

inline void GenerateDataForFunction(vector<tuple<double, double, bool>> &data, double(*getY)(double))
{
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		double x = (static_cast<double>(rand()) / RAND_MAX) * AREA_X + winInfo.padding,
			y = (static_cast<double>(rand()) / RAND_MAX) * AREA_Y + winInfo.padding;

		double yFromFunction = getY(x);
		bool isAbove = yFromFunction > y;

		auto t = make_tuple(x, y, isAbove);

		data.push_back(t);
	}
}