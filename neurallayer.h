#ifndef NEURALLAYER_H
#define NEURALLAYER_H
#include<QVector>
#include"neuron.h"
class NeuralLayer
{
public:
    NeuralLayer();
private:
    QVector<Neuron> neurons;
};

#endif // NEURALLAYER_H
