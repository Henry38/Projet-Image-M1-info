
#include "scaledialog.h"

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
#include <iostream>
void ScaleDialog::updateViewer()
{
    //delete apercu;
    //apercu = new QImage(*imgSource);

    float qW = ((float) widthSpinBox->value()) / ((float) imgSource->width());
    float qH = ((float) heightSpinBox->value()) / ((float) imgSource->height());
    float tmpqW, tmpqH;
    int xImgSource = 0;
    int yImgSource = 0;
    int offset = 0;
    int r1, r2, g1, g2, b1, b2;
    QRgb pixel;

    QImage *tmp = new QImage(imgSource->width(), (int) (imgSource->height()*qH), QImage::Format_ARGB32);
    for (int x=0; x<tmp->width(); x++) {
        xImgSource = x;
        yImgSource = 0;
        tmpqH = qH;
        for (int y=0; y<tmp->height(); y++) {
            while (tmpqH <= 1) {
               pixel = tmp->pixel(x, y);
               r1 = qRed(pixel);
               g1 = qGreen(pixel);
               b1 = qBlue(pixel);
               pixel = imgSource->pixel(xImgSource, yImgSource);
               if (offset != 0) {
                   r2 = qRed(pixel) * (qH - offset);
                   g2 = qGreen(pixel) * (qH - offset);
                   b2 = qBlue(pixel) * (qH - offset);
                   offset = 0;
               } else {
                   r2 = qRed(pixel) * qH;
                   g2 = qGreen(pixel) * qH;
                   b2 = qBlue(pixel) * qH;
               }
               tmp->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
               tmpqH += qH;
               yImgSource++;
            }
            if (tmpqH - qH <= 1) {
                tmpqH = qH;
            }
            if (tmpqH > 1) {
                tmpqH = 1 - (tmpqH - qH);
                pixel = tmp->pixel(x, y);
                r1 = qRed(pixel);
                g1 = qGreen(pixel);
                b1 = qBlue(pixel);
                pixel = imgSource->pixel(xImgSource, yImgSource);
                r2 = qRed(pixel) * tmpqH;
                g2 = qGreen(pixel) * tmpqH;
                b2 = qBlue(pixel) * tmpqH;
                tmp->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                offset = tmpqH;
                tmpqH = qH - tmpqH;
            }

        }
    }
    /*for (int x=0; x<tmp->width(); x++) {
        xImgSource = x;
        yImgSource = 0;
        tmpqH = qH;
        for (int y=0; y<tmp->height(); y++) {
            if (tmpqH >= 1) {
                //pixel = qRgba(qRed(xImgSource), qGreen(xImgSource), qBlue(xImgSource), 255);
                pixel = imgSource->pixel(xImgSource, yImgSource);
                tmp->setPixel(x, y, pixel);
                tmpqH--;
            } else {
                pixel = imgSource->pixel(xImgSource, yImgSource);
                int r1 = qRed(pixel) * tmpqH;
                int g1 = qGreen(pixel) * tmpqH;
                int b1 = qBlue(pixel) * tmpqH;
                yImgSource++;
                pixel = imgSource->pixel(xImgSource, yImgSource);
                int r2 = qRed(pixel) * (1-tmpqH);
                int g2 = qGreen(pixel) * (1-tmpqH);
                int b2 = qBlue(pixel) * (1-tmpqH);
                tmp->setPixel(x, y, qRgba(r1+r2, g1+g2, b1+b2, 255));
                tmpqH = qH-(1-tmpqH);
            }
        }
    }*/

    std::cout << tmp->width() << std::endl;
    display(tmp);
    ok_clicked = true;
}

void ScaleDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}
