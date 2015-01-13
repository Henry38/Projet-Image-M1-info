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
    sommeCoefficient = m.sommeCoefficient();
}

void Convolution::modifierCaseMatrix(int i, int j, int val)
{
    m.insert_element(i,j,val);
}

void Convolution::redimentionnerMatrix(int i, int val)
{
    m.resize(i);
    remplireMatrix(val);
}

void Convolution::retournerMatrix()
{
    m.retourner();
}

/*void Convolution::convolution(QImage *image)
{
    int sommeR;
    int sommeG;
    int sommeB;
    QRgb pixel;
    int decallage = m.getSize()/2;
    int finI = image->width() - m.getSize();
    int finJ = image->height() - m.getSize();
    QImage imageCopie(*image);
    retournerMatrix();
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
            if(sommeCoefficient > 0)
            {
                sommeR/=sommeCoefficient;
                sommeG/=sommeCoefficient;
                sommeB/=sommeCoefficient;
            }
            ajusterCouleur(&sommeR);
            ajusterCouleur(&sommeG);
            ajusterCouleur(&sommeB);
            imageCopie.setPixel(i+decallage,j+decallage,qRgb(sommeR,sommeG,sommeB));
        }
    }
    image->swap(imageCopie);
    retournerMatrix();
}*/

void Convolution::convolution(QImage *image)
{
    int sommeR;
    int sommeG;
    int sommeB;
    int nbPixel;
    QRgb pixel;
    int decalage = m.getSize()/2;
    //int finI = image->width();
    //int finJ = image->height() - m.getSize();
    QImage imageCopie(*image);
    retournerMatrix();
    for(int x = 0; x < image->width(); x++)
    {
        for(int y = 0; y < image->height(); y++)
        {
            sommeR = 0;
            sommeG = 0;
            sommeB = 0;
            nbPixel = 0;
            for(int i = -decalage; i <= decalage; i++)
            {
                for(int j = -decalage; j <= decalage; j++)
                {
                    if (x+j >= 0 && x+j < image->width() && y+i >= 0 && y+i < image->height()) {
                        pixel = image->pixel(x+j,y+i);
                        sommeR += qRed(pixel)*m.get_element(i+decalage,j+decalage);
                        sommeG += qGreen(pixel)*m.get_element(i+decalage,j+decalage);
                        sommeB += qBlue(pixel)*m.get_element(i+decalage,j+decalage);
                        nbPixel += m.get_element(i+decalage,j+decalage);
                    }
                }
            }
            if (nbPixel != 0) {
                sommeR/=nbPixel;
                sommeG/=nbPixel;
                sommeB/=nbPixel;
            }
            ajusterCouleur(&sommeR);
            ajusterCouleur(&sommeG);
            ajusterCouleur(&sommeB);
            imageCopie.setPixel(x, y, qRgb(sommeR,sommeG,sommeB));
        }
    }
    image->swap(imageCopie);
    retournerMatrix();
}

void Convolution::ajusterCouleur(int *couleur)
{
    if(*couleur > 255)
        *couleur = 255;
    else if(*couleur < 0)
        *couleur = 0;
}
