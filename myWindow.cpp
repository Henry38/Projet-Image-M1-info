#include "myWindow.h"
#include "BlurDialog.h"
#include "ui_myWindow.h"
#include "Histogramme.h"
#include "FiltreDialog.h"
#include "HistoDialog.h"
#include <QPixmap>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

#include <QKeyEvent>
#include <QShortcut>
#include <QRectF>
#include "Calcul.h"
using namespace cv;

myWindow::myWindow() : QMainWindow(0), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    img = new QImage();

    filename = "";

    scene = new MyGraphicsScene(this);
    scene->setPixmapItem(itemPixmap);
    ui->graphicsView->setScene(scene);

    pileAnnuler = new QStack<QImage*>();
    pileRefaire = new QStack<QImage*>();
    itemPixmap = scene->addPixmap(QPixmap::fromImage(*img));
    scene->setPixmapItem(itemPixmap);

    initMenu();
    ui->toolBar->toolButtonStyle();
    initBarreOutils();

    QDesktopWidget desktop;
    int xScreen = desktop.screenGeometry().width();
    int yScreen = desktop.screenGeometry().height();
    resize(xScreen / 2, yScreen / 2);
    move((xScreen - width()) / 2, (yScreen - height()) / 2);
}

myWindow::myWindow(QString url) : myWindow()
{
    open(url);
}

myWindow::~myWindow()
{
    delete img;
    delete pileAnnuler;
    delete pileRefaire;
    delete scene;
    delete ui;
}

void myWindow::repeindre()
{
    itemPixmap->setPixmap(QPixmap::fromImage(*img));

    ui->graphicsView->setImage(img);
    scene->setSceneRect(0, 0, img->width(), img->height());
    scene->update();

    QImage* image = new QImage(img->copy(img->rect()));
    pileAnnuler->push(image);
    pileRefaire->empty();
    if (scene->isModeRedimension() || scene->isModeRedimensionIntell()) {
        scene->updateVisibleTool();
    }
}

/*ouvre une nouvelle image en demandant l'url*/
bool myWindow::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg *.gif)");
    if (filename != "")
    {
        return open(filename);
    }
    return false;
}

/*ouvre l'image ciblee par l'url*/
bool myWindow::open(QString url)
{
    if (img->load(url))
    {
        filename = url;
        if(img->format() <= QImage::Format_Indexed8){
            img->convertToFormat(QImage::Format_RGB32);
        }

        pileAnnuler->empty();
        repeindre();
        return true;
    }
    return false;
}

/*sauvegarder sous*/
bool myWindow::saveAsFilename()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save File",
                               "/../Projet-Image-M1-info/ressources/untitled.png",
                               "Images (*.png *.xpm *.jpg)");
    if (filename != "")
    {
        return save(filename);
    }
    return false;
}

/*sauvegarde l'image a l'url donnee*/
bool myWindow::save(QString url)
{
    return img->save(url, 0, -1);
}

