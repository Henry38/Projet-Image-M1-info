
#include "ScaleDialog.h"

ScaleDialog::ScaleDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = new QImage(*imgSource);

    widthText = new QLabel(this);
    widthText->move(30, 295);
    widthText->setText("Largeur : ");

    widthSpinBox = new QSpinBox(this);
    widthSpinBox->move(90, 291);
    widthSpinBox->setMaximum(9999);
    widthSpinBox->setValue(imgSource->width());

    heightText = new QLabel(this);
    heightText->move(30, 325);
    heightText->setText("Hauteur : ");

    heightSpinBox = new QSpinBox(this);
    heightSpinBox->move(90, 321);
    heightSpinBox->setMaximum(9999);
    heightSpinBox->setValue(imgSource->height());

    display(apercu);
    ok_clicked = false;
}

ScaleDialog::~ScaleDialog() {
    delete apercu;
    delete widthText;
    delete heightText;
    delete widthSpinBox;
    delete heightSpinBox;
}

QImage* ScaleDialog::redimensionnementEnLargeur(QImage *imgDepart, float ratio) {
    QImage *imgArrivee = new QImage(imgDepart->width()*ratio, imgDepart->height(), QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    float tmpRatio, coef;
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
                   g2 = qGreen(pixel) * (ratio - coef);    // tmpqH??
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
}

QImage* ScaleDialog::redimensionnementEnHauteur(QImage *imgDepart, float ratio) {
    QImage *imgArrivee = new QImage(imgDepart->width(), imgDepart->height()*ratio, QImage::Format_ARGB32);
    for (int x=0; x<imgArrivee->width(); x++) {
        for (int y=0; y<imgArrivee->height(); y++) {
            imgArrivee->setPixel(x, y, qRgba(0, 0, 0, 255));
        }
    }

    int r1, r2, g1, g2, b1, b2;
    float tmpRatio, coef;
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
}

void ScaleDialog::updateViewer()
{
    float ratioWidth = ((float) widthSpinBox->value()) / ((float) imgSource->width());
    float ratioHeight = ((float) heightSpinBox->value()) / ((float) imgSource->height());

    delete apercu;
    QImage *tmp = redimensionnementEnLargeur(imgSource, ratioWidth);
    apercu = redimensionnementEnHauteur(tmp, ratioHeight);
    delete tmp;

    display(apercu);
    ok_clicked = true;
}

void ScaleDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}
