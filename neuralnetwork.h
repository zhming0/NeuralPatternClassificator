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
    ~NeuralNetwork();

    void learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, int maxK, double eps, double lambda, double micro);
    QVector<double> test(const QVector<double>&);
    int numberOfLayers() const;
    NeuralLayer* getLayer(int index) const;
    void saveToXML(const QString& path);
    QString getNetworkString();
    void setNetworkString(QString);
protected:
    void readFromXML(const QString& path);
    void genarateRandomNetwork();
    QVector<double> activate(const QVector<double>& input);
    //Gradient computeTotalGradient(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet);
    Gradient computePartialGradient(const QVector<double>& requiredOutput);
    double random();
    double gainFunction(double value) const;
private:
    friend class NeuralNetworkXmlHandler;
    QVector<NeuralLayer*> layers;
    QString _networkString;
};

#endif // NEURALNETWORK_H
