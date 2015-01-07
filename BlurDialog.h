#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QObject>
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
    BlurDialog(myWindow*, QImage*);
    ~BlurDialog();

private:
    Viewer *viewer;
    QLabel *text;
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    myWindow *mWin;
    QImage *apercu;

private slots:
    void repaintViewer(int);
    void applyBlur();
};

#endif // BLURDIALOG_H
