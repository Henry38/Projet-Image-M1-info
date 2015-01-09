#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{

public:
    Matrix();
    ~Matrix();

    void resize(int i);
    void insert_element (int i, int j,int val);
    void remplire(int val);
    int sommeCoefficient();
    int get_element(int i, int j);
    int getSize();
    void retourner();


private:
    int **tab2D;
    int size;

};

#endif // MATRIX_H