void myWindow::initMenu()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    actionOuvrir = new QAction("&Ouvrir",this);
    actionSauvegarder = new QAction("&Sauvegarder",this);
    actionSauvegarderSous = new QAction("&Sauvegarder sous...",this);
    actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionOuvrir);
    menuFichier->addAction(actionSauvegarder);
    menuFichier->addAction(actionSauvegarderSous);
    menuFichier->addAction(actionQuitter);

    QMenu *menuEdition =  menuBar()->addMenu("&Edition");

    actionHistogramme = new QAction("&Histogramme",this);
    actionNiveauDeGris = new QAction("&NiveauDeGris",this);
    actionFlouter = new QAction("&Flouter",this);
    actionFusion = new QAction("&Fusion",this);
    actionRedimensionner = new QAction("&Redimensionner",this);
    actionFiltre = new QAction("&Filtre",this);
    actionContours = new QAction("&Contours",this);
    actionRedimIntell = new QAction("&RedimIntell",this);
    actionGrabCut = new QAction("&GrabCut",this);
    actionRogner = new QAction("&Rogner",this);
    menuEdition->addAction(actionHistogramme);
    menuEdition->addAction(actionNiveauDeGris);
    menuEdition->addAction(actionFlouter);
    menuEdition->addAction(actionFusion);
    menuEdition->addAction(actionRedimensionner);
    menuEdition->addAction(actionFiltre);
    menuEdition->addAction(actionContours);
    menuEdition->addAction(actionRedimIntell);
    menuEdition->addAction(actionGrabCut);
    menuEdition->addAction(actionRogner);

    menuBar()->addAction(menuBar()->addSeparator());


    QObject::connect(actionOuvrir,SIGNAL(triggered()),this,SLOT(openFilename()));
    QObject::connect(actionSauvegarder,SIGNAL(triggered()),this,SLOT(sauvegarder()));
    QObject::connect(actionSauvegarderSous,SIGNAL(triggered()),this,SLOT(saveAsFilename()));
    QObject::connect(actionQuitter,SIGNAL(triggered()),this,SLOT(quitter()));

    QObject::connect(actionHistogramme,SIGNAL(triggered()),this,SLOT(histo()));
    QObject::connect(actionNiveauDeGris,SIGNAL(triggered()),this,SLOT(gris()));
    QObject::connect(actionFlouter,SIGNAL(triggered()),this,SLOT(flouter()));
    QObject::connect(actionFusion,SIGNAL(triggered()),this,SLOT(fusionner()));
    QObject::connect(actionRedimensionner,SIGNAL(triggered()),this,SLOT(redimensionner()));
    QObject::connect(actionFiltre,SIGNAL(triggered()),this,SLOT(filtre()));
    QObject::connect(actionContours,SIGNAL(triggered()),this,SLOT(contours()));
    QObject::connect(actionRedimIntell,SIGNAL(triggered()),this,SLOT(redimIntell()));
    QObject::connect(actionGrabCut,SIGNAL(triggered()),this,SLOT(grabCut()));
    QObject::connect(actionRogner,SIGNAL(triggered()),this,SLOT(rogner()));
}

void myWindow::initBarreOutils()
{
    QObject::connect(ui->actionPipette,SIGNAL(triggered()),this,SLOT(pipette()));
    QObject::connect(ui->actionSelection,SIGNAL(triggered()),this,SLOT(selection()));
    QObject::connect(ui->actionRedimensionner,SIGNAL(triggered()),this,SLOT(redimensionMode()));
    QObject::connect(ui->actionRedimensionIntell,SIGNAL(triggered()),this,SLOT(redimensionIntellMode()));

    QObject::connect(scene, SIGNAL(redimensionnement(QRect)), this, SLOT(redimensionnementIteractif(QRect)));
    QObject::connect(scene, SIGNAL(redimensionnementIntellEnLargeur(QRect)), this, SLOT(redimensionnementIntellEnLargeurIteractif(QRect)));
    QObject::connect(scene, SIGNAL(redimensionnementIntellEnHauteur(QRect)), this, SLOT(redimensionnementIntellEnHauteurIteractif(QRect)));

//    actionAnnuler = new QAction("&Annuler",this);
//    actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
//    actionAnnuler->setVisible(true);
    QShortcut *raccourciAnnuler= new QShortcut(QKeySequence("Ctrl+Z"),this);
    QObject::connect(raccourciAnnuler, SIGNAL(activated()),this, SLOT(annuler()));/*
    QObject::connect(actionAnnuler,SIGNAL(triggered()),this,SLOT(annuler()));

    actionRefaire = new QAction("&Refaire",this);
    actionRefaire->setShortcut(QKeySequence("Ctrl+Y"));
    actionRefaire->setVisible(true);*/
    QShortcut *raccourciRefaire= new QShortcut(QKeySequence("Ctrl+Y"),this);
    QObject::connect(raccourciRefaire, SIGNAL(activated()),this, SLOT(refaire()));
  //  QObject::connect(actionRefaire,SIGNAL(triggered()),this,SLOT(refaire()));

//    actionCopier = new QAction("&Copier",this);
//    actionCopier->setShortcut(QKeySequence("Ctrl+C"));
//    actionCopier->setVisible(true);
    QShortcut *raccourciCopier= new QShortcut(QKeySequence("Ctrl+C"),this);
    QObject::connect(raccourciCopier, SIGNAL(activated()),this, SLOT(copier()));/*
    QObject::connect(actionCopier,SIGNAL(triggered()),this,SLOT(copier()));

    actionCouper = new QAction("&Couper",this);
    actionCouper->setShortcut(QKeySequence("Ctrl+X"));
    actionCouper->setVisible(true);*/
    QShortcut *raccourciCouper= new QShortcut(QKeySequence("Ctrl+X"),this);
    QObject::connect(raccourciCouper, SIGNAL(activated()),this, SLOT(couper()));
    //QObject::connect(actionCouper,SIGNAL(triggered()),this,SLOT(couper()));

//    actionColler = new QAction("&Coller",this);
//    actionColler->setShortcut(QKeySequence("Ctrl+V"));
//    actionColler->setVisible(true);
    QShortcut *raccourciColler= new QShortcut(QKeySequence("Ctrl+V"),this);
    QObject::connect(raccourciColler, SIGNAL(activated()),this, SLOT(coller()));
    //QObject::connect(actionColler,SIGNAL(triggered()),this,SLOT(coller()));

    actionRogner->setEnabled(false);
}

