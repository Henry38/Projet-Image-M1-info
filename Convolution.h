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
    void convolutionMedian(QImage*,int);
    void setNoyau(Matrix*);
    int* lineariser(int deb, int fin,int taille,QImage*);
    int getMedianeFromTab(int* tab,int taille);
    int getMediane(int deb,int fin,int taille,QImage*);
    int* trierTableau(int*,int);
    void convolutionGradient(QImage* image,Matrix* noyau);
    void sommeImage(QImage* im1,QImage* im2);


private:
    void ajusterCouleur(int *couleur);
    Matrix m;
    int sommeCoefficient;

};

#endif // CONVOLUTION_H
