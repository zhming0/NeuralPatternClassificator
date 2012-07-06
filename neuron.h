#ifndef NEURON_H
#define NEURON_H
#include<QVector>
class Neuron
{
public:
    Neuron(int numOfDendrons, double threshold);
    int numberOfDendrons() const;
    double getOutput() const;
    void setOutput(double value);
    void setThreshold(double value);
    double getThreshold() const;
    double getDendronWeight(int index) const;
    void setDendronWeight(int index, double value);
private:
    double threshold, output;
    QVector<double> dendronWeight;
};

#endif // NEURON_H
