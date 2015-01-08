
#include "FusionDialog.h"

FusionDialog::FusionDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    apercu = NULL;//new QImage(*imgSource);

    textBrowser = new QLineEdit(this);
    textBrowser->move(20, 220);
    textBrowser->resize(200, 30);

    openButton = new QPushButton("Ouvrir", this);
    openButton->move(220, 220);
    openButton->resize(120, 30);

    QObject::connect(openButton, SIGNAL(clicked()), this, SLOT(openFilename()));

    updateViewer();
}

FusionDialog::~FusionDialog() {
    delete textBrowser;
    delete openButton;
    delete apercu;
}

void FusionDialog::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg)");
    if (filename != "")
    {
        textBrowser->setText(filename);
    }
}

void FusionDialog::updateViewer() {
    delete apercu;
    apercu = new QImage(*imgSource);
    if (textBrowser->text() == "") {
        display(apercu);
    } else {
        QImage tmp;
        if (tmp.load(textBrowser->text())) {
            // Fusionner tmp avec apercu

            display(apercu);
            ok_clicked = true;
        } else {
            QMessageBox messageBox(this);
            messageBox.setText("Url fausse !");
            messageBox.addButton("Ok", QMessageBox::AcceptRole);
            messageBox.exec();
            ok_clicked = false;
        }
    }
}

void FusionDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}
