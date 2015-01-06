
#include "myWindow.h"

myWindow::myWindow(QWidget *parent) : QMainWindow(parent) {
    img = new QImage();

    QDesktopWidget *desktop = new QDesktopWidget;
    int xScreen = desktop->screenGeometry().width();
    int yScreen = desktop->screenGeometry().height();
    move((xScreen - width()) / 2, (yScreen - height()) / 2);
    resize(xScreen / 2, yScreen / 2);

}

myWindow::myWindow(QString url, QWidget *parent) : myWindow(parent) {
    open(url);
    repaint();
}

myWindow::~myWindow() {
    delete img;
}

bool myWindow::openFilename() {
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Test", "Image Files (*.png *.jpg)");
    if (filename != "") {
        return open(filename);
    }
    return false;
}

bool myWindow::open(QString url) {
    if (img->load(url)) {
        resize(img->width(), img->height());
        return true;
    }
    return false;
}

void myWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int x = 0;
    int y = 0;
    if (width() > img->width()) {
        x = (width() - img->width()) / 2;
    }
    if (height() > img->height()) {
        y = (height() - img->height()) / 2;
    }

    painter.drawImage(x, y, *img);
    painter.end();
}
