#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QRubberBand>
#include <QPoint>
using namespace std;

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent = 0);
    ~MyGraphicsView();

signals:
    void sendMousePoint(QPoint point);

public slots:
    void mouseReleaseEvent(QMouseEvent * e);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent (QMouseEvent *move);
    bool getPret();
    void setPret(bool);
    QPoint getHG();
    QPoint getBD();

private:
       QRubberBand *rubberBand;
       bool selectOn ,pret;
       QPoint HG, BD;
       QGraphicsScene *scene;
};
#endif // MYGRAPHICSVIEW_H

