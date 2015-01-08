#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QImage>
#include "Matrix.h"

class Convolution {


public:
    Convolution(int taille = 3, int init = 1);
    void redimentionnerMatrix(int i, int val = 1);
    void remplireMatrix(int val);
    void modifierCaseMatrix(int i, int j, int val);
    void convolution(QImage *image);


private:
     Matrix m;
     int sommeCoefficient;

};

#endif // CONVOLUTION_H
