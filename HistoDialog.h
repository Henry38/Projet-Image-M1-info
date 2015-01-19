#ifndef HISTODIALOG_H
#define HISTODIALOG_H

#include "AbstractDialog.h"
#include "QImage"
#include "Histogramme.h"

class HistoDialog  : public AbstractDialog
{

public:
    HistoDialog(QImage *img);
    ~HistoDialog();


    // AbstractDialog interface
public slots:
    void updateViewer();
    void acceptDialog();

private:
     QLabel conteneurHisto;
     Histogramme h;
     QImage *img;
};

#endif // HISTODIALOG_H
