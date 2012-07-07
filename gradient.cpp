#include "gradient.h"
#include "neuralnetwork.h"
#include <qmath.h>
Gradient::Gradient(NeuralNetwork* network)
{
    this->network = network;
    this->init();
}

void Gradient::init()
{
    for (int i = 0; i < network->numberOfLayers(); i++)
    {
        QVector<double> tmp;
        QVector<QVector<double> > empty;
        this->weights.push_back(empty);
        this->threshold.push_back(tmp);
        for (int j = 0; j < network->getLayer(i)->numberOfNuerons(); j++)
        {
            this->threshold[i].push_back(0.0);
            this->weights[i].push_back(tmp);
            for (int k = 0; k < network->getLayer(i)->getNeuron(j)->numberOfDendrons(); k++)
                this->weights[i][j].push_back(0.0);
        }
    }
}

void Gradient::setThreshold(int i, int j, double value)
{
    this->threshold[i][j] = value;
}

double Gradient::getThreshold(int i, int j) const
{
    return this->threshold[i][j];
}
void Gradient::incrementThreshold(int i, int j, double value)
{
    this->threshold[i][j] += value;
}
void Gradient::setWeight(int i, int j, int k, double value)
{
    this->weights[i][j][k] = value;
}

double Gradient::getWeight(int i, int j, int k) const
{
    return this->weights[i][j][k];
}

void Gradient::incrementWeight(int i, int j, int k, double value)
{
    this->weights[i][j][k] += value;
}

double Gradient::getGradientAbs() const
{
    double res = 0;
    for (int i = 0; i < network->numberOfLayers(); i++)
    {
        res += getVectorAbs(this->threshold[i]);
        double tmpSum = 0;
        for (int j = 0; j < this->weights[i].size(); j++) {
            double tmp = getVectorAbs(this->weights[i][j]);
            tmpSum += tmp * tmp;
        }
        res += qSqrt(tmpSum);
    }
    return res;
}

double Gradient::getVectorAbs(const QVector<double>& vec) const
{
    double res = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        res += vec[i] * vec[i];
    }

    return qSqrt(res);
}
