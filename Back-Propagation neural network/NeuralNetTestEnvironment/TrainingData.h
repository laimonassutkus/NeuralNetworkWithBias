#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class TrainingData
{

public:
	TrainingData(const string filename);
	bool isEof(void) { return m_trainingDataFile.eof(); }
	void getTopology(vector<unsigned> &topology);

	// Returns the number of input values read from the file:
	unsigned getNextInputs(vector<double> &inputVals);
	unsigned getTargetOutputs(vector<double> &targetOutputVals);

	std::string AddNullTerminator(char a[], int length);

private:
	ifstream m_trainingDataFile;
};

