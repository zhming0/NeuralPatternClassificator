#include "neuralnetwork.h"
#include <ctime>
#include <QFile>
#include<iostream>
#include"gradient.h"
#include<qmath.h>
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

void NeuralNetwork::learn(const QVector<QVector<double> >& inputSet, const QVector<QVector<double> >& outputSet, int maxK, double eps, double lambda, double micro)
{
    if (inputSet.size() != outputSet.size())
    {
        std::cout << "NeuralNetwork::learn : The size of input and output is not equal" << std::endl;
        return;
    }
    this->genarateRandomNetwork();
    int ioSize = inputSet.size(), curK = 0;
    double curE = 0x7fffffff;
    while (curK < maxK && curE > eps)
    {
        Gradient totalGradient(this);
        for (int io = 0; io < ioSize; io++)
        {
            activate(inputSet[io]);

            Gradient partialGradient = computePartialGradient(outputSet[io]);

            //Add partial gradient to total gradient
            for (int i = this->numberOfLayers(); i >= 1; i--) {
                NeuralLayer* currentLayer = this->getLayer(i);
                for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
                {
                    totalGradient.incrementThreshold(i, j, partialGradient.getThreshold(i, j));
                    Neuron* currentNeuron = currentLayer->getNeuron(j);
                    for (int k = 0; k < currentNeuron->numberOfDendrons(); k++)
                        totalGradient.incrementWeight(i, j, k, partialGradient.getWeight(i, j, k));
                }
            }
        }
        curE = totalGradient.getGradientAbs();
        curK++;
    }
}

QVector<double> NeuralNetwork::activate(const QVector<double>& input)
{
    for (int i = 0; i < this->numberOfLayers(); i++)
    {
        NeuralLayer* currentLayer = this->getLayer(i);
        for(int j = 0; j < currentLayer->numberOfNuerons(); j++)
        {
            Neuron* currentNeuron = currentLayer->getNeuron(j);
            double sum = currentNeuron->getThreshold();
            for (int k = 0; k < currentNeuron->numberOfDendrons(); k++)
            {
                if (i == 0) {
                    sum += currentNeuron->getDendronWeight(k) * input[j];
                } else {
                    sum += currentNeuron->getDendronWeight(k) * this->getLayer(i-1)->getNeuron(k)->getOutput();
                }
            }

            currentNeuron->setOutput(sum);
        }
    }

    QVector<double> result;
    for (int i = 0; i < this->getLayer(this->numberOfLayers() - 1)->numberOfNuerons(); i++)
        result.push_back(this->getLayer(this->numberOfLayers() - 1)->getNeuron(i)->getOutput());
    return result;
}

double NeuralNetwork::gainFunction(double value) const
{
    return 1/(1+qExp(-value));
}

Gradient NeuralNetwork::computePartialGradient(const QVector<double>& requiredOutput)
{

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


