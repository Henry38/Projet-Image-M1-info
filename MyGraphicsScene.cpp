
#include "MyGraphicsScene.h"
#include <QPainter>
#include "myWindow.h"

MyGraphicsScene::MyGraphicsScene(QWidget *parent) : QGraphicsScene(parent)
{
    offset = QPoint(0, 0);
    rectTool = addRect(0, 0, 0, 0, QPen(), QBrush());
    rectTool->setZValue(100);
    dragTool = addPixmap(QPixmap::fromImage(QImage("../Projet-Image-M1-info/icones/Carre2.png")));
    dragTool->setZValue(100);
    dragTool->setOffset(-6, -6);
    dragXTool = addPixmap(QPixmap::fromImage(QImage("../Projet-Image-M1-info/icones/Carre2.png")));
    dragXTool->setZValue(100);
    dragXTool->setOffset(-6, -6);
    dragYTool = addPixmap(QPixmap::fromImage(QImage("../Projet-Image-M1-info/icones/Carre2.png")));
    dragYTool->setZValue(100);
    dragYTool->setOffset(-6, -6);

    grabTool = false;
    grabXTool = false;
    grabYTool = false;
    mode = 0;
    updateVisibleTool();
}

MyGraphicsScene::~MyGraphicsScene() {
    delete rectTool;
    delete dragTool;
    delete dragXTool;
    delete dragYTool;
}

void MyGraphicsScene::setPixmapItem(QGraphicsPixmapItem *itemSource)
{
    item = itemSource;
}

void MyGraphicsScene::enableRedimension()
{
    mode = 3;
    updateVisibleTool();
}

void MyGraphicsScene::disableRedimension()
{
    if (mode == 3) {
        mode = 0;
        updateVisibleTool();
    }
}

void MyGraphicsScene::enableRedimensionIntell()
{
    mode = 4;
    updateVisibleTool();
}

void MyGraphicsScene::disableRedimensionIntell()
{
    if (mode == 4) {
        mode = 0;
        updateVisibleTool();
    }
}

void MyGraphicsScene::enableSelectionAvantPlan()
{
    mode = 5;
    updateVisibleTool();
}

void MyGraphicsScene::disableSelectionAvantPlan()
{
    if (mode == 5) {
        mode = 0;
        updateVisibleTool();
    }
}

void MyGraphicsScene::enableSelectionArrierePlan()
{
    mode = 6;
    updateVisibleTool();
}

void MyGraphicsScene::disableSelectionArrierePlan()
{
    if (mode == 6) {
        mode = 0;
        updateVisibleTool();
    }
}

bool MyGraphicsScene::isModeRedimension()
{
    return (mode == 3);
}

bool MyGraphicsScene::isModeRedimensionIntell()
{
    return (mode == 4);
}

bool MyGraphicsScene::isModeSelectionAvantPlan()
{
    return (mode == 5);
}

bool MyGraphicsScene::isModeSelectionArrierePlan()
{
    return (mode == 6);
}

