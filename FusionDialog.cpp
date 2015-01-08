
#include "myWindow.h"
#include "FusionDialog.h"
#include "ui_test.h"

FusionDialog::FusionDialog(QImage *img) : QDialog(0), ui(new Ui::FusionDialog) {
    ui->setupUi(this);

    m_label = new QLabel();
    m_label->setPixmap(QPixmap::fromImage(*img));
    ui->scrollArea->setWidget(m_label);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openFilename()));
}

FusionDialog::~FusionDialog() {
    delete ui;
    delete m_label;
    delete img1, img2;
}

QImage calculFusion(QImage img1, QImage img2) {

    return QImage();
}

void FusionDialog::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg)");
    if (filename != "")
    {
        ui->textBrowser->setText(filename);
        img2->load(filename);

        m_label->setPixmap(QPixmap::fromImage(calculFusion(*img1, *img2)));

        /*QImage *tmp = new QImage(filename);
        m_label2->setPixmap(QPixmap::fromImage(*tmp));
        ui->scrollArea->setWidget(m_label2);
        ui->scrollArea->repaint();*/
    }
}
