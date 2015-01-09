#include "myWindow.h"

myWindow::myWindow() : QMainWindow(0)
{
    img = new QImage();

    initMenu();
    QDesktopWidget *desktop = new QDesktopWidget;
    int xScreen = desktop->screenGeometry().width();
    int yScreen = desktop->screenGeometry().height();
    move((xScreen - width()) / 2, (yScreen - height()) / 2);
    resize(xScreen / 2, yScreen / 2);

}

myWindow::myWindow(QString url) : myWindow()
{
    open(url);
    repaint();
}

myWindow::~myWindow()
{
    delete img;
}

bool myWindow::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg)");
    if (filename != "")
    {
        return open(filename);
    }
    return false;
}

/*Sauvegarder sous*/
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

bool myWindow::save(QString url)
{
    return img->save(url,0,-1);
}

bool myWindow::open(QString url)
{
    if (img->load(url))
    {
        resize(img->width()+160, img->height()+160);
        return true;
    }
    return false;
}

void myWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    int x = 0;
    int y = 0;
    if (width() > img->width())
    {
        x = (width() - img->width()) / 2;
    }
    if (height() > img->height())
    {
        y = (height() - img->height()) / 2;
    }

    painter.drawImage(x, y, *img);
    painter.end();
}

void myWindow::initMenu()
{
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    QAction *actionOuvrir = new QAction("&Ouvrir",this);
    QAction *actionSauvegarder = new QAction("&Sauvegarder",this);
    QAction *actionSauvegarderSous = new QAction("&Sauvegarder sous...",this);
    QAction *actionQuitter = new QAction("&Quitter", this);
    menuFichier->addAction(actionOuvrir);
    menuFichier->addAction(actionSauvegarder);
    menuFichier->addAction(actionSauvegarderSous);
    menuFichier->addAction(actionQuitter);

    QMenu *menuEdition = menuBar()->addMenu("&Edition");

    QAction *actionHistogramme = new QAction("&Histogramme",this);
    QAction *actionNiveauDeGris = new QAction("&NiveauDeGris",this);
    QAction *actionFlouter = new QAction("&Flouter",this);
    QAction *actionFusion = new QAction("&Fusion",this);
    QAction *actionRedimensionner = new QAction("&Redimensionner",this);
    QAction *actionFiltre = new QAction("&Filtre",this);
    QAction *actionContours = new QAction("&Contours",this);
    QAction *actionRedimIntell = new QAction("&RedimIntell",this);
    QAction *actionGrabCut = new QAction("&GrabCut",this);
    QAction *actionRogner = new QAction("&Rogner",this);
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

    QMenu *menuOutils = menuBar()->addMenu("&Outils");

    QAction *actionPipette = new QAction("&Pipette",this);
    QAction *actionSelection = new QAction("&Selection",this);

    menuOutils->addAction(actionPipette);
    menuOutils->addAction(actionSelection);


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

    QObject::connect(actionPipette,SIGNAL(triggered()),this,SLOT(pipette()));
    QObject::connect(actionSelection,SIGNAL(triggered()),this,SLOT(selection()));
}

bool myWindow::sauvegarder()
{
    return true;
}

void myWindow::quitter(){
    /*êtes vous sur ?*/
    qApp->quit();
}

/*affiche/edite l'histogramme*/
bool myWindow::histo()
{
    return true;
}

/*passe l'image en niveau de gris*/
bool myWindow::gris()
{
    QRgb pixel;
    int i,j,h = img->height(), w = img->width(),tmp;
    for(i=0; i<w; i++)
    {
        for(j = 0; j<h; j++)
        {
            pixel = img->pixel(i,j);
            tmp = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            pixel = qRgb(tmp,tmp,tmp);
            img->setPixel(i,j,pixel);
        }
    }
    repaint();
    return true;
}

/*floute l'image*/
bool myWindow::flouter()
{
    BlurDialog blurDiag(img);
    if (blurDiag.exec() == QDialog::Accepted)
    {
        repaint();
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
        repaint();
        return true;
    }
    return false;
}

bool myWindow::redimensionner()
{
    return true;
}

bool myWindow::filtre()
{
    return true;
}

bool myWindow::contours()
{
    return true;
}

bool myWindow::redimIntell()
{
    return true;
}

bool myWindow::grabCut()
{
    return true;
}

bool myWindow::rogner()
{
    return true;
}

bool myWindow::pipette()
{
    return true;
}

bool myWindow::selection()
{
    return true;
}
