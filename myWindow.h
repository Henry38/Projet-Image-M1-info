#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QDesktopWidget>

class myWindow : public QMainWindow {

public:
    // Methodes
    myWindow(QWidget *parent = 0);
    myWindow(QString url, QWidget *parent = 0);
    ~myWindow();

    bool openFilename();
    bool open(QString url);

private:
    // Methodes
    void paintEvent(QPaintEvent *);
    // Attribut
    QImage *img;

};

#endif // MYWINDOW_H
