#include "MyGraphicsView.h"
#include "myWindow.h"



MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

   rubberBand = new QRubberBand(QRubberBand::Rectangle,this );
   pret = false;
   selectOn = false;

}

MyGraphicsView::~MyGraphicsView()
{
    delete rubberBand;

}

bool MyGraphicsView::getPret(){
    return pret;
}

void MyGraphicsView::setPret(bool b){
    pret = b;
}
/*A FAIRE*/
/*
QPoint getSelectionBD(){
    return getBD;
}

QPoint getSelectionHG(){
    return HG;
}
*/
QPoint MyGraphicsView::getHG(){

    return HG;
}

QPoint MyGraphicsView::getBD(){
    return BD;
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent * e){
    if(e->button() == Qt::LeftButton)
    {
       BD =  e->pos();

        cout << "Coordonnées : (" << BD.x() << "," << BD.y() << ")"<< endl;

        //rubberBand->hide();
        selectOn = false;
        pret = true;

    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{

    rubberBand->hide();

    pret = false;
    selectOn = true;
    HG = e->pos();
    cout << "Coordonnees : (" << HG.x() << "," << HG.y() << ")"<< endl;
    rubberBand->setGeometry(QRect(HG, QSize()));
    rubberBand->show();
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
    if(selectOn ){
        rubberBand->setGeometry(QRect(HG, e->pos()).normalized());
        rubberBand->show();
    }
}