
#include <QApplication>
#include "myWindow.h"
#include<iostream>

#include <FusionDialog.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    myWindow fen("../Projet-Image-M1-info/ressources/box.png");
    //myWindow fen;
    fen.show();

    /*QImage *img = new QImage();
    img->load("../Projet-Image-M1-info/ressources/test.png");
    FusionDialog fen(img);
    fen.exec();*/

    return app.exec();
}
