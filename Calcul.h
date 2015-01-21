#ifndef CALCUL_H
#define CALCUL_H

#include <QImage>
#include <QVector>

class Calcul {
public:
    static QImage* redimensionnementEnLargeur(QImage*, int);
    static QImage* redimensionnementEnHauteur(QImage*, int);
    static QImage* zoneDeDensite(QImage*);
    static QVector<float> getYUV(QRgb);
};

#endif // CALCUL_H
