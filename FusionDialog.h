#ifndef FUSIONDIALOG_H
#define FUSIONDIALOG_H

/*#include <QDialog>
#include <QDialogButtonBox>
#include <QImage>*/

#include <QFileDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "AbstractDialog.h"


class FusionDialog : public AbstractDialog {

    Q_OBJECT

public:
    FusionDialog(QImage*);
    ~FusionDialog();

private:
    QImage *imgSource, *apercu;
    QLineEdit *textBrowser;
    QPushButton *openButton;
    bool ok_clicked;

public slots:
    void updateViewer();
    void acceptDialog();

private slots:
    void openFilename();

};

#endif // FUSIONDIALOG_H
