#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QImage>
#include "Matrix.h"

class Convolution {

public:
    Convolution();
    Convolution(Matrix);
    ~Convolution();
    void redimensionnerMatrix(int i, int val = 1);
    void remplirMatrix(int val);
    void modifierCaseMatrix(int i, int j, int val);
    void convolution(QImage *image, bool normalized = true);
    void retournerMatrix();
    Matrix* convolution(Matrix *mat);
    int*** convolutionToMatrix(QImage*);
    void convolutionCascade(Matrix*,Matrix*,int);
    void convolutionMedian(QImage*,int);
    void setNoyau(Matrix*);
    int* lineariser(int deb, int fin,int taille,QImage*);
    int getMedianeFromTab(int* tab,int taille);
    int getMediane(int deb,int fin,int taille,QImage*);
    int* trierTableau(int*,int);

private:
    void ajusterCouleur(int *couleur);
    Matrix m;

};

#endif // CONVOLUTION_H
