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
    void enableSelectionAvantPlan();
    void disableSelectionAvantPlan();
    void enableSelectionArrierePlan();
    void disableSelectionArrierePlan();
    bool isModeRedimension();
    bool isModeRedimensionIntell();
    bool isModeSelectionAvantPlan();
    bool isModeSelectionArrierePlan();
    void updateVisibleTool();
    void viderAvantPlan();
    void viderArrierePlan();
    QList<QPoint> effacerDoublons(QList<QPoint>);
    QList<QPoint> pointsAvant;
    QList<QPoint> pointsArriere;

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
