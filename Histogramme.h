#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "myWindow.h"
#include <QImage>

#include "Couple.h"

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
    Couple getDelimitation(int nbPixel[256]);
    virtual void etalement(Couple c) = 0;

    QImage *getImg();
    void setImg(QImage *image);

    int *getRouge();

    void reset(QImage *img);

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
