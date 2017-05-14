#pragma once
#include <vector>
#include <tuple>
#include <ctime>
#include "Writer.h"

#define AREA_X 1 
#define AREA_Y 1 
#define NUM_OF_POINTS 10000
#define PATH "./Data.txt"

using std::vector;
using std::tuple;
using std::exception;
using std::make_tuple;

inline bool GenerateDataForSinFunction(double x, double y);
inline void GenerateDataForXORGate(vector<tuple<double, double, bool>> &data);
inline bool GenerateDataForLinearFunction(double x, double y);
inline void GenerateDataForFunction(vector<tuple<double, double, bool>> &data, bool(*GetPositionIsAbove)(double, double));

inline int Generate(int mode, const std::vector<unsigned int> &topology)
{
	Writer writer(PATH);
	vector<tuple<double, double, bool>> data;
	srand(static_cast<int>(time(nullptr)));

	switch (mode)
	{
	case 1:
		GenerateDataForXORGate(data); break;
	case 2:
		GenerateDataForFunction(data, GenerateDataForLinearFunction); break;
	case 3:
		GenerateDataForFunction(data, GenerateDataForSinFunction); break;
	default:
		throw exception("Wrong selection of generating method.");
	}

	writer.ResetFile();
	writer.WriteValues(data);

	return 0;
}

inline void GenerateDataForXORGate(vector<tuple<double, double, bool>> &data)
{
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		double a = (static_cast<double>(rand()) / RAND_MAX) > 0.5 ? 1 : 0;
		double b = (static_cast<double>(rand()) / RAND_MAX) > 0.5 ? 1 : 0;
		double c;

		if (a && b)
			c = 0;
		else if (!a && !b)
			c = 0;
		else
			c = 1;

		auto t = make_tuple(a, b, c);
		data.push_back(t);
	}
}

inline bool GenerateDataForSinFunction(double x, double y)
{
	// our function is : f(x) = sin(x);
	double functionY = std::sin(x); 
	if (functionY > y)
		return false;
	return true;
}

inline bool GenerateDataForLinearFunction(double x, double y)
{
	// our function is : f(x) = x
	double functionY = x;
	if (functionY > y)
		return false;
	return true;
}

inline void GenerateDataForFunction(vector<tuple<double, double, bool>> &data, bool (*GetPositionIsAbove)(double, double))
{
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		double x = (static_cast<double>(rand()) / RAND_MAX) * AREA_X,
			y = (static_cast<double>(rand()) / RAND_MAX) * AREA_Y;
		bool isAbove = GetPositionIsAbove(x, y);
		auto t = make_tuple(x, y, isAbove);

		data.push_back(t);
	}
}