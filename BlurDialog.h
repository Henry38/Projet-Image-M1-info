#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QDialogButtonBox>
#include "Viewer.h"
#include "myWindow.h"

class BlurDialog : public QDialog {
    Q_OBJECT

public:
    BlurDialog(QImage &img);
    ~BlurDialog();

private:
    Viewer *viewer;
    QLabel *text;
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;

};

#endif // BLURDIALOG_H
