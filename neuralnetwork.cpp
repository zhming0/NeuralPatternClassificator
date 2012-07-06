#include "neuralnetwork.h"
#include <ctime>
#include<iostream>
#include"gradient.h"
NeuralNetwork::NeuralNetwork(const QVector<int>& sizeOfNetwork)
{
    for (int i = 0; i < sizeOfNetwork.size(); i++)
    {
        this->layers.push_back(new NeuralLayer(this, sizeOfNetwork[i]));
    }
}

NeuralNetwork::NeuralNetwork(const QString& path)
{
    this->readFromXML(path);
}

void NeuralNetwork::readFromXML(const QString& path)
{

}

int NeuralNetwork::numberOfLayers() const
{
    return this->layers.size();
}

NeuralLayer* NeuralNetwork::getLayer(int index) const
{
    if (index >= layers.size())
        return NULL;
    return this->layers[index];
}

void NeuralNetwork::learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, int maxK, double eps, double lambda, double micro)
{
    if (inputSet.size() != outputSet.size())
    {
        std::cout << "NeuralNetwork::learn : The size of input and output is not equal" << std::endl;
        return;
    }
    this->genarateRandomNetwork();
    int ioSize = inputSet.size(), curK = 0;
    double curE = 0x7fffffff;
    while (curK < maxK && curE > eps)
    {
        Gradient totalGradient(this);
        for (int io = 0; io < ioSize; io++)
        {
            activate(inputSet[io]);

            Gradient partialGradient = computePartialGradient(outputSet[io]);

            //Add partial gradient to total gradient
            for (int i = this->numberOfLayers(); i >= 1; i--) {
                NeuralLayer* currentLayer = this->getLayer(i);
                for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
                {
                    totalGradient.incrementThreshold(i, j, partialGradient.getThreshold(i, j));
                    Neuron* currentNeuron = currentLayer->getNeuron(j);
                    for (int k = 0; k < currentNeuron->numberOfDendrons(); k++)
                        totalGradient.incrementWeight(i, j, k, partialGradient.getWeight(i, j, k));
                }
            }
        }
        curE = totalGradient.getGradientAbs();
        curK++;
    }
}

QVector<double> NeuralNetwork::activate(const QVector<double>& input)
{

}

Gradient NeuralNetwork::computePartialGradient(const QVector<double>& requiredOutput)
{

}

double NeuralNetwork::random()
{
    srand((int)time(NULL));
    int tmp = rand() % 2000;
    double result = (double) tmp;
    result /= 1000.0;
    return result - 1.0;
}

void NeuralNetwork::genarateRandomNetwork()
{
    for (int i = 1; i < this->numberOfLayers(); i++)
    {
        NeuralLayer* currentLayer = this->getLayer(i);
        for (int j = 0; j < currentLayer->numberOfNuerons(); i++)
        {
            Neuron* currentNeuron = currentLayer->getNeuron(j);
            currentNeuron->setThreshold(random());
            for (int k = 0; k < currentNeuron->numberOfDendrons(); i++)
                currentNeuron->setDendronWeight(k, random());
        }
    }
}


