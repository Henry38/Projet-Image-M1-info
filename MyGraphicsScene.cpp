#include "MyGraphicsScene.h"

#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QPoint>
#include <iostream>

MyGraphicsScene::MyGraphicsScene(QWidget *parent) : QGraphicsScene(parent)
{
    grab = false;
    offset = QPoint(0, 0);
    rectTool = addRect(0, 0, 0, 0, QPen(), QBrush());
    rectTool->setZValue(100);
    grabTool = addPixmap(QPixmap::fromImage(QImage("../Projet-Image-M1-info/icones/Carre.png")));
    grabTool->setZValue(100);

    setVisibleResizeTool(false);
}

MyGraphicsScene::~MyGraphicsScene() {
    delete rectTool;
    delete grabTool;
}

void MyGraphicsScene::setPixmapItem(QGraphicsPixmapItem *itemSource)
{
    item = itemSource;
}

void MyGraphicsScene::setVisibleResizeTool(bool visible) {
    if (visible) {
        rectTool->setRect(item->x(), item->y(), item->pixmap().width(), item->pixmap().height());
        int x = item->x() + item->pixmap().width();
        int y = item->y() + item->pixmap().height();
        grabTool->setPos(x, y);
    } else {
        grab = false;
    }
    rectTool->setVisible(visible);
    grabTool->setVisible(visible);
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (grab) {
        rectTool->setRect(item->x(), item->y(), grabTool->x(), grabTool->y());
        QPointF point = mouseEvent->scenePos() - offset;
        if (point.x() < item->x()) {
            point.setX(item->x());
        }
        if (point.y() < item->y()) {
            point.setY(item->y());
        }
        grabTool->setPos(point);
    }
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF point = mouseEvent->scenePos() - grabTool->pos();
    if (grabTool->boundingRect().contains(point.x(), point.y())) {
        offset = point;
        grab = true;
    }
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    grab = false;
    emit redimensionnement(rectTool->rect());
}
