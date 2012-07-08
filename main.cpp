#include <QtCore/QCoreApplication>
#include <cstdio>
#include<iostream>
#include<neuralnetwork.h>
#include<QDir>
#include<QStringList>
#include<QVector>
#include<QImage>
#include<QColor>
#include<QHash>
#include <QDebug>
#include <QTextCodec>

QVector<double> fromImageToVector(const QImage& image)
{
    QVector<double> res;
    QSize size=image.size();
    for(int x=0;x<size.width();x++)
        for(int y=0;y<size.height();y++)
        {
            res<<qGray(image.pixel(x,y));
        }
    return res;
}

int main(int argc, char *argv[])
{
    QString helpString =    QString("NeuralPatternClassificator V0.1\n") +
                            QString("---------------help----------------\n") +
                            QString("-recognize -i <snapshot image> -x <Xml path> [-s <Alpha string>]\n")+
                            QString("-learn -i <Template image dir> -o <Output xml path> [-s <Alpha string>] [-maxK] [-eps] [-lambda] [-micro]\n")+
                            QString("-----------------------------------\n");
    if (argc==1 || argc % 2 == 1)
    {
        std::cout << helpString.toStdString() << std::endl;
    }else
    {
        QString cmd=QTextCodec::codecForLocale()->toUnicode(argv[1]);
        QHash<QString,QString> args;
        for(int i=2;i<argc;i+=2)
        {
            args[argv[i]]=QTextCodec::codecForLocale()->toUnicode(argv[i+1]);
        }
        if(cmd == "-recognize" && args.contains("-i") && args.contains("-x"))
        {
            NeuralNetwork network(args["-x"]);
            QImage image(args["-i"]);
            if (image.isNull())
            {
                std::cout << "No such file." << std::endl;
                return -1;
            }
            fromImageToVector(image);
            QVector<double> res = network.test(fromImageToVector(image));
            printf("Succeed Recognizing!!!\n");
            QString alphaString = (args.contains("-s"))?args["-s"]:"0123456789abcdefghijklmnopqrstuvwxyz";
            //double max=res[0];
            int maxI=0;
            for (int i = 0; i < res.size(); i++) {
                qDebug() << alphaString[i] << " : ";
                printf("%f\n", res[i]);
                if(res[i]>res[maxI])
                    maxI=i;
            }
            qDebug()<<"I suppose its:"<<alphaString[maxI];
        }else if(cmd == "-learn" && args.contains("-i") && args.contains("-o"))
        {
            std::cout << "Start Learning" << std::endl;
            QString alphaString = (args.contains("-s"))?args["-s"]:"0123456789abcdefghijklmnopqrstuvwxyz";
            QDir dir(args["-i"]);
            QStringList list = dir.entryList();
            std::cout << list.length() << std::endl;
            QVector<QVector<double> > output;
            QVector<QVector<double> > input;

            for (int i = 0; i < list.length(); i++)
            {
                qDebug() << "File: " << list[i];
                if (list[i][0] == '.')
                    continue;
                QVector<double> character;
                for (int j = 0; j < alphaString.length(); j++)
                {
                    if (list[i][0] == alphaString[j])
                        character.push_back(1);
                    else
                        character.push_back(0);
                }
                output.push_back(character);
                QImage image(args["-i"] + list[i]);
                QVector<double> bmp = fromImageToVector(image);
                input<<bmp;
            }
            QVector<int> dim;
            dim.push_back(input[0].size());
            dim.push_back(20);
            dim.push_back(output[0].size());
            NeuralNetwork network(dim);
            bool ok=true;
            int maxK=args.contains("-maxK")?args["-maxK"].toInt(&ok):8000;
            if(!ok)
            {
                std::cout << "Bad input" << std::endl;
                return 0;
            }
            double eps=args.contains("-eps")?args["-eps"].toDouble(&ok):0.07;
            if(!ok)
            {
                std::cout << "Bad input" << std::endl;
                return 0;
            }
            double lambda=args.contains("-lambda")?args["-lambda"].toDouble(&ok):0.05;
            if(!ok)
            {
                std::cout << "Bad input" << std::endl;
                return 0;
            }
            double micro=args.contains("-micro")?args["-micro"].toDouble(&ok):0.5;
            if(!ok)
            {
                std::cout << "Bad input" << std::endl;
                return 0;
            }
            network.learn(input, output, maxK, eps, lambda, micro);
            network.saveToXML(args["-o"]);
            std::cout << "Learnt!" << std::endl;
        }else
        {
            std::cout <<"Bad input!"<<std::endl<< helpString.toStdString() << std::endl;
        }
    }
    return 0;
}
