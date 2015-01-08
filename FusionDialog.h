#ifndef FUSIONDIALOG_H
#define FUSIONDIALOG_H

/*#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QImage>*/

#include <QDialog>
#include <QLabel>
#include <QtGui>
#include <QtCore>
#include "Viewer.h"

namespace Ui {
    class FusionDialog;
}

class FusionDialog : public QDialog {

    Q_OBJECT

public:
    FusionDialog(QImage*);
    ~FusionDialog();

private:
    Ui::FusionDialog *ui;
    QLabel *m_label;
    QImage *img1, *img2;
    /*Viewer *viewer1;
    QPushButton *open1, *open2;
    QLineEdit *path1, *path2;
    QDialogButtonBox *buttonBox;
    QImage *imgSource;*/

private slots:
    void openFilename();

};

#endif // FUSIONDIALOG_H
