#include "Histogramme.h"
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QGraphicsView>
#include "MyGraphicsView.h"
#include <iostream>

Histogramme::Histogramme(MyGraphicsView *g) : QGraphicsScene()
{
    QPushButton *bouton = new QPushButton("Mon bouton entre en scène !");
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(bouton);
    setSceneRect(0,0,200,200);
    addItem(proxy);
    std::cout << proxy->rect().y() << " " << proxy->rect().x() << std::endl;

    QPixmap pix;
    pix.load("../Projet-Image-M1-info/ressources/test.png");
    addPixmap(pix);

    g->setScene(this);
}

Histogramme::~Histogramme()
{

}
