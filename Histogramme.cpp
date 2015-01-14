#include "Histogramme.h"
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QGraphicsView>
#include "MyGraphicsView.h"
#include <iostream>
#include <QPixmap>

Histogramme::Histogramme(MyGraphicsView *g) : QGraphicsScene()
{
    //scene = new QGraphicsScene();

    /*bouton = new QPushButton("Mon bouton entre en scène !");
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(bouton);
    setSceneRect(0,0,200,200);
    addItem(proxy);
    std::cout << proxy->rect().y() << " " << proxy->rect().x() << std::endl;*/

    g->setScene(this);
    setSceneRect(0,0,200,200);


    pix = new QPixmap();
    pix->load("../Projet-Image-M1-info/ressources/Carre.png");
    repeindre();


}

Histogramme::~Histogramme()
{
    delete pix;
}


void Histogramme::repeindre() {
    clear();
    addPixmap(*pix);

}
