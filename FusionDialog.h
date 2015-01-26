#ifndef FUSIONDIALOG_H
#define FUSIONDIALOG_H

#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QFileDialog>

#include "AbstractDialog.h"

class FusionDialog : public AbstractDialog {

    Q_OBJECT

public:
    FusionDialog(QImage*);
    ~FusionDialog();
    bool matchImage(int, int);

private:
    QImage *imgSource, *imgOpen, *apercu;
    QLineEdit *textBrowser;
    QPushButton *openButton;
    QSlider *slider;
    QLabel *label;
    int imgOpen_x, imgOpen_y;

public slots:
    void updateViewer();
    void acceptDialog();

private slots:
    void openFilename();
    void writeOpacity(int);

};

#endif // FUSIONDIALOG_H
