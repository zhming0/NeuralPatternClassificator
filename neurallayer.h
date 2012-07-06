#ifndef NEURALLAYER_H
#define NEURALLAYER_H
#include<QVector>
#include"neuron.h"
class NeuralNetwork;
class NeuralLayer
{
public:
    NeuralLayer(NeuralNetwork* network, int numOfNeurons);
private:
    QVector<Neuron> neurons;
    NeuralNetwork* network;
};

#endif // NEURALLAYER_H
