#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include<QVector>
#include"neurallayer.h"
#include<QPair>
class Gradient;
class NeuralNetwork
{
public:
    NeuralNetwork(const QVector<int>& sizeOfNetwork);
    NeuralNetwork(const QString& path);
    void learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, int maxK, double eps, double lambda, double micro);
    QVector<double> test(QVector<double>);
    int numberOfLayers() const;
    NeuralLayer* getLayer(int index) const;
protected:
    void saveToXML(const QString& path);
    void readFromXML(const QString& path);
    void genarateRandomNetwork();
    QVector<double> activate(const QVector<double>& input);
    //Gradient computeTotalGradient(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet);
    Gradient computePartialGradient(const QVector<double>& requiredOutput);
    double random();
    double gainFunction(double value) const;
private:
    friend class NetworkXmlHandler;
    QVector<NeuralLayer*> layers;
};

#endif // NEURALNETWORK_H
