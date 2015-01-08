#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QScrollArea>

namespace Ui {
    class AbstractDialog;
}

class AbstractDialog : public QDialog {

    Q_OBJECT

public:
    AbstractDialog();
    ~AbstractDialog();
    QScrollArea* getViewer();

public slots:
    virtual void updateViewer() = 0;
    virtual void acceptDialog() = 0;

public:
    Ui::AbstractDialog *ui;
};

#endif // ABSTRACTDIALOG_H
