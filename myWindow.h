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

    bool open(QString url);
    bool save(QString url);
    void initMenu();
    bool estDansImage();

public slots:
    bool openFilename();
    bool saveAsFilename();
    bool sauvegarder();
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
    // Methodes
    void paintEvent(QPaintEvent *);
    // Attribut
    QImage *img;
    bool pipetteOn, selectOn;
    QRubberBand *rubberBand;
    QPoint origin;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

};

#endif // MYWINDOW_H
