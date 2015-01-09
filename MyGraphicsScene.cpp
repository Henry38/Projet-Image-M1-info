#include "MyGraphicsScene.h"
#include "myWindow.h"


MyGraphicsScene::MyGraphicsScene(QWidget *parent) :
    QGraphicsScene(parent)
{

}

void MyGraphicsScene::mouseReleaseEvent(QMouseEvent * e){
    if(e->button() == Qt::LeftButton)
    {
       QPoint p =  e->pos();

        cout << "Coordonnées SCENE DEPART: (" << p.x() << "," << p.y() << ")"<< endl;

        selectOn = false;

    }
}

void MyGraphicsScene::mousePressEvent(QMouseEvent *e)
{
    selectOn = true;
     origin = e->pos();
     cout << "Coordonnées SCENE ARRIVEE : (" << origin.x() << "," << origin.y() << ")"<< endl;

}

void MyGraphicsScene::mouseMoveEvent(QMouseEvent *e)
{
   // selectOn = false;
}
