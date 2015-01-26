#ifndef ABSTRACTDIALOG_H
#define ABSTRACTDIALOG_H

#include <QtGui>
#include <QtCore>
#include <QDialog>
#include <QScrollArea>
#include <QLabel>

namespace Ui {
    class AbstractDialog;
}

class AbstractDialog : public QDialog {

    Q_OBJECT

public:
    // Methodes
    AbstractDialog();
    ~AbstractDialog();
    void display(QImage*);
    QPoint getOKAnnuler();
    QScrollArea *getScrollArea();

private:
    // Attributs
    QLabel *label;
    void resizeEvent(QResizeEvent *event);  // inutile ?


public slots:
    virtual void updateViewer() = 0;
    virtual void acceptDialog() = 0;

protected:
    Ui::AbstractDialog *ui;
    int distBordGauche;
    int distBordHaut;
    int distBordDroit;
    int distBordBas;
};

#endif // ABSTRACTDIALOG_H
