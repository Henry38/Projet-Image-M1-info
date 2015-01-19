#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix
{

public:
    Matrix();
    Matrix(int);
    Matrix(int,int);
    ~Matrix();

    void resize(int);
    void insert_element (int, int,int);
    void remplir(int);
    int sommeCoefficient();
    int get_element(int, int);
    int getSize();
    void retourner();
    void remplirMedian();
    bool estPaire();
    void setSize(int);
    void setTab(int**);
    void agrandir(int);
    void afficher();
    Matrix* copie();


private:
    int **tab2D;
    int size;

};

#endif // MATRIX_H
