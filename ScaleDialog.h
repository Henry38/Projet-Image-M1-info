#ifndef SCALEDIALOG_H
#define SCALEDIALOG_H

#include <QObject>
#include <QImage>
#include <QLabel>
#include <QSpinBox>

#include "AbstractDialog.h"

class ScaleDialog : public AbstractDialog {

    Q_OBJECT

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

private slots:
    void sizeChanged(int);

};

#endif // SCALEDIALOG_H
