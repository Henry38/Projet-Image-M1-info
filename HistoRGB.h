#ifndef HISTORGB_H
#define HISTORGB_H

#include "Histogramme.h"
#include <QImage>

class HistoRGB : public Histogramme
{

public:
    HistoRGB(QImage *img);

    void compterPixel();
    void afficherLignes();
    void etalement(int v0, int v1, int vMin = 0, int vMax = 255);

};

#endif // HISTORGB_H
