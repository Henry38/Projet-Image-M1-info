#ifndef HISTOYUV_H
#define HISTOYUV_H

#include "Histogramme.h"
#include "Couple.h"

class HistoYUV : public Histogramme
{
public:
    HistoYUV(QImage *img);

    void compterPixel();
    void afficherLignes();
    void etalement(Couple c);
    void etalement();
    void egalisation();

    int *getY();
};

#endif // HISTOYUV_H
