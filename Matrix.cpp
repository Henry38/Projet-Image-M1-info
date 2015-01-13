#include "Matrix.h"

/*cree une matrice vide*/
Matrix::Matrix()
{
    size = 0;
}

/*cree une matrice de taille size*size */
Matrix::Matrix(int size)
{
    this->size = size;
    tab2D = new int*[size];
    for(int i = 0; i < size; i++)
    {
        tab2D[i] = new int[size];
    }

}

/*cree une matrice de taille size*size et la remplie de val*/
Matrix::Matrix(int size,int val)
{
    this->size = size;
    tab2D = new int*[size];
    for(int i = 0; i < size; i++)
    {
        tab2D[i] = new int[size];
        for(int j=0;j<size;j++){
            tab2D[i][j] = val;
        }
    }

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

void Matrix::remplir(int val)
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

void Matrix::setSize(int size){
    this->size = size;
}

void Matrix::setTab(int** tab){
    tab2D = tab;
}

void Matrix::insert_element (int i, int j,int val)
{
    tab2D[i][j] = val;
}

int Matrix::get_element(int i, int j)
{
    return tab2D[i][j];
}

void Matrix::remplirGaussien(){

}

void Matrix::agrandir(int n){
    int n_size = getSize()+n;
    int** tab = new int*[n_size];
    for(int i = 0; i < getSize(); i++)
    {
        tab[i] = new int[n_size];
        for(int j = 0; j< getSize();j++)
        {
            tab[i][j] = get_element(i,j);
        }
        for(int j= getSize(); j<n_size;j++)
        {
            tab[i][j] = 0;
        }
    }
    for(int i = getSize();i<n_size;i++)
    {
        tab[i] = new int[n_size];
        for(int j=0;j<n_size;j++)
        {
            tab[i][j] = 0;
        }
    }
    setTab(tab);
    setSize(n_size);

}

void Matrix::remplirMedian(){
    Matrix* noyau = new Matrix(2,1);

}

bool Matrix::estPaire(){
    return (getSize()%2 == 0);
}

void Matrix::afficher(){
    for(int i=0;i<getSize();i++)
    {
        for(int j =0;j<getSize();j++)
        {
            cout <<" "<< get_element(i,j);
        }
        cout <<""<<endl;
    }
}

Matrix* Matrix::copie(){
    Matrix* mat = new Matrix(getSize()) ;
    for(int i = 0; i < getSize(); i++)
    {
        for(int j=0;j<getSize();j++)
        {
            mat->insert_element(i,j,get_element(i,j));
        }
    }
    return mat;
}
