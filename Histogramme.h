#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "myWindow.h"
#include <QGraphicsScene>
#include <QPixmap>

class Histogramme : QGraphicsScene
{

public:
    Histogramme(MyGraphicsView *m);
    ~Histogramme();
    void repeindre();

private:
    QGraphicsScene *scene;
    QPixmap *pix;
};

#endif // HISTOGRAMME_H
