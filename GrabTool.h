#ifndef GRABTOOL_H
#define GRABTOOL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>

class GrabTool : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

public:
    GrabTool();
    ~GrabTool();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

    /*void dragEnterEvent(QGraphicsSceneDragDropEvent*);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent*);
    void dropEvent(QGraphicsSceneDragDropEvent*);*/

private:
    QPoint *click, *release;
};

#endif // GRABTOOL_H
