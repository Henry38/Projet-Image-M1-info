#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QObject>
#include <QDialog>
#include <QImage>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include "Viewer.h"
#include "myWindow.h"


class BlurDialog : public QDialog {

    Q_OBJECT
public:
    BlurDialog(QImage*);
    ~BlurDialog();

private:
    Viewer *viewer;
    QLabel *text;
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    QPushButton *buttonUpdate;
    QImage *apercu, *imgSource;

private slots:
    void updateViewer();
    void applyBlur();
};

#endif // BLURDIALOG_H
