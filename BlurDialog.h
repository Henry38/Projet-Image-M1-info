#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QObject>
#include <QImage>
#include <QLabel>
#include <QSpinBox>

#include "AbstractDialog.h"
#include "Convolution.h"

namespace Ui {
    class AbstractDialog;
}

class BlurDialog : public AbstractDialog {

    Q_OBJECT

public:
    BlurDialog(QImage*);
    ~BlurDialog();

private:
    QLabel *text, *label;
    QSpinBox *spinBox;
    QImage *imgSource, *apercu;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();
};

#endif // BLURDIALOG_H
