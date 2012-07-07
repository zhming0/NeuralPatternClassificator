#include <QtCore/QCoreApplication>
#include <cstdio>
#include<iostream>
#include<neuralnetwork.h>
#include<QDir>
#include<QStringList>
#include<QVector>
#include<QImage>

QVector<double> fromImageToVector(const QImage& image)
{
    QVector<double> res;
    QSize size=image.size();
    for(int x=0;x<size.width();x++)
        for(int y=0;y<size.height();y++)
        {
            res<<image.pixel(x,y);
        }
    return res;
}

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    QString helpString =    QString("NeuralPatternClassificator V0.1\n") +
                            QString("---------------help----------------\n") +
                            QString("-recognize -i <snapshot>\n")+
                            QString("-learn -i <template path> -o <Output path>\n")+
                            QString("-----------------------------------\n");
    std::cout << argc << std::endl;
    if (argc == 1)
    {
        std::cout << helpString.toStdString() << std::endl;
        //a.quit();
    }else if (argc == 4 && QString(argv[1]) == "-recognize" && QString(argv[2]) == "-i") {
        NeuralNetwork network("/Users/M/Desktop/test.xml");
        QImage image(argv[3]);
        QVector<double> res = network.test(fromImageToVector(image));
        printf("Finish testing!\n");
        QString alphaString = "0123456789abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < res.size(); i++) {
            if (res[i] == 1) {
                std::cout<<alphaString.toStdString()[i] << std::cout;
                break;
            }
        }
    }else if (argc == 6 && QString(argv[1]) == "-learn" && QString(argv[2]) == "-i" && QString(argv[4]) == "-o") {
        std::cout << "Start Learning" << std::endl;
        QString alphaString = "0123456789abcdefghijklmnopqrstuvwxyz";
        QDir dir("/Users/M/Desktop/alphabet_10x16_bw/");
        QStringList list = dir.entryList();
        std::cout << list.length() << std::endl;
        QVector<QVector<double> > output;
        QVector<QVector<double> > input;

        for (int i = 0; i < list.length(); i++)
        {
            std::cout << "File: " << list[i].toStdString() << std::endl;
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

            QImage image("/Users/M/Desktop/alphabet_10x16_bw/" + list[i]);
            QVector<double> bmp = fromImageToVector(image);
            input<<bmp;
        }
        QVector<int> dim;
        dim.push_back(input.size());
        dim.push_back(30);
        dim.push_back(output.size());
        NeuralNetwork network(dim);
        network.learn(input, output, 8000, 0.07, 0.05, 0.5);
    }else {
        std::cout << helpString.toStdString() << std::endl;
    }
    return 0;
}
