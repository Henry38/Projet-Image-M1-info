#ifndef HISTORGB_H
#define HISTORGB_H

#include "Histogramme.h"
#include <QImage>
#include "Couple.h"

class HistoRGB : public Histogramme
{

public:
    HistoRGB(QImage *img);

    void compterPixel();
    void afficherLignes();
    void etalement(Couple c);
    void etalement();
    void egalisation();

    void initDelimitation(Couple c);


};

#endif // HISTORGB_H
