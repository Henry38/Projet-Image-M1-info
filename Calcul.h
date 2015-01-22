#ifndef CALCUL_H
#define CALCUL_H

#include <QImage>
#include <QVector>

class Calcul {
public:
    static QImage* contour(QImage*);
    static QImage* redimensionnementEnLargeur(QImage*, int);
    static QImage* redimensionnementEnHauteur(QImage*, int);
    static QImage* chemin(QImage*);
    static QImage* redimensionnementIntellEnLargeur(QImage*, int);
    static QImage* redimensionnementIntellEnHauteur(QImage*, int);
    static QImage* zoneDeDensite(QImage*);
    static QVector<float> getYUV(QRgb);
    static float niveauDeGris(QRgb);
};

#endif // CALCUL_H
