#include "neuralnetwork.h"
#include <ctime>
#include <QFile>
#include<iostream>
NeuralNetwork::NeuralNetwork(const QVector<int>& sizeOfNetwork)
{
    for (int i = 0; i < sizeOfNetwork.size(); i++)
    {
        this->layers.push_back(new NeuralLayer(this, sizeOfNetwork[i]));
    }
}

NeuralNetwork::NeuralNetwork(const QString& path)
{
    this->readFromXML(path);
}

void NeuralNetwork::readFromXML(const QString& path)
{

}

void NeuralNetwork::saveToXML(const QString& path)
{
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
    {
        std::cout<<"File \""<<path.toStdString()<<"\" could not be opened for read"<<std::endl;
    }
    file.write("<?xml version=\"1.0\"?>\n");
    file.write("<neuralNetwork>\n");
    foreach(NeuralLayer* layer,layers)
    {
        file.write("\t<layer>\n");
        for(int ni=0,nc=layer->numberOfNuerons();ni<nc;ni++)
        {
            Neuron* neuron=layer->getNeuron(ni);
            file.write( QString().sprintf("\t\t<neuron threshold=\"%f\">\n",neuron->getThreshold()).toAscii() );
            for(int di=0,dc=neuron->numberOfDendrons();di<dc;di++)
            {
                file.write( QString().sprintf("\t\t\t<dendron weight=\"%f\"></dendron>\n",neuron->getDendronWeight(di)).toAscii() );
            }
            file.write("\t\t</neuron>\n");
        }
        file.write("\t</layer>\n");
    }
    file.write("</neuralNetwork>");
    file.close();
}

int NeuralNetwork::numberOfLayers() const
{
    return this->layers.size();
}

NeuralLayer* NeuralNetwork::getLayer(int index) const
{
    if (index >= layers.size())
        return NULL;
    return this->layers[index];
}

void NeuralNetwork::learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, double eps, double lambda, double micro)
{
    if (inputSet.size() != outputSet)
    {

        return;
    }
    this->genarateRandomNetwork();

}

double NeuralNetwork::random()
{
    srand((int)time(NULL));
    int tmp = rand() % 2000;
    double result = (double) tmp;
    result /= 1000.0;
    return result - 1.0;
}

void NeuralNetwork::genarateRandomNetwork()
{
    for (int i = 1; i < this->numberOfLayers(); i++)
    {
        NeuralLayer* currentLayer = this->getLayer(i);
        for (int j = 0; j < currentLayer->numberOfNuerons(); i++)
        {
            Neuron* currentNeuron = currentLayer->getNeuron(j);
            currentNeuron->setThreshold(random());
            for (int k = 0; k < currentNeuron->numberOfDendrons(); i++)
                currentNeuron->setDendronWeight(k, random());
        }
    }
}


