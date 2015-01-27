#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QPoint>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QStatusBar>
#include <QStack>
#include <QDesktopWidget>
#include <QShortcut>
#include <QDebug>

#include "Calcul.h"
#include "BlurDialog.h"
#include "FusionDialog.h"
#include "FiltreDialog.h"
#include "ScaleDialog.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"

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
    void selectAvtPlan();
    void selectArrPlan();

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
    MyGraphicsScene *scene;
    QString filename;
    QGraphicsPixmapItem *itemPixmap;
    cv::Mat matAvantGrabCut;

};

#endif // MYWINDOW_H
