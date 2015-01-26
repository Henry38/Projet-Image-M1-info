
#include <QApplication>
#include "myWindow.h"
#include<iostream>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    myWindow fen("../Projet-Image-M1-info/ressources/box.png");
    //myWindow fen;
    fen.show();


    return app.exec();
}
