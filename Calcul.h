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
    static QImage* normeDuGradient(QImage*);
    static QVector<float> getYUV(QRgb);
    static float niveauDeGris(QRgb);
    static void recadrer(QImage*,QPoint*,QPoint*);

private:
    //Methodes
    static void lessImportantVerticalPath(QImage*, QVector<int>*);
    static void lessImportantHorizontalPath(QImage*, QVector<int>*);

};

#endif // CALCUL_H
