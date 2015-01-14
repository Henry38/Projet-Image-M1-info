#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include "AbstractDialog.h"

class ScaleDialog : public AbstractDialog
{
public:
    ScaleDialog(QImage *img);
    ~ScaleDialog();
    QImage* redimensionnementEnLargeur(QImage*, float);
    QImage* redimensionnementEnHauteur(QImage*, float);

private:
    QImage *imgSource, *apercu;
    QLabel *widthText, *heightText;
    QSpinBox *widthSpinBox,*heightSpinBox;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();

};

#endif // SCALEDIALOG_H
