
#include "AbstractDialog.h"
#include "ui_AbstractDialog.h"

AbstractDialog::AbstractDialog() : QDialog(0), ui(new Ui::AbstractDialog)
{
    ui->setupUi(this);

    distBordGauche = ui->scrollArea->x();
    distBordHaut = ui->scrollArea->y();
    distBordDroit = 20;
    distBordBas = 20;

    label = new QLabel();
    label->setAlignment(Qt::AlignCenter);

    ui->scrollArea->setWidget(label);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(updateViewer()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptDialog()));


}

AbstractDialog::~AbstractDialog()
{
    delete ui;
    delete label;
}

/*affiche la QImage dans le QScrollArea*/
void AbstractDialog::display(QImage *img)
{
    label->setPixmap(QPixmap::fromImage(*img));
}

/*postionne les boutons OK en bas a droite de la fenetre*/
void AbstractDialog::resizeEvent(QResizeEvent *)
{
    ui->buttonBox->move(width()-ui->buttonBox->width()-distBordDroit,height()-ui->buttonBox->height()-distBordBas);
}

/*retourne la taille des boutons OK et annuler*/
QPoint AbstractDialog::getOKAnnuler()
{
    return QPoint(ui->buttonBox->width(), ui->buttonBox->height());
}

/*retourne la QScrollArea*/
QScrollArea *AbstractDialog::getScrollArea()
{
    return ui->scrollArea;
}
