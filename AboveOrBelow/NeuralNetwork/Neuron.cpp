#include "Neuron.h"

namespace neuralnet
{
	double Neuron::eta = 0.2;  
	double Neuron::alpha = 0.5;  

	void Neuron::updateInputWeights(Layer &prevLayer) const
	{
		for (unsigned n = 0; n < prevLayer.size(); ++n)
		{
			Neuron &neuron = prevLayer[n];
			double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

			double newDeltaWeight =
				eta
				* neuron.getOutputVal()
				* m_gradient
				+ alpha
				* oldDeltaWeight;

			neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
			neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
		}
	}

	double Neuron::sumDOW(const Layer &nextLayer) const
	{
		double sum = 0.0;

		for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {
			sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
		}

		return sum;
	}

	void Neuron::calcHiddenGradients(const Layer &nextLayer)
	{
		double dow = sumDOW(nextLayer);
		m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
	}

	void Neuron::calcOutputGradients(double targetVal)
	{
		double delta = targetVal - m_outputVal;
		m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
	}

	double Neuron::transferFunction(double x)
	{
		return tanh(x);
	}

	double Neuron::transferFunctionDerivative(double x)
	{
		return 1.0 - x * x;
	}

	void Neuron::feedForward(const Layer &prevLayer)
	{
		double sum = 0.0;

		for (unsigned n = 0; n < prevLayer.size(); ++n) {
			sum += prevLayer[n].getOutputVal() *
				prevLayer[n].m_outputWeights[m_myIndex].weight;
		}

		m_outputVal = Neuron::transferFunction(sum);
	}

	Neuron::Neuron(unsigned numOutputs, unsigned myIndex): m_outputVal(0), m_gradient(0)
	{
		for (unsigned c = 0; c < numOutputs; ++c)
		{
			m_outputWeights.push_back(Connection());
			m_outputWeights.back().weight = randomWeight();
		}

		m_myIndex = myIndex;
	}
}
