#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QImage>
#include "Matrix.h"

class Convolution {


public:
    Convolution(int taille = 3, int init = 1);
    Convolution(Matrix);
    ~Convolution();
    void redimensionnerMatrix(int i, int val = 1);
    void remplirMatrix(int val);
    void modifierCaseMatrix(int i, int j, int val);
    void convolution(QImage *image);
    void retournerMatrix();
    Matrix* convolution(Matrix *mat);
    void convolutionCascade(Matrix*,Matrix*,int);


private:
    void ajusterCouleur(int *couleur);
    Matrix m;
    int sommeCoefficient;

};

#endif // CONVOLUTION_H
