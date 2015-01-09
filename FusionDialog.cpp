
#include "FusionDialog.h"

FusionDialog::FusionDialog(QImage *img) : AbstractDialog() {
    imgSource = img;
    imgOpen = new QImage(img->width(), img->height(), QImage::Format_ARGB32);
    apercu = new QImage(*imgSource);

    textBrowser = new QLineEdit(this);
    textBrowser->move(20, 291);
    textBrowser->resize(260, 30);
    textBrowser->setReadOnly(true);

    openButton = new QPushButton("Ouvrir", this);
    openButton->move(280, 291);
    openButton->resize(120, 30);

    slider = new QSlider(Qt::Horizontal, this);
    slider->move(20, 320);
    slider->resize(120, 30);
    slider->setMaximum(255);
    slider->setSliderPosition(slider->maximum());

    label = new QLabel(this);
    label->move(160, 325);
    label->resize(120, 20);

    QObject::connect(openButton, SIGNAL(clicked()), this, SLOT(openFilename()));
    QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(writeOpacity(int)));

    writeOpacity(slider->value());
    display(apercu);
}

FusionDialog::~FusionDialog() {
    delete textBrowser;
    delete openButton;
    delete imgOpen;
    delete apercu;
    delete slider;
    delete label;
}

void FusionDialog::openFilename()
{
    QString filename = QFileDialog::getOpenFileName(this,
        "Ouvrir une image", QDir::currentPath() + "/../Projet-Image-M1-info/ressources", "Image Files (*.png *.jpg)");
    if (filename != "")
    {
        textBrowser->setText(filename);
        /*if (imgOpen == NULL) {
            imgOpen = new QImage(filename);
        } else {
            imgOpen->load(filename);
        }*/
        imgOpen->load(filename);
        //imgOpen->convertToFormat(QImage::Format_ARGB32);
        updateViewer();
    }
}

void FusionDialog::writeOpacity(int value) {
    label->setText("Opacité : " + QString::number(value));
    updateViewer();
}

void FusionDialog::updateViewer() {
    //delete apercu;
    calculFusion(imgOpen);
    display(apercu);

    /*if (textBrowser->text() == "") {
        display(apercu);
    } else {
        QImage tmp;
        if (tmp.load(textBrowser->text())) {
            // Fusionner tmp avec apercu
            //aperc
            display(apercu);
            ok_clicked = true;
        } else {
            QMessageBox messageBox(this);
            messageBox.setText("Aucune image, vérifier l'url ! ");
            messageBox.addButton("Ok", QMessageBox::AcceptRole);
            messageBox.exec();
            ok_clicked = false;
        }
    }*/
}

void FusionDialog::acceptDialog() {
    if (!ok_clicked) {
        updateViewer();
    }
    imgSource->swap(*apercu);
}

/* Calcul la fusion entre l'imgSource et la QImage passee en parametre */
void FusionDialog::calculFusion(QImage* img) {
    if (!img->isNull()) {
        double q = slider->value() / 255.0;
        double alpha;
        QRgb pixelSource, pixelOpen, color;

        for (int i = 0; i < imgSource->width(); i++)
        {
            for (int j = 0; j < imgSource->height(); j++)
            {
                pixelSource = imgSource->pixel(i, j);
                pixelOpen = img->pixel(i, j);
                alpha = qAlpha(pixelOpen) / 255.0;
                color = qRgba((1-q)*qRed(pixelSource) + q*qRed(pixelOpen),
                              (1-q)*qGreen(pixelSource) + q*qGreen(pixelOpen),
                              (1-q)*qBlue(pixelSource) + q*qBlue(pixelOpen),
                              255);
                apercu->setPixel(i, j, color);
            }
        }
    }
}
