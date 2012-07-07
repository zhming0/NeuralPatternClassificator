#include "neuralnetwork.h"
#include "neuralnetworkxmlhandler.h"
#include "gradient.h"
#include <ctime>
#include <QFile>
#include<iostream>
#include"gradient.h"
#include<qmath.h>
#include<cstdio>
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

QVector<double> NeuralNetwork::test(const QVector<double> & input)
{
    return activate(input);
}

void NeuralNetwork::readFromXML(const QString& path)
{
    QFile file(path);
    if(!file.open(QFile::ReadOnly))
    {
        std::cout<<"File \""<<path.toStdString()<<"\" could not be opened for reading"<<std::endl;
    }
    NeuralNetworkXmlHandler handler(this);
    QXmlSimpleReader reader;
    reader.setContentHandler(&handler);
    reader.parse(QXmlInputSource(&file));
    file.close();
}

void NeuralNetwork::saveToXML(const QString& path)
{
    QFile file(path);
    if(!file.open(QFile::WriteOnly))
    {
        std::cout<<"File \""<<path.toStdString()<<"\" could not be opened for writing"<<std::endl;
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
    std::cout << "NeuralNetwork::learn" << std::endl;
    this->genarateRandomNetwork();

    int ioSize = inputSet.size(), curK = 0;
    double curE = 0x7fffffff;
    Gradient deltaGradient(this);

    while (curK < maxK && curE > eps)
    {
        Gradient totalGradient(this);

        //Activate and compute gradient
        for (int io = 0; io < ioSize; io++)
        {
            activate(inputSet[io]);

            Gradient partialGradient = computePartialGradient(outputSet[io]);

            //Add partial gradient to total gradient
            for (int i = this->numberOfLayers() - 1; i >= 1; i--) {
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

        // update weights and thresholds
        for(int il=layers.count()-1;il>0;il--)
        {
            NeuralLayer* layer=layers.at(il);
            for(int in=0,cn=layer->numberOfNuerons();in<cn;in++)
            {
                Neuron* neuron=layer->getNeuron(in);
                double delta=-lambda*totalGradient.getThreshold(il,in)+micro*deltaGradient.getThreshold(il,in);
                neuron->setThreshold(neuron->getThreshold()+delta);
                deltaGradient.setThreshold(il,in,delta);
            }

            for(int in=0,cn=layer->numberOfNuerons();in<cn;in++)
            {
                Neuron* neuron=layer->getNeuron(in);
                for(int ii=0,ci=neuron->numberOfDendrons();ii<ci;ii++)
                {
                    double delta= -lambda*totalGradient.getWeight(il,in,ii)+micro*deltaGradient.getWeight(il,in,ii);
                    neuron->setDendronWeight(ii,neuron->getDendronWeight(ii)+delta);
                    deltaGradient.setWeight(il,in,ii,delta);
                }
            }
        }


        curE = totalGradient.getGradientAbs();
        curK++;
        printf("curE = %f, curK = %d\n", curE, curK);
    }
    this->saveToXML("/Users/M/Desktop/test.xml");
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
            currentNeuron->setOutput(gainFunction(sum));
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
    Gradient res(this);
    for (int i = this->numberOfLayers() - 1; i >= 1; i--)
    {
        //printf("i = %d\n", i);
        NeuralLayer* currentLayer = this->getLayer(i);
        if (i == this->numberOfLayers() - 1) {
            for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
            {
                Neuron* neuron = currentLayer->getNeuron(j);
                res.setThreshold(i, j, neuron->getOutput() * (1.0 - neuron->getOutput()) * (neuron->getOutput() - requiredOutput[j]));
            }

            for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
            {
                Neuron* neuron = currentLayer->getNeuron(j);
                for (int k = 0; k < neuron->numberOfDendrons(); k++)
                    res.setWeight(i, j, k, res.getThreshold(i, j) * this->getLayer(i - 1)->getNeuron(k)->getOutput());
            }

        } else {
            for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
            {
                Neuron* neuron = currentLayer->getNeuron(j);
                double tmp_sum = 0;
                for (int k = 0; k < this->getLayer(i + 1)->numberOfNuerons(); k++)
                    tmp_sum += res.getThreshold(i + 1, k) * this->getLayer(i + 1)->getNeuron(k)->getDendronWeight(j);
                res.setThreshold(i, j, neuron->getOutput() * (1.0 - this->getLayer(i + 1)->getNeuron(j)->getOutput()) * tmp_sum);
                //res.setThreshold(i, j, neuron->getOutput() * (1.0 - neuron->getOutput()) * tmp_sum);
            }

            for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
            {
                Neuron* neuron = currentLayer->getNeuron(j);
                for (int k = 0; k < neuron->numberOfDendrons(); k++)
                    res.setWeight(i, j, k, res.getThreshold(i, j) * this->getLayer(i - 1)->getNeuron(k)->getOutput());
            }
        }
    }
    return res;
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
        for (int j = 0; j < currentLayer->numberOfNuerons(); j++)
        {
            Neuron* currentNeuron = currentLayer->getNeuron(j);
            currentNeuron->setThreshold(random());
            for (int k = 0; k < currentNeuron->numberOfDendrons(); k++)
                currentNeuron->setDendronWeight(k, random());
        }
    }
}


