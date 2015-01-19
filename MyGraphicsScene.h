#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>

class MyGraphicsScene : public QGraphicsScene {

    Q_OBJECT

public:
    MyGraphicsScene(QWidget *parent = 0);
    ~MyGraphicsScene();
    void setPixmapItem(QGraphicsPixmapItem *);
    //QGraphicsPixmapItem *addPixmap(const QPixmap&);
    void setVisibleResizeTool(bool);

private:
    QPointF offset;
    QGraphicsPixmapItem *item;
    QGraphicsRectItem *rectTool;
    QGraphicsPixmapItem *grabTool;
    bool grab;


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

signals:
    void redimensionnement(QRectF);

};

#endif // MYGRAPHICSSCENE_H
