#include "Matrix.h"

Matrix::Matrix()
{
    size = 0;
}

Matrix::~Matrix()
{
    for(int i = 0; i < size; i++)
    {
        delete tab2D[i];
    }
    delete tab2D;
}

int Matrix::sommeCoefficient()
{
    int somme = 0;
    for(int i = 0; i<size; i++)
    {
        for(int j = 0; j<size; j++)
        {
            somme += tab2D[i][j];
        }
    }
    return somme;
}

void Matrix::remplire(int val)
{
    for(int i = 0; i < size; i++)
    {
        for(int j= 0; j < size; j++)
        {
            tab2D[i][j] = val;
        }
    }
}

void Matrix::resize(int i)
{
    size = i;
    tab2D = new int*[size];
    for(int i = 0; i < size; i++)
    {
        tab2D[i] = new int[size];
    }
}

void Matrix::retourner()
{
    int tmp;
    for(int i = 0; i < size/2;i++)
    {
        for(int j = 0; j< size;j++)
        {
            tmp = tab2D[i][j];
            tab2D[i][j] = tab2D[size-i-1][j];
            tab2D[size-i-1][j] = tmp;
        }
    }
    for(int i = 0; i < size;i++)
    {
        for(int j = 0; j< size/2;j++)
        {
            tmp = tab2D[i][j];
            tab2D[i][j] = tab2D[i][size-j-1];
            tab2D[i][size-j-1] = tmp;
        }
    }
}

int Matrix::getSize()
{
    return size;
}

void Matrix::insert_element (int i, int j,int val)
{
    tab2D[i][j] = val;
}

int Matrix::get_element(int i, int j)
{
    return tab2D[i][j];
}
