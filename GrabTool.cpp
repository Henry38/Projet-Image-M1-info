
#include "GrabTool.h"
#include <iostream>
GrabTool::GrabTool() : QObject(), QGraphicsPixmapItem() {
    QImage img("../Projet-Image-M1-info/ressources/Carre.png");
    setPixmap(QPixmap::fromImage(img));
    click = new QPoint();
    release = new QPoint();

    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsMovable);

}

GrabTool::~GrabTool() {
    delete click;
    delete release;
}

void GrabTool::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    click->setX(e->pos().x());
    click->setY(e->pos().y());
}

void GrabTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    release->setX(e->pos().x());
    release->setY(e->pos().y());
    //setPos(e->scenePos());
    moveBy(release->x()-click->x(), release->y()-click->y());
    //std::cout << x() << ", " << y() << std::endl;
}
/*
void GrabTool::dragEnterEvent(QGraphicsSceneDragDropEvent *e)
{
    std::cout << "DragEnter" << std::endl;
    e->setAccepted(true);
}

void GrabTool::dragLeaveEvent(QGraphicsSceneDragDropEvent *e)
{
    std::cout << "DragLeave" << std::endl;
}

void GrabTool::dropEvent(QGraphicsSceneDragDropEvent *e)
{
    std::cout <<  "DropEvent" << std::endl;
    //setPos(e->pos().x(), e->pos().y());
}
*/
