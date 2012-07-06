#include "neuralnetwork.h"

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

void NeuralNetwork::learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, double eps, double lambda, double micro)
{
    this->genarateRandomNetwork();

}

void NeuralNetwork::genarateRandomNetwork()
{

}


