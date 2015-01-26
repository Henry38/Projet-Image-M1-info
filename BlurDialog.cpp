
#include "BlurDialog.h"

BlurDialog::BlurDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = new QImage(*imgSource);

    text = new QLabel(this);
    text->move(30, 295);
    text->setText("Flou : ");

    spinBox = new QSpinBox(this);
    spinBox->move(80, 291);
    spinBox->setMinimum(0);
    spinBox->setMaximum(99);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxChanged(int)));

    display(apercu);
    ok_clicked = false;
}

BlurDialog::~BlurDialog() {
    delete text;
    delete spinBox;
    delete apercu;
}

void BlurDialog::updateViewer()
{
    delete apercu;
    apercu = new QImage(*imgSource);
    //*apercu = apercu->copy(imgSource->rect());
    Convolution c;
    c.redimensionnerMatrix(spinBox->value()*2 +1);
    c.convolution(apercu);

    display(apercu);
    ok_clicked = true;
}

void BlurDialog::acceptDialog()
{
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}

void BlurDialog::spinBoxChanged(int)
{
    ok_clicked = false;
}
