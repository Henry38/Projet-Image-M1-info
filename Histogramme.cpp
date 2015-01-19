#include "Histogramme.h"
#include <qimage.h>
#include <iostream>

#define LONGUEUR_TRAIT 3
#define NOMBRE_ESPACEMENT_ABSCISSE 10
#define NOMBRE_ESPACEMENT_ORDONNEE 10
#define BORD 20
#define HAUTEUR 600
#define LARGEUR 255*3+BORD*2+100

Histogramme::Histogramme(QImage *image) : QImage(LARGEUR,HAUTEUR,QImage::Format_RGB32)
{
    QPainter paint;
    img = new QImage();
    *img = (image->copy(0,0,image->width(),image->height()));
    distanceBord = BORD;
    nombreEspacementAbscisse = NOMBRE_ESPACEMENT_ABSCISSE;
    nombreEspacementOrdonnee = NOMBRE_ESPACEMENT_ABSCISSE;

    longueurAbscisse = width()-distanceBord-1- distanceBord;
    longueurOrdonnee = height()-distanceBord-1 - distanceBord;

    for(int i = 0; i < 256; i++)
    {
        nbPixelRouge[i] = 0;
        nbPixelVert[i] = 0;
        nbPixelBleu[i] = 0;
    }

    paint.begin(this);
    paint.fillRect ( 0, 0, LARGEUR, HAUTEUR, Qt::white);
    paint.end();
}

Histogramme::~Histogramme()
{
    delete img;
}

void Histogramme::afficheHisto()
{
    float tmp;
    float espacement_x;
    float espacement_y;
    QPainter paint;
    paint.begin(this);
    paint.fillRect ( 0, 0, LARGEUR, HAUTEUR, Qt::white);
    paint.setPen (Qt::black);
    paint.drawLine( distanceBord, distanceBord, distanceBord, height()-distanceBord-1);
    paint.drawLine( distanceBord, height()-distanceBord-1, width()-distanceBord-1, height()-distanceBord-1);

    espacement_x = (float)longueurAbscisse / (float)nombreEspacementAbscisse;
    espacement_y = (float)longueurOrdonnee / (float)nombreEspacementOrdonnee;

    tmp = espacement_x + distanceBord;
    for(int i = 1; i <= nombreEspacementAbscisse; i++)
    {
        paint.drawLine(tmp,longueurOrdonnee+distanceBord-LONGUEUR_TRAIT,tmp,longueurOrdonnee+distanceBord+LONGUEUR_TRAIT);
        tmp += espacement_x;
    }
    tmp = longueurOrdonnee + distanceBord - espacement_y;
    for(int i = 1; i <= nombreEspacementOrdonnee; i++)
    {
        paint.drawLine(distanceBord-LONGUEUR_TRAIT,tmp,distanceBord+LONGUEUR_TRAIT,tmp);
        tmp -= espacement_y;
    }
    paint.end();
}

void Histogramme::compterPixel()
{
    QRgb pixel;
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            nbPixelRouge[qRed(pixel)]++;
            nbPixelVert[qGreen(pixel)]++;
            nbPixelBleu[qBlue(pixel)]++;
        }
    }
    valeurMax = 0;
    for(int i = 0; i < 256; i++)
    {
        if(nbPixelRouge[i] > valeurMax)
        {
            valeurMax = nbPixelRouge[i];
        }
        if(nbPixelVert[i] > valeurMax)
        {
            valeurMax = nbPixelVert[i];
        }
        if(nbPixelBleu[i] > valeurMax)
        {
            valeurMax = nbPixelBleu[i];
        }
    }
}

void Histogramme::afficherLignes()
{
    compterPixel();
    afficherLigne(nbPixelBleu,Qt::blue);
    afficherLigne(nbPixelRouge,Qt::red);
    afficherLigne(nbPixelVert,Qt::green);
}

void Histogramme::afficherLigne(int pixels[256], Qt::GlobalColor c)
{
    const int nbCouleur = 256;
    int emplacementAxeAbscisse = longueurOrdonnee+distanceBord;
    QPainter paint;
    QPoint ancien(distanceBord,emplacementAxeAbscisse -(float)((float)pixels[0]/(float)valeurMax)*longueurOrdonnee);
    QPoint nouveau;
    paint.begin(this);
    paint.setPen(c);
    float tmp;
    float espaceEntrePoint = (float)longueurAbscisse/(nbCouleur-1);


    tmp = (float)distanceBord+espaceEntrePoint;
    for(int i = 1; i < nbCouleur; i++)
    {
        nouveau.setX(tmp);
        nouveau.setY(emplacementAxeAbscisse - (float)((float)pixels[i]/(float)valeurMax)*longueurOrdonnee);
        paint.drawLine(ancien.x(),ancien.y(),nouveau.x(),nouveau.y());
        ancien.setX(nouveau.x());
        ancien.setY(nouveau.y());
        tmp += espaceEntrePoint;
    }
    paint.end();
}

void Histogramme::etalement(int min, int max, int vMin, int vMax)
{
    QRgb pixel;
    int tmp;


    for(int i = 0; i < 255; i++)
    {
        nbPixelRouge[i]=0;
        nbPixelVert[i]=0;
        nbPixelBleu[i]=0;
    }
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            tmp = vMax*(qRed(pixel)-min)/((double)(max-min));
            if(tmp>255)
            {
                //cout << tmp << endl;
                tmp = 255;
            }
            else if(tmp < 0)
            {
                //cout << tmp << endl;
                tmp = 0;
            }
            img->setPixel(i,j,qRgba(tmp,tmp,tmp,qAlpha(pixel)));
        }
    }
   afficherLignes();
}

QImage *Histogramme::getImg()
{
    return img;
}
