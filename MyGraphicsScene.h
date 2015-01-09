#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QRubberBand>
#include <QPoint>
using namespace std;

class MyGraphicsScene: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QWidget *parent = 0);

signals:
    void sendMousePoint(QPoint point);

public slots:
    void mouseReleaseEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent (QMouseEvent *move);

private:
       QPoint origin;
       bool selectOn;
};
#endif // MYGRAPHICSSCENE_H
