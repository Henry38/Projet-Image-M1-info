#ifndef FUSIONDIALOG_H
#define FUSIONDIALOG_H

/*#include <QDialog>
#include <QDialogButtonBox>
#include <QImage>*/

#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QSlider>
#include <QLabel>

#include "AbstractDialog.h"


class FusionDialog : public AbstractDialog {

    Q_OBJECT

public:
    FusionDialog(QImage*);
    ~FusionDialog();

private:
    QImage *imgSource, *imgOpen, *apercu;
    QLineEdit *textBrowser;
    QPushButton *openButton;
    QSlider *slider;
    QLabel *label;
    bool ok_clicked;
    int img_x, img_y;

public slots:
    void updateViewer();
    void acceptDialog();
    void calculFusion(QImage*);

private slots:
    void openFilename();
    void writeOpacity(int);

};

#endif // FUSIONDIALOG_H
