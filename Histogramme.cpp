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

    gris = true;
    QRgb pixel;
    for(int i = 0; i < img->width(); i++)
    {
        for(int j = 0; j < img->height(); j++)
        {
            pixel = img->pixel(i,j);
            if(qRed(pixel)!=qGreen(pixel) || qGreen(pixel)!=qBlue(pixel))
                gris = false;
        }
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

bool Histogramme::gray()
{
    return gris;
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

    paint.setPen(Qt::black);
    QRectF rect(0,0,50,20);
    QRectF rect2(width()-55,height()-20,50,20);
    std::string s = std::to_string(valeurMax);
    char const *pchar = s.c_str();
    paint.drawText(rect, Qt::AlignLeft,pchar);
    paint.drawText(rect2, Qt::AlignRight,"255");
    paint.setPen(c);

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

Couple Histogramme::getDelimitation(int nbPixel[])
{
    Couple c;
    int i = 0;
    while(nbPixel[i] == 0)
    {
        i++;
    }
    c.deb = i;
    i = 255;
    while(nbPixel[i] == 0)
    {
        i--;
    }
    c.fin = i;
    return c;
}

QImage *Histogramme::getImg()
{
    return img;
}

void Histogramme::setImg(QImage * image)
{
    *img = (image->copy(0,0,image->width(),image->height()));
}

int *Histogramme::getRouge()
{
    return composantes[0];
}

void Histogramme::reset(QImage *img)
{
    setImg(img);
    compterPixel();
}


