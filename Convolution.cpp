#include "Convolution.h"

Convolution::Convolution(int taille, int init)
{
    m.resize(taille);
    remplireMatrix(init);
    sommeCoefficient = m.sommeCoefficient();
}

void Convolution::remplireMatrix(int val)
{
    m.remplire(val);
    sommeCoefficient = val*m.getSize()*m.getSize();
}

void Convolution::modifierCaseMatrix(int i, int j, int val)
{
    m.insert_element(i-1,j-1,val);
}

void Convolution::redimentionnerMatrix(int i, int val)
{
    m.resize(i);
    remplireMatrix(val);
}

void Convolution::convolution(QImage *image)
{
    int sommeR;
    int sommeG;
    int sommeB;
    QRgb pixel;
    int decallage = m.getSize()/2;
    int finI = image->width() - m.getSize();
    int finJ = image->height() - m.getSize();
    QImage imageCopie(*image);

    for(int i = 0; i < finI; i++)
    {
        for(int j = 0; j<finJ; j++)
        {
            sommeR = 0;
            sommeG = 0;
            sommeB = 0;
            for(int k = 0; k < m.getSize(); k++)
            {
                for(int l = 0; l < m.getSize(); l++)
                {
                    pixel = image->pixel(i+k,j+l);
                    sommeR += qRed(pixel)*m.get_element(k,l);
                    sommeG += qGreen(pixel)*m.get_element(k,l);
                    sommeB += qBlue(pixel)*m.get_element(k,l);
                }
            }
            imageCopie.setPixel(i+decallage,j+decallage,qRgb(sommeR/sommeCoefficient,sommeG/sommeCoefficient,sommeB/sommeCoefficient));
        }
    }
    image->swap(imageCopie);
}
