
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