/* Sauvegarder */
bool myWindow::sauvegarder()
{
    if (filename != "") {
        return save(filename);
    }
    return false;
}

/*quitte l'application*/
void myWindow::quitter()
{
    qApp->quit();
}

/*affiche/edite l'histogramme*/
bool myWindow::histo()
{
    HistoDialog histoDial(img);
    if (histoDial.exec() == QDialog::Accepted)
    {
        repeindre();
        return true;
    }
    return false;
}

/*passe l'image en niveau de gris*/
bool myWindow::gris()
{
    QImage *tmp = Calcul::imageEnNiveauDeGris(img);
    delete img;
    img = tmp;
    repeindre();

    return true;
}

/*floute l'image*/
bool myWindow::flouter()
{
    BlurDialog blurDiag(img);
    if (blurDiag.exec() == QDialog::Accepted)
    {
        repeindre();
        return true;
    }
    return false;
}

/*permet de selectionner 2 images et de les fusionner*/
bool myWindow::fusionner()
{
    FusionDialog fusionDialog(img);
    if (fusionDialog.exec() == QDialog::Accepted)
    {
        repeindre();
        return true;
    }
    return false;
}

/*redimensionne l'image en changeant les proportion*/
bool myWindow::redimensionner()
{
    ScaleDialog scaleDialog(img);
    if (scaleDialog.exec() == QDialog::Accepted) {
        repeindre();
        return true;
    }
    return false;
}

bool myWindow::filtre()
{
    FiltreDialog filtreDialog(img);
    if (filtreDialog.exec() == QDialog::Accepted)
    {
        repeindre();
        return true;
    }
    return false;
}

bool myWindow::contours()
{
    QImage *tmp = Calcul::contour(img);
    delete img;
    img = tmp;
    repeindre();

    return true;
}

bool myWindow::redimIntell()
{
    return true;
}

bool myWindow::grabCut()
{
    actionRogner->setEnabled(false);
    ui->graphicsView->cacherSelect();
    if(ui->graphicsView->getPret()){

    /*Tab temp à ne pas modifier tt que sur mme image*/
    Mat bgdModel = *(new Mat());
    Mat fgdModel= *(new Mat());
    /*nb d'iter de l'algo avt de rvoyer le res*/
    int iterCount =1;
    const string name= filename.toStdString();
    /*image*/
   // Mat  im( img->height(), img->width(), CV_8UC3, const_cast<uchar*>(img->bits()), img->bytesPerLine() );
   // im = true ? im.clone() : im;
    //Mat im( img->height(), img->width(), CV_8UC4, const_cast<uchar*>(img->bits()), img->bytesPerLine() );

    //im= true ? im.clone() : im;

    //Mat im = QImageToCvMat( *img, true );
    Mat im = cv::imread(name,1);
    /*masque*/
    Mat mask;
    mask.create( im.size(), CV_8UC1);
    /*ROI : region of interest*/

       QPoint HG = ui->graphicsView->getHG();
       QPoint BD = ui->graphicsView->getBD();
       Calcul::recadrer(img,&HG,&BD);
       /*Si selection dépasse de l'image*/

       Rect rect(HG.x(),HG.y(),BD.x()-HG.x(),BD.y()-HG.y());
       ui->graphicsView->cacherSelect();
       ui->graphicsView->setPret(false);
        /*rect : selection*/
        cv::grabCut( im, mask, rect, bgdModel, fgdModel, iterCount, GC_INIT_WITH_RECT);
        /*fait le decoupage*/
        compare(mask,GC_PR_FGD,mask,CMP_EQ);


        Mat fgd = *(new Mat(im.size(),CV_8UC3,Scalar(255,255,255)));
        im.copyTo(fgd,mask);
        //im.copyTo(fgdModel,mask);

        QImage image( fgd.data, fgd.cols, fgd.rows, fgd.step, QImage::Format_RGB888 );
       //  QImage image( fgd.data, fgd.cols, fgd.rows, fgd.step, QImage::Format_RGB32 );
        image = image.rgbSwapped();
        img = new QImage(image);
        cv::imshow("Resultat",fgd);
        //img = image;
        repeindre();
        return true;

   }else{
       return false;
   }
}

