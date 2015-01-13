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
#include "MyGraphicsView.h"
#include "MyGraphicsScene.h"
#include "scaledialog.h"
using namespace std;

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

private:
    // Attribut
    QImage *img;
    QRubberBand *rubberBand;
    QPoint origin;
    Ui::MainWindow *ui;
    //QGraphicsScene *scene;
    QGraphicsScene *scene;
    QString filename;

};

#endif // MYWINDOW_H
