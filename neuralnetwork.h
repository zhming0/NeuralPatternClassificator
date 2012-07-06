#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include<QVector>
#include"neurallayer.h"
#include<QPair>
class NeuralNetwork
{
public:
    NeuralNetwork(bool learn);
    void learn(QPair<QVector<double>, QVector<double> >, double eps, double lambda, double micro);
    QVector<double> test(QVector<double>);
protected:
    void saveToXML();
    void readFromXML();
private:
    QVector<NeuralLayer> layers;
};

#endif // NEURALNETWORK_H