/* rogne la selection de l'image*/
bool myWindow::rogner()
{
    if(ui->graphicsView->modeSelection()){
        if(ui->graphicsView->getPret()){

            QPoint HG = ui->graphicsView->getHG();
            QPoint BD = ui->graphicsView->getBD();
            /*Si selection dépasse de l'image*/
            Calcul::recadrer(img,&HG,&BD);
            QRect rect(HG,BD);
            *img = img->copy(rect);
            ui->graphicsView->cacherSelect();
            ui->graphicsView->setPret(false);
            repeindre();
            return true;

        }else{
            return false;
        }
    }else{
        return false;
    }
}

/*redimensionne l'image a la taille du rectangle*/
bool myWindow::redimensionnementIteractif(QRect rect) {
    QImage *tmp = Calcul::redimensionnementEnLargeur(img, rect.width());
    delete img;
    img = Calcul::redimensionnementEnHauteur(tmp, rect.height());
    delete tmp;
    repeindre();

    return true;
}

bool myWindow::redimensionnementIntellEnLargeurIteractif(QRect rect) {
    QImage *tmp = Calcul::redimensionnementIntellEnLargeur(img, rect.width());
    delete img;
    img = tmp;
    repeindre();

    return true;
}

bool myWindow::redimensionnementIntellEnHauteurIteractif(QRect rect) {
    QImage *tmp = Calcul::redimensionnementIntellEnHauteur(img, rect.height());
    delete img;
    img = tmp;
    repeindre();

    return true;
}

bool myWindow::selection()
{
    if (ui->actionSelection->isChecked()) {
        ui->graphicsView->setModeSelection();
        actionRogner->setEnabled(true);
    } else {
        ui->graphicsView->resetMode();
        ui->graphicsView->cacherSelect();
        actionRogner->setEnabled(false);
    }

    if(ui->actionPipette->isChecked()) {
        ui->actionPipette->setChecked(false);
        ui->statusbar->clearMessage();
    }
    if (ui->actionRedimensionner->isChecked()) {
        ui->actionRedimensionner->setChecked(false);
        scene->disableRedimension();
    }
    if (ui->actionRedimensionIntell->isChecked()) {
        ui->actionRedimensionIntell->setChecked(false);
        scene->disableRedimensionIntell();
    }
    return true;
}

bool myWindow::pipette()
{
    if (ui->actionPipette->isChecked()) {
        ui->graphicsView->setModePipette();
    } else {
        ui->graphicsView->resetMode();
        ui->statusbar->clearMessage();
    }

    if(ui->actionSelection->isChecked()){
        ui->actionSelection->setChecked(false);
        ui->graphicsView->cacherSelect();
        actionRogner->setEnabled(false);
    }
    if (ui->actionRedimensionner->isChecked()) {
        ui->actionRedimensionner->setChecked(false);
        scene->disableRedimension();
    }
    if (ui->actionRedimensionIntell->isChecked()) {
        ui->actionRedimensionIntell->setChecked(false);
        scene->disableRedimensionIntell();
    }
    return true;
}

bool myWindow::redimensionMode()
{
    if (ui->actionRedimensionner->isChecked()) {
        scene->enableRedimension();
    } else {
        scene->disableRedimension();
    }

    ui->graphicsView->resetMode();
    if(ui->actionSelection->isChecked()){
        ui->actionSelection->setChecked(false);
        ui->graphicsView->cacherSelect();
        actionRogner->setEnabled(false);
    }
    if(ui->actionPipette->isChecked()){
        ui->actionPipette->setChecked(false);
        ui->statusbar->clearMessage();
    }
    if (ui->actionRedimensionIntell->isChecked()) {
        ui->actionRedimensionIntell->setChecked(false);
        scene->disableRedimensionIntell();
    }
    return true;
}

