#ifndef NEURON_H
#define NEURON_H
#include<QVector>
class Neuron
{
public:
    Neuron(int numOfInputs, double threshold);
private:
    double threshold;
    QVector<double> dendronWeight;
};

#endif // NEURON_H
