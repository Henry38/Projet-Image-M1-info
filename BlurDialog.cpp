
#include "BlurDialog.h"

BlurDialog::BlurDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = NULL;//new QImage(*imgSource);

    text = new QLabel(this);
    text->move(30, 295);
    text->setText("Flou : ");

    spinBox = new QSpinBox(this);
    spinBox->move(80, 291);
    spinBox->setMinimum(0);
    spinBox->setMaximum(99);

    updateViewer();
    ok_clicked = false;
}

BlurDialog::~BlurDialog() {
    delete text;
    delete spinBox;
    delete apercu;
}

void BlurDialog::updateViewer() {
    delete apercu;
    apercu = new QImage(*imgSource);
    Convolution c;
    c.redimentionnerMatrix(spinBox->value()*2 +1);
    c.convolution(apercu);

    display(apercu);

    /*label->setPixmap(QPixmap::fromImage(*apercu));
    getViewer()->setWidget(label);*/
    ok_clicked = true;
}

void BlurDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}
