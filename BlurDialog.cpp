
#include "BlurDialog.h"

BlurDialog::BlurDialog(QImage *img) : QDialog(0) {
    setFixedSize(300, 300);
    imgSource = img;

    apercu = new QImage(*imgSource);
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

    buttonUpdate = new QPushButton("Mise à jour", this);
    buttonUpdate->move(160, 221);

    QObject::connect(buttonBox, SIGNAL( accepted() ), this, SLOT( accept() ));
    QObject::connect(buttonBox, SIGNAL( rejected() ), this, SLOT( reject() ));
    QObject::connect(buttonBox, SIGNAL( accepted() ), this, SLOT( applyBlur() ));
    QObject::connect(buttonUpdate, SIGNAL( clicked() ), this, SLOT( updateViewer() ));
}

BlurDialog::~BlurDialog() {
    delete viewer;
    delete text;
    delete buttonBox;
    delete spinBox;
    delete buttonUpdate;
    delete apercu;
}

void BlurDialog::updateViewer() {
    // Appliquer le flou sur apercu !
    //apercu->load("../Projet-Image-M1-info/ressources/test.png");

    viewer->setImage(apercu);
}

void BlurDialog::applyBlur() {
    // Appliquer le flou sur imgSource !

}
