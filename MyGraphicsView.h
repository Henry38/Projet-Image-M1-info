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
    bool getModePipette();
    void setModePipette(bool);
    QImage* getImage();
    void setImage(QImage*);
    QPoint getHG();
    QPoint getBD();
    bool estDansImage(QPoint*);

private:
       QRubberBand *rubberBand;
       bool selectOn ,pret,pipetteOn;
       QPoint HG, BD;
       QGraphicsScene *scene;
       QImage *image;

};
#endif // MYGRAPHICSVIEW_H

