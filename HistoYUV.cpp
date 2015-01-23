#include "HistoYUV.h"

HistoYUV::HistoYUV(QImage *img) : Histogramme(img)
{

}

void HistoYUV::afficherLignes()
{
    compterPixel();
    afficherLigne(composantes[0],Qt::cyan);
    afficherLigne(composantes[1],Qt::magenta);
    afficherLigne(composantes[2],Qt::yellow);

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

void HistoYUV::etalement()
{
    QRgb pixel;
    float Y, U, V;
    float tmp;
    Couple cY = getDelimitation(composantes[0]), cU = getDelimitation(composantes[1]), cV = getDelimitation(composantes[2]);
    std::cout<< "cYdeb : " << cY.deb << "cYfin : " << cY.fin << "cU.deb : " << cU.deb << "cU.fin : " << cU.fin  << "cV.deb : " << cV.deb  << "cV.fin : " << cV.fin<< std::endl;
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            tmp = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            Y = 255*(tmp-cY.deb)/((double)(cY.fin-cY.deb));
            U = 255*(0.492*(qBlue(pixel)-tmp)-cU.deb)/((double)(cU.fin-cU.deb));
            V = 255*(0.877*(qRed(pixel)-tmp)-cV.deb)/((double)(cV.fin-cV.deb));
            std::cout<< "Y : " << Y << " U : " << U << " V : " << V  << std::endl;
            /*if(rouge>255)
            {
                rouge = 255;
            }
            else if(rouge < 0)
            {
                rouge = 0;
            }
            if(vert>255)
            {
                vert = 255;
            }
            else if(vert < 0)
            {
                vert = 0;
            }
            if(bleu>255)
            {
                bleu = 255;
            }
            else if(bleu < 0)
            {
                bleu = 0;
            }*/
            img->setPixel(i,j,qRgba(Y+1.13983*V,Y-0.39465*U-0.58060*V,Y+2.03211*U,qAlpha(pixel)));
        }
    }
}

void HistoYUV::etalement(Couple c)
{

}

void HistoYUV::egalisation()
{

}
