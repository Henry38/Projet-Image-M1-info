
#include "FiltreDialog.h"

FiltreDialog::FiltreDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = new QImage(*imgSource);
    valMax = 9;

    FiltreDialog::setFixedWidth(800);
    text = new QLabel(this);
    text->move(291, 50);
    text->setText("Taille : ");

    spinBox = new QSpinBox(this);
    spinBox->move(330, 50);
    spinBox->setMinimum(3);
    spinBox->setMaximum(valMax); //a definir
    QSpinBox::connect(spinBox,SIGNAL(valueChanged(int)),this,SLOT(changerMatricePerso(int)));

    QValidator *validator = new QIntValidator(-999, 999, this);

    matP =  new QLineEdit**[valMax];
    for(int i=0;i<valMax;i++){
        matP[i] = new QLineEdit*[valMax];
       for(int j=0;j<valMax;j++){
         matP[i][j] = new QLineEdit(this);
         matP[i][j]->setValidator(validator);
         matP[i][j]->setFixedWidth(30);
         matP[i][j]->move(450+31*j,50+31*i);
        }
    }
    dimMatP = valMax;

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
    personnalise->setText("perso");
    personnalise->move(291,170);

   // QPushButton *ok = new QPushButton();


    gradient = new QRadioButton(this);
    gradient->setText("gradient");
    gradient->move(291,200);
/*

    sobel = new QRadioButton(this);
    sobel->setText("sobel");
    sobel->move(291,230);


    robert = new QRadioButton(this);
    robert->setText("robert");
    robert->move(291,260);
*/
    modePerso = false;
    matriceRemplie = false;
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
        c.convolutionMedian(apercu,spinBox->value());
    }
    if(gaussien->isChecked()){
        Matrix *noyau = new Matrix(2,1);
        Matrix *mat = noyau->copie();
        c.convolutionCascade(noyau,mat,spinBox->value());
        c.convolution(apercu);

    }
    if(personnalise->isChecked()){
        Matrix *noyau = new Matrix(dimMatP);
        int entreeValide = true;
        int i=0;
        int j;
        while(entreeValide && i<dimMatP){
            j=0;
            while(entreeValide && j<dimMatP){

                if(matP[i][j]->text().isEmpty()){
                    entreeValide = false;
                }else{
                    noyau->insert_element(i,j,matP[i][j]->text().toInt(0,10));
                }
                j++;
            }
            i++;
        }

        if(entreeValide){
            c.setNoyau(noyau);
            c.convolution(apercu);
            entreeValide = false;
        }else{
            cout<<"Il faut remplir toutes les cases !"<<endl;
        }
    }
    if(gradient->isChecked()){
        Matrix *noyau = new Matrix(3,0);
        noyau->insert_element(0,0,-1);
        noyau->insert_element(0,1,0);
        noyau->insert_element(0,2,1);
        noyau->insert_element(1,0,-2);
        noyau->insert_element(1,1,0);
        noyau->insert_element(1,2,2);
        noyau->insert_element(2,0,-1);
        noyau->insert_element(2,1,0);
        noyau->insert_element(2,2,1);
        c.setNoyau(noyau);
        c.convolution(apercu);
        noyau->insert_element(0,0,1);
        noyau->insert_element(0,1,2);
        noyau->insert_element(0,2,1);
        noyau->insert_element(1,0,0);
        noyau->insert_element(1,1,0);
        noyau->insert_element(1,2,0);
        noyau->insert_element(2,0,-1);
        noyau->insert_element(2,1,-2);
        noyau->insert_element(2,2,-1);
        c.setNoyau(noyau);
        c.convolution(apercu);
    }
    display(apercu);
    ok_clicked = true;

}

void FiltreDialog::acceptDialog()
{
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}

void FiltreDialog::changerMatricePerso(int b)
{
    if(personnalise->isChecked()){
        if(spinBox->value()<dimMatP){
            for(int i= 0;i<dimMatP;i++){
                if(i>=spinBox->value()){
                    for(int j=0;j<dimMatP;j++){
                        matP[i][j]->setVisible(false);
                    }
                }else{
                    for(int j=spinBox->value();j<dimMatP;j++){
                        matP[i][j]->setVisible(false);
                    }
                }
            }
        }else if(spinBox->value()>dimMatP){
            for(int i=0;i<spinBox->value();i++){
                if(i>=dimMatP){
                    for(int j=0;j<spinBox->value();j++){
                        matP[i][j]->setVisible(true);
                    }
                }else{
                    for(int j=dimMatP;j<spinBox->value();j++){
                        matP[i][j]->setVisible(true);
                    }
                }
            }
        }
        dimMatP = spinBox->value();
    }
    repaint();
}
