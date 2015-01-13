#ifndef FILTREDIALOG_H
#define FILTREDIALOG_H
#include <QObject>
#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QRadioButton>
#include <iostream>

#include "AbstractDialog.h"
#include "Convolution.h"
using namespace std;


class FiltreDialog : public AbstractDialog {

    Q_OBJECT

public:
    FiltreDialog(QImage*);
    ~FiltreDialog();

private:
    QLabel *text;
    QGridLayout *gridLayout;
    QRadioButton *moyenneur,*gaussien,*median,*personnalise;
    QSpinBox *spinBox;
    QImage *imgSource, *apercu;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();
};
#endif // FILTREDIALOG_H
