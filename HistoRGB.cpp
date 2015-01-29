#include "HistoRGB.h"
#include <QImage>
#include <QPixmap>

HistoRGB::HistoRGB(QImage *img) : Histogramme(img)
{

}

void HistoRGB::etalement(Couple c)
{
    QRgb pixel;
    float gris;
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            gris = 255*(qRed(pixel)-c.deb)/((double)(c.fin-c.deb));
            if(gris>255)
            {
                gris = 255;
            }
            else if(gris < 0)
            {
                gris = 0;
            }
            img->setPixel(i,j,qRgba(gris,gris,gris,qAlpha(pixel)));
        }
    }
}

void HistoRGB::etalement()
{
    QRgb pixel;
    float rouge, vert, bleu;
    Couple cRouge = getDelimitation(composantes[0]), cVert = getDelimitation(composantes[1]), cBleu = getDelimitation(composantes[2]);
    if(gris)
    {
        etalement(cRouge);
    }
    else
    {
        for(int i = 0; i < img->width(); i++)
        {
            for(int j = 0; j < img->height(); j++)
            {
                pixel = img->pixel(i,j);
                rouge = 255*(qRed(pixel)-cRouge.deb)/((double)(cRouge.fin-cRouge.deb));
                vert = 255*(qGreen(pixel)-cVert.deb)/((double)(cVert.fin-cVert.deb));
                bleu = 255*(qBlue(pixel)-cBleu.deb)/((double)(cBleu.fin-cBleu.deb));
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
                img->setPixel(i,j,qRgba(rouge,vert,bleu,qAlpha(pixel)));
            }
        }
    }
}

void HistoRGB::egalisation()
{
    if(gris)
    {
        egalisationGris();
    }
    else
    {
        QRgb pixel;
        float transformationRouge[256];
        float transformationVert[256];
        float transformationBleu[256];
        float constante = 255.0/((float)(img->width()*img->height()));
        int sommeRouge = 0;
        int sommeVert = 0;
        int sommeBleu = 0;
        for(int i = 0; i < 256; i++)
        {
            sommeRouge+=composantes[0][i];
            transformationRouge[i] = constante*sommeRouge;
            sommeVert+=composantes[0][i];
            transformationVert[i] = constante*sommeVert;
            sommeBleu+=composantes[0][i];
            transformationBleu[i] = constante*sommeBleu;
        }
        for(int i = 0; i < img->width(); i++)
        {
            for(int j = 0; j < img->height(); j++)
            {
                pixel = img->pixel(i,j);

                img->setPixel(i,j,qRgba(transformationRouge[qRed(pixel)],transformationVert[qGreen(pixel)],transformationBleu[qBlue(pixel)],qAlpha(pixel)));
            }
        }
    }
}

void HistoRGB::egalisationGris()
{
    QRgb pixel;
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
            tmp = transformation[qRed(pixel)];
            img->setPixel(i,j,qRgba(tmp,tmp,tmp,qAlpha(pixel)));
        }
    }
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
