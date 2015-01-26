#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QLabel>
#include <QSpinBox>

#include "AbstractDialog.h"
#include "Calcul.h"

class ScaleDialog : public AbstractDialog {

    Q_OBJECT

public:
    ScaleDialog(QImage *img);
    ~ScaleDialog();
    QImage* redimensionnementEnLargeur(QImage*, int);
    QImage* redimensionnementEnHauteur(QImage*, int);

private:
    QImage *imgSource, *apercu;
    QLabel *widthText, *heightText;
    QSpinBox *widthSpinBox,*heightSpinBox;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();

private slots:
    void sizeChanged(int);

};

#endif // SCALEDIALOG_H
