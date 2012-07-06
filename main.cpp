#include <QtCore/QCoreApplication>
#include <cstdio>
#include<iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString s = "你好";
    std::cout << s.toStdString() << std::endl;
    return a.exec();
}
