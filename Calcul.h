#ifndef CALCUL_H
#define CALCUL_H

#include <QImage>
#include <QVector>

class Calcul {

public:
    // Methodes
    static QImage* contour(QImage*);
    static QImage* imageEnNiveauDeGris(QImage*);
    static QImage* redimensionnementEnLargeur(QImage*, int);
    static QImage* redimensionnementEnHauteur(QImage*, int);
    static QImage* redimensionnementIntellEnLargeur(QImage*, int);
    static QImage* redimensionnementIntellEnHauteur(QImage*, int);
    static QImage* zoneDeDensite(QImage*);
    static QVector<float> getYUV(QRgb);
    static float niveauDeGris(QRgb);

private:
    //Methodes
    static void lessImportantPass(QImage*, QVector<int>*);

};

#endif // CALCUL_H
