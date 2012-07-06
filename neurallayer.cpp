#include "neurallayer.h"
#include "neuralnetwork.h"
NeuralLayer::NeuralLayer(NeuralNetwork* network, int numOfNeurons)
{
    this->network = network;
    for (int i = 0; i < numOfNeurons; i++)
    {
        if (this->network->numberOfLayers() == 0)
            this->neurons.push_back(new Neuron(1, 0));
        else
            this->neurons.push_back(new Neuron(this->network->getLayer(this->network->numberOfLayers() - 1)->numberOfNuerons(), 0));
    }
}

int NeuralLayer::numberOfNuerons() const
{
    return this->neurons.size();
}
