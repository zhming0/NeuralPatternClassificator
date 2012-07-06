#ifndef NETWORKXMLHANDLER_H
#define NETWORKXMLHANDLER_H

#include <QXmlContentHandler>

class NeuralNetwork;
//class NeuralLayer;
class Neuron;

class NetworkXmlHandler : public QXmlContentHandler
{
public:
    NetworkXmlHandler(NeuralNetwork*);
    virtual bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    virtual bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
private:
    NeuralNetwork* network;
    double currentNeuronThreshold;
    QList<double> currentNeuron;
    QList<Neuron*> currentLayer;
};

#endif // NETWORKXMLHANDLER_H
