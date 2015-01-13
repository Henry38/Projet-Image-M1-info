#include "FiltreDialog.h"


FiltreDialog::FiltreDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = new QImage(*imgSource);

    text = new QLabel(this);
    text->move(291, 50);
    text->setText("Taille : ");

    spinBox = new QSpinBox(this);
    spinBox->move(330, 50);
    spinBox->setMinimum(3);
    spinBox->setMaximum(9); //a definir

    gridLayout = new QGridLayout(this);

    moyenneur = new QRadioButton(this);
    moyenneur->setText("moyenneur");
    moyenneur->move(291,80);

    gaussien = new QRadioButton(this);
    gaussien->setText("gaussien");
    gaussien->move(291,110);

    median = new QRadioButton(this);
    median->setText("median");
    median->move(291,140);

    personnalise = new QRadioButton(this);
    personnalise->setText("personnalise");
    personnalise->move(291,170);

    display(apercu);
    ok_clicked = false;
}

FiltreDialog::~FiltreDialog() {
    delete text;
    delete gridLayout;
    delete moyenneur;
    delete gaussien;
    delete median;
    delete personnalise;
    delete spinBox;
    delete apercu;
}

void FiltreDialog::updateViewer()
{
    delete apercu;
    apercu = new QImage(*imgSource);
    Convolution c;
    if(moyenneur->isChecked()){
        c.redimensionnerMatrix(spinBox->value());
        c.convolution(apercu);
    }
    if(median->isChecked()){
        cout << "MEDIAN"<<endl;
    }
    if(gaussien->isChecked()){
        Matrix *noyau = new Matrix(2,1);
        Matrix *mat = noyau->copie();
        c.convolutionCascade(noyau,mat,spinBox->value());
        c.convolution(apercu);

    }
    if(personnalise->isChecked()){
        cout << "PERSO"<<endl;
    }
    //*apercu = apercu->copy(imgSource->rect());

    display(apercu);
    ok_clicked = true;
}

void FiltreDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}

