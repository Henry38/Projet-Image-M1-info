#ifndef FILTREDIALOG_H
#define FILTREDIALOG_H

#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QLineEdit>

#include "AbstractDialog.h"
#include "Calcul.h"
#include "Convolution.h"

using namespace std;

class FiltreDialog : public AbstractDialog {

    Q_OBJECT

public:
    FiltreDialog(QImage*);
    ~FiltreDialog();
public slots:
    void changerMatricePerso(int);
    void cacherMatrice();
    void changerMatrice();

private:
    QLabel *text;
    QGridLayout *gridLayout;
    QRadioButton *moyenneur,*gaussien,*median,*personnalise,*gradient/*,*sobel,*robert*/;
    QSpinBox *spinBox;
    QImage *imgSource, *apercu;
    bool ok_clicked, matriceRemplie,modePerso;
    QLineEdit*** matP;
    int valMax,dimMatP;

public slots:
    void updateViewer();
    void acceptDialog();

};

#endif // FILTREDIALOG_H
