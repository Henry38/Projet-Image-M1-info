#ifndef HISTOYUV_H
#define HISTOYUV_H

#include "Histogramme.h"

class HistoYUV : public Histogramme
{
public:
    HistoYUV(QImage *img);

    void compterPixel();
    void afficherLignes();
    void etalement(int v0, int v1, int vMin = 0, int vMax = 255);
};

#endif // HISTOYUV_H
