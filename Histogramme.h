#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "myWindow.h"
#include <QImage>

class Histogramme : public QImage
{

public:
    Histogramme(QImage *image);
    ~Histogramme();

    void afficheHisto();
    virtual void compterPixel() = 0;
    virtual void afficherLignes() = 0;
    bool gray();
    void afficherLigne(int pixels[256], Qt::GlobalColor c);
    virtual void etalement(int v0, int v1, int vMin = 0, int vMax = 255) = 0;

    QImage *getImg();
    void setImg(QImage *image);

protected:
    QImage *img;

    bool gris;

    int distanceBord;
    int nombreEspacementAbscisse;
    int nombreEspacementOrdonnee;

    int valeurMax;

    int composantes[3][256];

    int longueurAbscisse;
    int longueurOrdonnee;
};

#endif // HISTOGRAMME_H
