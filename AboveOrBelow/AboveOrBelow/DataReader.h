#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class DataReader
{

public:
	DataReader(const string filename);
	bool isEof() const { return m_trainingDataFile.eof(); }

	unsigned getNextInputs(vector<double> &inputVals);
	unsigned getTargetOutputs(vector<double> &targetOutputVals);

private:
	ifstream m_trainingDataFile;
};

