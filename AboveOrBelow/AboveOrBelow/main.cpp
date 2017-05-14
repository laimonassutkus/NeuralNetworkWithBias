#include "BackPropNeuralNet.h"
#include <string>
#include "../DataGenerator/Generator.h"
#include "DataReader.h"

using namespace std;
using namespace neuralNet;

void showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}

	cout << endl;
}

int main()
{
	vector<unsigned> topology = {2, 1};

	Generate(2, topology);
	Net myNet(topology);

	DataReader trainData("./Data.txt");
	clock_t start;
	double duration;

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	start = clock();
	while (!trainData.isEof()) {
		++trainingPass;
		cout << endl << "Pass " << trainingPass;

		// Get new input data and feed it forward:
		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		showVectorVals(": Inputs:", inputVals);
		myNet.feedForward(inputVals);

		// Collect the net's actual output results:
		myNet.getResults(resultVals);
		showVectorVals("Outputs:", resultVals);

		// Train the net what the outputs should have been:
		trainData.getTargetOutputs(targetVals);
		showVectorVals("Targets:", targetVals);
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// Report how well the training is working, average over recent samples:
		cout << "Net recent average error: "
			<< myNet.getRecentAverageError() << endl;
	}
	duration = (clock() - start) / static_cast<double>(CLOCKS_PER_SEC);

	cout << endl << "Done in " << duration << " seconds." << endl;

	system("pause");
}
