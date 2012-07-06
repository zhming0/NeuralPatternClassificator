#include "neuron.h"
#include<iostream>
Neuron::Neuron(int numOfDendrons, double threshold)
{
    this->threshold = threshold;
    for (int i = 0; i < numOfDendrons; i++)
    {
        this->dendronWeight.push_back(1.0);
    }
}

int Neuron::numberOfDendrons() const
{
    return dendronWeight.size();
}

double Neuron::getOutput() const
{
    return output;
}

void Neuron::setOutput(double value)
{
    output = value;
}

double Neuron::getDendronWeight(int index) const
{
    if (index >= dendronWeight.size()) {
        std::cout << "Neuron::getDendronWeight : index out of bound" << std::endl;
        return 0;
    }
    return this->dendronWeight[index];
}

void Neuron::setDendronWeight(int index, double value)
{
    if (index >= dendronWeight.size()) {
        std::cout << "Neuron::setDendronWeight : index out of bound" << std::endl;
    }
    this->dendronWeight[index] = value;
}

double Neuron::getThreshold() const
{
    return this->threshold;
}

void Neuron::setThreshold(double value)
{
    this->threshold = value;
}
