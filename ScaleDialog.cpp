
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

    QObject::connect(widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged(int)));
    QObject::connect(heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(sizeChanged(int)));

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

void ScaleDialog::updateViewer()
{
    delete apercu;
    QImage *tmp = Calcul::redimensionnementEnLargeur(imgSource, widthSpinBox->value());
    apercu = Calcul::redimensionnementEnHauteur(tmp, heightSpinBox->value());
    delete tmp;

    display(apercu);
    ok_clicked = true;
}

void ScaleDialog::acceptDialog()
{
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}

void ScaleDialog::sizeChanged(int)
{
    ok_clicked = false;
}
