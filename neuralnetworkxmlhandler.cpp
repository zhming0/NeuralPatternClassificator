#include "neuralnetworkxmlhandler.h"
#include "neuralnetwork.h"
#include "neurallayer.h"
#include "neuron.h"

NeuralNetworkXmlHandler::NeuralNetworkXmlHandler(NeuralNetwork * _network)
{
    network=_network;
}

bool NeuralNetworkXmlHandler::startElement(const QString &, const QString &localName, const QString &, const QXmlAttributes &atts)
{
    bool ret=true;
    if("neuralNetwork"==localName)
    {
        network->setNetworkString(atts.value("string"));
    }else if("layer"==localName)
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

bool NeuralNetworkXmlHandler::endElement(const QString &, const QString &localName, const QString &)
{
    bool ret=true;
    if("neuralNetwork"==localName)
    {
    }else if("layer"==localName)
    {
        NeuralLayer* layer=new NeuralLayer(network,currentLayer.count());
        for(int i = 0; i < currentLayer.size(); i++)
        {
            layer->getNeuron(i)->setThreshold(currentLayer[i]->getThreshold());
            for (int j = 0; j < layer->getNeuron(i)->numberOfDendrons(); j++)
                layer->getNeuron(i)->setDendronWeight(j, currentLayer[i]->getDendronWeight(j));
        }
        network->layers.push_back(layer);
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


void NeuralNetworkXmlHandler::setDocumentLocator(QXmlLocator *locator){};
bool NeuralNetworkXmlHandler::startDocument(){return true;}
bool NeuralNetworkXmlHandler::endDocument(){return true;}
bool NeuralNetworkXmlHandler::startPrefixMapping(const QString &prefix, const QString &uri){return true;}
bool NeuralNetworkXmlHandler::endPrefixMapping(const QString &prefix){return true;}
bool NeuralNetworkXmlHandler::characters(const QString &ch){return true;}
bool NeuralNetworkXmlHandler::ignorableWhitespace(const QString &ch){return true;}
bool NeuralNetworkXmlHandler::processingInstruction(const QString &target, const QString &data){return true;}
bool NeuralNetworkXmlHandler::skippedEntity(const QString &name){return true;}
QString NeuralNetworkXmlHandler::errorString() const{return "";};
