
#include "BlurDialog.h"

BlurDialog::BlurDialog(myWindow mWin, QImage &img) : QDialog(0) {
    setFixedSize(300, 300);

    viewer = new Viewer(10, 10, 200, 200, img, this);
    text = new QLabel(this);
    text->move(30, 224);
    text->setText("Flou : ");

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->move(120, 270);

    spinBox = new QSpinBox(this);
    spinBox->move(80, 220);
    spinBox->setMinimum(0);
    spinBox->setMaximum(9999);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    connect(buttonBox, SIGNAL(accepted()), mWin, SLOT( applyBlur() ));
}

BlurDialog::~BlurDialog() {
    delete viewer;
    delete text;
    delete buttonBox;
    delete spinBox;
}

void BlurDialog::setResult(int i) {

}
