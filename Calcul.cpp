
#include "Calcul.h"

/*QImage* ScaleDialog::redimensionnementEnLargeur(QImage *imgDepart, double ratio) {
    QImage *imgArrivee = new QImage(imgDepart->width()*ratio, imgDepart->height(), QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    double tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (ratio < 1) {
        // Redimensionnement négatif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = ratio;
            coef = 0;
            for (int x=0; x<imgArrivee->width(); x++) {
                while (tmpRatio <= 1) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * (ratio - coef);
                   g2 = qGreen(pixel) * (ratio - coef);
                   b2 = qBlue(pixel) * (ratio - coef);
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += ratio;
                   coef = 0;
                   xImgDepart++;
                }
                coef = 1.0 - (tmpRatio-ratio);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * coef;
                    g2 = qGreen(pixel) * coef;
                    b2 = qBlue(pixel) * coef;
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio--;
            }
        }
    } else {
        // Redimensionnement positif
        for (int y=0; y<imgArrivee->height(); y++) {
            xImgDepart = 0;
            yImgDepart = y;
            tmpRatio = ratio;
            for (int x=0; x<imgArrivee->width(); x++) {
                if (tmpRatio >= 1) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio--;
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * tmpRatio;
                    g1 = qGreen(pixel) * tmpRatio;
                    b1 = qBlue(pixel) * tmpRatio;
                    xImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (1-tmpRatio);
                    g2 = qGreen(pixel) * (1-tmpRatio);
                    b2 = qBlue(pixel) * (1-tmpRatio);
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = ratio - (1-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}*/

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

/*QImage* ScaleDialog::redimensionnementEnHauteur(QImage *imgDepart, double ratio) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height()*ratio, QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    double tmpRatio, coef;
    int xImgDepart = 0;
    int yImgDepart = 0;
    QRgb pixel;

    if (ratio < 1) {
        // Redimensionnement négatif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = ratio;
            coef = 0;
            for (int y=0; y<imgArrivee->height(); y++) {
                while (tmpRatio <= 1) {
                   pixel = imgArrivee->pixel(x, y);
                   r1 = qRed(pixel);
                   g1 = qGreen(pixel);
                   b1 = qBlue(pixel);
                   pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                   r2 = qRed(pixel) * (ratio - coef);
                   g2 = qGreen(pixel) * (ratio - coef);    // tmpqH??
                   b2 = qBlue(pixel) * (ratio - coef);
                   imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                   tmpRatio += ratio;
                   coef = 0;
                   yImgDepart++;
                }
                coef = 1.0 - (tmpRatio-ratio);
                if (coef > 0) {
                    pixel = imgArrivee->pixel(x, y);
                    r1 = qRed(pixel);
                    g1 = qGreen(pixel);
                    b1 = qBlue(pixel);
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * coef;
                    g2 = qGreen(pixel) * coef;
                    b2 = qBlue(pixel) * coef;
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                }
                tmpRatio--;
            }
        }
    } else {
        // Redimensionnement positif
        for (int x=0; x<imgArrivee->width(); x++) {
            xImgDepart = x;
            yImgDepart = 0;
            tmpRatio = ratio;
            for (int y=0; y<imgArrivee->height(); y++) {
                if (tmpRatio >= 1) {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    imgArrivee->setPixel(x, y, pixel);
                    tmpRatio--;
                } else {
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r1 = qRed(pixel) * tmpRatio;
                    g1 = qGreen(pixel) * tmpRatio;
                    b1 = qBlue(pixel) * tmpRatio;
                    yImgDepart++;
                    pixel = imgDepart->pixel(xImgDepart, yImgDepart);
                    r2 = qRed(pixel) * (1-tmpRatio);
                    g2 = qGreen(pixel) * (1-tmpRatio);
                    b2 = qBlue(pixel) * (1-tmpRatio);
                    imgArrivee->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                    tmpRatio = ratio - (1-tmpRatio);
                }
            }
        }
    }

    return imgArrivee;
}*/

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

