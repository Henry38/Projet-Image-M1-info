#include "HistoDialog.h"
#include <QLabel>
#include <QPixmap>
#include <qpoint.h>

HistoDialog::HistoDialog(QImage *img) : AbstractDialog(),conteneurHisto(this),h(img)
{
    h.afficheHisto();
    h.afficherLignes();
    this->img = img;
    setFixedSize(width()+h.width()+distBordGauche,getOKAnnuler().y() + h.height()+distBordHaut+distBordBas);

    conteneurHisto.move(width()-h.width() - distBordGauche,distBordHaut);
    conteneurHisto.setPixmap(QPixmap::fromImage(h));

    display(img);

}

HistoDialog::~HistoDialog()
{

}

void HistoDialog::updateViewer()
{
    h.afficheHisto();
    h.etalement(149,179);
    conteneurHisto.setPixmap(QPixmap::fromImage(h));
    display(h.getImg());
}

void HistoDialog::acceptDialog()
{
    *img = h.getImg()->copy(0,0,h.getImg()->width(),h.getImg()->height());
}


