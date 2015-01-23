#ifndef HISTODIALOG_H
#define HISTODIALOG_H

#include <QObject>
#include "AbstractDialog.h"
#include "QImage"
#include "Histogramme.h"
#include "QGroupBox"
#include "HistoRGB.h"
#include "HistoYUV.h"
#include "QSlider"

class HistoDialog  : public AbstractDialog
{
    Q_OBJECT

public:
    HistoDialog(QImage *img);
    ~HistoDialog();


    // AbstractDialog interface
public slots:
    void updateViewer();
    void acceptDialog();

private slots:
    void egalisation();
    void etalement();
    void annulerOperation();
    void afficherLignesRGB();
    void afficherLignesYUV();

private:

    bool RGB;
    int operation;

    QGroupBox choixCouleur;
    QGroupBox choixOperation;

    QLabel conteneurHisto;
    HistoRGB histoRGB;
    HistoYUV histoYUV;
    QImage *img;
};

#endif // HISTODIALOG_H
