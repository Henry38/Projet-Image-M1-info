#include "MyGraphicsView.h"
#include "myWindow.h"



MyGraphicsView::MyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{

   rubberBand = new QRubberBand(QRubberBand::Rectangle,this );
   pret = false;
   selectOn = false;
   pipetteOn = false;

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

bool MyGraphicsView::getModePipette(){
    return pipetteOn;
}

void MyGraphicsView::setModePipette(bool b){
    pipetteOn = b;
}


QImage* MyGraphicsView::getImage(){
    return image;
}

void MyGraphicsView::setImage(QImage* img){
    image = img;
}

QPoint MyGraphicsView::getHG(){

    QPoint *newHG = new QPoint(qMin(HG.x(),BD.x()),qMin(HG.y(),BD.y()));
    return *newHG;
}

QPoint MyGraphicsView::getBD(){
    QPoint *newBD = new QPoint(qMax(HG.x(),BD.x()),qMax(HG.y(),BD.y()));
    return *newBD;
}

void MyGraphicsView::mouseReleaseEvent(QMouseEvent * e){
    if(e->button() == Qt::LeftButton)
    {
       BD =  e->pos();

        //cout << "Coordonnées : (" << BD.x() << "," << BD.y() << ")"<< endl;
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
    //cout << "Coordonnees : (" << HG.x() << "," << HG.y() << ")"<< endl;
    rubberBand->setGeometry(QRect(HG, QSize()));
    rubberBand->show();

    if(pipetteOn){
        /*recuperer position souris ; recuperer pixel qui correspond à l'image*/
        QPoint *pix = new QPoint(e->pos().x() -width()/2 + image->width()/2 , e->pos().y() -height()/2 +image->height()/2 );
        if(estDansImage(pix)){
            QRgb pixel = image->pixel(*pix);
            cout << "Couleur : alpha :"<< qAlpha(pixel) <<" R "<< qRed(pixel) <<" G "<< qGreen(pixel) <<" B " << qBlue(pixel)<< endl;
            cout <<"Couleur : alpha :"<<" Y "<<" U "<<"V " <<endl;
        }

    }
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *e)
{
    if(selectOn){
        rubberBand->setGeometry(QRect(HG, e->pos()).normalized());
        rubberBand->show();
    }

}

bool MyGraphicsView::estDansImage(QPoint* p){
  return p->x()>=0 && p->y()>=0 && p->x()< image->width() && p->y() < image->height();
}


