
#include <QApplication>
#include "myWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    myWindow fen("../Projet-Image-M1-info/ressources/box.jpg");
    //myWindow fen;
    fen.show();


    return app.exec();
}
