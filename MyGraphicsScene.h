#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QPoint>

#include "Calcul.h"

class MyGraphicsScene : public QGraphicsScene {

    Q_OBJECT

public:
    // Methodes
    MyGraphicsScene(QWidget *parent = 0);
    ~MyGraphicsScene();
    void setPixmapItem(QGraphicsPixmapItem *);
    void enableRedimension();
    void disableRedimension();
    void enableRedimensionIntell();
    void disableRedimensionIntell();
    bool isModeRedimension();
    bool isModeRedimensionIntell();
    void updateVisibleTool();

private:
    // Attributs
    QPointF offset;
    QGraphicsPixmapItem *item;
    QGraphicsRectItem *rectTool;
    QGraphicsPixmapItem *dragTool;
    QGraphicsPixmapItem *dragXTool, *dragYTool;
    bool grabTool, grabXTool, grabYTool;
    int mode;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

signals:
    void redimensionnement(QRect);
    void redimensionnementIntellEnLargeur(QRect);
    void redimensionnementIntellEnHauteur(QRect);

};

#endif // MYGRAPHICSSCENE_H
