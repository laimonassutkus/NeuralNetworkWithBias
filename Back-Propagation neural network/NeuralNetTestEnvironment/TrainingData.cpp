#include "TrainingData.h"

std::string TrainingData::AddNullTerminator(char a[], int length)
{
	if (a[length - 1] == ' ')
	{
		a[length - 1] = '\0';
	}
	return std::string(a);
}

void TrainingData::getTopology(vector<unsigned> &topology)
{
	string line;
	string label;

	getline(m_trainingDataFile, line);
	stringstream ss(AddNullTerminator((char *)line.c_str(), line.size()));
	ss >> label;
	if (this->isEof() || label.compare("topology:") != 0) {
		abort();
	}

	while (!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return;
}

TrainingData::TrainingData(const string filename)
{
	m_trainingDataFile.open(filename.c_str());
	if (!m_trainingDataFile.is_open())
	{
		throw new exception("FILE IS NOT OPEN");
	}
}

unsigned TrainingData::getNextInputs(vector<double> &inputVals)
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

unsigned TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
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