void MyGraphicsScene::updateVisibleTool() {
    grabTool = false;
    grabXTool = false;
    grabYTool = false;
    rectTool->setVisible(false);
    dragTool->setVisible(false);
    dragXTool->setVisible(false);
    dragYTool->setVisible(false);

    // Mode redimension
    if (isModeRedimension()) {
        rectTool->setVisible(true);
        rectTool->setRect(item->x(), item->y(), item->pixmap().width(), item->pixmap().height());
        int x = item->x() + item->pixmap().width();
        int y = item->y() + item->pixmap().height();
        dragTool->setVisible(true);
        dragTool->setPos(x, y);
    }
    // Mode redimension intelligent
    if (isModeRedimensionIntell()) {
        rectTool->setVisible(true);
        rectTool->setRect(item->x(), item->y(), item->pixmap().width(), item->pixmap().height());
        int x = item->x() + item->pixmap().width();
        int y = item->y() + item->pixmap().height();
        dragXTool->setVisible(true);
        dragXTool->setPos(x, item->y() + (item->pixmap().height() / 2));
        dragYTool->setVisible(true);
        dragYTool->setPos(item->x() + (item->pixmap().width() / 2), y);
    }
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);

    if(isModeSelectionAvantPlan()){
            if(mouseEvent->button() == Qt::LeftButton){

            }
    }else if(isModeSelectionArrierePlan()){
            if(mouseEvent->button() == Qt::LeftButton){

            }
    }else{

        QGraphicsItem *tmp = itemAt(mouseEvent->scenePos(), QTransform());
        if (tmp == dragTool) {
            offset = mouseEvent->scenePos() - dragTool->pos();
            grabTool = true;
        } else if (tmp == dragXTool) {
            offset = mouseEvent->scenePos() - dragXTool->pos();
            grabXTool = true;
        } else if (tmp == dragYTool) {
            offset = mouseEvent->scenePos() - dragYTool->pos();
            grabYTool = true;
        }
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);

    if(isModeSelectionAvantPlan()){
                /*colorie les points selectionnés*/

         /*ajouter point dans liste*/
         pointsAvant.push_front(mouseEvent->scenePos().toPoint());
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x(),mouseEvent->scenePos().toPoint().y()-1));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()-1));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x(),mouseEvent->scenePos().toPoint().y()+1));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()+1));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()+1));
         pointsAvant.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()-1));

     }else if(isModeSelectionArrierePlan()){

        pointsArriere.push_front(mouseEvent->scenePos().toPoint());
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x(),mouseEvent->scenePos().toPoint().y()-1));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()-1));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x(),mouseEvent->scenePos().toPoint().y()+1));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()+1));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()-1,mouseEvent->scenePos().toPoint().y()+1));
        pointsArriere.push_front(QPoint(mouseEvent->scenePos().toPoint().x()+1,mouseEvent->scenePos().toPoint().y()-1));

      }else{
            if (grabTool) {
                QPointF point = mouseEvent->scenePos() - offset;
                if (point.x() < item->x()+1) {
                    point.setX(item->x()+1);
                }
                if (point.y() < item->y()+1) {
                    point.setY(item->y()+1);
                }
                dragTool->setPos(point);
                rectTool->setRect(item->x(), item->y(), dragTool->x(), dragTool->y());
            } else if (grabXTool) {
                int x = mouseEvent->scenePos().x() - offset.x();
                if (x < item->x()+1) {
                    x = item->x()+1;
                }
//                if (x > item->x() + item->pixmap().width()) {
//                    x = item->x() + item->pixmap().width();
//                }
                dragXTool->setX(x);
                rectTool->setRect(item->x(), item->y(), dragXTool->x(), dragYTool->y());
                dragYTool->setX(rectTool->rect().width()/2);
            } else if (grabYTool) {
                int y = mouseEvent->scenePos().y() - offset.y();
                if (y < item->y()+1) {
                    y = item->y()+1;
                }
//                if (y > item->y() + item->pixmap().height()) {
//                    y = item->y() + item->pixmap().height();
//                }
                dragYTool->setY(y);
                rectTool->setRect(item->x(), item->y(), dragXTool->x(), dragYTool->y());
                dragXTool->setY(rectTool->rect().height()/2);
            }
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

    if (grabTool) {
        grabTool = false;
        emit redimensionnement(rectTool->rect().toRect());
    }
    if (grabXTool) {
        grabXTool = false;
        emit redimensionnementIntellEnLargeur(rectTool->rect().toRect());
    }
    if (grabYTool) {
        grabYTool = false;
        emit redimensionnementIntellEnHauteur(rectTool->rect().toRect());
    }
}



void MyGraphicsScene::viderAvantPlan(){
    pointsAvant.empty();
}

void MyGraphicsScene::viderArrierePlan(){
    pointsArriere.empty();
}

QList<QPoint> MyGraphicsScene::effacerDoublons(QList<QPoint> liste){
    int j;
    for(int i=0;i<liste.size();i++){
        j=i+1;
        while(j<liste.size()){
            if(liste.at(i)==liste.at(j)){
                liste.removeAt(j);
            }else{
                j++;
            }
        }
    }
    return liste;
}
