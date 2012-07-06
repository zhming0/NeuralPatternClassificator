#ifndef GRADIENT_H
#define GRADIENT_H
#include<QVector>
class Gradient
{
public:
    Gradient();
private:
    QVector<QVector<double> > threshold;
    QVector<QVector<QVector<double> > > weights;
};

#endif // GRADIENT_H
