
#include "BlurDialog.h"

BlurDialog::BlurDialog(myWindow *mWin, QImage *img) : QDialog(0) {
    setFixedSize(300, 300);
    this->mWin = mWin;

    apercu = new QImage(*img);
    viewer = new Viewer(10, 10, 200, 200, apercu, this);
    text = new QLabel(this);
    text->move(30, 224);
    text->setText("Flou : ");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->move(120, 270);

    spinBox = new QSpinBox(this);
    spinBox->move(80, 220);
    spinBox->setMinimum(0);
    spinBox->setMaximum(9999);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(repaintViewer(int)));
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT( applyBlur() ));
}

BlurDialog::~BlurDialog() {
    delete viewer;
    delete text;
    delete buttonBox;
    delete spinBox;
}

void BlurDialog::repaintViewer(int n) {
    // Appliquer le flou sur apercu !
    //apercu->load("../Projet-Image-M1-info/ressources/test.png");

    viewer->setImage(apercu);
}

void BlurDialog::applyBlur() {
    // Appliquer le flou sur img !
}
