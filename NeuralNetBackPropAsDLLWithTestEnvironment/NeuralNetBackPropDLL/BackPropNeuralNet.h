#pragma once

#include <vector>
#include <cassert>

#include "Neuron.h"

using namespace std;

namespace neuralNet
{
	class Net
	{
	public:
		__declspec(dllexport) Net(const vector<unsigned> &topology);
		__declspec(dllexport) void feedForward(const vector<double> &inputVals);
		__declspec(dllexport) void backProp(const vector<double> &targetVals);
		__declspec(dllexport) void getResults(vector<double> &resultVals) const;
		__declspec(dllexport) double getRecentAverageError(void) const { return m_recentAverageError; }

	private:
		vector<Layer> m_layers;
		double m_error;
		double m_recentAverageError;
		static double m_recentAverageSmoothingFactor;
	};
}
