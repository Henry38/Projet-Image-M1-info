#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QRubberBand>
#include <QPoint>
#include <QDragMoveEvent>
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

public:
    bool getPret();
    void setPret(bool);
    int getMode();
    void resetMode();
    void setModeSelection();
    void setModePipette();
    void setModeRedimension();
    void setModeRedimIntell();
    bool sansMode();
    bool modeSelection();
    bool modePipette();
    bool modeRedimension();
    bool modeRedimIntell();
    void cacherSelect();
    QImage* getImage();
    void setImage(QImage*);
    QPoint getHG();
    QPoint getBD();
    bool estDansImage(QPoint*);

private:
       QRubberBand *rubberBand;
       bool pret;
       int mode;
       QPoint HG, BD;
       QGraphicsScene *scene;
       QImage *image;

};
#endif // MYGRAPHICSVIEW_H

