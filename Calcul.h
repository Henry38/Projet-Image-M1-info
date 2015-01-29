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
    static QImage* rognerImage(QImage* src, QPoint HG, QPoint BD);

private:
    //Methodes
    static QVector<QVector<int>>* cheminsOptimaux(QImage*, int);


};

#endif // CALCUL_H
