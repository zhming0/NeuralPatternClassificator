#include "neurallayer.h"
#include "neuralnetwork.h"
#include<iostream>
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

NeuralLayer::~NeuralLayer()
{
    for (int i = 0; i < this->numberOfNuerons(); i++)
        delete this->neurons[i];
}

int NeuralLayer::numberOfNuerons() const
{
    return this->neurons.size();
}

Neuron* NeuralLayer::getNeuron(int index)
{
    if (index >= this->numberOfNuerons())
    {
        std::cout << "NeuralLayer::getNeuron : index out of bound" << std::endl;
        return NULL;
    }
    return this->neurons[index];
}
