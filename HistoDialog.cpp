#include "HistoDialog.h"
#include <qpoint.h>
#include "couple.h"

HistoDialog::HistoDialog(QImage *img) : AbstractDialog(),histoYUV(img), histoRGB(img), conteneurHisto(this), choixCouleur(this), choixOperation(this)
{
    histoRGB.afficheHisto();
    histoRGB.afficherLignes();
    this->img = img;
    RGB = true;
    setFixedSize(width()+histoRGB.width()+distBordGauche,getOKAnnuler().y() + histoRGB.height()+distBordHaut+distBordBas);

    conteneurHisto.move(width()-histoRGB.width() - distBordGauche,distBordHaut);
    conteneurHisto.setPixmap(QPixmap::fromImage(histoRGB));

    //création des choix de couleurs ---
    QRadioButton *RGB = new QRadioButton("RGB");
    QRadioButton *YUV = new QRadioButton("YUV");
    RGB->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(RGB);
    vbox->addWidget(YUV);
    choixCouleur.setLayout(vbox);
    choixCouleur.setStyleSheet("border: 1px solid black;");
    RGB->setStyleSheet("border: 0px solid black;");
    YUV->setStyleSheet("border: 0px solid black;");

    QObject::connect(RGB, SIGNAL(clicked()), this, SLOT(afficherLignesRGB()));
    QObject::connect(YUV, SIGNAL(clicked()), this, SLOT(afficherLignesYUV()));
    //--- fin creation choix couleur

    //création des choix d'operation ---
    QRadioButton *egalisation = new QRadioButton("egalisation");
    QRadioButton *etalement = new QRadioButton("etalement");
    QRadioButton *aucun = new QRadioButton("aucun");

    operation = 0;
    aucun->setChecked(true);

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(aucun);
    vbox2->addWidget(egalisation);
    vbox2->addWidget(etalement);

    choixOperation.setLayout(vbox2);
    choixOperation.setStyleSheet("border: 1px solid black;");

    egalisation->setStyleSheet("border: 0px solid black;");
    etalement->setStyleSheet("border: 0px solid black;");
    aucun->setStyleSheet("border: 0px solid black;");

    QObject::connect(egalisation, SIGNAL(clicked()), this, SLOT(egalisation()));
    QObject::connect(etalement, SIGNAL(clicked()), this, SLOT(etalement()));
    QObject::connect(aucun, SIGNAL(clicked()), this, SLOT(annulerOperation()));
    //--- fin creation choix operation
    

    choixCouleur.move(distBordGauche,getScrollArea()->height()+ distBordHaut*2);
    choixOperation.move(choixCouleur.x() + choixCouleur.width() + 15,choixCouleur.y());

    display(img);

}

HistoDialog::~HistoDialog()
{

}

void HistoDialog::afficherLignesRGB()
{
    RGB = true;
    if(operation == 0)
    {
        histoRGB.afficheHisto();
        histoRGB.afficherLignes();
        conteneurHisto.setPixmap(QPixmap::fromImage(histoRGB));
    }
    else if(operation == 1)
    {
        egalisation();
    }
    else
    {
        etalement();
    }
}

void HistoDialog::afficherLignesYUV()
{
    RGB = false;
    if(operation == 0)
    {
        histoYUV.afficheHisto();
        histoYUV.afficherLignes();
        conteneurHisto.setPixmap(QPixmap::fromImage(histoYUV));
    }
    else if(operation == 1)
    {
        egalisation();
    }
    else
    {
        etalement();
    }
}

void HistoDialog::updateViewer()
{
    if(RGB)
        display(histoRGB.getImg());
    else
        display(histoYUV.getImg());
}

void HistoDialog::acceptDialog()
{
    if(RGB)
        *img = histoRGB.getImg()->copy(0,0,histoRGB.getImg()->width(),histoRGB.getImg()->height());
    else
        *img = histoYUV.getImg()->copy(0,0,histoYUV.getImg()->width(),histoYUV.getImg()->height());
}

void HistoDialog::egalisation()
{
    Histogramme *h;
    if(operation == 1 || operation == 2)
    {
        histoRGB.reset(img);
        histoYUV.reset(img);
    }
    operation = 1;
    if(RGB)
    {
        h = &histoRGB;
        if(histoRGB.gray())
        {
            histoRGB.egalisation();
        }
    }
    else
    {
        h = &histoRGB;
        if(histoRGB.gray())
        {
            histoRGB.egalisation();
        }
    }
    h->afficheHisto();
    h->afficherLignes();
    conteneurHisto.setPixmap(QPixmap::fromImage(histoRGB));
}

void HistoDialog::etalement()
{
    Histogramme *h;
    if(operation == 1 || operation == 2)
    {
        histoRGB.reset(img);
        histoYUV.reset(img);
    }
    operation = 2;
    if(RGB)
    {
        h = &histoRGB;
        histoRGB.etalement();
    }
    else
    {
        h = &histoYUV;
        Couple c = histoYUV.getDelimitation(histoYUV.getY());
        histoYUV.etalement(c);
    }
    h->afficheHisto();
    h->afficherLignes();
    conteneurHisto.setPixmap(QPixmap::fromImage(*h));
}

void HistoDialog::annulerOperation()
{
    operation = 0;
    if(RGB)
    {
        histoRGB.setImg(img);
        histoRGB.afficheHisto();
        histoRGB.afficherLignes();
        conteneurHisto.setPixmap(QPixmap::fromImage(histoRGB));

    }
    else
    {
        histoYUV.setImg(img);
        histoYUV.afficheHisto();
        histoYUV.afficherLignes();
        conteneurHisto.setPixmap(QPixmap::fromImage(histoYUV));
    }
}


