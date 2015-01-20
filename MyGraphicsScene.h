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
    void enableRedimension();
    void disableRedimension();

private:
    QPointF offset;
    QGraphicsPixmapItem *item;
    QGraphicsRectItem *rectTool;
    QGraphicsPixmapItem *grabTool;
    bool grab;
    int mode;


protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

signals:
    void redimensionnement(QRectF);

};

#endif // MYGRAPHICSSCENE_H
