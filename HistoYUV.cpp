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

void HistoYUV::etalement(Couple cY)
{
    QRgb pixel;
    float Y, U, V;
    float Yfin, Ufin, Vfin;
    float tmp;
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            tmp = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            Y = 255*(tmp-cY.deb)/((double)(cY.fin-cY.deb));
            U = 0.492*(qBlue(pixel)-tmp);
            V = 0.877*(qRed(pixel)-tmp);
            Yfin = Y+1.13983*V;
            Ufin = Y-0.39465*U-0.58060*V;
            Vfin = Y+2.03211*U;
            if(Ufin > 255)
            {
                Ufin = 255;
            }
            else if(Ufin < 0)
            {
                Ufin = 0;
            }
            if(Vfin > 255)
            {
                Vfin = 255;
            }
            else if(Vfin < 0)
            {
                Vfin = 0;
            }
            img->setPixel(i,j,qRgba(Yfin,Ufin,Vfin,qAlpha(pixel)));
        }
    }
}

void HistoYUV::egalisation()
{
    QRgb pixel;
    float Y, U, V;
    float Yfin, Ufin, Vfin;
    float transformation[256];
    float constante = 255.0/((float)(img->width()*img->height()));
    int somme = 0;
    int tmp;
    for(int i = 0; i < 256; i++)
    {
        somme+=composantes[0][i];
        transformation[i] = constante*somme;
    }
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);


            tmp = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);

            Y = transformation[tmp];

            U = 0.492*(qBlue(pixel)-tmp);
            V = 0.877*(qRed(pixel)-tmp);

            Yfin = Y+1.13983*V;
            Ufin = Y-0.39465*U-0.58060*V;
            Vfin = Y+2.03211*U;

            if(Ufin > 255)
            {
                Ufin = 255;
            }
            else if(Ufin < 0)
            {
                Ufin = 0;
            }
            if(Vfin > 255)
            {
                Vfin = 255;
            }
            else if(Vfin < 0)
            {
                Vfin = 0;
            }
            if(Yfin > 255)
            {
                Yfin = 255;
            }
            else if(Yfin < 0)
            {
                Yfin = 0;
            }

            img->setPixel(i,j,qRgba(Yfin,Ufin,Vfin,qAlpha(pixel)));
        }
    }
}

int *HistoYUV::getY()
{
    return composantes[0];
}
