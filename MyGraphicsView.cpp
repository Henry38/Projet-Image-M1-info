#include "MyGraphicsView.h"
#include "myWindow.h"
#include <sstream>


MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

   rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
   pret = false;
   mode = 0;

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

int MyGraphicsView::getMode(){
    return mode;
}

void MyGraphicsView::resetMode(){
    mode = 0;
}

void MyGraphicsView::setModeSelection(){
    mode = 1;
}

void MyGraphicsView::setModePipette(){
    mode = 2;
}

void MyGraphicsView::setModeRedimension(){

}

void MyGraphicsView::setModeRedimIntell(){

}

bool MyGraphicsView::sansMode(){
    return mode == 0;
}

bool MyGraphicsView::modeSelection(){
    return mode == 1;
}

bool MyGraphicsView::modePipette(){
    return mode == 2;
}

bool MyGraphicsView::modeRedimension(){
    return mode == 3;
}

bool MyGraphicsView::modeRedimIntell(){
    return mode == 4;
}

void MyGraphicsView::cacherSelect(){
    rubberBand->hide();
}

QImage* MyGraphicsView::getImage(){
    return image;
}

void MyGraphicsView::setImage(QImage* img){
    image = img;
}

QPoint MyGraphicsView::getHG(){

    QPoint newHG(qMin(HG.x(),BD.x()),qMin(HG.y(),BD.y()));
    return newHG;
}

QPoint MyGraphicsView::getBD(){
    QPoint newBD(qMax(HG.x(),BD.x()),qMax(HG.y(),BD.y()));
    return newBD;
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent * e)
{
    QGraphicsView::mouseReleaseEvent(e);

    if(modeSelection()) {
       BD =  mapToScene(e->pos()).toPoint();
       HG = mapToScene(HG).toPoint();
        //cout << "Coordonnées : (" << BD.x() << "," << BD.y() << ")"<< endl;
        pret = true;

    }
}

void MyGraphicsView::mousePressEvent(QMouseEvent *e)
{
    QGraphicsView::mousePressEvent(e);

    if (modeSelection() && e->button() == Qt::LeftButton) {
        rubberBand->hide();
        pret = false;
        HG = e->pos();
        //cout << "Coordonnees : (" << HG.x() << "," << HG.y() << ")"<< endl;
        rubberBand->setGeometry(QRect(HG, QSize()));
        rubberBand->show();
    } else if (modePipette() && e->button() == Qt::LeftButton) {
        /* recuperer position souris ; recuperer pixel qui correspond à l'image */
        QPoint *pix = new QPoint(mapToScene(e->pos()).toPoint().x(), mapToScene(e->pos()).toPoint().y());
        if(estDansImage(pix)){
            QRgb pixel = image->pixel(*pix);
            stringstream ss;
            QVector<float> yuv = Calcul::getYUV(pixel);
            ss << "alpha :"<< qAlpha(pixel) <<" R :"<< qRed(pixel) <<" G :"<< qGreen(pixel) <<" B :" << qBlue(pixel)<< endl;
            ss <<"| Y :"<< (int) yuv.at(0) <<" U :"<< (int) yuv.at(1) <<" V :"<< (int) yuv.at(2) <<endl;

            myWindow *w = (myWindow*)this->window();
            w->statusBar()->showMessage(ss.str().c_str());
        }
        delete pix;
    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
    QGraphicsView::mouseMoveEvent(e);

    if (modeSelection()) {
        rubberBand->setGeometry(QRect(HG, e->pos()).normalized());
    }
}

bool MyGraphicsView::estDansImage(QPoint* p){
  return p->x()>=0 && p->y()>=0 && p->x()< image->width() && p->y() < image->height();
}

