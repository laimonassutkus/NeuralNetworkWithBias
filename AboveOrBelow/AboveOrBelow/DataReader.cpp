#include "DataReader.h"

DataReader::DataReader(const string filename)
{
	m_trainingDataFile.open(filename.c_str());
	if (!m_trainingDataFile.is_open())
	{
		throw new exception("FILE IS NOT OPEN");
	}
}

unsigned DataReader::getNextInputs(vector<double> &inputVals)
{
	inputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	double oneValue;
	while (ss >> oneValue)
	{
		inputVals.push_back(oneValue);
	}

	return inputVals.size();
}

unsigned DataReader::getTargetOutputs(vector<double> &targetOutputVals)
{
	targetOutputVals.clear();

	string line;
	getline(m_trainingDataFile, line);
	stringstream ss(line);

	double oneValue;
	while (ss >> oneValue) {
		targetOutputVals.push_back(oneValue);
	}

	return targetOutputVals.size();
}