#include <iostream>

QImage* Calcul::chemin(QImage* imgDepart) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());
    int width = imgArrivee->width();
    int height = imgArrivee->height();

    float table[width][height];   // colonne ligne
    int indice[width][height];
    QRgb pixel;
    float power;

    // Initialisation
    for (int x=0; x<width; x++) {
        pixel = imgDepart->pixel(x, 0);
        table[x][0] = niveauDeGris(pixel);
        indice[x][0] = 0;
    }

    for (int y=1; y<height; y++) {
        for (int x=0; x<width; x++) {
            pixel = imgDepart->pixel(x, y);
            power = niveauDeGris(pixel);
            table[x][y] = std::numeric_limits<int>::max();
            indice[x][y] = 0;
            for (int k=-1; k<=1; k++) {
                if (x+k >= 0 && x+k < width) {
                    if (power + table[x+k][y-1] < table[x][y]) {
                        table[x][y] = power + table[x+k][y-1];
                        indice[x][y] = k;
                    }
                }
            }
        }
    }

    float min = table[0][height-1];
    int indexMin = 0;
    for (int x=1; x<width; x++) {
        power = table[x][height-1];
        if (power < min) {
            min = power;
            indexMin = x;
        }
    }

    for (int y=height-1; y>=0; y--) {
        imgDepart->setPixel(indexMin, y, qRgba(255, 0, 0, 255));
        indexMin += indice[indexMin][y];
    }

    return imgArrivee;
}

#include "Matrix.h"
#include "Convolution.h"

QImage* Calcul::redimensionnementIntellEnLargeur(QImage *imgDepart, int targetWidth) {
    QImage *imgArrivee = new QImage(targetWidth, imgDepart->height(), imgDepart->format());

    return imgArrivee;
}

QImage* Calcul::redimensionnementIntellEnHauteur(QImage *imgDepart, int targetHeight) {
    QImage *imgArrivee = new QImage(imgDepart->width(), targetHeight, imgDepart->format());

    return imgArrivee;
}

QImage* Calcul::zoneDeDensite(QImage *imgDepart) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height(), imgDepart->format());
    QRgb pixel, tmp;

    int somme;
    int min = 765;
    int max = 0;
    //std::cout << qAbs(-1) << std::endl;

    Matrix *m = new Matrix(imgDepart->width(), imgDepart->height());
    /*m->insert_element(0,0,1);
    m->insert_element(0,1,2);
    m->insert_element(0,2,1);
    m->insert_element(1,0,0);
    m->insert_element(1,1,0);
    m->insert_element(1,2,0);
    m->insert_element(2,0,-1);
    m->insert_element(2,1,-2);
    m->insert_element(2,2,-1);*/

    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            pixel = imgDepart->pixel(x, y);

            somme = 0;
            for (int i=x-1; i<=x+1; i++) {
                for (int j=x-1; j<=x+1; j++) {
                    if (i >= 0 && i < imgArrivee->width() && j >= 0 && j < imgArrivee->height()) {
                        tmp = imgDepart->pixel(i, j);
                        somme += qAbs(qRed(pixel) - qRed(tmp));
                        somme += qAbs(qGreen(pixel) - qGreen(tmp));
                        somme += qAbs(qBlue(pixel) - qBlue(tmp));
                    }
                }
            }
            if (min > somme) {
                min = somme;
            }
            if (max < somme) {
                max = somme;
            }
            m->insert_element(x, y, somme);
            //imgArrivee->setPixel(x, y, qRgba(somme, somme, somme, 255));
            //std::cout << qRed(imgArrivee->pixel(x, y)) << std::endl;
        }
    }

    int res;
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            res = (int) ((((float) (m->get_element(x, y) - min)) / ((float) (max - min))) * 255.0);

            imgArrivee->setPixel(x, y, qRgba(res, res, res, 255));
        }
    }

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
