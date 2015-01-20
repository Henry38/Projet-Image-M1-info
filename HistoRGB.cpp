#include "HistoRGB.h"

HistoRGB::HistoRGB(QImage *img) : Histogramme(img)
{

}

void HistoRGB::etalement(int min, int max, int vMin, int vMax)
{
    QRgb pixel;
    int tmp;


    for(int j = 0; j < 255; j++)
    {
        composantes[0][j]=0;
        composantes[1][j]=0;
        composantes[2][j]=0;
    }

    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            tmp = vMax*(qRed(pixel)-min)/((double)(max-min));
            if(tmp>255)
            {
                tmp = 255;
            }
            else if(tmp < 0)
            {
                tmp = 0;
            }
            img->setPixel(i,j,qRgba(tmp,tmp,tmp,qAlpha(pixel)));
        }
    }
    afficherLignes();
}

void HistoRGB::afficherLignes()
{
    compterPixel();
    if(gris)
    {
        afficherLigne(composantes[0],Qt::gray);
    }
    else
    {
        afficherLigne(composantes[0],Qt::red);
        afficherLigne(composantes[1],Qt::green);
        afficherLigne(composantes[2],Qt::blue);
    }
}

void HistoRGB::compterPixel()
{
    QRgb pixel;
    for(int j = 0; j < 256; j++)
    {
        composantes[0][j]=0;
        composantes[1][j]=0;
        composantes[2][j]=0;
    }
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            composantes[0][qRed(pixel)]++;
            composantes[1][qGreen(pixel)]++;
            composantes[2][qBlue(pixel)]++;
        }
    }
    valeurMax = 0;
    for(int i = 0; i < 256; i++)
    {
        if(composantes[0][i] > valeurMax)
        {
            valeurMax = composantes[0][i];
        }
        if(composantes[1][i] > valeurMax)
        {
            valeurMax = composantes[1][i];
        }
        if(composantes[2][i] > valeurMax)
        {
            valeurMax = composantes[2][i];
        }
    }
}
