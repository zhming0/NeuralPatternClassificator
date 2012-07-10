#ifndef NEURALLAYER_H
#define NEURALLAYER_H
#include<QVector>
#include"neuron.h"
class NeuralNetwork;
class NeuralLayer
{
public:
    NeuralLayer(NeuralNetwork* network, int numOfNeurons);
    ~NeuralLayer();
    int numberOfNuerons() const;
    Neuron* getNeuron(int index);
private:
    friend class NeuralNetworkXmlHandler;
    QVector<Neuron*> neurons;
    NeuralNetwork* network;
};

#endif // NEURALLAYER_H
