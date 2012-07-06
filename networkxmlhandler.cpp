#include "networkxmlhandler.h"
#include "neuralnetwork.h"
#include "neurallayer.h"
#include "neuron.h"

NetworkXmlHandler::NetworkXmlHandler(NeuralNetwork * _network)
{
    network=_network;
}

bool NetworkXmlHandler::startElement(const QString & uri, const QString &localName, const QString &, const QXmlAttributes &atts)
{
    bool ret=true;
    if("neuralNetwork"==localName)
    {
    }if("layer"==localName)
    {
        currentLayer.clear();
    }else if("neuron"==localName)
    {
        currentNeuron.clear();
        currentNeuronThreshold=atts.value("threshold").toDouble(&ret);
    }else if("dendron"==localName)
    {
        currentNeuron.append(atts.value("weight").toDouble(&ret));
    }else
    {
        ret=false;
    }
    return ret;
}

bool NetworkXmlHandler::endElement(const QString &, const QString &localName, const QString &)
{
    bool ret=true;
    if("neuralNetwork"==localName)
    {
    }else if("layer"==localName)
    {
        NeuralLayer* layer=new NeuralLayer(network,currentLayer.count());
        network->layers.push_back(layer);
        foreach(Neuron* neuron,currentLayer)
        {
            layer->neurons.push_back(neuron);
        }
    }else if("neuron"==localName)
    {
        Neuron *ins=new Neuron(currentNeuron.count(),currentNeuronThreshold);
        currentLayer.append(ins);
        int i=0;
        foreach(double weight,currentNeuron)
        {
            ins->setDendronWeight(i++,weight);
        }
    }else if("dendron"==localName)
    {
    }else
    {
        ret=false;
    }
    return ret;
}
