#include "HistoYUV.h"

HistoYUV::HistoYUV(QImage *img) : Histogramme(img)
{

}

void HistoYUV::afficherLignes()
{
    compterPixel();
    if(gris)
    {
        afficherLigne(composantes[0],Qt::gray);
    }
    else
    {
        afficherLigne(composantes[0],Qt::cyan);
        afficherLigne(composantes[1],Qt::magenta);
        afficherLigne(composantes[2],Qt::yellow);
    }
}

void HistoYUV::compterPixel()
{
    float Y;
    float U;
    float V;
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
            Y = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            U = 0.492*(qBlue(pixel)-Y);
            V = 0.877*(qRed(pixel)-Y);
            composantes[0][(int)Y]++;
            composantes[1][(int)U]++;
            composantes[2][(int)V]++;
        }
    }
    valeurMax = 0;
    for(int i = 0; i < 256; i++)
    {
        if(composantes[0][i] > valeurMax)
        {
            valeurMax = composantes[0][i];
        }
        if(!gris)
        {
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
}

void HistoYUV::etalement(int v0, int v1, int vMin, int vMax)
{

}
