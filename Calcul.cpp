
#include "Calcul.h"
#include "Convolution.h"
#include "Matrix.h"

QImage* Calcul::contour(QImage *imgDepart) {
    QImage *imgArrivee = new QImage(*imgDepart);

    Convolution c;
    c.redimensionnerMatrix(3,0);

    c.modifierCaseMatrix(0,1,-1);
    c.modifierCaseMatrix(2,1,-1);
    c.modifierCaseMatrix(1,0,-1);
    c.modifierCaseMatrix(1,2,-1);
    c.modifierCaseMatrix(1,1, 5);
    c.convolution(imgArrivee, 1);

    return imgArrivee;
}

QImage* Calcul::imageEnNiveauDeGris(QImage *imgDepart) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());

    QRgb pixel;
    int i, j;
    float tmp;
    int height = imgArrivee->height();
    int width = imgArrivee->width();
    for(i = 0; i < width; i++)
    {
        for(j = 0; j < height; j++)
        {
            pixel = imgDepart->pixel(i, j);
            tmp = niveauDeGris(pixel);
            imgArrivee->setPixel(i, j, qRgba(tmp, tmp, tmp, qAlpha(pixel)));
        }
    }

    return imgArrivee;
}

QImage* Calcul::redimensionnementEnLargeur(QImage *imgDepart, int targetWidth) {
    QImage *imgArrivee = new QImage(targetWidth, imgDepart->height(), QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    int tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (targetWidth < imgDepart->width()) {
        // Redimensionnement négatif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = targetWidth;
            coef = 0;
            for (int x=0; x<imgArrivee->width(); x++) {
                while (tmpRatio <= imgDepart->width()) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   g2 = qGreen(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   b2 = qBlue(pixel) * ((targetWidth - coef) / ((double)imgDepart->width()));
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += targetWidth;
                   coef = 0;
                   xImgDepart++;
                }
                coef = imgDepart->width() - (tmpRatio-targetWidth);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (coef / ((double) imgDepart->width()));
                    g2 = qGreen(pixel) * (coef / ((double) imgDepart->width()));
                    b2 = qBlue(pixel) * (coef / ((double) imgDepart->width()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio -= imgDepart->width();
            }
        }
    } else {
        // Redimensionnement positif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = targetWidth;
            for (int x=0; x<imgArrivee->width(); x++) {
                if (tmpRatio >= imgDepart->width()) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio -= imgDepart->width();
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    g1 = qGreen(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    b1 = qBlue(pixel) * (tmpRatio / ((double) imgDepart->width()));
                    xImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    g2 = qGreen(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    b2 = qBlue(pixel) * ((imgDepart->width()-tmpRatio) / ((double) imgDepart->width()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = targetWidth - (imgDepart->width()-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}

QImage* Calcul::redimensionnementEnHauteur(QImage *imgDepart, int targetHeight) {
    QImage *imgArrivee = new QImage(imgDepart->width(), targetHeight, QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    int tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (targetHeight < imgDepart->height()) {
        // Redimensionnement négatif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = targetHeight;
            coef = 0;
            for (int y=0; y<imgArrivee->height(); y++) {
                while (tmpRatio <= imgDepart->height()) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   g2 = qGreen(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   b2 = qBlue(pixel) * (targetHeight - coef) / ((double) imgDepart->height());
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += targetHeight;
                   coef = 0;
                   yImgDepart++;
                }
                coef = imgDepart->height() - (tmpRatio-targetHeight);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (coef / ((double) imgDepart->height()));
                    g2 = qGreen(pixel) * (coef / ((double) imgDepart->height()));
                    b2 = qBlue(pixel) * (coef / ((double) imgDepart->height()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio -= imgDepart->height();
            }
        }
    } else {
        // Redimensionnement positif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = targetHeight;
            for (int y=0; y<imgArrivee->height(); y++) {
                if (tmpRatio >= imgDepart->height()) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio -= imgDepart->height();
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    g1 = qGreen(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    b1 = qBlue(pixel) * (tmpRatio / ((double) imgDepart->height()));
                    yImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    g2 = qGreen(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    b2 = qBlue(pixel) * ((imgDepart->height()-tmpRatio) / ((double) imgDepart->height()));
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = targetHeight - (imgDepart->height()-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}

/*retourne l'ensemble des coordonnees x des pixels du chemin le moins informatif*/
void Calcul::lessImportantVerticalPath(QImage *imgEnergie, QVector<int> *vect) {
    int width = imgEnergie->width();
    int height = imgEnergie->height();

    float table[width][height];         // colonne ligne
    int indice[width][height];          // indice (-1, 0 ou 1) pour chaque pixel
    float min = std::numeric_limits<int>::max();
    int indexMin = -1;                  // index X du pixel de poids cumulatif minimal sur la derniere ligne
    QRgb pixel;
    float power;

    // Initialisation
    for (int x=0; x<width; x++) {
        table[x][0] = niveauDeGris(imgEnergie->pixel(x, 0));
    }

    // Remplissage de la table et des indices
    for (int y=1; y<height; y++) {
        for (int x=0; x<width; x++) {
            pixel = imgEnergie->pixel(x, y);
            power = niveauDeGris(pixel);
            table[x][y] = std::numeric_limits<int>::max();
            indice[x][y] = 0;
            for (int k=-1; k<=1; k++) {
                if (x+k >= 0 && x+k < width) {
                    if (power + table[x+k][y-1] < table[x][y]) {
                        table[x][y] = power + table[x+k][y-1];
                        indice[x][y] = k;
                        if (y == height-1 && table[x][y] < min) {
                            min = table[x][y];
                            indexMin = x;
                        }
                    }
                }
            }
        }
    }

    for (int y=height-1; y>=0; y--) {
        vect->append(indexMin);
        indexMin += indice[indexMin][y];
    }
}

/*retourne l'ensemble des coordonnees y des pixels du chemin le moins informatif*/
void Calcul::lessImportantHorizontalPath(QImage *imgEnergie, QVector<int> *vect) {
    int width = imgEnergie->width();
    int height = imgEnergie->height();

    float table[width][height];         // colonne ligne
    int indice[width][height];          // indice (-1, 0 ou 1) pour chaque pixel
    float min = std::numeric_limits<int>::max();
    int indexMin = -1;                  // index X du pixel de poids cumulatif minimal sur la derniere ligne
    QRgb pixel;
    float power;

    // Initialisation
    for (int y=0; y<height; y++) {
        table[0][y] = niveauDeGris(imgEnergie->pixel(0, y));
    }

    // Remplissage de la table et des indices
    for (int x=1; x<width; x++) {
        for (int y=0; y<height; y++) {
            pixel = imgEnergie->pixel(x, y);
            power = niveauDeGris(pixel);
            table[x][y] = std::numeric_limits<int>::max();
            indice[x][y] = 0;
            for (int k=-1; k<=1; k++) {
                if (y+k >= 0 && y+k < height) {
                    if (power + table[x-1][y+k] < table[x][y]) {
                        table[x][y] = power + table[x-1][y+k];
                        indice[x][y] = k;
                        if (x == width-1 && table[x][y] < min) {
                            min = table[x][y];
                            indexMin = y;
                        }
                    }
                }
            }
        }
    }

    for (int x=width-1; x>=0; x--) {
        vect->append(indexMin);
        indexMin += indice[x][indexMin];
    }
}


#include <iostream>

/*retourne l'ensemble des coordonnees x des pixels du chemin le moins informatif*/
void Calcul::lessImportantsVerticalsPaths(QImage *imgEnergie, QVector<QVector<int>> *vect) {
    int width = imgEnergie->width();
    int height = imgEnergie->height();

    float table[width][height];         // colonne ligne
    int indice[width][height];          // indice (-1, 0 ou 1) pour chaque pixel
//    float min = std::numeric_limits<int>::max();
//    int indexMin = -1;                  // index X du pixel de poids cumulatif minimal sur la derniere ligne
    QRgb pixel;
    float power;

    // Initialisation
    for (int x=0; x<width; x++) {
        table[x][0] = niveauDeGris(imgEnergie->pixel(x, 0));
    }

    // Remplissage de la table et des indices
    for (int y=1; y<height; y++) {
        for (int x=0; x<width; x++) {
            pixel = imgEnergie->pixel(x, y);
            power = niveauDeGris(pixel);
            table[x][y] = std::numeric_limits<int>::max();
            indice[x][y] = 0;
            for (int k=-1; k<=1; k++) {
                if (x+k >= 0 && x+k < width) {
                    if (power + table[x+k][y-1] < table[x][y]) {
                        table[x][y] = power + table[x+k][y-1];
                        indice[x][y] = k;
//                        if (y == height-1 && table[x][y] < min) {
//                            min = table[x][y];
//                            indexMin = x;
//                        }
                    }
                }
            }
        }
    }

    float min;
    bool use[width];
    int index;

    for (int i=0; i<width; i++) {
        min = std::numeric_limits<int>::max();
        for (int x=0; x<width; x++) {
            if (table[x][height-1] < min && !use[x]) {
                min = table[x][height-1];
                index = x;
            }
        }
        std::cout << index << std::endl;
        use[index] = true;
        vect->append(QVector<int>(0));
        for (int y=height-1; y>=0; y--) {
            vect->last().append(index);
            index += indice[index][y];
        }
    }
}




QImage* Calcul::redimensionnementIntellEnLargeur(QImage *imgDepart, int targetWidth) {
    QImage *imgArrivee = new QImage(*imgDepart);
    QImage *imgEnergie = normeDuGradient(imgDepart);
    QImage *tmpArrivee;
    QImage *tmpEnergie;

    int decal;
    int iteration = qAbs(targetWidth - imgDepart->width());

    // Redimensionnement negatif
    if (targetWidth < imgDepart->width()) {

        // Coordonnees X des pixels du chemin le moins important
        QVector<int> *path = new QVector<int>(0);
        while (iteration > 0) {
            iteration--;
            path->clear();
            lessImportantVerticalPath(imgEnergie, path);

            tmpArrivee = new QImage(imgArrivee->width()-1, imgArrivee->height(), imgArrivee->format());
            tmpEnergie = new QImage(imgArrivee->width()-1, imgArrivee->height(), imgEnergie->format());

            // Modification des images en fonction du chemin trouve
            for (int y=tmpArrivee->height()-1; y>=0; y--) {
                decal = 0;
                for (int x=0; x<tmpArrivee->width()+1; x++) {
                    if (x != path->at(y)) {
                        tmpArrivee->setPixel(x-decal, y, imgArrivee->pixel(x, y));
                        tmpEnergie->setPixel(x-decal, y, imgEnergie->pixel(x, y));
                    } else {
                        decal++;
                    }
                }
            }
            delete imgArrivee;
            delete imgEnergie;
            imgArrivee = tmpArrivee;
            imgEnergie = tmpEnergie;
        }
        delete path;

    // Redimensionnement positif
    } else {

        //QVector<int> path;
        // Coordonnees X des pixels du chemin les moins importants au plus importants
        QVector<QVector<int>> *listPath = new QVector<QVector<int>>(0);
        lessImportantsVerticalsPaths(imgEnergie, listPath);

        std::cout << iteration << std::endl;
        while (listPath->size() > iteration) {
            //iteration--;
            listPath->removeLast();
        }

        for (QVector<int> p : *listPath) {
            std::cout << p.at(0) << std::endl;
            for (int y=imgArrivee->height()-1; y>=0; y--) {
                decal = 0;
                for (int x=0; x<imgArrivee->width(); x++) {
                    if (x == p.at(imgArrivee->height()-1-y)) {
                        imgArrivee->setPixel(x, y, qRgb(255, 0, 0));
                    }
                }
            }
        }


//        while (iteration > 0) {
//            iteration--;
//            path = listPath->takeFirst();

//            tmpArrivee = new QImage(imgArrivee->width()-1, imgArrivee->height(), imgArrivee->format());
//            tmpEnergie = new QImage(imgArrivee->width()-1, imgArrivee->height(), imgEnergie->format());

//            // Modification des images en fonction du chemin trouve
//            for (int y=tmpArrivee->height()-1; y>=0; y--) {
//                decal = 0;
//                for (int x=0; x<tmpArrivee->width()+1; x++) {
//                    if (x != path.at(y)) {
//                        tmpArrivee->setPixel(x-decal, y, imgArrivee->pixel(x, y));
//                        tmpEnergie->setPixel(x-decal, y, imgEnergie->pixel(x, y));
//                    } else {
//                        decal++;
//                    }
//                }
//            }
//            delete imgArrivee;
//            delete imgEnergie;
//            path.clear();
//            imgArrivee = tmpArrivee;
//            imgEnergie = tmpEnergie;
//        }

        delete listPath;
    }

    return imgArrivee;
}

QImage* Calcul::redimensionnementIntellEnHauteur(QImage *imgDepart, int targetHeight) {
    QImage *imgArrivee = new QImage(*imgDepart);
    QImage *imgEnergie = normeDuGradient(imgDepart);
    QImage *tmpArrivee;
    QImage *tmpEnergie;

    int decal;
    int iteration = qAbs(targetHeight - imgDepart->height());

    // Coordonnees Y des pixels du chemin
    QVector<int> *path = new QVector<int>(0);

    // Redimensionnement negatif
    if (targetHeight < imgDepart->height()) {
        while (iteration > 0) {
            iteration--;
            path->clear();
            lessImportantHorizontalPath(imgEnergie, path);

            tmpArrivee = new QImage(imgArrivee->width(), imgArrivee->height()-1, imgArrivee->format());
            tmpEnergie = new QImage(imgArrivee->width(), imgArrivee->height()-1, imgEnergie->format());

            // Modification des images en fonction du chemin trouve
            for (int x=tmpArrivee->width()-1; x>=0; x--) {
                decal = 0;
                for (int y=0; y<tmpArrivee->height()+1; y++) {
                    if (y != path->at(x)) {
                        tmpArrivee->setPixel(x, y-decal, imgArrivee->pixel(x, y));
                        tmpEnergie->setPixel(x, y-decal, imgEnergie->pixel(x, y));
                    } else {
                        decal++;
                    }
                }
            }
            delete imgArrivee;
            delete imgEnergie;
            imgArrivee = tmpArrivee;
            imgEnergie = tmpEnergie;
        }

    // Redimensionnement positif
    } else {


    }
    delete path;

    return imgArrivee;
}

QImage* Calcul::normeDuGradient(QImage *imgDepart) {
    QImage *imgGris = imageEnNiveauDeGris(imgDepart);

    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), QImage::Format_ARGB32);
    Convolution c;

    // Filtre 1 de Sobel
    Matrix *Gx = new Matrix(3,0);
    Gx->insert_element(0, 0, -1);
    Gx->insert_element(0, 1, -2);
    Gx->insert_element(0, 2, -1);
    Gx->insert_element(1, 0, 0);
    Gx->insert_element(1, 1, 0);
    Gx->insert_element(1, 2, 0);
    Gx->insert_element(2, 0, 1);
    Gx->insert_element(2, 1, 2);
    Gx->insert_element(2, 2, 1);
    c.setNoyau(Gx);

    int*** tmpGx = c.convolution2(imgGris);
//    QImage *tmpGx = new QImage(*imgDepart);
//    c.convolution(tmpGx, 4);

    // Filtre 2 de Sobel
    Matrix *Gy = new Matrix(3,0);
    Gy->insert_element(0, 0, -1);
    Gy->insert_element(0, 1, 0);
    Gy->insert_element(0, 2, 1);
    Gy->insert_element(1, 0, -2);
    Gy->insert_element(1, 1, 0);
    Gy->insert_element(1, 2, 2);
    Gy->insert_element(2, 0, -1);
    Gy->insert_element(2, 1, 0);
    Gy->insert_element(2, 2, 1);
    c.setNoyau(Gy);

    int*** tmpGy = c.convolution2(imgGris);
//    QImage *tmpGy = new QImage(*imgDepart);
//    c.convolution(tmpGy, 4);

    //int r, g, b;
    int tmp;
    // Creation de l'image finale
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            tmp = qAbs(tmpGx[y][x][0]) + qAbs(tmpGy[y][x][0]);

            imgArrivee->setPixel(x, y, qRgba(tmp, tmp, tmp, 255));

//            r = qAbs(qRed(tmpGx->pixel(x, y))) + qAbs(qRed(tmpGy->pixel(x, y)));
//            g = qAbs(qGreen(tmpGx->pixel(x, y))) + qAbs(qGreen(tmpGy->pixel(x, y)));
//            b = qAbs(qBlue(tmpGx->pixel(x, y))) + qAbs(qBlue(tmpGy->pixel(x, y)));
//            r = qRed(tmpGx->pixel(x, y)) + qRed(tmpGy->pixel(x, y));
//            g = qGreen(tmpGx->pixel(x, y)) + qGreen(tmpGy->pixel(x, y));
//            b = qBlue(tmpGx->pixel(x, y)) + qBlue(tmpGy->pixel(x, y));
//            imgArrivee->setPixel(x, y, qRgba(r, g, b, 255));
        }
    }

    delete Gx;
    delete Gy;
    delete imgGris;
//    delete tmpGx;
//    delete tmpGy;

    return imgArrivee;
}

QVector<float> Calcul::getYUV(QRgb pixel) {
    QVector<float> yuv;
    float y = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
    float u = 0.492 * (qBlue(pixel) - y);
    float v = 0.877 * (qRed(pixel) - y);
    yuv.append(y);
    yuv.append(u);
    yuv.append(v);
    return yuv;
}

float Calcul::niveauDeGris(QRgb pixel) {
    return 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
}

void Calcul::recadrer(QImage* img,QPoint* A,QPoint*B){

    if(A->x()<0){
        A->setX(0);
    }

    if(A->y()<0){
        A->setY(0);
    }

    if(B->y()<0){
        B->setY(0);
    }

    if(B->x()<0){
        B->setX(0);
    }

    if(A->x() > img->width()){
      /*on recadre à la limite*/
       A->setX(img->width());
    }

    if(A->y() > img->width()){
      /*on recadre à la limite*/
        A->setY(img->width());
    }

    if(B->x() > img->width()){
      /*on recadre à la limite*/
        B->setX(img->width());
    }

    if(B->y() > img->width()){
      /*on recadre à la limite*/
        B->setY(img->width());
    }

}
