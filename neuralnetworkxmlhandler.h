#ifndef NETWORKXMLHANDLER_H
#define NETWORKXMLHANDLER_H

#include <QXmlContentHandler>

class NeuralNetwork;
//class NeuralLayer;
class Neuron;

class NeuralNetworkXmlHandler : public QXmlContentHandler
{
public:
    NeuralNetworkXmlHandler(NeuralNetwork*);
    virtual bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    virtual bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);

    virtual void setDocumentLocator(QXmlLocator *locator);
    virtual bool startDocument();
    virtual bool endDocument();
    virtual bool startPrefixMapping(const QString &prefix, const QString &uri);
    virtual bool endPrefixMapping(const QString &prefix);
    virtual bool characters(const QString &ch);
    virtual bool ignorableWhitespace(const QString &ch);
    virtual bool processingInstruction(const QString &target, const QString &data);
    virtual bool skippedEntity(const QString &name);
    virtual QString errorString() const;
private:
    NeuralNetwork* network;
    double currentNeuronThreshold;
    QList<double> currentNeuron;
    QList<Neuron*> currentLayer;
};

#endif // NETWORKXMLHANDLER_H
