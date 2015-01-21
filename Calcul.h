#ifndef CALCUL_H
#define CALCUL_H

#include <QImage>

class Calcul {
public:
    static QImage* redimensionnementEnLargeur(QImage*, int);
    static QImage* redimensionnementEnHauteur(QImage*, int);
    static QImage* zoneDeDensite(QImage*);
};

#endif // CALCUL_H
