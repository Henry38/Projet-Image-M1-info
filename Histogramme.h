#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include "myWindow.h"
#include <QGraphicsScene>

class Histogramme : QGraphicsScene
{

public:
    Histogramme(MyGraphicsView *m);
    ~Histogramme();



public slots:
    void updateViewer();
    void acceptDialog();

private:

};

#endif // HISTOGRAMME_H
