#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QObject>
#include "BlurDialog.h"
#include "FusionDialog.h"
#include <QtWidgets>
#include <iostream>
#include <QApplication>
#include <QPoint>
#include <QMouseEvent>
#include <QMessageBox>
#include <QRubberBand>
#include <QGraphicsScene>
#include <QtGui>
#include <QtCore>
#include <QStack>
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"
#include "ScaleDialog.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

namespace Ui {
    class MainWindow;
}
class myWindow : public QMainWindow {

    Q_OBJECT
public:
    // Methodes
    myWindow();
    myWindow(QString url);
    ~myWindow();

    void repeindre();
    bool open(QString url);
    bool save(QString url);
    void initMenu();
    void initBarreOutils();
    bool estDansImage();
    inline cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );

public slots:
    // Slot du menu
    //bool ouvrir();
    bool openFilename();
    bool sauvegarder();
    //bool sauvegarderSous();
    bool saveAsFilename();
    void quitter();
    bool histo();
    bool gris();
    bool flouter();
    bool fusionner();
    bool redimensionner();
    bool filtre();
    bool contours();
    bool redimIntell();
    bool grabCut();
    bool rogner();
    bool pipette();
    bool selection();
    bool redimensionnementIteractif(QRect);
    bool redimensionnementIntellEnLargeurIteractif(QRect);
    bool redimensionnementIntellEnHauteurIteractif(QRect);
    bool redimensionMode();
    bool redimensionIntellMode();
    bool annuler();
    bool refaire();
    bool copier();
    bool couper();
    bool coller();

private:
    // Attribut
    QImage *img;
    QAction *actionOuvrir;
    QAction *actionSauvegarder;
    QAction *actionSauvegarderSous;
    QAction *actionQuitter;
    QAction *actionHistogramme;
    QAction *actionNiveauDeGris;
    QAction *actionFlouter;
    QAction *actionFusion;
    QAction *actionRedimensionner;
    QAction *actionFiltre;
    QAction *actionContours;
    QAction *actionRedimIntell;
    QAction *actionGrabCut;
    QAction *actionRogner;
    QAction *actionPipette;
    QAction *actionSelection;
    QAction *actionAnnuler;
    QAction *actionRefaire;
    QAction *actionCopier;
    QAction *actionCouper;
    QAction *actionColler;
    QStack<QImage*>* pileAnnuler;
    QStack<QImage*>* pileRefaire;
    QImage* copie;
    QRubberBand *rubberBand;
    QPoint origin;
    Ui::MainWindow *ui;
    //QGraphicsScene *scene;
    MyGraphicsScene *scene;
    QString filename;
    QGraphicsPixmapItem *itemPixmap;

};

#endif // MYWINDOW_H
