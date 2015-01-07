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
using namespace std;

class myWindow : public QMainWindow {

    Q_OBJECT
public:
    // Methodes
    myWindow();
    myWindow(QString url);
    ~myWindow();

    bool open(QString url);
    bool save(QString url);
    void mouseReleaseEvent(QMouseEvent*);
    void initMenu();
    bool estDansImage(int,int);

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

};

#endif // MYWINDOW_H