bool myWindow::redimensionIntellMode()
{
    if (ui->actionRedimensionIntell->isChecked()) {
        scene->enableRedimensionIntell();
    } else {
        scene->disableRedimensionIntell();
    }

    ui->graphicsView->resetMode();
    if(ui->actionSelection->isChecked()){
        ui->actionSelection->setChecked(false);
        ui->graphicsView->cacherSelect();
        actionRogner->setEnabled(false);
    }
    if(ui->actionPipette->isChecked()){
        ui->actionPipette->setChecked(false);
        ui->statusbar->clearMessage();
    }
    if (ui->actionRedimensionner->isChecked()) {
        ui->actionRedimensionner->setChecked(false);
        scene->disableRedimension();
    }
    return true;
}

bool myWindow::annuler(){
    cout<<"annuler"<<endl;
    if(!pileAnnuler->isEmpty()){
        /*recuperer image ds pile annuler*/

        QImage * image = pileAnnuler->pop();
        image = new QImage(image->copy(image->rect()));
        /*mettre cette image dans pile refaire*/
        pileRefaire->push(image);

        /*afficher l'image*/
        img = image;
        itemPixmap->setPixmap(QPixmap::fromImage(*img));
        ui->graphicsView->setImage(img);
        scene->setSceneRect(0, 0, img->width(), img->height());
        scene->update();

        return true;
    }else{
        cout<<"FAUX! "<<endl;
        return false;
    }
}

bool myWindow::refaire(){
    cout<<"refaire"<<endl;
    if(!pileRefaire->isEmpty()){
        /*recuperer image ds pile refaire*/
        QImage * image =  pileRefaire->pop();
        image = new QImage(image->copy(image->rect()));
        /*mettre cette image dans pile annuler*/
        pileAnnuler->push(image);
        /*afficher image*/
        img = image;
        itemPixmap->setPixmap(QPixmap::fromImage(*img));
        ui->graphicsView->setImage(img);
        scene->setSceneRect(0, 0, img->width(), img->height());
        scene->update();

        return true;
    }else{
        cout<<"FAUX! "<<endl;
        return false;
    }


}

bool myWindow::copier(){
    cout<<"copier"<<endl;


    QPoint HG = ui->graphicsView->getHG();
    QPoint BD = ui->graphicsView->getBD();
    /*Si selection dépasse de l'image*/
    Calcul::recadrer(img,&HG,&BD);
    QRect rect(HG,BD);
    copie = new QImage(img->copy(rect));
    return true;
}

bool myWindow::couper(){
    cout << "couper"<<endl;
    QPoint HG = ui->graphicsView->getHG();
    QPoint BD = ui->graphicsView->getBD();
    /*Si selection dépasse de l'image*/
    Calcul::recadrer(img,&HG,&BD);
    QRect rect(HG,BD);
    copie = new QImage(img->copy(rect));
    copie->fill(Qt::white);
    /*fusion de copie et img*/
    /*img = nvelle_image*/
    /*remplacer avec blanc*/

    return true;
}

bool myWindow::coller(){
    cout <<"coller"<<endl;
    /*remplacer avec copie là où pointeur de souris*/
    return true;
}

inline cv::Mat myWindow::QImageToCvMat( const QImage &inImage, bool inCloneImageData)
  {
     switch ( inImage.format() )
     {
        // 8-bit, 4 channel
        case QImage::Format_RGB32:
        {
           cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

           return (inCloneImageData ? mat.clone() : mat);
        }

        // 8-bit, 3 channel
        case QImage::Format_RGB888:
        {
           if ( !inCloneImageData )
              qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning since we use a temporary QImage";

           QImage   swapped = inImage.rgbSwapped();

           return cv::Mat( swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
        }

        // 8-bit, 1 channel
        case QImage::Format_Indexed8:
        {
           cv::Mat  mat( inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar*>(inImage.bits()), inImage.bytesPerLine() );

           return (inCloneImageData ? mat.clone() : mat);
        }

        default:
           qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
           break;
     }

     return cv::Mat();
  }
