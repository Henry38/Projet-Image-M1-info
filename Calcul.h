#ifndef CALCUL_H
#define CALCUL_H

#include <QImage>

class Calcul {
public:
    static QImage* redimensionnementEnLargeur(QImage*, int);
    static QImage* redimensionnementEnHauteur(QImage*, int);
};

#endif // CALCUL_H
