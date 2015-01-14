#ifndef BLURDIALOG_H
#define BLURDIALOG_H

#include <QObject>
#include <QImage>
#include <QLabel>
#include <QSpinBox>

#include "AbstractDialog.h"
#include "Convolution.h"

class BlurDialog : public AbstractDialog {

    Q_OBJECT

public:
    BlurDialog(QImage*);
    ~BlurDialog();

private:
    QLabel *text;
    QSpinBox *spinBox;
    QImage *imgSource, *apercu;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();

private slots:
    void spinBoxChanged(int);

};

#endif // BLURDIALOG_H
