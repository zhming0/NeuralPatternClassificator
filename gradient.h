#ifndef GRADIENT_H
#define GRADIENT_H
#include<QVector>
class NeuralNetwork;
class Gradient
{
public:
    Gradient(NeuralNetwork*);
    void setThreshold(int i, int j, double value);
    double getThreshold(int i, int j) const;
    void incrementThreshold(int i, int j, double value);

    void setWeight(int i, int j, int k, double value);
    double getWeight(int i, int j, int k) const;
    void incrementWeight(int i, int j, int k, double value);

    double getGradientAbs() const;
protected:
    void init();
    double getVectorAbs(const QVector<double>& vec) const;
private:
    QVector<QVector<double> > threshold;
    QVector<QVector<QVector<double> > > weights;
    NeuralNetwork* network;
};

#endif // GRADIENT_H
